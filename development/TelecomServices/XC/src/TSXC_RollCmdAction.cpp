/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     Smart cards only
 AUTHOR   :     Nov, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_RollCmdAction  Class Implementation
--------------------------------------------------------------------------*/
#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_RollCmdAction.h>
#include <XC/TSXC_RollMsgAction.h>
#include <PII_TickTimer.h>
                               
//----------------------------------------------------------------------------------------------------------------------
//--- Constructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_RollCmdAction::TSXC_RollCmdAction(T6100_CardIf& theCardContext):
                        TSXC_BaseAction(theCardContext),
                        myXcAgCfg_Region(NULL),
                        myLineTxMessageRegion(NULL),
                        myPortTxMessageRegion(NULL),
                        myRollCommand_Region(NULL),
                        myRollResponse_Region(NULL),
                        myRollStatus_Region(NULL),
                        myRollRxStatus_Region(NULL),
                        myBrMaskRegion(NULL),
                        myRTRegion(NULL)
{
    myLastRollCommand  = ROLL_CMD_NOREQ;
    myRollCmdState     = ROLL_CMD_IDLE;    
    myLastRollCmdState = myRollCmdState;
    myActivationFlag = false;
    memset(&myRmvRollInfo, 0, sizeof(TSXC_Roll_Info));
    memset(&myAddRollInfo, 0, sizeof(TSXC_Roll_Info));
}

