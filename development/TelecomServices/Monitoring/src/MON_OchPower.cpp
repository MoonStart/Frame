// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OchPower.h"
#include "../MON_SubNodeParameters.h"
#include <BaseClass/FC_TextStream.h>
#include <CsPii/CSPII_CardIF.h>
#include <ErrorService/FC_Error.h>
#include <Configuration/CFG_PilotToneAssignment.h>

MON_OchPower::MON_OchPower():
    myAmplitude(TRAFFIC_DEFAULT_POWER),
    mySnr(TRAFFIC_DEFAULT_POWER),
    myTraceId(MON_ID_UNKNOWN),
    mySnrValid(true)
{
}

MON_OchPower::MON_OchPower(MON_RelativeTraceId theTraceId, CT_TEL_mBm theAmplitude, CT_TEL_mBm theSnr, bool theSnrValid):
    myAmplitude(theAmplitude),
    mySnr(theSnr),
    myTraceId(theTraceId),
    mySnrValid(theSnrValid)
{
}

MON_OchPower::MON_OchPower(const MON_OchPower& thePower):
    myAmplitude(thePower.myAmplitude),
    mySnr(thePower.mySnr),
    myTraceId(thePower.myTraceId),
    mySnrValid(thePower.mySnrValid)
{
}


void MON_OchPower::operator=(const MON_OchPower& theOchPower)
{
    myAmplitude = theOchPower.myAmplitude;
    mySnr       = theOchPower.mySnr;
    myTraceId   = theOchPower.myTraceId;
    mySnrValid  = theOchPower.mySnrValid;
}

bool MON_OchPower::operator==(const MON_OchPower& theOchPower) const
{
    return ((myAmplitude == theOchPower.myAmplitude) &&
            (mySnr == theOchPower.mySnr) &&
            (myTraceId == theOchPower.myTraceId) &&
            (mySnrValid == theOchPower.mySnrValid));
}

bool MON_OchPower::operator<(const MON_OchPower& theOchPower) const
{
    CT_TEL_mBm subNodeSNR = MON_SubNodeParameters::GetInstance().GetMinimumSNRatio();

    // if both are under minimum SNR, return compare amplitude
    if ((mySnr < subNodeSNR) &&
       (theOchPower.mySnr < subNodeSNR))
       return (myAmplitude < theOchPower.myAmplitude);

    // if both are over minimum SNR, return compare amplitude
    else if ((mySnr >= subNodeSNR) &&
       (theOchPower.mySnr >= subNodeSNR))
       return (myAmplitude < theOchPower.myAmplitude);

    // one of them is under minimum snr
    else return (mySnr < theOchPower.mySnr);
}

MON_OchPower::~MON_OchPower(void )
{
}


CT_TEL_mBm MON_OchPower::GetAmplitude() const
{
    return myAmplitude;
}

CT_TEL_mBm MON_OchPower::GetSnr() const
{
    return mySnr;
}

CT_TEL_mBm MON_OchPower::GetRealSnr() const
{
    if (mySnrValid)
    {
        return mySnr;
    }
    else
    {
        return TRAFFIC_DEFAULT_POWER;
    }
}

MON_RelativeTraceId MON_OchPower::GetTraceId() const
{
    return myTraceId;
}

ostream& MON_OchPower::WriteObject(ostream& theStream)
{
    uint32 aTraceId = myTraceId;
    theStream << FC_InsertVar(aTraceId);
    theStream << FC_InsertVar(myAmplitude);
    theStream << FC_InsertVar(mySnr);
    theStream << FC_InsertVar(mySnrValid);
    return theStream;
}

istream& MON_OchPower::ReadObject(istream& theStream)
{
    uint32 aTraceId;
    theStream >> FC_ExtractVar(aTraceId);
    myTraceId = (MON_RelativeTraceId)aTraceId;
    theStream >> FC_ExtractVar(myAmplitude);
    theStream >> FC_ExtractVar(mySnr);
    theStream >> FC_ExtractVar(mySnrValid);
    return theStream;
}

