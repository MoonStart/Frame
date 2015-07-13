// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_Counters.h"



//##ModelId=3C17861300BE
MON_Counters::MON_Counters(uint32 theIndex):
    MON_Object(theIndex)
{
}

//##ModelId=3C17861300C8
MON_Counters::~MON_Counters(void )
{
}

//##ModelId=3C17861300D2
ostream& MON_Counters::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
    return theStream;
}

//##ModelId=3C17861300D4
istream& MON_Counters::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
    return theStream;
}

//##ModelId=3C17861300DC
FC_Stream& MON_Counters::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
    return theStream;
}

//##ModelId=3C17861300E6
FC_Stream& MON_Counters::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
    return theStream;
}

