/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SSM
--------------------------------------------------------------------------*/

#ifndef STATS_SSMCOLLECTIONACTION_H
#define STATS_SSMCOLLECTIONACTION_H

#include <vector>
#include <gdef.h>
#include <CommonTypes/CT_PMA_General.h>
#include <ExecutionSupport/FC_Action.h>
#include <TimeService/FC_Time.h>
#include <ExecutionSupport/FC_PeriodicProcess.h>

// Forward class declaration.
class FC_Object;
class FC_BbAction;
class STATS_DataSmartCardSubApplication;

class STATS_SsmCollectionAction: public FC_Action
{
public:
    //The Action's constructor.
	STATS_SsmCollectionAction(STATS_DataSmartCardSubApplication* theSubApp, CT_PMA_StatsEntityType theStatType);

    //The Collector's destructor.
    virtual ~STATS_SsmCollectionAction();

    // Entry point for doing work when trigger criterion are met.
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                       FC_Object* theInvokerObj,
                                       FC_Object* theParam= NULL);

    //Obsolete method
    virtual void Run(FC_Object* theObject = NULL);

private:
    STATS_DataSmartCardSubApplication* myStatsSubApp;
    FC_TimedProcess*                   myTimeoutProcess;
    CT_PMA_StatsEntityType             myActionStatType;
    uint32                             myRequestCount;
    uint32                             myInitStatsCount;
    bool                               myIsRequestPending;
};

#endif //STATS_SSMCOLLECTIONACTION_H

