/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                ODU layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbValueOdu.h>


//-----------------------------------------------------------------
PM_BbValueOdu::PM_BbValueOdu(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue( dummy )
{
    // Set the PM parameter flag. This flag is used when 
    // making adjustments related to unavailability conditions.
    myUasParameterFlags[PM_TypeOdu::PM_CV]    = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeOdu::PM_ES]    = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeOdu::PM_SES]   = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeOdu::PM_PSC]   = PM_BASIC_PARAMETER;
    myUasParameterFlags[PM_TypeOdu::PM_PSD]   = PM_BASIC_PARAMETER;

    myUasParameterFlags[PM_TypeOdu::PM_UAS]   = PM_UAS_PARAMETER;
}

//-----------------------------------------------------------------
PM_BbValueOdu::~PM_BbValueOdu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& PM_BbValueOdu::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if ( myNumberOfParam == PM_TypeOdu::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_CV].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_ES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_SES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_UAS].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_PSC].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_PSD].UnsignedValue		);
    }
    else
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_CV].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_ES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_SES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_UAS].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_PSC].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_PSD].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeOdu::PM_CV_HIGH].UnsignedValue	);
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueOdu::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if ( myNumberOfParam == PM_TypeOdu::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_CV].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_ES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_SES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_UAS].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_PSC].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_PSD].UnsignedValue		 );
    }
    else
    {
        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_CV].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_ES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_SES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_UAS].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_PSC].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_PSD].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeOdu::PM_CV_HIGH].UnsignedValue	 );
    }

    return theStream;

}

//-----------------------------------------------------------------
bool PM_BbValueOdu::IsParam64BitValue( const CT_PM_Parameter theParameter )
{
    bool retVal = false;
 
    if ( (theParameter == PM_TypeOdu::PM_CV) && (myNumberOfParam > PM_TypeOdu::PM_CV_HIGH) )
    {
        retVal = true;
    }
 
    return retVal;
}

//-----------------------------------------------------------------
CT_PM_64BitValue PM_BbValueOdu::Get64BitValue( const CT_PM_Parameter theParameter )
{
    CT_PM_64BitValue theValue;
    theValue.UnsignedValue = 0;
 
    switch ( theParameter )
    {
        case PM_TypeOdu::PM_CV: 
            unsigned long long aHighValue = myCurValues[PM_TypeOdu::PM_CV_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            unsigned long long aLowValue  = myCurValues[PM_TypeOdu::PM_CV].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
    }
 
    return theValue;
}

//-----------------------------------------------------------------
void PM_BbValueOdu::Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue )
{
    switch ( theParameter )
    {
        case PM_TypeOdu::PM_CV:
            myCurValues[PM_TypeOdu::PM_CV_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
            myCurValues[PM_TypeOdu::PM_CV].UnsignedValue      = (uint32) (theValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------
// Class PM_BbValueOduGauge
//---------------------------

//-----------------------------------------------------------------
//##ModelId=3C5016260054
PM_BbValueOduGauge::PM_BbValueOduGauge(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeOduGauge::PM_PARAM_NUM)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//##ModelId=3C501626005E
PM_BbValueOduGauge::~PM_BbValueOduGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbValueOduGauge::ResetAll(void)
{
    uint32 i;

    for (i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].SignedValue = 0;
        myMinValues[i].SignedValue = CT_PM_DEFAULT_MIN_DELAY;
        myMaxValues[i].SignedValue = CT_PM_DEFAULT_MAX_DELAY;
    }
}

//-----------------------------------------------------------------
void PM_BbValueOduGauge::ResetAll(const uint32 theUtilization )
{
    uint32 i;

    for (i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].SignedValue = theUtilization;
        myMinValues[i].SignedValue = theUtilization;
        myMaxValues[i].SignedValue = theUtilization;
    }
}

//-----------------------------------------------------------------
// Typically runs when INIT-REG command executed.
// Care must be taken here to account for two scenarios:
// 1. DMSOURCE is ENABLED and we want the LOW value to pick up
//    first new read of current (same strategy as UTIL (RMON).
// 2. (see ResetMinParam() method below).
//-----------------------------------------------------------------
void PM_BbValueOduGauge::ResetMinParamDMSourceEnabled(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        myMinValues[theParameter].SignedValue = PM_TypeOduGauge::GetMaxValueTableOdu15M()[theParameter].SignedValue;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOduGauge::ResetMinParamDMSourceEnabled()" );
    }
}

//-----------------------------------------------------------------
// Typically runs when INIT-REG command executed.
// Care must be taken here to account for two scenarios:
// 1. (see ResetMinParamDMSourceEnabled() method above).
// 2. DMSOURCE is DISABLED and we want the LOW value to equal zero!
//-----------------------------------------------------------------
void PM_BbValueOduGauge::ResetMinParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_DELAY;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOduGauge::ResetMinParam()" );
    }
}

//-----------------------------------------------------------------
void PM_BbValueOduGauge::ResetMaxParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset maximum value.
        myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_DELAY;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOduGauge::ResetMaxParam()" );
    }
}

//-----------------------------------------------------------------
ostream& PM_BbValueOduGauge::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream   << FC_InsertVar( myCurValues[PM_TypeOduGauge::PM_DELAY].SignedValue );
        theStream   << FC_InsertVar( myMinValues[PM_TypeOduGauge::PM_DELAY].SignedValue );
        theStream   << FC_InsertVar( myMaxValues[PM_TypeOduGauge::PM_DELAY].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOduGauge::WriteObject()" );
    }

    return theStream;
}

//-----------------------------------------------------------------
istream& PM_BbValueOduGauge::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream   >> FC_ExtractVar( myCurValues[PM_TypeOduGauge::PM_DELAY].SignedValue );
        theStream   >> FC_ExtractVar( myMinValues[PM_TypeOduGauge::PM_DELAY].SignedValue );
        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeOduGauge::PM_DELAY].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOduGauge::ReadObject()" );
    }

    return theStream;
}

