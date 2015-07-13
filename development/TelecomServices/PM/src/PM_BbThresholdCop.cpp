/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   PM Configuration parameters class for Optical Channel layer.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdCop.h>


const uint8 PM_COP_MIN = (PM_TypeCop::PM_COP * 2);
const uint8 PM_COP_MAX = (PM_TypeCop::PM_COP * 2) + 1;


//-----------------------------------------------------------------
//##ModelId=3C1F6F520082
PM_BbThresholdCop::PM_BbThresholdCop(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeCop::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F52008D
PM_BbThresholdCop::~PM_BbThresholdCop()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C1F6F520096
void PM_BbThresholdCop::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 15-minutes.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_COP_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_COP_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
//##ModelId=3C1F6F5200E5
ostream& PM_BbThresholdCop::WriteObject( ostream& theStream )
{
     theStream << FC_InsertVar( myThresholdArray[PM_COP_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_COP_MAX].SignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
//##ModelId=3C1F6F5200F0
istream& PM_BbThresholdCop::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream  >> FC_ExtractVar( myThresholdArray[PM_COP_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_COP_MAX].SignedValue);

    return theStream;

}




//-----------------------------------------------------------------
//##ModelId=3C1F6F5202C6
PM_BbThresholdCop1Day::PM_BbThresholdCop1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdCop( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5202D1
PM_BbThresholdCop1Day::~PM_BbThresholdCop1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C1F6F5202DB
void PM_BbThresholdCop1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for Day.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_COP_MIN].SignedValue = PM_LOW_MIN_THRES_POWER_VALUE;
    myThresholdArray[PM_COP_MAX].SignedValue = PM_HIGH_MAX_THRES_POWER_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
