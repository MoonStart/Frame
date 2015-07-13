/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Optical layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEOPT_H
#define PM_BBVALUEOPT_H

#include <PM/PM_TypeOpt.h>
#include <PM/PM_BbGaugeValue.h>
#include <PM/PM_BbCounterValue.h>


//Keeps the parameter values of the Optical. A public method 
//inherits from PM_BbValue which returns the current value of 
//the parameters.
//##ModelId=3C501625026F
class PM_BbValueOpt : public PM_BbGaugeValue
{
public:

    friend class PM_BbValueTRN_RAM;
    friend class PM_BbValueSMTM;
    friend class PM_BbValueOSC;

    //Class default constructor.
    //##ModelId=3C5016260054
    PM_BbValueOpt(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    //##ModelId=3C501626005E
    virtual ~PM_BbValueOpt();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

    //Resets minimum value for one parameter.
    virtual void ResetMinParam(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

protected:

    //Stores the values to the stream.
    //##ModelId=3C5016260060
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C5016260072
    virtual istream& ReadObject( istream& theStream );

};

class PM_BbValueOptCounter : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueOptCounter(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueOptCounter();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEOPT_H
