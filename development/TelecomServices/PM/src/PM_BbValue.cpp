/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     24 August, 1998 Jean-Francois Birtz.
 DESCRIPTION:   PM Parameter values class. Keeps and sets PM
                parameter values.
--------------------------------------------------------------------------*/

#include "BaseClass/FC_TextStream.h"
#include "ErrorService/FC_Error.h"
#include "TimeService/FC_TimeService.h"
#include "PM_BbValue.h"
#include "PM_Def.h"
#include <EPM/PM_TypeOdu.h>
#include <PM/PM_TypeOtu.h>
#include <EPM/PM_TypeTcm.h>
#include <EPM/PM_BbValueOdu.h>
#include <PM/PM_BbValueOtu.h>
#include <EPM/PM_BbValueTcm.h>
#include <cstring>   // for strcpy


//-----------------------------------------------------------------
//##ModelId=3C1F6F6F03D6
PM_BbValue::PM_BbValue(uint32 theNumberOfParam, uint32 dummy):
    myNumberOfParam(theNumberOfParam),
    myStartTime(0),
    myEndTime(0),
    myRequestId(0),
    myUasParameterFlags(NULL)
{
    if(myNumberOfParam != 0)
    {
        CreateMembers();
        Reset();
    }
    else
    {
        myIdf       = NULL;
        myMaxTca    = NULL;
        myCurValues = NULL;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F700003
PM_BbValue::~PM_BbValue()
{
    DeleteMembers();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F70000C
void PM_BbValue::Reset()
{
    myRequestId = 0;
    myStartTime = 0;
    myEndTime = 0;

}

//-----------------------------------------------------------------
//##ModelId=3CBC723E00F5
void PM_BbValue::ResetAll(void)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F700036
void PM_BbValue::ResetAll(const PM_BbValue &thePreviousValue)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
void PM_BbValue::ResetAll(const uint32 theUtilization)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3C9255C00062
void PM_BbValue::ResetCurParam(CT_PM_Parameter theParameter)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA400A0
void PM_BbValue::ResetMinParam(CT_PM_Parameter theParameter)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA40168
void PM_BbValue::ResetMaxParam(CT_PM_Parameter theParameter)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3C9255BF0332
void PM_BbValue::GetValue(CT_PM_Parameter theParameter, CT_PM_64BitValue& theValue, bool useLowHigh64Bit)
{
    if ( useLowHigh64Bit && IsParam64BitValue( theParameter ) )
    {
        theValue = Get64BitValue( theParameter );
    }
    else
    {
        CT_PM_64BitValue a64BitValue;
        a64BitValue.UnsignedValue = myCurValues[theParameter].UnsignedValue;
        theValue = a64BitValue;
    }
}

//-----------------------------------------------------------------
//##ModelId=3C9255BF03C8
void PM_BbValue::SetValue(CT_PM_Parameter theParameter, CT_PM_64BitValue theValue)
{
    if ( IsParam64BitValue( theParameter ) )
    {
        Set64BitValue( theParameter, theValue );
    }
    else
    {
        CT_PM_Value aValue;
        aValue.UnsignedValue = (uint32)theValue.UnsignedValue;
        myCurValues[theParameter] = aValue;
    }
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F700017
void PM_BbValue::GetValues(CT_PM_Parameter  theParameter,
                           CT_PM_64BitValue&        theValue,
                           CT_PM_64BitValue&        theMinValue,
                           CT_PM_64BitValue&        theMaxValue) const
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F70002A
void PM_BbValue::SetValues(CT_PM_Parameter  theParameter,
                           CT_PM_64BitValue         theValue,
                           CT_PM_64BitValue         theMinValue,
                           CT_PM_64BitValue         theMaxValue)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F70005C
PM_BbValue& PM_BbValue::operator=(PM_BbValue &theOtherValue)
{
    uint32 i;
    CT_PM_64BitValue otherCurValue;

    if(theOtherValue.myNumberOfParam == 0)
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::operator=");

    if(GetNumberOfParam() != theOtherValue.GetNumberOfParam())
    {
        DeleteMembersDeep();
        myNumberOfParam = theOtherValue.GetNumberOfParam();
        CreateMembersDeep();
    }

    // Set value section.
    for (i=0; i<myNumberOfParam; i++)
    {
        theOtherValue.GetValue(i, otherCurValue);
        SetValue(i, otherCurValue);
    }

    // Set IDF section.
    *myIdf = *(theOtherValue.myIdf);

    // Set maximum TCA section.
    *myMaxTca = *(theOtherValue.myMaxTca);

    // Set Request Id.
    SetRequestId(theOtherValue.GetRequestId());

    // Set Start Time.
    SetStartTime(theOtherValue.GetStartTime());

    // Set End Time.
    SetEndTime(theOtherValue.GetEndTime());

    return *this;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F700048
bool PM_BbValue::operator==(PM_BbValue &theOtherValue)
{
    uint32 i;
    CT_PM_64BitValue otherCurValue;
    CT_PM_64BitValue curValue;

    if((theOtherValue.GetNumberOfParam() == 0) && (myNumberOfParam == 0) )
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::operator==");

    // Compare number of parameter and
    // Compare the request ID.
    if((GetNumberOfParam() != theOtherValue.GetNumberOfParam()) ||
       (GetRequestId()     != theOtherValue.GetRequestId()))
    {
        return false;
    }

    // Compare the value section.
    for (i=0; i<myNumberOfParam; i++)
    {
        theOtherValue.GetValue(i, otherCurValue);
        GetValue(i, curValue);

        if (curValue.SignedValue != otherCurValue.SignedValue)
        {
            return false;
        }
    }

    // Compare the IDF section.
    if ( !( *myIdf == *(theOtherValue.myIdf) ) )
    {
        return false;
    }

    // Compare the maximum TCA section.
    if ( !(*myMaxTca == *(theOtherValue.myMaxTca) ) )
    {
        return false;
    }

    // Compare the start time.
    if ( !(GetStartTime() == theOtherValue.GetStartTime() ) )
    {
        return false;
    }

    // Compare the end time.
    if ( !(GetEndTime() == theOtherValue.GetEndTime() ) )
    {
        return false;
    }

    return true;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7000E8
FC_Stream& PM_BbValue::WriteObjectBinary( FC_Stream& theStream )
{
    if(myNumberOfParam != 0)
    {
        // Write the period start time.
        myStartTime.WriteObjectBinary(theStream);
        // Write the period end time.
        myEndTime.WriteObjectBinary(theStream);
        // Write the IDF section.
        theStream << (*myIdf);
        // Write the request ID.
        theStream << myRequestId;
        // Write the registers value section.
        theStream.write_array((int32*)myCurValues, myNumberOfParam );
        // Write the TCA section.
        theStream << *myMaxTca;
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::WriteObjectBinary()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7000F3
FC_Stream& PM_BbValue::ReadObjectBinary( FC_Stream& theStream )
{
    if(myNumberOfParam != 0)
    {
        // Read the period start time.
        myStartTime.ReadObjectBinary(theStream);
        // Read the period end time.
        myEndTime.ReadObjectBinary(theStream);
        // Read the IDF section.
        theStream >> (*myIdf);
        // Read the request ID.
        theStream >> myRequestId;
        // Read the registers value section.
        theStream.read_array( (int32*)myCurValues, myNumberOfParam );
        // Read the TCA section.
        theStream >> *myMaxTca;
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::ReadObjectBinary()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7000B6
ostream& PM_BbValue::WriteObject( ostream& theStream )
{
    time_t startTime;
    time_t endTime;
    char    tmpBuff[30];
    struct  tm tmpTm;
    char    startTimeString[30];
    char    endTimeString[30];


    startTime = myStartTime.GetUTCTime();
    endTime = myEndTime.GetUTCTime();

    if ( strlen(FC_TimeService::Asctime (FC_TimeService::Gmtime(&startTime,&tmpTm),tmpBuff)) <= 30 )
        strcpy(startTimeString, FC_TimeService::Asctime (FC_TimeService::Gmtime(&startTime,&tmpTm),tmpBuff));
    if ( strlen(FC_TimeService::Asctime (FC_TimeService::Gmtime(&endTime,&tmpTm),tmpBuff)) <= 30 )
        strcpy(endTimeString, FC_TimeService::Asctime (FC_TimeService::Gmtime(&endTime,&tmpTm),tmpBuff));

    theStream << FC_InsertVar( startTime );
    theStream << FC_InsertVar( startTimeString );
    theStream << FC_InsertVar( endTime );
    theStream << FC_InsertVar( endTimeString );
    theStream << FC_InsertLabelAndVar( "myIdf", *myIdf );
    theStream << FC_InsertVar( myRequestId );
    theStream << FC_InsertVar( *myMaxTca );

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7000D4
istream& PM_BbValue::ReadObject( istream& theStream )
{
    time_t startTime;
    time_t endTime;


    theStream >> FC_ExtractVar(startTime);
    theStream >> FC_ExtractVar(endTime);
    theStream >> FC_ExtractVar( *myIdf );
    theStream >> FC_ExtractVar( myRequestId );
    theStream >> FC_ExtractVar( *myMaxTca );

    myStartTime.SetUTCTime(startTime);
    myEndTime.SetUTCTime(endTime);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA50391
void PM_BbValue::CreateMembers()
{
    myIdf = new PM_BbIdf(myNumberOfParam);

    myMaxTca = new PM_BbTca(myNumberOfParam);

    myCurValues = new CT_PM_Value [myNumberOfParam];
    myUasParameterFlags = new uint8 [myNumberOfParam];

    for (uint32 i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].UnsignedValue = 0;
        myUasParameterFlags[i] = PM_BASIC_PARAMETER;
    }

}

//-----------------------------------------------------------------
void PM_BbValue::CreateMembersDeep()
{
    CreateMembers();
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA60017
void PM_BbValue::DeleteMembers()
{
    delete myMaxTca;

    delete [] myCurValues;
    delete [] myUasParameterFlags;

    // Delete the object that contained the IDF.
    delete myIdf;

    myIdf = NULL;

    myMaxTca = NULL;
    myCurValues = NULL;
}

//-----------------------------------------------------------------
void PM_BbValue::DeleteMembersDeep()
{
    DeleteMembers();
}

//-----------------------------------------------------------------
bool PM_BbValue::IsUasParameter(CT_PM_Parameter  theParameter) const
{
    if((myNumberOfParam != 0) && (theParameter < myNumberOfParam))
    {
        if (myUasParameterFlags[theParameter] & PM_UAS_PARAMETER)
        {
            return true;
        }
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::GetValues()" );
    }
    return false;
}


bool PM_BbValue::IsUasAdjustedParameter(CT_PM_Parameter theParameter) const
{
    if((myNumberOfParam != 0) && (theParameter < myNumberOfParam))
    {
        if (myUasParameterFlags[theParameter] & PM_UAS_ADJUSTED_PARAMETER)
        {
            return true;
        }
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValue::GetValues()" );
    }
    return false;
}

void PM_BbValue::AllocateTca()
{
    myMaxTca->AllocateEventData();
}

//-----------------------------------------------------------------
PM_BbTca* PM_BbValue::GetMinTca()
{
    return NULL;

}

//-----------------------------------------------------------------
void PM_BbValue::SetTestValue()
{
    uint32 value = 0;
    CT_TimeTm ctTime = GetStartTime().GetCtTime();

    value = (ctTime.mon + 1) & 0xff;
    value = (value << 8) | (ctTime.mday) & 0xff;
    value = (value << 8) | (ctTime.hour) & 0xff;
    value = (value << 8) | (ctTime.min) & 0xff;

    myCurValues[0].UnsignedValue = value;
}

//-----------------------------------------------------------------
// See inheriting classes.
//-----------------------------------------------------------------
bool PM_BbValue::IsParam64BitValue( const CT_PM_Parameter theParameter )
{
    return false;
}

CT_PM_64BitValue PM_BbValue::Get64BitValue( const CT_PM_Parameter theParameter )
{
    CT_PM_64BitValue theValue;
    theValue.UnsignedValue = 0;
    return theValue;
}

void PM_BbValue::Set64BitValue( const CT_PM_Parameter theParameter, CT_PM_64BitValue theValue )
{
}
