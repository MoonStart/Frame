/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Slpf and Slpolicy Response 
TARGET:
AUTHOR:         June 08, 2007 - Tong Wu
DESCRIPTION:    Source file for TL1 Service Level Profile Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_SlpfRspBlk.h>

TL1_SlpfRspBlk::TL1_SlpfRspBlk( ) :
    myBitSet( INDEX_END, false ) 
{
}

TL1_SlpfRspBlk::TL1_SlpfRspBlk( const string*                  theEntityName,
                                const CT_TL1_LogicalAddr*      theAddr,
                                const string*                  theProfName,
                                const CT_SLPF_ProtLvl*         theProtectionLevel,
                                const CT_SLPF_Diversity*       theDiversity,
                                const CT_SLPF_Params*          theReversion,
                                const CT_SLPF_Params*          theCoRouting,
                                const CT_SLPF_Params*          theTransparentLineMSDCC,
                                const CT_SLPF_Params*          theTransparentSectionRSDCC,
                                const CT_SLPF_Params*          theTransparentOTUGCC0,
                                const CT_SLPF_Params*          theTrabsparentODUGCC12,
                                const int*                     theWaitTime,
                                const CT_SLPF_Params*          theCallSetupReroute,
                                const int*                     theMaxRerouteAttempts,
                                const int*                     theBackoffInterval,
                                const CT_SLPF_Params*          theBoundReroute,
                                const CT_SLPF_Params*          theEndToEndReroute,
                                const int*                     theLatency,
                                const uint32*                  theResourceClass,
                                const CT_SLPF_PRIORITY*        thePriority,
                                const CT_Resv_Style*           theReservationStyle,
                                const CT_Advertisement*        theResConnA,
                                const CT_Advertisement*        theResConnB,
                                const CT_Slpf_DiversityCheck*  theDiversityCheck,
                                const CT_Slpf_CpReversion*     theCpReversion,
                                const int*                     theCpWaitTime )
   : myBitSet( INDEX_END, false )
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_SlpfAddr ] = true;
        myAddr = *theAddr;
    }

    if( theProfName )
    {
        myBitSet[ INDEX_ProfileName ] = true;
        myProfileName = *theProfName;
    }

    if( theProtectionLevel )
    {
        myBitSet[ INDEX_ProtectionLevel ] = true;
        myProtectionLevel = *theProtectionLevel;
    }

    if( theDiversity )
    {
        myBitSet[ INDEX_Diversity ] = true;
        myDiversity = *theDiversity;
    }

    if( theReversion )
    {
        myBitSet[ INDEX_Reversion ] = true;
        myReversion = *theReversion;
    }

    if( theCoRouting )
    {
        myBitSet[ INDEX_CoRouting ] = true;
        myCoRouting = *theCoRouting;
    }

    if( theTransparentLineMSDCC )
    {
        myBitSet[ INDEX_TransparentLineMSDCC ] = true;
        myTransparentLineMSDCC = *theTransparentLineMSDCC;
    }
    
    if( theTransparentSectionRSDCC )
    {
        myBitSet[ INDEX_TransparentSectionRSDCC ] = true;
        myTransparentSectionRSDCC = *theTransparentSectionRSDCC;
    }
    
    if( theTransparentOTUGCC0 )
    {
        myBitSet[ INDEX_TransparentOTUGCC0 ] = true;
        myTransparentOTUGCC0 = *theTransparentOTUGCC0;
    }

    if( theTrabsparentODUGCC12 )
    {
        myBitSet[ INDEX_TransparentODUGCC12] = true;
        myTransparentODUGCC12 = *theTrabsparentODUGCC12;
    }

    if ( theWaitTime )
    {
        myBitSet[ INDEX_WaitTime ] = true;
        myWaitTime = *theWaitTime;
    }

    if ( theCallSetupReroute )
    {
        myBitSet[ INDEX_CallSetupReroute ] = true;
        myCallSetupReroute = *theCallSetupReroute;
    }

    if ( theMaxRerouteAttempts )
    {
        myBitSet[ INDEX_MaxRerouteAttempts ] = true;
        myMaxRerouteAttempts = *theMaxRerouteAttempts;
    }

    if ( theBackoffInterval )
    {
        myBitSet[ INDEX_BackoffInterval ] = true;
        myBackoffInterval = *theBackoffInterval;
    }

    if ( theBoundReroute )
    {
        myBitSet[ INDEX_BoundReroute ] = true;
        myBoundReroute = *theBoundReroute;
    }

    if ( theEndToEndReroute )
    {
        myBitSet[ INDEX_EndToEndReroute ] = true;
        myEndToEndReroute = *theEndToEndReroute;
    }

    if ( theLatency )
    {
        myBitSet[ INDEX_Latency ] = true;
        myLatency = *theLatency;
    }

    if ( theResourceClass )
    {
        myBitSet[ INDEX_ResourceClass ] = true;
        myResourceClass = *theResourceClass;
    }

    if ( thePriority )
    {
        myBitSet[ INDEX_Priority ] = true;
        myPriority = *thePriority;
    }

    if ( theReservationStyle )
    {
        myBitSet[ INDEX_ReservationStyle ] = true;
        myReservationStyle = *theReservationStyle;
    }

    if ( theResConnA )
    {
        myBitSet[ INDEX_ResConnA ] = true;
        myResConnA = *theResConnA;
    }

    if ( theResConnB )
    {
        myBitSet[ INDEX_ResConnB ] = true;
        myResConnB = *theResConnB;
    }

    if ( theDiversityCheck )
    {
        myBitSet[ INDEX_DiversityCheck ] = true;
        myDiversityCheck = *theDiversityCheck;
    }

    if ( theCpReversion )
    {
        myBitSet[ INDEX_CpReversion ] = true;
        myCpReversion = *theCpReversion;
    }
    
    if ( theCpWaitTime )
    {
        myBitSet[ INDEX_CpWaitTime ] = true;
        myCpWaitTime = *theCpWaitTime;
    }
}


