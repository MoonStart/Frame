/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Process that collects the data needed by the PM Processor 
                Oms.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OmsStatus.h>
#include <ExecutionSupport/FC_OneShotProcess.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Monitoring/MON_AppIf.h>

#include <PM/PM_Def.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbStatusOms.h>
#include <PM/PM_CollectorOms.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4CF00013
PM_CollectorOms::PM_CollectorOms (PM_GenericApplication&    theGenericApplication,
                                  FC_OneShotProcess         &theProcessorProcess, 
                                  uint32                    theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_OMS_STRING, theNumberOfPort),
    myStatusOms(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF0003B
PM_CollectorOms::~PM_CollectorOms ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF00045
void PM_CollectorOms::Init()
{
    // Initialize pointers to optical status and defect regions.
    myStatusOms = &(*myGenericApplication.GetRegionStatusOms());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CF0004F
void PM_CollectorOms::ProcessData() 
{
    MON_OmsStatus &statusObject = (MON_OmsStatus &)(*(myGenericApplication.GetMonApplication().GetStatusRegion()))[0];

    // Update Oms gauges statuses.
    (*myStatusOms)[0].Update(statusObject);

    // Call base class method.
    PM_Collector::ProcessData();

}
