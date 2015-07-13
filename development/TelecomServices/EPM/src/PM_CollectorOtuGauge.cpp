/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 19, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Otu Counter.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OptStatus.h>
#include <Monitoring/MON_MacStatus.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_AppIf.h>

#include <EPM/PM_BbStatusOtuGauge.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_Processor.h>
#include <PM/PM_OtuGaugeSubApplication.h>
#include <PM/PM_Def.h>
#include <EPM/PM_CollectorOtuGauge.h>

//------------------------
// Class PM_CollectorOtuGauge
//------------------------

//-----------------------------------------------------------------
PM_CollectorOtuGauge::PM_CollectorOtuGauge( PM_GenericApplication&    theGenericApplication,
                                            FC_OneShotProcess&        theProcessorProcess,
                                            uint32                    theNumberOfPort ) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_OTU_STRING, theNumberOfPort),
    myStatusOtuGauge(NULL)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_CollectorOtuGauge::~PM_CollectorOtuGauge()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorOtuGauge::Init()
{
    // Initialize pointer to optical status region.
    myStatusOtuGauge = &(*myGenericApplication.GetRegionStatusOtuGauge());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
void PM_CollectorOtuGauge::ProcessData() 
{   
    // If MON OTU application is available on the module, 
    // Update OTU status for pre-FEC value.
    MON_AppIf*  monOtuApp = myGenericApplication.GetMonApplicationPtr(CT_PM_OTU_MON_APPLICATION);

    if (monOtuApp) 
    {
        MON_OtuStatus &statusObject = (MON_OtuStatus &)(*(monOtuApp->GetStatusRegion()))[0];
        (*myStatusOtuGauge)[0].Update(statusObject);
    }

    // Call base class method.
    PM_Collector::ProcessData();
}

