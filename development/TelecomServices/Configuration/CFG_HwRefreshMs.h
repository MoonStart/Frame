// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHMS_
#define _CFG_HWREFRESHMS_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_MsIf;

class CFG_Ms;

//This action is invoked periodically in order to update 
//'SONET/SDH multiplex section layer' hardware registers 
//with current 'Ms' configuration.
class CFG_HwRefreshMs 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshMs(CFG_AppIf& theCfgIf, 
                    CFG_MsAutomaticCfgRegion* theAutomaticCfgRegion,
                    TSPII_MsRegion& theMsPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshMs();

	//This method refreshes all hardware related to SONET/SDH 
	//multiplex section layer. It reads the current value 
	//of each Ms layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_MsRegion& myMsPiiRegion;

    CFG_MsAutomaticCfgRegion* myAutomaticCfgRegion;
};

#endif /* _CFG_HWREFRESHMS_ */
