// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_MONITORCARDTYPEACTION_INCLUDED
#define _INC_TSXC_MONITORCARDTYPEACTION_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <XC/TSXC_BaseApplication.h>
#include <CSM/CSM_CardStatusRegion.h>

//
//This class is responsible for resizing the TSXC_ConfigRegion
// when the card type changes.
//

class TSXC_MonitorCardTypeAction : public FC_Action
{
public:

    // Constructor 
    TSXC_MonitorCardTypeAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_MonitorCardTypeAction();

    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);

    //
    // Need to have a method to retrieve the FC_BbAction since
    // this action runs under the context of a process.
    //
    FC_BbAction* GetBbAction() { return myBbAction; }

    // 
    // Get Methods
    //
    TSXC_ConfigRegion<TSXC_Connect>*    GetAgCfgRegion();
    TSXC_FrmCfgRegion<TSXC_Connect>*    GetFrmCfgRegion();
    TSXC_MuxCfgRegion<TSXC_MuxCfg>*     GetMuxCfgRegion();
    
    TSXC_S1McRegion<TSXC_S1MCast>*      GetS1McCfgRegion();
    TSXC_S1RtRegion<TSXC_S1Route>*      GetS1RtCfgRegion();
    
    TSXC_S3McRegion<TSXC_S3MCast>*      GetS3McCfgRegion();
    TSXC_S3RtRegion<TSXC_S3Route>*      GetS3RtCfgRegion();

    // 
    // Set Methods.  SubApplications will be invoking the non-debug methods
    // to set region pointers for XC_Cfg Action since the subapplications
    // contain pointers to these regions.
    //
    void SetAgCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theAGCfgRegion);
    void SetFrmCfgRegion(TSXC_FrmCfgRegion<TSXC_Connect>* theFrmCfgRegion);
    void SetMuxCfgRegion(TSXC_MuxCfgRegion<TSXC_MuxCfg>* theMuxCfgRegion);
    
    void SetS1McCfgRegion(TSXC_S1McRegion<TSXC_S1MCast>*    theS1McCfgRegion);
    void SetS1RtCfgRegion(TSXC_S1RtRegion<TSXC_S1Route>*    theS1RtCfgRegion);
    
    void SetS3McCfgRegion(TSXC_S3McRegion<TSXC_S3MCast>*    theS3McCfgRegion);
    void SetS3RtCfgRegion(TSXC_S3RtRegion<TSXC_S3Route>*    theS3RtCfgRegion);
    
    virtual void Run( FC_Object* theObject = NULL );

private:
    
	CSM_CardConfigStatusRegion*             myCardConfigStatusRegion;
    FC_BbAction*                            myBbAction;
	TSXC_ConfigRegion<TSXC_Connect>*        myXCAgentConfig_Region;
    TSXC_FrmCfgRegion<TSXC_Connect>*        myFrmCfg_Region;
    TSXC_MuxCfgRegion<TSXC_MuxCfg>*         myMuxCfg_Region;
        
    TSXC_S1McRegion<TSXC_S1MCast>*          myS1MCastCfg_Region;
    TSXC_S1RtRegion<TSXC_S1Route>*          myS1RouteCfg_Region;
    
    TSXC_S3McRegion<TSXC_S3MCast>*          myS3MCastCfg_Region;
    TSXC_S3RtRegion<TSXC_S3Route>*          myS3RouteCfg_Region;
    
    T6100_CardIf&                           myCardContext;
};

#endif /* _INC_TSXC_INCMODIFICATIONACTION_INCLUDED */

