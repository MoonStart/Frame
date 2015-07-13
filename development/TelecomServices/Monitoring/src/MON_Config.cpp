// Copyright(c) Tellabs Transport Group. All rights reserved


#include "../MON_Config.h"
#include <BaseClass/FC_TextStream.h>

//##ModelId=3C0FE67001F7
MON_Config::MON_Config(uint32 theIndex):
    MON_Object(theIndex)
{
    // validate configuration object by default
    // it creates confusion otherwise
    Validate();
}

//##ModelId=3C0FE6700201
MON_Config::~MON_Config()
{
}

void MON_Config::Reset()
{
    Validate();
}

//##ModelId=3C0FE6700216
FC_Stream& MON_Config::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);
    return theStream;
}

//##ModelId=3C0FE670022A
FC_Stream& MON_Config::ReadObjectBinary( FC_Stream& theStream )
{
    MON_Object::ReadObjectBinary(theStream);
    return theStream;
}

//##ModelId=3C0FE6700203
ostream& MON_Config::WriteObject( ostream& theStream )
{
    MON_Object::WriteObject(theStream);
    return theStream;
}

//##ModelId=3C0FE670020C
istream& MON_Config::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);
    return theStream;
}

