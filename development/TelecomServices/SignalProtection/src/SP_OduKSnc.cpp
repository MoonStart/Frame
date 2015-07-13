// Copyright(c) Tellabs Transport Group. All rights reserved. 

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../SP_OduKSnc.h"
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_Otu.h>
#include <Configuration/CFG_Odu.h>
#include <Configuration/CFG_Tcm.h>
#include <Configuration/CFG_Misc.h>
#include <ErrorService/FC_Error.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>
#include <SignalProtection/SP_1plus1SubApplication.h>
#include <SignalProtection/SP_SelectorPositionRegion.h>
#include <SignalProtection/SP_1plus1Selector.h>
#include <SignalProtection/SP_1plus1RequestParser.h>
#include <SignalProtection/SP_OduKSncMiscActions.h>
#include <SignalProtection/SP_1plus1K1K2Transmitter.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_FecIf.h>
#include <TsPii/TSPII_DwIf.h>
#include <TsPii/TSPII_OpticalIf.h>
#include <TsPii/TSPII_SncIf.h>
#include <TsPii/TSPII_TcmIf.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_OptConfig.h>
#include <Monitoring/MON_OtuConfig.h>
#include <Monitoring/MON_OduConfig.h>
#include <Monitoring/MON_TcmConfig.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_OduDefinitions.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <PII_Sleep.h>
#include <TimeService/FC_TimePrecise.h>

#ifdef __TARGET__
#endif


#define INVALID_PQW_CHANNEL 0xFF

#define SP_PQW_USER_CMD_MSG_MS_P 0x1
#define SP_PQW_USER_CMD_MSG_FS_P 0x2
#define SP_PQW_USER_CMD_MSG_LK_P 0x3
#define SP_PQW_USER_CMD_MSG_FS_W 0x4
#define SP_PQW_USER_CMD_MSG_MS_W 0x5
#define SP_PQW_USER_CMD_MSG_WTR  0x6
#define SP_PQW_USER_CMD_MSG_CLR  0x7
uint16 SP_PQW_USER_CMD_MSG_WTR_SHIFTED = (SP_PQW_USER_CMD_MSG_WTR << SP_PQW_USER_CMD_SHIFT);

int gSP_DebugTraceSnc = 0;


////////////////////////////////////////////////////////////////////////////////
SP_OduKSnc::SP_OduKSnc(SP_1plus1SubApplication & theApplIf, SP_1plus1ProtectionAction& theProtAction, SP_1plus1Selector& theSelector, int theIndex) :
    myApplIf(theApplIf),
    myProtectionAction(theProtAction),
    mySelector(theSelector),
    myMCFilterRegion(NULL),
    myPrivIndex(theIndex),
    myXCRouteCfgRegion(NULL),
    myCfgSwitchModeRegion(NULL)
{

    myShelfId = CSPII_CardIF::GetInstance()->GetShelfId();
    mySlotId = CSPII_CardIF::GetInstance()->GetSlotId();

    T6100_ShelfIf* theShelf = T6100_MainAppIf::Instance().GetShelfPtr(myShelfId);
    myCsmConfigRegion = &(theShelf->GetSlotPtr(mySlotId)->GetCsmApp().GetCardConfigStatusRegion());
    myCsmStatusRegion = &(theShelf->GetSlotPtr(mySlotId)->GetCsmApp().GetCardStatusRegion());

    //reset all data
    ResetData();
}

////////////////////////////////////////////////////////////////////////////////
SP_OduKSnc::~SP_OduKSnc()
{
}

CT_SP_Protection SP_OduKSnc::GetCurrentSelection()
{
    
    SP_SelectorPositionRegion* theSelectorPosnRegion = &(myApplIf.GetSelectorPosnRegion());
    SP_SelectorPosition& aSelectorPosn = static_cast<SP_SelectorPosition&>((*theSelectorPosnRegion)[myPrivIndex]);

    if (aSelectorPosn.GetSelectorPosition() == CT_SP_PROTECTION_SIDE)
    {
        mySelector.SelectProtection();
        mySelector.Switch();
        return CT_SP_PROTECTION_SIDE;
    }

    
    mySelector.SelectWorking();
    mySelector.Switch();
    
    return CT_SP_WORKING_SIDE;

}

CT_SP_Protection SP_OduKSnc::GetInitialSelection()
{
    //This is for dual card operation
    //Determine initial selection based on the state of the remote card
    uint8 thePQWChannel = INVALID_PQW_CHANNEL;
    bool isWorkingRealPort = false;
    if (mySourcesLocal.working == true)
    {
        thePQWChannel = myPQWChannels.working;
        isWorkingRealPort = true;
    }
    else if (mySourcesLocal.protection == true)
    {
        thePQWChannel = myPQWChannels.protection;
        isWorkingRealPort = false;
    }

    if (thePQWChannel != INVALID_PQW_CHANNEL)
    {
        PII_Sleep::Sleep(30);//Wait 30ms to let ODU SNC has been configured into FirmWare and PQWRxMessage is ready.
        TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
        uint16 rxMsg = (*theSncRegion)[0].GetRxPQM(thePQWChannel);
        //DEBUG
        if (gSP_DebugTraceSnc == 1)
        {
            fc_cout << "Rx message is " << rxMsg << endl;
        }
        bool mateSourceEnable = ((*theSncRegion)[0].GetRxHwPQWSquelch(thePQWChannel) == false);

        if (GetMateModPresence((isWorkingRealPort == true ? CT_SP_WORKING_SIDE: CT_SP_PROTECTION_SIDE)) == true)
        {
            //DEBUG
            PII_Sleep::Sleep(10);
            rxMsg = (*theSncRegion)[0].GetRxPQM(thePQWChannel);
            //DEBUG
            if (gSP_DebugTraceSnc == 1)
            {
                fc_cout << "Rx message is " << rxMsg << endl;
            }
            mateSourceEnable = ((*theSncRegion)[0].GetRxHwPQWSquelch(thePQWChannel) == false);
            //DEBUG
            if (gSP_DebugTraceSnc == 1)
            {
                fc_cout << "Mate present" << endl;
            }
            if ( (rxMsg & SP_PQW_MSG_VALID) == SP_PQW_MSG_VALID)
            {
                //if HW PQW indicates that src is enabled, then check the software bit as well
                //since there are many cases where hw squelch is not used
                if (mateSourceEnable)
                {
                    if ( (rxMsg & SP_PQW_SRC_ENABLED) != SP_PQW_SRC_ENABLED)
                       mateSourceEnable = false;
                }
            }
            else
            {
                //DEBUG
                if (gSP_DebugTraceSnc == 1)
                {
                    fc_cout << "Returning invalid selection 2" << endl;
                }
                //Use default initial selection
                return  CT_SP_INVALID_PROTECTION_SIDE; /*remote PQW is not valid, so no initial selection*/
            }
        }
        else
        {
            //DEBUG
            if (gSP_DebugTraceSnc == 1)
            {
                fc_cout << "Mate absent" << endl;
            }
            mateSourceEnable = false;
        }

        if (mateSourceEnable)
        {
            if (isWorkingRealPort)
            {
                mySelector.SelectProtection();
                mySelector.Switch();
                //DEBUG
                if (gSP_DebugTraceSnc == 1)
                {
                    fc_cout << "Slot " << (uint32)CSPII_CardIF::GetInstance()->GetSlotId() << " Mate source is enabled..selecting mate (protection) side" << endl;
                }
                return CT_SP_PROTECTION_SIDE;
            }
            else
            {
                mySelector.SelectWorking();
                mySelector.Switch();
                //DEBUG
                if (gSP_DebugTraceSnc == 1)
                {
                    fc_cout << "Slot " << (uint32)CSPII_CardIF::GetInstance()->GetSlotId() << " Mate source is enabled..selecting mate (working) side" << endl;
                }
                return CT_SP_WORKING_SIDE;
            }
        }
        else
        {
            //DEBUG
            if (gSP_DebugTraceSnc == 1)
            {
                fc_cout << "Returning invalid selection 3" << endl;
            }
            //Use default initial selection
            return CT_SP_INVALID_PROTECTION_SIDE;
        }
    }
    else
    {
        //DEBUG
        if (gSP_DebugTraceSnc == 1)
        {
            fc_cout << "Returning invalid selection 4" << endl;
        }
        //Use default initial selection
        return CT_SP_INVALID_PROTECTION_SIDE;

    }
    
    
}

void SP_OduKSnc::Enable()
{
    int theIdx;
    bool theDC;
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    myPQWChannels.working = myPQWChannels.protection = INVALID_PQW_CHANNEL;
    mySourcesLocal.working = mySourcesLocal.protection = false;

    CT_SP_1plus1Type protectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();

    //Configure SNC priority tables
    SP_OduKSncPriorityTable::GetInstance().Configure();

    //Setup the logical mate shelf id (this is required before setting up PQW connections)
    ConfigureLogicalShelfId(true, myProtectionAction.Get1plus1Config().GetSources().working.GetShelfId(), myProtectionAction.Get1plus1Config().GetSources().protection.GetShelfId());

    //Set up PQW channel information.
    //Enable fpp
    //Enable auto squelch so that we can switch faster
    //Setup current connection pattern information
    //Setup PQW connections
    //Setup client and server layers
    //Set up source enable ownership
    if (myProtectionAction.Get1plus1Config().GetSources().working.GetShelfId() == myShelfId &&
        myProtectionAction.Get1plus1Config().GetSources().working.GetSlotId() == mySlotId)
    {
        myMatePortOf.working = myProtectionAction.Get1plus1Config().GetSources().protection;
        myPQWChannels.working = myProtectionAction.Get1plus1Config().GetSources().working.GetChannelId()-1; /*make it 0-based*/
        myPQWChannels.protection = myProtectionAction.Get1plus1Config().GetSources().protection.GetChannelId()-1;/*make it 0-based*/
        theSncIf.SetFppEnabled(myPQWChannels.working, true);
        theSncIf.SetSquelchHoldOffDelay(myPQWChannels.working, myProtectionAction.Get1plus1Config().GetHoldOffTimer());
        theSncIf.SetFppSquelchEnabled(myPQWChannels.working, true);
        EvaluateConnectionPattern(CT_SP_WORKING_SIDE, (uint32)myProtectionAction.Get1plus1Config().GetSources().working.GetPortId(), true, &theIdx, &theDC);
        FindClientAndServerLayers(CT_SP_WORKING_SIDE, (uint32)myProtectionAction.Get1plus1Config().GetSources().working.GetPortId(), true);
        //Optionally setup TCM info
        if (protectionType == CT_SP_SNCS)
        {
            FindTcmLayers(CT_SP_WORKING_SIDE, (uint32)myProtectionAction.Get1plus1Config().GetSources().working.GetPortId(), true);
        }
        SetupPQWConnection(CT_SP_WORKING_SIDE, true, true);
        mySourcesLocal.working = true;

        //Add any additional input regions
        if (protectionType == CT_SP_SNCS)
        {
            ManageTcmInputRegions(CT_SP_WORKING_SIDE, true, false, false);
        }
        else
        {
            ManageInputRegions(CT_SP_WORKING_SIDE, true, false, false);
        }
    }

    if (myProtectionAction.Get1plus1Config().GetSources().protection.GetShelfId() == myShelfId &&
        myProtectionAction.Get1plus1Config().GetSources().protection.GetSlotId() == mySlotId)
    {
        myMatePortOf.protection = myProtectionAction.Get1plus1Config().GetSources().working;
        myPQWChannels.working = myProtectionAction.Get1plus1Config().GetSources().working.GetChannelId()-1;/*make it 0-based*/
        myPQWChannels.protection = myProtectionAction.Get1plus1Config().GetSources().protection.GetChannelId()-1;/*make it 0-based*/
        theSncIf.SetFppEnabled(myPQWChannels.protection, true);
        theSncIf.SetSquelchHoldOffDelay(myPQWChannels.protection, myProtectionAction.Get1plus1Config().GetHoldOffTimer());
        theSncIf.SetFppSquelchEnabled(myPQWChannels.protection, true);
        EvaluateConnectionPattern(CT_SP_PROTECTION_SIDE, (uint32)myProtectionAction.Get1plus1Config().GetSources().protection.GetPortId(), true, &theIdx, &theDC);
        FindClientAndServerLayers(CT_SP_PROTECTION_SIDE, (uint32)myProtectionAction.Get1plus1Config().GetSources().protection.GetPortId(), true);
        //Optionally setup TCM info
        if (protectionType == CT_SP_SNCS)
        {
            FindTcmLayers(CT_SP_PROTECTION_SIDE, (uint32)myProtectionAction.Get1plus1Config().GetSources().protection.GetPortId(), true);
        }
        SetupPQWConnection(CT_SP_PROTECTION_SIDE, true, true);
        mySourcesLocal.protection = true;

        //Add any additional input regions
        if (protectionType == CT_SP_SNCS)
        {
            ManageTcmInputRegions(CT_SP_PROTECTION_SIDE, true, false, false);
        }
        else
        {
            ManageInputRegions(CT_SP_PROTECTION_SIDE, true, false, false);
        }
    }
 
    //Setup switching priority tables
    AssignPriorityTable();
    
    if (mySourcesLocal.working == true)
    {
        //Enable interrupts last
        theSncIf.EnableRxSwPqwInterrupt(myPQWChannels.working, true);
        theSncIf.EnableRxHwPqwInterrupt(myPQWChannels.working, true);
        theSncIf.EnableTxHwPqwInterrupt(myPQWChannels.working, true);

        //Configure the message polling action
        SP_OduKSncPQWPollingAction::GetInstance()->SetConfiguration(true, myPQWChannels.working, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.working.GetSlotId()-1 /* 0-based*/);
        //Enable remote module timeout interrupt
        SP_OduKSncPQWTimeoutIntrCtrl::GetInstance().SetConfiguration(true, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.working.GetSlotId()-1 /* 0-based*/);
    }

    if (mySourcesLocal.protection == true)
    {
        //Enable interrupts last
        theSncIf.EnableRxSwPqwInterrupt(myPQWChannels.protection, true);
        theSncIf.EnableRxHwPqwInterrupt(myPQWChannels.protection, true);
        theSncIf.EnableTxHwPqwInterrupt(myPQWChannels.protection, true);

        //Configure the message polling action
        SP_OduKSncPQWPollingAction::GetInstance()->SetConfiguration(true, myPQWChannels.protection, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.protection.GetSlotId()-1 /* 0-based*/);
        //Enable remote module timeout interrupt
        SP_OduKSncPQWTimeoutIntrCtrl::GetInstance().SetConfiguration(true, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.protection.GetSlotId()-1 /* 0-based*/);
    }

    myIsConfigured = true;
        
}

void SP_OduKSnc::Disable(CT_SP_Protection theSide)
{

    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
    CT_SP_1plus1Type protectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();

    if (theSide == CT_SP_WORKING_SIDE)
    {
        if (mySourcesLocal.working == true)
        {
            theSncIf.SetTxPQM(myPQWChannels.working, 0, SP_PQW_ALL_MASK);
            //Disable interrupts
            theSncIf.EnableRxSwPqwInterrupt(myPQWChannels.working, false);
            theSncIf.EnableRxHwPqwInterrupt(myPQWChannels.working, false);
            theSncIf.EnableTxHwPqwInterrupt(myPQWChannels.working, false);

            DisableLite(CT_SP_WORKING_SIDE);

            if (protectionType == CT_SP_SNCS)
            {
                //Remove any input regions
                ManageTcmInputRegions(CT_SP_WORKING_SIDE, false, true, false);
            }
            else
            {
                //Remove any input regions
                ManageInputRegions(CT_SP_WORKING_SIDE, false, true, false);
            }
        }

        //tear down pqw connections
        if (mySourcesLocal.working == true)
        {
            SetupPQWConnection(CT_SP_WORKING_SIDE, false, true);
        }
    }

    if (theSide == CT_SP_PROTECTION_SIDE)
    {
        if (mySourcesLocal.protection == true)
        {
            theSncIf.SetTxPQM(myPQWChannels.protection, 0, SP_PQW_ALL_MASK);
            //Disable interrupts
            theSncIf.EnableRxSwPqwInterrupt(myPQWChannels.protection, false);
            theSncIf.EnableRxHwPqwInterrupt(myPQWChannels.protection, false);
            theSncIf.EnableTxHwPqwInterrupt(myPQWChannels.protection, false);

            DisableLite(CT_SP_PROTECTION_SIDE);

            if (protectionType == CT_SP_SNCS)
            {
                //Remove any input regions
                ManageTcmInputRegions(CT_SP_PROTECTION_SIDE, false, true, false);
            }
            else
            {
                //Remove any input regions
                ManageInputRegions(CT_SP_PROTECTION_SIDE, false, true, false);
            }
        }

        //tear down pqw connections
        if (mySourcesLocal.protection == true)
        {
            SetupPQWConnection(CT_SP_PROTECTION_SIDE, false, true);
        }
    }
}

//Disable function on a diet
//Only disables certain portions of the protection scheme.

void  SP_OduKSnc::DisableLite(CT_SP_Protection theSide)
{
    if (theSide == CT_SP_WORKING_SIDE)
    {
        if (mySourcesLocal.working == true)
        {
            //Configure the message polling action
            SP_OduKSncPQWPollingAction::GetInstance()->SetConfiguration(false, myPQWChannels.working, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.working.GetSlotId()-1 /* 0-based*/);
            //Enable remote module timeout interrupt
            SP_OduKSncPQWTimeoutIntrCtrl::GetInstance().SetConfiguration(false, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.working.GetSlotId()-1 /* 0-based*/);
        }
    }

    if (theSide == CT_SP_PROTECTION_SIDE)
    {
        if (mySourcesLocal.protection == true)
        {
            //Configure the message polling action
            SP_OduKSncPQWPollingAction::GetInstance()->SetConfiguration(false, myPQWChannels.protection, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.protection.GetSlotId()-1 /* 0-based*/);
            //Enable remote module timeout interrupt
            SP_OduKSncPQWTimeoutIntrCtrl::GetInstance().SetConfiguration(false, myMateLogicalShelf-1 /*0-based*/, myMatePortOf.protection.GetSlotId()-1 /* 0-based*/);
        }
    }
}

