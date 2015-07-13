//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_CfPf.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Cfpf::CFG_Cfpf(uint32 theIndex):
    CFG_Object(theIndex),
    myLACP(false), 
    myLinkOAM(false),
    myDot1X(false),
    myELMI(false),
    myLLDP(false),
    myGARP(false)
{
}

CFG_Cfpf::~CFG_Cfpf(void)
{
}

void CFG_Cfpf::SetLACP(bool theLACP)
{
    myLACP = theLACP;
}

bool CFG_Cfpf::GetLACP() const
{
    return myLACP;
}

void CFG_Cfpf::SetLinkOAM(bool theLinkOAM)
{
    myLinkOAM = theLinkOAM;
}

bool CFG_Cfpf::GetLinkOAM() const
{
    return myLinkOAM;
}

void CFG_Cfpf::SetDot1X(bool theDot1X)
{
    myDot1X = theDot1X;
}

bool CFG_Cfpf::GetDot1X() const
{
    return myDot1X;
}

void CFG_Cfpf::SetELMI(bool theELMI)
{
    myELMI = theELMI;
}

bool CFG_Cfpf::GetELMI() const
{
    return myELMI;
}

void CFG_Cfpf::SetLLDP(bool theLLDP)
{
    myLLDP = theLLDP;
}

bool CFG_Cfpf::GetLLDP() const
{
    return myLLDP;
}

void CFG_Cfpf::SetGARP(bool theGARP)
{
    myGARP = theGARP;
}

bool CFG_Cfpf::GetGARP() const
{
    return myGARP;
}

void CFG_Cfpf::Reset(void)
{
    // Initialize all attributes to default values.
    myLACP    = false;
    myLinkOAM = false;
    myDot1X   = false;
    myELMI    = false;    
    myLLDP    = false;
    myGARP    = false;
}

ostream& CFG_Cfpf::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myLACP);
    theStream   << FC_InsertVar(myLinkOAM);
    theStream   << FC_InsertVar(myDot1X);
    theStream   << FC_InsertVar(myELMI);
    theStream   << FC_InsertVar(myLLDP);
    theStream   << FC_InsertVar(myGARP);

    return theStream;
}

istream& CFG_Cfpf::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myLACP);
    theStream   >> FC_ExtractVar(myLinkOAM);
    theStream   >> FC_ExtractVar(myDot1X);
    theStream   >> FC_ExtractVar(myELMI);
    theStream   >> FC_ExtractVar(myLLDP);
    theStream   >> FC_ExtractVar(myGARP);

    return theStream;
}

FC_Stream& CFG_Cfpf::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myLACP;
    theStream   << myLinkOAM;
    theStream   << myDot1X;
    theStream   << myELMI;
    theStream   << myLLDP;
    theStream   << myGARP;

    return theStream;
}

FC_Stream& CFG_Cfpf::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> myLACP;
    theStream   >> myLinkOAM;
    theStream   >> myDot1X;
    theStream   >> myELMI;
    theStream   >> myLLDP;
    theStream   >> myGARP;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Cfpf::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"lacp",4))
    {
        SetLACP(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"oam",3))
    {
        SetLinkOAM(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"dot1x",5))
    {
        SetDot1X(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"elmi",4))
    {
        SetELMI(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"lldp",4))
    {
        SetLLDP(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"garp",4))
    {
        SetGARP(argv[1][0]=='e');
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "CFPF <lacp>      <e-nable|d-isable> " << endl;
        fc_cout << "CFPF <oam>       <e-nable|d-isable> " << endl;
        fc_cout << "CFPF <dot1x>     <e-nable|d-isable> " << endl;
        fc_cout << "CFPF <elmi>      <e-nable|d-isable> " << endl;
        fc_cout << "CFPF <lldp>      <e-nable|d-isable> " << endl;
        fc_cout << "CFPF <garp>      <e-nable|d-isable> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Cfpf::Display( FC_Stream& theStream )
{
    theStream   << "CFPF - Tunneling LACP             [lacp]   = " << DISPLAY_BOOL(myLACP) << endl;
    theStream   << "CFPF - Tunneling Link OAM         [oam]    = " << DISPLAY_BOOL(myLinkOAM) << endl;
    theStream   << "CFPF - Tunneling Dot1X Auth       [dot1x]  = " << DISPLAY_BOOL(myDot1X) << endl;
    theStream   << "CFPF - Tunneling ELMI             [elmi]   = " << DISPLAY_BOOL(myELMI)<< endl;
    theStream   << "CFPF - Tunneling LLDP             [lldp]   = " << DISPLAY_BOOL(myLLDP) << endl;
    theStream   << "CFPF - Tunneling GARP             [garp]   = " << DISPLAY_BOOL(myGARP) << endl;
}

