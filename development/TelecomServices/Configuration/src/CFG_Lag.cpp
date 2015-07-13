//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Lag.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Port.h>
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Lag::CFG_Lag(uint32 theIndex):
    CFG_Object(theIndex),
    myIsProvisioned(false),
    myLagList(),
    myLagId(-1),
    myLagMaster(0),
    myLacpEnabled(false),
    myLacpSystemID(),
    myLacpSystemPriority(0),
    myLacpTimeout(CT_TEL_LacpTimeoutMode_UNKNOWN),
    myAdminKey(0)
{
}

CFG_Lag::~CFG_Lag(void)
{
}

void CFG_Lag::SetLagList(list<CT_Port>& theLagList)
{
    myLagList = theLagList;
}

const list<CT_Port>& CFG_Lag::GetLagList()
{
    return myLagList;
}

void CFG_Lag::SetLagMaster(bool theLagMaster)
{
    myLagMaster = theLagMaster;
}

bool CFG_Lag::GetLagMaster() const
{
    return myLagMaster;
}

void CFG_Lag::SetLagId(int theLagId)
{
    myLagId = theLagId;
}

int CFG_Lag::GetLagId() const
{
    return myLagId;
}

list<CT_Port>::iterator CFG_Lag::GetLagListBegin()
{
    return myLagList.begin();
}

list<CT_Port>::iterator CFG_Lag::GetLagListEnd()
{
    return myLagList.end();
}

void CFG_Lag::SetIsProvisioned(bool theIsProvisioned)
{
    myIsProvisioned = theIsProvisioned;
}

bool CFG_Lag::GetIsProvisioned() const
{
    return myIsProvisioned;
}


void CFG_Lag::SetLacpEnabled(bool theLacpEnabled)
{
    myLacpEnabled = theLacpEnabled;
}

bool CFG_Lag::GetLacpEnabled() const
{
    return myLacpEnabled;
}


void CFG_Lag::SetLacpSystemID(CT_LacpSystemId theLacpSystemID)
{
    myLacpSystemID = theLacpSystemID;
}

CT_LacpSystemId CFG_Lag::GetLacpSystemID() const
{
    return myLacpSystemID;
}


void CFG_Lag::SetLacpSystemPriority(uint16 theLacpSystemPriority)
{
    myLacpSystemPriority = theLacpSystemPriority;
}

uint16 CFG_Lag::GetLacpSystemPriority() const
{
    return myLacpSystemPriority;
}


void CFG_Lag::SetLacpTimeoutMode(CT_TEL_LacpTimeoutMode theLacpTimeoutMode)
{
    myLacpTimeout = theLacpTimeoutMode;
}

CT_TEL_LacpTimeoutMode CFG_Lag::GetLacpTimeoutMode() const
{
    return myLacpTimeout;
}

void CFG_Lag::SetAdminKey(uint16 theAdminKey)
{
    myAdminKey = theAdminKey;
}

uint16 CFG_Lag::GetAdminKey() const
{
    return myAdminKey;
}


void CFG_Lag::Reset(void)
{
    // Initialize all attributes to default values.
    myIsProvisioned = false;
    myLagList.erase(myLagList.begin(), myLagList.end());
    myLagMaster = 0;
    myLagId = -1;
    myLacpEnabled = false;
    myLacpSystemID = CT_LacpSystemId();
    myLacpSystemPriority = 0;
    myLacpTimeout = CT_TEL_LacpTimeoutMode_UNKNOWN;
    myAdminKey = 0;
}

// For Display
ostream& CFG_Lag::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myIsProvisioned);
    theStream   << FC_InsertVar(myLagId);
    theStream   << FC_InsertVar(myLagMaster);

    string  aMembers;
    char    aPortId[4];
    char    aSlot[4];

    uint32  numberOfMbrs = myLagList.size();
    theStream << FC_InsertVar(numberOfMbrs);
    list<CT_Port>::iterator i;
    for (i = myLagList.begin(); i != myLagList.end(); i++)
    {
        CT_Port aPort;
        aPort = CT_Port(*i);

        sprintf(aSlot, "%3d", aPort.GetSlotId());
        aSlot[3] = 0;
        aMembers += aSlot;

        sprintf(aPortId, "%3d", aPort.GetPortId());
        aPortId[3] = 0;
        aMembers += aPortId;

    }
    theStream   << FC_InsertVar(aMembers);

    theStream   << FC_InsertVar(myLacpEnabled);
    theStream   << FC_InsertVar(myLacpSystemID);
    theStream   << FC_InsertVar(myLacpSystemPriority);

    uint8 aLacpTimeout = (uint8) myLacpTimeout;
    theStream   << FC_InsertVar(aLacpTimeout);

    theStream   << FC_InsertVar(myAdminKey);
    return theStream;
}

