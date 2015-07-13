//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Layer2.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Layer2::CFG_Layer2(uint32 theIndex):
    CFG_Object(theIndex),
    myBWPF(0),
    myCFPF(CT_TEL_DefaultCFPF),
    myPVID(CT_TEL_PvidNone),
    myTagmode(false),
    myTPID(CT_TEL_Tpid_STagStd),
    myPortLacpPriority(0),
    myPortLacpPartiMode(CT_TEL_LacpPartiMode_UNKNOWN),
    myMateLacpPriority(0),
    myMateLacpPartiMode(CT_TEL_LacpPartiMode_UNKNOWN),
    myPortMode(CT_TEL_PortMode_Undefined)
{
}

CFG_Layer2::~CFG_Layer2(void)
{
}

void CFG_Layer2::SetBWPF(int theBWPF)
{
    myBWPF = theBWPF;
}

int CFG_Layer2::GetBWPF() const
{
    return myBWPF;
}

void CFG_Layer2::SetCFPF(int theCFPF)
{
    myCFPF = theCFPF;
}

int CFG_Layer2::GetCFPF() const
{
    return myCFPF;
}

uint32 CFG_Layer2::GetPVID() const
{
    return myPVID;
}

void CFG_Layer2::SetPVID(uint32 thePVID)
{
    myPVID = thePVID;
}

bool CFG_Layer2::GetTagmode() const
{
    return myTagmode;
}

void CFG_Layer2::SetTagmode(bool theTagmode)
{
    myTagmode = theTagmode;
}

uint32 CFG_Layer2::GetTPID() const
{
    return myTPID;
}

void CFG_Layer2::SetTPID(uint32 theTPID)
{
    myTPID = theTPID;
}


uint16 CFG_Layer2::GetPortLacpPriority() const
{
    return myPortLacpPriority;
}

void CFG_Layer2::SetPortLacpPriority(uint16 theLacpPriority)
{
    myPortLacpPriority = theLacpPriority;
}

CT_TEL_LacpPartiMode CFG_Layer2::GetPortLacpPartiMode() const
{
    return myPortLacpPartiMode;
}

void CFG_Layer2::SetPortLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode)
{
    myPortLacpPartiMode = theLacpPartiMode;
}

uint16 CFG_Layer2::GetMateLacpPriority() const
{
    return myMateLacpPriority;
}

void CFG_Layer2::SetMateLacpPriority(uint16 theLacpPriority)
{
    myMateLacpPriority = theLacpPriority;
}

CT_TEL_LacpPartiMode CFG_Layer2::GetMateLacpPartiMode() const
{
    return myMateLacpPartiMode;
}

void CFG_Layer2::SetMateLacpPartiMode(CT_TEL_LacpPartiMode theLacpPartiMode)
{
    myMateLacpPartiMode = theLacpPartiMode;
}


uint8 CFG_Layer2::GetPortMode() const
{
    return myPortMode;
}

void CFG_Layer2::SetPortMode(uint8 thePortMode)
{
    myPortMode = thePortMode;
}

void CFG_Layer2::Reset(void)
{
    // Initialize all attributes to default values.
    myBWPF = 0;
    myCFPF = CT_TEL_DefaultCFPF;
    myPVID = CT_TEL_PvidNone;
    myTagmode = false;
    myTPID = CT_TEL_Tpid_STagStd;
    myPortLacpPriority = 0;
    myPortLacpPartiMode = CT_TEL_LacpPartiMode_UNKNOWN;
    myMateLacpPriority = 0;
    myMateLacpPartiMode = CT_TEL_LacpPartiMode_UNKNOWN;
    myPortMode = CT_TEL_PortMode_Undefined;
}

// For Display
ostream& CFG_Layer2::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myBWPF);
    theStream   << FC_InsertVar(myCFPF);
    theStream   << FC_InsertVar(myPVID);
    theStream   << FC_InsertVar(myTagmode);
    theStream   << FC_InsertVar(myTPID);
    theStream   << FC_InsertVar(myPortMode);

    theStream   << FC_InsertVar(myPortLacpPriority);
    uint8 aPortLacpPartiMode = (uint8) myPortLacpPartiMode;
    theStream   << FC_InsertVar(aPortLacpPartiMode);

    theStream   << FC_InsertVar(myMateLacpPriority);
    uint8 aMateLacpPartiMode = (uint8) myMateLacpPartiMode;
    theStream   << FC_InsertVar(aMateLacpPartiMode);

    return theStream;
}

