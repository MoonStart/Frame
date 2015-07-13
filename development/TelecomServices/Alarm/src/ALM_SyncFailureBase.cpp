/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Luc Charbonneau
 DESCRIPTION:   This class defines the failure type of Sync.
--------------------------------------------------------------------------*/

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

#include "../ALM_SyncFailureBase.h"


//--------------------------------------------------------------------------

ALM_SyncFailureBase::ALM_SyncFailureBase(int theIndex, bool theDefaultStatus):
    ALM_FailureBase (theIndex, ALM_NB_OF_FAILURE, theDefaultStatus)
{
}

//--------------------------------------------------------------------------

ALM_SyncFailureBase::~ALM_SyncFailureBase()
{
}

//--------------------------------------------------------------------------

int ALM_SyncFailureBase::GetIndexFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType) const
{
    int aFailureIndex;

    // return the index coresponding to the failure type.
    switch(theFailureType)
    {
        case CT_TelAlarmCondition::ALM_FREERUN_SYNC:     aFailureIndex = FREERUN_SYNC;     break;
        case CT_TelAlarmCondition::ALM_HOLDOVER_SYNC:    aFailureIndex = HOLDOVER_SYNC;    break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid SYNC Failure type.");
            break;
    }

    return aFailureIndex;
}

//--------------------------------------------------------------------------

CT_TelAlarmCondition::CT_FacilityAlarmType ALM_SyncFailureBase::GetTypeFromIndex( int theIndex) const
{
    CT_TelAlarmCondition::CT_FacilityAlarmType aFailureType;
    
    //return the failure type corresponding to the index
    switch(theIndex)
    {
        case FREERUN_SYNC:     aFailureType = CT_TelAlarmCondition::ALM_FREERUN_SYNC;     break;
        case HOLDOVER_SYNC:    aFailureType = CT_TelAlarmCondition::ALM_HOLDOVER_SYNC;    break;

        default:
            FC_THROW_ERROR(FC_ValueOutOfRangeError, "ALM: Invalid SYNC index.");
            break;
    }

    // give the failure type given the index.
    return aFailureType;
}

//--------------------------------------------------------------------------

void ALM_SyncFailureBase::PrintHeader() const
{
    /*
    fc_cout << endl
         << "----------------------------------------------------------------------\n"
         << "     FREERUN:   HOLDOVER: \n"
         << "     ---------  --------- \n"
         << "#    f ft(UTC): f ft(UTC):\n";
     */
    fc_cout << endl
         << "--------------------------\n"
         << "    FREERUN:    HOLDOVER: \n"
         << "    ----------  ---------- \n";
}

// SERIALIZATION
// Text mode
//--------------------------------------------------------------------------

ostream& ALM_SyncFailureBase::WriteObject (ostream& theStream)
{
    theStream   << FC_InsertVar(itsIndex);
    theStream   << FC_InsertVar(itsStatus[FREERUN_SYNC]);
    theStream   << FC_InsertVar(itsStatus[HOLDOVER_SYNC]);
    theStream   << FC_InsertVar(itsOccurTime[FREERUN_SYNC]);
    theStream   << FC_InsertVar(itsOccurTime[HOLDOVER_SYNC]);

    return theStream;
}

//--------------------------------------------------------------------------
istream& ALM_SyncFailureBase::ReadObject  (istream& theStream)
{
    theStream   >> FC_ExtractVar(itsIndex);
    theStream   >> FC_ExtractVar(itsStatus[FREERUN_SYNC]);
    theStream   >> FC_ExtractVar(itsStatus[HOLDOVER_SYNC]);
    theStream   >> FC_ExtractVar(itsOccurTime[FREERUN_SYNC]);
    theStream   >> FC_ExtractVar(itsOccurTime[HOLDOVER_SYNC]);

    return theStream;
}
