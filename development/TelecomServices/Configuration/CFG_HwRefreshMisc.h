// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHMISC_
#define _CFG_HWREFRESHMISC_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_SsmIf;

class CFG_Misc;

//This action is invoked periodically in order to update 
//'MISC layer' hardware registers 
//with current 'MISC' configuration.
class CFG_HwRefreshMisc 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshMisc(CFG_AppIf& theCfgIf,
                      TSPII_FabRegion* theFabPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshMisc();

	//This method refreshes all hardware related to MISC Layer.
	//It reads the current value of each MISC layer parameter and
    //invokes the corresponding PII interface. This action is normally 
    // invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_FabRegion* myFabPiiRegion;
    CT_CardFamily myCardFamily;

};

#endif /* _CFG_HWREFRESHMISC_ */
