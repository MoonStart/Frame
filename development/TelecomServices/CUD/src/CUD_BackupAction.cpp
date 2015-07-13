/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     April, 2007 Jim Beck.
 DESCRIPTION:   Action invoked when a request of Configuration backup
                data was performed on Admin.
--------------------------------------------------------------------------*/

#include <CUD_RegionImp.h>
#include <CUD_BbRequest.h>
#include "CUD_BackupAction.h"
#include <DBManagement/DBM_CUDBackupResultRegion.h>
#include <DBManagement/DBM_CUDBackupResultObject.h>
#include <DBManagement/DBM_CUDBackupReqObject.h>
#include <CUD/CUD_Manager.h>
#include <CommonTypes/CT_CUD_Definition.h>
#include <AgentServices/AS_IfRegionImp.h>
#include <T6100_Dispatcher.h>


//-----------------------------------------------------------------
CUD_BackupAction::CUD_BackupAction(AS_IfRegionImp<DBM_CUDBackupReqObject>& theRequestRegion,
                                   AS_IfRegionImp<DBM_CUDBackupResultObject>& theResultRegion)
:
    myRequestId(0),
    myBackupReqRegion( theRequestRegion ),
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
CUD_BackupAction::~CUD_BackupAction()
{
    myBackupReqRegion.RemoveObserver(this);

    if (myTimeoutProcess)
    {
        myTimeoutProcess->Suspend();
        delete myTimeoutProcess;
    }

    myTimeoutProcess = 0;
}


//-----------------------------------------------------------------
void CUD_BackupAction::Run(FC_Object *theObject)
{
    if (myRequestPending == false)
    {
        if (myBackupReqRegion[0].GetBackupRequestID() != myRequestId)
        {
			// Clear out the result for this operation
            myRegionsToUpdate[0].SetBackupResult(CT_CUD_UNKNOWN);

            myRequestPending = true;

            // Setup a timer in case the module does not respond.
            myTimer.Start();

            // The Action has been triggered, call the CUD_Manager function
            // to backup all ISS Configuration files.
            CUD_Manager::GetInstance()->RequestAllConfigFiles(this,
                                  myBackupReqRegion[0].GetProhibitPktSaveFlag());

            // Update the request ID
            myRequestId = myBackupReqRegion[0].GetBackupRequestID();
        }
    }
    else
    {
        // If the Backup Request is pending and the timer has expired,
        // fail the command.
        if (myTimer.IsExpired())
        {
            myRequestPending = false;

            DownloadStatus(CT_CUD_FAILURE);
        }
    }
}


//-----------------------------------------------------------------
void CUD_BackupAction::DownloadStatus(CT_CUD_Status status)
{
    // If the Backup result passes validation set the result and notify
    // all observers.
    if ( myRegionsToUpdate[0].ValidateBackupResult(status) == true )
    {
        myRequestPending = false;

        myRegionsToUpdate[0].SetBackupResult(status);

        // Notify anyone listening to this region of the change.
        myRegionsToUpdate.IncModificationCounter();
        myRegionsToUpdate.UpdateNotify();
    }
}
