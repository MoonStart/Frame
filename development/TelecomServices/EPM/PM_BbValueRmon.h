/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Teresa Chen
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Optical layer.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUERMON_H
#define PM_BBVALUERMON_H

#include <EPM/PM_TypeRmon.h>
#include <PM/PM_BbCounterValue.h>
#include <PM/PM_BbGaugeValue.h>

using namespace std;

//Keeps the parameter values of the Data. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.

//-----------------------------
// Class PM_BbValueRmonCounter
//-----------------------------

class PM_BbValueRmonCounter : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueRmonCounter(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueRmonCounter();

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
// Class PM_BbValueRmonGauge
//---------------------------

class PM_BbValueRmonGauge : public PM_BbGaugeValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueRmonGauge(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueRmonGauge();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

    //Resets all PM values to zero but current value.
    virtual void ResetAll(const uint32 theUtilization);

    //Resets minimum value for one parameter.
    virtual void ResetMinParam(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

};

#endif //PM_BBVALUERMON_H
