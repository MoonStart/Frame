// Copyright(c) Tellabs Transport Group. All rights reserved.

#include <CommonTypes/CT_SP_CommandType.h>
#include "../SP_SwitchingCommand.h"
#include "../SP_SwitchingCommandResult.h"
#include "../SP_ProtectionAction.h"
#include "../SP_1plus1CommandProcessorAction.h"
#include <Blackboard/FC_BbAction.h>

//##ModelId=3BBC9B390387
SP_1plus1CommandProcessorAction::SP_1plus1CommandProcessorAction(
    TEL_BbRegionBaseImp<SP_SwitchingCommand>&       theSwitchCommandRegion,
    TEL_BbRegionBaseImp<SP_SwitchingCommandResult>& theSwitchCommandResultRegion,
    TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
    SP_ProtectionActions&                           theProtectionActions,
    uint32 theGroupCount) :
    SP_CommandProcessorAction(theSwitchCommandRegion, theAppStatusRegion, theProtectionActions, theGroupCount),
    mySwitchCommandResultRegion(theSwitchCommandResultRegion)
{
    GetBbAction()->AddOutputRegion(&mySwitchCommandResultRegion);
}

//##ModelId=3BBC9B3903A4
SP_1plus1CommandProcessorAction::~SP_1plus1CommandProcessorAction()
{
}

//##ModelId=3BBC9B3903A6
FC_Object* SP_1plus1CommandProcessorAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;

    uint32 anIndex = 0;

    for (anIndex = 0; anIndex < myGroupCount; anIndex++)
    {
        SP_SwitchingCommand* aCommand = &(mySwitchCommandRegion[(bbindex_t)anIndex]);
        //get the protection group associated with this command object
        SP_ProtectionAction* aProtectionAction = myProtectionActions[(bbindex_t)anIndex];
        // if group is not enabled, skip it.
        if (aProtectionAction->IsEnabled())
        {

            // Execute command and save result
            SP_SwitchingCommandResult* aResult     = &(mySwitchCommandResultRegion[(bbindex_t)anIndex]);
            CT_SP_CommandResultCode    aResultCode = aProtectionAction->ExecuteSwitchingCommand(CT_SP_CommandType(aCommand->GetCommand()), aCommand->GetCommandID());
            aResult->SetCommandStatus(aResultCode, aCommand->GetCommandID());


        }
    }

    //now that all commands have been applied, update the result region counter
    mySwitchCommandResultRegion.IncModificationCounter();
    mySwitchCommandResultRegion.UpdateNotify();

    return NULL;
}
