//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_ODUDEFECT_H
#define MON_ODUDEFECT_H

#include "MON_Defects.h"

enum MON_FAILLAYER_ODU_BITMASK
{
    MON_FAILLAYER_ODUAIS_BITMASK         = 0x01,
    MON_FAILLAYER_ODULCK_BITMASK         = 0x02,
    MON_FAILLAYER_ODUOCI_BITMASK         = 0x04,
    MON_FAILLAYER_ODUPLM_BITMASK         = 0x08,
    MON_FAILLAYER_ODUGENAIS_BITMASK      = 0x10,
    MON_FAILLAYER_ODULOOMFI_BITMASK      = 0x20,
    MON_FAILLAYER_ODUTIM_BITMASK         = 0x40,
    MON_FAILLAYER_ODUINTERNALAIS_BITMASK = 0x80,
    MON_FAILLAYER_ODUMSIM_BITMASK        = 0x100,
    MON_FAILLAYER_ODULOFLOM_BITMASK      = 0x200,
    MON_FAILLAYER_ODU_DEFAULT_BITMASK    = 0xffff
};

//This class hold the defect value (AIS, TIM, etc)
//for the ODU layer.
class MON_OduDefects :public MON_Defects
{
public:

    //Constructor.
    MON_OduDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_OduDefects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    void GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool SetLayerFailOnTimEnable(bool theLayerFailOnTimEnable);

    bool IsLayerInDefects() const;
    bool IsLayerForMaintSigInDefects() const;
    bool IsInPropagateNextLayerDefectsTA() const;
    bool IsLayerInDefectsNTA() const;

    bool IsLayerLocked() const;
    bool IsConnectedAsSrc() const;
    bool IsConnectedAsDst() const;

    bool IsLayerInNonPropagateDefectsNTA() const;

    bool IsAdaptionLayerInDefectsTA() const;
    bool IsAdaptionLayerForMaintSigInDefectsTA() const;
    bool IsBDIForcedForDefects() const;
    bool IsBDIForcedForDefectsForMaintSig() const;
    bool IsLayerInternalInDefects() const;
    bool IsLayerInternalForMaintSigInDefects() const;
    bool IsInternalInPropagateNextLayerDefectsTA() const;
    bool IsLayerInternalInDefectsNTA() const;
    bool IsLayerInternalLocked() const;

    bool IsLayerInTermLpbk() const;

    //This method sets the Odu Non Terminating flag of the facility (YES or NO).
    void SetIsOduNonTerm(bool theIsOduTerm);
    //This method returns the Odu Non Terminating flag of the facility.
    bool GetIsOduNonTerm() const;

    bool  SetLockBitMask(uint8 theBitMask);
    uint8 GetLockBitMask() const;

    bool  SetInternalLockBitMask(uint8 theBitMask);
    uint8 GetInternalLockBitMask() const;

    bool IsOtuLayerLocked(uint8 theBitMask) const;
    bool IsAnyTcmLevelLocked(uint8 theBitMask) const;

    bool IsLayerInDegrade() const;
    bool AisFailLayer() const;
    bool OciFailLayer() const;
    bool LckFailLayer() const;
    bool PlmFailLayer() const;
    bool MfiFailLayer() const;
    bool GenAisFailLayer() const;
    bool TimFailLayer() const;
    bool InternalAisFailLayer() const;
    bool MsimFailLayer() const;
    bool LoflomFailLayer() const;
    bool IsOnlyPlmFailLayer() const;
    bool IsFilterPlmDefect() const;
    void SetFailLayerBitMask(uint16 theBitMask);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    //Set to true to indicate that the facility is Odu Non Terminating.
    bool myIsOduNonTerm; 

    // Used to keep track of where the lock was set (i.e., OTU or TCM Level).
    uint8 myLockBitMask;
    // Used to keep track of where the internal lock was set (TCM Level).
    uint8 myInternalLockBitMask;

