/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 25, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for LAPD TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDPARAMETERS_H__
#define __TL1_LAPDPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#include <LumosTypes/LT_System.h>

#include <CommonTypes/CT_DCC_Definitions.h>

class TL1_LAPDParameters  
{
public:
    
    TL1_LAPDParameters();

    virtual ~TL1_LAPDParameters();

    TL1_LAPDParameters(const TL1_LAPDParameters& theInst );

    TL1_LAPDParameters& operator=( const TL1_LAPDParameters& theInst );

    bool operator==( const TL1_LAPDParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_ProfileTableId*   GetAlarmProfile( ) const;
    inline void                 SetAlarmProfile( CT_ProfileTableId* theAlarmProfile );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline CT_LAPD_FlwProt*     GetFlwProtection( ) const;
    inline void                 SetFlwProtection( CT_LAPD_FlwProt* theFlwProtection );

    inline CT_LAPD_CheckSum*    GetChkSumEnable( ) const;
    inline void                 SetChkSumEnable( CT_LAPD_CheckSum* theChkSumEnable );

    inline uint16*              GetHldTmrMult( ) const;
    inline void                 SetHldTmrMult( uint16* theHldTmrMult );

    inline uint16*              GetConfigTmr( ) const;
    inline void                 SetConfigTmr( uint16* theConfigTmr );

    inline uint16*              GetHelloTmr( ) const;
    inline void                 SetHelloTmr( uint16* theHelloTmr );

    inline uint16*              GetLMetric( ) const;
    inline void                 SetLMetric( uint16* theLMetric );

    inline uint16*              GetReDirectHldTmr( ) const;
    inline void                 SetReDirectHldTmr( uint16* theReDirectHldTmr );

    inline uint16*              GetRoutingLevel( ) const;
    inline void                 SetRoutingLevel( uint16* theRoutingLevel );

    inline uint16*              GetEsConfigTmr( ) const;
    inline void                 SetEsConfigTmr( uint16* theEsConfigTmr );

    inline CT_LapdProfAddr*     GetProfileAddr( ) const;
    inline void                 SetProfileAddr( CT_LapdProfAddr* theProfileAddr );

private:

    LT_Handle*          myHandle;
    LT_Ctag             myCtag;
    CT_ProfileTableId*  myAlarmProfile;
    CT_SM_PST*          myPrimaryState;

    CT_LAPD_FlwProt*    myFlwProtection;
    CT_LAPD_CheckSum*   myChkSumEnable;
    CT_LapdProfAddr*    myProfileAddr;
    uint16*             myHldTmrMult;
    uint16*             myConfigTmr;
    uint16*             myHelloTmr;
    uint16*             myLMetric;
    uint16*             myReDirectHldTmr;
    uint16*             myRoutingLevel;
    uint16*             myEsConfigTmr;
};

class TL1_LAPDEntParameters : public TL1_LAPDParameters
{
public:
    
    TL1_LAPDEntParameters();

    virtual ~TL1_LAPDEntParameters();

    TL1_LAPDEntParameters(const TL1_LAPDEntParameters& theInst );

    TL1_LAPDEntParameters& operator=( const TL1_LAPDEntParameters& theInst );

    bool operator==( const TL1_LAPDEntParameters& theInst ) const;

    inline CT_OSIRtrAddr*   GetRouterAddr( ) const;
    inline void             SetRouterAddr( CT_OSIRtrAddr* theRouterAddr );

private:

    CT_OSIRtrAddr*      myRouterAddr;
};

class TL1_LAPDEdParameters : public TL1_LAPDParameters
{
public:
    
    TL1_LAPDEdParameters();

    virtual ~TL1_LAPDEdParameters();

    TL1_LAPDEdParameters(const TL1_LAPDEdParameters& theInst );

    TL1_LAPDEdParameters& operator=( const TL1_LAPDEdParameters& theInst );

    bool operator==( const TL1_LAPDEdParameters& theInst ) const;

