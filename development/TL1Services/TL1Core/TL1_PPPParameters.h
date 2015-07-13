/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Header file for PPP, PPPPF TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PPPPARAMETERS_H__
#define __TL1_PPPPARAMETERS_H__

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

#include <CommonTypes/CT_DCC_Definitions.h>

class TL1_PPPParameters  
{
public:
    
    TL1_PPPParameters();

    virtual ~TL1_PPPParameters();

    TL1_PPPParameters(const TL1_PPPParameters& theInst );

    TL1_PPPParameters& operator=( const TL1_PPPParameters& theInst );

    bool operator==( const TL1_PPPParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_ProfileTableId*   GetAlarmProfile( ) const;
    inline void                 SetAlarmProfile( CT_ProfileTableId* theAlarmProfile );

    inline uint8*   		GetNpOwner( ) const;
    inline void                 SetNpOwner( uint8* theNpOwner );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline CT_PPPProfAddr*     GetProfileAddr( ) const;
    inline void                SetProfileAddr( CT_PPPProfAddr* theProfileAddr );
    
private:

    LT_Handle*          myHandle;
    LT_Ctag             myCtag;
    CT_ProfileTableId*  myAlarmProfile;
    uint8*  		myNpOwner;
    CT_SM_PST*          myPrimaryState;
    CT_PPPProfAddr*     myProfileAddr;
};

class TL1_PPPEntParameters : public TL1_PPPParameters
{
public:
    
    TL1_PPPEntParameters();

    virtual ~TL1_PPPEntParameters();

    TL1_PPPEntParameters(const TL1_PPPEntParameters& theInst );

    TL1_PPPEntParameters& operator=( const TL1_PPPEntParameters& theInst );

    bool operator==( const TL1_PPPEntParameters& theInst ) const;

private:
};

class TL1_PPPEdParameters : public TL1_PPPParameters
{
public:
    
    TL1_PPPEdParameters();

    virtual ~TL1_PPPEdParameters();

    TL1_PPPEdParameters(const TL1_PPPEdParameters& theInst );

    TL1_PPPEdParameters& operator=( const TL1_PPPEdParameters& theInst );

    bool operator==( const TL1_PPPEdParameters& theInst ) const;

    inline bool* GetIsCommandForced( ) const;
    inline void  SetIsCommandForced( bool* theIsCommandForced );
    inline bool  GetIsCommandFRCD( ) const;

    bool IsControlPlaneRequest();

private:

    bool*   myIsCommandForced;
};



class TL1_PPPProfileEdParameters  
{
public:
    
    TL1_PPPProfileEdParameters();

    virtual ~TL1_PPPProfileEdParameters();

    TL1_PPPProfileEdParameters(const TL1_PPPProfileEdParameters& theBlock );

    TL1_PPPProfileEdParameters& operator=( const TL1_PPPProfileEdParameters& theBlock );

    bool operator==( const TL1_PPPProfileEdParameters& theBlock ) const;

    inline uint16*                  GetMaxUnits( ) const;
    inline void                     SetMaxUnits( uint16* theMaxUnits );

    inline LT_Handle*               GetHandle( ) const;
    inline void                     SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                  GetCtag( ) const;
    inline void                     SetCtag( LT_Ctag theCtag );

    inline string*                  GetPfName( ) const;
    inline void                     SetPfName( string* thePfname );

    inline CT_FCS*                  GetFCS( ) const;
    inline void                     SetFCS( CT_FCS* theFCS );

    inline uint16*                  GetRestartTimer( ) const;
    inline void                     SetRestartTimer( uint16* theRestartTimer );

    inline uint16*                  GetMaxFailureCount( ) const;
    inline void                     SetMaxFailureCount( uint16* theMaxFailureCount );

private:

    string*             myPfName;
    uint16*			    myMaxUnits;
    CT_FCS*             myFCS;
    uint16*			    myRestartTimer;
    uint16*			    myMaxFailureCount;
    LT_Handle*          myHandle;
    LT_Ctag			    myCtag;
};


//--------------------------------------------------------------------------------
inline CT_ProfileTableId*           
TL1_PPPParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_PPPParameters::SetAlarmProfile( CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------------------------
inline uint8*           
TL1_PPPParameters::GetNpOwner( ) const
{
    return myNpOwner;
}

inline void                         
TL1_PPPParameters::SetNpOwner( uint8* theNpOwner )
{
    myNpOwner = theNpOwner;
}

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_PPPParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_PPPParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_PPPParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_PPPParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_PPPParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_PPPParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}


//--------------------------------------------------------------------------------
inline bool*                        
TL1_PPPEdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_PPPEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}

inline bool                         
TL1_PPPEdParameters::GetIsCommandFRCD( ) const
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
TL1_PPPParameters::GetProfileAddr( ) const
{
    return myProfileAddr;
}

inline void             
TL1_PPPParameters::SetProfileAddr( CT_PPPProfAddr* theProfileAddr )
{
    myProfileAddr = theProfileAddr;
}


//--------------------------------------------------------------------------------
inline uint16*     
TL1_PPPProfileEdParameters::GetMaxUnits( ) const
{
    return myMaxUnits;
}

inline void     
TL1_PPPProfileEdParameters::SetMaxUnits( uint16* theMaxUnits )
{
    myMaxUnits = theMaxUnits;
}


//--------------------------------------------------------------------------------
inline CT_FCS*     
TL1_PPPProfileEdParameters::GetFCS( ) const
{
    return myFCS;
}

inline void     
TL1_PPPProfileEdParameters::SetFCS( CT_FCS* theFCS )
{
    myFCS = theFCS;
}


//--------------------------------------------------------------------------------
inline uint16*     
TL1_PPPProfileEdParameters::GetRestartTimer( ) const
{
    return myRestartTimer;
}

inline void     
TL1_PPPProfileEdParameters::SetRestartTimer( uint16* theRestartTimer )
{
    myRestartTimer = theRestartTimer;
}


//--------------------------------------------------------------------------------
inline uint16*     
TL1_PPPProfileEdParameters::GetMaxFailureCount( ) const
{
    return myMaxFailureCount;
}

inline void     
TL1_PPPProfileEdParameters::SetMaxFailureCount( uint16* theMaxFailureCount )
{
    myMaxFailureCount = theMaxFailureCount;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_PPPProfileEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_PPPProfileEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}


//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_PPPProfileEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_PPPProfileEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline string*
TL1_PPPProfileEdParameters::GetPfName( ) const
{
        return myPfName;
}

inline void
TL1_PPPProfileEdParameters::SetPfName( string* thePfname )
{
        myPfName = thePfname;
}

#endif
