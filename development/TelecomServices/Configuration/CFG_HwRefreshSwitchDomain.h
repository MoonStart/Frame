// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHSWITCHDOMAIN_
#define _CFG_HWREFRESHSWITCHDOMAIN_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
#include <Configuration/CFG_SwitchDomainSubApplication.h>

// Forward declaration of class.
//class CFG_Region;
//class TSPII_SsmIf;

class CFG_SwitchDomainSubApplication;
class CFG_SwitchDomain;
class FC_BbAction;

//This action is invoked periodically in order to update 
//'SWD0 layer' hardware registers 
//with current 'SWD0' configuration.
class CFG_HwRefreshSwitchDomain 
: public FC_Action
{
public:
    //Constructor
    CFG_HwRefreshSwitchDomain(CFG_SwitchDomainSubApplication& theSubApp, 
                              TSPII_SwitchRegion* theSwitchPiiRegion);
    
    //Virtual destructor
    virtual ~CFG_HwRefreshSwitchDomain();
    
    virtual void Run(FC_Object* theObject = NULL) {}
    
    //This method refreshes all hardware related to SWD0 Layer.
    //It reads the current value of each SWD0 layer parameter and
    //invokes the corresponding PII interface. This action is normally 
    // invoked upon a change of the region it handles.
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

    CFG_SwitchDomainSubApplication& GetSubApp() { return mySubApp;}
    
    
private:

    CFG_SwitchDomainSubApplication& mySubApp;
    
    TSPII_SwitchRegion* mySwitchPiiRegion;
    
    FC_BbAction* myBbAction;
    
    CT_CardFamily myCardFamily;

};

#endif /* _CFG_HWREFRESHSWITCHDOMAIN_ */
