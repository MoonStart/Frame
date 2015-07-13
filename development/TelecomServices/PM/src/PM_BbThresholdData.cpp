/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM Configuration parameters class. Keep the congig of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdData.h>


//-----------------------------------------------------------------
//##ModelId=3FA1610E0343
PM_BbThresholdData::PM_BbThresholdData(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(dummy, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610E0346
PM_BbThresholdData::~PM_BbThresholdData()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3FA1610E0348
void PM_BbThresholdData::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeData::PM_LOSS].UnsignedValue   = PM_MAX_THRES_LOSS_15M;
    myThresholdArray[PM_TypeData::PM_CV].UnsignedValue     = (CSPII_CardIF::GetInstance()->GetCardFamily() == TRN_FAM) ? 
                                                             PM_MAX_THRES_CV_15M_2_5G:
                                                             PM_MAX_THRES_CV_15M_10G;
    myThresholdArray[PM_TypeData::PM_SE].UnsignedValue     = PM_MAX_THRES_SE_15M;
    myThresholdArray[PM_TypeData::PM_SEFS].UnsignedValue   = PM_MAX_THRES_SEFS_15M;
    myThresholdArray[PM_TypeData::PM_SES].UnsignedValue    = PM_MAX_THRES_SES_15M;
    myThresholdArray[PM_TypeData::PM_ES].UnsignedValue     = PM_MAX_THRES_ES_15M;
    myThresholdArray[PM_TypeData::PM_SE_HIGH].UnsignedValue= PM_MAX_THRES_SE_15M;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
// Determine if 64bit threshold should be returned!
// NOTE: if high value is not used (e.g. ODU3 CV), it is zero(0).
//-----------------------------------------------------------------
CT_PM_64bit_ull PM_BbThresholdData::GetThreshold(CT_PM_Parameter theParameter) const
{
    if ( (theParameter == (CT_PM_Parameter)PM_TypeData::PM_SE) &&
         (myNumberOfParam > PM_TypeData::PM_SE_HIGH) )
    {
        CT_PM_64bit_ull aHighValue = myThresholdArray[PM_TypeData::PM_SE_HIGH].UnsignedValue;
        uint32 aLowValue  = myThresholdArray[PM_TypeData::PM_SE].UnsignedValue;
        return ( (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue );
    }
 
    return myThresholdArray[theParameter].UnsignedValue;
}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
//##ModelId=3FA1610E0352
ostream& PM_BbThresholdData::WriteObject( ostream& theStream )
{
    theStream 
        << FC_InsertVar( myThresholdArray[PM_TypeData::PM_LOSS].UnsignedValue   )
        << FC_InsertVar( myThresholdArray[PM_TypeData::PM_CV].UnsignedValue     )
        << FC_InsertVar( myThresholdArray[PM_TypeData::PM_SE].UnsignedValue     )
        << FC_InsertVar( myThresholdArray[PM_TypeData::PM_SEFS].UnsignedValue   )
        << FC_InsertVar( myThresholdArray[PM_TypeData::PM_SES].UnsignedValue    )
        << FC_InsertVar( myThresholdArray[PM_TypeData::PM_ES].UnsignedValue     )
        << FC_InsertVar( myThresholdArray[PM_TypeData::PM_SE_HIGH].UnsignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
//##ModelId=3FA1610E0355
istream& PM_BbThresholdData::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream 
        >> FC_ExtractVar( myThresholdArray[PM_TypeData::PM_LOSS].UnsignedValue   )
        >> FC_ExtractVar( myThresholdArray[PM_TypeData::PM_CV].UnsignedValue     )
        >> FC_ExtractVar( myThresholdArray[PM_TypeData::PM_SE].UnsignedValue     )
        >> FC_ExtractVar( myThresholdArray[PM_TypeData::PM_SEFS].UnsignedValue   )
        >> FC_ExtractVar( myThresholdArray[PM_TypeData::PM_SES].UnsignedValue    )
        >> FC_ExtractVar( myThresholdArray[PM_TypeData::PM_ES].UnsignedValue     )
        >> FC_ExtractVar( myThresholdArray[PM_TypeData::PM_SE_HIGH].UnsignedValue);

    return theStream;

}


//-----------------------------------------------------------------
//##ModelId=3FA16B810007
PM_BbThresholdData1Day::PM_BbThresholdData1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdData( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA16B81000A
PM_BbThresholdData1Day::~PM_BbThresholdData1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3FA16B81000C
void PM_BbThresholdData1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 1-day.
    myThresholdArray[PM_TypeData::PM_LOSS].UnsignedValue   = PM_MAX_THRES_LOSS_DAY;
    myThresholdArray[PM_TypeData::PM_CV].UnsignedValue     = (CSPII_CardIF::GetInstance()->GetCardFamily() == TRN_FAM) ? 
                                                             PM_MAX_THRES_CV_DAY_2_5G:
                                                             PM_MAX_THRES_CV_DAY_10G;
    myThresholdArray[PM_TypeData::PM_SE].UnsignedValue     = PM_MAX_THRES_SE_DAY;
    myThresholdArray[PM_TypeData::PM_SEFS].UnsignedValue   = PM_MAX_THRES_SEFS_DAY;
    myThresholdArray[PM_TypeData::PM_SES].UnsignedValue    = PM_MAX_THRES_SES_DAY;
    myThresholdArray[PM_TypeData::PM_ES].UnsignedValue     = PM_MAX_THRES_ES_DAY;
    myThresholdArray[PM_TypeData::PM_SE_HIGH].UnsignedValue= PM_MAX_THRES_SE_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
