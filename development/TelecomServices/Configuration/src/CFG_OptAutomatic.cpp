//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OptAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_OptAutomatic::CFG_OptAutomatic(uint32 theIndex):
    CFG_Object(theIndex),
	myLaserShutdown(false),
    myNearEndLaserShutdown(false),
    myLineSideProtExists(false),
    myForceFefi(false)
{
}

CFG_OptAutomatic::~CFG_OptAutomatic()
{
}


bool CFG_OptAutomatic::SetAutomaticLaserShutdown(bool theLaserShutdown)
{
    bool hasChanged = false;
    if(myLaserShutdown != theLaserShutdown)
    {
        myLaserShutdown = theLaserShutdown;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OptAutomatic::GetAutomaticLaserShutdown() const
{
    return myLaserShutdown;
}


bool CFG_OptAutomatic::SetNearEndAutomaticLaserShutdown(bool theNearEndLaserShutdown)
{
    bool hasChanged = false;
    if(myNearEndLaserShutdown != theNearEndLaserShutdown)
    {
        myNearEndLaserShutdown = theNearEndLaserShutdown;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OptAutomatic::GetNearEndAutomaticLaserShutdown() const
{
    return myNearEndLaserShutdown;
}


bool CFG_OptAutomatic::SetLineSideProtExists(bool theLineSideProtExists)
{
    bool hasChanged = false;
    if(myLineSideProtExists != theLineSideProtExists)
    {
        myLineSideProtExists = theLineSideProtExists;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OptAutomatic::GetLineSideProtExists() const
{
    return myLineSideProtExists;
}


bool CFG_OptAutomatic::SetForceFefi(bool theForceFefi)
{
    bool hasChanged = false;
    if(myForceFefi != theForceFefi)
    {
        myForceFefi = theForceFefi;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OptAutomatic::GetForceFefi() const
{
    return myForceFefi;
}


void CFG_OptAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myLaserShutdown        = false;
    myNearEndLaserShutdown = false;
    myLineSideProtExists   = false;
    myForceFefi            = false;
}

ostream& CFG_OptAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myLaserShutdown);
    theStream   << FC_InsertVar(myNearEndLaserShutdown);
    theStream   << FC_InsertVar(myLineSideProtExists);
    theStream   << FC_InsertVar(myForceFefi);
    return theStream;

}

istream& CFG_OptAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myLaserShutdown);
    theStream   >> FC_ExtractVar(myNearEndLaserShutdown);
    theStream   >> FC_ExtractVar(myLineSideProtExists);
    theStream   >> FC_ExtractVar(myForceFefi);
    return theStream;

}

FC_Stream& CFG_OptAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myLaserShutdown;
    theStream   << myNearEndLaserShutdown;
    theStream   << myLineSideProtExists;
    theStream   << myForceFefi;
    return theStream;

}

FC_Stream& CFG_OptAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myLaserShutdown;
    theStream   >> myNearEndLaserShutdown;
    theStream   >> myLineSideProtExists;
    theStream   >> myForceFefi;
    return theStream;

}

void CFG_OptAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "OPT AUTO - Laser Shutdown                   = " << DISPLAY_BOOL(myLaserShutdown) << endl;
    theStream   << "OPT AUTO - Near End Laser Shutdown          = " << DISPLAY_BOOL(myNearEndLaserShutdown) << endl;
    theStream   << "OPT AUTO - Line Side Protection Exists      = " << DISPLAY_BOOL(myLineSideProtExists) << endl;
    theStream   << "OPT AUTO - Force Fefi                       = " << DISPLAY_BOOL(myForceFefi) << endl;
}
