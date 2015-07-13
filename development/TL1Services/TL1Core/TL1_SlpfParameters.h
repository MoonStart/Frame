/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 08, 2007 - Tong Wu
DESCRIPTION:    Header file for SLPF and SLPOLICY TL1 ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLPFPARAMETERS_H__
#define __TL1_SLPFPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_SLPFRSPBLK_H__
#include <Response/TL1_SlpfRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>


class TL1_SlpfEdParameters  
{
public:
    
    TL1_SlpfEdParameters();

    virtual ~TL1_SlpfEdParameters();

    TL1_SlpfEdParameters(const TL1_SlpfEdParameters& theInst );

    TL1_SlpfEdParameters& operator=( const TL1_SlpfEdParameters& theInst );

    bool operator==( const TL1_SlpfEdParameters& theInst ) const;

    inline LT_Handle*           GetHandle( ) const;
    inline void                 SetHandle( LT_Handle* theHandle );

    inline LT_Ctag              GetCtag( ) const;
    inline void                 SetCtag( LT_Ctag theCtag );

    inline string*              GetProfileName( ) const;
    inline void                 SetProfileName( string* theProfileName  );

    inline CT_SLPF_ProtLvl*     GetProtLvl( ) const;
    inline void                 SetProtLvl( CT_SLPF_ProtLvl* theProtLevel );

    inline CT_SLPF_Diversity*   GetDiversity( ) const;
    inline void                 SetDiversity( CT_SLPF_Diversity* theDiversity );

    inline CT_SLPF_Params*      GetReversion( ) const;
    inline void                 SetReversion( CT_SLPF_Params* theReversion );

    inline CT_SLPF_Params*      GetCoRouting( ) const;
    inline void                 SetCoRouting( CT_SLPF_Params* theCoRouting );
    
    inline CT_SLPF_Params*      GetTransparentLineMSDCC( ) const;
    inline void                 SetTransparentLineMSDCC( CT_SLPF_Params* theTransLineMSDCC );
    
    inline CT_SLPF_Params*      GetTransparentSectionRSDCC( ) const;
    inline void                 SetTransparentSectionRSDCC( CT_SLPF_Params* theTransSectionRSDCC );
    
    inline CT_SLPF_Params*      GetTransparentOTUGCC0( ) const;
    inline void                 SetTransparentOTUGCC0( CT_SLPF_Params* theTransOTUGCC0 );
    
    inline CT_SLPF_Params*      GetTransparentODUGCC12( ) const;
    inline void                 SetTransparentODUGCC12( CT_SLPF_Params* theTransODUGCC12 );
          
    inline int*                 GetWtr( ) const;
    inline void                 SetWtr( int* theWtr );

    inline CT_SLPF_Params*      GetCallSetupReroute( ) const;
    inline void                 SetCallSetupReroute( CT_SLPF_Params* theCallSetupReroute );

    inline int*                 GetMaxRerouteAttempts( ) const;
    inline void                 SetMaxRerouteAttempts( int* theMaxRerouteAttempts );

    inline int*                 GetBackoffInterval( ) const;
    inline void                 SetBackoffInterval( int* theBackoffInterval );

    inline CT_SLPF_Params*      GetBoundReroute( ) const;
    inline void                 SetBoundReroute( CT_SLPF_Params* theBoundReroute );

    inline CT_SLPF_Params*      GetEndToEndReroute( ) const;
    inline void                 SetEndToEndReroute( CT_SLPF_Params* theEndToEndReroute );

    inline int*                 GetLatency( ) const;
    inline void                 SetLatency( int* theLatency );

    inline uint32*              GetResourceClass( ) const;
    inline void                 SetResourceClass( uint32* theResourceClass );

    inline CT_SLPF_PRIORITY*    GetPriority( ) const;
    inline void                 SetPriority( CT_SLPF_PRIORITY* thePriority );

    inline CT_Advertisement*    GetResConnA( ) const;
    inline void                 SetResConnA( CT_Advertisement* theResConnA );

    inline CT_Advertisement*    GetResConnB( ) const;
    inline void                 SetResConnB( CT_Advertisement* theResConnB );

    inline CT_Resv_Style*       GetReservationStyle( ) const;
    inline void                 SetReservationStyle( CT_Resv_Style* theReservationStyle );

    CT_Slpf_DiversityCheck*  GetDiversityCheck( ) const;
    void                     SetDiversityCheck( CT_Slpf_DiversityCheck* theDiversityCheck );

    CT_Slpf_CpReversion* GetCpReversion( ) const;
    void SetCpReversion(CT_Slpf_CpReversion* theCpReversion );
    
