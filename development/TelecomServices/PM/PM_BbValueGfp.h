/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     22 April 2004  Hemant Thakkar
 DESCRIPTION:   The Blackboard object of PM parameter values for GFP layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEGFP_H
#define PM_BBVALUEGFP_H

#include <PM/PM_TypeGfp.h>
#include "PM_BbCounterValue.h"
#include <ErrorService/FC_Error.h>


//Keeps the parameter values of the GFP layer. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
class PM_BbValueGfp : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueGfp(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueGfp();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEGFP_H
