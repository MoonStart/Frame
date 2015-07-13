/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Counter threshold class.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <PM/PM_BbCounterThreshold.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4CBF02DA
PM_BbCounterThreshold::PM_BbCounterThreshold(uint32 theNumberOfParam, uint32 dummy):
    PM_BbThreshold(theNumberOfParam, dummy)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBF02EE
PM_BbCounterThreshold::PM_BbCounterThreshold(uint32         theNumberOfParam,
                                             CT_PM_Value*   theThresholdPtr,
                                             bool*          theThresholdChangedPtr):
    PM_BbThreshold(theNumberOfParam, theThresholdPtr, theThresholdChangedPtr)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBF0302
PM_BbCounterThreshold::~PM_BbCounterThreshold()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
bool PM_BbCounterThreshold::SetThreshold(CT_PM_Parameter theParameter, uint32 theValue )
{
    uint32 previousThreshold;
    bool retVal = false;

    // Take a snapshot of the previous threshold configuration.
    previousThreshold = myThreshold[theParameter].SignedValue;

    // Set the threshold to the new configuration.
    myThreshold[theParameter].SignedValue = theValue;

    // Check if threshold configuration is changing.
    if (previousThreshold != myThreshold[theParameter].SignedValue)
    {
        myThresholdChanged[theParameter] = true;
        retVal = true;
    }

    return retVal;
}

//-----------------------------------------------------------------
CT_PM_64bit_ull PM_BbCounterThreshold::GetThreshold(CT_PM_Parameter theParameter) const
{
    return myThreshold[theParameter].UnsignedValue;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBF0366
void PM_BbCounterThreshold::GetThreshold(CT_PM_Parameter theParameter, int32& theMinValue, int32& theMaxValue) const
{
    FC_THROW_ERROR(FC_SWError, "PM: this method is not supported in this layer");

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBF0334
void PM_BbCounterThreshold::SetThreshold(CT_PM_Parameter theParameter, int32 theMinValue, int32 theMaxValue)
{
    FC_THROW_ERROR(FC_SWError, "PM: this method is not supported in this layer");

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBF037B
bool PM_BbCounterThreshold::HasThresholdChanged(CT_PM_Parameter theParameter) const
{
    bool previousThresholdChanged;

    previousThresholdChanged = myThresholdChanged[theParameter];
    myThresholdChanged[theParameter] = false;
    return previousThresholdChanged;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBF03A2
void PM_BbCounterThreshold::HasThresholdChanged(CT_PM_Parameter theParameter, bool& theMinFlag, bool& theMaxFlag) const
{
    FC_THROW_ERROR(FC_SWError, "PM: this method is not supported in this layer");

}

//-----------------------------------------------------------------
//##ModelId=3FA1610801ED
FC_Stream& PM_BbCounterThreshold::ReadObjectBinary( FC_Stream& theStream )
{
    uint32 i = 0;
    uint32 previousThreshold;


    for ( i=0; i<myNumberOfParam; i++)
    {
        previousThreshold = myThreshold[i].UnsignedValue;

        theStream >> myThreshold[i].UnsignedValue;

        // Check if threshold configuration is changing.
        if (previousThreshold != myThreshold[i].UnsignedValue)
            myThresholdChanged[i] = true;
    }

    return theStream;

}
