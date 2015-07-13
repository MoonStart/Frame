/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     July, 2007  Kumar C Solai
 DESCRIPTION:   TSXC_RollAction  Implementation
--------------------------------------------------------------------------*/
#include <T6100/T6100_MainAppIf.h>
#include <T6100/T6100_ShelfIf.h>
#include <T6100/T6100_SlotIf.h>
#include <XC/TSXC_ConnectService.h>
#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_RollAction.h>
#include <PII_TickTimer.h>
#include <CsPii/CSPII_SysCfgParamIF.h>

#define TIME_OUT_REASON     (2)

//*****************************************************************************************************************
//
//--- Constructor
//
TSXC_RollAction::TSXC_RollAction():
	myBbAction(NULL)
{
	myBbAction  = new FC_BbAction(this);
    myPeriodicProcess  = new FC_PeriodicProcess(*this, gTimerDispatcher, ROLL_TIMEOUT);
    myPeriodicProcess->Suspend();
    myRollState = ROLL_IDLE;
    myShelfIsNano = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsHwVer4();
    myDebugLevel = 0;
    myRollCommandID = 999;   
}

//
//--- Destructor
//
TSXC_RollAction::~TSXC_RollAction()
{
	delete myBbAction;
    delete myPeriodicProcess;
}

//----------------------------------------------------------------------------------------------------------------------
//--- Do the work
//
FC_Object* TSXC_RollAction::DoRunWithReason(unsigned theRunReason,
	                                 FC_Object* theInvokerObj,
	                                 FC_Object* theParam)
{
    TSXC_RollConnInfo       aCInfo;    
    TSXC_RollConnInfo       aCInfo_Old;    
    int                     count;
    int                     previousSlot;
    bool                    validResponse;
    bool                    responseNeeded;
    bool                    IsSameModule = false;
    //
    //---  Note theRunReason neverbeen used so far, This is just a test message.
    //
    validResponse = false;  
    if (TIME_OUT_REASON == theRunReason)
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"Roll Action Timed out...");
        myResponseFlag =0;
        validResponse = true;
    }
    else
    {
        //--- Other than timeout we got here because of some region got modified or refreshed 
        //--- we want to make sure the appropriate commandID is getting here once only
        //--- or we must eleminate duplicate or responses.
        switch(myRollState)
        {
            case    ROLL_WAIT_FOR_RES_FROM_NSMA:
                    //--- Check for responses from the old source module(s)
                    for (count = 0, previousSlot = 0; count < (int) myRollQueue[0].removeConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].removeConnInfo[count];
                        if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            if (((myResponseFlag & 1 << aCInfo.SlotID) != 0) && (myRollCommandID == GetCommandID(aCInfo)))
                            {
                                myResponseFlag &= ~(1 << aCInfo.SlotID);
                                validResponse = true;
                            }
                        previousSlot = aCInfo.SlotID;
                    }                
                    break;
                
            case    ROLL_WAIT_FOR_RES_FROM_SMN:            
            case    ROLL_WAIT_FOR_RES_FROM_NSM:
                    //--- Check for responses from the new source module(s)
                    for (count = 0, previousSlot = 0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].newSrcConnInfo[count];
                        if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            if (((myResponseFlag & 1 << aCInfo.SlotID) != 0) && (myRollCommandID == GetCommandID(aCInfo)))
                            {
                                myResponseFlag &= ~(1 << aCInfo.SlotID);
                                validResponse = true;
                            }
                        previousSlot = aCInfo.SlotID;
                    }                
                    break;
                        
            case    ROLL_WAIT_FOR_RES_FROM_SPFAB:
                    //--- Check for responses from the SPFAB module(s)
                    if (0 != myRollQueue[0].spfabConnInfo.size())                
                    {
                        aCInfo = myRollQueue[0].spfabConnInfo[0];
                        if (((myResponseFlag & 1 << aCInfo.SlotID) != 0) && (myRollCommandID == GetCommandID(aCInfo)))
                        {
                            myResponseFlag &= ~(1 << aCInfo.SlotID);
                            validResponse = true;
                        }                            
                    }                
                    break;
                    
            case    ROLL_WAIT_FOR_RES_FROM_FDM:
                    //--- Check for responses from final destination module(s)
                    for (count = 0, previousSlot = 0; count < (int) myRollQueue[0].postConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].postConnInfo[count];
                        if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            if (((myResponseFlag & 1 << aCInfo.SlotID) != 0) && (myRollCommandID == GetCommandID(aCInfo)))
                            {
                                myResponseFlag &= ~(1 << aCInfo.SlotID);
                                validResponse = true;
                            }
                        previousSlot = aCInfo.SlotID;
                    }                
                    break;                                            
            default:
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Roll state invalid during region trigger");                    
        } 
    }
    
    if (validResponse)
    { 
        switch(myRollState)
        {
            case    ROLL_IDLE:
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, "ROLL_STATE: Roll is in idle state");
                    myPeriodicProcess->Suspend();
                    break;
                    
                    //--- Process the Nano Mesh support                    
            case    ROLL_WAIT_FOR_RES_FROM_FDM:
                    if (myResponseFlag != 0)
                    {
                        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waiting for more response");
                        break;                        
                    }
                    
                    END_TIME(TSXC_DEBUG_LEVEL18);
                    myPeriodicProcess->Suspend();   
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waited for response from DST module");
                    PRINT_TIME(TSXC_DEBUG_LEVEL18,"TSXC_ROLL_DEBUG_INFO: post module response time : ");

                    //--- Clear query request on the final dstination module(s)
                    for (count=0, previousSlot=0; count < (int) myRollQueue[0].postConnInfo.size(); count++)
                    {    
                        aCInfo = myRollQueue[0].postConnInfo[count];
                        if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            ClearLastRequest(aCInfo, true, true);
                        previousSlot = aCInfo.SlotID;
                    }
                    myResponseFlag = 0;
                    myRollCommandID++;
                    START_TIME(TSXC_DEBUG_LEVEL18);
                    
                    //--- Step 2 send the new (ADD) connection info to the module(s)
                    for (count=0, previousSlot=0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
                    {     
                        aCInfo = myRollQueue[0].newSrcConnInfo[count];
                        responseNeeded = ((count == 0) || (previousSlot != aCInfo.SlotID));
                        NanoMeshSetConnection(aCInfo, count, responseNeeded);
                        previousSlot = aCInfo.SlotID;
                    }
                    myRollState = ROLL_WAIT_FOR_RES_FROM_NSM; 
                    myPeriodicProcess->WakeUp();                                          
                    break;
                    
            case    ROLL_WAIT_FOR_RES_FROM_NSM:
                    if (myResponseFlag != 0)
                    {
                        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waiting for more response");
                        break;                        
                    }

                    END_TIME(TSXC_DEBUG_LEVEL18);
                    myPeriodicProcess->Suspend();   
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waited for ADD response from new module");
                    PRINT_TIME(TSXC_DEBUG_LEVEL18,"TSXC_ROLL_DEBUG_INFO: New module connect time : ");

                    //--- Clear Add request (clear input only) on the new source module(s)
                    for (count=0, previousSlot=0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
                    {    
                        aCInfo = myRollQueue[0].newSrcConnInfo[count];
                        if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            ClearLastRequest(aCInfo, true, false);
                        previousSlot = aCInfo.SlotID;
                    }
                    
                    myResponseFlag = 0;
                    myRollCommandID++;
                    START_TIME(TSXC_DEBUG_LEVEL18);
                    //--- Send the remove command 
                    aCInfo = myRollQueue[0].newSrcConnInfo[0];
                    if (aCInfo.RollType == ROLL_TYPE_COMPLEX)
                    {
                        //--- Step three send the remove connection with mask info to that module(s).    
                        for (count=0, previousSlot=0; count < (int) myRollQueue[0].removeConnInfo.size(); count++)
                        {
                            aCInfo = myRollQueue[0].removeConnInfo[count];
                            responseNeeded = ((count == 0) || (previousSlot != aCInfo.SlotID));                            
                            NanoMeshSendRollRmvRequest(aCInfo, count, responseNeeded, ROLL_CMD_REQ_RMV);
                            previousSlot = aCInfo.SlotID;
                        }

                        myRollState = ROLL_WAIT_FOR_RES_FROM_NSMA;
                        myPeriodicProcess->WakeUp();
                        break;      
                    }
                    //--- else fall through and do the final step
                    
            case    ROLL_WAIT_FOR_RES_FROM_NSMA:
                    if (myResponseFlag != 0)
                    {
                        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waiting for more response");
                        break;                        
                    }

                    END_TIME(TSXC_DEBUG_LEVEL18);
                    myPeriodicProcess->Suspend();
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waited for RMV response from old module");
                    PRINT_TIME(TSXC_DEBUG_LEVEL18,"TSXC_ROLL_DEBUG_INFO: Old module response time : ");
                    
                    aCInfo = myRollQueue[0].newSrcConnInfo[0];
                    aCInfo_Old = myRollQueue[0].removeConnInfo[0];
                    IsSameModule = (aCInfo.ShelfID == aCInfo_Old.ShelfID && aCInfo.SlotID == aCInfo_Old.SlotID);
                                                              
                    if (aCInfo.RollType == ROLL_TYPE_COMPLEX)
                    {                    
                        //--- Send Clear to RMV request to the old module    
                        for (count=0, previousSlot=0; count < (int) myRollQueue[0].removeConnInfo.size(); count++)
                        {
                            aCInfo = myRollQueue[0].removeConnInfo[count];
                            if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            {
                                ClearLastRequest(aCInfo, true, false);                        
                                NanoMeshSendRollRmvRequest(aCInfo, count, false, ROLL_CMD_NOREQ);
                            }
                            previousSlot = aCInfo.SlotID;                        
                        }
                        
                        for (count=0; count < (int) myRollQueue[0].removeConnInfo.size(); count++)
                        {    
                            aCInfo = myRollQueue[0].removeConnInfo[count];
                            aCInfo.IsNanoMesh = false;  //--- This is to deactive the Fab-tx.
                            //--- Even though this connection shuld be removed, 
                            //--- we put it back any have but deactivate the Fab-tx   
                            SetConnection(aCInfo, false);                        
                        }
                        
                        if (!IsSameModule)
                        {
                            //--- Clear ADD request on the new source module(s)
                            for (count=0, previousSlot=0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
                            {    
                                aCInfo = myRollQueue[0].newSrcConnInfo[count];
                                if ((count == 0) || (previousSlot != aCInfo.SlotID))
                                    ClearLastRequest(aCInfo, false, true);
                                previousSlot = aCInfo.SlotID;
                            }
                        }                             
                    }
                    else
                    {
                        //--- Clear ADD request on the new source module(s)
                        for (count=0, previousSlot=0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
                        {    
                            aCInfo = myRollQueue[0].newSrcConnInfo[count];
                            if ((count == 0) || (previousSlot != aCInfo.SlotID))
                                ClearLastRequest(aCInfo, false, true);
                            previousSlot = aCInfo.SlotID;
                        }
                        
                        for (count=0; count < (int) myRollQueue[0].removeConnInfo.size(); count++)
                        {    
                            aCInfo = myRollQueue[0].removeConnInfo[count];
                            aCInfo.IsNanoMesh = false;  //--- This is to deactive the Fab-tx.
                            //--- Even though this connection shuld be removed, 
                            //--- we put it back any have but deactivate the Fab-tx   
                            SetConnection(aCInfo, false);                        
                        }                                                    
                    }                   

                    //--- Final step: Send post module connection as part of the final step               
                    for (count = 0; count < (int) myRollQueue[0].postConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].postConnInfo[count];
                        SetConnection(aCInfo, false);
                    }                    
                                        
                    //--- now that one roll task is completed remove this task and check  for more
                    myRollQueue[0].newSrcConnInfo.clear();
                    myRollQueue[0].spfabConnInfo.clear();
                    myRollQueue[0].removeConnInfo.clear();
                    myRollQueue[0].postConnInfo.clear();
                    myRollQueue.erase(myRollQueue.begin());

                    if (myRollQueue.size() > 0)
                        StartRoll();

                    else    //--- set state back to IDLE 
                        myRollState = ROLL_IDLE;          
                    break;                

                    
            //-----------------------------------------------------------------------------------------------------------------------
                    //--- Process the old way for the SPFAB on the USS shelf                                        
            case    ROLL_WAIT_FOR_RES_FROM_SMN:
                    if (myResponseFlag != 0)
                    {
                        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waiting for more response");
                        break;                        
                    }

                    END_TIME(TSXC_DEBUG_LEVEL18);
                    myPeriodicProcess->Suspend();
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waited for response from new module");
                    PRINT_TIME(TSXC_DEBUG_LEVEL18,"TSXC_ROLL_DEBUG_INFO: New module connect time : ");

                    //--- Clear connection request on the new source module(s)
                    for (count=0, previousSlot=0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].newSrcConnInfo[count];
                        if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            ClearLastRequest(aCInfo, true, true);
                        previousSlot = aCInfo.SlotID;
                    }
                    
                    START_TIME(TSXC_DEBUG_LEVEL18);
                     
                    //--- Set connections on the SPFAB modules 
                    for (count=0, previousSlot=0; count < (int) myRollQueue[0].spfabConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].spfabConnInfo[count];
                        responseNeeded = ((count == 0) || (previousSlot != aCInfo.SlotID));            
                        SetConnection(aCInfo, responseNeeded );
                        previousSlot = aCInfo.SlotID;                                   
                    }

                    if (0 != myRollQueue[0].spfabConnInfo.size())
                    {
                        //--- set the next state and start the timer
                        myRollState = ROLL_WAIT_FOR_RES_FROM_SPFAB; 
                        myPeriodicProcess->WakeUp();                
                        break;
                    }
                    //--- else fall through and do the next state

                    
            case    ROLL_WAIT_FOR_RES_FROM_SPFAB:

                    END_TIME(TSXC_DEBUG_LEVEL18);
                    myPeriodicProcess->Suspend();
                           
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: Waited for response from SPFAB");
                    PRINT_TIME(TSXC_DEBUG_LEVEL18,"TSXC_ROLL_DEBUG_INFO: SPFAB connect time : ");

                    //--- clear request for SPFABS modules 
                    for (count=0,previousSlot=0; count < (int) myRollQueue[0].spfabConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].spfabConnInfo[count];
                        if ((count == 0) || (previousSlot != aCInfo.SlotID))
                            ClearLastRequest(aCInfo, true, true);
                        previousSlot = aCInfo.SlotID;                                   
                    }

                    //--- remove old connection now possible on old source module(s) and SPFAB module
                    for (count = 0; count < (int) myRollQueue[0].removeConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].removeConnInfo[count];
                        RemoveConnection(aCInfo);
                    }

                    //--- Put the new connection so that it is not over written by the above remove connection.
                    //--- new connection now possible on new source module(s) and SPFAB module
                    for (count = 0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].newSrcConnInfo[count];
                        SetConnection(aCInfo, false);
                    }
                                                            
                    //--- Do the post connection request if any
                    for (count = 0; count < (int) myRollQueue[0].postConnInfo.size(); count++)
                    {
                        aCInfo = myRollQueue[0].postConnInfo[count];
                        SetConnection(aCInfo, false);
                    }
                                        
                    //--- now that one roll task is completed remove this task and check  for more
                    myRollQueue[0].newSrcConnInfo.clear();
                    myRollQueue[0].spfabConnInfo.clear();
                    myRollQueue[0].removeConnInfo.clear();
                    myRollQueue[0].postConnInfo.clear();
                    myRollQueue.erase(myRollQueue.begin());

                    if (myRollQueue.size() > 0)
                        StartRoll();

                    else    //--- set state back to IDLE 
                        myRollState = ROLL_IDLE;          
                    break;

            default:
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17,"ROLL_STATE: ROLL_INVALID_STATE");
        }
    }
	return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::SetupNextQueueElements()
{
    TSXC_RollQueue  aNewQueue;
    aNewQueue.newSrcConnInfo.clear();
    aNewQueue.spfabConnInfo.clear();
    aNewQueue.removeConnInfo.clear();
    aNewQueue.postConnInfo.clear();
    myRollQueue.push_back(aNewQueue);
    if (0 != myDebugLevel)
    {
        char    aDebugMsg[DEBUG_MSG_LEN];
        sprintf(aDebugMsg,"TSXC_ROLL_DEBUG: RollQueue count: %d",myRollQueue.size());
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, aDebugMsg);
    }        
}

