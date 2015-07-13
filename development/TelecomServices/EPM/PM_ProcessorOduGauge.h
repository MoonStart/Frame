/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Process that computes the PM Parameters for ODU gauges.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORODUGAUGE_H
#define PM_PROCESSORODUGAUGE_H

#include <PM/src/PM_Processor.h>

using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Data. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Data 
//is waked up by the Collector every second.
class PM_ProcessorOduGauge: public PM_Processor
{
public:

    //The constructor of OTU Gauge Processor.
    PM_ProcessorOduGauge(PM_GenericApplication& theGenericApplication,
                         uint16 theNumberOfPort);
    
    //The default destructor of ODU Gauge Processor.
    virtual ~PM_ProcessorOduGauge();

    //Creates actions and instances used by the ODU Gauge Processor.
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSORODUGAUGE_H

