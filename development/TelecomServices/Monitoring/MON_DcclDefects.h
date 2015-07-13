//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_DCCLDEFECTS_H
#define MON_DCCLDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the defects status and transition counts for the 
//DCCL (DCC Link) layer.
class MON_DcclDefects :public MON_Defects
{
public:

    //Constructor.
    MON_DcclDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_DcclDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;
    bool IsLayerInDefectsNTA() const;
    bool IsLayerLocked() const;

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
    
    //The current Link Down state and Count.
    bool   myLinkDownState;
    uint32 myLinkDownCount;

    //The current Link Incomplete state and Count.
    bool   myLinkIncompleteState;
    uint32 myLinkIncompleteCount;
};

#endif /* MON_DCCLDEFECTS_H */
