/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     December 19, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Otu.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTOROTUGAUGE_H
#define PM_COLLECTOROTUGAUGE_H

#include <vector>
#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <CommonTypes/CT_Telecom.h>
#include <EPM/PM_BbStatusOtuGauge.h>
#include <Configuration/CFG_Rs.h>


// Forward class declaration
class FC_OneShotProcess;

using namespace std;

//The Class is responsible to collect data used by the 
//Processor Otu Gauge. These data are needed once 
//every second.
class PM_CollectorOtuGauge: public PM_Collector
{

public:

    //The default constructor.
    PM_CollectorOtuGauge(PM_GenericApplication&  theGenericApplication,
						  FC_OneShotProcess&     theProcessorProcess,
						  uint32 theNumberOfPort);
    
    //The default destructor.
    virtual ~PM_CollectorOtuGauge();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    virtual void ProcessData();

protected:

    //Pointer to the region that contained Otu gauge 
    //values for the current second.
    TEL_BbRegionBaseImp<PM_BbStatusOtuGauge>* myStatusOtuGauge;

};

#endif //PM_COLLECTOROTU_H
