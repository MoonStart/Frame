//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_OTUDEFECT_H
#define MON_OTUDEFECT_H

#include "MON_Defects.h"

enum MON_FAILLAYER_OTU_BITMASK
{
    MON_FAILLAYER_OTUAIS_BITMASK        = 0x01,
    MON_FAILLAYER_OTULOF_BITMASK        = 0x02,
    MON_FAILLAYER_OTULOMF_BITMASK       = 0x04,
    MON_FAILLAYER_OTUFECM_BITMASK       = 0x08,
    MON_FAILLAYER_OTUTIM_BITMASK        = 0x10,
    MON_FAILLAYER_OTU_DEFAULT_BITMASK   = 0xffff
};

//This class contains the defects status and transition 
//counts for the Optical Transport Unit (OTU)
class MON_OtuDefects :public MON_Defects
{
public:

    //Constructor.
    MON_OtuDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OtuDefects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    void GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool SetLayerFailOnTimEnable(bool theLayerFailOnTimLayerEnable);

    bool IsLayerInDefects() const;
    bool IsLayerForMaintSigInDefects() const;
    bool IsLayerInDefectsNTA() const;
    bool IsLayerLocked() const;

    bool IsLayerInternalInDefects() const;
    bool IsLayerInternalForMaintSigInDefects() const;
    bool IsLayerInternalLocked() const;
    bool IsInternalInPropagateNextLayerDefectsTA() const;

    bool IsLayerInNonPropagateDefectsNTA() const;
    bool IsLayerForMaintSigInNonPropagateDefectsNTA() const;

    bool IsLayerInTermLpbk() const;

    bool IsLayerInDegrade() const;

    bool IsMateLayerInDefects() const;

    bool AisFailLayer() const;
    
    bool LofFailLayer() const;

    bool LomfFailLayer() const;

    bool FecmFailLayer() const;

    bool TimFailLayer() const;

    void SetFailLayerBitMask(uint16 theBitMask);
    
    // Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // True if upper layer is in failure (Traffic Affecting)
    bool myUpperLayerFailTAState;
    uint32 myUpperLayerFailTACount;

    // True if upper layer for maintenance signal is in failure (Traffic Affecting)
    bool myUpperLayerForMSFailTAState;
    uint32 myUpperLayerForMSFailTACount;

    // True if upper layer is in failure (Non Traffic Affecting)
    bool myUpperLayerFailNTAState;
    uint32 myUpperLayerFailNTACount;

    // True if layer is locked (propagated from upper layer)
    bool myLockState;
    uint32 myLockCount;

    //True if OTU frame is lost.
    bool myLOFState;

    // Number of LOF defect rising transition.
    uint32 myLOFCount;

    //True if OTU multiframe is lost.
    bool myLOMFState;

    // Number of LOMF defect rising transition.
    uint32 myLOMFCount;

    //True if OTU FEC mismatch (FECM) has occurred.
    bool myFECMState;

    // Number of FECM defect rising transition.
    uint32 myFECMCount;

    //True if the received PM trace differs from the expected.
    bool myTIMState;

    //Number of TIM defect rising transition.
    uint32 myTIMCount;

    //True if BDI (backward defect indication) is detected.
    bool myBDIState;

    //Number of BDI defect rising transition.
    uint32 myBDICount;

    //True if IAE (Incoming Alignment Error) is detected.
    bool myIAEState;

    //Number of IAE defect rising transition.
    uint32 myIAECount;

    //A PN-11 pattern (OTU-AIS) is detected in the OTU framing.
    //(INTERNAL USE ONLY)
    bool myAISState;

    //Number of AIS defect rising transition.
    //(INTERNAL USE ONLY)
    uint32 myAISCount;

    //True if SD-BER is detected.
    bool   mySdBerState;

    //Number of Dispersion Comp Init defect rising transition.
    uint32 myDispCompInitCount;

    //True if Dispersion Comp Init is detected.
    bool   myDispCompInitState;

    //Number of SD-BER defect rising transition.
    uint32 mySdBerCount;

    //Set to true when TIM should fail the layer
    bool myLayerFailOnTimEnable;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if upper layer for maintenance signal Internal is in failure 
    bool myUpperLayerForMSInternalFailTAState;
    uint32 myUpperLayerForMSInternalFailTACount;

    // True if layer Internalis locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockLockCount;

    // True if upper layer Internal Prop Next Layer is in failure 
    bool myUpperLayerInternalFailPNLTAState;
    uint32 myUpperLayerInternalFailPNLTACount;

    // True if layer terminal loopbacked (propagated from upper layer)
    bool myTermLpbkState;
    uint32 myTermLpbkCount;

    // True if Mate Defect is found
    bool myMateDefectState;
    uint32 myMateDefectCount;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;
};

#endif /* MON_OTUDEFECT_H */
