// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_SelectorPositionRegion.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

const FC_BbKey SP_SELECTORPOSREGIONKEY = "SP_SELECTOR_POSITION";
const FC_BbKey SP_ALTSELECTORPOSREGIONKEY = "SP_ALT_SELECTOR_POSITION";


SP_SelectorPosition::SP_SelectorPosition():
    mySelectorPosition(CT_SP_WORKING_SIDE)
{
}

SP_SelectorPosition::~SP_SelectorPosition()
{
}

bool SP_SelectorPosition::SetSelectorPostion(CT_SP_Protection theNewSelPosition)
{
	bool rc = false;
	if (mySelectorPosition != theNewSelPosition)
		rc = true;

    mySelectorPosition = theNewSelPosition;
	return rc;
}


ostream& SP_SelectorPosition::WriteObject( ostream& theStream )
{
    theStream   << FC_InsertVar(mySelectorPosition);
    return theStream;
}

istream& SP_SelectorPosition::ReadObject( istream& theStream )
{
    theStream   >> FC_ExtractVar(mySelectorPosition);
    return theStream;
}

FC_Stream& SP_SelectorPosition::WriteObjectBinary( FC_Stream& theStream )
{
    theStream   << mySelectorPosition;
    return theStream;

}

FC_Stream& SP_SelectorPosition::ReadObjectBinary( FC_Stream& theStream ) 
{
    theStream   >> mySelectorPosition;
    return theStream;

}


SP_SelectorPositionRegion::SP_SelectorPositionRegion()
{
}

SP_SelectorPositionRegion::SP_SelectorPositionRegion(	const FC_BbKey theKey, int theSize)
:TEL_BbRegionBaseImp<SP_SelectorPosition>( theKey, theSize)
{
}

SP_SelectorPositionRegion::~SP_SelectorPositionRegion()
{
}

void SP_SelectorPositionRegion::Conversion(FC_Version& theRxVersion, FC_Stream& theStream)
{
    theStream >> *this;
}