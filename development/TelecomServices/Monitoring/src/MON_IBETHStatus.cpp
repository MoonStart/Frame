// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_IBETHStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_IBETHStatus::MON_IBETHStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_IBETHStatus::~MON_IBETHStatus(void)
{
    // Nothing to do for now.
}


CT_IBETH_LinkState MON_IBETHStatus::GetProtocolLinkState() const 
{
    return myLinkState;
}

bool MON_IBETHStatus::SetProtocolLinkState(CT_IBETH_LinkState theLinkState) 
{
    bool hasChanged = false;
    if (!(myLinkState == theLinkState))
    {
        myLinkState = theLinkState;
        hasChanged = true;
    }

    return hasChanged;
}


void MON_IBETHStatus::Reset(void)
{
    MON_Object::Reset();
    myLinkState = CT_IBETH_LINK_STATE_UNKNOWN;
}

ostream& MON_IBETHStatus::WriteObject( ostream& theStream )
{
    uint32 aLinkState = myLinkState;

    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(aLinkState);
  
    return theStream;
}

istream& MON_IBETHStatus::ReadObject( istream& theStream )
{
    uint32 aLinkState = 0;

    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(aLinkState);
    
    myLinkState = (CT_IBETH_LinkState)aLinkState;

    return theStream;

}

FC_Stream& MON_IBETHStatus::WriteObjectBinary( FC_Stream& theStream )
{
    uint32 aLinkState = myLinkState;

    MON_Object::WriteObjectBinary(theStream);
    theStream << aLinkState;

    return theStream;

}

FC_Stream& MON_IBETHStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    uint32 aLinkState = 0;

    MON_Object::ReadObjectBinary(theStream);
    theStream >> aLinkState;
   

    myLinkState = (CT_IBETH_LinkState)aLinkState;

    return theStream;

}

void MON_IBETHStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "IBETH    - IBETH Protocol Link State           = " << DISPLAY_IBETH_LinkState(myLinkState) << endl;
    
}
