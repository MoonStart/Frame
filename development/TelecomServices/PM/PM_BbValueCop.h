/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Optical Channel.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUECOP_H
#define PM_BBVALUECOP_H

#include <PM/PM_TypeCop.h>
#include "PM_BbGaugeValue.h"


//Keeps the parameter values of the Optical Channel. A public 
//method inherits from PM_BbValue which returns the current 
//value of the parameters.
//##ModelId=3C1F6F5100A8
class PM_BbValueCop : public PM_BbGaugeValue
{
public:

    friend class PM_BbValueAMP; 
    friend class PM_BbValueMUX; 
    friend class PM_BbValueOLIM; 
    friend class PM_BbValueRCMM;

    //Class default constructor.
    //##ModelId=3C1F6F51024D
    PM_BbValueCop(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    //##ModelId=3C1F6F510260
    virtual ~PM_BbValueCop();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

    //Resets minimum value for one parameter.
    virtual void ResetMinParam(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F510262
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F510274
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUECOP_H
