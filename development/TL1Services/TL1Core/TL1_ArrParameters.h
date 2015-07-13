/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Aug 06, 2010 - Chengsi Shao
DESCRIPTION:    Header file for OPR ADEREROUTE Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ARRPARAMETERS_H__
#define __TL1_ARRPARAMETERS_H__

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

class TL1_OprArrParameters
{
public:
    TL1_OprArrParameters();
    virtual ~TL1_OprArrParameters();
    TL1_OprArrParameters ( const TL1_OprArrParameters& theInst );
    TL1_OprArrParameters& operator= ( const TL1_OprArrParameters& theInst );
    bool operator==  (const TL1_OprArrParameters& theInst) const;

    inline LT_Handle* GetHandle() const;
    inline void SetHandle( LT_Handle* theHandle );
    
    inline LT_Ctag  GetCtag() const;
    inline void SetCtag( LT_Ctag theCtag );
    
    inline CT_ControlPlane_CallId* GetCallId() const;
    inline void SetCallId( CT_ControlPlane_CallId* theCallId );
    
    inline CT_TL1_LinkAddr* GetLinkAddr() const;  
    inline void SetLinkAddr( CT_TL1_LinkAddr* theAddr );

    inline CT_ControlPlane_Hops* GetAvoidLinks() const;
    inline void SetAvoidLinks( CT_ControlPlane_Hops* theAvoidLinks );

    CT_CallPathType * GetPathType() const;  
    void SetPathType( CT_CallPathType * theType );

    CT_TL1_ExppathAddr* GetExpPathAddr() const;  
    void SetExpPathAddr( CT_TL1_ExppathAddr* theAddr );

    bool* GetCostOpt () const;  
    void SetCostOpt ( bool* theCostFlag );

    bool* GetCmdMode() const;  
    void SetCmdMode( bool* theCmdMode );


private:
    
    LT_Handle*                  myHandle;
    LT_Ctag                     myCtag;
    CT_ControlPlane_CallId*     myCallId;
    CT_TL1_LinkAddr*            myLinkAddr;
    CT_ControlPlane_Hops*       myAvoidLinks;
    CT_CallPathType*            myPathType;
    CT_TL1_ExppathAddr*         myExpPathAddr;
    bool*                       myCostFlag;
    bool*                       myCmdMode;
};    
//--------------------------------------------------------------------------------
inline LT_Handle* 
TL1_OprArrParameters::GetHandle() const
{
    return myHandle;
}

inline void 
TL1_OprArrParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag  
TL1_OprArrParameters::GetCtag() const
{
    return myCtag;
}

inline void 
TL1_OprArrParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_CallId* 
TL1_OprArrParameters::GetCallId( )const
{
    return myCallId;
}


inline void
TL1_OprArrParameters::SetCallId( CT_ControlPlane_CallId* theCallId )
{
    myCallId = theCallId;
}

//--------------------------------------------------------------------------------

inline CT_TL1_LinkAddr*
TL1_OprArrParameters::GetLinkAddr() const
{
    return myLinkAddr;
    
}

inline void
TL1_OprArrParameters::SetLinkAddr( CT_TL1_LinkAddr* theLinkAddr )
{
    myLinkAddr = theLinkAddr;
}

//--------------------------------------------------------------------------------

inline CT_ControlPlane_Hops*
TL1_OprArrParameters::GetAvoidLinks() const
{
    return myAvoidLinks;
}

void
TL1_OprArrParameters::SetAvoidLinks( CT_ControlPlane_Hops* theAvoidLinks )
{
    myAvoidLinks = theAvoidLinks;
}

#endif

