/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     21 Oct 2009   Larry Wolfrum
 DESCRIPTION:   PM Configuration parameters class. Keep the config of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <PM/PM_Def.h>
#include <EPM/PM_BbThresholdOdu.h>


//-----------------------------------------------------------------
PM_BbThresholdOdu::PM_BbThresholdOdu(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(dummy, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdOdu::~PM_BbThresholdOdu()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOdu::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeOdu::PM_CV].UnsignedValue		= PM_MAX_THRES_CV_15M_ODU;
    myThresholdArray[PM_TypeOdu::PM_ES].UnsignedValue		= PM_MAX_THRES_ES_15M;
    myThresholdArray[PM_TypeOdu::PM_SES].UnsignedValue		= PM_MAX_THRES_SES_15M;
    myThresholdArray[PM_TypeOdu::PM_UAS].UnsignedValue		= PM_MAX_THRES_UAS_15M;
    myThresholdArray[PM_TypeOdu::PM_CV_HIGH].UnsignedValue	= PM_MAX_THRES_CV_15M_ODU;

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
CT_PM_64bit_ull PM_BbThresholdOdu::GetThreshold(CT_PM_Parameter theParameter) const
{
    if ( (theParameter == (CT_PM_Parameter)PM_TypeOdu::PM_CV) &&
         (myNumberOfParam > PM_TypeOdu::PM_CV_HIGH) )
    {
        unsigned long long aHighValue = myThresholdArray[PM_TypeOdu::PM_CV_HIGH].UnsignedValue;
                    uint32 aLowValue  = myThresholdArray[PM_TypeOdu::PM_CV].UnsignedValue;
        return ( (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue );
    }

    return myThresholdArray[theParameter].UnsignedValue;
}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdOdu::WriteObject( ostream& theStream )
{
    theStream 
        << FC_InsertVar(myThresholdArray[PM_TypeOdu::PM_CV].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeOdu::PM_CV_HIGH].UnsignedValue	)
        << FC_InsertVar(myThresholdArray[PM_TypeOdu::PM_ES].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeOdu::PM_SES].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeOdu::PM_UAS].UnsignedValue		);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdOdu::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream 
        >> FC_ExtractVar(myThresholdArray[PM_TypeOdu::PM_CV].UnsignedValue   	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeOdu::PM_CV_HIGH].UnsignedValue	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeOdu::PM_ES].UnsignedValue   	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeOdu::PM_SES].UnsignedValue  	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeOdu::PM_UAS].UnsignedValue		 );

    return theStream;

}

//-----------------------------------------------------------------
PM_BbThresholdOdu1Day::PM_BbThresholdOdu1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdOdu( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdOdu1Day::~PM_BbThresholdOdu1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOdu1Day::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 1-day.
    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeOdu::PM_CV].UnsignedValue      	= PM_MAX_THRES_CV_DAY_ODU;
    myThresholdArray[PM_TypeOdu::PM_ES].UnsignedValue      	= PM_MAX_THRES_ES_DAY;
    myThresholdArray[PM_TypeOdu::PM_SES].UnsignedValue     	= PM_MAX_THRES_SES_DAY;
    myThresholdArray[PM_TypeOdu::PM_UAS].UnsignedValue     	= PM_MAX_THRES_UAS_DAY;
    myThresholdArray[PM_TypeOdu::PM_CV_HIGH].UnsignedValue 	= PM_MAX_THRES_CV_DAY_ODU;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
 
const uint8 PM_DELAY_MIN = (PM_TypeOduGauge::PM_DELAY * 2);
const uint8 PM_DELAY_MAX = (PM_TypeOduGauge::PM_DELAY * 2) + 1;
 
//-----------------------------------------------------------------
PM_BbThresholdOduGauge::PM_BbThresholdOduGauge(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeOduGauge::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
PM_BbThresholdOduGauge::~PM_BbThresholdOduGauge()
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOduGauge::Reset()
{
    uint32 i = 0;
 
    // Reset threshold with default valus for 15-minutes.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_DELAY_MIN].SignedValue  = PM_LOW_MIN_THRES_DELAY_VALUE;
    myThresholdArray[PM_DELAY_MAX].SignedValue  = PM_HIGH_MAX_THRES_DELAY_VALUE;
 
    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }
}
 
//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdOduGauge::WriteObject( ostream& theStream )
{
     theStream << FC_InsertVar( myThresholdArray[PM_DELAY_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_DELAY_MAX].SignedValue);
 
    return theStream;
}
 
//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdOduGauge::ReadObject( istream& theStream )
{
    uint32 i = 0;
 
    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }
 
    theStream  >> FC_ExtractVar( myThresholdArray[PM_DELAY_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_DELAY_MAX].SignedValue);
 
    return theStream;
}
 
//-----------------------------------------------------------------
PM_BbThresholdOduGauge1Day::PM_BbThresholdOduGauge1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdOduGauge( dummy, dummy2 )
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
PM_BbThresholdOduGauge1Day::~PM_BbThresholdOduGauge1Day()
{
    // Nothing to do for now.
}
 
//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOduGauge1Day::Reset()
{
    uint32 i = 0;
 
    // Reset threshold with default valus for Day.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_DELAY_MIN].SignedValue  = PM_LOW_MIN_THRES_DELAY_VALUE;
    myThresholdArray[PM_DELAY_MAX].SignedValue  = PM_HIGH_MAX_THRES_DELAY_VALUE;
 
    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }
}
