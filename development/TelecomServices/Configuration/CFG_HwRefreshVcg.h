// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHVCG_
#define _CFG_HWREFRESHVCG_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_VcgIf;

class CFG_Vcg;

//This action is invoked periodically in order to update 
//virtual concatenation layer' hardware registers 
//with current 'Vcg' configuration.
class CFG_HwRefreshVcg 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshVcg(CFG_AppIf& theCfgIf, 
                     uint8 theNumVcg,
                     TSPII_VcgRegion& theVcgPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshVcg();

	//This method refreshes all hardware related to virtual 
    //concatenation layer. It reads the current value 
	//of each Vcg layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    uint8 myNumVcg;

    TSPII_VcgRegion& myVcgPiiRegion;

};

#endif /* _CFG_HWREFRESHVCG_ */
