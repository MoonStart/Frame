
/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Cheryl Lindo, 5/23/08
DESCRIPTION:    Header file for TL1 CP Object Id declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CPOBJID_H__
#define __TL1_CPOBJID_H__


#ifndef TL1_OBJID_H
#include <Facade/TL1_ObjId.h>
#endif

#ifndef __FC_BBREGIONID_H__
#include <Blackboard/FC_BbRegionId.h>
#endif

class TL1_CPObjId : public TL1_ObjId
{
public:
    TL1_CPObjId( const FC_BbKey& theKey) : itsRegionKey(theKey) {}
	TL1_CPObjId();
    virtual ~TL1_CPObjId();

    TL1_CPObjId( const TL1_CPObjId& theId );

    virtual FC_ObjId* Clone() const;

    virtual bool operator==( const FC_ObjId& rhs ) const;

    static void SetRepository( FC_Blackboard& theRoot );

    virtual FC_FacadeObjId GetFacadeId( const string& theSubRegionId ) const;

    virtual bool IsValid() const;

    virtual istream& ReadObject( istream& theStream );

    virtual ostream& WriteObject( ostream& theStream );

    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

private:
    static FC_Blackboard* theirRoot;

    FC_BbKey itsRegionKey;
};

#endif
