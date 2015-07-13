/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     July, 2007 Jim Beck.
 DESCRIPTION:   Action invoked when a request of DPM Restore data
                was performed on Admin.
--------------------------------------------------------------------------*/

#include <CUD_RegionImp.h>
#include <CUD_BbRequest.h>
#include "CUD_PingPongRestoreAction.h"
#include <DBManagement/DBM_CUDPingPongRestoreReqObject.h>
#include <CUD/CUD_RmManager.h>
#include <CommonTypes/CT_CUD_Definition.h>
#include <AgentServices/AS_IfRegionImp.h>
#include <T6100_Dispatcher.h>


//-----------------------------------------------------------------
CUD_PingPongRestoreAction::CUD_PingPongRestoreAction(AS_IfRegionImp<DBM_CUDPingPongRestoreReqObject>& thePingPongRequestRegion)
:
    myRequestId(0),
    myPingPongRestoreReqRegion( thePingPongRequestRegion )
{
    myPingPongRestoreReqRegion.AddObserver(this);
}


//-----------------------------------------------------------------
CUD_PingPongRestoreAction::~CUD_PingPongRestoreAction()
{
    myPingPongRestoreReqRegion.RemoveObserver(this);
}


//-----------------------------------------------------------------
void CUD_PingPongRestoreAction::Run(FC_Object *theObject)
{
    if (myPingPongRestoreReqRegion[0].GetRestoreRequestID() != myRequestId)
    {
        // Update the request ID
        myRequestId = myPingPongRestoreReqRegion[0].GetRestoreRequestID();

        // The Action has been triggered, call the CUD_RmManager function
        // to backup all ISS Configuration files.
        CUD_RmManager::GetInstance()->startPingPongRestore();
    }
}
