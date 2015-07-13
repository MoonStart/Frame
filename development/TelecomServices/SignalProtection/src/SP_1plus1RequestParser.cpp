// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif
#include "../SP_TestMenu.h"

#include "../SP_1plus1K1K2Receiver.h"
#include "../SP_1plus1RequestParser.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_1plus1Selector.h"
#include "../SP_DefectProcessorAction.h"
#include "../SP_1plus1APSController.h"
#include "../SP_DefectProcessorAction.h"

#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include "../SP_SwitchingCommandResult.h"
#include <SignalProtection/SP_1plus1BaseApplication.h>
#include "../SP_1plus1ProtectionGroupStatus.h"
#include <Blackboard/FC_BbAction.h>
#include <CommonTypes/CT_SP_SwitchingPriority.h>

extern int gSP_DebugTraceSnc;

//##ModelId=390583FB0158
SP_1plus1RequestParser::SP_1plus1RequestParser(SP_1plus1ProtectionAction& theProtectionAction):
    myCommand(CT_SP_NO_REQUEST),
    myCommandHistory(CT_SP_NO_REQUEST),
    myProtectionAction(theProtectionAction),
    myDefectStatus(CT_SP_AUTO_NONE,CT_SP_AUTO_NONE),
    myHighestRequest(CT_SP_NO_REQUEST,CT_SP_NO_REQUEST),
    myBestSide(CT_SP_INVALID_PROTECTION_SIDE),
    myUpsrHoldOffTime(60),
    myWorkingCallbackTimer(*theProtectionAction.GetBbAction(), true), //high priority timer
    myProtectionCallbackTimer(*theProtectionAction.GetBbAction(), true), //high priority timer
    myHoldOffTimer(NULL, NULL),
    mySFDefects(NULL),
    mySFLowDefects(NULL),
    mySDDefects(NULL),
    myBestSideUsable(true),
    myEffectiveRequest(CT_SP_NO_REQUEST),
    myEffectiveRequestIsRemote(false),
    myRemoteRequest(CT_SP_APS_REQUEST_NR),
    myTestingApsBytes(0),
    myTestingMode(0),
    myFopPmDetected(false),
    myActualApsBidir(CT_SP_WITHOUTAPS_UNIDIR)
{
    myHoldOffTimer.working = &myWorkingCallbackTimer;
    myHoldOffTimer.protection = &myProtectionCallbackTimer;

    myHighestRequestIsRemote.working = false;
    myHighestRequestIsRemote.protection = false;

    mySFDefects = new CT_SP_ProtectionPair<Defect>(CT_TEL_MS_AIS_DEFECT, CT_TEL_MS_AIS_DEFECT);
    mySFLowDefects = new CT_SP_ProtectionPair<Defect>(CT_TEL_HOP_SFBER_DEFECT, CT_TEL_HOP_SFBER_DEFECT);
    mySDDefects = new CT_SP_ProtectionPair<Defect>(CT_TEL_MS_SDBER_DEFECT, CT_TEL_MS_SDBER_DEFECT);
}

//##ModelId=390583FB019E
SP_1plus1RequestParser::~SP_1plus1RequestParser()
{
    delete mySFDefects;
    delete mySFLowDefects;
    delete mySDDefects;
}

//##ModelId=3B8BC9E1032C
FC_Milliseconds SP_1plus1RequestParser::GetUpsrHoldOffTime()
{
    return myUpsrHoldOffTime;
}

//##ModelId=3B8BC9E10336
void SP_1plus1RequestParser::SetUpsrHoldOffTime(FC_Milliseconds theHoldOffTime)
{
    myUpsrHoldOffTime = theHoldOffTime;
}

//##ModelId=3B8BC9E10323
void SP_1plus1RequestParser::StopTimers()
{
    // Stop timer and soaking defect
    myHoldOffTimer.working->Stop();
    myHoldOffTimer.protection->Stop();
}

//##ModelId=39ACEFBA0058
void SP_1plus1RequestParser::Reset()
{
    // run the request parser in order to initialize defect status and count
    RunWithReason(0,NULL,NULL);

    // reset attributes
    myCommand = CT_SP_CommandType(CT_SP_NO_REQUEST);
    myDefectStatus = CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect>(CT_SP_AUTO_NONE,CT_SP_AUTO_NONE);
    myHighestRequest = CT_SP_ProtectionPair<CT_SP_Request>(CT_SP_NO_REQUEST,CT_SP_NO_REQUEST);
    myBestSide = CT_SP_Protection(CT_SP_INVALID_PROTECTION_SIDE);
    myActualApsBidir = CT_SP_WITHOUTAPS_UNIDIR;
    StopTimers();

    SetFopPmToggle(false);
}

#define UPDATE_FACILITY_FAILURE(side, path) \
    {\
        aDefectStatus.side = \
            UpdateFailureStatus( \
                            *myProtectionAction.myMonDefectsRegion.side,\
                            myProtectionAction.myMonStatusRegion.side,\
                            mySFDefects->side,\
                            mySFLowDefects->side,\
                            mySDDefects->side,\
                            myProtectionAction.Get1plus1Config().Get1plus1Type(), \
                            myProtectionAction.Get1plus1Config().Get1plus1SubType(), \
                            aGlitch,\
                            myProtectionAction.myMONObjectIndex.side,\
                            myProtectionAction.Get1plus1Config().GetSources().side.GetPortId(),\
                            myProtectionAction.myDefectProcessor->GetLayer(), \
                            &myProtectionAction, \
                            aFacility, \
                            myProtectionAction.myTspiiInterfaces.side, \
                            myProtectionAction.mySPDefects.side);\
        /* keep defect with highest priority */ \
        /* all STS48s must be in defect to set Line as failed */ \
        /* If STS#0, initialize global failure */ \
        if (path==0 || \
            myDefectStatus.side != CT_SP_AUTO_NONE) \
        { \
            if (aDefectStatus.side == CT_SP_AUTO_NONE || \
                aDefectStatus.side > myDefectStatus.side) \
            { \
                /* Clear failure if an STS is not failed or ... */\
                /* 'Upgrade' failure if it is higher priority */ \
                myDefectStatus.side = aDefectStatus.side; \
            } \
        } \
    }


