// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../MON_OptStatus.h"
#include <BaseClass/FC_TextStream.h>
#include <math.h>
#include <ErrorService/FC_Error.h>


MON_OptStatus::MON_OptStatus(uint32 theIndex):
    MON_Status(theIndex),
	myTotalInputPower(TRAFFIC_DEFAULT_POWER),
	myTotalOutputPower(TRAFFIC_DEFAULT_POWER),
	myTotalPeerOutputPower(TRAFFIC_DEFAULT_POWER),
	myTotalPeerOmsOutputPower(TRAFFIC_DEFAULT_POWER),
	myTotalOmsOutputPower(TRAFFIC_DEFAULT_POWER),
    myLaneLowReceivedPower(TRAFFIC_DEFAULT_POWER),
    myLaneHighReceivedPower(TRAFFIC_DEFAULT_POWER),
    myLaneLowTransmittedPower(TRAFFIC_DEFAULT_POWER),
    myLaneHighTransmittedPower(TRAFFIC_DEFAULT_POWER),
    myDetectedClockRate(0),
    myPrbsRxMostSignifCount(0),
    myPrbsRxLeastSignifCount(0),
    myPrbsRxTimeInterval(0),
    myPrbsRxLosync(CT_TEL_PRBS_OUTSYNC),
    myPrbsRxFirstSyncLosyncCount(0),
    myPrbsRxFirstSync(false),
    mySignifPowerChange(false),
    mySignifOutputPowerChange(false),
    mySignifPeerOutputPowerChange(false),
    mySignifPeerOmsOutputPowerChange(false),
    mySignifOmsOutputPowerChange(false),
    myRxLoisLaneSignifPowerChange(false),
    myRxHighLaneSignifPowerChange(false),
    myTxLoisLaneSignifPowerChange(false),
    myTxHighLaneSignifPowerChange(false),
    myRxLaneSignifPowerChange(false),
    myTxLaneSignifPowerChange(false),
    myIsDualOcmPresent(true),
    myActualGain(0),
    myChromaticDispersion(0),
    myDifferentialGroupDelay(0),
    my2ndOrderPolarModeDispersion(0),
    myStateOfPolarization(0),
    myPolarDependentLoss(TRAFFIC_DEFAULT_POWER),
    myQvalue(TRAFFIC_DEFAULT_POWER),
    myCarrierFrequencyOffset(TRAFFIC_DEFAULT_POWER),
    mySignalNoiseRatio(TRAFFIC_DEFAULT_POWER)
{
}

MON_OptStatus::~MON_OptStatus(void )
{
}

void MON_OptStatus::Reset()
{
    MON_Object::Reset();
    myTotalInputPower         = TRAFFIC_DEFAULT_POWER;
    myTotalOutputPower        = TRAFFIC_DEFAULT_POWER;
    myTotalPeerOutputPower    = TRAFFIC_DEFAULT_POWER;
    myTotalPeerOmsOutputPower = TRAFFIC_DEFAULT_POWER;
    myTotalOmsOutputPower     = TRAFFIC_DEFAULT_POWER;
    myLaneLowReceivedPower    = TRAFFIC_DEFAULT_POWER;
    myLaneHighReceivedPower   = TRAFFIC_DEFAULT_POWER;
    myLaneLowTransmittedPower = TRAFFIC_DEFAULT_POWER;
    myLaneHighTransmittedPower= TRAFFIC_DEFAULT_POWER;
    myDetectedClockRate       = 0;
    mySignifPowerChange           = false;
    mySignifOutputPowerChange     = false;
    mySignifPeerOutputPowerChange = false;
    mySignifPeerOmsOutputPowerChange = false;
    mySignifOmsOutputPowerChange  = false;
    myRxLoisLaneSignifPowerChange = false;
    myRxHighLaneSignifPowerChange = false;
    myRxLoisLaneSignifPowerChange = false;
    myRxHighLaneSignifPowerChange = false;
    myPrbsRxMostSignifCount  = 0;
    myPrbsRxLeastSignifCount = 0;
    myPrbsRxTimeInterval     = 0;
    myPrbsRxLosync           = CT_TEL_PRBS_OUTSYNC;
    myPrbsRxFirstSyncLosyncCount = 0;
    myPrbsRxFirstSync        = false;
    myIsDualOcmPresent       = true;
    myActualGain             = 0;
    myChromaticDispersion    = 0;
    myDifferentialGroupDelay = 0;
    my2ndOrderPolarModeDispersion = 0;
    myStateOfPolarization    = 0;
    myPolarDependentLoss     = TRAFFIC_DEFAULT_POWER;
    myQvalue                 = TRAFFIC_DEFAULT_POWER;
    myCarrierFrequencyOffset = TRAFFIC_DEFAULT_POWER;
    mySignalNoiseRatio       = TRAFFIC_DEFAULT_POWER;
}


