// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_PilotToneProcessorRequest.h"
#include <BaseClass/FC_TextStream.h>

MON_PilotToneProcessorRequest::MON_PilotToneProcessorRequest():
    MON_Object(0),
    myChannelId(0),
    myRequestId(0),
    mySamplingMode(0),
    myPriority(TSPII_PT_LOW_PRIORITY)
{
}

MON_PilotToneProcessorRequest::MON_PilotToneProcessorRequest(
                                  CT_Wavelength theChannelId, 
                                  MON_RequestID theRequestId,
                                  uint32 theSamplingMode,
                                  TSPII_PilotTonePriority thePriority):
    MON_Object(0),
    myChannelId(theChannelId),
    myRequestId(theRequestId),
    mySamplingMode(theSamplingMode),
    myPriority(thePriority)
{

}

//##ModelId=3C7170DB0005
MON_PilotToneProcessorRequest::~MON_PilotToneProcessorRequest()
{
}


//##ModelId=3C7170DB0040
MON_PilotToneProcessorRequest& MON_PilotToneProcessorRequest::operator=(const MON_PilotToneProcessorRequest& theRequest)
{
    myRequestId     = theRequest.myRequestId;
    myChannelId     = theRequest.myChannelId;
    mySamplingMode  = theRequest.mySamplingMode;
    myPriority      = theRequest.myPriority;

    return *this;
}

bool MON_PilotToneProcessorRequest::operator==(const MON_PilotToneProcessorRequest& theRequest) const
{
    return ((myRequestId    == theRequest.myRequestId) &&
            (myChannelId    == theRequest.myChannelId) &&
            (mySamplingMode == theRequest.mySamplingMode) &&
            (myPriority     == theRequest.myPriority) );
}

ostream& MON_PilotToneProcessorRequest::WriteObject(ostream& theStream)
{
    theStream << FC_InsertVar(myRequestId);
    theStream << FC_InsertVar(myChannelId);
    theStream << FC_InsertVar(mySamplingMode);
    uint32 aPriority = myPriority;
    theStream << FC_InsertVar(aPriority);
    return theStream;
}

istream& MON_PilotToneProcessorRequest::ReadObject(istream& theStream)
{
    theStream >> FC_ExtractVar(myRequestId);
    theStream >> FC_ExtractVar(myChannelId);
    theStream >> FC_ExtractVar(mySamplingMode);
    uint32 aPriority;
    theStream >> FC_ExtractVar(aPriority);
    myPriority = (TSPII_PilotTonePriority)aPriority;
    return theStream;
}

FC_Stream& MON_PilotToneProcessorRequest::WriteObjectBinary(FC_Stream& theStream)
{
    theStream << myRequestId;
    theStream << myChannelId;
    theStream << mySamplingMode;
    theStream << myPriority;
    return theStream;
}

FC_Stream& MON_PilotToneProcessorRequest::ReadObjectBinary(FC_Stream& theStream)
{
    theStream >> myRequestId;
    theStream >> myChannelId;
    theStream >> mySamplingMode;
    uint32 aPriority;
    theStream >> aPriority;
    myPriority = (TSPII_PilotTonePriority)aPriority;
    return theStream;
}

void MON_PilotToneProcessorRequest::Display(FC_Stream& theStream)
{
    theStream << "Request ID: "<< myRequestId << endl;
    theStream << "Channel ID: "<< (uint32)myChannelId.WavelengthIndex() << endl;
    theStream << "Sampling  : "<< mySamplingMode << endl;
    theStream << "Priority  : "<< ((myPriority==TSPII_PT_LOW_PRIORITY) ? "LOW":"HIGH") << endl;
}
