// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_RsStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_RsStatus::MON_RsStatus(uint32 theIndex):
    MON_Object(theIndex)
{
}

MON_RsStatus::~MON_RsStatus(void)
{
    // Nothing to do for now.

}

const CT_SDH16ByteTrace MON_RsStatus::GetReceivedTrace() const 
{
    return myReceivedTraceMessage;
}

bool MON_RsStatus::SetReceivedTrace(const CT_SDH16ByteTrace& theTrace) 
{
    bool hasChanged = false;
    if ((!(myReceivedTraceMessage == theTrace)) || (!(myReceivedTraceMessage.IsValid() == theTrace.IsValid())))
    {
        myReceivedTraceMessage = theTrace;
        hasChanged = true;
    }

    return hasChanged;
}

void MON_RsStatus::Reset(void)
{
    MON_Object::Reset();
    myReceivedTraceMessage = CT_SDH16ByteTrace();

}

ostream& MON_RsStatus::WriteObject( ostream& theStream )
{

    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myReceivedTraceMessage);
    return theStream;

}

istream& MON_RsStatus::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myReceivedTraceMessage);
    return theStream;

}

FC_Stream& MON_RsStatus::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << myReceivedTraceMessage;
    return theStream;

}

FC_Stream& MON_RsStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myReceivedTraceMessage;
    return theStream;

}

void MON_RsStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "RS      - Received Trace                    = " ;
    if(myReceivedTraceMessage.IsValid())
        myReceivedTraceMessage.Display(theStream);
    else
        theStream << "INVALID TRACE" << endl;
}
