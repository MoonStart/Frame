/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 11, 2006 - Thomas J. Novak
DESCRIPTION:    Implementation file for OSI TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSIPARAMETERS_H__
#include <TL1Core/TL1_OSIParameters.h>
#endif

TL1_OSIRTRParameters::TL1_OSIRTRParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myAlarmProfile=     (CT_ProfileTableId*)0;
    myPrimaryState=     (CT_SM_PST*)0;
    myEonGre=			(bool*)0;

    myPrimaryAddr=      (string*)0;
    myAuxAddr1=         (string*)0;
    myAuxAddr2=         (string*)0;
    myRSysId=           (string*)0;
    myMaxLifetime=      (uint16*)0;
    myLevel=            (uint16*)0;
    myNumMaxArea=       (uint16*)0;
}

TL1_OSIRTRParameters::TL1_OSIRTRParameters(const TL1_OSIRTRParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myPrimaryState=     theInst.myPrimaryState;
    myEonGre=			theInst.myEonGre;

    myPrimaryAddr=      theInst.myPrimaryAddr;
    myAuxAddr1=         theInst.myAuxAddr1;
    myAuxAddr2=         theInst.myAuxAddr2;
    myRSysId=           theInst.myRSysId;
    myMaxLifetime=      theInst.myMaxLifetime;
    myLevel=            theInst.myLevel;
    myNumMaxArea=       theInst.myNumMaxArea;
}

TL1_OSIRTRParameters::~TL1_OSIRTRParameters()
{
}

TL1_OSIRTRParameters& 
TL1_OSIRTRParameters::operator=( const TL1_OSIRTRParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myPrimaryState=     theInst.myPrimaryState;
    myEonGre=			theInst.myEonGre;

    myPrimaryAddr=      theInst.myPrimaryAddr;
    myAuxAddr1=         theInst.myAuxAddr1;
    myAuxAddr2=         theInst.myAuxAddr2;
    myRSysId=           theInst.myRSysId;
    myMaxLifetime=      theInst.myMaxLifetime;
    myLevel=            theInst.myLevel;
    myNumMaxArea=       theInst.myNumMaxArea;

    return *this;
}

bool 
TL1_OSIRTRParameters::operator==( const TL1_OSIRTRParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myAlarmProfile != theInst.myAlarmProfile )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;

    if ( myPrimaryAddr != theInst.myPrimaryAddr )
        return false;

    if ( myAuxAddr1 != theInst.myAuxAddr1 )
        return false;

    if ( myAuxAddr2 != theInst.myAuxAddr2 )
        return false;

    if ( myRSysId != theInst.myRSysId )
        return false;

    if ( myMaxLifetime != theInst.myMaxLifetime )
        return false;

    if ( myLevel != theInst.myLevel )
        return false;

    if ( myNumMaxArea != theInst.myNumMaxArea )
        return false;

    if ( myEonGre != theInst.myEonGre )
        return false;

    return true;
}

TL1_OSIRTREntParameters::TL1_OSIRTREntParameters( )
{
}

TL1_OSIRTREntParameters::~TL1_OSIRTREntParameters( )
{
}

TL1_OSIRTREntParameters::TL1_OSIRTREntParameters(const TL1_OSIRTREntParameters& theInst ) :
    TL1_OSIRTRParameters( theInst ) 
{
}

TL1_OSIRTREntParameters&
TL1_OSIRTREntParameters::operator=( const TL1_OSIRTREntParameters& theInst )
{
    TL1_OSIRTRParameters::operator=( theInst );

    return *this;
}

bool 
TL1_OSIRTREntParameters::operator==( const TL1_OSIRTREntParameters& theInst ) const
{
    if ( false == TL1_OSIRTRParameters::operator== ( theInst ) )
        return false;

    return true;
}

TL1_OSIRTREdParameters::TL1_OSIRTREdParameters( )
{
    myIsCommandForced= (bool*)0;
}

TL1_OSIRTREdParameters::~TL1_OSIRTREdParameters( )
{
}

TL1_OSIRTREdParameters::TL1_OSIRTREdParameters(const TL1_OSIRTREdParameters& theInst ) :
    TL1_OSIRTRParameters( theInst ) 
{
    myIsCommandForced= theInst.myIsCommandForced;
}

TL1_OSIRTREdParameters&
TL1_OSIRTREdParameters::operator=( const TL1_OSIRTREdParameters& theInst )
{
    TL1_OSIRTRParameters::operator=( theInst );
    myIsCommandForced= theInst.myIsCommandForced;

    return *this;
}

bool 
TL1_OSIRTREdParameters::operator==( const TL1_OSIRTREdParameters& theInst ) const
{
    if ( false == TL1_OSIRTRParameters::operator== ( theInst ) )
        return false;

    if ( myIsCommandForced != theInst.myIsCommandForced )
        return false;

    return true;
}