void SP_OduKSnc::AssignPriorityTable()
{
    //Setup priority table in hardware for working/and or protect oduk
    CT_SP_1plus1Type protectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    if (protectionType == CT_SP_SNCN)
    {
        if (mySourcesLocal.working == true)
        {
            theSncIf.SetTohPriorityAssignment(myPQWChannels.working, TSPII_SNCIF_PRIOR_TBL_0);
        }

        if (mySourcesLocal.protection == true)
        {
            theSncIf.SetTohPriorityAssignment(myPQWChannels.protection, TSPII_SNCIF_PRIOR_TBL_0);
        }
    }
    else if (protectionType == CT_SP_SNCI)
    {
        if (mySourcesLocal.working == true)
        {
            theSncIf.SetTohPriorityAssignment(myPQWChannels.working, TSPII_SNCIF_PRIOR_TBL_1);
        }

        if (mySourcesLocal.protection == true)
        {
            theSncIf.SetTohPriorityAssignment(myPQWChannels.protection, TSPII_SNCIF_PRIOR_TBL_1);
        }
    }
    else if (protectionType == CT_SP_SNCS)
    {
        if (mySourcesLocal.working == true)
        {
            theSncIf.SetTohPriorityAssignment(myPQWChannels.working, TSPII_SNCIF_PRIOR_TBL_2);
        }

        if (mySourcesLocal.protection == true)
        {
            theSncIf.SetTohPriorityAssignment(myPQWChannels.protection, TSPII_SNCIF_PRIOR_TBL_2);
        }
    }
}

void SP_OduKSnc::SetupPQWConnection(CT_SP_Protection theSide, bool configure, bool writeToHw)
{
    //Add destination PQW connection
    CT_SP_1plus1Type protectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    uint8 remotePQWChannel;
    uint8 localPQWChannel;
    uint32 aClientOduIdentifier;
    uint32 aServerOduIdentifier;
    uint8 theMateSlot;
    uint8 oduStreamId;
    uint32 aTcmIdentifier=0;

    if (theSide == CT_SP_WORKING_SIDE)
    {
        theMateSlot = myProtectionAction.Get1plus1Config().GetSources().protection.GetSlotId()-1;/*0 - based*/
        remotePQWChannel = myPQWChannels.protection;
        localPQWChannel = myPQWChannels.working;
        oduStreamId = (uint8)myXcIndex.working;
        aClientOduIdentifier = (uint32)myProtectionAction.Get1plus1Config().GetSources().working.GetPortId();
        aServerOduIdentifier = myServerLayerOduId.working.GetIdValue(); 
        if (protectionType == CT_SP_SNCS)
        {
            aTcmIdentifier = myTcmId.working.GetTcmLevel();
        }
    }
    else
    {
        theMateSlot = myProtectionAction.Get1plus1Config().GetSources().working.GetSlotId()-1;/*0 - based*/
        remotePQWChannel = myPQWChannels.working;
        localPQWChannel = myPQWChannels.protection;
        oduStreamId = (uint8)myXcIndex.protection;
        aClientOduIdentifier = (uint32)myProtectionAction.Get1plus1Config().GetSources().protection.GetPortId();
        aServerOduIdentifier = myServerLayerOduId.protection.GetIdValue();
        if (protectionType == CT_SP_SNCS)
        {
            aTcmIdentifier = myTcmId.protection.GetTcmLevel();
        }
    }
    
    
    if (configure)
    {
        //Add Odu stream pqw connection
        theSncIf.SetOduStreamPqwIndex(oduStreamId, localPQWChannel);

        //Add egress connection
        theSncIf.AddTohPqwEgressXconn(myMateLogicalShelf-1, 
                                      theMateSlot,
                                      remotePQWChannel, 
                                      localPQWChannel);

        //Setup ingress PQW connections
        theSncIf.AddTohPqwIngressXconn(localPQWChannel,
                                       aClientOduIdentifier,
                                       aServerOduIdentifier,
                                       aTcmIdentifier);

               
    }
    else
    {
        if (writeToHw)
        {
            //Delete Odu stream pqw connection
            theSncIf.SetOduStreamPqwIndex(oduStreamId, TSPII_SNCIF_INVALID_PQW_CHANNEL);
        }

        if (writeToHw)
        {
            //Delete egress PQW connections
            theSncIf.DeleteTohPqwEgressXconn(localPQWChannel);
        }

        if (writeToHw)
        {
            //Delete ingress PQW connections
            theSncIf.DeleteTohPqwIngressXconn(localPQWChannel);
        }
            
    }

    //theSncIf.CommitTohPqwEgressXconns();
    //theSncIf.CommitTohPqwIngressXconns();

}

bool SP_OduKSnc::GetSFDefects(CT_SP_Protection theSide, uint32* theCount, bool* theState)
{
    //Check for signal fail conditions
    uint32 aCount=0;
    bool aState=false;
    MON_Defects* aMonitoringObject = NULL;
    MON_Region* theDefectRegion = NULL;
    MON_Region* theConfigRegion = NULL;
    MON_OduConfig* aMonOduConfigObject = NULL;
    MON_OtuConfig* aMonOtuConfigObject = NULL;
    MON_OptConfig* aMonOptConfigObject = NULL;
    MON_TcmConfig* aMonTcmConfigObject = NULL;
    TSPII_DwRegion*            DwRegion = NULL;
    TSPII_FecRegion*           FecRegion = NULL;
    uint32 PII_count(0);

    CT_SP_1plus1Type protectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();
    
    CSM_PersistentConfigStatus* aPersConfigPtr = &((*myCsmConfigRegion)[0]);
    CT_AdministrativeConfigType theCardAdminState = aPersConfigPtr->GetAdministrativeConfig();

    CSM_CardStatus* aCardStatusPtr = &((*myCsmStatusRegion)[0]);
    CT_Status aCardStatus = aCardStatusPtr->GetCardStatus();

    uint8 thePQWChannel = 0;
    bool isLocal = false;
    SP_SncServerLayer serverLayer = Server_Layer_None;
    SP_SncServerLayer TwoStageTopserverLayer = Server_Layer_None;
    int serverIdx = -1;
    int TwoStageTopserverIdx = -1;
    int clientIdx = -1;
    CT_IntfId serverPort = CT_INTF_ID_UNKNOWN;
    CT_IntfId TwoStageTopserverPort = CT_INTF_ID_UNKNOWN;
    CT_IntfId clientPort = CT_INTF_ID_UNKNOWN;
    unsigned int serverTspiiPort =0;
    unsigned int TwoStageTopserverTspiiPort =0;
    int serverTspiiIdx = -1;
    int TwoStageTopserverTspiiIdx = -1;
    unsigned int clientTspiiPort =0;
    int clientTspiiIdx = -1;
    CT_IntfId otuKPort = CT_INTF_ID_UNKNOWN;
    int otuKIdx = -1;
    int tcmIdx = -1;

    if (theSide == CT_SP_WORKING_SIDE)
    {
        if (mySourcesLocal.working == true)
        {
            isLocal = true;
            serverLayer = myServerLayerType.working;
            TwoStageTopserverLayer = myTwoStageTopServerLayerType.working;
            serverPort = myServerLayerPort.working;
            TwoStageTopserverPort = myTwoStageTopServerLayerPort.working;
            serverIdx = myServerLayerIdx.working;
            TwoStageTopserverIdx = myTwoStageTopServerLayerIdx.working;
            clientPort = myLayerPort.working;
            clientIdx = myLayerIdx.working;
            serverTspiiPort = myServerTspiiPort.working;
            TwoStageTopserverTspiiPort = myTwoStageTopServerTspiiPort.working;
            serverTspiiIdx = myServerTspiiIdx.working;
            TwoStageTopserverTspiiIdx = myTwoStageTopServerTspiiIdx.working;
            clientTspiiPort= myTspiiOduPort.working;
            clientTspiiIdx = myTspiiOduIdx.working;
            otuKPort       = myOtuKPort.working;
            otuKIdx        = myOtuKIdx.working;
            thePQWChannel  = myPQWChannels.working;
            tcmIdx         = myTcmIdx.working;

        }
        else
        {
            //PQW channel is always referenced using the local source
            thePQWChannel = myPQWChannels.protection;
        }
    }

    else if (theSide == CT_SP_PROTECTION_SIDE)
    {
        if (mySourcesLocal.protection == true)
        {
            isLocal = true;
            serverLayer = myServerLayerType.protection;
            TwoStageTopserverLayer = myTwoStageTopServerLayerType.protection;
            serverPort = myServerLayerPort.protection;
            TwoStageTopserverPort = myTwoStageTopServerLayerPort.protection;
            serverIdx = myServerLayerIdx.protection;
            TwoStageTopserverIdx = myTwoStageTopServerLayerIdx.protection;
            clientPort = myLayerPort.protection;
            clientIdx = myLayerIdx.protection;
            serverTspiiPort = myServerTspiiPort.protection;
            TwoStageTopserverTspiiPort = myTwoStageTopServerTspiiPort.protection;
            serverTspiiIdx = myServerTspiiIdx.protection;
            TwoStageTopserverTspiiIdx = myTwoStageTopServerTspiiIdx.protection;
            clientTspiiPort= myTspiiOduPort.protection;
            clientTspiiIdx = myTspiiOduIdx.protection;
            otuKPort       = myOtuKPort.protection;
            otuKIdx        = myOtuKIdx.protection;
            thePQWChannel = myPQWChannels.protection;
            tcmIdx         = myTcmIdx.protection;
        }
        else
        {
            //PQW channel is always referenced using the local source
            thePQWChannel = myPQWChannels.working;
        }
    }

    if (isLocal)
    {
        if (GetTxSFHigh(thePQWChannel) == true)
        {
            //if this exists, then no need to check anything else
            (*theState) |= true;
            (*theCount) += 1;
        }
        else
        {
            //Check for other conditions
            //Card Lock
            if (theCardAdminState == CARD_LOCK)
            {
                (*theState) |= true;
                (*theCount) += 1;
            }

            //Card Fail
            if (aCardStatus == CT_FAILED)
            {
                (*theState) |= true;
                (*theCount) += 1;
            }

            if (protectionType == CT_SP_SNCN ||
                protectionType == CT_SP_SNCI)
            {
                //Check server SF and client SF
                //The following defects are checked
                //Server OTUk:
                  //---> Forced Layer Lock at OPT layer
                  //---> Forced Layer Fail at OPT layer
                  //---> TIM-OTU with AIS insert
                if (serverLayer == Server_Layer_OTUk)
                {
                    theConfigRegion = myApplIf.GetCardContext().GetOptIf().GetMonPortSideApp(serverPort).GetConfigRegion();
                    aMonOptConfigObject = static_cast<MON_OptConfig*>(&((*theConfigRegion)[serverIdx]));
                    if (aMonOptConfigObject->GetLayerLocked() == true)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                    if (aMonOptConfigObject->GetUpperLayerFailed() == true)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }

                    theDefectRegion = myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(serverPort).GetDefectsRegion();
                    theConfigRegion = myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(serverPort).GetConfigRegion();
                    aMonOtuConfigObject = static_cast<MON_OtuConfig*>(&((*theConfigRegion)[serverIdx]));
                    aMonitoringObject = static_cast<MON_Defects*>(&((*theDefectRegion)[serverIdx]));
                    if (aMonOtuConfigObject->GetLayerFailOnTIM())
                    {
                        aMonitoringObject->GetDefectStatus(CT_TEL_OTU_TIM_DEFECT, &aCount, &aState);
                        (*theState) |= aState;
                        (*theCount) += aCount;
                        aCount=0,aState=false;

                        FecRegion = TSPII_SubApplication::GetInstance()->GetFec(serverTspiiPort);
                        if(FecRegion)
                        {
                            PII_count = (*FecRegion)[serverTspiiIdx].GetTIM();
                            if(PII_count%2 != 0)
                            {
                                (*theState) |= true;
                                (*theCount) += 1;
                            }
                        }
                    }
                }
                else if (serverLayer == Server_Layer_ODUk)
                {
                  //Server ODUk
                    //---> Forced Layer Lock at OTUk port OPT layer
                    //---> Force layer Fail at OTUk port OPT layer
                    //---> PLM at ODUk
                    //---> TIM-ODU with AIS insert.
                    //---> UPPER LAYER FAIL TA (server layer oduk or tcm TA failure)
                    //---> UPPER_LAYER_PROP_NEXT_LAYER_TA (for LTC)

                    //@TO DO: Uncomment later
                    
                    MON_Region *theOtuConfigRegion = myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(otuKPort).GetConfigRegion();
                    aMonOtuConfigObject = static_cast<MON_OtuConfig*>(&((*theOtuConfigRegion)[otuKIdx]));
                    if (aMonOtuConfigObject->GetLayerFailOnTIM())
                    {
                        FecRegion = TSPII_SubApplication::GetInstance()->GetFec(GetTspiiPort(otuKPort));
                        if(FecRegion)
                        {
                            PII_count = (*FecRegion)[otuKIdx].GetTIM();
                            if(PII_count%2 != 0)
                            {
                                (*theState) |= true;
                                (*theCount) += 1;
                            }
                        }
                    }
                    /*aMonOptConfigObject = static_cast<MON_OptConfig*>(&((*theConfigRegion)[otuKIdx]));
                    if (aMonOptConfigObject->GetLayerLocked() == true)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                    if (aMonOptConfigObject->GetUpperLayerFailed() == true)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                    */

                    theConfigRegion = myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(serverPort).GetConfigRegion();
                    theDefectRegion = myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(serverPort).GetDefectsRegion();
                    aMonOduConfigObject = static_cast<MON_OduConfig*>(&((*theConfigRegion)[serverIdx]));
                    aMonitoringObject = static_cast<MON_Defects*>(&((*theDefectRegion)[serverIdx]));
                    if (aMonOduConfigObject->GetLayerLocked() == true)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                    if (aMonOduConfigObject->GetLayerFailOnTIM())
                    {
                        aMonitoringObject->GetDefectStatus(CT_TEL_ODU_TIM_DEFECT, &aCount, &aState);
                        (*theState) |= aState;
                        (*theCount) += aCount;
                        aCount=0,aState=false;

                        DwRegion = TSPII_SubApplication::GetInstance()->GetDw(serverTspiiPort);
                        if(DwRegion)
                        {
                            PII_count = (*DwRegion)[serverTspiiIdx].GetTIM();
                            if(PII_count%2 != 0)
                            {
                                (*theState) |= true;
                                (*theCount) += 1;
                            }
                        }
                    }

                    aMonitoringObject->GetDefectStatus(CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT, &aCount, &aState);
                    (*theState) |= aState;
                    (*theCount) += aCount;
                    aCount=0,aState=false;

                    aMonitoringObject->GetDefectStatus(CT_TEL_ODU_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, &aCount, &aState);
                    (*theState) |= aState;
                    (*theCount) += aCount;
                    aCount=0,aState=false;

                    aMonitoringObject->GetDefectStatus(CT_TEL_ODU_LOCK, &aCount, &aState);
                    (*theState) |= aState;
                    (*theCount) += aCount;
                    aCount=0,aState=false;

                    DwRegion = TSPII_SubApplication::GetInstance()->GetDw(serverTspiiPort);
                    if(DwRegion)
                    {
                        PII_count = (*DwRegion)[serverTspiiIdx].GetPLM();
                        if(PII_count%2 != 0)
                        {
                            (*theState) |= true;
                            (*theCount) += 1;
                        }
                    }

                    if (TwoStageTopserverLayer == Server_Layer_ODUk)//two stage odu
                    {
                        theConfigRegion = myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(TwoStageTopserverPort).GetConfigRegion();
                        theDefectRegion = myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(TwoStageTopserverPort).GetDefectsRegion();
                        aMonOduConfigObject = static_cast<MON_OduConfig*>(&((*theConfigRegion)[TwoStageTopserverIdx]));
                        aMonitoringObject = static_cast<MON_Defects*>(&((*theDefectRegion)[TwoStageTopserverIdx]));
                        if (aMonOduConfigObject->GetLayerFailOnTIM())
                        {
                            aMonitoringObject->GetDefectStatus(CT_TEL_ODU_TIM_DEFECT, &aCount, &aState);
                            (*theState) |= aState;
                            (*theCount) += aCount;
                            aCount=0,aState=false;

                            DwRegion = TSPII_SubApplication::GetInstance()->GetDw(TwoStageTopserverTspiiPort);
                            if(DwRegion)
                            {
                                PII_count = (*DwRegion)[TwoStageTopserverTspiiIdx].GetTIM();
                                if(PII_count%2 != 0)
                                {
                                    (*theState) |= true;
                                    (*theCount) += 1;
                                }
                            }
                        }
                    }
                }

                if (protectionType == CT_SP_SNCN)
                {
                    //Client ODUk
                        //---> PLM at ODUk
                        //---> TIM-ODU with AIS insert.
                        //---> UPPER LAYER FAIL TA (server layer oduk or tcm TA failure)
                        //---> UPPER_LAYER_PROP_NEXT_LAYER_TA (for LTC)
                    theConfigRegion = myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(clientPort).GetConfigRegion();
                    theDefectRegion = myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(clientPort).GetDefectsRegion();
                    aMonOduConfigObject = static_cast<MON_OduConfig*>(&((*theConfigRegion)[clientIdx]));
                    aMonitoringObject = static_cast<MON_Defects*>(&((*theDefectRegion)[clientIdx]));

                    if (aMonOduConfigObject->GetLayerLocked() == true)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }

                    if (aMonOduConfigObject->GetLayerFailOnTIM())
                    {
                        aMonitoringObject->GetDefectStatus(CT_TEL_ODU_TIM_DEFECT, &aCount, &aState);
                        (*theState) |= aState;
                        (*theCount) += aCount;
                        aCount=0,aState=false;
                        DwRegion = TSPII_SubApplication::GetInstance()->GetDw(clientTspiiPort);
                        if(DwRegion)
                        {
                            PII_count = (*DwRegion)[serverTspiiIdx].GetTIM();
                            if(PII_count%2 != 0)
                            {
                                (*theState) |= true;
                                (*theCount) += 1;
                            }
                        }
                    }

                    aMonitoringObject->GetDefectStatus(CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT, &aCount, &aState);
                    (*theState) |= aState;
                    (*theCount) += aCount;
                    aCount=0,aState=false;

                    aMonitoringObject->GetDefectStatus(CT_TEL_ODU_UPPER_LAYER_PROP_NEXT_LAYER_TA_DEFECT, &aCount, &aState);
                    (*theState) |= aState;
                    (*theCount) += aCount;
                    aCount=0,aState=false;

                    DwRegion = TSPII_SubApplication::GetInstance()->GetDw(clientTspiiPort);
                    PII_count = (*DwRegion)[clientTspiiIdx].GetPLM();
                    if(PII_count%2 != 0)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                }
                
                /* Taking an ODU out of service is defined in G.798 as being part of the adaptation layer between the ODU and the supporting OTU/ODU.
                   According to the ITU standards, SNC/I switch criteria is supposed to include defects at the adaptation layer.
                   As a result when an ODU that is a memeber of an SNC/I protection group is taken OOS, an SNC protection switch should take place. */
                if (protectionType == CT_SP_SNCI)
                {
                    theConfigRegion = myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(clientPort).GetConfigRegion();
                    aMonOduConfigObject = static_cast<MON_OduConfig*>(&((*theConfigRegion)[clientIdx]));
                    if (aMonOduConfigObject->GetLayerLocked() == true)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                }
            }
            else if (protectionType == CT_SP_SNCS)
            {
                //TCM adjecent to ODUk
                //--->IsLayerInDefects() ?checks myUpperLayerFailTAState and myLayerFailOnTimEnable with myTIMState
                //--->IsInPropagateNextLayerDefectsTA() ?checks myAISState and myUpperLayerFailPNLTAState 
                //--->GetLockBitMask() ?will be 0 no server layers (including OTU) are locked.

                theConfigRegion = myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetConfigRegion();
                theDefectRegion = myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetDefectsRegion();
                aMonTcmConfigObject = static_cast<MON_TcmConfig*>(&((*theConfigRegion)[tcmIdx]));
                aMonitoringObject = static_cast<MON_Defects*>(&((*theDefectRegion)[tcmIdx]));

                if (aMonTcmConfigObject->GetLayerLocked() == true)
                {
                    (*theState) |= true;
                    (*theCount) += 1;
                }

                if (aMonTcmConfigObject->GetLayerFailOnTIM())
                {
                    aCount=0,aState=false;
                    aMonitoringObject->GetDefectStatus(CT_TEL_TCM_TIM_DEFECT, &aCount, &aState);
                    (*theState) |= aState;
                    (*theCount) += aCount;
                }

                /* OOS-MA on the supporting SINK ODUkT-A will cause CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT on its supported ODUkT-A. 
                   OOS-MA on the supporting ODUk will also cause CT_TEL_ODU_UPPER_LAYER_FAIL_TA_DEFECT on its supported ODUkT-A.
                   But OOS-MA on the OTU will NOT cause its immediate supported ODUkT-A CT_TEL_TCM_UPPER_LAYER_FAIL_TA_DEFECT.
                   So no special case for the OOS-MA on the ODUkT and ODUk. Special case only needed for the OTU. */
                if (aMonitoringObject->IsLayerInDefects() ||
                    aMonitoringObject->IsInPropagateNextLayerDefectsTA() ||
                    aMonitoringObject->IsOtuLayerLocked(aMonitoringObject->GetLockBitMask()))
                {
                    (*theState) |= true;
                    (*theCount) += 1;
                }
            }
        }
    }
    else
    {
        //Give the opposite side (local port) as reference point for detecting module presence
        if (GetRxSFHigh((theSide == CT_SP_WORKING_SIDE ? CT_SP_PROTECTION_SIDE : CT_SP_WORKING_SIDE), thePQWChannel) == true)
        {
            (*theState) |= true;
            (*theCount) += 1;
        }
    }


    return false;
    
}


