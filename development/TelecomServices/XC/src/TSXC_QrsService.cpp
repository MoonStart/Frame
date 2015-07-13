/*--------------------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     December, 2007  Kumar C Solai
    DESCRIPTION:   TSXC_QrsService  Implementation
--------------------------------------------------------------------------*/
#include <XC/TSXC_QrsService.h>
#include <QRS/QRS_QueueManagerIf.h>

//--- Initialize the singleton pointer to NULL at the start
TSXC_QrsService* TSXC_QrsService::ItsInstance = NULL;

//--- Returns the pointer to the singleton class TSXC_QrsService
TSXC_QrsService* TSXC_QrsService::GetInstance()
{
    if (ItsInstance == NULL)
    {
        ItsInstance = new  TSXC_QrsService();
    }
    return ItsInstance;
}

//-----------------------------------------------------------------------------------
bool TSXC_QrsService::GetXcInitComplete()
{
    return QRS_QueueManagerIf::Instance()->GetXcInitComplete();
}

//-----------------------------------------------------------------------------------
bool TSXC_QrsService::GetXcByPassFlag()
{
    return QRS_QueueManagerIf::Instance()->GetXcByPassFlag();
}

//-----------------------------------------------------------------------------------
void TSXC_QrsService::RequestResponse(CT_XC_CQMID* theRespId)
{
    QRS_QueueManagerIf::Instance()->RequestResponse(
        theRespId->reqid,
        theRespId->step,
        true,                             // Status
        (QRS_QueueType)theRespId->type,
        theRespId->qmgrIdx);
}

