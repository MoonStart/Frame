/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSC.
 AUTHOR   :     June 12, 2003 Steve Thiffault.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                EON.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTOREON_H
#define PM_COLLECTOREON_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>


// Forward class declaration
class FC_OneShotProcess;


//The Class is responsible to collect data used by the 
//Processor for EON. These data are needed once every second. 
//All the data coming from Facility Monitoring are in form of 
//a free running counter. To provide the Processor with this 
//data, the Collector has to memorize the values of the free 
//running counters for the previous second and the current second.
//##ModelId=3FA1611003AE
class PM_CollectorEon: public PM_Collector
{

public:

    //The constructor of collector Data.
	//##ModelId=3FA16111013E
    PM_CollectorEon(PM_GenericApplication& theGenericApplication,
                    FC_OneShotProcess&     theProcessorProcess,
                    uint32                 theNumberOfPort);
    
    //The default destructor of collector Data.
	//##ModelId=3FA161110142
    virtual ~PM_CollectorEon();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
	//##ModelId=3FA16111014D
    void Init();

    //Updates PM defects and PM EON counters contain in the 
    //blackboard. The Collector blackboard regions will 
    //be used by the Processor.
	//##ModelId=3FA16111014E
    virtual void ProcessData();

protected:

    //Pointer to the region that contains EON counters for the current second.
	//##ModelId=3FA285A30193
    TEL_BbRegionBaseImp<PM_BbCountEon>* myCountEon;

};

#endif //PM_COLLECTOREON_H
