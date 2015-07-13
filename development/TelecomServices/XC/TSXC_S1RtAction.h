/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009  Kumar C Solai
    DESCRIPTION:   TSXC Stage One Route Action Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S1RTACTION_INCLUDED
#define _INC_TSXC_S1RTACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_S1Route.h>
#include <XC/TSXC_S1RtRegion.h>
#include <XC/TSXC_MCastFilterRegion.h>
#include <SignalProtection/SP_ApplicationStatus.h>
#include <Configuration/CFG_MiscSubApplication.h>
#include <Configuration/CFG_Misc.h>

//------------------------------------------------------------------------------
// This class is responsible for applying stage one route info based on
// region changes in Nano mesh or fab switch module.
//------------------------------------------------------------------------------
class TSXC_S1RtAction : public TSXC_BaseAction
{
public:

    // Constructor 
    TSXC_S1RtAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_S1RtAction();
    //-------------------------------------------------------------------------- 
    // This method causes this object to execute its main
    // function of applying Stage One Mulicast Configurations.
    //-------------------------------------------------------------------------- 
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam = NULL);

    //-------------------------------------------------------------------------- 
    // Get Methods
    //-------------------------------------------------------------------------- 

    //-------------------------------------------------------------------------- 
    // Set Methods.  SubApplications will be invoking the non-debug methods
    // to set region pointers for this Action since the subapplications
    // contain pointers to these regions.
    //-------------------------------------------------------------------------- 
    void SetS1RtCfgRegion(TSXC_S1RtRegion<TSXC_S1Route>*        theS1RtCfgRegion);
    void SetMCFilterRegion(TSXC_MCastFilterRegion<TSXC_MCastFilter>* theMCFilterRegion);    
    void SetMiscCfgRegion(CFG_MiscCfgRegion*                    theMiscCfgRegion);
    void SetSPReady_Regions(vector< TEL_BbRegionBaseImp<SP_ApplicationStatus>*> * theSPReady_Regions);
    void ApplyCesIngress(UINT16 theIndex);

private:
        
    TSXC_S1RtRegion<TSXC_S1Route>*                          myS1RtCfg_Region;
    TSXC_MCastFilterRegion<TSXC_MCastFilter>*               myXCMCastFilter_Region;    
    CFG_MiscCfgRegion*                                      myMiscConfig_Region;
    vector< TEL_BbRegionBaseImp<SP_ApplicationStatus>* >*   mySPReady_Regions;
};
#endif /* _INC_TSXC_S1RTACTION_INCLUDED */
