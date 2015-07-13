/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                TCM layer..
--------------------------------------------------------------------------*/

#ifndef PM_BBVALUETCM_H
#define PM_BBVALUETCM_H

#include <EPM/PM_TypeTcm.h>
#include <PM/PM_BbCounterValue.h>
#include <PM/PM_BbGaugeValue.h>
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_ObjectWithIdentifier.h>

//Keeps the parameter values of the TCM layer. A 
//public method inherits from PM_BbValue which returns 
//the current value of the parameters.
class PM_BbValueTcm : public PM_BbCounterValue
{
public:

    friend class PM_BbValueTRN_RAM;

    //Class default constructor.
    PM_BbValueTcm(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueTcm();

    // Method to set the object identifier value
    virtual void SetIdentifier( uint32 theIdentifier );

    // Method to retrieve the object identifier value
    virtual uint32 GetIdentifier();

    //Operator that copies the register values.
    virtual PM_BbValueTcm& operator=(PM_BbValueTcm &theOtherValue);

    //Operator that returns true if values of this object are equal
    virtual bool operator==(PM_BbValueTcm &theOtherValue);

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the states from a binary stream.
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Handle 64Bit values (e.g. ODU4 CV-ODU)
    virtual bool IsParam64BitValue( const CT_PM_Parameter theParameter );
    virtual CT_PM_64BitValue Get64BitValue( const CT_PM_Parameter theParameter );
    virtual void             Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue );

private:

    // Object ID component
    FC_ObjectWithIdentifier myObjectID;

};

//---------------------------
// Class PM_BbValueTcmGauge
//---------------------------

class PM_BbValueTcmGauge : public PM_BbGaugeValue
{
public:

    //Class default constructor.
    PM_BbValueTcmGauge(uint32 dummy = 0, uint32 dummy1 = 0);
    
    //Class default destructor.
    virtual ~PM_BbValueTcmGauge();

    //Resets all PM values to zero.
    virtual void ResetAll(void);

    //Resets all PM values to zero but current value.
    virtual void ResetAll(const uint32 theUtilization);

    //Resets minimum value for one parameter.
    virtual void ResetMinParam(CT_PM_Parameter theParameter);
    virtual void ResetMinParamDMSourceEnabled(CT_PM_Parameter theParameter);

    //Resets maximum value for one parameter.
    virtual void ResetMaxParam(CT_PM_Parameter theParameter);

    // Method to retrieve the object identifier value
    virtual uint32 GetIdentifier();

    // Method to set the object identifier value
    virtual void SetIdentifier( uint32 theIdentifier );

    //Operator that copies the register values.
    virtual PM_BbValueTcmGauge& operator=(PM_BbValueTcmGauge &theOtherValue);

    //Operator that returns true if values of this object are equal
    virtual bool operator==(PM_BbValueTcmGauge &theOtherValue);

protected:

    //Stores the values to the stream.
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    virtual istream& ReadObject( istream& theStream );

    //Writes the states to the binary stream.
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the states from a binary stream.
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
 
    // Object ID component
    FC_ObjectWithIdentifier myObjectID;
};

#endif //PM_BBVALUETCM_H
