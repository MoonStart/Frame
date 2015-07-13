// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHMAC_
#define _CFG_HWREFRESHMAC_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_MacIf;

class CFG_Mac;

//This action is invoked periodically in order to update 
//Mac layer' hardware registers with current 'Mac' configuration.
class CFG_HwRefreshMac 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshMac(CFG_AppIf& theCfgIf, 
                     CFG_MacAutomaticCfgRegion* theAutomaticCfgRegion,
                     TSPII_MacRegion& theMacPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshMac();

	//This method refreshes all hardware related to Mac 
    // layer. It reads the current value 
    //of each Mac layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_MacRegion& myMacPiiRegion;

    CFG_MacAutomaticCfgRegion* myAutomaticCfgRegion;

};

#endif /* _CFG_HWREFRESHMAC_ */
