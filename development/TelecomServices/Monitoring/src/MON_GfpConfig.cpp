//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_GfpConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_GfpConfig::MON_GfpConfig(uint32 theIndex):
    MON_Config(theIndex),
    myDefectFailLayerBitMask(MON_FAILLAYER_GFP_DEFAULT_BITMASK)
{
}

MON_GfpConfig::~MON_GfpConfig()
{
}

void MON_GfpConfig::Reset(void)
{
    MON_Config::Reset();
    myDefectFailLayerBitMask = MON_FAILLAYER_GFP_DEFAULT_BITMASK;
}

bool MON_GfpConfig::SetGfpLfFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpLfFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPLF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPLF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpLfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPLF_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpRfFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpRfFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPRF_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPRF_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpRfFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPRF_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpFefiFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpFefiFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPFEFI_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPFEFI_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpFefiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPFEFI_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpCsfFefiFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpCsfFefiFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPCSFFEFI_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPCSFFEFI_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpCsfFefiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFFEFI_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpLinkFailRxFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpLinkFailRxFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPLINKFAILRX_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPLINKFAILRX_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpLinkFailRxFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPLINKFAILRX_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpCsfLosFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpCsfLosFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPCSFLOS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPCSFLOS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpCsfLosFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFLOS_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpLofdFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpLofdFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPLOFD_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPLOFD_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpLofdFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPLOFD_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpPlmFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpPlmFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPPLM_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPPLM_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpPlmFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPPLM_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpCsfLosyncFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpCsfLosyncFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPCSFLOSYNC_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPCSFLOSYNC_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpCsfLosyncFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFLOSYNC_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpCsfFdiFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpCsfFdiFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPCSFFDI_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPCSFFDI_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpCsfFdiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFFDI_BITMASK) == 0 ? false : true;
}

bool MON_GfpConfig::SetGfpCsfRdiFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetGfpCsfRdiFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_GFPCSFRDI_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_GFPCSFRDI_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_GfpConfig::GetGfpCsfRdiFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_GFPCSFRDI_BITMASK) == 0 ? false : true;
}

uint16 MON_GfpConfig::GetFailLayerBitMask() const
{
    return myDefectFailLayerBitMask;
}

ostream& MON_GfpConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);
    return theStream;
}

istream& MON_GfpConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);
    return theStream;
}

FC_Stream& MON_GfpConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myDefectFailLayerBitMask;
    return theStream;
}

FC_Stream& MON_GfpConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myDefectFailLayerBitMask;
    return theStream;
}

void MON_GfpConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "GFP     - LF Fail Layer                     = " << DISPLAY_BOOL(GetGfpLfFailLayer()) << endl;  
    theStream   << "GFP     - RF Fail Layer                     = " << DISPLAY_BOOL(GetGfpRfFailLayer()) << endl;  
    theStream   << "GFP     - FEFI Fail Layer                   = " << DISPLAY_BOOL(GetGfpFefiFailLayer()) << endl;  
    theStream   << "GFP     - CSF FEFI Fail Layer               = " << DISPLAY_BOOL(GetGfpCsfFefiFailLayer()) << endl;  
    theStream   << "GFP     - LINK FAIL RX Fail Layer           = " << DISPLAY_BOOL(GetGfpLinkFailRxFailLayer()) << endl;  
    theStream   << "GFP     - CSF LOS Fail Layer                = " << DISPLAY_BOOL(GetGfpCsfLosFailLayer()) << endl;     
    theStream   << "GFP     - LOFD Fail Layer                   = " << DISPLAY_BOOL(GetGfpLofdFailLayer()) << endl;  
    theStream   << "GFP     - PLM Fail Layer                    = " << DISPLAY_BOOL(GetGfpPlmFailLayer()) << endl;    
    theStream   << "GFP     - CSF LOSSYNC Fail Layer            = " << DISPLAY_BOOL(GetGfpCsfLosyncFailLayer()) << endl;  
    theStream   << "GFP     - CSF FDI Fail Layer                = " << DISPLAY_BOOL(GetGfpCsfFdiFailLayer()) << endl;  
    theStream   << "GFP     - CSF RDI Fail Layer                = " << DISPLAY_BOOL(GetGfpCsfRdiFailLayer()) << endl; 
}

FC_CmdProcessor::STATUS MON_GfpConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto GFPERROR;

    if (!strcmp(argv[0],"gfplffaillayer"))
    {
        SetGfpLfFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"rffaillayer"))
    {
        SetGfpRfFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"fefifaillayer"))
    {
        SetGfpFefiFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"csffefifaillayer"))
    {
        SetGfpCsfFefiFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"linkfailrxfaillayer"))
    {
        SetGfpLinkFailRxFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"csflosfaillayer"))
    {
        SetGfpCsfLosFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"lofdfaillayer"))
    {
        SetGfpLofdFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"plmfaillayer"))
    {
        SetGfpPlmFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"csflosyncfailrxfaillayer"))
    {
        SetGfpCsfLosyncFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"csffdifaillayer"))
    {
        SetGfpCsfFdiFailLayer(argv[1][0]=='e');
    }
    else if (!strcmp(argv[0],"csfrdifaillayer"))
    {
        SetGfpCsfRdiFailLayer(argv[1][0]=='e');
    }
    else
    {
        goto GFPERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

GFPERROR:
    {
        fc_cout << "gfp gfplffaillayer           <e-nable|d-isable> " << endl;
        fc_cout << "gfp rffaillayer              <e-nable|d-isable> " << endl;
        fc_cout << "gfp fefifaillayer            <e-nable|d-isable> " << endl;
        fc_cout << "gfp csffefifaillayer         <e-nable|d-isable> " << endl;
        fc_cout << "gfp linkfailrxfaillayer      <e-nable|d-isable> " << endl;
        fc_cout << "gfp csflosfaillayer          <e-nable|d-isable> " << endl;
        fc_cout << "gfp lofdfaillayer            <e-nable|d-isable> " << endl;
        fc_cout << "gfp plmfaillayer             <e-nable|d-isable> " << endl;
        fc_cout << "gfp csflosyncfailrxfaillayer <e-nable|d-isable> " << endl;
        fc_cout << "gfp csffdifaillayer          <e-nable|d-isable> " << endl;
        fc_cout << "gfp csfrdifaillayer          <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}

