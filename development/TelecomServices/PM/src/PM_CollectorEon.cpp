/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSC.
 AUTHOR   :     June 12, 2003 Steve Thiffault.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                EON.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_OneShotProcess.h>
#include <TsPii/TSPII_SubApplication.h>
#include <TsPii/TSPII_IPCountersIf.h>

#include <PM/PM_BbCountEon.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_Def.h>
#include <PM/PM_CollectorEon.h>


//-----------------------------------------------------------------
//##ModelId=3FA16111013E
PM_CollectorEon::PM_CollectorEon (PM_GenericApplication&  theGenericApplication,
                                  FC_OneShotProcess       &theProcessorProcess,
                                  uint32                  theNumberOfPort) :
    PM_Collector(theGenericApplication, theProcessorProcess, PM_EON_STRING, theNumberOfPort),
    myCountEon(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA161110142
PM_CollectorEon::~PM_CollectorEon ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA16111014D
void PM_CollectorEon::Init()
{
    // Initialize pointers to EON count regions.
    myCountEon = &(*myGenericApplication.GetRegionCountEon());

    PM_Collector::Init();

}

//-----------------------------------------------------------------
//##ModelId=3FA16111014E
void PM_CollectorEon::ProcessData() 
{
    TSPII_IPCountersIf &countersObject = (TSPII_IPCountersIf &)(*(TSPII_SubApplication::GetInstance()->GetIPCounters()))[0];


    // Update ICMP and IP error counters.
    (*myCountEon)[0].Update(countersObject);

    // Call base class method.
    PM_Collector::ProcessData();

}
