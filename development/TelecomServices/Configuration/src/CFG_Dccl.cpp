//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Dccl.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>
#include <CFG_Definitions.h>


CFG_Dccl::CFG_Dccl(uint32 theIndex):
    CFG_Object(theIndex),
    myIsProvisioned(false),
    myLinkRouterId(0),
    myRouterShelfId(0),
    myIfIndexId(0),
    myLprfId(UNKNOWN_Link_Profile_ID),
    myProtocolLinkEnabled(false),
    myChecksumEnabled(false),
    myHTMultiplier(0),
    myConfigTimer(0),
    myHelloTimer(0),
    myDefaultMetric(0),
    myReDirectHoldingTimer(0),
    myLinkRoutingLevel(0),
    myESConfigurationTimer(0),
    myFollowProtectionEnabled(false)
{
}

CFG_Dccl::~CFG_Dccl(void)
{
}

void CFG_Dccl::SetLinkRouterID(CT_DCC_RouterId theRouterID)
{
    myLinkRouterId = theRouterID;
}

CT_DCC_RouterId CFG_Dccl::GetLinkRouterID() const
{
    return myLinkRouterId;
}


void CFG_Dccl::SetRouterShelfID(CT_ShelfId theRouterShelfId)
{
    myRouterShelfId = theRouterShelfId;
}

CT_ShelfId CFG_Dccl::GetRouterShelfID() const
{
    return myRouterShelfId;
}


void CFG_Dccl::SetIntfID(CT_IfIndexIdent theIfIndexId)
{
    myIfIndexId = theIfIndexId;
}

CT_IfIndexIdent CFG_Dccl::GetIntfID() const
{
    return myIfIndexId;
}

void CFG_Dccl::SetLinkProfileID(CT_Link_ProfileId theLprfId)
{
    myLprfId = theLprfId;
}

CT_Link_ProfileId CFG_Dccl::GetLinkProfileID() const
{
    return myLprfId;
}


//Set Link Is Provisioned field
void CFG_Dccl::SetIsProvisioned(bool theIsProvisioned)
{
    myIsProvisioned = theIsProvisioned;
}

//Get Link s Provisioned field
bool CFG_Dccl::GetIsProvisioned() const
{
    return myIsProvisioned;
}


void CFG_Dccl::SetProtocolLinkEnabled(bool theEnabled)
{
    myProtocolLinkEnabled = theEnabled;
}

bool CFG_Dccl::GetProtocolLinkEnabled() const
{
    return myProtocolLinkEnabled;
}


void CFG_Dccl::SetChecksumEnabled(bool theChecksumEnabled)
{
    myChecksumEnabled = theChecksumEnabled;
}

bool CFG_Dccl::GetChecksumEnabled() const
{
    return myChecksumEnabled;
}


void CFG_Dccl::SetHoldingTimerMultiplier(uint8 theHTMultiplier)
{
    myHTMultiplier = theHTMultiplier;
}

uint8 CFG_Dccl::GetHoldingTimerMultiplier() const
{
    return myHTMultiplier;
}


void CFG_Dccl::SetConfigurationTimer(uint16 theConfigTimer)
{
    myConfigTimer = theConfigTimer;
}

uint16 CFG_Dccl::GetConfigurationTimer() const
{
    return myConfigTimer;
}


void CFG_Dccl::SetHelloTimer(uint8 theHelloTimer)
{
    myHelloTimer = theHelloTimer;
}

uint8 CFG_Dccl::GetHelloTimer() const
{
    return myHelloTimer;
}


void CFG_Dccl::SetDefaultMetric(uint8 theDefaultMetric)
{
    myDefaultMetric = theDefaultMetric;
}

uint8 CFG_Dccl::GetDefaultMetric() const
{
    return myDefaultMetric;
}


void CFG_Dccl::SetReDirectHoldingTimer(uint16 theReDirectHoldingTimer)
{
    myReDirectHoldingTimer = theReDirectHoldingTimer;
}

uint16 CFG_Dccl::GetReDirectHoldingTimer() const
{
    return myReDirectHoldingTimer;
}


void CFG_Dccl::SetLinkRoutingLevel(uint8 theRoutingLevel)
{
    myLinkRoutingLevel = theRoutingLevel;
}

uint8 CFG_Dccl::GetLinkRoutingLevel() const
{
    return myLinkRoutingLevel;
}


