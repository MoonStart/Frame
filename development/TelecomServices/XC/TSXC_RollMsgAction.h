/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     Smart cards only
 AUTHOR   :     Nov, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_RollMsgAction  Class Definition
--------------------------------------------------------------------------*/
#ifndef TSXC_ROLLMSGACTION_H
#define TSXC_ROLLMSGACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <Blackboard/FC_BbAction.h>
#include <SignalProtection/SP_MessageRegion.h>
#include <XC/TSXC_RollCommand.h>
#include <XC/TSXC_RollResponse.h>
#include <XC/TSXC_RollStatus.h>

class FC_BbAction;

#define ROLL_MSG_NONE       0x00
#define ROLL_MSG_ACTIVATE   0x01
#define ROLL_MSG_DEACTIVATE 0x02
#define ROLL_MSG_WAIT       0x03

//----------------------------------------------------------------------------------------------------------------------
class TSXC_RollMsgAction : public FC_Action
{
public:

	// Constructor 
	TSXC_RollMsgAction(); 

	// Destructor
	virtual ~TSXC_RollMsgAction();

	// ***************************************************
	// This method causes this object to execute its main
	// function of monitoring the Roll connections.
	// ***************************************************
	virtual FC_Object* DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam = NULL);

	virtual void Run( FC_Object* theObject = NULL );

	FC_BbAction* GetBbAction() { return myBbAction; }
    void AddInputRegions();
    void RemoveInputRegions();
    void AddOutputRegion( FC_BbRegion* theOutputRegion );
    void RemoveOutputRegion( FC_BbRegion* theOutputRegion );
    
    void SetRollCommand_Region(TEL_BbRegionBaseImp <TSXC_RollCommand>*      theRollCommand_Region);
    void SetRollResponse_Region(TEL_BbRegionBaseImp <TSXC_RollResponse>*    theRollResponse_Region);
    void SetRollRxStatus_Region(TEL_BbRegionBaseImp <TSXC_RollRxStatus>*    theRollRxStatus_Region);
    void SetLineRxSP_MessageRegion(SP_MessageRegion*   theRxMessageRegion);
    void SetLineTxSP_MessageRegion(SP_MessageRegion*   theTxMessageRegion);
    void SetPortRxSP_MessageRegion(SP_MessageRegion*   theRxMessageRegion);
    void SetPortTxSP_MessageRegion(SP_MessageRegion*   theTxMessageRegion);
    void SetDebugLevel(int theValue);
            
private:

	FC_BbAction*                                myBbAction;
    TEL_BbRegionBaseImp <TSXC_RollCommand>*     myRollCommand_Region;
    TEL_BbRegionBaseImp <TSXC_RollResponse>*    myRollResponse_Region;
    TEL_BbRegionBaseImp <TSXC_RollRxStatus>*    myRollRxStatus_Region;
    SP_MessageRegion*                           myLineRxMessageRegion;
    SP_MessageRegion*                           myLineTxMessageRegion;
    SP_MessageRegion*                           myPortRxMessageRegion;    
    SP_MessageRegion*                           myPortTxMessageRegion;    
    INT32                                       myDebugLevel;
};

#endif /* TSXC_ROLLMSGACTION_H */
