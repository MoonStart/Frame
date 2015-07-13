// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_SYNCCFGACTION_38E35B0900D0_INCLUDED
#define _INC_SP_SYNCCFGACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <vector>
#include <CommonTypes/CT_FacilityIds.h>
#include <TsPii/TSPII_Region.h>

class SP_Application;
class FC_BbAction;
class SP_TimingModeRegion;
class CFG_Region;
class SP_TimingRSIF;

//This action is responsible for configuring the CFG_SYNC config region
class SP_SyncCfgAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_SyncCfgAction( SP_Application& theApplIf,
                      SP_TimingModeRegion& theTimingModeRegion,
                      SP_TimingRSIF& theTimingRSIF,
                      CT_IntfId theMateTimingIntf = CT_INTF_ID_UNKNOWN);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_SyncCfgAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles config request coming from the 
	//admin. 
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    FC_BbAction* GetBbAction() { return myBbAction; }

    void AddToRegionList(CFG_Region* theCfgRegion, TSPII_MsRegion* theTspiiRegion);
    void RemoveFromRegionList(CFG_Region* theCfgRegion);

private:

    SP_TimingModeRegion& myTimingModeRegion;
    FC_BbAction* myBbAction;
	SP_Application& myAppIf;
    SP_TimingRSIF& myTimingRSIF;

    vector<CFG_Region*> myMSTimingCfgRegionList;
    vector<TSPII_MsRegion*> myTSPIIRegionList;

    CT_IntfId myMateTimingIntf;

};

#endif /* _INC_SP_SYNCCFGACTION_38E35B0900D0_INCLUDED */