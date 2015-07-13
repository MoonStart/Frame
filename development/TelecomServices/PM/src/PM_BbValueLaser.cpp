/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders.
 AUTHOR   :     Sebastien Cossette, January 7, 2002.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                Laser.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueLaser.h>
#include <CommonTypes/CT_PM_Definition.h>

//-----------------------------------------------------------------
//##ModelId=3C1F6F560151
PM_BbValueLaser::PM_BbValueLaser(uint32 dummy, uint32 dummy1):
    PM_BbGaugeValue(PM_TypeLaser::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F560163
PM_BbValueLaser::~PM_BbValueLaser()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbValueLaser::ResetAll(void)
{
	// Laser temperature
	myCurValues[PM_TypeLaser::PM_LT].SignedValue = 0;
	myMinValues[PM_TypeLaser::PM_LT].SignedValue = CT_PM_DEFAULT_MIN_LT;
	myMaxValues[PM_TypeLaser::PM_LT].SignedValue = CT_PM_DEFAULT_MAX_LT;

	// Laser bias current
	myCurValues[PM_TypeLaser::PM_LBC].SignedValue = 0;
	myMinValues[PM_TypeLaser::PM_LBC].SignedValue = CT_PM_DEFAULT_MIN_LBC;
	myMaxValues[PM_TypeLaser::PM_LBC].SignedValue = CT_PM_DEFAULT_MAX_LBC;

}

//-----------------------------------------------------------------
void PM_BbValueLaser::ResetMinParam(CT_PM_Parameter theParameter)
{
	int32 signedValue;

    if( myNumberOfParam != 0 )
    {
		switch( theParameter )
		{
		case PM_TypeLaser::PM_LT:

			signedValue = CT_PM_DEFAULT_MIN_LT;
			break;

		case PM_TypeLaser::PM_LBC:

			signedValue = CT_PM_DEFAULT_MIN_LBC;
			break;

		default:
			FC_THROW_ERROR(FC_SWError, "PM_BbValueLaser::ResetMinParam()" );
		}

		// Reset minimum value.
		myMinValues[theParameter].SignedValue = signedValue;

        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueLaser::ResetMinParam()" );
    }

}

//-----------------------------------------------------------------
void PM_BbValueLaser::ResetMaxParam(CT_PM_Parameter theParameter)
{
	int32 signedValue;

    if( myNumberOfParam != 0 )
    {
		switch( theParameter )
		{
		case PM_TypeLaser::PM_LT:

			signedValue = CT_PM_DEFAULT_MAX_LT;
			break;

		case PM_TypeLaser::PM_LBC:

			signedValue = CT_PM_DEFAULT_MAX_LBC;
			break;

		default:
			FC_THROW_ERROR(FC_SWError, "PM_BbValueLaser::ResetMaxParam()" );
		}

		// Reset maximum value.
		myMaxValues[theParameter].SignedValue = signedValue;

        // Invalidate IDF.
        GetIdf()->SetIdf(theParameter);
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueLaser::ResetMaxParam()" );
    }
}

//-----------------------------------------------------------------
//##ModelId=3C1F6F560165
ostream& PM_BbValueLaser::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
    
        theStream   << FC_InsertVar( myCurValues[PM_TypeLaser::PM_LT].SignedValue  )
                    << FC_InsertVar( myCurValues[PM_TypeLaser::PM_LBC].SignedValue );

        theStream   << FC_InsertVar( myMinValues[PM_TypeLaser::PM_LT].SignedValue  )
                    << FC_InsertVar( myMinValues[PM_TypeLaser::PM_LBC].SignedValue );

        theStream   << FC_InsertVar( myMaxValues[PM_TypeLaser::PM_LT].SignedValue  )
                    << FC_InsertVar( myMaxValues[PM_TypeLaser::PM_LBC].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueLaser::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F560177
istream& PM_BbValueLaser::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbGaugeValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {
    
        theStream   >> FC_ExtractVar( myCurValues[PM_TypeLaser::PM_LT].SignedValue  )
                    >> FC_ExtractVar( myCurValues[PM_TypeLaser::PM_LBC].SignedValue );

        theStream   >> FC_ExtractVar( myMinValues[PM_TypeLaser::PM_LT].SignedValue  )
                    >> FC_ExtractVar( myMinValues[PM_TypeLaser::PM_LBC].SignedValue );

        theStream   >> FC_ExtractVar( myMaxValues[PM_TypeLaser::PM_LT].SignedValue  )
                    >> FC_ExtractVar( myMaxValues[PM_TypeLaser::PM_LBC].SignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueLaser::ReadObject()" );
    }

    return theStream;

}
