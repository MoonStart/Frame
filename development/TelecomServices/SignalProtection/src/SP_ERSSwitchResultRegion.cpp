/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:   T6100 Software Service
TARGET:          

-----------------------------------------------------------------------------*/ 
#include <BaseClass/FC_TextStream.h>

#include "../SP_ERSSwitchResultRegion.h"


SP_ERSSwitchResult::SP_ERSSwitchResult(void)
{
	Reset();
}

SP_ERSSwitchResult::~SP_ERSSwitchResult(void)
{
}

void SP_ERSSwitchResult::SetLastProcessedCommandID(CT_SP_CommandID theCommandID)
{
	myLastProcessedCommandID = theCommandID;
}
void SP_ERSSwitchResult::SetActiveSlot(CT_SlotId slot)
{
	myActiveSlot = slot;
}
void SP_ERSSwitchResult::SetStandbySlot(CT_SlotId slot)
{
	myStandbySlot = slot;
}
void SP_ERSSwitchResult::Reset()
{
	myLastProcessedCommandID = CT_SP_INVALID_COMMAND;
	myActiveSlot = UNKNOWN_SLOT_ID;
	myStandbySlot = UNKNOWN_SLOT_ID;
}

//-----------------------------------------------------------------------------
ostream& SP_ERSSwitchResult::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myLastProcessedCommandID);
	theStream << FC_InsertVar(myActiveSlot);
	theStream << FC_InsertVar(myStandbySlot);
    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& SP_ERSSwitchResult::WriteObjectBinary( FC_Stream& theStream )
{
    theStream <<myLastProcessedCommandID;
	theStream <<myActiveSlot;
	theStream <<myStandbySlot;
    return theStream;
}

//-----------------------------------------------------------------------------
istream& SP_ERSSwitchResult::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myLastProcessedCommandID);
	theStream >> FC_ExtractVar(myActiveSlot);
	theStream >> FC_ExtractVar(myStandbySlot);
    return theStream;
}

//-----------------------------------------------------------------------------
FC_Stream& SP_ERSSwitchResult::ReadObjectBinary( FC_Stream& theStream )
{
    theStream >> myLastProcessedCommandID;
	theStream >> myActiveSlot;
	theStream >> myStandbySlot;
    return theStream;
}

//-----------------------------------------------------------------------------
SP_ERSSwitchResultRegion::SP_ERSSwitchResultRegion(FC_BbKey theKey):
    FC_BbRegionVectImp<SP_ERSSwitchResult>(theKey, 1)
{
    
}

SP_ERSSwitchResultRegion::~SP_ERSSwitchResultRegion()
{
}

CT_SlotId SP_ERSSwitchResultRegion::GetActiveSlot()
{
	return (*this)[0].GetActiveSlot();
}
CT_SlotId SP_ERSSwitchResultRegion::GetStandbySlot()
{
	return (*this)[0].GetStandbySlot();
}

CT_SP_CommandID SP_ERSSwitchResultRegion::GetLastProcessedCommandID()
{
	return (*this)[0].GetLastProcessedCommandID();
}
