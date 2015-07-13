/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM inhibition class. Keeps the inhibition state of PM.
--------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include "../PM_BbInhibit.h"
#include <PM_Def.h>
#include <ErrorService/FC_Error.h>

using namespace std;

//-----------------------------------------------------------------
//##ModelId=3C1F6F760141
PM_BbInhibit::PM_BbInhibit (uint32 dummy1, uint32 dummy2)
{
    myControlWord = 0;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F76015F
PM_BbInhibit::~PM_BbInhibit()
{

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F760161
void PM_BbInhibit::Reset()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3C9255C2000B
bool PM_BbInhibit::GetInhibitParam(CT_PM_Parameter theParameter) const
{

    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

    return false;

}

//-----------------------------------------------------------------
//##ModelId=3C9255C20033
void PM_BbInhibit::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAB0259
bool PM_BbInhibit::GetTcaInhibitParam(CT_PM_Parameter theParameter) const
{

    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

    return false;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAB02B3
void PM_BbInhibit::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{

    FC_THROW_ERROR( FC_NotSupportedError, "PM: This method is not supported" );

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7601BA
FC_Stream& PM_BbInhibit::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myControlWord;

    return theStream;

}
   
//-----------------------------------------------------------------
//##ModelId=3C1F6F7601CD
FC_Stream& PM_BbInhibit::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> myControlWord;
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7601E1
ostream& PM_BbInhibit::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myControlWord);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7601F5
istream& PM_BbInhibit::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myControlWord);

    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F76016A
bool PM_BbInhibit::GetInhibit(CT_PM_BbControlWord theControlWord) const
{
    // WARNING ! control word is reverse logic. When this next
    // call returns false, ihibition is active.
    return !GetControlBit(theControlWord);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F760175
void PM_BbInhibit::SetInhibit(CT_PM_BbControlWord theControlWord, bool theBoolVal)
{
    ChangeControlBit(theBoolVal, theControlWord);

}

//-----------------------------------------------------------------
bool PM_BbInhibit::SetControlWord(CT_PM_BbControlWord theWord)
{
    bool retVal = false;
 
    if ( myControlWord != theWord )
    {
        myControlWord = theWord;
        retVal = true;
    }
 
    return retVal;
}

