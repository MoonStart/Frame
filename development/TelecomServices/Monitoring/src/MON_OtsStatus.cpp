// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OtsStatus.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>


MON_OtsStatus::MON_OtsStatus(uint32 theIndex):
    MON_Object(theIndex),
    myTraceMessage()
{
}

MON_OtsStatus::~MON_OtsStatus(void )
{
}

void MON_OtsStatus::Reset()
{
    MON_Object::Reset();
    myTraceMessage = CT_G709Trace();
}

const CT_G709Trace MON_OtsStatus::GetTraceMessage() const
{
    return myTraceMessage;
}

bool MON_OtsStatus::SetTraceMessage(const CT_G709Trace theTrace)
{
    // keep track of any changes

    if (myTraceMessage == theTrace)
        return false; // trace has not changed
    else
    {
        myTraceMessage = theTrace;
        return true;// trace has changed
    }
}

ostream& MON_OtsStatus::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
	theStream << FC_InsertVar(myTraceMessage);
    return theStream;
}

istream& MON_OtsStatus::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
	theStream >> FC_ExtractVar(myTraceMessage);
    return theStream;
}

FC_Stream& MON_OtsStatus::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
	theStream << myTraceMessage;
    return theStream;
}

FC_Stream& MON_OtsStatus::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
	theStream >> myTraceMessage;
    return theStream;
}

void MON_OtsStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "OTS     - Received Trace                    = " ;
    myTraceMessage.Display(theStream);
}