    inline bool* GetIsCommandForced( ) const;
    inline void  SetIsCommandForced( bool* theIsCommandForced );
    inline bool  GetIsCommandFRCD( ) const;

private:

    bool*   myIsCommandForced;
};

//--------------------------------------------------------------------------------
inline CT_ProfileTableId*           
TL1_LAPDParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_LAPDParameters::SetAlarmProfile( CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_LAPDParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_LAPDParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_LAPDParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_LAPDParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_LAPDParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_LAPDParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_LAPD_FlwProt*     
TL1_LAPDParameters::GetFlwProtection( ) const
{
    return myFlwProtection;
}

inline void                 
TL1_LAPDParameters::SetFlwProtection( CT_LAPD_FlwProt* theFlwProtection )
{
    myFlwProtection = theFlwProtection;
}

//--------------------------------------------------------------------------------
inline CT_LAPD_CheckSum*    
TL1_LAPDParameters::GetChkSumEnable( ) const
{
    return myChkSumEnable;
}

inline void                 
TL1_LAPDParameters::SetChkSumEnable( CT_LAPD_CheckSum* theChkSumEnable )
{
    myChkSumEnable = theChkSumEnable;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_LAPDParameters::GetHldTmrMult( ) const
{
    return myHldTmrMult;
}

inline void                 
TL1_LAPDParameters::SetHldTmrMult( uint16* theHldTmrMult )
{
    myHldTmrMult = theHldTmrMult;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_LAPDParameters::GetConfigTmr( ) const
{
    return myConfigTmr;
}

inline void                 
TL1_LAPDParameters::SetConfigTmr( uint16* theConfigTmr )
{
    myConfigTmr = theConfigTmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_LAPDParameters::GetHelloTmr( ) const
{
    return myHelloTmr;
}

inline void                 
TL1_LAPDParameters::SetHelloTmr( uint16* theHelloTmr )
{
    myHelloTmr = theHelloTmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_LAPDParameters::GetLMetric( ) const
{
    return myLMetric;
}

inline void                 
TL1_LAPDParameters::SetLMetric( uint16* theLMetric )
{
    myLMetric = theLMetric;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_LAPDParameters::GetReDirectHldTmr( ) const
{
    return myReDirectHldTmr; 
}

inline void                 
TL1_LAPDParameters::SetReDirectHldTmr( uint16* theReDirectHldTmr )
{
    myReDirectHldTmr = theReDirectHldTmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_LAPDParameters::GetRoutingLevel( ) const
{
    return myRoutingLevel;
}

inline void                 
TL1_LAPDParameters::SetRoutingLevel( uint16* theRoutingLevel )
{
    myRoutingLevel = theRoutingLevel;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_LAPDParameters::GetEsConfigTmr( ) const
{
    return myEsConfigTmr;
}

inline void                 
TL1_LAPDParameters::SetEsConfigTmr( uint16* theEsConfigTmr )
{
    myEsConfigTmr = theEsConfigTmr;
}
 
//--------------------------------------------------------------------------------
inline bool*                        
TL1_LAPDEdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_LAPDEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}

inline bool                         
TL1_LAPDEdParameters::GetIsCommandFRCD( ) const
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
inline CT_LapdProfAddr* 
TL1_LAPDParameters::GetProfileAddr( ) const
{
    return myProfileAddr;
}

inline void             
TL1_LAPDParameters::SetProfileAddr( CT_LapdProfAddr* theProfileAddr )
{
    myProfileAddr = theProfileAddr;
}

//--------------------------------------------------------------------------------
inline CT_OSIRtrAddr*    
TL1_LAPDEntParameters::GetRouterAddr( ) const
{
    return myRouterAddr;
}


inline void              
TL1_LAPDEntParameters::SetRouterAddr( CT_OSIRtrAddr* theRouterAddr )
{
    myRouterAddr = theRouterAddr;
}

#endif
