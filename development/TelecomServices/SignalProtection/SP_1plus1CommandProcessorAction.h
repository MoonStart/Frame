// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef SP_1PLUS1COMMANDPROCESSORACTION_H
#define SP_1PLUS1COMMANDPROCESSORACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include "SP_CommandProcessorAction.h"

class SP_ProtectionAction;
class SP_1plus1SwitchingCommandResult;
class SP_SwitchingCommand;


//This class is an action that looks for new 1+1 switching 
//command in command region and execute each one of them on 
//the corresponding protection group.
//##ModelId=3BBC9B39030E
class SP_1plus1CommandProcessorAction 
: public SP_CommandProcessorAction
{
public:
	//Constructor.  Requires the command and result region as 
	//well as a vector protection action.
	//##ModelId=3BBC9B390387
    SP_1plus1CommandProcessorAction(    
        TEL_BbRegionBaseImp<SP_SwitchingCommand>&       theSwitchCommandRegion,
        TEL_BbRegionBaseImp<SP_SwitchingCommandResult>& theSwitchCommandResultRegion,
		TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
        SP_ProtectionActions&                           theProtectionActions,
		uint32 theGroupCount);

    //Destructor.
	//##ModelId=3BBC9B3903A4
    virtual ~SP_1plus1CommandProcessorAction();

	//Looks for new switching command ID through the command 
	//region and applies the to their corresponding 
	//protection action. Also puts the execution result in 
	//the result region.
	//##ModelId=3BBC9B3903A6
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
private:
	//Pointer to the command result region.
	//##ModelId=3BBC9B3A009A
    TEL_BbRegionBaseImp<SP_SwitchingCommandResult>& mySwitchCommandResultRegion;
};

#endif /* SP_1PLUS1COMMANDPROCESSORACTION_H */
