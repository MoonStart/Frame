/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 4, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor 
                Optical Channel.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORCOP
#define PM_COLLECTORCOP

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

// Forward class declaration
class FC_OneShotProcess;
class PM_GenericApplication;


//The Class is responsible to collect data used by the 
//Processor Optical Channel. These data are needed once every 
//second.
//##ModelId=3C1F8E7B0020
class PM_CollectorCop: public PM_Collector
{

public:

    //The default constructor.
    //##ModelId=3C1F8E7B01CC
    PM_CollectorCop(PM_GenericApplication&  theGenericApplication,
                    FC_OneShotProcess&      theProcessorProcess,
                    uint32                  theNumberOfPort,
                    bool                    theObtainDataFromOpticalLayer = false,
                    bool                    theObtainAltPower = false);
    
    //The default destructor.
    //##ModelId=3C1F8E7B01E0
    virtual ~PM_CollectorCop();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    //##ModelId=3C1F8E7B01E2
    void Init();

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    //##ModelId=3C1F8E7B01EA
    virtual void ProcessData();

protected:

    //Pointer to the region that contained Optical Channel gauges values 
    //for the current second.
	//##ModelId=3C9781660365
    TEL_BbRegionBaseImp<PM_BbStatusCop>* myStatusCop;

    //Pointer to the region that contained Optical Channel defects
    //for the current second.
	//##ModelId=3E7222C40048
    TEL_BbRegionBaseImp<PM_BbDefectCop>* myDefectCop;

    bool myObtainDataFromOpticalLayer;
    bool myObtainAltPower;

};

#endif //PM_COLLECTORCOP
