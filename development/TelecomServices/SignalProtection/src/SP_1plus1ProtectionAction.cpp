// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <cstdio>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <ExecutionSupport/FC_EventLogger.h>
#include <SignalProtection/SP_1plus1SubApplication.h>

#include "../SP_SwitchingStatistic.h"
#include "../SP_ProtectionGroupStatusRegion.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_1plus1ProtectionGroupConfig.h"
#include "../SP_1plus1ProtectionGroupStatus.h"
#include "../SP_1plus1APSController.h"
#include "../SP_1plus1FsmLogger.h"
#include "../SP_1plus1RequestParser.h"
#include "../SP_1plus1Selector.h"
#include "../SP_1plus1K1K2Transmitter.h"
#include "../SP_TestMenu.h"
#include "../SP_DefectProcessorAction.h"
#include "../SP_SwitchingCommand.h"
#include "../SP_Utilities.h"
#include "../SP_SelectorPositionRegion.h"
#include "../SP_OduKSnc.h"
#include <Blackboard/FC_BbAction.h>
#include <Blackboard/FC_BbRegionId.h>
#include <Blackboard/FC_BbRegion.h>
#include <SignalProtection/SP_SCTestMenu.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_VcgBaseApplication.h>
#include <Configuration/CFG_AppIf.h>
#include <Monitoring/MON_MsDefects.h>
#include <Monitoring/MON_MsStatus.h>
#include <TsPii/TSPII_SubApplication.h>
#include <Configuration/CFG_MsProt.h>
#include <Configuration/CFG_Opt.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <Alarm/ALM_AppIf.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <TsPii/TSPII_Region.h>
#include <CsPii/CSPII_CardIF.h>
#include <TimeService/FC_TimePrecise.h>

extern int gSP_DebugTraceYCable;
extern int gSP_DebugTraceSnc;


FC_Fsm SP_1plus1ProtectionAction::ourFsm;

SP_1plus1ProtectionAction::SP_1plus1ProtectionAction(SP_Application & theApplIf) :
    SP_ProtectionAction(theApplIf),
    myLastCommand(CT_SP_NO_REQUEST),
    myLastCommandID(0),
    myRequestParserPtr(NULL),
    mySelectorPtr(NULL), // Configured in derived class
    myAPSControllerPtr(NULL),
    myK1K2TransmitterPtr(NULL),
    mySwitchingStat(NULL,NULL),
    myIndex(-1),
    myDefectProcessor(NULL),
    myCfgMsRegion(NULL,NULL),
    mySyncRegion(NULL),
    myOduSncInstance(NULL),
    myMonDefectsRegion(NULL,NULL),
    myMonStatusRegion(NULL,NULL),
    mySendHopIndication (false),
    myDoingWarmRestart(false),
    myLastStatus(CT_SP_NO_REQUEST),
    myNotifSoakTimer(5*1000),
    myNotifSoak(false),
    myConfigMismatchHoldoffCount(0),
    myBiSwitchingChanged(false),
    myFopNrOnRequestedEntity(false),
    myFopNrTimerOnRequestedEntity(*GetBbAction())
{
    myProtectionConfig = SP_1plus1ProtectionGroupConfig(); //set to default config
    myMONObjectIndex.working = myMONObjectIndex.protection = -1;
    myTspiiInterfaces.working = myTspiiInterfaces.protection = TSPII_DONT_CARE;
    mySPDefects.working = mySPDefects.protection = NULL;

    // Make sure the 1+1 FSM is initialized before creating the APS controller.
    SP_1plus1APSController::InitFsm(ourFsm);

    // This counter assumes that actions are created in the same order as in the region
    static int count = 0;
    char anID[10];
    sprintf(anID, "%i", count);
    myLogger = new SP_1plus1FsmLogger(anID);
    count++;
    myRequestParserPtr   = new SP_1plus1RequestParser(*this);
    myK1K2TransmitterPtr = new SP_1plus1K1K2Transmitter(*this);
    myAPSControllerPtr   = new SP_1plus1APSController(*this, 
                                                      *myRequestParserPtr, 
                                                      *myK1K2TransmitterPtr, 
                                                      myLogger,
                                                      ourFsm);

}

SP_1plus1ProtectionAction::~SP_1plus1ProtectionAction()
{
    delete myRequestParserPtr;
    delete mySelectorPtr;
    delete myAPSControllerPtr;
    delete myK1K2TransmitterPtr;
    delete myLogger;
    delete mySwitchingStat.working;
    delete mySwitchingStat.protection;
    if (myOduSncInstance)
    {
        delete myOduSncInstance;
        myOduSncInstance = NULL;
    }
}

FC_Object*  SP_1plus1ProtectionAction::DoRunWithReason(unsigned theRunReason,
                                                       FC_Object* theInvokerObj,
                                                       FC_Object* theParam)
{
    // Do not run anything if where are not enabled
    if (stopped) return NULL;

    //indicate that this action is allowed to operate
    if (theRunReason == SP_DEFECT_REASON_COMMIT ||
        theRunReason == SP_DEFECT_REASON_NO_COMMIT)
        AllowOperation();

    // Do not run anything if we are not enabled
    // or not allowed to operate
    if (!IsEnabled() || !IsAllowedToOperate())
        return NULL;

    FC_TimePrecise time_start;
    time_start.GetCurrentTime();
    if (SP_TestMenu::mySpDebug)
    {
        Log("1+1", theRunReason, theInvokerObj, theParam);
        fc_cout <<endl<<"======================="<<endl;
        fc_cout << dec << uint32(time_start.GetUTCTime()) << "sec " << dec << uint32(time_start.GetFractionalTime()) << "ms" << endl;
        fc_cout << "[SP_1plus1ProtectionAction]Enter-GPID:" <<dec<< (uint32) myProtectionConfig.GetGroupID() 
                << " PQW/W:" << (uint32) myProtectionConfig.GetSources().working.GetChannelId()
                << " PQW/P:" << (uint32) myProtectionConfig.GetSources().protection.GetChannelId()
                << endl;
        if( theRunReason == 0x100 || theRunReason == 0x2000 || theRunReason == 0x8008)
        {
            // output obj information
            if(theInvokerObj)
            {
                FC_BbRegion* aPtr = dynamic_cast<FC_BbRegion*>(theInvokerObj);
                if(aPtr)
                {
                    FC_BbRegionId aRegionId(*aPtr);
                    fc_cout <<"REGION: " << aRegionId << endl;
                }
                else
                {
                    fc_cout <<"CLASS: " << theInvokerObj->GetObjClassName() << endl;
                }
            }			
        }
    }
    //Log an event (DEBUG PUPOSE)
    if (SP_TestMenu::mySpEventLog)
        FC_EventRecord(EVENT_SP_INVOKED,0);

    if (theRunReason == SP_CONFIG_REFRESH_REASON)
    {
        RefreshConfiguration();
    }
    
    // Update the current request
    myRequestParserPtr->RunWithReason(theRunReason, this, theParam);

    // Run APS controller only if not locked
    if (GetConfig().GetState() != CT_SP_LOCKED)
    {
        try
        {
            // clear any unstable state machine indication
            myAPSControllerPtr->MarkAsStable();

            myAPSControllerPtr->RunWithReason(theRunReason, this, theParam);
        }
        catch (FC_OperationTimeoutError&)
        {
            // indicate to stabe machine that it is unstable
            myAPSControllerPtr->MarkAsUnstable();

            // Force one last execution (for now, it as no effect)
            myAPSControllerPtr->SingleRun();
        }
    }

    //Update signal selection
    if (mySelectorPtr) mySelectorPtr->RunWithReason(theRunReason, this, theParam);

    // Update APS message to transmit in linear 1+1
    if ((Get1plus1Config().Get1plus1Type() == CT_SP_LINEAR) &&
        (Get1plus1Config().GetDirectionMode() == CT_SP_BIDIRECTIONAL))
        myK1K2TransmitterPtr->RunWithReason(theRunReason, this, theParam);

    if(Get1plus1Config().IsBiSwitching())
    {
        CheckFopNr();
    }

    // Update the status of the switch with the latest changes
    if (theRunReason != SP_DEFECT_REASON_NO_COMMIT)
        GetAppIf().GetStatusCollectionAction()->RunWithReason(theRunReason, this, theParam);

    //Perform any clean up and housekeeping functions
    PostRun();

    if (Get1plus1Config().Get1plus1Type() == CT_SP_LINEAR)
    {
        myCfgMsRegion.working->UpdateNotify();
        myCfgMsRegion.protection->UpdateNotify();
    }
    else if (Get1plus1Config().Get1plus1Type() == CT_SP_TIMING)
    {
        if (mySyncRegion)
            mySyncRegion->UpdateNotify();
    }
    else if (Get1plus1Config().IsBiSwitching())
    {
        SetTxApsBytes(true);
    }

    FC_TimePrecise time_end;
    time_end.GetCurrentTime();

    if (gSP_DebugTraceSnc) printf("[%10ld:%6ld]:--------------------------------------PG[%d] End-----------------------------------------\n", uint32(time_end.GetUTCTime()), uint32(time_end.GetFractionalTime()), Get1plus1Config().GetGroupID());
    if (SP_TestMenu::mySpDebug)
    {
        #ifdef __TARGET__
        uint32 rxApsBytes = Get1plus1Config().IsBiSwitching()? GetApsBytes() : 0 ;
        printf("PG[%d], [%10ld:%6ld], [%10ld:%6ld], <%x, %x, %x, %x>, <%x, %x>\n",
               Get1plus1Config().GetGroupID(),
               uint32(time_start.GetUTCTime()), uint32(time_start.GetFractionalTime()),//start time
               uint32(time_end.GetUTCTime()), uint32(time_end.GetFractionalTime()),//end time
               myRequestParserPtr->GetHighestRequest().working, myRequestParserPtr->GetHighestRequest().protection,//defect on W,P
               myRequestParserPtr->GetCommand().myRequest, rxApsBytes, //command, Rx APS bytes
               myRequestParserPtr->GetBestSide(), myTxApsBytes // best side, Tx APS bytes
               );
        #endif
    }
    return NULL;
}

