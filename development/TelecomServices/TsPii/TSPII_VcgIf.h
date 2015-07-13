#ifndef _TSPII_VCGIF_H
#define _TSPII_VCGIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  Generic
 AUTHOR   :  Hemant Thakkar/Denham Reynolds - July 2003
 DESCRIPTION:Base class for the hardware independent interface.
             Provides the interface for ports hardware
 MODIFIED :
--------------------------------------------------------------------------*/

#include "CommonTypes/CT_Telecom.h"
#include "TsPii/TSPII_BaseIf.h"
#include "TsPii/TSPII_XcIf.h"


#define TSPII_VCG_MBRS_MAX  672

#define TSPII_UNDEFINED_PROTECTED_VCG_ID -1

enum TSPII_VcgDriverEvent
{
    TSPII_VCGDE_REMOVE_DONE,
    TSPII_VCGDE_EVENTS_END,
};
class TSPII_VcgIf : public TSPII_BaseIf
{
public:

    /* Constructor */                 TSPII_VcgIf(bool theDefault = false);
    virtual                           ~TSPII_VcgIf();
    virtual void                      Reset();

    // -----------------------------------------------------------------------------------
    // Monitor Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint16                    GetNumActiveTxMbrs();
    virtual uint16                    GetNumActiveRxMbrs();
    virtual uint16                    GetTxSeqNbr(uint16 theSeq);
    virtual uint16                    GetRxSeqNbr(uint16 theSeq);
    virtual uint32                    GetRxDiffDelay(uint16 theMbr);
    virtual CT_TEL_VCG_STATE          GetTxState(uint16 theMbr);
    virtual CT_TEL_VCG_STATE          GetRxState(uint16 theMbr);
    virtual bool                      GetLcasDetected();
    virtual bool                      GetLcasRxDetected(); // is LCAS being received?
    virtual uint32                    GetTxTlc();
    virtual uint32                    GetTxPlc();
    virtual uint32                    GetRxTlc();
    virtual uint32                    GetRxPlc();
    virtual uint32                    GetLosAlign();
    virtual uint32                    GetTxFop();
    virtual uint32                    GetRxFop();
    virtual uint32                    GetSeqMisMatch(uint16 theMbr);
    virtual uint32                    GetLosMfAlign(uint16 theMbr);
    virtual uint32                    GetMbrNotDskew(uint16 theMbr);
    virtual bool                      GetActiveVcg();
    virtual bool                      GetForceEvcRefreshAndClearForce();

    // -----------------------------------------------------------------------------------
    // Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                      SetHoldOffTimer(uint32 theTime);
    virtual uint32                    GetHoldOffTimer() const;

    virtual void                      SetWaitToRestoreTimer(uint32 theTime);
    virtual uint32                    GetWaitToRestoreTimer() const;

    virtual void                      SetPlcThres(uint16 theThres);
    virtual uint16                    GetPlcThres() const;

    virtual void                      SetTlcThres(uint16 theThres);
    virtual uint16                    GetTlcThres() const;

    virtual void                      SetDiffDelayThres(uint32 theThres);
    virtual uint32                    GetDiffDelayThres() const;

    virtual void                      SetVcatType(CT_TEL_VCAT_TYPE theType);
    virtual CT_TEL_VCAT_TYPE          GetVcatType() const;

    virtual void                      SetIsConnAsSrc(bool theMode);
    virtual bool                      GetIsConnAsSrc();

    virtual void                      SetIsConnAsDest(bool theMode);
    virtual bool                      GetIsConnAsDest();

    virtual void                      SetLcasEnabled(bool theMode);
    virtual bool                      GetLcasEnabled();

    virtual void                      SetMembers(const vector<uint16> & theTimeSlots);
    virtual const vector<uint16> &    GetMembers();
    virtual void                      SetSrcMembers(const vector<uint16> & theTimeSlots);
    virtual const vector<uint16> &    GetSrcMembers();
    virtual void                      SetSnkMembers(const vector<uint16> & theTimeSlots);
    virtual const vector<uint16> &    GetSnkMembers();
    virtual void                      DoMemberChanges();
    virtual void                      SetProtectedVcgID(int theVcgId, int theVcgSlot);
    virtual int                       GetProtectedVcgID();
    virtual int                       GetProtectedVcgSlot();
    virtual void                      InitVcgTable() {};

    virtual bool                      IsLcasMemberBusy(TSPII_XcRecord theXconn);
    virtual void                      DoDriverEvent(TSPII_VcgDriverEvent theEvent, uint16 thePhyMember, bool isPort2Line);
    virtual string                    DisplayDelayedXc();

    virtual void                      SetRerouteTtp(bool theMode);
    virtual void                      SetActiveVcg(bool isActive) {};

    // -----------------------------------------------------------------------------------
    // STAT Interfaces
    // -----------------------------------------------------------------------------------
    virtual bool                      GetVcgStats(uint32 & theIngressEnqueueDropFrames,
                                                  uint32 & theIngressEnqueueFrames,
                                                  uint32 & theIngressDequeueFrames,
                                                  uint32 & theEgressEnqueueDropFrames,
                                                  uint32 & theEgressEnqueueFrames,
                                                  uint32 & theEgressDequeueFrames);
    virtual bool                      ClearVcgStats();
    virtual void                      DumpVcgStats();

    // -----------------------------------------------------------------------------------
    // Serialization
    // -----------------------------------------------------------------------------------
    virtual FC_Stream &               WriteObjectBinary(FC_Stream & theStream);
    virtual FC_Stream &               ReadObjectBinary(FC_Stream & theStream);
    virtual ostream &                 WriteObject(ostream & theStream);
    virtual istream &                 ReadObject(istream & theStream);

