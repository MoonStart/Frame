/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   PM Configuration parameters class for Oms layer.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdOms.h>


const uint8 PM_OPR_MIN = (PM_TypeOms::PM_OPR * 2);
const uint8 PM_OPR_MAX = (PM_TypeOms::PM_OPR * 2) + 1;
const uint8 PM_OPT_MIN = (PM_TypeOms::PM_OPT * 2);
const uint8 PM_OPT_MAX = (PM_TypeOms::PM_OPT * 2) + 1;


//-----------------------------------------------------------------
//##ModelId=3E6E4C9B015B
PM_BbThresholdOms::PM_BbThresholdOms(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeOms::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9B0170
PM_BbThresholdOms::~PM_BbThresholdOms()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3E6E4C9B0184
void PM_BbThresholdOms::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 15-minutes.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_OPR_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPR_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
//##ModelId=3E6E4C9B018F
ostream& PM_BbThresholdOms::WriteObject( ostream& theStream )
{
     theStream << FC_InsertVar( myThresholdArray[PM_OPR_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OPR_MAX].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OPT_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_OPT_MAX].SignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
//##ModelId=3E6E4C9B01AD
istream& PM_BbThresholdOms::ReadObject( istream& theStream )
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
               >> FC_ExtractVar( myThresholdArray[PM_OPT_MAX].SignedValue);

    return theStream;

}



//-----------------------------------------------------------------
//##ModelId=3E6E4C9C03DE
PM_BbThresholdOms1Day::PM_BbThresholdOms1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdOms( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C9D000A
PM_BbThresholdOms1Day::~PM_BbThresholdOms1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3E6E4C9D0014
void PM_BbThresholdOms1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for Day.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_OPR_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPR_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_OPT_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
