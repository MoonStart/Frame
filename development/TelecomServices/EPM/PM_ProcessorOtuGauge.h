/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     December 21, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that computes the PM Parameters for OTU gauges.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSOROTUGAUGE_H
#define PM_PROCESSOROTUGAUGE_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Data. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Data 
//is waked up by the Collector every second.
class PM_ProcessorOtuGauge:    public PM_Processor
{
public:

    //The constructor of OTU Gauge Processor.
    PM_ProcessorOtuGauge(PM_GenericApplication& theGenericApplication,
						  uint16 theNumberOfPort);
    
    //The default destructor of OTU Gauge Processor.
    virtual ~PM_ProcessorOtuGauge();

    //Creates actions and instances used by the OTU Gauge Processor.
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSOROTUGAUGE_H
