// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchRequest.h"
#include <BaseClass/FC_TextStream.h>

extern bool gInterferenceEnabled;

MON_OchRequest::MON_OchRequest(uint32 theIndex):
    MON_Config(theIndex),
    myChannelId(0),
    myRequestID(0),
    myInterferenceAnalyserEnable(true)
{
}

MON_OchRequest::~MON_OchRequest(void )
{
}

void MON_OchRequest::Reset()
{
    MON_Config::Reset();
    myRequestID = 0;
    myChannelId = CT_Wavelength(0);
    myInterferenceAnalyserEnable = true;
}

MON_RequestID MON_OchRequest::SetChannelId(CT_Wavelength theChannelId, bool theInterferenceAnalyserEnable)
{
    //Increment request counter at each tone set
    static MON_RequestID sRequestID = 0;
    myRequestID = ++sRequestID;
    myChannelId = theChannelId;
    myInterferenceAnalyserEnable = theInterferenceAnalyserEnable;
    return myRequestID;
}

CT_Wavelength MON_OchRequest::GetChannelId() const
{
    return myChannelId;
}

MON_RequestID MON_OchRequest::GetRequestID() const
{
    return myRequestID;
}

void MON_OchRequest::SetInterferenceAnalyserEnable(bool theInterferenceAnalyserEnable)
{
    myInterferenceAnalyserEnable = theInterferenceAnalyserEnable;
}

bool MON_OchRequest::GetInterferenceAnalyserEnable() const
{
    return (myInterferenceAnalyserEnable && gInterferenceEnabled);
}

ostream& MON_OchRequest::WriteObject(ostream& theStream)
{
    uint8 aChannelId = myChannelId.WavelengthIndex();
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myRequestID);
    theStream << FC_InsertLabelAndVar("myChannelId", aChannelId);
    theStream << FC_InsertVar(myInterferenceAnalyserEnable);    
    return theStream;
}

istream& MON_OchRequest::ReadObject(istream& theStream)
{
    uint8 aChannelId;  // for conversion
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myRequestID);
    theStream >> FC_ExtractVar(aChannelId);
    theStream >> FC_ExtractVar(myInterferenceAnalyserEnable);
    // Convert and store the expected channel
    CT_Wavelength bChannelId(aChannelId);
    myChannelId = bChannelId;
    return theStream;
}

FC_Stream& MON_OchRequest::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myRequestID;
    theStream << myChannelId;
    theStream << myInterferenceAnalyserEnable;
    return theStream;
}

FC_Stream& MON_OchRequest::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myRequestID;
    theStream >> myChannelId;
    theStream >> myInterferenceAnalyserEnable;
    return theStream;
}

