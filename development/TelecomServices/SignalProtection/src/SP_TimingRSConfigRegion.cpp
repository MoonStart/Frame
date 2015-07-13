// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_TimingRSConfigRegion.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>


SP_TimingRSConfig::SP_TimingRSConfig():
	myRedundancyMode(CT_SP_RS_UNKNOWN)
{
}

SP_TimingRSConfig::~SP_TimingRSConfig()
{
}

bool SP_TimingRSConfig::SetRedundancyMode(CT_SP_RSMode theRedundancyMode)
{
	bool hasChanged = false;
	if (theRedundancyMode != myRedundancyMode)
		hasChanged = true;

	myRedundancyMode = theRedundancyMode;
	return hasChanged;
}

CT_SP_RSMode SP_TimingRSConfig::GetRedundancyMode()
{
	return myRedundancyMode;
}

ostream& SP_TimingRSConfig::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myRedundancyMode);
    return theStream;
}

istream& SP_TimingRSConfig::ReadObject( istream& theStream )
{
    theStream>>FC_ExtractVar(myRedundancyMode);
    return theStream;
}

FC_Stream& SP_TimingRSConfig::WriteObjectBinary( FC_Stream& theStream )
{
    theStream<<myRedundancyMode;
    return theStream;

}

FC_Stream& SP_TimingRSConfig::ReadObjectBinary( FC_Stream& theStream ) 
{
    theStream>>myRedundancyMode;
    return theStream;

}


SP_TimingRSConfigRegion::SP_TimingRSConfigRegion()
{
}

SP_TimingRSConfigRegion::SP_TimingRSConfigRegion(	const FC_BbKey theKey, int theSize)
:TEL_BbRegionBaseImp<SP_TimingRSConfig>( theKey, theSize)
{
}

SP_TimingRSConfigRegion::~SP_TimingRSConfigRegion()
{
}
