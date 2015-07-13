/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009  Kumar C Solai
    DESCRIPTION:   TSXC Stage Three Route Action  Class Definition
--------------------------------------------------------------------------*/
#ifndef _INC_TSXC_S3RTACTION_INCLUDED
#define _INC_TSXC_S3RTACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_S3Route.h>
#include <XC/TSXC_S3RtRegion.h>
#include <Configuration/CFG_MiscSubApplication.h>
#include <Configuration/CFG_Misc.h>

//------------------------------------------------------------------------------
// This class is responsible for applying stage three route info based on
// region changes in Nano mesh or fab switch module.
//------------------------------------------------------------------------------
class TSXC_S3RtAction : public TSXC_BaseAction
{
public:

    // Constructor 
    TSXC_S3RtAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_S3RtAction();

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
    void SetS3RtCfgRegion(TSXC_S3RtRegion<TSXC_S3Route>*    theS3RtCfgRegion);
    void SetMiscCfgRegion(CFG_MiscCfgRegion*                theMiscCfgRegion);

private:
        
    TSXC_S3RtRegion<TSXC_S3Route>*                          myS3RtCfg_Region;
    CFG_MiscCfgRegion*                                      myMiscConfig_Region;
};
#endif /* _INC_TSXC_S3RTACTION_INCLUDED */
