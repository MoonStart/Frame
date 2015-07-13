/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 26, 2007 - Tong Wu
DESCRIPTION:    Header file for NP TL1 ENT and ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NPPARAMETERS_H__
#define __TL1_NPPARAMETERS_H__

#include <LumosTypes/LT_System.h>

#ifndef __TL1_NP_RESPONSE_BLOCK_H__
#include <Response/TL1_NpRspBlk.h>
#endif

class TL1_NPParameters  
{
public:
    
    TL1_NPParameters();

    virtual ~TL1_NPParameters();

    TL1_NPParameters(const TL1_NPParameters& theInst );

    TL1_NPParameters& operator=( const TL1_NPParameters& theInst );

    bool operator==( const TL1_NPParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline string*              GetNpName( ) const;
    inline void                 SetNpName( string* theNpName );

    inline uint16*              GetTimeout( ) const;
    inline void                 SetTimeout( uint16* theTimeout );

private:

    LT_Handle*            myHandle;
    LT_Ctag               myCtag;
    CT_SM_PST*            myPrimaryState;

    string*               myNpName;
    uint16*               myTimeout;
};

class TL1_NPEntParameters : public TL1_NPParameters
{
public:
    
    TL1_NPEntParameters();

    virtual ~TL1_NPEntParameters();

    TL1_NPEntParameters(const TL1_NPEntParameters& theInst );

    TL1_NPEntParameters& operator=( const TL1_NPEntParameters& theInst );

    bool operator==( const TL1_NPEntParameters& theInst ) const;

};

class TL1_NPEdParameters : public TL1_NPParameters
{
public:
    
    TL1_NPEdParameters();

    virtual ~TL1_NPEdParameters();

    TL1_NPEdParameters(const TL1_NPEdParameters& theInst );

    TL1_NPEdParameters& operator=( const TL1_NPEdParameters& theInst );

    bool operator==( const TL1_NPEdParameters& theInst ) const;

};


//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_NPParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_NPParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_NPParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_NPParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_NPParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_NPParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline string*    
TL1_NPParameters::GetNpName( ) const
{
    return myNpName;
}


inline void              
TL1_NPParameters::SetNpName( string* theNpName )
{
    myNpName = theNpName;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_NPParameters::GetTimeout( ) const
{
    return myTimeout;
}

inline void                 
TL1_NPParameters::SetTimeout( uint16* theTimeout )
{
    myTimeout = theTimeout;
}
 

#endif