//##ModelId=3911CCD6005A
FC_Object*  SP_1plus1RequestParser::DoRunWithReason(unsigned theRunReason,
                                                       FC_Object* theInvokerObj,
                                                       FC_Object* theParam)
{

    CT_SP_Protection myPreBestSide = myBestSide;
    // suppose there is no glitch initially
    bool aGlitch(false);
    CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect> aDefectStatus(CT_SP_AUTO_NONE,CT_SP_AUTO_NONE);
    CT_SP_Protection aFacility = CT_SP_WORKING_SIDE;
    CT_SP_1plus1Type the1plus1Type = myProtectionAction.Get1plus1Config().Get1plus1Type();
    bool withAps = myProtectionAction.Get1plus1Config().IsBiSwitching();

    // clear current defects
    myDefectStatus = aDefectStatus;

    //set the current selected side to be usable
    myBestSideUsable = true;

    if (the1plus1Type != CT_SP_UNKNOWN)
    {
        // Read the SD/SF status on each facility
        UPDATE_FACILITY_FAILURE(working, 0);

        //protect facility may not always be defined i.e one source timing protection
        if (myProtectionAction.myMonDefectsRegion.protection != NULL)
        {
            aFacility = CT_SP_PROTECTION_SIDE;
            UPDATE_FACILITY_FAILURE(protection, 0);
        }
        else
        {
            //default to SF, so that the protect source will never be picked
            myDefectStatus.protection = CT_SP_AUTO_SF;
        }
    }
    else
        FC_REPORT_ERROR(FC_NotSupportedError, "Unexpected 1+1 type");


    // re-schedule the protection action to run because Monitoring service won't
    // recall us in case of a glitch
    if (aGlitch)
        myProtectionAction.GetHighPriorityWakeUpAction().RunWithReason(SP_DEFECT_GLITCH_REASON, this, this);

#define SOAK_FAILURE(side) \
    /* CHECK IF DEFECT IS CURRENTLY BEING SOAKED */ \
    if (myHoldOffTimer.side->IsStarted() && \
        myHoldOffTimer.side->IsExpired()) \
    { \
        /* DEFECT SOAKING COMPLETED */ \
        if (myDefectStatus.side == CT_SP_AUTO_NONE) \
            /* If the defect is cleared, clear the expired timer */ \
            myHoldOffTimer.side->Stop(); \
    }\
    else \
    { \
        if (myDefectStatus.side != CT_SP_AUTO_NONE) \
        {\
            /* DEFECT MUST BE SOAKED */ \
            myDefectStatus.side = CT_SP_AUTO_NONE; \
            if (!myHoldOffTimer.side->IsStarted()) \
                myHoldOffTimer.side->Start((FC_Milliseconds)(myProtectionAction.Get1plus1Config().GetHoldOffTimer() - myProtectionAction.GetHoldOffTimerOffset())); \
        }\
    }

    // soak defect if hold off timer is enabled and the defect is local
    if (myProtectionAction.Get1plus1Config().GetHoldOffEnabled())
    {
        if (myProtectionAction.IsLocalDefect(CT_SP_WORKING_SIDE))
        {
            SOAK_FAILURE(working);
        }

        if (myProtectionAction.IsLocalDefect(CT_SP_PROTECTION_SIDE))
        {
            SOAK_FAILURE(protection);
        }
    }

    CT_SP_ProtectionPair<CT_SP_Request> aCurrentDefectRequest(CT_SP_NO_REQUEST, CT_SP_NO_REQUEST);

    if (gSP_DebugTraceSnc) 
    {
          fc_cout<< " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
            << " myDefectStatus.working is " << (uint32) (myDefectStatus.working) 
            << " myDefectStatus.protection is " << (uint32) (myDefectStatus.protection) <<endl;
    }

    switch(myDefectStatus.working)
    {
    case CT_SP_AUTO_SF:     aCurrentDefectRequest.working = CT_SP_1PLUS1_SF_W;     break;
    case CT_SP_AUTO_SF_LOW: aCurrentDefectRequest.working = CT_SP_1PLUS1_SF_LOW_W; break;
    case CT_SP_AUTO_SD:     aCurrentDefectRequest.working = CT_SP_1PLUS1_SD_W;     break;
    // no default required
    }

    switch(myDefectStatus.protection)
    {
    case CT_SP_AUTO_SF:     aCurrentDefectRequest.protection = CT_SP_1PLUS1_SF_P;      break;
    case CT_SP_AUTO_SF_LOW: aCurrentDefectRequest.protection = CT_SP_1PLUS1_SF_LOW_P;  break;
    case CT_SP_AUTO_SD:     aCurrentDefectRequest.protection = CT_SP_1PLUS1_SD_P;      break;
    // no default required
    }


    // Check on which side the command applies to
    CT_SP_ProtectionPair<bool> commandAffects(false,false);

    if (gSP_DebugTraceSnc)
    {
       fc_cout<< " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
               << " myCommand.myRequest is " << (uint32) (myCommand.myRequest) <<endl;
    }

    switch (myCommand.myRequest)
    {
    case CT_SP_1PLUS1_MS_P:
    case CT_SP_1PLUS1_FS_P:
    case CT_SP_1PLUS1_EXER_P:
        commandAffects.working = true;
        break;
    case CT_SP_1PLUS1_LK_P:
    case CT_SP_1PLUS1_FS_W:
    case CT_SP_1PLUS1_MS_W:
    case CT_SP_1PLUS1_EXER_W:
        commandAffects.protection = true;
        break;
    case CT_SP_NO_REQUEST:
    case CT_SP_1PLUS1_CLEAR:
        break;
    default:
        FC_THROW_ERROR(FC_InvalidArgumentError, "Invalid 1+1 command");
    }

    // Update highest priority request of each facility
    if (commandAffects.working)
    {
        myHighestRequest.protection = aCurrentDefectRequest.protection;
        myHighestRequest.working    = GetHighestPriorityRequest(myCommand.myRequest,
                                                                aCurrentDefectRequest.working);
    }
    else if (commandAffects.protection)
    {
        myHighestRequest.working    = aCurrentDefectRequest.working;
        myHighestRequest.protection = GetHighestPriorityRequest(myCommand.myRequest,
                                                                aCurrentDefectRequest.protection);
    }
    else
    {
        myHighestRequest.working    = aCurrentDefectRequest.working;
        myHighestRequest.protection = aCurrentDefectRequest.protection;
    }

        //----------------------------------------BISNC start------------------------------------------------------
    if (myDefectStatus.working != CT_SP_AUTO_NONE && gSP_DebugTraceSnc)
    {
        printf("BISNC:++++: Work Defect -- %s\n", DISPLAY_CT_SP_AutoSwitchDefect(myDefectStatus.working));
    }

    if (myDefectStatus.protection != CT_SP_AUTO_NONE && gSP_DebugTraceSnc)
    {
        printf("BISNC:++++: Prot Defect -- %s\n", DISPLAY_CT_SP_AutoSwitchDefect(myDefectStatus.protection));
    }

    // disable the FOP at the begining, only B not match can enable FOP, otherwise FOP is always disabled
    SetFopPmToggle(false);
    
    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        
        //printf("BISNC:++++: pass 1st check -- it is bi snc\n");

        uint32 retApsBytes;

        if (myTestingMode == 0)
        { 
            retApsBytes = myProtectionAction.GetApsBytes();
        }
        else
        {
            retApsBytes = myTestingApsBytes;
        }

        APS_BYTES* apsBytes = (APS_BYTES*)&retApsBytes;

        if (gSP_DebugTraceSnc) 
        	printf("RxAps(%#X): REQ(%X),A(%x),B(%x),D(%x),R(%x),RequestedSig(%d),BridgedSig(%d)\r\n",
                retApsBytes, apsBytes->requestAndProtType.request, apsBytes->requestAndProtType.bitA, 
                apsBytes->requestAndProtType.bitB, apsBytes->requestAndProtType.bitD, apsBytes->requestAndProtType.bitR,
                apsBytes->requestedSignal, apsBytes->bridgedSignal);

        if (myHighestRequest.protection != CT_SP_1PLUS1_SF_P && myHighestRequest.protection != CT_SP_1PLUS1_SF_LOW_P 
            && retApsBytes != 0 && retApsBytes != 0x66666666)
        {
            myRemoteRequest = apsBytes->requestAndProtType.request;

            if (apsBytes->requestAndProtType.bitB == 1) // far end protection is 1:n
            {
                // If the "B" bit mismatches, the selector is released since 1:n and 1+1 are incompatible
                // TODO: switch back to working side immemidiately, how???
                // enable FOP
                SetFopPmToggle(true);

                SetActualApsBidir(CT_SP_WITHOUTAPS_UNIDIR);

        


                if (gSP_DebugTraceSnc) 
                {
                     fc_cout << " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
                           << " SP_1plus1RequestParser::DoRunWithReason 1111 SetActualApsBidir to "  << (uint32) (GetActualApsBidir()) <<endl;
                     printf("BISNC:++++: remote is 1:n\n");
                }

            }
            else if (apsBytes->requestAndProtType.bitA == 0) // far end protection doesn't use APS channel
            {
                // If the "A" bit mismatches, the side expecting APS will fall back to 1+1 unidirectional switching without APS.
                // Ignore the remote request
                
                // Open issue: request prioriry should be dynamically calculated by protection type and whether bitD mismatches
                // Not only SP application needs to know bitD, also Agent PROT application, thus whether bitD mismatches must be known by Agent PROT application too.

                SetActualApsBidir(CT_SP_WITHOUTAPS_UNIDIR);

         
                if (gSP_DebugTraceSnc) 
                {
                   fc_cout << " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
                           << " SP_1plus1RequestParser::DoRunWithReason 2222 SetActualApsBidir to "  << (uint32)(GetActualApsBidir()) <<endl;
                   printf("BISNC:++++: remote is without APS\n");

                }

            }
            else if (apsBytes->requestAndProtType.bitD == 0) // far end protection is unidirectional switching
            {
                // If the "D" bit mismatches, the bidirectional side will fall back to unidirectional switching.
                // Since we don't have 1+1 Unidirectional w/APS, this side will fall back to 1+1 unidirectional switching without APS.
                // Ignore the remote request.
                
                // Open issue: request prioriry should be dynamically calculated by protection type and whether bitD mismatches
                // Not only SP application needs to know bitD, also Agent PROT application, thus whether bitD mismatches must be known by Agent PROT application too.
                SetActualApsBidir(CT_SP_WITHOUTAPS_UNIDIR);

                
                if (gSP_DebugTraceSnc) 
                {
                   fc_cout << " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
                           << " SP_1plus1RequestParser::DoRunWithReason 3333 SetActualApsBidir to "  << (uint32)(GetActualApsBidir())<<endl;
                   printf("BISNC:++++: remote is unidirectional\n");
                }

            }
            else
            {
                SetActualApsBidir(CT_SP_WITHAPS_BIDIR);

                // Get the remote request
                CT_SP_ProtectionPair<CT_SP_Request> remoteRequests(CT_SP_NO_REQUEST, CT_SP_NO_REQUEST);

                ConvertApsRequestToSpRequest(*apsBytes, remoteRequests);

                if (gSP_DebugTraceSnc)
                {

                   fc_cout << " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
                        << " SP_1plus1RequestParser::DoRunWithReason 4444 SetActualApsBidir to "  <<(uint32)( GetActualApsBidir())<<endl;

                    printf("RemoteWorkRequest[%s]\n", DISPLAY_CT_SP_Request_1PLUS1(remoteRequests.working));
                    printf("RemoteProtRequest[%s]\n", DISPLAY_CT_SP_Request_1PLUS1(remoteRequests.protection));
                }
                // If the "R" bit mismatches one side will clear switches to "WTR" and the other will clear to "DNR".
                bool revertive = myProtectionAction.Get1plus1Config().GetRevertiveMode();
                if (revertive && apsBytes->requestAndProtType.bitR == 0)
                {
                    if (gSP_DebugTraceSnc) printf("BISNC:++++: R mismatches, local is revertive\n");

                    if (remoteRequests.working == CT_SP_1PLUS1_DO_NOT_REVERT)
                    {
                        remoteRequests.working = CT_SP_NO_REQUEST;
                    }
                }
                else if (!revertive && apsBytes->requestAndProtType.bitR == 1)
                {
                    if (gSP_DebugTraceSnc) printf("BISNC:++++: R mismatches, local is non-revertive\n");

                    if (remoteRequests.working == CT_SP_1PLUS1_WTR)
                    {
                        remoteRequests.working = CT_SP_NO_REQUEST;
                    }
                }
                else // revertive-mode is compatible
                {
                    // ignore the remote request if it is wrong
                    if ((apsBytes->requestAndProtType.bitR == 0 && remoteRequests.working == CT_SP_1PLUS1_WTR) ||
                        (apsBytes->requestAndProtType.bitR == 1 && remoteRequests.working == CT_SP_1PLUS1_DO_NOT_REVERT))
                    {
                        if (gSP_DebugTraceSnc) printf("BISNC:++++: Wrong DNR or WTR\n");
                        
                        remoteRequests.working = CT_SP_NO_REQUEST;
                    }
                }

                // No request exists on working/protection during WTR, but the lower remote rquest EXER should be ignored.
                if (myProtectionAction.myAPSControllerPtr != NULL && myProtectionAction.myAPSControllerPtr->IsWtrTimerRunning())
                {
                    if (remoteRequests.working == CT_SP_1PLUS1_EXER_P)
                    {
                        remoteRequests.working = CT_SP_NO_REQUEST;
                    }
                    if (remoteRequests.protection == CT_SP_1PLUS1_EXER_W)
                    {
                        remoteRequests.protection = CT_SP_NO_REQUEST;
                    }
                }

                // till now, myHighestRequest is the higher one between myCommand and myDefectStatus
                // below, compare myHighestRequest and remoteRequest, the higher one is the new myHighestRequest

                // According to G.873.1:
                // In bidirectional switching, the local request will be indicated 
                // only in the case where it is as high or higher than any request 
                // received from the far end over the APS channel.
                int localHighestRequestPriorityWorking = CT_SP_SwitchingPriority::GetPriority(myHighestRequest.working, the1plus1Type, myActualApsBidir);
                int remoteRequestPriorityWorking = CT_SP_SwitchingPriority::GetPriority(remoteRequests.working, the1plus1Type, myActualApsBidir);
                if (localHighestRequestPriorityWorking > remoteRequestPriorityWorking)
                {
                    // keep myHighestRequest.working not changed
                    myHighestRequestIsRemote.working = false;
                }
                else if (localHighestRequestPriorityWorking < remoteRequestPriorityWorking)
                {
                    myHighestRequest.working = remoteRequests.working;
                    myHighestRequestIsRemote.working = true;
                }
                else 
                //if(localHighestRequestPriorityWorking == remoteRequestPriorityWorking)
                {
                    // MR t71mr00224099, ignore the remote NR
                    if (myHighestRequest.working == CT_SP_NO_REQUEST) {
                        myHighestRequestIsRemote.working = false;
                    }
                }

                int localHighestRequestPriorityProtection = CT_SP_SwitchingPriority::GetPriority(myHighestRequest.protection, the1plus1Type, myActualApsBidir);
                int remoteRequestPriorityProtection = CT_SP_SwitchingPriority::GetPriority(remoteRequests.protection, the1plus1Type, myActualApsBidir);
                if (localHighestRequestPriorityProtection > remoteRequestPriorityProtection)
                {
                    // keep myHighestRequest.protection not changed
                    myHighestRequestIsRemote.protection = false;
                }
                else if (localHighestRequestPriorityProtection < remoteRequestPriorityProtection)
                {
                    myHighestRequest.protection = remoteRequests.protection;
                    myHighestRequestIsRemote.protection = true;
                }
                else if(localHighestRequestPriorityProtection == remoteRequestPriorityProtection)
                {
                    if (myHighestRequest.protection == CT_SP_NO_REQUEST) {
                        myHighestRequestIsRemote.protection = false;
                    }
                }
            }
            if (gSP_DebugTraceSnc)
            {
                printf("BISNC:++++: Final calculating\n");
                printf("            Cmd[%s], DoW[%s], DoP[%s]\n", DISPLAY_CT_SP_Request_1PLUS1(myCommand.myRequest),
                        DISPLAY_CT_SP_Request_1PLUS1(aCurrentDefectRequest.working), DISPLAY_CT_SP_Request_1PLUS1(aCurrentDefectRequest.protection));
                printf("            Output -HighestOnWork[%s][%s]\n", DISPLAY_CT_SP_Request_1PLUS1(myHighestRequest.working), myHighestRequestIsRemote.working ? "remote" : "local");
                printf("            Output -HighestOnProt[%s][%s]\n", DISPLAY_CT_SP_Request_1PLUS1(myHighestRequest.protection), myHighestRequestIsRemote.protection ? "remote" : "local");
            }
        }
        else // signal failure exists on protetion side, ignore the remote request trasmitted via protection channel
        {
           if ((retApsBytes == 0 ||retApsBytes == 0x66666666) &&
               myHighestRequest.protection != CT_SP_1PLUS1_SF_P &&
               myHighestRequest.protection != CT_SP_1PLUS1_SF_LOW_P)
           {
              SetActualApsBidir(CT_SP_WITHOUTAPS_UNIDIR);  //suppose it downgrades following uni_dir switch behavior
           }else
           {
              SetActualApsBidir(CT_SP_WITHAPS_BIDIR); //suppose it's still following bi_dir switch behavior
           }
        

            // do nothing.
            myHighestRequestIsRemote.working = false;
            myHighestRequestIsRemote.protection = false;
            if (gSP_DebugTraceSnc) 
            {
               fc_cout << " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
                    << " SP_1plus1RequestParser::DoRunWithReason 5555 SetActualApsBidir to "  <<(uint32)( GetActualApsBidir())<<endl;
               printf("BISNC:++++: Ignore APS becuase of SF_P or Invalid Bytes\n");
            }
        }
    }
    else // unidirectional switching, hightest request has been decided.
    {
    
        myHighestRequestIsRemote.working = false;
        myHighestRequestIsRemote.protection = false;

        SetActualApsBidir(CT_SP_WITHOUTAPS_UNIDIR);

        if (gSP_DebugTraceSnc) 
        {
           fc_cout << " PgId is " << (uint32)(myProtectionAction.Get1plus1Config().GetGroupID())
                << " SP_1plus1RequestParser::DoRunWithReason 6666 SetActualApsBidir to "  << (uint32)(GetActualApsBidir())<<endl;
        }

        // do nothing.
    }

    //----------------------------------------BISNC end------------------------------------------------------

    //Determine the best side.
    if(CT_SP_SwitchingPriority::GetPriority(myHighestRequest.working, the1plus1Type, myActualApsBidir) <
        CT_SP_SwitchingPriority::GetPriority(myHighestRequest.protection, the1plus1Type, myActualApsBidir) )
    {
       myBestSide = CT_SP_WORKING_SIDE;
       // if there was a command to switch TO protection, flush it

       myEffectiveRequest = myHighestRequest.protection;
       myEffectiveRequestIsRemote = myHighestRequestIsRemote.protection;

       // if there was a command to switch TO protection, flush it
       if (commandAffects.working)
       {
           myCommand.myRequest = myHighestRequest.working = CT_SP_NO_REQUEST;
       }
    }
    else if(CT_SP_SwitchingPriority::GetPriority(myHighestRequest.working, the1plus1Type, myActualApsBidir) >
        CT_SP_SwitchingPriority::GetPriority(myHighestRequest.protection, the1plus1Type, myActualApsBidir)) 
    {

        myEffectiveRequest = myHighestRequest.working; 
        myEffectiveRequestIsRemote = myHighestRequestIsRemote.working;

        if (myHighestRequest.working != CT_SP_1PLUS1_RR
            && myHighestRequest.working != CT_SP_1PLUS1_DO_NOT_REVERT
            && myHighestRequest.working != CT_SP_1PLUS1_WTR)
        {
           myBestSide = CT_SP_PROTECTION_SIDE; 

       // if there was a command to switch TO working, flush it
       if (commandAffects.protection)
           myCommand.myRequest = myHighestRequest.protection = CT_SP_NO_REQUEST;
        }
        else
        {
            // DNR/WTR/RR doesn't trigger switch
            // do nothing, keep last state
        }

    }
    else
    {
        myBestSide = CT_SP_INVALID_PROTECTION_SIDE;

        myEffectiveRequest = myHighestRequest.working;
        myEffectiveRequestIsRemote = false;
    }

    if (gSP_DebugTraceSnc) printf("BISNC:++++: Best side is [%s]\n", DISPLAY_CT_SP_Protection(myBestSide));

    // Clear the command if it has been drop for higher
    // priority defect
    switch (myHighestRequest.working)
    {
    case CT_SP_1PLUS1_SF_W:
    case CT_SP_1PLUS1_SF_LOW_W:
    case CT_SP_1PLUS1_SD_W:
    case CT_SP_1PLUS1_SF_P:
    case CT_SP_1PLUS1_SF_LOW_P:
    case CT_SP_1PLUS1_SD_P:
        if (CT_SP_SwitchingPriority::GetPriority(myHighestRequest.working, the1plus1Type, myActualApsBidir) > CT_SP_SwitchingPriority::GetPriority(myCommand.myRequest, the1plus1Type, myActualApsBidir))
        {
           ClearSwitchingCommand();
        }
    }
    switch (myHighestRequest.protection)
    {
    case CT_SP_1PLUS1_SF_W:
    case CT_SP_1PLUS1_SF_LOW_W:
    case CT_SP_1PLUS1_SD_W:
    case CT_SP_1PLUS1_SF_P:
    case CT_SP_1PLUS1_SF_LOW_P:
    case CT_SP_1PLUS1_SD_P:
        if (CT_SP_SwitchingPriority::GetPriority(myHighestRequest.protection, the1plus1Type, myActualApsBidir) > CT_SP_SwitchingPriority::GetPriority(myCommand.myRequest, the1plus1Type, myActualApsBidir))
        {
           ClearSwitchingCommand();
        }
    }
    
    //----------------------------------------------------------------------------------------------

    //For timing protection schemes, the rcvd SSM also
    //has to be taken into account to select the best side
    //If the best side is getting DUS/DNU, it cannot be selected
    //If the SSM rcvd on the best side is lower than
    //the other side, it cannot be selected either
    //In either of these cases, there are 2 options
    //either switch to the other reference (if it is not DUS/DNU or failed)
    //or switch to internal

    if (the1plus1Type == CT_SP_TIMING)
    {
        bool isSsmSwitchingAllowed = myProtectionAction.IsSsmSwitchingAllowed();
        CT_SP_Protection thePreferredSide = myProtectionAction.GetPreferredSide();
        CT_SP_Protection theBestSide = myBestSide;
        //if my best side is invalid
        //it means that the selected side has not changed
        //set the best side equal to the last selected side
        if (myBestSide == CT_SP_INVALID_PROTECTION_SIDE)
        {
            if (myProtectionAction.mySelectorPtr)
            {
                switch (myProtectionAction.mySelectorPtr->GetSelection())
                {
                     case CT_SP_PROTECTION_SIDE: theBestSide = CT_SP_PROTECTION_SIDE; break;
                     case CT_SP_WORKING_SIDE:    theBestSide = CT_SP_WORKING_SIDE; break;
                     default: break;
                }
            }
        }

        //Get the Rx SSM
        CT_FAC_RxSsm theWorkingRxSSM = CT_RxSsm_DUS; //default to DUS
        CT_FAC_RxSsm theProtectRxSSM = CT_RxSsm_DUS; //default to DUS

        if (isSsmSwitchingAllowed)
        {
            theWorkingRxSSM = UpdateRxSSM(myProtectionAction.myMonStatusRegion.working, myProtectionAction.myMONObjectIndex.working, myProtectionAction.Get1plus1Config().Get1plus1SubType(), CT_SP_WORKING_SIDE, myProtectionAction.GetConfig().GetFacilityStandard());
            //if protect is configured, read the rx SSM
            if (myProtectionAction.myMonDefectsRegion.protection != NULL)
            {
                theProtectRxSSM = UpdateRxSSM(myProtectionAction.myMonStatusRegion.protection, myProtectionAction.myMONObjectIndex.protection, myProtectionAction.Get1plus1Config().Get1plus1SubType(), CT_SP_PROTECTION_SIDE, myProtectionAction.GetConfig().GetFacilityStandard());
            }
        }

        if (theBestSide == CT_SP_WORKING_SIDE)
        {
            //if the working side is failed, go into internal timing
            if (aCurrentDefectRequest.working == CT_SP_1PLUS1_SF_W || aCurrentDefectRequest.working == CT_SP_1PLUS1_SF_LOW_W)
            {
                myBestSideUsable = false;
            }
            else if (myCommand.myRequest == CT_SP_1PLUS1_FS_W  ||
                     myCommand.myRequest == CT_SP_1PLUS1_LK_P)
            {
                //working SSM is lower quality but we are not allowed to switch to protect
                //if working SSM is DUS/DNU go into internal timing
                if (isSsmSwitchingAllowed)
                {
                    if (theWorkingRxSSM == CT_RxSsm_DUS || theWorkingRxSSM == CT_RxSsm_DNU)
                        myBestSideUsable = false;
                }
            }
            else //working side not failed and we are not forced to it
            {
                //if the protection side is not failed
                if (aCurrentDefectRequest.protection == CT_SP_NO_REQUEST)
                {
                    //if SSM quality is better on the protect side and
                    //we are not forced to working, select the protect
                    //side instead
                    if (isSsmSwitchingAllowed)
                    {
                        if (GetHighestSSMPriority(theProtectRxSSM, theWorkingRxSSM))
                        {
                            //select protection
                            myBestSide = CT_SP_PROTECTION_SIDE;
                            //consider the working side degraded because it has a lower
                            //SSM quality. Status will be adjusted by protection action
                            //so degrade does not propagate in the status
                            myHighestRequest.working = CT_SP_1PLUS1_SD_W;
                            //clear any manual switches if they exist
                            if (myCommand.myRequest == CT_SP_1PLUS1_MS_W)
                                myCommand.myRequest = myHighestRequest.protection = CT_SP_NO_REQUEST;
                        }
                        else
                        {
                            //protect SSM quality is equal or lower in priority to working SSM
                            //if working SSM is DUS/DNU go into internal timing
                            if (theWorkingRxSSM == CT_RxSsm_DUS || theWorkingRxSSM == CT_RxSsm_DNU)
                            {
                                myBestSideUsable = false;
                            }
                            else
                            {
                                if (thePreferredSide == CT_SP_PROTECTION_SIDE)
                                {
                                    if(theWorkingRxSSM == theProtectRxSSM)
                                    {
                                        //Select protection side
                                        myHighestRequest.working = CT_SP_1PLUS1_SD_W;
                                        myBestSide = CT_SP_PROTECTION_SIDE;
                                    }
                                }
                                //keep the SD status for lower SSM on protect
                                //provided there are no other requests to switch to working
                                if ((GetHighestSSMPriority(theWorkingRxSSM, theProtectRxSSM)) &&
                                    (myHighestRequest.protection == CT_SP_NO_REQUEST))
                                {
                                    myHighestRequest.protection = CT_SP_1PLUS1_SD_P;
                                }
                            }
                        }
                    } //SSM switching allowed
                    else
                    {
                        if (myCommand.myRequest != CT_SP_1PLUS1_MS_W)
                        {
                            if (thePreferredSide == CT_SP_PROTECTION_SIDE)
                            {
                                //Select protection side
                                myHighestRequest.working = CT_SP_1PLUS1_SD_W;
                                myBestSide = CT_SP_PROTECTION_SIDE;
                            }
                        }
                    }
                }
                //protection side is failed
                else
                {
                    if (isSsmSwitchingAllowed)
                    {
                        if (theWorkingRxSSM == CT_RxSsm_DUS || theWorkingRxSSM == CT_RxSsm_DNU)
                            myBestSideUsable = false;
                    }
                }
            }
        }

        //protection active
        else if (theBestSide == CT_SP_PROTECTION_SIDE)
        {
            //if the protect side is failed, go into internal timing
            if (aCurrentDefectRequest.protection == CT_SP_1PLUS1_SF_P || aCurrentDefectRequest.protection == CT_SP_1PLUS1_SF_LOW_P)
            {
                myBestSideUsable = false;
            }
            else if (myCommand.myRequest == CT_SP_1PLUS1_FS_P)
            {
                if (isSsmSwitchingAllowed)
                {
                    //protect SSM is lower quality but we are not allowed to switch to working
                    //if protect SSM is DUS/DNU go into internal timing
                    if (theProtectRxSSM == CT_RxSsm_DUS || theProtectRxSSM == CT_RxSsm_DNU)
                        myBestSideUsable = false;
                }
            }
            else //protect side not failed or not forced to it
            {
                //if the working side is not failed
                if (aCurrentDefectRequest.working == CT_SP_NO_REQUEST)
                {
                    if (isSsmSwitchingAllowed)
                    {
                        //if SSM quality is better on the working side and
                        //we are not forced to protect, select the working
                        //side instead
                        if (GetHighestSSMPriority(theWorkingRxSSM, theProtectRxSSM))
                        {

                            //select working
                            myBestSide = CT_SP_WORKING_SIDE;
                            //consider the protect side degraded because it has a lower
                            //SSM quality. Status will be adjusted by protection action
                            //so degrade does not propagate in the status
                            myHighestRequest.protection = CT_SP_1PLUS1_SD_P;
                            //clear any manual switches if they exist
                            if (myCommand.myRequest == CT_SP_1PLUS1_MS_P)
                                myCommand.myRequest = myHighestRequest.working = CT_SP_NO_REQUEST;
                        }
                        else
                        {
                            //working SSM quality is equal or lower in priority to protect SSM
                            //if protect SSM is DUS/DNU go into internal timing
                            if (theProtectRxSSM == CT_RxSsm_DUS || theProtectRxSSM == CT_RxSsm_DNU)
                            {
                                myBestSideUsable = false;
                            }
                            else
                            {
                                if (thePreferredSide == CT_SP_WORKING_SIDE)
                                {
                                    if(theWorkingRxSSM == theProtectRxSSM)
                                    {
                                        //Select working side
                                        myHighestRequest.protection = CT_SP_1PLUS1_SD_P;
                                        myBestSide = CT_SP_WORKING_SIDE;
                                    }
                                }
                                //keep the SD status for lower SSM on working
                                //provided there are no other requests to switch to protection
                                if ((GetHighestSSMPriority(theProtectRxSSM, theWorkingRxSSM)) &&
                                   (myHighestRequest.working == CT_SP_NO_REQUEST))
                                {
                                    myHighestRequest.working = CT_SP_1PLUS1_SD_W;
                                }
                            }
                        }
                    } //SSM switching allowed
                    else
                    {
                        if (myCommand.myRequest != CT_SP_1PLUS1_MS_P)
                        {
                            if (thePreferredSide == CT_SP_WORKING_SIDE)
                            {
                                //Select working side
                                myHighestRequest.protection = CT_SP_1PLUS1_SD_P;
                                myBestSide = CT_SP_WORKING_SIDE;
                            }
                        }
                    }
                }
                //working side is failed
                else
                {
                    if (isSsmSwitchingAllowed)
                    {
                        if (theProtectRxSSM == CT_RxSsm_DUS || theProtectRxSSM == CT_RxSsm_DNU)
                            myBestSideUsable = false;
                    }
                }
            }
        }
    }

    if(SP_TestMenu::mySpDebug)
    {
        fc_cout << "[SP_1plus1RequestParser]Defect  W: " << DISPLAY_CT_SP_AutoSwitchDefect(myDefectStatus.working) << endl;
        fc_cout << "                                P: " << DISPLAY_CT_SP_AutoSwitchDefect(myDefectStatus.protection) << endl;
        fc_cout <<"                        HRequest W: " << DISPLAY_CT_SP_Request_1PLUS1(myHighestRequest.working) << endl;
        fc_cout << "                                P: " << DISPLAY_CT_SP_Request_1PLUS1(myHighestRequest.protection) << endl;

        if(myBestSide != myPreBestSide)
        {
            fc_cout << "[SP_1plus1RequestParser]BestSide change from " << DISPLAY_CT_SP_Protection(myPreBestSide) << " to " << DISPLAY_CT_SP_Protection(myBestSide) 
                    << endl;
        }
        else
        {
            fc_cout << "[SP_1plus1RequestParser]BestSide no change, keep " 
                    << endl;
        }

    }
    return NULL;
}


