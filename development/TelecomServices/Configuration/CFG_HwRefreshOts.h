// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHOTS_
#define _CFG_HWREFRESHOTS_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.

class CFG_HwRefreshOts 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshOts(CFG_AppIf& theCfgIf,
                     CFG_OtsOHCfgRegion& theCfgOtsOHRegion,
                     CFG_OtsOchOHAutomaticCfgRegion& theOtsOchOHAutomaticCfgRegion,
                     TSPII_OtsOHRegion& theOtsPiiRegion,
                     TSPII_OmsOHRegion* theOmsPiiRegion,
                     TSPII_OchOHRegion* theOchPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshOts();

    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

private:
    
    CFG_OtsOHCfgRegion& myCfgOtsOHRegion;
    CFG_OtsOchOHAutomaticCfgRegion& myOtsOchOHAutomaticCfgRegion;
    TSPII_OtsOHRegion& myOtsPiiRegion;
    TSPII_OmsOHRegion* myOmsPiiRegion;
    TSPII_OchOHRegion* myOchPiiRegion;
};

#endif /* _CFG_HWREFRESHOTS_ */
