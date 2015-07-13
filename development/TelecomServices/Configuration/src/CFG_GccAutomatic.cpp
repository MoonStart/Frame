//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_GccAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_GccAutomatic::CFG_GccAutomatic(uint32 theIndex):
    myDisableLink(false),
    CFG_Object(theIndex)
{
}

CFG_GccAutomatic::~CFG_GccAutomatic()
{
}

bool CFG_GccAutomatic::SetDisableLink(bool theDisableLink)
{
    bool hasChanged = false;
    if(myDisableLink != theDisableLink)
    {
        myDisableLink = theDisableLink;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_GccAutomatic::GetDisableLink() const
{
    return myDisableLink;
}


void CFG_GccAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myDisableLink    = false;
}

ostream& CFG_GccAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myDisableLink);
    return theStream;

}

istream& CFG_GccAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myDisableLink);
    return theStream;

}

FC_Stream& CFG_GccAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myDisableLink;
    return theStream;

}

FC_Stream& CFG_GccAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myDisableLink;
    return theStream;

}

void CFG_GccAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "GCC AUTO - Disable Link                    = " << DISPLAY_BOOL(myDisableLink) << endl;
}
