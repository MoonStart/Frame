/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 9, 2002.
 DESCRIPTION:   Process that computes the PM Parameters for the Laser.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORLASER
#define PM_PROCESSORLASER

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Laser. These Parameters are derived from the data supplied 
//by the Collector. The Process of Processor Laser is waked 
//up by the Collector every second.
//##ModelId=3C1F9DEA02A9
class PM_ProcessorLaser:    public PM_Processor
{
public:

    //The constructor of Processor Laser.
    //##ModelId=3C1F9DEB0098
    PM_ProcessorLaser(PM_GenericApplication&    theGenericApplication,
                      uint32                    theNumberOfPort);
    
    //The default destructor of Processor Laser.
    //##ModelId=3C1F9DEB00A4
    virtual ~PM_ProcessorLaser();

    //Creates actions and instances used by the Processor Laser.
    //##ModelId=3CBC723400A0
    virtual void CreateActionsInstances();

};

#endif //PM_PROCESSORLASER
