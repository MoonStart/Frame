// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_COMMANDPROCESSORACTION_38E35B0900D0_INCLUDED
#define _INC_SP_COMMANDPROCESSORACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <vector>
#include "SP_Definitions.h"

class SP_ProtectionAction;
class SP_SwitchingCommandResult;
class SP_SwitchingCommand;
class FC_BbAction;
class FC_OneShotProcess;
class FC_WakeUpProcessAction;
class SP_ApplicationStatus;

//This class handles switching request coming from the admin. 
//It also updates the command results once the command is 
//completed. There is one command processor action per port 
//shelf per protection type. It handles the new commands for 
//each protection group of the port shelf. This class is a 
//base class for all command processor of signal protection.
//##ModelId=38E35B0900D0
class SP_CommandProcessorAction 
: public FC_Action
{
public:
	//Constructor. Requires command region and protection 
	//actions vector. Disable command processing by default.
    //##ModelId=3BBC9B0F02A0
    SP_CommandProcessorAction(  
        TEL_BbRegionBaseImp<SP_SwitchingCommand>& theSwitchCommandRegion,
		TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
        SP_ProtectionActions& theProtectionActions,
		uint32 theGroupCount);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_CommandProcessorAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles switching request coming from the 
	//admin. It also updates the command results once the 
	//command is completed.
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL) = 0;

	//Forces the command processing to start if it was 
	//stopped(debug).
    //##ModelId=39ACEFB00072
    inline void Start();
	//Forces the command processing to stop (debug).
    //##ModelId=39ACEFB0005E
    inline void Stop();

	//Returns a reference to the low priority wake up action.
	//##ModelId=39ACEFA0000B
    inline FC_WakeUpProcessAction& GetLowPriorityWakeUpAction();

    FC_BbAction* GetBbAction() { return myBbAction; }

protected:
	//Reference to the command region.
    //##ModelId=394102B8010F
    TEL_BbRegionBaseImp<SP_SwitchingCommand>& mySwitchCommandRegion;

	//Reference to the app ready region
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & myAppStatusRegion;

	//Reference to the vector of protection actions
    //##ModelId=3BC5A34B02E3
    SP_ProtectionActions& myProtectionActions;

	//Pointer to the low priority wake up action usually 
	//execute for low priority event (configuration or 
	//command update).
	//##ModelId=39ACEF9F02E5
    FC_WakeUpProcessAction* myLowPriorityCallbackAction;
	//Low priority process running low priority action.
	//##ModelId=3B8BC9BD01FE
    FC_OneShotProcess* myLowPriorityProcess;

	//True if processing is stop (debug).
    //##ModelId=39ACEFB0002C
    bool stopped;

	//The number of protection groups this action processes
	uint32 myGroupCount;


private:
    FC_BbAction* myBbAction;

};

//##ModelId=39ACEFB00072
inline void SP_CommandProcessorAction::Start() { stopped = false; }
//##ModelId=39ACEFB0005E
inline void SP_CommandProcessorAction::Stop() { stopped = true; }

//##ModelId=39ACEFA0000B
inline FC_WakeUpProcessAction& SP_CommandProcessorAction::GetLowPriorityWakeUpAction()
{
    return *myLowPriorityCallbackAction;
}

#endif /* _INC_SP_COMMANDPROCESSORACTION_38E35B0900D0_INCLUDED */
