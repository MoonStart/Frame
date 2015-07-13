/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002, Sebastien Cossette
 DESCRIPTION:   PM reset class. Keeps the reset state of PM.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <PM/PM_BbReset.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4CA9030B
PM_BbReset::PM_BbReset(uint32 theNumberOfParam, uint32 dummy)
{
    uint32 counter = 0;
    myNumberOfParam = theNumberOfParam;
    myResetCount = new PM_ResetCounter[myNumberOfParam];

    for (counter=0 ; counter < myNumberOfParam ; counter++)
    {
        myResetCount[counter] = 0;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA9031F
PM_BbReset::PM_BbReset (uint32 theNumberOfParam, PM_ResetCounter* theResetCount)
{
    uint32 counter = 0;
    myNumberOfParam = theNumberOfParam;
    myResetCount = theResetCount;

    for (counter=0 ; counter < myNumberOfParam ; counter++)
    {
        myResetCount[counter] = 0;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA90332
PM_BbReset::~PM_BbReset()
{
    delete [] myResetCount;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA9033C
void PM_BbReset::Reset()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA90346
char PM_BbReset::GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA9036E
char PM_BbReset::GetResetMinRegisterCounter(PM_ResetCounter theParameterToReset) const
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA90382
char PM_BbReset::GetResetMaxRegisterCounter(PM_ResetCounter theParameterToReset) const
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA90396
void PM_BbReset::ResetCurRegister(CT_PM_Parameter theParameterToReset)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA903AA
void PM_BbReset::ResetMinRegister(CT_PM_Parameter theParameterToReset)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA903BF
void PM_BbReset::ResetMaxRegister(CT_PM_Parameter theParameterToReset)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA903CA
void PM_BbReset::ResetAllCurRegisters(void)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CA903E7
void PM_BbReset::ResetAllMinRegisters(void)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAA0013
void PM_BbReset::ResetAllMaxRegisters(void)
{
    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
bool PM_BbReset::SetPMResetCount(CT_PM_Parameter theParam, PM_ResetCounter theCount)
{
    bool retVal = false;

    if ( myResetCount[theParam] != theCount )
    {
        myResetCount[theParam] = theCount;
        retVal = true;
    }

    return retVal;
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAA001F
FC_Stream& PM_BbReset::WriteObjectBinary( FC_Stream& theStream )
{
    theStream.write_array(myResetCount, myNumberOfParam);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAA0032
FC_Stream& PM_BbReset::ReadObjectBinary( FC_Stream& theStream )
{
    theStream.read_array(myResetCount, myNumberOfParam);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAA0045
ostream& PM_BbReset::WriteObject( ostream& theStream )
{
    uint32 counter = 0;

    for (counter=0 ; counter < myNumberOfParam ; counter++)
    {
        theStream << FC_InsertVar(myResetCount[counter]);
    }

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAA0059
istream& PM_BbReset::ReadObject( istream& theStream )
{
    uint32 counter = 0;

    for (counter=0 ; counter < myNumberOfParam ; counter++)
    {
        theStream >> FC_ExtractVar(myResetCount[counter]);
    }

    return theStream;

}
