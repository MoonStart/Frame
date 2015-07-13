/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     27 February 2006  Larry Wolfrum
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Far-End SONET/SDH HOP layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <EPM/PM_BbValueHopFarEnd.h>


//-----------------------------------------------------------------
PM_BbValueHopFarEnd::PM_BbValueHopFarEnd(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue(PM_TypeHopFarEnd::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbValueHopFarEnd::~PM_BbValueHopFarEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& PM_BbValueHopFarEnd::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeHopFarEnd::PM_CV].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeHopFarEnd::PM_ES].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeHopFarEnd::PM_SES].UnsignedValue  )
        << FC_InsertVar( myCurValues[PM_TypeHopFarEnd::PM_UAS].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeHopFarEnd::PM_FC].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueHopFarEnd::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueHopFarEnd::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeHopFarEnd::PM_CV].UnsignedValue   )
            >> FC_ExtractVar( myCurValues[PM_TypeHopFarEnd::PM_ES].UnsignedValue   )
            >> FC_ExtractVar( myCurValues[PM_TypeHopFarEnd::PM_SES].UnsignedValue  )
            >> FC_ExtractVar( myCurValues[PM_TypeHopFarEnd::PM_UAS].UnsignedValue   )
            >> FC_ExtractVar( myCurValues[PM_TypeHopFarEnd::PM_FC].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueHopFarEnd::ReadObject()" );
    }

    return theStream;

}
