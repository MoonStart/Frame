//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_HOPDEFECTS_H
#define MON_HOPDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the defects status and transition counts for the 
//HOP (high order path) layer (or SONET Path).
class MON_HopDefects :public MON_Defects
{
public:

    //Constructor.
    MON_HopDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_HopDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;
    bool IsLayerInDefectsNTA() const;
    bool IsLayerLocked() const;

    bool IsLayerInternalInDefects() const;
    bool IsLayerInternalLocked() const;

    bool IsConnectedAsSrc() const;
    bool IsConnectedAsDst() const;

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

    // True if upper layer is in failure (Non Traffic Affecting)
    bool myUpperLayerFailNTAState;
    uint32 myUpperLayerFailNTACount;

    // True if layer is locked (propagated from upper layer)
    bool myLockState;
    uint32 myLockCount;
    
    //The current AIS state and Count.
    bool   myAISState;
    uint32 myAISCount;
    //The current LOP state and Count.
    bool   myLOPState;
    uint32 myLOPCount;
    //The current UNEQ state and Count.
    bool   myUNEQState;
    uint32 myUNEQCount;
    //The current PLM state and Count.
    bool   myPLMState;
    uint32 myPLMCount;
    //The current TIM state and Count.
    bool   myTIMState;
    uint32 myTIMCount;
    //The current RDI state and Count.
    bool   myRDIState;
    uint32 myRDICount;
    //The current SD-BER state and Count.
    bool   mySdBerState;
    uint32 mySdBerCount;
    //The current SF-BER state and Count.
    bool   mySfBerState;
    uint32 mySfBerCount;

    //The currect hop involved in a connection as the source state and count
    bool myIsConnectedAsSrcState;
    uint32 myIsConnectedAsSrcCount;

    //The currect hop involved in a connection as the destination state and count
    bool myIsConnectedAsDstState;
    uint32 myIsConnectedAsDstCount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if layer Internalis locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockLockCount;

};

#endif /* MON_HOPDEFECTS_H */
