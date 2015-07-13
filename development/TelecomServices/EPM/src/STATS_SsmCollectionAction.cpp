/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SSM
--------------------------------------------------------------------------*/
#include "../STATS_SsmCollectionAction.h"

#include <list>
#include <ErrorService/FC_Error.h>
#include <TimeService/FC_TimeService.h>
#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>
#include <ExecutionSupport/FC_TimedProcess.h>
#include <ExecutionSupport/FC_TimerDispatcher.h>
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100/T6100_CardIf.h>
#include <PM/STATS_DataSmartCardSubApplication.h>
#include <CommonTypes/CT_PMA_General.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_SsmIf.h>
#include <TsPii/TSPII_VcgIf.h>

using namespace std;

//-----------------------------------------------------------------
STATS_SsmCollectionAction::STATS_SsmCollectionAction(STATS_DataSmartCardSubApplication* theSubApp, 
                                                     CT_PMA_StatsEntityType theStatType) :

    myStatsSubApp(theSubApp),
    myActionStatType(theStatType),
    myRequestCount(0),
    myInitStatsCount(0),
    myIsRequestPending(false)
{
    myTimeoutProcess = new FC_TimedProcess(*this, gTimerDispatcher, 1000);
    myTimeoutProcess->SuspendImmediate();
}

//-----------------------------------------------------------------
STATS_SsmCollectionAction::~STATS_SsmCollectionAction()
{
    delete myTimeoutProcess;
}

//-----------------------------------------------------------------
FC_Object* STATS_SsmCollectionAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvokerObj, FC_Object* theParam)
{
    STATS_RequestRegion* aRequest = dynamic_cast<STATS_RequestRegion*>(theInvokerObj);
 
    if ( aRequest ) 
    {
        if ( (*aRequest)[0].GetInitStatsCount() != myInitStatsCount ) // new request
        {
            myInitStatsCount = (*aRequest)[0].GetInitStatsCount();
            bbindex_t aInitStatsEntityId = (bbindex_t)((*aRequest)[0].GetInitStatsEntityId());
            //----------------------------------------------------------
            // Call TSPII to inform about the new request!
            //----------------------------------------------------------
            TSPII_VcgRegion* theVcgRegion = TSPII_SubApplication::GetInstance()->GetVcg();
            TSPII_VcgIf&         theVcgIf = static_cast<TSPII_VcgIf&> ((*theVcgRegion)[aInitStatsEntityId]);
            theVcgIf.ClearVcgStats(); // Reset VCG Stats!
        }

        if ( (*aRequest)[0].GetRequestCount() != myRequestCount ) // new request 
        {
            myRequestCount = (*aRequest)[0].GetRequestCount();
            bbindex_t aRequestEntityId = (bbindex_t)((*aRequest)[0].GetRequestEntityId());

            if ( myActionStatType == CT_PMA_STATS_ENTITY_VCG )
            {
                uint32 theIngressEnqueueDropFrames, theIngressEnqueueFrames, theIngressDequeueFrames;
                uint32 theEgressEnqueueDropFrames,  theEgressEnqueueFrames,  theEgressDequeueFrames;
                TSPII_VcgRegion* theVcgRegion = TSPII_SubApplication::GetInstance()->GetVcg();
                TSPII_VcgIf&         theVcgIf = static_cast<TSPII_VcgIf&> ((*theVcgRegion)[aRequestEntityId]);

                theVcgIf.GetVcgStats( theIngressEnqueueDropFrames, 
                                      theIngressEnqueueFrames, 
                                      theIngressDequeueFrames, 
                                      theEgressEnqueueDropFrames, 
                                      theEgressEnqueueFrames, 
                                      theEgressDequeueFrames);
                // Update Response!
                //-----------------
                STATS_Response* aStatsResponse = &((*myStatsSubApp->GetStatsResponseRegion(myActionStatType))[0]);
                aStatsResponse->ResetData();
                aStatsResponse->SetRequestCount( myRequestCount );
                aStatsResponse->UpdateStatsDataMap(CT_PMA_INGENQDROPFRAME_STAT_ID, theIngressEnqueueDropFrames);
                aStatsResponse->UpdateStatsDataMap(CT_PMA_INGENQFRAME_STAT_ID,     theIngressEnqueueFrames);
                aStatsResponse->UpdateStatsDataMap(CT_PMA_INGDEQFRAME_STAT_ID,     theIngressDequeueFrames);
                aStatsResponse->UpdateStatsDataMap(CT_PMA_EGRENQDROPFRAME_STAT_ID, theEgressEnqueueDropFrames);
                aStatsResponse->UpdateStatsDataMap(CT_PMA_EGRENQFRAME_STAT_ID,     theEgressEnqueueFrames);
                aStatsResponse->UpdateStatsDataMap(CT_PMA_EGRDEQFRAME_STAT_ID,     theEgressDequeueFrames);

                myStatsSubApp->GetStatsResponseRegion(myActionStatType)->IncModificationCounter();
                myStatsSubApp->GetStatsResponseRegion(myActionStatType)->UpdateNotify();
            }
            else if ( myActionStatType == CT_PMA_STATS_ENTITY_EQPT )
            {
                myIsRequestPending = true;
                //----------------------------------------------------------
                // Call TSPII to inform about the new request!
                //----------------------------------------------------------
                TSPII_SsmRegion* theSsmRegion = TSPII_SubApplication::GetInstance()->GetSsm();
                TSPII_SsmIf&         theSsmIf = static_cast<TSPII_SsmIf&> ((*theSsmRegion)[0]);

                theSsmIf.StartEqptStatsCollection(TSPII_SSMIF_LAYER_L2); 
                //----------------------------------------------------------
                // WakeUp() after the requested period of time!
                //----------------------------------------------------------
                myTimeoutProcess->SetDelay( ((*aRequest)[0].GetDuration()) * 1000 ); // Duration in SECs!
                myTimeoutProcess->WakeUp();
            }
        }
    }
    else if ( myIsRequestPending ) // ONLY true for EQPT!
    {
        //--------------------------------------------------------------
        // Is the Data region (VCG or EQPT) updated from the Backend? 
        //--------------------------------------------------------------
        if ( myTimeoutProcess->GetTimer().IsExpired() )
        {
            //------------------------------------------------------
            // Request has completed! Notify TL1 thru Response Region.
            //------------------------------------------------------
            myIsRequestPending = false;
            myTimeoutProcess->SuspendImmediate();

            TSPII_SsmRegion* theSsmRegion = TSPII_SubApplication::GetInstance()->GetSsm();
            TSPII_SsmIf&         theSsmIf = static_cast<TSPII_SsmIf&> ((*theSsmRegion)[0]);

            list<string> aStrList;
            theSsmIf.GetEqptStats(TSPII_SSMIF_LAYER_L2, &aStrList);

            STATS_Response* aStatsResponse = &((*myStatsSubApp->GetStatsResponseRegion(myActionStatType))[0]);
            aStatsResponse->ResetData();
            aStatsResponse->SetRequestCount( myRequestCount );
            aStatsResponse->UpdateStatsDataList( aStrList );

            myStatsSubApp->GetStatsResponseRegion(myActionStatType)->IncModificationCounter();
            myStatsSubApp->GetStatsResponseRegion(myActionStatType)->UpdateNotify();
        }
    }

    return NULL;
}

//-----------------------------------------------------------------
void STATS_SsmCollectionAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_SWError, "Run method is obsoleted!");
}
