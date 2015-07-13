/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         September 10, 2014 Jing Jin
DESCRIPTION:    Implementation file for EXDPATH TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXDPATHPARAMETERS_H__
#include <TL1Core/TL1_ExdpathParameters.h>
#endif

TL1_ExdpathParameters::TL1_ExdpathParameters()
{
    myHandle=       (LT_Handle*)0;
    myCtag=         (LT_Ctag)0;
    myExdpathName=  (string*)0;
    myRoute=        (CT_ControlPlane_Hops*)0;
    myInsertBefore= (CT_ControlPlane_Hops*)0;
    myInsertAfter=  (CT_ControlPlane_Hops*)0;
    myRemove=       (CT_ControlPlane_Hops*)0;
    mySubRoute=     (CT_ControlPlane_Hops*)0;
}

TL1_ExdpathParameters::~TL1_ExdpathParameters()
{
}

TL1_ExdpathParameters::TL1_ExdpathParameters(const TL1_ExdpathParameters& theInst )
{
    myHandle=       theInst.myHandle;
    myCtag=         theInst.myCtag;
    myExdpathName=  theInst.myExdpathName;
    myRoute=        theInst.myRoute;
    myInsertBefore= theInst.myInsertBefore;
    myInsertAfter=  theInst.myInsertAfter;
    myRemove=       theInst.myRemove;
    mySubRoute=     theInst.mySubRoute;
}

TL1_ExdpathParameters& 
TL1_ExdpathParameters::operator=( const TL1_ExdpathParameters& theInst )
{
    myHandle=       theInst.myHandle;
    myCtag=         theInst.myCtag;
    myExdpathName=  theInst.myExdpathName;
    myRoute=        theInst.myRoute;
    myInsertBefore= theInst.myInsertBefore;
    myInsertAfter=  theInst.myInsertAfter;
    myRemove=       theInst.myRemove;
    mySubRoute=     theInst.mySubRoute;

    return *this;
}

bool TL1_ExdpathParameters::
operator==( const TL1_ExdpathParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myExdpathName != theInst.myExdpathName )
        return false;

    if ( myRoute != theInst.myRoute )
        return false;

    if ( myInsertBefore != theInst.myInsertBefore )
        return false;

    if ( myInsertAfter != theInst.myInsertAfter )
        return false;

    if ( myRemove != theInst.myRemove )
        return false;

    if ( mySubRoute != theInst.mySubRoute )
        return false;

    return true;
}

