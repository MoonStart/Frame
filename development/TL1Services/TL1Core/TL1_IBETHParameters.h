/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         
DESCRIPTION:    Header file for IBETH TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IBETHPARAMETERS_H__
#define __TL1_IBETHPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_FACDOMAIN_H__
#include <TL1Core/TL1_FacDomain.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_FACRSPBLK_H__
#include <Response/TL1_FACRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>

#include <CommonTypes/CT_IBETH_Definitions.h>

class TL1_IBETHParameters  
{
public:
    
    TL1_IBETHParameters();

    virtual ~TL1_IBETHParameters();

    TL1_IBETHParameters(const TL1_IBETHParameters& theInst );

    TL1_IBETHParameters& operator=( const TL1_IBETHParameters& theInst );

    bool operator==( const TL1_IBETHParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_LkType*           GetLkType( ) const;
    inline void                 SetLkType( CT_LkType* theLkType );

	inline int*				    GetBridge() const;
	inline void				    SetBridge( int*	theBridge );

	inline int*				    GetP2PVlan() const;
	inline void				    SetP2PVlan( int*	theP2PVlan );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

private:

    LT_Handle*          myHandle;
    LT_Ctag             myCtag;
    CT_LkType*          myLkType;
    int *               myBridge;
	int *               myP2PVlan;
    CT_SM_PST*          myPrimaryState;
   
};

class TL1_IBETHEntParameters : public TL1_IBETHParameters
{
public:
    
    TL1_IBETHEntParameters();

    virtual ~TL1_IBETHEntParameters();

    TL1_IBETHEntParameters(const TL1_IBETHEntParameters& theInst );

    TL1_IBETHEntParameters& operator=( const TL1_IBETHEntParameters& theInst );

    bool operator==( const TL1_IBETHEntParameters& theInst ) const;

private:
};

class TL1_IBETHEdParameters : public TL1_IBETHParameters
{
public:
    
    TL1_IBETHEdParameters();

    virtual ~TL1_IBETHEdParameters();

    TL1_IBETHEdParameters(const TL1_IBETHEdParameters& theInst );

    TL1_IBETHEdParameters& operator=( const TL1_IBETHEdParameters& theInst );

    bool operator==( const TL1_IBETHEdParameters& theInst ) const;

private:

};


inline CT_LkType*           
TL1_IBETHParameters::GetLkType( ) const
{
    return myLkType;
}

inline void                         
TL1_IBETHParameters::SetLkType( CT_LkType* theLkType )
{
    myLkType = theLkType;
}

inline int *           
TL1_IBETHParameters::GetBridge( ) const
{
    return myBridge;
}

inline void                         
TL1_IBETHParameters::SetBridge( int* theBridge )
{
    myBridge = theBridge;
}

inline int *           
TL1_IBETHParameters::GetP2PVlan( ) const
{
    return myP2PVlan;
}

inline void                         
TL1_IBETHParameters::SetP2PVlan( int* theP2PVlan )
{
    myP2PVlan = theP2PVlan;
}

inline CT_SM_PST*                   
TL1_IBETHParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_IBETHParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

inline LT_Handle*                   
TL1_IBETHParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_IBETHParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

inline LT_Ctag                     
TL1_IBETHParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_IBETHParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

#endif
