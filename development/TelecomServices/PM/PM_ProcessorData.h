/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Process that computes the PM Parameters Data.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORDATA_H
#define PM_PROCESSORDATA_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Data. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Data 
//is waked up by the Collector every second.
//##ModelId=3C1F9DED014F
class PM_ProcessorData:    public PM_Processor
{
public:

    //The constructor of Processor Data.
    //##ModelId=3C1F9DED0308
    PM_ProcessorData(PM_GenericApplication& theGenericApplication, 
                     uint16                 theNumberOfPort);
    
    //The default destructor of Processor Data.
    //##ModelId=3C1F9DED0313
    virtual ~PM_ProcessorData();

    //Creates actions and instances used by the Processor Data.
    //##ModelId=3CBC723803B3
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSORDATA_H
