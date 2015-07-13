// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_DrtrStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_DrtrStatus::MON_DrtrStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_DrtrStatus::~MON_DrtrStatus(void)
{
    // Nothing to do for now.
}


CT_DCC_RouterState MON_DrtrStatus::GetLevel1_RouterState() const 
{
    return myLevel1_RouterState;
}

bool MON_DrtrStatus::SetLevel1_RouterState(CT_DCC_RouterState theRouterState) 
{
    bool hasChanged = false;
    if (!(myLevel1_RouterState == theRouterState))
    {
        myLevel1_RouterState = theRouterState;
        hasChanged = true;
    }

    return hasChanged;
}

CT_DCC_RouterState MON_DrtrStatus::GetLevel2_RouterState() const 
{
    return myLevel2_RouterState;
}


bool MON_DrtrStatus::SetLevel2_RouterState(CT_DCC_RouterState theRouterState) 
{
    bool hasChanged = false;
    if (!(myLevel2_RouterState == theRouterState))
    {
        myLevel2_RouterState = theRouterState;
        hasChanged = true;
    }

    return hasChanged;
}


uint32 MON_DrtrStatus::GetSequenceNumber() const 
{
    return mySequenceNumber;
}

bool MON_DrtrStatus::SetSequenceNumber(uint32 theSequenceNumber) 
{
    bool hasChanged = false;
    if (mySequenceNumber != theSequenceNumber)
    {
        mySequenceNumber = theSequenceNumber;
        hasChanged = true;
    }

    return hasChanged;
}


void MON_DrtrStatus::Reset(void)
{
    MON_Object::Reset();
    myLevel1_RouterState = CT_DCC_ROUTER_STATE_UNKNOWN;
    myLevel2_RouterState = CT_DCC_ROUTER_STATE_UNKNOWN;
    mySequenceNumber = 0;

}

ostream& MON_DrtrStatus::WriteObject( ostream& theStream )
{

    MON_Object::WriteObject(theStream);

    uint32 aLevel1_RouterState = (uint32) myLevel1_RouterState;
    uint32 aLevel2_RouterState = (uint32) myLevel2_RouterState;

    theStream << FC_InsertVar(aLevel1_RouterState);
    theStream << FC_InsertVar(aLevel2_RouterState);
    theStream << FC_InsertVar(mySequenceNumber);

    return theStream;

}

istream& MON_DrtrStatus::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);

    uint32 aLevel1_RouterState = 0;
    uint32 aLevel2_RouterState = 0;

    theStream >> FC_ExtractVar(aLevel1_RouterState);
    theStream >> FC_ExtractVar(aLevel2_RouterState);
    theStream >> FC_ExtractVar(mySequenceNumber);

    myLevel1_RouterState = (CT_DCC_RouterState)aLevel1_RouterState;
    myLevel2_RouterState = (CT_DCC_RouterState)aLevel2_RouterState;

    return theStream;

}

FC_Stream& MON_DrtrStatus::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);

    uint32 aLevel1_RouterState = (uint32) myLevel1_RouterState;
    uint32 aLevel2_RouterState = (uint32) myLevel2_RouterState;

    theStream << aLevel1_RouterState;
    theStream << aLevel2_RouterState;
    theStream << mySequenceNumber;

    return theStream;

}

FC_Stream& MON_DrtrStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Object::ReadObjectBinary(theStream);

    uint32 aLevel1_RouterState = 0;
    uint32 aLevel2_RouterState = 0;

    theStream >> aLevel1_RouterState;
    theStream >> aLevel2_RouterState;
    theStream >> mySequenceNumber;

    myLevel1_RouterState = (CT_DCC_RouterState)aLevel1_RouterState;
    myLevel2_RouterState = (CT_DCC_RouterState)aLevel2_RouterState;

    return theStream;

}

void MON_DrtrStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "DRTR    - DCC Level 1 Router State          = " << DISPLAY_DCC_RouterState(myLevel1_RouterState) << endl;
    theStream   << "DRTR    - DCC Level 2 Router State          = " << DISPLAY_DCC_RouterState(myLevel2_RouterState) << endl;
    theStream   << "DRTR    - Sequence Number                   = " << mySequenceNumber << endl;
}