//##ModelId=39170C3F00CF
CT_SP_Request SP_1plus1RequestParser::GetHighestPriorityRequest(CT_SP_Request theARequest, CT_SP_Request theBRequest) const
{
    CT_SP_1plus1Type the1plus1Type = myProtectionAction.Get1plus1Config().Get1plus1Type();
    bool withAps = myProtectionAction.Get1plus1Config().IsBiSwitching();
    int Apriority = CT_SP_SwitchingPriority::GetPriority(theARequest, the1plus1Type, myActualApsBidir);
    int Bpriority = CT_SP_SwitchingPriority::GetPriority(theBRequest, the1plus1Type, myActualApsBidir);

    if (Apriority > Bpriority)
        return theARequest;
    else
        return theBRequest;
}

//##ModelId=3911CCD500F9
CT_SP_CommandResultCode SP_1plus1RequestParser::SetSwitchingCommand(CT_SP_CommandType& theCommand)
{
    CT_SP_1plus1Type the1plus1Type = myProtectionAction.Get1plus1Config().Get1plus1Type();
    bool withAps = myProtectionAction.Get1plus1Config().IsBiSwitching();
    CT_SP_Request theRequest = theCommand.myRequest;
    // if no request, return completed immediately
    // The facade interface always sends a NO_REQUEST after a command was done (completed or failed).
    if (theCommand.myRequest == CT_SP_NO_REQUEST)
    {
        //Check if we missed the clear command. If so, clear the
        //switch command now
        if (myCommand.myRequest != CT_SP_NO_REQUEST &&
            myCommand.myRequest != CT_SP_1PLUS1_CLEAR)
        {
            theRequest = CT_SP_1PLUS1_CLEAR;
        }
        else
        {
             return CT_SP_COMMAND_COMPLETED;
        }
    }

    // validate parameter
    int newPriority = CT_SP_SwitchingPriority::GetPriority(theRequest, the1plus1Type, myActualApsBidir);
    int oldPriority = CT_SP_SwitchingPriority::GetPriority(GetHighestPriorityRequest(myHighestRequest.working, myHighestRequest.protection), the1plus1Type, myActualApsBidir);

    fc_cout << "SP_1plus1RequestParser::SetSwitchingCommand theRequest is " << (uint32)theRequest
      << " the1plus1Type is " << (uint32) the1plus1Type
      << " myHighestRequest.working is " << (uint32)myHighestRequest.working
      << " myHighestRequest.protection is " <<(uint32)myHighestRequest.protection
      <<endl;


    if (oldPriority > newPriority)
    {
        //for timing protection schemes
        //a state of SD is an internal state
        //used to represent lower SSM quality.
        //Manual Switch commands should be allowed
        //if we are switching to reference with better quality
        if (the1plus1Type == CT_SP_TIMING)
        {
            bool acceptCommand = false;
            switch (theRequest)
            {
            case CT_SP_1PLUS1_MS_W:
                if ((CT_SP_SwitchingPriority::GetPriority(myHighestRequest.protection, the1plus1Type, myActualApsBidir) == oldPriority) &&
                    myHighestRequest.protection == CT_SP_1PLUS1_SD_P)
                    acceptCommand = true;
                break;
            case CT_SP_1PLUS1_MS_P:
                if ((CT_SP_SwitchingPriority::GetPriority(myHighestRequest.working, the1plus1Type, myActualApsBidir) == oldPriority) &&
                    myHighestRequest.working == CT_SP_1PLUS1_SD_W)
                    acceptCommand = true;
                break;
            default:
                break;
            }
            if (acceptCommand == true)
            {
                myCommand.myRequest = theRequest;
                return CT_SP_COMMAND_COMPLETED;
            }
            else
                return CT_SP_COMMAND_DENIED;
        }
        else
        {
            return CT_SP_COMMAND_DENIED;
        }
    }
    else if (oldPriority == newPriority)
    {
        //for timing protection, manual commands of same priority
        //are allowed to preempt each other (GR253 Section 5)
        if (the1plus1Type == CT_SP_TIMING)
        {
            myCommand.myRequest = theRequest;
            return CT_SP_COMMAND_COMPLETED;
        }
        else
        {
            return CT_SP_COMMAND_DENIED;
        }

    }
    else
    {
        myCommand.myRequest = theRequest;
        return CT_SP_COMMAND_COMPLETED;
    }
}

