/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     Smart cards only
 AUTHOR   :     Nov, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_RollMsgAction  Class Implementation
--------------------------------------------------------------------------*/
#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_RollMsgAction.h>
                                
//*****************************************************************************************************************
//
//--- Constructor
//
TSXC_RollMsgAction::TSXC_RollMsgAction():myBbAction(NULL)
{
	myBbAction  = new FC_BbAction(this);
    myDebugLevel = 0; 
}

//
//--- Destructor
//
TSXC_RollMsgAction::~TSXC_RollMsgAction()
{
	delete myBbAction;
}

//-------------------------------------------------------------------------------------------------------------------------------
//--- Add Output region.  Need this method since regions ptrs are located in SubApps, while XC_Roll_Msg action is in BaseApp.
void TSXC_RollMsgAction::AddOutputRegion( FC_BbRegion* theOutputRegion )
{
    GetBbAction()->AddOutputRegion( theOutputRegion, false, false);
}

//------------------------------------------------------------------------------------------------------------------------------
//--- Remove Output region.  Need this method since regions ptrs are located in SubApps, while XC_Roll_Msg action is in BaseApp.
void TSXC_RollMsgAction::RemoveOutputRegion( FC_BbRegion* theOutputRegion )
{
    GetBbAction()->RemoveOutputRegion( theOutputRegion );
}

//----------------------------------------------------------------------------------------------------------------------
//--- Do the work
//
FC_Object* TSXC_RollMsgAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    bool    aActivateMsgRcvd_Line = false;
    bool    aWaitMsgRcvd_Line     = false;
    bool    aActivateMsgRcvd_Port = false;
    bool    aWaitMsgRcvd_Port     = false;
        
    //--- Process the line side now
    uint8 aTxMsgLine = (*myLineTxMessageRegion)[0].GetMessage();
    uint8 aRxMsgLine = (*myLineRxMessageRegion)[0].GetMessage();
    
    if (ROLL_MSG_WAIT  == aTxMsgLine && ROLL_MSG_ACTIVATE == aRxMsgLine)
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, "RMsgA->Got the Activate message"); 
        aActivateMsgRcvd_Line = true;
    }
    else if (ROLL_MSG_WAIT  == aRxMsgLine && ROLL_MSG_ACTIVATE == aTxMsgLine)
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, "RMsgA->Message Confirmed");
        aWaitMsgRcvd_Line = true;
    }
    
    //--- Process the Port side now    
    uint8 aTxMsgPort = (*myPortTxMessageRegion)[0].GetMessage();
    uint8 aRxMsgPort = (*myPortRxMessageRegion)[0].GetMessage();
    
    if (ROLL_MSG_WAIT  == aTxMsgPort && ROLL_MSG_ACTIVATE == aRxMsgPort)
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, "RMsgA->Got the Activate message");
        aActivateMsgRcvd_Port = true;
    }
    else if (ROLL_MSG_WAIT  == aRxMsgPort && ROLL_MSG_ACTIVATE == aTxMsgPort)
    {
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL17, "RMsgA->Message Confirmed");
        aWaitMsgRcvd_Port = true;
    }
    
    if (aActivateMsgRcvd_Line || aActivateMsgRcvd_Port || aWaitMsgRcvd_Line || aWaitMsgRcvd_Port)
    {
        if (aActivateMsgRcvd_Line || aActivateMsgRcvd_Port)
        {
            (*myRollRxStatus_Region)[0].SetRollMsgSent((int) (aActivateMsgRcvd_Line ? aTxMsgLine : aTxMsgPort));
            (*myRollRxStatus_Region)[0].SetRollMsgRcvd(ROLL_MSG_ACTIVATE);
        }
        else 
        {
            (*myRollRxStatus_Region)[0].SetRollMsgSent((int) (aWaitMsgRcvd_Line ? aTxMsgLine : aTxMsgPort));
            (*myRollRxStatus_Region)[0].SetRollMsgRcvd(ROLL_MSG_WAIT);            
        }
        (*myRollRxStatus_Region)[0].SetRollCommandID((*myRollCommand_Region)[0].GetRollCommandID());
        (*myRollRxStatus_Region)[0].SetRollCommand((*myRollCommand_Region)[0].GetRollCommand());
        myRollRxStatus_Region->IncModificationCounter();
        myRollRxStatus_Region->UpdateNotify();
    }
    if (myDebugLevel != 0)
    {
        char aDebugMsg[100];
        sprintf(aDebugMsg,"RMsgA->Roll ID:%d TXL:%d RXL: %d TXP:%d RXP: %d",     
                            (*myRollCommand_Region)[0].GetRollCommandID(), 
                            (int) aTxMsgLine, (int) aRxMsgLine, (int) aTxMsgPort, (int) aRxMsgPort); 
        XCDEBUG_INFO(TSXC_DEBUG_LEVEL18, aDebugMsg); 
    }
	return NULL;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetLineRxSP_MessageRegion(SP_MessageRegion* theRxMessageRegion)
{
    myLineRxMessageRegion = theRxMessageRegion;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetLineTxSP_MessageRegion(SP_MessageRegion* theTxMessageRegion)
{
    myLineTxMessageRegion = theTxMessageRegion;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetPortRxSP_MessageRegion(SP_MessageRegion* theRxMessageRegion)
{
    myPortRxMessageRegion = theRxMessageRegion;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetPortTxSP_MessageRegion(SP_MessageRegion* theTxMessageRegion)
{
    myPortTxMessageRegion = theTxMessageRegion;    
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetRollCommand_Region(TEL_BbRegionBaseImp <TSXC_RollCommand> * theRollCommand_Region)
{
    myRollCommand_Region = theRollCommand_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetRollResponse_Region(TEL_BbRegionBaseImp <TSXC_RollResponse> * theRollResponse_Region)
{
    myRollResponse_Region = theRollResponse_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetRollRxStatus_Region(TEL_BbRegionBaseImp <TSXC_RollRxStatus> * theRollRxStatus_Region)
{
    myRollRxStatus_Region = theRollRxStatus_Region;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::AddInputRegions()
{
    myBbAction->AddInputRegion(myLineRxMessageRegion, false);
    myBbAction->AddInputRegion(myPortRxMessageRegion, false);        
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::RemoveInputRegions()
{
    myBbAction->RemoveInputRegion(myLineRxMessageRegion);
    myBbAction->RemoveInputRegion(myPortRxMessageRegion);        
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::SetDebugLevel(int theValue)
{
    myDebugLevel = theValue;
}

//----------------------------------------------------------------------------------------------------------------------
void TSXC_RollMsgAction::Run( FC_Object* theObject )
{
	FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}
//----------------------------------------------------------------------------------------------------------------------
