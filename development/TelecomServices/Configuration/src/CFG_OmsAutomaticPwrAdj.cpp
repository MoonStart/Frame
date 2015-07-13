//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OmsAutomaticPwrAdj.h"
#include "BaseClass/FC_TextStream.h"
#include "ErrorService/FC_Error.h"
#include <string.h>

CFG_OmsAutomaticPwrAdj::CFG_OmsAutomaticPwrAdj(uint32 theIndex):
    CFG_Object(theIndex),
    myGain(TRAFFIC_CFG_DEFAULT_VALUE),
    myGainTilt(TRAFFIC_CFG_DEFAULT_VALUE),
    myGroupEvoa(TRAFFIC_CFG_DEFAULT_VALUE)
{
}

CFG_OmsAutomaticPwrAdj::~CFG_OmsAutomaticPwrAdj(void)
{
}


void CFG_OmsAutomaticPwrAdj::Reset(void)
{
    myGain = TRAFFIC_CFG_DEFAULT_VALUE;
    myGainTilt = TRAFFIC_CFG_DEFAULT_VALUE;
    myGroupEvoa = TRAFFIC_CFG_DEFAULT_VALUE;
}

CT_TEL_mBm CFG_OmsAutomaticPwrAdj::GetGain() const
{
    return myGain;
}

bool CFG_OmsAutomaticPwrAdj::SetGain(CT_TEL_mBm theGain)
{
    bool hasChanged = false;
    if (myGain != theGain)
    {
        myGain = theGain;
        hasChanged = true;
    }
    return hasChanged;
}


CT_TEL_mBm CFG_OmsAutomaticPwrAdj::GetGainTilt() const
{
    return myGainTilt;
}

bool CFG_OmsAutomaticPwrAdj::SetGainTilt(CT_TEL_mBm theGainTilt)
{
    bool hasChanged = false;
    if (myGainTilt != theGainTilt)
    {
        myGainTilt = theGainTilt;
        hasChanged = true;
    }
    return hasChanged;
}


CT_TEL_mBm CFG_OmsAutomaticPwrAdj::GetGroupEvoa() const
{
    return myGroupEvoa;
}

bool CFG_OmsAutomaticPwrAdj::SetGroupEvoa(CT_TEL_mBm theEvoa)
{
    bool hasChanged = false;
    if (myGroupEvoa != theEvoa)
    {
        myGroupEvoa = theEvoa;
        hasChanged = true;
    }
    return hasChanged;
}


ostream& CFG_OmsAutomaticPwrAdj::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myGain);
    theStream << FC_InsertVar(myGainTilt);
    theStream << FC_InsertVar(myGroupEvoa);
    return theStream;
}

istream& CFG_OmsAutomaticPwrAdj::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myGain);
    theStream >> FC_ExtractVar(myGainTilt);
    theStream >> FC_ExtractVar(myGroupEvoa);
    return theStream;
}

FC_Stream& CFG_OmsAutomaticPwrAdj::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream << myGain;
    theStream << myGainTilt;
    theStream << myGroupEvoa;
    return theStream;
}

FC_Stream& CFG_OmsAutomaticPwrAdj::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream >> myGain;
    theStream >> myGainTilt;
    theStream >> myGroupEvoa;
    return theStream;
}

void CFG_OmsAutomaticPwrAdj::Display( FC_Stream& theStream )
{
    theStream   << "OMS-AUTO - Gain             [gain]          = " << DISPLAY_MBM(myGain) << endl;
    theStream   << "OMS-AUTO - Gain Tilt        [tilt]          = " << DISPLAY_MBM(myGainTilt) << endl;
    theStream   << "OMS-AUTO - Group Evoa       [evoa]          = " << DISPLAY_MBM(myGroupEvoa) << endl;
}

FC_CmdProcessor::STATUS CFG_OmsAutomaticPwrAdj::Set(int argc, char **argv)
{

    //We need 2 arguments
    if (argc < 2)
        goto OMSERROR;

    if(!strcmp(argv[0],"gain"))
    {
        SetGain(CT_TEL_mBm(atof(argv[1])*100));
    }
    else if(!strcmp(argv[0],"tilt"))
    {
        SetGainTilt(CT_TEL_mBm(atof(argv[1])*100));
    }
    else if(!strcmp(argv[0],"evoa"))
    {
        SetGroupEvoa(CT_TEL_mBm(atof(argv[1])*100));
    }
    else
    {
        goto OMSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OMSERROR:
    {
        fc_cout << "oms <gain> <db>" << endl;
        fc_cout << "oms <tilt> <db>" << endl;
        fc_cout << "oms <evoa> <db>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_FAILURE;
}
