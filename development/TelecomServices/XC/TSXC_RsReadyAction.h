// Copyright(c) Tellabs Transport Group. All rights reserved.
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TSXC_RSREADYACTION_INCLUDED
#define _INC_TSXC_RSREADYACTION_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_Milliseconds.h>

#include <XC/TSXC_RsReadyRegion.h>
#include <XC/TSXC_RsReady.h>

class FC_BbAction;


//
// This action is responsible for:
//
// 1 - Comparing the CFG RS information against 
//     TSPII RS information.  When these
//     two match, this action will modify 
//     TSXC_RsReadyRegion which will trigger 
//     TSXC_CfgAction to run.  This results in 
//     the application of connections to hardware.
//
// 2 - Comparing previous CFG RS information 
//     to current CFG RS information.  When these
//     two differ, this action will modify 
//     TSXC_RsReadyRegion which will trigger 
//     TSXC_CfgAction to run.  This results in 
//     the application of connections to hardware.
//
// The first comparison is done periodically after
// card initialization.  
//
// The second comparison is done whenever the CFG RS
// region is updated.
//

class TSXC_RsReadyAction : public FC_Action
{
public:

    // Constructor 
    TSXC_RsReadyAction(T6100_CardIf& theCardContext,  
                       TSXC_RsReadyRegion<TSXC_RsReady>* theTSXC_RsReady_Region);

    // Destructor
    virtual ~TSXC_RsReadyAction();

    //
    // This method causes this object to execute its main
    // function of applying CrossConnect Configurations.
    //
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);

    virtual void Run( FC_Object* theObject = NULL );

    FC_BbAction* GetBbAction() { return myBbAction; }
    void AddInputRegion( FC_BbRegion* theInputRegion );
    void RemoveInputRegion( FC_BbRegion* theInputRegion );

private:
    
    void CompareCfgToTspii();
    void CompareCurrentAndPrevCfg();
    uint32 CfgToTspii(uint32 theCfgDev);

    T6100_CardIf& myCardContext;
    FC_PeriodicProcess* myPeriodicProcess;
    FC_BbAction* myBbAction;
    TSXC_RsReadyRegion<TSXC_RsReady>* myXCRsReady_Region;
    static const FC_Milliseconds  RUN_FREQUENCY;
};

#endif /* _INC_TSXC_RSREADYACTION_INCLUDED */

