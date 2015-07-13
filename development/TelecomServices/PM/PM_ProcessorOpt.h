/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, December 4, 2001.
 DESCRIPTION:   Process that computes the PM Parameters Optical.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSOROPT
#define PM_PROCESSOROPT

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes 
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Optical. These Parameters are derived from the data 
//supplied by the Collector. The Process of Processor Optical
//is waked up by the Collector every second.
//##ModelId=3C1F9DEC0035
class PM_ProcessorOpt:    public PM_Processor
{
public:

    //The constructor of Processor Optical.
    //##ModelId=3C1F9DEC01EE
    PM_ProcessorOpt(PM_GenericApplication&  theGenericApplication,
                    uint32                  theNumberOfPort);
    
    //The default destructor of Processor Optical.
    //##ModelId=3C1F9DEC01F8
    virtual ~PM_ProcessorOpt();

    //Creates actions and instances used by the Processor 
    //Optical.
    //##ModelId=3CBC723603CE
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSOROPT
