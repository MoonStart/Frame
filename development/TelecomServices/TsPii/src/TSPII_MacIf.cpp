/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Denham Reynolds March 2008
 DESCRIPTION:Definition of the class TSPII_MacIf. Models the Media Access
             Control termination entity.
 MODIFIED :
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_MacIf.h"
#include "BaseClass/FC_TextStream.h"
#include "TsPii/TSPII_Common.h"
#include <string.h>

const uint8 MAC_REFRESH = 4;     //refresh Get modifier

///////////////////////////////////////////////////////////////////////////////
TSPII_MacIf::TSPII_MacIf(bool theDefault) :
    TSPII_BaseIf(theDefault)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////////
TSPII_MacIf::~TSPII_MacIf()
{
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::RefreshGet()
{

    // Monitoring attributes
    itsAutoNegStatus = GetAutoNegStatus();
    itsAutoNegRemoteSignal = GetAutoNegRemoteSignal();
    itsOpRate = GetOpRate();
    itsOpDuplexMode = GetOpDuplexMode();
    itsOpFlowCtrl = GetOpFlowCtrl();
    itsOpAutoNeg = GetOpAutoNeg();
    itsLinkFailRx = GetLinkFailRx();
    itsRFLinkFail = GetRFLinkFail();
    itsFefi = GetFefi();
    itsEthSfpXfpType = GetEthSfpXfpType();

    //itsLacpFail = GetLacpFail();

    itsPortLacpState = GetPortLacpState();
    itsPortAggregationField = GetPortAggregationField();
    itsPortLacpPriority  = GetPortLacpPriority();
    itsPartnerActiveFlag = GetPartnerActiveFlag();
    itsPartnerSystemID = GetPartnerSystemID();
    itsPartnerPortPriority = GetPartnerPortPriority();
    itsPartnerOperationalKey = GetPartnerOperationalKey();
    itsPartnerPortState = GetPartnerPortState();
    itsLagActorSystemID = GetLagActorSystemID();
    itsLagActorSystemPriority = GetLagActorSystemPriority();
    itsLagActorOperationalKey = GetLagActorOperationalKey();
    itsLagActorAdminKey = GetLagActorAdminKey();
    itsLagPartnerSystemID = GetLagPartnerSystemID();
    itsLagPartnerSystemPriority = GetLagPartnerSystemPriority();
    itsLagPartnerOperationalKey = GetLagPartnerOperationalKey();
    itsLagPartnerAdminKey = GetLagPartnerAdminKey();

    // Configuration attributes
    itsAutoNeg = GetAutoNeg();
    itsCfgRate = GetCfgRate();
    itsCfgDuplexMode = GetCfgDuplexMode();
    itsCfgFlowCtrl = GetCfgFlowCtrl();
    itsCfgAdvrtFlowCtrl = GetCfgAdvrtFlowCtrl();
    itsFefiTransparencyEnabled= GetFefiTransparencyEnabled();
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::RefreshSet()
{
    // Configuration attributes
    SetAutoNeg(itsAutoNeg);
    SetCfgRate(itsCfgRate);
    SetCfgDuplexMode(itsCfgDuplexMode);
    SetCfgFlowCtrl(itsCfgFlowCtrl);
    SetCfgAdvrtFlowCtrl(itsCfgAdvrtFlowCtrl);
    EnableFefiTransparency(itsFefiTransparencyEnabled);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::Reset()
{
    TSPII_BaseIf::Reset();

    // Monitoring attributes
    itsAutoNegStatus = CT_TEL_MAC_AUTONEG_UNKNOWN;
    itsAutoNegRemoteSignal = CT_TEL_DETECTED_UNKNOWN;
    itsOpRate = 0;
    itsOpDuplexMode = CT_TEL_MAC_DUPLEX_UNKNOWN;
    itsOpFlowCtrl = CT_TEL_MAC_FLW_UNKNOWN;
    itsOpAutoNeg = false;
    itsLinkFailRx = 0;
    itsRFLinkFail = 0;
    itsFefi = 0;
    itsEthSfpXfpType = CT_ETH_NOT_ASSIGNED;

    //itsLacpFail = 0;

    itsPortLacpState = CT_TEL_LacpPortState_UNKNOWN;
    itsPortAggregationField = 0;
    itsPortLacpPriority  = 0;;
    itsPartnerActiveFlag = false;
    itsPartnerSystemID = CT_LacpSystemId();
    itsPartnerPortPriority = 0;
    itsPartnerOperationalKey = 0;
    itsPartnerPortState = 0;
    itsLagActorSystemID = CT_LacpSystemId();
    itsLagActorSystemPriority = 0;
    itsLagActorOperationalKey = 0;
    itsLagActorAdminKey = 0;
    itsLagPartnerSystemID = CT_LacpSystemId();
    itsLagPartnerSystemPriority = 0;
    itsLagPartnerOperationalKey = 0;
    itsLagPartnerAdminKey = 0;

    // Configuration attributes
    itsAutoNeg = false;
    itsCfgRate = 0;
    itsCfgDuplexMode = CT_TEL_MAC_DUPLEX_UNKNOWN;
    itsCfgFlowCtrl = CT_TEL_MAC_FLW_UNKNOWN;
    itsCfgAdvrtFlowCtrl = CT_TEL_MAC_ADFLW_UNKNOWN;
    trace = 0;
    itsFefiTransparencyEnabled= false;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MAC_AUTONEGSTATUS TSPII_MacIf::GetAutoNegStatus()
{
    return itsAutoNegStatus;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_DETECTED TSPII_MacIf::GetAutoNegRemoteSignal()
{
    return itsAutoNegRemoteSignal;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_daHz TSPII_MacIf::GetOpRate()
{
    return itsOpRate;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MAC_DUPLEX_MODE TSPII_MacIf::GetOpDuplexMode()
{
    return itsOpDuplexMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MAC_FLOWCTRL TSPII_MacIf::GetOpFlowCtrl()
{
    return itsOpFlowCtrl;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MacIf::GetOpAutoNeg()
{
    return itsOpAutoNeg;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MacIf::GetLinkFailRx()
{
    return itsLinkFailRx;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MacIf::GetRFLinkFail()
{
    return itsRFLinkFail;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::SetAutoNeg(bool theEnable)
{
    itsAutoNeg = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MacIf::GetAutoNeg() const
{
    return itsAutoNeg;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::SetCfgRate(CT_TEL_daHz theRate)
{
    itsCfgRate = theRate;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_daHz TSPII_MacIf::GetCfgRate() const
{
    return itsCfgRate;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::SetCfgDuplexMode(CT_TEL_MAC_DUPLEX_MODE theMode)
{
    itsCfgDuplexMode = theMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MAC_DUPLEX_MODE TSPII_MacIf::GetCfgDuplexMode() const
{
    return itsCfgDuplexMode;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::SetCfgFlowCtrl(CT_TEL_MAC_FLOWCTRL theMode)
{
    itsCfgFlowCtrl = theMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MAC_FLOWCTRL TSPII_MacIf::GetCfgFlowCtrl() const
{
    return itsCfgFlowCtrl;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::SetCfgAdvrtFlowCtrl(CT_TEL_MAC_ADFLW_CTRL theMode)
{
    itsCfgAdvrtFlowCtrl = theMode;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_MAC_ADFLW_CTRL TSPII_MacIf::GetCfgAdvrtFlowCtrl() const
{
    return itsCfgAdvrtFlowCtrl;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MacIf::GetFefi()
{
    return itsFefi;
}


///////////////////////////////////////////////////////////////////////////////
CT_ETH_SFP_XFP_TYPE TSPII_MacIf::GetEthSfpXfpType() const
{
    return itsEthSfpXfpType;
}


///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::EnableFefiTransparency(bool enable)
{
    itsFefiTransparencyEnabled = enable;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MacIf::GetFefiTransparencyEnabled() const
{
    return itsFefiTransparencyEnabled;
}


///////////////////////////////////////////////////////////////////////////////
//uint32 TSPII_MacIf::GetLacpFail()
//{
//    return itsLacpFail;
//}


///////////////////////////////////////////////////////////////////////////////
CT_TEL_LacpPortState TSPII_MacIf::GetPortLacpState() const
{
    return itsPortLacpState;
}

///////////////////////////////////////////////////////////////////////////////
CT_AGGRE_FIELD TSPII_MacIf::GetPortAggregationField() const
{
    return itsPortAggregationField;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MacIf::GetPortLacpPriority() const
{
    return itsPortLacpPriority;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MacIf::GetPartnerActiveFlag() const
{
    return itsPartnerActiveFlag;
}

///////////////////////////////////////////////////////////////////////////////
const CT_LacpSystemId & TSPII_MacIf::GetPartnerSystemID() const
{
    return itsPartnerSystemID;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MacIf::GetPartnerPortPriority() const
{
    return itsPartnerPortPriority;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MacIf::GetPartnerOperationalKey() const
{
    return itsPartnerOperationalKey;
}

///////////////////////////////////////////////////////////////////////////////
uint8 TSPII_MacIf::GetPartnerPortState() const
{
    return itsPartnerPortState;
}


///////////////////////////////////////////////////////////////////////////////
const CT_LacpSystemId & TSPII_MacIf::GetLagActorSystemID() const
{
    return itsLagActorSystemID;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MacIf::GetLagActorSystemPriority() const
{
    return itsLagActorSystemPriority;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MacIf::GetLagActorOperationalKey() const
{
    return itsLagActorOperationalKey;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MacIf::GetLagActorAdminKey() const
{
    return itsLagActorAdminKey;
}


///////////////////////////////////////////////////////////////////////////////
const CT_LacpSystemId & TSPII_MacIf::GetLagPartnerSystemID() const
{
    return itsLagPartnerSystemID;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MacIf::GetLagPartnerSystemPriority() const
{
    return itsLagPartnerSystemPriority;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_MacIf::GetLagPartnerOperationalKey() const
{
    return itsLagPartnerOperationalKey;
}

///////////////////////////////////////////////////////////////////////////////
uint16 TSPII_MacIf::GetLagPartnerAdminKey() const
{
    return itsLagPartnerAdminKey;
}



///////////////////////////////////////////////////////////////////////////////

FC_Stream & TSPII_MacIf::WriteObjectBinary(FC_Stream & theStream)
{
    int     aTemp;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring attributes
    aTemp = itsAutoNegStatus;
    theStream << aTemp;
    aTemp = itsAutoNegRemoteSignal;
    theStream << aTemp;
    theStream << itsOpRate;
    aTemp = itsOpDuplexMode;
    theStream << aTemp;
    aTemp = itsOpFlowCtrl;
    theStream << aTemp;
    theStream << itsOpAutoNeg;
    theStream << itsLinkFailRx;
    theStream << itsRFLinkFail;
    theStream << itsFefi;
    aTemp = itsEthSfpXfpType;
    theStream << aTemp;

    //theStream << itsLacpFail;
    aTemp = itsPortLacpState;
    theStream << aTemp;
    theStream << itsPortAggregationField;
    theStream << itsPortLacpPriority;
    theStream << itsPartnerActiveFlag;
    theStream << itsPartnerSystemID;
    theStream << itsPartnerPortPriority;
    theStream << itsPartnerOperationalKey;
    theStream << itsPartnerPortState;
    theStream << itsLagActorSystemID;
    theStream << itsLagActorSystemPriority;
    theStream << itsLagActorOperationalKey;
    theStream << itsLagActorAdminKey;
    theStream << itsLagPartnerSystemID;
    theStream << itsLagPartnerSystemPriority;
    theStream << itsLagPartnerOperationalKey;
    theStream << itsLagPartnerAdminKey;

    // Configuration attributes
    theStream << itsAutoNeg;
    theStream << itsCfgRate;
    aTemp = itsCfgDuplexMode;
    theStream << aTemp;
    aTemp = itsCfgFlowCtrl;
    theStream << aTemp;
    aTemp = itsCfgAdvrtFlowCtrl;
    theStream << aTemp;
    theStream << itsFefiTransparencyEnabled;

    return TSPII_BaseIf::WriteObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
FC_Stream & TSPII_MacIf::ReadObjectBinary(FC_Stream & theStream)
{
    int     aTemp;

    // Monitoring attributes
    theStream >> aTemp;
    itsAutoNegStatus = (CT_TEL_MAC_AUTONEGSTATUS) aTemp;
    theStream >> aTemp;
    itsAutoNegRemoteSignal = (CT_TEL_DETECTED) aTemp;
    theStream >> itsOpRate;
    theStream >> aTemp;
    itsOpDuplexMode = (CT_TEL_MAC_DUPLEX_MODE) aTemp;
    theStream >> aTemp;
    itsOpFlowCtrl = (CT_TEL_MAC_FLOWCTRL) aTemp;
    theStream >> itsOpAutoNeg;
    theStream >> itsLinkFailRx;
    theStream >> itsRFLinkFail;
    theStream >> itsFefi;
    theStream >> aTemp;
    itsEthSfpXfpType = (CT_ETH_SFP_XFP_TYPE) aTemp;

    //theStream >> itsLacpFail;
    theStream >> aTemp;
    itsPortLacpState = (CT_TEL_LacpPortState) aTemp;
    theStream >> itsPortAggregationField;
    theStream >> itsPortLacpPriority;
    theStream >> itsPartnerActiveFlag;
    theStream >> itsPartnerSystemID;
    theStream >> itsPartnerPortPriority;
    theStream >> itsPartnerOperationalKey;
    theStream >> itsPartnerPortState;
    theStream >> itsLagActorSystemID;
    theStream >> itsLagActorSystemPriority;
    theStream >> itsLagActorOperationalKey;
    theStream >> itsLagActorAdminKey;
    theStream >> itsLagPartnerSystemID;
    theStream >> itsLagPartnerSystemPriority;
    theStream >> itsLagPartnerOperationalKey;
    theStream >> itsLagPartnerAdminKey;

    // Configuration attributes
    theStream >> itsAutoNeg;
    theStream >> itsCfgRate;
    theStream >> aTemp;
    itsCfgDuplexMode = (CT_TEL_MAC_DUPLEX_MODE) aTemp;
    theStream >> aTemp;
    itsCfgFlowCtrl = (CT_TEL_MAC_FLOWCTRL) aTemp;
    theStream >> aTemp;
    itsCfgAdvrtFlowCtrl = (CT_TEL_MAC_ADFLW_CTRL) aTemp;
    theStream >> itsFefiTransparencyEnabled;

    RefreshSet();

    return TSPII_BaseIf::ReadObjectBinary(theStream);
}

///////////////////////////////////////////////////////////////////////////////
ostream & TSPII_MacIf::WriteObject(ostream & theStream)
{
    int     aTemp;

    // Update H/W
    UpdateValues();
    RefreshGet();

    // Monitoring attributes
    aTemp = itsAutoNegStatus;
    theStream << FC_InsertVar(aTemp);
    aTemp = itsAutoNegRemoteSignal;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(itsOpRate);
    aTemp = itsOpDuplexMode;
    theStream << FC_InsertVar(aTemp);
    aTemp = itsOpFlowCtrl;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(itsOpAutoNeg);
    theStream << FC_InsertVar(itsLinkFailRx);
    theStream << FC_InsertVar(itsRFLinkFail);
    theStream << FC_InsertVar(itsFefi);
    aTemp = itsEthSfpXfpType;
    theStream << FC_InsertVar(aTemp);

    //theStream << FC_InsertVar(itsLacpFail);
    aTemp = itsPortLacpState;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(itsPortAggregationField);
    theStream << FC_InsertVar(itsPortLacpPriority);
    theStream << FC_InsertVar(itsPartnerActiveFlag);
    theStream << FC_InsertVar(itsPartnerSystemID);
    theStream << FC_InsertVar(itsPartnerPortPriority);
    theStream << FC_InsertVar(itsPartnerOperationalKey);
    theStream << FC_InsertVar(itsPartnerPortState);
    theStream << FC_InsertVar(itsLagActorSystemID);
    theStream << FC_InsertVar(itsLagActorSystemPriority);
    theStream << FC_InsertVar(itsLagActorOperationalKey);
    theStream << FC_InsertVar(itsLagActorAdminKey);
    theStream << FC_InsertVar(itsLagPartnerSystemID);
    theStream << FC_InsertVar(itsLagPartnerSystemPriority);
    theStream << FC_InsertVar(itsLagPartnerOperationalKey);
    theStream << FC_InsertVar(itsLagPartnerAdminKey);

    // Configuration attributes
    theStream << FC_InsertVar(itsAutoNeg);
    theStream << FC_InsertVar(itsCfgRate);
    aTemp = itsCfgDuplexMode;
    theStream << FC_InsertVar(aTemp);
    aTemp = itsCfgFlowCtrl;
    theStream << FC_InsertVar(aTemp);
    aTemp = itsCfgAdvrtFlowCtrl;
    theStream << FC_InsertVar(aTemp);
    theStream << FC_InsertVar(itsFefiTransparencyEnabled);

    return TSPII_BaseIf::WriteObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
istream & TSPII_MacIf::ReadObject(istream & theStream)
{
    int     aTemp;

    // Monitoring attributes
    theStream >> FC_ExtractVar(aTemp);
    itsAutoNegStatus = (CT_TEL_MAC_AUTONEGSTATUS) aTemp;
    theStream >> FC_ExtractVar(aTemp);
    itsAutoNegRemoteSignal = (CT_TEL_DETECTED) aTemp;
    theStream >> FC_ExtractVar(itsOpRate);
    theStream >> FC_ExtractVar(aTemp);
    itsOpDuplexMode = (CT_TEL_MAC_DUPLEX_MODE) aTemp;
    theStream >> FC_ExtractVar(aTemp);
    itsOpFlowCtrl = (CT_TEL_MAC_FLOWCTRL) aTemp;
    theStream >> FC_ExtractVar(itsOpAutoNeg);
    theStream >> FC_ExtractVar(itsLinkFailRx);
    theStream >> FC_ExtractVar(itsRFLinkFail);
    theStream >> FC_ExtractVar(itsFefi);
    theStream >> FC_ExtractVar(aTemp);
    itsEthSfpXfpType = (CT_ETH_SFP_XFP_TYPE) aTemp;

    //theStream >> FC_ExtractVar(itsLacpFail);
    theStream >> FC_ExtractVar(aTemp);
    itsPortLacpState = (CT_TEL_LacpPortState) aTemp;
    theStream >> FC_ExtractVar(itsPortAggregationField);
    theStream >> FC_ExtractVar(itsPortLacpPriority);
    theStream >> FC_ExtractVar(itsPartnerActiveFlag);
    theStream >> FC_ExtractVar(itsPartnerSystemID);
    theStream >> FC_ExtractVar(itsPartnerPortPriority);
    theStream >> FC_ExtractVar(itsPartnerOperationalKey);
    theStream >> FC_ExtractVar(itsPartnerPortState);
    theStream >> FC_ExtractVar(itsLagActorSystemID);
    theStream >> FC_ExtractVar(itsLagActorSystemPriority);
    theStream >> FC_ExtractVar(itsLagActorOperationalKey);
    theStream >> FC_ExtractVar(itsLagActorAdminKey);
    theStream >> FC_ExtractVar(itsLagPartnerSystemID);
    theStream >> FC_ExtractVar(itsLagPartnerSystemPriority);
    theStream >> FC_ExtractVar(itsLagPartnerOperationalKey);
    theStream >> FC_ExtractVar(itsLagPartnerAdminKey);

    // Configuration attributes
    theStream >> FC_ExtractVar(itsAutoNeg);
    theStream >> FC_ExtractVar(itsCfgRate);
    theStream >> FC_ExtractVar(aTemp);
    itsCfgDuplexMode = (CT_TEL_MAC_DUPLEX_MODE) aTemp;
    theStream >> FC_ExtractVar(aTemp);
    itsCfgFlowCtrl = (CT_TEL_MAC_FLOWCTRL) aTemp;
    theStream >> FC_ExtractVar(aTemp);
    itsCfgAdvrtFlowCtrl = (CT_TEL_MAC_ADFLW_CTRL) aTemp;
    theStream >> FC_ExtractVar(itsFefiTransparencyEnabled);

    RefreshSet();

    return TSPII_BaseIf::ReadObject(theStream);
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_MacIf::Display(FC_Stream & theStream)
{
    // Update H/W
    UpdateValues();
    RefreshGet();

    theStream << "  MAC Configuration/Status\n";
    theStream << "    CONFIGURATION\n";
    theStream << "      Auto Negotiation       = " << DISPLAY_BOOL(itsAutoNeg)                 << "\n";
    theStream << "      Rate                   = " << itsCfgRate << "("<< (int)(itsCfgRate/100000)<< ") Mbs" <<"\n";
    theStream << "      Duplex                 = " << DISPLAY_MAC_DUPLEX_MODE(itsCfgDuplexMode) << "\n";
    theStream << "      Flow Control           = " << DISPLAY_MAC_FLOWCTRL(itsCfgFlowCtrl)         << "\n";
    theStream << "      Advertise Flow Control = " << DISPLAY_MAC_ADFLOWCTRL(itsCfgAdvrtFlowCtrl)         << "\n";
    theStream << "      FEFI Xparency Enabled  = " << TEXT_ON_OFF(itsFefiTransparencyEnabled) << endl;
    theStream << "    MONITORING\n";
    theStream << "      Auto Neg Status        = " << DISPLAY_MAC_AUTONEGSTATUS(itsAutoNegStatus)  << "\n";
    theStream << "      Auto Neg Remote Sig    = " << DISPLAY_DETECTED(itsAutoNegRemoteSignal)  << "\n";
    theStream << "      Op Rate                = " << itsOpRate << "("<<(int) (itsOpRate/100000)<< ") Mbs" << "\n";
    theStream << "      Op Duplex Mode         = " << DISPLAY_MAC_DUPLEX_MODE(itsOpDuplexMode)      << "\n";
    theStream << "      Op Flow Control        = " << DISPLAY_MAC_FLOWCTRL(itsOpFlowCtrl)          << "\n";
    theStream << "      Op Auto Negotiation    = " << DISPLAY_BOOL(itsOpAutoNeg)                 << "\n";
    theStream << "      Link Fail Rx           = " << TEXT_DEFECT(itsLinkFailRx)         << "\n";
    theStream << "      RF Link Fail           = " << TEXT_DEFECT(itsRFLinkFail)         << "\n";
    theStream << "      Debug trace            = " << DISPLAY_MAC_TRACE(trace) << "\n";
    theStream << "      FEFI                   = " << TEXT_DEFECT(itsFefi)               << endl;
    theStream << "      Ethernet Sfp/Xfp Type  = " << DISPLAY_ETH_SFP_XFP_TYPE(itsEthSfpXfpType)      << "\n";

    //theStream << "      LACP Fail              = " << TEXT_DEFECT(itsLacpFail)               << endl;
    theStream << "      LACP Port State        = " << DISPLAY_LACP_PORT_STATE(itsPortLacpState)          << "\n";
    theStream << "      LACP Aggregation       = " << DisplayAggreField(itsPortAggregationField)          << "\n";
    theStream << "      LACP Port Priority     = " << dec << (int)itsPortLacpPriority                 << "\n";
    theStream << "      Partner Active Flag    = " << DISPLAY_BOOL(itsPartnerActiveFlag)                 << "\n";
    theStream << "      Partner System ID      = " << itsPartnerSystemID.DisplayAddr()      << "\n";
    theStream << "      Partner Port Priority  = " << dec << (int)itsPartnerPortPriority        << "\n";
    theStream << "      Partner Operational Key= " << itsPartnerOperationalKey        << "\n";
    theStream << "      Partner Port State     = 0x" << hex << static_cast<uint32>(itsPartnerPortState)  << dec  << "\n";
    theStream << "      Lag Actor System ID    = " << itsLagActorSystemID.DisplayAddr()      << "\n";
    theStream << "      Lag Actor Port Prior   = " << dec << (int)itsLagActorSystemPriority        << "\n";
    theStream << "      Lag Actor Oper Key     = " << dec << itsLagActorOperationalKey        << "\n";
    theStream << "      Lag Actor Admin Key    = " << dec << (int)itsLagActorAdminKey        << "\n";
    theStream << "      Lag Partner System ID  = " << itsLagPartnerSystemID.DisplayAddr()      << "\n";
    theStream << "      Lag Partner Port Prior = " << dec << (int)itsLagPartnerSystemPriority        << "\n";
    theStream << "      Lag Partner Oper Key   = " << dec << itsLagPartnerOperationalKey        << "\n";
    theStream << "      Lag Partner Admin Key  = " << dec << (int)itsLagPartnerAdminKey        << "\n";
    theStream << endl;

    TSPII_BaseIf::Display(theStream);
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MacIf::Set(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "autoneg") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAutoNeg(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAutoNeg(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "rate") == 0))
    {
        itsCfgRate = strtoul(argv[1], NULL, 0);
        SetCfgRate(itsCfgRate);
        printUsage = false;
    }
    else if ((argc == 2) && (strcmp(argv[0], "duplex") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_MAC_DUPLEX_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_MAC_DUPLEX_MODE(i)) == 0)
        {
            SetCfgDuplexMode((CT_TEL_MAC_DUPLEX_MODE)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "flow") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_MAC_FLW_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_MAC_FLOWCTRL(i)) == 0)
        {
            SetCfgFlowCtrl((CT_TEL_MAC_FLOWCTRL)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "adflow") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_MAC_ADFLW_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_MAC_ADFLOWCTRL(i)) == 0)
        {
            SetCfgAdvrtFlowCtrl((CT_TEL_MAC_ADFLW_CTRL)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "trace") ==0))
    {
        trace = atoi(argv[1]);
        printUsage = false;

    }
    else if(argc == 2 && strcmp(argv[0], "fefiXparency") == 0)
    {
        if(strcmp(argv[1], "on") == 0)
        {
            EnableFefiTransparency(true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            EnableFefiTransparency(false);
        }
        else
        {
            printUsage = true;
        }
    }
    else
    {
        printUsage =  TSPII_BaseIf::Set(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    autoneg         <on,off>\n"
                   "    rate            <0-X>\n"
                   "    duplex          <FullDuplex,HalfDuplex,Auto,Unknown>\n"
                   "    flow            <FlowRxTx,FlowTx,FlowRx,Unknown>\n"
                   "    adflow          <NoPause,SPause,APause,BPause,Unknown>\n"
                   "    trace           <0-X  0 = OFF, 1 = Debug, 2 = Detail>\n"
                   "    fefiXparency    <on|off>\n"<< endl;
    }

    return printUsage;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_MacIf::Simul(int argc, char ** argv)
{
    bool printUsage = false;

    if ((argc == 2) && (strcmp(argv[0], "anstatus") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_MAC_AUTONEG_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_MAC_AUTONEGSTATUS(i)) == 0)
        {
            itsAutoNegStatus = ((CT_TEL_MAC_AUTONEGSTATUS)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "anrmtsig") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_DETECTED_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_DETECTED(i)) == 0)
        {
            itsAutoNegRemoteSignal = ((CT_TEL_DETECTED)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "rate") == 0))
    {
        itsOpRate = strtoul(argv[1], NULL, 0);
    }
    else if ((argc == 2) && (strcmp(argv[0], "duplex") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_MAC_DUPLEX_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_MAC_DUPLEX_MODE(i)) == 0)
        {
            itsOpDuplexMode = ((CT_TEL_MAC_DUPLEX_MODE)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "flow") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_MAC_FLW_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_MAC_FLOWCTRL(i)) == 0)
        {
            itsOpFlowCtrl = ((CT_TEL_MAC_FLOWCTRL)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "opautoneg") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            itsOpAutoNeg = true;
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            itsOpAutoNeg = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "linkfailrx") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsLinkFailRx))
            {
                itsLinkFailRx++;
            }
            else
            {
                itsLinkFailRx+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsLinkFailRx))
            {
                itsLinkFailRx++;
            }
            else
            {
                itsLinkFailRx+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "rflinkfail") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsRFLinkFail))
            {
                itsRFLinkFail++;
            }
            else
            {
                itsRFLinkFail+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsRFLinkFail))
            {
                itsRFLinkFail++;
            }
            else
            {
                itsRFLinkFail+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if(argc == 2 && strcmp(argv[0], "fefi") == 0)
    {
        if (strcmp(argv[1], "on") == 0)
        {
            if(!TSPII_DEFECT(itsFefi))
            {
                itsFefi++;
            }
            else
            {
                itsFefi+=2;
            }

        }
        else if (strcmp(argv[1], "off") == 0)
        {
            if(TSPII_DEFECT(itsFefi))
            {
                itsFefi++;
            }
            else
            {
                itsFefi+=2;
            }
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strncmp(argv[0], "eths", 4) == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_ETH_NOT_ASSIGNED; i++) if (strcmp(argv[1], DISPLAY_ETH_SFP_XFP_TYPE(i)) == 0)
        {
            itsEthSfpXfpType = ((CT_ETH_SFP_XFP_TYPE)i);
            printUsage = false;
            break;
        }
    }
    //else if(argc == 2 && strcmp(argv[0], "lacpfail") == 0)
    //{
    //    if (strcmp(argv[1], "on") == 0)
    //    {
    //        if(!TSPII_DEFECT(itsLacpFail))
    //        {
    //            itsLacpFail++;
    //        }
    //        else
    //        {
    //            itsLacpFail+=2;
    //        }
    //
    //    }
    //    else if (strcmp(argv[1], "off") == 0)
    //    {
    //        if(TSPII_DEFECT(itsLacpFail))
    //        {
    //            itsLacpFail++;
    //        }
    //        else
    //        {
    //            itsLacpFail+=2;
    //        }
    //    }
    //    else
    //    {
    //        printUsage = true;
    //    }
    //}
    else if ((argc == 2) && (strcmp(argv[0], "portstate") == 0))
    {
        printUsage = true;
        for (int i = 0; i <= CT_TEL_LacpPortState_UNKNOWN; i++) if (strcmp(argv[1], DISPLAY_LACP_PORT_STATE(i)) == 0)
        {
            itsPortLacpState = ((CT_TEL_LacpPortState)i);
            printUsage = false;
            break;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggre") == 0))
    {
        itsPortAggregationField = (uint16) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggreAggr") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAggreFieldAggregationBit(itsPortAggregationField, true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAggreFieldAggregationBit(itsPortAggregationField, false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggreIndv") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAggreFieldIndividualBit(itsPortAggregationField, true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAggreFieldIndividualBit(itsPortAggregationField, false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggreSync") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAggreFieldSyncBit(itsPortAggregationField, true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAggreFieldSyncBit(itsPortAggregationField, false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggreColl") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAggreFieldCollectingBit(itsPortAggregationField, true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAggreFieldCollectingBit(itsPortAggregationField, false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggreDist") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAggreFieldDistributingBit(itsPortAggregationField, true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAggreFieldDistributingBit(itsPortAggregationField, false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggreDef") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAggreFieldDefaultedBit(itsPortAggregationField, true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAggreFieldDefaultedBit(itsPortAggregationField, false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portaggreExp") == 0))
    {
        if (strcmp(argv[1], "on") == 0)
        {
            SetAggreFieldExpiredBit(itsPortAggregationField, true);
        }
        else if (strcmp(argv[1], "off") == 0)
        {
            SetAggreFieldExpiredBit(itsPortAggregationField, false);
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 2) && (strcmp(argv[0], "portpriority") == 0))
    {
        itsPortLacpPriority = (uint16) atoi(argv[1]);
    }
    else if(argc == 2 && strcmp(argv[0], "partactive") == 0)
    {
        if (strcmp(argv[1], "true") == 0)
        {
            itsPartnerActiveFlag = true;
        }
        else if (strcmp(argv[1], "false") == 0)
        {
            itsPartnerActiveFlag = false;
        }
        else
        {
            printUsage = true;
        }
    }
    else if ((argc == 7) && (strcmp(argv[0], "partsysid") == 0))
    {
        CT_LacpSystemId systemid(argv[1][0], argv[2][0], argv[3][0], argv[4][0], argv[5][0], argv[6][0]);
        itsPartnerSystemID = systemid;
    }
    else if ((argc == 2) && (strcmp(argv[0], "partpriority") == 0))
    {
        itsPartnerPortPriority = (uint16) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "partoperkey") == 0))
    {
        itsPartnerOperationalKey = (uint32) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "partstate") == 0))
    {
        itsPartnerPortState = (uint8) atoi(argv[1]);
    }
    else if ((argc == 7) && (strcmp(argv[0], "lagactorsysid") == 0))
    {
        CT_LacpSystemId systemid(argv[1][0], argv[2][0], argv[3][0], argv[4][0], argv[5][0], argv[6][0]);
        itsLagActorSystemID = systemid;
    }
    else if ((argc == 2) && (strcmp(argv[0], "lagactorsysprio") == 0))
    {
        itsLagActorSystemPriority = (uint16) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "lagactoroperkey") == 0))
    {
        itsLagActorOperationalKey = (uint32) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "lagactoradminkey") == 0))
    {
        itsLagActorAdminKey = (uint16) atoi(argv[1]);
    }
    else if ((argc == 7) && (strcmp(argv[0], "lagpartsysid") == 0))
    {
        CT_LacpSystemId systemid(argv[1][0], argv[2][0], argv[3][0], argv[4][0], argv[5][0], argv[6][0]);
        itsLagPartnerSystemID = systemid;
    }
    else if ((argc == 2) && (strcmp(argv[0], "lagpartsysprio") == 0))
    {
        itsLagPartnerSystemPriority = (uint16) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "lagpartoperkey") == 0))
    {
        itsLagPartnerOperationalKey = (uint32) atoi(argv[1]);
    }
    else if ((argc == 2) && (strcmp(argv[0], "lagpartadminkey") == 0))
    {
        itsLagPartnerAdminKey = (uint16) atoi(argv[1]);
    }
    else
    {
        printUsage = TSPII_BaseIf::Simul(argc, argv);
    }
    if (printUsage)
    {
        fc_cout << "    anstatus        <Config,Complete,Disabled,PDF,Other,NA,Unknown>\n"
                   "    anrmtsig        <Yes,No,NA,Unknown>\n"
                   "    rate            <0-X>\n"
                   "    duplex          <FullDuplex,HalfDuplex,Unknown>\n"
                   "    flow            <FlowRxTx,FlowTx,FlowRx,Unknown>\n"
                   "    opautoneg       <on,off>\n"
                   "    linkfailrx      <on|off>\n"
                   "    rflinkfail      <on|off>\n"
                   "    fefi            <on|off>\n"
                   "    eths            <10G | 100_BASE_FX | 1G_ELEC | 1G_OPT | UNKNOWN \n"
                   // "    lacpfail        <on|off>\n"
                   "    portstate        <LACP_PORT_STATE_BUNDLE | LACP_PORT_STATE_STANDBY | LACP_PORT_STATE_DOWN | \n"
                   "                      LACP_PORT_STATE_PORT_UP_INDIVIDUAL | LACP_PORT_STATE_UNKNOWN>\n"
                   "    portaggre        <0- 65535>\n"
                   "    portaggreAggr    <on|off>\n"
                   "    portaggreIndv    <on|off>\n"
                   "    portaggreSync    <on|off>\n"
                   "    portaggreColl    <on|off>\n"
                   "    portaggreDist    <on|off>\n"
                   "    portaggreDef     <on|off>\n"
                   "    portaggreExp     <on|off>\n"
                   "    portpriority     <0- 65535>\n"
                   "    partactive       <true|false>\n"
                   "    partsysid        <ch1 ch2 ch3 ch4 ch5 ch6 (six chars - space separated)>\n"
                   "    partpriority     <0- 65535>\n"
                   "    partoperkey      <uint32>\n"
                   "    partstate        <0-255>\n"
                   "    lagactorsysid    <ch1 ch2 ch3 ch4 ch5 ch6 (six chars - space separated)>\n"
                   "    lagactorsysprio  <0- 65535>\n"
                   "    lagactoroperkey  <uint32>\n"
                   "    lagactoradminkey <0- 65535>\n"
                   "    lagpartsysid     <ch1 ch2 ch3 ch4 ch5 ch6 (six chars - space separated)>\n"
                   "    lagpartsysprio   <0- 65535>\n"
                   "    lagpartoperkey   <uint32>\n"
                   "    lagpartadminkey  <0- 65535>\n" << endl;
    }

    return printUsage;
}

