// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHHOP_
#define _CFG_HWREFRESHHOP_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <CommonTypes/CT_FacilityIds.h>
#include <TsPii/TSPII_Region.h>
#include <XC/TSXC_BaseApplication.h>
#include <XC/TSXC_ConfigRegion.h>
#include <XC/TSXC_RsReadyRegion.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_HopIf;

class CFG_Hop;

//This action is invoked periodically in order to update 
//'SONET/SDH high order path layer' hardware registers 
//with current 'Hop' configuration.
class CFG_HwRefreshHop 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshHop(CFG_AppIf&                 theCfgIf, 
                     CFG_HopAutomaticCfgRegion* theAutomaticCfgRegion,
                     TSPII_HopRegion&           theHopPiiRegion,
                     CT_NumberOfHops            theHopsOnCard,
                     uint8                      theXcFacilityID,
                     TSXC_ConfigRegion<TSXC_Connect>*  theXcConfigRegion  = NULL,
                     TSXC_RsReadyRegion<TSXC_RsReady>* theXcRsReadyRegion = NULL);

	//Virtual destructor
	virtual ~CFG_HwRefreshHop();

	//This method refreshes all hardware related to SONET/SDH 
	//high order path layer. It reads the current value 
	//of each Hop layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);


private:

    TSPII_HopRegion& myHopPiiRegion;
    CFG_HopAutomaticCfgRegion* myAutomaticCfgRegion;

    TSXC_ConfigRegion<TSXC_Connect>* myXcConfigRegion;
    TSXC_RsReadyRegion<TSXC_RsReady>* myXcRsReadyRegion;
    uint8 myXCFacilityID;

    bool myFirstRefreshAction;

    CT_NumberOfHops myHopsOnCard;
};

#endif /* _CFG_HWREFRESHHOP_ */
