/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009  Kumar C Solai
    DESCRIPTION:   TSXC Stage Two Multicast Action Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S2MCACTION_INCLUDED
#define _INC_TSXC_S2MCACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_S2MCast.h>
#include <XC/TSXC_S2McRegion.h>
#include <Configuration/CFG_MiscSubApplication.h>
#include <Configuration/CFG_Misc.h>

//------------------------------------------------------------------------------
// This class is responsible for applying stage two Multicast based on
// region changes in fab switch module.
//------------------------------------------------------------------------------
class TSXC_S2McAction : public TSXC_BaseAction
{
public:

    // Constructor 
    TSXC_S2McAction(T6100_CardIf& theCardContext, uint16 theFirstMcastId);

    // Destructor
    virtual ~TSXC_S2McAction();

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
    void SetS2McRegion(TSXC_S2McRegion<TSXC_S2MCast>*   theS2McCfgRegion);
    void SetMiscCfgRegion(CFG_MiscCfgRegion*            theMiscCfgRegion);
    
private:
    //-------------------------------------------------------------------------- 
    // Helper Methods
    //-------------------------------------------------------------------------- 
    uint8 BitPositionToTspiiSlot(uint8 theBitPos, CT_CardType theCardType);
    void ProcessUFABE();
    void ProcessMFAB();
           
    TSXC_S2McRegion<TSXC_S2MCast>*          myS2McCfg_Region;
    TSXC_S2McRegion<TSXC_S2MCast>*          myPrevS2McCfg_Region;
    CFG_MiscCfgRegion*                      myMiscConfig_Region;
    uint16                                  myFirstMcastId;
};
#endif /* _INC_TSXC_S2MCACTION_INCLUDED */