istream& CFG_Lag::ReadObject( istream& theStream )
{
    uint32  numberOfMbrs;
    uint32 i = 0;

    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myIsProvisioned);
    theStream   >> FC_ExtractVar(myLagId);
    theStream   >> FC_ExtractVar(myLagMaster);

    myLagList.erase(myLagList.begin(), myLagList.end());
    theStream   >> FC_ExtractVar(numberOfMbrs);

    char    aMembersBuf[256];
    theStream   >> FC_ExtractVar(aMembersBuf);

    list<CT_Port> aLagList;
    aLagList.erase(aLagList.begin(), aLagList.end());

    char    *aPortId;
    char    *aSlot;

    aSlot = strtok(aMembersBuf, " ");
    if(aSlot != NULL)
    {
        aPortId = strtok(NULL, " ");
    }

    for (i = 0; i < numberOfMbrs; i++)
    {
        CT_Port aPort;
        aPort.SetPortInfo(UNKNOWN_SHELF_ID, uint8(atoi(aSlot)), CT_IntfId(atoi(aPortId)), FAC_SUBTYPE_UNKNOWN, UNKNOWN_CHANNEL_ID);

        aLagList.push_back(aPort);

        aSlot = strtok(NULL, " ");
        if(aSlot != NULL)
        {
            aPortId = strtok(NULL, " ");
        }

    }

    SetLagList(aLagList);

    theStream   >> FC_ExtractVar(myLacpEnabled);
    theStream   >> FC_ExtractVar(myLacpSystemID);
    theStream   >> FC_ExtractVar(myLacpSystemPriority);

    uint8 aLacpTimeout;
    theStream   >> FC_ExtractVar(aLacpTimeout);
    myLacpTimeout = (CT_TEL_LacpTimeoutMode) aLacpTimeout;

    theStream   >> FC_ExtractVar(myAdminKey);
    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Lag::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   <<  myIsProvisioned;
    theStream   <<  myLagId;
    theStream   <<  myLagMaster;

    uint32  numberOfMbrs = myLagList.size();
    theStream << numberOfMbrs;
    list<CT_Port>::iterator i;
    for (i = myLagList.begin(); i != myLagList.end(); i++)
        theStream << (*i);

    theStream   <<  myLacpEnabled;
    theStream   <<  myLacpSystemID;
    theStream   <<  myLacpSystemPriority;

    uint8 aLacpTimeout = (uint8) myLacpTimeout;
    theStream   <<  aLacpTimeout;

    theStream   <<  myAdminKey;
    return theStream;
}

FC_Stream& CFG_Lag::ReadObjectBinary( FC_Stream& theStream )
{
    uint32  numberOfMbrs;
    uint32 i = 0;
    myLagList.erase(myLagList.begin(), myLagList.end());

    CFG_Object::ReadObjectBinary(theStream);

    theStream   >>  myIsProvisioned;
    theStream   >>  myLagId;
    theStream   >>  myLagMaster;

    theStream >> numberOfMbrs;
    for (i = 0; i < numberOfMbrs; i++)
    {
        CT_Port aPort;
        theStream >> aPort;
        myLagList.push_back(aPort);

    }

    theStream   >>  myLacpEnabled;
    theStream   >>  myLacpSystemID;
    theStream   >>  myLacpSystemPriority;

    uint8 aLacpTimeout;
    theStream   >>  aLacpTimeout;
    myLacpTimeout = (CT_TEL_LacpTimeoutMode) aLacpTimeout;

    theStream   >>  myAdminKey;
    return theStream;
}

