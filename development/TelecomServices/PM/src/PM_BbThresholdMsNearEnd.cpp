/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     16 February 2004   Hemant Thakkar
 DESCRIPTION:   PM Configuration parameters class. Keep the config of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdMsNearEnd.h>


//-----------------------------------------------------------------
PM_BbThresholdMsNearEnd::PM_BbThresholdMsNearEnd(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(PM_TypeMsNearEnd::PM_PARAM_NUM, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdMsNearEnd::~PM_BbThresholdMsNearEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdMsNearEnd::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeMsNearEnd::PM_AISS].UnsignedValue    = PM_MAX_THRES_AISS_15M;
    myThresholdArray[PM_TypeMsNearEnd::PM_CV].UnsignedValue      = PM_MAX_THRES_CV_15M_2_5G;
    myThresholdArray[PM_TypeMsNearEnd::PM_SES].UnsignedValue     = PM_MAX_THRES_SES_15M;
    myThresholdArray[PM_TypeMsNearEnd::PM_ES].UnsignedValue      = PM_MAX_THRES_ES_15M;
    myThresholdArray[PM_TypeMsNearEnd::PM_UAS].UnsignedValue     = PM_MAX_THRES_UAS_15M;
    myThresholdArray[PM_TypeMsNearEnd::PM_FC].UnsignedValue      = PM_MAX_THRES_FC_15M;
    myThresholdArray[PM_TypeMsNearEnd::PM_PSC].UnsignedValue     = PM_MAX_THRES_PSC_15M;
    myThresholdArray[PM_TypeMsNearEnd::PM_PSD].UnsignedValue     = PM_MAX_THRES_PSD_15M;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdMsNearEnd::WriteObject( ostream& theStream )
{
    theStream 
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_CV].UnsignedValue   )
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_SES].UnsignedValue  )
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_ES].UnsignedValue   )
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_UAS].UnsignedValue )
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_AISS].UnsignedValue   )
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_FC].UnsignedValue   )
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_PSC].UnsignedValue  )
        << FC_InsertVar(myThresholdArray[PM_TypeMsNearEnd::PM_PSD].UnsignedValue  );

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdMsNearEnd::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream 
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_CV].UnsignedValue   )
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_SES].UnsignedValue  )
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_ES].UnsignedValue   )
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_UAS].UnsignedValue )
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_AISS].UnsignedValue   )
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_FC].UnsignedValue   )
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_PSC].UnsignedValue  )
        >> FC_ExtractVar(myThresholdArray[PM_TypeMsNearEnd::PM_PSD].UnsignedValue  );

    return theStream;

}



//-----------------------------------------------------------------
PM_BbThresholdMsNearEnd1Day::PM_BbThresholdMsNearEnd1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdMsNearEnd( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdMsNearEnd1Day::~PM_BbThresholdMsNearEnd1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdMsNearEnd1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 1-day.
    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeMsNearEnd::PM_AISS].UnsignedValue    = PM_MAX_THRES_AISS_DAY;
    myThresholdArray[PM_TypeMsNearEnd::PM_CV].UnsignedValue      = PM_MAX_THRES_CV_DAY_2_5G;
    myThresholdArray[PM_TypeMsNearEnd::PM_SES].UnsignedValue     = PM_MAX_THRES_SES_DAY;
    myThresholdArray[PM_TypeMsNearEnd::PM_ES].UnsignedValue      = PM_MAX_THRES_ES_DAY;
    myThresholdArray[PM_TypeMsNearEnd::PM_UAS].UnsignedValue     = PM_MAX_THRES_UAS_DAY;
    myThresholdArray[PM_TypeMsNearEnd::PM_FC].UnsignedValue      = PM_MAX_THRES_FC_DAY;
    myThresholdArray[PM_TypeMsNearEnd::PM_PSC].UnsignedValue     = PM_MAX_THRES_PSC_DAY;
    myThresholdArray[PM_TypeMsNearEnd::PM_PSD].UnsignedValue     = PM_MAX_THRES_PSD_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
