// Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../SP_ProtectionAction.h"
#include "../SP_1plus1ProtectionAction.h"
#include "../SP_1plus1ConfigAction.h"
#include "../SP_ProtectionGroupConfig.h"
#include "../SP_ApplicationStatus.h"
#include "../SP_SwitchingCommand.h"
#include <Blackboard/FC_BbAction.h>
#include <ExecutionSupport/FC_TimedProcess.h>

//##ModelId=3BBC9B390387
SP_1plus1ConfigAction::SP_1plus1ConfigAction(
        SP_ProtectionGroupConfigRegion& theConfigRegion,
        TEL_BbRegionBaseImp<SP_ApplicationStatus> & theAppStatusRegion,
        TEL_BbRegionBaseImp<SP_SwitchingCommand>& theSwitchCommandRegion,
        SP_ProtectionActions& theProtectionActions,
        uint32 theGroupCount) :
        SP_ConfigAction(theConfigRegion, theAppStatusRegion, theSwitchCommandRegion, theProtectionActions, theGroupCount)
{

}

//##ModelId=3BBC9B3903A4
SP_1plus1ConfigAction::~SP_1plus1ConfigAction()
{
}

//##ModelId=3BBC9B3903A6
FC_Object* SP_1plus1ConfigAction::DoRunWithReason(unsigned theRunReason,
                                                          FC_Object* theInvokerObj,
                                                          FC_Object* theParam)
{
    if (stopped) return NULL;

    uint32 anIndex = 0;
    bool isReady = true;

    //first iterate through the region to perform
    //any deletes
    //This allows for clean up prior to any new
    //updates
    for (anIndex = 0; anIndex < myGroupCount; anIndex++)
    {
        SP_ProtectionGroupConfig& aConfig = static_cast<SP_ProtectionGroupConfig&>(myConfigRegion[(bbindex_t)anIndex]);
        //get the protection group associated with this config object
        SP_ProtectionAction* aProtectionAction = static_cast<SP_ProtectionAction*>(myProtectionActions[anIndex]);

        //if the current state is enabled
        //check whether the group needs to be disabled
        if (aProtectionAction->IsEnabled())
        {
            //The group needs to be disabled if the usage status has changed
            //or the 1p1 type is different or the sources are different
            if (aProtectionAction->IsProtectionGroupDifferent(aConfig))
            {
                aProtectionAction->Disable();
            }
        }

    }

    //Now iterate through the region and perform any creates
    //or updates
    bool hasConfigChanged = false;
    for (anIndex = 0; anIndex < myGroupCount; anIndex++)
    {
        hasConfigChanged = false;
        SP_ProtectionGroupConfig& aConfig = static_cast<SP_ProtectionGroupConfig&>(myConfigRegion[(bbindex_t)anIndex]);
        //get the protection group associated with this config object
        SP_1plus1ProtectionAction* aProtectionAction = static_cast<SP_1plus1ProtectionAction*>(myProtectionActions[anIndex]);
        bool oldUsageStatus = aProtectionAction->IsEnabled();
        if (aConfig.InUse() && !oldUsageStatus)
        {
            //Configure protection scheme if allowed to with current configuration
            if (aProtectionAction->IsConfigurationAllowed(aConfig))
            {
                //Creating a new protection scheme. Check whether
                //all required resources are available
                if (aProtectionAction->IsResourceReady(aConfig))
                {
                    //copy the configuration
                    aProtectionAction->CopyConfiguration(aConfig);
                    aProtectionAction->Enable();
                    aProtectionAction->ApplyConfiguration();
                    aProtectionAction->RestartComplete();
                }
                else
                {
                    isReady = false;
                }
            }
        }
        else
        {
            //copy the configuration
            hasConfigChanged = aProtectionAction->CopyConfiguration(aConfig);
            if (hasConfigChanged)
                aProtectionAction->ApplyConfiguration();
            aProtectionAction->RestartComplete();
        }
    }

    //SP application has been fully configured
    //Indicate this in the readiness region
    SP_ApplicationStatus& aAppStatus = static_cast<SP_ApplicationStatus&>(myAppStatusRegion[0]);
    if (aAppStatus.IsStatusDifferent(true) && isReady)
    {
        aAppStatus.SetApplicationStatus(true);
        //increment the modification counter
        myAppStatusRegion.IncModificationCounter();
        //update notify
        myAppStatusRegion.UpdateNotify();

        //Now that application is initialized, we do not need
        //the command region as an input region anymore.
        //Remove the command region from the list of input regions
        //for this action so that we do not get woken up when a user command
        //changes.
        GetBbAction()->RemoveInputRegion(&mySwitchCommandRegion);
    }

    if (isReady == false)
    {
        //wake ourselves up for run later
        myTimedProcess->WakeUp();
    }

    return NULL;
}
