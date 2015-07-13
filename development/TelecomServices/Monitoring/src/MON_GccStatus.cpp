// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_GccStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_GccStatus::MON_GccStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_GccStatus::~MON_GccStatus(void)
{
    // Nothing to do for now.
}


CT_DCC_LinkState MON_GccStatus::GetProtocolLinkState() const 
{
    return myLinkState;
}

bool MON_GccStatus::SetProtocolLinkState(CT_DCC_LinkState theLinkState) 
{
    bool hasChanged = false;
    if (!(myLinkState == theLinkState))
    {
        myLinkState = theLinkState;
        hasChanged = true;
    }

    return hasChanged;
}


bool MON_GccStatus::GetTunnelSessionState() const 
{
    return myTunnelState;
}

bool MON_GccStatus::SetTunnelSessionState(bool theTunnelState) 
{
    bool hasChanged = false;
    if (!(myTunnelState == theTunnelState))
    {
        myTunnelState = theTunnelState;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_GccStatus::GetMagicNumber() const 
{
    return myMagicNumber;
}

bool MON_GccStatus::SetMagicNumber(uint32 theMagicNumber) 
{
    bool hasChanged = false;
    if (!(myMagicNumber == theMagicNumber))
    {
        myMagicNumber = theMagicNumber;
        hasChanged = true;
    }

    return hasChanged;
}

void MON_GccStatus::Reset(void)
{
    MON_Object::Reset();
    myLinkState = CT_DCC_LINK_STATE_UNKNOWN;
    myTunnelState = false;
    myMagicNumber = 0;
}

ostream& MON_GccStatus::WriteObject( ostream& theStream )
{
    uint32 aLinkState = myLinkState;

    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(aLinkState);
    theStream << FC_InsertVar(myTunnelState);
    theStream << FC_InsertVar(myMagicNumber);
    return theStream;
}

istream& MON_GccStatus::ReadObject( istream& theStream )
{
    uint32 aLinkState = 0;

    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(aLinkState);
    theStream >> FC_ExtractVar(myTunnelState);
    theStream >> FC_ExtractVar(myMagicNumber);

    myLinkState = (CT_DCC_LinkState)aLinkState;

    return theStream;

}

FC_Stream& MON_GccStatus::WriteObjectBinary( FC_Stream& theStream )
{
    uint32 aLinkState = myLinkState;

    MON_Object::WriteObjectBinary(theStream);
    theStream << aLinkState;
    theStream << myTunnelState;
    theStream << myMagicNumber;

    return theStream;

}

FC_Stream& MON_GccStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    uint32 aLinkState = 0;

    MON_Object::ReadObjectBinary(theStream);
    theStream >> aLinkState;
    theStream >> myTunnelState;
    theStream >> myMagicNumber;

    myLinkState = (CT_DCC_LinkState)aLinkState;

    return theStream;

}

void MON_GccStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "GCC    - GCC Protocol Link State           = " << DISPLAY_DCC_LinkState(myLinkState) << endl;
    theStream   << "GCC    - GCC Tunnel Session State          = " << DISPLAY_BOOL(myTunnelState) << endl;
    theStream   << "GCC    - PPP Magic Number                  = " << myMagicNumber << endl;
}
