/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     12 December, 2001 Sebastien Cossette.
 DESCRIPTION:   PM Configuration parameters class for Optical layer.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdOpt.h>


const uint8 PM_OPR_MIN = (PM_TypeOpt::PM_OPR * 2);
const uint8 PM_OPR_MAX = (PM_TypeOpt::PM_OPR * 2) + 1;
const uint8 PM_OPT_MIN = (PM_TypeOpt::PM_OPT * 2);
const uint8 PM_OPT_MAX = (PM_TypeOpt::PM_OPT * 2) + 1;
const uint8 PM_DGD_MIN = (PM_TypeOpt::PM_DGD * 2);
const uint8 PM_DGD_MAX = (PM_TypeOpt::PM_DGD * 2) + 1;
const uint8 PM_CD_MIN  = (PM_TypeOpt::PM_CD  * 2);
const uint8 PM_CD_MAX  = (PM_TypeOpt::PM_CD  * 2) + 1;
const uint8 PM_OSNR_MIN= (PM_TypeOpt::PM_OSNR* 2);
const uint8 PM_OSNR_MAX= (PM_TypeOpt::PM_OSNR* 2) + 1;

//-----------------------------------------------------------------
//##ModelId=3C501626027C
PM_BbThresholdOpt::PM_BbThresholdOpt(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeOpt::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C501626028E
PM_BbThresholdOpt::~PM_BbThresholdOpt()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C5016260290
void PM_BbThresholdOpt::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 15-minutes.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_OPR_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPR_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;
    myThresholdArray[PM_DGD_MIN].SignedValue = PM_LOW_MIN_THRES_DGD_VALUE;
    myThresholdArray[PM_DGD_MAX].SignedValue = PM_HIGH_MAX_THRES_DGD_VALUE;
    myThresholdArray[PM_CD_MIN].SignedValue  = PM_LOW_MIN_THRES_CD_VALUE;
    myThresholdArray[PM_CD_MAX].SignedValue  = PM_HIGH_MAX_THRES_CD_VALUE;
    myThresholdArray[PM_OSNR_MIN].SignedValue= PM_LOW_MIN_THRES_OSNR_VALUE;
    myThresholdArray[PM_OSNR_MAX].SignedValue= PM_HIGH_MAX_THRES_OSNR_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
//##ModelId=3C50162602D5
ostream& PM_BbThresholdOpt::WriteObject( ostream& theStream )
{
    char mTA_OPR_MINbuf[80];
    char mTA_OPR_MAXbuf[80];
    char mTA_OPT_MINbuf[80];
    char mTA_OPT_MAXbuf[80];
    char mTA_DGD_MINbuf[80];
    char mTA_DGD_MAXbuf[80];
    char mTA_CD_MINbuf[80];
    char mTA_CD_MAXbuf[80];
    char mTA_OSNR_MINbuf[80];
    char mTA_OSNR_MAXbuf[80];

    sprintf(mTA_OPR_MINbuf, "%d", myThresholdArray[PM_OPR_MIN].SignedValue);
    sprintf(mTA_OPR_MAXbuf, "%d", myThresholdArray[PM_OPR_MAX].SignedValue);
    sprintf(mTA_OPT_MINbuf, "%d", myThresholdArray[PM_OPT_MIN].SignedValue);
    sprintf(mTA_OPT_MAXbuf, "%d", myThresholdArray[PM_OPT_MAX].SignedValue);
    sprintf(mTA_DGD_MINbuf, "%d", myThresholdArray[PM_DGD_MIN].SignedValue);
    sprintf(mTA_DGD_MAXbuf, "%d", myThresholdArray[PM_DGD_MAX].SignedValue);
    sprintf(mTA_CD_MINbuf,  "%d", myThresholdArray[PM_CD_MIN].SignedValue);
    sprintf(mTA_CD_MAXbuf,  "%d", myThresholdArray[PM_CD_MAX].SignedValue);
    sprintf(mTA_OSNR_MINbuf,"%d", myThresholdArray[PM_OSNR_MIN].SignedValue);
    sprintf(mTA_OSNR_MAXbuf,"%d", myThresholdArray[PM_OSNR_MAX].SignedValue);

    fc_cout << "" << endl;
    fc_cout << "--------------------------------------------------------------" << endl;
    fc_cout << " myThresholdArray OPR MIN = " << mTA_OPR_MINbuf << endl;
    fc_cout << " myThresholdArray OPR MAX = " << mTA_OPR_MAXbuf << endl;
    fc_cout << " myThresholdArray OPT MIN = " << mTA_OPT_MINbuf << endl;
    fc_cout << " myThresholdArray OPT MAX = " << mTA_OPT_MAXbuf << endl;
    fc_cout << " myThresholdArray DGD MIN = " << mTA_DGD_MINbuf << endl;
    fc_cout << " myThresholdArray DGD MAX = " << mTA_DGD_MAXbuf << endl;
    fc_cout << " myThresholdArray CD MIN  = " << mTA_CD_MINbuf  << endl;
    fc_cout << " myThresholdArray CD MAX  = " << mTA_CD_MAXbuf  << endl;
    fc_cout << " myThresholdArray OSNR MIN= " << mTA_OSNR_MINbuf<< endl;
    fc_cout << " myThresholdArray OSNR MAX= " << mTA_OSNR_MAXbuf<< endl;
    fc_cout << "--------------------------------------------------------------" << endl;
    fc_cout << "" << endl;

    //------------------------------------------------------------------------

     theStream << FC_InsertVar( myThresholdArray[PM_OPR_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OPR_MAX].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OPT_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OPT_MAX].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_DGD_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_DGD_MAX].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_CD_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_CD_MAX].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OSNR_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OSNR_MAX].SignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
