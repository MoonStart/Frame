// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <TsPii/TSPII_OpticalIf.h>
#include <ErrorService/FC_Error.h>
#include "../MON_TxOptOnDemandAction.h"
#include "../MON_TxOptRequest.h"
#include "../MON_TxOptResult.h"
#include "../MON_AppIf.h"
#include "../MON_Region.h"


MON_TxOptOnDemandAction::MON_TxOptOnDemandAction(MON_AppIf& theMonIf,
                                                 TSPII_OpticalRegion& theOptPiiRegion):
    MON_UpdateStatusAction(theMonIf,NULL),
    myOptPiiRegion(theOptPiiRegion),
    myRequestID(0)
{
    GetBbAction()->AddInputRegion(GetMonIf().GetRequestRegion());
    GetBbAction()->AddOutputRegion(GetMonIf().GetResultRegion(), false);
}

MON_TxOptOnDemandAction::~MON_TxOptOnDemandAction()
{
    GetBbAction()->RemoveInputRegion(GetMonIf().GetRequestRegion());
    GetBbAction()->RemoveOutputRegion(GetMonIf().GetResultRegion());
}

FC_Object* MON_TxOptOnDemandAction::Suspend(unsigned theRunReason,
                                            FC_Object* theInvokerObj,
                                            FC_Object* theParam)
{
    GetMonIf().GetResultRegion()->Reset();
    return NULL;
}

FC_Object* MON_TxOptOnDemandAction::Process(unsigned theRunReason,
                                            FC_Object* theInvokerObj,
                                            FC_Object* theParam)
{
    MON_TxOptRequest& aRequest = static_cast<MON_TxOptRequest&>((*GetMonIf().GetRequestRegion())[0]);
    MON_TxOptResult& aResult = static_cast<MON_TxOptResult&>((*GetMonIf().GetResultRegion())[0]);
    TSPII_OpticalIf& aOptPii = myOptPiiRegion[0];
    MON_RequestID aNewRequestID = aRequest.GetRequestID();

    //Check if it is a new request
    if(aNewRequestID != myRequestID)
    {
        //Fill result region
        aResult.SetRequestID(aRequest.GetRequestID());
        aResult.SetTransmitPower(aOptPii.GetOpticalPowerTransmitted());

        //Update our current request ID
        myRequestID = aNewRequestID;

        //Validate the object
        aResult.Validate();

        GetMonIf().GetResultRegion()->IncModificationCounter();
    }

    return NULL;
}
