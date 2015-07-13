/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January, 2002 Sebastien Cossette.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                OTU.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueOtu.h>

//-----------------------------------------------------------------
//##ModelId=3C1F6F5C00B8
PM_BbValueOtu::PM_BbValueOtu(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue( dummy )
{
    // Set the PM parameter flag. This flag is used when 
    // making adjustments related to unavailability conditions.
    myUasParameterFlags[PM_TypeOtu::PM_CV]  = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeOtu::PM_ES]  = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeOtu::PM_SES] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeOtu::PM_UAS] = PM_UAS_PARAMETER;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5C00CB
PM_BbValueOtu::~PM_BbValueOtu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5C00CD
ostream& PM_BbValueOtu::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if ( myNumberOfParam == PM_TypeOtu::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_BE].UnsignedValue  );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_UBE].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_CV].UnsignedValue  );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_ES].UnsignedValue  );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_SES].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_UAS].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_PSC].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_PSD].UnsignedValue );
    }
    else
    {
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_BE].UnsignedValue  );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_UBE].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_CV].UnsignedValue  );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_ES].UnsignedValue  );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_SES].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_UAS].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_PSC].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_PSD].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_CV_HIGH].UnsignedValue );
        theStream << FC_InsertVar( myCurValues[PM_TypeOtu::PM_BE_HIGH].UnsignedValue );
    }

    return theStream;
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5C00E0
istream& PM_BbValueOtu::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if ( myNumberOfParam == PM_TypeOtu::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_BE].UnsignedValue  );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_UBE].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_CV].UnsignedValue  );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_ES].UnsignedValue  );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_SES].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_UAS].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_PSC].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_PSD].UnsignedValue );
    }
    else
    {
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_BE].UnsignedValue  );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_UBE].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_CV].UnsignedValue  );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_ES].UnsignedValue  );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_SES].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_UAS].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_PSC].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_PSD].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_CV_HIGH].UnsignedValue );
        theStream >> FC_ExtractVar( myCurValues[PM_TypeOtu::PM_BE_HIGH].UnsignedValue );
    }

    return theStream;
}

//-----------------------------------------------------------------
bool PM_BbValueOtu::IsParam64BitValue( const CT_PM_Parameter theParameter )
{
    bool retVal = false;
 
    if ( ((theParameter == PM_TypeOtu::PM_CV) && (myNumberOfParam > PM_TypeOtu::PM_CV_HIGH)) ||
         ((theParameter == PM_TypeOtu::PM_BE) && (myNumberOfParam > PM_TypeOtu::PM_BE_HIGH)) )
    {
        retVal = true;
    }
 
    return retVal;
}
 
//-----------------------------------------------------------------
CT_PM_64BitValue PM_BbValueOtu::Get64BitValue( const CT_PM_Parameter theParameter )
{
    CT_PM_64BitValue theValue;
    CT_PM_64bit_ull aHighValue = 0;
    CT_PM_64bit_ull aLowValue = 0;
    theValue.UnsignedValue = 0;
 
    switch ( theParameter )
    {
        case PM_TypeOtu::PM_CV:
            aHighValue = myCurValues[PM_TypeOtu::PM_CV_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeOtu::PM_CV].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;

        case PM_TypeOtu::PM_BE:
            aHighValue = myCurValues[PM_TypeOtu::PM_BE_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeOtu::PM_BE].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
    }
 
    return theValue;
}
 
//-----------------------------------------------------------------
void PM_BbValueOtu::Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue )
{
    switch ( theParameter )
    {
        case PM_TypeOtu::PM_CV:
#ifdef PSOSP
            myCurValues[PM_TypeOtu::PM_CV_HIGH].UnsignedValue = (uint32) 0;
            myCurValues[PM_TypeOtu::PM_CV].UnsignedValue      = (uint32) theValue.UnsignedValue;
#else
            myCurValues[PM_TypeOtu::PM_CV_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
            myCurValues[PM_TypeOtu::PM_CV].UnsignedValue      = (uint32) (theValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
#endif
            break;

        case PM_TypeOtu::PM_BE:
#ifdef PSOSP
            myCurValues[PM_TypeOtu::PM_BE_HIGH].UnsignedValue = (uint32) 0;
            myCurValues[PM_TypeOtu::PM_BE].UnsignedValue      = (uint32) theValue.UnsignedValue;
#else
            myCurValues[PM_TypeOtu::PM_BE_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
            myCurValues[PM_TypeOtu::PM_BE].UnsignedValue      = (uint32) (theValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
#endif
            break;
    }
}


//---------------------------
// Class PM_BbValueOtuGauge
//---------------------------

//-----------------------------------------------------------------
//##ModelId=3C5016260054
PM_BbValueOtuGauge::PM_BbValueOtuGauge(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeOtuGauge::PM_PARAM_NUM)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//##ModelId=3C501626005E
PM_BbValueOtuGauge::~PM_BbValueOtuGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbValueOtuGauge::ResetAll(void)
{
    uint32 i;


    for (i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].SignedValue = 0;
        myMinValues[i].SignedValue = CT_PM_DEFAULT_MIN_BER;
        myMaxValues[i].SignedValue = CT_PM_DEFAULT_MAX_BER;
    }

}

//-----------------------------------------------------------------
void PM_BbValueOtuGauge::ResetMinParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_BER;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOtuGauge::ResetMinParam()" );
    }

}

//-----------------------------------------------------------------
void PM_BbValueOtuGauge::ResetMaxParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset maximum value.
        myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_BER;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOtuGauge::ResetMaxParam()" );
    }

}

//-----------------------------------------------------------------
//##ModelId=3C5016260060
ostream& PM_BbValueOtuGauge::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream   << FC_InsertVar( myCurValues[PM_TypeOtuGauge::PM_BER].SignedValue );
        theStream   << FC_InsertVar( myMinValues[PM_TypeOtuGauge::PM_BER].SignedValue );
        theStream   << FC_InsertVar( myMaxValues[PM_TypeOtuGauge::PM_BER].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOtuGauge::WriteObject()" );
    }

    return theStream;
}

//-----------------------------------------------------------------
//##ModelId=3C5016260072
istream& PM_BbValueOtuGauge::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream   >> FC_ExtractVar( myCurValues[PM_TypeOtuGauge::PM_BER].SignedValue );
        theStream   >> FC_ExtractVar( myMinValues[PM_TypeOtuGauge::PM_BER].SignedValue );
        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeOtuGauge::PM_BER].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOtuGauge::ReadObject()" );
    }

    return theStream;
}

