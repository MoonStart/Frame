/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Laser.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORLASER
#define PM_COLLECTORLASER

#include <PM/src/PM_Collector.h>


// Forward class declaration
class FC_OneShotProcess;
class PM_GenericApplication;
template <class T> class TEL_BbRegionBaseImp;


//The Class is responsible to collect data used by the 
//Processor for Laser. These data are needed once every 
//second.
//##ModelId=3C50173301B9
class PM_CollectorLaser: public PM_Collector
{

public:

    //The default constructor.
    //##ModelId=3C50178201C7
    PM_CollectorLaser(PM_GenericApplication& theGenericApplication,
                      FC_OneShotProcess&     theProcessorProcess,
                      uint32                 theNumberOfPort);

    //The default destructor.
    //##ModelId=3C50178201D2
    virtual ~PM_CollectorLaser();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    //##ModelId=3C50178201DC
    void Init();

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    //##ModelId=3C50178201E5
    virtual void ProcessData();

protected:

    //Pointer to the region that contained Laser gauges values 
    //for the current second.
	//##ModelId=3C501782020E
    TEL_BbRegionBaseImp<PM_BbStatusLaser>* myStatusLaser;

};

#endif //PM_COLLECTORLASER
