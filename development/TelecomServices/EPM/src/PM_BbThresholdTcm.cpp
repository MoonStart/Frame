/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     7 Oct 2010   Larry Wolfrum
 DESCRIPTION:   PM Configuration parameters class. Keep the config of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <PM/PM_Def.h>
#include <EPM/PM_BbThresholdTcm.h>


//-----------------------------------------------------------------
PM_BbThresholdTcm::PM_BbThresholdTcm(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(dummy, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdTcm::~PM_BbThresholdTcm()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdTcm::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeTcm::PM_CV].UnsignedValue		= PM_MAX_THRES_CV_15M_TCM;
    myThresholdArray[PM_TypeTcm::PM_ES].UnsignedValue		= PM_MAX_THRES_ES_15M;
    myThresholdArray[PM_TypeTcm::PM_SES].UnsignedValue		= PM_MAX_THRES_SES_15M;
    myThresholdArray[PM_TypeTcm::PM_UAS].UnsignedValue		= PM_MAX_THRES_UAS_15M;
    myThresholdArray[PM_TypeTcm::PM_CV_HIGH].UnsignedValue	= PM_MAX_THRES_CV_15M_TCM;

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
CT_PM_64bit_ull PM_BbThresholdTcm::GetThreshold(CT_PM_Parameter theParameter) const
{
    if ( (theParameter == (CT_PM_Parameter)PM_TypeTcm::PM_CV) &&
         (myNumberOfParam > PM_TypeTcm::PM_CV_HIGH) )
    {
        unsigned long long aHighValue = myThresholdArray[PM_TypeTcm::PM_CV_HIGH].UnsignedValue;
                    uint32 aLowValue  = myThresholdArray[PM_TypeTcm::PM_CV].UnsignedValue;
        return ( (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue );
    }

    return myThresholdArray[theParameter].UnsignedValue;
}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdTcm::WriteObject( ostream& theStream )
{
    theStream 
        << FC_InsertVar(myThresholdArray[PM_TypeTcm::PM_CV].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeTcm::PM_CV_HIGH].UnsignedValue	)
        << FC_InsertVar(myThresholdArray[PM_TypeTcm::PM_ES].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeTcm::PM_SES].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeTcm::PM_UAS].UnsignedValue		);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdTcm::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream 
        >> FC_ExtractVar(myThresholdArray[PM_TypeTcm::PM_CV].UnsignedValue   	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeTcm::PM_CV_HIGH].UnsignedValue	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeTcm::PM_ES].UnsignedValue   	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeTcm::PM_SES].UnsignedValue  	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeTcm::PM_UAS].UnsignedValue		 );

    return theStream;

}



//-----------------------------------------------------------------
PM_BbThresholdTcm1Day::PM_BbThresholdTcm1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdTcm( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdTcm1Day::~PM_BbThresholdTcm1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdTcm1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 1-day.
    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeTcm::PM_CV].UnsignedValue      	= PM_MAX_THRES_CV_DAY_TCM;
    myThresholdArray[PM_TypeTcm::PM_CV_HIGH].UnsignedValue 	= PM_MAX_THRES_CV_DAY_TCM;
    myThresholdArray[PM_TypeTcm::PM_ES].UnsignedValue      	= PM_MAX_THRES_ES_DAY;
    myThresholdArray[PM_TypeTcm::PM_SES].UnsignedValue     	= PM_MAX_THRES_SES_DAY;
    myThresholdArray[PM_TypeTcm::PM_UAS].UnsignedValue     	= PM_MAX_THRES_UAS_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

const uint8 PM_DELAY_MIN = (PM_TypeTcmGauge::PM_DELAY * 2);
const uint8 PM_DELAY_MAX = (PM_TypeTcmGauge::PM_DELAY * 2) + 1;

//-----------------------------------------------------------------
PM_BbThresholdTcmGauge::PM_BbThresholdTcmGauge(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeTcmGauge::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdTcmGauge::~PM_BbThresholdTcmGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdTcmGauge::Reset()
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
ostream& PM_BbThresholdTcmGauge::WriteObject( ostream& theStream )
{
     theStream << FC_InsertVar( myThresholdArray[PM_DELAY_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_DELAY_MAX].SignedValue);

    return theStream;
}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdTcmGauge::ReadObject( istream& theStream )
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
PM_BbThresholdTcmGauge1Day::PM_BbThresholdTcmGauge1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdTcmGauge( dummy, dummy2 )
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdTcmGauge1Day::~PM_BbThresholdTcmGauge1Day()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdTcmGauge1Day::Reset()
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
