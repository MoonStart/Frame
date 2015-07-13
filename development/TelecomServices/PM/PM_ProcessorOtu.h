/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     Sebastien Cossette, January 28, 2002.
 DESCRIPTION:   Process that computes the PM Parameters for OTU.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSOROTU
#define PM_PROCESSOROTU

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Optical Transport Unit. These Parameters are derived from 
//the data supplied by the Collector. The Process of 
//Processor OTU is waked up by the Collector every second.
//##ModelId=3C9255A90100
class PM_ProcessorOtu:    public PM_Processor
{
public:

    //The constructor of Processor OTU.
    //##ModelId=3C9255A90359
    PM_ProcessorOtu(PM_GenericApplication&  theGenericApplication,
                    uint32                  theNumberOfPort);
    
    //The default destructor of Processor OTU.
    //##ModelId=3C9255A90377
    virtual ~PM_ProcessorOtu();

    //Creates actions and instances used by the Processor OTU.
    //##ModelId=3CBC72330081
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSOROTU
