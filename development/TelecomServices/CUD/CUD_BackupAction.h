/*--------------------------------------------------------------------------
Copyright(c) Tellabs Metro Networking Group. All rights reserved

SUBSYSTEM   :   Card Services
TARGET      :
AUTHOR      :   Jim Beck
DESCRIPTION :   Backup Action used to bridge between the backup
                command and the CUD (Configuration file
                Upload/Download) subsystem.
--------------------------------------------------------------------------*/

#ifndef _CUD_BACKUPACTION_H_
#define _CUD_BACKUPACTION_H_

#include <DBManagement/DBM_CUDBackupReqRegion.h>
#include <DBManagement/DBM_CUDBackupResultRegion.h>
#include <DBManagement/DBM_CUDBackupResultObject.h>
#include <DBManagement/DBM_CUDBackupReqObject.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <ExecutionSupport/FC_BaseTimer.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_CUD_Definition.h>
#include "CUD_BbRequest.h"
#include <ExecutionSupport/FC_ListOfAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>

class FC_PeriodicProcess;

template <class OBJECT_TYPE> class CUD_RegionImp;


class CUD_BackupAction : public FC_Action
{
public:
    // Constructor
    CUD_BackupAction(AS_IfRegionImp<DBM_CUDBackupReqObject>& theRequestRegion,
                     AS_IfRegionImp<DBM_CUDBackupResultObject>& theResponseRegion);

    // Destructor
    virtual ~CUD_BackupAction();

    void Run(FC_Object *theObject);

    virtual void DownloadStatus(CT_CUD_Status status);

private:
    uint32 myRequestId;

    AS_IfRegionImp<DBM_CUDBackupReqObject>& myBackupReqRegion;
    AS_IfRegionImp<DBM_CUDBackupResultObject>& myRegionsToUpdate;

    bool                myRequestPending;

    FC_PeriodicProcess* myTimeoutProcess;
    FC_BaseTimer        myTimer;
};

#endif /* _CUD_BACKUPACTION_H_ */