void SP_1plus1ProtectionAction::Enable()
{
    //set up the index of this protection group
    SetMyIndex();

    // Setup working stat objects
    {
        // Init new stat value
        if (mySwitchingStat.working) delete mySwitchingStat.working;
        mySwitchingStat.working = new SP_SwitchingStatistic();
        mySwitchingStat.working->SetCurrentlyActive(false);
        mySwitchingStat.working->SetInvolvedInProtection(true);
        mySwitchingStat.working->SetProtecting(false);
        mySwitchingStat.working->MarkAsChanged();
    }
    // Setup protection stat objects
    {
        // Init new stat value
        if (mySwitchingStat.protection) delete mySwitchingStat.protection;
        mySwitchingStat.protection = new SP_SwitchingStatistic();
        mySwitchingStat.protection->SetCurrentlyActive(false);
        mySwitchingStat.protection->SetInvolvedInProtection(true);
        mySwitchingStat.protection->SetProtecting(true);
        mySwitchingStat.protection->MarkAsChanged();
    }
    

    //Register to write kbytes
    SetupKbyteTransmit();

    //For timing protection register to write to the sync region
    if (Get1plus1Config().Get1plus1Type() == CT_SP_TIMING)
    {
        T6100_TelecomIf* theSyncIntfPtr = GetAppIf().GetCardContext().GetSyncIfPtr();
        if (theSyncIntfPtr)
        {
            if (theSyncIntfPtr->GetCfgCardAppPtr())
            {
                mySyncRegion = GetAppIf().GetCardContext().GetSyncIf().GetCfgCardApp().GetProtCfgRegion();
                GetBbAction()->AddOutputRegion(mySyncRegion, false, false);
            }
        }
    }

    //register for defects
    RegisterToMONDefects();

    //Get initial selection
    CT_SP_Protection initialSelection = GetInitialSelection();

    // Reset APS controller
    //SPECIAL HANDLING FOR WARM RESTART
    //SPECIAL HANDLING IF AN INITIAL SELECTION MODE IS SPECIFIED
    if (myDoingWarmRestart || (initialSelection != CT_SP_INVALID_PROTECTION_SIDE)) 
    {
        CT_SP_Protection currentSelection;
        if (initialSelection != CT_SP_INVALID_PROTECTION_SIDE)
            currentSelection = initialSelection;
        else
            currentSelection = GetCurrentSelection();

        if (currentSelection == CT_SP_PROTECTION_SIDE)
        {
            //protection was active prior to restart
            SP_SwitchingCommand* aCommand = &(static_cast<SP_1plus1SubApplication&>(GetAppIf()).GetCommandRegion()[myIndex]);
            if (aCommand->GetCommand() == CT_SP_1PLUS1_MS_P ||
                aCommand->GetCommand() == CT_SP_1PLUS1_FS_P)
            {
                //if there is a user command to protection, init to COMMAND_TO_PROTECTION
                CT_SP_CommandType aCommandType(aCommand->GetCommand());
                myRequestParserPtr->SetSwitchingCommand(aCommandType);
                myRequestParserPtr->InitWarm();
                myLastCommand = aCommand->GetCommand();
                // save command ID 
                myLastCommandID = aCommand->GetCommandID();
                myAPSControllerPtr->Restart(S_COMMAND_TO_PROTECTION, C_1PLUS1_SYNC, T_1PLUS1_SYNC);
                myAPSControllerPtr->SetLastState(S_COMMAND_TO_PROTECTION);
                
                
                
                //Set up kbyte transmitter
                myK1K2TransmitterPtr->SetAPSChannel(CT_SP_PROTECTION_SIDE);
                CT_SP_Request aProtectionRequest = myRequestParserPtr->GetHighestRequest().working;
                
                if(Get1plus1Config().IsBiSwitching())
                {
                    PrepareTxApsBytes(1, aProtectionRequest, myRequestParserPtr->GetHighestRequestIsRemote().working);
                    SetTxApsBytes(true);
                }
                myK1K2TransmitterPtr->SetRequest(myAPSControllerPtr->ConvertRequestToK1Request(aProtectionRequest));
            }
            else
            {
                //no user command to protection, init to DNR
                myAPSControllerPtr->Restart(S_PROTECTION_NO_REQUEST, C_1PLUS1_SYNC, T_1PLUS1_SYNC);
                myAPSControllerPtr->SetLastState(S_PROTECTION_NO_REQUEST);
            }
            if (mySelectorPtr) mySelectorPtr->SelectProtection();  
        }
        else if (currentSelection == CT_SP_WORKING_SIDE)
        {
            //working was active prior to restart
            //save off any manual commands
            SP_SwitchingCommand* aCommand = &(static_cast <SP_1plus1SubApplication&>(GetAppIf()).GetCommandRegion()[myIndex]);
            if (aCommand->GetCommand() == CT_SP_1PLUS1_MS_W ||
                aCommand->GetCommand() == CT_SP_1PLUS1_FS_W ||
                aCommand->GetCommand() == CT_SP_1PLUS1_LK_P)
            {
                CT_SP_CommandType aCommandType(aCommand->GetCommand());
                myRequestParserPtr->SetSwitchingCommand(aCommandType);
                myRequestParserPtr->InitWarm();
                myLastCommand = aCommand->GetCommand();
                // save command ID 
                myLastCommandID = aCommand->GetCommandID();

                myK1K2TransmitterPtr->SetAPSChannel(CT_SP_WORKING_SIDE);
                CT_SP_Request aProtectionRequest = myRequestParserPtr->GetHighestRequest().protection;

                if(Get1plus1Config().IsBiSwitching())
                {
                    PrepareTxApsBytes(0,aProtectionRequest,myRequestParserPtr->GetHighestRequestIsRemote().working);
                    SetTxApsBytes(true);
                }    
                
                myK1K2TransmitterPtr->SetRequest(myAPSControllerPtr->ConvertRequestToK1Request(aProtectionRequest));
            }
            myAPSControllerPtr->Restart(S_WORKING_SELECTED, C_1PLUS1_SYNC, T_1PLUS1_SYNC);
            myAPSControllerPtr->SetLastState(S_WORKING_SELECTED);
            if (mySelectorPtr) mySelectorPtr->SelectWorking();
        }
        else
        {
            //Invalid side.
            //This is a valid state when timing protection is configured.
            //It means that we are in internal timing mode.
            //Default the state machine to working if no manual commands exist
            //that force it to protection side.
            if (Get1plus1Config().Get1plus1Type() == CT_SP_TIMING)
            {
                //the selected side is not usable
                myRequestParserPtr->BestSideUsable(false);
                
                SP_SwitchingCommand* aCommand = &(static_cast<SP_1plus1SubApplication&>(GetAppIf()).GetCommandRegion()[myIndex]);
                if (aCommand->GetCommand() == CT_SP_1PLUS1_MS_P ||
                    aCommand->GetCommand() == CT_SP_1PLUS1_FS_P)
                {
                    //if there is a user command to protection, init to COMMAND_TO_PROTECTION
                    CT_SP_CommandType aCommandType(aCommand->GetCommand());
                    myRequestParserPtr->SetSwitchingCommand(aCommandType);
                    myRequestParserPtr->InitWarm();
                    myLastCommand = aCommand->GetCommand();
                    // save command ID 
                    myLastCommandID = aCommand->GetCommandID();
                    myAPSControllerPtr->Restart(S_COMMAND_TO_PROTECTION, C_1PLUS1_SYNC, T_1PLUS1_SYNC);
                    myAPSControllerPtr->SetLastState(S_COMMAND_TO_PROTECTION);
                    if (mySelectorPtr) mySelectorPtr->SelectProtection();

                    myK1K2TransmitterPtr->SetAPSChannel(CT_SP_PROTECTION_SIDE);
                    CT_SP_Request aProtectionRequest = myRequestParserPtr->GetHighestRequest().working;
                    myK1K2TransmitterPtr->SetRequest(myAPSControllerPtr->ConvertRequestToK1Request(aProtectionRequest));
                }
                else
                {
                    if (aCommand->GetCommand() == CT_SP_1PLUS1_MS_W ||
                        aCommand->GetCommand() == CT_SP_1PLUS1_FS_W ||
                        aCommand->GetCommand() == CT_SP_1PLUS1_LK_P)
                    {
                        CT_SP_CommandType aCommandType(aCommand->GetCommand());
                        myRequestParserPtr->SetSwitchingCommand(aCommandType);
                        myRequestParserPtr->InitWarm();
                        myLastCommand = aCommand->GetCommand();
                        // save command ID 
                        myLastCommandID = aCommand->GetCommandID();

                        myK1K2TransmitterPtr->SetAPSChannel(CT_SP_WORKING_SIDE);
                        CT_SP_Request aProtectionRequest = myRequestParserPtr->GetHighestRequest().protection;
                        myK1K2TransmitterPtr->SetRequest(myAPSControllerPtr->ConvertRequestToK1Request(aProtectionRequest));
                    }
                    myAPSControllerPtr->Restart(S_WORKING_SELECTED, C_1PLUS1_SYNC, T_1PLUS1_SYNC);
                    myAPSControllerPtr->SetLastState(S_WORKING_SELECTED);
                    if (mySelectorPtr) mySelectorPtr->SelectWorking();
                }
            }
        }
    } //END WARM RESTART CODE
    else
    {
        myAPSControllerPtr->Reset();
        // Clear any command left in the parser
        myRequestParserPtr->Reset();
        
        //reset K1K2 transmitter. Applicable in LAPS mode only
        if (Get1plus1Config().Get1plus1Type() == CT_SP_LINEAR)
        {
            myK1K2TransmitterPtr->Reset();
        }

        //reset selector to default selection and bridge
        if (mySelectorPtr) mySelectorPtr->Reset();
    }

    // Call base class
    SP_ProtectionAction::Enable();

    //Calculate and send hop indication
    mySendHopIndication = true;

    //Reset the last processed status
    myLastStatus=CT_SP_NO_REQUEST;
    myNotifSoak = false;

    myBiSwitchingChanged = false;

    myConfigMismatchHoldoffCount=0;

    // Update the status of the switch with the latest changes
    GetAppIf().GetStatusCollectionAction()->RunWithReason(0, this, 0);


}


void SP_1plus1ProtectionAction::Disable()
{
    // Reset APS controllers
    myAPSControllerPtr->Reset();

    // disable working stat objects
    {
        mySwitchingStat.working->SetCurrentlyActive(false);
        mySwitchingStat.working->SetInvolvedInProtection(false);
        mySwitchingStat.working->MarkAsChanged();
    }
    // disable protection stat objects
    {
        mySwitchingStat.protection->SetCurrentlyActive(false);
        mySwitchingStat.protection->SetInvolvedInProtection(false);
        mySwitchingStat.protection->MarkAsChanged();
    }
    

    //For LAPS reset kbytes and stop writing kbytes to CFG
    if (Get1plus1Config().Get1plus1Type() == CT_SP_LINEAR)
    {
        myK1K2TransmitterPtr->Reset(); //reset the kbytes to a default value
        GetBbAction()->RemoveOutputRegion(myCfgMsRegion.working);
        GetBbAction()->RemoveOutputRegion(myCfgMsRegion.protection);
    }

    //indicate that the selected side is not usable (used only for timing protection)
    myRequestParserPtr->BestSideUsable(false);

    if (mySelectorPtr) mySelectorPtr->Reset();

    // Stop timer of request parser (for hold off)
    myRequestParserPtr->StopTimers();

    //For timing protection stop provisioning the Sync region
    //NOTE: This has to be done after the selector has been reset
    if (Get1plus1Config().Get1plus1Type() == CT_SP_TIMING)
    {
        if (mySyncRegion)
            GetBbAction()->RemoveOutputRegion(mySyncRegion);
    }

    //UnregisterFromMonDefects
    UnregisterFromMONDefects();

    myTspiiInterfaces.working = myTspiiInterfaces.protection = TSPII_DONT_CARE;
    mySPDefects.working = mySPDefects.protection = NULL;

    //Stop sending hop indications
    mySendHopIndication = false;

    myFopNrOnRequestedEntity = false;
    myRequestParserPtr->SetFopPmToggle(false);

    //calculate service status
    CalculateServiceStatus(true); //forced clear

    //Clear the last processed command and id
    myLastCommand=CT_SP_NO_REQUEST;
    myLastCommandID=0;

    //Clear the last processed status
    myLastStatus=CT_SP_NO_REQUEST;
    myNotifSoak = false;

    myBiSwitchingChanged = false;

    RefreshAps();

    // Call base class
    SP_ProtectionAction::Disable();

    // Update the status of the switch with the latest changes
    GetAppIf().GetStatusCollectionAction()->RunWithReason(0, this, 0);

}


