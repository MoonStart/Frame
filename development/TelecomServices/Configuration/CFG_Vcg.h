/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_VCGOBJECT_H
#define CFG_VCGOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_Telecom.h>
#include <list>

#include "CFG_Object.h"


//This object contains all the virtual concatenation
// configuration for one port.
class CFG_Vcg
: public CFG_Object
{

public:

	//Constructor.
    CFG_Vcg(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Vcg(void);

    // Set Value of Hold Off Timer.
    bool SetHoldOffTmr(uint32 theHoldOffTmr);

    // Get Value of Hold Off Timer.
    uint32 GetHoldOffTmr() const;

    // Set Value of Wait to Restore Timer
    bool SetWaitToRetoreTmr(uint32 theWaitToRetoreTmr);

    // Get Value of Wait to Restore Timer
    uint32 GetWaitToRetoreTmr() const;

    // Set Partial Loss of Capacity Threshold
    bool SetPartialLossCpyTH(uint32 thePartialLossCpyTH);

    // Get Partial Loss of Capacity Threshold
    uint32 GetPartialLossCpyTH() const;

    // Set Total Loss of Capacicty Threshold
    bool SetTotalLossCpyTH(uint32 theTotalLossCpyTH);

    // Get Total Loss of Capacicty Threshold
    uint32 GetTotalLossCpyTH() const;

    // Set Differential Delay
    bool SetDiffDelay(uint32 theDiffDelay);
  
    // Get Differential Delay
    uint32 GetDiffDelay() const;

    // This method allows specifying if the Vcg is involved in a 
    // connection as the source of a connection (according to the facilities 
    // perspective of the circuit toward the interior of the card)
    bool SetIsConnectedAsSrc(bool theState);

    // This method returns whether the Vcg is involved in a 
    // connection as the source of a connection
    bool GetIsConnectedAsSrc() const;

    // This method allows specifying if the Vcg is involved in a 
    // connection as the destination of a connection (according to the facilities 
    // perspective of the circuit toward the interior of the card)
    bool SetIsConnectedAsDest(bool theState);

    // This method returns whether the Vcg is involved in a 
    // connection as the destination of a connection
    bool GetIsConnectedAsDest() const;

    // Set virtual concatenation type
    void SetVcatType(CT_TEL_VCAT_TYPE theVcatType);

    //Get virtual concatenation type
    CT_TEL_VCAT_TYPE GetVcatType() const;

    // Set Index of Protected VCG (on other card).
    bool SetProtectVcgIdx(uint8 theProtectVcgIdx);
  
    // Get Index of Protected VCG (on other card).
    uint8 GetProtectVcgIdx() const;

    // Set Slot of Protected VCG (on other card).
    bool SetProtectVcgSlot(CT_SlotId theProtectVcgSlot);
  
    // Get Slot of Protected VCG (on other card).
    CT_SlotId GetProtectVcgSlot() const;

    // Set list of ids of TTPs to support the VCG
    void SetTTPList(vector<uint16>& theTTPList);

    // Get list of ids of TTPs used to support the VCG
    const vector<uint16>& GetTTPList();

    // Set list of Source TTPs 
    void SetSourceTTPList(vector<uint16>& theTTPList);

    // Get list of Source TTPs
    const vector<uint16>& GetSourceTTPList();

    // Set list of Sink TTPs
    void SetSinkTTPList(vector<uint16>& theTTPList);

    // Get list of Sink TTPs
    const vector<uint16>& GetSinkTTPList();

    // Whether the VCG is provisioned (or not)
    void SetIsProvisioned(bool theProvisioned);
    bool GetIsProvisioned() const;

    // Whether the LCAS is enabled (or not)
    void SetLcasEnabled(bool theLcasEnabled);
    bool GetLcasEnabled() const;

    // VCG Locked
    void SetLayerLocked(bool theState);
    bool GetLayerLocked() const;

    //Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

    //Added to debug how long Automatic Action is taking.
//    void SetDebugFlagSet(bool theDebugEnable);
//    bool IsDebugFlagSet() const;
//    void SetProcessTime(const uint32 theTime);
//    void SetBreakdown(const uint32 aPt1, const uint32 aPt2, const uint32 aPt3,
//                      const uint32 aPt4, const uint32 aPt5, const uint32 aPt6,
//                      const uint32 aPt7);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    
    // Current Value of Hold Off Timer.
    uint32 myHoldOffTmr;

    // Current Value of Wait to Restore Timer.
    uint32 myWaitToRetoreTmr;

    // Current value of Partial Loss of Capacity Threshold.
    uint32 myPartialLossCpyTH;

    // Current value of Total Loss of Capacicty Threshold.
    uint32 myTotalLossCpyTH;

    // Current value of Differential Delay.
    uint32 myDiffDelay;

    // Is the facility involved in a connection as the source.
    bool myIsConnectedAsSrc;
   
    // Is the facility involved in a connection as the destination
    bool myIsConnectedAsDest;

    // Whether the VCG is provisioned (or not)
    bool myIsProvisioned;
    
    // Current value of Virtual concatenation type.
    CT_TEL_VCAT_TYPE myVcatType;

    // Index of Protected VCG (on other card).
    uint8 myProtectVcgIdx;

    // Slot Id of Protected VCG (on other card)
    CT_SlotId myProtectVcgSlot;

    // Is LCAS enabled on this VCG.
    bool myLcasEnabled;

    // List of TTP ids that make up this VCG.
    vector<uint16> myTTPList;
    vector<uint16> mySourceTTPList;
    vector<uint16> mySinkTTPList;

    // VCG Locked
    bool myLayerLocked;

    //Added to debug how long Automatic Action is taking.
//    bool myDebugFlag;
//    uint32 myLastTime;
//    uint32 myShortestTime;
//    uint32 myLongestTime;
//    uint32 myPoint1;
//    uint32 myPoint2;
//    uint32 myPoint3;
//    uint32 myPoint4;
//    uint32 myPoint5;
//    uint32 myPoint6;
//    uint32 myPoint7;

};

#endif /* CFG_VCGOBJECT_H */

