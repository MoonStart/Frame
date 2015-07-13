/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 19, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Rmon Counter.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <Monitoring/MON_RmonCounters.h>
#include <Monitoring/MON_AppIf.h>

#include <EPM/PM_BbCountRmon.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_Def.h>
#include <EPM/PM_CollectorRmonCounter.h>

//------------------------
// Class PM_CollectorRmonCounter
//------------------------

//-----------------------------------------------------------------
PM_CollectorRmonCounter::PM_CollectorRmonCounter (PM_GenericApplication&  theGenericApplication,
                                FC_OneShotProcess           &theProcessorProcess,
                                uint32                      theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_RMON_STRING, theNumberOfPort),
    myCountRmon(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_CollectorRmonCounter::~PM_CollectorRmonCounter ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_CollectorRmonCounter::Init()
{
    // Initialize pointers to RMON counter regions.
    myCountRmon = &(*myGenericApplication.GetRegionCountRmon());

    // Call base class method.
    PM_Collector::Init();
}

void PM_CollectorRmonCounter::ProcessData()
{   

	MON_RmonCounters &countersObject = (MON_RmonCounters &)(*(myGenericApplication.GetMonApplication().GetCountersRegion()))[0];

	// Update RMON error counters 
	(*myCountRmon)[0].Update(countersObject);

    // Call base class method.
    PM_Collector::ProcessData();
}


