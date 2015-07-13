/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders and OSCs.
 AUTHOR   :     February 10, 1999 Marc-Andre Ledoux.
 DESCRIPTION:   Process that collects the data needed by the PM Processor
                Data (RS, FICON, ESCON, GbE, GOPT).
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTORDATA_H
#define PM_COLLECTORDATA_H

#include <PM/src/PM_Collector.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>


// Forward class declaration
class FC_OneShotProcess;


//The Class is responsible to collect data used by the 
//Processor for Data (RS, FICON, ESCON, GbE, GOPT). These data
//are needed once every second. All the data coming from 
//Facility Monitoring are in form of a free running counter. 
//To provide the Processor with this data, the Collector has 
//to memorize the values of the free running counters for the 
//previous second and the current second.
//##ModelId=3C1F8A54014E
class PM_CollectorData: public PM_Collector
{

public:

    //The constructor of collector Data.
    //##ModelId=3C1F8A5402FA
    PM_CollectorData(PM_GenericApplication& theGenericApplication,
                     FC_OneShotProcess&     theProcessorProcess,
                     uint32                 theNumberOfPort,
                     bool                   theObtainDataFromOpticalLayer = false,
                     CT_PM_Side             theSide = CT_PM_UNKNOWN_SIDE);
    
    //The default destructor of collector Data.
    //##ModelId=3C1F8A54030E
    virtual ~PM_CollectorData();

    //This method initializes pointers of used regions. It 
    //must be called before the execution of the Collector.
    //##ModelId=3C1F8A540310
    void Init();

    //Updates PM defects and PM BIP counters contain in the 
    //blackboard. The data is derived from the Facility 
    //Monitoring for BIP counters. The Collector blackboard 
    //regions will be used by the Processor.
    //##ModelId=3C1F8A540318
    virtual void ProcessData();

protected:

    //Pointer to the region that contains Data defects status for the current second.
    //##ModelId=3C977FAE00A6
    TEL_BbRegionBaseImp<PM_BbDefectData>* myDefectData;

    //Pointer to the region that contains Data counters for the current second.
    //##ModelId=3C977FAE0164
    TEL_BbRegionBaseImp<PM_BbCountData>* myCountData;

    // Certain Data layer PM retrieves LOS data from optical layer
    // This flag declares whether this collector belongs to one of these apps.
    bool myObtainDataFromOpticalLayer;

    //Interface on which this collector operates.
    CT_PM_Side myPmSide;
};

#endif //PM_COLLECTORDATA_H
