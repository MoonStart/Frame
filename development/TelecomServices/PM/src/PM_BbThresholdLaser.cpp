/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   PM Configuration parameters class for Laser.
--------------------------------------------------------------------------*/

#include <cstring>
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <PM_Def.h>
#include <PM/PM_BbThresholdLaser.h>


const uint8 PM_LT_MIN = (PM_TypeLaser::PM_LT * 2);
const uint8 PM_LT_MAX = (PM_TypeLaser::PM_LT * 2) + 1;
const uint8 PM_LBC_MIN = (PM_TypeLaser::PM_LBC * 2);
const uint8 PM_LBC_MAX = (PM_TypeLaser::PM_LBC * 2) + 1;


//-----------------------------------------------------------------
//##ModelId=3C1F6F5603DA
PM_BbThresholdLaser::PM_BbThresholdLaser(uint32 dummy, uint32 dummy2 ):
    // Create a array for min and max values.
    PM_BbGaugeThreshold(PM_TypeLaser::PM_PARAM_NUM * 2, myThresholdArray, myThresholdChangedArray)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5603E5
PM_BbThresholdLaser::~PM_BbThresholdLaser()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C1F6F570006
void PM_BbThresholdLaser::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for 15-minutes.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_LT_MIN].SignedValue  = PM_LOW_MIN_THRES_LT_VALUE;
    myThresholdArray[PM_LT_MAX].SignedValue  = PM_HIGH_MAX_THRES_LT_VALUE;
    myThresholdArray[PM_LBC_MIN].SignedValue = PM_LOW_MIN_THRES_LBC_VALUE;
    myThresholdArray[PM_LBC_MAX].SignedValue = PM_HIGH_MAX_THRES_LBC_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}

//-----------------------------------------------------------------
//  Store the Configuration Parameters to the stream.
//##ModelId=3C1F6F57004D
ostream& PM_BbThresholdLaser::WriteObject( ostream& theStream )
{
     theStream << FC_InsertVar( myThresholdArray[PM_LT_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_LT_MAX].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_LBC_MIN].SignedValue)
               << FC_InsertVar( myThresholdArray[PM_LBC_MAX].SignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//  Read the Configuration Parameters from the stream.
//##ModelId=3C1F6F570060
istream& PM_BbThresholdLaser::ReadObject( istream& theStream )
{
    uint32 i = 0;


    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

    theStream  >> FC_ExtractVar( myThresholdArray[PM_LT_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_LT_MAX].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_LBC_MIN].SignedValue)
               >> FC_ExtractVar( myThresholdArray[PM_LBC_MAX].SignedValue);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5702B9
PM_BbThresholdLaser1Day::PM_BbThresholdLaser1Day(uint32 dummy, uint32 dummy2 ):
    PM_BbThresholdLaser( dummy, dummy2 )
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F5702C5
PM_BbThresholdLaser1Day::~PM_BbThresholdLaser1Day()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//  Reset all threshold values.
//##ModelId=3C1F6F5702CE
void PM_BbThresholdLaser1Day::Reset()
{
    uint32 i = 0;


    // Reset threshold with default valus for Day.
    // enum * 2 for max value and (enum * 2) + 1 for min value.
    myThresholdArray[PM_LT_MIN].SignedValue  = PM_LOW_MIN_THRES_LT_VALUE;
    myThresholdArray[PM_LT_MAX].SignedValue  = PM_HIGH_MAX_THRES_LT_VALUE;
    myThresholdArray[PM_LBC_MIN].SignedValue = PM_LOW_MIN_THRES_LBC_VALUE;
    myThresholdArray[PM_LBC_MAX].SignedValue = PM_HIGH_MAX_THRES_LBC_VALUE;

    // Reset change flag.
    for ( i=0; i<(myNumberOfParam); i++)
    {
        myThresholdChangedArray[i] = true;
    }

}
