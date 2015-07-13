/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     August 15, 2002 Sebastien Cossette.
 DESCRIPTION:   PM Parameter values class. Keeps and set PM parameter values.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbCounterValue.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4CBE00C7
PM_BbCounterValue::PM_BbCounterValue(uint32 numberOfParam, uint32 dummy1):
    PM_BbValue(numberOfParam)
{
    Reset();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBE00DB
PM_BbCounterValue::~PM_BbCounterValue()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBE00E5
void PM_BbCounterValue::Reset()
{

    if(myNumberOfParam != 0)
    {
        // Reset data to default values.
        ResetAll();
        GetIdf()->Reset();
        GetMaxTca()->Reset();
    }

    // Call base class reset.
    PM_BbValue::Reset();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBE00EE
void PM_BbCounterValue::ResetAll(void)
{
    uint32 i;
    CT_PM_64BitValue unionValue;
    unionValue.UnsignedValue = 0;

    for (i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].UnsignedValue = 0;
        SetValue(i, unionValue);
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBE010C
void PM_BbCounterValue::ResetAll(const PM_BbValue &thePreviousValue)
{
    ResetAll();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBE0117
void PM_BbCounterValue::ResetCurParam(CT_PM_Parameter theParameter)
{
    if((myNumberOfParam != 0) && (theParameter < myNumberOfParam))
    {
        // Reset value.
        myCurValues[theParameter].UnsignedValue = 0;
        // Reset maximum TCA.
        GetMaxTca()->ResetTca(theParameter);
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);

        // For 64bit value, set high 32 bit to zero, t71mr00217518
        CT_PM_64BitValue unionValue;
        unionValue.UnsignedValue = 0;
        SetValue(theParameter, unionValue);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbCounterValue::ResetCurParam()" );
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBE0166
void PM_BbCounterValue::GetValues(CT_PM_Parameter   theParameter,
                                  CT_PM_Value&      theValue,
                                  CT_PM_Value&      theMinValue,
                                  CT_PM_Value&      theMaxValue) const
{
    if((myNumberOfParam != 0) && (theParameter < myNumberOfParam))
    {
        theValue.SignedValue    = myCurValues[theParameter].SignedValue ;
        theMinValue.SignedValue = 0 ;
        theMaxValue.SignedValue = myCurValues[theParameter].SignedValue ;
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbCounterValue::GetValues()" );
    }

}