CT_SP_CommandResultCode SP_1plus1ProtectionAction::ExecuteSwitchingCommand(CT_SP_CommandType theCommand, CT_SP_CommandID theCommandID)
{
    //if the command and command id match
    //return completed
    if (myLastCommand == theCommand.myRequest &&
        myLastCommandID == theCommandID)
        return CT_SP_COMMAND_COMPLETED;

    // execute the command on the request parser
    CT_SP_CommandResultCode aResult = CT_SP_COMMAND_FAILED;

    // Don't accept any command if we're locked
    if (Get1plus1Config().GetState() != CT_SP_LOCKED)
        aResult = myRequestParserPtr->SetSwitchingCommand(theCommand);
    else
        aResult = CT_SP_COMMAND_DENIED;

    CT_SP_1plus1Type protectionType = Get1plus1Config().Get1plus1Type();
    if (protectionType==CT_SP_SNCN || protectionType==CT_SP_SNCI || protectionType==CT_SP_SNCS)
    {
        if (myOduSncInstance)
        {
            if (aResult==CT_SP_COMMAND_COMPLETED)
            {
                bool bSourceLocalWorking = false;
                bool bSourceLocalProtection = false;
                if (Get1plus1Config().GetSources().working.GetShelfId() == CSPII_CardIF::GetInstance()->GetShelfId() &&
                    Get1plus1Config().GetSources().working.GetSlotId() == CSPII_CardIF::GetInstance()->GetSlotId())
                {
                    bSourceLocalWorking = true;
                }
                if (Get1plus1Config().GetSources().protection.GetShelfId() == CSPII_CardIF::GetInstance()->GetShelfId() &&
                    Get1plus1Config().GetSources().protection.GetSlotId() == CSPII_CardIF::GetInstance()->GetSlotId())
                {
                    bSourceLocalProtection = true;
                }
                if(bSourceLocalWorking)
                {
                    if(theCommand.myRequest == CT_SP_1PLUS1_LK_P || theCommand.myRequest == CT_SP_1PLUS1_FS_P || theCommand.myRequest == CT_SP_1PLUS1_FS_W || myOduSncInstance->IsDropContinue(CT_SP_WORKING_SIDE))
                    {
                        myOduSncInstance->SetFppSquelchEnabled(false);
                    }
                    else if(theCommand.myRequest == CT_SP_NO_REQUEST || theCommand.myRequest==CT_SP_1PLUS1_CLEAR || theCommand.myRequest==CT_SP_1PLUS1_MS_P | theCommand.myRequest==CT_SP_1PLUS1_MS_W)
                    {
                        myOduSncInstance->SetFppSquelchEnabled(true);
                    }
                }
                if(bSourceLocalProtection)
                {
                    if(theCommand.myRequest == CT_SP_1PLUS1_LK_P || theCommand.myRequest == CT_SP_1PLUS1_FS_P || theCommand.myRequest == CT_SP_1PLUS1_FS_W || myOduSncInstance->IsDropContinue(CT_SP_PROTECTION_SIDE))
                    {
                        myOduSncInstance->SetFppSquelchEnabled(false);
                    }
                    else if(theCommand.myRequest == CT_SP_NO_REQUEST || theCommand.myRequest==CT_SP_1PLUS1_CLEAR || theCommand.myRequest==CT_SP_1PLUS1_MS_P | theCommand.myRequest==CT_SP_1PLUS1_MS_W)
                    {
                        myOduSncInstance->SetFppSquelchEnabled(true);
                    }
                }
            }
        }
    }

    // save command ID 
    myLastCommandID = theCommandID;

    // Force the execution of the command if successfull
    if (aResult == CT_SP_COMMAND_COMPLETED || aResult == CT_SP_COMMAND_PENDING)
    {
#ifdef WIN32
        // Immediately run the action (because of the test parser)
        GetBbAction()->RunWithReason(SP_SWITCHING_COMMAND_REASON_IMMEDIAT,this, &theCommand);
#else
        // Schedule the process to run to apply the new configuration changes
        GetLowPriorityWakeUpAction().RunWithReason(SP_SWITCHING_COMMAND_REASON, this, &theCommand);
#endif
        // save command
        myLastCommand = theCommand.myRequest;
    }

    // Update the status to reflect processed command id change
    GetAppIf().GetStatusCollectionAction()->RunWithReason(0, this, 0);

    return aResult;
}


bool SP_1plus1ProtectionAction::DelayedUpdateStatus(SP_ProtectionGroupStatusRegion& theStatusRegion,
                                                    CT_SP_ProtectionPair<TEL_BbRegionBaseImp<SP_SwitchingStatistic>*>& theStatRegions)
{
    if (myIndex != -1)
    {
        SP_1plus1ProtectionGroupStatus& a1plus1Status = dynamic_cast<SP_1plus1ProtectionGroupStatus&>(theStatusRegion[myIndex]);
        CT_SP_1plus1Type protectionType = Get1plus1Config().Get1plus1Type();

        bool changed = false;
        if (IsEnabled())
        {
            // Check on which side is the best
            CT_SP_Request aRequest;

            // none is the best
             //check if we are sending DO NOT REVERT or WTR 
            SP_K1Request aK1Request = myK1K2TransmitterPtr->GetTransmittedKbytes().request;
            CT_SP_Protection aSide = mySelectorPtr ? mySelectorPtr->GetSelection() : CT_SP_WORKING_SIDE;
            //a1plus1Status.SetSelectedSide(aSide);

            //set the last processed command id
            //a1plus1Status.SetLastProcessedCommandID(myLastCommandID);

            switch (aK1Request)
            {
                case SP_1PLUS1_K1_DO_NOT_REVERT: aRequest = CT_SP_1PLUS1_DO_NOT_REVERT; break;
                case SP_1PLUS1_K1_WTR:           aRequest = CT_SP_1PLUS1_WTR; break;
                case SP_1PLUS1_K1_LP:            aRequest = CT_SP_1PLUS1_LK_P; break;
                case SP_1PLUS1_K1_FS:
                    {
                        switch (aSide)
                        {
                            case CT_SP_WORKING_SIDE:    aRequest = CT_SP_1PLUS1_FS_W; break;
                            case CT_SP_PROTECTION_SIDE: aRequest = CT_SP_1PLUS1_FS_P; break;
                            default:                    aRequest = CT_SP_NO_REQUEST; break;
                        }
                        break;
                    }
                case SP_1PLUS1_K1_SF_H:
                case SP_1PLUS1_K1_SF_L:
                    {
                        switch (aSide)
                        {
                            case CT_SP_WORKING_SIDE:    aRequest = CT_SP_1PLUS1_SF_P; break;
                            case CT_SP_PROTECTION_SIDE: aRequest = CT_SP_1PLUS1_SF_W; break;
                            default:                    aRequest = CT_SP_NO_REQUEST; break;
                        }

                        //For timing protection with only one source defined
                        //the protection source is always considered failed.
                        //Adjust the status so that SF-P never shows up in the status
                        if (protectionType == CT_SP_TIMING &&
                            Get1plus1Config().GetSources().protection.IsDefault())
                        {
                            aRequest = CT_SP_NO_REQUEST;
                            if (myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SF)
                                aRequest = CT_SP_1PLUS1_SF_W;
                        }
                        break;
                    }
                case SP_1PLUS1_K1_SD_H:
                case SP_1PLUS1_K1_SD_L:
                    {
                        switch (aSide)
                        {
                            case CT_SP_WORKING_SIDE:    aRequest = CT_SP_1PLUS1_SD_P; break;
                            case CT_SP_PROTECTION_SIDE: aRequest = CT_SP_1PLUS1_SD_W; break;
                            default:                    aRequest = CT_SP_NO_REQUEST; break;
                        }
                        //In timing protection mode, degrade means
                        //that the SSM is lower in quality.
                        //The protection status returned to upper layers
                        //should not be degrade in this situation but rather
                        //should be set according to the following rules:
                        //1. NR if revertive, or non revertive and on working
                        //side. 
                        //2. For non-revertive protect side set status to DNR
                        if (protectionType == CT_SP_TIMING)
                        {
                            aRequest = CT_SP_NO_REQUEST;
                            if ((aSide == CT_SP_PROTECTION_SIDE) && (Get1plus1Config().GetRevertiveMode() == false))
                                aRequest = CT_SP_1PLUS1_DO_NOT_REVERT;

                        }

                        break;
                    }
                case SP_1PLUS1_K1_MS:
                    {
                        switch (aSide)
                        {
                            case CT_SP_WORKING_SIDE:    aRequest = CT_SP_1PLUS1_MS_W; break;
                            case CT_SP_PROTECTION_SIDE: aRequest = CT_SP_1PLUS1_MS_P; break;
                            default:                    aRequest = CT_SP_NO_REQUEST; break;
                        }
                        break;
                    }
                default:                         aRequest = CT_SP_NO_REQUEST; break;
            }

    


            if ( (myNotifSoak == false) ||
                 (myNotifSoak == true && myNotifSoakTimer.IsExpired() )
               )
            {

                a1plus1Status.SetSelectedSide(aSide);

                //set the last processed command id
                a1plus1Status.SetLastProcessedCommandID(myLastCommandID);

                //Update best side usable
                changed |= a1plus1Status.SetSelectedSideUsable(myRequestParserPtr->IsBestSideUsable());

                // Update auto switch reason with current defect of unit
                // Request are always local in 1+1 unidir
                // Set same request in both unit status
                changed |= a1plus1Status.GetProtectionUnits().SetAutoSwitchReason(myRequestParserPtr->GetDefectStatus().working, CT_SP_WORKING_SIDE);
                changed |= a1plus1Status.GetProtectionUnits().SetAutoSwitchReason(myRequestParserPtr->GetDefectStatus().protection, CT_SP_PROTECTION_SIDE);
                changed |= a1plus1Status.GetProtectionUnits().SetRemoteOrLocal(CT_SP_LOCAL_REQUEST);
                changed |= a1plus1Status.GetProtectionUnits().SetRequest(aRequest);  

                //Adjust auto switch reason for timing protection schemes
                //For timing protection schemes with only one source,
                //do not display the protection as failed.
                //Do not display SD in auto switch reason either.
                if (protectionType == CT_SP_TIMING)
                {
                    //adjust SD
                    switch (myRequestParserPtr->GetDefectStatus().working)
                    {
                    case CT_SP_AUTO_SD:
                        a1plus1Status.GetProtectionUnits().SetAutoSwitchReason(CT_SP_AUTO_NONE, CT_SP_WORKING_SIDE);
                        break;
                    default:
                        break;
                    }
                    switch (myRequestParserPtr->GetDefectStatus().protection)
                    {
                        case CT_SP_AUTO_SD:
                        a1plus1Status.GetProtectionUnits().SetAutoSwitchReason(CT_SP_AUTO_NONE, CT_SP_PROTECTION_SIDE);
                        break;
                    default:
                        break;
                    }
                    //adjust SF on P
                    if (Get1plus1Config().GetSources().protection.IsDefault())
                    {
                        a1plus1Status.GetProtectionUnits().SetAutoSwitchReason(CT_SP_AUTO_NONE, CT_SP_PROTECTION_SIDE);
                    }    
                }

                // BISNC, status change
                if (Get1plus1Config().IsBiSwitching())
                {
                    CT_SP_Location requestLocation;

                    uint32 apsBytes = myTxApsBytes;
                    APS_BYTES* apsByptesStr = reinterpret_cast<APS_BYTES*>(&apsBytes);

                    if (apsByptesStr->requestAndProtType.request != CT_SP_APS_REQUEST_RR)
                    {
                        CT_SP_ProtectionPair<CT_SP_Request> spRequest(CT_SP_NO_REQUEST, CT_SP_NO_REQUEST);
                        myRequestParserPtr->ConvertApsRequestToSpRequest(*apsByptesStr, spRequest);

                        aRequest = myRequestParserPtr->GetHighestPriorityRequest(spRequest.working, spRequest.protection);

                        requestLocation = CT_SP_LOCAL_REQUEST;
                    }
                    else // remote request has the highest priority
                    {
                        aRequest = myRequestParserPtr->GetEffectiveRequest();
                        requestLocation = CT_SP_REMOTE_REQUEST;
                    }

                    if (gSP_DebugTraceSnc) printf("BISNC:++++: PG(%d), Status(%s), remote(%d)\n", myIndex + 1, DISPLAY_CT_SP_Request_1PLUS1(aRequest), (int)requestLocation);

                    changed |= a1plus1Status.GetProtectionUnits().SetRequest(aRequest);

                    changed |= a1plus1Status.GetProtectionUnits().SetRemoteOrLocal(requestLocation);

                    if (gSP_DebugTraceSnc)
                        fc_cout  << " DelayedUpdateStatus 1111 PgId is " << (uint32)(myIndex + 1) 
                            << " actualApsType old is "  << (uint32)a1plus1Status.GetProtectionUnits().GetActualApsBidir()
                            << " new is " <<(uint32) myRequestParserPtr->GetActualApsBidir() << endl;

                    changed |= a1plus1Status.GetProtectionUnits().SetActualApsBidir(myRequestParserPtr->GetActualApsBidir());


                }else
                {
                    if (gSP_DebugTraceSnc)
                         fc_cout  << " DelayedUpdateStatus 2222 PgId is " << (uint32)(myIndex + 1) 
                            << " actualApsType old is "  << (uint32)a1plus1Status.GetProtectionUnits().GetActualApsBidir()
                            << " new is " <<(uint32) myRequestParserPtr->GetActualApsBidir() << endl;

                    changed |= a1plus1Status.GetProtectionUnits().SetActualApsBidir(myRequestParserPtr->GetActualApsBidir());
                }

                changed |= DoSpecificStatusUpdate(a1plus1Status);
            }
            else
            {
                //Wake up status collector after timer has expired
               GetAppIf().GetLongDelayStatusCollectionAction()->RunWithReason(0, this, 0);
            }

            // Start a notification soak timer after a SF/SD condition to avoid
            // notification floods.
            if (aRequest == CT_SP_1PLUS1_SD_P ||
                aRequest == CT_SP_1PLUS1_SD_W ||
                aRequest == CT_SP_1PLUS1_SF_P ||
                aRequest == CT_SP_1PLUS1_SF_W)
            {
                if (myLastStatus != aRequest)
                {
                    myNotifSoakTimer.Start();
                    myNotifSoak = true;
                }
            }

            if (myNotifSoak == true && myNotifSoakTimer.IsExpired())
                myNotifSoak = false;

            //Save the last request
            myLastStatus = aRequest;
        }
        else // not enabled
        {
            // reset unit status to default status
            a1plus1Status.GetProtectionUnits().Init(CONFIG_RST);
            changed = true;
        }

        // Notify statistics region of possible changes
        // Only for protection schemes that support stats
        if (protectionType == CT_SP_LINEAR ||
            protectionType == CT_SP_DPRING ||
            protectionType == CT_SP_OAPS ||
            protectionType == CT_SP_YCABLE ||
            protectionType == CT_SP_SNCN ||
            protectionType == CT_SP_SNCI ||
            protectionType == CT_SP_SNCS )
        {
            if (mySwitchingStat.working->HasChangedSinceLastCheck())
            {
                // Copy statistics to Stat Region and notify region
                (*theStatRegions.working)[myIndex] = *mySwitchingStat.working;
                changed = true;
                //send hop indication
                mySendHopIndication = true;
            }

            if (mySwitchingStat.protection->HasChangedSinceLastCheck())
            {
                // Copy statistics to Stat Region and notify region
                (*theStatRegions.protection)[myIndex] = *mySwitchingStat.protection;
                changed = true;
                //send hop indication
                mySendHopIndication = true;
            }
        }

        //calculate service status
        CalculateServiceStatus(false); //not forced


        return changed;
    }
    else
        return false;

}

