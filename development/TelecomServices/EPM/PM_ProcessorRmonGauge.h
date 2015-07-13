/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     December 21, 2005 Larry Wolfrum.
 DESCRIPTION:   Process that computes the PM Parameters for RMON gauges.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORRMONGAUGE_H
#define PM_PROCESSORRMONGAUGE_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Data. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Data 
//is waked up by the Collector every second.
class PM_ProcessorRmonGauge:    public PM_Processor
{
public:

    //The constructor of RMON Gauge Processor.
    PM_ProcessorRmonGauge(PM_GenericApplication& theGenericApplication,
						  uint16 theNumberOfPort);
    
    //The default destructor of RMON Gauge Processor.
    virtual ~PM_ProcessorRmonGauge();

    //Creates actions and instances used by the RMON Gauge Processor.
    virtual void CreateActionsInstances();

    //This method is responsible for detecting a system time 
    //change and prints an error message if "warning" is on. 
    //It is also responsible of the change of period and 
    //adjusts the current/previous regions via the 
    //ControlPeriod object for all accumulation period 
    //supported. Note that, this method must be called at the 
    //end of the Run of the derived Processor class.
    virtual void Run(FC_Object* theObject = NULL);
};

#endif //PM_PROCESSORRMONGAUGE_H
