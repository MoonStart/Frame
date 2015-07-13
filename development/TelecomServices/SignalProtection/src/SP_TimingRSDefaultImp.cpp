// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_TimingRSIF.h"
#include "../SP_TimingRSConfigRegion.h"


SP_TimingRSDefaultImp::SP_TimingRSDefaultImp(SP_TimingRSConfigRegion* theTimingRsConfigRegion):
myTimingRsConfigRegion(theTimingRsConfigRegion),
myPrevRsMode(CT_SP_RS_UNKNOWN)
{
}

SP_TimingRSDefaultImp::~SP_TimingRSDefaultImp()
{
}

void SP_TimingRSDefaultImp::SetClockMode(CT_TEL_ClkMode newClkMode)
{
}
void SP_TimingRSDefaultImp::AcquireTimingMastership()
{
}
void SP_TimingRSDefaultImp::ReleaseTimingMastership()
{
}
bool SP_TimingRSDefaultImp::IsMaster()
{
    if (IsConfiguredMaster() == true)
        return true;
    else
        return false;
}
bool SP_TimingRSDefaultImp::IsMateMaster()
{
    return false;
}
bool SP_TimingRSDefaultImp::IsMatePresent()
{
    return false;
}
void SP_TimingRSDefaultImp::SetHwAutoSwitchMode(bool theEnableAutoSwitch)
{
}

bool SP_TimingRSDefaultImp::IsSwitchRequired()
{
    return false;
}

bool SP_TimingRSDefaultImp::IsConfiguredMaster()
{    
    if (myTimingRsConfigRegion)
    {
        CT_SP_RSMode theRsMode =  (*myTimingRsConfigRegion)[0].GetRedundancyMode();
        if (theRsMode == CT_SP_RS_MASTER)
            return true;
    }

    return false;

}
bool SP_TimingRSDefaultImp::IsConfiguredSlave()
{
    if (myTimingRsConfigRegion)
    {
        CT_SP_RSMode theRsMode =  (*myTimingRsConfigRegion)[0].GetRedundancyMode();
        if (theRsMode == CT_SP_RS_SLAVE)
            return true;
    }

    return false;
}

bool SP_TimingRSDefaultImp::IsConfiguredAuto()
{
    if (myTimingRsConfigRegion)
    {
        CT_SP_RSMode theRsMode =  (*myTimingRsConfigRegion)[0].GetRedundancyMode();
        if (theRsMode == CT_SP_RS_AUTO)
            return true;
    }

    return false;
}

bool SP_TimingRSDefaultImp::HasConfigurationChanged()
{
    bool hasChanged = false;
    if (myTimingRsConfigRegion)
    {
        CT_SP_RSMode theNewRsMode =  (*myTimingRsConfigRegion)[0].GetRedundancyMode();
        if (myPrevRsMode != theNewRsMode)
        {
            myPrevRsMode = theNewRsMode;
            hasChanged = true;
        }
    }
    return hasChanged;
}

CT_TEL_ClkMode SP_TimingRSDefaultImp::GetMateClockMode()
{
    return CT_TEL_CLKMODE_UNKNOWN;
}

void SP_TimingRSDefaultImp::SendLocalClockMode(CT_TEL_ClkMode newClkMode)
{
}

bool SP_TimingRSDefaultImp::SwitchOnTimeoutAllowed()
{
    return true;
}

bool SP_TimingRSDefaultImp::IsMateReady()
{
    return true;
}

void SP_TimingRSDefaultImp::EvaluateTimingReferences()
{
}

CT_TEL_ClkMode SP_TimingRSDefaultImp::GetLocalClockMode()
{
    return CT_TEL_CLKMODE_UNKNOWN;
}

void SP_TimingRSDefaultImp::SendTRSMessage(SP_TimingMode theMessage)
{
}

void SP_TimingRSDefaultImp::RetrieveSelectedTxSsm()
{
    //Do nothing
}