bool SP_OduKSnc::GetSDDefects(CT_SP_Protection theSide, uint32* theCount, bool* theState)
{
    //Check for signal degrade conditions
    TSPII_DwRegion*            DwRegion = NULL;
    TSPII_FecRegion*           FecRegion = NULL;
    TSPII_TcmRegion*           TcmRegion = NULL;
    uint32 PII_count(0);
    CT_SP_1plus1Type protectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();

    uint8 thePQWChannel = 0;
    bool isLocal = false;
    SP_SncServerLayer serverLayer = Server_Layer_None;
    int serverIdx = -1;
    int clientIdx = -1;
    CT_IntfId serverPort = CT_INTF_ID_UNKNOWN;
    CT_IntfId clientPort = CT_INTF_ID_UNKNOWN;
    unsigned int serverTspiiPort =0;
    int serverTspiiIdx = -1;
    unsigned int clientTspiiPort =0;
    int clientTspiiIdx = -1;
    uint16 tcmTspiiIdx = CT_DEFAULT_ODU_POSITION;


    if (theSide == CT_SP_WORKING_SIDE)
    {
        if (mySourcesLocal.working == true)
        {
            isLocal = true;
            serverLayer = myServerLayerType.working;
            serverPort = myServerLayerPort.working;
            serverIdx = myServerLayerIdx.working;
            clientPort = myLayerPort.working;
            clientIdx = myLayerIdx.working;
            serverTspiiPort = myServerTspiiPort.working;
            serverTspiiIdx = myServerTspiiIdx.working;
            clientTspiiPort= myTspiiOduPort.working;
            clientTspiiIdx = myTspiiOduIdx.working;
            thePQWChannel = myPQWChannels.working;
            tcmTspiiIdx = myTspiiTcmIdx.working;
        }
        else
        {
            //PQW channel is always referenced using the local source
            thePQWChannel = myPQWChannels.protection;
        }
    }

    else if (theSide == CT_SP_PROTECTION_SIDE)
    {
        if (mySourcesLocal.protection == true)
        {
            isLocal = true;
            serverLayer = myServerLayerType.protection;
            serverPort = myServerLayerPort.protection;
            serverIdx = myServerLayerIdx.protection;
            clientPort = myLayerPort.protection;
            clientIdx = myLayerIdx.protection;
            serverTspiiPort = myServerTspiiPort.protection;
            serverTspiiIdx = myServerTspiiIdx.protection;
            clientTspiiPort= myTspiiOduPort.protection;
            clientTspiiIdx = myTspiiOduIdx.protection;
            thePQWChannel = myPQWChannels.protection;
            tcmTspiiIdx = myTspiiTcmIdx.protection;
        }
        else
        {
            //PQW channel is always referenced using the local source
            thePQWChannel = myPQWChannels.working;
        }
    }


    if (isLocal)
    {
        if (GetTxSD(thePQWChannel) == true)
        {
            //if this exists, then no need to check anything else
            (*theState) |= true;
            (*theCount) += 1;
        }
        else
        {

            if (protectionType == CT_SP_SNCN)
            {
                //Check client SSD
                DwRegion = TSPII_SubApplication::GetInstance()->GetDw(clientTspiiPort);
                PII_count = (*DwRegion)[clientTspiiIdx].GetBerSd();
                if(PII_count%2 != 0)
                {
                    (*theState) |= true;
                    (*theCount) += 1;
                }
            }
            else if (protectionType == CT_SP_SNCI)
            {
                //check server SSD
                if (serverLayer == Server_Layer_OTUk)
                {
                    //OTU-SDBER
                    //ODU-SDBER
                    FecRegion = TSPII_SubApplication::GetInstance()->GetFec(serverTspiiPort);
                    PII_count = (*FecRegion)[serverTspiiIdx].GetBerSd();
                    if(PII_count%2 != 0)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                }
                else if (serverLayer == Server_Layer_ODUk)
                {
                    //ODU-SDBER
                    DwRegion = TSPII_SubApplication::GetInstance()->GetDw(serverTspiiPort);
                    PII_count = (*DwRegion)[serverTspiiIdx].GetBerSd();
                    if(PII_count%2 != 0)
                    {
                        (*theState) |= true;
                        (*theCount) += 1;
                    }
                }
            }
            else if (protectionType == CT_SP_SNCS)
            {
                //ODU-SDBER
                TcmRegion = TSPII_SubApplication::GetInstance()->GetTcm();
                PII_count = (*TcmRegion)[tcmTspiiIdx].GetBerSd();
                if(PII_count%2 != 0)
                {
                    (*theState) |= true;
                    (*theCount) += 1;
                }
            }
        }
    }
    else
    {
        if (GetRxSD(thePQWChannel) == true)
        {
            (*theState) |= true;
            (*theCount) += 1;
        }
    }

    return false;
}


bool SP_OduKSnc::GetRxSFHigh(CT_SP_Protection theSide, uint8 thePQWChannel)
{
    bool theState = false;
    //Get the rx PQW (HW+SW) and determine state
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
  
    //Get HW SF HIGH indication    
    uint32 PII_count = theSncIf.GetRxSFHigh(thePQWChannel);
    if(PII_count%2 != 0)
    {
        theState = true;
        return theState;
    }   

    //If remote module is not present, then return SF (used only in switched mode)
    if (GetMateModPresence(theSide) == false)
    {
        theState = true;
        return theState;
    }

    uint16 rxMsg = theSncIf.GetRxPQM(thePQWChannel);
    rxMsg = (rxMsg & SP_PQW_AUTO_CMD);
    rxMsg = rxMsg >> SP_PQW_AUTO_CMD_SHIFT;
                
    //DEBUG                    
    //fc_cout << "SF Rx Msg: " << (uint32) rxMsg <<endl;
    //END DEBUG
    //if rx msg quality word section has SF indicated, then consider it an SF on mate module
    if ( rxMsg == CT_SP_AUTO_SF )
    {
        theState = true;
    }
    return theState;
}
bool SP_OduKSnc::GetRxSFLow(uint8 thePQWChannel)
{ 
    bool theState = false;
    return theState;
}
bool SP_OduKSnc::GetRxSD(uint8 thePQWChannel)
{
    bool theState = false;
    //Get the rx PQW (HW+SW) and determine state
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    //Get HW SD indication (only valid in switched mode)
    uint32 PII_count = theSncIf.GetRxSD(thePQWChannel);
    if(PII_count%2 != 0)
    {
        theState = true;
        return theState;
    }
    
    uint16 rxMsg = theSncIf.GetRxPQM(thePQWChannel);
    rxMsg = (rxMsg & SP_PQW_AUTO_CMD);
    rxMsg = rxMsg >> SP_PQW_AUTO_CMD_SHIFT;
                
    //DEBUG                    
    //fc_cout << "SF Rx Msg: " << (uint32) rxMsg <<endl;
    //END DEBUG
    //if rx msg quality word section has SD indicated, then consider it an SD on mate module
    if ( rxMsg == CT_SP_AUTO_SD )
    {
        theState = true;
    }
    return theState;
}

bool SP_OduKSnc::GetTxSFHigh(uint8 thePQWChannel)
{
    bool theState = false;
    //Get the tx PQW (HW) and determine state
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
 
    //Get HW SF HIGH indication   
    uint32 PII_count = theSncIf.GetTxSFHigh(thePQWChannel);
    if(PII_count%2 != 0)
    {
        theState = true;
    }
   
    return theState;
}
bool SP_OduKSnc::GetTxSFLow(uint8 thePQWChannel)
{ 
    bool theState = false;
    return theState;
}
bool SP_OduKSnc::GetTxSD(uint8 thePQWChannel)
{
    bool theState = false;
    //Get the tx PQW (HW) and determine state
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    //Get HW SD indication
    uint32 PII_count = theSncIf.GetTxSD(thePQWChannel);
    if(PII_count%2 != 0)
    {
        theState = true;
    }
   
    return theState;
}

////This function expects the real port to be passed in
bool SP_OduKSnc::IsConfigurationMismatch(CT_SP_Protection theSide)
{
    //@TO DO: Need to pass in real port
    //@ TO DO: Verify if this is needed for single card
    //Determine if there is a configuration mismatch and correct.
    //Only done in the cases where it is a 2 card setup

    //If both sources are local, then no need to check mismatch since split
    //brain not possible.
    if (mySourcesLocal.working == true && mySourcesLocal.protection == true)
    {
        return false;
    }

    //Do not check a source that is not local
    if (mySourcesLocal.working == false && theSide == CT_SP_WORKING_SIDE)
    {
        return false;
    }

    //Do not check a source that is not local
    if (mySourcesLocal.protection == false && theSide == CT_SP_PROTECTION_SIDE)
    {
        return false;
    }

    uint8 thePQWChannel = INVALID_PQW_CHANNEL;
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);

    if (theSide == CT_SP_WORKING_SIDE)
        thePQWChannel = myPQWChannels.working;
    else
        thePQWChannel = myPQWChannels.protection;


    uint16 rxMsg = theSncIf.GetRxPQM(thePQWChannel);
    uint16 txMsg = theSncIf.GetTxPQM(thePQWChannel);
    bool mateSourceEnable = true;
    /*No need to check RxHwPQWSquelch. On the active: TxSwPQWSrcEnable=true; on the standby TxSwPQWSrcEnable=false.
    Check RxHwPQWSquelch will cause the unnecessary switch when both working and protecting have defects(MR172662)*/
    bool txSourceEnable = true;

    if (GetMateModPresence(theSide) == true)
    {
        if ( (rxMsg & SP_PQW_MSG_VALID) == SP_PQW_MSG_VALID)
        {
            //if HW PQW indicates that src is enabled, then check the software bit as well
            //since there are many cases where hw squelch is not used
            if (mateSourceEnable)
            {
                if ( (rxMsg & SP_PQW_SRC_ENABLED) != SP_PQW_SRC_ENABLED)
                   mateSourceEnable = false;
            }

            if (txSourceEnable)
            {
                //if HW PQW indicates that src is enabled, then check the software bit as well
                //since there are many cases where hw squelch is not used
                if ( (txMsg & SP_PQW_SRC_ENABLED) != SP_PQW_SRC_ENABLED)
                   txSourceEnable = false;
            }

            //If both sources are disabled:
            //On working card, indicate config mismatch
            //On protect card, indicate no config mismatch
            if (mateSourceEnable == false && txSourceEnable == false)
            {
                if (theSide == CT_SP_WORKING_SIDE)
                {
                    //Check to see whether there are any forced/lockout commands in place. If so dont attempt to correct
                    const CT_SP_CommandType& theCommand = myProtectionAction.myRequestParserPtr->GetCommand();
                    if (theCommand.myRequest == CT_SP_1PLUS1_FS_P ||
                        theCommand.myRequest == CT_SP_1PLUS1_LK_P ||
                        theCommand.myRequest == CT_SP_1PLUS1_FS_W)
                    {
                        if (gSP_DebugTraceSnc == 1)
                        {
                            fc_cout << "Both sources off..not attempting to correct due to forced or lockout present" << endl;
                        }
                        return false;
                    }
                    else
                    {
                        //DEBUG
                        if (gSP_DebugTraceSnc == 1)
                        {
                            fc_cout << "Config mismatch detected, both sources off..attempting to correct" << endl;
                        }
                        return true;
                    }
                }
            }
        
            //If both sources are enabled:
            //On working card, indicate no config mismatch
            //On protect card, indicate config mismatch
            if (mateSourceEnable == true && txSourceEnable == true)
            {   
                if (theSide == CT_SP_PROTECTION_SIDE)
                {
                    //DEBUG
                    if (gSP_DebugTraceSnc == 1)
                    {
                        fc_cout << "Config mismatch detected, both sources on..attempting to correct" << endl;
                    }
                    return true;
                }
            }
        }
    }

    return false;
}

bool SP_OduKSnc::CheckConfiguration(SP_ProtectionGroupConfig& theConfig)
{
    bool hasChanged = false;
    bool hasXcPatChanged = false;
    int theIdx;
    bool theDC;
    SP_1plus1ProtectionGroupConfig & aConfig = static_cast<SP_1plus1ProtectionGroupConfig&> (theConfig);
    
    //If only one side has changed and the side that changed was local, then...
    //disable the side that changed.
    //Clear interupt and poll configuration for the side that is not changing
    //Reset the data
    //Enable again to resetup the protection group.

    if (myIsConfigured)
    {
        bool workingChanged = (myProtectionAction.Get1plus1Config().GetSources().working != aConfig.GetSources().working);
        bool protectChanged = (myProtectionAction.Get1plus1Config().GetSources().protection != aConfig.GetSources().protection);
        //If working has changed and protect has not...
        if (workingChanged == true &&
            protectChanged == false)
        {
            //Then disable the working
            if (mySourcesLocal.working == true)
            {
                Disable(CT_SP_WORKING_SIDE);
            }

            //Lite disable on the side that didnt change
            if (mySourcesLocal.protection == true)
            {
                DisableLite(CT_SP_PROTECTION_SIDE);
            }

            hasChanged = true;
        }

        //If protect has changed and working has not...
        if (workingChanged == false &&
            protectChanged == true)
        {
            if (mySourcesLocal.protection == true)
            {
                Disable(CT_SP_PROTECTION_SIDE);
            }

            //Lite disable on the side that didnt change
            if (mySourcesLocal.working == true)
            {
                DisableLite(CT_SP_WORKING_SIDE);
            }

            hasChanged = true;
        }
        

        if (workingChanged == false &&
            protectChanged == false)
        {
            CT_SP_Protection selectedSide = mySelector.GetSelection();
            //Sources didnt change, but connection pattern may have
            if (mySourcesLocal.working == true)
            {
                hasXcPatChanged = EvaluateConnectionPattern(CT_SP_WORKING_SIDE, (uint32)aConfig.GetSources().working.GetPortId(), false, &theIdx, &theDC);
                //On the non-selected side, turn off tx on a transition from DC to not DC.
                if (selectedSide == CT_SP_PROTECTION_SIDE)
                {
                    if (hasXcPatChanged)
                    {
                        if (myDC.working == true && theDC == false)
                        {
                            SourceTxControlSelectorImp(CT_SP_WORKING_SIDE, SP_SEL_SWITCH_AWAY);
                            if (gSP_DebugTraceSnc == 1)
                            {
                                fc_cout << "Transition from DC to nonDC on working side, turning off tx" << endl;
                            }
                        }
                    }
                }
                hasChanged |= hasXcPatChanged;

            }

            if (mySourcesLocal.protection == true)
            {
                hasXcPatChanged = EvaluateConnectionPattern(CT_SP_PROTECTION_SIDE, (uint32)aConfig.GetSources().protection.GetPortId(), false, &theIdx, &theDC);
                //On the non-selected side, turn off tx on a transition from DC to not DC.
                if (selectedSide == CT_SP_WORKING_SIDE)
                {
                    if (hasXcPatChanged)
                    {
                        if (myDC.protection == true && theDC == false)
                        {
                            SourceTxControlSelectorImp(CT_SP_PROTECTION_SIDE, SP_SEL_SWITCH_AWAY);
                            if (gSP_DebugTraceSnc == 1)
                            {
                                fc_cout << "Transition from DC to nonDC on protection side, turning off tx" << endl;
                            }
                        }
                    }
                }
                hasChanged |= hasXcPatChanged;
            }

            if (hasChanged)
            {
                DisableLite(CT_SP_WORKING_SIDE);
                DisableLite(CT_SP_PROTECTION_SIDE);
            }
        }

        if (hasChanged)
        {
            //This is the last thing that should be done in this function, as we are numbing the protection scheme for a reenable
            ResetData();
        }
        else
        {
            //If PS hasnt changed, check for a change in the holdoff timer configuration value. If the value has changed, then go ahead and reconfigure
            //the hardware with that value
            TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
            TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
            uint32 holdOffTimer = aConfig.GetHoldOffTimer();

            if (mySourcesLocal.working == true)
            {
                if (theSncIf.GetSquelchHoldOffDelay(myPQWChannels.working) != holdOffTimer)
                {
                    theSncIf.SetSquelchHoldOffDelay(myPQWChannels.working, holdOffTimer);
                }
            }

            if (mySourcesLocal.protection == true)
            {
                if (theSncIf.GetSquelchHoldOffDelay(myPQWChannels.protection) != holdOffTimer)
                {
                    theSncIf.SetSquelchHoldOffDelay(myPQWChannels.protection, holdOffTimer);
                }
            }

        }
    }
    
    return (hasChanged);
}

