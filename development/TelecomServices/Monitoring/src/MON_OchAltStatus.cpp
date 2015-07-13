// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchAltStatus.h"
#include <BaseClass/FC_TextStream.h>

//##ModelId=3C1A4D7C000D
MON_OchAltStatus::MON_OchAltStatus(uint32 theIndex):
    MON_Object(theIndex),
    myActualGain(0),
    myConfiguredGain(TRAFFIC_DEFAULT_POWER),
    myActivePath(0)
{
}

MON_OchAltStatus::MON_OchAltStatus(const MON_OchAltStatus& theOchAltStatus):
    MON_Object(theOchAltStatus),
    myActualGain(theOchAltStatus.myActualGain),
    myConfiguredGain(theOchAltStatus.myConfiguredGain),
    myActivePath(theOchAltStatus.myActivePath)
{
}

void MON_OchAltStatus::operator=(const MON_OchAltStatus& theOchAltStatus)
{
    MON_Object::operator=(theOchAltStatus);
    myActualGain = theOchAltStatus.myActualGain;
    myConfiguredGain = theOchAltStatus.myConfiguredGain;
    myActivePath = theOchAltStatus.myActivePath;
}

bool MON_OchAltStatus::operator==(const MON_OchAltStatus& theOchAltStatus) const
{
    if (!MON_Object::operator ==(theOchAltStatus))
        return false;

    bool equal=true;
    equal &= (myActualGain == theOchAltStatus.myActualGain);
    equal &= (myConfiguredGain == theOchAltStatus.myConfiguredGain);
    equal &= (myActivePath == theOchAltStatus.myActivePath);

    return equal;
}

//##ModelId=3C1A4D7C0016
MON_OchAltStatus::~MON_OchAltStatus(void )
{
}

//##ModelId=3C1A4D7C0020
void MON_OchAltStatus::Reset()
{
    MON_Object::Reset();
    myActualGain = 0;
    myConfiguredGain = 0;
    myActivePath = 0;
}

bool MON_OchAltStatus::SetActualGain(CT_TEL_mBm theGain)
{
    bool hasChanged=false;
    if (myActualGain!=theGain)
    {
        myActualGain=theGain;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_mBm MON_OchAltStatus::GetActualGain() const
{
    return myActualGain;
}


bool MON_OchAltStatus::SetConfiguredGain(CT_TEL_mBm theGain)
{
    bool hasChanged=false;
    if (myConfiguredGain!=theGain)
    {
        myConfiguredGain=theGain;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_mBm MON_OchAltStatus::GetConfiguredGain() const
{
    return myConfiguredGain;
}

bool MON_OchAltStatus::SetActivePath(bool theActivePath)
{
    bool hasChanged=false;
    if (myActivePath!=theActivePath)
    {
        myActivePath=theActivePath;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_OchAltStatus::GetActivePath() const
{
    return myActivePath;
}

ostream& MON_OchAltStatus::WriteObject(ostream& theStream)
{
    MON_Object::WriteObject(theStream);
    theStream <<  FC_InsertVar(myActualGain);
    theStream <<  FC_InsertVar(myConfiguredGain);
    theStream <<  FC_InsertVar(myActivePath);
    return theStream;
}

istream& MON_OchAltStatus::ReadObject(istream& theStream)
{
    MON_Object::ReadObject(theStream);
    theStream >>  FC_ExtractVar(myActualGain);
    theStream >>  FC_ExtractVar(myConfiguredGain);
    theStream >>  FC_ExtractVar(myActivePath);
    return theStream;
}

FC_Stream& MON_OchAltStatus::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << myActualGain;
    theStream << myConfiguredGain;
    theStream << myActivePath;
    return theStream;
}

FC_Stream& MON_OchAltStatus::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Object::ReadObjectBinary(theStream);
    theStream >> myActualGain;
    theStream >> myConfiguredGain;
    theStream >> myActivePath;
    return theStream;
}

void MON_OchAltStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "OCH     - Actual Gain                       = " << DISPLAY_MBM(myActualGain) <<" dB" << endl;
    theStream   << "OCH     - Configured Gain                   = " << DISPLAY_MBM(myConfiguredGain) <<" dB" << endl;
    theStream   << "OCH     - Active Path                       = " << DISPLAY_BOOL(myActivePath) <<" dB" << endl;
}

