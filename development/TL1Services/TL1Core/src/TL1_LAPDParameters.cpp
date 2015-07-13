/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 25, 2006 - Thomas J. Novak
DESCRIPTION:    Implementation file for LAPD TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LAPDPARAMETERS_H__
#include <TL1Core/TL1_LAPDParameters.h>
#endif

TL1_LAPDParameters::TL1_LAPDParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myAlarmProfile=     (CT_ProfileTableId*)0;
    myPrimaryState=     (CT_SM_PST*)0;

    myFlwProtection=    (CT_LAPD_FlwProt*)0;
    myChkSumEnable=     (CT_LAPD_CheckSum*)0;
    myHldTmrMult=       (uint16*)0;
    myConfigTmr=        (uint16*)0;
    myHelloTmr=         (uint16*)0;
    myLMetric=          (uint16*)0;
    myReDirectHldTmr=   (uint16*)0;
    myRoutingLevel=     (uint16*)0;
    myEsConfigTmr=      (uint16*)0;
    myProfileAddr=      (CT_LapdProfAddr*)0;
}

TL1_LAPDParameters::TL1_LAPDParameters(const TL1_LAPDParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myPrimaryState=     theInst.myPrimaryState;

    myFlwProtection=    theInst.myFlwProtection;
    myChkSumEnable=     theInst.myChkSumEnable;
    myHldTmrMult=       theInst.myHldTmrMult;
    myConfigTmr=        theInst.myConfigTmr;
    myHelloTmr=         theInst.myHelloTmr;
    myLMetric=          theInst.myLMetric;
    myReDirectHldTmr=   theInst.myReDirectHldTmr;
    myRoutingLevel=     theInst.myRoutingLevel;
    myEsConfigTmr=      theInst.myEsConfigTmr;
    myProfileAddr=      theInst.myProfileAddr;
}

TL1_LAPDParameters::~TL1_LAPDParameters()
{
}

TL1_LAPDParameters& 
TL1_LAPDParameters::operator=( const TL1_LAPDParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myAlarmProfile=     theInst.myAlarmProfile;
    myPrimaryState=     theInst.myPrimaryState;

    myFlwProtection=    theInst.myFlwProtection;
    myChkSumEnable=     theInst.myChkSumEnable;
    myHldTmrMult=       theInst.myHldTmrMult;
    myConfigTmr=        theInst.myConfigTmr;
    myHelloTmr=         theInst.myHelloTmr;
    myLMetric=          theInst.myLMetric;
    myReDirectHldTmr=   theInst.myReDirectHldTmr;
    myRoutingLevel=     theInst.myRoutingLevel;
    myEsConfigTmr=      theInst.myEsConfigTmr;
    myProfileAddr=      theInst.myProfileAddr;

    return *this;
}

bool 
TL1_LAPDParameters::operator==( const TL1_LAPDParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myAlarmProfile != theInst.myAlarmProfile )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;

    if ( myFlwProtection != theInst.myFlwProtection )
        return false;

    if ( myChkSumEnable != theInst.myChkSumEnable )
        return false;

    if ( myHldTmrMult != theInst.myHldTmrMult )
        return false;

    if ( myConfigTmr != theInst.myConfigTmr )
        return false;

    if ( myHelloTmr != theInst.myHelloTmr )
        return false;

    if ( myLMetric != theInst.myLMetric )
        return false;

    if ( myReDirectHldTmr != theInst.myReDirectHldTmr )
        return false;

    if ( myRoutingLevel != theInst.myRoutingLevel )
        return false;

    if ( myEsConfigTmr != theInst.myEsConfigTmr )
        return false;

    if ( myProfileAddr != theInst.myProfileAddr )
        return false;
 
    return true;
}

TL1_LAPDEntParameters::TL1_LAPDEntParameters( )
{
    myRouterAddr=  (CT_OSIRtrAddr*)0;
}

TL1_LAPDEntParameters::~TL1_LAPDEntParameters( )
{
}

TL1_LAPDEntParameters::TL1_LAPDEntParameters(const TL1_LAPDEntParameters& theInst ) :
    TL1_LAPDParameters( theInst ) 
{
    myRouterAddr=  theInst.myRouterAddr;
}

TL1_LAPDEntParameters&
TL1_LAPDEntParameters::operator=( const TL1_LAPDEntParameters& theInst )
{
    TL1_LAPDParameters::operator=( theInst );

    myRouterAddr=  theInst.myRouterAddr;

    return *this;
}

bool 
TL1_LAPDEntParameters::operator==( const TL1_LAPDEntParameters& theInst ) const
{
    if ( false == TL1_LAPDParameters::operator== ( theInst ) )
        return false;

    if ( myRouterAddr !=  theInst.myRouterAddr )
        return false;

    return true;
}

TL1_LAPDEdParameters::TL1_LAPDEdParameters( )
{
    myIsCommandForced= (bool*)0;
}

TL1_LAPDEdParameters::~TL1_LAPDEdParameters( )
{
}

TL1_LAPDEdParameters::TL1_LAPDEdParameters(const TL1_LAPDEdParameters& theInst ) :
    TL1_LAPDParameters( theInst ) 
{
    myIsCommandForced= theInst.myIsCommandForced;
}

TL1_LAPDEdParameters&
TL1_LAPDEdParameters::operator=( const TL1_LAPDEdParameters& theInst )
{
    TL1_LAPDParameters::operator=( theInst );
    myIsCommandForced= theInst.myIsCommandForced;

    return *this;
}

bool 
TL1_LAPDEdParameters::operator==( const TL1_LAPDEdParameters& theInst ) const
{
    if ( false == TL1_LAPDParameters::operator== ( theInst ) )
        return false;

    if ( myIsCommandForced != theInst.myIsCommandForced )
        return false;

    return true;
}

