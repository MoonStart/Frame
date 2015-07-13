/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for TCM layer
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_TcmCounters.h>
#include <Monitoring/MON_TcmDefects.h>
#include <Monitoring/MON_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_AppIf.h>
#include <Alarm/ALM_AppIf.h>
#include <Alarm/ALM_FailureRegionImp.h>
#include <Alarm/ALM_FailureBase.h>

#include <EPM/PM_BbDefectTcm.h>
#include <EPM/PM_BbCountTcm.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_TcmSubApplication.h>
#include <PM/PM_Def.h>
#include <EPM/PM_CollectorTcm.h>
#include <PM/PM_RegionImp.h>
//#include <PM/PM_BbCfg.h>


//-----------------------------------------------------------------
PM_CollectorTcm::PM_CollectorTcm (PM_GenericApplication&  theGenericApplication,
                                  FC_OneShotProcess&      theProcessorProcess,
                                  uint32                  theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_TCM_STRING, theNumberOfPort),
    myDefectTcm(NULL),
    myCountTcm(NULL)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_CollectorTcm::~PM_CollectorTcm ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_CollectorTcm::Init()
{
    // Initialize pointers to ODU status and defect regions.
    myDefectTcm = &(*myGenericApplication.GetRegionDefectTcm());
    myCountTcm = &(*myGenericApplication.GetRegionCountTcm());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorTcm::ProcessData()
{
    uint8 anIndex;

    for (anIndex = 0; anIndex < myNumberOfPort; anIndex++)
    {
        MON_TcmCounters &countersObject = (MON_TcmCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[anIndex];
        MON_TcmDefects &defectsObject = (MON_TcmDefects &)(*(myGenericApplication.GetMonApplication().GetDefectsRegion()))[anIndex];

        // Update error counters and defect-second counters.
        (*myDefectTcm)[anIndex].Update(defectsObject);
        (*myCountTcm)[anIndex].Update(countersObject);
    }

    // Call base class method.
    PM_Collector::ProcessData();
}


