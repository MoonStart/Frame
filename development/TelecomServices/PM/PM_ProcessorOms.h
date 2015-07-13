/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   Process that computes the PM Parameters Oms.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSOROMS
#define PM_PROCESSOROMS

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes 
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Oms. These Parameters are derived from the data 
//supplied by the Collector. The Process of Processor Oms
//is waked up by the Collector every second.
//##ModelId=3E6E4C9601A4
class PM_ProcessorOms:    public PM_Processor
{
public:

    //The constructor of Processor Oms.
	//##ModelId=3E6E4C9703AF
    PM_ProcessorOms(PM_GenericApplication&  theGenericApplication,
                    uint32                  theNumberOfPort);
    
    //The default destructor of Processor Oms.
	//##ModelId=3E6E4C9703BA
    virtual ~PM_ProcessorOms();

    //Creates actions and instances used by the Processor 
    //Oms.
	//##ModelId=3E6E4C9703C3
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSOROMS
