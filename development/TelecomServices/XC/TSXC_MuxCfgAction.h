/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_MUXCFGACTION_INCLUDED
#define _INC_TSXC_MUXCFGACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_MuxCfg.h>
#include <XC/TSXC_MuxCfgRegion.h>

#include <TsPii/TSPII_XcIf.h>

class QRS_ResponseRegion;

//------------------------------------------------------------------------------
// This class is responsible for applying stage one route info based on
// region changes in Nano mesh or fab switch module.
//------------------------------------------------------------------------------
class TSXC_MuxCfgAction : public TSXC_BaseAction
{
public:

    // Constructor 
    TSXC_MuxCfgAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_MuxCfgAction();
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
    void SetMuxCfgRegion(TSXC_MuxCfgRegion<TSXC_MuxCfg>* theMuxCfgRegion);

private:
        
    TSXC_MuxCfgRegion<TSXC_MuxCfg>* myMuxCfg_Region;
};
#endif /* _INC_TSXC_MUXCFGACTION_INCLUDED */
