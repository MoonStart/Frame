// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef SP_1PLUS1CONFIGACTION_H
#define SP_1PLUS1CONFIGACTION_H

#include <ExecutionSupport/FC_Action.h>
#include "SP_ConfigAction.h"



//This class is an action that looks for new 1+1 configuration
// changes in the  config region and execute each one of them on 
//the corresponding protection group.
//##ModelId=3BBC9B39030E
class SP_1plus1ConfigAction 
: public SP_ConfigAction
{
public:
	//Constructor.  Requires the config region as 
	//well as a vector protection action.
	//##ModelId=3BBC9B390387
    SP_1plus1ConfigAction(    
        SP_ProtectionGroupConfigRegion& theConfigRegion,
		TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
		TEL_BbRegionBaseImp<SP_SwitchingCommand>& theSwitchCommandRegion,
        SP_ProtectionActions& theProtectionActions,
		uint32 theGroupCount);

    //Destructor.
	//##ModelId=3BBC9B3903A4
    virtual ~SP_1plus1ConfigAction();

	//Looks for new configuration in the config 
	//region and applies the to their corresponding 
	//protection action. 
	//##ModelId=3BBC9B3903A6
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
private:
	
};

#endif /* SP_1PLUS1CONFIGACTION_H */
