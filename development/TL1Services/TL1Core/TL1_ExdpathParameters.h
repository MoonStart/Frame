/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         September 10, 2014 Jing Jin
DESCRIPTION:    Header file for EXDPATH TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXDPATHPARAMETERS_H__
#define __TL1_EXDPATHPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_CALLRSPBLK_H__
#include <Response/TL1_CallRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>

class TL1_ExdpathParameters  
{
public:
    
    TL1_ExdpathParameters();

    virtual ~TL1_ExdpathParameters();

    TL1_ExdpathParameters(const TL1_ExdpathParameters& theInst );

    TL1_ExdpathParameters& operator=( const TL1_ExdpathParameters& theInst );

    bool operator==( const TL1_ExdpathParameters& theInst ) const;

    inline LT_Handle*               GetHandle( ) const;
    inline void                     SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                  GetCtag( ) const;
    inline void                     SetCtag( LT_Ctag theCtag );

    inline string*                  GetExdpathName() const;
    inline void                     SetExdpathName( string* theExdpathName );

    inline CT_ControlPlane_Hops*    GetRoute( ) const;
    inline void                     SetRoute( CT_ControlPlane_Hops* theRoute );

    inline CT_ControlPlane_Hops*    GetInsertBefore( ) const;
    inline void                     SetInsertBefore( CT_ControlPlane_Hops* theInsertBefore );

    inline CT_ControlPlane_Hops*    GetInsertAfter( ) const;
    inline void                     SetInsertAfter( CT_ControlPlane_Hops* theInsertAfter );

    inline CT_ControlPlane_Hops*    GetRemove( ) const;
    inline void                     SetRemove( CT_ControlPlane_Hops* theRemove );

    inline CT_ControlPlane_Hops*    GetSubRoute( ) const;
    inline void                     SetSubRoute( CT_ControlPlane_Hops* theSubRoute );

private:

    LT_Handle*              myHandle;
    LT_Ctag                 myCtag;
    string*                 myExdpathName;
    CT_ControlPlane_Hops*   myRoute;
    CT_ControlPlane_Hops*   myInsertBefore;
    CT_ControlPlane_Hops*   myInsertAfter;
    CT_ControlPlane_Hops*   myRemove;
    CT_ControlPlane_Hops*   mySubRoute;
};

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_ExdpathParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_ExdpathParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_ExdpathParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_ExdpathParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline string*                  
TL1_ExdpathParameters::GetExdpathName() const
{
    return myExdpathName;
}

inline void                     
TL1_ExdpathParameters::SetExdpathName( string* theExdpathName )
{
    myExdpathName = theExdpathName;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExdpathParameters::GetRoute( ) const
{
    return myRoute;
}

inline void                         
TL1_ExdpathParameters::SetRoute( CT_ControlPlane_Hops* theRoute )
{
    myRoute = theRoute;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExdpathParameters::GetInsertBefore( ) const
{
    return myInsertBefore;
}

inline void                         
TL1_ExdpathParameters::SetInsertBefore( CT_ControlPlane_Hops* theInsertBefore )
{
    myInsertBefore = theInsertBefore;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExdpathParameters::GetInsertAfter( ) const
{
    return myInsertAfter;
}

inline void                         
TL1_ExdpathParameters::SetInsertAfter( CT_ControlPlane_Hops* theInsertAfter )
{
    myInsertAfter = theInsertAfter;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExdpathParameters::GetRemove( ) const
{
    return myRemove;
}

inline void                         
TL1_ExdpathParameters::SetRemove( CT_ControlPlane_Hops* theRemove )
{
    myRemove = theRemove;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExdpathParameters::GetSubRoute( ) const
{
    return mySubRoute;
}

inline void                         
TL1_ExdpathParameters::SetSubRoute( CT_ControlPlane_Hops* theSubRoute )
{
    mySubRoute = theSubRoute;
}

#endif

