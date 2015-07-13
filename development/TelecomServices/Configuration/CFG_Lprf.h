/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_LPRFOBJECT_H
#define CFG_LPRFOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_DCC_Definitions.h>


#include "CFG_Object.h"


// This object contains all the generic DCC Link Profile
// configuration (i.e., the Lapd Profile).
class CFG_Lprf
: public CFG_Object
{

public:

	//Constructor.
    CFG_Lprf(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Lprf(void);

    // From LAPD Profile
    void SetTransferMode(CT_LPF_TxMode theTransferMode);
    CT_LPF_TxMode GetTransferMode() const;

    void SetRetransmissionCount(uint8 theRetransmissionCount);
    uint8 GetRetransmissionCount() const;

    void SetAckWaitTimer(uint16 theAckWaitTimer);
    uint16 GetAckWaitTimer() const;

    void SetMaxFrameSize(uint16 theMaxFrameSize);
    uint16 GetMaxFrameSize() const;

    void SetFrameCount(uint8 theFrameCount);
    uint8 GetFrameCount() const;

    void SetInactivityTimer(uint16 theInactivityTimer);
    uint16 GetInactivityTimer() const;

    void SetSideAssignment(CT_LPF_Side theSideAssignment);
    CT_LPF_Side GetSideAssignment() const;

    void SetSequenceRange(uint8 theSequenceRange);
    uint8 GetSequenceRange() const;


	//Debug Methods
    virtual void Reset();
    virtual void Display(FC_Stream& theStream);
    virtual FC_CmdProcessor::STATUS Set(int argc, char **argv);

protected:

	//Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    CT_LPF_TxMode     myTransferMode;
    uint8             myRetransmissionCount;
    uint16            myAckWaitTimer;
    uint16            myMaxFrameSize;
    uint8             myFrameCount;
    uint16            myInactivityTimer;
    CT_LPF_Side       mySideAssignment;
    uint8             mySequenceRange;

};

#endif /* CFG_LPRFOBJECT_H */

