/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     13 February 2004  Hemant Thakkar
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Far-End SONET/SDH Multiplex Section layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueMsFarEnd.h>


//-----------------------------------------------------------------
PM_BbValueMsFarEnd::PM_BbValueMsFarEnd(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue(PM_TypeMsFarEnd::PM_PARAM_NUM)
{
    // Set the PM parameter flag. This flag is used when 
    // making adjustments related to unavailability conditions.
    myUasParameterFlags[PM_TypeMsFarEnd::PM_CV] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeMsFarEnd::PM_ES] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeMsFarEnd::PM_SES] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeMsFarEnd::PM_AISS] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeMsFarEnd::PM_UAS] = PM_UAS_PARAMETER;
}

//-----------------------------------------------------------------
PM_BbValueMsFarEnd::~PM_BbValueMsFarEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& PM_BbValueMsFarEnd::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeMsFarEnd::PM_AISS].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeMsFarEnd::PM_CV].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeMsFarEnd::PM_ES].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeMsFarEnd::PM_SES].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeMsFarEnd::PM_UAS].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeMsFarEnd::PM_FC].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueMsFarEnd::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueMsFarEnd::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeMsFarEnd::PM_AISS].UnsignedValue )
            >> FC_ExtractVar( myCurValues[PM_TypeMsFarEnd::PM_CV].UnsignedValue   )
            >> FC_ExtractVar( myCurValues[PM_TypeMsFarEnd::PM_ES].UnsignedValue   )
            >> FC_ExtractVar( myCurValues[PM_TypeMsFarEnd::PM_SES].UnsignedValue  )
            >> FC_ExtractVar( myCurValues[PM_TypeMsFarEnd::PM_UAS].UnsignedValue   )
            >> FC_ExtractVar( myCurValues[PM_TypeMsFarEnd::PM_FC].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueMsFarEnd::ReadObject()" );
    }

    return theStream;

}
