//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OchAutoOnSC.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

CFG_OchAutoOnSC::CFG_OchAutoOnSC(uint32 theIndex):
    CFG_Object(theIndex),
    myGain(TRAFFIC_DEFAULT_POWER),
    myActivePath(false),
    myPortNumber(CT_TEL_INVALID_PORT_NUMBER)
{
}

CFG_OchAutoOnSC::~CFG_OchAutoOnSC()
{
}


void CFG_OchAutoOnSC::Reset()
{
    // Initialize all attributes to default values.
    myGain = TRAFFIC_DEFAULT_POWER;
    myActivePath = false;
    myPortNumber = CT_TEL_INVALID_PORT_NUMBER;
}

CT_TEL_mBm CFG_OchAutoOnSC::GetGain() const
{
    return myGain;
}

bool CFG_OchAutoOnSC::SetGain(CT_TEL_mBm theGain)
{
    bool hasChanged = false;
    if (theGain != myGain)
    {
        myGain = theGain;
        hasChanged = true;
    }
    return hasChanged;
}


bool CFG_OchAutoOnSC::GetActivePath() const
{
    return myActivePath;
}

bool CFG_OchAutoOnSC::SetActivePath(bool theActivePath)
{
    bool hasChanged = false;
    if (myActivePath != theActivePath)
    {
        myActivePath = theActivePath;
        hasChanged = true;
    }

    return hasChanged;
}

uint8 CFG_OchAutoOnSC::GetPortNumber() const
{
    return myPortNumber;
}

bool CFG_OchAutoOnSC::SetPortNumber(uint8 thePortNumber)
{
    bool hasChanged = false;
    if (myPortNumber != thePortNumber)
    {
        myPortNumber = thePortNumber;
    }

    return hasChanged;
}

ostream& CFG_OchAutoOnSC::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myGain);
    theStream << FC_InsertVar(myActivePath);
    theStream << FC_InsertVar(myPortNumber);
    
    return theStream;

}

istream& CFG_OchAutoOnSC::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myGain);
    theStream >> FC_ExtractVar(myActivePath);
    theStream >> FC_ExtractVar(myPortNumber);
    
    return theStream;

}

FC_Stream& CFG_OchAutoOnSC::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream << myGain;
    theStream << myActivePath;
    theStream << myPortNumber;
    
    return theStream;

}

FC_Stream& CFG_OchAutoOnSC::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream >> myGain;
    theStream >> myActivePath;
    theStream >> myPortNumber;
    
    return theStream;

}

FC_CmdProcessor::STATUS CFG_OchAutoOnSC::Set(int argc, char **argv)
{
    #if 0
    //We need 2 arguments
    if (argc < 2)
        goto OCHERROR;

    if (!strcmp(argv[0],"gain"))
        this->SetGain(atoi(argv[1]));
    else
        goto OCHERROR;

    return FC_CmdProcessor::E_SUCCESS;

OCHERROR:
    {
        fc_cout << "och <gain> <mBm>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
    #endif
    return FC_CmdProcessor::E_SUCCESS;
}

void CFG_OchAutoOnSC::Display( FC_Stream& theStream )
{
    theStream   << "OCH AUTO - Gain             [gain]          = " << DISPLAY_MBM(myGain) << endl;
}
