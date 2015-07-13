// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHDCCL_
#define _CFG_HWREFRESHDCCL_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_DcclIf;

class CFG_Dccl;
class CFG_DcclProt;

//This action is invoked periodically in order to update 
//'SONET/SDH high order path layer' hardware registers 
//with current 'Dccl' configuration.
class CFG_HwRefreshDccl 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshDccl(CFG_AppIf& theCfgIf,
                      CFG_DcclAutomaticCfgRegion* theAutomaticCfgRegion,
                      TSPII_DcclRegion& theDcclPiiRegion,
                      CFG_DcclProtCfgRegion* theProtCfgRegion,
                      uint8 theNumLinks,
                      CFG_AppIf* theLprfCfgApp = NULL,
                      CFG_AppIf* thePprfCfgApp = NULL);

	//Virtual destructor
	virtual ~CFG_HwRefreshDccl();

	//This method refreshes all hardware related to SONET/SDH 
	//high order path layer. It reads the current value 
	//of each Dccl layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_DcclRegion& myDcclPiiRegion;
    CFG_DcclAutomaticCfgRegion* myAutomaticCfgRegion;
    CFG_DcclProtCfgRegion* myProtCfgRegion;

    CFG_AppIf* myLprfCfgApp;
    CFG_AppIf* myPprfCfgApp;

    CT_DCC_LinkType myLastSentLinkType;
    bool  myFirstRefreshAction;

    uint8 myNumLinks;
};

#endif /* _CFG_HWREFRESHDCCL_ */
