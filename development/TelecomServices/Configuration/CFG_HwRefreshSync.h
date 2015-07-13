// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHSYNC_
#define _CFG_HWREFRESHSYNC_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_ClkSelIf;

class CFG_Sync;

//This action is invoked periodically in order to update 
//timing mode.
class CFG_HwRefreshSync 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshSync(CFG_AppIf& theCfgIf, 
		              CFG_Region& theConfigRegion,
                      TSPII_ClkSelRegion& theSyncPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshSync();

	//This method refreshes all hardware related to timing mode. 
    // This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_ClkSelRegion& mySyncPiiRegion;
	CFG_Region&  myConfigRegion;

};

#endif /* _CFG_HWREFRESHSYNC_ */