//----------------------------------------------------------------------------------------------------------------------
UINT32 TSXC_RollAction::GetCommandID(const TSXC_RollConnInfo& theCInfo)
{
    TEL_BbRegionBaseImp<TSXC_RollResponse>* aRollResRegionPtr;
    UINT32  retValue = 0;
    
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();
    if (NULL != aCardPtr)
    { 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        aRollResRegionPtr = xcApp.GetRollResponse_Region();
        retValue = (*aRollResRegionPtr)[0].GetRollCommandID();
    }
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::SetConnection(const TSXC_RollConnInfo& theCInfo, bool theResponseNeeded)
{
    TEL_BbRegionBaseImp<TSXC_RollCommand>*  aRollCmdRegionPtr;
    TEL_BbRegionBaseImp<TSXC_RollResponse>* aRollResRegionPtr;
    TSXC_ConfigRegion<TSXC_Connect>*        aConfigRegionPtr;
    TSXC_ConnectService*                    aConnectService = TSXC_ConnectService::GetInstance();    
    TSXC_Connection                         aConnection;
    CT_CardType                             aCardType;
                
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();
    if (NULL != aCardPtr)
    { 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        aConfigRegionPtr  = xcApp.GetAgCfgRegion();
        aRollCmdRegionPtr = xcApp.GetRollCommand_Region();
        aRollResRegionPtr = xcApp.GetRollResponse_Region();

        aCardType = aConfigRegionPtr->GetMyCardType();
        if (CARD_TYPE_SPFAB == aCardType)
            //--- send the connection to both SPFAB modules. 
            aConnectService->ConnectOrDisconnectOnSPFAB(theCInfo.ShelfID,theCInfo.SrcFac, &theCInfo.SrcFacStsMap,
                theCInfo.DstFac, &theCInfo.DstFacStsMap, theCInfo.ConnType, theCInfo.Xc_Mapping, XC_CONNECT, false);
        else
            aConnectService->ConnectOrDisconnect(theCInfo.ShelfID, theCInfo.SlotID, theCInfo.SrcFac, &theCInfo.SrcFacStsMap,
                        theCInfo.DstFac, &theCInfo.DstFacStsMap, theCInfo.ConnType, theCInfo.Xc_Mapping, XC_CONNECT, 
                        theCInfo.XcAllowed, false, false, theCInfo.IsNanoMesh);

        aConnection.aCE.srcFacPort  = theCInfo.SrcFac; 
        aConnection.aCE.srcFacChan  = theCInfo.SrcFacStsMap.FindLowestInUseSts()+1;
        aConnection.aCE.dstFacPort  = theCInfo.DstFac;
        aConnection.aCE.dstFacChan  = theCInfo.DstFacStsMap.FindLowestInUseSts()+1;
        
        myBbAction->AddOutputRegion(aRollCmdRegionPtr, false, false);           
        if (theResponseNeeded)
        {   
            TSXC_Roll_Info           aRollInfo;       
            TSXC_RollConnInfo        aCInfo_rmv;
            TSXC_RollConnInfo        aCInfo_post;
            bool                     isProtected;

            aCInfo_rmv  = myRollQueue[0].removeConnInfo[0];
            aCInfo_post = myRollQueue[0].postConnInfo[0];

            isProtected =  (myRollQueue[0].newSrcConnInfo.size() >= 2);

            memset(&aRollInfo, 0, sizeof(TSXC_Roll_Info));
            aRollInfo.OldSrcShelf = aCInfo_rmv.ShelfID;
            aRollInfo.OldSrcSlot  = aCInfo_rmv.SlotID;
            aRollInfo.NewSrcShelf = theCInfo.ShelfID;
            aRollInfo.NewSrcSlot  = theCInfo.SlotID;
            aRollInfo.IsProtected = isProtected;
            aRollInfo.IsResponseExpected = true;
            aRollInfo.MulticastId = theCInfo.MulticastId;
            aRollInfo.RemoteDstSlot = aCInfo_post.SlotID;

            myBbAction->AddInputRegion(aRollResRegionPtr);
            (*aRollCmdRegionPtr)[0].SetRollConnectKeyOne(aConnection);
            (*aRollCmdRegionPtr)[0].SetRollInfo(aRollInfo);
            (*aRollCmdRegionPtr)[0].SetRollCommand(ROLL_CMD_REQ);
            (*aRollCmdRegionPtr)[0].SetRollCommandID(myRollCommandID);
            myResponseFlag |= (1 << theCInfo.SlotID);
            
            aRollCmdRegionPtr->IncModificationCounter();
            aRollCmdRegionPtr->UpdateNotify();
        }
        myBbAction->RemoveOutputRegion(aRollCmdRegionPtr);
        
        if (0 != myDebugLevel )
        {
            char    aDebugMsg[255];
            sprintf(aDebugMsg,"%sResponse expected for: (%d-%d)-%d,%d -> %d,%d",
                    theResponseNeeded ? "":"No ", theCInfo.ShelfID, theCInfo.SlotID,
                    aConnection.aCE.srcFacPort, aConnection.aCE.srcFacChan,
                    aConnection.aCE.dstFacPort, aConnection.aCE.dstFacChan);
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, aDebugMsg);
        }
       
        //--- Note: the update notify should be done after the command is sent 
        if (CARD_TYPE_SPFAB == aCardType)
        {
            aConnectService->CommitPairConns(theCInfo.ShelfID,SPFAB_PRI_SLOT,theCInfo.ShelfID,SPFAB_SEC_SLOT);
        }
        else
            aConfigRegionPtr->UpdateNotify(); 
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::RemoveConnection(const TSXC_RollConnInfo& theCInfo)
{
    TSXC_ConfigRegion<TSXC_Connect>*        aConfigRegionPtr;
    TSXC_ConnectService*    aConnectService = TSXC_ConnectService::GetInstance();    
    CT_CardType             aCardType;
                   
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();
    //--- Do not remove any connections in old module because there could be broadcast (SPFAB mode only)
    if (NULL != aCardPtr)
    { 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        aConfigRegionPtr  = xcApp.GetAgCfgRegion();

        aCardType = aConfigRegionPtr->GetMyCardType();
        if (CARD_TYPE_SPFAB == aCardType)
            //--- send the connection to both SPFAB modules. 
            aConnectService->ConnectOrDisconnectOnSPFAB(theCInfo.ShelfID,theCInfo.SrcFac, &theCInfo.SrcFacStsMap,
                theCInfo.DstFac, &theCInfo.DstFacStsMap, theCInfo.ConnType, theCInfo.Xc_Mapping, XC_DISCONNECT, false);
        else
            //--- SMTMU modules or other than SPFAB
            aConnectService->ConnectOrDisconnect(theCInfo.ShelfID, theCInfo.SlotID, theCInfo.SrcFac, &theCInfo.SrcFacStsMap,
                        theCInfo.DstFac, &theCInfo.DstFacStsMap, theCInfo.ConnType, theCInfo.Xc_Mapping, XC_DISCONNECT,
                        false, false, false, theCInfo.IsNanoMesh);
                        
        //--- The following is to updateNotify the regions for the SPFAB(S)
        if (!myShelfIsNano)
             aConnectService->CommitPairConns(theCInfo.ShelfID,SPFAB_PRI_SLOT,theCInfo.ShelfID,SPFAB_SEC_SLOT);
        
        if (0 != myDebugLevel ) 
        {
            char                    aDebugMsg[255];
            TSXC_Connection         aConnection;
            aConnection.aCE.srcFacPort  = theCInfo.SrcFac; 
            aConnection.aCE.srcFacChan  = theCInfo.SrcFacStsMap.FindLowestInUseSts()+1;
            aConnection.aCE.dstFacPort  = theCInfo.DstFac;
            aConnection.aCE.dstFacChan  = theCInfo.DstFacStsMap.FindLowestInUseSts()+1;            
                
            sprintf(aDebugMsg,"Removing connection for: (%d-%d)-%d,%d -> %d,%d", theCInfo.ShelfID, theCInfo.SlotID,
                        aConnection.aCE.srcFacPort, aConnection.aCE.srcFacChan,
                        aConnection.aCE.dstFacPort, aConnection.aCE.dstFacChan);
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, aDebugMsg);
        }
    } 
}
    
//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::ClearLastRequest(const TSXC_RollConnInfo& theCInfo, bool theClearMyInput, bool theSendNoReq)
{
    //--- Based on the connection information: 
    //--- Clear the Roll command request, remove input region (response region) 
    TEL_BbRegionBaseImp<TSXC_RollCommand>*  aRollCmdRegionPtr;
    TEL_BbRegionBaseImp<TSXC_RollResponse>* aRollResRegionPtr;
    
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();
    if (NULL != aCardPtr)
    { 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        if (theClearMyInput)
        {
        aRollResRegionPtr = xcApp.GetRollResponse_Region();
        myBbAction->RemoveInputRegion(aRollResRegionPtr);
        }
        if (theSendNoReq)
        {
            aRollCmdRegionPtr = xcApp.GetRollCommand_Region();
            myBbAction->AddOutputRegion(aRollCmdRegionPtr, false, false);
            (*aRollCmdRegionPtr)[0].SetRollCommand(ROLL_CMD_NOREQ);
            aRollCmdRegionPtr->IncModificationCounter();
            aRollCmdRegionPtr->UpdateNotify(); 
            myBbAction->RemoveOutputRegion(aRollCmdRegionPtr); 
        }        
    }
}

//----------------------------------------------------------------------------------------------------------------------
TSXC_RollFsmState TSXC_RollAction::GetRollState()
{
    return (myRollState);
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::StartRoll()
{
    TSXC_RollConnInfo aCInfo;
    UINT8           previousSlot;
    bool            responseNeeded;
    int             count;

    if (myShelfIsNano)
    {
        NanoMeshStartRoll();
    }
    else
    {    
        if (0 != myDebugLevel)
        {
            char    aDebugMsg[DEBUG_MSG_LEN];
            sprintf(aDebugMsg,  
                    "New SRC count: %d, SPFAB connections: %d,"
                    " Remove connections: %d, post connections: %d and RollQueues: %d",
                    myRollQueue[0].newSrcConnInfo.size(), myRollQueue[0].spfabConnInfo.size() , 
                    myRollQueue[0].removeConnInfo.size(), myRollQueue[0].postConnInfo.size(),
                    myRollQueue.size());
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, aDebugMsg);
        }

        START_TIME(TSXC_DEBUG_LEVEL18);
        myResponseFlag = 0;
        myRollCommandID++;

        for (count=0,previousSlot=0; count < (int) myRollQueue[0].newSrcConnInfo.size(); count++)
        {
            aCInfo = myRollQueue[0].newSrcConnInfo[count];
            responseNeeded = ((count == 0) || (previousSlot != aCInfo.SlotID));
            SetConnection(aCInfo, responseNeeded);
            previousSlot = aCInfo.SlotID;
        }

        if (0 == myRollQueue[0].newSrcConnInfo.size())
        {
            //--- In the case of protected connection no need to set New module Connection
            //--- Set connections on the SPFAB modules 
            for (count=0,previousSlot=0; count < (int) myRollQueue[0].spfabConnInfo.size(); count++)
            {
                aCInfo = myRollQueue[0].spfabConnInfo[count];
                responseNeeded = ((count == 0) || (previousSlot != aCInfo.SlotID));            
                SetConnection(aCInfo, responseNeeded );
                previousSlot = aCInfo.SlotID;                    
            }

            if (0 == myRollQueue[0].spfabConnInfo.size())
            {
                //--- If both New Module and SPFAB connection conunt is zero
                //--- remove old connection now (possible on old source module(s) and SPFAB module
                for (count=0; count < (int) myRollQueue[0].removeConnInfo.size(); count++)
                {
                    aCInfo = myRollQueue[0].removeConnInfo[count];
                    RemoveConnection(aCInfo);
                }

                //--- Do the post connection request if any
                for (count = 0; count < (int) myRollQueue[0].postConnInfo.size(); count++)
                {
                    aCInfo = myRollQueue[0].postConnInfo[count];
                    SetConnection(aCInfo, false);
                }

                //--- now that one roll task is completed remove this task and check  for more
                myRollQueue[0].newSrcConnInfo.clear();
                myRollQueue[0].spfabConnInfo.clear();
                myRollQueue[0].removeConnInfo.clear();
                myRollQueue[0].postConnInfo.clear();            
                myRollQueue.erase(myRollQueue.begin());

                if (myRollQueue.size() > 0)
                    StartRoll(); //--- This may be recursive                 
                else    //--- set state back to IDLE 
                    myRollState = ROLL_IDLE;   
                    //--- return controll back to all the way.                        
            }
            else
            {
                START_TIME(TSXC_DEBUG_LEVEL18);
                myRollState = ROLL_WAIT_FOR_RES_FROM_SPFAB; 
                myPeriodicProcess->WakeUp();  
            }    
        }
        else
        {    
            //--- This is the Normal case where the New module XC have to set
            //--- set the next state
            myRollState = ROLL_WAIT_FOR_RES_FROM_SMN;
            myPeriodicProcess->WakeUp();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::NanoMeshSendRollRmvRequest(const TSXC_RollConnInfo& theCInfo, int theMIndex, bool theResponseNeeded, int theCmd)
{
    TEL_BbRegionBaseImp<TSXC_RollCommand>*  aRollCmdRegionPtr;
    TEL_BbRegionBaseImp<TSXC_RollResponse>* aRollResRegionPtr;    
    TSXC_Connection         aConnection;
    TSXC_Connection         aConnectionTwo;
    TSXC_Roll_Info          aRollInfo;
    TSXC_RollConnInfo       aCInfo_add;
    TSXC_RollConnInfo       aCInfo_post;
    memset(&aCInfo_add, 0, sizeof(TSXC_RollConnInfo));         
    memset(&aCInfo_post, 0, sizeof(TSXC_RollConnInfo));         
    bool                    isProtected =  (myRollQueue[0].newSrcConnInfo.size() >= 2);
    
    if (theMIndex < (int) myRollQueue[0].newSrcConnInfo.size())
    {
        aCInfo_add = myRollQueue[0].newSrcConnInfo[theMIndex]; 
    }
    
    if (theMIndex < (int) myRollQueue[0].postConnInfo.size())
    {
        aCInfo_post = myRollQueue[0].postConnInfo[theMIndex]; 
    }
    
    memset(&aRollInfo, 0, sizeof(TSXC_Roll_Info));         
    aRollInfo.OldSrcShelf = theCInfo.ShelfID;
    aRollInfo.OldSrcSlot  = theCInfo.SlotID;
    aRollInfo.NewSrcShelf = aCInfo_add.ShelfID;    
    aRollInfo.NewSrcSlot  = aCInfo_add.SlotID;
    aRollInfo.IsProtected = isProtected;
    aRollInfo.IsResponseExpected = theResponseNeeded;
    aRollInfo.MulticastId = theCInfo.MulticastId;
    aRollInfo.RemoteDstSlot = aCInfo_post.SlotID;
       
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();          
    if (NULL != aCardPtr)
    {
        TSXC_S1McRegion<TSXC_S1MCast>* aMCRegionPtr = NULL;
        TSXC_S1RtRegion<TSXC_S1Route>* aRTRegionPtr = NULL; 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        aRollCmdRegionPtr = xcApp.GetRollCommand_Region();
        aRollResRegionPtr = xcApp.GetRollResponse_Region();        
        aMCRegionPtr      = xcApp.GetS1McCfgRegion();
        aRTRegionPtr      = xcApp.GetS1RtCfgRegion();
        if (ROLL_CMD_NOREQ == theCmd && theCInfo.IsNanoMesh)
        {
            UINT16 aMask =  ~(1 << (aCInfo_post.SlotID-1));        
            for (int anIndex = theCInfo.ChannelIndex; anIndex < (theCInfo.ChannelIndex+theCInfo.ChannelCount); anIndex++)
            {
                //--- Fixed MCastId setup
                (*aMCRegionPtr)[anIndex].SetMCastId(theCInfo.MulticastId);
                (*aMCRegionPtr)[anIndex].SetMCastImuxLMap(theCInfo.MulticastIMUXLMap & aMask);
                (*aMCRegionPtr)[anIndex].SetMCastImuxPMap(theCInfo.MulticastIMUXPMap & aMask);

                //--- Flexible MCastId setup
                (*aMCRegionPtr)[anIndex+XC_MAX_FIXED_MCASTID].SetMCastId(theCInfo.MulticastIdFlex);
                (*aMCRegionPtr)[anIndex+XC_MAX_FIXED_MCASTID].SetMCastImuxLMap(theCInfo.MulticastIMUXLMapFlex & aMask);
                (*aMCRegionPtr)[anIndex+XC_MAX_FIXED_MCASTID].SetMCastImuxPMap(theCInfo.MulticastIMUXPMapFlex & aMask);
                
                if ((theCInfo.MulticastIMUXLMap & aMask) + (theCInfo.MulticastIMUXPMap & aMask) == 0)
                {
                    //--- Set the route information
                    (*aRTRegionPtr)[anIndex].SetMCastId(XC_MCASTID_UNKNOWN, CT_XC_MAPPING_FIXED);
                    (*aRTRegionPtr)[anIndex].SetMCastId(XC_MCASTID_UNKNOWN, CT_XC_MAPPING_FLEXIBLE);
                }
                else
                {
                    //--- Set the route information
                    (*aRTRegionPtr)[anIndex].SetMCastId(theCInfo.MulticastId, CT_XC_MAPPING_FIXED);
                    (*aRTRegionPtr)[anIndex].SetMCastId(theCInfo.MulticastIdFlex, CT_XC_MAPPING_FLEXIBLE);
                }
            }

            (*aMCRegionPtr).IncModificationCounter();        
            (*aRTRegionPtr).IncModificationCounter();
            aMCRegionPtr->UpdateNotify();
            aRTRegionPtr->UpdateNotify();
            //--- clear any mask info.
            memset(&aRollInfo, 0, sizeof(TSXC_Roll_Info));
        }
        
        aConnection.aCE.srcFacPort  = theCInfo.SrcFac; 
        aConnection.aCE.srcFacChan  = theCInfo.SrcFacStsMap.FindLowestInUseSts()+1;
        aConnection.aCE.dstFacPort  = theCInfo.DstFac;
        aConnection.aCE.dstFacChan  = theCInfo.DstFacStsMap.FindLowestInUseSts()+1;
        
        aConnectionTwo.aCE.srcFacPort  = aCInfo_add.SrcFac; 
        aConnectionTwo.aCE.srcFacChan  = aCInfo_add.SrcFacStsMap.FindLowestInUseSts()+1;
        aConnectionTwo.aCE.dstFacPort  = aCInfo_add.DstFac;
        aConnectionTwo.aCE.dstFacChan  = aCInfo_add.DstFacStsMap.FindLowestInUseSts()+1;
        if (theResponseNeeded)
            myBbAction->AddInputRegion(aRollResRegionPtr);        
        myBbAction->AddOutputRegion(aRollCmdRegionPtr, false, false);
        (*aRollCmdRegionPtr)[0].SetRollConnectKeyOne(aConnection);
        (*aRollCmdRegionPtr)[0].SetRollConnectKeyTwo(aConnectionTwo);
        (*aRollCmdRegionPtr)[0].SetRollInfo(aRollInfo);
        (*aRollCmdRegionPtr)[0].SetRollCommand(theCmd);
        (*aRollCmdRegionPtr)[0].SetRollCommandID(myRollCommandID);
        myResponseFlag |= (1 << theCInfo.SlotID);        
        aRollCmdRegionPtr->IncModificationCounter();
        aRollCmdRegionPtr->UpdateNotify();
        myBbAction->RemoveOutputRegion(aRollCmdRegionPtr);

        if (0 != myDebugLevel )
        {
            char    aDebugMsg[DEBUG_MSG_LEN];
            sprintf(aDebugMsg,"RMV: %sResponse expected for: (%d-%d)-%d,%d -> %d,%d",
                    theResponseNeeded ? "":"No ", theCInfo.ShelfID, theCInfo.SlotID,
                    aConnection.aCE.srcFacPort, aConnection.aCE.srcFacChan,
                    aConnection.aCE.dstFacPort, aConnection.aCE.dstFacChan);
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL19, aDebugMsg);
        }        
    } 
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::NanoMeshSetConnection(const TSXC_RollConnInfo& theCInfo, int theMIndex, bool theResponseNeeded)
{
    TEL_BbRegionBaseImp<TSXC_RollCommand>*  aRollCmdRegionPtr;
    TEL_BbRegionBaseImp<TSXC_RollResponse>* aRollResRegionPtr;
    TSXC_ConfigRegion<TSXC_Connect>*        aConfigRegionPtr;
    TSXC_S1McRegion<TSXC_S1MCast>*          aMCRegionPtr = NULL;
    TSXC_S1RtRegion<TSXC_S1Route>*          aRTRegionPtr = NULL;
       
    TSXC_ConnectService*    aConnectService = TSXC_ConnectService::GetInstance();    
    TSXC_Connection         aConnection;
    TSXC_Connection         aConnectionTwo;    
    TSXC_Roll_Info          aRollInfo;
    TSXC_RollConnInfo       aCInfo_rmv;
    TSXC_RollConnInfo       aCInfo_post;
    memset(&aCInfo_rmv, 0, sizeof(TSXC_RollConnInfo));         
    memset(&aCInfo_post, 0, sizeof(TSXC_RollConnInfo));         
    bool                    isProtected =  (myRollQueue[0].newSrcConnInfo.size() >= 2);
    
    if (theMIndex < (int) myRollQueue[0].removeConnInfo.size())
    {
        aCInfo_rmv = myRollQueue[0].removeConnInfo[theMIndex]; 
    }
    
    if (theMIndex < (int) myRollQueue[0].postConnInfo.size())
    {
        aCInfo_post = myRollQueue[0].postConnInfo[theMIndex]; 
    }
    
    memset(&aRollInfo, 0, sizeof(TSXC_Roll_Info));       
    aRollInfo.OldSrcShelf = aCInfo_rmv.ShelfID;
    aRollInfo.OldSrcSlot  = aCInfo_rmv.SlotID;
    aRollInfo.NewSrcShelf = theCInfo.ShelfID;      
    aRollInfo.NewSrcSlot  = theCInfo.SlotID;
    aRollInfo.IsProtected = isProtected;
    aRollInfo.IsResponseExpected = theResponseNeeded;
    aRollInfo.MulticastId = theCInfo.MulticastId;
    aRollInfo.RemoteDstSlot = aCInfo_post.SlotID;
                       
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();
    if (NULL != aCardPtr)
    { 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        aConfigRegionPtr  = xcApp.GetAgCfgRegion();
        aRollCmdRegionPtr = xcApp.GetRollCommand_Region();
        aRollResRegionPtr = xcApp.GetRollResponse_Region();
        aMCRegionPtr      = xcApp.GetS1McCfgRegion();
        aRTRegionPtr      = xcApp.GetS1RtCfgRegion();
        
        aConnectService->ConnectOrDisconnect(theCInfo.ShelfID, theCInfo.SlotID, theCInfo.SrcFac, &theCInfo.SrcFacStsMap,
                                            theCInfo.DstFac, &theCInfo.DstFacStsMap, theCInfo.ConnType, theCInfo.Xc_Mapping, 
                                            XC_CONNECT, theCInfo.XcAllowed, false, false, theCInfo.IsNanoMesh);
                
        for (int anIndex = theCInfo.ChannelIndex; anIndex < (theCInfo.ChannelIndex+theCInfo.ChannelCount); anIndex++)
        {
            //--- Fixed MCastId setup
            (*aMCRegionPtr)[anIndex].SetMCastId(theCInfo.MulticastId);
            (*aMCRegionPtr)[anIndex].SetMCastImuxLMap(theCInfo.MulticastIMUXLMap);
            (*aMCRegionPtr)[anIndex].SetMCastImuxPMap(theCInfo.MulticastIMUXPMap);

            //--- Flexible MCastId setup
            (*aMCRegionPtr)[anIndex+XC_MAX_FIXED_MCASTID].SetMCastId(theCInfo.MulticastIdFlex);
            (*aMCRegionPtr)[anIndex+XC_MAX_FIXED_MCASTID].SetMCastImuxLMap(theCInfo.MulticastIMUXLMapFlex);
            (*aMCRegionPtr)[anIndex+XC_MAX_FIXED_MCASTID].SetMCastImuxPMap(theCInfo.MulticastIMUXPMapFlex);

            //--- Set the route information
            (*aRTRegionPtr)[anIndex].SetMCastId(theCInfo.MulticastId, CT_XC_MAPPING_FIXED);
            (*aRTRegionPtr)[anIndex].SetMCastId(theCInfo.MulticastIdFlex, CT_XC_MAPPING_FLEXIBLE);
        }
        
        (*aMCRegionPtr).IncModificationCounter();        
        (*aRTRegionPtr).IncModificationCounter();
                        
        aConnection.aCE.srcFacPort  = theCInfo.SrcFac; 
        aConnection.aCE.srcFacChan  = theCInfo.SrcFacStsMap.FindLowestInUseSts()+1;
        aConnection.aCE.dstFacPort  = theCInfo.DstFac;
        aConnection.aCE.dstFacChan  = theCInfo.DstFacStsMap.FindLowestInUseSts()+1;
        
        aConnectionTwo.aCE.srcFacPort  = aCInfo_rmv.SrcFac; 
        aConnectionTwo.aCE.srcFacChan  = aCInfo_rmv.SrcFacStsMap.FindLowestInUseSts()+1;
        aConnectionTwo.aCE.dstFacPort  = aCInfo_rmv.DstFac;
        aConnectionTwo.aCE.dstFacChan  = aCInfo_rmv.DstFacStsMap.FindLowestInUseSts()+1;
        
        if (theResponseNeeded)
            myBbAction->AddInputRegion(aRollResRegionPtr);
        myBbAction->AddOutputRegion(aRollCmdRegionPtr, false, false);                
        (*aRollCmdRegionPtr)[0].SetRollConnectKeyOne(aConnection);
        (*aRollCmdRegionPtr)[0].SetRollConnectKeyTwo(aConnectionTwo);
        (*aRollCmdRegionPtr)[0].SetRollInfo(aRollInfo);
        (*aRollCmdRegionPtr)[0].SetRollCommand(ROLL_CMD_REQ_ADD);            
        (*aRollCmdRegionPtr)[0].SetRollCommandID(myRollCommandID);
        myResponseFlag |= (1 << theCInfo.SlotID);

        aRollCmdRegionPtr->IncModificationCounter();
        aRollCmdRegionPtr->UpdateNotify();
        myBbAction->RemoveOutputRegion(aRollCmdRegionPtr);
        
        if (0 != myDebugLevel )
        {
            char    aDebugMsg[DEBUG_MSG_LEN];
            sprintf(aDebugMsg,"ADD: %sResponse expected for: (%d-%d)-%d,%d -> %d,%d",
                    theResponseNeeded ? "":"No ", theCInfo.ShelfID, theCInfo.SlotID,
                    aConnection.aCE.srcFacPort, aConnection.aCE.srcFacChan,
                    aConnection.aCE.dstFacPort, aConnection.aCE.dstFacChan);
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL19, aDebugMsg);
        }
        
        //--- Note: the update notify should be done after the command is sent 
        aConfigRegionPtr->UpdateNotify();
        aMCRegionPtr->UpdateNotify();
        aRTRegionPtr->UpdateNotify();         
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::NanoMeshStartRoll()
{
    TSXC_RollConnInfo   aCInfo_post;
    uint8               previousSlot;    
    bool                responseNeeded;
    int                 count;
      
    if (0 != myDebugLevel)
    {
        char    aDebugMsg[DEBUG_MSG_LEN];
        sprintf(aDebugMsg,  
                "New SRC count: %d, Remove connections: %d, post connections: %d and RollQueues: %d",
                myRollQueue[0].newSrcConnInfo.size(), myRollQueue[0].removeConnInfo.size(),   
                myRollQueue[0].postConnInfo.size(),   myRollQueue.size());
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL19, aDebugMsg);
    }
    myResponseFlag = 0;
    myRollCommandID++;
    
    //--- In the simple roll there is no need to cutoff the existing traffic instead set the new connection.
    //--- Set the MCRT region as per new connection. The Destination route info is already send by TSXC-CS.
    //--- Send roll query to post connection module, send simple roll command to new src module.
    //--- Wait for both response. Then apply the post connection. At this point the roll is done.
    //--- The agent will resend the connection at later time to clean the old connections.
        
    START_TIME(TSXC_DEBUG_LEVEL18);
    //--- Query one or two module that route info is set okay on the post or final destination module.
    for (count=0, previousSlot=0; count < (int) myRollQueue[0].postConnInfo.size(); count++)
    {
        aCInfo_post = myRollQueue[0].postConnInfo[count];
        responseNeeded = ((count == 0) || (previousSlot != aCInfo_post.SlotID));
        SendQueryRemoteSrcAdded(aCInfo_post, responseNeeded);
        previousSlot = aCInfo_post.SlotID;
    }
    myRollState = ROLL_WAIT_FOR_RES_FROM_FDM;        
    myPeriodicProcess->WakeUp();       
}
/*
//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::SendQueryActivateStatus(TSXC_RollConnInfo theCInfo, bool theResponseNeeded)
{
    TEL_BbRegionBaseImp<TSXC_RollCommand>*  aRollCmdRegionPtr;
    TEL_BbRegionBaseImp<TSXC_RollResponse>* aRollResRegionPtr;
                   
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();
    if (NULL != aCardPtr)
    { 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        aRollCmdRegionPtr = xcApp.GetRollCommand_Region();
        aRollResRegionPtr = xcApp.GetRollResponse_Region();
        
        myBbAction->AddOutputRegion(aRollCmdRegionPtr, false, false);        
        if (theResponseNeeded)
        {          
            myBbAction->AddInputRegion(aRollResRegionPtr);
            (*aRollCmdRegionPtr)[0].SetRollCommand(ROLL_CMD_REQ_ASQ);
            (*aRollCmdRegionPtr)[0].SetRollCommandID(myRollCommandID);
            myResponseFlag |= (1 << theCInfo.SlotID);
            aRollCmdRegionPtr->IncModificationCounter();
            aRollCmdRegionPtr->UpdateNotify();
        }
        myBbAction->RemoveOutputRegion(aRollCmdRegionPtr);
                
        if (0 != myDebugLevel )
        {
            char    aDebugMsg[DEBUG_MSG_LEN];
            sprintf(aDebugMsg,"%sResponse expected for this query for activation status: (%d-%d) ",
                    theResponseNeeded ? "":"No ", theCInfo.ShelfID, theCInfo.SlotID );                   
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, aDebugMsg);
        }
    }
}
*/
//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::SendQueryRemoteSrcAdded(const TSXC_RollConnInfo& theCInfo, bool theResponseNeeded)
{
    TEL_BbRegionBaseImp<TSXC_RollCommand>*  aRollCmdRegionPtr;
    TEL_BbRegionBaseImp<TSXC_RollResponse>* aRollResRegionPtr;
    TSXC_Roll_Info          aRollInfo;
    
    memset(&aRollInfo,0,sizeof(TSXC_Roll_Info));
    aRollInfo.RemoteSrcChan = theCInfo.RemoteSrcChan;                
    aRollInfo.RemoteSrcSlot = theCInfo.RemoteSrcSlot;                
    aRollInfo.DestChanIndex = theCInfo.DestChanIndex;  
                    
    T6100_ShelfIf* aShelfPtr = T6100_MainAppIf::Instance().GetShelfPtr(theCInfo.ShelfID);
    T6100_SlotIf*  aSlotPtr  = aShelfPtr->GetSlotPtr(theCInfo.SlotID);
    T6100_CardIf*  aCardPtr  = aSlotPtr->GetSmartCardPtr();
    if (NULL != aCardPtr)
    { 
        TSXC_BaseApplication& xcApp = aCardPtr->GetXCAppIf().GetXCApp();
        aRollCmdRegionPtr = xcApp.GetRollCommand_Region();
        aRollResRegionPtr = xcApp.GetRollResponse_Region();
        
        myBbAction->AddOutputRegion(aRollCmdRegionPtr, false, false);        
        if (theResponseNeeded)
        {          
            myBbAction->AddInputRegion(aRollResRegionPtr);
            (*aRollCmdRegionPtr)[0].SetRollInfo(aRollInfo);            
            (*aRollCmdRegionPtr)[0].SetRollCommand(ROLL_CMD_REQ_RSQ);
            (*aRollCmdRegionPtr)[0].SetRollCommandID(myRollCommandID);
            myResponseFlag |= (1 << theCInfo.SlotID);
            
            aRollCmdRegionPtr->IncModificationCounter();
            aRollCmdRegionPtr->UpdateNotify();
        }
        myBbAction->RemoveOutputRegion(aRollCmdRegionPtr);        
        
        if (0 != myDebugLevel )
        {
            char    aDebugMsg[DEBUG_MSG_LEN];
            sprintf(aDebugMsg,"%sResponse expected for this query: (%d-%d)-DstChanIndex: %d, RemoteSrc: %d RemoteSlot: %d",
                    theResponseNeeded ? "":"No ", theCInfo.ShelfID, theCInfo.SlotID,
                    aRollInfo.DestChanIndex, aRollInfo.RemoteSrcChan, aRollInfo.RemoteSrcSlot);                   
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, aDebugMsg);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::SetSourceMC(const TSXC_RollConnInfo& theCInfo, XC_ConnAction Action)
{
    TSXC_RollConnInfo*  aNewSrcInfoPtr = NULL;
    int                 aSize = 0;
    
    if (XC_CONNECT == Action)
    {
        if (myRollQueue.size() > 0) 
        {
            aSize = myRollQueue[myRollQueue.size()-1].newSrcConnInfo.size();
            if (aSize > 0)
            {
                aNewSrcInfoPtr = &(myRollQueue[myRollQueue.size()-1].newSrcConnInfo[aSize-1]);
            }
        }
    }
    else
    {
        if (myRollQueue.size() > 0) 
        {
            aSize = myRollQueue[myRollQueue.size()-1].removeConnInfo.size();
            if (aSize > 0)
            {
                aNewSrcInfoPtr = &(myRollQueue[myRollQueue.size()-1].removeConnInfo[aSize-1]);
            }
        }        
    }
    
    if (NULL != aNewSrcInfoPtr)
    {
         aNewSrcInfoPtr->MulticastId            = theCInfo.MulticastId;    
         aNewSrcInfoPtr->MulticastIMUXLMap      = theCInfo.MulticastIMUXLMap;
         aNewSrcInfoPtr->MulticastIMUXPMap      = theCInfo.MulticastIMUXPMap;
         aNewSrcInfoPtr->MulticastIdFlex        = theCInfo.MulticastIdFlex;
         aNewSrcInfoPtr->MulticastIMUXLMapFlex  = theCInfo.MulticastIMUXLMapFlex;
         aNewSrcInfoPtr->MulticastIMUXPMapFlex  = theCInfo.MulticastIMUXPMapFlex;
         aNewSrcInfoPtr->ChannelIndex           = theCInfo.ChannelIndex;
         aNewSrcInfoPtr->ChannelCount           = theCInfo.ChannelCount;        
    }
    else
    {
        FC_REPORT_ERROR(FC_LogicError, "TSXC_RA->SetSourceMC(), trouble adding Muiticast info.");
    }                       
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::SetRouteInfo(CT_ShelfId theShelfID, UINT8 theSlotID, int theChanIndex, int theSrcChan, UINT8 theSrcSlot)
{
    TSXC_RollConnInfo*  aDestInfoPtr = NULL;
    int                 aSize = 0;
    if (myRollQueue.size() > 0)
    {
        aSize = myRollQueue[myRollQueue.size()-1].postConnInfo.size();
        if (aSize > 0)
        {
            aDestInfoPtr = &(myRollQueue[myRollQueue.size()-1].postConnInfo[aSize-1]);
        }        
    }
    if (NULL != aDestInfoPtr && aDestInfoPtr->ShelfID == theShelfID && aDestInfoPtr->SlotID ==  theSlotID)
    {
        aDestInfoPtr->DestChanIndex =  (UINT16) theChanIndex;
        aDestInfoPtr->RemoteSrcChan =  (UINT16) theSrcChan;
        aDestInfoPtr->RemoteSrcSlot =  (UINT8)  theSrcSlot;     
    }
    else
    {
        FC_REPORT_ERROR(FC_LogicError, "TSXC_RA->SetRouteInfo(), trouble adding route info.");
    }
}                                                
//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::AddNewSrcConnection(const TSXC_RollConnInfo& theNewSrc)
{
    if (myRollQueue.size() > 0)
        myRollQueue[myRollQueue.size()-1].newSrcConnInfo.push_back(theNewSrc);        
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::AddPostConnection(const TSXC_RollConnInfo& theNewDst)
{
    if (myRollQueue.size() > 0)
        myRollQueue[myRollQueue.size()-1].postConnInfo.push_back(theNewDst);        
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::AddSpfabConnection(const TSXC_RollConnInfo& theSpfabConn)
{
    if (myRollQueue.size() > 0)
        myRollQueue[myRollQueue.size()-1].spfabConnInfo.push_back(theSpfabConn);            
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::AddRemoveConnection(const TSXC_RollConnInfo& theRemoveConn)
{
    //--- Here we check remove connection output Channel must not be same as New source modules output channel 
    //--- on the same module(solt). This filter is need to avoid removing the exiting connections.
    bool removeOkay = true;
    TSXC_RollConnInfo aCInfo;
    
    if (myRollQueue.size() > 0)
    {
        for (int cnt=0; cnt < (int) myRollQueue[myRollQueue.size()-1].newSrcConnInfo.size(); cnt++)
        {
            aCInfo = myRollQueue[myRollQueue.size()-1].newSrcConnInfo[cnt];
            if ((aCInfo.SlotID == theRemoveConn.SlotID) &&
                    (aCInfo.DstFacStsMap.FindLowestInUseSts() ==  
                        theRemoveConn.DstFacStsMap.FindLowestInUseSts()))
                            removeOkay = false;
        }
        if (true == removeOkay)
            myRollQueue[myRollQueue.size()-1].removeConnInfo.push_back(theRemoveConn); 
    }                   
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::AddSpfabRemoveConnection(const TSXC_RollConnInfo& theRemoveConn)
{
    //--- Here we check remove connection when both output slot and output Channel must not be same 
    //--- as New spfab connection's output slot and output channel. 
    //--- This filter is need to avoid removing the exiting connections.
    bool removeOkay = true;
    TSXC_RollConnInfo aCInfo;
    
    if (myRollQueue.size() > 0)
    {
        for (int cnt=0; cnt < (int) myRollQueue[myRollQueue.size()-1].spfabConnInfo.size(); cnt++)
        {
            aCInfo = myRollQueue[myRollQueue.size()-1].spfabConnInfo[cnt];
            if ((aCInfo.DstFac == theRemoveConn.DstFac) && 
                    (aCInfo.DstFacStsMap.FindLowestInUseSts() ==  
                        theRemoveConn.DstFacStsMap.FindLowestInUseSts()))
                            removeOkay = false;
        }
        if (true == removeOkay)
            myRollQueue[myRollQueue.size()-1].removeConnInfo.push_back(theRemoveConn); 
    }                   
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::SetDebugLevel(int theValue)
{
    myDebugLevel = theValue;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollAction::Run( FC_Object* theObject )
{
	FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
//----------------------------------------------------------------------------------------------------------------------
