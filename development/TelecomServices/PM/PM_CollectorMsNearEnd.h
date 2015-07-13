/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     February 9, 2004  Hemant Thakkar
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                for Near-End SONET/SDH MS layer..
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORMSNEAREND_H
#define PM_COLLECTORMSNEAREND_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>


// Forward class declaration
class FC_OneShotProcess;


//The Class is responsible to collect data used by the 
//Processor for Near-End SONET/SDH MS layer. These data
//are needed once every second. All the data coming from 
//Facility Monitoring are in form of a free running counter. 
//To provide the Processor with this data, the Collector has 
//to memorize the values of the free running counters for the 
//previous second and the current second.
class PM_CollectorMsNearEnd: public PM_Collector
{

public:

    //The constructor of collector MsNearEnd.
    PM_CollectorMsNearEnd(PM_GenericApplication& theGenericApplication,
                          FC_OneShotProcess&     theProcessorProcess,
                          uint32                 theNumberOfPort,
                          CT_PM_Side             theSide);
    
    //The default destructor of collector MsNearEnd.
    virtual ~PM_CollectorMsNearEnd();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    void Init();

    //Updates PM defects and PM BIP counters contain in the 
    //blackboard. The data is derived from the Facility 
    //Monitoring for BIP counters. The Collector blackboard 
    //regions will be used by the Processor.
    virtual void ProcessData();

protected:

    //Pointer to the region that contains MS defects status for the current second.
    TEL_BbRegionBaseImp<PM_BbDefectMsNearEnd>* myDefectMsNearEnd;

    //Pointer to the region that contains MS counters for the current second.
    TEL_BbRegionBaseImp<PM_BbCountMsNearEnd>* myCountMsNearEnd;

    //Pointer to the region that contains MS failures for the current second.
    TEL_BbRegionBaseImp<PM_BbFailureMsNearEnd>* myFailureMsNearEnd;

    //Pointer to the region that contains MS status for the current second.
    TEL_BbRegionBaseImp<PM_BbStatusMsNearEnd>* myStatusMsNearEnd;

    //Interface on which this collector operates.
    CT_PM_Side myMsNearEndSide;
};

#endif //PM_COLLECTORMSNEAREND_H
