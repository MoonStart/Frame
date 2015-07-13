/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   Process that computes the PM Parameters EON.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSOREON_H
#define PM_PROCESSOREON_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//EON. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor EON 
//is waked up by the Collector every second.
//##ModelId=3FA1610902D7
class PM_ProcessorEon:    public PM_Processor
{
public:

    //The constructor of Processor EON.
	//##ModelId=3FA1610A0047
    PM_ProcessorEon(PM_GenericApplication& theGenericApplication, 
                    uint16                 theNumberOfPort);
    
    //The default destructor of Processor EON.
	//##ModelId=3FA1610A0058
    virtual ~PM_ProcessorEon();

    //Creates actions and instances used by the Processor Data.
	//##ModelId=3FA1610A005A
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSOREON_H
