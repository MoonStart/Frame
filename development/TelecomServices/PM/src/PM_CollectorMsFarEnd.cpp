/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 2004 Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for Far-End SONET/SDH MS layer
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_MsCounters.h>
#include <Monitoring/MON_MsDefects.h>
#include <Monitoring/MON_AppIf.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <PM/PM_BbDefectMsFarEnd.h>
#include <PM/PM_BbFailureMsFarEnd.h>
#include <PM/PM_BbCountMsFarEnd.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_Def.h>
#include <PM/PM_CollectorMsFarEnd.h>


//-----------------------------------------------------------------
PM_CollectorMsFarEnd::PM_CollectorMsFarEnd (PM_GenericApplication&  theGenericApplication,
                                            FC_OneShotProcess&      theProcessorProcess,
                                            uint32                  theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_MS_FE_STRING, theNumberOfPort),
    myDefectMsFarEnd(NULL),
    myCountMsFarEnd(NULL),
    myFailureMsFarEnd(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_CollectorMsFarEnd::~PM_CollectorMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorMsFarEnd::Init()
{
    // Initialize pointers to MsFarEnd status and defect regions.
    myDefectMsFarEnd = &(*myGenericApplication.GetRegionDefectMsFarEnd());
    myCountMsFarEnd = &(*myGenericApplication.GetRegionCountMsFarEnd());
    myFailureMsFarEnd = &(*myGenericApplication.GetRegionFailureMsFarEnd());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorMsFarEnd::ProcessData() 
{
    MON_MsCounters &countersObject = (MON_MsCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[0];
    MON_MsDefects &defectsObject = (MON_MsDefects &)(*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[0];
    ALM_FailureBase &failureObject = (ALM_FailureBase &)(*(myGenericApplication.GetAlmMsApplication().GetFilteredRegionPtr()))[0];

    // Update Regenerator error counters, 
    // defect-second counters and failure-second counters.
    (*myDefectMsFarEnd)[0].Update(defectsObject);
    (*myCountMsFarEnd)[0].Update(countersObject);
    (*myFailureMsFarEnd)[0].Update(failureObject);

    // Call base class method.
    PM_Collector::ProcessData();

}