void MON_OptStatus::GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const
{
    switch (theStatus)
    {
    case CT_TEL_OPT_INPUT_POWER_STATUS:
        *theLevel = GetTotalInputPower();
        break;
    case CT_TEL_OPT_OUTPUT_POWER_STATUS:
        *theLevel = GetTotalOutputPower();
        break;
    case CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS:
        *theLevel = GetDetectedClockRate();
        break;
    case CT_TEL_OPT_PEER_OUTPUT_POWER_STATUS:
        *theLevel = GetTotalPeerOutputPower();
        break;
    case CT_TEL_OPT_PEER_OMS_OUTPUT_POWER_STATUS:
        *theLevel = GetTotalPeerOmsOutputPower();
        break;
    case CT_TEL_OPT_OMS_OUTPUT_POWER_STATUS:
        *theLevel = GetTotalOmsOutputPower();
        break;
    case CT_TEL_OPT_ACTUAL_GAIN_STATUS:
        *theLevel = GetActualGain();
        break;
    case CT_TEL_OPT_RX_LANE_LOW_POWER_STATUS:
        *theLevel = GetLaneLowReceivedPower();
        break;
    case CT_TEL_OPT_RX_LANE_HIGH_POWER_STATUS:
        *theLevel = GetLaneHighReceivedPower();
        break;
    case CT_TEL_OPT_TX_LANE_LOW_POWER_STATUS:
        *theLevel = GetLaneLowTransmittedPower();
        break;
    case CT_TEL_OPT_TX_LANE_HIGH_POWER_STATUS:
        *theLevel = GetLaneHighTransmittedPower();
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OptStatus: unsupported status");
    }
}

