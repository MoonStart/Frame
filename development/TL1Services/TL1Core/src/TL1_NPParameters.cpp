/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Implementation file for NP TL1 ENT and ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NPPARAMETERS_H__
#include <TL1Core/TL1_NPParameters.h>
#endif

TL1_NPParameters::TL1_NPParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myPrimaryState=     (CT_SM_PST*)0;

    myNpName=           (string*)0;
    myTimeout=          (uint16*)0;
}

TL1_NPParameters::TL1_NPParameters(const TL1_NPParameters& theInst ) 
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myPrimaryState=     theInst.myPrimaryState;

    myNpName=           theInst.myNpName;
    myTimeout=          theInst.myTimeout;
}

TL1_NPParameters::~TL1_NPParameters()
{
}

TL1_NPParameters& 
TL1_NPParameters::operator=( const TL1_NPParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myPrimaryState=     theInst.myPrimaryState;

    myNpName=           theInst.myNpName;
    myTimeout=          theInst.myTimeout;
    return *this;
}

bool 
TL1_NPParameters::operator==( const TL1_NPParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;

    if ( myNpName != theInst.myNpName )
        return false;

    if ( myTimeout != theInst.myTimeout )
        return false;
  
    return true;
}

TL1_NPEntParameters::TL1_NPEntParameters( )
{
}

TL1_NPEntParameters::~TL1_NPEntParameters( )
{
}

TL1_NPEntParameters::TL1_NPEntParameters(const TL1_NPEntParameters& theInst ) :
    TL1_NPParameters( theInst ) 
{
}

TL1_NPEntParameters&
TL1_NPEntParameters::operator=( const TL1_NPEntParameters& theInst )
{
    TL1_NPParameters::operator=( theInst );

    return *this;
}

bool 
TL1_NPEntParameters::operator==( const TL1_NPEntParameters& theInst ) const
{
    if ( false == TL1_NPParameters::operator== ( theInst ) )
        return false;

    return true;
}

TL1_NPEdParameters::TL1_NPEdParameters( )
{
}

TL1_NPEdParameters::~TL1_NPEdParameters( )
{
}

TL1_NPEdParameters::TL1_NPEdParameters(const TL1_NPEdParameters& theInst ) :
    TL1_NPParameters( theInst ) 
{
}

TL1_NPEdParameters&
TL1_NPEdParameters::operator=( const TL1_NPEdParameters& theInst )
{
    TL1_NPParameters::operator=( theInst );

    return *this;
}

bool 
TL1_NPEdParameters::operator==( const TL1_NPEdParameters& theInst ) const
{
    if ( false == TL1_NPParameters::operator== ( theInst ) )
        return false;

    return true;
}


