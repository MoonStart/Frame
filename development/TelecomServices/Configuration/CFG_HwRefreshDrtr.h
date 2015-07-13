// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHDRTR_
#define _CFG_HWREFRESHDRTR_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_DrtrIf;

class CFG_Drtr;

//This action is invoked periodically in order to update 
//'Drtr layer' hardware registers 
//with current 'Drtr' configuration.
class CFG_HwRefreshDrtr 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshDrtr(CFG_AppIf& theCfgIf, 
                      TSPII_DrtrRegion& theDrtrPiiRegion,
                      CFG_AppIf* theTarpCfgApp,
                      uint8 theNumRouters = 1);

	//Virtual destructor
	virtual ~CFG_HwRefreshDrtr();

	//This method refreshes all hardware related to Drtr layer. 
    // It reads the current value of each Drtr layer parameter 
    //an invokes the corresponding PII interface. This action 
    //is normally invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

private:

    CFG_AppIf* myTarpCfgApp;

    TSPII_DrtrRegion& myDrtrPiiRegion;

    bool myFirstRefreshAction;

    uint8 myNumRouters;
};

#endif /* _CFG_HWREFRESHDRTR_ */
