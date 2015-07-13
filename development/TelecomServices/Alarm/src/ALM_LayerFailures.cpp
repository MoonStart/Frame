/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette, Patrick Meehan
 DESCRIPTION:   This class represents all failures with in a layer for
                Signal Alarm. The class object, when instantiated, is the
                primary interface to MON for retrieving, soaking, and updating
                the Signal Alarm region.
--------------------------------------------------------------------------*/

#include <Blackboard/FC_BbRegion.h>
#include <T6100_Dispatcher.h>
#include <CsPii/CSPII_CardIF.h>
#include <ErrorService/FC_Error.h>
#include <T6100_CardActiveRegion.h>

#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include "ALM_NormalFailure.h"
#include <Alarm/ALM_SubApplicationOnCard.h>

#include "ALM_LayerFailures.h"


//-----------------------------------------------------------------
//##ModelId=3C506C32013D
ALM_LayerFailures::ALM_LayerFailures (
        const ALM_FailureNb theNbOfFailure,
        ALM_IndexNb theIndex,
        ALM_AppIf& theApplication,
        ALM_LayerFailures* theHigherLayerPtr,
        const ALM_FailureNb theNbOfSigProtSoakFailure):

    itsNbOfFailure (theNbOfFailure),
    itsNbOfSigProtSoakFailure (theNbOfSigProtSoakFailure),
    itsIndex (theIndex),
    itsFilteredFailureRegionPtr(theApplication.GetFilteredRegionPtr()),
    itsFilteredFailureBase((*theApplication.GetFilteredRegionPtr())[theIndex]),
    myApplication(dynamic_cast<ALM_SubApplicationOnCard&>(theApplication)),
    itsHigherLayerPtr(theHigherLayerPtr),
    itsDefectFilterType(ALM_FILTER_LOCAL),
    itsFailureFilterType(ALM_FILTER_LOCAL),
    itsFilteredFailure(0),
    itsRawFailure(0),
    itsSigProtSoakDefect(NULL)
{
    //--------------------------------------------------------------------
    // Get memory to keep the reference to Failure object and init it to 0.
    // This will be done for both itsFailureTable and itsSigProtSoakFailureTable.
    //--------------------------------------------------------------------
    GetInitFailurePtr();

    // Allocate defect status memory.
    itsDefect = new ALM_DefectStatus[theNbOfFailure];

    if (itsNbOfSigProtSoakFailure) // default 0
    {
        itsSigProtSoakDefect = new ALM_DefectStatus[itsNbOfSigProtSoakFailure];
    }
}


//-----------------------------------------------------------------
//##ModelId=3C506C320151
ALM_LayerFailures::~ALM_LayerFailures ()
{
    // Release the array of Failure object pointers
    delete [] itsFailureTable;
    delete [] itsDefect;

    // Release the array, if it was created!
    if (itsSigProtSoakFailureTable)
    {
        delete [] itsSigProtSoakFailureTable;
        delete [] itsSigProtSoakDefect;
    }
}


//-----------------------------------------------------------------
//##ModelId=3C506C320153
void ALM_LayerFailures::Run (FC_Object* theObject)
{
    FC_THROW_ERROR( FC_NotSupportedError, "Run not supported" );
}

