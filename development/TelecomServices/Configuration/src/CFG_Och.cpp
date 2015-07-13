//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Och.h"
#include "BaseClass/FC_TextStream.h"
#include "ErrorService/FC_Error.h"
#include <string.h>

const CT_TEL_mBm CFG_MAX_DEFAULT_GAIN = 0;

CFG_Och::CFG_Och(uint32 theIndex):
    CFG_Object(theIndex),
    myAutoPowerAdjEnable(false),
    myGain(CFG_MAX_DEFAULT_GAIN)
{
}

CFG_Och::~CFG_Och(void)
{
}

void CFG_Och::Reset(void)
{
    myAutoPowerAdjEnable = false;
    myGain = CFG_MAX_DEFAULT_GAIN;
}

bool CFG_Och::GetAutoPowerAdjEnable() const
{
    return myAutoPowerAdjEnable;
}

void CFG_Och::SetAutoPowerAdjEnable(bool theAutoPowerAdjEnable)
{
    myAutoPowerAdjEnable = theAutoPowerAdjEnable;
}

CT_TEL_mBm CFG_Och::GetGain() const
{
    return myGain;
}

void CFG_Och::SetGain(CT_TEL_mBm theGain)
{
    myGain = theGain;
}


// For Display
ostream& CFG_Och::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myAutoPowerAdjEnable);
    theStream << FC_InsertVar(myGain);
    return theStream;

}

// For Display
istream& CFG_Och::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myAutoPowerAdjEnable);
    theStream >> FC_ExtractVar(myGain);
    return theStream;

}

// For persitance and region transfer
FC_Stream& CFG_Och::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream << myAutoPowerAdjEnable;
    theStream << myGain;
    return theStream;

}

// For persitance and region transfer
FC_Stream& CFG_Och::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream >> myAutoPowerAdjEnable;
    theStream >> myGain;
    return theStream;

}

FC_CmdProcessor::STATUS CFG_Och::Set(int argc, char **argv)
{
    //We need 2 arguments
    if (argc < 2)
        goto OCHERROR;

    if (!strcmp(argv[0],"autopowadj"))
    {
        SetAutoPowerAdjEnable(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"gain"))
    {
        SetGain(atoi(argv[1]));
    }
    else
    {
        goto OCHERROR;
    }
    return FC_CmdProcessor::E_SUCCESS;

OCHERROR:
    {
        fc_cout << "och <autopowadj> <e-nable|d-isable> " << endl;
        fc_cout << "och <gain> <gain in mBm>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Och::Display( FC_Stream& theStream )
{
    theStream   << "OCH      - Gain             [gain]          = " << DISPLAY_MBM(myGain) << endl;
    theStream   << "OCH      - Auto Pwr. Adj.   [autopwradj]    = " << DISPLAY_BOOL(myAutoPowerAdjEnable) << endl;
}
