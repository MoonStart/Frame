/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Process that collects the data needed by the PM Processor Odu Counter.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OduCounters.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_MacStatus.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_AppIf.h>

#include <EPM/PM_BbStatusOdu.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_Processor.h>
#include <PM/PM_OduGaugeSubApplication.h>
#include <PM/PM_Def.h>
#include <EPM/PM_CollectorOduGauge.h>
#include <EPM/src/PM_AutoRateLock.h>

//------------------------
// Class PM_CollectorOduGauge
//------------------------

//-----------------------------------------------------------------
PM_CollectorOduGauge::PM_CollectorOduGauge( PM_GenericApplication& theGenericApplication,
											  FC_OneShotProcess&   theProcessorProcess,
											  uint32               theNumberOfPort ) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_ODU_STRING, theNumberOfPort),
    myStatusOduGauge(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_CollectorOduGauge::~PM_CollectorOduGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorOduGauge::Init()
{
    // Initialize pointers to optical status and defect regions.
    myStatusOduGauge = &(*myGenericApplication.GetRegionStatusOduGauge());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorOduGauge::ProcessData() 
{
    MON_AppIf* monOduApp = myGenericApplication.GetMonApplicationPtr(0);
    if ( monOduApp ) 
    {
        for (uint8 anIndex = 0; anIndex < myNumberOfPort; anIndex++)
        {
            MON_OduStatus &statusObject = (MON_OduStatus &)(*(monOduApp->GetStatusRegion()))[anIndex];
            (*myStatusOduGauge)[anIndex].Update(statusObject);
        }
    }

    // Call base class method.
    PM_Collector::ProcessData();
}