bool MON_OptStatus::SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel)
{
    //Return true if changed
    bool hasChanged = false;

    switch (theStatus)
    {
    case CT_TEL_OPT_INPUT_POWER_STATUS:
        hasChanged = SetTotalInputPower(theLevel);
        break;
    case CT_TEL_OPT_OUTPUT_POWER_STATUS:
        hasChanged = SetTotalOutputPower(theLevel);
        break;
    case CT_TEL_OPT_DETECTED_CLOCK_RATE_STATUS:
        hasChanged = SetDetectedClockRate(theLevel);
        break;
    case CT_TEL_OPT_PEER_OUTPUT_POWER_STATUS:
        hasChanged = SetTotalPeerOutputPower(theLevel);
        break;
    case CT_TEL_OPT_PEER_OMS_OUTPUT_POWER_STATUS:
        hasChanged = SetTotalPeerOmsOutputPower(theLevel);
        break;
    case CT_TEL_OPT_OMS_OUTPUT_POWER_STATUS:
        hasChanged = SetTotalOmsOutputPower(theLevel);
        break;
    case CT_TEL_OPT_ACTUAL_GAIN_STATUS:
        hasChanged = SetActualGain(theLevel);
        break;
    case CT_TEL_OPT_RX_LANE_LOW_POWER_STATUS:
        hasChanged = SetLaneLowReceivedPower(theLevel);
        break;
    case CT_TEL_OPT_RX_LANE_HIGH_POWER_STATUS:
        hasChanged = SetLaneHighReceivedPower(theLevel);
        break;
    case CT_TEL_OPT_TX_LANE_LOW_POWER_STATUS:
        hasChanged = SetLaneLowTransmittedPower(theLevel);
        break;
    case CT_TEL_OPT_TX_LANE_HIGH_POWER_STATUS:
        hasChanged = SetLaneHighTransmittedPower(theLevel);
        break;
    default:
        FC_THROW_ERROR(FC_NotSupportedError, "MON_OptStatus: unsupported status");
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetTotalInputPower() const
{
    return myTotalInputPower; 
}

bool MON_OptStatus::SetTotalInputPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    
    // Default power change to false
    mySignifPowerChange = false;
  
    if (myTotalInputPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myTotalInputPower);
        mySignifPowerChange = aDiffPower >= ((CT_TEL_mBm) CT_TEL_POWER_FACTOR);
  
        // Now set myTotalInputPower
        myTotalInputPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetTotalOutputPower() const
{
    return myTotalOutputPower; 
}

bool MON_OptStatus::SetTotalOutputPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    
    // Default power change to false
    mySignifOutputPowerChange = false;
  
    if (myTotalOutputPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myTotalOutputPower);
        mySignifOutputPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myTotalOutputPower
        myTotalOutputPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetTotalPeerOutputPower() const
{
    return myTotalPeerOutputPower; 
}

bool MON_OptStatus::SetTotalPeerOutputPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    
    // Default power change to false
    mySignifPeerOutputPowerChange = false;
  
    if (myTotalPeerOutputPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myTotalPeerOutputPower);
        mySignifPeerOutputPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myTotalInputPower
        myTotalPeerOutputPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetTotalPeerOmsOutputPower() const
{
    return myTotalPeerOmsOutputPower; 
}

bool MON_OptStatus::SetTotalPeerOmsOutputPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    
    // Default power change to false
    mySignifPeerOmsOutputPowerChange = false;
  
    if (myTotalPeerOmsOutputPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myTotalPeerOmsOutputPower);
        mySignifPeerOmsOutputPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myTotalInputPower
        myTotalPeerOmsOutputPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetTotalOmsOutputPower() const
{
    return myTotalOmsOutputPower; 
}

bool MON_OptStatus::SetTotalOmsOutputPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    
    // Default power change to false
    mySignifOmsOutputPowerChange = false;
  
    if (myTotalOmsOutputPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myTotalOmsOutputPower);
        mySignifOmsOutputPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myTotalInputPower
        myTotalOmsOutputPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}


CT_TEL_mBm MON_OptStatus::GetLaneLowReceivedPower() const
{
    return myLaneLowReceivedPower; 
}

bool MON_OptStatus::SetLaneLowReceivedPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    // Default power change to false
    myRxLoisLaneSignifPowerChange = false;
  
    if (myLaneLowReceivedPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myLaneLowReceivedPower);
        myRxLoisLaneSignifPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myLaneLowReceivedPower
        myLaneLowReceivedPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetLaneHighReceivedPower() const
{
    return myLaneHighReceivedPower; 
}

bool MON_OptStatus::SetLaneHighReceivedPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    // Default power change to false
    myRxHighLaneSignifPowerChange = false;
  
    if (myLaneHighReceivedPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myLaneHighReceivedPower);
        myRxHighLaneSignifPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myLaneHighReceivedPower
        myLaneHighReceivedPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

const vector<CT_TEL_mBm>& MON_OptStatus::GetLaneReceivedPower() const
{
    return myLaneReceivedPower; 
}

bool MON_OptStatus::SetLaneReceivedPower(const vector<CT_TEL_mBm>& theLanePowers)
{
    //return true if changed
    bool hasChanged = false;
    // Default power change to false
    myRxLaneSignifPowerChange = false;

    if (theLanePowers.size() != myLaneReceivedPower.size())
    {
        myLaneReceivedPower = theLanePowers;
        hasChanged = true;
        myRxLaneSignifPowerChange = true;
    }
    else
    {
        for (uint32 i = 0; i < myLaneReceivedPower.size(); i++)
        {
            CT_TEL_mBm thePower = theLanePowers[i];
            if (myLaneReceivedPower[i] != thePower)
            {
                // Check if there is a significant change in power 
                CT_TEL_mBm aDiffPower = abs(thePower - myLaneReceivedPower[i]);
                myRxLaneSignifPowerChange |= aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
                myLaneReceivedPower[i] = thePower;
                hasChanged = true;
            }
        }
    }

    return hasChanged;
}


CT_TEL_mBm MON_OptStatus::GetLaneLowTransmittedPower() const
{
    return myLaneLowTransmittedPower; 
}

bool MON_OptStatus::SetLaneLowTransmittedPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    // Default power change to false
    myTxLoisLaneSignifPowerChange = false;
  
    if (myLaneLowTransmittedPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myLaneLowTransmittedPower);
        myTxLoisLaneSignifPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myLaneLowTransmittedPower
        myLaneLowTransmittedPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetLaneHighTransmittedPower() const
{
    return myLaneHighTransmittedPower; 
}

bool MON_OptStatus::SetLaneHighTransmittedPower(CT_TEL_mBm thePower)
{

    //return true if changed
    bool hasChanged = false;
    // Default power change to false
    myTxHighLaneSignifPowerChange = false;
  
    if (myLaneHighTransmittedPower != thePower)
    {
        // Check if there is a significant change in power 
        CT_TEL_mBm aDiffPower = abs(thePower - myLaneHighTransmittedPower);
        myTxHighLaneSignifPowerChange = aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
  
        // Now set myLaneHighTransmittedPower
        myLaneHighTransmittedPower = thePower;
        hasChanged = true;
    }

    return hasChanged;
}

const vector<CT_TEL_mBm>& MON_OptStatus::GetLaneTransmittedPower() const
{
    return myLaneTransmittedPower; 
}

bool MON_OptStatus::SetLaneTransmittedPower(const vector<CT_TEL_mBm>& theLanePowers)
{
    //return true if changed
    bool hasChanged = false;
    // Default power change to false
    myTxLaneSignifPowerChange = false;

    if (theLanePowers.size() != myLaneTransmittedPower.size())
    {
        myLaneTransmittedPower = theLanePowers;
        hasChanged = true;
        myTxLaneSignifPowerChange = true;
    }
    else
    {
        for (uint32 i = 0; i < myLaneTransmittedPower.size(); i++)
        {
            CT_TEL_mBm thePower = theLanePowers[i];
            if (myLaneTransmittedPower[i] != thePower)
            {
                // Check if there is a significant change in power 
                CT_TEL_mBm aDiffPower = abs(thePower - myLaneTransmittedPower[i]);
                myTxLaneSignifPowerChange |= aDiffPower >= ((CT_TEL_mBm) (CT_TEL_POWER_FACTOR/4));
                myLaneTransmittedPower[i] = thePower;
                hasChanged = true;
            }
        }
    }

    return hasChanged;
}


CT_TEL_uAmps MON_OptStatus::GetDetectedClockRate() const
{
    return myDetectedClockRate; 
}

bool MON_OptStatus::SetDetectedClockRate(CT_TEL_daHz theClockRate)
{
    //return true if changed
    bool hasChanged = false;

    if (myDetectedClockRate != theClockRate)
    {
        myDetectedClockRate = theClockRate;
        hasChanged |= true;
    }

    return hasChanged;
}


bool MON_OptStatus::GetIsClockRateLocked() const 
{
    return (myDetectedClockRate != 0);
}

//Returns whether there was a significant power change (as determined by SetTotalInputPower)
bool MON_OptStatus::GetSignifPowerChange() 
{
    return mySignifPowerChange;
}

// Returns whether there was a significant output power
// change (as determined by SetTotalInputPower)
bool MON_OptStatus::GetSignifOutputPowerChange() 
{
    return mySignifOutputPowerChange;
}

// Returns whether there was a significant peer output 
// power change (as determined by SetTotalPeerOutputPower)
bool MON_OptStatus::GetSignifPeerOutputPowerChange() 
{
    return mySignifPeerOutputPowerChange;
}

// Returns whether there was a significant peer OMS output 
// power change (as determined by SetTotalPeerOmsOutputPower)
bool MON_OptStatus::GetSignifPeerOmsOutputPowerChange() 
{
    return mySignifPeerOmsOutputPowerChange;
}

// Returns whether there was a significant OMS output 
// power change (as determined by SetTotalOmsOutputPower)
bool MON_OptStatus::GetSignifOmsOutputPowerChange() 
{
    return mySignifOmsOutputPowerChange;
}

// Returns whether there was a significant output power
// change (as determined by SetLaneLowReceivedPower)
bool MON_OptStatus::GetRxLoisLaneSignifPowerChange() 
{
    return myRxLoisLaneSignifPowerChange;
}

// Returns whether there was a significant output power
// change (as determined by SetLaneHighReceivedPower)
bool MON_OptStatus::GetRxHighLaneSignifPowerChange() 
{
    return myRxHighLaneSignifPowerChange;
}

// Returns whether there was a significant output power
// change (as determined by SetLaneReceivedPower)
bool MON_OptStatus::GetRxLaneSignifPowerChange() 
{
    return myRxLaneSignifPowerChange;
}


// Returns whether there was a significant output power
// change (as determined by SetLaneLowTransmittedPower)
bool MON_OptStatus::GetTxLoisLaneSignifPowerChange() 
{
    return myTxLoisLaneSignifPowerChange;
}

// Returns whether there was a significant output power
// change (as determined by SetLaneHighTransmittedPower)
bool MON_OptStatus::GetTxHighLaneSignifPowerChange() 
{
    return myTxHighLaneSignifPowerChange;
}

// Returns whether there was a significant output power
// change (as determined by SetLaneTransmittedPower)
bool MON_OptStatus::GetTxLaneSignifPowerChange() 
{
    return myTxLaneSignifPowerChange;
}


uint32 MON_OptStatus::GetPrbsRxMostSignifCount() const 
{
    return myPrbsRxMostSignifCount;
}

bool MON_OptStatus::SetPrbsRxMostSignifCount(uint32 thePrbsRxMostSignifCount) 
{
    bool hasChanged = false;
    if (myPrbsRxMostSignifCount != thePrbsRxMostSignifCount)
    {
        myPrbsRxMostSignifCount = thePrbsRxMostSignifCount;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_OptStatus::GetPrbsRxLeastSignifCount() const 
{
    return myPrbsRxLeastSignifCount;
}

bool MON_OptStatus::SetPrbsRxLeastSignifCount(uint32 thePrbsRxLeastSignifCount) 
{
    bool hasChanged = false;
    if (myPrbsRxLeastSignifCount != thePrbsRxLeastSignifCount)
    {
        myPrbsRxLeastSignifCount = thePrbsRxLeastSignifCount;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_OptStatus::GetPrbsRxTimeInterval() const 
{
    return myPrbsRxTimeInterval;
}

bool MON_OptStatus::SetPrbsRxTimeInterval(uint32 thePrbsRxTimeInterval) 
{
    bool hasChanged = false;
    if (myPrbsRxTimeInterval != thePrbsRxTimeInterval)
    {
        myPrbsRxTimeInterval = thePrbsRxTimeInterval;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_PrbsSyncStatus MON_OptStatus::GetPrbsRxLosync() const 
{
    return myPrbsRxLosync;
}

bool MON_OptStatus::SetPrbsRxLosync(CT_TEL_PrbsSyncStatus thePrbsRxLosync) 
{
    bool hasChanged = false;
    if (myPrbsRxLosync != thePrbsRxLosync)
    {
        myPrbsRxLosync = thePrbsRxLosync;
        hasChanged = true;
    }

    return hasChanged;
}

uint32 MON_OptStatus::GetPrbsRxFirstSyncLosyncCount() const 
{
    return myPrbsRxFirstSyncLosyncCount;
}

bool MON_OptStatus::SetPrbsRxFirstSyncLosyncCount(uint32 thePrbsRxFirstSyncLosyncCount) 
{
    bool hasChanged = false;
    if (myPrbsRxFirstSyncLosyncCount != thePrbsRxFirstSyncLosyncCount)
    {
        myPrbsRxFirstSyncLosyncCount = thePrbsRxFirstSyncLosyncCount;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_OptStatus::GetPrbsRxFirstSync() const 
{
    return myPrbsRxFirstSync;
}

bool MON_OptStatus::SetPrbsRxFirstSync(bool thePrbsRxFirstSync) 
{
    bool hasChanged = false;
    if (myPrbsRxFirstSync != thePrbsRxFirstSync)
    {
        myPrbsRxFirstSync = thePrbsRxFirstSync;
        hasChanged = true;
    }

    return hasChanged;
}

bool MON_OptStatus::GetIsDualOcmPresent() const 
{
    return myIsDualOcmPresent;
}

bool MON_OptStatus::SetIsDualOcmPresent(bool theEnable) 
{
    bool hasChanged = false;
    if (myIsDualOcmPresent != theEnable)
    {
        myIsDualOcmPresent = theEnable;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_mBm MON_OptStatus::GetActualGain() const
{
    return myActualGain; 
}

bool MON_OptStatus::SetActualGain(CT_TEL_mBm theActualGain)
{

    //return true if changed
    bool hasChanged = false;
    
    if (myActualGain != theActualGain)
    { 
        myActualGain = theActualGain;
        hasChanged = true;
    }

    return hasChanged;
}


int32 MON_OptStatus::GetChromaticDispersion() const
{
    return myChromaticDispersion; 
}

bool MON_OptStatus::SetChromaticDispersion(int32 theChromaticDispersion)
{

    //return true if changed
    bool hasChanged = false;
    
    if (myChromaticDispersion != theChromaticDispersion)
    { 
        myChromaticDispersion = theChromaticDispersion;
        hasChanged = true;
    }

    return hasChanged;
}

uint16 MON_OptStatus::GetDifferentialGroupDelay() const
{
    return myDifferentialGroupDelay; 
}

bool MON_OptStatus::SetDifferentialGroupDelay(uint16 theDifferentialGroupDelay)
{

    //return true if changed
    bool hasChanged = false;
    
    if (myDifferentialGroupDelay != theDifferentialGroupDelay)
    { 
        myDifferentialGroupDelay = theDifferentialGroupDelay;
        hasChanged = true;
    }

    return hasChanged;
}

///
uint16 MON_OptStatus::Get2ndOrderPolarModeDispersion() const
{
    return my2ndOrderPolarModeDispersion; 
}

bool MON_OptStatus::Set2ndOrderPolarModeDispersion(uint16 the2ndOrderPolarModeDispersion)
{

    //return true if changed
    bool hasChanged = false;
    
    if (my2ndOrderPolarModeDispersion != the2ndOrderPolarModeDispersion)
    { 
        my2ndOrderPolarModeDispersion = the2ndOrderPolarModeDispersion;
        hasChanged = true;
    }

    return hasChanged;
}

///
uint32 MON_OptStatus::GetStateOfPolarization() const
{
    return myStateOfPolarization; 
}

bool MON_OptStatus::SetStateOfPolarization(uint32 theStateOfPolarization)
{

    //return true if changed
    bool hasChanged = false;
    
    if (myStateOfPolarization != theStateOfPolarization)
    { 
        myStateOfPolarization = theStateOfPolarization;
        hasChanged = true;
    }

    return hasChanged;
}

///
CT_TEL_mBm MON_OptStatus::GetPolarDependentLoss() const
{
    return myPolarDependentLoss; 
}

bool MON_OptStatus::SetPolarDependentLoss(CT_TEL_mBm thePolarDependentLoss)
{

    //return true if changed
    bool hasChanged = false;
    
    if (myPolarDependentLoss != thePolarDependentLoss)
    { 
        myPolarDependentLoss = thePolarDependentLoss;
        hasChanged = true;
    }

    return hasChanged;
}

///
CT_TEL_mBm MON_OptStatus::GetQvalue() const
{
    return myQvalue; 
}

bool MON_OptStatus::SetQvalue(CT_TEL_mBm theQvalue)
{

    //return true if changed
    bool hasChanged = false;
    
    if (myQvalue != theQvalue)
    { 
        myQvalue = theQvalue;
        hasChanged = true;
    }

    return hasChanged;
}

///
CT_TEL_mBm MON_OptStatus::GetCarrierFrequencyOffset() const
{
    return myCarrierFrequencyOffset; 
}

bool MON_OptStatus::SetCarrierFrequencyOffset(CT_TEL_mBm theCarrierFrequencyOffset)
{

    //return true if changed
    bool hasChanged = false;
    
    if (myCarrierFrequencyOffset != theCarrierFrequencyOffset)
    { 
        myCarrierFrequencyOffset = theCarrierFrequencyOffset;
        hasChanged = true;
    }

    return hasChanged;
}

///
CT_TEL_mBm MON_OptStatus::GetSignalNoiseRatio() const
{
    return mySignalNoiseRatio; 
}

bool MON_OptStatus::SetSignalNoiseRatio(CT_TEL_mBm theSignalNoiseRatio)
{

    //return true if changed
    bool hasChanged = false;
    
    if (mySignalNoiseRatio != theSignalNoiseRatio)
    { 
        mySignalNoiseRatio = theSignalNoiseRatio;
        hasChanged = true;
    }

    return hasChanged;
}


// For Display
ostream& MON_OptStatus::WriteObject(ostream& theStream)
{
    uint8 tmpPrbsRxLosync = myPrbsRxLosync;

    MON_Object::WriteObject(theStream);
    theStream << FC_InsertVar(myTotalInputPower);
    theStream << FC_InsertVar(myTotalOutputPower);
    theStream << FC_InsertVar(myTotalPeerOutputPower);
    theStream << FC_InsertVar(myTotalPeerOmsOutputPower);
    theStream << FC_InsertVar(myTotalOmsOutputPower);
    theStream << FC_InsertVar(myDetectedClockRate);
    theStream << FC_InsertVar(myPrbsRxMostSignifCount);
    theStream << FC_InsertVar(myPrbsRxLeastSignifCount);
    theStream << FC_InsertVar(myPrbsRxTimeInterval);
    theStream << FC_InsertVar(tmpPrbsRxLosync);
    theStream << FC_InsertVar(myPrbsRxFirstSyncLosyncCount);
    theStream << FC_InsertVar(myPrbsRxFirstSync);
    theStream << FC_InsertVar(myIsDualOcmPresent);
    theStream << FC_InsertVar(myActualGain);
    theStream << FC_InsertVar(myChromaticDispersion);
    theStream << FC_InsertVar(myDifferentialGroupDelay);
    theStream << FC_InsertVar(my2ndOrderPolarModeDispersion);
    theStream << FC_InsertVar(myStateOfPolarization);
    theStream << FC_InsertVar(myPolarDependentLoss);
    theStream << FC_InsertVar(myQvalue);
    theStream << FC_InsertVar(myCarrierFrequencyOffset);
    theStream << FC_InsertVar(mySignalNoiseRatio);
    theStream << FC_InsertVar(myLaneLowReceivedPower);
    theStream << FC_InsertVar(myLaneHighReceivedPower);
    theStream << FC_InsertVar(myLaneLowTransmittedPower);
    theStream << FC_InsertVar(myLaneHighTransmittedPower);

  	uint32	numOfLanes = myLaneReceivedPower.size();
    theStream << FC_InsertVar(numOfLanes);
	for (uint32 i = 0; i != myLaneReceivedPower.size(); i++)
    {
        CT_TEL_mBm power = myLaneReceivedPower[i];
		theStream << FC_InsertVar(power);
    }
  	numOfLanes = myLaneTransmittedPower.size();
    theStream << FC_InsertVar(numOfLanes);
	for (uint32 i = 0; i != myLaneTransmittedPower.size(); i++)
    {
        CT_TEL_mBm power = myLaneTransmittedPower[i];
		theStream << FC_InsertVar(power);
    }

    return theStream;
}

istream& MON_OptStatus::ReadObject(istream& theStream)
{
    uint8 tmpPrbsRxLosync;

    MON_Object::ReadObject(theStream);
    theStream >> FC_ExtractVar(myTotalInputPower);
    theStream >> FC_ExtractVar(myTotalOutputPower);
    theStream >> FC_ExtractVar(myTotalPeerOutputPower);
    theStream >> FC_ExtractVar(myTotalPeerOmsOutputPower);
    theStream >> FC_ExtractVar(myTotalOmsOutputPower);
    theStream >> FC_ExtractVar(myDetectedClockRate);
    theStream >> FC_ExtractVar(myPrbsRxMostSignifCount);
    theStream >> FC_ExtractVar(myPrbsRxLeastSignifCount);
    theStream >> FC_ExtractVar(myPrbsRxTimeInterval);
    theStream >> FC_ExtractVar(tmpPrbsRxLosync);
    theStream >> FC_ExtractVar(myPrbsRxFirstSyncLosyncCount);
    theStream >> FC_ExtractVar(myPrbsRxFirstSync);
    theStream >> FC_ExtractVar(myIsDualOcmPresent);
    theStream >> FC_ExtractVar(myActualGain);
    theStream >> FC_ExtractVar(myChromaticDispersion);
    theStream >> FC_ExtractVar(myDifferentialGroupDelay);
    theStream >> FC_ExtractVar(my2ndOrderPolarModeDispersion);
    theStream >> FC_ExtractVar(myStateOfPolarization);
    theStream >> FC_ExtractVar(myPolarDependentLoss);
    theStream >> FC_ExtractVar(myQvalue);
    theStream >> FC_ExtractVar(myCarrierFrequencyOffset);
    theStream >> FC_ExtractVar(mySignalNoiseRatio);
    theStream >> FC_ExtractVar(myLaneLowReceivedPower);
    theStream >> FC_ExtractVar(myLaneHighReceivedPower);
    theStream >> FC_ExtractVar(myLaneLowTransmittedPower);
    theStream >> FC_ExtractVar(myLaneHighTransmittedPower);

    myPrbsRxLosync = (CT_TEL_PrbsSyncStatus)(tmpPrbsRxLosync);

#ifndef PSOSP
    size_t	numOfLanes = 0;
    theStream >> FC_ExtractVar(numOfLanes);
    if (myLaneReceivedPower.size() != numOfLanes)
    {
        myLaneReceivedPower.clear();
        myLaneReceivedPower.resize(numOfLanes);
    }
    for (uint32 i = 0; i < numOfLanes; i++)
    {
        CT_TEL_mBm power;
        theStream >> FC_ExtractVar(power);
        myLaneReceivedPower[i] = power;
    }
    numOfLanes = 0;
    theStream >> FC_ExtractVar(numOfLanes);
    if (myLaneTransmittedPower.size() != numOfLanes)
    {
        myLaneTransmittedPower.clear();
        myLaneTransmittedPower.resize(numOfLanes);
    }
    for (uint32 i = 0; i < numOfLanes; i++)
    {
        CT_TEL_mBm power;
        theStream >> FC_ExtractVar(power);
        myLaneTransmittedPower[i] = power;
    }
#endif

    return theStream;
}

// For persistence and region transfer
FC_Stream& MON_OptStatus::WriteObjectBinary(FC_Stream& theStream)
{
    uint8 tmpPrbsRxLosync = myPrbsRxLosync;

    MON_Object::WriteObjectBinary(theStream);
    theStream << myTotalInputPower;
    theStream << myTotalOutputPower;
    theStream << myTotalPeerOutputPower;
    theStream << myTotalPeerOmsOutputPower;
    theStream << myTotalOmsOutputPower;
    theStream << myDetectedClockRate;
    theStream << myPrbsRxMostSignifCount;
    theStream << myPrbsRxLeastSignifCount;
    theStream << myPrbsRxTimeInterval;
    theStream << tmpPrbsRxLosync;
    // -- Used only locally -- theStream << myPrbsRxLosyncCount;
    // -- Used only locally -- theStream << myPrbsRxFirstSync;
    theStream << myIsDualOcmPresent;
    theStream << myActualGain;
    theStream << myChromaticDispersion;
    theStream << myDifferentialGroupDelay;
    // -- Used only locally -- theStream << my2ndOrderPolarModeDispersion;
    // -- Used only locally -- theStream << myStateOfPolarization;
    // -- Used only locally -- theStream << myPolarDependentLoss;
    // -- Used only locally -- theStream << myQvalue;
    // -- Used only locally -- theStream << myCarrierFrequencyOffset;
    // -- Used only locally -- theStream << mySignalNoiseRatio;
    theStream << myLaneLowReceivedPower;
    theStream << myLaneHighReceivedPower;
    theStream << myLaneLowTransmittedPower;
    theStream << myLaneHighTransmittedPower;


  	uint32	numOfLanes = myLaneReceivedPower.size();
    theStream << numOfLanes;
	for (uint32 i = 0; i != myLaneReceivedPower.size(); i++)
    {
        CT_TEL_mBm power = myLaneReceivedPower[i];
		theStream << power;
    }
  	numOfLanes = myLaneTransmittedPower.size();
    theStream << numOfLanes;
	for (uint32 i = 0; i != myLaneTransmittedPower.size(); i++)
    {
        CT_TEL_mBm power = myLaneTransmittedPower[i];
		theStream << power;
    }

    return theStream;
}

FC_Stream& MON_OptStatus::ReadObjectBinary(FC_Stream& theStream)
{
    uint8 tmpPrbsRxLosync;

    MON_Object::ReadObjectBinary(theStream);
    theStream >> myTotalInputPower;
    theStream >> myTotalOutputPower;
    theStream >> myTotalPeerOutputPower;
    theStream >> myTotalPeerOmsOutputPower;
    theStream >> myTotalOmsOutputPower;
    theStream >> myDetectedClockRate;
    theStream >> myPrbsRxMostSignifCount;
    theStream >> myPrbsRxLeastSignifCount;
    theStream >> myPrbsRxTimeInterval;
    theStream >> tmpPrbsRxLosync;
    // -- Used only locally -- theStream >> myPrbsRxLosyncCount;
    // -- Used only locally -- theStream >> myPrbsRxFirstSync;
    theStream >> myIsDualOcmPresent;
    theStream >> myActualGain;
    theStream >> myChromaticDispersion;
    theStream >> myDifferentialGroupDelay;
    // -- Used only locally -- theStream >> my2ndOrderPolarModeDispersion;
    // -- Used only locally -- theStream >> myStateOfPolarization;
    // -- Used only locally -- theStream >> myPolarDependentLoss;
    // -- Used only locally -- theStream >> myQvalue;
    // -- Used only locally -- theStream >> myCarrierFrequencyOffset;
    // -- Used only locally -- theStream >> mySignalNoiseRatio;
    theStream >> myLaneLowReceivedPower;
    theStream >> myLaneHighReceivedPower;
    theStream >> myLaneLowTransmittedPower;
    theStream >> myLaneHighTransmittedPower;

    myPrbsRxLosync = (CT_TEL_PrbsSyncStatus)(tmpPrbsRxLosync);

#ifndef PSOSP
    size_t	numOfLanes = 0;
    theStream >> numOfLanes;
    if (myLaneReceivedPower.size() != numOfLanes)
    {
        myLaneReceivedPower.clear();
        //When upgrading, there has a chance that SPM has upgraded the new load
        //while the modules still have the old load, the numOfLanes maybe a random
        //big value, this will deplete the memory and cause SPM hang up.
        //So add this logic to avoid this scenario.
        numOfLanes = (numOfLanes > CT_NUM_PSX_LANES) ? CT_NUM_PSX_LANES : numOfLanes;
        myLaneReceivedPower.resize(numOfLanes);
    }
    for (uint32 i = 0; i < numOfLanes; i++)
    {
        CT_TEL_mBm power;
        theStream >> power;
        myLaneReceivedPower[i] = power;
    }
    numOfLanes = 0;
    theStream >> numOfLanes;
    if (myLaneTransmittedPower.size() != numOfLanes)
    {
        myLaneTransmittedPower.clear();
        //When upgrading, there has a chance that SPM has upgraded the new load
        //while the modules still have the old load, the numOfLanes maybe a random
        //big value, this will deplete the memory and cause SPM hang up.
        //So add this logic to avoid this scenario.
        numOfLanes = (numOfLanes > CT_NUM_PSX_LANES) ? CT_NUM_PSX_LANES : numOfLanes;
        myLaneTransmittedPower.resize(numOfLanes);
    }
    for (uint32 i = 0; i < numOfLanes; i++)
    {
        CT_TEL_mBm power;
        theStream >> power;
        myLaneTransmittedPower[i] = power;
    }
#endif

    return theStream;
}

void MON_OptStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    theStream   << "OPT     - Output Power   (mBm)              = " << myTotalOutputPower << endl;
    theStream   << "OPT     - Input Power    (mBm)              = " << myTotalInputPower << endl;
    theStream   << "OPT     - Peer Output Power   (mBm)         = " << myTotalPeerOutputPower << endl;
    theStream   << "OPT     - Peer OMS Output Power   (mBm)     = " << myTotalPeerOmsOutputPower << endl;
    theStream   << "OPT     - OMS Output Power   (mBm)          = " << myTotalOmsOutputPower << endl;
    theStream   << "OPT     - Lane Low Received Power   (mBm)   = " << myLaneLowReceivedPower << endl;
    theStream   << "OPT     - Lane High Received Power  (mBm)   = " << myLaneHighReceivedPower << endl;

    theStream   << "OPT     - Lanes Received Power  (mBm)       = " ;
    for (uint32 i = 0; i < myLaneReceivedPower.size(); i++)
    {
        theStream << myLaneReceivedPower[i];
        if (i < (myLaneReceivedPower.size() - 1))
        {
            theStream << ", ";
        }
    }
    theStream   << endl;

    theStream   << "OPT     - Lane Low Transmitted Power  (mBm) = " << myLaneLowTransmittedPower << endl;
    theStream   << "OPT     - Lane High Transmitted Power (mBm) = " << myLaneHighTransmittedPower << endl;

    theStream   << "OPT     - Lanes Transmitted Power  (mBm)    = " ;
    for (uint32 i = 0; i < myLaneTransmittedPower.size(); i++)
    {
        theStream << myLaneTransmittedPower[i];
        if (i < (myLaneTransmittedPower.size() - 1))
        {
            theStream << ", ";
        }
    }
    theStream   << endl;

    theStream   << "OPT     - Detected Clock Rate  (daHz)       = " << myDetectedClockRate << endl;
    theStream   << "OPT     - Is Clock Rate Locked              = " << DISPLAY_BOOL(GetIsClockRateLocked()) << endl;
    theStream   << "OPT     - PRBS Rx Errors Most Signif Count  = " << myPrbsRxMostSignifCount << endl;
    theStream   << "OPT     - PRBS Rx Errors Least Signif Count = " << myPrbsRxLeastSignifCount << endl;
    theStream   << "OPT     - PRBS Rx Errors Time Interval (ms) = " << myPrbsRxTimeInterval << endl;
    theStream   << "OPT     - PRBS Rx Losync                    = " << DISPLAY_PRBS_SYNC_STATUS(myPrbsRxLosync) << endl;
    theStream   << "OPT     - PRBS Rx FirstSyncLosyncCount      = " << myPrbsRxFirstSyncLosyncCount << endl;
    theStream   << "OPT     - PRBS Rx First Sync                = " << DISPLAY_BOOL(myPrbsRxFirstSync) << endl;
    theStream   << "OPT     - Dual OCM Present                  = " << DISPLAY_BOOL(myIsDualOcmPresent) << endl;
    theStream   << "OPT     - Actual Gain (dB)                  = " << myActualGain << endl;  
    theStream   << "OPT     - Chromatic Dispersion (ps/nm)      = " << uint32(myChromaticDispersion) << endl;  
    theStream   << "OPT     - Differential Group Delay (ps)     = " << uint32(myDifferentialGroupDelay) << endl;  
    theStream   << "OPT     - 2nd Order Polar Mode Disp (ps2)   = " << uint32(my2ndOrderPolarModeDispersion) << endl;  
    theStream   << "OPT     - State Of Polarization (rad/s)     = " << uint32(myStateOfPolarization) << endl;  
    theStream   << "OPT     - Polar Dependent Loss (mBm)        = " << myPolarDependentLoss << endl;  
    theStream   << "OPT     - Q value (mBm)                     = " << myQvalue << endl;  
    theStream   << "OPT     - Carrier Frequency Offset (mHz)    = " << myCarrierFrequencyOffset << endl;  
    theStream   << "OPT     - Signal-to-Noise Ratio (mBm)       = " << mySignalNoiseRatio << endl;  
}
