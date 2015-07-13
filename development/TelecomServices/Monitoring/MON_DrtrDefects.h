//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_DRTRDEFECT_H
#define MON_DRTRDEFECT_H

#include "MON_Defects.h"

//This class contains the defects status and transition 
//counts for the DCC Router (DRTR)
class MON_DrtrDefects :public MON_Defects
{
public:

    //Constructor.
    MON_DrtrDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_DrtrDefects(void);

    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;
    bool IsLayerInDefectsNTA() const;
    bool IsLayerLocked() const;

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

    // True if upper layer is in failure (Non Traffic Affecting)
    bool myUpperLayerFailNTAState;
    uint32 myUpperLayerFailNTACount;

    // True if layer is locked (propagated from upper layer)
    bool myLockState;
    uint32 myLockCount;

    //The current Adjancency Rejected state and Count.
    bool   myRejectedAdjancencyState;
    uint32 myRejectedAdjancencyCount;

    //The current Area Address Mismatch state and Count.
    bool   myAreaAddressMismatchState;
    uint32 myAreaAddressMismatchCount;

    //The current Maximum Area Address Mismatch state and Count.
    bool   myMaxAreaAddressMismatchState;
    uint32 myMaxAreaAddressMismatchCount;

    //The current Level 1D atabaseO verload state and Count.
    bool   myL1DatabaseOverloadState;
    uint32 myL1DatabaseOverloadCount;

    //The current Level 2 Database Overload state and Count.
    bool   myL2DatabaseOverloadState;
    uint32 myL2DatabaseOverloadCount;
};

#endif /* MON_DRTRDEFECT_H */