    int* GetCpWtr( ) const;
    void SetCpWtr( int* theCpWtr );


private:

    LT_Handle*              myHandle;
    LT_Ctag                 myCtag;
    string*                 myProfName;
    CT_SLPF_ProtLvl*        myProtLvl;
    CT_SLPF_Diversity*      myDiversity;
    CT_SLPF_Params*         myReversion;
    CT_SLPF_Params*         myCoRouting;
    CT_SLPF_Params*         myTransLineMSDCC;
    CT_SLPF_Params*         myTransSectionRSDCC;
    CT_SLPF_Params*         myTransOTUGCC0;
    CT_SLPF_Params*         myTransODUGCC12;
    int*                    myWtr;
    CT_SLPF_Params*         myCallSetupReroute;
    int*                    myMaxRerouteAttempts;
    int*                    myBackoffInterval;
    CT_SLPF_Params*         myBoundReroute;
    CT_SLPF_Params*         myEndToEndReroute;
    int*                    myLatency;
    uint32*                 myResourceClass;
    CT_SLPF_PRIORITY*       myPriority;
    CT_Resv_Style*          myReservationStyle;
    CT_Advertisement*       myResConnA;
    CT_Advertisement*       myResConnB;
    CT_Slpf_DiversityCheck*	myDiversityCheck;
    CT_Slpf_CpReversion*	myCpReversion;
    int*                    myCpWtr;
};


class TL1_SlpolicyEdParameters  
{
public:
    
    TL1_SlpolicyEdParameters();

    virtual ~TL1_SlpolicyEdParameters();

    TL1_SlpolicyEdParameters(const TL1_SlpolicyEdParameters& theInst );

    TL1_SlpolicyEdParameters& operator=( const TL1_SlpolicyEdParameters& theInst );

    bool operator==( const TL1_SlpolicyEdParameters& theInst ) const;

    inline LT_Handle*                 GetHandle( ) const;
    inline void                       SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                    GetCtag( ) const;
    inline void                       SetCtag( LT_Ctag theCtag );

    inline string*                    GetPolicyName( ) const;
    inline void                       SetPolicyName( string* thePolicyName  );

