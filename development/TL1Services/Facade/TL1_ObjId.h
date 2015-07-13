/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 19, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Object Id declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OBJID_H__
#define __TL1_OBJID_H__


#ifndef FC_BBSYSOBJID_H
#include <Facade/FC_BbSysObjId.h>
#endif

#ifndef __FC_BBREGIONID_H__
#include <Blackboard/FC_BbRegionId.h>
#endif

class TL1_ObjId : public FC_BbSysObjId
{
public:
    TL1_ObjId( const FC_BbKey& theKey) : itsRegionKey(theKey) {}
	TL1_ObjId();
    virtual ~TL1_ObjId();

    TL1_ObjId( const TL1_ObjId& theId );

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
