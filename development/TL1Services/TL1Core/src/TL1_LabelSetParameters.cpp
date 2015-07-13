/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010  - Tom Novak
DESCRIPTION:    Implementation file for LABELSET TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LABELSETPARAMETERS_H__
#include <TL1Core/TL1_LabelSetParameters.h>
#endif

TL1_LabelSetParameters::TL1_LabelSetParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myIngress=          (CT_ControlPlane_LabelSet*)0;
    myEgress=           (CT_ControlPlane_LabelSet*)0;
    myOperationType=    (CT_OperationType*)0;
    mySeedLabelSet=     (CT_TL1_LabelSetAddr*)0;
    myIdxRangeList=     (CT_TL1_LabelSetIdxRangeList*)0;
}

TL1_LabelSetParameters::~TL1_LabelSetParameters()
{
}

TL1_LabelSetParameters::TL1_LabelSetParameters(const TL1_LabelSetParameters& theInst )
{
    myHandle=           theInst.myHandle;
    myCtag=             theInst.myCtag;
    myIngress=          theInst.myIngress;
    myEgress=           theInst.myEgress;
    myOperationType=    theInst.myOperationType;
    mySeedLabelSet=     theInst.mySeedLabelSet;
    myIdxRangeList=     theInst.myIdxRangeList;
}

TL1_LabelSetParameters& 
TL1_LabelSetParameters::operator=( const TL1_LabelSetParameters& theInst )
{
    myHandle=           theInst.myHandle;
    myCtag=             theInst.myCtag;
    myIngress=          theInst.myIngress;
    myEgress=           theInst.myEgress;
    myOperationType=    theInst.myOperationType;
    mySeedLabelSet=     theInst.mySeedLabelSet;
    myIdxRangeList=     theInst.myIdxRangeList;

    return *this;
}

bool TL1_LabelSetParameters::
operator==( const TL1_LabelSetParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myIngress != theInst.myIngress )
        return false;

    if ( myEgress != theInst.myEgress )
        return false;

    if ( myOperationType != theInst.myOperationType )
        return false;

    if ( mySeedLabelSet != theInst.mySeedLabelSet )
        return false;

    if ( myIdxRangeList != theInst.myIdxRangeList )
        return false;

    return true;
}
