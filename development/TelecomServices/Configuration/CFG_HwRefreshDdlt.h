// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHDDTL_
#define _CFG_HWREFRESHDDTL_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <T6100_CardIf.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_DdltIf;

class CFG_Ddlt;

//This action is invoked periodically in order to update 
//'DDTL layer' hardware registers 
//with current 'DDTL' configuration.
class CFG_HwRefreshDdlt 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshDdlt(CFG_AppIf& theCfgIf, 
                      TSPII_DdltRegion& theDdltPiiRegion,
                      CFG_AppIf* theLprfCfgApp = NULL,
                      CFG_AppIf* theCfgDcclSectionApp = NULL,
                      CFG_AppIf* theCfgDcclLineApp = NULL);

	//Virtual destructor
	virtual ~CFG_HwRefreshDdlt();

	//This method refreshes all hardware related to DDTL layer. 
    // It reads the current value of each DDTL layer parameter 
    //an invokes the corresponding PII interface. This action 
    //is normally invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

private:

    TSPII_DdltRegion& myDdltPiiRegion;

    bool  myFirstRefreshAction;

    CFG_AppIf* myLprfCfgApp;

    CFG_AppIf* myCfgDcclSectionApp;
    CFG_AppIf* myCfgDcclLineApp;
};

#endif /* _CFG_HWREFRESHDDTL_ */