FC_Stream& MON_OchPower::WriteObjectBinary(FC_Stream& theStream)
{
    theStream << myTraceId;
    theStream << myAmplitude;
    theStream << mySnr;
    theStream << mySnrValid;
    return theStream;
}

FC_Stream& MON_OchPower::ReadObjectBinary(FC_Stream& theStream)
{
    uint32 aTraceId;
    theStream >> aTraceId;
    myTraceId = (MON_RelativeTraceId)aTraceId;
    theStream >> myAmplitude;
    theStream >> mySnr;
    theStream >> mySnrValid;
    return theStream;
}


void MON_OchPower::Display(FC_Stream& theStream)
{
    theStream.GetOutputStream()  << "Trace ID " << DISPLAY_REL_TRACE_ID(myTraceId) << endl;
    theStream.GetOutputStream()  << "PT Amplitude       (dBm) = " << DISPLAY_MBM(myAmplitude) << endl;
    theStream.GetOutputStream()  << "PT SNR             (dB ) = " << DISPLAY_MBM(mySnr) << endl;
    theStream.GetOutputStream()  << "VALID SNR         (bool) = " << DISPLAY_BOOL(mySnrValid) << endl;
}

CT_TEL_PilotToneID MON_OchPower::GetTraceId(const CT_Wavelength& theWavelength, MON_RelativeTraceId theRelativeId)
{
    return (CFG_PilotToneAssignment::GetInstance().CH_ID_TO_OTID(theWavelength.WavelengthIndex(), theRelativeId));
}

CT_Wavelength MON_OchPower::GetChannelId(CT_TEL_PilotToneID theTraceId)
{
    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();

    if ((theTraceId==0) ||
        ((uint32)(theTraceId-1) > MON_NUMBER_OF_ID_PER_LAMBDA*omsWavelengthCapacity))
        return UNKNOWN_WAVELENGHT;
    else
        return(CT_Wavelength(CFG_PilotToneAssignment::GetInstance().OTID_TO_CH_ID(theTraceId)));
}

MON_RelativeTraceId MON_OchPower::GetRelativeTraceId(CT_TEL_PilotToneID theTraceId)
{
    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();

    if ((theTraceId==0) ||
        ((uint32)(theTraceId-1) > MON_NUMBER_OF_ID_PER_LAMBDA*omsWavelengthCapacity))
        return MON_ID_UNKNOWN;
    else
        return (MON_RelativeTraceId)((theTraceId-1)%MON_NUMBER_OF_ID_PER_LAMBDA);
}

CT_TEL_Hz MON_OchPower::ConvertChannelToCenterFrequency(const CT_Wavelength& theChannelId)
{
    uint32 omsWavelengthCapacity = MON_SubNodeParameters::GetInstance().GetOmsWavelengthCapacity();

    FC_THROW_ERROR_IF(theChannelId.WavelengthIndex() >= omsWavelengthCapacity,
        FC_InvalidArgumentError, "Wavelength out of range");
    return(CFG_PilotToneAssignment::GetInstance().CH_ID_TO_CENTER_FREQ(theChannelId.WavelengthIndex()));
}

CT_TEL_Hz MON_OchPower::GetFrequencyOffset(MON_RelativeTraceId theRelId)
{
    switch (theRelId)
    {
    case MON_ID_FIRST:
        return -250;
    case MON_ID_SECOND:
        return 0;
    case MON_ID_DEBUG:
        return 250;
    case MON_ID_NOISE:
        return 500;
    default:
        FC_THROW_ERROR(FC_InvalidArgumentError, "Cannot find a frequency offset for this ID");
        return 0;
    }
}

CT_TEL_Hz MON_OchPower::GetFrequency(CT_TEL_PilotToneID theTraceId)
{
    return  ConvertChannelToCenterFrequency(GetChannelId(theTraceId))
            + GetFrequencyOffset(GetRelativeTraceId(theTraceId));
}

void MON_OchPower::Boost(CT_TEL_mBm theBoost)
{
    myAmplitude += theBoost;
}

