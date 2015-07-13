/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     13 February 2004  Hemant Thakkar
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Far-End SONET/SDH MS layer..
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEMSFAREND_H
#define PM_BBVALUEMSFAREND_H

#include <PM/PM_TypeMsFarEnd.h>
#include "PM_BbCounterValue.h"
#include <ErrorService/FC_Error.h>


//Keeps the parameter values of the Far-End SONET/SDH MS layer. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
class PM_BbValueMsFarEnd : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;
    friend class PM_BbValueSMTM;

    //Class default constructor.
    PM_BbValueMsFarEnd(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueMsFarEnd();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEMSFAREND_H
