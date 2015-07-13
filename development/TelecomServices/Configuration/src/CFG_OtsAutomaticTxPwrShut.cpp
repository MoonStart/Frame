//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OtsAutomaticTxPwrShut.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>

CFG_OtsAutomaticTxPwrShut::CFG_OtsAutomaticTxPwrShut(uint32 theIndex):
    CFG_Object(theIndex),
    myAtpsActive(false)
{
}

CFG_OtsAutomaticTxPwrShut::~CFG_OtsAutomaticTxPwrShut(void)
{
}

void CFG_OtsAutomaticTxPwrShut::Reset(void)
{
    myAtpsActive=false;
}

bool CFG_OtsAutomaticTxPwrShut::GetAtpsActive() const
{
    return myAtpsActive;
}

bool CFG_OtsAutomaticTxPwrShut::SetAtpsActive(bool theAtpsState)
{
    bool hasChanged=false;
    if (myAtpsActive != theAtpsState)
    {
        myAtpsActive = theAtpsState;
        hasChanged = true;
    }
    return hasChanged;
}

ostream& CFG_OtsAutomaticTxPwrShut::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
	theStream << FC_InsertVar(myAtpsActive);
    return theStream;
}

istream& CFG_OtsAutomaticTxPwrShut::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
	theStream >> FC_ExtractVar(myAtpsActive);
    return theStream;
}

FC_Stream& CFG_OtsAutomaticTxPwrShut::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
	theStream << myAtpsActive;
    return theStream;
}

FC_Stream& CFG_OtsAutomaticTxPwrShut::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
	theStream >> myAtpsActive;
    return theStream;
}

void CFG_OtsAutomaticTxPwrShut::Display( FC_Stream& theStream )
{
    theStream.GetOutputStream()   << "OTS AUTO Shutdown active          = " << DISPLAY_BOOL(myAtpsActive) << endl;
}
