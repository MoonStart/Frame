/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Aug 06, 2010 - Chengsi Shao
DESCRIPTION:    Implementation file for OPR ADMREROUTE Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ARRPARAMETERS_H__
#include <TL1Core/TL1_ArrParameters.h>
#endif

TL1_OprArrParameters::TL1_OprArrParameters( )
{
    myHandle=      (LT_Handle*)0;
    myCtag=        (LT_Ctag)0;
    myCallId=      (CT_ControlPlane_CallId*)0;
    myLinkAddr=    (CT_TL1_LinkAddr*)0;
    myAvoidLinks=  (CT_ControlPlane_Hops*)0;
    myPathType=    (CT_CallPathType*)0;
    myExpPathAddr= (CT_TL1_ExppathAddr*)0;
    myCostFlag=    (bool*)0;
    myCmdMode=     (bool*)0;
}

TL1_OprArrParameters::TL1_OprArrParameters( const TL1_OprArrParameters & theInst )
{
    myHandle=      theInst.myHandle;
    myCtag=        theInst.myCtag;
    myCallId=      theInst.myCallId;
    myLinkAddr=    theInst.myLinkAddr;
    myAvoidLinks=  theInst.myAvoidLinks;
    myPathType=    theInst.myPathType;
    myExpPathAddr= theInst.myExpPathAddr;
    myCostFlag=    theInst.myCostFlag;
    myCmdMode=     theInst.myCmdMode;
}

TL1_OprArrParameters::~TL1_OprArrParameters( )
{
}

TL1_OprArrParameters&
TL1_OprArrParameters::operator=( const TL1_OprArrParameters& theInst )
{
    myHandle=      theInst.myHandle;
    myCtag=        theInst.myCtag;
    myCallId=      theInst.myCallId;
    myLinkAddr=    theInst.myLinkAddr;
    myAvoidLinks=  theInst.myAvoidLinks;
    myPathType=    theInst.myPathType;
    myExpPathAddr= theInst.myExpPathAddr;
    myCostFlag=    theInst.myCostFlag;
    myCmdMode=     theInst.myCmdMode;

    return *this;
}

bool TL1_OprArrParameters::operator==( const TL1_OprArrParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;
    if ( myCtag != theInst.myCtag )
        return false;
    if ( myCallId != theInst.myCallId )
        return false;
    if ( myLinkAddr != theInst.myLinkAddr )
        return false;
    if ( myAvoidLinks != theInst.myAvoidLinks )
        return false;
    if ( myPathType != theInst.myPathType )
        return false;
    if ( myExpPathAddr != theInst.myExpPathAddr )
        return false;
    if ( myCostFlag != theInst.myCostFlag )
        return false;
    if ( myCmdMode != theInst.myCmdMode )
        return false;    

    return true;
}

//--------------------------------------------------------------------------------

CT_CallPathType*
TL1_OprArrParameters::GetPathType() const
{
    return myPathType;
}

void
TL1_OprArrParameters::SetPathType( CT_CallPathType * theType )
{
    myPathType = theType;
}

//--------------------------------------------------------------------------------

CT_TL1_ExppathAddr*
TL1_OprArrParameters::GetExpPathAddr() const
{
    return myExpPathAddr;
}

void
TL1_OprArrParameters::SetExpPathAddr( CT_TL1_ExppathAddr* theAddr )
{
    myExpPathAddr = theAddr;
}

//--------------------------------------------------------------------------------

bool*
TL1_OprArrParameters::GetCostOpt() const
{
    return myCostFlag;
}

void
TL1_OprArrParameters::SetCostOpt( bool* theCostFlag )
{
    myCostFlag = theCostFlag;
}

//--------------------------------------------------------------------------------

bool*
TL1_OprArrParameters::GetCmdMode() const
{
    return myCmdMode;
}

void
TL1_OprArrParameters::SetCmdMode( bool* theCmdMode )
{
    myCmdMode = theCmdMode;
}