//----------------------------------------------------------------------------------------------------------------------
//--- Destructor
//----------------------------------------------------------------------------------------------------------------------
TSXC_RollCmdAction::~TSXC_RollCmdAction()
{

}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::AddInputRegions()
{
    myBbAction->AddInputRegion(myXcAgCfg_Region);
    myBbAction->AddInputRegion(myRollCommand_Region);
    if (CARD_FAM_SSM == myCardContext.GetCardFamily().GetCardFamily())
    {    
        myBbAction->AddInputRegion(myRollRxStatus_Region, false);
        myBbAction->AddInputRegion(myRTRegion, false);        
    } 
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::RemoveInputRegions()
{
    myBbAction->RemoveInputRegion(myXcAgCfg_Region);
    myBbAction->RemoveInputRegion(myRollCommand_Region);
    if (CARD_FAM_SSM == myCardContext.GetCardFamily().GetCardFamily())
    {     
        myBbAction->RemoveInputRegion(myRollRxStatus_Region);
        myBbAction->RemoveInputRegion(myRTRegion);        
    }     
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::AddOutputRegions()
{
    myBbAction->AddOutputRegion(myRollResponse_Region, false, false);
    if (CARD_FAM_SSM == myCardContext.GetCardFamily().GetCardFamily())
    {
        myBbAction->AddOutputRegion(myRollStatus_Region, false, false);
        myBbAction->AddOutputRegion(myBrMaskRegion, false, false);        
        myBbAction->AddOutputRegion(myLineTxMessageRegion, false, false);
        myBbAction->AddOutputRegion(myPortTxMessageRegion, false, false);
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::RemoveOutputRegions()
{
    myBbAction->RemoveOutputRegion(myRollResponse_Region);
    if (CARD_FAM_SSM == myCardContext.GetCardFamily().GetCardFamily())
    {
        myBbAction->RemoveOutputRegion(myRollStatus_Region);
        myBbAction->RemoveOutputRegion(myBrMaskRegion);                      
        myBbAction->RemoveOutputRegion(myLineTxMessageRegion);
        myBbAction->RemoveOutputRegion(myPortTxMessageRegion);
    }   
}

//----------------------------------------------------------------------------------------------------------------------
//--- Do the work
//
FC_Object* TSXC_RollCmdAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    if (myRollCommand_Region)
    {
        INT32 aRollCommand = (*myRollCommand_Region)[0].GetRollCommand();
        bool IsSameModule = false;
        if (0 != myDebugLevel)
        {
            char aDebugMsg[120];
            if ((aRollCommand != myLastRollCommand) || (myRollCmdState != myLastRollCmdState))
            {
                int32 aRollCmdId = (*myRollCommand_Region)[0].GetRollCommandID();
                int32 aRollRxCmdId = -1;
                int32 aRollMsgRcvd = -1;

                if (myRollRxStatus_Region)
                {
                    aRollRxCmdId = (*myRollRxStatus_Region)[0].GetRollCommandID();
                    aRollMsgRcvd = (*myRollRxStatus_Region)[0].GetRollMsgRcvd();
                }

                sprintf(aDebugMsg,"RCmdA->CMD:%s(Pre:%s), CMDState:%s(Pre: %s)R-ID:%d ST-ID:%d MSG-ID:%d", 
                                    RollCommandToText(aRollCommand), RollCommandToText(myLastRollCommand),
                                    RollStateToText((int) myRollCmdState), RollStateToText((int) myLastRollCmdState),
                                    aRollCmdId, aRollRxCmdId, aRollMsgRcvd);
                XCDEBUG_INFO(TSXC_DEBUG_LEVEL18, aDebugMsg);
            }
        }
                 
        switch(myRollCmdState)
        {
            case ROLL_CMD_IDLE:
                    switch(aRollCommand)
                    {
                        case ROLL_RES_NONE:
                        case ROLL_CMD_NOREQ:
                                //--- do nothing
                                break;
                        case ROLL_CMD_REQ:
                                myRollCmdState = ROLL_CMD_INPROGRESS;
                                SetAddConnectInfo(aRollCommand);
                                CheckConnection(aRollCommand);                        
                                break;
                                                        
                        case ROLL_CMD_REQ_ADD:
                                myActivationFlag = false;
                                myRollCmdState = ROLL_CMD_INPROGRESS;                    
                                SetAddConnectInfo(aRollCommand, true);
                                CheckConnection(aRollCommand); 
                                break;
                                
                        case ROLL_CMD_REQ_RMV:
                                myRollCmdState = ROLL_CMD_INPROGRESS;                          
                                SetRmvConnectInfo();              
                                break;
       
                        case ROLL_CMD_REQ_RSQ:
                                myRollCmdState = ROLL_CMD_INPROGRESS;
                                IsRemoteSrcAdded();
                                break;        
                    }
                    if (!(aRollCommand == ROLL_CMD_REQ_RMV))
                        break;
                    //--- else fall through 
            case ROLL_CMD_INPROGRESS:
                    switch(aRollCommand)
                    {
                        case ROLL_CMD_REQ:
                                CheckConnection(aRollCommand);
                                break;

                        case ROLL_CMD_REQ_RMV:
                                if (ROLL_CMD_REQ_ADD == myLastRollCommand)
                                    SetRmvConnectInfo();
                                IsSameModule = (myRmvRollInfo.OldSrcShelf == myRmvRollInfo.NewSrcShelf && 
                                                myRmvRollInfo.OldSrcSlot ==  myRmvRollInfo.NewSrcSlot);
                                if (myRollRxStatus_Region)
                                {
                                    if ((*myRollCommand_Region)[0].GetRollCommandID() == (*myRollRxStatus_Region)[0].GetRollCommandID() || 
                                          IsSameModule)
                                    {
                                        if (IsSameModule ||
                                           (*myRollRxStatus_Region)[0].GetRollMsgRcvd() == ROLL_MSG_WAIT)
                                        {
                                            XCDEBUG_INFO(TSXC_DEBUG_LEVEL18, "RCmdA->Got Message from New src moulde" );                                    
                                            myRollCmdState = ROLL_CMD_COMPLETE;
                                            //if (myRmvRollInfo.IsResponseExpected)
                                            SendResponse(ROLL_RES_DONE);
                                            SetStatus(true, aRollCommand);
                                        }
                                    }
                                }
                                break;

                        case ROLL_CMD_REQ_ADD:
                                CheckForActivation();
                                if (myActivationFlag)
                                {
                                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL18,"RCmdA->Got activation okay from old src moulde");                                                               
                                    myRollCmdState = ROLL_CMD_COMPLETE;
                                    SetStatus(true, aRollCommand);                                
                                    ClearAddRmvConnectInfo(); // This is to remove any mask info
                                }                        
                                else 
                                {
                                    if ((*myRollResponse_Region)[0].GetRollResponse() != ROLL_RES_DONE)
                                        CheckConnection(aRollCommand);
                                }
                                break;

                        case ROLL_CMD_REQ_RSQ:
                                IsRemoteSrcAdded();                    
                                break;                                                  
                    }
                    if (ROLL_CMD_NOREQ != aRollCommand)            
                        break;
                    // else fall through and clean up
                    
            case ROLL_CMD_COMPLETE:
                    switch(aRollCommand)
                    {
                        case ROLL_CMD_REQ_RMV:
                        case ROLL_CMD_REQ_ADD:
                        case ROLL_CMD_REQ_RSQ:                    
                        case ROLL_CMD_REQ:
                                //--- do nothing
                                XCDEBUG_INFO(TSXC_DEBUG_LEVEL18, "RCmdA->Roll completed");
                                break;                                            
                        case ROLL_RES_NONE:
                        case ROLL_CMD_NOREQ:
                                if (ROLL_CMD_REQ_RMV == myLastRollCommand)
                                        ClearAddRmvConnectInfo();

                                //--- This is just to clear the response after the command/response sequence is complete
                                if ((*myRollResponse_Region)[0].GetRollResponse() == ROLL_RES_DONE)
                                    SendResponse(ROLL_RES_NONE);
                                else
                                   SendResponse(ROLL_RES_DONE);
                                XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, "RCmdA->Roll completed and  resets");   
                                myRollCmdState = ROLL_CMD_IDLE;
                                myActivationFlag = false;
                                break;                                                                   
                    }
                    break;            
                
            default:
                    XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, "RCmdA->Roll CMD state invalid on action");                    
        }
        myLastRollCommand  = aRollCommand;
        myLastRollCmdState = myRollCmdState;     
    }
	return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SendResponse(INT32 theResponse)
{
    if (myRollResponse_Region && myRollCommand_Region)
    {
        (*myRollResponse_Region)[0].SetRollCommandID((*myRollCommand_Region)[0].GetRollCommandID());
        (*myRollResponse_Region)[0].SetRollResponse(theResponse);

        //--- No need to send a "none message" because this is to clean the response at the end.
        if (ROLL_RES_NONE != theResponse)
        {
            myRollResponse_Region->IncModificationCounter();
            myRollResponse_Region->UpdateNotify();
        }
        if (0 != myDebugLevel)
        {
            char aDebugMsg[80];
            int32 aRollCmdId = -1;

            if (myRollCommand_Region)
            {
                aRollCmdId = (*myRollCommand_Region)[0].GetRollCommandID();
            }

            sprintf(aDebugMsg,"RCmdA->Sent a Response as %s, for the ID: %d",
                                RollCommandToText(theResponse), aRollCmdId);
            XCDEBUG_INFO(TSXC_DEBUG_LEVEL19, aDebugMsg);
        }
    }        
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetStatus(bool theNotifyOkay, INT32 theRollCommand)
{
    if (NULL != myRollStatus_Region)
    {
        if (ROLL_CMD_REQ_RMV == theRollCommand)
        {
            (*myRollStatus_Region)[0].SetRollConnectRmvKey(myRmvConnectKey);
            (*myRollStatus_Region)[0].SetRollInfo(myRmvRollInfo);
        }
        else
        {
            (*myRollStatus_Region)[0].SetRollConnectAddKey(myAddConnectKey);
            (*myRollStatus_Region)[0].SetRollInfo(myAddRollInfo);            
        }       
        (*myRollStatus_Region)[0].SetRollCmdState(myRollCmdState);
        (*myRollStatus_Region)[0].SetRollCommand(theRollCommand);
        
        if (theNotifyOkay)
        {
            myRollStatus_Region->IncModificationCounter();
            myRollStatus_Region->UpdateNotify();
        }                  
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::CheckForActivation()
{
    if (myRollCommand_Region && myRollRxStatus_Region)
    {
        INT32   aRollCmdID   = (*myRollCommand_Region)[0].GetRollCommandID();
        INT32   aRollRxCmdID = (*myRollRxStatus_Region)[0].GetRollCommandID();
        INT32   aRollRxMsg   = (*myRollRxStatus_Region)[0].GetRollMsgRcvd();

        if (aRollCmdID ==  aRollRxCmdID && aRollRxMsg == ROLL_MSG_ACTIVATE)
        {
            myActivationFlag = true;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::CheckConnection(INT32 theRollCommand)
{
    CT_CardType     aCardType = myXcAgCfg_Region->GetMyCardType();
    const int*      aConfigMapPtr = SMTMUConfigMap;
    TSXC_Connect*   aXcAgCfgObjectPtr;
    TSXC_Connection aConn;
             
    //
    // Point to config map region based on card type.
    //
    if (aCardType == CARD_TYPE_SMTMU)
    {
        aConfigMapPtr = SMTMUConfigMap;
    }
    else if (aCardType == CARD_TYPE_SPFAB)
    {
        aConfigMapPtr = SPFABConfigMap;
    }
    else if ((aCardType == CARD_TYPE_SSMX) || (aCardType == CARD_TYPE_SSMD))
    {
        aConfigMapPtr = SSMConfigMap;
    }
    else if (aCardType == CARD_TYPE_FGTMM)
    {
        aConfigMapPtr = FGTMMConfigMap;
    }
    else if ((aCardType == CARD_TYPE_OTNMX) || (aCardType == CARD_TYPE_OTNMD))
    {
        aConfigMapPtr = OTNMConfigMap;
    }
    else
    {
        FC_REPORT_ERROR(FC_LogicError, "Unexpected Map pointer");
    }
    int facOffset = *(aConfigMapPtr + myAddConnectKey.aCE.dstFacPort);
    aXcAgCfgObjectPtr = &((*myXcAgCfg_Region)[facOffset + myAddConnectKey.aCE.dstFacChan - 1]);
                
    aConn.aCE.srcFacPort = aXcAgCfgObjectPtr->GetInputFacility();;
    aConn.aCE.srcFacChan = aXcAgCfgObjectPtr->GetInputFacilityEndpoint();
    aConn.aCE.dstFacPort = aXcAgCfgObjectPtr->GetOutputFacility();
    aConn.aCE.dstFacChan = aXcAgCfgObjectPtr->GetOutputFacilityEndpoint();
    
    if ((aConn.aCKey == myAddConnectKey.aCKey) && (aXcAgCfgObjectPtr->GetState() == CT_XC_STATE_CONNECTED))
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL19, "RCmdA->CheckConnection(), Found the matching XC");
        if (myAddRollInfo.IsResponseExpected)
        { 
            //--- Match found for this roll connection.
            SendResponse(ROLL_RES_DONE);
        }
        if (theRollCommand == ROLL_CMD_REQ)
        {
            myRollCmdState = ROLL_CMD_COMPLETE;
            SetStatus(true, theRollCommand);
        }
        else
        {
            SetStatus(false, theRollCommand);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::IsRemoteSrcAdded()
{
    if (myRollCommand_Region)
    {
        TSXC_S3RtRegion<TSXC_S3Route>* aRTRegionPtr = NULL;
        TSXC_Roll_Info   aRollInfo = (*myRollCommand_Region)[0].GetRollInfo();   
        aRTRegionPtr = myCardContext.GetXCAppIf().GetXCApp().GetS3RtCfgRegion();
        if (NULL != aRTRegionPtr && aRollInfo.DestChanIndex < (XC_MAX_XC_SSM_IM_LINE+XC_MAX_XC_SSM_IM_PORT))
        {
            TSXC_S3Route* aRTObjPtr = &(*aRTRegionPtr)[aRollInfo.DestChanIndex];
            for (uint8 anIndex=0; anIndex < XC_MAX_SRC_ENDPT; anIndex++)
            {
                if (aRollInfo.RemoteSrcSlot == aRTObjPtr->GetSrcSlot(anIndex) &&
                    aRollInfo.RemoteSrcChan == aRTObjPtr->GetSrcFacilityEndpoint(anIndex))
                {
                    SendResponse(ROLL_RES_DONE);
                    myRollCmdState = ROLL_CMD_COMPLETE;                
                    break;
                }     
            }
        }
    } 
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetAddConnectInfo(INT32 theRollCommand, bool IsSSMNano)
{
    if (myRollCommand_Region)
    {
        myOtherModuleConnectKey = (*myRollCommand_Region)[0].GetRollConnectKeyTwo();
        myAddConnectKey = (*myRollCommand_Region)[0].GetRollConnectKeyOne();
        myAddRollInfo   = (*myRollCommand_Region)[0].GetRollInfo();
        
        if (IsSSMNano && (theRollCommand == ROLL_CMD_REQ_ADD))
        {    
            if (NULL != myBrMaskRegion)
            {
                //--- Mute the transmitter to the remote module.
                UINT16 aMask = ~(1 << (myAddRollInfo.RemoteDstSlot-1));
                (*myBrMaskRegion)[0].SetMCastImuxLMask(aMask);
                (*myBrMaskRegion)[0].SetMCastImuxPMask(aMask);
                (*myBrMaskRegion)[0].SetMCastId(myAddRollInfo.MulticastId);
                (*myBrMaskRegion)[0].SetMaskAction(CT_XC_BR_MASK_AND);
                myBrMaskRegion->IncModificationCounter();
                myBrMaskRegion->UpdateNotify();                  
            }

            XCDEBUG_INFO(TSXC_DEBUG_LEVEL20, "RCmdA->Setting the Add connection and setting the MSG WAIT");
            
            //--- this is to setup a mail box to receive the activation message from the old source module.
            CT_IntfId aSrcPort;
            CT_IntfId aDstPort;
            UINT8     aSrcChan;
            UINT8     aDstChan;

            if (GetPortInfo(myAddConnectKey, aSrcPort, aSrcChan) && 
                GetPortInfo(myOtherModuleConnectKey, aDstPort, aDstChan))
            {
                CT_Port cTSrcPort( myAddRollInfo.NewSrcShelf, myAddRollInfo.NewSrcSlot, aSrcPort, FAC_SUBTYPE_ALL, aSrcChan);
                CT_Port cTDstPort( myAddRollInfo.OldSrcShelf, myAddRollInfo.OldSrcSlot, aDstPort, FAC_SUBTYPE_ALL, aDstChan);
                SetTxMsgRequest(cTSrcPort, cTDstPort, (UINT8) ROLL_MSG_WAIT);               
            }
            else
            {
                FC_REPORT_ERROR(FC_LogicError, "RCmdA->SetAddConnectInfo(), trouble with port info.");
            }
        }
        SetStatus(true, theRollCommand);
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetRmvConnectInfo()
{
    if (myRollCommand_Region)
    {
        myOtherModuleConnectKey = (*myRollCommand_Region)[0].GetRollConnectKeyTwo();
        myRmvConnectKey = (*myRollCommand_Region)[0].GetRollConnectKeyOne();
        myRmvRollInfo   = (*myRollCommand_Region)[0].GetRollInfo();

        if (NULL != myBrMaskRegion)
        {
            //--- Mute the transmitter to the remote module.
            UINT16 aMask = ~(1 << (myRmvRollInfo.RemoteDstSlot-1));
            (*myBrMaskRegion)[0].SetMCastImuxLMask(aMask);
            (*myBrMaskRegion)[0].SetMCastImuxPMask(aMask);
            (*myBrMaskRegion)[0].SetMCastId(myRmvRollInfo.MulticastId);
            (*myBrMaskRegion)[0].SetMaskAction(CT_XC_BR_MASK_AND);
            myBrMaskRegion->IncModificationCounter();
            myBrMaskRegion->UpdateNotify();        
        }

        XCDEBUG_INFO(TSXC_DEBUG_LEVEL20, "RCmdA->Setting the RMV connection and setting the MSG ACTIVATE");
        
        //--- this is to setup a mail box to transmit the activation message to new source module.
        CT_IntfId aSrcPort;
        CT_IntfId aDstPort;
        UINT8     aSrcChan;
        UINT8     aDstChan;
            
        if (GetPortInfo(myRmvConnectKey, aSrcPort, aSrcChan) && 
            GetPortInfo(myOtherModuleConnectKey, aDstPort, aDstChan))
        {
            CT_Port cTSrcPort( myRmvRollInfo.OldSrcShelf, myRmvRollInfo.OldSrcSlot, aSrcPort, FAC_SUBTYPE_ALL, aSrcChan);
            CT_Port cTDstPort( myRmvRollInfo.NewSrcShelf, myRmvRollInfo.NewSrcSlot, aDstPort, FAC_SUBTYPE_ALL, aDstChan);
            SetTxMsgRequest(cTSrcPort, cTDstPort, (UINT8) ROLL_MSG_ACTIVATE);               
        }
        else
        {
            FC_REPORT_ERROR(FC_LogicError, "RCmdA->SetRmvConnectInfo(), trouble with port info.");
        }
        SetStatus(true, ROLL_CMD_REQ_RMV);
    }
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::ClearAddRmvConnectInfo()
{
    myAddConnectKey.aCKey = 0;
    myRmvConnectKey.aCKey = 0;
    memset(&myAddRollInfo, 0, sizeof(TSXC_Roll_Info));
    memset(&myRmvRollInfo, 0, sizeof(TSXC_Roll_Info));
    
    if ( (CARD_FAM_SSM == myCardContext.GetCardFamily().GetCardFamily()) &&
         (myRollRxStatus_Region) )
    {
        if ((*myLineTxMessageRegion)[0].GetMessage() != ROLL_MSG_NONE)
        {
            (*myLineTxMessageRegion)[0].Reset();    //--- Mute the transmitter
            myLineTxMessageRegion->IncModificationCounter();
            myLineTxMessageRegion->UpdateNotify();
        }
        if ((*myPortTxMessageRegion)[0].GetMessage() != ROLL_MSG_NONE)
        {
            (*myPortTxMessageRegion)[0].Reset();    //--- Mute the transmitter
            myPortTxMessageRegion->IncModificationCounter();
            myPortTxMessageRegion->UpdateNotify();
        }
        (*myRollRxStatus_Region)[0].Reset(); //--- Clear RxStatus region for the next use.
        (*myBrMaskRegion)[0].Reset();     //--- Clear mask region
        myBrMaskRegion->IncModificationCounter();
        myBrMaskRegion->UpdateNotify();
         
        (*myRollStatus_Region)[0].Reset();      //--- clear status
        myRollStatus_Region->IncModificationCounter();
        myRollStatus_Region->UpdateNotify();        
    }

    XCDEBUG_INFO(TSXC_DEBUG_LEVEL19, "RCmdA->ClearAddRmvConnectInfo() reset mask/status/xmit");           
}

//----------------------------------------------------------------------------------------------------------------------
bool TSXC_RollCmdAction::GetPortInfo(TSXC_Connection theXC, CT_IntfId& thePort, UINT8& theChan)
{
    bool aResult = true;
    UINT8 aXCPort = theXC.aCE.srcFacPort;
    theChan = theXC.aCE.srcFacChan;
    if (aXCPort == XC_SSM_IM_LINE_FACILITY_ID || aXCPort == XC_SSM_IM_PORT_FACILITY_ID)
    {
        aXCPort = theXC.aCE.dstFacPort;
        theChan = theXC.aCE.dstFacChan;
    }
    switch (aXCPort)
    {
        case XC_SSM_DWDM_FACILITY_ID:
                thePort = CT_LINE_SIDE_0;
                break;
        case XC_SSM_TTP_FACILITY_ID:
                thePort = CT_PORT_SIDE_32;
                break;
        case XC_SSM_PORT0_FACILITY_ID: 
        case XC_SSM_PORT1_FACILITY_ID: 
        case XC_SSM_PORT2_FACILITY_ID: 
        case XC_SSM_PORT3_FACILITY_ID: 
        case XC_SSM_PORT4_FACILITY_ID: 
        case XC_SSM_PORT5_FACILITY_ID: 
        case XC_SSM_PORT6_FACILITY_ID: 
        case XC_SSM_PORT7_FACILITY_ID: 
        case XC_SSM_PORT8_FACILITY_ID: 
        case XC_SSM_PORT9_FACILITY_ID: 
        case XC_SSM_PORT10_FACILITY_ID:
        case XC_SSM_PORT11_FACILITY_ID:
        case XC_SSM_PORT12_FACILITY_ID:
                thePort = (CT_IntfId) ((aXCPort - XC_SSM_PORT0_FACILITY_ID) + CT_PORT_SIDE_0);
                break;
        default:
                aResult = false;
    }
    return aResult;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetTxMsgRequest(CT_Port theSrcPort, CT_Port theDstPort, uint8 theMsg)
{
    if (CARD_FAM_SSM == myCardContext.GetCardFamily().GetCardFamily())
    {
        SP_MessageRegion*  aTxMsgRegionPtr = (theSrcPort.myPortId == CT_LINE_SIDE_0) ? 
                                              myLineTxMessageRegion : myPortTxMessageRegion;
        (*aTxMsgRegionPtr)[0].SetMessage(theSrcPort, theDstPort, theMsg);
        aTxMsgRegionPtr->IncModificationCounter();
        aTxMsgRegionPtr->UpdateNotify();                            
    }
}

//----------------------------------------------------------------------------------------------------------------------
const char* TSXC_RollCmdAction::RollCommandToText(int theRollCommand)
{
    switch(theRollCommand)
    {
        case ROLL_CMD_NOREQ:    return ("NOREQ");
        case ROLL_CMD_REQ:      return ("REQ");
        case ROLL_RES_NONE:     return ("NONE");
        case ROLL_RES_DONE:     return ("DONE");
        case ROLL_CMD_REQ_RMV:  return ("RMV");
        case ROLL_CMD_REQ_ADD:  return ("ADD");
        case ROLL_CMD_REQ_ASQ:  return ("ASRSQ");
        case ROLL_CMD_REQ_RSQ:  return ("RSRCQ");
        default:                return ("INVALID");   
    }    
}

//----------------------------------------------------------------------------------------------------------------------
const char* TSXC_RollCmdAction::RollStateToText(int theRollState)
{
    switch(theRollState)
    {
        case ROLL_CMD_IDLE:         return ("IDLE");
        case ROLL_CMD_INPROGRESS:   return ("PROGRESS");
        case ROLL_CMD_COMPLETE:     return ("COMPLETE");
        default:                return ("INVALID");   
    }    
}
           
//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetLineTxSP_MessageRegion(SP_MessageRegion* theTxMessageRegion)
{
    myLineTxMessageRegion = theTxMessageRegion;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetPortTxSP_MessageRegion(SP_MessageRegion* theTxMessageRegion)
{
    myPortTxMessageRegion = theTxMessageRegion;    
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetRollCommand_Region(TEL_BbRegionBaseImp <TSXC_RollCommand> * theRollCommand_Region)
{
    myRollCommand_Region = theRollCommand_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetRollResponse_Region(TEL_BbRegionBaseImp <TSXC_RollResponse> * theRollResponse_Region)
{
    myRollResponse_Region = theRollResponse_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetRollStatus_Region(TEL_BbRegionBaseImp <TSXC_RollStatus> * theRollStatus_Region)
{
    myRollStatus_Region = theRollStatus_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetRollRxStatus_Region(TEL_BbRegionBaseImp <TSXC_RollRxStatus> * theRollRxStatus_Region)
{
    myRollRxStatus_Region = theRollRxStatus_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetXcAgCfg_Region(TSXC_ConfigRegion<TSXC_Connect>* theXcAgCfg_Region)
{
    myXcAgCfg_Region = theXcAgCfg_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetRollBrMask_Region(TSXC_BrMCastMaskRegion<TSXC_BrMCastMask>* theRollBrMask_Region)
{
    myBrMaskRegion   = theRollBrMask_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollCmdAction::SetRTCfgRegion(TSXC_S3RtRegion<TSXC_S3Route>*   theRTRegion)     
{
    myRTRegion = theRTRegion;
}
//----------------------------------------------------------------------------------------------------------------------