SP_ProtectionGroupConfig& SP_1plus1ProtectionAction::GetConfig()
{
    SP_ProtectionGroupConfig& aConfig = static_cast<SP_ProtectionGroupConfig&>(myProtectionConfig);
    return aConfig;
}

SP_1plus1ProtectionGroupConfig& SP_1plus1ProtectionAction::Get1plus1Config()
{
    SP_1plus1ProtectionGroupConfig& aConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(myProtectionConfig);
    return aConfig;
}

CT_SP_CommandID SP_1plus1ProtectionAction::GetLastCommandID()
{
    return myLastCommandID;
}

CT_SP_Request SP_1plus1ProtectionAction::GetLastCommandPriority()
{
    return myLastCommand;
}

bool SP_1plus1ProtectionAction::IsProtectionGroupDifferent(SP_ProtectionGroupConfig& theConfig)
{
    SP_1plus1ProtectionGroupConfig& aConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(theConfig);
    if (myProtectionConfig.InUse() != aConfig.InUse() ||
        myProtectionConfig.Get1plus1Type() != aConfig.Get1plus1Type() ||
        myProtectionConfig.GetSources().working != aConfig.GetSources().working ||
        myProtectionConfig.GetSources().protection != aConfig.GetSources().protection)
    {
        return true;
    }
    else
        return false;
}

bool SP_1plus1ProtectionAction::CopyConfiguration(SP_ProtectionGroupConfig& theConfig)
{
    bool hasChanged = true;
    SP_1plus1ProtectionGroupConfig& aOldConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(myProtectionConfig);
    SP_1plus1ProtectionGroupConfig& aConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(theConfig);

    if (aOldConfig == aConfig)
        hasChanged = false;
    else
    {
        myBiSwitchingChanged = (myProtectionConfig.IsBiSwitching() != aConfig.IsBiSwitching());
        printf("BISNC:++++: SP_1plus1ProtectionAction::CopyConfiguration, myBiSwitchingChanged(%d)\n", myBiSwitchingChanged);
        myProtectionConfig = theConfig;
    }
    return hasChanged;
}

void SP_1plus1ProtectionAction::RegisterToMONDefects()
{
    //Get the defect processor associated with this protection scheme.
    //Register to the defect processor
    SP_1plus1SubApplication& theApp = static_cast<SP_1plus1SubApplication&>(GetAppIf());
    CT_IntfId theWorkingPort   = myProtectionConfig.GetSources().working.GetPortId();
    CT_IntfId theProtectPort   = myProtectionConfig.GetSources().protection.GetPortId();
    CT_ShelfId theWorkingShelf = myProtectionConfig.GetSources().working.GetShelfId();
    CT_ShelfId theProtectShelf = myProtectionConfig.GetSources().protection.GetShelfId();
    CT_SlotId theWorkingSlot   = myProtectionConfig.GetSources().working.GetSlotId();
    CT_SlotId theProtectSlot   = myProtectionConfig.GetSources().protection.GetSlotId();

    CT_SP_1plus1Type protectionType = myProtectionConfig.Get1plus1Type();
    if (protectionType == CT_SP_SNCN ||
        protectionType == CT_SP_SNCI ||
        protectionType == CT_SP_SNCS )
    {
        CT_ODU_Identifier aWOduIdentifier((uint32)theWorkingPort);
        CT_ODU_Identifier aPOduIdentifier((uint32)theProtectPort);
        theWorkingPort = myOduSncInstance->GetClientOduKPort(aWOduIdentifier);
        theProtectPort = myOduSncInstance->GetClientOduKPort(aPOduIdentifier);

        //Adjust the shelf/slot to point to our shelf and slot.
        if (myOduSncInstance->GetIndex(CT_SP_WORKING_SIDE) != -1)
        {
            theProtectShelf = theWorkingShelf;
            theProtectSlot = theWorkingSlot;
        }

        if (myOduSncInstance->GetIndex(CT_SP_PROTECTION_SIDE) != -1)
        {
            theWorkingShelf = theProtectShelf;
            theWorkingSlot = theProtectSlot;
        }
    }

    myDefectProcessor = theApp.GetDefectProcessor(myProtectionConfig.Get1plus1Type(), myProtectionConfig.GetSources().working.GetPortType(), theWorkingPort, theProtectPort);
    if (myDefectProcessor == NULL)
    {
        //Get using alternate method
        myDefectProcessor = theApp.GetDefectProcessor(myProtectionConfig.Get1plus1Type(), myProtectionConfig.GetSources().working.GetPortType(), theWorkingSlot, theWorkingPort, theProtectSlot, theProtectPort);
    }

    FC_THROW_ERROR_IF(myDefectProcessor == NULL,
                      FC_RuntimeError,
                      "Unable to retrieve defect processor");

    myDefectProcessor->RegisterForDefects(this, theWorkingShelf, theWorkingSlot, theWorkingPort, theProtectShelf, theProtectSlot, theProtectPort);

    //Register for MON_Defects
    myMonDefectsRegion.working = myDefectProcessor->GetMONDefectRegion(theWorkingShelf, theWorkingSlot, theWorkingPort);
    myMonDefectsRegion.protection = myDefectProcessor->GetMONDefectRegion(theProtectShelf, theProtectSlot, theProtectPort);
    myMonStatusRegion.working = myDefectProcessor->GetMONStatusRegion(theWorkingShelf, theWorkingSlot, theWorkingPort, myProtectionConfig.Get1plus1Type());
    myMonStatusRegion.protection = myDefectProcessor->GetMONStatusRegion(theProtectShelf, theProtectSlot, theProtectPort, myProtectionConfig.Get1plus1Type());
    
}

void SP_1plus1ProtectionAction::UnregisterFromMONDefects()
{
    myDefectProcessor->UnregisterFromDefects(this);
    myMonDefectsRegion.working = NULL;
    myMonDefectsRegion.protection = NULL;
    myMonStatusRegion.working = NULL;
    myMonStatusRegion.protection = NULL;
}

//set indices into the config and mon regions
void SP_1plus1ProtectionAction::SetMyIndex()
{
    myIndex = myProtectionConfig.GetGroupID() -1;
    CT_SP_1plus1Type protectionType = myProtectionConfig.Get1plus1Type();

    if (protectionType == CT_SP_UPSR)
    {
        myMONObjectIndex.working = myProtectionConfig.GetSources().working.GetChannelId()-1;
        myMONObjectIndex.protection = myProtectionConfig.GetSources().protection.GetChannelId()-1;
    }
    else if (protectionType == CT_SP_SNCN ||
             protectionType == CT_SP_SNCI ||
             protectionType == CT_SP_SNCS )
    {
        myMONObjectIndex.working = myMONObjectIndex.protection = -1; //Clear out indices to begin with

        myMONObjectIndex.working = myOduSncInstance->GetIndex(CT_SP_WORKING_SIDE);
        myMONObjectIndex.protection = myOduSncInstance->GetIndex(CT_SP_PROTECTION_SIDE);

        //it is possible that atmost one of these indices is -1, so adjust to point to the index of the non -1
        if (myMONObjectIndex.working == -1)
        {
            myMONObjectIndex.working = myMONObjectIndex.protection;
        }

        if (myMONObjectIndex.protection == -1)
        {
            myMONObjectIndex.protection = myMONObjectIndex.working;
        }
    }
    else
    {
        myMONObjectIndex.working = myMONObjectIndex.protection = 0;
    }

}


