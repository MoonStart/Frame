// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_DcclStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_DcclStatus::MON_DcclStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_DcclStatus::~MON_DcclStatus(void)
{
    // Nothing to do for now.
}


CT_DCC_LinkState MON_DcclStatus::GetProtocolLinkState() const 
{
    return myLinkState;
}

bool MON_DcclStatus::SetProtocolLinkState(CT_DCC_LinkState theLinkState) 
{
    bool hasChanged = false;
    if (!(myLinkState == theLinkState))
    {
        myLinkState = theLinkState;
        hasChanged = true;
    }

    return hasChanged;
}


bool MON_DcclStatus::GetTunnelSessionState() const 
{
    return myTunnelState;
}

bool MON_DcclStatus::SetTunnelSessionState(bool theTunnelState) 
{
    bool hasChanged = false;
    if (!(myTunnelState == theTunnelState))
    {
        myTunnelState = theTunnelState;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_DcclStatus::GetMagicNumber() const 
{
    return myMagicNumber;
}

bool MON_DcclStatus::SetMagicNumber(uint32 theMagicNumber) 
{
    bool hasChanged = false;
    if (!(myMagicNumber == theMagicNumber))
    {
        myMagicNumber = theMagicNumber;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_DcclStatus::GetIsSelected() const 
{
    return myIsSelected;
}

bool MON_DcclStatus::SetIsSelected(bool theSelectionState) 
{
    bool hasChanged = false;
    if (!(myIsSelected == theSelectionState))
    {
        myIsSelected = theSelectionState;
        hasChanged = true;
    }

    return hasChanged;
}


void MON_DcclStatus::Reset(void)
{
    MON_Object::Reset();
    myLinkState = CT_DCC_LINK_STATE_UNKNOWN;
    myTunnelState = false;
    myMagicNumber = 0;
    myIsSelected = false;

}

ostream& MON_DcclStatus::WriteObject( ostream& theStream )
{
    uint32 aLinkState = myLinkState;

    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(aLinkState);
    theStream << FC_InsertVar(myTunnelState);
    theStream << FC_InsertVar(myMagicNumber);
    theStream << FC_InsertVar(myIsSelected);
    return theStream;

}

istream& MON_DcclStatus::ReadObject( istream& theStream )
{
    uint32 aLinkState = 0;

    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(aLinkState);
    theStream >> FC_ExtractVar(myTunnelState);
    theStream >> FC_ExtractVar(myMagicNumber);
    theStream >> FC_ExtractVar(myIsSelected);

    myLinkState = (CT_DCC_LinkState)aLinkState;

    return theStream;

}

FC_Stream& MON_DcclStatus::WriteObjectBinary( FC_Stream& theStream )
{
    uint32 aLinkState = myLinkState;

    MON_Object::WriteObjectBinary(theStream);
    theStream << aLinkState;
    theStream << myTunnelState;
    theStream << myMagicNumber;
    theStream << myIsSelected;

    return theStream;

}

FC_Stream& MON_DcclStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    uint32 aLinkState = 0;

    MON_Object::ReadObjectBinary(theStream);
    theStream >> aLinkState;
    theStream >> myTunnelState;
    theStream >> myMagicNumber;
    theStream >> myIsSelected;

    myLinkState = (CT_DCC_LinkState)aLinkState;

    return theStream;

}

void MON_DcclStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "DCCL    - DCC Protocol Link State           = " << DISPLAY_DCC_LinkState(myLinkState) << endl;
    theStream   << "DCCL    - DCC Tunnel Session State          = " << DISPLAY_BOOL(myTunnelState) << endl;
    theStream   << "DCCL    - PPP Magic Number                  = " << myMagicNumber << endl;
    theStream   << "DCCL    - Selected For Traffic              = " << DISPLAY_BOOL(myIsSelected) << endl;
}
