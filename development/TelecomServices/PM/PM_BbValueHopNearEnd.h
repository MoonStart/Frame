/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     13 February 2004  Hemant Thakkar
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Near-End SONET/SDH HOP layer..
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEHOPNEAREND_H
#define PM_BBVALUEHOPNEAREND_H

#include <PM/PM_TypeHopNearEnd.h>
#include "PM_BbCounterValue.h"
#include <ErrorService/FC_Error.h>


//Keeps the parameter values of the Near-End SONET/SDH HOP layer. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
class PM_BbValueHopNearEnd : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueHopNearEnd(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueHopNearEnd();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEHOPNEAREND_H