bool SP_OduKSnc::IsProtectionGroupDifferent(SP_ProtectionGroupConfig& theConfig)
{
    //If only one of the 2 sources has changed and the protection type hasnt changed, 
    //then
    SP_1plus1ProtectionGroupConfig& aConfig = static_cast<SP_1plus1ProtectionGroupConfig&>(theConfig);
    if (myProtectionAction.Get1plus1Config().InUse() != aConfig.InUse() ||
        myProtectionAction.Get1plus1Config().Get1plus1Type() != aConfig.Get1plus1Type())
    {
        return true;
    }
    else
    {
        //If only one of the sources is different, do not consider this a chance as we we may be switching
        //out a leg (for always on)
        if (myProtectionAction.Get1plus1Config().GetSources().working != aConfig.GetSources().working &&
            myProtectionAction.Get1plus1Config().GetSources().protection != aConfig.GetSources().protection)
            return true;
    }

    //For SNC-S, check to see whether stored TCM ID is different from current and if so, cause a recreation of the protection group
    if (myProtectionAction.Get1plus1Config().Get1plus1Type() == CT_SP_SNCS)
    {
        CFG_Region* theCfgTcmRegion = myApplIf.GetCardContext().GetTcmIf().GetCfgPortSideApp(SP_TCM_PORT_ID).GetCfgRegion();
        CFG_Tcm* aCfgTcmObject = NULL;

        if (mySourcesLocal.working == true)
        {
            CFG_Region* theCfgOdukRegion = myApplIf.GetCardContext().GetOduIf().GetCfgPortSideApp(myLayerPort.working).GetCfgRegion();
            CFG_Odu* aCfgOdukObject = static_cast<CFG_Odu*>(&((*theCfgOdukRegion)[myLayerIdx.working]));
            if (aCfgOdukObject->GetServerID() != myServerLinkageId.working)
                return true;

            aCfgTcmObject = static_cast<CFG_Tcm*>(&((*theCfgTcmRegion)[myTcmIdx.working]));
            if (aCfgTcmObject->GetTcmIdentifier() != myTcmId.working)
                return true;
        }

        if (mySourcesLocal.protection == true)
        {
            CFG_Region* theCfgOdukRegion = myApplIf.GetCardContext().GetOduIf().GetCfgPortSideApp(myLayerPort.protection).GetCfgRegion();
            CFG_Odu* aCfgOdukObject = static_cast<CFG_Odu*>(&((*theCfgOdukRegion)[myLayerIdx.protection]));
            if (aCfgOdukObject->GetServerID() != myServerLinkageId.protection)
                return true;

            aCfgTcmObject = static_cast<CFG_Tcm*>(&((*theCfgTcmRegion)[myTcmIdx.protection]));
            if (aCfgTcmObject->GetTcmIdentifier() != myTcmId.protection)
                return true;
        }

    }

    return false;
}


bool SP_OduKSnc::EvaluateConnectionPattern(CT_SP_Protection theSide, uint32 thePortId, bool doSave, int* theIdx, bool* isDC)
{
    bool hasChanged = false;    
    int offset = -1;
    (*theIdx) = offset;
    (*isDC) = false;

    int oldXcIndex = -1;
    if ( theSide == CT_SP_WORKING_SIDE )
    {
        oldXcIndex = myXcIndex.working;
    }
    else
    {
        oldXcIndex = myXcIndex.protection;
    }


    //Look for connection pattern changes and configure selector appropriately
    bool dropAndContinueExists = false;
    TSXC_BaseApplication& theXCAppIf = myApplIf.GetCardContext().GetXCAppIf().GetXCApp();
    if (theXCAppIf.GetAgCfgRegion()->Size() > 0)
    {
        offset = theXCAppIf.GetIndexFromOduLogicalId(thePortId);
        if (offset == -1)
        {
            fc_cout << "SP_OduKSnc::EvaluateConnectionPattern Invalid index returned from xc. Port id was " << thePortId << endl;
            //If I am configured but XC is not ready, then dont overwrite my configuration with invalid values.
            if (myIsConfigured)
            {
                return hasChanged;
            }
        }
        if (offset != oldXcIndex)
        {
            //If I am configured but XC is not ready, then dont overwrite my configuration with invalid values.
            if (myIsConfigured)
            {
                return hasChanged;
            }
        }
    }
    else
    {
        fc_cout << "SP_OduKSnc::EvaluateConnectionPattern XC CFG AG region size is 0 " << endl;
    }

    if ( myXCRouteCfgRegion && myXCRouteCfgRegion->Size() > 0)
    {
        if (offset != -1)
        {
            uint16 mcastIdFixed =  (*myXCRouteCfgRegion)[(uint16)offset].GetMCastId(CT_XC_MAPPING_FIXED);
            uint16 mcastIdFlex =   (*myXCRouteCfgRegion)[(uint16)offset].GetMCastId(CT_XC_MAPPING_FLEXIBLE);
            if ( mcastIdFixed != mcastIdFlex)
            {
                dropAndContinueExists = true;
            }
        }
    }
    else
    {
        //If the xc route cfg region is expected to be present
        if (myXCRouteCfgRegion)
        {
            fc_cout << "SP_OduKSnc::EvaluateConnectionPattern XCRouteCfgRegion is 0 " << endl;
        }
    }

    hasChanged |= SetXcParams(theSide, dropAndContinueExists, offset, doSave);
    (*theIdx) = offset;
    (*isDC) = dropAndContinueExists;
    return hasChanged;
}

bool SP_OduKSnc::GetMateModPresence(CT_SP_Protection theSide)
{
    bool thePresence = true;
    
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
    uint32 PII_count;
    if (theSide == CT_SP_WORKING_SIDE)
    {
        PII_count= theSncIf.GetPqwTimeout(myMateLogicalShelf-1, myMatePortOf.working.GetSlotId()-1 /*TSPII expects 0-based*/);
    }
    else
    {
        PII_count= theSncIf.GetPqwTimeout(myMateLogicalShelf-1, myMatePortOf.protection.GetSlotId()-1 /*TSPII expects 0-based*/);
    }
    if(PII_count%2 != 0)
    {
        thePresence = false;
    }
    
    return thePresence;
}

