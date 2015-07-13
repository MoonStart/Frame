/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     Steve Thiffault, December 4, 2001.
 DESCRIPTION:   Process that collects the data needed by the PM Processor 
                Optical Transport Unit or FEC.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTOROTU
#define PM_COLLECTOROTU

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

// Forward class declaration
class FC_OneShotProcess;
class PM_GenericApplication;


//The Class is responsible to collect data used by the 
//Processor of OTU. These data are needed once every 
//second.
//##ModelId=3C1F6F7D00C9
class PM_CollectorOtu: public PM_Collector
{

public:

    //The default constructor.
    //##ModelId=3C1F6F7D0319
    PM_CollectorOtu(PM_GenericApplication&  theGenericApplication,
                    FC_OneShotProcess&      theProcessorProcess,
                    uint32                  theNumberOfPort,
                    CT_PM_Side              theSide);
    
    //The default destructor.
    //##ModelId=3C1F6F7D032C
    virtual ~PM_CollectorOtu();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    //##ModelId=3C1F6F7D032E
    void Init();

    //Updates PM counts contained in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
    //##ModelId=3C1F6F7D0336
    virtual void ProcessData();

protected:

    //Pointer to the region that contains OTU defects status for the current second.
	//##ModelId=3E7222CC01E4
    TEL_BbRegionBaseImp<PM_BbDefectOtu>* myDefectOtu;

    //Pointer to the region that contained OTU counts values 
    //for the current second.
	//##ModelId=3C9255C502CE
    TEL_BbRegionBaseImp<PM_BbCountOtu>* myCountOtu;

    //Pointer to the region that contains OCH protection status for the current second.
    TEL_BbRegionBaseImp<PM_BbStatusOtu>* myStatusOtu;

    //Interface on which this collector operates.
    CT_PM_Side myOtuSide;
};

#endif //PM_COLLECTOROTU
