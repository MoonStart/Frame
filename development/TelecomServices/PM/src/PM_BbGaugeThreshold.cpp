/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Gauge Threshold class.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <PM/PM_BbGaugeThreshold.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4CB90386
PM_BbGaugeThreshold::PM_BbGaugeThreshold(uint32 theNumberOfParam, uint32 dummy):
    PM_BbThreshold(theNumberOfParam, dummy)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB90399
PM_BbGaugeThreshold::PM_BbGaugeThreshold(uint32         theNumberOfParam,
                                         CT_PM_Value*   theThresholdPtr,
                                         bool*          theThresholdChangedPtr):
    PM_BbThreshold(theNumberOfParam, theThresholdPtr, theThresholdChangedPtr)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB903AD
PM_BbGaugeThreshold::~PM_BbGaugeThreshold()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
bool PM_BbGaugeThreshold::SetThreshold(CT_PM_Parameter theParameter, uint32 theValue )
{
    FC_THROW_ERROR(FC_SWError, "PM: this method is not supported in this layer");
    return false;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBA000C
CT_PM_64bit_ull PM_BbGaugeThreshold::GetThreshold(CT_PM_Parameter theParameter) const
{
    FC_THROW_ERROR(FC_SWError, "PM: this method is not supported in this layer");

    return 0;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBA0020
void PM_BbGaugeThreshold::GetThreshold(CT_PM_Parameter theParameter,
                                       int32&          theMinValue,
                                       int32&          theMaxValue) const
{
    theMinValue = myThreshold[(theParameter * 2)].SignedValue;
    theMaxValue = myThreshold[(theParameter * 2) + 1].SignedValue;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB903D5
void PM_BbGaugeThreshold::SetThreshold(CT_PM_Parameter  theParameter,
                                       int32            theMinValue,
                                       int32            theMaxValue)
{
    int32 previousMinThreshold;
    int32 previousMaxThreshold;


    // Take a snapshot of the previous threshold configuration.
    previousMinThreshold = myThreshold[(theParameter * 2)].SignedValue;
    previousMaxThreshold = myThreshold[(theParameter * 2) + 1].SignedValue;

    // Set the threshold to the new configuration.
    myThreshold[(theParameter * 2)].SignedValue = theMinValue;
    myThreshold[(theParameter * 2) + 1].SignedValue = theMaxValue;

    // Check if threshold configuration is changing.
    if (previousMinThreshold != myThreshold[(theParameter * 2)].SignedValue)
        myThresholdChanged[(theParameter * 2)] = true;

    if (previousMaxThreshold != myThreshold[(theParameter * 2) + 1].SignedValue)
        myThresholdChanged[(theParameter * 2) + 1] = true;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBA0035
bool PM_BbGaugeThreshold::HasThresholdChanged(CT_PM_Parameter theParameter) const
{
    FC_THROW_ERROR(FC_SWError, "PM: this method is not supported in this layer");

    return false;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBA0052
void PM_BbGaugeThreshold::HasThresholdChanged(CT_PM_Parameter   theParameter,
                                              bool&             theMinFlag,
                                              bool&             theMaxFlag) const
{
    theMinFlag = myThresholdChanged[(theParameter * 2)];
    myThresholdChanged[(theParameter * 2)] = false;
    theMaxFlag = myThresholdChanged[(theParameter * 2) + 1];
    myThresholdChanged[(theParameter * 2) + 1] = false;

}

//-----------------------------------------------------------------
//##ModelId=3FA16107026A
FC_Stream& PM_BbGaugeThreshold::ReadObjectBinary( FC_Stream& theStream )
{
    uint32 i = 0;
    int32 previousThreshold;


    for ( i=0; i<myNumberOfParam; i++)
    {
        previousThreshold = myThreshold[i].SignedValue;

        theStream >> myThreshold[i].SignedValue;

        // Check if threshold configuration is changing.
        if (previousThreshold != myThreshold[i].SignedValue)
            myThresholdChanged[i] = true;
    }

    return theStream;

}

