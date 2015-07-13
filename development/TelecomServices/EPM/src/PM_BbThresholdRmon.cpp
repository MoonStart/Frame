/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     January 25, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Configuration parameters class. Keep the congig of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_Def.h>
#include <EPM/PM_BbThresholdRmon.h>


//-----------------------------------------------------------------
PM_BbThresholdRmonCounter::PM_BbThresholdRmonCounter(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(dummy, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdRmonCounter::~PM_BbThresholdRmonCounter()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdRmonCounter::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeRmonCounter::PM_DROP].UnsignedValue    = PM_MAX_THRES_DROP_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_PKT].UnsignedValue     = PM_MAX_THRES_PKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue   = PM_MAX_THRES_BCPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue   = PM_MAX_THRES_MCPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue   = PM_MAX_THRES_CRCAE_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_USPKT].UnsignedValue   = PM_MAX_THRES_USPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue   = PM_MAX_THRES_OSPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_FRAG].UnsignedValue    = PM_MAX_THRES_FRAG_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_JABR].UnsignedValue    = PM_MAX_THRES_JABR_15M;

    myThresholdArray[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue    = PM_MAX_THRES_DROP_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue     = PM_MAX_THRES_PKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue   = PM_MAX_THRES_BCPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue   = PM_MAX_THRES_MCPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue   = PM_MAX_THRES_CRCAE_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue   = PM_MAX_THRES_USPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue   = PM_MAX_THRES_OSPKT_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue   = PM_MAX_THRES_FRAG_15M;
    myThresholdArray[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue   = PM_MAX_THRES_JABR_15M;
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
CT_PM_64bit_ull PM_BbThresholdRmonCounter::GetThreshold(CT_PM_Parameter theParameter) const
{
    PM_TypeRmonCounter::PM_Param aLowParam  = PM_TypeRmonCounter::PM_PARAM_NUM;
    PM_TypeRmonCounter::PM_Param aHighParam = PM_TypeRmonCounter::PM_PARAM_NUM;

    switch ( theParameter )
    {
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_DROP: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_DROP_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_DROP;
                aHighParam = PM_TypeRmonCounter::PM_DROP_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_PKT: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_PKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_PKT;
                aHighParam = PM_TypeRmonCounter::PM_PKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_BCPKT: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_BCPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_BCPKT;
                aHighParam = PM_TypeRmonCounter::PM_BCPKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_MCPKT: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_MCPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_MCPKT;
                aHighParam = PM_TypeRmonCounter::PM_MCPKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_CRCAE: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_CRCAE_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_CRCAE;
                aHighParam = PM_TypeRmonCounter::PM_CRCAE_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_USPKT: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_USPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_USPKT;
                aHighParam = PM_TypeRmonCounter::PM_USPKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_OSPKT: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_OSPKT_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_OSPKT;
                aHighParam = PM_TypeRmonCounter::PM_OSPKT_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_FRAG: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_FRAG_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_FRAG;
                aHighParam = PM_TypeRmonCounter::PM_FRAG_HIGH;
            }
            break;
        case (CT_PM_Parameter) PM_TypeRmonCounter::PM_JABR: 
            if ( myNumberOfParam > PM_TypeRmonCounter::PM_JABR_HIGH )
            {
                aLowParam  = PM_TypeRmonCounter::PM_JABR;
                aHighParam = PM_TypeRmonCounter::PM_JABR_HIGH;
            }
            break;

        default:
            break;
    }

    if ( aLowParam != aHighParam ) // both defaulted to PM_PARAM_NUM
    {
        CT_PM_64bit_ull aHighValue = myThresholdArray[aHighParam].UnsignedValue;
                    uint32 aLowValue  = myThresholdArray[aLowParam ].UnsignedValue;
        return ( (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue );
    }
 
    return myThresholdArray[theParameter].UnsignedValue;
}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdRmonCounter::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_DROP].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_PKT].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_USPKT].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_FRAG].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_JABR].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue);
    return theStream;
}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdRmonCounter::ReadObject( istream& theStream )
{
    uint32 i = 0;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_DROP].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_PKT].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_USPKT].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_FRAG].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_JABR].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue);
    return theStream;
}

