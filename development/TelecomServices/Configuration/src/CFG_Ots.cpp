//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_Ots.h"
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>

CFG_Ots::CFG_Ots(uint32 theIndex):
    CFG_Object(theIndex),
    myCatpsEnable(false),
    myChOutputPwrTarget(TRAFFIC_CFG_DEFAULT_VALUE), // 0dBm
    myChInputPwrTarget(TRAFFIC_CFG_DEFAULT_VALUE), // 0dBm
    myMaximumGain(1800), // 18dB
    myMinimumChOutputPwr(TRAFFIC_CFG_DEFAULT_VALUE), // -6dBm
    myTxTrace()
{
}

CFG_Ots::~CFG_Ots(void)
{
}

void CFG_Ots::Reset(void)
{
    myCatpsEnable = false;
    myChOutputPwrTarget = TRAFFIC_CFG_DEFAULT_VALUE; // 0dBm
    myChInputPwrTarget = TRAFFIC_CFG_DEFAULT_VALUE; // 0dBm
    myMaximumGain = 1800; // 1dBm
    myMinimumChOutputPwr = TRAFFIC_CFG_DEFAULT_VALUE; // 0dBm
    myTxTrace = CT_G709Trace();
}

bool CFG_Ots::GetCatpsEnable() const
{
    return myCatpsEnable;
}

void CFG_Ots::SetCatpsEnable(bool theCatpsEnable)
{
    myCatpsEnable = theCatpsEnable;
}

const CT_G709Trace& CFG_Ots::GetTxTrace() const
{
    return myTxTrace;
}

void CFG_Ots::SetTxTrace(const CT_G709Trace& theTrace)
{
    myTxTrace = theTrace;
}

CT_TEL_mBm CFG_Ots::GetChannelOutputPowerTarget() const
{
    return myChOutputPwrTarget;
}

void CFG_Ots::SetChannelOutputPowerTarget(CT_TEL_mBm thePower)
{
    myChOutputPwrTarget = thePower;
}

CT_TEL_mBm CFG_Ots::GetChannelInputPowerTarget() const
{
    return myChInputPwrTarget;
}

void CFG_Ots::SetChannelInputPowerTarget(CT_TEL_mBm thePower)
{
    myChInputPwrTarget = thePower;
}

CT_TEL_mBm CFG_Ots::GetMaximumGain() const
{
    return myMaximumGain;
}

void CFG_Ots::SetMaximumGain(CT_TEL_mBm theGain)
{
    myMaximumGain = theGain;
}

CT_TEL_mBm CFG_Ots::GetMinimumChOutputPwr() const
{
    return myMinimumChOutputPwr;
}

void CFG_Ots::SetMinimumChOutputPwr(CT_TEL_mBm thePower)
{
    myMinimumChOutputPwr = thePower;
}


ostream& CFG_Ots::WriteObject( ostream& theStream )
{
    CFG_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myCatpsEnable);
    theStream << FC_InsertVar(myTxTrace);
    theStream << FC_InsertVar(myChOutputPwrTarget);
    theStream << FC_InsertVar(myChInputPwrTarget);
    theStream << FC_InsertVar(myMaximumGain);
    theStream << FC_InsertVar(myMinimumChOutputPwr);
    return theStream;
}


istream& CFG_Ots::ReadObject( istream& theStream )
{
    CFG_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myCatpsEnable);
    theStream >> FC_ExtractVar(myTxTrace);
    theStream >> FC_ExtractVar(myChOutputPwrTarget);
    theStream >> FC_ExtractVar(myChInputPwrTarget);
    theStream >> FC_ExtractVar(myMaximumGain);
    theStream >> FC_ExtractVar(myMinimumChOutputPwr);
    return theStream;
}


FC_Stream& CFG_Ots::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream << myCatpsEnable;
    theStream << myTxTrace;
    theStream << myChOutputPwrTarget;
    theStream << myChInputPwrTarget;
    theStream << myMaximumGain;
    theStream << myMinimumChOutputPwr;
    return theStream;
}


FC_Stream& CFG_Ots::ReadObjectBinary( FC_Stream& theStream )
{
    CFG_Object::ReadObjectBinary(theStream);
    theStream >> myCatpsEnable;
    theStream >> myTxTrace;
    theStream >> myChOutputPwrTarget;
    theStream >> myChInputPwrTarget;
    theStream >> myMaximumGain;
    theStream >> myMinimumChOutputPwr;
    return theStream;
}

FC_CmdProcessor::STATUS CFG_Ots::Set(int argc, char **argv)
{
    //We need 2 arguments
    if (argc < 2)
        goto OTSERROR;

    if (!strcmp(argv[0],"catps"))
    {
        SetCatpsEnable(argv[1][0]=='e');
    }
    else if(!strcmp(argv[0],"outpwr"))
    {
        CT_TEL_mBm aPower = (CT_TEL_mBm)(strtod(argv[1], NULL)*100.0f);
        SetChannelOutputPowerTarget(aPower);
    }
    else if(!strcmp(argv[0],"inpwr"))
    {
        CT_TEL_mBm aPower = (CT_TEL_mBm)(strtod(argv[1], NULL)*100.0f);
        SetChannelInputPowerTarget(aPower);
    }
    else if(!strcmp(argv[0],"maxgain"))
    {
        CT_TEL_mBm aPower = (CT_TEL_mBm)(strtod(argv[1], NULL)*100.0f);
        SetMaximumGain(aPower);
    }
    else if(!strcmp(argv[0],"minpwr"))
    {
        CT_TEL_mBm aPower = (CT_TEL_mBm)(strtod(argv[1], NULL)*100.0f);
        SetMinimumChOutputPwr(aPower);
    }
    else if(!strcmp(argv[0],"txtrace"))
    {
        if (argc != 2) goto OTSERROR;
        string aMessage(argv[1]);
        string aSapi("");
        string aDapi("");

        CT_G709Trace aTrace(aSapi,aDapi,aMessage);
        SetTxTrace(aTrace);
    }
    else
        goto OTSERROR;

    return FC_CmdProcessor::E_SUCCESS;

OTSERROR:
    {
        fc_cout << "ots <catps> <e-nable|d-isable>" << endl;
        fc_cout << "ots <outpwr> <power (mBm)>" << endl;
        fc_cout << "ots <inpwr>  <power (mBm)>" << endl;
        fc_cout << "ots <maxgain><gain  (mB)>" << endl;
        fc_cout << "ots <minpwr> <power (mBm)>" << endl;
        fc_cout << "ots <txtrace> <28-byte trace>" << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
    //return FC_CmdProcessor::E_FAILURE;
}

void CFG_Ots::Display( FC_Stream& theStream )
{
    theStream   << "OTS      - CATPS Enable     [catps]         = " << DISPLAY_BOOL(myCatpsEnable) << endl;
    theStream   << "OTS      - Ch. Output Pwr Target [mBm]      = " << DISPLAY_MBM(myChOutputPwrTarget) << endl;
    theStream   << "OTS      - Ch. Input  Pwr Target [mBm]      = " << DISPLAY_MBM(myChInputPwrTarget) << endl;
    theStream   << "OTS      - Main Amp gain         [mB ]      = " << DISPLAY_MBM(myMaximumGain) << endl;
    theStream   << "OTS      - Min. Ch. Input  Pwr   [mBm]      = " << DISPLAY_MBM(myMinimumChOutputPwr) << endl;
    theStream   << "OTS      - Tx Trace         [txtrace]       = ";
    myTxTrace.Display(theStream);
}
