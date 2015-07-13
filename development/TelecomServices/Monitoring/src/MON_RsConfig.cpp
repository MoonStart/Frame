//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_RsConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_RsConfig::MON_RsConfig(uint32 theIndex):
    MON_Config(theIndex),
    myExpectedTrace(),
    myTIMMonitoringEnable(false),
    myLayerFailOnTIM(false),
    myIsConnectedAsSrc(false),
    myIsConnectedAsDst(false),
    myDefectFailLayerBitMask(MON_FAILLAYER_RS_DEFAULT_BITMASK)
{
}

MON_RsConfig::~MON_RsConfig()
{
}

void MON_RsConfig::Reset(void)
{
    MON_Config::Reset();
    myExpectedTrace = CT_SDH16ByteTrace();
    myTIMMonitoringEnable = false;
    myLayerFailOnTIM = false;
    myIsConnectedAsSrc = false;
    myIsConnectedAsDst = false;
    myDefectFailLayerBitMask = MON_FAILLAYER_RS_DEFAULT_BITMASK;
}

bool MON_RsConfig::SetExpectedTrace(const CT_SDH16ByteTrace& theTrace)
{
    bool hasChanged = (!(myExpectedTrace == theTrace));
    myExpectedTrace = theTrace;
    return hasChanged;
}

const CT_SDH16ByteTrace MON_RsConfig::GetExpectedTrace() const
{
    return myExpectedTrace;
}

bool MON_RsConfig::SetTIMMonitoringEnable(bool theTIMMonitoringState)
{
    // This setting has effect only in LTE termination type.
    bool hasChanged = (myTIMMonitoringEnable != theTIMMonitoringState);
    myTIMMonitoringEnable = theTIMMonitoringState;
    return hasChanged;
}

bool MON_RsConfig::GetTIMMonitoringEnable() const
{
    return myTIMMonitoringEnable;
}

bool MON_RsConfig::SetLayerFailOnTIM(bool theLayerFailOnTIM)
{
    bool hasChanged = (myLayerFailOnTIM != theLayerFailOnTIM);
    myLayerFailOnTIM = theLayerFailOnTIM;
    return hasChanged;
}

bool MON_RsConfig::GetLayerFailOnTIM() const
{
    return myLayerFailOnTIM;
}

bool MON_RsConfig::SetIsConnectedAsSrc(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsSrc != theState)
    {
        myIsConnectedAsSrc = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetIsConnectedAsSrc() const
{
    return myIsConnectedAsSrc;
}

bool MON_RsConfig::SetIsConnectedAsDst(bool theState)
{
    bool hasChanged = false;
    if (myIsConnectedAsDst != theState)
    {
        myIsConnectedAsDst = theState;
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetIsConnectedAsDst() const
{
    return myIsConnectedAsDst;
}

bool MON_RsConfig::SetLosFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLosFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSLOS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSLOS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetLosFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSLOS_BITMASK) == 0 ? false : true;
}

bool MON_RsConfig::SetLofFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLofFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSLOF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSLOF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetLofFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSLOF_BITMASK) == 0 ? false : true;
}


bool MON_RsConfig::SetTlabAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetTlabAisFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSTLABAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSTLABAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetTlabAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSTLABAIS_BITMASK) == 0 ? false : true;
}

bool MON_RsConfig::SetGenAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGenAisFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSGENAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSGENAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetGenAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSGENAIS_BITMASK) == 0 ? false : true;
}

bool MON_RsConfig::SetTimFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetTimFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSTIM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSTIM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetTimFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSTIM_BITMASK) == 0 ? false : true;
}

bool MON_RsConfig::SetLfFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetLfFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSLF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSLF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetLfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSLF_BITMASK) == 0 ? false : true;
}

bool MON_RsConfig::SetInternalLofFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetInternalLofFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSINTLOF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSINTLOF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetInternalLofFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSINTLOF_BITMASK) == 0 ? false : true;
}

bool MON_RsConfig::SetRfFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetRfFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_RSRF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_RSRF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_RsConfig::GetRfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_RSRF_BITMASK) == 0 ? false : true;
}

uint16 MON_RsConfig::GetFailLayerBitMask() const
{
    return myDefectFailLayerBitMask;
}

ostream& MON_RsConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myExpectedTrace);
    theStream << FC_InsertVar(myTIMMonitoringEnable);
    theStream << FC_InsertVar(myLayerFailOnTIM);
    theStream << FC_InsertVar(myIsConnectedAsSrc);
    theStream << FC_InsertVar(myIsConnectedAsDst);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);
    return theStream;
}

istream& MON_RsConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myExpectedTrace);
    theStream >> FC_ExtractVar(myTIMMonitoringEnable);
    theStream >> FC_ExtractVar(myLayerFailOnTIM);
    theStream >> FC_ExtractVar(myIsConnectedAsSrc);
    theStream >> FC_ExtractVar(myIsConnectedAsDst);
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);
    return theStream;
}

