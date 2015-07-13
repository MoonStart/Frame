//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_T1E1Automatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_T1E1Automatic::CFG_T1E1Automatic(uint32 theIndex):
    myDisqualifyRef(false),
    CFG_Object(theIndex)
{
}

CFG_T1E1Automatic::~CFG_T1E1Automatic()
{
}

bool CFG_T1E1Automatic::SetDisqualifyRef(bool theDisqualifyRef)
{
    bool hasChanged = false;
    if(myDisqualifyRef != theDisqualifyRef)
    {
        myDisqualifyRef = theDisqualifyRef;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_T1E1Automatic::GetDisqualifyRef() const
{
    return myDisqualifyRef;
}


void CFG_T1E1Automatic::Reset()
{
    // Initialize all attributes to default values.
    myDisqualifyRef    = false;
}

ostream& CFG_T1E1Automatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myDisqualifyRef);
    return theStream;

}

istream& CFG_T1E1Automatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myDisqualifyRef);
    return theStream;

}

FC_Stream& CFG_T1E1Automatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myDisqualifyRef;
    return theStream;

}

FC_Stream& CFG_T1E1Automatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myDisqualifyRef;
    return theStream;

}

void CFG_T1E1Automatic::Display( FC_Stream& theStream )
{
    theStream   << "T1E1 AUTO  - Disqualify Reference                     = " << DISPLAY_BOOL(myDisqualifyRef) << endl;
}