//-----------------------------------------------------------------
//##ModelId=3DBFFAE4030A
FC_Object* ALM_LayerFailures::DoRunWithReason(unsigned theRunReason,
                                FC_Object* theInvoker, FC_Object* theParam)
{
    int32 aFailureIndex;

    // Temp failure status
    bool aFailureStatus;

    //Bit filed that represents all defects of this layer.
    ALM_BitField aBitFieldDefect = 0;

    //If context is valid, read the defect from the monitor and processed
    if (myApplication.GetContextStatusRegion().GetActive())
    {

        //Read all defects within a layer and filters status only.
        //It is not necessary to filter the counters.
        aBitFieldDefect = Filter(ReadDefects());

        //Directive from the higher layer
        if( itsHigherLayerPtr )
        {
            if (itsHigherLayerPtr->GetDefectFilterType() == ALM_FILTER_ALL)
                aBitFieldDefect &= GetNoFilterMask(); //Filter all defects according to layer mask.
        }
    }

    // Directive to filter defects of lower layer
    if( aBitFieldDefect & GetFilterAllMask() )
    {
        itsDefectFilterType = ALM_FILTER_ALL;
    } else {
        itsDefectFilterType = ALM_FILTER_LOCAL;
    }

    itsRawFailure = 0;
    ALM_BitField aMask = 1;

    // For each defect in this layer, inform the Failure object of the status and
    // transition counter value, get the status of the failures
    // and store them into the BB.
    for( aFailureIndex = 0; aFailureIndex<itsNbOfFailure; aFailureIndex++ )
    {
        // informs the Failure object of the status and transition counter and
        // get the status of the failure. If the failure requires soaking, the
        // soaking action is performed here.
        aFailureStatus = itsFailureTable[aFailureIndex]->
            DefectUpdated( (aBitFieldDefect & aMask) ? true : false, itsDefect[aFailureIndex].GetTCount() );

        itsRawFailure += (aFailureStatus ? aMask : 0);
        aMask <<= 1;
    }

    //Some derived class as behavior to do AFTER the defect are soaked, call it
    ProcessAfterSoaking();

    //Processed with the filtering of failure
    //Directive from the higher layer
    if( itsHigherLayerPtr )
    {
        if (itsHigherLayerPtr->GetFailureFilterType() == ALM_FILTER_ALL)
            itsRawFailure &= GetNoFilterMask(); //Filter all failures according to layer mask.
    }

    // If a change to the failure status has occurred, update the failure
    // in the Signal Alarm blackboard region.
    FailureFiltering();

    // Directive to filter the lower layer
    if( itsFilteredFailure & GetFilterAllMask() )
    {
        itsFailureFilterType = ALM_FILTER_ALL;
    } else {
        itsFailureFilterType = ALM_FILTER_LOCAL;
    }

    //---------------------------------------------------------------------
    // Now handle the Signal Protection Soak alarms (i.e. PROTNA).
    // Notice that if itsSigProtSoakFailureTable[i] == NULL,
    // meaning that the SP condition is not valid for this layer,
    // the for() loop will skip this SP condition type.
    //---------------------------------------------------------------------
    for( aFailureIndex = 0; aFailureIndex<itsNbOfSigProtSoakFailure; aFailureIndex++ )
    {
      if ( itsSigProtSoakFailureTable[aFailureIndex] ) // check for NULL
      {
        aFailureStatus = itsSigProtSoakFailureTable[aFailureIndex]->DefectUpdated
                       ( itsSigProtSoakDefect[aFailureIndex].GetStatus(),
                         itsSigProtSoakDefect[aFailureIndex].GetTCount() );

        CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType = GetSigProtSoakTypeFromIndex(aFailureIndex);

        //-----------------------------------------------------
        // If the filtered failure goes from false to true or
        // from true to false set the occurring time.
        //-----------------------------------------------------
        if (itsFilteredFailureBase.GetSigProtStatus(theFailureType) != aFailureStatus)
        {
            if (aFailureStatus == true) // report defect!
            {
                itsFilteredFailureBase.ReportSigProtDefect(theFailureType, itsSigProtSoakDefect[aFailureIndex].GetYCablePROTNA());
            }
            else
            {
                itsFilteredFailureBase.ClearSigProtDefect (theFailureType, itsSigProtSoakDefect[aFailureIndex].GetYCablePROTNA());
            }
            itsFilteredFailureRegionPtr->IncModificationCounter();
        }
      }
    }

    return NULL;
}

