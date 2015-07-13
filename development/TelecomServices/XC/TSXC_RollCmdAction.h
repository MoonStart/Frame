/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     Smart cards only
 AUTHOR   :     Nov, 2009  Kumar C Solai
 DESCRIPTION:   TSXC_RollCmdAction  Class Definition
--------------------------------------------------------------------------*/
#ifndef TSXC_ROLLCMDACTION_H
#define TSXC_ROLLCMDACTION_H

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_RollCommand.h>
#include <XC/TSXC_RollResponse.h>
#include <XC/TSXC_RollStatus.h>
#include <XC/TSXC_RollRxStatus.h>
#include <XC/TSXC_RollMsgAction.h>
	
//------------------------------------------------------------------------------
// This class is responsible for applying stage one Multicast based on
// region changes in Nano mesh mode.
//------------------------------------------------------------------------------
class TSXC_RollCmdAction : public TSXC_BaseAction
{
public:

	// Constructor 
	TSXC_RollCmdAction(T6100_CardIf& theCardContext); 

	// Destructor
	virtual ~TSXC_RollCmdAction();
    
    //-------------------------------------------------------------------------- 
    // This method causes this object to execute its main
    // function of applying Stage One Mulicast Configurations.
    //-------------------------------------------------------------------------- 
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);
    void AddInputRegions();
    void AddOutputRegions();
    void RemoveInputRegions();
    void RemoveOutputRegions();
    //-------------------------------------------------------------------------- 
    // Get Methods
    //-------------------------------------------------------------------------- 

    //-------------------------------------------------------------------------- 
    // Set Methods.  SubApplications will be invoking the non-debug methods
    // to set region pointers for this Action since the subapplications
    // contain pointers to these regions.
    //--------------------------------------------------------------------------

    void SetLineTxSP_MessageRegion(SP_MessageRegion*                        theTxMessageRegion);
    void SetPortTxSP_MessageRegion(SP_MessageRegion*                        theTxMessageRegion);
    void SetXcAgCfg_Region(TSXC_ConfigRegion<TSXC_Connect>*                 theXcAgCfg_Region);
    void SetRollCommand_Region(TEL_BbRegionBaseImp <TSXC_RollCommand>*      theRollCommand_Region);
    void SetRollResponse_Region(TEL_BbRegionBaseImp <TSXC_RollResponse>*    theRollResponse_Region);
    void SetRollStatus_Region(TEL_BbRegionBaseImp <TSXC_RollStatus>*        theRollStatus_Region);
    void SetRollRxStatus_Region(TEL_BbRegionBaseImp <TSXC_RollRxStatus>*    theRollRxStatus_Region);
    void SetRollBrMask_Region(TSXC_BrMCastMaskRegion<TSXC_BrMCastMask>*     theRollBrMask_Region);
    void SetRTCfgRegion(TSXC_S3RtRegion<TSXC_S3Route>*                      theRTRegion);     
        
private:
    void IsRemoteSrcAdded();
    void SetAddConnectInfo(INT32 theRollCommand, bool IsSSMNano=false);
    void SetRmvConnectInfo();
    void SendResponse(INT32 theResponse);
    void SetStatus(bool theNotifyOkay, INT32 theRollCommand);
    void ClearAddRmvConnectInfo();
    void CheckForActivation();
    void CheckConnection(INT32 theRollCommand);
    void SetTxMsgRequest(CT_Port aSrcPort, CT_Port aDstPort, uint8 aMsg);
    bool GetPortInfo(TSXC_Connection theXC, CT_IntfId& thePort, UINT8& theChan);
    
    const char* RollCommandToText(int theRollCommand);
    const char* RollStateToText(int theRollState);
            
private:
        
    TSXC_ConfigRegion<TSXC_Connect>*            myXcAgCfg_Region;
    SP_MessageRegion*                           myLineTxMessageRegion;
    SP_MessageRegion*                           myPortTxMessageRegion;
    TEL_BbRegionBaseImp <TSXC_RollCommand>*     myRollCommand_Region;
    TEL_BbRegionBaseImp <TSXC_RollResponse>*    myRollResponse_Region;
    TEL_BbRegionBaseImp <TSXC_RollStatus>*      myRollStatus_Region;
    TEL_BbRegionBaseImp <TSXC_RollRxStatus>*    myRollRxStatus_Region;
    
    TSXC_BrMCastMaskRegion<TSXC_BrMCastMask>*   myBrMaskRegion;
    TSXC_S3RtRegion<TSXC_S3Route>*              myRTRegion;
    
    bool                                        myActivationFlag;
    TSXC_Connection                             myOtherModuleConnectKey;
    TSXC_Connection                             myAddConnectKey;
    TSXC_Roll_Info                              myAddRollInfo;
    TSXC_Connection                             myRmvConnectKey;
    TSXC_Roll_Info                              myRmvRollInfo;        
    INT32                                       myLastRollCommand;
    INT32                                       myLastRollCmdState;    
    TSXC_RollCmdFsmState                        myRollCmdState;
};
#endif /* TSXC_ROLLCMDACTION_H */