void SP_1plus1ProtectionAction::CalculateServiceStatus(bool forcedClear)
{
    //Only calculate service status
    //if the protection group is configured.
    //If selected side is not failed
    //set the non service affecting alarm.
    //If selected side is failed
    //clear the non service affecting alarm.
    //If forcedClear, clear the non service affecting alarm
    CT_DirectionFlag pType = 0;
    int i = 0;
    int theWIndex = 0; //channel should be zero for facility entities
    int thePIndex = 0; //channel should be zero for facility entities

    CT_SP_1plus1Type protectionType = Get1plus1Config().Get1plus1Type();

    if ((protectionType == CT_SP_OAPS ||
         protectionType == CT_SP_DPRING ||
         protectionType == CT_SP_LINEAR ||
         protectionType == CT_SP_UPSR ||
         protectionType == CT_SP_YCABLE ||
         protectionType == CT_SP_SNCN ||
         protectionType == CT_SP_SNCI ||
         protectionType == CT_SP_SNCS ) &&
         Get1plus1Config().InUse())
    {

        //bool clear = forcedClear;
        bool clearW = forcedClear;
        bool clearP = forcedClear;

        //Retrieve the alarm index
        if (protectionType == CT_SP_UPSR ||
            protectionType == CT_SP_SNCN ||
            protectionType == CT_SP_SNCI ||
            protectionType == CT_SP_SNCS)
        {
            theWIndex = GetAlmIndex(CT_SP_WORKING_SIDE);
            thePIndex = GetAlmIndex(CT_SP_PROTECTION_SIDE);
        }


        if (mySelectorPtr->GetSelection() == CT_SP_WORKING_SIDE)
        {
            if (myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SF ||
                myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SF_LOW)
            {
                if (myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_LK_P ||
                    myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_FS_W)
                {
                    //selected side failed..clear the non service affecting alarm
                    clearW = true;
                    clearP = true;
                }
                else if (Get1plus1Config().GetState() != CT_SP_DISABLED_STATE)
                {
                    //selected side failed..clear the non service affecting alarm
                    clearW = true;
                    clearP = true;
                }

            }
        }
        else if (mySelectorPtr->GetSelection() == CT_SP_PROTECTION_SIDE)
        {
            if (myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SF ||
                myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SF_LOW)
            {
                if (myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_FS_P)
                {
                    //selected side failed..clear the non service affecting alarm
                    clearW = true;
                    clearP = true;
                }
                else if (Get1plus1Config().GetState() != CT_SP_DISABLED_STATE)
                {
                    //selected side failed..clear the non service affecting alarm
                    clearW = true;
                    clearP = true;
                }
            }
        }

        SP_AlmAppIfCollection theWorkAlmApps;
        SP_AlmAppIfCollection theProtAlmApps;
    
        GetAlmAppIf(Get1plus1Config().GetSources().working.GetPortId(), theWorkAlmApps, SP_ESCALATION);
        GetAlmAppIf(Get1plus1Config().GetSources().protection.GetPortId(), theProtAlmApps, SP_ESCALATION);

        CT_TelAlarmCondition::CT_FacilityAlarmType theFailureType = CT_TelAlarmCondition::ALM_SP_NOT_SA;
        if (protectionType == CT_SP_SNCN ||
            protectionType == CT_SP_SNCI ||
            protectionType == CT_SP_SNCS)
        {
            theFailureType = CT_TelAlarmCondition::ALM_SP_ODUKP_NOT_SA;
        }

        if (theWIndex != -1)
        {
            SP_AlmAppIfCollection::iterator theAlmAppIt;
            for (theAlmAppIt = theWorkAlmApps.begin();
                 theAlmAppIt != theWorkAlmApps.end();
                 ++theAlmAppIt )
            {
                if (clearW)
                {
                    //clear the NSA alarm on working since the condition of traffic is SA
                    (*theAlmAppIt)->ClearSigProtDefect(theFailureType,
                                                 theWIndex);
                }
                else
                {
                    // report NSA set, since the traffic status is NSA
                    (*theAlmAppIt)->ReportSigProtDefect(theFailureType,
                                             theWIndex);
                }
            }
        }
        
        if (thePIndex != -1)
        {
            SP_AlmAppIfCollection::iterator theAlmAppIt;
            for (theAlmAppIt = theProtAlmApps.begin();
                 theAlmAppIt != theProtAlmApps.end();
                 ++theAlmAppIt )
            {
            
                if (clearP)
                {
                    //clear the NSA alarm on protection since the condition of traffic is SA
                    (*theAlmAppIt)->ClearSigProtDefect(theFailureType,
                                                 thePIndex);
                }
                else
                {
                    // report NSA set, since the traffic status is NSA
                    (*theAlmAppIt)->ReportSigProtDefect(theFailureType,
                                             thePIndex);
                }
            }
        }
        
        
        //--------------------------------------------
        //Now report/clear PROTNA alarm as needed
        //Rules for raising protna
        //1. Raise protna if non-seleced fac is failed or degraded
        //2. There is a Forced Switch/Lockout command present away from non-selected facility
        theWorkAlmApps.clear();
        theProtAlmApps.clear();
        theWIndex = 0;
        thePIndex = 0;
        clearW = forcedClear;
        clearP = forcedClear;

        //Adjust the failure type
        theFailureType = CT_TelAlarmCondition::ALM_SP_PROTNA_UID;
        if (protectionType == CT_SP_SNCN ||
            protectionType == CT_SP_SNCI ||
            protectionType == CT_SP_SNCS)
        {
            theFailureType = CT_TelAlarmCondition::ALM_SP_ODUKP_PROTNA_UID;
        }

        if (protectionType == CT_SP_OAPS ||
            protectionType == CT_SP_DPRING ||
            protectionType == CT_SP_LINEAR ||
            protectionType == CT_SP_YCABLE)
        {
            if (mySelectorPtr->GetSelection() == CT_SP_WORKING_SIDE)
            {
                if (myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SF ||
                    myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SF_LOW ||
                    myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SD ||
                    myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_LK_P ||
                    myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_FS_W)
                {
                    //non-selected fac not available
                    clearP = false;
            
                }
                else
                {
                    clearP = true;
                }

                //working is selected, so always clear PROTNA alarm
                clearW = true;
            }
            else //protection is selected
            {
                if (myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SF ||
                    myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SF_LOW ||
                    myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SD ||
                    myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_FS_P)
                {
                    //non-selected fac not available
                    clearW = false;
            
                }
                else
                {
                    clearW = true;
                }

                //protect is selected, so always clear PROTNA alarm
                clearP = true;
            }

            //if a forced clear, clear the protna alarm on both facilities
            if (forcedClear)
            {
                clearW = true;
                clearP = true;
            }

            GetAlmAppIf(Get1plus1Config().GetSources().working.GetPortId(), theWorkAlmApps, SP_PROTNA);
            GetAlmAppIf(Get1plus1Config().GetSources().protection.GetPortId(), theProtAlmApps, SP_PROTNA);

            
            if (thePIndex != -1)
            {
                SP_AlmAppIfCollection::iterator theAlmAppIt;
                for (theAlmAppIt = theProtAlmApps.begin();
                     theAlmAppIt != theProtAlmApps.end();
                     ++theAlmAppIt )
                {
            
                    if (clearP)
                    {
                        //clear the protna alarm since non-selected fac is available for protection
                        (*theAlmAppIt)->ClearSigProtDefect(theFailureType,
                                                 thePIndex, (protectionType == CT_SP_YCABLE));
                    }
                    else
                    {
                        // report protna since protect fac is not available for protection
                        (*theAlmAppIt)->ReportSigProtDefect(theFailureType,
                                             thePIndex, (protectionType == CT_SP_YCABLE));
                    }
                }
            }
            
            if (theWIndex != -1)
            {
                SP_AlmAppIfCollection::iterator theAlmAppIt;
                for (theAlmAppIt = theWorkAlmApps.begin();
                     theAlmAppIt != theWorkAlmApps.end();
                     ++theAlmAppIt )
                {
                    if (clearW)
                    {
                        //clear the protna alarm since non-selected fac is available for protection
                        (*theAlmAppIt)->ClearSigProtDefect(theFailureType,
                                                 theWIndex, (protectionType == CT_SP_YCABLE));
                    }
                    else
                    {
                        // report protna since working fac is not available for protection
                        (*theAlmAppIt)->ReportSigProtDefect(theFailureType,
                                             theWIndex, (protectionType == CT_SP_YCABLE));
                    }
                }
            }    
            
        } //Protection type
        else if (protectionType == CT_SP_UPSR ||
                protectionType == CT_SP_SNCN ||
                protectionType == CT_SP_SNCI ||
                protectionType == CT_SP_SNCS)
        {
            theWIndex = GetAlmIndex(CT_SP_WORKING_SIDE);
            thePIndex = GetAlmIndex(CT_SP_PROTECTION_SIDE);

            if (mySelectorPtr->GetSelection() == CT_SP_WORKING_SIDE)
            {
                if (myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_LK_P ||
                    myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_FS_W)
                {
                    //non-selected fac not available
                    clearP = false;
                    //working is selected, so always clear PROTNA alarm
                    clearW = true;
            
                }
                else if (myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SF ||
                    myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SF_LOW ||
                    myRequestParserPtr->GetDefectStatus().protection == CT_SP_AUTO_SD)
                {
                    //If the protection group is in a disabled state, only raise PROTNA if the protect (non-selected) facility
                    //is a "real" facility
                    if (Get1plus1Config().GetState() == CT_SP_DISABLED_STATE)
                    {
                        if (Get1plus1Config().GetSources().protection.GetPortId() == CT_LINE_SIDE_0)
                        {
                            clearP = false;
                            clearW = false;
                        }
                        else
                        {
                            clearP = true;
                            clearW = true;
                        }
                    }
                    else
                    {
                        clearP = false;
                        clearW = false;
                    }
                }
                else
                {
                    clearP = true;
                    //working is selected, so always clear PROTNA alarm
                    clearW = true;
                }
            }
            else //protection is selected
            {
                
                if (myRequestParserPtr->GetCommand().myRequest == CT_SP_1PLUS1_FS_P)
                {
                    //non-selected fac not available
                    clearW = false;
                    //protect is selected, so always clear PROTNA alarm
                    clearP = true;
                }
                else if (myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SF ||
                    myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SF_LOW ||
                    myRequestParserPtr->GetDefectStatus().working == CT_SP_AUTO_SD)
                {
                    //If the protection group is in a disabled state, only raise PROTNA if the working (non-selected) facility
                    //is a "real" facility
                    if (Get1plus1Config().GetState() == CT_SP_DISABLED_STATE)
                    {
                        if (Get1plus1Config().GetSources().working.GetPortId() == CT_LINE_SIDE_0)
                        {
                            clearP = false;
                            clearW = false;
                        }
                        else
                        {
                            clearW = true;
                            //protect is selected, so always clear PROTNA alarm
                            clearP = true;
                        }
                    }
                    else
                    {
                        clearP = false;
                        clearW = false;
                    }
                }
                else
                {
                    clearW = true;
                    //protect is selected, so always clear PROTNA alarm
                    clearP = true;
                }

            }

            //if a forced clear, clear the protna alarm on both facilities
            if (forcedClear)
            {
                clearW = true;
                clearP = true;
            }

            GetAlmAppIf(Get1plus1Config().GetSources().working.GetPortId(), theWorkAlmApps, SP_PROTNA);
            GetAlmAppIf(Get1plus1Config().GetSources().protection.GetPortId(), theProtAlmApps, SP_PROTNA);
            
            if (thePIndex != -1)
            {
                SP_AlmAppIfCollection::iterator theAlmAppIt;
                for (theAlmAppIt = theProtAlmApps.begin();
                     theAlmAppIt != theProtAlmApps.end();
                     ++theAlmAppIt )
                {
            
                    if (clearP)
                    {
                        //clear the protna alarm since non-selected fac is available for protection
                        (*theAlmAppIt)->ClearSigProtDefect(theFailureType,
                                                 thePIndex);
                    }
                    else
                    {
                        // report protna since protect fac is not available for protection
                        (*theAlmAppIt)->ReportSigProtDefect(theFailureType,
                                             thePIndex);
                    }
                }
            }
            
            if (theWIndex != -1)
            {
                SP_AlmAppIfCollection::iterator theAlmAppIt;
                for (theAlmAppIt = theWorkAlmApps.begin();
                     theAlmAppIt != theWorkAlmApps.end();
                     ++theAlmAppIt )
                {
            
                    if (clearW)
                    {
                        //clear the protna alarm since non-selected fac is available for protection
                        (*theAlmAppIt)->ClearSigProtDefect(theFailureType,
                                                 theWIndex);
                    }
                    else
                    {
                        // report protna since protect fac is not available for protection
                        (*theAlmAppIt)->ReportSigProtDefect(theFailureType,
                                             theWIndex);
                    }
                }
            }
        } //Protection type

        //--------------------------------------------
        //Now report/clear FOP alarm as needed
        if ((Get1plus1Config().Get1plus1Type()== CT_SP_SNCN) || (Get1plus1Config().Get1plus1Type()== CT_SP_SNCI) || (Get1plus1Config().Get1plus1Type()== CT_SP_SNCS))
        {
            ReportFopIfNeeded(); 
        }
    } //In Use

}

