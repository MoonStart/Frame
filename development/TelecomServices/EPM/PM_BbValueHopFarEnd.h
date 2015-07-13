/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     27 February 2006  Larry Wolfrum
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Far-End SONET/SDH HOP layer..
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEHOPFAREND_H
#define PM_BBVALUEHOPFAREND_H

#include <EPM/PM_TypeHopFarEnd.h>
#include <PM/PM_BbCounterValue.h>
#include <ErrorService/FC_Error.h>


//Keeps the parameter values of the Far-End SONET/SDH HOP layer. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
class PM_BbValueHopFarEnd : public PM_BbCounterValue
{
public:

    //Class default constructor.
    PM_BbValueHopFarEnd(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueHopFarEnd();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEHOPFAREND_H
