/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Process that computes the PM Parameters for Tcm gauges.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORTcmGAUGE_H
#define PM_PROCESSORTcmGAUGE_H

#include <PM/src/PM_Processor.h>

using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Data. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Data 
//is waked up by the Collector every second.
class PM_ProcessorTcmGauge: public PM_Processor
{
public:

    //The constructor of OTU Gauge Processor.
    PM_ProcessorTcmGauge(PM_GenericApplication& theGenericApplication,
                         uint16 theNumberOfPort);
    
    //The default destructor of Tcm Gauge Processor.
    virtual ~PM_ProcessorTcmGauge();

    //Creates actions and instances used by the Tcm Gauge Processor.
    virtual void CreateActionsInstances();

    virtual void Run(FC_Object* theObject = NULL);

    //Initializes the Processor.
    virtual void Init();

    //Initializes the Processor for a particular "port" number.
    virtual void Init( uint16 thePortNumber );

    // Method to retieve flag indicating that at least one dynamically
    // allocated object was encountered by the processor.
    bool AreObjectsAllocated();

private:
 
    bool myObjectsAllocated;
};
 
inline
bool PM_ProcessorTcmGauge::AreObjectsAllocated()
{
    return myObjectsAllocated;
}

#endif //PM_PROCESSORTcmGAUGE_H