void SP_1plus1ProtectionAction::ReportFopIfNeeded()
{
    SP_AlmAppIfCollection theProtAlmApps; 
    GetAlmAppIf(Get1plus1Config().GetSources().protection.GetPortId(), theProtAlmApps, SP_PROTNA);
    int thePIndex = GetAlmIndex(CT_SP_PROTECTION_SIDE);

    if (thePIndex != -1)
    {
        SP_AlmAppIfCollection::iterator theAlmAppIt;
        for (theAlmAppIt = theProtAlmApps.begin(); theAlmAppIt != theProtAlmApps.end(); ++theAlmAppIt )
        {
            if (myRequestParserPtr->FopPmNeedToBeReported())
            {
                if (gSP_DebugTraceSnc) fc_cout << "Report FOP-PM at index: " << thePIndex << endl;
                (*theAlmAppIt)->ReportSigProtDefect( CT_TelAlarmCondition::ALM_SP_FOP_PM_UID, thePIndex);
            }
            else
            {
                if (gSP_DebugTraceSnc) fc_cout << "Clear  FOP-PM at index: " << thePIndex << endl;
                (*theAlmAppIt)->ClearSigProtDefect( CT_TelAlarmCondition::ALM_SP_FOP_PM_UID, thePIndex);
            }

            if (myFopNrOnRequestedEntity)
            {
                if (gSP_DebugTraceSnc) fc_cout << "Report FOP-NR at index: " << thePIndex << endl;
                (*theAlmAppIt)->ReportSigProtDefect( CT_TelAlarmCondition::ALM_SP_FOP_NR_UID, thePIndex);
            }
            else
            {
                if (gSP_DebugTraceSnc) fc_cout << "Clear  FOP-NR at index: " << thePIndex << endl;
                (*theAlmAppIt)->ClearSigProtDefect( CT_TelAlarmCondition::ALM_SP_FOP_NR_UID, thePIndex);
            }
        }
    }
}

void SP_1plus1ProtectionAction::PreRun()
{
    //default implementation do nothing
}

void SP_1plus1ProtectionAction::PostRun()
{
    //default implementation do nothing
}

CT_SP_Protection SP_1plus1ProtectionAction::GetPreferredSide()
{
    //All things being equal, indicate which side is the preferred side
    return CT_SP_INVALID_PROTECTION_SIDE;

}

int SP_1plus1ProtectionAction::GetAlmIndex(CT_SP_Protection theSide)
{
    fc_cout << "SP_1plus1ProtectionAction::GetAlmIndex not implemented in base class" << endl;
    return 0;
}

void SP_1plus1ProtectionAction::TransformSources(CT_SP_ProtectionPair<CT_Port> & theOrigSources, CT_SP_ProtectionPair<CT_ChannelId>& theChannels, CT_SP_ProtectionPair<CT_Port> & theNewSources, CT_SP_1plus1Type the1plus1Type)
{
    //By default do not transform the sources
    theNewSources.working = theOrigSources.working;
    theNewSources.protection = theOrigSources.protection;
}

void SP_1plus1ProtectionAction::SetupKbyteTransmit()
{
    SP_1plus1BaseApplication& theApp = static_cast<SP_1plus1BaseApplication&>(GetAppIf());
        
    //For LAPS register to write kbytes
    if (Get1plus1Config().Get1plus1Type() == CT_SP_LINEAR)
    {
        if (theApp.GetProtectionSide() == SP_PORT)
        {
            //add output region for kbyte transmission
            myCfgMsRegion.working        = GetAppIf().GetCardContext().GetMsIf().GetCfgPortSideApp(Get1plus1Config().GetSources().working.GetPortId()).GetProtCfgRegion();
            myCfgMsRegion.protection     = GetAppIf().GetCardContext().GetMsIf().GetCfgPortSideApp(Get1plus1Config().GetSources().protection.GetPortId()).GetProtCfgRegion();
            GetBbAction()->AddOutputRegion(myCfgMsRegion.working, false, false);
            GetBbAction()->AddOutputRegion(myCfgMsRegion.protection, false, false);
            
        }
        else if (theApp.GetProtectionSide() == SP_LINE)
        {
            myCfgMsRegion.working        = GetAppIf().GetCardContext().GetMsIf().GetCfgLineSideApp(Get1plus1Config().GetSources().working.GetPortId()).GetProtCfgRegion();
            myCfgMsRegion.protection     = GetAppIf().GetCardContext().GetMsIf().GetCfgLineSideApp(Get1plus1Config().GetSources().protection.GetPortId()).GetProtCfgRegion();
            GetBbAction()->AddOutputRegion(myCfgMsRegion.working, false, false);
            GetBbAction()->AddOutputRegion(myCfgMsRegion.protection, false, false);
        }
    }
}

void SP_1plus1ProtectionAction::ConfigureHopBERAlarming(bool theEnable)
{
    int theWIndex = 0;
    int thePIndex = 0;

    CT_SP_1plus1Type protectionType = Get1plus1Config().Get1plus1Type();

    if (protectionType == CT_SP_UPSR)
    {
        //adjust the channel number for UPSR. ALM is expecting 0 based
        //channel numbers between 0-47.
        theWIndex = GetAlmIndex(CT_SP_WORKING_SIDE);
        thePIndex = GetAlmIndex(CT_SP_PROTECTION_SIDE);

        SP_AlmAppIfCollection theWorkAlmApps;
        SP_AlmAppIfCollection theProtAlmApps;
    
        GetAlmAppIf(Get1plus1Config().GetSources().working.GetPortId(), theWorkAlmApps, SP_ARC);
        GetAlmAppIf(Get1plus1Config().GetSources().protection.GetPortId(), theProtAlmApps, SP_ARC);

        // clear the NR alarm since the protection scheme is being enabled
        if (theEnable)
        {
            
            SP_AlmAppIfCollection::iterator theAlmAppIt;
            for (theAlmAppIt = theWorkAlmApps.begin();
                 theAlmAppIt != theWorkAlmApps.end();
                 ++theAlmAppIt )
            {
                (*theAlmAppIt)->ClearSigProtDefect(CT_TelAlarmCondition::ALM_SP_STRM_A_NR,
                                             theWIndex);
            }

            for (theAlmAppIt = theProtAlmApps.begin();
                 theAlmAppIt != theProtAlmApps.end();
                 ++theAlmAppIt )
            {
            
                (*theAlmAppIt)->ClearSigProtDefect(CT_TelAlarmCondition::ALM_SP_STRM_A_NR,
                                             thePIndex);
            }
        }
        // clear the NR alarm since the protection scheme is being enabled
        else
        {
            
            SP_AlmAppIfCollection::iterator theAlmAppIt;
            for (theAlmAppIt = theWorkAlmApps.begin();
                 theAlmAppIt != theWorkAlmApps.end();
                 ++theAlmAppIt )
            {
                (*theAlmAppIt)->ReportSigProtDefect(CT_TelAlarmCondition::ALM_SP_STRM_A_NR,
                                             theWIndex);
            }

            for (theAlmAppIt = theProtAlmApps.begin();
                 theAlmAppIt != theProtAlmApps.end();
                 ++theAlmAppIt )
            {
            
                (*theAlmAppIt)->ReportSigProtDefect(CT_TelAlarmCondition::ALM_SP_STRM_A_NR,
                                             thePIndex);
            }
        }
    }

}

bool SP_1plus1ProtectionAction::IsSsmSwitchingAllowed()
{
    //If in system slave timing mode, do not switch on SSM. SSM switching is done else where
    CT_SP_1plus1SubType subType = Get1plus1Config().Get1plus1SubType();
    if (subType == CT_SP_EXT_SLAVE)
        return false;
    
    //Default: Always allowed
    return true;
}

CT_SP_Protection SP_1plus1ProtectionAction::GetCurrentYCableSelection(unsigned int tspiiIntf1 /*bp*/, unsigned int tspiiIntf2 /*real*/)
{
    CT_IntfId wPort = Get1plus1Config().GetSources().working.GetPortId();
    CT_IntfId pPort = Get1plus1Config().GetSources().protection.GetPortId();
    SP_1plus1SubApplication& theApp = static_cast<SP_1plus1SubApplication&>(GetAppIf());
    SP_SelectorPositionRegion* theSelectorPosnRegion = &(theApp.GetSelectorPosnRegion());
    SP_SelectorPosition& aSelectorPosn = static_cast<SP_SelectorPosition&>((*theSelectorPosnRegion)[myIndex]);
    bool bothRealPorts = (IsPortFacility(wPort) && IsPortFacility(pPort));

    if ( (aSelectorPosn.GetSelectorPosition() == CT_SP_PROTECTION_SIDE && IsPortFacility(wPort)) ||
         (aSelectorPosn.GetSelectorPosition() == CT_SP_WORKING_SIDE && IsPortFacility(pPort))
       )
    {
        if (bothRealPorts == false) /* One is a shadow port*/
        {
            //If remote laser is disabled, then it means that a switch occured when this module
            //was resetting, so select ourselves.
            TSPII_OpticalRegion* OpticalRegion = NULL;
            //Verify the backplane is not in LOS prior to reading mate laser state.
            OpticalRegion = TSPII_SubApplication::GetInstance()->GetOptical(tspiiIntf1);
            uint32 PII_count = (*OpticalRegion)[GetYCableMateSlotIdx()].GetOptLOS();
            if(PII_count%2 == 0)
            {
                OpticalRegion = TSPII_SubApplication::GetInstance()->GetOptical(tspiiIntf2);
                uint8 rxMsg = (*OpticalRegion)[0].GetRxYCableMessage();
                bool mateLaserEnable = ( ((rxMsg & SP_LASER_STATE) == 0x0) ? false : true);
                if (mateLaserEnable == false)
                {
                    if (mySelectorPtr)
                    {
                        fc_cout << "Mate laser off condition detected..going active" << endl;
                        if (aSelectorPosn.GetSelectorPosition() == CT_SP_PROTECTION_SIDE)
                        {
                            mySelectorPtr->SelectWorking();
                            mySelectorPtr->Switch();
                            return CT_SP_WORKING_SIDE;
                        }
                        else if (aSelectorPosn.GetSelectorPosition() == CT_SP_WORKING_SIDE)
                        {
                            mySelectorPtr->SelectProtection();
                            mySelectorPtr->Switch();
                            return CT_SP_PROTECTION_SIDE;
                        }
                    }
                }
            }
        }
    }

    //If we get here, the do normal processing
    if (aSelectorPosn.GetSelectorPosition() == CT_SP_PROTECTION_SIDE)
    {
        if (mySelectorPtr)
        {
            mySelectorPtr->SelectProtection();
            mySelectorPtr->Switch();
        }

        return CT_SP_PROTECTION_SIDE;
    }

    if (mySelectorPtr)
    {
        mySelectorPtr->SelectWorking();
        mySelectorPtr->Switch();
    }
    return CT_SP_WORKING_SIDE;
}

