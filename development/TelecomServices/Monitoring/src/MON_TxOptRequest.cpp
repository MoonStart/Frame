// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_TxOptRequest.h"
#include <BaseClass/FC_TextStream.h>


MON_TxOptRequest::MON_TxOptRequest(uint32 theIndex):
    MON_Object(theIndex),
    myRequestID(0)
{
    Validate();
}

MON_TxOptRequest::~MON_TxOptRequest(void)
{
}

void MON_TxOptRequest::Reset()
{
    MON_Object::Reset();
    Validate();
    myRequestID = 0;
}

MON_RequestID MON_TxOptRequest::RequestTxPower(void)
{
    //Increment request counter at each request
    static MON_RequestID sRequestID = 0;
    myRequestID = ++sRequestID;
    return myRequestID;
}

MON_RequestID MON_TxOptRequest::GetRequestID() const
{
    return myRequestID;
}


ostream& MON_TxOptRequest::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myRequestID);
    return theStream;
}

istream& MON_TxOptRequest::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myRequestID);
    return theStream;
}

FC_Stream& MON_TxOptRequest::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << myRequestID;
    return theStream;
}

FC_Stream& MON_TxOptRequest::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myRequestID;
    return theStream;
}

void MON_TxOptRequest::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "TX OPT  - Request ID                        = " << myRequestID << endl;
}
