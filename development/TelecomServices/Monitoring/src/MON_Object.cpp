// Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_Object.h"
#include <BaseClass/FC_TextStream.h>

//##ModelId=3C0FE670016B
MON_Object::MON_Object(uint32 theIndex):
    myIndex(theIndex),
    isValidated(false)
{
}

MON_Object::MON_Object(const MON_Object& theObject):
    myIndex(theObject.myIndex),
    isValidated(theObject.isValidated)
{
}

void MON_Object::operator=(const MON_Object& theObject)
{
   isValidated = theObject.isValidated;
}

//##ModelId=3C0FE670016D
MON_Object::~MON_Object()
{
}

bool MON_Object::operator==(const MON_Object& theObject) const
{
    return (isValidated==theObject.isValidated);
}

void MON_Object::Reset()
{
    isValidated = false;
}

bool MON_Object::IsValidated() const
{
    return isValidated;
}

bool MON_Object::Validate()
{
    if (isValidated)
        return false;
    else
    {
        isValidated = true;
        return true;
    }
}

bool MON_Object::Invalidate()
{
    if (!isValidated)
        return false;
    else
    {
        isValidated = false;
        return true;
    }
}

//##ModelId=3C0FE67001A8
FC_Stream& MON_Object::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << isValidated;
    return theStream;
}

//##ModelId=3C0FE67001B3
FC_Stream& MON_Object::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> isValidated;
    return theStream;
}

//##ModelId=3C0FE6700194
ostream& MON_Object::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(myIndex);
    theStream   << FC_InsertVar(isValidated);
    return theStream;
}

//##ModelId=3C0FE670019E
istream& MON_Object::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(myIndex);
    theStream   >> FC_ExtractVar(isValidated);
    return theStream;
}

//##ModelId=3C7170F202EB
void MON_Object::Display(FC_Stream& theStream)
{
    if(!IsValidated())
    {
        theStream << "              **** DATA INVALID ****"  << endl;  
    }
}
FC_CmdProcessor::STATUS MON_Object::Set(int argc, char** argv)
{
    return FC_CmdProcessor::E_FAILURE;
}

FC_CmdProcessor::STATUS MON_Object::Debug(int argc, char** argv)
{
    return FC_CmdProcessor::E_FAILURE;
}

