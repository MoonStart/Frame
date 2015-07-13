
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         Cheryl Lindo, 5/22/08
DESCRIPTION:    Implementation file for TL1 CP Object Id
-----------------------------------------------------------------------------*/ 

#include <Facade/TL1_CPObjId.h>

#include <CommonTypes/CT_TL1_Error.h>

#include <CsPii/CSPII_SysCfgParamIF.h>

#include <BaseClass/AG_Error.h>
#include <BaseClass/FC_Stream.h>
#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_Blackboard.h>

FC_Blackboard* TL1_CPObjId::theirRoot = 0;


TL1_CPObjId::TL1_CPObjId()
{
}

TL1_CPObjId::~TL1_CPObjId()
{
}

TL1_CPObjId::TL1_CPObjId( const TL1_CPObjId& theId )
{
    itsRegionKey = theId.itsRegionKey;
}

FC_ObjId* TL1_CPObjId::Clone() const
{
    return new TL1_CPObjId(*this);
}

void TL1_CPObjId::SetRepository( FC_Blackboard& theRoot )
{
    TL1_CPObjId::theirRoot = &theRoot;
}

bool TL1_CPObjId::IsValid() const
{
    FC_THROW_ERROR_IF( !theirRoot, FC_RuntimeError,
                       "TL1_CPObjId root has not been initialized" );
    FC_BbRegion* region = theirRoot->GetRegionPtr( itsRegionKey );
    return (region != 0);
}

FC_FacadeObjId TL1_CPObjId::GetFacadeId( const string& theSubRegionId ) const
{
    FC_THROW_ERROR_IF( !theirRoot, FC_RuntimeError,
                       "TL1_CPObjId root has not been initialized" );

    FC_BbRegion* region = theirRoot->GetRegionPtr( itsRegionKey );

	if ( !region )
    {
        if (!CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsCtrlPlaneSupported())
        {
            VALIDATION_THROW_TL1_EXCEPTION(CT_TL1_IICMError(CT_TL1_IICMError::ER_IICM_INV),
                                          "Control Plane commands not allowed on non-Control-Plane nodes.");
        }
        else
        {
            throw CT_TL1_IIACError(CT_TL1_IIACError::ER_IIAC_AID_NR);
        }
    }

    // TL1 Entities region contains a single object and as such
    // each TL1_CPObjId by design always point to the first and only object
    // in the region
    return FC_FacadeObjId( *region, 0 );
}

istream& TL1_CPObjId::ReadObject( istream& theStream )
{
    theStream >> FC_ExtractVar( *theirRoot );
    theStream >> FC_ExtractVar( itsRegionKey );

    return theStream;
}

ostream& TL1_CPObjId::WriteObject( ostream& theStream )
{
    theStream << FC_InsertVar( *theirRoot );
    theStream << FC_InsertVar( itsRegionKey );

    return theStream;
}

FC_Stream& TL1_CPObjId::ReadObjectBinary( FC_Stream& theStream )
{
    theStream << itsRegionKey;

    return theStream;
}

FC_Stream& TL1_CPObjId::WriteObjectBinary( FC_Stream& theStream )
{
    theStream >> itsRegionKey;

    return theStream;
}

bool TL1_CPObjId::operator==( const FC_ObjId& rhs ) const
{
    bool response = false;
    const TL1_CPObjId* objId = dynamic_cast<const TL1_CPObjId*>(&rhs);

    if ( objId )
    {
        response = (itsRegionKey == objId->itsRegionKey);
    }

    return response;
}
