//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_BwPf.h"
#include "../CFG_Definitions.h"
#include <CommonTypes/CT_Telecom.h>
#include <ErrorService/FC_Error.h>
#include <string.h>
#include <BaseClass/FC_TextStream.h>


CFG_Bwpf::CFG_Bwpf(uint32 theIndex):
    CFG_Object(theIndex),
    myComitInfoRate(0),
    myComitBrstSz(0),
    myExcessBrstSz(0),
    myExcessInfoRate(0),
    myColorMode(CT_TEL_BW_CM_UNKNOWN),
    myMeterType(CT_TEL_BW_METERTYPE_UNKNOWN)
{
}

CFG_Bwpf::~CFG_Bwpf(void)
{
}

void CFG_Bwpf::SetComitInfoRate(uint32 theComitInfoRate)
{
    myComitInfoRate = theComitInfoRate;
}

uint32 CFG_Bwpf::GetComitInfoRate() const
{
    return myComitInfoRate;
}

void CFG_Bwpf::SetComitBrstSz(uint32 theComitBrstSz)
{
    myComitBrstSz = theComitBrstSz;
}

uint32 CFG_Bwpf::GetComitBrstSz() const
{
    return myComitBrstSz;
}

void CFG_Bwpf::SetExcessInfoRate(uint32 theExcessInfoRate)
{
    myExcessInfoRate = theExcessInfoRate;
}

uint32 CFG_Bwpf::GetExcessInfoRate() const
{
    return myExcessInfoRate;
}

void CFG_Bwpf::SetExcessBrstSz(uint32 theExcessBrstSz)
{
    myExcessBrstSz = theExcessBrstSz;
}

uint32 CFG_Bwpf::GetExcessBrstSz() const
{
    return myExcessBrstSz;
}

void CFG_Bwpf::SetColorMode(CT_TEL_BW_CM theColorMode)
{
    myColorMode = theColorMode;
}

CT_TEL_BW_CM CFG_Bwpf::GetColorMode() const
{
    return myColorMode;
}

void CFG_Bwpf::SetMeterType(CT_TEL_BW_METERTYPE theMeterType)
{
    myMeterType= theMeterType;
}

CT_TEL_BW_METERTYPE CFG_Bwpf::GetMeterType() const
{
    return myMeterType;
}

void CFG_Bwpf::Reset(void)
{
    // Initialize all attributes to default values.
    myComitInfoRate = 0;
    myComitBrstSz = 0;
    myExcessBrstSz = 0;
    myExcessInfoRate = 0;
    myColorMode = CT_TEL_BW_CM_UNKNOWN;
    myMeterType = CT_TEL_BW_METERTYPE_UNKNOWN;
}

ostream& CFG_Bwpf::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream   << FC_InsertVar(myComitInfoRate);
    theStream   << FC_InsertVar(myComitBrstSz);
    theStream   << FC_InsertVar(myExcessBrstSz);
    theStream   << FC_InsertVar(myExcessInfoRate);

    uint8 aColorMode = myColorMode;
    theStream   << FC_InsertVar(aColorMode);
    uint8 aMeterType = myMeterType;
    theStream   << FC_InsertVar(aMeterType);

    return theStream;
}

istream& CFG_Bwpf::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);

    theStream   >> FC_ExtractVar(myComitInfoRate);
    theStream   >> FC_ExtractVar(myComitBrstSz);
    theStream   >> FC_ExtractVar(myExcessBrstSz);
    theStream   >> FC_ExtractVar(myExcessInfoRate);

    uint8 aColorMode = 0;
    theStream   >> FC_ExtractVar(aColorMode);
    myColorMode = (CT_TEL_BW_CM) aColorMode;
    uint8 aMeterType = 0;
    theStream   >> FC_ExtractVar(aMeterType);
    myMeterType = (CT_TEL_BW_METERTYPE) aMeterType;

    return theStream;
}

FC_Stream& CFG_Bwpf::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   <<  myComitInfoRate;
    theStream   <<  myComitBrstSz;
    theStream   <<  myExcessBrstSz;
    theStream   <<  myExcessInfoRate;
    theStream   <<  (uint8)myColorMode;
    theStream   <<  (uint8)myMeterType;

    return theStream;
}

FC_Stream& CFG_Bwpf::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);

    theStream   >>  myComitInfoRate;
    theStream   >>  myComitBrstSz;
    theStream   >>  myExcessBrstSz;
    theStream   >>  myExcessInfoRate;

    uint8  aColorMode = 0;
    theStream   >> aColorMode;
    myColorMode = (CT_TEL_BW_CM) aColorMode;
    uint8  aMeterType = 0;
    theStream   >> aMeterType;
    myMeterType = (CT_TEL_BW_METERTYPE) aMeterType;

    return theStream;
}

FC_CmdProcessor::STATUS CFG_Bwpf::Set(int argc, char **argv)
{
    char aParam[32];

    //We need 2 arguments
    if (argc < 2)
        goto MSERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);

    if (!strncmp(aParam,"cir",3))
    {
        SetComitInfoRate(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"cbs",3))
    {
        SetComitBrstSz(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"eir",3))
    {
        SetExcessInfoRate(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"ebs",3))
    {
        SetExcessBrstSz(static_cast<uint32>(strtoul(argv[1], NULL, 0)));
    }
    else if (!strncmp(aParam,"cm",2))
    {
        SetColorMode(CFG_STRING_TO_COLOR_MD(argv[1]));
    }
    else if (!strncmp(aParam,"mt",2))
    {
        SetMeterType(CFG_STRING_TO_METER_TYPE(argv[1]));
    }
    else
    {
        goto MSERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

MSERROR:
    {
        fc_cout << "BWPF <cir>    <int32> " << endl;
        fc_cout << "BWPF <cbs>    <int32> " << endl;
        fc_cout << "BWPF <eir>    <int32> " << endl;
        fc_cout << "BWPF <ebs>    <int32> " << endl;
        fc_cout << "BWPF <cm>     <blind|aware> " << endl;
        fc_cout << "BWPF <mt>     <srTCM|trTCM> " << endl;

        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_SUCCESS;
}

void CFG_Bwpf::Display( FC_Stream& theStream )
{
    theStream   << "BWPF - Committed Information Rate [cir]   = " << (uint32)myComitInfoRate << endl;
    theStream   << "BWPF - Committed Burst Size       [cbs]   = " << (uint32)myComitBrstSz << endl;
    theStream   << "BWPF - Excess Information Rate    [eir]   = " << (uint32)myExcessInfoRate << endl;
    theStream   << "BWPF - Excess Burst Size          [ebs]   = " << (uint32)myExcessBrstSz << endl;
    theStream   << "BWPF - Color Mode                 [cm]    = " << DISPLAY_BW_COLOR_MODE(myColorMode) << endl;
    theStream   << "BWPF - Meter Type                 [mt]    = " << DISPLAY_BW_METER_TYPE(myMeterType) << endl;
}

