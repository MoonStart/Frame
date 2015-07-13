//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OmsAutomaticShutdown.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>

CFG_OmsAutomaticShutdown::CFG_OmsAutomaticShutdown(uint32 theIndex):
    CFG_Object(theIndex),
    myAmplifierShutdown(false)
{
}

CFG_OmsAutomaticShutdown::~CFG_OmsAutomaticShutdown(void)
{
}


void CFG_OmsAutomaticShutdown::Reset(void)
{
    myAmplifierShutdown = false;
}

bool CFG_OmsAutomaticShutdown::GetAmplifierShutdown() const
{
    return myAmplifierShutdown;
}

bool CFG_OmsAutomaticShutdown::SetAmplifierShutdown(bool theAmplifierShutdown)
{
    bool hasChanged=false;
    if (myAmplifierShutdown != theAmplifierShutdown)
    {
        myAmplifierShutdown = theAmplifierShutdown;
        hasChanged = true;
    }
    return hasChanged;
}


ostream& CFG_OmsAutomaticShutdown::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
	theStream << FC_InsertVar(myAmplifierShutdown);
    return theStream;
}


istream& CFG_OmsAutomaticShutdown::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
	theStream >> FC_ExtractVar(myAmplifierShutdown);
    return theStream;
}

FC_Stream& CFG_OmsAutomaticShutdown::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
	theStream << myAmplifierShutdown;
    return theStream;
}

FC_Stream& CFG_OmsAutomaticShutdown::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
	theStream >> myAmplifierShutdown;
    return theStream;
}

void CFG_OmsAutomaticShutdown::Display( FC_Stream& theStream )
{
    theStream   << "OMS AUTO - Automatic Amp. Shutdown          = " << DISPLAY_BOOL(myAmplifierShutdown) << endl;
}
