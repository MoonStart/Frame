// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_CONFIGACTION_38E35B0900D0_INCLUDED
#define _INC_SP_CONFIGACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include "SP_ProtectionGroupConfigRegion.h"
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <vector>
#include "SP_Definitions.h"
#include "SP_ApplicationStatus.h"


class SP_ProtectionAction;
class FC_BbAction;
class FC_OneShotProcess;
class FC_TimedProcess;
class FC_WakeUpProcessAction;
class SP_SwitchingCommand;
class FC_TimedProcess;


//This class handles configuration request coming from the admin. 
//There is one config action per side per protection type. 
// This class is a 
//base class for all config actions of signal protection.
//##ModelId=38E35B0900D0
class SP_ConfigAction 
: public FC_Action
{
public:
	//Constructor. Requires config region and protection 
	//actions vector. 
    //##ModelId=3BBC9B0F02A0
    SP_ConfigAction(  
        SP_ProtectionGroupConfigRegion& theConfigRegion,
		TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
		TEL_BbRegionBaseImp<SP_SwitchingCommand>& theSwitchCommandRegion,
        SP_ProtectionActions& theProtectionActions,
		uint32 theGroupCount);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_ConfigAction();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

	//This method handles config request coming from the 
	//admin. 
    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL) = 0;

	//Forces the config action to start if it was 
	//stopped(debug).
    //##ModelId=39ACEFB00072
    inline void Start();
	//Forces the configuration action to stop (debug).
    //##ModelId=39ACEFB0005E
    inline void Stop();

	//Returns a reference to the low priority wake up action.
	//##ModelId=39ACEFA0000B
    inline FC_WakeUpProcessAction& GetLowPriorityWakeUpAction();

    FC_BbAction* GetBbAction() { return myBbAction; }

protected:
	//Reference to the config region.
    //##ModelId=394102B8010F
    SP_ProtectionGroupConfigRegion& myConfigRegion;

	//Reference to the vector of protection actions
    //##ModelId=3BC5A34B02E3
    SP_ProtectionActions& myProtectionActions;

	//Reference to the app ready region
	TEL_BbRegionBaseImp<SP_ApplicationStatus> & myAppStatusRegion;

	//Reference to the command region
	TEL_BbRegionBaseImp<SP_SwitchingCommand>& mySwitchCommandRegion;

	//Pointer to the low priority wake up action usually 
	//execute for low priority event (configuration or 
	//command update).
	//##ModelId=39ACEF9F02E5
    FC_WakeUpProcessAction* myLowPriorityCallbackAction;

	//Low priority process running low priority action.
	//##ModelId=3B8BC9BD01FE
    FC_OneShotProcess* myLowPriorityProcess;

	FC_TimedProcess* myTimedProcess;

	//True if processing is stop (debug).
    //##ModelId=39ACEFB0002C
    bool stopped;

	//The number of protection groups this action processes
	uint32 myGroupCount;


private:
    FC_BbAction* myBbAction;

};

//##ModelId=39ACEFB00072
inline void SP_ConfigAction::Start() { stopped = false; }
//##ModelId=39ACEFB0005E
inline void SP_ConfigAction::Stop() { stopped = true; }

//##ModelId=39ACEFA0000B
inline FC_WakeUpProcessAction& SP_ConfigAction::GetLowPriorityWakeUpAction()
{
    return *myLowPriorityCallbackAction;
}

#endif /* _INC_SP_CONFIGACTION_38E35B0900D0_INCLUDED */
