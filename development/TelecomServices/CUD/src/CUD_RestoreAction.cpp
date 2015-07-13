/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     April, 2007 Jim Beck.
 DESCRIPTION:   Action invoked when a request of Configuration Restore
                data was performed on Admin.
--------------------------------------------------------------------------*/

#include <CUD_RegionImp.h>
#include <CUD_BbRequest.h>
#include "CUD_RestoreAction.h"
#include <DBManagement/DBM_CUDRestoreResultRegion.h>
#include <DBManagement/DBM_CUDRestoreResultObject.h>
#include <DBManagement/DBM_CUDRestoreReqObject.h>
#include <CUD/CUD_Manager.h>
#include <CommonTypes/CT_CUD_Definition.h>
#include <AgentServices/AS_IfRegionImp.h>
#include <T6100_Dispatcher.h>


//-----------------------------------------------------------------
CUD_RestoreAction::CUD_RestoreAction(AS_IfRegionImp<DBM_CUDRestoreReqObject>& theRequestRegion,
                                     AS_IfRegionImp<DBM_CUDRestoreResultObject>& theResultRegion)
:
    myRequestId(0),
    myRestoreReqRegion( theRequestRegion ),
    myRequestPending(false),
    myTimeoutProcess(NULL),
    myTimer(CUD_CARD_TIMEOUT_VALUE),
    myRegionsToUpdate( theResultRegion )
{
    theRequestRegion.AddObserver(this);

    myTimeoutProcess =
                new FC_PeriodicProcess(*this, gTimerDispatcher, CUD_CHK_CARD_TIMEOUT);

    myTimeoutProcess->WakeUp();
}


//-----------------------------------------------------------------
CUD_RestoreAction::~CUD_RestoreAction()
{
    myRestoreReqRegion.RemoveObserver(this);

    if (myTimeoutProcess)
    {
        myTimeoutProcess->Suspend();
        delete myTimeoutProcess;
    }

    myTimeoutProcess = 0;
}


//-----------------------------------------------------------------
void CUD_RestoreAction::Run(FC_Object *theObject)
{
    if (myRequestPending == false)
    {
        if (myRestoreReqRegion[0].GetRestoreRequestID() != myRequestId)
        {
            myRequestPending = true;

            // Clear out the result
            myRegionsToUpdate[0].SetRestoreResult(CT_CUD_UNKNOWN);

            // Setup a timer in case the module does not respond.
            myTimer.Start();

            // The Action has been triggered, call the CUD_Manager function
            // to restore all ISS Configuration files.
            CUD_Manager::GetInstance()->DownloadAllConfigFiles(this);

            // Update the request ID
            myRequestId = myRestoreReqRegion[0].GetRestoreRequestID();
        }
    }
    else
    {
        // If the Restore request is pending and the timer
        // has expired, fail the command.
        if (myTimer.IsExpired())
        {
            myRequestPending = false;

            // The Command timed out, backout the Restore attempt on all
            // modules that completed restore.
            CUD_Manager::GetInstance()->BackoutRestoreOnAllDpmModules();

            RestoreStatus(CT_CUD_FAILURE);
        }
    }
}


//-----------------------------------------------------------------
void CUD_RestoreAction::RestoreStatus(CT_CUD_Status status)
{
    // If the Restore result passes validation set the result and notify
    // all observers.
    if ( myRegionsToUpdate[0].ValidateRestoreResult(status) == true )
    {
        myRequestPending = false;

        myRegionsToUpdate[0].SetRestoreResult(status);

        // Notify anyone listening to this region of the change.
        myRegionsToUpdate.IncModificationCounter();
        myRegionsToUpdate.UpdateNotify();
    }
}
