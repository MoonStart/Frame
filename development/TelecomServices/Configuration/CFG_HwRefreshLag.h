// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHLAG_
#define _CFG_HWREFRESHLAG_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_LagIf;

class CFG_Lag;

//This action is invoked periodically in order to update 
//Link Aggregation Group layer' hardware registers 
//with current 'Lag' configuration.
class CFG_HwRefreshLag 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshLag(CFG_AppIf& theCfgIf,
                     uint8 theNumLag, 
                     TSPII_LagRegion& theLagPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshLag();

	//This method refreshes all hardware related to Link 
    //Aggregation Group layer. It reads the current value 
	//of each Lag layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_LagRegion& myLagPiiRegion;
    uint8 myNumLag;

};

#endif /* _CFG_HWREFRESHLAG_ */
