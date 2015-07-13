/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                TCM layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbValueTcm.h>


//-----------------------------------------------------------------
PM_BbValueTcm::PM_BbValueTcm(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue( dummy )
{
    // Set the PM parameter flag. This flag is used when 
    // making adjustments related to unavailability conditions.
    myUasParameterFlags[PM_TypeTcm::PM_CV] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeTcm::PM_ES] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeTcm::PM_SES] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeTcm::PM_UAS] = PM_UAS_PARAMETER;
}

//-----------------------------------------------------------------
PM_BbValueTcm::~PM_BbValueTcm()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& PM_BbValueTcm::WriteObject( ostream& theStream )
{
    // Call base classes methods.
    PM_BbCounterValue::WriteObject(theStream);

    myObjectID.WriteObject(theStream);

    if ( myNumberOfParam == PM_TypeTcm::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_CV].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_ES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_SES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_UAS].UnsignedValue		);
    }
    else
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_CV].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_ES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_SES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_UAS].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeTcm::PM_CV_HIGH].UnsignedValue	);
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueTcm::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    myObjectID.ReadObject(theStream);

    if ( myNumberOfParam == PM_TypeTcm::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_CV].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_ES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_SES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_UAS].UnsignedValue		 );
    }
    else
    {
        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_CV].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_ES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_SES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_UAS].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeTcm::PM_CV_HIGH].UnsignedValue	 );
    }

    return theStream;

}

//-----------------------------------------------------------------
FC_Stream& PM_BbValueTcm::WriteObjectBinary( FC_Stream& theStream )
{
    // Call the base classes methods.
    PM_BbCounterValue::WriteObjectBinary( theStream );

    myObjectID.WriteObjectBinary( theStream );

    return theStream;

}

//-----------------------------------------------------------------
FC_Stream& PM_BbValueTcm::ReadObjectBinary( FC_Stream& theStream )
{
    // Call the base classes methods.
    PM_BbCounterValue::ReadObjectBinary( theStream );

    myObjectID.ReadObjectBinary( theStream );
    
    return theStream;

}

//-----------------------------------------------------------------------------
void PM_BbValueTcm::SetIdentifier( uint32 theIdentifier )
{
    myObjectID.SetIdentifier( theIdentifier );
}

//-----------------------------------------------------------------------------
uint32 PM_BbValueTcm::GetIdentifier()
{
    return myObjectID.GetIdentifier();
}

//-----------------------------------------------------------------
PM_BbValueTcm& PM_BbValueTcm::operator=(PM_BbValueTcm &theOtherValue)
{
    if( this == &theOtherValue )
    {
        return *this;
    }

    ((PM_BbCounterValue&) *this) = theOtherValue;

    // Set object ID.
    myObjectID = theOtherValue.myObjectID;

    return *this;
}

//-----------------------------------------------------------------
bool PM_BbValueTcm::operator==(PM_BbValueTcm &theOtherValue)
{
    bool isEqual = (((PM_BbCounterValue&) *this) == theOtherValue);

    if( isEqual && (myObjectID != theOtherValue.myObjectID ) )
    {
        isEqual = false;
    }

    return isEqual;
}

//-----------------------------------------------------------------
bool PM_BbValueTcm::IsParam64BitValue( const CT_PM_Parameter theParameter )
{
    bool retVal = false;
 
    if ( (theParameter == PM_TypeTcm::PM_CV) && (myNumberOfParam > PM_TypeTcm::PM_CV_HIGH) )
    {
        retVal = true;
    }
 
    return retVal;
}
 
