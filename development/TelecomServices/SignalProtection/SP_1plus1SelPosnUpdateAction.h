// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1SELPOSNUPDATEACTION_38E35B0900D0_INCLUDED
#define _INC_SP_1PLUS1SELPOSNUPDATEACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SignalProtection.h>
#include "SP_Definitions.h"

class FC_BbAction;
class FC_PeriodicProcess;
class SP_SelectorPositionRegion;
class SP_Application;
class SP_1plus1ProtectionAction;
class SP_SelectorPosition;


//This action is responsible for copying the selector configuration for protection schemes
//from the selector to the persistent region. 
class SP_1plus1SelPosnUpdateAction
: public FC_Action
{
public:
	//Constructor. Requires application interface
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_1plus1SelPosnUpdateAction( SP_SelectorPositionRegion& theSelectorPosnRegion,
		                              SP_SelectorPositionRegion* theAltSelectorPosnRegion,
		                              SP_ProtectionActions& theProtectionActions
									  );

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_1plus1SelPosnUpdateAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles config request coming from the 
	//admin. 
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

	virtual SP_SelectorPosition* GetSelectorPosnObject(SP_1plus1ProtectionAction* theProtectionAction, int theIndex);

protected:

	//Reference to the selector position region
	SP_SelectorPositionRegion& theirSelectorPosnRegion;
	//Pointer since it could be empty
	SP_SelectorPositionRegion* theirAltSelectorPosnRegion;
    FC_PeriodicProcess* myProcess;
	SP_ProtectionActions& theirProtectionActions;

private:

};

#endif /* _INC_SP_1PLUS1SELPOSNUPDATEACTION_38E35B0900D0_INCLUDED */