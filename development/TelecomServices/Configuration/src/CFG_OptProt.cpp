//Copyright(c) Tellabs Transport Group. All rights reserved

#include "CFG_OptProt.h"
#include "ErrorService/FC_Error.h"
#include <CommonTypes/CT_Telecom.h>
#include "CommonTypes/CT_SystemIds.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>

using namespace std;


CFG_OptProt::CFG_OptProt(uint32 theIndex):
    CFG_Object(theIndex),
    myForceLaserShutdown(false),
    itsReady(false)
{
    // Nothing to do for now.

}

CFG_OptProt::~CFG_OptProt(void)
{
    // Nothing to do for now.

}

void CFG_OptProt::SetForceLaserShutdown(bool theLaserShutdown)
{
    myForceLaserShutdown  = theLaserShutdown;
    itsReady           = true;

}

bool CFG_OptProt::GetForceLaserShutdown(void) const
{
    return myForceLaserShutdown;

}

void CFG_OptProt::Reset(void)
{
    // Initialize all attributes to default values.
    myForceLaserShutdown = false;
    itsReady         = false;
}

ostream& CFG_OptProt::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myForceLaserShutdown);
    theStream   << FC_InsertVar(itsReady);
    return theStream;

}

istream& CFG_OptProt::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myForceLaserShutdown);
    theStream   >> FC_ExtractVar(itsReady);
    return theStream;

}

FC_Stream& CFG_OptProt::WriteObjectBinary( FC_Stream& theStream )
{

    CFG_Object::WriteObjectBinary(theStream);
    theStream   << myForceLaserShutdown;
    theStream   << itsReady;

    return theStream;

}

FC_Stream& CFG_OptProt::ReadObjectBinary( FC_Stream& theStream )
{
    uint8   ready, forceLaserShutdown;

    theStream   >> forceLaserShutdown;
    theStream   >> ready;

    // Conversion to custom type.
    itsReady = (ready == 1) ? true : false;
    myForceLaserShutdown = (forceLaserShutdown == 1) ? true : false;
    return theStream;

}

FC_CmdProcessor::STATUS CFG_OptProt::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto OPTPROTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"forcelasershut"))
    {
        SetForceLaserShutdown(argv[1][0]=='e');
    }
    else
    {
        goto OPTPROTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OPTPROTERROR:
    {
        fc_cout << "opt <forcelasershut>  <e-enable,d-disable>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_OptProt::Display( FC_Stream& theStream )
{
    theStream   << "OPT PROT - Force Laser Shutdown [forcelasershut]  = " << DISPLAY_BOOL(myForceLaserShutdown) << endl;
}