void SP_OduKSnc::ConfigureLogicalShelfId(bool configure, CT_ShelfId wShelf, CT_ShelfId pShelf)
{
    if (configure)
    {
        CT_ShelfId theShelfId1, theShelfId2;
        if (myCfgSwitchModeRegion)
        {
            CFG_Misc& aMiscCfgObject = static_cast<CFG_Misc&> ((*myCfgSwitchModeRegion)[0]);
            SP_OduKSncSwitchFabConfig::GetInstance().GetLogicalShelfId(aMiscCfgObject, wShelf, pShelf, &theShelfId1, &theShelfId2);
            //Setup the logical mate shelf id
            if (wShelf == pShelf)
            {
                myMateLogicalShelf = theShelfId1; //Mate is on my shelf
            }
            else
            {
                myMateLogicalShelf = theShelfId2; //Mate is on another shelf
            }
        }
        else
        {
            theShelfId1 = 1;
            theShelfId2 = 1;
            myMateLogicalShelf = 1;
        }
    }
    else
    {
        myMateLogicalShelf =0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
void SP_OduKSnc::MulticastSelectorImp(CT_SP_Protection theSide, SP_SncSelSwitchDir theDir)
{
    //If switching to, then pick the flexible entry,
    //If switching away, then pick the fixed entry
    if (myMCFilterRegion)
    {
        int theMCastRegionIndex =0;

        if (theSide == CT_SP_WORKING_SIDE)
        {
            theMCastRegionIndex = myXcIndex.working;
        }
        else
        {
            theMCastRegionIndex = myXcIndex.protection;
        }

        TSXC_BaseApplication& theXCAppIf = myApplIf.GetCardContext().GetXCAppIf().GetXCApp();
        TSXC_S1RtAction* aS1RtAction = theXCAppIf.GetS1RtAction();    
        if (theDir == SP_SEL_SWITCH_TO)
        {
            (*myMCFilterRegion)[theMCastRegionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FIXED);
            if (gSP_DebugTraceSnc)
            {
                fc_cout << "[SP_OduKSnc]MulticastSelectorImp() switch to FIX-GP" << endl;
            }
        }
        else
        {
            (*myMCFilterRegion)[theMCastRegionIndex].SetMCastTypeToUse(CT_XC_MAPPING_FLEXIBLE);
            if (gSP_DebugTraceSnc)
            {
                fc_cout << "[SP_OduKSnc]MulticastSelectorImp() switch to FLEXIBLE-GP" << endl;
            }
        }

        //Apply to hardware
        aS1RtAction->ApplyCesIngress((uint16)theMCastRegionIndex);
    }
    
}

//////////////////////////////////////////////////////////////////////////////////////////////
void SP_OduKSnc::SourceTxControlSelectorImp(CT_SP_Protection theSide, SP_SncSelSwitchDir theDir)
{
    FC_TimePrecise starttime;
    starttime.GetCurrentTime();
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
    TSPII_DwRegion* theDwRegion;
    bool sourceEnable = ( (theDir == SP_SEL_SWITCH_TO) ? true : false);

    //@TO DO: Does this tie into odu layer or TOH fpga
    if (theSide == CT_SP_WORKING_SIDE)
    {
        theDwRegion = TSPII_SubApplication::GetInstance()->GetDw(myTspiiOduPort.working);
        (*theDwRegion)[myTspiiOduIdx.working].SetSrcTrafficEnabled(sourceEnable);
        theSncIf.SetSrcTrafficEnabled(myPQWChannels.working, sourceEnable);
        if ( gSP_DebugTraceSnc == 1 )
        {
            FC_TimePrecise time;
            time.GetCurrentTime();
            fc_cout << "WSNCEn " << uint32(myTspiiOduIdx.working) << " " << uint32(sourceEnable ? 1:0) << " pqw=" << uint32(myPQWChannels.working) << " " << uint32(time.GetUTCTime()) << "sec " << uint32(time.GetFractionalTime()) << "ms" << endl;
        }
    }
    else
    {
        theDwRegion = TSPII_SubApplication::GetInstance()->GetDw(myTspiiOduPort.protection);
        (*theDwRegion)[myTspiiOduIdx.protection].SetSrcTrafficEnabled(sourceEnable);
        theSncIf.SetSrcTrafficEnabled(myPQWChannels.protection, sourceEnable);
        if ( gSP_DebugTraceSnc == 1 )
        {
            FC_TimePrecise time;
            time.GetCurrentTime();
            fc_cout << "PSNCEn " << uint32(myTspiiOduIdx.protection) << " " << uint32(sourceEnable ? 1:0) << " pqw=" << uint32(myPQWChannels.protection) << " " << uint32(time.GetUTCTime()) << "sec " << uint32(time.GetFractionalTime()) << "ms" << endl;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
void SP_OduKSnc::SendSelStateMessage(uint16 usrCmdMsg, CT_SP_Protection theSide, SP_SncSelSwitchDir theDir)
{
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
    const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect>& theDefect = myProtectionAction.myRequestParserPtr->GetDefectStatus();
    uint16 defectMsg;

    if (gSP_DebugTraceSnc)
    {
        fc_cout << "[SP_OduKSnc]SendSelStateMessage to " << DISPLAY_CT_SP_Protection(theSide) <<" do " <<DISPLAY_SNC_SEL_SWITCH_DIR(theDir) << endl;
    } 
    
    defectMsg = ((theSide == CT_SP_WORKING_SIDE) ? theDefect.working : theDefect.protection);
    
    //Shift to correct position
    defectMsg = defectMsg << SP_PQW_AUTO_CMD_SHIFT;
    
    //Send defect and manual switch indicator
    uint16 theTxMsg = 0;

    //if (mySetToDefault == false)
    // {
        theTxMsg = (theTxMsg | defectMsg);
        theTxMsg = (theTxMsg | usrCmdMsg);
    //}

    //Add the current selection bit
    uint16 theCurrSel = 1; //Selected
    if (theDir == SP_SEL_SWITCH_AWAY)
        theCurrSel =0;

    //Shift to correct position
    theCurrSel = theCurrSel << SP_PQW_SRC_ENAB_SHIFT;
    theTxMsg = theTxMsg | theCurrSel;

    //Add the valid state
    theTxMsg = (theTxMsg | 0x1);

    if (theSide == CT_SP_WORKING_SIDE)
    {
        theSncIf.SetTxPQM(myPQWChannels.working, theTxMsg, SP_PQW_ALL_MASK);

        if (gSP_DebugTraceSnc == 1)
        {
            if (myTxMsg.working != theTxMsg)
            {
                fc_cout << "Tx Msg: " << (uint32) theTxMsg << " Tx Mask: " << SP_PQW_ALL_MASK << endl;
            }
        }

        myTxMsg.working = theTxMsg;
    }
    else
    {
        theSncIf.SetTxPQM(myPQWChannels.protection, theTxMsg, SP_PQW_ALL_MASK);

        if (gSP_DebugTraceSnc == 1)
        {
            if (myTxMsg.protection != theTxMsg)
            {
                fc_cout << "Tx Msg: " << (uint32) theTxMsg << " Tx Mask: " << SP_PQW_ALL_MASK << endl;
            }
        }

        myTxMsg.protection = theTxMsg;
    }

    //DEBUG
    //fc_cout << "Tx Msg: " << (uint32) theTxMsg << " Tx Mask: " << SP_PQW_ALL_MASK << endl;
    //END DEBUG
}


//////////////////////////////////////////////////////////////////////////////////////////////
void SP_OduKSnc::GetSwitchParams(bool* switchingAllowed, uint16* userCmdMsg, SP_SncSelSwitchDir* theWDir, SP_SncSelSwitchDir* thePDir, bool* sendMessage, bool* mateActive, CT_SP_Protection theCurrentSelection)
{
    if (gSP_DebugTraceSnc == 1)
    {
        DispPQW();
    }
    (*sendMessage) = true;
    bool switchAllowed = true;

    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
    uint8 thePQWChannel = INVALID_PQW_CHANNEL;
    uint16 mateusrCmdMsg =0;
    bool mateSourceEnable = false;
    bool bothSourcesLocal = (mySourcesLocal.working == true && mySourcesLocal.protection == true);


    if (bothSourcesLocal == true)
    {
        mateSourceEnable = false;
        switchAllowed = true;
    }
    else
    {
        if (mySourcesLocal.working == true)
            thePQWChannel = myPQWChannels.working;
        else
            thePQWChannel = myPQWChannels.protection;

        uint16 rxMsg = theSncIf.GetRxPQM(thePQWChannel);
        if (gSP_DebugTraceSnc)
        {
            fc_cout << "[SP_OduKSnc]GetSwitchParams GetRxPQM()=0x" << hex << rxMsg << dec << endl;
        }
        
        mateSourceEnable = (theSncIf.GetRxHwPQWSquelch(thePQWChannel) == false);
        mateusrCmdMsg = (rxMsg & SP_PQW_USR_CMD);

        if (GetMateModPresence((mySourcesLocal.working == true ? CT_SP_WORKING_SIDE : CT_SP_PROTECTION_SIDE)) == true)
        {
            if ( (rxMsg & SP_PQW_MSG_VALID) == SP_PQW_MSG_VALID)
            {
                //if HW PQW indicates that src is enabled, then check the software bit as well
                //since there are many cases where hw squelch is not used
                if (mateSourceEnable)
                {
                    if ( (rxMsg & SP_PQW_SRC_ENABLED) != SP_PQW_SRC_ENABLED)
                        mateSourceEnable = false;
                }
            }
            else
            {
                switchAllowed = false; /*Not allowed to switch since remote PQW is not valid*/
            }
        }
        else
        {
            mateSourceEnable = false;
        }
    }

    //@TO DO: Prevent both sources from turning on at the same time
    //@TO DO: Add WTR processing?????
    uint16 usrCmdMsg = 0x0;
    bool usrCommand = true;
    const CT_SP_CommandType& theCommand = myProtectionAction.myRequestParserPtr->GetCommand();
    switch (theCommand.myRequest)
    {
        case CT_SP_1PLUS1_MS_P:
            usrCmdMsg = SP_PQW_USER_CMD_MSG_MS_P;
            break;
        case CT_SP_1PLUS1_FS_P:
            usrCmdMsg = SP_PQW_USER_CMD_MSG_FS_P;
            break;
        case CT_SP_1PLUS1_LK_P:
            usrCmdMsg = SP_PQW_USER_CMD_MSG_LK_P;
            break;
        case CT_SP_1PLUS1_FS_W:
            usrCmdMsg = SP_PQW_USER_CMD_MSG_FS_W;
            break;
        case CT_SP_1PLUS1_MS_W:
            usrCmdMsg = SP_PQW_USER_CMD_MSG_MS_W;
            break;
        case CT_SP_1PLUS1_CLEAR:/*Revertive mode, when traffic is forced switched to protection,
            if Rls-PROTNSW-ODU, the protection state machine will go to NO-REQ immediately. The
            Release command need to be synchronized between the working and protection card.t71mr00223669*/
            usrCmdMsg = SP_PQW_USER_CMD_MSG_CLR;
            break;
        default:
            myUserCommandIsPending = false;
            usrCommand = false;
            break;
    }

    //Treat a WTR condition as a manual command for signaling to mate module
    SP_K1Request aK1Request = myProtectionAction.myK1K2TransmitterPtr->GetTransmittedKbytes().request;
    if (aK1Request == SP_1PLUS1_K1_WTR)
    {
        usrCmdMsg = SP_PQW_USER_CMD_MSG_WTR;
    }

    //Now shift to correct position
    usrCmdMsg = usrCmdMsg << SP_PQW_USER_CMD_SHIFT;

    
    //Both ends have synchronized on the command, so 
    //if we are switching away stop selecting local traffic regardless of mate
    //source state. If we are switching to, then only select local traffic only when
    //other side is turned off

    bool selectLocalTraffic = false;

    if (bothSourcesLocal == false)
    {
        bool remoteSelected = false;
        if ( (theCurrentSelection == CT_SP_WORKING_SIDE &&
              mySourcesLocal.working == false) ||
             (theCurrentSelection == CT_SP_PROTECTION_SIDE &&
              mySourcesLocal.protection == false)
           )
        {
            remoteSelected = true;
        }

        //Remote is selected, turn off source
        if (remoteSelected == true)
        {
            if (usrCommand == true)
            {
                if (usrCmdMsg == mateusrCmdMsg)
                {
                    selectLocalTraffic = false;
                    myUserCommandIsPending = false;
                }
                else
                {
                    myUserCommandIsPending = true;
                    switchAllowed = false;
                    (*sendMessage) = false;
                }
            }
            else
            {
                //If we are just coming out of WTR due to timer expiration, do not do anything until the working
                //side timer has also expired since there is no way to synchronize timers across multiple modules.
                const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect>& theDefect = myProtectionAction.myRequestParserPtr->GetDefectStatus();
                if (mySourcesLocal.protection == true && //Protect side
                    mateusrCmdMsg == SP_PQW_USER_CMD_MSG_WTR_SHIFTED &&
                    usrCommand == false &&
                    theDefect.protection == CT_SP_AUTO_NONE)
                {
                    //fc_cout << "Waiting for working wtr to expire" << endl;
                    switchAllowed = false;
                    (*sendMessage) = false;
                }
                else
                {
                    selectLocalTraffic = false;
                }
            }
        }
        //Local is selected
        else
        {
            if (mateSourceEnable == false)
            {
                selectLocalTraffic = true;
                myUserCommandIsPending = false;
            }
            else
            {
                if (usrCommand == true)
                {
                    myUserCommandIsPending = true;
                }
                else
                {
                    (*mateActive) = true;
                }
                switchAllowed = false;
            }
        }
    }

    //If deleting, then turn off the sources
    //if (mySetToDefault == true)
    // {
    //    selectLocalTraffic = false;
    //    switchAllowed = true;
    //}

#ifdef __SIMULATION__
    switchAllowed = true;
#endif

    (*switchingAllowed) = switchAllowed;
    if (bothSourcesLocal == true)
    {
        if (theCurrentSelection == CT_SP_WORKING_SIDE)
        {
            (*theWDir) = SP_SEL_SWITCH_TO;
            (*thePDir) = SP_SEL_SWITCH_AWAY;
        }
        else
        {
            (*theWDir) = SP_SEL_SWITCH_AWAY;
            (*thePDir) = SP_SEL_SWITCH_TO;
        }
    }
    else
    {
        if (selectLocalTraffic == true)
        {
            if (mySourcesLocal.working == true)
            {
                (*theWDir) = SP_SEL_SWITCH_TO;
                (*thePDir) = SP_SEL_SWITCH_AWAY;
            }
            else if (mySourcesLocal.protection == true)
            {
                (*theWDir) = SP_SEL_SWITCH_AWAY;
                (*thePDir) = SP_SEL_SWITCH_TO;
            }
        }
        else
        {
            //Other side is selected, switch away from our local side
            if (mySourcesLocal.working == true)
            {
                (*theWDir) = SP_SEL_SWITCH_AWAY;
                (*thePDir) = SP_SEL_SWITCH_TO;
            }
            else if (mySourcesLocal.protection == true)
            {
                (*theWDir) = SP_SEL_SWITCH_TO;
                (*thePDir) = SP_SEL_SWITCH_AWAY;
            }
        }
    }
   
    (*userCmdMsg) = usrCmdMsg;
    if (gSP_DebugTraceSnc == 1)
    {
        DispSwitchParams(*switchingAllowed, *userCmdMsg, *theWDir, *thePDir, *sendMessage, *mateActive, theCurrentSelection);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////
bool SP_OduKSnc::SetXcParams(CT_SP_Protection theSide, bool isDropAndContinue, int theXcIndex, bool doSave)
{
    
    bool hasChanged = false;
    
    if (theSide == CT_SP_WORKING_SIDE)
    {
        hasChanged |= (isDropAndContinue != myDC.working);
        hasChanged |= (theXcIndex != myXcIndex.working);
        if (doSave)
        {
            myDC.working = isDropAndContinue;
            myXcIndex.working = theXcIndex;
        }
        
    }
    else
    {
        hasChanged |= (isDropAndContinue != myDC.protection);
        hasChanged |= (theXcIndex != myXcIndex.protection);
        if (doSave)
        {
            myDC.protection = isDropAndContinue;
            myXcIndex.protection = theXcIndex;
        }
    }
    
    return hasChanged;
}


#define APPLY_SELECTOR(side, theFac, theDir) \
    {\
        if (mySourcesLocal.side == true) \
        { \
            if (myDC.side) \
            { \
                /*Turn on the tx source since there is a drop and continue*/ \
                SourceTxControlSelectorImp(theFac, SP_SEL_SWITCH_TO); \
                MulticastSelectorImp(theFac, theDir); \
            } \
            else \
            { \
                SourceTxControlSelectorImp(theFac, theDir); \
            } \
            /*Save off sel switch direction*/ \
            myPrevSelSwitchDir.side = theDir; \
        }\
    }

void SP_OduKSnc::Switch(CT_SP_Protection theSelectedSide)
{
    //For SNC, selector control varies based on configuration:
            
    //If there is a multicast, then the multicast tables are manipulated
    //If there is no multicast, then the source tx is controlled

    //@TO DO: Need to consider previous selector state when
    //sending selector state message
    bool switchingAllowed = true;
    SP_SncSelSwitchDir theWDir = SP_SEL_SWITCH_DIR_UNKNOWN;
    SP_SncSelSwitchDir thePDir = SP_SEL_SWITCH_DIR_UNKNOWN;
    uint16 userCmdMsg=0;
    bool sendTxMessage = true;
    bool mateActive = false;
    CT_SP_Protection firstApplySide = CT_SP_WORKING_SIDE;

 
    //Get switching parameters
    GetSwitchParams(&switchingAllowed, &userCmdMsg, &theWDir, &thePDir, &sendTxMessage, &mateActive, theSelectedSide);
    //First disable non-selected side
    //Then enable the selected side
    //Manipulate the selector
    if (switchingAllowed == true)
    {
        if (mySourcesLocal.working == true && mySourcesLocal.protection == true)
        {
            if (theWDir == SP_SEL_SWITCH_AWAY)
            {
                firstApplySide = CT_SP_WORKING_SIDE;
            }
            else
            {
                firstApplySide = CT_SP_PROTECTION_SIDE;
            }
        }
        else
        {
            firstApplySide = CT_SP_WORKING_SIDE;
        }

        if (gSP_DebugTraceSnc)
        {
            if(mySourcesLocal.working)
            {
                fc_cout << "[SP_OduKSnc]switchAllowed= true, local working side TSPII do " << DISPLAY_SNC_SEL_SWITCH_DIR(theWDir) << " ,DC = " << myDC.working << endl;
            }
            if(mySourcesLocal.protection)
            {
                fc_cout << "[SP_OduKSnc]switchAllowed= true, local protection side TSPII do " << DISPLAY_SNC_SEL_SWITCH_DIR(thePDir) << " ,DC = " << myDC.protection << endl;
            }
        }

        if (firstApplySide == CT_SP_WORKING_SIDE)
        {
            APPLY_SELECTOR(working, CT_SP_WORKING_SIDE, theWDir);
            APPLY_SELECTOR(protection, CT_SP_PROTECTION_SIDE, thePDir);
        }
        else
        {
            APPLY_SELECTOR(protection, CT_SP_PROTECTION_SIDE, thePDir);
            APPLY_SELECTOR(working, CT_SP_WORKING_SIDE, theWDir);
        }

    }
    else
    {
        if (myPrevSelSwitchDir.working != SP_SEL_SWITCH_DIR_UNKNOWN)
        {
            theWDir = myPrevSelSwitchDir.working;
        }

        if (myPrevSelSwitchDir.protection != SP_SEL_SWITCH_DIR_UNKNOWN)
        {
            thePDir = myPrevSelSwitchDir.protection;
        }

        if (theWDir == SP_SEL_SWITCH_AWAY)
        {
            if (gSP_DebugTraceSnc)
            {
                fc_cout << "[SP_OduKSnc]switchingAllowed = false, W DC " << endl;
            }
            
            //For drop and continue connections; keep the continue leg up regardless of whether switching is allowed
            if (myDC.working)
            { 
                //fc_cout << "SP DEBUG >>>>>>>>>>>>>>>> Activating continue leg for " << (uint32)myImuxHopIndex << endl;
                SourceTxControlSelectorImp(CT_SP_WORKING_SIDE, SP_SEL_SWITCH_TO); /*Turn on the tx source since there is a drop and continue*/
                MulticastSelectorImp(CT_SP_WORKING_SIDE, SP_SEL_SWITCH_AWAY); /*To keep the continue leg up always*/   
            }
        }

        if (thePDir == SP_SEL_SWITCH_AWAY)
        {
            if (gSP_DebugTraceSnc)
            {
                fc_cout << "[SP_OduKSnc]switchingAllowed = false, P DC " << endl;
            }
            
            //For drop and continue connections; keep the continue leg up regardless of whether switching is allowed
            if (myDC.protection)
            { 
                //fc_cout << "SP DEBUG >>>>>>>>>>>>>>>> Activating continue leg for " << (uint32)myImuxHopIndex << endl;
                SourceTxControlSelectorImp(CT_SP_PROTECTION_SIDE, SP_SEL_SWITCH_TO); /*Turn on the tx source since there is a drop and continue*/
                MulticastSelectorImp(CT_SP_PROTECTION_SIDE, SP_SEL_SWITCH_AWAY); /*To keep the continue leg up always*/   
            }
        }
    }
    //to send the sel state
    //Send selector state to remote
    if (sendTxMessage)
    {
        if (mySourcesLocal.working == true)
        {
            SendSelStateMessage(userCmdMsg, CT_SP_WORKING_SIDE, theWDir);
        }

        if (mySourcesLocal.protection == true)
        {
            SendSelStateMessage(userCmdMsg, CT_SP_PROTECTION_SIDE, thePDir);
        }
    }
}

void SP_OduKSnc::Commit()
{
    if (myDC.working == true || myDC.protection == true)
    {
        if (myMCFilterRegion)
        {
            myMCFilterRegion->IncModificationCounter();
            myMCFilterRegion->UpdateNotify();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
bool SP_OduKSnc::FindClientAndServerLayers(CT_SP_Protection theSide, uint32 theOduIdentifier, bool doSave)
{
    CT_CardType  cardtype = CSPII_CardIF::GetInstance()->GetCardType();

    CT_ODU_Identifier aOduIdentifier (theOduIdentifier);

    //Server defaults
    CT_IntfId theServerLayerPort = CT_INTF_ID_UNKNOWN;
    CT_IntfId theTwoStageTopServerLayerPort = CT_INTF_ID_UNKNOWN;
    int       theServerLayerIdx = -1;
    int       theTwoStageTopServerLayerIdx = -1;
    SP_SncServerLayer theServerLayerType = Server_Layer_None;
    SP_SncServerLayer theTwoStageTopServerLayerType = Server_Layer_None;
    uint16 theServerTspiiIdx = CT_DEFAULT_ODU_POSITION;
    uint16 theTwoStageTopServerTspiiIdx = CT_DEFAULT_ODU_POSITION;
    unsigned int theServerTspiiPort = 0;
    unsigned int theTwoStageTopServerTspiiPort = 0;
    CT_ODU_Identifier theServerOduId = CT_DEFAULT_ODU_ID;
    CT_ODU_Identifier theTwoStageTopServerOduId = CT_DEFAULT_ODU_ID;
    CT_IntfId theOtuKPort = CT_INTF_ID_UNKNOWN;
    int theOtukIdx = -1;

    //Client defaults
    CT_IntfId theLayerPort = CT_INTF_ID_UNKNOWN;
    int      theLayerIdx = -1;
    uint16 theTspiiOduIdx = CT_DEFAULT_ODU_POSITION;
    unsigned int theTspiiOduPort = 0;
    
    
    theLayerPort = GetClientOduKPort(aOduIdentifier);
    if (OSM1S == cardtype)
    {
        theTspiiOduPort = GetTspiiPort(theLayerPort, true);
    }
    else
    {
        theTspiiOduPort = GetTspiiPort(theLayerPort);
    }

    vector<CT_ODU_ServerID> aPositionList;
    CFG_Region* theCfgOdukRegion = myApplIf.GetCardContext().GetOduIf().GetCfgPortSideApp(theLayerPort).GetCfgRegion();
    for (int i=0; i<(int)theCfgOdukRegion->Size(); i++)
    {
        CFG_Odu* aCfgOdukObject = static_cast<CFG_Odu*>(&((*theCfgOdukRegion)[i]));
        if (aCfgOdukObject->GetOduIdentifier().GetIdValue() == theOduIdentifier)
        {
            aPositionList.clear();
            aPositionList = aCfgOdukObject->GetOduPositionList();

            theLayerIdx = i;
            theTspiiOduIdx = GetTSPIIOduKIndex(aOduIdentifier);

            if (aCfgOdukObject->GetOduObjectType() == CT_ODU_POOL_ODU_WITHIN_CLIENT)
            {
                //OTUk is the server layer
                theServerLayerPort = CT_IntfId(aPositionList[0].GetPoolInstance());
                theServerLayerIdx = 0;
                theServerLayerType = Server_Layer_OTUk;
                theServerOduId = aOduIdentifier; //Set server oduk id equal to client odu k id value since server is otuk
                theServerTspiiIdx = 0;
                theServerTspiiPort = GetTspiiPort(theServerLayerPort);
                theOtuKPort = theServerLayerPort; //Since server is OTUk, set otuk port equal to server port
                theOtukIdx = theServerLayerIdx; //Since server is OTUk, set otuk port idx to server port idx

            }

            else if (aCfgOdukObject->GetOduObjectType() == CT_ODU_POOL_MUX)
            {
                //ODUk is the server layer
                bool isOduType     = false;
                if (OSM1S == cardtype)
                {
                    isOduType = true;
                }
                theServerLayerPort = GetServerOduKPort(aPositionList[0]);
                theServerLayerIdx  = aPositionList[0].GetPoolInstance();
                theServerLayerType = Server_Layer_ODUk;
                theServerTspiiPort = GetTspiiPort(theServerLayerPort, isOduType);

                //Look up the CFG server oduk object
                CFG_Region* theCfgServerOdukRegion = myApplIf.GetCardContext().GetOduIf().GetCfgPortSideApp(theServerLayerPort).GetCfgRegion();
                CFG_Odu* aCfgServerOdukObject = static_cast<CFG_Odu*>(&((*theCfgServerOdukRegion)[theServerLayerIdx]));

                theServerTspiiIdx= GetTSPIIOduKIndex(aCfgServerOdukObject->GetOduIdentifier());
                theServerOduId = aCfgServerOdukObject->GetOduIdentifier();
                theOtuKPort = (CT_IntfId)GetUplayerPhysicalPort(aPositionList[0]);
                theOtukIdx = 0;

                if(aCfgServerOdukObject->GetOduObjectType() == CT_ODU_POOL_MUX)//two stage odu
                {
                    aPositionList.clear();
                    aPositionList = aCfgServerOdukObject->GetOduPositionList();
                    theTwoStageTopServerLayerPort = GetServerOduKPort(aPositionList[0]);
                    theTwoStageTopServerLayerIdx  = aPositionList[0].GetPoolInstance();
                    theTwoStageTopServerLayerType = Server_Layer_ODUk;
                    theTwoStageTopServerTspiiPort = GetTspiiPort(theTwoStageTopServerLayerPort, isOduType);

                    CFG_Region* theCfgTwoStageTopServerOdukRegion = myApplIf.GetCardContext().GetOduIf().GetCfgPortSideApp(theTwoStageTopServerLayerPort).GetCfgRegion();
                    CFG_Odu* aCfgTwoStageTopServerOdukObject = static_cast<CFG_Odu*>(&((*theCfgTwoStageTopServerOdukRegion)[theTwoStageTopServerLayerIdx]));

                    theTwoStageTopServerTspiiIdx= GetTSPIIOduKIndex(aCfgTwoStageTopServerOdukObject->GetOduIdentifier());
                    theTwoStageTopServerOduId = aCfgTwoStageTopServerOdukObject->GetOduIdentifier();
                }
            }

            break;
        }
    }

    if (theServerLayerPort == CT_INTF_ID_UNKNOWN ||
        theServerLayerIdx == -1 ||
        theServerLayerType == Server_Layer_None ||
        theServerOduId == CT_DEFAULT_ODU_ID ||
        theServerTspiiIdx == CT_DEFAULT_ODU_POSITION ||
        theServerTspiiPort == 0 ||
        theLayerPort == CT_INTF_ID_UNKNOWN ||
        theLayerIdx == -1 ||
        theTspiiOduIdx == CT_DEFAULT_ODU_POSITION ||
        theTspiiOduPort == 0 ||
        theOtuKPort == CT_INTF_ID_UNKNOWN ||
        theOtukIdx == -1)
    {
        return false;
    }
    else
    {
        if (doSave)
        {
            ((theSide == CT_SP_WORKING_SIDE) ? myLayerPort.working = theLayerPort     : myLayerPort.protection = theLayerPort);
            ((theSide == CT_SP_WORKING_SIDE) ? myLayerIdx.working = theLayerIdx       : myLayerIdx.protection = theLayerIdx);
            ((theSide == CT_SP_WORKING_SIDE) ? myTspiiOduPort.working = theTspiiOduPort  : myTspiiOduPort.protection = theTspiiOduPort);
            ((theSide == CT_SP_WORKING_SIDE) ? myTspiiOduIdx.working = theTspiiOduIdx : myTspiiOduIdx.protection = theTspiiOduIdx);

            ((theSide == CT_SP_WORKING_SIDE) ? myServerLayerType.working = theServerLayerType : myServerLayerType.protection = theServerLayerType);
            ((theSide == CT_SP_WORKING_SIDE) ? myTwoStageTopServerLayerType.working = theTwoStageTopServerLayerType : myTwoStageTopServerLayerType.protection = theTwoStageTopServerLayerType);
            ((theSide == CT_SP_WORKING_SIDE) ? myServerLayerPort.working = theServerLayerPort : myServerLayerPort.protection = theServerLayerPort);
            ((theSide == CT_SP_WORKING_SIDE) ? myTwoStageTopServerLayerPort.working = theTwoStageTopServerLayerPort : myTwoStageTopServerLayerPort.protection = theTwoStageTopServerLayerPort);
            ((theSide == CT_SP_WORKING_SIDE) ? myServerLayerIdx.working = theServerLayerIdx   : myServerLayerIdx.protection = theServerLayerIdx);
            ((theSide == CT_SP_WORKING_SIDE) ? myTwoStageTopServerLayerIdx.working = theTwoStageTopServerLayerIdx   : myTwoStageTopServerLayerIdx.protection = theTwoStageTopServerLayerIdx);
            ((theSide == CT_SP_WORKING_SIDE) ? myServerLayerOduId.working = theServerOduId    : myServerLayerOduId.protection = theServerOduId);
            ((theSide == CT_SP_WORKING_SIDE) ? myTwoStageTopServerLayerOduId.working = theTwoStageTopServerOduId    : myTwoStageTopServerLayerOduId.protection = theTwoStageTopServerOduId);
            ((theSide == CT_SP_WORKING_SIDE) ? myServerTspiiPort.working = theServerTspiiPort : myServerTspiiPort.protection = theServerTspiiPort);
            ((theSide == CT_SP_WORKING_SIDE) ? myTwoStageTopServerTspiiPort.working = theTwoStageTopServerTspiiPort : myTwoStageTopServerTspiiPort.protection = theTwoStageTopServerTspiiPort);
            ((theSide == CT_SP_WORKING_SIDE) ? myServerTspiiIdx.working = theServerTspiiIdx   : myServerTspiiIdx.protection = theServerTspiiIdx);
            ((theSide == CT_SP_WORKING_SIDE) ? myTwoStageTopServerTspiiIdx.working = theTwoStageTopServerTspiiIdx   : myTwoStageTopServerTspiiIdx.protection = theTwoStageTopServerTspiiIdx);

            ((theSide == CT_SP_WORKING_SIDE) ? myOtuKPort.working = theOtuKPort : myOtuKPort.protection = theOtuKPort);
            ((theSide == CT_SP_WORKING_SIDE) ? myOtuKIdx.working = theOtukIdx   : myOtuKIdx.protection = theOtukIdx);
        }

        return true;
    }
}

bool SP_OduKSnc::FindTcmLayers(CT_SP_Protection theSide, uint32 theOduIdentifier, bool doSave)
{
    CT_ODU_Identifier aOduIdentifier (theOduIdentifier);

    //TCM defaults
    CT_ODU_Identifier aTcmId = CT_DEFAULT_ODU_ID;
    int aTcmIdx = -1;
    uint16 aTspiiTcmIdx = CT_DEFAULT_ODU_POSITION;
    CT_ODU_ServerID aLinkageServerId = CT_DEFAULT_ODU_SERVER_ID;
    
    
    CT_IntfId theLayerPort = GetClientOduKPort(aOduIdentifier);

    CFG_Region* theCfgOdukRegion = myApplIf.GetCardContext().GetOduIf().GetCfgPortSideApp(theLayerPort).GetCfgRegion();
    for (int i=0; i<(int)theCfgOdukRegion->Size(); i++)
    {
        CFG_Odu* aCfgOdukObject = static_cast<CFG_Odu*>(&((*theCfgOdukRegion)[i]));
        if (aCfgOdukObject->GetOduIdentifier().GetIdValue() == theOduIdentifier)
        {
            aLinkageServerId = aCfgOdukObject->GetServerID();
            if (aLinkageServerId != CT_DEFAULT_ODU_SERVER_ID) 
            {
                if (aLinkageServerId.GetIdTelecomLayer() == CT_ServerPool_Layer_Tcm)
                {
                    uint16 aPoolIndex = aLinkageServerId.GetPoolInstance();
                    CFG_Region* theCfgTcmRegion = myApplIf.GetCardContext().GetTcmIf().GetCfgPortSideApp(SP_TCM_PORT_ID).GetCfgRegion();

                    CFG_Tcm* aCfgTcmObject = static_cast<CFG_Tcm*>(&((*theCfgTcmRegion)[aPoolIndex]));
                    if (aCfgTcmObject)
                    {
                        if (aCfgTcmObject->GetTcmIdentifier() != CT_DEFAULT_ODU_ID && aCfgTcmObject->GetProvisionningActive())
                        {
                            aTcmId = aCfgTcmObject->GetTcmIdentifier();
                            aTcmIdx = aPoolIndex;
                            aTspiiTcmIdx = aPoolIndex;
                        }
                    }
                }
            }
            break;
        }
    }

    if (aTcmId == CT_DEFAULT_ODU_ID ||
        aTcmIdx == -1 ||
        aTspiiTcmIdx == CT_DEFAULT_ODU_POSITION ||
        aLinkageServerId == CT_DEFAULT_ODU_SERVER_ID)
    {
        return false;
    }
    else
    {
        if (doSave)
        {
            ((theSide == CT_SP_WORKING_SIDE) ? myTcmId.working = aTcmId                      : myTcmId.protection = aTcmId);
            ((theSide == CT_SP_WORKING_SIDE) ? myTcmIdx.working = aTcmIdx                    : myTcmIdx.protection = aTcmIdx);
            ((theSide == CT_SP_WORKING_SIDE) ? myTspiiTcmIdx.working = aTspiiTcmIdx          : myTspiiTcmIdx.protection = aTspiiTcmIdx);
            ((theSide == CT_SP_WORKING_SIDE) ? myServerLinkageId.working = aLinkageServerId  : myServerLinkageId.protection = aLinkageServerId);
        }

        return true;
    }
}

CT_IntfId SP_OduKSnc::GetClientOduKPort(CT_ODU_Identifier aOduIdentifier)
{
    CT_IntfId theClientPort = CT_INTF_ID_UNKNOWN;
    uint8 kVal = aOduIdentifier.GetOduKvalue();
    if (kVal == CT_ODU_Layer0 || kVal == CT_ODU_LayerF)
    {
        theClientPort = CT_PORT_SIDE_30;
    }
    else if (kVal == CT_ODU_Layer1)
    {
        theClientPort = CT_PORT_SIDE_31;
    }
    else if (kVal == CT_ODU_Layer2)
    {
        theClientPort = CT_PORT_SIDE_32;
    }
    else if (kVal == CT_ODU_Layer3)
    {
        theClientPort = CT_PORT_SIDE_33;
    }
    else if (kVal == CT_ODU_Layer4)
    {
        theClientPort = CT_PORT_SIDE_34;
    }

    return theClientPort;
}

CT_IntfId SP_OduKSnc::GetServerOduKPort(CT_ODU_ServerID theServerId)
{
    CT_IntfId theServerPort = CT_INTF_ID_UNKNOWN;
    uint8 kVal = theServerId.GetOduKvalue();
    if (kVal == CT_ODU_Layer1)
    {
        //ODU1 is the server
        theServerPort = CT_PORT_SIDE_31;
    }
    else if (kVal == CT_ODU_Layer2)
    {
        //ODU2 is the server
        theServerPort = CT_PORT_SIDE_32;
    }
    else if (kVal == CT_ODU_Layer3)
    {
        //ODU3 is the server
        theServerPort = CT_PORT_SIDE_33;
    }
    else if (kVal == CT_ODU_Layer4)
    {
        //ODU4 is the server
        theServerPort = CT_PORT_SIDE_34;
    }

    return theServerPort;
}

uint16 SP_OduKSnc::GetTSPIIOduKIndex(CT_ODU_Identifier aOduIdentifier)
{
    uint16 aTmpInstance = CT_DEFAULT_ODU_POSITION;
    uint8 kVal = aOduIdentifier.GetOduKvalue();
    if (kVal == CT_ODU_Layer0 || kVal == CT_ODU_LayerF)
    {
        aTmpInstance = TSPII_SubApplication::GetInstance()->GetOdu0PoolIndex(aOduIdentifier.GetIdValue());
    }
    else if (kVal == CT_ODU_Layer1)
    {
        aTmpInstance = TSPII_SubApplication::GetInstance()->GetOdu1PoolIndex(aOduIdentifier.GetIdValue());
    }
    else if (kVal == CT_ODU_Layer2)
    {
        aTmpInstance = TSPII_SubApplication::GetInstance()->GetOdu2PoolIndex(aOduIdentifier.GetIdValue());
    }
    else if (kVal == CT_ODU_Layer3)
    {
        aTmpInstance = TSPII_SubApplication::GetInstance()->GetOdu3PoolIndex(aOduIdentifier.GetIdValue());
    }
    else if (kVal == CT_ODU_Layer4)
    {
        aTmpInstance = TSPII_SubApplication::GetInstance()->GetOdu4PoolIndex(aOduIdentifier.GetIdValue());
    }

    return aTmpInstance;

}

void SP_OduKSnc::AddPortMapping(CT_IntfId thePort, unsigned int tspiiPort, bool isOduType)
{
    unsigned int iPort = (unsigned int)thePort;
    if (isOduType)
    {
        iPort += (unsigned int)CT_INTF_ID_UNKNOWN + 1;
    }
    myPortMap.insert(SP_PortMap::value_type(iPort, tspiiPort));
}

unsigned int SP_OduKSnc::GetTspiiPort(CT_IntfId thePort, bool isOduType)
{
    unsigned int iPort = (unsigned int)thePort;
    if (isOduType)
    {
        iPort += (unsigned int)CT_INTF_ID_UNKNOWN + 1;
    }
    SP_PortMap::iterator it;
    //map<unsigned int,unsigned int>::iterator it;
    it = myPortMap.find(iPort);
    if (it != myPortMap.end())
        return ((*it).second);

    return 0;
}

int SP_OduKSnc::GetIndex(CT_SP_Protection theSide)
{
    if (theSide == CT_SP_WORKING_SIDE)
        return myLayerIdx.working;
    else
        return myLayerIdx.protection;
}

void SP_OduKSnc::GetAlmAppIf(uint32 theOduIdentifier, SP_AlmAppIfCollection& theAlmIfCollection)
{
    CT_ODU_Identifier aOduIdentifier (theOduIdentifier);

    CT_IntfId thePort = GetClientOduKPort(aOduIdentifier);
    if (mySourcesLocal.working)
    {
        if ((uint32)myProtectionAction.Get1plus1Config().GetSources().working.GetPortId() == theOduIdentifier)
        {
            theAlmIfCollection.push_back ( &(myApplIf.GetCardContext().GetOduIf().GetAlmPortSideApp(thePort)));
        }
    }

    if (mySourcesLocal.protection)
    {
        if ((uint32)myProtectionAction.Get1plus1Config().GetSources().protection.GetPortId() == theOduIdentifier)
        {
            theAlmIfCollection.push_back ( &(myApplIf.GetCardContext().GetOduIf().GetAlmPortSideApp(thePort)));
        }

    }
    
}

bool SP_OduKSnc::AreDependenciesReady(SP_ProtectionGroupConfig& theConfig)
{
    bool isReady = true;
    int theIdx = -1;
    bool theDC = false;
    SP_1plus1ProtectionGroupConfig & config = static_cast<SP_1plus1ProtectionGroupConfig&> (theConfig);
    if (config.GetSources().working.GetShelfId() == myShelfId &&
        config.GetSources().working.GetSlotId() == mySlotId)
    {
        if (FindClientAndServerLayers(CT_SP_WORKING_SIDE, (uint32)config.GetSources().working.GetPortId(), false) == false)
        {
            isReady = false;
        }

        EvaluateConnectionPattern(CT_SP_WORKING_SIDE, (uint32)config.GetSources().working.GetPortId(), false, &theIdx, &theDC);
        if (theIdx == -1)
        {
            isReady = false;
        }

        if (config.Get1plus1Type() == CT_SP_SNCS)
        {
            if (FindTcmLayers(CT_SP_WORKING_SIDE, (uint32)config.GetSources().working.GetPortId(), false) == false)
            {
                isReady = false;
            }
        }
    }

    if (config.GetSources().protection.GetShelfId() == myShelfId &&
        config.GetSources().protection.GetSlotId() == mySlotId)
    {
        if (FindClientAndServerLayers(CT_SP_PROTECTION_SIDE, (uint32)config.GetSources().protection.GetPortId(), false) == false)
        {
            isReady = false;
        }
        EvaluateConnectionPattern(CT_SP_PROTECTION_SIDE, (uint32)config.GetSources().protection.GetPortId(), false, &theIdx, &theDC);
        if (theIdx == -1)
        {
            isReady = false;
        }

        if (config.Get1plus1Type() == CT_SP_SNCS)
        {
            if (FindTcmLayers(CT_SP_PROTECTION_SIDE, (uint32)config.GetSources().protection.GetPortId(), false) == false)
            {
                isReady = false;
            }
        }
    }

    return isReady;
}

bool SP_OduKSnc::ManageInputRegions(CT_SP_Protection theSide, bool addInput, bool removeInput, bool checkInput)
{
    bool result = false;
    CT_IntfId theServerLayerPort = CT_INTF_ID_UNKNOWN;
    CT_IntfId theClientLayerPort = CT_INTF_ID_UNKNOWN;
    CT_IntfId theOTUkPort        = CT_INTF_ID_UNKNOWN;
    SP_SncServerLayer theServerLayerType = Server_Layer_None;
    uint32 serverRefCount =0;
    uint32 otuRefCount =0;
    uint32 clientRefCount = 0;
    bool processServer = false;
    bool processOtu = false;
    bool processClient = false;

    if (theSide == CT_SP_WORKING_SIDE)
    {
        theServerLayerPort = myServerLayerPort.working;
        theServerLayerType = myServerLayerType.working;
        theClientLayerPort = myLayerPort.working;
        theOTUkPort        = myOtuKPort.working;
    }
    else
    {
        theServerLayerPort = myServerLayerPort.protection;
        theServerLayerType = myServerLayerType.protection;
        theClientLayerPort = myLayerPort.protection;
        theOTUkPort        = myOtuKPort.protection;
    }

    //Check for ODU server port(excluding OTU port)
    //If already in the map, it means input regions were mapped previously
    //If doing a delete, decrement the reference count and if the count reaches zero
    //then remove the input region assocation
    if(theServerLayerPort!=theOTUkPort)
    {
        SP_PortMap::iterator serverIt;
        serverIt = myServerObserveMap.find((unsigned int)theServerLayerPort);
        if (serverIt != myServerObserveMap.end())
        {
            serverRefCount = (*serverIt).second;
            if (addInput)
            {
                serverRefCount++;
                (*serverIt).second = serverRefCount;
            }
            else if (removeInput)
            {
                serverRefCount--;
                if (serverRefCount == 0)
                {
                    myServerObserveMap.erase(serverIt);
                    processServer = true;
                }
                else
                {
                    (*serverIt).second = serverRefCount;
                }
            }
        }
        else
        {
            //Not in the map
            //If adding input regions, then add to the map so that future adds do not do the same thing
            if (addInput)
            {
                processServer = true;
                myServerObserveMap.insert(SP_PortMap::value_type((unsigned int)theServerLayerPort, 1));
            }
        }
    }

    //Check for OTU port
    //If already in the map, it means input regions were mapped previously
    //If doing a delete, decrement the reference count and if the count reaches zero
    //then remove the input region assocation
    SP_PortMap::iterator otuIt;
    otuIt = myOtuObserveMap.find((unsigned int)theOTUkPort);
    if (otuIt != myOtuObserveMap.end())
    {
        otuRefCount = (*otuIt).second;
        if (addInput)
        {
            otuRefCount++;
            (*otuIt).second = otuRefCount;
        }
        else if (removeInput)
        {
            otuRefCount--;
            if (otuRefCount == 0)
            {
                myOtuObserveMap.erase(otuIt);
                processOtu = true;
            }
            else
            {
                (*otuIt).second = otuRefCount;
            }
        }
    }
    else
    {
        //Not in the map
        //If adding input regions, then add to the map so that future adds do not do the same thing
        if (addInput)
        {
            processOtu = true;
            myOtuObserveMap.insert(SP_PortMap::value_type((unsigned int)theOTUkPort, 1));
        }
    }


    //Check for client port
    //If already in the map, it means input regions were mapped previously
    //If doing a delete, decrement the reference count and if the count reaches zero
    //then remove the input region assocation
    SP_PortMap::iterator clientIt;
    clientIt = myClientObserveMap.find((unsigned int)theClientLayerPort);
    if (clientIt != myClientObserveMap.end())
    {
        clientRefCount = (*clientIt).second;
        if (addInput)
        {
            clientRefCount++;
            (*clientIt).second = clientRefCount;
        }
        else if (removeInput)
        {
            clientRefCount--;
            if (clientRefCount == 0)
            {
                myClientObserveMap.erase(clientIt);
                processClient = true;
            }
            else
            {
                (*clientIt).second = clientRefCount;
            }
        }
    }
    else
    {
        //Not in the map
        //If adding input regions, then add to the map so that future adds do not do the same thing
        if (addInput)
        {
            processClient = true;
            myClientObserveMap.insert(SP_PortMap::value_type((unsigned int)theClientLayerPort, 1));
        }
    }

    if (checkInput)
    {
        processServer = true;
        processOtu = true;
        processClient = true;
    }

    //If server is OTUk
    //Add MON OPT config, OTU CONFIG, OTU DEFECTS

    //If server is ODUk
    //Add MON ODU config, ODU Defect
    if (processServer == true)
    {
        if (addInput)
        {
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theServerLayerPort).GetDefectsRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theServerLayerPort).GetConfigRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
        }
        else if (removeInput)
        {
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theServerLayerPort).GetDefectsRegion());
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theServerLayerPort).GetConfigRegion());
        }
        else if (checkInput)
        {
            if (myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theServerLayerPort).GetDefectsRegion()->IsValid() &&
                myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theServerLayerPort).GetConfigRegion()->IsValid())
            {
                result |= true;
            }

        }
    }

    //Add MON OTU config, OPT Defect
    if (processOtu == true)
    {
        if (addInput)
        {
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(theOTUkPort).GetDefectsRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(theOTUkPort).GetConfigRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetOptIf().GetMonPortSideApp(theOTUkPort).GetConfigRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
        }
        else if (removeInput)
        {
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(theOTUkPort).GetDefectsRegion());
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(theOTUkPort).GetConfigRegion());
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetOptIf().GetMonPortSideApp(theOTUkPort).GetConfigRegion());
        }
        else if (checkInput)
        {
            if (myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(theOTUkPort).GetDefectsRegion()->IsValid() &&
                myApplIf.GetCardContext().GetOtuIf().GetMonPortSideApp(theOTUkPort).GetConfigRegion()->IsValid() &&
                myApplIf.GetCardContext().GetOptIf().GetMonPortSideApp(theOTUkPort).GetConfigRegion()->IsValid())
            {
                result |= true;
            }
        }
    }

    //Client MON ODU config
    if (processClient == true)
    {
        if (addInput)
        {
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theClientLayerPort).GetConfigRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
        }
        else if (removeInput)
        {
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theClientLayerPort).GetConfigRegion());
        }
        else if (checkInput)
        {
            if (myApplIf.GetCardContext().GetOduIf().GetMonPortSideApp(theClientLayerPort).GetConfigRegion()->IsValid())
            {
                result |= true;
            }
        }
    }


    return result;
}

