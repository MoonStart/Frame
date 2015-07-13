//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_GFPDEFECTS_H
#define MON_GFPDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

enum MON_FAILLAYER_GFP_BITMASK
{
    MON_FAILLAYER_GFPLF_BITMASK         = 0x01,
    MON_FAILLAYER_GFPRF_BITMASK         = 0x02,   
    MON_FAILLAYER_GFPFEFI_BITMASK       = 0x04,     
    MON_FAILLAYER_GFPCSFFEFI_BITMASK    = 0x08, 
    MON_FAILLAYER_GFPLINKFAILRX_BITMASK = 0x10,    
    MON_FAILLAYER_GFPCSFLOS_BITMASK     = 0x20,    
    MON_FAILLAYER_GFPLOFD_BITMASK       = 0x40,
    MON_FAILLAYER_GFPPLM_BITMASK        = 0x80,   
    MON_FAILLAYER_GFPCSFLOSYNC_BITMASK  = 0x100,  
    MON_FAILLAYER_GFPCSFFDI_BITMASK     = 0x200, 
    MON_FAILLAYER_GFPCSFRDI_BITMASK     = 0x400, 
    MON_FAILLAYER_GFPUPPERLAYER_BITMASK = 0x800, 
    MON_FAILLAYER_GFP_DEFAULT_BITMASK   = 0xffff
};

//This class contains the defects status and transition counts for the 
//GFP layer.
class MON_GfpDefects :public MON_Defects
{
public:

    //Constructor.
    MON_GfpDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_GfpDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);
    virtual bool GetDefectForMaintSig(CT_TEL_Defect theDefect) const;

    bool IsLayerInDefects() const;
    bool IsLayerLocked() const;

    bool LfFailLayer() const;
    bool RfFailLayer() const;
    bool FefiFailLayer() const;
    bool CsfFefiFailLayer() const;
    bool LinkFailRxFailLayer() const;
    bool CsfLosFailLayer() const;
    bool CsfLosyncFailLayer() const;
    bool LofdFailLayer() const;
    bool PlmFailLayer() const;
    bool CsfFdiFailLayer() const;
    bool CsfRdiFailLayer() const;
    
    void SetFailLayerBitMask(uint16 theBitMask);

    bool IsLayerInternalLocked() const;

    bool IsLayerForMaintSigInDefects() const;    

protected:
    // Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    // True if upper layer for maintenance signal is in failure (Traffic Affecting)
    bool myUpperLayerForMSFailTAState;
    uint32 myUpperLayerForMSFailTACount;
    
    //The current Lofd state and Count.
    bool   myLOFDState;
    uint32 myLOFDCount;
    //The current Plm state and Count.
    bool   myPLMState;
    uint32 myPLMCount;
    //The current CsfLos state and Count.
    bool   myCsfLosState;
    uint32 myCsfLosCount;
    //The current SD-BER state and Count.
    bool   myCsfLosyncState;
    uint32 myCsfLosyncCount;
    //The current Virtual LOFD state and Count.
    bool   myVirtualLOFDState;
    uint32 myVirtualLOFDCount;
    //The current CsfRfLinkFail state and count.
    bool   myCsfRFLinkFailState;
    uint32 myCsfRFLinkFailCount;
    //The current CsfRfOffline state and count.  
    bool   myCsfRFOfflineState;
    uint32 myCsfRFOfflineCount;
    //The current CsfRfAutoNegFail state and count.  
    bool   myCsfRFAutoNegFailState;
    uint32 myCsfRFAutoNegFailCount;
    //The current CsfLinkFailRx state and count.  
    bool   myCsfLinkFailRxState;
    uint32 myCsfLinkFailRxCount;
    //The current RfLinkFail state and count.
    bool   myRFLinkFailState;
    uint32 myRFLinkFailCount;
    //The current RfOffline state and count.  
    bool   myRFOfflineState;
    uint32 myRFOfflineCount;
    //The current RfAutoNegFail state and count.  
    bool   myRFAutoNegFailState;
    uint32 myRFAutoNegFailCount;
    //The current LinkFailRx state and count.  
    bool   myLinkFailRxState;
    uint32 myLinkFailRxCount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerForMSInternalFailTAState;
    uint32 myUpperLayerForMSInternalFailTACount;
    
    // True if layer Internalis locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockLockCount;

    // True if Fefi Enabled
    bool myFefiState;
    uint32 myFefiCount;

    // True if CSF Fefi Enabled
    bool myCsfFefiState;
    uint32 myCsfFefiCount;

    // True if CSF Fdi Enabled
    bool myCsfFdiState;
    uint32 myCsfFdiCount;
    // True if CSF Rdi Enabled
    bool myCsfRdiState;
    uint32 myCsfRdiCount;

    bool myCsfAnfState;
    uint32 myCsfAnfCount;

    //The current Loss of Alignment state and Count.
    bool   myLosAlignState;
    uint32 myLosAlignCount;
    //The current Sequence MisMatch state and Count.
    bool   mySeqMisMatchState;
    uint32 mySeqMisMatchCount;
    //The current Core Hec state and Count.
    bool   myCoreHecState;
    uint32 myCoreHecCount;
    //The current Pli state and Count.
    bool   myPliState;
    uint32 myPliCount;
    
    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;
};

#endif /* MON_GFPDEFECTS_H */
