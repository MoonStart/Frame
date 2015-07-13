//Copyright(c) Tellabs Transport Group. All rights reserved

#include "../CFG_OptAutoRateLock.h"
#include <BaseClass/FC_TextStream.h>

CFG_OptAutoRateLock::CFG_OptAutoRateLock(uint32 theIndex):
    CFG_Object(theIndex),
    mySignalType(CT_TEL_SIGNAL_UNKNOWN),
    mySignalRate(0),
    myRateLockState(CFG_RATE_DISABLED),
	myLockToPortSide(true),
	myNumLockAttempts(0)
{
}

CFG_OptAutoRateLock::~CFG_OptAutoRateLock()
{
}

bool CFG_OptAutoRateLock::SetSignalType(CT_TEL_SignalType theSignalType)
{
    bool hasChanged = false;
    if(mySignalType != theSignalType)
    {
        mySignalType = theSignalType;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_SignalType CFG_OptAutoRateLock::GetSignalType() const
{
    return mySignalType;
}

bool CFG_OptAutoRateLock::SetSignalRate(CT_TEL_daHz theSignalType)
{
    bool hasChanged = false;
    if(mySignalRate != theSignalType)
    {
        mySignalRate = theSignalType;
        hasChanged = true;
    }
    return hasChanged;
}

CT_TEL_daHz CFG_OptAutoRateLock::GetSignalRate() const
{
    return mySignalRate;
}

bool CFG_OptAutoRateLock::SetLockState(CFG_RateLockState theRateLockState)
{
    bool hasChanged = false;
    if(myRateLockState != theRateLockState)
    {
        myRateLockState = theRateLockState;
        hasChanged = true;
    }
    return hasChanged;
}

CFG_RateLockState CFG_OptAutoRateLock::GetLockState() const
{
    return myRateLockState;
}

void CFG_OptAutoRateLock::SetSide(bool thelockToPort)
{
	if (myLockToPortSide != thelockToPort)
		myNumLockAttempts++;

	myLockToPortSide = thelockToPort;
	
}

ostream& CFG_OptAutoRateLock::WriteObject( ostream& theStream )
{
	CFG_Object::WriteObject(theStream);
    uint8 aSignalType = mySignalType;
    theStream   << FC_InsertVar(aSignalType);
    theStream   << FC_InsertVar(mySignalRate);
    uint8 aRateLockState = myRateLockState;
    theStream   << FC_InsertVar(aRateLockState);
	theStream   << FC_InsertVar(myLockToPortSide);
	theStream   << FC_InsertVar(myNumLockAttempts);
    return theStream;

}

istream& CFG_OptAutoRateLock::ReadObject( istream& theStream )
{
	CFG_Object::ReadObject(theStream);
    uint8 aSignalType = 0;
    theStream   >> FC_ExtractVar(aSignalType);
    mySignalType = (CT_TEL_SignalType) aSignalType;
    theStream   >> FC_ExtractVar(mySignalRate);
    uint8 aRateLockState = 0;
    theStream   >> FC_ExtractVar(aRateLockState);
    myRateLockState = (CFG_RateLockState) aRateLockState;
	theStream   >> FC_ExtractVar(myLockToPortSide);
	theStream   >> FC_ExtractVar(myNumLockAttempts);
    return theStream;

}

FC_Stream& CFG_OptAutoRateLock::WriteObjectBinary( FC_Stream& theStream )
{
    CFG_Object::WriteObjectBinary(theStream);
    theStream   << (uint8)mySignalType;
    theStream   << mySignalRate;
    theStream   << (uint8)myRateLockState;
	theStream   << myLockToPortSide;
	theStream   << myNumLockAttempts;
    return theStream;

}

FC_Stream& CFG_OptAutoRateLock::ReadObjectBinary( FC_Stream& theStream ) 
{
    CFG_Object::ReadObjectBinary(theStream);
    uint8 aSignalType = 0;
    theStream   >> aSignalType;
    mySignalType = (CT_TEL_SignalType) aSignalType;
    theStream   >> mySignalRate;
    uint8 aRateLockState = 0;
    theStream   >> aRateLockState;
    myRateLockState = (CFG_RateLockState) aRateLockState;
	theStream   >> myLockToPortSide;
	theStream   >> myNumLockAttempts;
    return theStream;

}

void CFG_OptAutoRateLock::Reset()
{
    // Initialize all attributes to default values.
    mySignalType = CT_TEL_SIGNAL_UNKNOWN;
    myRateLockState = CFG_RATE_DISABLED;
    mySignalRate = 0;
	myLockToPortSide = true;
    myNumLockAttempts = 0;
}

void CFG_OptAutoRateLock::Display( FC_Stream& theStream )
{
    theStream   << "OPT LOCK - Signal Type                      = " << DISPLAY_SIGNAL_TYPE(mySignalType) << endl;
    theStream   << "OPT LOCK - Signal Rate (DaHz)               = " << mySignalRate << endl;
    theStream   << "OPT LOCK - Locked state                     = " << DISPLAY_RATE_LOCK_STATE(myRateLockState) << endl;
	if (myLockToPortSide)
	    theStream   << "OPT LOCK - Side                             = " << "Port" << endl;
	else
        theStream   << "OPT LOCK - Side                             = " << "Line" << endl;

	theStream   << "OPT LOCK - Attempts At Lock                 = " << myNumLockAttempts << endl;

}
