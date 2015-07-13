/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 19, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Rmon.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORRMONCOUNTER_H
#define PM_COLLECTORRMONCOUNTER_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <EPM/PM_BbCountRmon.h>

// Forward class declaration
class FC_OneShotProcess;

using namespace std;

//The Class is responsible to collect data used by the 
//Processor for Rmon Ethernet count statistics. These data
//are needed once every second. All the data coming from 
//Facility Monitoring are in form of a free running counter. 
//To provide the Processor with this data, the Collector has 
//to memorize the values of the free running counters for the 
//previous second and the current second.
class PM_CollectorRmonCounter: public PM_Collector
{

public:

    //The constructor of collector Data.
    PM_CollectorRmonCounter(PM_GenericApplication& theGenericApplication,
                     FC_OneShotProcess&     theProcessorProcess,
                     uint32                 theNumberOfPort);
    
    //The default destructor of collector Data.
    virtual ~PM_CollectorRmonCounter();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM defects and PM counters contained in the 
    //blackboard. The data is derived from the Facility 
    //Monitoring for Ethernet statistics. The Collector blackboard 
    //regions will be used by the Processor.
    virtual void ProcessData();

protected:

    //Pointer to the region that contains Rmon counters for the current second.
    TEL_BbRegionBaseImp<PM_BbCountRmon>* myCountRmon;
};

#endif //PM_COLLECTORRMONCOUNTER_H
