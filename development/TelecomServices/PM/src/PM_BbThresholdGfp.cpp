/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004   Hemant Thakkar
 DESCRIPTION:   PM Configuration parameters class. Keep the config of PM.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdGfp.h>


//-----------------------------------------------------------------
PM_BbThresholdGfp::PM_BbThresholdGfp(uint32 dummy, uint32 dummy2 ):
    PM_BbCounterThreshold(PM_TypeGfp::PM_PARAM_NUM, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdGfp::~PM_BbThresholdGfp()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdGfp::Reset()
{
    uint32 i = 0;

    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeGfp::PM_10B_ERR].UnsignedValue    = PM_MAX_THRES_10B_ERR_15M;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
ostream& PM_BbThresholdGfp::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myThresholdArray[PM_TypeGfp::PM_10B_ERR].UnsignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
istream& PM_BbThresholdGfp::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream >> FC_ExtractVar(myThresholdArray[PM_TypeGfp::PM_10B_ERR].UnsignedValue);

    return theStream;

}



//-----------------------------------------------------------------
PM_BbThresholdGfp1Day::PM_BbThresholdGfp1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdGfp( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbThresholdGfp1Day::~PM_BbThresholdGfp1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
void PM_BbThresholdGfp1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 1-day.
    // Reset threshold with default valus for 15-minutes.
    myThresholdArray[PM_TypeGfp::PM_10B_ERR].UnsignedValue    = PM_MAX_THRES_10B_ERR_DAY;

    // Reset change flag.
    for ( i=0; i<myNumberOfParam; i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
