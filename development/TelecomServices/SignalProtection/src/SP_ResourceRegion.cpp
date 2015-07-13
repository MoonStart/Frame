// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_ResourceRegion.h"
#include <ErrorService/FC_Error.h>
#include <BaseClass/FC_TextStream.h>

const FC_BbKey SP_RESOURCEREGION_A_KEY = "SP_RESOURCE_A";
const FC_BbKey SP_RESOURCEREGION_B_KEY = "SP_RESOURCE_B";


SP_ResourceObject::SP_ResourceObject():
	myResourceId((uint8)CT_INTF_ID_UNKNOWN),
	myIsEnable(false)
{
	myResourceList = CT_FAC_StsMap();
}

SP_ResourceObject::~SP_ResourceObject()
{
}

void SP_ResourceObject::SetResourceList(CT_FAC_StsMap& theResourceList, CT_IntfId thePortId)
{
	myResourceList = theResourceList;
    myResourceId   = (uint8)thePortId;
}

void SP_ResourceObject::SetEnabledState(bool theState)
{
	myIsEnable = theState;
}

CT_FAC_StsMap& SP_ResourceObject::GetResourceList()
{
	return myResourceList;
}

CT_IntfId SP_ResourceObject::GetResourceFacility()
{
	return (CT_IntfId)myResourceId;
}

bool SP_ResourceObject::GetIsEnabled()
{
	return myIsEnable;
}

void SP_ResourceObject::Reset()
{
	myIsEnable = false;
	myResourceList.Reset();
	myResourceId = (uint8)CT_INTF_ID_UNKNOWN;
}

ostream& SP_ResourceObject::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar(myResourceList);
    theStream << FC_InsertVar(myResourceId);
	theStream << FC_InsertVar(myIsEnable);
    return theStream;
}

istream& SP_ResourceObject::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar(myResourceList);
    theStream >> FC_ExtractVar(myResourceId);
	theStream >> FC_ExtractVar(myIsEnable);
    return theStream;
}

FC_Stream& SP_ResourceObject::WriteObjectBinary( FC_Stream& theStream )
{
    theStream << myResourceList;
    theStream << myResourceId;
	theStream << myIsEnable;
    return theStream;

}

FC_Stream& SP_ResourceObject::ReadObjectBinary( FC_Stream& theStream ) 
{
    theStream >> myResourceList;
    theStream >> myResourceId;
	theStream >> myIsEnable;
    return theStream;

}


SP_ResourceRegion::SP_ResourceRegion()
{
}

SP_ResourceRegion::SP_ResourceRegion(	const FC_BbKey theKey, int theSize)
:TEL_BbRegionBaseImp<SP_ResourceObject>( theKey, theSize)
{
}

SP_ResourceRegion::~SP_ResourceRegion()
{
}