void CFG_Dccl::SetESConfigurationTimer(uint16 theESConfigurationTimer)
{
    myESConfigurationTimer = theESConfigurationTimer;
}

uint16 CFG_Dccl::GetESConfigurationTimer() const
{
    return myESConfigurationTimer;
}


void CFG_Dccl::SetFollowProtection(bool theFollowProtectionEnabled)
{
    myFollowProtectionEnabled = theFollowProtectionEnabled;
}

bool CFG_Dccl::GetFollowProtection() const
{
    return myFollowProtectionEnabled;
}



void CFG_Dccl::Reset(void)
{
    // Initialize all attributes to default values.
    myLinkRouterId = 0;
    myRouterShelfId = 0;
    myIfIndexId = 0;
    myLprfId = UNKNOWN_Link_Profile_ID;
    myProtocolLinkEnabled = false;
    myIsProvisioned = 0;
    myChecksumEnabled = false;
    myHTMultiplier = 0;
    myConfigTimer = 0;
    myHelloTimer = 0;
    myDefaultMetric = 0;
    myReDirectHoldingTimer = 0;
    myLinkRoutingLevel = 0;
    myESConfigurationTimer = 0;
    myFollowProtectionEnabled = false;
}

// For Display
ostream& CFG_Dccl::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);

    theStream   << FC_InsertVar(myLinkRouterId);
    theStream   << FC_InsertVar(myRouterShelfId);
    theStream   << FC_InsertVar(myIfIndexId);
    theStream   << FC_InsertVar(myLprfId);

    theStream   << FC_InsertVar(myProtocolLinkEnabled);
    theStream   << FC_InsertVar(myIsProvisioned);

    theStream   << FC_InsertVar(myChecksumEnabled);
    theStream   << FC_InsertVar(myHTMultiplier);
    theStream   << FC_InsertVar(myConfigTimer);
    theStream   << FC_InsertVar(myHelloTimer);
    theStream   << FC_InsertVar(myDefaultMetric);
    theStream   << FC_InsertVar(myReDirectHoldingTimer);
    theStream   << FC_InsertVar(myLinkRoutingLevel);
    theStream   << FC_InsertVar(myESConfigurationTimer);
    theStream   << FC_InsertVar(myFollowProtectionEnabled);

    return theStream;
}

istream& CFG_Dccl::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myLinkRouterId);
    theStream   >> FC_ExtractVar(myRouterShelfId);
    theStream   >> FC_ExtractVar(myIfIndexId);
    theStream   >> FC_ExtractVar(myLprfId);

    theStream   >> FC_ExtractVar(myProtocolLinkEnabled);
    theStream   >> FC_ExtractVar(myIsProvisioned);

    theStream   >> FC_ExtractVar(myChecksumEnabled);
    theStream   >> FC_ExtractVar(myHTMultiplier);
    theStream   >> FC_ExtractVar(myConfigTimer);
    theStream   >> FC_ExtractVar(myHelloTimer);
    theStream   >> FC_ExtractVar(myDefaultMetric);
    theStream   >> FC_ExtractVar(myReDirectHoldingTimer);
    theStream   >> FC_ExtractVar(myLinkRoutingLevel);
    theStream   >> FC_ExtractVar(myESConfigurationTimer);
    theStream   >> FC_ExtractVar(myFollowProtectionEnabled);

    return theStream;
}

// For persitance and region transfer
FC_Stream& CFG_Dccl::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);


    theStream   << myLinkRouterId;
    theStream   << myRouterShelfId;
    theStream   << myIfIndexId;
    theStream   << myLprfId;

    theStream   << myProtocolLinkEnabled;
    theStream   << myIsProvisioned;

    theStream   << myFollowProtectionEnabled;

    return theStream;
}

