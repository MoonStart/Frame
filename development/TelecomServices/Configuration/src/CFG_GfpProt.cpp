//Copyright(c) Tellabs Transport Group. All rights reserved

#include "CFG_GfpProt.h"
#include "ErrorService/FC_Error.h"
#include <CommonTypes/CT_Telecom.h>
#include "CommonTypes/CT_SystemIds.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>

using namespace std;


CFG_GfpProt::CFG_GfpProt(uint32 theIndex):
    CFG_Object(theIndex),
    myForceLinkFailTx(0),
    itsReady(false)
{
    // Nothing to do for now.

}

CFG_GfpProt::~CFG_GfpProt(void)
{
    // Nothing to do for now.

}

void CFG_GfpProt::SetForceLinkFailTx(bool theForceLinkFailTx)
{
    myForceLinkFailTx  = theForceLinkFailTx;
    itsReady           = true;

}

bool CFG_GfpProt::GetForceLinkFailTx(void)
{
    return myForceLinkFailTx;

}

void CFG_GfpProt::Reset(void)
{
    // Initialize all attributes to default values.
    myForceLinkFailTx = 0;
    itsReady         = false;
}

ostream& CFG_GfpProt::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceLinkFailTx);
    theStream   << FC_InsertVar(itsReady);
    return theStream;

}

istream& CFG_GfpProt::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceLinkFailTx);
    theStream   >> FC_ExtractVar(itsReady);
    return theStream;

}

FC_Stream& CFG_GfpProt::WriteObjectBinary( FC_Stream& theStream )
{

    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceLinkFailTx;
    theStream   << itsReady;

    return theStream;

}

FC_Stream& CFG_GfpProt::ReadObjectBinary( FC_Stream& theStream )
{
    uint8   ready, forceLinkFailTx;

    theStream   >> forceLinkFailTx;
    theStream   >> ready;

    // Conversion to custom type.
    itsReady = (ready == 1) ? true : false;
    myForceLinkFailTx = (ready == 1) ? true : false;
    return theStream;

}

FC_CmdProcessor::STATUS CFG_GfpProt::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto GFPPROTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"lnkfailtx"))
    {
        SetForceLinkFailTx(argv[1][0]=='e');
    }
    else
    {
        goto GFPPROTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

GFPPROTERROR:
    {
        fc_cout << "gfp <lnkfailtx>  <e-enable,d-disable>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_GfpProt::Display( FC_Stream& theStream )
{
    theStream   << "GFP PROT  - Force LinkFailTx (CR0) [lnkfailtx]  = " << DISPLAY_BOOL(myForceLinkFailTx) << endl;
}
