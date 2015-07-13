//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef SP_TIMINGRSIF_H
#define SP_TIMINGRSIF_H

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SignalProtection.h>
#include <SignalProtection/SP_Definitions.h>

class SP_TimingRSConfigRegion;


//This class defines an abstract interface
//for timing redundancy related operations
//Any module that supports timing redundancy is
//expected to provide a concrete implemenatation of this
//interface
class SP_TimingRSIF
{
public:
    virtual void SetClockMode(CT_TEL_ClkMode newClkMode) = 0;
	virtual void AcquireTimingMastership() = 0;
	virtual void ReleaseTimingMastership() = 0;
	virtual bool IsMaster() = 0;
	virtual bool IsMateMaster() = 0;
	virtual bool IsMatePresent() = 0;
    virtual bool IsMateReady() = 0;
	virtual void SetHwAutoSwitchMode(bool theEnableAutoSwitch) = 0;
    virtual bool IsSwitchRequired() = 0;
    virtual bool IsConfiguredMaster() =0;
    virtual bool IsConfiguredSlave() = 0;
    virtual bool IsConfiguredAuto() =0;
    virtual bool HasConfigurationChanged() =0;
    virtual CT_TEL_ClkMode GetMateClockMode() =0;
    virtual void SendLocalClockMode(CT_TEL_ClkMode newClkMode) = 0;
    virtual bool SwitchOnTimeoutAllowed() =0;
    virtual void EvaluateTimingReferences() =0;
    virtual CT_TEL_ClkMode GetLocalClockMode() =0;
    virtual void SendTRSMessage(SP_TimingMode theMessage)=0;
    virtual void RetrieveSelectedTxSsm()=0;
};


//This class provides a base implementation for the above
//SP_TimingRSIF interface
class SP_TimingRSDefaultImp: public SP_TimingRSIF
{
public:
	// Default class constructor
    SP_TimingRSDefaultImp(SP_TimingRSConfigRegion* theTimingRsConfigRegion);
	
    // Virtual class destructor
    virtual ~SP_TimingRSDefaultImp();

    virtual void SetClockMode(CT_TEL_ClkMode newClkMode);
	virtual void AcquireTimingMastership();
	virtual void ReleaseTimingMastership();
	virtual bool IsMaster();
	virtual bool IsMateMaster();
	virtual bool IsMatePresent();
    virtual bool IsMateReady();
	virtual void SetHwAutoSwitchMode(bool theEnableAutoSwitch);
    virtual bool IsSwitchRequired();
    virtual bool IsConfiguredMaster();
    virtual bool IsConfiguredSlave();
    virtual bool IsConfiguredAuto();
    virtual bool HasConfigurationChanged();
    virtual CT_TEL_ClkMode GetMateClockMode();
    virtual void SendLocalClockMode(CT_TEL_ClkMode newClkMode);
    virtual bool SwitchOnTimeoutAllowed();
    virtual void EvaluateTimingReferences();
    virtual CT_TEL_ClkMode GetLocalClockMode();
    virtual void SendTRSMessage(SP_TimingMode theMessage);
    virtual void RetrieveSelectedTxSsm();

private:
    SP_TimingRSConfigRegion* myTimingRsConfigRegion;
    CT_SP_RSMode myPrevRsMode;
};

#endif /* SP_TIMINGRSIF_H */
