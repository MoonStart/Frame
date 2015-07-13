/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Shawn He
DESCRIPTION:    Implementation file for GCC TL1 ENT/ED 
                Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_GCCPARAMETERS_H__
#include <TL1Core/TL1_GCCParameters.h>
#endif

#ifndef __T7100_TL1AGENTUTILITY_H__
#include <TL1Core/T7100_TL1AgentUtility.h>
#endif

TL1_GCCParameters::TL1_GCCParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myAlarmProfile=     (CT_ProfileTableId*)0;
    myNpOwner=          (uint8*)0;
    myPrimaryState=     (CT_SM_PST*)0;
    myProfileAddr=      (CT_PPPProfAddr*)0;
    myType=             (CT_GCC_Type*)0; 
}

TL1_GCCParameters::TL1_GCCParameters(const TL1_GCCParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myNpOwner=          theInst.myNpOwner;
    myPrimaryState=     theInst.myPrimaryState;
    myProfileAddr=      theInst.myProfileAddr;
    myType=             theInst.myType;
}

TL1_GCCParameters::~TL1_GCCParameters()
{
}

TL1_GCCParameters& 
TL1_GCCParameters::operator=( const TL1_GCCParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myNpOwner=          theInst.myNpOwner;
    myPrimaryState=     theInst.myPrimaryState;
    myProfileAddr=      theInst.myProfileAddr;
    myType=             theInst.myType;
    
    return *this;
}

bool 
TL1_GCCParameters::operator==( const TL1_GCCParameters& theInst ) const
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

    if ( myType != theInst.myType )
        return false;
 
    return true;
}

TL1_GCCEntParameters::TL1_GCCEntParameters( )
{
}

TL1_GCCEntParameters::~TL1_GCCEntParameters( )
{
}

TL1_GCCEntParameters::TL1_GCCEntParameters(const TL1_GCCEntParameters& theInst ) :
    TL1_GCCParameters( theInst ) 
{
}

TL1_GCCEntParameters&
TL1_GCCEntParameters::operator=( const TL1_GCCEntParameters& theInst )
{
    TL1_GCCParameters::operator=( theInst );

    return *this;
}

bool 
TL1_GCCEntParameters::operator==( const TL1_GCCEntParameters& theInst ) const
{
    if ( false == TL1_GCCParameters::operator== ( theInst ) )
        return false;

    return true;
}

TL1_GCCEdParameters::TL1_GCCEdParameters( )
:myIsCommandForced(0)
{
}

TL1_GCCEdParameters::~TL1_GCCEdParameters( )
{
}

TL1_GCCEdParameters::TL1_GCCEdParameters(const TL1_GCCEdParameters& theInst ) :
    TL1_GCCParameters( theInst ) 
{
    myIsCommandForced = theInst.myIsCommandForced;
}

TL1_GCCEdParameters&
TL1_GCCEdParameters::operator=( const TL1_GCCEdParameters& theInst )
{
    TL1_GCCParameters::operator=( theInst );
    myIsCommandForced = theInst.myIsCommandForced;

    return *this;
}

bool 
TL1_GCCEdParameters::operator==( const TL1_GCCEdParameters& theInst ) const
{
    if ( false == TL1_GCCParameters::operator== ( theInst ) )
        return false;

    if ( myIsCommandForced != theInst.myIsCommandForced )
    {
        return false;
    }

    return true;
}

//------------------------------------------------------------------------
bool TL1_GCCEdParameters::IsControlPlaneRequest()
{
    return T7100_TL1AgentUtility::IsControlPlaneRequest( GetHandle() );
}
