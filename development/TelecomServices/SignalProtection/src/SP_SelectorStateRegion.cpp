// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SelectorStateRegion.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

const FC_BbKey SP_SELECTORSTATEREGION_KEY = "SP_SELECTOR_STATE_KEY";


SP_SelectorState::SP_SelectorState():
    mySelectorState(CT_SP_INVALID_PROTECTION_SIDE)
{
}

SP_SelectorState::~SP_SelectorState()
{
}

bool SP_SelectorState::SetSelectorState(CT_SP_Protection theNewSelState)
{
	bool rc = false;
	if (mySelectorState != theNewSelState)
		rc = true;

    mySelectorState = theNewSelState;
	return rc;
}


ostream& SP_SelectorState::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(mySelectorState);
    return theStream;
}

istream& SP_SelectorState::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(mySelectorState);
    return theStream;
}

FC_Stream& SP_SelectorState::WriteObjectBinary( FC_Stream& theStream )
{
    theStream   << mySelectorState;
    return theStream;

}

FC_Stream& SP_SelectorState::ReadObjectBinary( FC_Stream& theStream ) 
{
    theStream   >> mySelectorState;
    return theStream;

}


SP_SelectorStateRegion::SP_SelectorStateRegion()
{
}

SP_SelectorStateRegion::SP_SelectorStateRegion(	const FC_BbKey theKey, int theSize)
:TEL_BbRegionBaseImp<SP_SelectorState>( theKey, theSize)
{
}

SP_SelectorStateRegion::~SP_SelectorStateRegion()
{
}