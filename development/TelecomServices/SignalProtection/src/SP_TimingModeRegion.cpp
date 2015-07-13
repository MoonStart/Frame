// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_TimingModeRegion.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>


SP_TimingModeObject::SP_TimingModeObject():
	myTimingMode(CT_TEL_CLKMODE_UNKNOWN),
    mySelectedRefSsm(CT_RxSsm_ALL),
	myTimingReference(CT_TEL_CLKSEL_REF_INTERNAL)
{
}

SP_TimingModeObject::~SP_TimingModeObject()
{
}

bool SP_TimingModeObject::SetTimingMode(CT_TEL_ClkMode theTimingMode)
{
	bool hasChanged = false;
	if (theTimingMode != myTimingMode)
		hasChanged = true;

	myTimingMode = theTimingMode;
	return hasChanged;
}

CT_TEL_ClkMode SP_TimingModeObject::GetTimingMode()
{
	return myTimingMode;
}

bool SP_TimingModeObject::SetTimingReference(CT_TEL_ClkSelRef theTimingReference)
{
	bool hasChanged = false;
	if (theTimingReference != myTimingReference)
		hasChanged = true;

	myTimingReference = theTimingReference;
	return hasChanged;
}

CT_TEL_ClkSelRef SP_TimingModeObject::GetTimingReference()
{
	return myTimingReference;
}

bool SP_TimingModeObject::SetSelectedRefSsm(CT_FAC_RxSsm theSelectedRefSsm)
{
	bool hasChanged = false;
	if (theSelectedRefSsm != mySelectedRefSsm)
		hasChanged = true;

	mySelectedRefSsm = theSelectedRefSsm;
	return hasChanged;
}

CT_FAC_RxSsm SP_TimingModeObject::GetSelectedRefSsm()
{
	return mySelectedRefSsm;
}

ostream& SP_TimingModeObject::WriteObject( ostream& theStream )
{
	uint8 aTimingMode(myTimingMode);
    theStream << FC_InsertVar(aTimingMode);
    uint32 aSelectedRefSSM = (uint32) mySelectedRefSsm;
    theStream   << FC_InsertVar(aSelectedRefSSM);
	uint8 aTimingRef = (uint8) myTimingReference;
    theStream   << FC_InsertVar(aTimingRef);
    return theStream;
}

istream& SP_TimingModeObject::ReadObject( istream& theStream )
{
    uint8 aTimingMode;
    theStream>>FC_ExtractVar(aTimingMode);
    myTimingMode = (CT_TEL_ClkMode)aTimingMode;
    uint32 aSelectedRefSSM = 0;
    theStream   >> FC_ExtractVar(aSelectedRefSSM);
    mySelectedRefSsm = (CT_FAC_RxSsm) aSelectedRefSSM;
	uint8 aTimingRef;
	theStream >> FC_ExtractVar(aTimingRef);
    myTimingReference = (CT_TEL_ClkSelRef) aTimingRef;
    return theStream;
}

FC_Stream& SP_TimingModeObject::WriteObjectBinary( FC_Stream& theStream )
{
    uint8 aTimingMode(myTimingMode);
    theStream<<aTimingMode;
    uint32 aSelectedRefSSM = (uint32) mySelectedRefSsm;
    theStream   << aSelectedRefSSM;
	uint8 aTimingRef = (uint8) myTimingReference;
	theStream << aTimingRef;
    return theStream;

}

FC_Stream& SP_TimingModeObject::ReadObjectBinary( FC_Stream& theStream ) 
{
    uint8 aTimingMode;
    theStream>>aTimingMode;
    myTimingMode = (CT_TEL_ClkMode)aTimingMode;
    uint32 aSelectedRefSSM = 0;
    theStream   >> aSelectedRefSSM;
    mySelectedRefSsm = (CT_FAC_RxSsm)aSelectedRefSSM;
	uint8 aTimingRef;
	theStream >> aTimingRef;
	myTimingReference = (CT_TEL_ClkSelRef)aTimingRef;
    return theStream;

}


SP_TimingModeRegion::SP_TimingModeRegion()
{
}

SP_TimingModeRegion::SP_TimingModeRegion(	const FC_BbKey theKey, int theSize)
:TEL_BbRegionBaseImp<SP_TimingModeObject>( theKey, theSize)
{
}

SP_TimingModeRegion::~SP_TimingModeRegion()
{
}
