/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         December 30, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for LAPD Profile TL1 EDIT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDPROFILEEDPARAMETERS_H__
#define __TL1_LAPDPROFILEEDPARAMETERS_H__

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

class TL1_LAPDProfileEdParameters  
{
public:
    
    TL1_LAPDProfileEdParameters();

    virtual ~TL1_LAPDProfileEdParameters();

    TL1_LAPDProfileEdParameters(const TL1_LAPDProfileEdParameters& theBlock );

    TL1_LAPDProfileEdParameters& operator=( const TL1_LAPDProfileEdParameters& theBlock );

    bool operator==( const TL1_LAPDProfileEdParameters& theBlock ) const;

    inline CT_LPF_TxMode*           GetTransferMode( ) const;
    inline void				        SetTransferMode( CT_LPF_TxMode* theTransferMode );

    inline uint16*                  GetRetransmitCount( ) const;
    inline void                     SetRetransmitCount( uint16* theRetransmitCount );

    inline CT_LapdProfile_Timer*    GetAckTimer( ) const;
    inline void                     SetAckTimer( CT_LapdProfile_Timer* theAckTimer );

    inline uint16*                  GetMaxSize( ) const;
    inline void                     SetMaxSize( uint16* theMaxSize );

    inline uint16*                  GetFrameCount( ) const;
    inline void                     SetFrameCount( uint16* theFrameCount );

    inline uint16*                  GetInactivityTimer( ) const;
    inline void                     SetInactivityTimer( uint16* theInactivityTimer );

    inline CT_LPF_Side*             GetSide( ) const;
    inline void                     SetSide( CT_LPF_Side* theSide );

    inline CT_LPF_SeqNum*           GetSequenceNumber( ) const;
    inline void                     SetSequenceNumber( CT_LPF_SeqNum* theSequenceNumber );

    inline bool*                    GetIsCommandForced( ) const;
    inline void                     SetIsCommandForced( bool* theIsCommandForced );

    inline LT_Handle*               GetHandle( ) const;
    inline void                     SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                  GetCtag( ) const;
    inline void                     SetCtag( LT_Ctag theCtag );

	inline CT_Fac_TraceString*      GetPfName( ) const;
	inline void				        SetPfName( CT_Fac_TraceString* thePfname );

private:

    CT_Fac_TraceString*     myPfName;
	CT_LPF_TxMode*		    myTransferMode;
    uint16*				    myRetransmitCount;
    CT_LapdProfile_Timer*   myAckTimer;
    uint16*				    myMaxSize;
    uint16*				    myFrameCount;
    uint16*				    myInactivityTimer;
    CT_LPF_Side*		    mySide;
    CT_LPF_SeqNum*	        mySequenceNumber;
    bool*                   myIsCommandForced;
    LT_Handle*			    myHandle;
    LT_Ctag				    myCtag;
};


//--------------------------------------------------------------------------------

inline CT_LPF_TxMode*     
TL1_LAPDProfileEdParameters::GetTransferMode( ) const
{
    return myTransferMode;
}

inline void     
TL1_LAPDProfileEdParameters::SetTransferMode( CT_LPF_TxMode* theTransferMode )
{
    myTransferMode = theTransferMode;
}
//--------------------------------------------------------------------------------

inline uint16*     
TL1_LAPDProfileEdParameters::GetRetransmitCount( ) const
{
    return myRetransmitCount;
}

inline void     
TL1_LAPDProfileEdParameters::SetRetransmitCount( uint16* theRetransmitCount )
{
    myRetransmitCount = theRetransmitCount;
}
//--------------------------------------------------------------------------------

inline CT_LapdProfile_Timer*     
TL1_LAPDProfileEdParameters::GetAckTimer( ) const
{   
    return myAckTimer;
}

inline void    
TL1_LAPDProfileEdParameters::SetAckTimer( CT_LapdProfile_Timer* theAckTimer )
{
    myAckTimer = theAckTimer;
}
//--------------------------------------------------------------------------------

inline uint16*     
TL1_LAPDProfileEdParameters::GetMaxSize( ) const
{
    return myMaxSize;
}

inline void     
TL1_LAPDProfileEdParameters::SetMaxSize( uint16* theMaxSize )
{
    myMaxSize = theMaxSize;
}
//--------------------------------------------------------------------------------

inline uint16*     
TL1_LAPDProfileEdParameters::GetFrameCount( ) const
{
    return myFrameCount;
}

inline void     
TL1_LAPDProfileEdParameters::SetFrameCount( uint16* theFrameCount )
{
    myFrameCount = theFrameCount;
}
//--------------------------------------------------------------------------------

inline uint16*     
TL1_LAPDProfileEdParameters::GetInactivityTimer( ) const
{
    return myInactivityTimer;
}

inline void     
TL1_LAPDProfileEdParameters::SetInactivityTimer( uint16* theInactivityTimer )
{
    myInactivityTimer = theInactivityTimer;
}
//--------------------------------------------------------------------------------

inline CT_LPF_Side*     
TL1_LAPDProfileEdParameters::GetSide( ) const
{
    return mySide;
}

inline void     
TL1_LAPDProfileEdParameters::SetSide( CT_LPF_Side* theSide )
{
    mySide = theSide;
}
//--------------------------------------------------------------------------------

inline CT_LPF_SeqNum*     
TL1_LAPDProfileEdParameters::GetSequenceNumber( ) const
{
    return mySequenceNumber;
}

inline void     
TL1_LAPDProfileEdParameters::SetSequenceNumber( CT_LPF_SeqNum* theSequenceNumber )
{
    mySequenceNumber = theSequenceNumber;
}
//--------------------------------------------------------------------------------

inline LT_Handle*                   
TL1_LAPDProfileEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_LAPDProfileEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}
//--------------------------------------------------------------------------------

inline LT_Ctag                     
TL1_LAPDProfileEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_LAPDProfileEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_Fac_TraceString* 
TL1_LAPDProfileEdParameters::GetPfName( ) const
{
	return myPfName;
}

inline void				   
TL1_LAPDProfileEdParameters::SetPfName( CT_Fac_TraceString* thePfname )
{
	myPfName = thePfname;
}

//--------------------------------------------------------------------------------
inline bool*                        
TL1_LAPDProfileEdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_LAPDProfileEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}
#endif
