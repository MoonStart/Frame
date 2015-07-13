// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_HopStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_HopStatus::MON_HopStatus(uint32 theIndex):
    MON_Object(theIndex)
{
}

MON_HopStatus::~MON_HopStatus(void)
{
    // Nothing to do for now.

}


const CT_SONET64ByteTrace MON_HopStatus::GetReceivedTrace() const 
{
    return myReceivedTraceMessage;
}

bool MON_HopStatus::SetReceivedTrace(const CT_SONET64ByteTrace& theTrace) 
{
    bool hasChanged = false;
    if (!(myReceivedTraceMessage == theTrace))
    {
        myReceivedTraceMessage = theTrace;
        hasChanged = true;
    }

    return hasChanged;
}

void MON_HopStatus::SetProcessTime(const FC_Milliseconds& theTime)
{
    myLastTime = theTime;

    if (myLastTime > myLongestTime)
        myLongestTime = myLastTime;

    if (myShortestTime == 0)
    {
        myShortestTime = myLastTime;
    }
    else if ((myLastTime != 0) && (myLastTime < myShortestTime))
    {
        myShortestTime = myLastTime;
    }
}

bool MON_HopStatus::IsDebugFlagSet() const 
{
    return myDebugFlag;
}

void MON_HopStatus::Reset(void)
{
    MON_Object::Reset();
    myReceivedTraceMessage = CT_SONET64ByteTrace();
    myLastTime = 0;
    myShortestTime = 0;  
    myLongestTime = 0;
    myDebugFlag = false;

}

ostream& MON_HopStatus::WriteObject( ostream& theStream )
{

    MON_Object::WriteObject(theStream);
    //theStream << FC_InsertVar(myReceivedTraceMessage);
    theStream << FC_InsertVar(myLastTime);
    theStream << FC_InsertVar(myShortestTime);
    theStream << FC_InsertVar(myLongestTime);
    theStream << FC_InsertVar(myDebugFlag);
    return theStream;

}

istream& MON_HopStatus::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);
    //theStream >> FC_ExtractVar(myReceivedTraceMessage);
    theStream >> FC_ExtractVar(myLastTime);
    theStream >> FC_ExtractVar(myShortestTime);
    theStream >> FC_ExtractVar(myLongestTime);
    theStream >> FC_ExtractVar(myDebugFlag);
    return theStream;

}

FC_Stream& MON_HopStatus::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);
    //theStream << myReceivedTraceMessage;
    return theStream;

}

FC_Stream& MON_HopStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Object::ReadObjectBinary(theStream);
    //theStream >> myReceivedTraceMessage;
    return theStream;

}

void MON_HopStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    // Trace is not supported   
    //theStream   << "HOP     - Received Trace                    = " ;
    //myReceivedTraceMessage.Display(theStream);
    theStream   << "HOP     - Received Trace                    = Path Trace NOT SUPPORTED" << endl;
        if (myDebugFlag)
    {
        theStream   << "HOP     - Last Time ms                      = " << myLastTime << endl;
        theStream   << "HOP     - Shortest Time ms                  = " << myShortestTime << endl;
        theStream   << "HOP     - Longest Time ms                   = " << myLongestTime << endl;
    }
}
