// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHLAYER2_
#define _CFG_HWREFRESHLAYER2_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <T6100_TelecomIf.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_L2If;

class CFG_Layer2;

//This action is invoked periodically in order to update 
//Layer 2 layer' hardware registers with current 'Layer2'
// configuration.
class CFG_HwRefreshLayer2 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshLayer2(CFG_AppIf& theCfgIf,
                        uint8 theNumLayer2,
                        TSPII_L2Region& theLayer2PiiRegion,
                        T6100_TelecomIf* theL2pfMainApp);

	//Virtual destructor
	virtual ~CFG_HwRefreshLayer2();

	//This method refreshes all hardware related to the 
    //layer 2 layer. It reads the current value 
	//of each Layer2 layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_L2Region& myLayer2PiiRegion;
    
    T6100_TelecomIf* myL2pfMainApp;

    uint8 myNumLayer2;

};

#endif /* _CFG_HWREFRESHLAYER2_ */
