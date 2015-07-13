// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SsmRegion.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

const FC_BbKey SP_SSMCOLLECTIONREGIONKEY = "SP_SSMCollection";
const FC_BbKey SP_SSMDISTRIBUTIONREGIONKEY = "SP_SSMDistribution";


SP_SsmValue::SP_SsmValue():
	mySelectedSide(CT_SP_INVALID_PROTECTION_SIDE)
{
	mySsmVal.working = mySsmVal.protection = CT_RxSsm_ALL;
	myInterface.working = CT_Port();
	myInterface.protection = CT_Port();
	myDataValid.working = myDataValid.protection = false;
}

SP_SsmValue::~SP_SsmValue()
{
}

bool SP_SsmValue::SetSsmValue(CT_SP_Protection theSide, CT_Port& theInterface, CT_FAC_RxSsm theSsmVal, bool isValid)
{
	bool hasChanged = false;

	if (theSide == CT_SP_WORKING_SIDE)
	{
	    if ((theSsmVal != mySsmVal.working) ||
            (theInterface != myInterface.working) ||
			(isValid != myDataValid.working))
		    hasChanged = true;

	    myInterface.working = theInterface;
	    mySsmVal.working = theSsmVal;
		myDataValid.working = isValid;
	}
	else if (theSide == CT_SP_PROTECTION_SIDE)
	{
		if ((theSsmVal != mySsmVal.protection) ||
            (theInterface != myInterface.protection) ||
			(isValid != myDataValid.protection))
		    hasChanged = true;

	    myInterface.protection = theInterface;
	    mySsmVal.protection = theSsmVal;
		myDataValid.protection = isValid;
	}

	return hasChanged;
}

CT_FAC_RxSsm SP_SsmValue::GetSsmValue(CT_SP_Protection theSide)
{
	if (theSide == CT_SP_WORKING_SIDE)
	{
		return mySsmVal.working;
	}
	else
	{
		return mySsmVal.protection;
	}
}

bool SP_SsmValue::Reset(CT_SP_Protection theSide)
{
	CT_Port thePort;
    return (SetSsmValue(theSide,thePort,CT_RxSsm_ALL, false));	
}

bool SP_SsmValue::IsSsmValid(CT_SP_Protection theSide)
{
	if (theSide == CT_SP_INVALID_PROTECTION_SIDE)
		return false;

	return (theSide == CT_SP_WORKING_SIDE ? myDataValid.working : myDataValid.protection);
}

bool SP_SsmValue::SetSelectedSide(CT_SP_Protection theSide)
{
	bool hasChanged = false;
	if (mySelectedSide != theSide)
	{
        mySelectedSide = theSide;
		hasChanged = true;
	}

	return hasChanged;
}

CT_SP_Protection SP_SsmValue::GetSelectedSide()
{
    return mySelectedSide;
}

//get the interfaces
CT_SP_ProtectionPair<CT_Port> & SP_SsmValue::GetInterfaces()
{
	return myInterface;
}

CT_ShelfId SP_SsmValue::GetSsmShelf(CT_SP_Protection theSide)
{
    if (theSide == CT_SP_WORKING_SIDE)
	{
		return myInterface.working.GetShelfId();
	}
	else
	{
		return myInterface.protection.GetShelfId();
	}
}
CT_SlotId SP_SsmValue::GetSsmSlot(CT_SP_Protection theSide)
{
    if (theSide == CT_SP_WORKING_SIDE)
	{
		return myInterface.working.GetSlotId();
	}
	else
	{
		return myInterface.protection.GetSlotId();
	}
}


ostream& SP_SsmValue::WriteObject( ostream& theStream )
{
	uint32 aWorkingSsm;
	uint32 aProtectionSsm;

	aWorkingSsm = (uint32)mySsmVal.working;
    theStream   << FC_InsertVar(aWorkingSsm);
	theStream   << FC_InsertVar(myInterface.working);
    theStream   << FC_InsertVar(myDataValid.working);

	aProtectionSsm = (uint32)mySsmVal.protection;
    theStream   << FC_InsertVar(aProtectionSsm);
	theStream   << FC_InsertVar(myInterface.protection);
	theStream   << FC_InsertVar(myDataValid.protection);

	theStream   << FC_InsertVar(mySelectedSide);
    return theStream;
}

istream& SP_SsmValue::ReadObject( istream& theStream )
{
	uint32 aWorkingSsm;
	uint32 aProtectionSsm;

    theStream   >> FC_ExtractVar(aWorkingSsm);
	mySsmVal.working = (CT_FAC_RxSsm)aWorkingSsm;
	theStream   >> FC_ExtractVar(myInterface.working);
	theStream   >> FC_ExtractVar(myDataValid.working);

	theStream   >> FC_ExtractVar(aProtectionSsm);
	mySsmVal.protection = (CT_FAC_RxSsm)aProtectionSsm;
	theStream   >> FC_ExtractVar(myInterface.protection);
	theStream   >> FC_ExtractVar(myDataValid.protection);

	theStream   >> FC_ExtractVar(mySelectedSide);
    return theStream;
}

FC_Stream& SP_SsmValue::WriteObjectBinary( FC_Stream& theStream )
{
	uint32 tmp;

	tmp = (uint32)mySsmVal.working;
    theStream   << tmp;
	theStream   << myInterface.working;
	theStream   << myDataValid.working;

	tmp = (uint32)mySsmVal.protection;
    theStream   << tmp;
	theStream   << myInterface.protection;
	theStream   << myDataValid.protection;

	theStream   << mySelectedSide;
    return theStream;

}

FC_Stream& SP_SsmValue::ReadObjectBinary( FC_Stream& theStream ) 
{
	uint32 tmp;

    theStream   >> tmp;
	mySsmVal.working = (CT_FAC_RxSsm)tmp;
	theStream   >> myInterface.working;
	theStream   >> myDataValid.working;

	theStream   >> tmp;
	mySsmVal.protection = (CT_FAC_RxSsm)tmp;
	theStream   >> myInterface.protection;
	theStream   >> myDataValid.protection;

	theStream   >> mySelectedSide;
    return theStream;

}


SP_SsmRegion::SP_SsmRegion()
{
}

SP_SsmRegion::SP_SsmRegion(	const FC_BbKey theKey, int theSize)
:TEL_BbRegionBaseImp<SP_SsmValue>( theKey, theSize)
{
}

SP_SsmRegion::~SP_SsmRegion()
{
}
