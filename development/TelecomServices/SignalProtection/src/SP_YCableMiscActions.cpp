// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../SP_YCableMiscActions.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_Defects.h"
#include <ErrorService/FC_Error.h>
#include <T6100_Services.h>
#include <T6100_Dispatcher.h>
#include <T6100_MainAppIf.h>
#include <T6100_ShelfIf.h>
#include <T6100_SlotIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <Blackboard/FC_BoolRegion.h>
#include <Blackboard/FC_BbAction.h>
#include <CSM/CSM_SfpAppIf.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <CSM/CSM_CardStatus.h>
#include <CsPii/CSPII_CardIF.h>
#include <Diag/DIAG_AppIf.h>
#include <Diag/DIAG_TestResultRegion.h>
#include <Diag/DIAG_TestResult.h>


#ifdef __TARGET__
    int gSP_DebugTraceYCable = 1;
#else
    int gSP_DebugTraceYCable = 0;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////-----SP_YCablePollData action-------------------------------------------

SP_YCablePollData::SP_YCablePollData(uint32 tspiiIntf, TSPII_OpticalRegion* theRxOpticalRegion) :
    myPort(tspiiIntf),
    myRxOpticalRegion(theRxOpticalRegion)
{
	myIsConfigured = false;
	myRxMsg = 0;
}
SP_YCablePollData::~SP_YCablePollData()
{
}

bool SP_YCablePollData::SetPollData(uint8 theRxMsg)
{
	bool hasChanged = false;

	if (theRxMsg != myRxMsg)
	{
		myRxMsg = theRxMsg;
		hasChanged = true;
	}
	return hasChanged;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////-----SP_YCableEqptData-------------------------------------------

SP_YCableEqptData::SP_YCableEqptData(T6100_SfpIf* theSfpIf, uint8 idx) :
    mySfpIf(theSfpIf),
    myDefectIdx(idx)
{
	myCardFault = false; //Assume equipment ok to start with
	mySfpFault = false; //Assume sfp ok to start with
}
SP_YCableEqptData::~SP_YCableEqptData()
{
}

bool SP_YCableEqptData::SetCardData(bool theCardFault)
{
	bool hasChanged = false;

    if (theCardFault != myCardFault)
	{
		myCardFault = theCardFault;
		hasChanged = true;
	}

	return hasChanged;
}

bool SP_YCableEqptData::SetSfpData(bool theSfpFault)
{
	bool hasChanged = false;

    if (theSfpFault != mySfpFault)
	{
		mySfpFault = theSfpFault;
		hasChanged = true;
	}

	return hasChanged;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////-----SP_YCableMsgPollingAction action-------------------------------------------

SP_YCableMsgPollingAction * SP_YCableMsgPollingAction::itsInstance = NULL;

SP_YCableMsgPollingAction::SP_YCableMsgPollingAction(FC_BoolRegion& theIsrMonRegion, TSPII_OpticalRegion* mateOpticalRegion):
    myIsrMonRegion(theIsrMonRegion),
    myMateOpticalRegion(mateOpticalRegion)
{
    myProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, 500);
    myMateLos = false;

	//Set instance pointer
	itsInstance = this;
}

//##ModelId=38EDF51800A6
SP_YCableMsgPollingAction::~SP_YCableMsgPollingAction()
{
    myProcess->SuspendImmediate();
    delete myProcess;
    myProcess = NULL;

	//Free poll data memory
    myDataCollectionSet.clear();
}

SP_YCableMsgPollingAction* SP_YCableMsgPollingAction::GetInstance()
{
    if(itsInstance == NULL)
    {
		FC_THROW_ERROR(FC_NotSupportedError, "SP_YCableMsgPollingAction::GetInstance() Instance not set");
    }
    return itsInstance;
}

//##ModelId=3B8BC9D30390
void SP_YCableMsgPollingAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_YCableMsgPollingAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    
    bool hasChanged = false;
    uint8 rxMsg;
    uint32 PII_count;
    bool configured = false;
    int i;

	TSPII_OpticalRegion * theOpticalRegion = NULL;
    for (i=0; (uint32)i<myDataCollectionSet.size(); i++)
    {
		SP_YCablePollData* thePollData = myDataCollectionSet[i];
        if (thePollData->IsConfigured() == true)
        {
			theOpticalRegion = thePollData->GetOpticalRegion();
            rxMsg = (*theOpticalRegion)[0].GetRxYCableMessage();
            hasChanged |= thePollData->SetPollData(rxMsg);
            configured = true;
        }

    }

    //If atleast one group is configured, then check for mate presence.
    if (configured)
    {
        bool mateLos = false;
        PII_count = (*myMateOpticalRegion)[0].GetOptLOS();
		if(PII_count%2 != 0)
		{
            mateLos = true;
        }

        if (mateLos != myMateLos)
        {
            hasChanged = true;
            myMateLos = mateLos;
        }
    }
	
    if (hasChanged)
    {
        myIsrMonRegion.IncModificationCounter();
        myIsrMonRegion.UpdateNotify();
    }
    return NULL;
}

