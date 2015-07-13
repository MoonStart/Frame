/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009  Kumar C Solai
    DESCRIPTION:   TSXC Stage One Tx Enable Action Class Definition
--------------------------------------------------------------------------*/
#ifndef TSXC_S1ENACTION_H
#define TSXC_S1ENACTION_H

#include <XC/TSXC_BaseAction.h>

//------------------------------------------------------------------------------
// This class is responsible for applying stage one enable xmit based on
// region changes in Nano mesh mode or HCSS switch mode.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class TSXC_S1EnAction : public TSXC_BaseAction
{
public:

	// Constructor 
	TSXC_S1EnAction(T6100_CardIf& theCardContext); 

	// Destructor
	virtual ~TSXC_S1EnAction();
    
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
    void SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion);
    int ConvertSsmPortToTspii(uint8 srcFac);
            
private:
        
    TSXC_ConfigRegion<TSXC_Connect>*                       myXCAgentConfig_Region;       
    CFG_MiscCfgRegion*                                     myMiscConfig_Region;
    TEL_BbRegionBaseImp <TSXC_RollStatus>*                 myRollStatus_Region;

    uint32 CreateOduId(uint8 theInputFacility, uint8 theInputFacilityEndpoint, CT_XC_ConnectType theConnType);
};

#endif
