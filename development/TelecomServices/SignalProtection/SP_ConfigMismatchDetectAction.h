// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef __SP_CONFIGMISMATCHDETECTACTION_H__
#define __SP_CONFIGMISMATCHDETECTACTION_H__

#include <SignalProtection/SP_1plus1ProtectionAction.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <SignalProtection/SP_ProtectionGroupConfigRegion.h>



class FC_PeriodicProcess;
class FC_Action;
class SP_1plus1SubApplication;

/////////////////////////////////////////////////////////////////////////
//This action is responsible detecting and correcting configuration mismatch
//Configuration mismatch includes "dual-on" and "dual-off" scenarios
class SP_ConfigMismatchDetectAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_ConfigMismatchDetectAction (SP_1plus1SubApplication& theApplIf,
                                   SP_ProtectionActions& theProtectionActions,
                                   SP_ProtectionGroupConfigRegion& theConfigRegion);

    //Destructor.
    //##ModelId=SP_ConfigMismatchDetectAction
    virtual ~SP_ConfigMismatchDetectAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//Run method
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    FC_PeriodicProcess* GetProcessPtr();

protected:
	
private:

    FC_PeriodicProcess* myProcess;
    SP_ProtectionActions& myProtectionActions;
    SP_ProtectionGroupConfigRegion& myConfigRegion;
    uint32 myIndex;
};


#endif /* __SP_CONFIGMISMATCHDETECTACTION_H__ */

