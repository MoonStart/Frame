/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004   Hemant Thakkar
 DESCRIPTION:   Process that computes the PM Parameters of GFP.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORGFP_H
#define PM_PROCESSORGFP_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//GFP layer. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor Gfp 
//is waked up by the Collector every second.
class PM_ProcessorGfp:    public PM_Processor
{
public:

    //The constructor of Processor Gfp.
    PM_ProcessorGfp(PM_GenericApplication& theGenericApplication, 
                    uint16                 theNumberOfPort);
    
    //The default destructor of Processor Gfp.
    virtual ~PM_ProcessorGfp();

    //Creates actions and instances used by the Processor Gfp.
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSORGFP_H
