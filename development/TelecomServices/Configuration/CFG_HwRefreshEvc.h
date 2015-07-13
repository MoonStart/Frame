// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHEVC_
#define _CFG_HWREFRESHEVC_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <T6100_TelecomIf.h>

// Forward declaration of class.
//class CFG_Region;
class TSPII_EvcIf;

class CFG_Evc;

//This action is invoked periodically in order to update 
//Ethernet Virtual Connections layer' hardware registers 
//with current 'Evc' configuration.
class CFG_HwRefreshEvc 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshEvc(CFG_AppIf& theCfgIf,
                     CFG_EvcAutomaticCfgRegion* theAutomaticCfgRegion,
                     unsigned int theNumEvcs,
                     TSPII_EvcRegion& theEvcPiiRegion,
                     T6100_TelecomIf* theBwpfMainApp,
                     T6100_TelecomIf* theVcgApp);

	//Virtual destructor
	virtual ~CFG_HwRefreshEvc();

	//This method refreshes all hardware related to Ethernet 
    //Virtual Connections layer. It reads the current value 
	//of each Evc layer parameter an invokes the corresponding 
	//PII interface. This action is normally invoked upon a 
	//change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_EvcRegion& myEvcPiiRegion;
    CFG_EvcAutomaticCfgRegion* myAutomaticCfgRegion;
    T6100_TelecomIf* myBwpfMainApp;
    T6100_TelecomIf* myVcgApp;
    unsigned int myNumEvcs;

};

#endif /* _CFG_HWREFRESHEVC_ */
