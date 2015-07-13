/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, December 17, 2001.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Optical Channel.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueCop.h>
#include <CommonTypes/CT_PM_Definition.h>


//-----------------------------------------------------------------
//##ModelId=3C1F6F51024D
PM_BbValueCop::PM_BbValueCop(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeCop::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F510260
PM_BbValueCop::~PM_BbValueCop()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbValueCop::ResetAll(void)
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
void PM_BbValueCop::ResetMinParam(CT_PM_Parameter theParameter)
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
        FC_THROW_ERROR(FC_SWError, "PM_BbValueCop::ResetMinParam()" );
    }

}

//-----------------------------------------------------------------
void PM_BbValueCop::ResetMaxParam(CT_PM_Parameter theParameter)
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
        FC_THROW_ERROR(FC_SWError, "PM_BbValueCop::ResetMaxParam()" );
    }

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F510262
ostream& PM_BbValueCop::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream   << FC_InsertVar( myCurValues[PM_TypeCop::PM_COP].SignedValue  );
        theStream   << FC_InsertVar( myMinValues[PM_TypeCop::PM_COP].SignedValue  );
        theStream   << FC_InsertVar( myMaxValues[PM_TypeCop::PM_COP].SignedValue  );
    }
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F510274
istream& PM_BbValueCop::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream   >> FC_ExtractVar( myCurValues[PM_TypeCop::PM_COP].SignedValue  );
        theStream   >> FC_ExtractVar( myMinValues[PM_TypeCop::PM_COP].SignedValue  );
        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeCop::PM_COP].SignedValue  );
    }

    return theStream;

}
