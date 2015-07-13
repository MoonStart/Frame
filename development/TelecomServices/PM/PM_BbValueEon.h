/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                EON.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEEON_H
#define PM_BBVALUEEON_H

#include <PM/PM_TypeEon.h>
#include "PM_BbCounterValue.h"
#include <ErrorService/FC_Error.h>


//Keeps the parameter values of the EON. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
//##ModelId=3FA1610A0065
class PM_BbValueEon : public PM_BbCounterValue
{
public:

    friend class PM_BbValueOSC; 

    //Class default constructor.
	//##ModelId=3FA1610A01CE
    PM_BbValueEon(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
	//##ModelId=3FA1610A01D1
    virtual ~PM_BbValueEon();

protected:

    //Stores the values to the stream.
	//##ModelId=3FA1610A01D3
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
	//##ModelId=3FA1610A01DD
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEEON_H
