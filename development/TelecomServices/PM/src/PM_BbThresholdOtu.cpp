/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Configuration parameters class. Keep the congig of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdOtu.h>
#include <CommonTypes/CT_Float32.h>

static const uint32 PM_LOW_MIN_THRES_BER_VALUE  = CT_Float32(0.0).GetValue();
static const uint32 PM_HIGH_MAX_THRES_BER_VALUE = CT_Float32(1.0E-4).GetValue();

//-----------------------------------------------------------------
//##ModelId=3C1F6F5C034D
PM_BbThresholdOtu::PM_BbThresholdOtu(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold( dummy, myThresholdArray, myThresholdChangedArray )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5C0360
PM_BbThresholdOtu::~PM_BbThresholdOtu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C1F6F5C0362
void PM_BbThresholdOtu::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeOtu::PM_BE].SignedValue    = PM_MAX_THRES_BE_15M;
    myThresholdArray[PM_TypeOtu::PM_BE_HIGH].UnsignedValue = PM_MAX_THRES_BE_15M;
    myThresholdArray[PM_TypeOtu::PM_UBE].SignedValue   = PM_MAX_THRES_UBE_15M;
    myThresholdArray[PM_TypeOtu::PM_PSC].UnsignedValue = PM_MAX_THRES_PSC_15M;
    myThresholdArray[PM_TypeOtu::PM_PSD].UnsignedValue = PM_MAX_THRES_PSD_15M;
    myThresholdArray[PM_TypeOtu::PM_CV].UnsignedValue  = PM_MAX_THRES_CV_15M_10G;
    myThresholdArray[PM_TypeOtu::PM_CV_HIGH].UnsignedValue = PM_MAX_THRES_CV_15M_10G;
    myThresholdArray[PM_TypeOtu::PM_ES].UnsignedValue  = PM_MAX_THRES_ES_15M;
    myThresholdArray[PM_TypeOtu::PM_SES].UnsignedValue = PM_MAX_THRES_SES_15M;
    myThresholdArray[PM_TypeOtu::PM_UAS].UnsignedValue = PM_MAX_THRES_UAS_15M;
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
CT_PM_64bit_ull PM_BbThresholdOtu::GetThreshold(CT_PM_Parameter theParameter) const
{
    if ( (theParameter == (CT_PM_Parameter)PM_TypeOtu::PM_CV) &&
         (myNumberOfParam > PM_TypeOtu::PM_CV_HIGH) )
    {
        CT_PM_64bit_ull aHighValue = myThresholdArray[PM_TypeOtu::PM_CV_HIGH].UnsignedValue;
                 uint32 aLowValue  = myThresholdArray[PM_TypeOtu::PM_CV].UnsignedValue;
        return ( (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue );
    }
    else if ( (theParameter == (CT_PM_Parameter)PM_TypeOtu::PM_BE) &&
              (myNumberOfParam > PM_TypeOtu::PM_BE_HIGH) )
    {
        CT_PM_64bit_ull aHighValue = myThresholdArray[PM_TypeOtu::PM_BE_HIGH].UnsignedValue;
                 uint32 aLowValue  = myThresholdArray[PM_TypeOtu::PM_BE].UnsignedValue;
        return ( (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue );
    }

    return myThresholdArray[theParameter].UnsignedValue;
}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
//##ModelId=3C1F6F5C036B
ostream& PM_BbThresholdOtu::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_BE].SignedValue )
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_BE_HIGH].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_UBE].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_PSC].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_PSD].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_CV].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_CV_HIGH].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_ES].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_SES].SignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOtu::PM_UAS].SignedValue);


    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
//##ModelId=3C1F6F5C037E
istream& PM_BbThresholdOtu::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_BE].SignedValue )
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_BE_HIGH].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_UBE].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_PSC].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_PSD].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_CV].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_CV_HIGH].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_ES].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_SES].SignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOtu::PM_UAS].SignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5D01F9
PM_BbThresholdOtu1Day::PM_BbThresholdOtu1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdOtu( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5D020D
PM_BbThresholdOtu1Day::~PM_BbThresholdOtu1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C1F6F5D020F
void PM_BbThresholdOtu1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 1-day.
    myThresholdArray[PM_TypeOtu::PM_BE].SignedValue    = PM_MAX_THRES_BE_DAY;
    myThresholdArray[PM_TypeOtu::PM_BE_HIGH].UnsignedValue  = PM_MAX_THRES_BE_DAY;
    myThresholdArray[PM_TypeOtu::PM_UBE].SignedValue   = PM_MAX_THRES_UBE_DAY;
    myThresholdArray[PM_TypeOtu::PM_PSC].UnsignedValue = PM_MAX_THRES_PSC_DAY;
    myThresholdArray[PM_TypeOtu::PM_PSD].UnsignedValue = PM_MAX_THRES_PSD_DAY;
    myThresholdArray[PM_TypeOtu::PM_CV].UnsignedValue  = PM_MAX_THRES_CV_DAY_10G;
    myThresholdArray[PM_TypeOtu::PM_CV_HIGH].UnsignedValue  = PM_MAX_THRES_CV_DAY_10G;
    myThresholdArray[PM_TypeOtu::PM_ES].UnsignedValue  = PM_MAX_THRES_ES_DAY;
    myThresholdArray[PM_TypeOtu::PM_SES].UnsignedValue = PM_MAX_THRES_SES_DAY;
    myThresholdArray[PM_TypeOtu::PM_UAS].UnsignedValue = PM_MAX_THRES_UAS_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}


const uint8 PM_BER_MIN = (PM_TypeOtuGauge::PM_BER * 2);
const uint8 PM_BER_MAX = (PM_TypeOtuGauge::PM_BER * 2) + 1;


//-----------------------------------------------------------------
PM_BbThresholdOtuGauge::PM_BbThresholdOtuGauge(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeOtuGauge::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdOtuGauge::~PM_BbThresholdOtuGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOtuGauge::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 15-minutes.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_BER_MIN].SignedValue  = PM_LOW_MIN_THRES_BER_VALUE;
    myThresholdArray[PM_BER_MAX].SignedValue  = PM_HIGH_MAX_THRES_BER_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }
}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdOtuGauge::WriteObject( ostream& theStream )
{
     theStream << FC_InsertVar( myThresholdArray[PM_BER_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_BER_MAX].SignedValue);

    return theStream;
}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdOtuGauge::ReadObject( istream& theStream )
{
    uint32 i = 0;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream  >> FC_ExtractVar( myThresholdArray[PM_BER_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_BER_MAX].SignedValue);

    return theStream;
}

//-----------------------------------------------------------------
PM_BbThresholdOtuGauge1Day::PM_BbThresholdOtuGauge1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdOtuGauge( dummy, dummy2 )
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdOtuGauge1Day::~PM_BbThresholdOtuGauge1Day()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOtuGauge1Day::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for Day.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_BER_MIN].SignedValue  = PM_LOW_MIN_THRES_BER_VALUE;
    myThresholdArray[PM_BER_MAX].SignedValue  = PM_HIGH_MAX_THRES_BER_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }
}
