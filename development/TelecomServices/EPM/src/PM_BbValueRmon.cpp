/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     December 2005, Teresa Chen
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                RMON (GBEP, TGBEP, ...)
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbValueRmon.h>

//-----------------------------
// Class PM_BbValueRmonCOunter
//-----------------------------

//-----------------------------------------------------------------
PM_BbValueRmonCounter::PM_BbValueRmonCounter(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue( dummy )
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbValueRmonCounter::~PM_BbValueRmonCounter()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
ostream& PM_BbValueRmonCounter::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if ( myNumberOfParam == PM_TypeRmonCounter::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_DROP].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_PKT].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_USPKT].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_FRAG].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_JABR].UnsignedValue  );
    }
    else
    {
        theStream
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_DROP].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_PKT].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_USPKT].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_FRAG].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_JABR].UnsignedValue  )

        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue  );
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueRmonCounter::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if ( myNumberOfParam == PM_TypeRmonCounter::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_DROP].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_PKT].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_USPKT].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_FRAG].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_JABR].UnsignedValue  );
    }
    else
    {
        theStream
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_DROP].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_PKT].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_USPKT].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_FRAG].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_JABR].UnsignedValue  )

        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue  );
    }

    return theStream;
}

//-----------------------------------------------------------------
bool PM_BbValueRmonCounter::IsParam64BitValue( const CT_PM_Parameter theParameter )
{
    bool retVal = false;
 
    if ( (theParameter == PM_TypeRmonCounter::PM_DROP)  && (myNumberOfParam > PM_TypeRmonCounter::PM_DROP_HIGH)  ||
         (theParameter == PM_TypeRmonCounter::PM_PKT)   && (myNumberOfParam > PM_TypeRmonCounter::PM_PKT_HIGH)   ||
         (theParameter == PM_TypeRmonCounter::PM_BCPKT) && (myNumberOfParam > PM_TypeRmonCounter::PM_BCPKT_HIGH) ||
         (theParameter == PM_TypeRmonCounter::PM_MCPKT) && (myNumberOfParam > PM_TypeRmonCounter::PM_MCPKT_HIGH) ||
         (theParameter == PM_TypeRmonCounter::PM_CRCAE) && (myNumberOfParam > PM_TypeRmonCounter::PM_CRCAE_HIGH) ||
         (theParameter == PM_TypeRmonCounter::PM_USPKT) && (myNumberOfParam > PM_TypeRmonCounter::PM_USPKT_HIGH) ||
         (theParameter == PM_TypeRmonCounter::PM_OSPKT) && (myNumberOfParam > PM_TypeRmonCounter::PM_OSPKT_HIGH) ||
         (theParameter == PM_TypeRmonCounter::PM_FRAG) && (myNumberOfParam > PM_TypeRmonCounter::PM_FRAG_HIGH) ||
         (theParameter == PM_TypeRmonCounter::PM_JABR) && (myNumberOfParam > PM_TypeRmonCounter::PM_JABR_HIGH) )
    {
        retVal = true;
    }
 
    return retVal;
}
 
//-----------------------------------------------------------------
CT_PM_64BitValue PM_BbValueRmonCounter::Get64BitValue( const CT_PM_Parameter theParameter )
{
    CT_PM_64BitValue theValue; theValue.UnsignedValue = 0;
    CT_PM_64bit_ull aHighValue = 0;
    CT_PM_64bit_ull aLowValue  = 0;
 
    switch ( theParameter )
    {
        case PM_TypeRmonCounter::PM_DROP:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_DROP].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_PKT:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_PKT].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_BCPKT:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_MCPKT:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_CRCAE:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_USPKT:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_USPKT].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_OSPKT:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_FRAG:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_FRAG].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
        case PM_TypeRmonCounter::PM_JABR:
            aHighValue = myCurValues[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            aLowValue  = myCurValues[PM_TypeRmonCounter::PM_JABR].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
    }
 
    return theValue;
}
 
//-----------------------------------------------------------------
void PM_BbValueRmonCounter::Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue )
{
    long long aMultiplier = CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;

    switch ( theParameter )
    {
        case PM_TypeRmonCounter::PM_DROP:
            myCurValues[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_DROP].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_DROP].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif
            break;
        case PM_TypeRmonCounter::PM_PKT:
            myCurValues[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_PKT].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_PKT].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif
            break;
        case PM_TypeRmonCounter::PM_BCPKT:
            myCurValues[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif            
            break;
        case PM_TypeRmonCounter::PM_MCPKT:
            myCurValues[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif            
            break;
        case PM_TypeRmonCounter::PM_CRCAE:
            myCurValues[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif            
            break;
        case PM_TypeRmonCounter::PM_USPKT:
            myCurValues[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_USPKT].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_USPKT].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif            
            break;
        case PM_TypeRmonCounter::PM_OSPKT:
            myCurValues[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif            
            break;
        case PM_TypeRmonCounter::PM_FRAG:
            myCurValues[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_FRAG].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_FRAG].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif            
            break;
        case PM_TypeRmonCounter::PM_JABR:
            myCurValues[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / aMultiplier);
#ifdef PSOSP
            myCurValues[PM_TypeRmonCounter::PM_JABR].UnsignedValue      = theValue.UnsignedValue;
#else
            myCurValues[PM_TypeRmonCounter::PM_JABR].UnsignedValue      = (uint32) (theValue.UnsignedValue % aMultiplier);
#endif            
            break;
    }
}


//---------------------------
// Class PM_BbValueRmonGauge
//---------------------------

//-----------------------------------------------------------------
//##ModelId=3C5016260054
PM_BbValueRmonGauge::PM_BbValueRmonGauge(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeRmonGauge::PM_PARAM_NUM)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//##ModelId=3C501626005E
PM_BbValueRmonGauge::~PM_BbValueRmonGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbValueRmonGauge::ResetAll(void)
{
    uint32 i;


    for (i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].SignedValue = 0;
        myMinValues[i].SignedValue = CT_PM_DEFAULT_MIN_UTIL;
        myMaxValues[i].SignedValue = CT_PM_DEFAULT_MAX_UTIL;
    }

}

//-----------------------------------------------------------------
void PM_BbValueRmonGauge::ResetAll(const uint32 theUtilization )
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
void PM_BbValueRmonGauge::ResetMinParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_UTIL;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueRmonGauge::ResetMinParam()" );
    }

}

//-----------------------------------------------------------------
void PM_BbValueRmonGauge::ResetMaxParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset maximum value.
        myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_UTIL;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueRmonGauge::ResetMaxParam()" );
    }

}

//-----------------------------------------------------------------
//##ModelId=3C5016260060
ostream& PM_BbValueRmonGauge::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream   << FC_InsertVar( myCurValues[PM_TypeRmonGauge::PM_UTIL].SignedValue );
        theStream   << FC_InsertVar( myMinValues[PM_TypeRmonGauge::PM_UTIL].SignedValue );
        theStream   << FC_InsertVar( myMaxValues[PM_TypeRmonGauge::PM_UTIL].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueRmonGauge::WriteObject()" );
    }

    return theStream;
}

//-----------------------------------------------------------------
//##ModelId=3C5016260072
istream& PM_BbValueRmonGauge::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream   >> FC_ExtractVar( myCurValues[PM_TypeRmonGauge::PM_UTIL].SignedValue );
        theStream   >> FC_ExtractVar( myMinValues[PM_TypeRmonGauge::PM_UTIL].SignedValue );
        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeRmonGauge::PM_UTIL].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueRmonGauge::ReadObject()" );
    }

    return theStream;
}
