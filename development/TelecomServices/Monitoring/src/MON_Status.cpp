// //Copyright(c) Tellabs Transport Group. All rights reserved.


#include "../MON_Status.h"
#include "../MON_Definitions.h"
#include <ErrorService/FC_Error.h>


MON_Status::MON_Status(uint32 theIndex):
    MON_Object(theIndex)
{
}

MON_Status::~MON_Status()
{
}

ostream& MON_Status::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
    return theStream;
}

istream& MON_Status::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
    return theStream;
}

FC_Stream& MON_Status::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
    return theStream;
}

FC_Stream& MON_Status::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
    return theStream;
}