//##ModelId=3B8BC9E10322
void SP_1plus1RequestParser::ClearSwitchingCommand()
{
    // clear previous command
    myCommand.myRequest = CT_SP_NO_REQUEST;

}

//##ModelId=39170C3F02E1
bool SP_1plus1RequestParser::GetClearCommand()
{
    if (myCommand.myRequest == CT_SP_1PLUS1_CLEAR)
    {
        myCommand.myRequest = CT_SP_NO_REQUEST;
        return true;
    }
    else
        return false;
}



//  /////////////////////////////////////////////////////////////////
//  From FC_Object
//  /////////////////////////////////////////////////////////////////
//##ModelId=3B8BC9E102FA
ostream& SP_1plus1RequestParser::WriteObject( ostream& theStream )
{
    SP_RequestParser::WriteObject(theStream);

    theStream<<FC_InsertVar(myCommand);
    return theStream;
}

//##ModelId=3B8BC9E102DC
istream& SP_1plus1RequestParser::ReadObject( istream& theStream )
{
    SP_RequestParser::ReadObject(theStream);

    theStream>>FC_ExtractVar(myCommand);

    myCommandHistory = myCommand;

    return theStream;
}

//##ModelId=3B8BC9E102BE
FC_Stream& SP_1plus1RequestParser::WriteObjectBinary( FC_Stream& theStream )
{
    SP_RequestParser::WriteObjectBinary(theStream);

    theStream<<myCommand;
    return theStream;
}

