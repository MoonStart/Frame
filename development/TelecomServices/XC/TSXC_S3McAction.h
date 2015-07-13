/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage Three Multicast Action  Class Definition
--------------------------------------------------------------------------*/

#ifndef _INC_TSXC_S3MCACTION_INCLUDED
#define _INC_TSXC_S3MCACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_S3MCast.h>
#include <XC/TSXC_S3McRegion.h>
#include <Configuration/CFG_MiscSubApplication.h>
#include <Configuration/CFG_Misc.h>

//------------------------------------------------------------------------------------------------------------------------------
// This class is responsible for applying stage three MCast based on
// region changes.
//
//------------------------------------------------------------------------------------------------------------------------------
class TSXC_S3McAction : public TSXC_BaseAction
{
public:
    // Constructor 
    TSXC_S3McAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_S3McAction();

    //-------------------------------------------------------------------------- 
    // This method causes this object to execute its main
    // function of applying Stage three Mulicast Configurations.
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
    void SetS3McCfgRegion(TSXC_S3McRegion<TSXC_S3MCast>*    theS3McCfgRegion);
    void SetMiscCfgRegion(CFG_MiscCfgRegion*                theMiscCfgRegion);

private:
    TSXC_S3McRegion<TSXC_S3MCast>*          myS3McCfg_Region;
    CFG_MiscCfgRegion*                      myMiscConfig_Region;       
                      
};
#endif /* _INC_TSXC_S3MCACTION_INCLUDED */
