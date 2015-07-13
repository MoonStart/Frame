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
#include <PM/PM_BbThresholdHopNearEnd.h>


//-----------------------------------------------------------------
PM_BbThresholdHopNearEnd::PM_BbThresholdHopNearEnd(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(PM_TypeHopNearEnd::PM_PARAM_NUM, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdHopNearEnd::~PM_BbThresholdHopNearEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdHopNearEnd::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeHopNearEnd::PM_CV].UnsignedValue		= PM_MAX_THRES_CV_15M_STS1;
    myThresholdArray[PM_TypeHopNearEnd::PM_SES].UnsignedValue		= PM_MAX_THRES_SES_15M;
    myThresholdArray[PM_TypeHopNearEnd::PM_ES].UnsignedValue		= PM_MAX_THRES_ES_15M;
    myThresholdArray[PM_TypeHopNearEnd::PM_UAS].UnsignedValue		= PM_MAX_THRES_UAS_15M;
    myThresholdArray[PM_TypeHopNearEnd::PM_FC].UnsignedValue		= PM_MAX_THRES_FC_15M;
    myThresholdArray[PM_TypeHopNearEnd::PM_PJCSGEN].UnsignedValue	= PM_MAX_THRES_PJCSGEN_15M;
    myThresholdArray[PM_TypeHopNearEnd::PM_PJCSDET].UnsignedValue	= PM_MAX_THRES_PJCSDET_15M;
    myThresholdArray[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue	= PM_MAX_THRES_PJCSDIFF_15M;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdHopNearEnd::WriteObject( ostream& theStream )
{
    theStream 
        << FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_CV].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_SES].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_ES].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_UAS].UnsignedValue		)
        << FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_FC].UnsignedValue		)
		<< FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_PJCSGEN].UnsignedValue   )
		<< FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_PJCSDET].UnsignedValue   )
		<< FC_InsertVar(myThresholdArray[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue  );

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdHopNearEnd::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream 
        >> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_CV].UnsignedValue   	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_SES].UnsignedValue  	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_ES].UnsignedValue   	 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_UAS].UnsignedValue		 )
        >> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_FC].UnsignedValue		 )
		>> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_PJCSGEN].UnsignedValue   )
		>> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_PJCSDET].UnsignedValue   )
		>> FC_ExtractVar(myThresholdArray[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue  );

    return theStream;

}



//-----------------------------------------------------------------
PM_BbThresholdHopNearEnd1Day::PM_BbThresholdHopNearEnd1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdHopNearEnd( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdHopNearEnd1Day::~PM_BbThresholdHopNearEnd1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdHopNearEnd1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 1-day.
    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeHopNearEnd::PM_CV].UnsignedValue      	= PM_MAX_THRES_CV_DAY_STS1;
    myThresholdArray[PM_TypeHopNearEnd::PM_SES].UnsignedValue     	= PM_MAX_THRES_SES_DAY;
    myThresholdArray[PM_TypeHopNearEnd::PM_ES].UnsignedValue      	= PM_MAX_THRES_ES_DAY;
    myThresholdArray[PM_TypeHopNearEnd::PM_UAS].UnsignedValue     	= PM_MAX_THRES_UAS_DAY;
    myThresholdArray[PM_TypeHopNearEnd::PM_FC].UnsignedValue      	= PM_MAX_THRES_FC_DAY;
    myThresholdArray[PM_TypeHopNearEnd::PM_PJCSGEN].UnsignedValue	= PM_MAX_THRES_PJCSGEN_DAY;
    myThresholdArray[PM_TypeHopNearEnd::PM_PJCSDET].UnsignedValue	= PM_MAX_THRES_PJCSDET_DAY;
    myThresholdArray[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue	= PM_MAX_THRES_PJCDIFF_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