    inline uint16*                    GetSvcLvlCodePoint1( ) const;
    inline void                       SetSvcLvlCodePoint1( uint16* theSvcLvlCodePoint1 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid1( ) const;
    inline void                       SetSvcLvlProfileAid1( CT_TL1_LogicalAddr* theSvcLvlProfileAid1 );

    inline uint16*                    GetSvcLvlCodePoint2( ) const;
    inline void                       SetSvcLvlCodePoint2( uint16* theSvcLvlCodePoint2 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid2( ) const;
    inline void                       SetSvcLvlProfileAid2( CT_TL1_LogicalAddr* theSvcLvlProfileAid2 );

    inline uint16*                    GetSvcLvlCodePoint3( ) const;
    inline void                       SetSvcLvlCodePoint3( uint16* theSvcLvlCodePoint3 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid3( ) const;
    inline void                       SetSvcLvlProfileAid3( CT_TL1_LogicalAddr* theSvcLvlProfileAid3 );

    inline uint16*                    GetSvcLvlCodePoint4( ) const;
    inline void                       SetSvcLvlCodePoint4( uint16* theSvcLvlCodePoint4 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid4( ) const;
    inline void                       SetSvcLvlProfileAid4( CT_TL1_LogicalAddr* theSvcLvlProfileAid4 );

    inline uint16*                    GetSvcLvlCodePoint5( ) const;
    inline void                       SetSvcLvlCodePoint5( uint16* theSvcLvlCodePoint5 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid5( ) const;
    inline void                       SetSvcLvlProfileAid5( CT_TL1_LogicalAddr* theSvcLvlProfileAid5 );

    inline uint16*                    GetSvcLvlCodePoint6( ) const;
    inline void                       SetSvcLvlCodePoint6( uint16* theSvcLvlCodePoint6 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid6( ) const;
    inline void                       SetSvcLvlProfileAid6( CT_TL1_LogicalAddr* theSvcLvlProfileAid6 );

    inline uint16*                    GetSvcLvlCodePoint7( ) const;
    inline void                       SetSvcLvlCodePoint7( uint16* theSvcLvlCodePoint7 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid7( ) const;
    inline void                       SetSvcLvlProfileAid7( CT_TL1_LogicalAddr* theSvcLvlProfileAid7 );

    inline uint16*                    GetSvcLvlCodePoint8( ) const;
    inline void                       SetSvcLvlCodePoint8( uint16* theSvcLvlCodePoint8 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid8( ) const;
    inline void                       SetSvcLvlProfileAid8( CT_TL1_LogicalAddr* theSvcLvlProfileAid8 );

    inline uint16*                    GetSvcLvlCodePoint9( ) const;
    inline void                       SetSvcLvlCodePoint9( uint16* theSvcLvlCodePoint9 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid9( ) const;
    inline void                       SetSvcLvlProfileAid9( CT_TL1_LogicalAddr* theSvcLvlProfileAid9 );

    inline uint16*                    GetSvcLvlCodePoint10( ) const;
    inline void                       SetSvcLvlCodePoint10( uint16* theSvcLvlCodePoint10 );

    inline CT_TL1_LogicalAddr*        GetSvcLvlProfileAid10( ) const;
    inline void                       SetSvcLvlProfileAid10( CT_TL1_LogicalAddr* theSvcLvlProfileAid10 );

private:

    LT_Handle*                myHandle;
    LT_Ctag                   myCtag;
    string*                   myPolicyName;
    uint16*                   mySvcLvlCodePoint1;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid1;
    uint16*                   mySvcLvlCodePoint2;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid2;
    uint16*                   mySvcLvlCodePoint3;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid3;
    uint16*                   mySvcLvlCodePoint4;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid4;
    uint16*                   mySvcLvlCodePoint5;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid5;
    uint16*                   mySvcLvlCodePoint6;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid6;
    uint16*                   mySvcLvlCodePoint7;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid7;
    uint16*                   mySvcLvlCodePoint8;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid8;
    uint16*                   mySvcLvlCodePoint9;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid9;
    uint16*                   mySvcLvlCodePoint10;
    CT_TL1_LogicalAddr*       mySvcLvlProfileAid10;
};


//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_SlpfEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_SlpfEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_SlpfEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_SlpfEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline string*    
TL1_SlpfEdParameters::GetProfileName( ) const
{
    return myProfName;
}


inline void              
TL1_SlpfEdParameters::SetProfileName( string* theProfileName )
{
    myProfName = theProfileName;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_ProtLvl*                     
TL1_SlpfEdParameters::GetProtLvl( ) const
{
    return myProtLvl;
}

inline void                         
TL1_SlpfEdParameters::SetProtLvl( CT_SLPF_ProtLvl* theProtLevel )
{
    myProtLvl = theProtLevel;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Diversity*                     
TL1_SlpfEdParameters::GetDiversity( ) const
{
    return myDiversity;
}

inline void                         
TL1_SlpfEdParameters::SetDiversity( CT_SLPF_Diversity* theDiversity )
{
    myDiversity = theDiversity;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*    
TL1_SlpfEdParameters::GetReversion( ) const
{
    return myReversion;
}


inline void              
TL1_SlpfEdParameters::SetReversion( CT_SLPF_Params* theReversion )
{
    myReversion = theReversion;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*    
TL1_SlpfEdParameters::GetCoRouting( ) const
{
    return myCoRouting;
}


inline void              
TL1_SlpfEdParameters::SetCoRouting( CT_SLPF_Params* theCoRouting )
{
    myCoRouting = theCoRouting;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*                   
TL1_SlpfEdParameters::GetTransparentLineMSDCC( ) const
{
    return myTransLineMSDCC;
}

inline void                         
TL1_SlpfEdParameters::SetTransparentLineMSDCC( CT_SLPF_Params* theTransLineMSDCC )
{
    myTransLineMSDCC = theTransLineMSDCC;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*                     
TL1_SlpfEdParameters::GetTransparentSectionRSDCC( ) const
{
    return myTransSectionRSDCC;
}

inline void                         
TL1_SlpfEdParameters::SetTransparentSectionRSDCC( CT_SLPF_Params* theTransSectionRSDCC )
{
    myTransSectionRSDCC = theTransSectionRSDCC;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*   
TL1_SlpfEdParameters::GetTransparentOTUGCC0( ) const
{
    return myTransOTUGCC0;
}


inline void              
TL1_SlpfEdParameters::SetTransparentOTUGCC0( CT_SLPF_Params* theTransOTUGCC0 )
{
    myTransOTUGCC0 = theTransOTUGCC0;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*                     
TL1_SlpfEdParameters::GetTransparentODUGCC12( ) const
{
    return myTransODUGCC12;
}

inline void                         
TL1_SlpfEdParameters::SetTransparentODUGCC12( CT_SLPF_Params* theTransODUGCC12)
{
    myTransODUGCC12 = theTransODUGCC12;
}

//--------------------------------------------------------------------------------
inline int*                       
TL1_SlpfEdParameters::GetWtr( ) const
{
    return myWtr;
}

inline void                       
TL1_SlpfEdParameters::SetWtr( int* theWtr )
{
    myWtr = theWtr;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*            
TL1_SlpfEdParameters::GetCallSetupReroute( ) const
{
    return myCallSetupReroute;
}

inline void                       
TL1_SlpfEdParameters::SetCallSetupReroute( CT_SLPF_Params* theCallSetupReroute )
{
    myCallSetupReroute = theCallSetupReroute;
}

//--------------------------------------------------------------------------------
inline int*                       
TL1_SlpfEdParameters::GetMaxRerouteAttempts( ) const
{
    return myMaxRerouteAttempts;
}

inline void                       
TL1_SlpfEdParameters::SetMaxRerouteAttempts( int* theMaxRerouteAttempts )
{
    myMaxRerouteAttempts = theMaxRerouteAttempts;
}

//--------------------------------------------------------------------------------
inline int*                       
TL1_SlpfEdParameters::GetBackoffInterval( ) const
{
    return myBackoffInterval;
}

inline void                       
TL1_SlpfEdParameters::SetBackoffInterval( int* theBackoffInterval )
{
    myBackoffInterval = theBackoffInterval;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*            
TL1_SlpfEdParameters::GetBoundReroute( ) const
{
    return myBoundReroute;
}

inline void                       
TL1_SlpfEdParameters::SetBoundReroute( CT_SLPF_Params* theBoundReroute )
{
    myBoundReroute = theBoundReroute;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_Params*            
TL1_SlpfEdParameters::GetEndToEndReroute( ) const
{
    return myEndToEndReroute;
}

inline void                       
TL1_SlpfEdParameters::SetEndToEndReroute( CT_SLPF_Params* theEndToEndReroute )
{
    myEndToEndReroute = theEndToEndReroute;
}

//--------------------------------------------------------------------------------
inline int* 
TL1_SlpfEdParameters::GetLatency( ) const
{
    return myLatency;
}

inline void                       
TL1_SlpfEdParameters::SetLatency( int* theLatency )
{
    myLatency = theLatency;
}

//--------------------------------------------------------------------------------
inline uint32*                       
TL1_SlpfEdParameters::GetResourceClass( ) const
{
    return myResourceClass;
}

inline void                       
TL1_SlpfEdParameters::SetResourceClass( uint32* theResourceClass )
{
    myResourceClass = theResourceClass;
}

//--------------------------------------------------------------------------------
inline CT_SLPF_PRIORITY*
TL1_SlpfEdParameters::GetPriority() const
{
    return myPriority;
}

inline void
TL1_SlpfEdParameters::SetPriority( CT_SLPF_PRIORITY* thePriority )
{
    myPriority = thePriority;
}


//--------------------------------------------------------------------------------
inline CT_Resv_Style*
TL1_SlpfEdParameters::GetReservationStyle() const
{
    return myReservationStyle;
}

inline void
TL1_SlpfEdParameters::SetReservationStyle( CT_Resv_Style* theReservationStyle )
{
    myReservationStyle = theReservationStyle;
}


//--------------------------------------------------------------------------------
inline CT_Advertisement*    
TL1_SlpfEdParameters::GetResConnA( ) const
{
    return myResConnA;
}

inline void                 
TL1_SlpfEdParameters::SetResConnA( CT_Advertisement* theResConnA ) 
{
    myResConnA = theResConnA;
}

//--------------------------------------------------------------------------------
inline CT_Advertisement*    
TL1_SlpfEdParameters::GetResConnB( ) const
{
    return myResConnB;
}

inline void                 
TL1_SlpfEdParameters::SetResConnB( CT_Advertisement* theResConnB ) 
{
    myResConnB = theResConnB;
}

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_SlpolicyEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_SlpolicyEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_SlpolicyEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_SlpolicyEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline string*    
TL1_SlpolicyEdParameters::GetPolicyName( ) const
{
    return myPolicyName;
}

inline void              
TL1_SlpolicyEdParameters::SetPolicyName( string* thePolicyName )
{
    myPolicyName = thePolicyName;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint1( ) const
{
    return mySvcLvlCodePoint1;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint1( uint16* theSvcLvlCodePoint1 )
{
    mySvcLvlCodePoint1 = theSvcLvlCodePoint1;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid1( ) const
{
    return mySvcLvlProfileAid1;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid1( CT_TL1_LogicalAddr* theSvcLvlProfileAid1 )
{
    mySvcLvlProfileAid1 = theSvcLvlProfileAid1;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint2( ) const
{
    return mySvcLvlCodePoint2;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint2( uint16* theSvcLvlCodePoint2 )
{
    mySvcLvlCodePoint2 = theSvcLvlCodePoint2;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid2( ) const
{
    return mySvcLvlProfileAid2;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid2( CT_TL1_LogicalAddr* theSvcLvlProfileAid2 )
{
    mySvcLvlProfileAid2 = theSvcLvlProfileAid2;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint3( ) const
{
    return mySvcLvlCodePoint3;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint3( uint16* theSvcLvlCodePoint3 )
{
    mySvcLvlCodePoint3 = theSvcLvlCodePoint3;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid3( ) const
{
    return mySvcLvlProfileAid3;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid3( CT_TL1_LogicalAddr* theSvcLvlProfileAid3 )
{
    mySvcLvlProfileAid3 = theSvcLvlProfileAid3;
}
//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint4( ) const
{
    return mySvcLvlCodePoint4;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint4( uint16* theSvcLvlCodePoint4 )
{
    mySvcLvlCodePoint4 = theSvcLvlCodePoint4;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid4( ) const
{
    return mySvcLvlProfileAid4;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid4( CT_TL1_LogicalAddr* theSvcLvlProfileAid4 )
{
    mySvcLvlProfileAid4 = theSvcLvlProfileAid4;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint5( ) const
{
    return mySvcLvlCodePoint5;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint5( uint16* theSvcLvlCodePoint5 )
{
    mySvcLvlCodePoint5 = theSvcLvlCodePoint5;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid5( ) const
{
    return mySvcLvlProfileAid5;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid5( CT_TL1_LogicalAddr* theSvcLvlProfileAid5 )
{
    mySvcLvlProfileAid5 = theSvcLvlProfileAid5;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint6( ) const
{
    return mySvcLvlCodePoint6;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint6( uint16* theSvcLvlCodePoint6 )
{
    mySvcLvlCodePoint6 = theSvcLvlCodePoint6;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid6( ) const
{
    return mySvcLvlProfileAid6;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid6( CT_TL1_LogicalAddr* theSvcLvlProfileAid6 )
{
    mySvcLvlProfileAid6 = theSvcLvlProfileAid6;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint7( ) const
{
    return mySvcLvlCodePoint7;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint7( uint16* theSvcLvlCodePoint7 )
{
    mySvcLvlCodePoint7 = theSvcLvlCodePoint7;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid7( ) const
{
    return mySvcLvlProfileAid7;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid7( CT_TL1_LogicalAddr* theSvcLvlProfileAid7 )
{
    mySvcLvlProfileAid7 = theSvcLvlProfileAid7;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint8( ) const
{
    return mySvcLvlCodePoint8;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint8( uint16* theSvcLvlCodePoint8 )
{
    mySvcLvlCodePoint8 = theSvcLvlCodePoint8;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid8( ) const
{
    return mySvcLvlProfileAid8;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid8( CT_TL1_LogicalAddr* theSvcLvlProfileAid8 )
{
    mySvcLvlProfileAid8 = theSvcLvlProfileAid8;
}
//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint9( ) const
{
    return mySvcLvlCodePoint9;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint9( uint16* theSvcLvlCodePoint9 )
{
    mySvcLvlCodePoint9 = theSvcLvlCodePoint9;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid9( ) const
{
    return mySvcLvlProfileAid9;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid9( CT_TL1_LogicalAddr* theSvcLvlProfileAid9 )
{
    mySvcLvlProfileAid9 = theSvcLvlProfileAid9;
}

//--------------------------------------------------------------------------------
inline uint16*                     
TL1_SlpolicyEdParameters::GetSvcLvlCodePoint10( ) const
{
    return mySvcLvlCodePoint10;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlCodePoint10( uint16* theSvcLvlCodePoint10 )
{
    mySvcLvlCodePoint10 = theSvcLvlCodePoint10;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LogicalAddr*                    
TL1_SlpolicyEdParameters::GetSvcLvlProfileAid10( ) const
{
    return mySvcLvlProfileAid10;
}

inline void                         
TL1_SlpolicyEdParameters::SetSvcLvlProfileAid10( CT_TL1_LogicalAddr* theSvcLvlProfileAid10 )
{
    mySvcLvlProfileAid10 = theSvcLvlProfileAid10;
}

#endif
