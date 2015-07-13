/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Oms layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEOMS_H
#define PM_BBVALUEOMS_H

#include <PM/PM_TypeOms.h>
#include <PM/PM_BbGaugeValue.h>


//Keeps the parameter values of the Oms. A public method 
//inherits from PM_BbValue which returns the current value of 
//the parameters.
//##ModelId=3E6E4C980021
class PM_BbValueOms : public PM_BbGaugeValue
{
public:

    friend class PM_BbValueAMP; 
    friend class PM_BbValueOLIM; 

    //Class default constructor.
    //##ModelId=3E6E4C99032F
    PM_BbValueOms(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    //##ModelId=3E6E4C99033A
    virtual ~PM_BbValueOms();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

    //Resets minimum value for one parameter.
    virtual void ResetMinParam(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

protected:

    //Stores the values to the stream.
    //##ModelId=3E6E4C99034D
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4C990361
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEOMS_H
