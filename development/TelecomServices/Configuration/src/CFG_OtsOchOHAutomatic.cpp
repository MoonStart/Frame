//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OtsOchOHAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_OtsOchOHAutomatic::CFG_OtsOchOHAutomatic(uint32 theIndex):
    CFG_Object(theIndex),
    myForceFDIO(false),
    myForceFDIP(false),
    myForceOCI(false),
    myForceFDIPOS(false)
{
}

CFG_OtsOchOHAutomatic::~CFG_OtsOchOHAutomatic()
{
}


void CFG_OtsOchOHAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myForceFDIO = false;
    myForceFDIP = false;
    myForceOCI = false;
}


bool CFG_OtsOchOHAutomatic::SetForceFDIO(bool theForceFDIO)
{
    bool hasChanged = false;
    if(myForceFDIO != theForceFDIO)
    {
        myForceFDIO = theForceFDIO;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsOchOHAutomatic::GetForceFDIO() const
{
    return myForceFDIO;
}

bool CFG_OtsOchOHAutomatic::SetForceFDIP(bool theForceFDIP)
{
    bool hasChanged = false;
    if(myForceFDIP != theForceFDIP)
    {
        myForceFDIP = theForceFDIP;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsOchOHAutomatic::GetForceFDIP() const
{
    return myForceFDIP;
}

bool CFG_OtsOchOHAutomatic::SetForceFDIPOS(bool theForceFDIPOS)
{
    bool hasChanged = false;
    if(myForceFDIPOS != theForceFDIPOS)
    {
        myForceFDIPOS = theForceFDIPOS;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsOchOHAutomatic::GetForceFDIPOS() const
{
    return myForceFDIPOS;
}

bool CFG_OtsOchOHAutomatic::SetForceOCI(bool theForceOCI)
{
    bool hasChanged = false;
    if(myForceOCI != theForceOCI)
    {
        myForceOCI = theForceOCI;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsOchOHAutomatic::GetForceOCI() const
{
    return myForceOCI;
}

ostream& CFG_OtsOchOHAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceFDIO);
    theStream   << FC_InsertVar(myForceFDIP);
    theStream   << FC_InsertVar(myForceOCI);
    return theStream;

}

istream& CFG_OtsOchOHAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceFDIO);
    theStream   >> FC_ExtractVar(myForceFDIP);
    theStream   >> FC_ExtractVar(myForceOCI);
    return theStream;

}

FC_Stream& CFG_OtsOchOHAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceFDIO;
    theStream   << myForceFDIP;
    theStream   << myForceOCI;
    return theStream;

}

FC_Stream& CFG_OtsOchOHAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myForceFDIO;
    theStream   >> myForceFDIP;
    theStream   >> myForceOCI;
    return theStream;

}

void CFG_OtsOchOHAutomatic::Display( FC_Stream& theStream )
{
    theStream   << DISPLAY_BOOL(myForceFDIP) << "\t"
                << DISPLAY_BOOL(myForceFDIO) << "\t"
                << DISPLAY_BOOL(myForceOCI)  << "\t" << endl;
}
