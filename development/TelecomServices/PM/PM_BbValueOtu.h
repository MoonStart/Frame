/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002 Sebastien Cossette.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                OTU.
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUEOTU_H
#define PM_BBVALUEOTU_H

#include <PM/PM_TypeOtu.h>
#include <PM/PM_BbCounterValue.h>
#include <PM/PM_BbGaugeValue.h>
#include <ErrorService/FC_Error.h>


//Keeps the parameter values of the Optical Transport Unit. A 
//public method inherits from PM_BbValue which returns the 
//current value of the parameters.
//##ModelId=3C1F6F5B0279
class PM_BbValueOtu : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;
    friend class PM_BbValueSMTM;

    //Class default constructor.
    //##ModelId=3C1F6F5C00B8
    PM_BbValueOtu(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    //##ModelId=3C1F6F5C00CB
    virtual ~PM_BbValueOtu();

protected:

    //Stores the values to the stream.
    //##ModelId=3C1F6F5C00CD
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3C1F6F5C00E0
    virtual istream& ReadObject( istream& theStream );

    //Handle 64Bit values (e.g. ODU4 CV-ODU)
    virtual bool IsParam64BitValue( const CT_PM_Parameter theParameter );
    virtual CT_PM_64BitValue Get64BitValue( const CT_PM_Parameter theParameter );
    virtual void             Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue );
};


//---------------------------
// Class PM_BbValueOtuGauge
//---------------------------

class PM_BbValueOtuGauge : public PM_BbGaugeValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueOtuGauge(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueOtuGauge();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

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

#endif //PM_BBVALUEOTU_H
