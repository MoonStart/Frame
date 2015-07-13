/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009  Kumar C Solai
    DESCRIPTION:   TSXC Stage One Multicast Action Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S1MCACTION_INCLUDED
#define _INC_TSXC_S1MCACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>

#include <XC/TSXC_S1MCast.h>
#include <XC/TSXC_S1McRegion.h>
#include <XC/TSXC_BrMCastMaskRegion.h>
#include <XC/TSXC_BrMCastMask.h>
#include <Configuration/CFG_MiscSubApplication.h>
#include <Configuration/CFG_Misc.h>

//------------------------------------------------------------------------------
// This class is responsible for applying stage one Multicast based on
// region changes in Nano mesh mode.
//------------------------------------------------------------------------------
class TSXC_S1McAction : public TSXC_BaseAction
{
public:

    // Constructor 
    TSXC_S1McAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_S1McAction();

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

    void SetS1McCfgRegion(TSXC_S1McRegion<TSXC_S1MCast>*             theS1McCfgRegion);
    void SetBrMaskRegion(TSXC_BrMCastMaskRegion<TSXC_BrMCastMask>*   theBrMaskRegion);
    void SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion);

private:
   
    TSXC_S1McRegion<TSXC_S1MCast>*                          myS1McCfg_Region;
    TSXC_BrMCastMaskRegion<TSXC_BrMCastMask>*               myXCBrMCastMask_Region;
    CFG_MiscCfgRegion*                                      myMiscConfig_Region;
};
#endif /* _INC_TSXC_S1MCACTION_INCLUDED */
