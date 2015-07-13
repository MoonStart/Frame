/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Laser.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUELASER_H
#define PM_BBVALUELASER_H

#include <PM/PM_TypeLaser.h>
#include "PM_BbGaugeValue.h"


//Keeps the parameter values of the Laser. 
//A public method inherits from PM_BbValue which 
//returns the current value of the parameters.
//##ModelId=3C1F6F550356
class PM_BbValueLaser : public PM_BbGaugeValue
{
public:

    friend class PM_BbValueTRN_RAM;
    friend class PM_BbValueSMTM;

    //Class default constructor.
    //##ModelId=3C1F6F560151
    PM_BbValueLaser(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    //##ModelId=3C1F6F560163
    virtual ~PM_BbValueLaser();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

    //Resets minimum value for one parameter.
    virtual void ResetMinParam(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F560165
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F560177
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUELASER_H
