/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_TARPOBJECT_H
#define CFG_TARPOBJECT_H

#include <gdef.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include <vector>

#include "CFG_Object.h"


//This object contains all the TARP configuration.
class CFG_Tarp
: public CFG_Object
{

public:

	//Constructor.
    CFG_Tarp(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_Tarp(void);

    // TARP Parameters

    //Set TARP Flush Timer
    void SetFlushTimer(uint16 theFlushTimer);

    //Get TARP Flush Timer
    uint16 GetFlushTimer() const;

    //Set TARP Entry Timer
    void SetEntryTimer(uint8 theEntryTimer);

    //Get TARP Entry Timer
    uint8 GetEntryTimer() const;

    //Set TARP Type 1 Timer
    void SetType1Timer(uint16 theType1Timer);

    //Get TARP Type 1 Timer
    uint16 GetType1Timer() const;

    //Set TARP Type 2 Timer
    void SetType2Timer(uint16 theType2Timer);

    //Get TARP Type 2 Timer
    uint16 GetType2Timer() const;

    //Set TARP Type 3 Timer
    void SetType3Timer(uint16 theType3Timer);

    //Get TARP Type 3 Timer
    uint16 GetType3Timer() const;

    //Set TARP Type 4 Timer
    void SetType4Timer(uint16 theType4igTimer);

    //Get TARP Type 4 Timer
    uint16 GetType4Timer() const;

    //Set TARP Protocol Address
    void SetProtocolAddr(uint8 theProtocolAddr);

    //Get TARP Protocol Address
    uint8 GetProtocolAddr() const;

    //Set TARP Reset Sequence Number
    void SetResetSequenceCounter(uint8 theResetSequenceCounter);

    //Get TARP Reset Sequence Number
    uint8 GetResetSequenceCounter() const;

    //Set TARP Lifetime Hops
    void SetLifetimeHops(uint16 theLifetimeHops);

    //Get TARP Lifetime Hops
    uint16 GetLifetimeHops() const;

    //Set TARP Flush Count
    void SetFlushCounter( uint32 theFlushCounter );

    //Get TARP Flush Count
    uint32 GetFlushCounter( ) const;

    //This method is used to Enable the Dcc TARP.
    void SetDCCTarpEnabled(bool theDCCTarpEnabled);

    //This method returns the state of the Dcc TARP.
    bool GetDCCTarpEnabled() const;

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

    uint16 myFlushTimer;
    uint8  myEntryTimer;
    uint16 myType1Timer;
    uint16 myType2Timer;
    uint16 myType3Timer;
    uint16 myType4Timer;
    uint8  myProtocolAddr;
    uint8  myResetSequenceCounter;
    uint16 myLifetimeHops;
    uint32 myFlushCounter;
    bool   myTarpEnabled;
};

#endif /* CFG_TARPOBJECT_H */

