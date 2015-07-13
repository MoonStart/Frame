// Copyright(c) Tellabs Transport Group. All rights reserved.
#ifndef _INC_TSXC_CFGACTION_INCLUDED
#define _INC_TSXC_CFGACTION_INCLUDED

#include <XC/TSXC_BaseAction.h>
#include <XC/TSXC_ConfigRegion.h>
#include <XC/TSXC_SourceActiveStatusRegion.h>
#include <XC/TSXC_Connect.h>
#include <XC/TSXC_RollStatus.h>
#include <XC/TSXC_SourceActiveStatus.h>
#include <Configuration/CFG_MiscSubApplication.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Misc.h>
#include <CommonTypes/CT_CrossConnect.h>
#include <TsPii/TSPII_XcIf.h>
#include <TsPii/TSPII_Region.h>
#include <SignalProtection/SP_ApplicationStatus.h>
#include <XC/TSXC_PortDataAllocRegion.h>
#include <XC/TSXC_PortDataAlloc.h>

#define TSXC_FORCECONN_INTERVAL  (10)

class QRS_ResponseRegion;


//------------------------------------------------------------------------------
// This class is responsible for applying cross connects based on
// region changes in Nano mesh mode.
//------------------------------------------------------------------------------
class TSXC_CfgAction : public TSXC_BaseAction
{
public:

    // Constructor 
    TSXC_CfgAction(T6100_CardIf& theCardContext);

    // Destructor
    virtual ~TSXC_CfgAction();

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

    void SetAgCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theAGCfgRegion);
    void SetSPCfgRegion(TSXC_ConfigRegion<TSXC_Connect>* theSPCfgRegion);
    void SetSPSrcActRegion(TSXC_SourceActiveStatusRegion<TSXC_SourceActiveStatus>* theSPSrcActRegion);
    void SetDisplayConnDelete(bool theValue);
    void SetDisplayConnAdd(bool theValue);
    void SetSPReady_Regions(vector< TEL_BbRegionBaseImp<SP_ApplicationStatus>*> * theSPReady_Regions);
    void SetRollStatus_Region(TEL_BbRegionBaseImp <TSXC_RollStatus>* theRollStatus_Region);    
    void SetPortDataAllocRegion(TSXC_PortDataAllocRegion<TSXC_PortDataAlloc>* thePortDataAllocRegion);

    //
    // Conversion methods
    //
    TSPII_XcType ConnectTypeToTspii(CT_XC_ConnectType connType, uint8 dstFac, uint8 srcFac = 0);

private:
    
    TSXC_ConfigRegion<TSXC_Connect>*                        myXCAgentConfig_Region;
    TSXC_ConfigRegion<TSXC_Connect>*                        myXCSigProtectConfig_Region;
    TSXC_SourceActiveStatusRegion<TSXC_SourceActiveStatus>* mySPSourceActive_Region;
    vector< TEL_BbRegionBaseImp<SP_ApplicationStatus>* >*   mySPReady_Regions;
    TEL_BbRegionBaseImp <TSXC_RollStatus>*                  myRollStatus_Region;
    TSXC_PortDataAllocRegion<TSXC_PortDataAlloc>*           myPortDataAlloc_Region;

    static bool myDisplayConnDelete;
    static bool myDisplayConnAdd;
};

#endif /* _INC_TSXC_CFGACTION_INCLUDED */
