/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 12, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Entity base class declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENTITY_H__
#define __TL1_ENTITY_H__

#ifndef __FC_BBOBJECT_H__
#include <Blackboard/FC_BbObject.h>
#endif

/** for TL1 ODUKT debug 
* When Agent and BE are OK, cancel this definition.
*/
//#define SIM_TCM_TEST
#include <set>

class FC_BbRegion;
class AS_Context;

using namespace std;

/**
   CLASS TL1_Entity

   This is the base class for all TL1 Entity. This is an abstract base class
   and no instance of it should be instantiated. A class should be derived from
   it for each of the AID family.
 */
class TL1_Entity : public FC_BbObject
{
public:
    typedef set<FC_BbRegion*> RegionSet;

    TL1_Entity();
    virtual ~TL1_Entity();

    virtual void InstallNotifObservers( AS_Context& theContext );
    virtual void UninstallNotifObservers( AS_Context& theContext );

    //
    // FC_Object methods
    //
    virtual ostream& WriteObject( ostream& theStream );

    virtual istream& ReadObject( istream& theSream );

    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    void SetParent( FC_BbRegion& theParent );

    const string&  GetEntityName(void) const;

    const string&  GetAidName(void) const;

    void SetAidName(const string& name);

    // Methods to manage notification of the modified regions
    void AddDirtyRegion(FC_BbRegion* theRegion);
    void NotifyDirtyRegions();

private:
    FC_BbRegion* itsParent;
    RegionSet itsDirtyRegions;
    string itsAidName;
};

#endif