TL1_SlpfRspBlk::TL1_SlpfRspBlk( const TL1_SlpfRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=                  t1Blk.myBitSet;
    myEntityName=              t1Blk.myEntityName;
    myAddr=                    t1Blk.myAddr;    
    myProfileName=             t1Blk.myProfileName;
    myProtectionLevel=         t1Blk.myProtectionLevel;
    myDiversity=               t1Blk.myDiversity;
    myReversion=               t1Blk.myReversion;
    myCoRouting=               t1Blk.myCoRouting;
    myTransparentLineMSDCC=    t1Blk.myTransparentLineMSDCC;
    myTransparentSectionRSDCC= t1Blk.myTransparentSectionRSDCC;
    myTransparentOTUGCC0=      t1Blk.myTransparentOTUGCC0;    
    myTransparentODUGCC12=     t1Blk.myTransparentODUGCC12;
    myWaitTime=                t1Blk.myWaitTime;
    myCallSetupReroute=        t1Blk.myCallSetupReroute;
    myMaxRerouteAttempts=      t1Blk.myMaxRerouteAttempts;
    myBackoffInterval=         t1Blk.myBackoffInterval;
    myBoundReroute=            t1Blk.myBoundReroute;
    myEndToEndReroute=         t1Blk.myEndToEndReroute;
    myLatency=                 t1Blk.myLatency;
    myResourceClass=           t1Blk.myResourceClass;
    myPriority=                t1Blk.myPriority;
    myReservationStyle=        t1Blk.myReservationStyle;
    myResConnA=                t1Blk.myResConnA;
    myResConnB=                t1Blk.myResConnB;
    myDiversityCheck=          t1Blk.myDiversityCheck;
    myCpReversion=             t1Blk.myCpReversion;
    myCpWaitTime=              t1Blk.myCpWaitTime;
}

TL1_SlpfRspBlk::~TL1_SlpfRspBlk( )
{
}

TL1_SlpfRspBlk& 
TL1_SlpfRspBlk::operator=( const TL1_SlpfRspBlk& t1Blk )
{
    myBitSet=                  t1Blk.myBitSet;
    myEntityName=              t1Blk.myEntityName;
    myAddr=                    t1Blk.myAddr;    
    myProfileName=             t1Blk.myProfileName;
    myProtectionLevel=         t1Blk.myProtectionLevel;
    myDiversity=               t1Blk.myDiversity;
    myReversion=               t1Blk.myReversion;
    myCoRouting=               t1Blk.myCoRouting;
    myTransparentLineMSDCC=    t1Blk.myTransparentLineMSDCC;
    myTransparentSectionRSDCC= t1Blk.myTransparentSectionRSDCC;
    myTransparentOTUGCC0=      t1Blk.myTransparentOTUGCC0;    
    myTransparentODUGCC12=     t1Blk.myTransparentODUGCC12;
    myWaitTime=                t1Blk.myWaitTime;
    myCallSetupReroute=        t1Blk.myCallSetupReroute;
    myMaxRerouteAttempts=      t1Blk.myMaxRerouteAttempts;
    myBackoffInterval=         t1Blk.myBackoffInterval;
    myBoundReroute=            t1Blk.myBoundReroute;
    myEndToEndReroute=         t1Blk.myEndToEndReroute;
    myLatency=                 t1Blk.myLatency;
    myResourceClass=           t1Blk.myResourceClass;
    myPriority=                t1Blk.myPriority;
    myReservationStyle=        t1Blk.myReservationStyle;
    myResConnA=                t1Blk.myResConnA;
    myResConnB=                t1Blk.myResConnB;
    myDiversityCheck=          t1Blk.myDiversityCheck;
    myCpReversion=             t1Blk.myCpReversion;
    myCpWaitTime=              t1Blk.myCpWaitTime;
    
    return *this;
}

bool 
TL1_SlpfRspBlk::operator==( const TL1_SlpfRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( !( myProfileName == t1Blk.myProfileName ) )
        return false;

    if ( myProtectionLevel != t1Blk.myProtectionLevel )
        return false;

    if ( myDiversity != t1Blk.myDiversity )
        return false;

    if ( myReversion != t1Blk.myReversion )
        return false;

    if ( myCoRouting != t1Blk.myCoRouting )
        return false;

    if ( myTransparentLineMSDCC != t1Blk.myTransparentLineMSDCC )
        return false;

    if ( myTransparentSectionRSDCC != t1Blk.myTransparentSectionRSDCC )
        return false;

    if ( myTransparentOTUGCC0 != t1Blk.myTransparentOTUGCC0 )
        return false;

    if ( myTransparentODUGCC12 != t1Blk.myTransparentODUGCC12 )
        return false;

    if ( myWaitTime != t1Blk.myWaitTime )
        return false;

    if ( myCallSetupReroute != t1Blk.myCallSetupReroute )
        return false;

    if ( myMaxRerouteAttempts != t1Blk.myMaxRerouteAttempts )
        return false;

    if ( myBackoffInterval != t1Blk.myBackoffInterval )
        return false;

    if ( myBoundReroute != t1Blk.myBoundReroute )
        return false;

    if ( myEndToEndReroute != t1Blk.myEndToEndReroute )
        return false;

    if ( myLatency != t1Blk.myLatency )
        return false;

    if ( myResourceClass != t1Blk.myResourceClass )
        return false;

    if ( myPriority != t1Blk.myPriority )
        return false;

    if ( myReservationStyle != t1Blk.myReservationStyle )
        return false;

    if ( myResConnA != t1Blk.myResConnA )
        return false;

    if ( myResConnB != t1Blk.myResConnB )
        return false;

    if ( myDiversityCheck != t1Blk.myDiversityCheck )
        return false;

    if ( myCpReversion != t1Blk.myCpReversion )
        return false;
    
    if ( myCpWaitTime != t1Blk.myCpWaitTime )
        return false;

    return true;
}


