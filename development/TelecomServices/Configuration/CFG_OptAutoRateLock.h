/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CFG_OPTAUTORATELOCK_H
#define CFG_OPTAUTORATELOCK_H

#include <CommonTypes/CT_Telecom.h>
#include "CFG_Object.h"
#include "CFG_Definitions.h"

//This object contains all the generic optical configuration for one port.
class CFG_OptAutoRateLock 
: public CFG_Object
{

public:

    //Constructor.
    CFG_OptAutoRateLock(uint32 theIndex);

	//Virtual destructor.
    virtual ~CFG_OptAutoRateLock(void);

    //This method sets the signal type to configure.
    bool SetSignalType(CT_TEL_SignalType theSignalType);

    //This method returns the current signal type to configure.
    CT_TEL_SignalType GetSignalType() const;

    //This method sets the signal rate to configure.
    bool SetSignalRate(CT_TEL_daHz theSignalType);

    //This method returns the current signal type to configure.
    CT_TEL_daHz GetSignalRate() const;

    //This method sets the state of the Auto rate lock down mecanism
    bool SetLockState(CFG_RateLockState theRateLockState);

    //This method returns the state of the Auto rate lock down mecanism
    CFG_RateLockState GetLockState() const;

	//This method sets the side that autorate lock is currently trying
	void SetSide(bool thelockToPort);


    //Debug methods.
    virtual void Reset(void);
    virtual void Display(FC_Stream& theStream);

protected:

    //Serialization methods
    virtual ostream& WriteObject( ostream& theStream );
    virtual istream& ReadObject( istream& theStream );
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

private:

    // The signal type 
    CT_TEL_SignalType mySignalType;
    CT_TEL_daHz mySignalRate;

    // True if the Signal type configured locked with the one we receive
    CFG_RateLockState myRateLockState;

	bool myLockToPortSide;
	uint32 myNumLockAttempts;
};

#endif /* CFG_OPTAUTORATELOCK_H */

