//Copyright(c) Tellabs Transport Group. All rights reserved
#ifndef MON_ALTVCGDEFECTS_H
#define MON_ALTVCGDEFECTS_H

#include "MON_Defects.h"

#include <CommonTypes/CT_Telecom.h>

//This class contains the defects status and transition counts for the 
//Alternate VCG layer.
class MON_AltVcgDefects :public MON_Defects
{
public:

    //Constructor.
    MON_AltVcgDefects(uint32 theIndex);

    //Virtual destructor.
    virtual ~MON_AltVcgDefects(void);

    //Debug methods
    void Reset();
    virtual void Display(FC_Stream& theStream);

    //Returns the status and count of the defect given in argument.
    void GetDefectStatus(CT_TEL_Defect theDefect, uint32* theCount, bool* theState) const;
    bool SetDefectStatus(CT_TEL_Defect theDefect, bool theState, bool theTransition);

    bool IsLayerInDefects() const;
    
    bool IsConnectedAsSrc() const;
    bool IsConnectedAsDst() const;

protected:
    // Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:
    //The current TX TLC (total loss of capacity) state and Count.
    bool myTX_TLCState;
    uint32 myTX_TLCCount;
    //The current TX PLC (partial loss of capacity) state and Count.
    bool myTX_PLCState;
    uint32 myTX_PLCCount;
    //The current RX TLC (total loss of capacity) state and Count.
    bool myRX_TLCState;
    uint32 myRX_TLCCount;
    //The current RX PLC (partial loss of capacity) state and count.
    bool myRX_PLCState;
    uint32 myRX_PLCCount;
    //The current LOS Alignment state and count.  
    bool myLOS_AlignState;
    uint32 myLOS_AlignCount;
    //The current LOS MultiFrame Alignment state and count.  
    bool myLOS_MF_AlignState;
    uint32 myLOS_MF_AlignCount;
    //The current TX FOP (failure of protocol) state and Count.
    bool myTX_FOPState;
    uint32 myTX_FOPCount;
    //The current RX FOP (failure of protocol) state and Count.
    bool myRX_FOPState;
    uint32 myRX_FOPCount;
    //The current Sequence MisMatch state and count.
    bool mySeqMisMatchState;
    uint32 mySeqMisMatchCount;
    //The current MND (Member Not De-Skewable) state and count.
    bool myMbrNotDeSkewState;
    uint32 myMbrNotDeSkewCount;
    //The currect VCG involved in a connection as the source state and count
    bool myIsConnectedAsSrcState;
    uint32 myIsConnectedAsSrcCount;
    //The currect VCG involved in a connection as the destination state and count
    bool myIsConnectedAsDstState;
    uint32 myIsConnectedAsDstCount;

};

#endif /* MON_ALTVCGDEFECTS_H */