istream& CFG_Layer2::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myBWPF);
    theStream   >> FC_ExtractVar(myCFPF);
    theStream   >> FC_ExtractVar(myPVID);
    theStream   >> FC_ExtractVar(myTagmode);
    theStream   >> FC_ExtractVar(myTPID);
    theStream   >> FC_ExtractVar(myPortMode);

    theStream   >> FC_ExtractVar(myPortLacpPriority);

    uint8 aPortLacpPartiMode;
    theStream   >> FC_ExtractVar(aPortLacpPartiMode);
    myPortLacpPartiMode = (CT_TEL_LacpPartiMode) aPortLacpPartiMode;

    theStream   >> FC_ExtractVar(myMateLacpPriority);

    uint8 aMateLacpPartiMode;
    theStream   >> FC_ExtractVar(aMateLacpPartiMode);
    myMateLacpPartiMode = (CT_TEL_LacpPartiMode) aMateLacpPartiMode;

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Layer2::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   <<  myBWPF;
    theStream   <<  myCFPF;
    theStream   <<  myPVID;
    theStream   <<  myTagmode;
    theStream   <<  myTPID;
    theStream   <<  myPortMode;

    theStream   <<  myPortLacpPriority;

    uint8 aPortLacpPartiMode = (uint8) myPortLacpPartiMode;
    theStream   <<  aPortLacpPartiMode;

    theStream   <<  myMateLacpPriority;

    uint8 aMateLacpPartiMode = (uint8) myMateLacpPartiMode;
    theStream   <<  aMateLacpPartiMode;

    return theStream;
}

FC_Stream& CFG_Layer2::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream   >>  myBWPF;
    theStream   >>  myCFPF;
    theStream   >>  myPVID;
    theStream   >>  myTagmode;
    theStream   >>  myTPID;
    theStream   >>  myPortMode;

    theStream   >>  myPortLacpPriority;

    uint8 aPortLacpPartiMode;
    theStream   >>  aPortLacpPartiMode;
    myPortLacpPartiMode = (CT_TEL_LacpPartiMode) aPortLacpPartiMode;

    theStream   >>  myMateLacpPriority;

    uint8 aMateLacpPartiMode;
    theStream   >>  aMateLacpPartiMode;
    myMateLacpPartiMode = (CT_TEL_LacpPartiMode) aMateLacpPartiMode;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Layer2::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"bwpf",4))
    {
        SetBWPF(int(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"cfpf",4))
    {
        SetCFPF(int(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"pvid",4))
    {
        SetPVID(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"tag",3))
    {
        SetTagmode(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"tpid",4))
    {
        SetTPID(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"pmode",5))
    {
        SetPortMode(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"pprio",5))
    {
        SetPortLacpPriority(uint16(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"mprio",5))
    {
        SetMateLacpPriority(uint16(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"ppart",5))
    {
        SetPortLacpPartiMode(CFG_STRING_TO_PARTI_MODE(argv[1]));
    }
    else if (!strncmp(aParam,"mpart",5))
    {
        SetMateLacpPartiMode(CFG_STRING_TO_PARTI_MODE(argv[1]));
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "LAYER2 <bwpf>      <int> " << endl;
        fc_cout << "LAYER2 <cfpf>      <int> " << endl;
        fc_cout << "LAYER2 <pvid>      0-4094" << endl;
        fc_cout << "LAYER2 <tag>       <e-nable|d-isable> " << endl;
        fc_cout << "LAYER2 <tpid>      <uint32>" << endl;
        fc_cout << "LAYER2 <pmode>     <uint8>" << endl;
        fc_cout << "LAYER2 <pprio>     <int (0-65535)>" << endl;
        fc_cout << "LAYER2 <ppart>     <passive | active | static>" << endl;
        fc_cout << "LAYER2 <mprio>     <int (0-65535)>" << endl;
        fc_cout << "LAYER2 <mpart>     <passive | active | static>" << endl;

        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Layer2::Display( FC_Stream& theStream )
{
    theStream   << "LAYER2       - BandWidth Profile       [bwpf]  = " << (int)myBWPF << endl;
    theStream   << "LAYER2       - Control Frame Profile   [cfpf]  = " << (int)myCFPF << endl;
    theStream   << "LAYER2       - Port VLAN ID            [pvid]  = " << (uint32)myPVID << endl;
    theStream   << "LAYER2       - Tag Mode                [tag]   = " << DISPLAY_BOOL(myTagmode) << endl;
    theStream   << "LAYER2       - Tag Protocol Id         [tpid]  = 0x" << hex  << (uint32)myTPID << dec << endl;
    theStream   << "LAYER2       - Port Mode               [pmode] = 0x" << hex  << (uint32)myPortMode << dec << endl;
    theStream   << "LAYER2       - Port Lacp Priority      [pprio] = " << myPortLacpPriority << endl;
    theStream   << "LAYER2       - Port Lacp Participation [ppart] = " << DISPLAY_PARTI_MODE(myPortLacpPartiMode) << endl;
    theStream   << "LAYER2       - Mate Lacp Priority      [mprio] = " << myMateLacpPriority << endl;
    theStream   << "LAYER2       - Mate Lacp Participation [mpart] = " << DISPLAY_PARTI_MODE(myMateLacpPartiMode) << endl;
}  

