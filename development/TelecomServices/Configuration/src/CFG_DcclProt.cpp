//Copyright(c) Tellabs Transport Group. All rights reserved

#include "CFG_DcclProt.h"
#include "ErrorService/FC_Error.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>

using namespace std;


CFG_DcclProt::CFG_DcclProt(uint32 theIndex):
    CFG_Object(theIndex)
{
    Reset();

}

CFG_DcclProt::~CFG_DcclProt(void)
{
    // Nothing to do for now.

}

bool CFG_DcclProt::SetBroadcastMode(CT_DCC_BroadcastMode theBroadcastMode)
{
    bool hasChanged = ( (myBroadcastMode != theBroadcastMode) ? true : false);
    myBroadcastMode = theBroadcastMode;
    return hasChanged;
}

bool CFG_DcclProt::SetSelectionMode(CT_DCC_SelectionMode theSelectionMode)
{
    bool hasChanged = ( (mySelectionMode != theSelectionMode) ? true : false);
    mySelectionMode = theSelectionMode;
    return hasChanged;
}

bool CFG_DcclProt::SetRemotePort(uint8 theRemotePort)
{
    bool hasChanged = ( (myRemotePort != theRemotePort) ? true : false);
    myRemotePort = theRemotePort;
    return hasChanged;
}

bool CFG_DcclProt::SetRxSelected(bool theSelected)
{
    bool hasChanged = ( (myIsRxSelected != theSelected) ? true : false);
    myIsRxSelected = theSelected;
    return hasChanged;
}

CT_DCC_BroadcastMode CFG_DcclProt::GetBroadcastMode() const
{
    return myBroadcastMode;
}

CT_DCC_SelectionMode CFG_DcclProt::GetSelectionMode() const
{
    return mySelectionMode;
}

uint8 CFG_DcclProt::GetRemotePort() const
{
    return myRemotePort;
}

bool CFG_DcclProt::GetRxSelected() const
{
    return myIsRxSelected;
}


void CFG_DcclProt::Reset(void)
{
    // Initialize all attributes to default values.
    myBroadcastMode = CT_DCC_MASTER;
    mySelectionMode = CT_DCC_LOCAL;
    myRemotePort = DCC_INVALID_PROT_REMOTE_PORT;
    myIsRxSelected = true;
}

ostream& CFG_DcclProt::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    uint32 aBroadcastMode = (uint32) myBroadcastMode;
    uint32 aSelMode = (uint32) mySelectionMode;
    theStream   << FC_InsertVar(aBroadcastMode);
    theStream   << FC_InsertVar(aSelMode);
    theStream   << FC_InsertVar(myRemotePort);
    theStream   << FC_InsertVar(myIsRxSelected);
    return theStream;

}

istream& CFG_DcclProt::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    uint32 aBroadcastMode;
    uint32 aSelMode;
    theStream   >> FC_ExtractVar(aBroadcastMode);
    theStream   >> FC_ExtractVar(aSelMode);
    theStream   >> FC_ExtractVar(myRemotePort);
    theStream   >> FC_ExtractVar(myIsRxSelected);

    myBroadcastMode = (CT_DCC_BroadcastMode)aBroadcastMode;
    mySelectionMode = (CT_DCC_SelectionMode)aSelMode;
    return theStream;

}

FC_Stream& CFG_DcclProt::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);

    uint32 aBroadcastMode = (uint32) myBroadcastMode;
    uint32 aSelMode = (uint32) mySelectionMode;
    theStream   << aBroadcastMode;
    theStream   << aSelMode;
    theStream   << myRemotePort;
    theStream   << myIsRxSelected;

    return theStream;
}

FC_Stream& CFG_DcclProt::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    uint32 aBroadcastMode;
    uint32 aSelMode;
    theStream   >> aBroadcastMode;
    theStream   >> aSelMode;
    theStream   >> myRemotePort;
    theStream   >> myIsRxSelected;
    myBroadcastMode = (CT_DCC_BroadcastMode)aBroadcastMode;
    mySelectionMode = (CT_DCC_SelectionMode)aSelMode;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_DcclProt::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto DCCLPROTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strcmp(aParam,"broadcastmode"))
    {
        SetBroadcastMode( (argv[1][0]=='m') ? CT_DCC_MASTER : CT_DCC_SLAVE);
    }
    else if (!strcmp(aParam,"selectionmode"))
    {
        SetSelectionMode( (argv[1][0]=='l') ? CT_DCC_LOCAL : CT_DCC_REMOTE);
    }
    else if (!strcmp(aParam,"rxselected"))
    {
        SetRxSelected( (argv[1][0]=='y') ? true : false);
    }
    else if (!strcmp(aParam,"remport"))
    {
        SetRemotePort((uint8)atoi(argv[1]));
    }
    else
    {
        goto DCCLPROTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

DCCLPROTERROR:
    {
        fc_cout << "dccl <broadcastmode>  <m-aster,s-lave>" << endl;
        fc_cout << "dccl <selectionmode>  <l-ocal,r-emote>" << endl;
        fc_cout << "dccl <remport>        <port # (1-n)>" << endl;
        fc_cout << "dccl <rxselected>     <y-es|n-o>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_DcclProt::Display( FC_Stream& theStream )
{
    theStream   << "DCCL PROT  - Broadcast Mode         [broadcastmode] = " << DISPLAY_DCC_BroadcastMode(myBroadcastMode) << endl;
    theStream   << "DCCL PROT  - Selection Mode         [selectionmode] = " << DISPLAY_DCC_SelectionMode(mySelectionMode) << endl;
    theStream   << "DCCL PROT  - Remote Port            [remport]       = " <<  (uint32)myRemotePort << endl;
    theStream   << "DCCL PROT  - Is Rx Selected         [rxselected]    = " <<  DISPLAY_BOOL(myIsRxSelected) << endl;
}
