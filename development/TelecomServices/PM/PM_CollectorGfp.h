/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     February 9, 2004  Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for GFP layer..
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORGFP_H
#define PM_COLLECTORGFP_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>


// Forward class declaration
class FC_OneShotProcess;


//The Class is responsible to collect data used by the 
//Processor for GFP layer. These data
//are needed once every second. All the data coming from 
//Facility Monitoring are in form of a free running counter. 
//To provide the Processor with this data, the Collector has 
//to memorize the values of the free running counters for the 
//previous second and the current second.
class PM_CollectorGfp: public PM_Collector
{

public:

    //The constructor of collector Gfp.
    PM_CollectorGfp(PM_GenericApplication& theGenericApplication,
                    FC_OneShotProcess&     theProcessorProcess,
                    uint32                 theNumberOfPort);
    
    //The default destructor of collector Gfp.
    virtual ~PM_CollectorGfp();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM 10B_ERR counters contain in the 
    //blackboard. The data is derived from the Facility 
    //Monitoring for 10B_ERR counters. The Collector blackboard 
    //regions will be used by the Processor.
    virtual void ProcessData();

protected:
    //Pointer to the region that contains GFP defects status for the current second.
    TEL_BbRegionBaseImp<PM_BbDefectGfp>* myDefectGfp;

    //Pointer to the region that contains MS counters for the current second.
    TEL_BbRegionBaseImp<PM_BbCountGfp>* myCountGfp;

};

#endif //PM_COLLECTORGFP_H
