// Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../SP_ConfigMismatchDetectAction.h"
#include "../SP_1plus1ProtectionAction.h"
#include <ErrorService/FC_Error.h>
#include <T6100_Services.h>
#include <T6100_Dispatcher.h>
//#include <T6100_MainAppIf.h>
//#include <T6100_TelecomIf.h>
#include <Blackboard/FC_BbAction.h>

#ifdef __TARGET__
    #define SP_FIX_CONFIG_MISMATCH 1
#endif

#define MAX_PROCESS_PER_ITERATION 20
//TEMP
//#define SP_FIX_CONFIG_MISMATCH 1

int gSP_CfgMismatchDebugTrace = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This action is responsible detecting and correcting configuration mismatch
//Configuration mismatch includes "dual-on" and "dual-off" scenarios
////////////////////////////////////////////////////////////////////////////
SP_ConfigMismatchDetectAction::SP_ConfigMismatchDetectAction(
    SP_1plus1SubApplication& theApplIf,
    SP_ProtectionActions& theProtectionActions,
    SP_ProtectionGroupConfigRegion& theConfigRegion):
    myProtectionActions(theProtectionActions),
    myConfigRegion(theConfigRegion),
    myIndex(0)
{
    myProcess = new FC_PeriodicProcess(*this, gTimerDispatcher, 5000/*5secs poll rate*/);
    myProcess->WakeUp();
}

//##ModelId=38EDF51800A6
SP_ConfigMismatchDetectAction::~SP_ConfigMismatchDetectAction()
{
    myProcess->SuspendImmediate();
    delete myProcess;
    myProcess = NULL;
}

//##ModelId=3B8BC9D30390
void SP_ConfigMismatchDetectAction::Run( FC_Object* theObject )
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* SP_ConfigMismatchDetectAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    uint32 loopCount = myIndex + MAX_PROCESS_PER_ITERATION;
    if (loopCount  >= myProtectionActions.size())
        loopCount = myProtectionActions.size();

    for (; myIndex < loopCount; myIndex++)
    {
        //get the protection group associated with this config object
        SP_1plus1ProtectionAction* aProtectionAction = static_cast<SP_1plus1ProtectionAction*>(myProtectionActions[myIndex]);

        //if the current state is enabled
        //check whether the group needs to be disabled and re-enabled to correct a configuration mismatch...
        if (aProtectionAction->IsEnabled())
        {
            if (aProtectionAction->IsConfigurationMismatch())
            {
#ifdef SP_FIX_CONFIG_MISMATCH
                SP_ProtectionGroupConfig& aConfig = static_cast<SP_ProtectionGroupConfig&>(myConfigRegion[(bbindex_t)myIndex]);
                if (!aProtectionAction->IsProtectionGroupDifferent(aConfig))
                {
                    if (gSP_CfgMismatchDebugTrace == 1)
                    {
                        fc_cout << "SP_ConfigMismatchDetectAction: Index: " << myIndex << ", configuration mismatch detected, correcting" << endl;
                    }
                    //SP_ProtectionGroupConfig& aConfig = aProtectionAction->GetConfig();
                    aProtectionAction->DisableBase();
                    aProtectionAction->CopyConfiguration(aConfig);
                    aProtectionAction->Enable();
                    aProtectionAction->ApplyConfiguration();
                }
#endif
            }
        }
    }

    if (myIndex >= myProtectionActions.size())
        myIndex =0;

    return NULL;
}

FC_PeriodicProcess* SP_ConfigMismatchDetectAction::GetProcessPtr()
{
    return myProcess;
}