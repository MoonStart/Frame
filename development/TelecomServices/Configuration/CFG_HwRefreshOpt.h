// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHOPT_
#define _CFG_HWREFRESHOPT_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <Monitoring/MON_Definitions.h>

//class CFG_Region;
class FC_WakeUpProcessAction;
class FC_OneShotProcess;
class CFG_OptSubApplication;

//This action is invoked periodically in order to update 
//'optical layer' hardware registers with current 'optical 
//layer' configuration.
class CFG_HwRefreshOpt 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshOpt(CFG_AppIf& theCfgIf, 
                     TSPII_OpticalRegion& theOptPiiRegion,
                     CFG_OptAutoRateLockRegion& theOptAutoRateLockRegion,
					 CFG_OptProtCfgRegion* theOptProtRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshOpt();

	//This method refreshes all hardware related to optical 
	//layer.  It reads the current value of each Opt layer 
	//parameter an invokes the corresponding PII interface. 
	//This action is normally invoked upon a change of the 
	//region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    
    void UpdateObject(unsigned theRunReason, TSPII_OpticalIf& theOptPii);

private:

    TSPII_OpticalRegion& myOptPiiRegion;
	FC_WakeUpProcessAction* myWakeUpAction;
	FC_OneShotProcess* myProcess;
    CFG_TxOchAutomaticCfgRegion* myTxOchAutomaticConfigRegion;
    CFG_OptAutoRateLockRegion& myOptAutoRateLockRegion;
	CFG_OptProtCfgRegion* myOptProtRegion;

    uint32 myLocalPrbsRxSessionCounter;
    CFG_OptSubApplication& myCfgApp;
    MON_OptStatusRegion* myOptStatusRegion;
};

#endif /* _INC_CFG_HWREFRESHOPT_3C178282014D_INCLUDED */