//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetEntityName( string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetSlpfAddr( CT_TL1_LogicalAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_SlpfAddr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetSlpfAddr( const CT_TL1_LogicalAddr& theAddr )
{
    myBitSet[ INDEX_SlpfAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetProfileName( string& theProfName) const
{
    if( true == myBitSet[ INDEX_ProfileName ] )
    {
        theProfName = myProfileName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetProfileName( const string& theProfName )
{
   myBitSet[ INDEX_ProfileName ] = true;
   myProfileName = theProfName;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetProtectionLevel( CT_SLPF_ProtLvl& theProtLevel ) const
{
    if( true == myBitSet[ INDEX_ProtectionLevel ] )
    {
        theProtLevel = myProtectionLevel;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetProtectionLevel( const CT_SLPF_ProtLvl& theProtLevel )
{
    myBitSet[ INDEX_ProtectionLevel ] = true;
    myProtectionLevel= theProtLevel;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetDiversity( CT_SLPF_Diversity& theDiversity ) const
{
    if( true == myBitSet[ INDEX_Diversity ] )
    {
        theDiversity = myDiversity;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetDiversity( const CT_SLPF_Diversity& theDiversity )
{
    myBitSet[ INDEX_Diversity ] = true;
    myDiversity = theDiversity;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetReversion( CT_SLPF_Params& theReversion ) const
{
    if( true == myBitSet[ INDEX_Reversion ] )
    {
        theReversion = myReversion;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetReversion( const CT_SLPF_Params& theReversion )
{
    myBitSet[ INDEX_Reversion ] = true;
    myReversion = theReversion;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetCoRouting( CT_SLPF_Params& theCoRouting ) const
{
    if( true == myBitSet[ INDEX_CoRouting ] )
    {
        theCoRouting = myCoRouting;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetCoRouting( const CT_SLPF_Params& theCoRouting )
{
    myBitSet[ INDEX_CoRouting ] = true;
    myCoRouting = theCoRouting;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetTransLineMSDCC( CT_SLPF_Params& theTransLineMSDCC ) const
{
    if( true == myBitSet[ INDEX_TransparentLineMSDCC ] )
    {
        theTransLineMSDCC = myTransparentLineMSDCC;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetTransLineMSDCC( const CT_SLPF_Params& theTransLineMSDCC )
{
    myBitSet[ INDEX_TransparentLineMSDCC ] = true;
    myTransparentLineMSDCC = theTransLineMSDCC;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetTransSectionRSDCC( CT_SLPF_Params& theTransSectionRSDCC ) const
{
    if( true == myBitSet[ INDEX_TransparentSectionRSDCC ] )
    {
        theTransSectionRSDCC = myTransparentSectionRSDCC;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetTransSectionRSDCC( const CT_SLPF_Params& theTransSectionRSDCC )
{
    myBitSet[ INDEX_TransparentSectionRSDCC ] = true;
    myTransparentSectionRSDCC = theTransSectionRSDCC;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetTransOTUGCC0( CT_SLPF_Params& theTransOTUGCC0 ) const
{
    if( true == myBitSet[ INDEX_TransparentOTUGCC0 ] )
    {
        theTransOTUGCC0 = myTransparentOTUGCC0;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetTransOTUGCC0( const CT_SLPF_Params& theTransOTUGCC0 )
{
    myBitSet[ INDEX_TransparentOTUGCC0 ] = true;
    myTransparentOTUGCC0 = theTransOTUGCC0;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetTransODUGCC12( CT_SLPF_Params& theTransODUGCC12 ) const
{
    if( true == myBitSet[ INDEX_TransparentODUGCC12 ] )
    {
        theTransODUGCC12 = myTransparentODUGCC12;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetTransODUGCC12( const CT_SLPF_Params& theTransODUGCC12 )
{
    myBitSet[ INDEX_TransparentODUGCC12 ] = true;
    myTransparentODUGCC12 = theTransODUGCC12;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetWtr( int& theWaitTime ) const
{
    if( true == myBitSet[ INDEX_WaitTime ] )
    {
        theWaitTime = myWaitTime;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetWtr( const int& theWaitTime ) 
{
    myBitSet[ INDEX_WaitTime ] = true;
    myWaitTime = theWaitTime;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetCallSetupReroute( CT_SLPF_Params& theCallSetupReroute ) const
{
    if( true == myBitSet[ INDEX_CallSetupReroute ] )
    {
        theCallSetupReroute = myCallSetupReroute;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetCallSetupReroute( const CT_SLPF_Params& theCallSetupReroute ) 
{
    myBitSet[ INDEX_CallSetupReroute ] = true;
    myCallSetupReroute = theCallSetupReroute;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetMaxRerouteAttempts( int& theMaxRerouteAttempts ) const
{
    if( true == myBitSet[ INDEX_MaxRerouteAttempts ] )
    {
        theMaxRerouteAttempts = myMaxRerouteAttempts;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetMaxRerouteAttempts( const int& theMaxRerouteAttempts ) 
{
    myBitSet[ INDEX_MaxRerouteAttempts ] = true;
    myMaxRerouteAttempts = theMaxRerouteAttempts;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetBackoffInterval( int& theBackoffInterval ) const
{
    if( true == myBitSet[ INDEX_BackoffInterval ] )
    {
        theBackoffInterval = myBackoffInterval;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetBackoffInterval( const int& theBackoffInterval ) 
{
    myBitSet[ INDEX_BackoffInterval ] = true;
    myBackoffInterval = theBackoffInterval;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetBoundReroute( CT_SLPF_Params& theBoundReroute ) const
{
    if( true == myBitSet[ INDEX_BoundReroute ] )
    {
        theBoundReroute = myBoundReroute;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetBoundReroute( const CT_SLPF_Params& theBoundReroute ) 
{
    myBitSet[ INDEX_BoundReroute ] = true;
    myBoundReroute = theBoundReroute;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetEndToEndReroute( CT_SLPF_Params& theEndToEndReroute ) const
{
    if( true == myBitSet[ INDEX_EndToEndReroute ] )
    {
        theEndToEndReroute = myEndToEndReroute;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetEndToEndReroute( const CT_SLPF_Params& theEndToEndReroute ) 
{
    myBitSet[ INDEX_EndToEndReroute ] = true;
    myEndToEndReroute = theEndToEndReroute;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetLatency( int& theLatency ) const
{
    if( true == myBitSet[ INDEX_Latency ] )
    {
        theLatency = myLatency;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetLatency( const int& theLatency )
{
    myBitSet[ INDEX_Latency ] = true;
    myLatency = theLatency;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetResourceClass( CT_ControlPlane_Addr& theResourceClass ) const
{
    if( true == myBitSet[ INDEX_ResourceClass ] )
    {
        theResourceClass = myResourceClass;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetResourceClass( const CT_ControlPlane_Addr& theResourceClass )
{
    myBitSet[ INDEX_ResourceClass ] = true;
    myResourceClass = theResourceClass;
}

//--------------------------------------------------------------
bool
TL1_SlpfRspBlk::GetPriority( CT_SLPF_PRIORITY& thePriority ) const
{
    if ( true == myBitSet[ INDEX_Priority ] )
    {
        thePriority = myPriority;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetPriority( const CT_SLPF_PRIORITY& thePriority )
{
    myBitSet[ INDEX_Priority ] = true;
    myPriority = thePriority;
}


//--------------------------------------------------------------
bool
TL1_SlpfRspBlk::GetReservationStyle( CT_Resv_Style& theReservationStyle ) const
{
    if ( true == myBitSet[ INDEX_ReservationStyle ] )
    {
        theReservationStyle = myReservationStyle;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetReservationStyle( const CT_Resv_Style& theReservationStyle )
{
    myBitSet[ INDEX_ReservationStyle ] = true;
    myReservationStyle = theReservationStyle;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetResConnA( CT_Advertisement& theResConnA ) const
{
    if ( true == myBitSet[ INDEX_ResConnA ] )
    {
        theResConnA = myResConnA;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetResConnA( const CT_Advertisement& theResConnA )
{
    myBitSet[ INDEX_ResConnA ] = true;
    myResConnA = theResConnA;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetResConnB( CT_Advertisement& theResConnB ) const
{
    if ( true == myBitSet[ INDEX_ResConnB ] )
    {
        theResConnB = myResConnB;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetResConnB( const CT_Advertisement& theResConnB )
{
    myBitSet[ INDEX_ResConnB ] = true;
    myResConnB = theResConnB;
}

//--------------------------------------------------------------
bool
TL1_SlpfRspBlk::GetDiversityCheck( CT_Slpf_DiversityCheck& theDiversityCheck) const
{
    if ( true == myBitSet[ INDEX_DiversityCheck ] )
    {
        theDiversityCheck = myDiversityCheck;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetDiversityCheck( const CT_Slpf_DiversityCheck& theDiversityCheck )
{
    myBitSet[ INDEX_DiversityCheck ] = true;
    myDiversityCheck = theDiversityCheck;
}

//--------------------------------------------------------------
bool
TL1_SlpfRspBlk::GetCpReversion(CT_Slpf_CpReversion& theCpReversion ) const
{
    if ( true == myBitSet[ INDEX_CpReversion ] )
    {
        theCpReversion = myCpReversion;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_SlpfRspBlk::SetCpReversion( const CT_Slpf_CpReversion& theCpReversion )
{
    myBitSet[ INDEX_CpReversion ] = true;
    myCpReversion = theCpReversion;
}

//--------------------------------------------------------------
bool 
TL1_SlpfRspBlk::GetCpWtr( int& theCpWaitTime ) const
{
    if ( true == myBitSet[ INDEX_WaitTime ] )
    {
        theCpWaitTime = myCpWaitTime;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpfRspBlk::SetCpWtr( const int& theCpWaitTime )
{
    myBitSet[ INDEX_WaitTime ] = true;
    myCpWaitTime = theCpWaitTime;
}

//--------------------------------------------------------------

TL1_SlpolicyRspBlk::TL1_SlpolicyRspBlk( ) :
    myBitSet( INDEX_END, false ) 
{
}

TL1_SlpolicyRspBlk::TL1_SlpolicyRspBlk( const string*                  theEntityName,
                                        const CT_TL1_LogicalAddr*      theAddr,
                                        const string*                  thePolicyName,
                                        const int16*         	       theSvcLvlCodePt1,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid1,
                                        const string*                  theSvcLvlPfName1,
                                        const int16*         	       theSvcLvlCodePt2,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid2,
                                        const string*                  theSvcLvlPfName2,
                                        const int16*         	       theSvcLvlCodePt3,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid3,
                                        const string*                  theSvcLvlPfName3,
                                        const int16*         	       theSvcLvlCodePt4,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid4,
                                        const string*                  theSvcLvlPfName4,
                                        const int16*         	       theSvcLvlCodePt5,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid5,
                                        const string*                  theSvcLvlPfName5,
                                        const int16*         	       theSvcLvlCodePt6,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid6,
                                        const string*                  theSvcLvlPfName6,
                                        const int16*         	       theSvcLvlCodePt7,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid7,
                                        const string*                  theSvcLvlPfName7,
                                        const int16*         	       theSvcLvlCodePt8,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid8,
                                        const string*                  theSvcLvlPfName8,
                                        const int16*         	       theSvcLvlCodePt9,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid9,
                                        const string*                  theSvcLvlPfName9,
                                        const int16*         	       theSvcLvlCodePt10,
                                        const CT_TL1_LogicalAddr*      theSvcLvlPfAid10,
                                        const string*                  theSvcLvlPfName10 )
   : myBitSet( INDEX_END, false )
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_SlpolicyAddr ] = true;
        myAddr = *theAddr;
    }

    if( thePolicyName )
    {
        myBitSet[ INDEX_PolicyName ] = true;
        myPolicyName = *thePolicyName;
    }

    if( theSvcLvlCodePt1 )
    {
        myBitSet[ INDEX_SvcLvlCodePt1 ] = true;
        mySvcLvlCodePt1 = *theSvcLvlCodePt1;
    }

    if( theSvcLvlPfAid1 )
    {
        myBitSet[ INDEX_SvcLvlPfAid1 ] = true;
        mySvcLvlPfAid1 = *theSvcLvlPfAid1;
    }

    if( theSvcLvlPfName1 )
    {
        myBitSet[ INDEX_SvcLvlPfName1 ] = true;
        mySvcLvlPfName1 = *theSvcLvlPfName1;
    }

    if( theSvcLvlCodePt2 )
    {
        myBitSet[ INDEX_SvcLvlCodePt2 ] = true;
        mySvcLvlCodePt2 = *theSvcLvlCodePt2;
    }

    if( theSvcLvlPfAid2 )
    {
        myBitSet[ INDEX_SvcLvlPfAid2 ] = true;
        mySvcLvlPfAid2 = *theSvcLvlPfAid2;
    }

    if( theSvcLvlPfName2 )
    {
        myBitSet[ INDEX_SvcLvlPfName2 ] = true;
        mySvcLvlPfName2 = *theSvcLvlPfName2;
    }

    if( theSvcLvlCodePt3 )
    {
        myBitSet[ INDEX_SvcLvlCodePt3 ] = true;
        mySvcLvlCodePt3 = *theSvcLvlCodePt3;
    }

    if( theSvcLvlPfAid3 )
    {
        myBitSet[ INDEX_SvcLvlPfAid3 ] = true;
        mySvcLvlPfAid3 = *theSvcLvlPfAid3;
    }

    if( theSvcLvlPfName3 )
    {
        myBitSet[ INDEX_SvcLvlPfName3 ] = true;
        mySvcLvlPfName3 = *theSvcLvlPfName3;
    }

    if( theSvcLvlCodePt4 )
    {
        myBitSet[ INDEX_SvcLvlCodePt4 ] = true;
        mySvcLvlCodePt4 = *theSvcLvlCodePt4;
    }

    if( theSvcLvlPfAid4 )
    {
        myBitSet[ INDEX_SvcLvlPfAid4 ] = true;
        mySvcLvlPfAid4 = *theSvcLvlPfAid4;
    }

    if( theSvcLvlPfName4 )
    {
        myBitSet[ INDEX_SvcLvlPfName4 ] = true;
        mySvcLvlPfName4 = *theSvcLvlPfName4;
    }

    if( theSvcLvlCodePt5 )
    {
        myBitSet[ INDEX_SvcLvlCodePt5 ] = true;
        mySvcLvlCodePt5 = *theSvcLvlCodePt5;
    }

    if( theSvcLvlPfAid5 )
    {
        myBitSet[ INDEX_SvcLvlPfAid5 ] = true;
        mySvcLvlPfAid5 = *theSvcLvlPfAid5;
    }

    if( theSvcLvlPfName5 )
    {
        myBitSet[ INDEX_SvcLvlPfName5 ] = true;
        mySvcLvlPfName5 = *theSvcLvlPfName5;
    }
    
    if( theSvcLvlCodePt6 )
    {
        myBitSet[ INDEX_SvcLvlCodePt6 ] = true;
        mySvcLvlCodePt6 = *theSvcLvlCodePt6;
    }

    if( theSvcLvlPfAid6 )
    {
        myBitSet[ INDEX_SvcLvlPfAid6 ] = true;
        mySvcLvlPfAid6 = *theSvcLvlPfAid6;
    }

    if( theSvcLvlPfName6 )
    {
        myBitSet[ INDEX_SvcLvlPfName6 ] = true;
        mySvcLvlPfName6 = *theSvcLvlPfName6;
    }

    if( theSvcLvlCodePt7 )
    {
        myBitSet[ INDEX_SvcLvlCodePt7 ] = true;
        mySvcLvlCodePt7 = *theSvcLvlCodePt7;
    }

    if( theSvcLvlPfAid7 )
    {
        myBitSet[ INDEX_SvcLvlPfAid7 ] = true;
        mySvcLvlPfAid7 = *theSvcLvlPfAid7;
    }

    if( theSvcLvlPfName7 )
    {
        myBitSet[ INDEX_SvcLvlPfName7 ] = true;
        mySvcLvlPfName7 = *theSvcLvlPfName7;
    }

    if( theSvcLvlCodePt8 )
    {
        myBitSet[ INDEX_SvcLvlCodePt8 ] = true;
        mySvcLvlCodePt8 = *theSvcLvlCodePt8;
    }

    if( theSvcLvlPfAid8 )
    {
        myBitSet[ INDEX_SvcLvlPfAid8 ] = true;
        mySvcLvlPfAid8= *theSvcLvlPfAid8;
    }

    if( theSvcLvlPfName8)
    {
        myBitSet[ INDEX_SvcLvlPfName8] = true;
        mySvcLvlPfName8= *theSvcLvlPfName8;
    }

    if( theSvcLvlCodePt9)
    {
        myBitSet[ INDEX_SvcLvlCodePt9 ] = true;
        mySvcLvlCodePt9= *theSvcLvlCodePt9;
    }

    if( theSvcLvlPfAid9)
    {
        myBitSet[ INDEX_SvcLvlPfAid9] = true;
        mySvcLvlPfAid9 = *theSvcLvlPfAid9;
    }

    if( theSvcLvlPfName9 )
    {
        myBitSet[ INDEX_SvcLvlPfName9 ] = true;
        mySvcLvlPfName9 = *theSvcLvlPfName9;
    }

    if( theSvcLvlCodePt10 )
    {
        myBitSet[ INDEX_SvcLvlCodePt10 ] = true;
        mySvcLvlCodePt10 = *theSvcLvlCodePt10;
    }

    if( theSvcLvlPfAid10 )
    {
        myBitSet[ INDEX_SvcLvlPfAid10 ] = true;
        mySvcLvlPfAid10 = *theSvcLvlPfAid10;
    }

    if( theSvcLvlPfName10 )
    {
        myBitSet[ INDEX_SvcLvlPfName10 ] = true;
        mySvcLvlPfName10 = *theSvcLvlPfName10;
    }


}


TL1_SlpolicyRspBlk::TL1_SlpolicyRspBlk( const TL1_SlpolicyRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=                  t1Blk.myBitSet;
    myEntityName=              t1Blk.myEntityName;
    myAddr=                    t1Blk.myAddr;    
    myPolicyName=              t1Blk.myPolicyName;
    mySvcLvlCodePt1=           t1Blk.mySvcLvlCodePt1;
    mySvcLvlPfAid1=            t1Blk.mySvcLvlPfAid1;
    mySvcLvlPfName1=           t1Blk.mySvcLvlPfName1;
    mySvcLvlCodePt2=           t1Blk.mySvcLvlCodePt2;
    mySvcLvlPfAid2=            t1Blk.mySvcLvlPfAid2;
    mySvcLvlPfName2=           t1Blk.mySvcLvlPfName2;
    mySvcLvlCodePt3=           t1Blk.mySvcLvlCodePt3;
    mySvcLvlPfAid3=            t1Blk.mySvcLvlPfAid3;
    mySvcLvlPfName3=           t1Blk.mySvcLvlPfName3;
    mySvcLvlCodePt4=           t1Blk.mySvcLvlCodePt4;
    mySvcLvlPfAid4=            t1Blk.mySvcLvlPfAid4;
    mySvcLvlPfName4=           t1Blk.mySvcLvlPfName4;
    mySvcLvlCodePt5=           t1Blk.mySvcLvlCodePt5;
    mySvcLvlPfAid5=            t1Blk.mySvcLvlPfAid5;
    mySvcLvlPfName5=           t1Blk.mySvcLvlPfName5;
    mySvcLvlCodePt6=           t1Blk.mySvcLvlCodePt6;
    mySvcLvlPfAid6=            t1Blk.mySvcLvlPfAid6;
    mySvcLvlPfName6=           t1Blk.mySvcLvlPfName6;
    mySvcLvlCodePt7=           t1Blk.mySvcLvlCodePt7;
    mySvcLvlPfAid7=            t1Blk.mySvcLvlPfAid7;
    mySvcLvlPfName7=           t1Blk.mySvcLvlPfName7;
    mySvcLvlCodePt8=           t1Blk.mySvcLvlCodePt8;
    mySvcLvlPfAid8=            t1Blk.mySvcLvlPfAid8;
    mySvcLvlPfName8=           t1Blk.mySvcLvlPfName8;
    mySvcLvlCodePt9=           t1Blk.mySvcLvlCodePt9;
    mySvcLvlPfAid9=            t1Blk.mySvcLvlPfAid9;
    mySvcLvlPfName9=           t1Blk.mySvcLvlPfName9;
    mySvcLvlCodePt10=          t1Blk.mySvcLvlCodePt10;
    mySvcLvlPfAid10=           t1Blk.mySvcLvlPfAid10;
    mySvcLvlPfName10=          t1Blk.mySvcLvlPfName10;

}

TL1_SlpolicyRspBlk::~TL1_SlpolicyRspBlk( )
{
}

TL1_SlpolicyRspBlk& 
TL1_SlpolicyRspBlk::operator=( const TL1_SlpolicyRspBlk& t1Blk )
{
    myBitSet=                  t1Blk.myBitSet;
    myEntityName=              t1Blk.myEntityName;
    myAddr=                    t1Blk.myAddr;    
    myPolicyName=              t1Blk.myPolicyName;
    mySvcLvlCodePt1=           t1Blk.mySvcLvlCodePt1;
    mySvcLvlPfAid1=            t1Blk.mySvcLvlPfAid1;
    mySvcLvlPfName1=           t1Blk.mySvcLvlPfName1;
    mySvcLvlCodePt2=           t1Blk.mySvcLvlCodePt2;
    mySvcLvlPfAid2=            t1Blk.mySvcLvlPfAid2;
    mySvcLvlPfName2=           t1Blk.mySvcLvlPfName2;
    mySvcLvlCodePt3=           t1Blk.mySvcLvlCodePt3;
    mySvcLvlPfAid3=            t1Blk.mySvcLvlPfAid3;
    mySvcLvlPfName3=           t1Blk.mySvcLvlPfName3;
    mySvcLvlCodePt4=           t1Blk.mySvcLvlCodePt4;
    mySvcLvlPfAid4=            t1Blk.mySvcLvlPfAid4;
    mySvcLvlPfName4=           t1Blk.mySvcLvlPfName4;
    mySvcLvlCodePt5=           t1Blk.mySvcLvlCodePt5;
    mySvcLvlPfAid5=            t1Blk.mySvcLvlPfAid5;
    mySvcLvlPfName5=           t1Blk.mySvcLvlPfName5;
    mySvcLvlCodePt6=           t1Blk.mySvcLvlCodePt6;
    mySvcLvlPfAid6=            t1Blk.mySvcLvlPfAid6;
    mySvcLvlPfName6=           t1Blk.mySvcLvlPfName6;
    mySvcLvlCodePt7=           t1Blk.mySvcLvlCodePt7;
    mySvcLvlPfAid7=            t1Blk.mySvcLvlPfAid7;
    mySvcLvlPfName7=           t1Blk.mySvcLvlPfName7;
    mySvcLvlCodePt8=           t1Blk.mySvcLvlCodePt8;
    mySvcLvlPfAid8=            t1Blk.mySvcLvlPfAid8;
    mySvcLvlPfName8=           t1Blk.mySvcLvlPfName8;
    mySvcLvlCodePt9=           t1Blk.mySvcLvlCodePt9;
    mySvcLvlPfAid9=            t1Blk.mySvcLvlPfAid9;
    mySvcLvlPfName9=           t1Blk.mySvcLvlPfName9;
    mySvcLvlCodePt10=          t1Blk.mySvcLvlCodePt10;
    mySvcLvlPfAid10=           t1Blk.mySvcLvlPfAid10;
    mySvcLvlPfName10=          t1Blk.mySvcLvlPfName10;


    return *this;
}

bool 
TL1_SlpolicyRspBlk::operator==( const TL1_SlpolicyRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !( myAddr == t1Blk.myAddr ) )
        return false;

    if ( !( myPolicyName == t1Blk.myPolicyName ) )
        return false;

    if ( mySvcLvlCodePt1 != t1Blk.mySvcLvlCodePt1 )
        return false;

    if ( !(mySvcLvlPfAid1 == t1Blk.mySvcLvlPfAid1) )
        return false;

    if ( !( mySvcLvlPfName1 == t1Blk.mySvcLvlPfName1 ) )
        return false;

    if ( mySvcLvlCodePt2 != t1Blk.mySvcLvlCodePt2 )
        return false;

    if ( !(mySvcLvlPfAid2 == t1Blk.mySvcLvlPfAid2) )
        return false;

    if ( !( mySvcLvlPfName2 == t1Blk.mySvcLvlPfName2 ) )
        return false;

    if ( mySvcLvlCodePt3 != t1Blk.mySvcLvlCodePt3 )
        return false;

    if ( !(mySvcLvlPfAid3 == t1Blk.mySvcLvlPfAid3) )
        return false;

    if ( !( mySvcLvlPfName3 == t1Blk.mySvcLvlPfName3 ) )
        return false;

    if ( mySvcLvlCodePt4 != t1Blk.mySvcLvlCodePt4 )
        return false;

    if ( !(mySvcLvlPfAid4 == t1Blk.mySvcLvlPfAid4) )
        return false;

    if ( !( mySvcLvlPfName4 == t1Blk.mySvcLvlPfName4 ) )
        return false;

    if ( mySvcLvlCodePt5 != t1Blk.mySvcLvlCodePt5 )
        return false;

    if ( !(mySvcLvlPfAid5 == t1Blk.mySvcLvlPfAid5) )
        return false;

    if ( !( mySvcLvlPfName5 == t1Blk.mySvcLvlPfName5 ) )
        return false;
    
    if ( mySvcLvlCodePt6 != t1Blk.mySvcLvlCodePt6 )
        return false;

    if ( !(mySvcLvlPfAid6 == t1Blk.mySvcLvlPfAid6) )
        return false;

    if ( !( mySvcLvlPfName6 == t1Blk.mySvcLvlPfName6 ) )
        return false;

    if ( mySvcLvlCodePt7 != t1Blk.mySvcLvlCodePt7 )
        return false;

    if ( !(mySvcLvlPfAid7 == t1Blk.mySvcLvlPfAid7) )
        return false;

    if ( !( mySvcLvlPfName7 == t1Blk.mySvcLvlPfName7 ) )
        return false;

    if ( mySvcLvlCodePt8 != t1Blk.mySvcLvlCodePt8 )
        return false;

    if ( !(mySvcLvlPfAid8 == t1Blk.mySvcLvlPfAid8) )
        return false;

    if ( !( mySvcLvlPfName8 == t1Blk.mySvcLvlPfName8 ) )
        return false;

    if ( mySvcLvlCodePt9 != t1Blk.mySvcLvlCodePt9 )
        return false;

    if ( !(mySvcLvlPfAid9 == t1Blk.mySvcLvlPfAid9) )
        return false;

    if ( !( mySvcLvlPfName9 == t1Blk.mySvcLvlPfName9 ) )
        return false;

    if ( mySvcLvlCodePt10 != t1Blk.mySvcLvlCodePt10 )
        return false;

    if ( !(mySvcLvlPfAid10 == t1Blk.mySvcLvlPfAid10) )
        return false;

    if ( !( mySvcLvlPfName10 == t1Blk.mySvcLvlPfName10 ) )
        return false;


    return true;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetEntityName( string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSlpolicyAddr( CT_TL1_LogicalAddr& theAddr ) const
{
    if( true == myBitSet[ INDEX_SlpolicyAddr ] )
    {
        theAddr = myAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSlpolicyAddr( const CT_TL1_LogicalAddr& theAddr )
{
    myBitSet[ INDEX_SlpolicyAddr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetPolicyName( string& thePolicyName) const
{
    if( true == myBitSet[ INDEX_PolicyName ] )
    {
        thePolicyName = myPolicyName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetPolicyName( const string& thePolicyName )
{
   myBitSet[ INDEX_PolicyName ] = true;
   myPolicyName = thePolicyName;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt1( int16& theSvcLvlCodePt1 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt1 ] )
    {
        theSvcLvlCodePt1 = mySvcLvlCodePt1;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt1( const int16& theSvcLvlCodePt1 )
{
    myBitSet[ INDEX_SvcLvlCodePt1 ] = true;
    mySvcLvlCodePt1= theSvcLvlCodePt1;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid1( CT_TL1_LogicalAddr& theSvcLvlPfAid1 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid1 ] )
    {
        theSvcLvlPfAid1 = mySvcLvlPfAid1;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid1( const CT_TL1_LogicalAddr& theSvcLvlPfAid1 )
{
    myBitSet[ INDEX_SvcLvlPfAid1 ] = true;
    mySvcLvlPfAid1 = theSvcLvlPfAid1;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName1( string& theSvcLvlPfName1 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName1 ] )
    {
        theSvcLvlPfName1 = mySvcLvlPfName1;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName1( const string& theSvcLvlPfName1 )
{
    myBitSet[ INDEX_SvcLvlPfName1 ] = true;
    mySvcLvlPfName1 = theSvcLvlPfName1;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt2( int16& theSvcLvlCodePt2 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt2 ] )
    {
        theSvcLvlCodePt2 = mySvcLvlCodePt2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt2( const int16& theSvcLvlCodePt2 )
{
    myBitSet[ INDEX_SvcLvlCodePt2 ] = true;
    mySvcLvlCodePt2= theSvcLvlCodePt2;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid2( CT_TL1_LogicalAddr& theSvcLvlPfAid2 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid2 ] )
    {
        theSvcLvlPfAid2 = mySvcLvlPfAid2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid2( const CT_TL1_LogicalAddr& theSvcLvlPfAid2 )
{
    myBitSet[ INDEX_SvcLvlPfAid2 ] = true;
    mySvcLvlPfAid2 = theSvcLvlPfAid2;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName2( string& theSvcLvlPfName2 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName2 ] )
    {
        theSvcLvlPfName2 = mySvcLvlPfName2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName2( const string& theSvcLvlPfName2 )
{
    myBitSet[ INDEX_SvcLvlPfName2 ] = true;
    mySvcLvlPfName2 = theSvcLvlPfName2;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt3( int16& theSvcLvlCodePt3 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt3 ] )
    {
        theSvcLvlCodePt3 = mySvcLvlCodePt3;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt3( const int16& theSvcLvlCodePt3 )
{
    myBitSet[ INDEX_SvcLvlCodePt3 ] = true;
    mySvcLvlCodePt3= theSvcLvlCodePt3;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid3( CT_TL1_LogicalAddr& theSvcLvlPfAid3 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid3 ] )
    {
        theSvcLvlPfAid3 = mySvcLvlPfAid3;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid3( const CT_TL1_LogicalAddr& theSvcLvlPfAid3 )
{
    myBitSet[ INDEX_SvcLvlPfAid3 ] = true;
    mySvcLvlPfAid3 = theSvcLvlPfAid3;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName3( string& theSvcLvlPfName3 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName3 ] )
    {
        theSvcLvlPfName3 = mySvcLvlPfName3;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName3( const string& theSvcLvlPfName3 )
{
    myBitSet[ INDEX_SvcLvlPfName3 ] = true;
    mySvcLvlPfName3 = theSvcLvlPfName3;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt4( int16& theSvcLvlCodePt4 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt4 ] )
    {
        theSvcLvlCodePt4 = mySvcLvlCodePt4;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt4( const int16& theSvcLvlCodePt4 )
{
    myBitSet[ INDEX_SvcLvlCodePt4 ] = true;
    mySvcLvlCodePt4= theSvcLvlCodePt4;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid4( CT_TL1_LogicalAddr& theSvcLvlPfAid4 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid4 ] )
    {
        theSvcLvlPfAid4 = mySvcLvlPfAid4;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid4( const CT_TL1_LogicalAddr& theSvcLvlPfAid4 )
{
    myBitSet[ INDEX_SvcLvlPfAid4 ] = true;
    mySvcLvlPfAid4 = theSvcLvlPfAid4;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName4( string& theSvcLvlPfName4 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName4 ] )
    {
        theSvcLvlPfName4 = mySvcLvlPfName4;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName4( const string& theSvcLvlPfName4 )
{
    myBitSet[ INDEX_SvcLvlPfName4 ] = true;
    mySvcLvlPfName4 = theSvcLvlPfName4;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt5( int16& theSvcLvlCodePt5 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt5 ] )
    {
        theSvcLvlCodePt5 = mySvcLvlCodePt5;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt5( const int16& theSvcLvlCodePt5 )
{
    myBitSet[ INDEX_SvcLvlCodePt5 ] = true;
    mySvcLvlCodePt5= theSvcLvlCodePt5;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid5( CT_TL1_LogicalAddr& theSvcLvlPfAid5 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid5 ] )
    {
        theSvcLvlPfAid5 = mySvcLvlPfAid5;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid5( const CT_TL1_LogicalAddr& theSvcLvlPfAid5 )
{
    myBitSet[ INDEX_SvcLvlPfAid5 ] = true;
    mySvcLvlPfAid5 = theSvcLvlPfAid5;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName5( string& theSvcLvlPfName5 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName5 ] )
    {
        theSvcLvlPfName5 = mySvcLvlPfName5;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName5( const string& theSvcLvlPfName5 )
{
    myBitSet[ INDEX_SvcLvlPfName5 ] = true;
    mySvcLvlPfName5 = theSvcLvlPfName5;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt6( int16& theSvcLvlCodePt6 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt6 ] )
    {
        theSvcLvlCodePt6 = mySvcLvlCodePt6;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt6( const int16& theSvcLvlCodePt6 )
{
    myBitSet[ INDEX_SvcLvlCodePt6 ] = true;
    mySvcLvlCodePt6= theSvcLvlCodePt6;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid6( CT_TL1_LogicalAddr& theSvcLvlPfAid6 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid6 ] )
    {
        theSvcLvlPfAid6 = mySvcLvlPfAid6;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid6( const CT_TL1_LogicalAddr& theSvcLvlPfAid6 )
{
    myBitSet[ INDEX_SvcLvlPfAid6 ] = true;
    mySvcLvlPfAid6 = theSvcLvlPfAid6;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName6( string& theSvcLvlPfName6 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName6 ] )
    {
        theSvcLvlPfName6 = mySvcLvlPfName6;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName6( const string& theSvcLvlPfName6 )
{
    myBitSet[ INDEX_SvcLvlPfName6 ] = true;
    mySvcLvlPfName6 = theSvcLvlPfName6;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt7( int16& theSvcLvlCodePt7 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt7 ] )
    {
        theSvcLvlCodePt7 = mySvcLvlCodePt7;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt7( const int16& theSvcLvlCodePt7 )
{
    myBitSet[ INDEX_SvcLvlCodePt7 ] = true;
    mySvcLvlCodePt7= theSvcLvlCodePt7;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid7( CT_TL1_LogicalAddr& theSvcLvlPfAid7 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid7 ] )
    {
        theSvcLvlPfAid7 = mySvcLvlPfAid7;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid7( const CT_TL1_LogicalAddr& theSvcLvlPfAid7 )
{
    myBitSet[ INDEX_SvcLvlPfAid7 ] = true;
    mySvcLvlPfAid7 = theSvcLvlPfAid7;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName7( string& theSvcLvlPfName7 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName7 ] )
    {
        theSvcLvlPfName7 = mySvcLvlPfName7;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName7( const string& theSvcLvlPfName7 )
{
    myBitSet[ INDEX_SvcLvlPfName7 ] = true;
    mySvcLvlPfName7 = theSvcLvlPfName7;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt8( int16& theSvcLvlCodePt8 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt8 ] )
    {
        theSvcLvlCodePt8 = mySvcLvlCodePt8;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt8( const int16& theSvcLvlCodePt8 )
{
    myBitSet[ INDEX_SvcLvlCodePt8 ] = true;
    mySvcLvlCodePt8= theSvcLvlCodePt8;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid8( CT_TL1_LogicalAddr& theSvcLvlPfAid8 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid8 ] )
    {
        theSvcLvlPfAid8 = mySvcLvlPfAid8;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid8( const CT_TL1_LogicalAddr& theSvcLvlPfAid8 )
{
    myBitSet[ INDEX_SvcLvlPfAid8 ] = true;
    mySvcLvlPfAid8 = theSvcLvlPfAid8;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName8( string& theSvcLvlPfName8 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName8 ] )
    {
        theSvcLvlPfName8 = mySvcLvlPfName8;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName8( const string& theSvcLvlPfName8 )
{
    myBitSet[ INDEX_SvcLvlPfName8 ] = true;
    mySvcLvlPfName8 = theSvcLvlPfName8;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt9( int16& theSvcLvlCodePt9) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt9 ] )
    {
        theSvcLvlCodePt9= mySvcLvlCodePt9;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt9 ( const int16& theSvcLvlCodePt9)
{
    myBitSet[ INDEX_SvcLvlCodePt9] = true;
    mySvcLvlCodePt9 = theSvcLvlCodePt9;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid9( CT_TL1_LogicalAddr& theSvcLvlPfAid9 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid9 ] )
    {
        theSvcLvlPfAid9 = mySvcLvlPfAid9;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid9( const CT_TL1_LogicalAddr& theSvcLvlPfAid9 )
{
    myBitSet[ INDEX_SvcLvlPfAid9 ] = true;
    mySvcLvlPfAid9 = theSvcLvlPfAid9;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName9( string& theSvcLvlPfName9 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName9 ] )
    {
        theSvcLvlPfName9 = mySvcLvlPfName9;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName9( const string& theSvcLvlPfName9 )
{
    myBitSet[ INDEX_SvcLvlPfName9 ] = true;
    mySvcLvlPfName9 = theSvcLvlPfName9;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlCodePt10( int16& theSvcLvlCodePt10 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlCodePt10 ] )
    {
        theSvcLvlCodePt10 = mySvcLvlCodePt10;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlCodePt10( const int16& theSvcLvlCodePt10 )
{
    myBitSet[ INDEX_SvcLvlCodePt10 ] = true;
    mySvcLvlCodePt10 = theSvcLvlCodePt10;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfAid10( CT_TL1_LogicalAddr& theSvcLvlPfAid10 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfAid10 ] )
    {
        theSvcLvlPfAid10 = mySvcLvlPfAid10;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfAid10( const CT_TL1_LogicalAddr& theSvcLvlPfAid10 )
{
    myBitSet[ INDEX_SvcLvlPfAid10 ] = true;
    mySvcLvlPfAid10 = theSvcLvlPfAid10;
}

//--------------------------------------------------------------
bool 
TL1_SlpolicyRspBlk::GetSvcLvlPfName10( string& theSvcLvlPfName10 ) const
{
    if( true == myBitSet[ INDEX_SvcLvlPfName10 ] )
    {
        theSvcLvlPfName10 = mySvcLvlPfName10;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_SlpolicyRspBlk::SetSvcLvlPfName10( const string& theSvcLvlPfName10 )
{
    myBitSet[ INDEX_SvcLvlPfName10 ] = true;
    mySvcLvlPfName10 = theSvcLvlPfName10;
}


