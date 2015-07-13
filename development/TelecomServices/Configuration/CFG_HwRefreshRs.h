// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHRS_
#define _CFG_HWREFRESHRS_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include "Monitoring/MON_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_RsIf;

class CFG_Rs;

//This action is invoked periodically in order to update 
//'SONET/SDH Regeneration section layer' hardware registers 
//with current 'Rs' configuration.
class CFG_HwRefreshRs 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshRs(CFG_AppIf& theCfgIf, 
                    CFG_RsAutomaticCfgRegion* theAutomaticCfgRegion,
                    CFG_OptAutoRateLockRegion* theAutoRateLockRegion,
                    TSPII_RsRegion& theRsPiiRegion,
                    CFG_OptProtCfgRegion* theOptProtCfgRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshRs();

	//This method refreshes all hardware related to SONET/SDH 
	//Regeneration section layer. It reads the current value 
	//of each Rs layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_RsRegion& myRsPiiRegion;
    CFG_RsAutomaticCfgRegion* myAutomaticCfgRegion;
    CFG_OptAutoRateLockRegion* myAutoRateLockRegion;
    MON_RsConfigRegion* myRsMonConfigRegion;
    CFG_OptProtCfgRegion* myOptProtCfgRegion;
    bool myPreivousIsYcableStandby;
    
};

#endif /* _CFG_HWREFRESHRS_ */
