//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OchAutomatic.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

CFG_OchAutomatic::CFG_OchAutomatic(uint32 theIndex):
    CFG_Object(theIndex),
    myGain(TRAFFIC_DEFAULT_POWER)
{
}

CFG_OchAutomatic::~CFG_OchAutomatic()
{
}


void CFG_OchAutomatic::Reset()
{
    // Initialize all attributes to default values.
    myGain = TRAFFIC_DEFAULT_POWER;
}

CT_TEL_mBm CFG_OchAutomatic::GetGain() const
{
    return myGain;
}

bool CFG_OchAutomatic::SetGain(CT_TEL_mBm theGain)
{
    bool hasChanged = false;
    if (theGain != myGain)
    {
        myGain = theGain;
        hasChanged = true;
    }
    return hasChanged;
}

ostream& CFG_OchAutomatic::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myGain);
    return theStream;

}

istream& CFG_OchAutomatic::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myGain);
    return theStream;

}

FC_Stream& CFG_OchAutomatic::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream << myGain;
    return theStream;

}

FC_Stream& CFG_OchAutomatic::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream >> myGain;
    return theStream;

}

FC_CmdProcessor::STATUS CFG_OchAutomatic::Set(int argc, char **argv)
{
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
}

void CFG_OchAutomatic::Display( FC_Stream& theStream )
{
    theStream   << "OCH AUTO - Gain             [gain]          = " << DISPLAY_MBM(myGain) << endl;
}