bool SP_OduKSnc::ManageTcmInputRegions(CT_SP_Protection theSide, bool addInput, bool removeInput, bool checkInput)
{
    bool result = false;
    CT_IntfId theTcmPort = SP_TCM_PORT_ID;
    uint32 tcmRefCount =0;
    bool processTcm = false;
    
    //Check for server port
    //If already in the map, it means input regions were mapped previously
    //If doing a delete, decrement the reference count and if the count reaches zero
    //then remove the input region assocation
    SP_PortMap::iterator tcmIt;
    tcmIt = myTcmObserveMap.find((unsigned int)theTcmPort);
    if (tcmIt != myTcmObserveMap.end())
    {
        tcmRefCount = (*tcmIt).second;
        if (addInput)
        {
            tcmRefCount++;
            (*tcmIt).second = tcmRefCount;
        }
        else if (removeInput)
        {
            tcmRefCount--;
            if (tcmRefCount == 0)
            {
                myTcmObserveMap.erase(tcmIt);
                processTcm = true;
            }
            else
            {
                (*tcmIt).second = tcmRefCount;
            }
        }
    }
    else
    {
        //Not in the map
        //If adding input regions, then add to the map so that future adds do not do the same thing
        if (addInput)
        {
            processTcm = true;
            myTcmObserveMap.insert(SP_PortMap::value_type((unsigned int)theTcmPort, 1));
        }
    }

    if (checkInput)
    {
        processTcm = true;
    }

    //MON TCM config
    if (processTcm == true)
    {
        if (addInput)
        {
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetConfigRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
            myProtectionAction.GetBbAction()->AddInputRegion(myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetDefectsRegion(), true, true, true, FC_BbRegObsPriority::HIGH);
        }
        else if (removeInput)
        {
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetConfigRegion());
            myProtectionAction.GetBbAction()->RemoveInputRegion(myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetDefectsRegion());
        }
        else if (checkInput)
        {
            if ( myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetConfigRegion()->IsValid() &&
                 myApplIf.GetCardContext().GetTcmIf().GetMonPortSideApp(SP_TCM_PORT_ID).GetDefectsRegion()->IsValid() )
            {
                result |= true;
            }
        }
    }


    return result;
}