//-----------------------------------------------------------------
CT_PM_64BitValue PM_BbValueTcm::Get64BitValue( const CT_PM_Parameter theParameter )
{
    CT_PM_64BitValue theValue;
    theValue.UnsignedValue = 0;
 
    switch ( theParameter )
    {
        case PM_TypeTcm::PM_CV: 
            unsigned long long aHighValue = myCurValues[PM_TypeTcm::PM_CV_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            unsigned long long aLowValue  = myCurValues[PM_TypeTcm::PM_CV].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
    }
 
    return theValue;
}
 
//-----------------------------------------------------------------
void PM_BbValueTcm::Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue )
{
    switch ( theParameter )
    {
        case PM_TypeTcm::PM_CV:
            myCurValues[PM_TypeTcm::PM_CV_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
            myCurValues[PM_TypeTcm::PM_CV].UnsignedValue      = (uint32) (theValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
 
//---------------------------
// Class PM_BbValueTcmGauge
//---------------------------
 
//-----------------------------------------------------------------
//##ModelId=3C5016260054
PM_BbValueTcmGauge::PM_BbValueTcmGauge(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeTcmGauge::PM_PARAM_NUM)
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
//##ModelId=3C501626005E
PM_BbValueTcmGauge::~PM_BbValueTcmGauge()
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
// Typically runs when new period -and- INHIBITED
//-----------------------------------------------------------------
void PM_BbValueTcmGauge::ResetAll(void)
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
// Typically runs when new period -and- not INHIBITED
//-----------------------------------------------------------------
void PM_BbValueTcmGauge::ResetAll(const uint32 theUtilization )
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
void PM_BbValueTcmGauge::ResetMinParamDMSourceEnabled(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        myMinValues[theParameter].SignedValue = PM_TypeTcmGauge::GetMaxValueTableTcm15M()[theParameter].SignedValue;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueTcmGauge::ResetMinParamDMSourceEnabled()" );
    }
}

//-----------------------------------------------------------------
// Typically runs when INIT-REG command executed.
// Care must be taken here to account for two scenarios:
// 1. (see ResetMinParamDMSourceEnabled() method above).
// 2. DMSOURCE is DISABLED and we want the LOW value to equal zero!
//-----------------------------------------------------------------
void PM_BbValueTcmGauge::ResetMinParam(CT_PM_Parameter theParameter)
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
        FC_THROW_ERROR(FC_SWError, "PM_BbValueTcmGauge::ResetMinParam()" );
    }
}
 
//-----------------------------------------------------------------
// Typically runs when INIT-REG command executed
//-----------------------------------------------------------------
void PM_BbValueTcmGauge::ResetMaxParam(CT_PM_Parameter theParameter)
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
        FC_THROW_ERROR(FC_SWError, "PM_BbValueTcmGauge::ResetMaxParam()" );
    }
}
 
//-----------------------------------------------------------------
ostream& PM_BbValueTcmGauge::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    myObjectID.WriteObject( theStream );
 
    if(myNumberOfParam != 0)
    {
        theStream   << FC_InsertVar( myCurValues[PM_TypeTcmGauge::PM_DELAY].SignedValue );
        theStream   << FC_InsertVar( myMinValues[PM_TypeTcmGauge::PM_DELAY].SignedValue );
        theStream   << FC_InsertVar( myMaxValues[PM_TypeTcmGauge::PM_DELAY].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueTcmGauge::WriteObject()" );
    }
 
    return theStream;
}
 
//-----------------------------------------------------------------
istream& PM_BbValueTcmGauge::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    myObjectID.ReadObject( theStream );

    if(myNumberOfParam != 0)
    {
 
        theStream   >> FC_ExtractVar( myCurValues[PM_TypeTcmGauge::PM_DELAY].SignedValue );
        theStream   >> FC_ExtractVar( myMinValues[PM_TypeTcmGauge::PM_DELAY].SignedValue );
        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeTcmGauge::PM_DELAY].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueTcmGauge::ReadObject()" );
    }
 
    return theStream;
}

//-----------------------------------------------------------------
FC_Stream& PM_BbValueTcmGauge::WriteObjectBinary( FC_Stream& theStream )
{
    // Call the base classes methods.
    PM_BbGaugeValue::WriteObjectBinary( theStream );

    myObjectID.WriteObjectBinary( theStream );

    return theStream;
}

//-----------------------------------------------------------------
FC_Stream& PM_BbValueTcmGauge::ReadObjectBinary( FC_Stream& theStream )
{
    // Call the base classes methods.
    PM_BbGaugeValue::ReadObjectBinary( theStream );

    myObjectID.ReadObjectBinary( theStream );
    
    return theStream;
}

//-----------------------------------------------------------------------------
uint32 PM_BbValueTcmGauge::GetIdentifier()
{
    return myObjectID.GetIdentifier();
}

//-----------------------------------------------------------------------------
void PM_BbValueTcmGauge::SetIdentifier( uint32 theIdentifier )
{
    myObjectID.SetIdentifier( theIdentifier );
}

//-----------------------------------------------------------------
PM_BbValueTcmGauge& PM_BbValueTcmGauge::operator=(PM_BbValueTcmGauge &theOtherValue)
{
    if( this == &theOtherValue )
    {
        return *this;
    }

    ((PM_BbGaugeValue&) *this) = ((PM_BbValue &)theOtherValue);

    // Set object ID.
    myObjectID = theOtherValue.myObjectID;

    return *this;
}

//-----------------------------------------------------------------
bool PM_BbValueTcmGauge::operator==(PM_BbValueTcmGauge &theOtherValue)
{
    bool isEqual = (((PM_BbGaugeValue&) *this) == ((PM_BbValue &)theOtherValue));

    if( isEqual && (myObjectID != theOtherValue.myObjectID ) )
    {
        isEqual = false;
    }

    return isEqual;
}

