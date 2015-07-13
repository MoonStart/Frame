/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   Process that computes the PM Parameters of Far-End SONET/SDH
                Multiplex Section.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORMSFAREND_H
#define PM_PROCESSORMSFAREND_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Far-End SONET/SDH MS layer. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor MsFarEnd 
//is waked up by the Collector every second.
class PM_ProcessorMsFarEnd:    public PM_Processor
{
public:

    //The constructor of Processor MsFarEnd.
    PM_ProcessorMsFarEnd(PM_GenericApplication& theGenericApplication, 
                          uint16                 theNumberOfPort);
    
    //The default destructor of Processor MsFarEnd.
    virtual ~PM_ProcessorMsFarEnd();

    //Creates actions and instances used by the Processor MsFarEnd.
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSORMSFAREND_H