    // -----------------------------------------------------------------------------------
    // Test Menus
    // -----------------------------------------------------------------------------------
    virtual void                      Display(FC_Stream & theStream);
    virtual void                      Display(FC_Stream & theStream, int argc, char ** argv);
    virtual bool                      Set(int argc, char ** argv);
    virtual bool                      Simul(int argc, char ** argv);


    // -----------------------------------------------------------------------------------
    // Exclusive method that Cfg_HwRefreshVcg calls to ensure that all EVC's
    // are in sync with VCG changes
    // -----------------------------------------------------------------------------------
    virtual void                      KickEvcRefresh();

    // VCG resequencing support
    bool getReSequenceNeeded() const;
    virtual void setReSequenceNeeded(bool state);
    virtual bool fixSequenceMisMatch();
    virtual bool  CheckSeqMsMatch();

    // -----------------------------------------------------------------------------------
    //Added to debug how long Automatic Action is taking.
    // -----------------------------------------------------------------------------------
    void SetDebugFlagSet(bool theDebugEnable);
    bool IsDebugFlagSet() const;
    void SetProcessTime(const uint32 theTime);
    void SetBreakdown(const uint32 aPt1, const uint32 aPt2, const uint32 aPt3,
                      const uint32 aPt4, const uint32 aPt5, const uint32 aPt6,
                      const uint32 aPt7, const uint32 aPt8, const uint32 aPt9,
                      const uint32 aPt10);
    void SetProtectVcgBreakdown(const uint32 aPt11, const uint32 aPt12);
    void SetProtectedVcgProcessTime(const uint32 theTime);

protected:

    void                 RefreshGet();
    void                 RefreshSet();
    string               DisplayMembers();
    string               DisplaySrcMembers();
    string               DisplaySnkMembers();
    string               DisplayActualMembers();
    string               DisplayTxSeqNbr();
    string               DisplayRxSeqNbr();
    string               DisplayRxDiffDelay();
    string               DisplayTxState();
    string               DisplayRxState();
    string               DisplaySeqMisMatch();
    string               DisplayLosMfAlign();
    string               DisplayMbrNotDskew();

    // Monitoring attributes
    uint16               itsNumActiveTxMbrs;
    uint16               itsNumActiveRxMbrs;
    uint16               itsTxSeqNbr[TSPII_VCG_MBRS_MAX];
    uint16               itsRxSeqNbr[TSPII_VCG_MBRS_MAX];
    uint32               itsRxDiffDelay[TSPII_VCG_MBRS_MAX];
    CT_TEL_VCG_STATE     itsTxState[TSPII_VCG_MBRS_MAX];
    CT_TEL_VCG_STATE     itsRxState[TSPII_VCG_MBRS_MAX];
    uint32               itsSeqMisMatch[TSPII_VCG_MBRS_MAX];
    uint32               itsLosMfAlign[TSPII_VCG_MBRS_MAX];
    uint32               itsMbrNotDskew[TSPII_VCG_MBRS_MAX];
    bool                 itsLcasDetected;
    bool                 itsLcasRxDetected;
    uint32               itsTxTlc;
    uint32               itsTxPlc;
    uint32               itsRxTlc;
    uint32               itsRxPlc;
    uint32               itsLosAlign;
    uint32               itsTxFop;
    uint32               itsRxFop;
    bool                 itsActive;
    bool                 itsForceEvcRefresh;

    // Stat/Diagnostic attributes
    uint32               itsIngressEnqueueDropFrames;
    uint32               itsIngressEnqueueFrames;
    uint32               itsIngressDequeueFrames;
    uint32               itsEgressEnqueueDropFrames;
    uint32               itsEgressEnqueueFrames;
    uint32               itsEgressDequeueFrames;

    // Configuration attributes
    uint32               itsHoldOffTimer;
    uint32               itsWaitToRestoreTimer;
    uint16               itsPlcThres;
    uint16               itsTlcThres;
    uint32               itsDiffDelayThres;
    CT_TEL_VCAT_TYPE     itsVcatType;
    bool                 itsIsConnAsSrc;
    bool                 itsIsConnAsDest;
    int                  itsProtectedVcgId;
    int                  itsProtectedVcgSlot;
    bool                 itsLcasEnabled;
    bool                 itsRerouteTtp;
    vector<uint16>       itsMembers;
    vector<uint16>       itsSrcMembers;
    vector<uint16>       itsSnkMembers;
    vector<uint16>       itsActualMembers;   //to display the actual member config

    //Added to debug how long Automatic Action is taking.
    bool myDebugFlag;
    uint32 myLastTime;
    uint32 myShortestTime;
    uint32 myLongestTime;
    uint32 myPoint1;
    uint32 myPoint2;
    uint32 myPoint3;
    uint32 myPoint4;
    uint32 myPoint5;
    uint32 myPoint6;
    uint32 myPoint7;
    uint32 myPoint8;
    uint32 myPoint9;
    uint32 myPoint10;
    uint32 myProtectPoint1;
    uint32 myProtectPoint2;

    uint32 myProtectLastTime;
    uint32 myProtectLongestTime;
    uint32 myProtectShortestTime;

    bool   myReSeqNeeded;
    uint32 myReSeqReqTimeStamp;
    uint32 myReSeqStartFixTimeStamp;
    uint32 myReSeqEndTimeStamp;
    uint32 minReSeqEndTime;
    uint32 maxReSeqEndTime;
    uint32 myReSeqExecTime;
    uint32 minReSeqExecTime;
    uint32 maxReSeqExecTime;
    uint32 myReSeqcount;
    bool   myRxSeqFixed;
//    TspiiVcgGroupMemberMap   theVcgGroupMemberMap;
    int    mySeqMsMatchFixCount;
};

#endif // _TSPII_VCGIF_H