FC_Stream& MON_RsConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myExpectedTrace;
    theStream << myTIMMonitoringEnable;
    theStream << myLayerFailOnTIM;
    theStream << myIsConnectedAsSrc;
    theStream << myIsConnectedAsDst;
    theStream << myDefectFailLayerBitMask;
    return theStream;
}

FC_Stream& MON_RsConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myExpectedTrace;
    theStream >> myTIMMonitoringEnable;
    theStream >> myLayerFailOnTIM;
    theStream >> myIsConnectedAsSrc;
    theStream >> myIsConnectedAsDst;
    theStream >> myDefectFailLayerBitMask;
    return theStream;
}

void MON_RsConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "RS      - TIM Monitoring        [tim]       = " << DISPLAY_BOOL(myTIMMonitoringEnable) << endl;
    theStream   << "RS      - Layer Fail On TIM     [timfail]   = " << DISPLAY_BOOL(myLayerFailOnTIM) << endl;
    theStream   << "RS      - Is Connected As Src   [src]       = " << DISPLAY_BOOL(myIsConnectedAsSrc) << endl;
    theStream   << "RS      - Is Connected As Dst   [dst]       = " << DISPLAY_BOOL(myIsConnectedAsDst) << endl;
    theStream   << "RS      - Expected Trace        [trace]     = " ;
    myExpectedTrace.Display(theStream);
    theStream   << "RS      - LOS Fail Layer                    = " << DISPLAY_BOOL(GetLosFailLayer()) << endl;  
    theStream   << "RS      - LOF Fail Layer                    = " << DISPLAY_BOOL(GetLofFailLayer()) << endl;  
    theStream   << "RS      - TLABAIS Fail Layer                = " << DISPLAY_BOOL(GetTlabAisFailLayer()) << endl;  
    theStream   << "RS      - TIM Fail Layer                    = " << DISPLAY_BOOL(GetTimFailLayer()) << endl;  
    theStream   << "RS      - GENAIS Fail Layer                 = " << DISPLAY_BOOL(GetGenAisFailLayer()) << endl;     
    theStream   << "RS      - INTERNALLOF Fail Layer            = " << DISPLAY_BOOL(GetInternalLofFailLayer()) << endl;
    theStream   << "RS      - LF Fail Layer                     = " << DISPLAY_BOOL(GetLfFailLayer()) << endl;     
    theStream   << "RS      - RF Fail Layer                     = " << DISPLAY_BOOL(GetRfFailLayer()) << endl;     
 }

FC_CmdProcessor::STATUS MON_RsConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto RSERROR;

    if (!strcmp(argv[0],"tim"))
    {
        SetTIMMonitoringEnable(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"timfail"))
    {
        SetLayerFailOnTIM(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"src"))
    {
        SetIsConnectedAsSrc(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"dst"))
    {
        SetIsConnectedAsDst(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"trace"))
    {
        string aMessage(argv[1]); aMessage.resize(15,' ');
        CT_SDH16ByteTrace aTrace(aMessage);
        SetExpectedTrace(aTrace);
    }
    else if (!strcmp(argv[0],"losfaillayer"))
    {
        SetLosFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"loffaillayer"))
    {
        SetLofFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"tlabaisfaillayer"))
    {
        SetTlabAisFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"genaisfaillayer"))
    {
        SetGenAisFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"timfaillayer"))
    {
        SetTimFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"lffaillayer"))
    {
        SetLfFailLayer(argv[1][0]=='e');
    }   
    else if (!strcmp(argv[0],"rffaillayer"))
    {
        SetRfFailLayer(argv[1][0]=='e');
    }
    else
    {
        goto RSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

RSERROR:
    {
        fc_cout << "rs <src|dst> <e-nable|d-isable> " << endl;
        fc_cout << "rs <tim|timfail> <e-nable|d-isable> " << endl;
        fc_cout << "rs <trace> <15-byte message>" << endl;
        fc_cout << "rs losfaillayer             <e-nable|d-isable> " << endl;
        fc_cout << "rs loffaillayer             <e-nable|d-isable> " << endl;
        fc_cout << "rs tlabaisfaillayer         <e-nable|d-isable> " << endl;
        fc_cout << "rs timfaillayer             <e-nable|d-isable> " << endl;
        fc_cout << "rs genaisfaillayer          <e-nable|d-isable> " << endl;
        fc_cout << "rs lffaillayer              <e-nable|d-isable> " << endl;
        fc_cout << "rs rffaillayer              <e-nable|d-isable> " << endl;
        fc_cout << "rs internalloffaillayer     <e-nable|d-isable> " << endl;     
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}
