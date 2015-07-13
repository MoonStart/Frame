/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for TCM layer.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORTCM_H
#define PM_COLLECTORTCM_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <PM/src/PM_CommandUpdateAction.h>


// Forward class declaration
class FC_OneShotProcess;


//The Class is responsible to collect data used by the 
//Processor for the TCM layer. This data
//is needed once every second. All the data coming from 
//Facility Monitoring are in form of a free running counter. 
//To provide the Processor with this data, the Collector has 
//to memorize the values of the free running counters for the 
//previous second and the current second.
class PM_CollectorTcm: public PM_Collector
{

public:

    //The constructor of collector ODU.
    PM_CollectorTcm(PM_GenericApplication& theGenericApplication,
                    FC_OneShotProcess&     theProcessorProcess,
                    uint32                 theNumberOfPort);
    
    //The default destructor of collector ODU.
    virtual ~PM_CollectorTcm();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM defects and PM BIP counters contain in the 
    //blackboard. The data is derived from the Facility 
    //Monitoring for BIP counters. The Collector blackboard 
    //regions will be used by the Processor.
    virtual void ProcessData();

protected:

    //Pointer to the region that contains ODU defects status for the current second.
    TEL_BbRegionBaseImp<PM_BbDefectTcm>* myDefectTcm;

    //Pointer to the region that contains ODU counters for the current second.
    TEL_BbRegionBaseImp<PM_BbCountTcm>* myCountTcm;

};

#endif //PM_COLLECTORTCM_H
