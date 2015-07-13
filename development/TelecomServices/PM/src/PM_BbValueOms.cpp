/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Oms layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueOms.h>
#include <CommonTypes/CT_PM_Definition.h>

//-----------------------------------------------------------------
//##ModelId=3E6E4C99032F
PM_BbValueOms::PM_BbValueOms(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeOms::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C99033A
PM_BbValueOms::~PM_BbValueOms()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbValueOms::ResetAll(void)
{
    uint32 i;


    for (i=0; i<myNumberOfParam; i++)
    {
        myCurValues[i].SignedValue = 0;
        myMinValues[i].SignedValue = CT_PM_DEFAULT_MIN_POWER;
        myMaxValues[i].SignedValue = CT_PM_DEFAULT_MAX_POWER;
    }

}

//-----------------------------------------------------------------
void PM_BbValueOms::ResetMinParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset minimum value.
        myMinValues[theParameter].SignedValue = CT_PM_DEFAULT_MIN_POWER;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOms::ResetMinParam()" );
    }

}

//-----------------------------------------------------------------
void PM_BbValueOms::ResetMaxParam(CT_PM_Parameter theParameter)
{
    if(myNumberOfParam != 0 && theParameter < myNumberOfParam)
    {
        // Reset maximum value.
        myMaxValues[theParameter].SignedValue = CT_PM_DEFAULT_MAX_POWER;
        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOms::ResetMaxParam()" );
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C99034D
ostream& PM_BbValueOms::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream   << FC_InsertVar( myCurValues[PM_TypeOms::PM_OPR].SignedValue )
                    << FC_InsertVar( myCurValues[PM_TypeOms::PM_OPT].SignedValue );

        theStream   << FC_InsertVar( myMinValues[PM_TypeOms::PM_OPR].SignedValue )
                    << FC_InsertVar( myMinValues[PM_TypeOms::PM_OPT].SignedValue );

        theStream   << FC_InsertVar( myMaxValues[PM_TypeOms::PM_OPR].SignedValue )
                    << FC_InsertVar( myMaxValues[PM_TypeOms::PM_OPT].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOms::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4C990361
istream& PM_BbValueOms::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream   >> FC_ExtractVar( myCurValues[PM_TypeOms::PM_OPR].SignedValue )
                    >> FC_ExtractVar( myCurValues[PM_TypeOms::PM_OPT].SignedValue );

        theStream   >> FC_ExtractVar( myMinValues[PM_TypeOms::PM_OPR].SignedValue )
                    >> FC_ExtractVar( myMinValues[PM_TypeOms::PM_OPT].SignedValue );

        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeOms::PM_OPR].SignedValue )
                    >> FC_ExtractVar( myMaxValues[PM_TypeOms::PM_OPT].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueOms::ReadObject()" );
    }

    return theStream;

}
