// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_1plus1ProtectionGroupStatus.h"
#include <BaseClass/FC_TextStream.h>


SP_1plus1ProtectionGroupStatus::SP_1plus1ProtectionGroupStatus():
    myUnitStatus(),
    mySelectedSide(CT_SP_WORKING_SIDE),
	myLastProcessedCommandID(CT_SP_INVALID_COMMAND),
    mySelectedSideUsable(true)
{
}

SP_1plus1ProtectionGroupStatus::SP_1plus1ProtectionGroupStatus(const SP_1plus1ProtectionGroupStatus& theStatus):
    SP_ProtectionGroupStatus(theStatus),
    myUnitStatus(theStatus.myUnitStatus),
    mySelectedSide(theStatus.mySelectedSide),
	myLastProcessedCommandID(theStatus.myLastProcessedCommandID),
    mySelectedSideUsable(theStatus.mySelectedSideUsable)
{
}

bool SP_1plus1ProtectionGroupStatus::operator==(const SP_1plus1ProtectionGroupStatus& theStatus) const
{
    return ( (SP_ProtectionGroupStatus::operator==(theStatus)) && 
             (myUnitStatus == theStatus.myUnitStatus) && 
             (mySelectedSide == theStatus.mySelectedSide) &&
			 (myLastProcessedCommandID == theStatus.myLastProcessedCommandID) &&
             (mySelectedSideUsable == theStatus.mySelectedSideUsable));
}

SP_1plus1ProtectionGroupStatus& SP_1plus1ProtectionGroupStatus::operator=(const SP_1plus1ProtectionGroupStatus& theStatus)
{
    SP_ProtectionGroupStatus::operator=(theStatus);
    myUnitStatus = theStatus.myUnitStatus;
    mySelectedSide = theStatus.mySelectedSide;
	myLastProcessedCommandID = theStatus.myLastProcessedCommandID;
    mySelectedSideUsable = theStatus.mySelectedSideUsable;
    return *this;
}

SP_1plus1ProtectionGroupStatus::~SP_1plus1ProtectionGroupStatus()
{
}

void SP_1plus1ProtectionGroupStatus::SetSelectedSide(const CT_SP_Protection theSelection)
{
    mySelectedSide = theSelection;
}

void SP_1plus1ProtectionGroupStatus::SetLastProcessedCommandID(CT_SP_CommandID theCommandID)
{
    myLastProcessedCommandID = theCommandID;
}

bool SP_1plus1ProtectionGroupStatus::SetSelectedSideUsable(bool theUsable)
{
    bool hasChanged = false;
    if (mySelectedSideUsable != theUsable)
    {
        mySelectedSideUsable = theUsable;
        hasChanged = true;
    }
    return hasChanged;
}

//Return current source of request (remote or local).
CT_SP_Location SP_1plus1ProtectionGroupStatus::GetRemoteOrLocal() const
{
      return myUnitStatus.GetRemoteOrLocal();
}

CT_SP_ApsBidirType  SP_1plus1ProtectionGroupStatus::GetActualApsBidir() const
{
      return myUnitStatus.GetActualApsBidir();
}

//Return current automatic switch reason.	
const CT_SP_ProtectionPair<CT_SP_AutoSwitchDefect> SP_1plus1ProtectionGroupStatus::GetAutoSwitchReason() const
{
	return myUnitStatus.GetAutoSwitchReason();
}

//Return the current switch request.
CT_SP_Request SP_1plus1ProtectionGroupStatus::GetRequest() const
{
	return myUnitStatus.GetRequest();
}

CT_SP_CommandID SP_1plus1ProtectionGroupStatus::GetLastProcessedCommandID()
{
    return myLastProcessedCommandID;
}

CT_SP_1plus1UnitStatus& SP_1plus1ProtectionGroupStatus::GetProtectionUnits()
{
    return myUnitStatus;
}

CT_SP_Protection SP_1plus1ProtectionGroupStatus::GetSelectedSide()
{
    return mySelectedSide;
}

bool SP_1plus1ProtectionGroupStatus::GetSelectedSideUsable()
{
    return mySelectedSideUsable;
}

ostream& SP_1plus1ProtectionGroupStatus::WriteObject( ostream& theStream )
{
    SP_ProtectionGroupStatus::WriteObject(theStream);
	theStream<<FC_InsertVar(myUnitStatus);
	theStream<<FC_InsertVar(mySelectedSide);
	theStream<<FC_InsertVar(myLastProcessedCommandID);
    theStream<<FC_InsertVar(mySelectedSideUsable);

    return theStream;
}

istream& SP_1plus1ProtectionGroupStatus::ReadObject( istream& theStream )
{
    SP_ProtectionGroupStatus::ReadObject(theStream);
	theStream>>FC_ExtractVar(myUnitStatus);
	theStream>>FC_ExtractVar(mySelectedSide);
	theStream>>FC_ExtractVar(myLastProcessedCommandID);
    theStream>>FC_ExtractVar(mySelectedSideUsable);

    return theStream;
}

FC_Stream& SP_1plus1ProtectionGroupStatus::WriteObjectBinary( FC_Stream& theStream )
{
    SP_ProtectionGroupStatus::WriteObjectBinary(theStream);
	theStream<<myUnitStatus;
	theStream<<mySelectedSide;
	theStream<<myLastProcessedCommandID;
    theStream<<mySelectedSideUsable;

    return theStream;
}

FC_Stream& SP_1plus1ProtectionGroupStatus::ReadObjectBinary( FC_Stream& theStream )
{
    SP_ProtectionGroupStatus::ReadObjectBinary(theStream);
	theStream>>myUnitStatus;
	theStream>>mySelectedSide;
	theStream>>myLastProcessedCommandID;
    theStream>>mySelectedSideUsable;

    return theStream;
}
