/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Data (RS, FICON,ESCON, GbE, GOPT).
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueData.h>


//-----------------------------------------------------------------
//##ModelId=3C9255B80332
PM_BbValueData::PM_BbValueData(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue( dummy )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C9255B8033D
PM_BbValueData::~PM_BbValueData()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C9255B803B4
ostream& PM_BbValueData::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if ( myNumberOfParam == PM_TypeData::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeData::PM_LOSS].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_CV].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_SE].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_SEFS].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_SES].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_ES].UnsignedValue   );
    }
    else
    {
        theStream
        << FC_InsertVar( myCurValues[PM_TypeData::PM_LOSS].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_CV].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_SE].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_SEFS].UnsignedValue )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_SES].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_ES].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeData::PM_SE_HIGH].UnsignedValue );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C9255B803BF
istream& PM_BbValueData::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if ( myNumberOfParam == PM_TypeData::GetMaxNbParamsNoHighOrder64Bits() )
    {
        theStream 
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_LOSS].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_CV].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_SE].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_SEFS].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_SES].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_ES].UnsignedValue   );
    }
    else
    {
        theStream
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_LOSS].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_CV].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_SE].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_SEFS].UnsignedValue )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_SES].UnsignedValue  )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_ES].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeData::PM_SE_HIGH].UnsignedValue );
    }

    return theStream;

}

//-----------------------------------------------------------------
bool PM_BbValueData::IsParam64BitValue( const CT_PM_Parameter theParameter )
{
    bool retVal = false;
 
    if ( (theParameter == PM_TypeData::PM_SE) && (myNumberOfParam > PM_TypeData::PM_SE_HIGH) )
    {
        retVal = true;
    }
 
    return retVal;
}
 
//-----------------------------------------------------------------
CT_PM_64BitValue PM_BbValueData::Get64BitValue( const CT_PM_Parameter theParameter )
{
    CT_PM_64BitValue theValue;
    theValue.UnsignedValue = 0;
 
    switch ( theParameter )
    {
        case PM_TypeData::PM_SE:

            CT_PM_64bit_ull aHighValue = myCurValues[PM_TypeData::PM_SE_HIGH].UnsignedValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER;
            CT_PM_64bit_ull aLowValue  = myCurValues[PM_TypeData::PM_SE].UnsignedValue;
            theValue.UnsignedValue = aHighValue + aLowValue;
            break;
    }
 
    return theValue;
}
 
//-----------------------------------------------------------------
void PM_BbValueData::Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue )
{
    switch ( theParameter )
    {
        case PM_TypeData::PM_SE:
#ifdef PSOSP
            myCurValues[PM_TypeData::PM_SE_HIGH].UnsignedValue = (uint32) 0;
            myCurValues[PM_TypeData::PM_SE].UnsignedValue      = (uint32) theValue.UnsignedValue;
#else
            myCurValues[PM_TypeData::PM_SE_HIGH].UnsignedValue = (uint32) (theValue.UnsignedValue / CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
            myCurValues[PM_TypeData::PM_SE].UnsignedValue      = (uint32) (theValue.UnsignedValue % CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER);
#endif

            break;
    }
}

