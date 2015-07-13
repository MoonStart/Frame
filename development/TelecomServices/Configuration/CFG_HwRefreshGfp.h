// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHGFP_
#define _CFG_HWREFRESHGFP_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_GfpIf;

class CFG_Gfp;

//This action is invoked periodically in order to update 
//'GFP layer' hardware registers 
//with current 'Gfp' configuration.
class CFG_HwRefreshGfp 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshGfp(CFG_AppIf& theCfgIf, 
                     CFG_GfpAutomaticCfgRegion* theAutomaticCfgRegion,
                     CFG_GfpProtCfgRegion* theProtCfgRegion,
                     uint8 theNumGfp,
                     TSPII_GfpRegion& theGfpPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshGfp();

	//This method refreshes all hardware related to GFP layer. 
    // It reads the current value of each Gfp layer parameter 
    //an invokes the corresponding PII interface. This action 
    //is normally invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_GfpRegion& myGfpPiiRegion;
    CFG_GfpAutomaticCfgRegion* myAutomaticCfgRegion;
    CFG_GfpProtCfgRegion* myProtCfgRegion;
    uint32* myLocalAutoNegSessionCounters;
    uint8 myNumGfp;

};

#endif /* _CFG_HWREFRESHGFP_ */
