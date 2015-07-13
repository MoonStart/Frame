/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, December 4, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Optical.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTOROPT
#define PM_COLLECTOROPT

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

// Forward class declaration.
class FC_OneShotProcess;
class PM_GenericApplication;


//The Class is responsible to collect data used by the 
//Processor Optical. These data are needed once 
//every second.
//##ModelId=3C1F8D6300E7
class PM_CollectorOpt: public PM_Collector
{

public:

    //The default constructor.
    //##ModelId=3C1F8D630291
    PM_CollectorOpt(PM_GenericApplication&  theGenericApplication,
                    FC_OneShotProcess&      theProcessorProcess,
                    uint32                  theNumberOfPort);
    
    //The default destructor.
    //##ModelId=3C1F8D63029C
    virtual ~PM_CollectorOpt();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    //##ModelId=3C1F8D6302A5
    void Init();

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    //##ModelId=3C1F8D6302C4
    virtual void ProcessData();

protected:

    //Pointer to the region that contained Optical gauges 
    //values for the current second.
	//##ModelId=3C20AB6C02EE
    TEL_BbRegionBaseImp<PM_BbStatusOpt>* myStatusOpt;

};

#endif //PM_COLLECTOROPT