//##ModelId=3B8BC9E102A0
FC_Stream& SP_1plus1RequestParser::ReadObjectBinary( FC_Stream& theStream )
{
    SP_RequestParser::ReadObjectBinary(theStream);

    theStream>>myCommand;

    myCommandHistory = myCommand;

    return theStream;
}

//  /////////////////////////////////////////////////////////////////
//  From RS_Redundant
//  /////////////////////////////////////////////////////////////////
//##ModelId=3B8BC9E10318
bool SP_1plus1RequestParser::HasChangedSinceLastCheck()
{
    bool hasChanged = SP_RequestParser::HasChangedSinceLastCheck();

    if ((myCommandHistory == myCommand) &&
        !hasChanged)
    {
        return false;
    }
    else
    {
        myCommandHistory = myCommand;
        return true;
    }
}


void SP_1plus1RequestParser::InitWarm()
{
    CT_SP_ProtectionPair<bool> commandAffects(false,false);
    switch (myCommand.myRequest)
    {
    case CT_SP_1PLUS1_MS_P:
    case CT_SP_1PLUS1_FS_P:
        commandAffects.working = true;
        break;
    case CT_SP_1PLUS1_LK_P:
    case CT_SP_1PLUS1_FS_W:
    case CT_SP_1PLUS1_MS_W:
        commandAffects.protection = true;
        break;
    default:
        break;
    }

    // Update highest priority request of each facility
    if (commandAffects.working)
    {
        myHighestRequest.working    = myCommand.myRequest;
    }
    else if (commandAffects.protection)
    {
        myHighestRequest.protection = myCommand.myRequest;
    }
}

