//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_MSDEFECTS_H
#define MON_MSDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

enum MON_FAILLAYER_MS_BITMASK
{
    MON_FAILLAYER_MSAIS_BITMASK         = 0x01,
    MON_FAILLAYER_MSINTAIS_BITMASK      = 0x02,
    MON_FAILLAYER_MSPROPAIS_BITMASK     = 0x04,
    MON_FAILLAYER_MS_DEFAULT_BITMASK    = 0xffff
};

//This class contains the defects status and transition counts for the 
//Multiplex Section (MS) layer (or SONET Section).
class MON_MsDefects :public MON_Defects
{
public:

    //Constructor.
    MON_MsDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_MsDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);
    bool GetDefectForMaintSig(CT_TEL_Defect theDefect) const;
    bool IsLayerInDefects() const;
    bool IsLayerInDefectsNTA() const;
    bool IsLayerLocked() const;

    bool IsLayerInternalInDefects() const;
    bool IsLayerInternalLocked() const;

    bool IsLayerInTermLpbk() const;

    bool AisFailLayer() const;
    bool InternalAisFailLayer() const;
    bool PropritaryInternalAisLFailLayer() const;

    bool IsLayerForMaintSigInDefects() const;
    bool IsLayerInternalForMaintSigInDefects() const;

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
    //The current AIS state and Count.
    bool   myAISState;
    uint32 myAISCount;
    //The current Internal AIS-L state and Count.
    bool   myInternalAISLState;
    uint32 myInternalAISLCount;
    //The current Internal AIS-L state and Count.
    bool   myPropritaryInternalAISLState;
    uint32 myPropritaryInternalAISLCount;
    //The current RDI state and Count.
    bool   myRDIState;
    uint32 myRDICount;
    //The current SD-BER state and Count.
    bool   mySdBerState;
    uint32 mySdBerCount;
    //The current SF-BER state and Count.
    bool   mySfBerState;
    uint32 mySfBerCount;
    //The current Reference state and Count.
    bool   myRefState;
    uint32 myRefCount; 

    // True if upper layer Internal Layer is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if upper layer for maintenance signal Internal Layer is in failure 
    bool myUpperLayerForMSInternalFailTAState;
    uint32 myUpperLayerForMSInternalFailTACount;  

    // True if layer Internal Layer is locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockLockCount;

    // True if layer terminal loopbacked (propagated from upper layer)
    bool myTermLpbkState;
    uint32 myTermLpbkCount;

    // The bitmasks that indicates which defects should fail the layer
    uint16 myDefectFailLayerBitMask;   
};

#endif /* MON_MSDEFECTS_H */