    // True if upper layer is in failure (Traffic Affecting)
    bool myUpperLayerFailTAState;
    uint32 myUpperLayerFailTACount;

    // True if upper layer is in failure for maintenance signal (Traffic Affecting)
    bool myUpperLayerForMSFailTAState;
    uint32 myUpperLayerForMSFailTACount;

    // True if upper layer is in failure (Non Traffic Affecting)
    bool myUpperLayerFailNTAState;
    uint32 myUpperLayerFailNTACount;

    bool myUpperLayerFailPNLTAState;
    uint32 myUpperLayerFailPNLTACount;

    // True if layer is locked (propagated from upper layer)
    bool myLockState;
    uint32 myLockCount;

    //True if the received SM trace differs from the expected.
    bool myTIMState;

    //Number of TIM defect rising transition.
    uint32 myTIMCount;

    //True if BDI (backward defect indication) is detected.
    bool myBDIState;

    //Number of BDI defect rising transition.
    uint32 myBDICount;

    //True if ODU_AIS is detected.
    bool myAISState;

    //Number of AIS defect rising transition.
    uint32 myAISCount;

    //True if ODU_AIS is detected.
    bool myLCKState;

    //Number of AIS defect rising transition.
    uint32 myLCKCount;

    //True if ODU_AIS is detected.
    bool myOCIState;

    //Number of AIS defect rising transition.
    uint32 myOCICount;

    //True if SD-BER is detected.
    bool   mySdBerState;

    //Number of SD-BER defect rising transition.
    uint32 mySdBerCount;

    //True if SF-BER is detected.
    bool   mySfBerState;

    //Number of SF-BER defect rising transition.
    uint32 mySfBerCount;

    //True if GEN AIS is detected.
    bool   myGenAISState;

    //Number of GEN-AIS defect rising transition.
    uint32 myGenAISCount;   

    //True if MSIM is detected.
    bool   myMSIMState;

    //Number of MSIM defect rising transition.
    uint32 myMSIMCount;

    //True if LOFLOM is detected.
    bool   myLOFLOMState;

    //Number of LOFLOM defect rising transition.
    uint32 myLOFLOMCount;


    //Set to true when TIM should fail the layer
    bool myLayerFailOnTimEnable;

    //The currect facility involved in a connection as the source state and count
    bool myIsConnectedAsSrcState;
    uint32 myIsConnectedAsSrcCount;

    //The currect facility involved in a connection as the destination state and count
    bool myIsConnectedAsDstState;
    uint32 myIsConnectedAsDstCount;

    //The current Internal AIS state and Count.
    bool   myInternalAISState;
    uint32 myInternalAISCount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if upper layer for maintenance signal Internal is in failure 
    bool myUpperLayerForMSInternalFailTAState;
    uint32 myUpperLayerForMSInternalFailTACount;

    // True if upper layer Internal NTA is in failure 
    bool myUpperLayerInternalFailNTAState;
    uint32 myUpperLayerInternalFailNTACount;

    // True if upper layer Internal Prop Next Layer (PNL) TA is in failure 
    bool myUpperLayerInternalFailPNLTAState;
    uint32 myUpperLayerInternalFailPNLTACount;

    // True if layer Internalis locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockCount;

    // True if payload mismatch
    bool myPLMState;
    uint32 myPLMCount;

    // True if layer terminal loopbacked (propagated from upper layer)
    bool myTermLpbkState;
    uint32 myTermLpbkCount;

    // True if upper layer is in degrade
    bool myUpperLayerDegradeState;
    uint32 myUpperLayerDegradeCount;

    // True if upper layer is locked
    bool myUpperLayerLockState;
    uint32 myUpperLayerLockCount;
    
    //True if LOOMFI is detected.
    bool   myLOOMFIState;

    //Number of LOOMFI defect rising transition.
    uint32 myLOOMFICount;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;

    // True if SSF is detected.
    bool mySSFState;
    uint32 mySSFCount;
};

#endif /* MON_ODUDEFECT_H */
