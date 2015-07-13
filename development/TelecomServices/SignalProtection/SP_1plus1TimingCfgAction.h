// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1TIMINGCFGACTION_38E35B0900D0_INCLUDED
#define _INC_SP_1PLUS1TIMINGCFGACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include "SP_ProtectionGroupConfigRegion.h"
#include <TelCommon/TEL_BbRegionBaseImp.h>

class SP_Application;
class CFG_Region;
class FC_BbAction;
class SP_ApplicationStatus;

//This action is responsible for validating the sync prot config region
//when no tming protection schemes exist. This action runs once at startup
//when the application is ready.
class SP_1plus1TimingCfgAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_1plus1TimingCfgAction( SP_Application& theApplIf,
                              SP_ProtectionGroupConfigRegion& theConfigRegion,
	                          TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
							  CFG_Region& theCfgRsRegion,
							  CFG_Region& theCfgSyncProtRegion);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_1plus1TimingCfgAction();

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

private:

	//Reference to the app ready region
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & myAppStatusRegion;
	//Reference to the config region.
    //##ModelId=394102B8010F
    SP_ProtectionGroupConfigRegion & myConfigRegion;
	CFG_Region& myCfgRsRegion;
    FC_BbAction* myBbAction;
	SP_Application& myAppIf;
	CFG_Region& myCfgSyncProtRegion;

};

#endif /* _INC_SP_1PLUS1TIMINGCFGACTION_38E35B0900D0_INCLUDED */