//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_HopAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_HopAutomatic::CFG_HopAutomatic(uint32 theIndex):
    myForceInternalAIS(false),
    CFG_Object(theIndex)
{
}

CFG_HopAutomatic::~CFG_HopAutomatic()
{
}

bool CFG_HopAutomatic::SetForceInternalAIS(bool theForceInternalAIS)
{
    bool hasChanged = false;
    if(myForceInternalAIS != theForceInternalAIS)
    {
        myForceInternalAIS = theForceInternalAIS;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_HopAutomatic::GetForceInternalAIS() const
{
    return myForceInternalAIS;
}


void CFG_HopAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myForceInternalAIS    = false;
}

ostream& CFG_HopAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceInternalAIS);
    return theStream;

}

istream& CFG_HopAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceInternalAIS);
    return theStream;

}

FC_Stream& CFG_HopAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceInternalAIS;
    return theStream;

}

FC_Stream& CFG_HopAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myForceInternalAIS;
    return theStream;

}

void CFG_HopAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "HOP AUTO - Force Internal AIS               = " << DISPLAY_BOOL(myForceInternalAIS) << endl;
}
