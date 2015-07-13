/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        CFG_CmmOosAutomaticAction.h
 *    DATE:          11/16/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     Configuration
 *    OVERVIEW:      CMM Out-of-service processing action
 *    FEATURE PACK:  FP3.3
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:        NONE
 *
 ******************************************************************************/
#ifndef __CFG_CMMOOSAUTOMATICACTION_H__
#define __CFG_CMMOOSAUTOMATICACTION_H__

#include <ExecutionSupport/FC_Action.h>
#include <Monitoring/MON_Definitions.h>
#include <Configuration/CFG_Definitions.h>
//#include <CSM/CSM_CardStatus.h>

#define CMM_OOS_MAX_CSM_REGIONS 2

class FC_BbAction;
class CFG_OmsSubApplication;
class CSM_CardConfigStatusRegion;
class CSM_CardStatusRegion;

class CFG_CmmOosAutomaticAction : public FC_Action
{
public:
    /* Constructor */               CFG_CmmOosAutomaticAction(CFG_OmsSubApplication&        theCfgApp,
                                                              CFG_CmmOosAutomaticRegion*    theCmmOosAutomaticRegion);
    virtual                         ~CFG_CmmOosAutomaticAction();

    bool                            IsActionValid();

    // Behavior
    virtual void                    Run(FC_Object* theObject = NULL);

private:
    FC_BbAction*                    myBbAction;
    CFG_OmsSubApplication&          myCfgApp;
    CSM_CardStatusRegion*           myCmmCardStatusRegions[CMM_OOS_MAX_CSM_REGIONS];
	CSM_CardConfigStatusRegion*     myCmmCardConfigRegions[CMM_OOS_MAX_CSM_REGIONS];
    CFG_CmmOosAutomaticRegion*      myCmmOosAutomaticRegion;
    MON_OmsDefectsRegion*           myIamMonDefectRegion;
    CSM_CardStatusRegion*           myIamCardStatusRegion;
};

#endif /* __CFG_CMMOOSAUTOMATICACTION_H__ */
