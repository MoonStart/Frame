/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     April 22, 2004 Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for GFP layer
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
//#include <Monitoring/MON_GfpCounters.h>
#include <Monitoring/MON_GfpDefects.h>
#include <Alarm/ALM_GfpFailureBase.h>
#include <Monitoring/MON_AppIf.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>
#include <PM/PM_BbDefectGfp.h>
#include <PM/PM_BbCountGfp.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_Def.h>
#include <PM/PM_CollectorGfp.h>


//-----------------------------------------------------------------
PM_CollectorGfp::PM_CollectorGfp (PM_GenericApplication&  theGenericApplication,
                                  FC_OneShotProcess&      theProcessorProcess,
                                  uint32                  theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_MS_NE_STRING, theNumberOfPort),
    myDefectGfp(NULL),
    myCountGfp(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_CollectorGfp::~PM_CollectorGfp ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorGfp::Init()
{
    // Initialize pointers to Gfp status and defect regions.
    myCountGfp = &(*myGenericApplication.GetRegionCountGfp());
    myDefectGfp = &(*myGenericApplication.GetRegionDefectGfp());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorGfp::ProcessData() 
{
    MON_GfpCounters &countersObject = (MON_GfpCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[0];
    MON_GfpDefects &defectsObject = (MON_GfpDefects &)(*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[0];

    // Update error counters, 
    (*myCountGfp)[0].Update(countersObject);
    (*myDefectGfp)[0].Update(defectsObject);

    // Call base class method.
    PM_Collector::ProcessData();

}
