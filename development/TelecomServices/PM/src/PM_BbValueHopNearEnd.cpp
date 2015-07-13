/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM and RAMM.
 AUTHOR   :     13 February 2004  Hemant Thakkar
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Near-End SONET/SDH HOP layer.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueHopNearEnd.h>


//-----------------------------------------------------------------
PM_BbValueHopNearEnd::PM_BbValueHopNearEnd(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue(PM_TypeHopNearEnd::PM_PARAM_NUM)
{
    // Set the PM parameter flag. This flag is used when 
    // making adjustments related to unavailability conditions.
    myUasParameterFlags[PM_TypeHopNearEnd::PM_CV] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeHopNearEnd::PM_ES] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeHopNearEnd::PM_SES] = PM_UAS_ADJUSTED_PARAMETER;
    myUasParameterFlags[PM_TypeHopNearEnd::PM_UAS] = PM_UAS_PARAMETER;
}

//-----------------------------------------------------------------
PM_BbValueHopNearEnd::~PM_BbValueHopNearEnd()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
ostream& PM_BbValueHopNearEnd::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_CV].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_ES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_SES].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_FC].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_UAS].UnsignedValue		)
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_PJCSDET].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_PJCSGEN].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueHopNearEnd::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
istream& PM_BbValueHopNearEnd::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {

        theStream 
            >> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_CV].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_ES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_SES].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_FC].UnsignedValue		 )
            >> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_UAS].UnsignedValue		 )
			>> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_PJCSDET].UnsignedValue   )
			>> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_PJCSGEN].UnsignedValue   )
			>> FC_ExtractVar( myCurValues[PM_TypeHopNearEnd::PM_PJCDIFF].UnsignedValue  );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueHopNearEnd::ReadObject()" );
    }

    return theStream;

}
