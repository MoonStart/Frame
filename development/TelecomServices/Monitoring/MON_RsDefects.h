//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_RSDEFECTS_H
#define MON_RSDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

enum MON_FAILLAYER_RS_BITMASK
{
    MON_FAILLAYER_RSLOS_BITMASK         = 0x01,
    MON_FAILLAYER_RSLOF_BITMASK         = 0x02,
    MON_FAILLAYER_RSTLABAIS_BITMASK     = 0x04,
    MON_FAILLAYER_RSGENAIS_BITMASK      = 0x08,
    MON_FAILLAYER_RSTIM_BITMASK         = 0x10,
    MON_FAILLAYER_RSLF_BITMASK          = 0x20,
    MON_FAILLAYER_RSINTLOF_BITMASK      = 0x40,
    MON_FAILLAYER_RSRF_BITMASK          = 0x80,
    MON_FAILLAYER_RS_DEFAULT_BITMASK    = 0xffff
};

//This class contains the defects status and transition counts for the 
//Regenerator Section (RS) layer (or SONET Section).
class MON_RsDefects :public MON_Defects
{
public:

    //Constructor.
    MON_RsDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_RsDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    void GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const;
    bool GetDefectForMaintSig(CT_TEL_Defect theDefect) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool SetLayerFailOnTimEnable(bool theLayerFailOnTimEnable);
    bool IsLayerInDefects() const;
    bool IsLayerInDefectsNTA() const;
    bool IsLayerForMaintSigInDefects() const;
    bool IsLayerInternalForMaintSigInDefects() const;
    bool IsLayerInternalInDefects() const;
    bool IsLayerInternalLocked() const;
    bool IsInternalInPropagateNextLayerDefectsTA() const;

    bool IsLayerLocked() const;
    bool IsConnectedAsSrc() const;
    bool IsConnectedAsDst() const;

    bool GetLocalFault() const;
    bool GetRemoteFault() const;

    bool IsLayerInTermLpbk() const;

    bool LosFailLayer() const;
    bool LofFailLayer() const;
    bool TlabAisFailLayer() const;
    bool GenAisFailLayer() const;
    bool TimFailLayer() const;
    bool LfFailLayer() const;
    bool InternalLofFailLayer() const;
    bool RfFailLayer() const;
    void SetFailLayerBitMask(uint16 theBitMask);

protected:
    // Serialization methods
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

    //The current AIS transmitted state and Count.
    bool myAISTxState;
    uint32 myAISTxCount;
    //The current TLAB AIS transmitted state and Count.
    bool myTlabAISTxState;
    uint32 myTlabAISTxCount;

    //The current out of SONET/SDH frame state and Count.
    bool myOOFState;
    uint32 myOOFCount;
    //The current LOS state and Count.
    bool myLOSState;
    uint32 myLOSCount;
    //The Pii LOS state and Count. The value never overwritten by MON.
    bool myPiiLOSState;
    uint32 myPiiLOSCount;
    //The current LOF state and Count.
    bool myLOFState;
    uint32 myLOFCount;
    //The current TIM state and Count.
    bool myTIMState;
    uint32 myTIMCount;

    //The current TLAB AIS  state and Count.
    bool myTlabAISState;
    uint32 myTlabAISCount;

    //The current GEN AIS  state and Count.
    bool myGenAISState;
    uint32 myGenAISCount;

    //The current internal GEN AIS  state and Count.
    bool myInternalGenAISState;
    uint32 myInternalGenAISCount;

    //The currect facility involved in a connection as the source state and count
    bool myIsConnectedAsSrcState;
    uint32 myIsConnectedAsSrcCount;

    //The currect facility involved in a connection as the destination state and count
    bool myIsConnectedAsDstState;
    uint32 myIsConnectedAsDstCount;


    //Set to true when TIM should fail the layer
    bool myLayerFailOnTimEnable;
    uint32 myLayerFailOnTimCount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if upper layer for maintenance signal Internal is in failure 
    bool myUpperLayerForMSInternalFailTAState;
    uint32 myUpperLayerForMSInternalFailTACount;

    // True if layer Internalis locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockCount;

    // True if upper layer Internal Prop Next Layer is in failure 
    bool myUpperLayerInternalFailPNLTAState;
    uint32 myUpperLayerInternalFailPNLTACount;

    //The current Internal LOF state and Count.
    bool myInternalLOFState;
    uint32 myInternalLOFCount;

    // The current Internal CSF OPU state and count
    bool myInternalCSFOPUState;
    uint32 myInternalCSFOPUCount;

    bool myLocalFaultState;
    uint32 myLocalFaultCount;

    bool myRemoteFaultState;
    uint32 myRemoteFaultCount;

    // True if layer terminal loopbacked (propagated from upper layer)
    bool myTermLpbkState;
    uint32 myTermLpbkCount;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;    
};

#endif /* MON_RSDEFECTS_H */