//##ModelId=3C50162602DF
istream& PM_BbThresholdOpt::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream  >> FC_ExtractVar( myThresholdArray[PM_OPR_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_OPR_MAX].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_OPT_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_OPT_MAX].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_DGD_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_DGD_MAX].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_CD_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_CD_MAX].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_OSNR_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_OSNR_MAX].SignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C50162700D8
PM_BbThresholdOpt1Day::PM_BbThresholdOpt1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdOpt( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C50162700EB
PM_BbThresholdOpt1Day::~PM_BbThresholdOpt1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C50162700ED
void PM_BbThresholdOpt1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for Day.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_OPR_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPR_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;
    myThresholdArray[PM_DGD_MIN].SignedValue = PM_LOW_MIN_THRES_DGD_VALUE;
    myThresholdArray[PM_DGD_MAX].SignedValue = PM_HIGH_MAX_THRES_DGD_VALUE;
    myThresholdArray[PM_CD_MIN].SignedValue  = PM_LOW_MIN_THRES_CD_VALUE;
    myThresholdArray[PM_CD_MAX].SignedValue  = PM_HIGH_MAX_THRES_CD_VALUE;
    myThresholdArray[PM_OSNR_MIN].SignedValue= PM_LOW_MIN_THRES_OSNR_VALUE;
    myThresholdArray[PM_OSNR_MAX].SignedValue= PM_HIGH_MAX_THRES_OSNR_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}


PM_BbThresholdOptCounter::PM_BbThresholdOptCounter(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(dummy, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdOptCounter::~PM_BbThresholdOptCounter()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOptCounter::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeOptCounter::PM_PSC].UnsignedValue   = PM_MAX_THRES_PSC_15M;
    myThresholdArray[PM_TypeOptCounter::PM_PSD].UnsignedValue   = PM_MAX_THRES_PSD_15M;
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
//CT_PM_64bit_ull PM_BbThresholdOpt::GetThreshold(CT_PM_Parameter theParameter) const
//{
//    PM_TypeOpt::PM_Param aLowParam  = PM_TypeOpt::PM_PARAM_NUM;
//    PM_TypeOpt::PM_Param aHighParam = PM_TypeOpt::PM_PARAM_NUM;
//
//    switch ( theParameter )
//    {
//        case (CT_PM_Parameter) PM_TypeOpt::PM_PSC: 
//            if ( myNumberOfParam > PM_TypeOpt::PM_DROP_HIGH )
//            {
//                aLowParam  = PM_TypeOpt::PM_DROP;
//                aHighParam = PM_TypeOpt::PM_DROP_HIGH;
//            }
//            break;
//        case (CT_PM_Parameter) PM_TypeOpt::PM_PKT: 
//            if ( myNumberOfParam > PM_TypeOpt::PM_PKT_HIGH )
//            {
//                aLowParam  = PM_TypeOpt::PM_PKT;
//                aHighParam = PM_TypeOpt::PM_PKT_HIGH;
//            }
//            break;
//
//        default:
//            break;
//    }
//
//    if ( aLowParam != aHighParam ) // both defaulted to PM_PARAM_NUM
//    {
//        CT_PM_64bit_ull aHighValue = myThresholdArray[aHighParam].UnsignedValue;
//                    uint32 aLowValue  = myThresholdArray[aLowParam ].UnsignedValue;
//        return ( (aHighValue * CT_PMA_HIGH_ORDER_BYTES_MULTIPLIER) + aLowValue );
//    }
// 
//    return myThresholdArray[theParameter].UnsignedValue;
//}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdOptCounter::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar( myThresholdArray[PM_TypeOptCounter::PM_PSC].UnsignedValue)
              << FC_InsertVar( myThresholdArray[PM_TypeOptCounter::PM_PSD].UnsignedValue);

    return theStream;
}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdOptCounter::ReadObject( istream& theStream )
{
    uint32 i = 0;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream >> FC_ExtractVar( myThresholdArray[PM_TypeOptCounter::PM_PSC].UnsignedValue)
              >> FC_ExtractVar( myThresholdArray[PM_TypeOptCounter::PM_PSD].UnsignedValue);
    return theStream;
}

//-----------------------------------------------------------------
PM_BbThresholdOptCounter1Day::PM_BbThresholdOptCounter1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdOptCounter( dummy, dummy2 )
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
PM_BbThresholdOptCounter1Day::~PM_BbThresholdOptCounter1Day()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdOptCounter1Day::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 1-day.
    myThresholdArray[PM_TypeOptCounter::PM_PSC].UnsignedValue    = PM_MAX_THRES_PSC_DAY;
    myThresholdArray[PM_TypeOptCounter::PM_PSD].UnsignedValue    = PM_MAX_THRES_PSD_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }
}
