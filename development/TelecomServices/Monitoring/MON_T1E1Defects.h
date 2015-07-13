//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_T1E1DEFECTS_H
#define MON_T1E1DEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the defects status and transition counts for the 
//T1E1 layer.
class MON_T1E1Defects :public MON_Defects
{
public:

    //Constructor.
    MON_T1E1Defects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_T1E1Defects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;
    bool IsLayerLocked() const;

protected:
    // Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    //The current Los state and Count.
    bool   myLOSState;
    uint32 myLOSCount;
    //The current Lof state and Count.
    bool   myLOFState;
    uint32 myLOFCount;
    //The current Ais state and Count.
    bool   myAISState;
    uint32 myAISCount;
	//The current Ais state and Count.
    bool   myOffFreqState;
    uint32 myOffFreqCount;

    // True if layer is locked 
    bool myLockState;
    uint32 myLockCount;
};

#endif /* MON_T1E1DEFECTS_H */