void SP_1plus1RequestParser::ConvertApsRequestToSpRequest(APS_BYTES apsBytes, CT_SP_ProtectionPair<CT_SP_Request>& spRequest)
{
    spRequest.working = spRequest.protection = CT_SP_NO_REQUEST;
    
    switch (apsBytes.requestAndProtType.request)
    {
        case CT_SP_APS_REQUEST_LOP: // 1111 Lockout of Protection (LO)
        {
            spRequest.protection = CT_SP_1PLUS1_LK_P;
            break;
        }
        case CT_SP_APS_REQUEST_FS: // 1110 Forced Switch (FS)
        {
            if (apsBytes.requestedSignal == 1) // working signal is requested to be carried over the protection entity
            {
                spRequest.working = CT_SP_1PLUS1_FS_P;
            }
            else // Null signal is requested to be carried over the protection entity
            {
                spRequest.protection = CT_SP_1PLUS1_FS_W;
            }
            break;
        }
        case CT_SP_APS_REQUEST_SF: // 1100 Signal Fail (SF)
        {
            if (apsBytes.requestedSignal == 1) // working signal is requested to be carried over the protection entity
            {
                spRequest.working = CT_SP_1PLUS1_SF_W;
            }
            else // Null signal is requested to be carried over the protection entity
            {
                spRequest.protection = CT_SP_1PLUS1_SF_P;
            }
            break;
        }
        case CT_SP_APS_REQUEST_SD: // 1010 Signal Degrade (SD)
        {
            if (apsBytes.requestedSignal == 1) // working signal is requested to be carried over the protection entity
            {
                spRequest.working = CT_SP_1PLUS1_SD_W;
            }
            else // Null signal is requested to be carried over the protection entity
            {
                spRequest.protection = CT_SP_1PLUS1_SD_P;
            }
            break;
        }
        case CT_SP_APS_REQUEST_MS: // 1000 Manual Switch (MS)
        {
            if (apsBytes.requestedSignal == 1) // working signal is requested to be carried over the protection entity
            {
                spRequest.working = CT_SP_1PLUS1_MS_P;
            }
            else // Null signal is requested to be carried over the protection entity
            {
                spRequest.protection = CT_SP_1PLUS1_MS_W;
            }
            break;
        }
        case CT_SP_APS_REQUEST_WTR: // 0110 Wait to Restore (WTR)
        {
            spRequest.working = CT_SP_1PLUS1_WTR;
            break;
        }
        case CT_SP_APS_REQUEST_EXER: // 0100 Exercise (EXER)
        {
            if (apsBytes.requestedSignal == 1) // working signal is requested to be carried over the protection entity
            {
                spRequest.working = CT_SP_1PLUS1_EXER_P;
            }
            else // Null signal is requested to be carried over the protection entity
            {
                spRequest.protection = CT_SP_1PLUS1_EXER_W;
            }
            break;

        }
        case CT_SP_APS_REQUEST_RR: // 0010 Reverse Request (RR)
        {
            spRequest.working = CT_SP_1PLUS1_RR;
            break;
        }
        case CT_SP_APS_REQUEST_DNR: // 0001 Do Not Revert (DNR)
        {
            spRequest.working = CT_SP_1PLUS1_DO_NOT_REVERT;
            break;
        }
        case CT_SP_APS_REQUEST_NR: // 0000 No Request (NR)
        {
            break;
        }
        default: break; // Others Reserved for future international standardization
    }
}



CT_SP_ApsBidirType SP_1plus1RequestParser::GetActualApsBidir() const
{
    return myActualApsBidir;
}

void SP_1plus1RequestParser::SetActualApsBidir(CT_SP_ApsBidirType theActualApsBidir)
{
    myActualApsBidir = theActualApsBidir;
}