FC_Milliseconds SP_OduKSnc::GetSncWTROffset()
{
    //On a dual card SNC add a WTR offset to the protect card
    //so that the working card WTR expires prior to the protect card.
    if (mySourcesLocal.working &&
        mySourcesLocal.protection)
    {
        //Both sources local, no offset.
        return 0;
    }
    else
    {
        if (mySourcesLocal.protection == true)
        {
            return (2*1000);
        }

        return 0; //Working card, no offset added
    }
}

void SP_OduKSnc::SetXcRegions(TSXC_S1RtRegion<TSXC_S1Route>*   theXCRouteCfgRegion, TSXC_MCastFilterRegion<TSXC_MCastFilter>*  theMCFilterRegion)
{
    myXCRouteCfgRegion = theXCRouteCfgRegion;
    myMCFilterRegion = theMCFilterRegion;
}

void SP_OduKSnc::SetCfgMiscRegion(CFG_MiscCfgRegion* theCfgSwitchModeRegion)
{
    myCfgSwitchModeRegion = theCfgSwitchModeRegion;
}


void SP_OduKSnc::ResetData()
{
    ConfigureLogicalShelfId(false, myShelfId, myShelfId);
    //Clear out pqw channel information
    myPQWChannels.working = myPQWChannels.protection = INVALID_PQW_CHANNEL;
    mySourcesLocal.working = mySourcesLocal.protection = false;
    myDC.working = myDC.protection = false;
    myTxMsg.working = myTxMsg.protection =0;
    myMatePortOf.working.Reset();
    myMatePortOf.protection.Reset();
    myPrevSelSwitchDir.working = myPrevSelSwitchDir.protection = SP_SEL_SWITCH_DIR_UNKNOWN;
    myXcIndex.working = myXcIndex.protection = -1;
    myUserCommandIsPending = false;
    myServerLayerPort.working = myServerLayerPort.protection = CT_INTF_ID_UNKNOWN;
    myTwoStageTopServerLayerPort.working = myTwoStageTopServerLayerPort.protection = CT_INTF_ID_UNKNOWN;
    myServerLayerIdx.working = myServerLayerIdx.protection = -1;
    myTwoStageTopServerLayerIdx.working = myTwoStageTopServerLayerIdx.protection = -1;
    myServerLayerType.working = myServerLayerType.protection = Server_Layer_None;
    myTwoStageTopServerLayerType.working = myTwoStageTopServerLayerType.protection = Server_Layer_None;
    myServerLayerOduId.working = myServerLayerOduId.protection = CT_DEFAULT_ODU_ID;
    myTwoStageTopServerLayerOduId.working = myTwoStageTopServerLayerOduId.protection = CT_DEFAULT_ODU_ID;
    myServerTspiiIdx.working = myServerTspiiIdx.protection = CT_DEFAULT_ODU_POSITION;
    myTwoStageTopServerTspiiIdx.working = myTwoStageTopServerTspiiIdx.protection = CT_DEFAULT_ODU_POSITION;
    myServerTspiiPort.working = myServerTspiiPort.protection = 0;
    myTwoStageTopServerTspiiPort.working = myTwoStageTopServerTspiiPort.protection = 0;
    myLayerPort.working = myLayerPort.protection = CT_INTF_ID_UNKNOWN;
    myLayerIdx.working = myLayerIdx.protection = -1;
    myTspiiOduIdx.working = myTspiiOduIdx.protection = CT_DEFAULT_ODU_POSITION;
    myTspiiOduPort.working = myTspiiOduPort.protection = 0;
    myOtuKPort.working = myOtuKPort.protection = CT_INTF_ID_UNKNOWN;
    myOtuKIdx.working = myOtuKIdx.protection = -1;
    myServerLinkageId.working = myServerLinkageId.protection = CT_DEFAULT_ODU_SERVER_ID;
    myTcmId.working = myTcmId.protection = CT_DEFAULT_ODU_ID;
    myTcmIdx.working = myTcmIdx.protection = -1;
    myTspiiTcmIdx.working = myTspiiTcmIdx.protection = CT_DEFAULT_ODU_POSITION;
    myIsConfigured = false;
    //PQW Debug Info
    myTxPQM.working = myTxPQM.protection =0;
    myTxSFH.working = myTxSFH.protection =0;
    myTxSFL.working = myTxSFL.protection =0;
    myTxSD.working = myTxSD.protection =0;
    myTxPQWInvalid.working = myTxPQWInvalid.protection =0;
    myTxHWSquelch.working = myTxHWSquelch.protection =0;
    myRxPQM.working = myRxPQM.protection =0;
    myRxSFH.working = myRxSFH.protection =0;
    myRxSFL.working = myRxSFL.protection =0;
    myRxSD.working = myRxSD.protection =0;
    myRxPQWInvalid.working = myRxPQWInvalid.protection =0;
    myRxHWSquelch.working = myRxHWSquelch.protection =0;
    myDefectStatus.working=myDefectStatus.protection=0;
    //SwitchParams Debug Info
    mySwitchingAllowed = false;
    myUserCmdMsg = 0;
    myWDir = SP_SEL_SWITCH_DIR_UNKNOWN;
    myPDir= SP_SEL_SWITCH_DIR_UNKNOWN;
    mySendMessage = false;
    myMateActive = false;
    myCurrentSelection = CT_SP_INVALID_PROTECTION_SIDE;

    myTxApsBytes = 0;

}


void SP_OduKSnc::DumpData()
{
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
    uint16 txMsg;
    uint16 rxMsg;
    fc_cout <<     "Is Configured    : " << DISPLAY_BOOL(myIsConfigured) <<endl;
    fc_cout <<     "UserCmdPend      : " << DISPLAY_BOOL(myUserCommandIsPending) <<endl;
    fc_cout <<     "Mate Logical Id  : ";
    fc_cout << (uint32) myMateLogicalShelf;
    fc_cout <<endl;

    if (mySourcesLocal.working == true)
    {
        fc_cout << endl;
        fc_cout << "**********WORKING ODUk DATA*******************" << endl;
        txMsg = theSncIf.GetTxPQM(myPQWChannels.working);
        rxMsg = theSncIf.GetRxPQM(myPQWChannels.working); 
        fc_cout <<     "SW TX PQW        : " << txMsg << endl; 
        fc_cout <<     "TX SF_HIGH PQW   : " << DISPLAY_BOOL(GetTxSFHigh(myPQWChannels.working)) <<endl; 
        fc_cout <<     "TX SF_LOW PQW    : " << DISPLAY_BOOL(GetTxSFLow(myPQWChannels.working)) <<endl;        
        fc_cout <<     "TX SD PQW        : " << DISPLAY_BOOL(GetTxSD(myPQWChannels.working)) <<endl;  
        fc_cout <<endl; 
        fc_cout <<     "SW RX PQW        : " << rxMsg << endl; 
        fc_cout <<     "RX PQW VALID     : " << DISPLAY_BOOL( ((rxMsg & SP_PQW_MSG_VALID) == SP_PQW_MSG_VALID) ) <<endl;
        fc_cout <<     "HW MATE SRC ENAB : " << DISPLAY_BOOL( (theSncIf.GetRxHwPQWSquelch(myPQWChannels.working) == false) ) <<endl; 
        fc_cout <<     "SW MATE SRC ENAB : " << DISPLAY_BOOL( ((rxMsg & SP_PQW_SRC_ENABLED) == SP_PQW_SRC_ENABLED) ) <<endl;  
        fc_cout <<     "RX SF_HIGH PQW   : "  << DISPLAY_BOOL(GetRxSFHigh(CT_SP_WORKING_SIDE, myPQWChannels.working)) <<endl; 
        fc_cout <<     "RX SF_LOW PQW    : "  << DISPLAY_BOOL(GetRxSFLow(myPQWChannels.working)) <<endl;  
        fc_cout <<     "RX SD PQW        : "  << DISPLAY_BOOL(GetRxSD(myPQWChannels.working)) <<endl;   
        fc_cout <<endl; 
        fc_cout <<     "FPP Enabled      : " << DISPLAY_BOOL(theSncIf.GetFppEnabled(myPQWChannels.working)) <<endl;
        fc_cout <<     "Auto Squelch Ena : " << DISPLAY_BOOL(theSncIf.GetFppSquelchEnabled(myPQWChannels.working)) <<endl;
        fc_cout <<     "Squelch HoldOff  : " << theSncIf.GetSquelchHoldOffDelay(myPQWChannels.working) <<endl;
        fc_cout <<     "Mate Mod Present : " << DISPLAY_BOOL(GetMateModPresence(CT_SP_WORKING_SIDE)) <<endl;
        fc_cout <<     "PQW Channel      : " << (uint32) myPQWChannels.working <<endl; 
        fc_cout <<     "Source Local     : " << (uint32) mySourcesLocal.working <<endl; 
        fc_cout <<     "DC               : " << (uint32) myDC.working <<endl; 
        fc_cout <<     "Xc Index         : " << myXcIndex.working << endl;
        fc_cout <<     "Tx Msg           : " << (uint32) myTxMsg.working <<endl; 
        fc_cout <<endl; 
        fc_cout <<     "Server Port      : " << DISPLAY_CT_IntfId(myServerLayerPort.working) <<endl;
        fc_cout <<     "TwoStageTopServer Port      : " << DISPLAY_CT_IntfId(myTwoStageTopServerLayerPort.working) <<endl;
        fc_cout <<     "Server Idx       : " << (int) myServerLayerIdx.working <<endl; 
        fc_cout <<     "TwoStageTopServer Idx       : " << (int) myTwoStageTopServerLayerIdx.working <<endl; 
        fc_cout <<     "Server Type      : " << DISPLAY_SNC_SERVER_LAYER_TYPE(myServerLayerType.working) <<endl;
        fc_cout <<     "TwoStageTopServer Type      : " << DISPLAY_SNC_SERVER_LAYER_TYPE(myTwoStageTopServerLayerType.working) <<endl;
        fc_cout <<     "Server OduId     : " << myServerLayerOduId.working.GetIdValue() <<endl;
        fc_cout <<     "TwoStageTopServer OduId     : " << myTwoStageTopServerLayerOduId.working.GetIdValue() <<endl;
        fc_cout <<     "Server Tsp Port  : " << (int) myServerTspiiPort.working <<endl; 
        fc_cout <<     "TwoStageTopServer Tsp Port  : " << (int) myTwoStageTopServerTspiiPort.working <<endl; 
        fc_cout <<     "Server Tsp Idx   : " << (int) myServerTspiiIdx.working <<endl; 
        fc_cout <<     "TwoStageTopServer Tsp Idx   : " << (int) myTwoStageTopServerTspiiIdx.working <<endl; 
        fc_cout <<     "OtuK Port        : " << DISPLAY_CT_IntfId(myOtuKPort.working) <<endl;
        fc_cout <<     "OtuK Idx         : " << (int) myOtuKIdx.working <<endl; 
        fc_cout <<     "Port             : " << DISPLAY_CT_IntfId(myLayerPort.working) <<endl;
        fc_cout <<     "Idx              : " << (int) myLayerIdx.working <<endl; 
        fc_cout <<     "Tsp Port         : " << (int) myTspiiOduPort.working <<endl; 
        fc_cout <<     "Tsp Idx          : " << (int) myTspiiOduIdx.working <<endl; 
        fc_cout <<endl; 
        fc_cout <<     "Linkage Id       : " << (uint32) myServerLinkageId.working.GetIdValue() <<endl; 
        fc_cout <<     "Tcm Id           : " << (uint32) myTcmId.working.GetIdValue() <<endl; 
        fc_cout <<     "Tcm Idx          : " << (int) myTcmIdx.working <<endl; 
        fc_cout <<     "Tcm Tsp Idx      : " << (int) myTspiiTcmIdx.working <<endl; 
        fc_cout <<endl; 
        fc_cout <<     "PrevSelSwitchDir : " << DISPLAY_SNC_SEL_SWITCH_DIR(myPrevSelSwitchDir.working) << endl; 
    }
    else
    {
        fc_cout << endl;
        fc_cout << "**********WORKING ODUk DATA*******************" << endl;
        fc_cout << "WORKING ODUk IS NOT ON THIS CARD" << endl;
    }
    if (mySourcesLocal.protection == true)
    {
        fc_cout << endl;
        fc_cout << "**********PROTECT ODUk DATA*******************" << endl;
        txMsg = theSncIf.GetTxPQM(myPQWChannels.protection);
        rxMsg = theSncIf.GetRxPQM(myPQWChannels.protection); 
        fc_cout <<     "SW TX PQW        : " << txMsg << endl; 
        fc_cout <<     "TX SF_HIGH PQW   : " << DISPLAY_BOOL(GetTxSFHigh(myPQWChannels.protection)) <<endl; 
        fc_cout <<     "TX SF_LOW PQW    : " << DISPLAY_BOOL(GetTxSFLow(myPQWChannels.protection)) <<endl;        
        fc_cout <<     "TX SD PQW        : " << DISPLAY_BOOL(GetTxSD(myPQWChannels.protection)) <<endl;  
        fc_cout <<endl; 
        fc_cout <<     "SW RX PQW        : " << rxMsg << endl; 
        fc_cout <<     "RX PQW VALID     : " << DISPLAY_BOOL( ((rxMsg & SP_PQW_MSG_VALID) == SP_PQW_MSG_VALID) ) <<endl;
        fc_cout <<     "HW MATE SRC ENAB : " << DISPLAY_BOOL( (theSncIf.GetRxHwPQWSquelch(myPQWChannels.protection) == false) ) <<endl; 
        fc_cout <<     "SW MATE SRC ENAB : " << DISPLAY_BOOL( ((rxMsg & SP_PQW_SRC_ENABLED) == SP_PQW_SRC_ENABLED) ) <<endl;  
        fc_cout <<     "RX SF_HIGH PQW   : "  << DISPLAY_BOOL(GetRxSFHigh(CT_SP_PROTECTION_SIDE, myPQWChannels.protection)) <<endl; 
        fc_cout <<     "RX SF_LOW PQW    : "  << DISPLAY_BOOL(GetRxSFLow(myPQWChannels.protection)) <<endl;  
        fc_cout <<     "RX SD PQW        : "  << DISPLAY_BOOL(GetRxSD(myPQWChannels.protection)) <<endl;   
        fc_cout <<endl; 
        fc_cout <<     "FPP Enabled      : " << DISPLAY_BOOL(theSncIf.GetFppEnabled(myPQWChannels.protection)) <<endl;
        fc_cout <<     "Auto Squelch Ena : " << DISPLAY_BOOL(theSncIf.GetFppSquelchEnabled(myPQWChannels.protection)) <<endl;
        fc_cout <<     "Squelch HoldOff  : " << theSncIf.GetSquelchHoldOffDelay(myPQWChannels.protection) <<endl;
        fc_cout <<     "Mate Mod Present : " << DISPLAY_BOOL(GetMateModPresence(CT_SP_PROTECTION_SIDE)) <<endl;
        fc_cout <<     "PQW Channel      : " << (uint32) myPQWChannels.protection <<endl; 
        fc_cout <<     "Source Local     : " << (uint32) mySourcesLocal.protection <<endl; 
        fc_cout <<     "DC               : " << (uint32) myDC.protection <<endl; 
        fc_cout <<     "Xc Index         : " << myXcIndex.protection << endl;
        fc_cout <<     "Tx Msg           : " << (uint32) myTxMsg.protection <<endl; 
        fc_cout <<endl; 
        fc_cout <<     "Server Port      : " << DISPLAY_CT_IntfId(myServerLayerPort.protection) <<endl;
        fc_cout <<     "TwoStageTopServer Port      : " << DISPLAY_CT_IntfId(myTwoStageTopServerLayerPort.protection) <<endl;
        fc_cout <<     "Server Idx       : " << (int) myServerLayerIdx.protection <<endl; 
        fc_cout <<     "TwoStageTopServer Idx       : " << (int) myTwoStageTopServerLayerIdx.protection <<endl; 
        fc_cout <<     "Server Type      : " << DISPLAY_SNC_SERVER_LAYER_TYPE(myServerLayerType.protection) <<endl;
        fc_cout <<     "TwoStageTopServer Type      : " << DISPLAY_SNC_SERVER_LAYER_TYPE(myTwoStageTopServerLayerType.protection) <<endl;
        fc_cout <<     "Server OduId     : " << myServerLayerOduId.protection.GetIdValue() <<endl;
        fc_cout <<     "TwoStageTopServer OduId     : " << myTwoStageTopServerLayerOduId.protection.GetIdValue() <<endl;
        fc_cout <<     "Server Tsp Port  : " << (int) myServerTspiiPort.protection <<endl; 
        fc_cout <<     "TwoStageTopServer Tsp Port  : " << (int) myTwoStageTopServerTspiiPort.protection <<endl; 
        fc_cout <<     "Server Tsp Idx   : " << (int) myServerTspiiIdx.protection <<endl; 
        fc_cout <<     "TwoStageTopServer Tsp Idx   : " << (int) myTwoStageTopServerTspiiIdx.protection <<endl; 
        fc_cout <<     "OtuK Port        : " << DISPLAY_CT_IntfId(myOtuKPort.protection) <<endl;
        fc_cout <<     "OtuK Idx         : " << (int) myOtuKIdx.protection <<endl; 
        fc_cout <<     "Port             : " << DISPLAY_CT_IntfId(myLayerPort.protection) <<endl;
        fc_cout <<     "Idx              : " << (int) myLayerIdx.protection <<endl; 
        fc_cout <<     "Tsp Port         : " << (int) myTspiiOduPort.protection <<endl; 
        fc_cout <<     "Tsp Idx          : " << (int) myTspiiOduIdx.protection <<endl; 
        fc_cout <<endl; 
        fc_cout <<     "Linkage Id       : " << (uint32) myServerLinkageId.protection.GetIdValue() <<endl; 
        fc_cout <<     "Tcm Id           : " << (uint32) myTcmId.protection.GetIdValue() <<endl; 
        fc_cout <<     "Tcm Idx          : " << (int) myTcmIdx.protection <<endl; 
        fc_cout <<     "Tcm Tsp Idx      : " << (int) myTspiiTcmIdx.protection <<endl; 
        fc_cout <<endl; 
        fc_cout <<     "PrevSelSwitchDir : " << DISPLAY_SNC_SEL_SWITCH_DIR(myPrevSelSwitchDir.protection) << endl; 
    }
    else
    {
        fc_cout << endl;
        fc_cout << "**********PROTECT ODUk DATA*******************" << endl;
        fc_cout << "PROTECT ODUk IS NOT ON THIS CARD" << endl;
    }
}

