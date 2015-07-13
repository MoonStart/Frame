//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OtsAutomatic.h"
#include <BaseClass/FC_TextStream.h>

CFG_OtsAutomatic::CFG_OtsAutomatic(uint32 theIndex):
    CFG_Object(theIndex),
    myForceOtsBDIO(false),
    myForceOtsBDIP(false),
    myForceOtsPMI(false),
    myForceOmsFDIO(false),
    myForceOmsFDIP(false),
    myForceOTS_PMIReason("")
{
}

CFG_OtsAutomatic::~CFG_OtsAutomatic()
{
}


void CFG_OtsAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myForceOtsBDIO = false;
    myForceOtsBDIP = false;
    myForceOtsPMI = false;
    myForceOmsFDIO = false;
    myForceOmsFDIP = false;
    myForceOTS_PMIReason = "";
}


bool CFG_OtsAutomatic::SetForceOtsBDIO(bool theForceOtsBDIO)
{
    bool hasChanged = false;
    if(myForceOtsBDIO != theForceOtsBDIO)
    {
        myForceOtsBDIO = theForceOtsBDIO;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsAutomatic::GetForceOtsBDIO() const
{
    return myForceOtsBDIO;
}

bool CFG_OtsAutomatic::SetForceOtsBDIP(bool theForceOtsBDIP)
{
    bool hasChanged = false;
    if(myForceOtsBDIP != theForceOtsBDIP)
    {
        myForceOtsBDIP = theForceOtsBDIP;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsAutomatic::GetForceOtsBDIP() const
{
    return myForceOtsBDIP;
}

bool CFG_OtsAutomatic::SetForceOtsPMI(bool theForceOtsPMI)
{
    bool hasChanged = false;
    if(myForceOtsPMI != theForceOtsPMI)
    {
        myForceOtsPMI = theForceOtsPMI;
        hasChanged = true;
    }

    if(!myForceOtsPMI)
    {
        myForceOTS_PMIReason = "";
    }
    
    return hasChanged;
}

bool CFG_OtsAutomatic::GetForceOtsPMI() const
{
    return myForceOtsPMI;
}

void CFG_OtsAutomatic::SetForceOtsPMIReason(string theReason)
{
    myForceOTS_PMIReason = theReason;
}

bool CFG_OtsAutomatic::SetForceOmsFDIO(bool theForceOmsFDIO)
{
    bool hasChanged = false;
    if(myForceOmsFDIO != theForceOmsFDIO)
    {
        myForceOmsFDIO = theForceOmsFDIO;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsAutomatic::GetForceOmsFDIO() const
{
    return myForceOmsFDIO;
}

bool CFG_OtsAutomatic::SetForceOmsFDIP(bool theForceOmsFDIP)
{
    bool hasChanged = false;
    if(myForceOmsFDIP != theForceOmsFDIP)
    {
        myForceOmsFDIP = theForceOmsFDIP;
        hasChanged = true;
    }
    return hasChanged;
}

bool CFG_OtsAutomatic::GetForceOmsFDIP() const
{
    return myForceOmsFDIP;
}

ostream& CFG_OtsAutomatic::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceOtsBDIO);
    theStream   << FC_InsertVar(myForceOtsBDIP);
    theStream   << FC_InsertVar(myForceOtsPMI);
    theStream   << FC_InsertVar(myForceOmsFDIO);
    theStream   << FC_InsertVar(myForceOmsFDIP);
    return theStream;

}

istream& CFG_OtsAutomatic::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceOtsBDIO);
    theStream   >> FC_ExtractVar(myForceOtsBDIP);
    theStream   >> FC_ExtractVar(myForceOtsPMI);
    theStream   >> FC_ExtractVar(myForceOmsFDIO);
    theStream   >> FC_ExtractVar(myForceOmsFDIP);
    return theStream;

}

FC_Stream& CFG_OtsAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceOtsBDIO;
    theStream   << myForceOtsBDIP;
    theStream   << myForceOtsPMI;
    theStream   << myForceOmsFDIO;
    theStream   << myForceOmsFDIP;
    return theStream;

}

FC_Stream& CFG_OtsAutomatic::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >> myForceOtsBDIO;
    theStream   >> myForceOtsBDIP;
    theStream   >> myForceOtsPMI;
    theStream   >> myForceOmsFDIO;
    theStream   >> myForceOmsFDIP;
    return theStream;

}

void CFG_OtsAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "OTS AUTO - Force BDI-O                      = " << DISPLAY_BOOL(myForceOtsBDIO) << endl;
    theStream   << "OTS AUTO - Force BDI-P                      = " << DISPLAY_BOOL(myForceOtsBDIP) << endl;
    theStream   << "OTS AUTO - Force PMI                        = " << DISPLAY_BOOL(myForceOtsPMI) << " (" << myForceOTS_PMIReason << ")" << endl;
    theStream   << "OMS AUTO - Force FDI-O                      = " << DISPLAY_BOOL(myForceOmsFDIO) << endl;
    theStream   << "OMS AUTO - Force FDI-P                      = " << DISPLAY_BOOL(myForceOmsFDIP) << endl;
}
