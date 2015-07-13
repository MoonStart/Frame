//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_MACDEFECTS_H
#define MON_MACDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the defects status and transition counts for the 
//GFP layer.
class MON_MacDefects :public MON_Defects
{
public:

    //Constructor.
    MON_MacDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_MacDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;
    bool IsLayerLocked() const;

    bool IsLayerInternalLocked() const;

protected:
    // Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    //The current RfLinkFail state and count.
    bool   myRFLinkFailState;
    uint32 myRFLinkFailCount;

    // True if upper layer Internal is in failure 
    bool myUpperLayerInternalFailTAState;
    uint32 myUpperLayerInternalFailTACount;

    // True if layer Internalis locked (propagated from upper layer)
    bool myInternalLockState;
    uint32 myInternalLockLockCount;

    // True if Fefi Enabled
    bool myFefiState;
    uint32 myFefiCount;

    // True if Lacp Fail Enabled
    bool myLacpFailState;
    uint32 myLacpFailCount;


};

#endif /* MON_MACDEFECTS_H */
