/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for EXPPATH TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXPPATHPARAMETERS_H__
#define __TL1_EXPPATHPARAMETERS_H__

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

class TL1_ExppathParameters  
{
public:
    
    TL1_ExppathParameters();

    virtual ~TL1_ExppathParameters();

    TL1_ExppathParameters(const TL1_ExppathParameters& theInst );

    TL1_ExppathParameters& operator=( const TL1_ExppathParameters& theInst );

    bool operator==( const TL1_ExppathParameters& theInst ) const;

    inline LT_Handle*               GetHandle( ) const;
    inline void                     SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                  GetCtag( ) const;
    inline void                     SetCtag( LT_Ctag theCtag );

    inline string*                  GetExppathName() const;
    inline void                     SetExppathName( string* theExppathName );

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
    string*                 myExppathName;
    CT_ControlPlane_Hops*   myRoute;
    CT_ControlPlane_Hops*   myInsertBefore;
    CT_ControlPlane_Hops*   myInsertAfter;
    CT_ControlPlane_Hops*   myRemove;
    CT_ControlPlane_Hops*   mySubRoute;
};

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_ExppathParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_ExppathParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_ExppathParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_ExppathParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline string*                  
TL1_ExppathParameters::GetExppathName() const
{
    return myExppathName;
}

inline void                     
TL1_ExppathParameters::SetExppathName( string* theExppathName )
{
    myExppathName = theExppathName;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExppathParameters::GetRoute( ) const
{
    return myRoute;
}

inline void                         
TL1_ExppathParameters::SetRoute( CT_ControlPlane_Hops* theRoute )
{
    myRoute = theRoute;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExppathParameters::GetInsertBefore( ) const
{
    return myInsertBefore;
}

inline void                         
TL1_ExppathParameters::SetInsertBefore( CT_ControlPlane_Hops* theInsertBefore )
{
    myInsertBefore = theInsertBefore;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExppathParameters::GetInsertAfter( ) const
{
    return myInsertAfter;
}

inline void                         
TL1_ExppathParameters::SetInsertAfter( CT_ControlPlane_Hops* theInsertAfter )
{
    myInsertAfter = theInsertAfter;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExppathParameters::GetRemove( ) const
{
    return myRemove;
}

inline void                         
TL1_ExppathParameters::SetRemove( CT_ControlPlane_Hops* theRemove )
{
    myRemove = theRemove;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ExppathParameters::GetSubRoute( ) const
{
    return mySubRoute;
}

inline void                         
TL1_ExppathParameters::SetSubRoute( CT_ControlPlane_Hops* theSubRoute )
{
    mySubRoute = theSubRoute;
}

#endif
