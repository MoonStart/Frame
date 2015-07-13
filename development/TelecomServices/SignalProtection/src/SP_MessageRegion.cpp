// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_MessageRegion.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

const FC_BbKey SP_RX_MSGREGION_KEY = "SP_RX_MSG";
const FC_BbKey SP_TX_MSGREGION_KEY = "SP_TX_MSG";


SP_Message::SP_Message()
{
	Reset();
}

SP_Message::~SP_Message()
{
}

void SP_Message::SetMessage(CT_Port& theSrcAddress, CT_Port& theDstAddress, uint8 theMessage)
{
    myMessage = theMessage;
    mySrcAddress = theSrcAddress;
    myDstAddress = theDstAddress;
}

void SP_Message::SetMessage(uint8 theMessage, uint8 theMask)
{
    // Clear out current bits based on mask
    myMessage &= ~(theMask);
    // Set new bits based on mask
    myMessage |= (theMessage & theMask);

}

CT_Port& SP_Message::GetSrcAddress()
{
    return mySrcAddress;
}

CT_Port& SP_Message::GetDstAddress()
{
    return myDstAddress;
}

uint8 SP_Message::GetMessage()
{
    return myMessage;
}

void SP_Message::IncMessageRxCounter()
{
    myMessageRxCounter++;
}

uint32 SP_Message::GetMessageRxCounter()
{
    return myMessageRxCounter;
}

void SP_Message::Reset()
{
    myMessage =0;
    mySrcAddress = CT_Port();
    myDstAddress = CT_Port();
    myMessageRxCounter =0;
}

ostream& SP_Message::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myMessage);
    theStream << FC_InsertVar(mySrcAddress);
    theStream << FC_InsertVar(myDstAddress);
    theStream << FC_InsertVar(myMessageRxCounter);
    return theStream;
}

istream& SP_Message::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myMessage);
    theStream >> FC_ExtractVar(mySrcAddress);
    theStream >> FC_ExtractVar(myDstAddress);
    theStream >> FC_ExtractVar(myMessageRxCounter);
    return theStream;
}

FC_Stream& SP_Message::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myMessage;
    theStream << mySrcAddress;
    theStream << myDstAddress;
    theStream << myMessageRxCounter;
    return theStream;
}

FC_Stream& SP_Message::ReadObjectBinary( FC_Stream& theStream ) 
{
    theStream >> myMessage;
    theStream >> mySrcAddress;
    theStream >> myDstAddress;
    theStream >> myMessageRxCounter;
    return theStream;
}


SP_MessageRegion::SP_MessageRegion()
{
}

SP_MessageRegion::SP_MessageRegion(	const FC_BbKey theKey, int theSize)
:TEL_BbRegionBaseImp<SP_Message>( theKey, theSize)
{
}

SP_MessageRegion::~SP_MessageRegion()
{
}
