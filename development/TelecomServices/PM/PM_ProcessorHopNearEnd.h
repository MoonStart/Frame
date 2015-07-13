/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   Process that computes the PM Parameters of Near-End SONET/SDH
                HOP.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSORHOPNEAREND_H
#define PM_PROCESSORHOPNEAREND_H

#include <PM/src/PM_Processor.h>


using namespace std;

// Forward declaration of classes.
class PM_GenericApplication;

//This class is responsible to compute the Parameter of 
//Near-End SONET/SDH HOP layer. These Parameters are derived from the data
//supplied by the Collector. The Process of Processor HopNearEnd 
//is waked up by the Collector every second.
class PM_ProcessorHopNearEnd:    public PM_Processor
{
public:

    //The constructor of Processor HopNearEnd.
    PM_ProcessorHopNearEnd(PM_GenericApplication& theGenericApplication, 
                          uint16                 theNumberOfPort,
                          CT_PM_Sts_Offset		 theSts1Offset);
    
    //The default destructor of Processor HopNearEnd.
    virtual ~PM_ProcessorHopNearEnd();

    //Creates actions and instances used by the Processor HopNearEnd.
    virtual void CreateActionsInstances();

	// Overridden version of the run method.
	virtual void Run(FC_Object* theObject = NULL);

private:

	// Offset of the starting STS-1 into the set of STS-1s contained
	// in the OC-192.
	CT_PM_Sts_Offset mySts1Offset;
};

#endif //PM_PROCESSORHOPNEAREND_H
