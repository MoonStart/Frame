// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../CFG_Object.h"
#include <BaseClass/FC_TextStream.h>


//##ModelId=3C0FE6300033
CFG_Object::CFG_Object(uint32 theIndex):
    myIndex(theIndex)
{
}

//##ModelId=3C0FE6300035
CFG_Object::~CFG_Object()
{
}

//##ModelId=3C3B463A01F2
FC_Stream& CFG_Object::WriteObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

//##ModelId=3C3B463A0242
FC_Stream& CFG_Object::ReadObjectBinary( FC_Stream& theStream )
{
    return theStream;
}

//##ModelId=3C3B463A0148
ostream& CFG_Object::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(myIndex);
    return theStream;
}

//##ModelId=3C3B463A01A2
istream& CFG_Object::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(myIndex);
    return theStream;
}

bool CFG_Object::IsValidated() const
{
    return isValidated;
}

void CFG_Object::Validate()
{
    isValidated = true;
}

void CFG_Object::Invalidate()
{
    isValidated = false;
}

void CFG_Object::Display(FC_Stream& theStream)
{
    theStream.GetOutputStream() << "Data is " << (IsValidated() ? "" :"NOT ") <<"validated." << endl;
  
}

FC_CmdProcessor::STATUS CFG_Object::Set(int argc, char** argv)
{
    return FC_CmdProcessor::E_FAILURE;
}

FC_CmdProcessor::STATUS CFG_Object::Debug(int argc, char** argv)
{
    return FC_CmdProcessor::E_FAILURE;
}