//-----------------------------------------------------------------
PM_BbThresholdRmonCounter1Day::PM_BbThresholdRmonCounter1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdRmonCounter( dummy, dummy2 )
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdRmonCounter1Day::~PM_BbThresholdRmonCounter1Day()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdRmonCounter1Day::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 1-day.
    myThresholdArray[PM_TypeRmonCounter::PM_DROP].UnsignedValue    = PM_MAX_THRES_DROP_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_PKT].UnsignedValue     = PM_MAX_THRES_PKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_BCPKT].UnsignedValue   = PM_MAX_THRES_BCPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_MCPKT].UnsignedValue   = PM_MAX_THRES_MCPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_CRCAE].UnsignedValue   = PM_MAX_THRES_CRCAE_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_USPKT].UnsignedValue   = PM_MAX_THRES_USPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_OSPKT].UnsignedValue   = PM_MAX_THRES_OSPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_FRAG].UnsignedValue    = PM_MAX_THRES_FRAG_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_JABR].UnsignedValue    = PM_MAX_THRES_JABR_DAY;

    myThresholdArray[PM_TypeRmonCounter::PM_DROP_HIGH].UnsignedValue    = PM_MAX_THRES_DROP_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_PKT_HIGH].UnsignedValue     = PM_MAX_THRES_PKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_BCPKT_HIGH].UnsignedValue   = PM_MAX_THRES_BCPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_MCPKT_HIGH].UnsignedValue   = PM_MAX_THRES_MCPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_CRCAE_HIGH].UnsignedValue   = PM_MAX_THRES_CRCAE_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_USPKT_HIGH].UnsignedValue   = PM_MAX_THRES_USPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_OSPKT_HIGH].UnsignedValue   = PM_MAX_THRES_OSPKT_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_FRAG_HIGH].UnsignedValue   = PM_MAX_THRES_FRAG_DAY;
    myThresholdArray[PM_TypeRmonCounter::PM_JABR_HIGH].UnsignedValue   = PM_MAX_THRES_JABR_DAY;
    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }
}

const uint8 PM_UTIL_MIN = (PM_TypeRmonGauge::PM_UTIL * 2);
const uint8 PM_UTIL_MAX = (PM_TypeRmonGauge::PM_UTIL * 2) + 1;


//-----------------------------------------------------------------
PM_BbThresholdRmonGauge::PM_BbThresholdRmonGauge(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeRmonGauge::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdRmonGauge::~PM_BbThresholdRmonGauge()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdRmonGauge::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 15-minutes.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_UTIL_MIN].SignedValue  = PM_LOW_MIN_THRES_UTIL_VALUE;
    myThresholdArray[PM_UTIL_MAX].SignedValue  = PM_HIGH_MAX_THRES_UTIL_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }
}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdRmonGauge::WriteObject( ostream& theStream )
{
     theStream << FC_InsertVar( myThresholdArray[PM_UTIL_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_UTIL_MAX].SignedValue);

    return theStream;
}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdRmonGauge::ReadObject( istream& theStream )
{
    uint32 i = 0;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream  >> FC_ExtractVar( myThresholdArray[PM_UTIL_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_UTIL_MAX].SignedValue);

    return theStream;
}

//-----------------------------------------------------------------
PM_BbThresholdRmonGauge1Day::PM_BbThresholdRmonGauge1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdRmonGauge( dummy, dummy2 )
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdRmonGauge1Day::~PM_BbThresholdRmonGauge1Day()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdRmonGauge1Day::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for Day.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_UTIL_MIN].SignedValue  = PM_LOW_MIN_THRES_UTIL_VALUE;
    myThresholdArray[PM_UTIL_MAX].SignedValue  = PM_HIGH_MAX_THRES_UTIL_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }
}