FC_Stream& CFG_Dccl::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >> myLinkRouterId;
    theStream   >> myRouterShelfId;
    theStream   >> myIfIndexId;
    theStream   >> myLprfId;

    theStream   >> myProtocolLinkEnabled;
    theStream   >> myIsProvisioned;

    theStream   >> myFollowProtectionEnabled;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Dccl::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto DCCLERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"isprov",6))
    {
        SetIsProvisioned(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"logic",5))
    {
        SetLinkRouterID(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"shelf",5))
    {
        SetRouterShelfID(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"ifind",5))
    {
        SetIntfID(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"lprf",4))
    {
        SetLinkProfileID(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"link",4))
    {
        SetProtocolLinkEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"check",5))
    {
        SetChecksumEnabled(argv[1][0]=='e');
    }
    else if (!strncmp(aParam,"hold",4))
    {
        SetHoldingTimerMultiplier(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"conf",4))
    {
        SetConfigurationTimer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"hello",5))
    {
        SetHelloTimer(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"defa",4))
    {
        SetDefaultMetric(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"redir",5))
    {
        SetReDirectHoldingTimer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"rout",4))
    {
        SetLinkRoutingLevel(uint8(atoi(argv[1])));
    }
    else if (!strncmp(aParam,"escon",5))
    {
        SetESConfigurationTimer(atoi(argv[1]));
    }
    else if (!strncmp(aParam,"fol",3))
    {
        SetFollowProtection(argv[1][0]=='e');
    }
    else
    {
        goto DCCLERROR;
    }


    return FC_CmdProcessor::E_SUCCESS;

DCCLERROR:
    {
        fc_cout << "dccl logicalid     <integer (id)> " << endl;
        fc_cout << "dccl shelfid       <integer (id)> " << endl;
        fc_cout << "dccl ifindexid     <4 byte hex value> " << endl;
        fc_cout << "dccl lprfid        <integer (id)> " << endl;
        fc_cout << "dccl linkenable    <e-nable|d-isable> "  << endl;
        fc_cout << "dccl isprovisioned <e-nable|d-isable> "  << endl;
        fc_cout << "dccl checksum      <e-nable|d-isable> "  << endl;
        fc_cout << "dccl htmultipli    <2-63> "  << endl;
        fc_cout << "dccl configtimer   <1-300> (sec)" << endl;
        fc_cout << "dccl hellotimer    <2-50> (sec)" << endl;
        fc_cout << "dccl defaultmetric <0-63> " << endl;
        fc_cout << "dccl redirecttimer <2-600> (sec)" << endl;
        fc_cout << "dccl routinglevel  <1-3> " << endl;
        fc_cout << "dccl esconfigtimer <1-600> (sec)" << endl;
        fc_cout << "dccl follprot      <e-nable|d-isable> " << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

//    return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Dccl::Display( FC_Stream& theStream )
{
    theStream   << "Lapd Parameters:" << endl;
    theStream   << "  DCCL  - Lapd Is Provisioned [isprovisioned] = " << DISPLAY_BOOL(myIsProvisioned) << endl;
    theStream   << "  DCCL  - Lapd Link  Enabled  [linkenable]    = " << DISPLAY_BOOL(myProtocolLinkEnabled) << endl;
    theStream   << "  DCCL  - Lapd Profile ID     [lprfid]        = " << uint32(myLprfId) << endl;
    theStream   << "  DCCL  - Interface Index ID  [ifindexid]     = " << hex << myIfIndexId << dec << endl;
    theStream   << "  DCCL  - Router Logical ID   [logicalid]     = " << uint32(myLinkRouterId) << endl;
    theStream   << "  DCCL  - Router Shelf ID     [shelfid]       = " << uint32(myRouterShelfId) << endl;

    theStream   << "  DCCL  - Checksum Enabled    [checksum]      = " << DISPLAY_BOOL(myChecksumEnabled) << endl;
    theStream   << "  DCCL  - Holding Timer Mult  [htmultipli]    = " << uint32(myHTMultiplier) << endl;
    theStream   << "  DCCL  - Config Timer (s)    [configtimer]   = " << uint32(myConfigTimer) << endl;
    theStream   << "  DCCL  - Hello Timer (s)     [hellotimer]    = " << uint32(myHelloTimer) << endl;
    theStream   << "  DCCL  - Default Metric      [defaultmetric] = " << uint32(myDefaultMetric) << endl;
    theStream   << "  DCCL  - ReDirect Timer (s)  [redirecttimer] = " << uint32(myReDirectHoldingTimer) << endl;
    theStream   << "  DCCL  - Routing Level       [routinglevel]  = " << uint32(myLinkRoutingLevel) << endl;
    theStream   << "  DCCL  - ES Config Timer (s) [esconfigtimer] = " << uint32(myESConfigurationTimer) << endl;
    theStream   << "  DCCL  - Follow Protection   [followprotect] = " << DISPLAY_BOOL(myFollowProtectionEnabled) << endl;
}