FC_PeriodicProcess* SP_YCableMsgPollingAction::GetProcessPtr()
{
    return myProcess;
}

void SP_YCableMsgPollingAction::InitializePollData(uint32 tspiiIntf, TSPII_OpticalRegion* theRxOpticalRegion)
{
    myDataCollectionSet.push_back(new SP_YCablePollData(tspiiIntf, theRxOpticalRegion));
}

void SP_YCableMsgPollingAction::SetConfiguration(bool isConfigured, uint32 tspiiIntf)
{
    if (gSP_DebugTraceYCable != 0)
    {
        if (isConfigured)
            fc_cout << "SP_YCableMsgPollingAction: Adding port " << tspiiIntf << " to polling list" << endl;
        else
            fc_cout << "SP_YCableMsgPollingAction: Removing port " << tspiiIntf << " from polling list" << endl;
    }

	for (int i=0; (uint32)i<myDataCollectionSet.size(); i++)
	{
		SP_YCablePollData* thePollData = myDataCollectionSet[i];
		if (thePollData->GetPort() == tspiiIntf)
		{
			thePollData->SetIsConfigured(isConfigured);
			break;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////-----SP_EqptFltDetectionAction action-------------------------------------------

//SP_EqptFltDetectionAction * SP_EqptFltDetectionAction::itsInstance = NULL;

SP_EqptFltDetectionAction::SP_EqptFltDetectionAction(FC_BoolRegion& theIsrMonRegion, TEL_BbRegionBaseImp<SP_Defects>& theDefectsRegion):
    myIsrMonRegion(theIsrMonRegion),
    myDefectsRegion(theDefectsRegion)
{
    myBbAction = new FC_BbAction(this);

    CT_ShelfId aShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
	CT_SlotId aSlotId = CSPII_CardIF::GetInstance()->GetSlotId();
    T6100_SlotIf* aSlot = T6100_MainAppIf::Instance().GetShelfPtr(aShelfId)->GetSlotPtr(aSlotId);
    
    myBbAction->AddInputRegion(&(aSlot->GetCsmApp().GetCardStatusRegion()));

	//Set instance pointer
	//itsInstance = this;
}

//##ModelId=38EDF51800A6
SP_EqptFltDetectionAction::~SP_EqptFltDetectionAction()
{
    CT_ShelfId aShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
	CT_SlotId aSlotId = CSPII_CardIF::GetInstance()->GetSlotId();
    T6100_SlotIf* aSlot = T6100_MainAppIf::Instance().GetShelfPtr(aShelfId)->GetSlotPtr(aSlotId);

    myBbAction->RemoveInputRegion(&(aSlot->GetCsmApp().GetCardStatusRegion()));

    T6100_SfpIf* aSfpIf = NULL;
    SP_YCableEqptData* theEqptData = NULL;
    for (int i=0; (uint32)i<myDataCollectionSet.size(); i++)
    {
        theEqptData = myDataCollectionSet[i];
        aSfpIf = theEqptData->GetSfpIntf();
        if (aSfpIf)
        {
            myBbAction->RemoveInputRegion(aSfpIf->GetDiagApp().GetTestResultRegionPtr());
        }
    }

    delete myBbAction;
    myBbAction = NULL;

    //Free poll data memory
    myDataCollectionSet.clear();
}

//SP_EqptFltDetectionAction* SP_EqptFltDetectionAction::GetInstance()
//{
//   if(itsInstance == NULL)
//    {
//		FC_THROW_ERROR(FC_NotSupportedError, "SP_EqptFltDetectionAction::GetInstance() Instance not set");
//    }
//    return itsInstance;
//}

//##ModelId=3B8BC9D30390
void SP_EqptFltDetectionAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_EqptFltDetectionAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    
    //For each pluggable device, check for CSM status
    //If different, then set has changed flag
    T6100_SfpIf* aSfpIf = NULL;
    CSM_CardStatus*  aCSMPtr = NULL;
    SP_YCableEqptData* theEqptData = NULL;
    bool aCardFault = false;
    bool aSfpFault = false;
    int i;
    bool hasChanged = false;

    CT_ShelfId aShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
	CT_SlotId aSlotId = CSPII_CardIF::GetInstance()->GetSlotId();

    T6100_SlotIf* aSlot = T6100_MainAppIf::Instance().GetShelfPtr(aShelfId)->GetSlotPtr(aSlotId);
    //Check for module fault conditions
    aCSMPtr = &(aSlot->GetCsmApp().GetCardStatusRegion()[0]);
    CT_Status aCardStatus = aCSMPtr->GetCardStatus();

    for (i=0; (uint32)i<myDataCollectionSet.size(); i++)
    {
        aSfpFault = false;
        theEqptData = myDataCollectionSet[i];
        aSfpIf = theEqptData->GetSfpIntf();

        if (aSfpIf)
        {
            DIAG_AppIf* aDiagAppPtr = aSfpIf->GetDiagAppPtr();
            if(aDiagAppPtr)
            {
                CT_EqAlarmStatus aAlarmStatus = CT_NO_EQ_ALARM;
                for( int j = 0; (size_t)j < aDiagAppPtr->GetTestResultRegionPtr()->Size();j++)
                {
                    DIAG_TestResult& aTestResult = (*aDiagAppPtr->GetTestResultRegionPtr())[j];
                    if(aTestResult.IsValid())
                    {
                        if( (aTestResult.GetResultValue() == CT_DIAG_RESULT_CRITICAL_FAILURE)||
                            (aTestResult.GetResultValue() == CT_DIAG_RESULT_MAJOR_FAILURE))
                        {
                            aSfpFault = true;
                            break;
                        }
                    }
                }
            }
        }
        
        aCardFault = ( (aCardStatus == CT_FAILED) );
        hasChanged |= theEqptData->SetCardData(aCardFault);
		hasChanged |= theEqptData->SetSfpData(aSfpFault);

        if(aCardFault)
        {
            hasChanged |= myDefectsRegion[(bbindex_t)theEqptData->GetDefectIdx()].SetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT, true, 1);
        }
        else
        {
            hasChanged |= myDefectsRegion[(bbindex_t)theEqptData->GetDefectIdx()].SetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT, false, 1);
        }

		if(aSfpFault)
        {
            hasChanged |= myDefectsRegion[(bbindex_t)theEqptData->GetDefectIdx()].SetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT, true, 1);
        }
        else
        {
            hasChanged |= myDefectsRegion[(bbindex_t)theEqptData->GetDefectIdx()].SetDefectStatus(CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT, false, 1);
        }
    }
    
    if (hasChanged)
    {
        myIsrMonRegion.IncModificationCounter();
        myIsrMonRegion.UpdateNotify();
    }
    
    return NULL;
}

void SP_EqptFltDetectionAction::InitializeEqptData(T6100_SfpIf* theEqptIf, uint8 theDefectIdx)
{
    myDataCollectionSet.push_back(new SP_YCableEqptData(theEqptIf, theDefectIdx));
    if (theEqptIf)
    {
        myBbAction->AddInputRegion(theEqptIf->GetDiagApp().GetTestResultRegionPtr(), false);
    }
}