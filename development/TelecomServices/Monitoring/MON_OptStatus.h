// //Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_MON_OPTSTATUS_3C0FE66F019C_INCLUDED
#define _INC_MON_OPTSTATUS_3C0FE66F019C_INCLUDED

#include "MON_Status.h"
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_Equipment.h>

//This class hold the status value (equipment levels) for the 
//optical layer (transmit side).
class MON_OptStatus 
: public MON_Status
{
public:
    //Constructor.
    MON_OptStatus(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OptStatus(void );

    //Returns the level of the status provide as argument.
    virtual void GetLevel(CT_TEL_Status theStatus, CT_TEL_Type* theLevel) const;

    //Returns true if level has changed.
    virtual bool SetLevel(CT_TEL_Status theStatus, CT_TEL_Type theLevel);

    //Returns the total aggregate optical input power.
    virtual CT_TEL_mBm GetTotalInputPower() const;

    //Sets the total input power.
    virtual bool SetTotalInputPower(CT_TEL_daHz thePower);

    //Returns the total aggregate optical output power.
    virtual CT_TEL_mBm GetTotalOutputPower() const;

    //Sets the total output power.
    virtual bool SetTotalOutputPower(CT_TEL_daHz thePower);

    //Returns the power of the Received Lowest Lane.
    virtual CT_TEL_mBm GetLaneLowReceivedPower() const;

    //Sets the power of the Received Lowest Lane.
    virtual bool SetLaneLowReceivedPower(CT_TEL_daHz thePower);

    //Returns the power of the Received Highest Lane.
    virtual CT_TEL_mBm GetLaneHighReceivedPower() const;

    //Sets the power of the Received Highest Lane.
    virtual bool SetLaneHighReceivedPower(CT_TEL_daHz thePower);

    //Returns the power of the Received Lane.
    virtual const vector<CT_TEL_mBm>& GetLaneReceivedPower() const;

    //Sets the power of the Received Lane.
    virtual bool SetLaneReceivedPower(const vector<CT_TEL_mBm>& theLanePowers);

    //Returns the power of the Transmitted Lowest Lane.
    virtual CT_TEL_mBm GetLaneLowTransmittedPower() const;

    //Sets the power of the Transmitted Lowest Lane.
    virtual bool SetLaneLowTransmittedPower(CT_TEL_daHz thePower);

    //Returns the power of the Transmitted Highest Lane.
    virtual CT_TEL_mBm GetLaneHighTransmittedPower() const;

    //Sets the power of the Transmitted Highest Lane.
    virtual bool SetLaneHighTransmittedPower(CT_TEL_daHz thePower);

    //Returns the power of the Transmitted Lane.
    virtual const vector<CT_TEL_mBm>& GetLaneTransmittedPower() const;

    //Sets the power of the Transmitted Lane.
    virtual bool SetLaneTransmittedPower(const vector<CT_TEL_mBm>& theLanePowers);


    //Returns the total aggregate optical input power.
    CT_TEL_uAmps GetDetectedClockRate() const;

    //Sets the total input power.
    virtual bool SetDetectedClockRate(CT_TEL_daHz theCurrent);


    //Gets whether the Clock Rate is Locked
    bool GetIsClockRateLocked() const ;

    //Returns whether there was a significant power change (as determined by SetTotalInputPower)
    virtual bool GetSignifPowerChange();
    virtual bool GetSignifOutputPowerChange();
    virtual bool GetSignifPeerOutputPowerChange();
    virtual bool GetSignifPeerOmsOutputPowerChange();
    virtual bool GetSignifOmsOutputPowerChange();

    virtual bool GetRxLoisLaneSignifPowerChange();
    virtual bool GetRxHighLaneSignifPowerChange();
    virtual bool GetTxLoisLaneSignifPowerChange();
    virtual bool GetTxHighLaneSignifPowerChange();
    virtual bool GetRxLaneSignifPowerChange();
    virtual bool GetTxLaneSignifPowerChange();

    //Sets the Most Significant Digits of the PRBS Rx Error Counter
    bool SetPrbsRxMostSignifCount(uint32 thePrbsRxMostSignifCount) ;

    //Gets the Most Significant Digits of the PRBS Rx Error Counter
     uint32 GetPrbsRxMostSignifCount() const ;

    //Sets the Least Significant Digits of the PRBS Rx Error Counter
    bool SetPrbsRxLeastSignifCount(uint32 thePrbsRxLeastSignifCount) ;

    //Gets the Least Significant Digits of the PRBS Rx Error Counter
    uint32 GetPrbsRxLeastSignifCount() const ;

    //Sets the Time associated with the PRBS Rx Error Counter
    bool SetPrbsRxTimeInterval(uint32 thePrbsRxTimeInterval) ;

    //Gets the Time associated with the PRBS Rx Error Counter
    uint32 GetPrbsRxTimeInterval() const ;

    //Sets the PRBS Rx Losync
    bool SetPrbsRxLosync(CT_TEL_PrbsSyncStatus thePrbsRxLosync) ;

    //Gets the PRBS Rx Losync
    CT_TEL_PrbsSyncStatus GetPrbsRxLosync() const ;

    // Sets the PRBS Rx Losync Count
    bool SetPrbsRxFirstSyncLosyncCount(uint32 thePrbsRxLosyncCount);

    // Gets the PRBS Rx Losync Count
    uint32 GetPrbsRxFirstSyncLosyncCount() const;

    // Sets the PRBS Rx First Sync flag
    bool SetPrbsRxFirstSync(bool thePrbsRxFirstSync);

    // Gets the PRBS Rx First Sync flag
    bool GetPrbsRxFirstSync() const;

    //Returns the total aggregate optical peer output power
    virtual CT_TEL_mBm GetTotalPeerOutputPower() const;

    //Sets the total optical peer output power.
    virtual bool SetTotalPeerOutputPower(CT_TEL_mBm thePower);

    //Returns the total aggregate optical peer OMS output power
    virtual CT_TEL_mBm GetTotalPeerOmsOutputPower() const;

    //Sets the total optical peer OMS output power.
    virtual bool SetTotalPeerOmsOutputPower(CT_TEL_mBm thePower);

    //Returns the total aggregate optical OMS output power
    virtual CT_TEL_mBm GetTotalOmsOutputPower() const;

    //Sets the total optical OMS output power.
    virtual bool SetTotalOmsOutputPower(CT_TEL_mBm thePower);

    //Sets whether the OCM is Dual (true)
    bool SetIsDualOcmPresent(bool theEnable) ;

    //Gets whether the OCM is Dual (true)
    bool GetIsDualOcmPresent() const ;

    //Returns the actual gain.    
    CT_TEL_mBm GetActualGain() const;

    //Sets the actual gain.    
    bool SetActualGain(CT_TEL_mBm theGain);


    //Sets the Chromatic Dispersion
    bool SetChromaticDispersion(int32 theChromaticDispersion) ;

    //Gets the Chromatic Dispersion
    int32 GetChromaticDispersion() const ;

    //Sets the Chromatic Dispersion
    bool SetDifferentialGroupDelay(uint16 theDifferentialGroupDelay) ;

    //Gets the Chromatic Dispersion
    uint16 GetDifferentialGroupDelay() const ;


    //Sets the 2nd Order Polarization Mode Dispersion
    bool Set2ndOrderPolarModeDispersion(uint16 the2ndOrderPolarModeDispersion) ;

    //Gets the 2nd Order Polarization Mode Dispersion
    uint16 Get2ndOrderPolarModeDispersion() const ;

    //Sets the State Of Polarization
    bool SetStateOfPolarization(uint32 theStateOfPolarization) ;

    //Gets the State Of Polarization
    uint32 GetStateOfPolarization() const ;


    //Sets the Polarization Dependent Loss.    
    bool SetPolarDependentLoss(CT_TEL_mBm thePolarDependentLoss);

    //Returns the Polarization Dependent Loss.    
    CT_TEL_mBm GetPolarDependentLoss() const;

    //Sets the Q value.    
    bool SetQvalue(CT_TEL_mBm theQvalue);

    //Returns Q value.    
    CT_TEL_mBm GetQvalue() const;

    //Sets the Carrier Frequency Offset.    
    bool SetCarrierFrequencyOffset(CT_TEL_mBm theCarrierFrequencyOffset);

    //Returns the Carrier Frequency Offset.    
    CT_TEL_mBm GetCarrierFrequencyOffset() const;

    //Sets the Signal-to-Noise Ratio.    
    bool SetSignalNoiseRatio(CT_TEL_mBm theSignalNoiseRatio);

    //Returns the Signal-to-Noise Ratio.    
    CT_TEL_mBm GetSignalNoiseRatio() const;

    
    void Reset();

    virtual void Display(FC_Stream& theStream);

protected:
    virtual ostream& WriteObject(ostream& theStream);

    virtual istream& ReadObject(istream& theStream);

    virtual FC_Stream& WriteObjectBinary(FC_Stream& theStream);

    virtual FC_Stream& ReadObjectBinary(FC_Stream& theStream);

private:
    //The total aggregate optical input power in milliBels (0.01 dBm).
    CT_TEL_mBm myTotalInputPower;
    //The total aggregate optical output power in milliBels (0.01 dBm).
    CT_TEL_mBm myTotalOutputPower;
    //The power of the Received Lowest Lane in milliBels (0.01 dBm).
    CT_TEL_mBm myLaneLowReceivedPower;
    //The power of the Received Highest Lane in milliBels (0.01 dBm).
    CT_TEL_mBm myLaneHighReceivedPower;
    //The power of the Transmitted Lowest Lane in milliBels (0.01 dBm).
    CT_TEL_mBm myLaneLowTransmittedPower;
    //The power of the Transmitted Highest Lane in milliBels (0.01 dBm).
    CT_TEL_mBm myLaneHighTransmittedPower;

    //The power of the Received Lane in milliBels (0.01 dBm).
    //CT_TEL_mBm myLaneReceivedPower[CT_NUM_PSX_LANES];
    //The power of the Transmitted Lane in milliBels (0.01 dBm).
    //CT_TEL_mBm myLaneTransmittedPower[CT_NUM_PSX_LANES];
    //The power of the Received Lane in milliBels (0.01 dBm).
    vector<CT_TEL_mBm> myLaneReceivedPower;
    //The power of the Transmitted Lane in milliBels (0.01 dBm).
    vector<CT_TEL_mBm> myLaneTransmittedPower;

    //Indicates a significant change in the input power (1 dBm or greater).
    bool mySignifPowerChange;
    //Indicates a significant change in the output power (1/4 dBm or greater).
    bool mySignifOutputPowerChange;
    //Indicates a significant change in the peer output power (1/4 dBm or greater).
    bool mySignifPeerOutputPowerChange;
    //Indicates a significant change in the peer OMS output power (1/4 dBm or greater).
    bool mySignifPeerOmsOutputPowerChange;
    //Indicates a significant change in the OMS output power (1/4 dBm or greater).
    bool mySignifOmsOutputPowerChange;
    //Indicates a significant change in the Rx Low (Lois) Lane (1/4 dBm or greater).
    bool myRxLoisLaneSignifPowerChange;
    //Indicates a significant change in the Rx Highest Lane (1/4 dBm or greater).
    bool myRxHighLaneSignifPowerChange;
    //Indicates a significant change in the Tx Low (Lois) Lane (1/4 dBm or greater).
    bool myTxLoisLaneSignifPowerChange;
    //Indicates a significant change in the Tx Highest Lane (1/4 dBm or greater).
    bool myTxHighLaneSignifPowerChange;
    //Indicates a significant change in the Rx Lane (1/4 dBm or greater).
    bool myRxLaneSignifPowerChange;
    //Indicates a significant change in the Tx Lane (1/4 dBm or greater).
    bool myTxLaneSignifPowerChange;
    //The current rate
    CT_TEL_mBm myDetectedClockRate;

    //The Most Significant Digits of the PRBS Rx Error Counter
    uint32 myPrbsRxMostSignifCount;
    //The Least Significant Digits of the PRBS Rx Error Counter
    uint32 myPrbsRxLeastSignifCount;
    //The Time associated with the PRBS Rx Error Counter
    uint32 myPrbsRxTimeInterval;
    //The PRBS Rx Losync
    CT_TEL_PrbsSyncStatus myPrbsRxLosync;
    //The PRBS Rx LosyncCount
    uint32 myPrbsRxFirstSyncLosyncCount;
    //Flag indicating when Prbs first goes in Sync
    bool myPrbsRxFirstSync;
    //The total aggregate optical peer output power in milliBels (0.01 dBm).
    CT_TEL_mBm myTotalPeerOutputPower;
    //The total aggregate optical peer OMS output power in milliBels (0.01 dBm).
    CT_TEL_mBm myTotalPeerOmsOutputPower;
    //The total aggregate OMS output power in milliBels (0.01 dBm).
    CT_TEL_mBm myTotalOmsOutputPower;
    //Indicates if the OCM is Dual (true) or Single (false)
    bool myIsDualOcmPresent;
    //The Actual Gain obtained.
    CT_TEL_mBm myActualGain;
    //The Chromatic Dispersion obtained.
    int32 myChromaticDispersion;
    //The Differential Group Delay obtained.
    uint16 myDifferentialGroupDelay;
    //The 2nd Order Polar Mode Dispersion obtained
    uint16 my2ndOrderPolarModeDispersion;
    //The State Of Polarization obtained    
    uint32 myStateOfPolarization;
    //The Polarization Dependent Loss obtained    
    CT_TEL_mBm myPolarDependentLoss;
    //The Q value obtained    
    CT_TEL_mBm myQvalue;
    //The Carrier Frequency Offset obtained    
    CT_TEL_mBm myCarrierFrequencyOffset;
    //The Signal to Noise Ratio obtained    
    CT_TEL_mBm mySignalNoiseRatio;
    
};

#endif /* _INC_MON_OPTSTATUS_3C0FE66F019C_INCLUDED */