CT_SP_Protection SP_1plus1ProtectionAction::GetInitialYCableSelection(unsigned int tspiiIntf1 /*bp*/, unsigned int tspiiIntf2 /*real*/)
{

    CT_IntfId wPort = Get1plus1Config().GetSources().working.GetPortId();
    CT_IntfId pPort = Get1plus1Config().GetSources().protection.GetPortId();
    SP_1plus1SubApplication& theApp = static_cast<SP_1plus1SubApplication&>(GetAppIf());
    bool bothRealPorts = (IsPortFacility(wPort) && IsPortFacility(pPort));

    if (bothRealPorts == false) /* One is a shadow port*/
    {
        TSPII_OpticalRegion* OpticalRegion = NULL;
        //Verify the backplane is not in LOS prior to reading mate laser state.
        OpticalRegion = TSPII_SubApplication::GetInstance()->GetOptical(tspiiIntf1);
        uint32 PII_count = (*OpticalRegion)[GetYCableMateSlotIdx()].GetOptLOS();
        if(PII_count%2 == 0)
        {
            OpticalRegion = TSPII_SubApplication::GetInstance()->GetOptical(tspiiIntf2);
            uint8 rxMsg = (*OpticalRegion)[0].GetRxYCableMessage();
            fc_cout << "PG " << (uint32)myIndex << ": Rx YCable msg is " << (uint32)rxMsg << endl;
            bool mateLaserEnable = ( ((rxMsg & SP_LASER_STATE) == 0x0) ? false : true);
            if (IsPortFacility(wPort))
            {
                if (mateLaserEnable)
                {
                    fc_cout << "PG " << (uint32)myIndex << ": Remote module (protection) is selected" << endl;
                    mySelectorPtr->SelectProtection();
                    mySelectorPtr->Switch();
                    return CT_SP_PROTECTION_SIDE;
                }
            }
            else if (IsPortFacility(pPort))
            {
                if (mateLaserEnable)
                {
                    fc_cout << "PG " << (uint32)myIndex << ": Remote module (working) is selected" << endl;
                    mySelectorPtr->SelectWorking();
                    mySelectorPtr->Switch();
                    return CT_SP_WORKING_SIDE;
                }
            }
        }
        else
        {
            fc_cout << "PG " << (uint32)myIndex << ": Skipping initial y-cable selection due to backplane LOS" << endl;
        }
    }
    return CT_SP_INVALID_PROTECTION_SIDE;
}

bool SP_1plus1ProtectionAction::IsYCableConfigurationMismatch(TSPII_OpticalRegion* theRxRegion, CT_Status theEqptStatus, bool realPortIsWorking, bool txLaserEnable, TSPII_OpticalRegion* theBkplRegion)
{
    bool matePresent = true;

    CT_IntfId wPort = Get1plus1Config().GetSources().working.GetPortId();
    bool isRevertive = Get1plus1Config().GetRevertiveMode();

    uint8 rxMsg = (*theRxRegion)[0].GetRxYCableMessage();
    bool mateLaserEnable = ( ((rxMsg & SP_LASER_STATE) == 0x0) ? false : true);

    uint32 PII_count = (*theBkplRegion)[GetYCableMateSlotIdx()].GetOptLOS();
    if(PII_count%2 != 0)
    {
        matePresent = false;
    }

    if (matePresent == true)
    {
        //If both sources are disabled:
        //On working card, indicate config mismatch
        //On protect card, indicate no config mismatch
        if (mateLaserEnable == false && txLaserEnable == false)
        {
            if (realPortIsWorking)
            {
                //If the port is configured for "laser off" then do no consider this a mismatch
                CFG_Region* theCfgOptRegion = GetAppIf().GetCardContext().GetOptIf().GetCfgPortSideApp(wPort).GetCfgRegion();
                CFG_Opt* aCfgOptObject = static_cast<CFG_Opt*>(&((*theCfgOptRegion)[0]));
                bool configLaserEnable = aCfgOptObject->GetLaserEnable();

                bool eqptPresent = false;
                //If the pluggable is not present or faulted, then do not consider this a mismatch scenario
                if (theEqptStatus == CT_OK)
                {
                    eqptPresent = true;
                }


                if (configLaserEnable == true && eqptPresent == true)
                {
                    //DEBUG
                    if (gSP_DebugTraceYCable == 1)
                    {
                        fc_cout << "Both lasers off..Config mismatch detected..attempting to correct" << endl;
                    }
                    //END DEBUG

                    return true;
                }
            }
        }
            
        //If both sources are enabled:
        //On working card, indicate no config mismatch
        //On protect card, indicate config mismatch
        if (mateLaserEnable == true && txLaserEnable == true)
        {   
            if (!realPortIsWorking)
            {
                //DEBUG
                if (gSP_DebugTraceYCable == 1)
                {
                    fc_cout << "Both lasers on..Config mismatch detected..attempting to correct" << endl;
                }
                //END DEBUG

                return true;
            }
        }


        //if my current selector state doesnt match actual traffic state, then also consider this a mismatch
        if (mateLaserEnable == true && txLaserEnable == false)
        {
            if (realPortIsWorking == true && mySelectorPtr->GetSelection() == CT_SP_WORKING_SIDE)
            {

                //In revertive mode apply a holdoff before considering this scenario a mismatch. We wait 6 iterations before proceeding with mismatch
                //No holdoff in nonrevertive mode.
                if ( (isRevertive == false) || (isRevertive == true && myConfigMismatchHoldoffCount >= 6))
                {
                    //DEBUG
                    if (gSP_DebugTraceYCable == 1)
                    {
                        fc_cout << "Laser off, selector state wrong (should be protection)..Config mismatch detected..attempting to correct" << endl;
                    }
                    //END DEBUG
                    myConfigMismatchHoldoffCount = 0;
                    return true;
                }
                else
                {
                    if (isRevertive)
                        myConfigMismatchHoldoffCount++;

                    //if (gSP_DebugTraceYCable == 1)
                    //{
                    //    fc_cout << "Laser off, selector state wrong (should be protection)..Config mismatch detected..waiting for holdoff" << endl;
                    //}

                    return false; //Indicate no config mismatch since we are in holdoff period
                }
            }

            if (realPortIsWorking == false && mySelectorPtr->GetSelection() == CT_SP_PROTECTION_SIDE)
            {
                //DEBUG
                if (gSP_DebugTraceYCable == 1)
                {
                    fc_cout << "Laser off, selector state wrong (should be working)..Config mismatch detected..attempting to correct" << endl;
                }
                //END DEBUG

                return true;
            }
        }
    }

    //If we got to this point, there is no config mismatch, therefore clear the holdoff counter
    myConfigMismatchHoldoffCount = 0;

    return false;
}

void SP_1plus1ProtectionAction::DumpSpecificData()
{
    //Do nothing
}

CT_SP_Protection SP_1plus1ProtectionAction::GetInitialSelection()
{
    return CT_SP_INVALID_PROTECTION_SIDE;
}

bool SP_1plus1ProtectionAction::IsConfigurationMismatch()
{
    return false;
}

FC_Milliseconds SP_1plus1ProtectionAction::GetWTROffset()
{
    CT_SP_1plus1Type protectionType = Get1plus1Config().Get1plus1Type();
    if (protectionType == CT_SP_SNCN ||
        protectionType == CT_SP_SNCI ||
        protectionType == CT_SP_SNCS)
    {
        if (myOduSncInstance)
        {
           return (myOduSncInstance->GetSncWTROffset());
        }
    }
    
    return 0;
}

FC_Milliseconds SP_1plus1ProtectionAction::GetHoldOffTimerOffset()
{
    CT_SP_1plus1Type protectionType = Get1plus1Config().Get1plus1Type();
    if (protectionType == CT_SP_YCABLE|| 
        protectionType == CT_SP_SNCN || 
        protectionType == CT_SP_SNCI || 
        protectionType == CT_SP_SNCS)
    {
        return 0; //No offsets for y-cable or SNC.
    }
    else
    {
        return (Get1plus1Config().GetHoldOffTimer()*0.1);
    }
}

bool SP_1plus1ProtectionAction::IsLocalDefect(CT_SP_Protection theSide)
{
    bool isLocal = true;
    CT_SP_1plus1Type protectionType = Get1plus1Config().Get1plus1Type();
    if (protectionType == CT_SP_YCABLE)
    {
        CT_IntfId wPort = Get1plus1Config().GetSources().working.GetPortId();
        CT_IntfId pPort = Get1plus1Config().GetSources().protection.GetPortId();

        if (theSide == CT_SP_WORKING_SIDE)
        {
            isLocal = IsPortFacility(wPort);
        }
        else if (theSide == CT_SP_PROTECTION_SIDE)
        {
            isLocal = IsPortFacility(pPort);
        }
    }
    
    return isLocal;
}

void SP_1plus1ProtectionAction::SetTspiiInterface(CT_SP_Protection theSide, unsigned int theId)
{
    if (theSide == CT_SP_WORKING_SIDE)
    {
        myTspiiInterfaces.working = theId;
    }
    else if (theSide == CT_SP_PROTECTION_SIDE)
    {
        myTspiiInterfaces.protection = theId;
    }
}

void SP_1plus1ProtectionAction::SetSPDefects(CT_SP_Protection theSide, SP_Defects* theDefects)
{
    if (theSide == CT_SP_WORKING_SIDE)
    {
        mySPDefects.working = theDefects;
    }
    else if (theSide == CT_SP_PROTECTION_SIDE)
    {
        mySPDefects.protection = theDefects;
    }
}

bool SP_1plus1ProtectionAction::DoSpecificStatusUpdate(SP_1plus1ProtectionGroupStatus& a1plus1Status)
{
    //Do nothing in base class
    return false;
}

uint16 SP_1plus1ProtectionAction::GetYCableMateSlotIdx()
{
    //Only return 0 in base class for backward compatibility.
    return 0;
}

// prepare TX APS bytes and store to myTxApsBytes of sp_oduksnc instance.
// input parameter participant, 0: highest request on protection, 1: highest request on working
void SP_1plus1ProtectionAction::PrepareTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest)
{
    myTxApsBytes = ConvertCurrentReqToTxApsBytes(theParticipant, theRequest, theRemoteOrLocalRequest);
}

