//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_MacAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_MacAutomatic::CFG_MacAutomatic(uint32 theIndex):
    //myRemoteFaultForced(false),
    //myFefiEnabled(false),
    CFG_Object(theIndex)    
{
}

CFG_MacAutomatic::~CFG_MacAutomatic()
{
}

/*bool CFG_MacAutomatic::SetRemoteFaultForced(bool theRemoteFaultForced)
{
    bool hasChanged = false;
    if (myRemoteFaultForced != theRemoteFaultForced)
    {
        myRemoteFaultForced = theRemoteFaultForced;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_MacAutomatic::GetRemoteFaultForced() const
{
    return(myRemoteFaultForced);
}*/

/*bool CFG_MacAutomatic::SetFefiEnabled(bool theFefiEnabled)
{
    bool hasChanged = false;
    if(myFefiEnabled != theFefiEnabled)
    {
        myFefiEnabled = theFefiEnabled;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_MacAutomatic::GetFefiEnabled() const
{
    return myFefiEnabled;
}*/

void CFG_MacAutomatic::Reset()
{
    // Initialize all attributes to default values.
    //myRemoteFaultForced = false;
    //myFefiEnabled = false;
}

ostream& CFG_MacAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    //theStream   << FC_InsertVar(myRemoteFaultForced);   
    //theStream   << FC_InsertVar(myFefiEnabled);   
    return theStream;
}

istream& CFG_MacAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    //theStream   >> FC_ExtractVar(myRemoteFaultForced); 
    //theStream   >> FC_ExtractVar(myFefiEnabled);
    return theStream;

}

FC_Stream& CFG_MacAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    //theStream   << myRemoteFaultForced;
    //theStream   << myFefiEnabled;
    return theStream;
}

FC_Stream& CFG_MacAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    //theStream   >> myRemoteFaultForced;
    //theStream   >> myFefiEnabled;
    return theStream;
}

void CFG_MacAutomatic::Display( FC_Stream& theStream )
{
    //theStream   << "MAC AUTO  - Force Link Fail Tx                = " << DISPLAY_BOOL(myRemoteFaultForced) << endl; 
    //theStream   << "MAC AUTO  - FEFI                              = " << DISPLAY_BOOL(myFefiEnabled) << endl; 
}
