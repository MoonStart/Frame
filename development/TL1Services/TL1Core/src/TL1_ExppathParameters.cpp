/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Implementation file for EXPPATH TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EXPPATHPARAMETERS_H__
#include <TL1Core/TL1_ExppathParameters.h>
#endif

TL1_ExppathParameters::TL1_ExppathParameters()
{
    myHandle=       (LT_Handle*)0;
    myCtag=         (LT_Ctag)0;
    myExppathName=  (string*)0;
    myInsertBefore= (CT_ControlPlane_Hops*)0;
    myInsertAfter=  (CT_ControlPlane_Hops*)0;
    myRemove=       (CT_ControlPlane_Hops*)0;
    mySubRoute=     (CT_ControlPlane_Hops*)0;
}

TL1_ExppathParameters::~TL1_ExppathParameters()
{
}

TL1_ExppathParameters::TL1_ExppathParameters(const TL1_ExppathParameters& theInst )
{
    myHandle=       theInst.myHandle;
    myCtag=         theInst.myCtag;
    myExppathName=  theInst.myExppathName;
    myInsertBefore= theInst.myInsertBefore;
    myInsertAfter=  theInst.myInsertAfter;
    myRemove=       theInst.myRemove;
    mySubRoute=     theInst.mySubRoute;
}

TL1_ExppathParameters& 
TL1_ExppathParameters::operator=( const TL1_ExppathParameters& theInst )
{
    myHandle=       theInst.myHandle;
    myCtag=         theInst.myCtag;
    myExppathName=  theInst.myExppathName;
    myInsertBefore= theInst.myInsertBefore;
    myInsertAfter=  theInst.myInsertAfter;
    myRemove=       theInst.myRemove;
    mySubRoute=     theInst.mySubRoute;

    return *this;
}

bool TL1_ExppathParameters::
operator==( const TL1_ExppathParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myExppathName != theInst.myExppathName )
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

