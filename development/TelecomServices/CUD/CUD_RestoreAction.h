/*--------------------------------------------------------------------------
Copyright(c) Tellabs Metro Networking Group. All rights reserved

SUBSYSTEM   :   Card Services
TARGET      :
AUTHOR      :   Jim Beck
DESCRIPTION :   Restore Action used to bridge between the database
                restore command and the CUD (Configuration file
                Upload/Download) subsystem.
--------------------------------------------------------------------------*/

#ifndef _CUD_RESTOREACTION_H_
#define _CUD_RESTOREACTION_H_

#include <DBManagement/DBM_CUDRestoreReqRegion.h>
#include <DBManagement/DBM_CUDRestoreResultRegion.h>
#include <DBManagement/DBM_CUDRestoreResultObject.h>
#include <DBManagement/DBM_CUDRestoreReqObject.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <ExecutionSupport/FC_BaseTimer.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_CUD_Definition.h>
#include "CUD_BbRequest.h"
#include <ExecutionSupport/FC_ListOfAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>

class FC_PeriodicProcess;

template <class OBJECT_TYPE> class CUD_RegionImp;


class CUD_RestoreAction : public FC_Action
{
public:
    // Constructor
    CUD_RestoreAction(AS_IfRegionImp<DBM_CUDRestoreReqObject>& theRequestRegion,
                      AS_IfRegionImp<DBM_CUDRestoreResultObject>& theResponseRegion);

    // Destructor
    virtual ~CUD_RestoreAction();

    void Run(FC_Object *theObject);

    virtual void RestoreStatus(CT_CUD_Status status);

private:
    uint32 myRequestId;

    AS_IfRegionImp<DBM_CUDRestoreReqObject>& myRestoreReqRegion;
    AS_IfRegionImp<DBM_CUDRestoreResultObject>& myRegionsToUpdate;

    bool                myRequestPending;

    FC_PeriodicProcess* myTimeoutProcess;
    FC_BaseTimer        myTimer;
};

#endif /* _CUD_RESTOREACTION_H_ */

