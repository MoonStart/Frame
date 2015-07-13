// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchResult.h"
#include <BaseClass/FC_TextStream.h>
#include <Monitoring/MON_PilotToneProcessorRequest.h>

//##ModelId=3C7170F003D9
MON_OchResult::MON_OchResult(uint32 theIndex):
    MON_OchStatus(theIndex),
    myRequestInformation(),
    myErrorCode(0)
{
}

void MON_OchResult::operator=(const MON_OchResult& theOchResult)
{
    MON_OchStatus::operator=(theOchResult);
    myRequestInformation.operator=(theOchResult.myRequestInformation);
    myErrorCode = theOchResult.myErrorCode;
}

//##ModelId=3C7170F10005
MON_OchResult::~MON_OchResult(void )
{
}

//##ModelId=3C7170F10019
void MON_OchResult::Reset()
{
    MON_OchStatus::Reset();
    myRequestInformation.Reset();
}

bool MON_OchResult::operator==(const MON_OchResult& theOchResult) const
{
    return ((myRequestInformation == theOchResult.myRequestInformation) &&
            (myErrorCode == theOchResult.myErrorCode) );
}

void MON_OchResult::SetRequestInformation(MON_PilotToneProcessorRequest& theRequest)
{
    myRequestInformation = theRequest;
}

const MON_PilotToneProcessorRequest& MON_OchResult::GetRequestInformation() const
{
    return myRequestInformation;
}

void MON_OchResult::SetErrorCode(uint32 theErrorCode)
{
    myErrorCode = theErrorCode;
}

uint32 MON_OchResult::GetErrorCode() const
{
    return myErrorCode;
}


//##ModelId=3C7170F10037
ostream& MON_OchResult::WriteObject(ostream& theStream)
{
    MON_OchStatus::WriteObject(theStream);
    theStream << FC_InsertVar(myRequestInformation);
    theStream << FC_InsertVar(myErrorCode);
    return theStream;
}

//##ModelId=3C7170F1004B
istream& MON_OchResult::ReadObject(istream& theStream)
{
    MON_OchStatus::ReadObject(theStream);
    theStream >> FC_ExtractVar(myRequestInformation);
    theStream >> FC_ExtractVar(myErrorCode);
    return theStream;
}

//##ModelId=3C7170F1005F
FC_Stream& MON_OchResult::WriteObjectBinary(FC_Stream& theStream)
{
    MON_OchStatus::WriteObjectBinary(theStream);
    theStream << myRequestInformation;
    theStream << myErrorCode;
    return theStream;
}

//##ModelId=3C7170F10073
FC_Stream& MON_OchResult::ReadObjectBinary(FC_Stream& theStream)
{
    MON_OchStatus::ReadObjectBinary(theStream);
    theStream >> myRequestInformation;
    theStream >> myErrorCode;
    return theStream;
}

//##ModelId=3C7170F1001A
void MON_OchResult::Display(FC_Stream& theStream)
{
    MON_OchStatus::Display(theStream);
    myRequestInformation.Display(theStream);
    FC_FmtFlags prevFlags = theStream.GetOutputStream().flags();
    theStream.GetOutputStream().setf(ios::hex, ios::basefield);
    theStream   << "OCH     - Pilot tone error code             = 0x" << myErrorCode << endl;
    theStream.GetOutputStream().flags(prevFlags);
}
