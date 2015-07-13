//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_SYNCDEFECTS_H
#define MON_SYNCDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the defects status and transition counts for
//Synchronization (SYNC).
class MON_SyncDefects :public MON_Defects
{
public:

    //Constructor.
    MON_SyncDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_SyncDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;

protected:
    // Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    //The current IsInFreerun State and Count.
    bool   myFreerunState;
    uint32 myFreerunCount;
    //The current IsInHoldover State and Count.
    bool   myHoldoverState;
    uint32 myHoldoverCount;
};

#endif /* MON_SYNCDEFECTS_H */
