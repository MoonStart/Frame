// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHT1E1_
#define _CFG_HWREFRESHT1E1_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_T1E1If;

class CFG_T1E1;

//This action is invoked periodically in order to update 
//'T1E1 layer' hardware registers 
//with current 'T1E1' configuration.
class CFG_HwRefreshT1E1 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshT1E1(CFG_AppIf& theCfgIf, 
                      CFG_T1E1AutomaticCfgRegion* theAutomaticCfgRegion,
					  CFG_T1E1CfgRegion& theAltConfigRegion,
					  CFG_T1E1AutomaticCfgRegion* theAutoShutdownCfgRegion,
                      TSPII_T1E1Region& theT1E1PiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshT1E1();

	//This method refreshes all hardware related to T1E1 layer. 
    // It reads the current value of each T1E1 layer parameter 
    //an invokes the corresponding PII interface. This action 
    //is normally invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

private:

    TSPII_T1E1Region& myT1E1PiiRegion;
    CFG_T1E1AutomaticCfgRegion* myAutomaticCfgRegion;
	CFG_T1E1CfgRegion& myAltConfigRegion;
	CFG_T1E1AutomaticCfgRegion* myAutoShutdownCfgRegion;

    bool myFirstRefreshAction;

};

#endif /* _CFG_HWREFRESHT1E1_ */
