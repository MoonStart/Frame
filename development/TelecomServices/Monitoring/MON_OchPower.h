//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OCHPOWER_H
#define MON_OCHPOWER_H

#include "MON_Object.h"
#include <CommonTypes/CT_Telecom.h>
#include <TelCommon/TEL_BbObjectBase.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>

class MON_OchPower
: public TEL_BbObjectBase
{

public:

	//Constructor.
    MON_OchPower();
    MON_OchPower(const MON_OchPower& thePower);
    MON_OchPower(MON_RelativeTraceId theTraceId, 
                 CT_TEL_mBm theAmplitude=TRAFFIC_DEFAULT_POWER, 
                 CT_TEL_mBm theSnr=TRAFFIC_DEFAULT_POWER,
                 bool theSnrValid = true);

	//Virtual destructor.
    virtual ~MON_OchPower(void);
 
    CT_TEL_mBm GetAmplitude() const; 
    CT_TEL_mBm GetSnr() const;
    CT_TEL_mBm GetRealSnr() const;
    MON_RelativeTraceId GetTraceId() const;

    void Display(FC_Stream& theStream);
    void Boost(CT_TEL_mBm theBoost);

    bool operator==(const MON_OchPower& theOchPower) const;
    bool operator<(const MON_OchPower& theOchPower) const;
    void operator=(const MON_OchPower& theOchPower);

    static CT_TEL_PilotToneID GetTraceId(const CT_Wavelength& theWavelength, MON_RelativeTraceId theRelativeId);
    static CT_Wavelength GetChannelId(CT_TEL_PilotToneID theTraceId);
    static MON_RelativeTraceId GetRelativeTraceId(CT_TEL_PilotToneID theTraceId);
    static CT_TEL_Hz ConvertChannelToCenterFrequency(const CT_Wavelength& theChannelId);
    static CT_TEL_Hz GetFrequencyOffset(MON_RelativeTraceId theRelId);
    static CT_TEL_Hz GetFrequency(CT_TEL_PilotToneID theTraceId);

protected:
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    CT_TEL_mBm myAmplitude;
    CT_TEL_mBm mySnr;
    bool mySnrValid;
    MON_RelativeTraceId myTraceId;
	bool myNeSupportsPilotTone;
	CT_TEL_mBm myDefMinSnr;
};

#endif /* MON_OCHPOWER_H */
