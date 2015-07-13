/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 23, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for Tarp L1 Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TARPPARAMETERS_H__
#define __TL1_TARPPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
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

class TL1_TarpEdParameters  
{
public:
    
    TL1_TarpEdParameters();

    virtual ~TL1_TarpEdParameters();

    TL1_TarpEdParameters(const TL1_TarpEdParameters& theInst );

    TL1_TarpEdParameters& operator=( const TL1_TarpEdParameters& theInst );

    bool operator==( const TL1_TarpEdParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_ProfileTableId*   GetAlarmProfile( ) const;
    inline void                 SetAlarmProfile( CT_ProfileTableId* theAlarmProfile );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline uint16*              GetFlushTimer( ) const; 
    inline void                 SetFlushTimer( uint16* theFlushTmr );

    inline uint16*              GetEntryTimer( ) const; 
    inline void                 SetEntryTimer( uint16* theEntryTmr );

    inline uint16*              GetT1Timer( ) const;     
    inline void                 SetT1Timer( uint16* theT1Tmr );

    inline uint16*              GetT2Timer( ) const;  
    inline void                 SetT2Timer( uint16* theT2Tmr );

    inline uint16*              GetT3Timer( ) const; 
    inline void                 SetT3Timer( uint16* theT3Tmr );

    inline uint16*              GetT4Timer( ) const;  
    inline void                 SetT4Timer( uint16* theT4Tmr );

    inline uint16*              GetProtocolAddress( ) const;
    inline void                 SetProtocolAddress( uint16* theProtAddr );

    inline uint16*              GetSequenceNumber( ) const;
    inline void                 SetSequenceNumber( uint16* theSeqNum );

    inline uint32*              GetLifetimeTarpMsg( ) const; 
    inline void                 SetLifetimeTarpMsg( uint32* theLFTarpMsg );

    inline CT_TarpResetType*    GetResetType( ) const;
    inline void                 SetResetType( CT_TarpResetType* theResetType );

    inline bool*                GetIsCommandForced( ) const;
    inline void                 SetIsCommandForced( bool* theIsCommandForced );

private:

    LT_Handle*          myHandle;
    LT_Ctag             myCtag;
    CT_ProfileTableId*  myAlarmProfile;
    CT_SM_PST*          myPrimaryState;
    bool*               myIsCommandForced;

    uint16*             myFlushTmr;
    uint16*             myEntryTmr;
    uint16*             myT1Tmr;
    uint16*             myT2Tmr;
    uint16*             myT3Tmr;
    uint16*             myT4Tmr;
    uint16*             myProtAddr;
    uint16*             mySeqNum;
    uint32*             myLFTarpMsg;
    CT_TarpResetType*   myResetType;

};

//--------------------------------------------------------------------------------
inline CT_ProfileTableId*           
TL1_TarpEdParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_TarpEdParameters::SetAlarmProfile( CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_TarpEdParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_TarpEdParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_TarpEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_TarpEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_TarpEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_TarpEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline bool*                        
TL1_TarpEdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_TarpEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetFlushTimer( ) const 
{
    return myFlushTmr;
}
inline void                 
TL1_TarpEdParameters::SetFlushTimer( uint16* theFlushTmr )
{
    myFlushTmr = theFlushTmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetEntryTimer( ) const 
{
    return myEntryTmr;
}

inline void                 
TL1_TarpEdParameters::SetEntryTimer( uint16* theEntryTmr )
{
    myEntryTmr = theEntryTmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetT1Timer( ) const     
{
    return myT1Tmr;
}

inline void                 
TL1_TarpEdParameters::SetT1Timer( uint16* theT1Tmr )
{
    myT1Tmr = theT1Tmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetT2Timer( ) const  
{
    return myT2Tmr;
}

inline void                 
TL1_TarpEdParameters::SetT2Timer( uint16* theT2Tmr )
{
    myT2Tmr = theT2Tmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetT3Timer( ) const 
{
    return myT3Tmr;
}

inline void                 
TL1_TarpEdParameters::SetT3Timer( uint16* theT3Tmr )
{
    myT3Tmr = theT3Tmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetT4Timer( ) const  
{
    return myT4Tmr;
}

inline void                 
TL1_TarpEdParameters::SetT4Timer( uint16* theT4Tmr )
{
    myT4Tmr = theT4Tmr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetProtocolAddress( ) const
{
    return myProtAddr;
}

inline void                 
TL1_TarpEdParameters::SetProtocolAddress( uint16* theProtAddr )
{
    myProtAddr = theProtAddr;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_TarpEdParameters::GetSequenceNumber( ) const
{
    return mySeqNum;
}

inline void                 
TL1_TarpEdParameters::SetSequenceNumber( uint16* theSeqNum )
{
    mySeqNum = theSeqNum;
}

//--------------------------------------------------------------------------------
inline uint32*              
TL1_TarpEdParameters::GetLifetimeTarpMsg( ) const 
{
    return myLFTarpMsg;
}

inline void                 
TL1_TarpEdParameters::SetLifetimeTarpMsg( uint32* theLFTarpMsg )
{
    myLFTarpMsg = theLFTarpMsg;
}

//--------------------------------------------------------------------------------
inline CT_TarpResetType*   
TL1_TarpEdParameters::GetResetType( ) const
{
    return myResetType;

}

inline void                 
TL1_TarpEdParameters::SetResetType( CT_TarpResetType* theResetType )
{
    myResetType = theResetType;
}





#endif
