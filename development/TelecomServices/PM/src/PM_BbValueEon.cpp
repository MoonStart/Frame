/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   The Blackboard object of PM parameter values for the
                EON.
--------------------------------------------------------------------------*/

#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbValueEon.h>


//-----------------------------------------------------------------
//##ModelId=3FA1610A01CE
PM_BbValueEon::PM_BbValueEon(uint32 dummy, uint32 dummy1):
    PM_BbCounterValue(PM_TypeEon::PM_PARAM_NUM)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610A01D1
PM_BbValueEon::~PM_BbValueEon()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610A01D3
ostream& PM_BbValueEon::WriteObject( ostream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::WriteObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream 
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_ICMPDUR ].UnsignedValue    )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_ICMPDUT].UnsignedValue     )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_ICMPER].UnsignedValue      )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_ICMPTTLER].UnsignedValue   )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_IPADDER].UnsignedValue     )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_IPDISCR].UnsignedValue     )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_IPDISCT].UnsignedValue     )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_IPHDRR].UnsignedValue      )
        << FC_InsertVar( myCurValues[PM_TypeEon::PM_IPNOROUTEST].UnsignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueEon::WriteObject()" );
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610A01DD
istream& PM_BbValueEon::ReadObject( istream& theStream )
{
    // Call base class method.
    PM_BbCounterValue::ReadObject(theStream);

    if(myNumberOfParam != 0)
    {
        theStream 
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_ICMPDUR ].UnsignedValue    )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_ICMPDUT].UnsignedValue     )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_ICMPER].UnsignedValue      )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_ICMPTTLER].UnsignedValue   )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_IPADDER].UnsignedValue     )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_IPDISCR].UnsignedValue     )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_IPDISCT].UnsignedValue     )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_IPHDRR].UnsignedValue      )
        >> FC_ExtractVar( myCurValues[PM_TypeEon::PM_IPNOROUTEST].UnsignedValue );
    }
    else
    {
        FC_THROW_ERROR(FC_SWError, "PM_BbValueEon::ReadObject()" );
    }

    return theStream;

}