//convert the currentReq (including the request value and its source) from request parsing to Tx ApsBytes
uint32 SP_1plus1ProtectionAction::ConvertCurrentReqToTxApsBytes(CT_SP_Request theEffectiveRequest,  bool theRemoteOrLocalRequest)
{
    APS_BYTES theApsBytes;
    memset(&theApsBytes,0,sizeof(theApsBytes));
  
    if (Get1plus1Config().IsBiSwitching())
    {
        theApsBytes.requestAndProtType.bitA    = 1; //with aps;
        theApsBytes.requestAndProtType.bitB    = 0; //1+1
        theApsBytes.requestAndProtType.bitD    = 1; //bi_directional switch
        theApsBytes.requestAndProtType.bitR    = ((true == Get1plus1Config().GetRevertiveMode()) ? 1:0 ); //revertive or no-revertive

        switch (theEffectiveRequest)
        {
//on protection channel
            case CT_SP_1PLUS1_LK_P:
                theApsBytes.requestedSignal = 0;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_LOP;
                break;

            case CT_SP_1PLUS1_FS_W:
                theApsBytes.requestedSignal = 0;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_FS;
                break;

            case CT_SP_1PLUS1_SF_P:
                theApsBytes.requestedSignal = 0;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_SF;
                break;
                
            case CT_SP_1PLUS1_SD_P:
                theApsBytes.requestedSignal = 0;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_SD;
                break;
                
            case CT_SP_1PLUS1_MS_W:
                theApsBytes.requestedSignal = 0;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_MS;
                break;
            
            case CT_SP_1PLUS1_EXER_W:
                theApsBytes.requestedSignal = 0;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_EXER;
                break;

//on working channel
            case CT_SP_1PLUS1_FS_P:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request= theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_FS;
                break;

            case CT_SP_1PLUS1_SF_W:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_SF;
                break;

            case CT_SP_1PLUS1_SD_W:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_SD;
                break;
                
            case CT_SP_1PLUS1_MS_P:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_MS;
                break;

            case CT_SP_1PLUS1_WTR:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_WTR;
                break;
                
            case CT_SP_1PLUS1_DO_NOT_REVERT:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_DNR;
                break;

            case CT_SP_1PLUS1_EXER_P:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = theRemoteOrLocalRequest ? CT_SP_APS_REQUEST_RR:CT_SP_APS_REQUEST_EXER;
                break;

            default:
                theApsBytes.requestedSignal = 1;
                theApsBytes.bridgedSignal = 1;
                theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_NR;
                break;
        }
        return *((uint32*)(&theApsBytes));
    }
    else
    {
        return 0;
    }
}
//convert the currentReq (including the request value and its source) from request parsing to Tx ApsBytes
//theParticipant=0, means highest request on protection channel
//theParticipant=1, means highest request on working1 channel
//theParticipant=2, means highest request on working2 channel
//theParticipant=n, means highest request on workingN channel
// input theRemoteOrLocalRequest, 0: local request; 1: remote request.
uint32 SP_1plus1ProtectionAction::ConvertCurrentReqToTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest)
{   
    APS_BYTES theApsBytes;
    memset(&theApsBytes,0,sizeof(theApsBytes));

    if (Get1plus1Config().IsBiSwitching())
    {
        theApsBytes.requestAndProtType.bitA    = 1; //with aps;
        theApsBytes.requestAndProtType.bitB    = 0; //1+1;
        theApsBytes.requestAndProtType.bitD    = 1; //bi_directional switch
        theApsBytes.requestAndProtType.bitR    = ((true == Get1plus1Config().GetRevertiveMode()) ? 1:0 ); //revertive or no-revertive

        if(0 == theParticipant) //highest request on protection channel
        {
            theApsBytes.requestedSignal = 0;
            theApsBytes.bridgedSignal = 1;

            if( false == theRemoteOrLocalRequest ) //highest request on local
            {

                switch(theRequest)
                {
                    case CT_SP_1PLUS1_LK_P:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_LOP;
                        break;

                    case CT_SP_1PLUS1_FS_W:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_FS;
                        break;

                    case CT_SP_1PLUS1_SF_P:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_SF;
                        break;

                    case CT_SP_1PLUS1_SD_P:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_SD;
                        break;
                        
                    case CT_SP_1PLUS1_MS_W:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_MS;
                        break;

                    case CT_SP_1PLUS1_EXER_W:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_EXER;
                        break;

                    default:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_NR;
                        theApsBytes.requestedSignal = 0;
                        theApsBytes.bridgedSignal = 1;
                        break;
                }
            }
            else  //highest request from remote
            {

                switch(theRequest)
                {
                    case CT_SP_1PLUS1_LK_P:
                    case CT_SP_1PLUS1_FS_W:
                    case CT_SP_1PLUS1_SF_P:
                    case CT_SP_1PLUS1_SD_P:
                    case CT_SP_1PLUS1_MS_W:
                    case CT_SP_1PLUS1_EXER_W:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_RR;
                        break;

                    default:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_NR;
                        theApsBytes.requestedSignal = 0;
                        theApsBytes.bridgedSignal = 1;
                        break;
                }
            }
        }
        else if(1 == theParticipant) //highest request on working channel
        {
            theApsBytes.requestedSignal = 1;
            theApsBytes.bridgedSignal = 1;

            if(false == theRemoteOrLocalRequest) //highest request on local
            {
                switch (theRequest)
                {
                    case CT_SP_1PLUS1_FS_P:
                        theApsBytes.requestAndProtType.request=CT_SP_APS_REQUEST_FS;
                        break;

                    case CT_SP_1PLUS1_SF_W:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_SF;
                        break;

                    case CT_SP_1PLUS1_SD_W:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_SD;
                        break;
                        
                    case CT_SP_1PLUS1_MS_P:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_MS;
                        break;

                    case CT_SP_1PLUS1_WTR:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_WTR;
                        break;
                        
                    case CT_SP_1PLUS1_DO_NOT_REVERT:
                        theApsBytes.requestAndProtType.request =CT_SP_APS_REQUEST_DNR;
                        break;

                    case CT_SP_1PLUS1_EXER_P:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_EXER;
                        break;
                        
                    default:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_NR;
                        theApsBytes.requestedSignal = 0;
                        theApsBytes.bridgedSignal = 1;
                        break;
                }
            }
            else //highest request from remote
            {
                switch (theRequest)
                {
                    case CT_SP_1PLUS1_FS_P:
                    case CT_SP_1PLUS1_SF_W:
                    case CT_SP_1PLUS1_SD_W:
                    case CT_SP_1PLUS1_MS_P:
                    case CT_SP_1PLUS1_WTR:
                    case CT_SP_1PLUS1_EXER_P:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_RR;
                        break;

                    case CT_SP_1PLUS1_DO_NOT_REVERT:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_DNR;
                        break;

                    default:
                        theApsBytes.requestAndProtType.request = CT_SP_APS_REQUEST_NR;
                        theApsBytes.requestedSignal = 0;
                        theApsBytes.bridgedSignal = 1;
                        break;
                }
            }
        }
        return *((uint32*)(&theApsBytes));
    }
    else 
    {
        return 0;
    }
}

void SP_1plus1ProtectionAction::CheckFopNr()
{
    
    CT_SlotId pSlot = Get1plus1Config().GetSources().protection.GetSlotId();
    CT_SlotId mySlot = GetAppIf().GetCardContext().GetCardId();

    if (pSlot != mySlot) return;

    if (Get1plus1Config().IsBiSwitching() && myOduSncInstance != NULL)
    {
        uint8 receivedRequestedEntity = (GetApsBytes() & 0x00FF0000) >> 16;
        uint8 sentRequestedEntity = (myOduSncInstance->GetTxApsBytes() & 0x00FF0000) >> 16;

        if (((receivedRequestedEntity != sentRequestedEntity) && 
                    (myRequestParserPtr->GetDefectStatus().protection != CT_SP_AUTO_SF &&
                     myRequestParserPtr->GetDefectStatus().protection != CT_SP_AUTO_SF_LOW)) //1. ignore the APS when SF_P
            || (GetApsBytes() == 0) || (GetApsBytes() == 0x66666666)) // 2. No APS in APS channel, Far End doesn't/can't response
        {
            if (myFopNrTimerOnRequestedEntity.IsExpired() && myFopNrTimerOnRequestedEntity.IsStarted())
            {
                if (gSP_DebugTraceSnc) printf("BISNC:++++: CheckFopNr - timer expired\n");

                myFopNrOnRequestedEntity = true;

                myFopNrTimerOnRequestedEntity.Stop();
            }
            if (!myFopNrTimerOnRequestedEntity.IsStarted() && !myFopNrOnRequestedEntity)
            {
                if (gSP_DebugTraceSnc) printf("BISNC:++++: CheckFopNr - start timer\n");

                myFopNrTimerOnRequestedEntity.Start(1000); // follow G.798 instead of G.873
            }
        }
        else
        {
            myFopNrOnRequestedEntity = false;

            if (myFopNrTimerOnRequestedEntity.IsStarted())
            {
                if (gSP_DebugTraceSnc) printf("BISNC:++++: CheckFopNr - stop timer\n");
                myFopNrTimerOnRequestedEntity.Stop();
            }
        }
    }
    else
    {
        myFopNrOnRequestedEntity = false;
        if (myFopNrTimerOnRequestedEntity.IsStarted())
        {
            myFopNrTimerOnRequestedEntity.Stop();
        }
    }
    
}

void SP_1plus1ProtectionAction::RefreshConfiguration()
{
    if (myBiSwitchingChanged)
    {
        CT_SP_1plus1Type protType = myProtectionConfig.Get1plus1Type();
        CT_SP_1plus1Type subType = myProtectionConfig.Get1plus1SubType();
        //add DPRING
        if (protType == CT_SP_SNCN || protType == CT_SP_SNCI || protType == CT_SP_SNCS || protType == CT_SP_DPRING ||
            subType == CT_SP_SNCN || subType == CT_SP_SNCI || subType == CT_SP_SNCS)
        {
            RefreshAps();
        }

        myBiSwitchingChanged = false;
    }
}

//dispaly TxApsBytes as specified format
void SP_1plus1ProtectionAction::DisplayTxApsBytes(uint32 theTxApsBytes)
{

    uint32 tmpTxApsBytes = theTxApsBytes;
    APS_BYTES theApsBytes = *((APS_BYTES*)(&tmpTxApsBytes));
#if 0
    fc_cout <<showbase;

    fc_cout << "TxAps("<<hex << theTxApsBytes <<endl;

    fc_cout << dec;
    
    fc_cout << "TxApsBytes BitA is "  << (uint32)((uint8)theApsBytes.requestAndProtType.bitA )
        << ", BitB is " << (uint32)((uint8)theApsBytes.requestAndProtType.bitB ) 
        << ", BitD is " << (uint32)((uint8)theApsBytes.requestAndProtType.bitD )
        << ", BitR is " << (uint32)((uint8)theApsBytes.requestAndProtType.bitR ) <<endl;
    
    fc_cout << "TxApsBytes Request is "<<DISPLAY_CT_SP_APS_REQUEST(theApsBytes.requestAndProtType.request) << endl;

    fc_cout << "TxApsBytes Requested Signal is " <<(uint32)(uint8)theApsBytes.requestedSignal 
                << ", Bridged Signal is " <<(uint32)(uint8)theApsBytes.bridgedSignal <<endl;
        
    fc_cout <<noshowbase;

#endif
    printf("TxAps(%#X): REQ(%X),A(%x),B(%x),D(%x),R(%x),RequestedSig(%d),BridgedSig(%d)\r\n",
            theTxApsBytes, theApsBytes.requestAndProtType.request, theApsBytes.requestAndProtType.bitA, 
            theApsBytes.requestAndProtType.bitB, theApsBytes.requestAndProtType.bitD, theApsBytes.requestAndProtType.bitR,
            theApsBytes.requestedSignal, theApsBytes.bridgedSignal);
}
