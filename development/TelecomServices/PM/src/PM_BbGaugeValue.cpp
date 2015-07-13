/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     24 August, 1998 Jean-Francois Birtz.
 DESCRIPTION:   PM Parameter Gauge values class. Keeps and sets PM
                parameter gauge values.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include "../PM_BbGaugeValue.h"


//-----------------------------------------------------------------
//##ModelId=3E6E4CB801FE
PM_BbGaugeValue::PM_BbGaugeValue(uint32 theNumberOfParam, uint32 dummy):
    PM_BbValue(theNumberOfParam)
{
    if(myNumberOfParam != 0)
    {
        CreateMembers();
        Reset();
    }
    else
    {
        myMinTca    = NULL;
        myMaxValues = NULL;
        myMinValues = NULL;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB8021B
PM_BbGaugeValue::~PM_BbGaugeValue()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB80225
void PM_BbGaugeValue::Reset()
{
    if(myNumberOfParam != 0)
    {
        // Reset data to default values.
        ResetAll();
        GetIdf()->Reset();
        GetMinTca()->Reset();
        GetMaxTca()->Reset();
    }

    // Call base class reset.
    PM_BbValue::Reset();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB80239
void PM_BbGaugeValue::ResetAll(void)
{
    uint32 i;


    for (i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].SignedValue = 0;
        myMinValues[i].SignedValue =  6000;
        myMaxValues[i].SignedValue = -6000;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB80243
void PM_BbGaugeValue::ResetAll(const PM_BbValue &thePreviousValue)
{
    uint32 i;
    CT_PM_64BitValue prevCurValue;
    CT_PM_64BitValue prevMinValue;
    CT_PM_64BitValue prevMaxValue;

    for (i=0; i<myNumberOfParam; i++)
    {
        thePreviousValue.GetValues(i, prevCurValue, prevMinValue, prevMaxValue);

        // For gauges the current value used is the previous value
        // until a new value is read from hardware.
        myCurValues[i].SignedValue = (int32)prevCurValue.SignedValue;
        myMinValues[i].SignedValue = (int32)prevCurValue.SignedValue;
        myMaxValues[i].SignedValue = (int32)prevCurValue.SignedValue;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB80258
void PM_BbGaugeValue::ResetCurParam(CT_PM_Parameter theParameter)
{
    if((myNumberOfParam != 0) && (theParameter < myNumberOfParam))
    {
        // Reset value.
        myCurValues[theParameter].SignedValue = 0;
        // Reset minimum TCA.
        GetMinTca()->ResetTca(theParameter);
        // Reset maximum TCA.
        GetMaxTca()->ResetTca(theParameter);
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbGaugeValue::ResetCurParam()" );
    }
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB8026C
void PM_BbGaugeValue::ResetMinParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        myMinValues[theParameter].SignedValue =  6000;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbGaugeValue::ResetMinParam()" );
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB80281
void PM_BbGaugeValue::ResetMaxParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset maximum value.
        myMaxValues[theParameter].SignedValue = -6000;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbGaugeValue::ResetMaxParam()" );
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB802C6
FC_Stream& PM_BbGaugeValue::WriteObjectBinary( FC_Stream& theStream )
{
    // Call base class method.
    PM_BbValue::WriteObjectBinary(theStream);

    if(myNumberOfParam != 0)
    {
        // Write the registers max value section.
        theStream.write_array( (int32*)myMaxValues, myNumberOfParam );
        // Write the minimum TCA section.
        theStream << (*GetMinTca());
        // Write the registers min value section.
        theStream.write_array( (int32*)myMinValues, myNumberOfParam );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbGaugeValue::WriteObjectBinary()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB802E4
FC_Stream& PM_BbGaugeValue::ReadObjectBinary( FC_Stream& theStream )
{
    // Call base class method.
    PM_BbValue::ReadObjectBinary(theStream);

    if(myNumberOfParam != 0)
    {
        // Read the registers max value section.
        theStream.read_array( (int32*)myMaxValues, myNumberOfParam );
        // Read the minimum TCA section.
        theStream >> (*GetMinTca());
        // Read the registers min value section.
        theStream.read_array( (int32*)myMinValues, myNumberOfParam );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbGaugeValue::ReadObjectBinary()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB80295
ostream& PM_BbGaugeValue::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbValue::WriteObject(theStream);

    theStream << FC_InsertVar( *GetMinTca() );

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB802B2
istream& PM_BbGaugeValue::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbValue::ReadObject(theStream);

    theStream >> FC_ExtractVar( *GetMinTca() );

    return theStream;

}

//-----------------------------------------------------------------
PM_BbTca* PM_BbGaugeValue::GetMinTca()
{
    return myMinTca;

}

//-----------------------------------------------------------------
void PM_BbGaugeValue::GetValues(CT_PM_Parameter  theParameter,
                           CT_PM_64BitValue&        theValue,
                           CT_PM_64BitValue&        theMinValue,
                           CT_PM_64BitValue&        theMaxValue) const
{
    if((myNumberOfParam != 0) && (theParameter < myNumberOfParam))
    {
        theValue.SignedValue    = myCurValues[theParameter].SignedValue ;
        theMinValue.SignedValue = myMinValues[theParameter].SignedValue ;
        theMaxValue.SignedValue = myMaxValues[theParameter].SignedValue ;
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::GetValues()" );
    }

}

//-----------------------------------------------------------------
void PM_BbGaugeValue::SetValues(CT_PM_Parameter  theParameter,
                           CT_PM_64BitValue         theValue,
                           CT_PM_64BitValue         theMinValue,
                           CT_PM_64BitValue         theMaxValue)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        myCurValues[theParameter].SignedValue  = (int32)theValue.SignedValue ;
        myMinValues[theParameter].SignedValue  = (int32)theMinValue.SignedValue ;
        myMaxValues[theParameter].SignedValue  = (int32)theMaxValue.SignedValue ;
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::SetValues()" );
    }

}

//-----------------------------------------------------------------
PM_BbValue& PM_BbGaugeValue::operator=(PM_BbValue &theOtherValue)
{
    uint32 i;
    CT_PM_64BitValue otherCurValue;
    CT_PM_64BitValue otherMinValue;
    CT_PM_64BitValue otherMaxValue;
    const PM_BbGaugeValue &otherValue = dynamic_cast<PM_BbGaugeValue &>(const_cast<PM_BbValue &>(theOtherValue));

    if(otherValue.myNumberOfParam == 0)
        FC_THROW_ERROR(FC_SWError, "PM_BbGaugeValue::operator=");

    if(GetNumberOfParam() != otherValue.GetNumberOfParam())
    {
        DeleteMembersDeep();
        myNumberOfParam = otherValue.GetNumberOfParam();
        CreateMembersDeep();
    }

    // Set value section.
    for (i=0; i<myNumberOfParam; i++)
    {
        otherValue.GetValues(i, otherCurValue, otherMinValue, otherMaxValue);
        SetValues(i, otherCurValue, otherMinValue, otherMaxValue);
    }

    // Set IDF section.
    *myIdf = *(otherValue.myIdf);

    // Set minimum TCA section.
    *myMinTca = *(otherValue.myMinTca);

    // Set maximum TCA section.
    *myMaxTca = *(otherValue.myMaxTca);

    // Set Request Id.
    SetRequestId(otherValue.GetRequestId());

    // Set Start Time.
    SetStartTime(otherValue.GetStartTime());

    // Set End Time.
    SetEndTime(otherValue.GetEndTime());

    return *this;

}

//-----------------------------------------------------------------
bool PM_BbGaugeValue::operator==(PM_BbValue &theOtherValue)
{
    uint32 i;
    CT_PM_64BitValue otherCurValue;
    CT_PM_64BitValue otherMinValue;
    CT_PM_64BitValue otherMaxValue;
    CT_PM_64BitValue curValue;
    CT_PM_64BitValue minValue;
    CT_PM_64BitValue maxValue;
    const PM_BbGaugeValue &otherValue = dynamic_cast<PM_BbGaugeValue &>(const_cast<PM_BbValue &>(theOtherValue));

    if((otherValue.GetNumberOfParam() == 0) && (myNumberOfParam == 0) )
        FC_THROW_ERROR(FC_SWError, "PM_BbGaugeValue::operator==");

    // Compare number of parameter and
    // Compare the request ID.
    if((GetNumberOfParam() != otherValue.GetNumberOfParam()) ||
       (GetRequestId()     != otherValue.GetRequestId()))
    {
        return false;
    }

    // Compare the value section.
    for (i=0; i<myNumberOfParam; i++)
    {
        otherValue.GetValues(i, otherCurValue, otherMinValue, otherMaxValue);
        GetValues(i, curValue, minValue, maxValue);

        if ((curValue.SignedValue != otherCurValue.SignedValue) &&
            (minValue.SignedValue != otherMinValue.SignedValue) &&
            (maxValue.SignedValue != otherMaxValue.SignedValue) )
        {
            return false;
        }
    }

    // Compare the IDF section.
    if ( !( *myIdf == *(otherValue.myIdf) ) )
    {
        return false;
    }

    // Compare the minimum TCA section.
    if ( !( *myMinTca == *(otherValue.myMinTca) ) )
    {
        return false;
    }

    // Compare the maximum TCA section.
    if ( !(*myMaxTca == *(otherValue.myMaxTca) ) )
    {
        return false;
    }

    // Compare the start time.
    if ( !(GetStartTime() == otherValue.GetStartTime() ) )
    {
        return false;
    }

    // Compare the end time.
    if ( !(GetEndTime() == otherValue.GetEndTime() ) )
    {
        return false;
    }

    return true;

}

//-----------------------------------------------------------------
void PM_BbGaugeValue::CreateMembers()
{
    myMinTca = new PM_BbTca(myNumberOfParam);
    myMaxValues = new CT_PM_Value [myNumberOfParam];
    myMinValues = new CT_PM_Value [myNumberOfParam];
}

//-----------------------------------------------------------------
void PM_BbGaugeValue::CreateMembersDeep()
{
    // Create members of base class first
    PM_BbValue::CreateMembersDeep();

    CreateMembers();
}

//-----------------------------------------------------------------
void PM_BbGaugeValue::DeleteMembers()
{
    delete myMinTca;

    delete [] myMinValues;
    delete [] myMaxValues;

    myMinTca = NULL;
    myMaxValues = NULL;
    myMinValues = NULL;
}

//-----------------------------------------------------------------
void PM_BbGaugeValue::DeleteMembersDeep()
{
    DeleteMembers();

    // Delete members of base class last.
     PM_BbValue::DeleteMembersDeep();
}

//-----------------------------------------------------------------
void PM_BbGaugeValue::AllocateTca()
{
    myMinTca->AllocateEventData();

    PM_BbValue::AllocateTca();
}

