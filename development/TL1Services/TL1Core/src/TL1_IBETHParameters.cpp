/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         
DESCRIPTION:    Implementation file for IBETH TL1 ENT/ED 
                Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IBETHPARAMETERS_H__
#include <TL1Core/TL1_IBETHParameters.h>
#endif

#ifndef __T7100_TL1AGENTUTILITY_H__
#include <TL1Core/T7100_TL1AgentUtility.h>
#endif

TL1_IBETHParameters::TL1_IBETHParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myLkType=           (CT_LkType*)0;
    myBridge=           (int*)0;
	myP2PVlan =         (int*)0;
    myPrimaryState=     (CT_SM_PST*)0;
   
}

TL1_IBETHParameters::TL1_IBETHParameters(const TL1_IBETHParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myLkType=           theInst.myLkType;
    myBridge=           theInst.myBridge;
	myP2PVlan=           theInst.myP2PVlan;
    myPrimaryState=     theInst.myPrimaryState;
}

TL1_IBETHParameters::~TL1_IBETHParameters()
{
}

TL1_IBETHParameters& 
TL1_IBETHParameters::operator=( const TL1_IBETHParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myLkType=           theInst.myLkType;
    myBridge=           theInst.myBridge;
	myP2PVlan=          theInst.myP2PVlan;
    myPrimaryState=     theInst.myPrimaryState;
    
    return *this;
}

bool 
TL1_IBETHParameters::operator==( const TL1_IBETHParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myLkType != theInst.myLkType )
        return false;

    if ( myBridge != theInst.myBridge )
        return false;

	if ( myP2PVlan != theInst.myP2PVlan )
		   return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;
 
    return true;
}

TL1_IBETHEntParameters::TL1_IBETHEntParameters( )
{
}

TL1_IBETHEntParameters::~TL1_IBETHEntParameters( )
{
}

TL1_IBETHEntParameters::TL1_IBETHEntParameters(const TL1_IBETHEntParameters& theInst ) :
    TL1_IBETHParameters( theInst ) 
{
}

TL1_IBETHEntParameters&
TL1_IBETHEntParameters::operator=( const TL1_IBETHEntParameters& theInst )
{
    TL1_IBETHParameters::operator=( theInst );

    return *this;
}

bool 
TL1_IBETHEntParameters::operator==( const TL1_IBETHEntParameters& theInst ) const
{
    if ( false == TL1_IBETHParameters::operator== ( theInst ) )
        return false;

    return true;
}

TL1_IBETHEdParameters::TL1_IBETHEdParameters( )
{
}

TL1_IBETHEdParameters::~TL1_IBETHEdParameters( )
{
}

TL1_IBETHEdParameters::TL1_IBETHEdParameters(const TL1_IBETHEdParameters& theInst ) :
    TL1_IBETHParameters( theInst ) 
{
  
}

TL1_IBETHEdParameters&
TL1_IBETHEdParameters::operator=( const TL1_IBETHEdParameters& theInst )
{
    TL1_IBETHParameters::operator=( theInst );
  
    return *this;
}

bool 
TL1_IBETHEdParameters::operator==( const TL1_IBETHEdParameters& theInst ) const
{
    if ( false == TL1_IBETHParameters::operator== ( theInst ) )
        return false;

    return true;
}

