// Copyright(c) Tellabs Transport Group. All rights reserved

#include "../MON_SyncStatus.h"
#include <string.h>
#include <BaseClass/FC_TextStream.h>


MON_SyncStatus::MON_SyncStatus(uint32 theIndex):
    MON_Object(theIndex)
{
    Reset();
}

MON_SyncStatus::~MON_SyncStatus(void)
{
    // Nothing to do for now.

}

CT_TEL_ClkSelState MON_SyncStatus::GetCurrentState() const
{
    return myCurrentState;
}

bool MON_SyncStatus::SetCurrentState(CT_TEL_ClkSelState theCurrentState)
{
    bool hasChanged = false;
    if (!(myCurrentState == theCurrentState))
    {
        myCurrentState = theCurrentState;
        hasChanged = true;
    }

    return hasChanged;
}

void MON_SyncStatus::Reset(void)
{
    MON_Object::Reset();
    myCurrentState  = CT_TEL_CLKSEL_STATE_FREERUN;
    myFreerunSsm    = CT_RxSsm_SMC;
	myClockMode     = CT_TEL_CLKMODE_UNKNOWN;
	myMateClockMode = CT_TEL_CLKMODE_UNKNOWN;
}


CT_FAC_RxSsm MON_SyncStatus::GetFreerunSsm() const
{
    return myFreerunSsm;
}

bool MON_SyncStatus::SetFreerunSsm(CT_FAC_RxSsm theFreerunSsm)
{
    bool hasChanged = false;
    if (!(myFreerunSsm == theFreerunSsm))
    {
        myFreerunSsm = theFreerunSsm;
        hasChanged = true;
    }

    return hasChanged;
}

CT_TEL_ClkMode MON_SyncStatus::GetClockMode() const
{
	return myClockMode;
}

bool MON_SyncStatus::SetClockMode(CT_TEL_ClkMode theClockMode)
{
	bool hasChanged = false;
    if (!(myClockMode == theClockMode))
    {
	    myClockMode = theClockMode;
		hasChanged = true;
	}
	
	return hasChanged;
}

CT_TEL_ClkMode MON_SyncStatus::GetMateClockMode() const
{
	return myMateClockMode;
}

bool MON_SyncStatus::SetMateClockMode(CT_TEL_ClkMode theMateClockMode)
{
	bool hasChanged = false;
    if (!(myMateClockMode == theMateClockMode))
    {
	    myMateClockMode = theMateClockMode;
		hasChanged = true;
	}
	
	return hasChanged;
}

ostream& MON_SyncStatus::WriteObject( ostream& theStream )
{

    MON_Object::WriteObject(theStream);
    uint32 aCurrentState = myCurrentState;
    theStream   << FC_InsertVar(aCurrentState);
    uint32 aSsm = (uint32) myFreerunSsm;
    theStream << FC_InsertVar(aSsm);
	uint32 aClockMode = myClockMode;
    theStream << FC_InsertVar(aClockMode);
	uint32 aMateClockMode = myMateClockMode;
    theStream << FC_InsertVar(aMateClockMode);
    return theStream;
}

istream& MON_SyncStatus::ReadObject( istream& theStream )
{
    MON_Object::ReadObject(theStream);
 
    uint32 aCurrentState = 0;
    theStream   >> aCurrentState;
    myCurrentState = (CT_TEL_ClkSelState)aCurrentState;
    uint32 aSsm;
    theStream >> FC_ExtractVar(aSsm);
    myFreerunSsm = (CT_FAC_RxSsm) aSsm;
	uint32 aClockMode;
	theStream >> FC_ExtractVar(aClockMode);
	myClockMode = (CT_TEL_ClkMode) aClockMode;
	uint32 aMateClockMode;
	theStream >> FC_ExtractVar(aMateClockMode);
	myMateClockMode = (CT_TEL_ClkMode) aMateClockMode;
    return theStream;

}

FC_Stream& MON_SyncStatus::WriteObjectBinary( FC_Stream& theStream )
{
    MON_Object::WriteObjectBinary(theStream);
    theStream << (uint32)myCurrentState;
    uint32 aSsm = (uint32) myFreerunSsm;
    theStream << aSsm;
	uint32 aClockMode = (uint32)myClockMode;
	theStream << aClockMode;
	uint32 aMateClockMode = (uint32)myMateClockMode;
	theStream << aMateClockMode;
    return theStream;

}

FC_Stream& MON_SyncStatus::ReadObjectBinary( FC_Stream& theStream ) 
{
    MON_Object::ReadObjectBinary(theStream);

    uint32 aCurrentState = 0;
    theStream   >> aCurrentState;
    myCurrentState = (CT_TEL_ClkSelState)aCurrentState;
    uint32 aSsm;
    theStream >> aSsm;
    myFreerunSsm = (CT_FAC_RxSsm) aSsm;
	uint32 aClockMode;
	theStream >> aClockMode;
	myClockMode = (CT_TEL_ClkMode)aClockMode;
	uint32 aMateClockMode;
	theStream >> aMateClockMode;
	myMateClockMode = (CT_TEL_ClkMode)aMateClockMode;
    return theStream;

}

void MON_SyncStatus::Display(FC_Stream& theStream)
{
    MON_Object::Display(theStream);
    FC_FmtFlags previousFlags = fc_cout.Flags();
    fc_cout.Setf(ios::hex, ios::basefield);    
    theStream   << "SYNC    - Current Timing Dynamic State   = " << DISPLAY_CLKSEL_STATE(myCurrentState) << endl;
    theStream   << "SYNC    - Freerun SSM Value              = " << display_RXSSM(myFreerunSsm) << endl;
	theStream   << "SYNC    - Clock Mode                     = " << DISPLAY_CLK_MODE(myClockMode) << endl;
	theStream   << "SYNC    - Mate Clock Mode                = " << DISPLAY_CLK_MODE(myMateClockMode) << endl;
    fc_cout.Flags(previousFlags);
}