void SP_OduKSnc::DispPQW()
{
    TSPII_SncRegion * theSncRegion = TSPII_SubApplication::GetInstance()->GetSnc();
    TSPII_SncIf& theSncIf = static_cast<TSPII_SncIf&> ((*theSncRegion)[0]);
    CT_SP_ProtectionPair<uint16> txPQM;
    CT_SP_ProtectionPair<uint8>  txSFH;
    CT_SP_ProtectionPair<uint8>  txSFL;
    CT_SP_ProtectionPair<uint8>  txSD;
    CT_SP_ProtectionPair<uint8>  txPQWInvalid;
    CT_SP_ProtectionPair<uint8>  txHWSquelch;
    CT_SP_ProtectionPair<uint16> rxPQM;
    CT_SP_ProtectionPair<uint8>  rxSFH;
    CT_SP_ProtectionPair<uint8>  rxSFL;
    CT_SP_ProtectionPair<uint8>  rxSD;
    CT_SP_ProtectionPair<uint8>  rxPQWInvalid;
    CT_SP_ProtectionPair<uint8>  rxHWSquelch;
    CT_SP_ProtectionPair<uint16> defectStatus;

    if (mySourcesLocal.working == true)
    {
        bool bChanged=false;
        txPQM.working = theSncIf.GetTxPQM(myPQWChannels.working);
        txSFH.working = theSncIf.GetTxSFHigh(myPQWChannels.working)%2;
        txSFL.working = theSncIf.GetTxSFLow(myPQWChannels.working)%2;
        txSD.working = theSncIf.GetTxSD(myPQWChannels.working)%2;
        txPQWInvalid.working = (theSncIf.GetTxPQWInvalid(myPQWChannels.working) ? 1:0);
        txHWSquelch.working = (theSncIf.GetTxHwPQWSquelch(myPQWChannels.working) ? 1:0);
        rxPQM.working = theSncIf.GetRxPQM(myPQWChannels.working); 
        rxSFH.working = theSncIf.GetRxSFHigh(myPQWChannels.working)%2;
        rxSFL.working = theSncIf.GetRxSFLow(myPQWChannels.working)%2;
        rxSD.working = theSncIf.GetRxSD(myPQWChannels.working)%2;
        rxPQWInvalid.working = (theSncIf.GetRxPQWInvalid(myPQWChannels.working) ? 1:0);
        rxHWSquelch.working = (theSncIf.GetRxHwPQWSquelch(myPQWChannels.working) ? 1:0);
        defectStatus.working = myProtectionAction.myRequestParserPtr->GetDefectStatus().working;
        if (txPQM.working != myTxPQM.working)
        {
            myTxPQM.working = txPQM.working;
            bChanged = true;
        }
        if (txSFH.working != myTxSFH.working) 
        {
            myTxSFH.working = txSFH.working;
            bChanged = true;
        }
        if (txSFL.working != myTxSFL.working) 
        {
            myTxSFL.working = txSFL.working;
            bChanged = true;
        }
        if (txSD.working != myTxSD.working) 
        {
            myTxSD.working = txSD.working;
            bChanged = true;
        }
        if (txPQWInvalid.working != myTxPQWInvalid.working) 
        {
            myTxPQWInvalid.working = txPQWInvalid.working;
            bChanged = true;
        }
        if (txHWSquelch.working != myTxHWSquelch.working) 
        {
            myTxHWSquelch.working = txHWSquelch.working;
            bChanged = true;
        }
        if (rxPQM.working != myRxPQM.working)
        {
            myRxPQM.working = rxPQM.working;
            bChanged = true;
        }
        if (rxSFH.working != myRxSFH.working) 
        {
            myRxSFH.working = rxSFH.working;
            bChanged = true;
        }
        if (rxSFL.working != myRxSFL.working) 
        {
            myRxSFL.working = rxSFL.working;
            bChanged = true;
        }
        if (rxSD.working != myRxSD.working) 
        {
            myRxSD.working = rxSD.working;
            bChanged = true;
        }
        if (rxPQWInvalid.working != myRxPQWInvalid.working) 
        {
            myRxPQWInvalid.working = rxPQWInvalid.working;
            bChanged = true;
        }
        if (rxHWSquelch.working != myRxHWSquelch.working) 
        {
            myRxHWSquelch.working = rxHWSquelch.working;
            bChanged = true;
        }
        if (defectStatus.working != myDefectStatus.working) 
        {
            myDefectStatus.working = defectStatus.working;
            bChanged = true;
        }
        if ( bChanged )
        {
            fc_cout << "W Tx: PQM=" << uint32(myTxPQM.working);
            fc_cout << " SFH=" << uint32(myTxSFH.working);            
            fc_cout << " SFL=" << uint32(myTxSFL.working);
            fc_cout << " SD=" << uint32(myTxSD.working);
            fc_cout << " Invld=" << uint32(myTxPQWInvalid.working);
            fc_cout << " Sql=" << uint32(myTxHWSquelch.working);
            fc_cout << " Rx: PQM=" << uint32(myRxPQM.working);
            fc_cout << " SFH=" << uint32(myRxSFH.working);
            fc_cout << " SFL=" << uint32(myRxSFL.working);
            fc_cout << " SD=" << uint32(myRxSD.working);
            fc_cout << " Invld=" << uint32(myRxPQWInvalid.working);
            fc_cout << " Sql=" << uint32(myRxHWSquelch.working);
            fc_cout << " Dft=" << uint32(myDefectStatus.working);
            fc_cout << " odu=" << uint32(myTspiiOduIdx.working);
            fc_cout << " pqw=" << uint32(myPQWChannels.working);
            fc_cout << endl;
        }
    }
    if (mySourcesLocal.protection == true)
    {
        bool bChanged=false;
        txPQM.protection = theSncIf.GetTxPQM(myPQWChannels.protection);
        txSFH.protection = theSncIf.GetTxSFHigh(myPQWChannels.protection)%2;
        txSFL.protection = theSncIf.GetTxSFLow(myPQWChannels.protection)%2;
        txSD.protection = theSncIf.GetTxSD(myPQWChannels.protection)%2;
        txPQWInvalid.protection = (theSncIf.GetTxPQWInvalid(myPQWChannels.protection) ? 1:0);
        txHWSquelch.protection = (theSncIf.GetTxHwPQWSquelch(myPQWChannels.protection) ? 1:0);
        rxPQM.protection = theSncIf.GetRxPQM(myPQWChannels.protection);
        rxSFH.protection = theSncIf.GetRxSFHigh(myPQWChannels.protection)%2;
        rxSFL.protection = theSncIf.GetRxSFLow(myPQWChannels.protection)%2;
        rxSD.protection = theSncIf.GetRxSD(myPQWChannels.protection)%2;
        rxPQWInvalid.protection = (theSncIf.GetRxPQWInvalid(myPQWChannels.protection) ? 1:0);
        rxHWSquelch.protection = (theSncIf.GetRxHwPQWSquelch(myPQWChannels.protection) ? 1:0);
        defectStatus.protection = myProtectionAction.myRequestParserPtr->GetDefectStatus().protection;
        if (txPQM.protection != myTxPQM.protection)
        {
            myTxPQM.protection = txPQM.protection;
            bChanged = true;
        }
        if (txSFH.protection != myTxSFH.protection) 
        {
            myTxSFH.protection = txSFH.protection;
            bChanged = true;
        }
        if (txSFL.protection != myTxSFL.protection) 
        {
            myTxSFL.protection = txSFL.protection;
            bChanged = true;
        }
        if (txPQWInvalid.protection != myTxPQWInvalid.protection) 
        {
            myTxPQWInvalid.protection = txPQWInvalid.protection;
            bChanged = true;
        }
        if (txHWSquelch.protection != myTxHWSquelch.protection) 
        {
            myTxHWSquelch.protection = txHWSquelch.protection;
            bChanged = true;
        }
        if (rxPQM.protection != myRxPQM.protection)
        {
            myRxPQM.protection = rxPQM.protection;
            bChanged = true;
        }
        if (rxSFH.protection != myRxSFH.protection) 
        {
            myRxSFH.protection = rxSFH.protection;
            bChanged = true;
        }
        if (rxSFL.protection != myRxSFL.protection) 
        {
            myRxSFL.protection = rxSFL.protection;
            bChanged = true;
        }
        if (rxPQWInvalid.protection != myRxPQWInvalid.protection) 
        {
            myRxPQWInvalid.protection = rxPQWInvalid.protection;
            bChanged = true;
        }
        if (rxHWSquelch.protection != myRxHWSquelch.protection) 
        {
            myRxHWSquelch.protection = rxHWSquelch.protection;
            bChanged = true;
        }
        if (defectStatus.protection != myDefectStatus.protection) 
        {
            myDefectStatus.protection = defectStatus.protection;
            bChanged = true;
        }
        if ( bChanged )
        {
            fc_cout << "P Tx: PQM=" << uint32(myTxPQM.protection);
            fc_cout << " SFH=" << uint32(myTxSFH.protection);
            fc_cout << " SFL=" << uint32(myTxSFL.protection);
            fc_cout << " SD=" << uint32(myTxSD.protection);
            fc_cout << " Invld=" << uint32(myTxPQWInvalid.protection);
            fc_cout << " Sql=" << uint32(myTxHWSquelch.protection);
            fc_cout << " Rx: PQM=" << uint32(myRxPQM.protection);
            fc_cout << " SFH=" << uint32(myRxSFH.protection);
            fc_cout << " SFL=" << uint32(myRxSFL.protection);
            fc_cout << " SD=" << uint32(myRxSD.protection);
            fc_cout << " Invld=" << uint32(myRxPQWInvalid.protection);
            fc_cout << " Sql=" << uint32(myRxHWSquelch.protection);
            fc_cout << " Dft="  << uint32(myDefectStatus.protection);
            fc_cout << " odu=" << uint32(myTspiiOduIdx.protection);
            fc_cout << " pqw=" << uint32(myPQWChannels.protection);
            fc_cout << endl;
        }
    }
}

void SP_OduKSnc::DispSwitchParams(bool switchingAllowed, uint16 userCmdMsg, SP_SncSelSwitchDir theWDir, SP_SncSelSwitchDir thePDir, bool sendMessage, bool mateActive, CT_SP_Protection theCurrentSelection)
{
    bool bChanged = false;
    if ( switchingAllowed != mySwitchingAllowed )
    {
        bChanged = true;
        mySwitchingAllowed = switchingAllowed;
    }
    if ( userCmdMsg != myUserCmdMsg )
    {
        bChanged = true;
        myUserCmdMsg = userCmdMsg;
    }
    if ( theWDir != myWDir )
    {
        bChanged = true;
        myWDir = theWDir;
    }
    if ( thePDir != myPDir )
    {
        bChanged = true;
        myPDir = thePDir;
    }
    if ( sendMessage != mySendMessage )
    {
        bChanged = true;
        mySendMessage = sendMessage;
    }
    if ( mateActive != myMateActive )
    {
        bChanged = true;
        myMateActive = mateActive;
    }
    if ( theCurrentSelection != myCurrentSelection )
    {
        bChanged = true;
        myCurrentSelection = theCurrentSelection;
    }
    if ( bChanged )
    {
        fc_cout << "swAlw=" << uint32(switchingAllowed ? 1:0);
        fc_cout << " Cmd=" << uint32(userCmdMsg);
        fc_cout << " WDir=" << uint32(theWDir);
        fc_cout << " PDir=" << uint32(thePDir);
        fc_cout << " sndMsg=" << uint32(sendMessage ? 1:0);
        fc_cout << " mtAct=" << uint32(mateActive ? 1:0);
        fc_cout<< " CurSel=" << uint32(theCurrentSelection) << endl;
    }
}

uint16 SP_OduKSnc::GetUplayerPhysicalPort(CT_ODU_ServerID theServerID)
{
    uint16 port = 0;
    switch(theServerID.GetIdTelecomLayer())
    {
        case CT_ServerPool_Layer_Otu:
            port = theServerID.GetPoolInstance();
            break;            
        case CT_ServerPool_Layer_Odu:
            {
                T6100_TelecomIf& theOduApp = myApplIf.GetCardContext().GetOduIf();
                CFG_AppIf& aCfgApp =  theOduApp.GetCfgPortSideApp((CT_IntfId)((CT_PORT_SIDE_30) + int(theServerID.GetOduKvalue())));
                CFG_Odu& aCfgOdu = dynamic_cast<CFG_Odu&>((*(aCfgApp.GetCfgRegion()))[theServerID.GetPoolInstance()]);
                port = GetUplayerPhysicalPort(aCfgOdu.GetServerID());
            }
            break;            
        case CT_ServerPool_Layer_Tcm:
            {
                T6100_TelecomIf& theOdukTApp = myApplIf.GetCardContext().GetTcmIf();
                CFG_AppIf& aCfgApp =  theOdukTApp.GetCfgPortSideApp((CT_IntfId)CT_PORT_SIDE_40);
                CFG_Tcm& aCfgTcm = dynamic_cast<CFG_Tcm&>((*(aCfgApp.GetCfgRegion()))[theServerID.GetPoolInstance()]);
                port = GetUplayerPhysicalPort(aCfgTcm.GetServerID());
            }
            break;            
        default:
            break;
    }
    return port;
}
// prepare TX APS bytes and store to myTxApsBytes of sp_oduksnc instance.
void SP_OduKSnc::PrepareTxApsBytes()
{
    CT_SP_Request theEffectiveRequest = myProtectionAction.myRequestParserPtr->GetEffectiveRequest();
    bool theRemoteOrLocalRequest = myProtectionAction.myRequestParserPtr->IsEffectiveRequestFromRemote();
    myTxApsBytes = ConvertCurrentReqToTxApsBytes(theEffectiveRequest, theRemoteOrLocalRequest);
}

// prepare TX APS bytes and store to myTxApsBytes of sp_oduksnc instance.
// input parameter participant, 0: highest request on protection, 1: highest request on working
void SP_OduKSnc::PrepareTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest)
{
    myTxApsBytes = ConvertCurrentReqToTxApsBytes(theParticipant, theRequest, theRemoteOrLocalRequest);
}

//convert the currentReq (including the request value and its source) from request parsing to Tx ApsBytes
uint32 SP_OduKSnc::ConvertCurrentReqToTxApsBytes(CT_SP_Request theEffectiveRequest,  bool theRemoteOrLocalRequest)
{
    APS_BYTES theApsBytes;
    memset(&theApsBytes,0,sizeof(theApsBytes));
  
    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        theApsBytes.requestAndProtType.bitA    = 1; //with aps;
        theApsBytes.requestAndProtType.bitB    = 0; //1+1
        theApsBytes.requestAndProtType.bitD    = 1; //bi_directional switch
        theApsBytes.requestAndProtType.bitR    = ((true == myProtectionAction.Get1plus1Config().GetRevertiveMode()) ? 1:0 ); //revertive or no-revertive

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
uint32 SP_OduKSnc::ConvertCurrentReqToTxApsBytes(uint8 theParticipant, CT_SP_Request theRequest, bool theRemoteOrLocalRequest)
{   
    APS_BYTES theApsBytes;
    memset(&theApsBytes,0,sizeof(theApsBytes));

    if (myProtectionAction.Get1plus1Config().IsBiSwitching())
    {
        theApsBytes.requestAndProtType.bitA    = 1; //with aps;
        theApsBytes.requestAndProtType.bitB    = 0; //1+1;
        theApsBytes.requestAndProtType.bitD    = 1; //bi_directional switch
        theApsBytes.requestAndProtType.bitR    = ((true == myProtectionAction.Get1plus1Config().GetRevertiveMode()) ? 1:0 ); //revertive or no-revertive

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
    }else 
    {
        return 0;
    }
}

        
//dispaly TxApsBytes as specified format
void SP_OduKSnc::DisplayTxApsBytes(uint32 theTxApsBytes)
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



//call tspii_dw interface to set Tx APS bytes
void SP_OduKSnc::SetTxApsBytes(bool theApsInsert)
{
    CT_SP_APS_Channel theApsChannel;
    
    CT_SP_1plus1Type theProtectionType = myProtectionAction.Get1plus1Config().Get1plus1Type();

    unsigned int oduTspiiPort = -1;
    unsigned int oduTspiiIdx = -1;
    
    if (CT_SP_SNCI == theProtectionType)
    {
        theApsChannel =  CT_SP_APS_ODUkServerLayerTrail;
        oduTspiiPort = myTspiiOduPort.protection;
        oduTspiiIdx = myTspiiOduIdx.protection;
    }
    else if (CT_SP_SNCN == theProtectionType)
    {
        theApsChannel =  CT_SP_APS_ODUkPath ;
        oduTspiiPort = myTspiiOduPort.protection;
        oduTspiiIdx = myTspiiOduIdx.protection;
    }
    else if (CT_SP_SNCS == theProtectionType)
    {
        //fc_cout <<showbase;
        fc_cout << "BI_SNC : SNCS_BIDIR is not supported to transmit ApsBytes yet !!" <<endl;
        //fc_cout <<noshowbase;
        return;
    }
    else
    {
        //fc_cout <<showbase;
        fc_cout << "BI_SNC : SNC_BIDIR TxApsByte should never go here!!" <<endl;
        //fc_cout <<noshowbase;
        return;
    }

    if (myProtectionAction.Get1plus1Config().GetSources().protection.GetShelfId() == myShelfId &&
        myProtectionAction.Get1plus1Config().GetSources().protection.GetSlotId() == mySlotId)
    {
        
        DisplayTxApsBytes(myTxApsBytes);

        TSPII_DwRegion* theDwRegion = TSPII_SubApplication::GetInstance()->GetDw(oduTspiiPort);
        if (theDwRegion != NULL)
        {
            if (gSP_DebugTraceSnc)
            {
                printf("BISNC:++++: Set tx APS to DW[%#x][%#x]\n", oduTspiiPort, oduTspiiIdx);
            }
            (*theDwRegion)[oduTspiiIdx].SetTxApsBytes(theApsChannel, myTxApsBytes ,theApsInsert);
        }
        else
        {
            printf("BISNC:++++: Can't find DW[%#x] to set tx APS\n", oduTspiiPort);
        }
    }
}

uint32 SP_OduKSnc::GetTxApsBytes()
{
    return myTxApsBytes;
}
