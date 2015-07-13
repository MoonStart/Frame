/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Implementation file for PPP, PPPPF TL1 ENT/ED 
                Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PPPPARAMETERS_H__
#include <TL1Core/TL1_PPPParameters.h>
#endif

#ifndef __T7100_TL1AGENTUTILITY_H__
#include <TL1Core/T7100_TL1AgentUtility.h>
#endif

TL1_PPPParameters::TL1_PPPParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myAlarmProfile=     (CT_ProfileTableId*)0;
    myNpOwner=          (uint8*)0;
    myPrimaryState=     (CT_SM_PST*)0;
    myProfileAddr=      (CT_PPPProfAddr*)0;
}

TL1_PPPParameters::TL1_PPPParameters(const TL1_PPPParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myNpOwner=          theInst.myNpOwner;
    myPrimaryState=     theInst.myPrimaryState;
    myProfileAddr=      theInst.myProfileAddr;
}

TL1_PPPParameters::~TL1_PPPParameters()
{
}

TL1_PPPParameters& 
TL1_PPPParameters::operator=( const TL1_PPPParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myNpOwner=          theInst.myNpOwner;
    myPrimaryState=     theInst.myPrimaryState;
    myProfileAddr=      theInst.myProfileAddr;

    return *this;
}

bool 
TL1_PPPParameters::operator==( const TL1_PPPParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myAlarmProfile != theInst.myAlarmProfile )
        return false;
    
    if ( myNpOwner != theInst.myNpOwner )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;

    if ( myProfileAddr != theInst.myProfileAddr )
        return false;
 
    return true;
}

TL1_PPPEntParameters::TL1_PPPEntParameters( )
{
}

TL1_PPPEntParameters::~TL1_PPPEntParameters( )
{
}

TL1_PPPEntParameters::TL1_PPPEntParameters(const TL1_PPPEntParameters& theInst ) :
    TL1_PPPParameters( theInst ) 
{
}

TL1_PPPEntParameters&
TL1_PPPEntParameters::operator=( const TL1_PPPEntParameters& theInst )
{
    TL1_PPPParameters::operator=( theInst );

    return *this;
}

bool 
TL1_PPPEntParameters::operator==( const TL1_PPPEntParameters& theInst ) const
{
    if ( false == TL1_PPPParameters::operator== ( theInst ) )
        return false;

    return true;
}

TL1_PPPEdParameters::TL1_PPPEdParameters( )
:myIsCommandForced(0)
{
}

TL1_PPPEdParameters::~TL1_PPPEdParameters( )
{
}

TL1_PPPEdParameters::TL1_PPPEdParameters(const TL1_PPPEdParameters& theInst ) :
    TL1_PPPParameters( theInst ) 
{
    myIsCommandForced = theInst.myIsCommandForced;
}

TL1_PPPEdParameters&
TL1_PPPEdParameters::operator=( const TL1_PPPEdParameters& theInst )
{
    TL1_PPPParameters::operator=( theInst );
    myIsCommandForced = theInst.myIsCommandForced;

    return *this;
}

bool 
TL1_PPPEdParameters::operator==( const TL1_PPPEdParameters& theInst ) const
{
    if ( false == TL1_PPPParameters::operator== ( theInst ) )
        return false;

    if ( myIsCommandForced != theInst.myIsCommandForced )
    {
        return false;
    }

    return true;
}

//------------------------------------------------------------------------
bool TL1_PPPEdParameters::IsControlPlaneRequest()
{
    return T7100_TL1AgentUtility::IsControlPlaneRequest( GetHandle() );
}


TL1_PPPProfileEdParameters::TL1_PPPProfileEdParameters()
{
    myPfName=           (string*)0;
    myMaxUnits=         (uint16*)0;
    myFCS=              (CT_FCS*)0;
    myRestartTimer=     (uint16*)0;
    myMaxFailureCount=  (uint16*)0;
    myHandle=           (LT_Handle*)0;             
    myCtag=             (LT_Ctag)0;
}

TL1_PPPProfileEdParameters::TL1_PPPProfileEdParameters(const TL1_PPPProfileEdParameters& theBlock )
{
    myPfName=           theBlock.myPfName;
    myMaxUnits=         theBlock.myMaxUnits;
    myFCS=              theBlock.myFCS;
    myRestartTimer=     theBlock.myRestartTimer;
    myMaxFailureCount=  theBlock.myMaxFailureCount;
    myHandle=           theBlock.myHandle;     
    myCtag=             theBlock.myCtag;
}

TL1_PPPProfileEdParameters::~TL1_PPPProfileEdParameters()
{
}

TL1_PPPProfileEdParameters& 
TL1_PPPProfileEdParameters::operator=( const TL1_PPPProfileEdParameters& theBlock )
{
    myPfName=           theBlock.myPfName;
    myMaxUnits=         theBlock.myMaxUnits;
    myFCS=              theBlock.myFCS;
    myRestartTimer=     theBlock.myRestartTimer;
    myMaxFailureCount=  theBlock.myMaxFailureCount;
    myHandle=           theBlock.myHandle; 
    myCtag=             theBlock.myCtag;

    return *this;
}

bool 
TL1_PPPProfileEdParameters::operator==( const TL1_PPPProfileEdParameters& theBlock ) const
{
	if( myPfName != theBlock.myPfName )
		return false;

    if( myMaxUnits != theBlock.myMaxUnits )
        return false;

    if( myRestartTimer != theBlock.myRestartTimer )
        return false;

    if( myMaxFailureCount != theBlock.myMaxFailureCount )
        return false;

    if( myFCS != theBlock.myFCS )
        return false;

    if( myHandle != theBlock.myHandle )     
        return false;

    if( myCtag != theBlock.myCtag )
        return false;

    return true;
}
