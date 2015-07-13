/*--------------------------------------------------------------------------
Copyright(c) Tellabs Metro Networking Group. All rights reserved

SUBSYSTEM   :   Card Services
TARGET      :
AUTHOR      :   Jim Beck
DESCRIPTION :   Restore Action used to kick off the Ping Pong
                DPM restore.
--------------------------------------------------------------------------*/

#ifndef _CUD_PINGPONGRESTOREACTION_H_
#define _CUD_PINGPONGRESTOREACTION_H_

#include <DBManagement/DBM_CUDPingPongRestoreReqRegion.h>
#include <DBManagement/DBM_CUDPingPongRestoreReqObject.h>
#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_CUD_Definition.h>
#include <CUD/CUD_RmRestoreManager.h>
#include "CUD_BbRequest.h"
#include <ExecutionSupport/FC_ListOfAction.h>
#include <ExecutionSupport/FC_OneShotProcess.h>

class FC_PeriodicProcess;

template <class OBJECT_TYPE> class CUD_RegionImp;


class CUD_PingPongRestoreAction : public FC_Action
{
public:
    // Constructor
    CUD_PingPongRestoreAction(AS_IfRegionImp<DBM_CUDPingPongRestoreReqObject>& thePingPongRequestRegion);

    // Destructor
    virtual ~CUD_PingPongRestoreAction();

    void Run(FC_Object *theObject);

    uint32                myRequestId;

private:
    CUD_RmRestoreManager* myRestoreManager;

    AS_IfRegionImp<DBM_CUDPingPongRestoreReqObject>& myPingPongRestoreReqRegion;
};

#endif /* _CUD_PINGPONGRESTOREACTION_H_ */
