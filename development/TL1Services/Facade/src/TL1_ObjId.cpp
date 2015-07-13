/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 19, 2003- Jean-Francois Tremblay
DESCRIPTION:    Implementation file for TL1 Object Id
-----------------------------------------------------------------------------*/ 

#include <Facade/TL1_ObjId.h>

#include <CommonTypes/CT_TL1_Error.h>

#include <BaseClass/FC_Stream.h>
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_Blackboard.h>

FC_Blackboard* TL1_ObjId::theirRoot = 0;


TL1_ObjId::TL1_ObjId()
{
}

TL1_ObjId::~TL1_ObjId()
{
}

TL1_ObjId::TL1_ObjId( const TL1_ObjId& theId )
{
    itsRegionKey = theId.itsRegionKey;
}

FC_ObjId* TL1_ObjId::Clone() const
{
    return new TL1_ObjId(*this);
}

void TL1_ObjId::SetRepository( FC_Blackboard& theRoot )
{
    TL1_ObjId::theirRoot = &theRoot;
}

bool TL1_ObjId::IsValid() const
{
    FC_THROW_ERROR_IF( !theirRoot, FC_RuntimeError,
                       "TL1_ObjId root has not been initialized" );
    FC_BbRegion* region = theirRoot->GetRegionPtr( itsRegionKey );
    return (region != 0);
}

FC_FacadeObjId TL1_ObjId::GetFacadeId( const string& theSubRegionId ) const
{
    FC_THROW_ERROR_IF( !theirRoot, FC_RuntimeError,
                       "TL1_ObjId root has not been initialized" );

    FC_BbRegion* region = theirRoot->GetRegionPtr( itsRegionKey );

	if ( !region )
    {
        throw CT_TL1_IIACError(CT_TL1_IIACError::ER_IIAC_AID_NR);
    }

    // TL1 Entities region contains a single object and as such
    // each TL1_ObjId by design always point to the first and only object
    // in the region
    return FC_FacadeObjId( *region, 0 );
}

istream& TL1_ObjId::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar( *theirRoot );
    theStream >> FC_ExtractVar( itsRegionKey );

    return theStream;
}

ostream& TL1_ObjId::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar( *theirRoot );
    theStream << FC_InsertVar( itsRegionKey );

    return theStream;
}

FC_Stream& TL1_ObjId::ReadObjectBinary( FC_Stream& theStream )
{
    theStream << itsRegionKey;

    return theStream;
}

FC_Stream& TL1_ObjId::WriteObjectBinary( FC_Stream& theStream )
{
    theStream >> itsRegionKey;

    return theStream;
}

bool TL1_ObjId::operator==( const FC_ObjId& rhs ) const
{
    bool response = false;
    const TL1_ObjId* objId = dynamic_cast<const TL1_ObjId*>(&rhs);

    if ( objId )
    {
        response = (itsRegionKey == objId->itsRegionKey);
    }

    return response;
}
