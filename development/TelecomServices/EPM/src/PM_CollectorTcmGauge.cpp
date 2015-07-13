/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Process that collects the data needed by the PM Processor Tcm Counter.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_TcmCounters.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_MacStatus.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_AppIf.h>

#include <EPM/PM_BbStatusTcmGauge.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_Processor.h>
#include <PM/PM_TcmGaugeSubApplication.h>
#include <PM/PM_Def.h>
#include <EPM/PM_CollectorTcmGauge.h>
#include <EPM/src/PM_AutoRateLock.h>

//------------------------
// Class PM_CollectorTcmGauge
//------------------------

//-----------------------------------------------------------------
PM_CollectorTcmGauge::PM_CollectorTcmGauge( PM_GenericApplication& theGenericApplication,
                                            FC_OneShotProcess&   theProcessorProcess,
                                            uint32               theNumberOfPort ) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_TCM_STRING, theNumberOfPort),
    myStatusTcmGauge(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_CollectorTcmGauge::~PM_CollectorTcmGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorTcmGauge::Init()
{
    // Initialize pointers to optical status and defect regions.
    myStatusTcmGauge = &(*myGenericApplication.GetRegionStatusTcmGauge());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorTcmGauge::ProcessData() 
{
    MON_AppIf* monTcmApp = myGenericApplication.GetMonApplicationPtr(0);
    if ( monTcmApp ) 
    {
        for (uint8 anIndex = 0; anIndex < myNumberOfPort; anIndex++)
        {
            MON_TcmStatus &statusObject = (MON_TcmStatus &)(*(monTcmApp->GetStatusRegion()))[anIndex];
            (*myStatusTcmGauge)[anIndex].Update(statusObject);
        }
    }

    // Call base class method.
    PM_Collector::ProcessData();
}

