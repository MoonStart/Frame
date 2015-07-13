//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_DcclAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_DcclAutomatic::CFG_DcclAutomatic(uint32 theIndex):
    myDisableLink(false),
    CFG_Object(theIndex)
{
}

CFG_DcclAutomatic::~CFG_DcclAutomatic()
{
}

bool CFG_DcclAutomatic::SetDisableLink(bool theDisableLink)
{
    bool hasChanged = false;
    if(myDisableLink != theDisableLink)
    {
        myDisableLink = theDisableLink;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_DcclAutomatic::GetDisableLink() const
{
    return myDisableLink;
}


void CFG_DcclAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myDisableLink    = false;
}

ostream& CFG_DcclAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myDisableLink);
    return theStream;

}

istream& CFG_DcclAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myDisableLink);
    return theStream;

}

FC_Stream& CFG_DcclAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myDisableLink;
    return theStream;

}

FC_Stream& CFG_DcclAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myDisableLink;
    return theStream;

}

void CFG_DcclAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "DCCL AUTO - Disable Link                    = " << DISPLAY_BOOL(myDisableLink) << endl;
}
