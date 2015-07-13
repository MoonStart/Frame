// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHOMSONSC_
#define _CFG_HWREFRESHOMSONSC_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>

class CFG_HwRefreshOmsOnSC
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshOmsOnSC(CFG_AppIf& theCfgIf, 
                     CFG_OmsAutomaticShutdownRegion& theAutomaticShutdownRegion,
                     CFG_OptAutomaticCfgRegion* thePumpRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshOmsOnSC();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

private:

    CFG_OmsAutomaticShutdownRegion& myAutomaticShutdownRegion;
    CFG_OptAutomaticCfgRegion* myPumpRegion;
    CSM_CardConfigStatusRegion* myCardConfigRegion;
};

#endif /* _CFG_HWREFRESHOMS_ */
