/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 2004  Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for Far-End SONET/SDH MS layer..
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORMSFAREND_H
#define PM_COLLECTORMSFAREND_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>


// Forward class declaration
class FC_OneShotProcess;


//The Class is responsible to collect data used by the 
//Processor for Far-End SONET/SDH MS layer. These data
//are needed once every second. All the data coming from 
//Facility Monitoring are in form of a free running counter. 
//To provide the Processor with this data, the Collector has 
//to memorize the values of the free running counters for the 
//previous second and the current second.
class PM_CollectorMsFarEnd: public PM_Collector
{

public:

    //The constructor of collector MsFarEnd.
    PM_CollectorMsFarEnd(PM_GenericApplication& theGenericApplication,
                         FC_OneShotProcess&     theProcessorProcess,
                         uint32                 theNumberOfPort);
    
    //The default destructor of collector MsFarEnd.
    virtual ~PM_CollectorMsFarEnd();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates Far-End defects and counters contained in the 
    //blackboard.  The Collector blackboard 
    //regions will be used by the Processor.
    virtual void ProcessData();

protected:

    //Pointer to the region that contains MS defects status for the current second.
    TEL_BbRegionBaseImp<PM_BbDefectMsFarEnd>* myDefectMsFarEnd;

    //Pointer to the region that contains MS failures status for the current second.
    TEL_BbRegionBaseImp<PM_BbFailureMsFarEnd>* myFailureMsFarEnd;

    //Pointer to the region that contains MS counters for the current second.
    TEL_BbRegionBaseImp<PM_BbCountMsFarEnd>* myCountMsFarEnd;

};

#endif //PM_COLLECTORMSFAREND_H
