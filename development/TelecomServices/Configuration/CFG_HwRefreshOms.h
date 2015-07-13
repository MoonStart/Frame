// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHOMS_
#define _CFG_HWREFRESHOMS_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>


class CFG_HwRefreshOms 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshOms(CFG_AppIf& theCfgIf, 
                     CFG_OtsCfgRegion* theOtsRegion,
                     CFG_OtsAutomaticTxPwrShutRegion* theAutomaticTxPwrShutRegion,
                     CFG_OmsAutomaticShutdownRegion& theAutomaticShutdownRegion,
                     CFG_OmsAutomaticPwrAdjRegion& theAutomaticPwrAdjRegion,
                     CFG_CmmOosAutomaticRegion* theCmmOosAutomaticRegion,
                     CFG_OptAutomaticCfgRegion* thePump1Region,
                     CFG_OptAutomaticCfgRegion* thePump2Region,
                     TSPII_PipeRegion& thePipePiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshOms();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

	void UpdateInputRegions(CFG_OtsCfgRegion* theOtsRegion,
		                    CFG_OtsAutomaticTxPwrShutRegion* theAutomaticTxPwrShutRegion);

private:

    CFG_OtsCfgRegion* myOtsRegion;
    CFG_OtsAutomaticTxPwrShutRegion* myAutomaticTxPwrShutRegion;
    CFG_OmsAutomaticShutdownRegion& myAutomaticShutdownRegion;
    CFG_OmsAutomaticPwrAdjRegion& myAutomaticPwrAdjRegion;
    CFG_CmmOosAutomaticRegion* myCmmOosAutomaticRegion;

    CFG_OptAutomaticCfgRegion* myPump1Region;
    CFG_OptAutomaticCfgRegion* myPump2Region;
    TSPII_PipeRegion& myPipePiiRegion;
};

#endif /* _CFG_HWREFRESHOMS_ */
