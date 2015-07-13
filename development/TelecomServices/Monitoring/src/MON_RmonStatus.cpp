// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_RmonStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_RmonStatus::MON_RmonStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_RmonStatus::~MON_RmonStatus(void)
{
    // Nothing to do for now.
}

uint32 MON_RmonStatus::GetIfPhysAddressHigh() const
{
    return myIfPhysAddressHigh;
}

bool MON_RmonStatus::SetIfPhysAddressHigh(uint32 theIfPhysAddressHigh)
{
    bool hasChanged = false;
    if (!(myIfPhysAddressHigh == theIfPhysAddressHigh))
    {
        myIfPhysAddressHigh = theIfPhysAddressHigh;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_RmonStatus::GetIfPhysAddressLow() const
{
    return myIfPhysAddressLow;
}

bool MON_RmonStatus::SetIfPhysAddressLow(uint32 theIfPhysAddressLow)
{
    bool hasChanged = false;
    if (!(myIfPhysAddressLow == theIfPhysAddressLow))
    {
        myIfPhysAddressLow = theIfPhysAddressLow;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_RmonStatus::GetIfMtu() const
{
    return myIfMtu;
}

bool MON_RmonStatus::SetIfMtu(uint32 theIfMtu)
{
    bool hasChanged = false;
    if (!(myIfMtu == theIfMtu))
    {
        myIfMtu = theIfMtu;
        hasChanged = true;
    }

    return hasChanged;
}

void MON_RmonStatus::Reset(void)
{
    MON_Object::Reset();
    myIfPhysAddressHigh = 0;
    myIfPhysAddressLow  = 0;
    myIfMtu             = 0;
}




ostream& MON_RmonStatus::WriteObject( ostream& theStream )
{

    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myIfPhysAddressHigh);
    theStream << FC_InsertVar(myIfPhysAddressLow);
    theStream << FC_InsertVar(myIfMtu);
    return theStream;
}

istream& MON_RmonStatus::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myIfPhysAddressHigh);
    theStream >> FC_ExtractVar(myIfPhysAddressLow);
    theStream >> FC_ExtractVar(myIfMtu);
    return theStream;

}

FC_Stream& MON_RmonStatus::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << myIfPhysAddressHigh;
    theStream << myIfPhysAddressLow;
    theStream << myIfMtu;
    return theStream;

}

FC_Stream& MON_RmonStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myIfPhysAddressHigh;
    theStream >> myIfPhysAddressLow;
    theStream >> myIfMtu;
    return theStream;

}

void MON_RmonStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "RMON    - Interface Physical Address - High = " << myIfPhysAddressHigh << endl;
    theStream   << "RMON    - Interface Physical Address - Low  = " << myIfPhysAddressLow << endl;
    theStream   << "RMON    - Interface MTU Size                = " << myIfMtu << endl;
}