//-----------------------------------------------------------------
//##ModelId=3C506C320166
void ALM_LayerFailures::FailureFiltering()
{
    int32 aFailureIndex;

    // Temp failure status
    bool aFailureStatus;

    // Temp occurring time
    time_t anOccurTime;

    // mask
    ALM_BitField aMask = 1;

    // Process with the filtering of all failures
    itsFilteredFailure = Filter(itsRawFailure);

    // Set the occurring time if the failure condition changed
    for( aFailureIndex = 0; aFailureIndex < itsNbOfFailure; aFailureIndex++ )
    {
        // Get the status of the filtered failure
        aFailureStatus = (itsFilteredFailure & aMask) ? true : false;

        // If the filtered failure goes from false to true or
        // from true to false set the occurring time
        if (itsFilteredFailureBase.GetStatusFromIndex(aFailureIndex) != aFailureStatus)
        {
            // Get the occurring time form system library
            anOccurTime = CSPII_CardIF::GetInstance()->GetUTCTime();
            // Set the failure into the BB
            itsFilteredFailureBase.SetStatusFromIndex (aFailureIndex, aFailureStatus);
            // Set the occurring time into the BB
            itsFilteredFailureBase.SetOccurTimeFromIndex(aFailureIndex, anOccurTime);
            // Increment assiciated region modification counter
            itsFilteredFailureRegionPtr->IncModificationCounter();
        }

        aMask <<= 1;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C506C320179
ALM_BitField ALM_LayerFailures::Filter(ALM_BitField theFailure) const
{
    return theFailure;
}

//-----------------------------------------------------------------
//##ModelId=3C506C32022D
void ALM_LayerFailures::AddAt(ALM_FailureNb theIndex, ALM_NormalFailure *theFailurePtr)
{
    itsFailureTable[theIndex] = theFailurePtr;
}

//-----------------------------------------------------------------
void ALM_LayerFailures::AddSigProtSoakAt(ALM_FailureNb theIndex, ALM_NormalFailure *theFailurePtr)
{
    itsSigProtSoakFailureTable[theIndex] = theFailurePtr;
}

//-----------------------------------------------------------------
//##ModelId=3C506C320273
void ALM_LayerFailures::GetInitFailurePtr()
{
    // Get memory to keep the reference to Failure object
    itsFailureTable = new ALM_NormalFailure*[itsNbOfFailure];

    for (ALM_FailureNb i = 0; i < itsNbOfFailure; i++)
    {
        // Init every pointer to 0
        itsFailureTable[i] = NULL;
    }

    //-------------------------------------------------------
    // For the SigProtSoak table, we will initialize the ptr
    // to the array of pointers (see class definition) to NULL
    // because it is possible that there are NO SOAK failures.
    //-------------------------------------------------------
    itsSigProtSoakFailureTable = NULL;

    if (itsNbOfSigProtSoakFailure) // default 0
    {
        // Get memory to keep the reference to Failure object
        itsSigProtSoakFailureTable = new ALM_NormalFailure*[itsNbOfSigProtSoakFailure];

        for (ALM_FailureNb i = 0; i < itsNbOfSigProtSoakFailure; i++)
        {
            // Init every pointer to 0
            itsSigProtSoakFailureTable[i] = NULL;
        }
    }
}

//-----------------------------------------------------------------
//##ModelId=3C95FE08021A
void ALM_LayerFailures::Reset()
{
    int32 aFailureIndex;

    //Initialise all parameters of the action

    //Init the filtewr type of this layer
    itsDefectFilterType = ALM_FILTER_LOCAL;
    itsFailureFilterType = ALM_FILTER_LOCAL;

    //Reset the state of all soaking machine and defect status
    for( aFailureIndex = 0; aFailureIndex<itsNbOfFailure; aFailureIndex++ )
    {
        //Reset soaking machine
        itsFailureTable[aFailureIndex]->Reset();
        //Reset defect status
        itsDefect[aFailureIndex].Reset();
    }

    //Reset the state of all Signal Protect soaking machine
    if (itsSigProtSoakFailureTable)
    {
        for( aFailureIndex = 0; aFailureIndex<itsNbOfSigProtSoakFailure; aFailureIndex++ )
        {
            if ( itsSigProtSoakFailureTable[aFailureIndex] ) // check for NULL
            {
                //Reset soaking machine
                itsSigProtSoakFailureTable[aFailureIndex]->Reset();
                //Reset defect status
                itsSigProtSoakDefect[aFailureIndex].Reset();
            }
        }
    }
}

//-----------------------------------------------------------------
//##ModelId=3CC4D1D201A2
bool ALM_LayerFailures::MaskAllDefect() const
{
    return myApplication.GetMaskAllDefectFlag(itsIndex);
}

//-----------------------------------------------------------------
//##ModelId=3C506C320242
void ALM_LayerFailures::ProcessAfterSoaking()
{
    // do nothing. Inheriting classes define behavior!
}

//-----------------------------------------------------------------
//##ModelId=3F954C3000DD
ALM_BitField ALM_LayerFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    // By default filters everyting.
    return 0;
}

//------------------------------------------------------------------
CT_TelAlarmCondition::CT_FacilityAlarmType ALM_LayerFailures::GetSigProtSoakTypeFromIndex(int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;

    //return the Signal Protect defect type corresponding to the index
    switch(theIndex)
    {
        case SOAK_SP_NOT_SA:            aFailureType = CT_TelAlarmCondition::ALM_SP_NOT_SA;           break;
        case SOAK_SP_STRM_A_NR:         aFailureType = CT_TelAlarmCondition::ALM_SP_STRM_A_NR;        break;
        case SOAK_SP_ALM_MATE_ID:       aFailureType = CT_TelAlarmCondition::ALM_SP_ALM_MATE_ID;      break;
        case SOAK_SP_PROTNA_UID:        aFailureType = CT_TelAlarmCondition::ALM_SP_PROTNA_UID;       break;
        case SOAK_SP_ODUKP_NOT_SA:      aFailureType = CT_TelAlarmCondition::ALM_SP_ODUKP_NOT_SA;     break;
        case SOAK_SP_ODUKP_PROTNA_UID:  aFailureType = CT_TelAlarmCondition::ALM_SP_ODUKP_PROTNA_UID; break;

        case SOAK_SP_FOP_PM_UID:        aFailureType = CT_TelAlarmCondition::ALM_SP_FOP_PM_UID;          break;
        case SOAK_SP_FOP_NR_UID:        aFailureType = CT_TelAlarmCondition::ALM_SP_FOP_NR_UID;          break;
        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid Sig Prot Soak index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

