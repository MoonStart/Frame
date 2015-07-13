//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_MsConfig.h"
#include "BaseClass/FC_TextStream.h"
#include <string.h>

MON_MsConfig::MON_MsConfig(uint32 theIndex):
    MON_Config(theIndex),
    mySdBerLevel(CT_TEL_INFINITE_BER),
    mySfBerLevel(CT_TEL_INFINITE_BER),
    myDefectFailLayerBitMask(MON_FAILLAYER_MS_DEFAULT_BITMASK)
{
}

MON_MsConfig::~MON_MsConfig()
{
}

void MON_MsConfig::Reset(void)
{
    MON_Config::Reset();
    mySdBerLevel = CT_TEL_INFINITE_BER;
    mySfBerLevel = CT_TEL_INFINITE_BER;
    myDefectFailLayerBitMask = MON_FAILLAYER_MS_DEFAULT_BITMASK;
}

bool MON_MsConfig::SetBerSdThreshold(CT_TEL_BERLevels theSdBerThreshold)
{
    bool hasChanged = (mySdBerLevel != theSdBerThreshold);
    mySdBerLevel = theSdBerThreshold;
    return hasChanged;
}

CT_TEL_BERLevels MON_MsConfig::GetBerSdThreshold() const
{
    return mySdBerLevel;
}

bool MON_MsConfig::SetBerSfThreshold(CT_TEL_BERLevels theSfBerThreshold)
{

    bool hasChanged = (mySfBerLevel != theSfBerThreshold);
    mySfBerLevel = theSfBerThreshold;
    return hasChanged;
}

CT_TEL_BERLevels MON_MsConfig::GetBerSfThreshold() const
{
    return mySfBerLevel;
}

bool MON_MsConfig::SetAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetAisFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_MSAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_MSAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_MsConfig::GetAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_MSAIS_BITMASK) == 0 ? false : true;
}

bool MON_MsConfig::SetInternalAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetInternalAisFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_MSINTAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_MSINTAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_MsConfig::GetInternalAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_MSINTAIS_BITMASK) == 0 ? false : true;
}

bool MON_MsConfig::SetPropAisFailLayer(bool theState)
{
    bool hasChanged = false;
    if (GetPropAisFailLayer() != theState)
    {
        if (theState)
        {
            myDefectFailLayerBitMask |= MON_FAILLAYER_MSPROPAIS_BITMASK;
        }
        else
        {
            myDefectFailLayerBitMask &= (~MON_FAILLAYER_MSPROPAIS_BITMASK);
        }
        hasChanged = true;
    }
    return hasChanged;
}

bool MON_MsConfig::GetPropAisFailLayer() const
{
    return (myDefectFailLayerBitMask & MON_FAILLAYER_MSPROPAIS_BITMASK) == 0 ? false : true;
}

uint16 MON_MsConfig::GetFailLayerBitMask() const
{
    return myDefectFailLayerBitMask;
}

ostream& MON_MsConfig::WriteObject(ostream& theStream)
{
    MON_Config::WriteObject(theStream);
    uint32 aSdBerLevel = (uint32) mySdBerLevel;
    uint32 aSfBerLevel = (uint32) mySfBerLevel;
    theStream << FC_InsertVar(aSdBerLevel);
    theStream << FC_InsertVar(aSfBerLevel);
    theStream << FC_InsertVar(myDefectFailLayerBitMask);
    return theStream;
}

istream& MON_MsConfig::ReadObject(istream& theStream)
{
    MON_Config::ReadObject(theStream);
    uint32 aSdBerLevel;
    uint32 aSfBerLevel;
    theStream >> FC_ExtractVar(aSdBerLevel);
    theStream >> FC_ExtractVar(aSfBerLevel);
    mySdBerLevel = (CT_TEL_BERLevels) aSdBerLevel;
    mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    theStream >> FC_ExtractVar(myDefectFailLayerBitMask);
    return theStream;
}

FC_Stream& MON_MsConfig::WriteObjectBinary(FC_Stream& theStream)
{
    MON_Config::WriteObjectBinary(theStream);
    uint32 aSdBerLevel = (uint32) mySdBerLevel;
    uint32 aSfBerLevel = (uint32) mySfBerLevel;
    theStream << aSdBerLevel;
    theStream << aSfBerLevel;
    theStream << myDefectFailLayerBitMask;
    return theStream;
}

FC_Stream& MON_MsConfig::ReadObjectBinary(FC_Stream& theStream)
{
    MON_Config::ReadObjectBinary(theStream);
    uint32 aSdBerLevel;
    uint32 aSfBerLevel;
    theStream >> aSdBerLevel;
    theStream >> aSfBerLevel;
    mySdBerLevel = (CT_TEL_BERLevels) aSdBerLevel;
    mySfBerLevel = (CT_TEL_BERLevels) aSfBerLevel;
    theStream >> myDefectFailLayerBitMask;
    return theStream;
}

void MON_MsConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream   << "MS      - SD BER Threshold      [sdber]     = " << DISPLAY_BER(mySdBerLevel) << endl;
    theStream   << "MS      - SF BER Threshold      [sfber]     = " << DISPLAY_BER(mySfBerLevel) << endl;
    theStream   << "MS      - AIS Fail Layer                    = " << DISPLAY_BOOL(GetAisFailLayer()) << endl;   
    theStream   << "MS      - INTERNAL AIS Fail Layer           = " << DISPLAY_BOOL(GetInternalAisFailLayer()) << endl;   
    theStream   << "MS      - PROPRITARY AIS Fail Layer         = " << DISPLAY_BOOL(GetPropAisFailLayer()) << endl;   
}

FC_CmdProcessor::STATUS MON_MsConfig::Set(int argc, char** argv)
{
    if (argc < 2)
        goto MSERROR;

    if (!strcmp(argv[0],"sdber"))
    {
        SetBerSdThreshold(MON_STRING_TO_BER(argv[1]));
    }
    else if (!strcmp(argv[0],"sfber"))
    {
        SetBerSfThreshold(MON_STRING_TO_BER(argv[1]));
    }
    else if (!strcmp(argv[0],"aisfaillayer"))
    {
        SetAisFailLayer(argv[1][0]=='e');
    }  
    else if (!strcmp(argv[0],"internalaisfaillayer"))
    {
        SetInternalAisFailLayer(argv[1][0]=='e');
    }    
    else if (!strcmp(argv[0],"propaisfaillayer"))
    {
        SetPropAisFailLayer(argv[1][0]=='e');
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "ms <sdber> <Numeric value range 3 .. 12 inclusive> " << endl;
        fc_cout << "ms <sfber> <Numeric value range 3 .. 12 inclusive> " << endl;
        fc_cout << "ms aisfaillayer             <e-nable|d-isable> " << endl;
        fc_cout << "ms internalaisfaillayer     <e-nable|d-isable> " << endl;
        fc_cout << "ms propaisfaillayer         <e-nable|d-isable> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_SUCCESS;
}