FC_CmdProcessor::STATUS CFG_Lag::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"lagid",6))
    {
        SetLagId(int(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"prov",4))
    {
        SetIsProvisioned(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"master",6))
    {
        SetLagMaster(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"list",4))
    {
        list<CT_Port> aLagList;
        CT_Port aPort;
        aLagList.erase(aLagList.begin(), aLagList.end());
        aPort.SetPortInfo(UNKNOWN_SHELF_ID, uint8(atoi(argv[1])), CT_IntfId(atoi(argv[2])), FAC_SUBTYPE_UNKNOWN, UNKNOWN_CHANNEL_ID);
        aLagList.push_back(aPort);
        aPort.SetPortInfo(UNKNOWN_SHELF_ID, uint8(atoi(argv[3])), CT_IntfId(atoi(argv[4])), FAC_SUBTYPE_UNKNOWN, UNKNOWN_CHANNEL_ID);
        aLagList.push_back(aPort);
        SetLagList(aLagList);
    }
    else if (!strncmp(aParam,"lacpen",6))
    {
        SetLacpEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"lacpid",6))
    {
        myLacpSystemID = CT_LacpSystemId(argv[1][0], argv[2][0], argv[3][0], argv[4][0], argv[5][0], argv[6][0]);
    }
    else if (!strncmp(aParam,"lacppr",6))
    {
        SetLacpSystemPriority(uint16(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"lacpti",6))
    {
        SetLacpTimeoutMode(CFG_STRING_TO_LACP_TIMEOUT(argv[1]));
    }
    else if (!strncmp(aParam,"admin",5))
    {
        SetAdminKey(uint16(atoi(argv[1])));
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "LAG <prov>          <e-nable|d-isable> " << endl;
        fc_cout << "LAG <lagid>         <int> " << endl;
        fc_cout << "LAG <lacpen-able>   <e-nable|d-isable> " << endl;
        fc_cout << "LAG <lacpid>        <ch1 ch2 ch3 ch4 ch5 ch6 (six chars - space separated - Sys ID)> " << endl;
        fc_cout << "LAG <lacppri-ority> <int (0-65535)> " << endl;
        fc_cout << "LAG <lacptim-eout>  <long | short> " << endl;
        fc_cout << "LAG <admin-key>     <int (0-65535)> " << endl;
        fc_cout << "LAG <master>        <e-nable|d-isable> " << endl;
        fc_cout << "LAG <list>          <slot port slot port> " << endl;

        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Lag::Display( FC_Stream& theStream )
{
    theStream   << "LAG       - Provisioned   [prov]    = " << DISPLAY_BOOL(myIsProvisioned) << endl;
    theStream   << "LAG       - Lag Id        [lagid]   = " << (int)myLagId << endl;
    theStream   << "LAG       - Lacp Enabled  [lacpen]  = " << DISPLAY_BOOL(myLacpEnabled) << endl;
    theStream   << "LAG       - Lacp Sys ID   [lacpid]  ="  << myLacpSystemID.DisplayAddr() << endl;
    theStream   << "LAG       - Lacp Priority [lacppri] = " << dec << myLacpSystemPriority << endl;
    theStream   << "LAG       - Lacp Timeout  [lacptim] = " << DISPLAY_TIMEOUT_MODE(myLacpTimeout) << endl;
    theStream   << "LAG       - Admin Key     [admink]  = " << dec << myAdminKey << endl;
    theStream   << "LAG       - Lag Master    [master]  = " << DISPLAY_BOOL(myLagMaster) << endl;
    theStream   << "LAG       - Lag List      [list]    = Slot  Port" << endl;
    list<CT_Port>::iterator i;
    for (i = myLagList.begin(); i != myLagList.end(); i++)
    {
        CT_Port aPort;
        aPort = CT_Port(*i);
        theStream   << "                                      " << (uint32)aPort.GetSlotId() << "  " << DISPLAY_CT_IntfId(aPort.GetPortId()) << endl;
        //theStream   << "                                      " << (uint32)i->GetSlotId() << "  " << DISPLAY_CT_IntfId(i->GetPortId()) << endl;
    }
}

