/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORODUGAUGE_H
#define PM_COLLECTORODUGAUGE_H

#include <vector>
#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_Telecom.h>
#include <EPM/PM_BbStatusOduGauge.h>

// Forward class declaration
class FC_OneShotProcess;

using namespace std;

//The Class is responsible to collect data used by the 
//Processor Odu Gauge. These data are needed once 
//every second.
class PM_CollectorOduGauge: public PM_Collector
{

public:

    //The default constructor.
    PM_CollectorOduGauge(PM_GenericApplication&  theGenericApplication,
						  FC_OneShotProcess&     theProcessorProcess,
						  uint32 theNumberOfPort);
    
    //The default destructor.
    virtual ~PM_CollectorOduGauge();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    virtual void ProcessData();

protected:

    //Pointer to the region that contained Odu gauge 
    //values for the current second.
    TEL_BbRegionBaseImp<PM_BbStatusOduGauge>* myStatusOduGauge;

};

#endif //PM_COLLECTORODU_H
