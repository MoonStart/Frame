// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SwitchingStatistic.h"
#include <BaseClass/FC_TextStream.h>


//##ModelId=39ACEFB40226
bool SP_SwitchingStatistic::SetCurrentlyActive(bool theState)
{
    if (isCurrentlyActive != theState)
    {
        isCurrentlyActive = theState;
        return true;
    }
    else
        return false;
}

bool SP_SwitchingStatistic::SetRevertiveMode(bool theMode)
{
	if (revertiveMode != theMode)
	{
	    revertiveMode = theMode;
		return true;
	}
	else
		return false;
}

//##ModelId=38F484310275
bool SP_SwitchingStatistic::IsInvolvedInProtection()
{
	return myProtectionState;
}

//##ModelId=38F484A0001B
bool SP_SwitchingStatistic::IsProtecting()
{
	return myProtectingRole;
}

//##ModelId=38F484A0001B
bool SP_SwitchingStatistic::IsRevertive()
{
	return revertiveMode;
}



//##ModelId=38F4917A02ED
void SP_SwitchingStatistic::IncrementPSCspan()
{
    myPSCspan++;
}

//##ModelId=38F491C300AD
void SP_SwitchingStatistic::IncrementPSCwork()
{
	myPSCwork++;
}


//##ModelId=38F4B47E00A8
bool SP_SwitchingStatistic::SetInvolvedInProtection(bool theProtectionInvolvement)
{
    if (myProtectionState != theProtectionInvolvement)
    {
        myProtectionState = theProtectionInvolvement;
        return true;
    }
    else
        return false;
}

//##ModelId=38F4B4E9030F
bool SP_SwitchingStatistic::SetProtecting(bool theProtecting)
{
    if (myProtectingRole != theProtecting)
    {
	    myProtectingRole = theProtecting;
        return true;
    }
    else
        return false;
}


//##ModelId=38FB09660199
SP_SwitchingStatistic::~SP_SwitchingStatistic()
{
}

//##ModelId=3911AE7F00F2
SP_SwitchingStatistic::SP_SwitchingStatistic():
	myProtectionState(false),
	myProtectingRole(false),
	myPSCwork(0),
	myPSCspan(0),
    isCurrentlyActive(false),
    myHasChanged(false),
	revertiveMode(false)
{
}

//##ModelId=3932D1DD02DA
ostream& SP_SwitchingStatistic::WriteObject( ostream& theStream )
{
	theStream<<FC_InsertVar(myProtectionState);
	theStream<<FC_InsertVar(myProtectingRole);
	theStream<<FC_InsertVar(isCurrentlyActive);
	theStream<<FC_InsertVar(myPSCwork);
	theStream<<FC_InsertVar(myPSCspan);
	theStream<<FC_InsertVar(revertiveMode);

    return theStream;
}

//##ModelId=3932D1DD021B
istream& SP_SwitchingStatistic::ReadObject( istream& theStream )
{
	theStream>>FC_ExtractVar(myProtectionState);
	theStream>>FC_ExtractVar(myProtectingRole);
	theStream>>FC_ExtractVar(isCurrentlyActive);
	theStream>>FC_ExtractVar(myPSCwork);
	theStream>>FC_ExtractVar(myPSCspan);
    theStream>>FC_ExtractVar(revertiveMode);

    myHasChanged = false;

    return theStream;
}

//##ModelId=39ACEFB401C2
FC_Stream& SP_SwitchingStatistic::WriteObjectBinary( FC_Stream& theStream )
{
	theStream<<myProtectionState;
	theStream<<myProtectingRole;
	theStream<<isCurrentlyActive;
	theStream<<myPSCwork;
	theStream<<myPSCspan;
	theStream<<revertiveMode;

    return theStream;
}

//##ModelId=39ACEFB4015E
FC_Stream& SP_SwitchingStatistic::ReadObjectBinary( FC_Stream& theStream )
{
	theStream>>myProtectionState;
	theStream>>myProtectingRole;
	theStream>>isCurrentlyActive;
	theStream>>myPSCwork;
	theStream>>myPSCspan;
	theStream>>revertiveMode;

    myHasChanged = false;

    return theStream;
}


//##ModelId=3B8BC9DB00B6
SP_SwitchingStatistic& SP_SwitchingStatistic::operator=(const SP_SwitchingStatistic &rhs)
{
	myProtectionState = rhs.myProtectionState;
	myProtectingRole = rhs.myProtectingRole;
	myPSCwork = rhs.myPSCwork;
	myPSCspan = rhs.myPSCspan;
    isCurrentlyActive = rhs.isCurrentlyActive;
	revertiveMode = rhs.revertiveMode;

    return *this;
}

//##ModelId=3B8BC9DB007A
bool SP_SwitchingStatistic::HasChangedSinceLastCheck()
{
    if (myHasChanged == true)
    {
        myHasChanged = false;
        return true;
    }
    else
        return false;
}

