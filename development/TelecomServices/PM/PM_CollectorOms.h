/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Oms.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTOROMS
#define PM_COLLECTOROMS

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

// Forward class declaration.
class FC_OneShotProcess;
class PM_GenericApplication;


//The Class is responsible to collect data used by the 
//Processor Oms. These data are needed once 
//every second.
//##ModelId=3E6E4CED020E
class PM_CollectorOms: public PM_Collector
{

public:

    //The default constructor.
    //##ModelId=3E6E4CF00013
    PM_CollectorOms(PM_GenericApplication&  theGenericApplication,
                    FC_OneShotProcess&      theProcessorProcess,
                    uint32                  theNumberOfPort);
    
    //The default destructor.
    //##ModelId=3E6E4CF0003B
    virtual ~PM_CollectorOms();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    //##ModelId=3E6E4CF00045
    void Init();

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    //##ModelId=3E6E4CF0004F
    virtual void ProcessData();

protected:

    //Pointer to the region that contained Oms gauges 
    //values for the current second.
    //##ModelId=3E7222C10396
    TEL_BbRegionBaseImp<PM_BbStatusOms>* myStatusOms;

};

#endif //PM_COLLECTOROMS
