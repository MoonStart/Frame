/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   Process that computes the PM Parameters of Near-End SONET/SDH
                MS.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSOROPTCOUNTER_H
#define PM_PROCESSOROPTCOUNTER_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Near-End SONET/SDH MS layer. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Opt 
//is waked up by the Collector every second.
class PM_ProcessorOptCounter:    public PM_Processor
{
public:

    //The constructor of Processor Opt.
    PM_ProcessorOptCounter(PM_GenericApplication& theGenericApplication, 
                           uint16                 theNumberOfPort);
    
    //The default destructor of Processor Opt.
    virtual ~PM_ProcessorOptCounter();

    //Creates actions and instances used by the Processor Opt.
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSOROPTCOUNTER_H
