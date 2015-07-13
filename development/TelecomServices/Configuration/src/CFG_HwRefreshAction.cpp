//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_HwRefreshAction.h"
#include "Blackboard/FC_BbAction.h"
#include "ErrorService/FC_Error.h"
#include "T6100_CardActiveRegion.h"
#include "../CFG_AppIf.h"
#include "CommonTypes/CT_Telecom.h"
#include <cstring>

bool CFG_HwRefreshAction::myEnable = true;

//##ModelId=3C0FE6300070
CFG_HwRefreshAction::CFG_HwRefreshAction(CFG_AppIf& theCfgIf):
    myCfgIf(theCfgIf),
    myBbAction(NULL)
{
    // create BB action
    myBbAction =  new FC_BbAction(this);
    myBbAction->AddInputRegion(&myCfgIf.GetContextStatusRegion());
}

//##ModelId=3C0FE630008F
CFG_HwRefreshAction::~CFG_HwRefreshAction()
{
    myBbAction->RemoveInputRegion(&myCfgIf.GetContextStatusRegion());
    delete myBbAction;
}


void CFG_HwRefreshAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_NotSupportedError, "Run not supported");
}

FC_Object* CFG_HwRefreshAction::DoRunWithReason(unsigned theRunReason,
                                                FC_Object* theInvokerObj,
                                                FC_Object* theParam)
{
    // myEnable could be changed for debug purpose
    if (myEnable)
    {
        if (myCfgIf.GetContextStatusRegion().GetActive())
            return Process(theRunReason, theInvokerObj, theParam);
        else
            return Suspend(theRunReason, theInvokerObj, theParam);
    }
    return NULL;
}

FC_Object* CFG_HwRefreshAction::Suspend(unsigned theRunReason,
                                        FC_Object* theInvokerObj,
                                        FC_Object* theParam)
{
    //TODO: invalidate output region
    return NULL;
}



FC_CmdProcessor::STATUS CFG_HwRefreshAction::Debug(int argc, char **argv)
{
    char aParam[32];
    char aParamState[16];

    //We need at least 2 arguments
    if (argc < 2)
        goto OPTERROR;

    // avoid copy overflow.
    if ((strlen(argv[0])>32) || (strlen(argv[1])>16))
        goto OPTERROR;
    //Copy arguments
    strcpy(aParam, argv[0]);
    strcpy(aParamState, argv[1]);

    if (!strncmp(aParam,"hold",4))
    {
        fc_cout   << "HOLD OFF - Fix me " << endl;
        /*
        fc_cout   << "HOLD OFF - Last Returned Apply Condition     = " << DISPLAY_BOOL(myLastReturnedApplyCondition) << endl;
        fc_cout   << "HOLD OFF - HoldOff Timer Is Active           = " << DISPLAY_BOOL(myHoldOffTimerIsActive) << endl;
        fc_cout   << "HOLD OFF - Last 1st Holdoff Condition            = " << DISPLAY_BOOL(myLastHoldOffCondition) << endl;
        fc_cout   << "HOLD OFF - 1st Holdoff Start Count               = " << (uint32)myHoldOffStartCount << endl;
        fc_cout   << "HOLD OFF - 1st Holdoff Counter                   = " << (uint32)myHoldOffCounter << endl;
        fc_cout   << "HOLD OFF - Last 2nd Holdoff Condition        = " << DISPLAY_BOOL(myLast2ndHoldOffCondition) << endl;
        fc_cout   << "HOLD OFF - 2nd Holdoff Start Count           = " << (uint32)my2ndHoldOffStartCount << endl;
        fc_cout   << "HOLD OFF - 2nd Holdoff Counter               = " << (uint32)my2ndHoldOffCounter << endl;
        fc_cout   << "HOLD OFF - Last ALS HoldOff Delay (time)         = " << myHoldOffDelay << endl;
        */
    }
    else
    {
        goto OPTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OPTERROR:
    {
        fc_cout << "opt hold-off x   " << endl;
        fc_cout << "odu hold-off x   " << endl;
        fc_cout << "rs hold-off x    " << endl;
        fc_cout << "gfp hold-off x   " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_FAILURE;
}
