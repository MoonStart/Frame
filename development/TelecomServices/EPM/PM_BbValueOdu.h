/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                ODU layer..
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEODU_H
#define PM_BBVALUEODU_H

#include <EPM/PM_TypeOdu.h>
#include <PM/PM_BbCounterValue.h>
#include <PM/PM_BbGaugeValue.h>
#include <ErrorService/FC_Error.h>

//Keeps the parameter values of the ODU layer. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
class PM_BbValueOdu : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueOdu(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueOdu();

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Handle 64Bit values (e.g. ODU4 CV-ODU)
    virtual bool IsParam64BitValue( const CT_PM_Parameter theParameter );
    virtual CT_PM_64BitValue Get64BitValue( const CT_PM_Parameter theParameter );
    virtual void             Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue );
};

//---------------------------
// Class PM_BbValueOduGauge
//---------------------------

class PM_BbValueOduGauge : public PM_BbGaugeValue
{
public:

    //Class default constructor.
    PM_BbValueOduGauge(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueOduGauge();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

    //Resets all PM values to zero but current value.
    virtual void ResetAll(const uint32 theUtilization);

    //Resets minimum value for one parameter.
    virtual void ResetMinParam(CT_PM_Parameter theParameter);
    virtual void ResetMinParamDMSourceEnabled(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUEODU_H
