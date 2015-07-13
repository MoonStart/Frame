// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchConfig.h"
#include "../MON_SubNodeParameters.h"
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CommonTypes/CT_Telecom.h>


MON_OchConfig::MON_OchConfig(uint32 theIndex):
    MON_Config(theIndex),
    myLossOfInputPowerThreshold(TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD),
    myMinimumSNRatio(TEL_DEFAULT_MINIMUM_SN_RATIO),
    myExpectedChannelId(UNKNOWN_WAVELENGHT),
    myInterferenceEnable(true)
{
}

MON_OchConfig::~MON_OchConfig()
{
}

void MON_OchConfig::Refresh()
{
    myLossOfInputPowerThreshold = MON_SubNodeParameters::GetInstance().GetLossOfInputPowerThreshold();
    myMinimumSNRatio            = MON_SubNodeParameters::GetInstance().GetMinimumSNRatio();
}

void MON_OchConfig::Reset()
{
    MON_Config::Reset();
    myLossOfInputPowerThreshold = TEL_DEFAULT_LOSS_OF_INPUT_POWER_THRESHOLD;
    myMinimumSNRatio = TEL_DEFAULT_MINIMUM_SN_RATIO;
    myExpectedChannelId = CT_Wavelength(UNKNOWN_WAVELENGHT);
    myInterferenceEnable = true;
}

void MON_OchConfig::SetLossOfInputPowerThreshold(CT_TEL_mBm thePowerThreshold)
{
    myLossOfInputPowerThreshold = thePowerThreshold;
    MON_SubNodeParameters::GetInstance().SetLossOfInputPowerThreshold(thePowerThreshold);
}

CT_TEL_mBm MON_OchConfig::GetLossOfInputPowerThreshold()
{
    CT_TEL_mBm aThreshold = MON_SubNodeParameters::GetInstance().GetLossOfInputPowerThreshold();
    if(myLossOfInputPowerThreshold != aThreshold)
        Refresh();

    return(myLossOfInputPowerThreshold);
}

void MON_OchConfig::SetMinimumSNRatio(CT_TEL_mBm theMinimumSNRatio)
{
    myMinimumSNRatio = theMinimumSNRatio;
    MON_SubNodeParameters::GetInstance().SetMinimumSNRatio(theMinimumSNRatio);
}

CT_TEL_mBm MON_OchConfig::GetMinimumSNRatio()
{
    CT_TEL_mBm aSnr = MON_SubNodeParameters::GetInstance().GetMinimumSNRatio();
    if(myMinimumSNRatio != aSnr)
        Refresh();

    return(myMinimumSNRatio);
}

void MON_OchConfig::SetExpectedChannelId(CT_Wavelength theExpectedChannelId)
{
    myExpectedChannelId = theExpectedChannelId;
}

CT_Wavelength MON_OchConfig::GetExpectedChannelId()
{
    return myExpectedChannelId;
}

void MON_OchConfig::SetInterferenceEnable(bool theInterferenceEnable)
{
    myInterferenceEnable = theInterferenceEnable;
}

bool MON_OchConfig::GetInterferenceEnable(void)
{
    return myInterferenceEnable;
}


FC_Stream& MON_OchConfig::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Config::WriteObjectBinary(theStream);
    theStream << myLossOfInputPowerThreshold;
    theStream << myMinimumSNRatio;
    theStream << myExpectedChannelId;
    theStream << myInterferenceEnable;
    return theStream;
}

FC_Stream& MON_OchConfig::ReadObjectBinary( FC_Stream& theStream )
{
    MON_Config::ReadObjectBinary(theStream);
    theStream >> myLossOfInputPowerThreshold;
    theStream >> myMinimumSNRatio;
    theStream >> myExpectedChannelId;
    theStream >> myInterferenceEnable;
    return theStream;
}

ostream& MON_OchConfig::WriteObject( ostream& theStream )
{
    uint8 aExpectedChannelId = myExpectedChannelId.WavelengthIndex();
    MON_Config::WriteObject(theStream);
    theStream   << FC_InsertVar(myLossOfInputPowerThreshold);
    theStream   << FC_InsertVar(myMinimumSNRatio);
    theStream   << FC_InsertLabelAndVar("myExpectedChannelId", aExpectedChannelId);
    theStream   << FC_InsertVar(myInterferenceEnable);
    return theStream;
}


istream& MON_OchConfig::ReadObject( istream& theStream )
{
    uint8 aExpectedChannelId;  // for conversion
    MON_Config::ReadObject(theStream);
    theStream   >> FC_ExtractVar(myLossOfInputPowerThreshold);
    theStream   >> FC_ExtractVar(myMinimumSNRatio);
    theStream   >> FC_ExtractVar(aExpectedChannelId);
    theStream   >> FC_ExtractVar(myInterferenceEnable);
    // Convert and store the expected channel
    CT_Wavelength bExpectedChannelId(aExpectedChannelId);
    myExpectedChannelId = bExpectedChannelId;
    return theStream;
}

void MON_OchConfig::Display( FC_Stream& theStream )
{
    MON_Config::Display(theStream);
    theStream.GetOutputStream()
                << endl
                << "OCH     - Expected Channel                  = " << (uint32) myExpectedChannelId.WavelengthIndex() << endl;
    theStream   << "OCH     - Loss Input Pwr Theshold (dB)      = " << DISPLAY_MBM(myLossOfInputPowerThreshold) << endl;
    theStream   << "OCH     - Minimum S/N Ratio (dB)            = " << DISPLAY_MBM(myMinimumSNRatio) << endl;
    theStream   << "OCH     - TRACE ID INTERFERENCE ENABLED     = " << DISPLAY_BOOL(myInterferenceEnable) << endl;
}

FC_CmdProcessor::STATUS MON_OchConfig::Set(int argc, char** argv)
{
    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();
    uint32 aChannelId = 0;
    bool aEnable = false;

    if (argc < 2)
        goto OCHERROR;


    if (!strcmp(argv[0],"pt"))
    {
        if (argc < 3) goto OCHERROR;

        aChannelId = atoi(argv[2]);
        aEnable = argv[1][0]=='e';

        if (aEnable && aChannelId < omsWavelengthCapacity)
            SetExpectedChannelId(CT_Wavelength((uint8)aChannelId));
        else
            SetExpectedChannelId(CT_Wavelength(UNKNOWN_WAVELENGHT));

    }
    else if (!strcmp(argv[0],"lossthresh"))
    {
        double power = atof(argv[1]);
        SetLossOfInputPowerThreshold((CT_TEL_mBm)(power * 100));
    }
    else if (!strcmp(argv[0],"minimumSN"))
    {
        double power = atof(argv[1]);
        SetMinimumSNRatio((CT_TEL_mBm)(power * 100));
    }
    else
        goto OCHERROR;


    return FC_CmdProcessor::E_SUCCESS;

OCHERROR:
    {
        fc_cout << "pt <monitor e-nable|d-isable> <channelID 0-" << omsWavelengthCapacity-1 << "> " << endl;
        fc_cout << "lossthresh <power (dBm)> " << endl;
        fc_cout << "minimumSN  <power (dBm)> " << endl;
        return FC_CmdProcessor::E_FAILURE;
    }
}


