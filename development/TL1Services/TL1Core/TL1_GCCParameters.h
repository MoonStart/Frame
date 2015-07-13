/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Shawn He
DESCRIPTION:    Header file for GCC TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_GCCPARAMETERS_H__
#define __TL1_GCCPARAMETERS_H__

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

#ifndef __TL1_PPPDOMAIN_H__
#include <TL1Core/TL1_PPPParameters.h>
#endif


#include <LumosTypes/LT_System.h>

#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_OduDefinitions.h>

class TL1_GCCParameters  
{
public:
    
    TL1_GCCParameters();

    virtual ~TL1_GCCParameters();

    TL1_GCCParameters(const TL1_GCCParameters& theInst );

    TL1_GCCParameters& operator=( const TL1_GCCParameters& theInst );

    bool operator==( const TL1_GCCParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_ProfileTableId*   GetAlarmProfile( ) const;
    inline void                 SetAlarmProfile( CT_ProfileTableId* theAlarmProfile );

    inline uint8*   		    GetNpOwner( ) const;
    inline void                 SetNpOwner( uint8* theNpOwner );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline CT_PPPProfAddr*      GetProfileAddr( ) const;
    inline void                 SetProfileAddr( CT_PPPProfAddr* theProfileAddr );

    inline CT_GCC_Type*         GetType() const;
    inline void                 SetType( CT_GCC_Type*  theType );

private:

    LT_Handle*          myHandle;
    LT_Ctag             myCtag;
    CT_ProfileTableId*  myAlarmProfile;
    uint8*  		    myNpOwner;
    CT_SM_PST*          myPrimaryState;
    CT_PPPProfAddr*     myProfileAddr;
    CT_GCC_Type*        myType;
};

class TL1_GCCEntParameters : public TL1_GCCParameters
{
public:
    
    TL1_GCCEntParameters();

    virtual ~TL1_GCCEntParameters();

    TL1_GCCEntParameters(const TL1_GCCEntParameters& theInst );

    TL1_GCCEntParameters& operator=( const TL1_GCCEntParameters& theInst );

    bool operator==( const TL1_GCCEntParameters& theInst ) const;

private:
};

class TL1_GCCEdParameters : public TL1_GCCParameters
{
public:
    
    TL1_GCCEdParameters();

    virtual ~TL1_GCCEdParameters();

    TL1_GCCEdParameters(const TL1_GCCEdParameters& theInst );

    TL1_GCCEdParameters& operator=( const TL1_GCCEdParameters& theInst );

    bool operator==( const TL1_GCCEdParameters& theInst ) const;

    inline bool* GetIsCommandForced( ) const;
    inline void  SetIsCommandForced( bool* theIsCommandForced );
    inline bool  GetIsCommandFRCD( ) const;

    bool IsControlPlaneRequest();

private:

    bool*   myIsCommandForced;
};

//--------------------------------------------------------------------------------
inline CT_ProfileTableId*           
TL1_GCCParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_GCCParameters::SetAlarmProfile( CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------------------------
inline uint8*           
TL1_GCCParameters::GetNpOwner( ) const
{
    return myNpOwner;
}

inline void                         
TL1_GCCParameters::SetNpOwner( uint8* theNpOwner )
{
    myNpOwner = theNpOwner;
}

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_GCCParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_GCCParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_GCCParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_GCCParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_GCCParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_GCCParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}


//--------------------------------------------------------------------------------
inline bool*                        
TL1_GCCEdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_GCCEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}

inline bool                         
TL1_GCCEdParameters::GetIsCommandFRCD( ) const
{
    if ( GetIsCommandForced( ) )
    {
        if ( *GetIsCommandForced( ) )
        {
            return true;
        }
    }

    return false;
}


//--------------------------------------------------------------------------------
inline CT_PPPProfAddr* 
TL1_GCCParameters::GetProfileAddr( ) const
{
    return myProfileAddr;
}

inline void             
TL1_GCCParameters::SetProfileAddr( CT_PPPProfAddr* theProfileAddr )
{
    myProfileAddr = theProfileAddr;
}


//--------------------------------------------------------------------------------
inline CT_GCC_Type*  
TL1_GCCParameters::GetType( ) const
{
    return myType;
}

inline void 
TL1_GCCParameters::SetType( CT_GCC_Type*  theType )
{
    myType = theType;
}

#endif
