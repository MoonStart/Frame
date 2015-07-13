/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM
 AUTHOR   :     22 April 2004  Hemant Thakkar
 DESCRIPTION:   The Blackboard object of PM parameter values for GFP layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueGfp.h>


//-----------------------------------------------------------------
PM_BbValueGfp::PM_BbValueGfp(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue(PM_TypeGfp::PM_PARAM_NUM)
{
}

//-----------------------------------------------------------------
PM_BbValueGfp::~PM_BbValueGfp()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& PM_BbValueGfp::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream << FC_InsertVar( myCurValues[PM_TypeGfp::PM_10B_ERR].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueGfp::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueGfp::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream >> FC_ExtractVar( myCurValues[PM_TypeGfp::PM_10B_ERR].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueGfp::ReadObject()" );
    }

    return theStream;

}

