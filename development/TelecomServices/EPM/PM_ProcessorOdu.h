/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     22 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Process that computes the PM Parameters ODU layer.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORODU_H
#define PM_PROCESSORODU_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//ODU layer. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor ODU 
//is woken up by the Collector every second.
class PM_ProcessorOdu:    public PM_Processor
{
public:

    //The constructor of Processor ODU.
    PM_ProcessorOdu(PM_GenericApplication& theGenericApplication, 
                    uint16                 theNumberOfPort);
    
    //The default destructor of Processor ODU.
    virtual ~PM_ProcessorOdu();

    //Creates actions and instances used by the Processor ODU.
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSORODU_H
