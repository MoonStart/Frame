/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Sebastien Cossette, March 07, 2002.
 DESCRIPTION:   PM end of period service.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbEndOfPeriod.h>


//-----------------------------------------------------------------
//##ModelId=3C9255A700EA
PM_BbEndOfPeriod::PM_BbEndOfPeriod()
{
    for (int i = 0; i < CT_PM_PERIOD_UNKNOWN; i++)
    {
        myPeriod[i] = 0;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C9255A700F3
PM_BbEndOfPeriod::~PM_BbEndOfPeriod()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C9255A70139
FC_Stream& PM_BbEndOfPeriod::WriteObjectBinary( FC_Stream& theStream )
{
    for (int i = 0; i < CT_PM_PERIOD_UNKNOWN; i++)
    {
        theStream << myPeriod[i];
    }

    return theStream;

}

//----------------------------------------------------------------- 
//##ModelId=3C9255A70144
FC_Stream& PM_BbEndOfPeriod::ReadObjectBinary( FC_Stream& theStream )
{
    for (int i = 0; i < CT_PM_PERIOD_UNKNOWN; i++)
    {
        theStream >> myPeriod[i];
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A70157
ostream& PM_BbEndOfPeriod::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(myPeriod[CT_PM_PERIOD_15_MINUTES]);
    theStream   << FC_InsertVar(myPeriod[CT_PM_PERIOD_1_DAY]);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A70162
istream& PM_BbEndOfPeriod::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(myPeriod[CT_PM_PERIOD_15_MINUTES]);
    theStream   >> FC_ExtractVar(myPeriod[CT_PM_PERIOD_1_DAY]);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A70125
bool PM_BbEndOfPeriod::operator==(const PM_BbEndOfPeriod& theAlarmObject)
{
    if(   myPeriod[CT_PM_PERIOD_15_MINUTES] == theAlarmObject.myPeriod[CT_PM_PERIOD_15_MINUTES]
       && myPeriod[CT_PM_PERIOD_1_DAY] == theAlarmObject.myPeriod[CT_PM_PERIOD_1_DAY])
    {
        return true;
    }

    return false;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A7012F
PM_BbEndOfPeriod& PM_BbEndOfPeriod::operator =(const PM_BbEndOfPeriod& theAlarmObject)
{
    myPeriod[CT_PM_PERIOD_15_MINUTES] = theAlarmObject.myPeriod[CT_PM_PERIOD_15_MINUTES];
    myPeriod[CT_PM_PERIOD_1_DAY] = theAlarmObject.myPeriod[CT_PM_PERIOD_1_DAY];

    return *this;

}
