/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   Process that computes the PM Parameters Optical Channel.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORCOP
#define PM_PROCESSORCOP

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Optical Channel. These Parameters are derived from the data 
//supplied by the Collector. The Process of Processor COP is 
//waked up by the Collector every second.
//##ModelId=3C501624013A
class PM_ProcessorCop:    public PM_Processor
{
public:

    //Class default constructor.
    //##ModelId=3C50162402F1
    PM_ProcessorCop(PM_GenericApplication&  theGenericApplication,
                    uint32                  theNumberOfPort,
                    CT_CardFamily           theCardFamily,
                    CT_PM_Side              theSide);

    //Class default destructor.
    //##ModelId=3C5016240304
    virtual ~PM_ProcessorCop();

    //Creates action and instances used by the Processor COP.
    //##ModelId=3CBC72350304
    virtual void CreateActionsInstances();

    // Over-ridden version of Run() method to check directionless
    // state of RCMM, if necessary.
    virtual void Run(FC_Object* theObject = NULL);

private:

    // Card family associated with the processor context.
	//##ModelId=3FA1610D0304
    CT_CardFamily myCardFamily;

    // My side.
    CT_PM_Side mySide;

};

#endif //PM_PROCESSORCOP
