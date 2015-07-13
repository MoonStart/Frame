//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Oms.h"
#include "BaseClass/FC_TextStream.h"
#include "ErrorService/FC_Error.h"
#include <string.h>

CFG_Oms::CFG_Oms(uint32 theIndex):
    CFG_Object(theIndex),
    myPowerControlEnable(false),
    myGain(TRAFFIC_CFG_DEFAULT_VALUE),
    myGroupEvoaPowerControlEnable(false),
    myGroupEvoa(TRAFFIC_CFG_DEFAULT_VALUE)
{
}

CFG_Oms::~CFG_Oms(void)
{
}

void CFG_Oms::Reset(void)
{
    myPowerControlEnable = false;
    myGain = TRAFFIC_CFG_DEFAULT_VALUE;
    myGroupEvoaPowerControlEnable = false;
    myGroupEvoa = TRAFFIC_CFG_DEFAULT_VALUE;
}

bool CFG_Oms::GetPowerControlEnable() const
{
    return myPowerControlEnable;
}

void CFG_Oms::SetPowerControlEnable(bool thePowerControlEnable)
{
    myPowerControlEnable = thePowerControlEnable;
}

CT_TEL_mBm CFG_Oms::GetGain() const
{
    return myGain;
}

void CFG_Oms::SetGain(CT_TEL_mBm theGain)
{
    myGain = theGain;
}


bool CFG_Oms::GetGroupEvoaPowerControlEnable() const
{
    return myGroupEvoaPowerControlEnable;
}

void CFG_Oms::SetGroupEvoaPowerControlEnable(bool thePowerControlEnable)
{
    myGroupEvoaPowerControlEnable = thePowerControlEnable;
}

CT_TEL_mBm CFG_Oms::GetGroupEvoa() const
{
    return myGroupEvoa;
}

void CFG_Oms::SetGroupEvoa(CT_TEL_mBm theEvoa)
{
    myGroupEvoa = theEvoa;
}


ostream& CFG_Oms::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myPowerControlEnable);
    theStream << FC_InsertVar(myGain);
    theStream << FC_InsertVar(myGroupEvoaPowerControlEnable);
    theStream << FC_InsertVar(myGroupEvoa);
    return theStream;

}

istream& CFG_Oms::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myPowerControlEnable);
    theStream >> FC_ExtractVar(myGain);
    theStream >> FC_ExtractVar(myGroupEvoaPowerControlEnable);
    theStream >> FC_ExtractVar(myGroupEvoa);
    return theStream;

}

FC_Stream& CFG_Oms::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream << myPowerControlEnable;
    theStream << myGain;
    theStream << myGroupEvoaPowerControlEnable;
    theStream << myGroupEvoa;
    return theStream;

}

FC_Stream& CFG_Oms::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream >> myPowerControlEnable;
    theStream >> myGain;
    theStream >> myGroupEvoaPowerControlEnable;
    theStream >> myGroupEvoa;
    return theStream;

}

FC_CmdProcessor::STATUS CFG_Oms::Set(int argc, char **argv)
{
    bool aEnable;

    //We need 2 arguments
    if (argc < 2)
        goto OMSERROR;

    aEnable = argv[1][0]=='e';

    if(!strcmp(argv[0],"gain"))
    {
        SetGain(CT_TEL_mBm(atof(argv[1])*100));
    }   
    else if(!strcmp(argv[0],"pwrctrl"))
    {
        SetPowerControlEnable(aEnable);
    }
    else if(!strcmp(argv[0],"evoa"))
    {
        SetGroupEvoa(CT_TEL_mBm(atof(argv[1])*100));
    }
    else if(!strncmp(argv[0],"evpw",4))
    {
        SetGroupEvoaPowerControlEnable(aEnable);
    }
    else
    {
        goto OMSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OMSERROR:
    {
        fc_cout << "oms <pwrctrl> <e-nable|d-isable>" << endl;
        fc_cout << "oms <gain> <db>" << endl;
        fc_cout << "oms <evpw-rctrl> <e-nable|d-isable>" << endl;
        fc_cout << "oms <evoa> <db>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_FAILURE;
}

void CFG_Oms::Display( FC_Stream& theStream )
{
    theStream   << "OMS      - Gain Power control   [pwrctrl]   = " << DISPLAY_BOOL(myPowerControlEnable) << endl;
    theStream   << "OMS      - Gain                 [gain]      = " << DISPLAY_MBM(myGain) << endl;
    theStream   << "OMS      - Evoa Power control   [evpwrctrl] = " << DISPLAY_BOOL(myGroupEvoaPowerControlEnable) << endl;
    theStream   << "OMS      - Group Evoa           [evoa]      = " << DISPLAY_MBM(myGroupEvoa) << endl;
}
