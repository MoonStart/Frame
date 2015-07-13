/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 11, 2006 - Thomas J. Novak
DESCRIPTION:    Header file for OSI TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSIPARAMETERS_H__
#define __TL1_OSIPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#include <LumosTypes/LT_System.h>

#include <CommonTypes/CT_DCC_Definitions.h>

class TL1_OSIRTRParameters  
{
public:
    
    TL1_OSIRTRParameters();

    virtual ~TL1_OSIRTRParameters();

    TL1_OSIRTRParameters(const TL1_OSIRTRParameters& theInst );

    TL1_OSIRTRParameters& operator=( const TL1_OSIRTRParameters& theInst );

    bool operator==( const TL1_OSIRTRParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline CT_ProfileTableId*   GetAlarmProfile( ) const;
    inline void                 SetAlarmProfile( CT_ProfileTableId* theAlarmProfile );

    inline CT_SM_PST*           GetPrimaryState( ) const;
    inline void                 SetPrimaryState( CT_SM_PST* thePrimaryState );

    inline string*              GetPrimaryAddress( ) const;
    inline void                 SetPrimaryAddress( string* thePrimaryAddr );

    inline string*              GetAuxillaryAddress1( ) const;
    inline void                 SetAuxillaryAddress1( string* theAuxAddr1 );

    inline string*              GetAuxillaryAddress2( ) const;
    inline void                 SetAuxillaryAddress2( string* theAuxAddr2 );

    inline string*              GetRoutingSysId( ) const;
    inline void                 SetRoutingSysId( string* theRSysId );

    inline uint16*              GetMaxLifetimeControl( ) const;
    inline void                 SetMaxLifetimeControl( uint16* theMaxLifetime );

    inline uint16*              GetRoutingLevel( ) const;
    inline void                 SetRoutingLevel( uint16* theLevel );

    inline uint16*              GetMaxAreaAddress( ) const;
    inline void                 SetMaxAreaAddress( uint16* theNumMaxArea );

    inline bool*				GetEonGre( ) const;
    inline void                 SetEonGre( bool* theEonGre ); 

private:

    LT_Handle*          myHandle;
    LT_Ctag             myCtag;
    CT_ProfileTableId*  myAlarmProfile;
    CT_SM_PST*          myPrimaryState;
    bool*				myEonGre; 

    string*             myPrimaryAddr; 
    string*             myAuxAddr1; 
    string*             myAuxAddr2; 
    string*             myRSysId; 
    uint16*             myMaxLifetime; 
    uint16*             myLevel; 
    uint16*             myNumMaxArea; 
};

class TL1_OSIRTREntParameters : public TL1_OSIRTRParameters
{
public:
    
    TL1_OSIRTREntParameters();

    virtual ~TL1_OSIRTREntParameters();

    TL1_OSIRTREntParameters(const TL1_OSIRTREntParameters& theInst );

    TL1_OSIRTREntParameters& operator=( const TL1_OSIRTREntParameters& theInst );

    bool operator==( const TL1_OSIRTREntParameters& theInst ) const;

private:

};

class TL1_OSIRTREdParameters : public TL1_OSIRTRParameters
{
public:
    
    TL1_OSIRTREdParameters();

    virtual ~TL1_OSIRTREdParameters();

    TL1_OSIRTREdParameters(const TL1_OSIRTREdParameters& theInst );

    TL1_OSIRTREdParameters& operator=( const TL1_OSIRTREdParameters& theInst );

    bool operator==( const TL1_OSIRTREdParameters& theInst ) const;

    inline bool* GetIsCommandForced( ) const;
    inline void  SetIsCommandForced( bool* theIsCommandForced );
    inline bool  GetIsCommandFRCD( ) const;

private:

    bool*   myIsCommandForced;
};

//--------------------------------------------------------------------------------
inline CT_ProfileTableId*           
TL1_OSIRTRParameters::GetAlarmProfile( ) const
{
    return myAlarmProfile;
}

inline void                         
TL1_OSIRTRParameters::SetAlarmProfile( CT_ProfileTableId* theAlarmProfile )
{
    myAlarmProfile = theAlarmProfile;
}

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_OSIRTRParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_OSIRTRParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_OSIRTRParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_OSIRTRParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_OSIRTRParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_OSIRTRParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline string*              
TL1_OSIRTRParameters::GetPrimaryAddress( ) const
{
    return myPrimaryAddr;
}

inline void                 
TL1_OSIRTRParameters::SetPrimaryAddress( string* thePrimaryAddr )
{
    myPrimaryAddr = thePrimaryAddr;
}

//--------------------------------------------------------------------------------
inline string*              
TL1_OSIRTRParameters::GetAuxillaryAddress1( ) const
{
    return myAuxAddr1;
}

inline void                 
TL1_OSIRTRParameters::SetAuxillaryAddress1( string* theAuxAddr1 )
{
    myAuxAddr1 = theAuxAddr1;
}

//--------------------------------------------------------------------------------
inline string*              
TL1_OSIRTRParameters::GetAuxillaryAddress2( ) const
{
    return myAuxAddr2;
}

inline void                
TL1_OSIRTRParameters::SetAuxillaryAddress2( string* theAuxAddr2 )
{
    myAuxAddr2 = theAuxAddr2;
}

//--------------------------------------------------------------------------------
inline string*              
TL1_OSIRTRParameters::GetRoutingSysId( ) const
{
    return myRSysId;
}

inline void                 
TL1_OSIRTRParameters::SetRoutingSysId( string* theRSysId )
{
    myRSysId = theRSysId;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_OSIRTRParameters::GetMaxLifetimeControl( ) const
{
    return myMaxLifetime;
}

inline void                 
TL1_OSIRTRParameters::SetMaxLifetimeControl( uint16* theMaxLifetime )
{
    myMaxLifetime = theMaxLifetime; 
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_OSIRTRParameters::GetRoutingLevel( ) const
{
    return myLevel;
}

inline void                 
TL1_OSIRTRParameters::SetRoutingLevel( uint16* theLevel )
{
    myLevel = theLevel;
}

//--------------------------------------------------------------------------------
inline uint16*              
TL1_OSIRTRParameters::GetMaxAreaAddress( ) const 
{
    return myNumMaxArea;
}

inline void                 
TL1_OSIRTRParameters::SetMaxAreaAddress( uint16* theNumMaxArea )
{
    myNumMaxArea = theNumMaxArea;  
}


//--------------------------------------------------------------------------------
inline bool*              
TL1_OSIRTRParameters::GetEonGre( ) const 
{
    return myEonGre;
}

inline void                 
TL1_OSIRTRParameters::SetEonGre( bool* theEonGre )
{
    myEonGre = theEonGre;  
}


//--------------------------------------------------------------------------------
inline bool*                        
TL1_OSIRTREdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_OSIRTREdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}


inline bool                         
TL1_OSIRTREdParameters::GetIsCommandFRCD( ) const
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


#endif
