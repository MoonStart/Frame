/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     December 21, 2005, Larry Wolfrum.
 DESCRIPTION:   Process that computes the PM Parameters for RMON gauges.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORRMONCOUNTER_H
#define PM_PROCESSORRMONCOUNTER_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Data. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Data 
//is waked up by the Collector every second.
class PM_ProcessorRmonCounter:    public PM_Processor
{
public:

    //The constructor of Processor Data.
    PM_ProcessorRmonCounter(PM_GenericApplication& theGenericApplication, 
                     uint16                 theNumberOfPort);
    
    //The default destructor of Processor Data.
    virtual ~PM_ProcessorRmonCounter();

    //Creates actions and instances used by the Processor Data.
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSORRMONCOUNTER_H
