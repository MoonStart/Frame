//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_TCMDEFECT_H
#define MON_TCMDEFECT_H

#include "MON_Defects.h"
#include <CommonTypes/CT_OduDefinitions.h>

//This class hold the defect value (AIS, TIM, etc)
//for the TCM layer.
class MON_TcmDefects :public MON_Defects
{
public:

    //Constructor.
    MON_TcmDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_TcmDefects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    void GetDefectStatusSpecial(CT_TEL_Defect theDefect, uint32* theCount, bool* theState, bool theSAFlag) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool SetLayerFailOnTimEnable(bool theLayerFailOnTimEnable);
    bool SetLayerFailOnLtcEnable(bool theLayerFailOnLtcEnable);

    bool IsLayerInDefects() const;
    bool IsLayerForMaintSigInDefects() const;

    bool IsLayerLocked() const;

    bool IsServerLayerFailed() const;

    bool IsLayerInDefectsNTA() const;
    bool IsInPropagateNextLayerDefectsTA() const;
    bool IsLayerInNonPropagateDefectsNTA() const;
    bool IsIgnoreDirectUpperLayerDefects() const;

    bool IsLayerInternalInDefects() const;
    bool IsInternalInPropagateNextLayerDefectsTA() const;

    bool IsLayerInDegrade() const;

    bool  SetLockBitMask(uint8 theBitMask);
    uint8 GetLockBitMask() const;

    bool  SetInternalLockBitMask(uint8 theBitMask);
    uint8 GetInternalLockBitMask() const;

    bool IsLayerInTermLpbk() const;

    bool IsOtuLayerLocked(uint8 theBitMask) const;

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
    bool myUpperLayerFailTAState;
    uint32 myUpperLayerFailTACount;

    bool myUpperLayerFailNTAState;
    uint32 myUpperLayerFailNTACount;

    bool myUpperLayerFailPNLTAState;
    uint32 myUpperLayerFailPNLTACount;

    bool myLockState;
    uint32 myLockCount;    

    bool myLTCState;
    uint32 myLTCCount;

    bool myAISState;
    uint32 myAISCount;

    bool myLCKState;
    uint32 myLCKCount;
    
    bool myOCIState;
    uint32 myOCICount;
    
    bool myTIMState;
    uint32 myTIMCount;

    bool   mySdBerState;
    uint32 mySdBerCount;

    bool myBDIState;
    uint32 myBDICount;

    bool myIAEState;
    uint32 myIAECount;

    bool myBIAEState;
    uint32 myBIAECount;

    bool myLayerFailOnTimEnable;
    bool myLayerFailOnLtcEnable;

    bool   mySnkOnlyModeState;
    uint32 mySnkOnlyModeCount;

    bool   mySrcOnlyModeState;
    uint32 mySrcOnlyModeCount;

    bool   myNimModeState;
    uint32 myNimModeCount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if upper layer Internal Prop Next Layer is in failure 
    bool myUpperLayerInternalFailPNLTAState;
    uint32 myUpperLayerInternalFailPNLTACount;

    // Used to keep track of where the lock was set (OTU or TCM Level).
    uint8  myLockBitMask;
    // Used to keep track of where the internal lock was set (OTU or TCM Level).
    uint8  myInternalLockBitMask;

    // True if upper layer is in degrade
    bool myUpperLayerDegradeState;
    uint32 myUpperLayerDegradeCount;

    // True if layer terminal loopbacked (propagated from upper layer)
    bool myTermLpbkState;
    uint32 myTermLpbkCount;
};

#endif /* MON_TCMDEFECT_H */
