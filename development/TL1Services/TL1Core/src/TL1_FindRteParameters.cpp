/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 30, 2011 - TLD
DESCRIPTION:    Implementation file for TL1 OPR-FINDRTE parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_FindRteParameters.h>



TL1_OprFindRteParameters::TL1_OprFindRteParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myAEnd=             (CT_ControlPlane_TNA*)0;
    myZEnd=             (CT_ControlPlane_TNA*)0;
    myAEnd2=            (CT_ControlPlane_TNA*)0;
    myZEnd2=            (CT_ControlPlane_TNA*)0;
    myNodeAddr=         (CT_TL1_NodeAddr*)0;
    myNodeId2=          (uint32*)0;
    mySignalType=       (CT_Call_SignalType*)0;
    myMultiplierValue=  (uint8*)0;
    myWorkingToNode=    (uint32*)0;
    myProtectToNode=    (uint32*)0;
    myWorkingPath=      (CT_TL1_ExppathAddr*)0;
    myProtectPath=      (CT_TL1_ExppathAddr*)0;
    mySrlg=             (CT_ControlPlane_Srlg*)0;
    mySlpf=             (CT_TL1_LogicalAddr*)0;
    myExpRate=          (CT_TEL_daHz*)0;
    myGfpTs=            (uint8*)0;
    myWkgXPath=         (CT_TL1_ExdpathAddr*)0;
    myProtXPath=        (CT_TL1_ExdpathAddr*)0;
}


TL1_OprFindRteParameters::~TL1_OprFindRteParameters()
{
}


TL1_OprFindRteParameters::TL1_OprFindRteParameters(const TL1_OprFindRteParameters& theInst )
{
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myAEnd=                 theInst.myAEnd;
    myZEnd=                 theInst.myZEnd;
    myAEnd2=                theInst.myAEnd2;
    myZEnd2=                theInst.myZEnd2;
    myNodeAddr=             theInst.myNodeAddr;
    myNodeId2=              theInst.myNodeId2;
    mySignalType=           theInst.mySignalType;
    myMultiplierValue=      theInst.myMultiplierValue;
    myWorkingToNode=        theInst.myWorkingToNode;
    myProtectToNode=        theInst.myProtectToNode;
    myWorkingPath=          theInst.myWorkingPath;
    myProtectPath=          theInst.myProtectPath;
    mySrlg=                 theInst.mySrlg;
    mySlpf=                 theInst.mySlpf;
    myExpRate=              theInst.myExpRate;
    myGfpTs=                theInst.myGfpTs;
    myWkgXPath=             theInst.myWkgXPath;
    myProtXPath=            theInst.myProtXPath;
}


TL1_OprFindRteParameters& 
TL1_OprFindRteParameters::operator=( const TL1_OprFindRteParameters& theInst )
{
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myAEnd=                 theInst.myAEnd;
    myZEnd=                 theInst.myZEnd;
    myAEnd2=                theInst.myAEnd2;
    myZEnd2=                theInst.myZEnd2;
    myNodeAddr=             theInst.myNodeAddr;
    myNodeId2=              theInst.myNodeId2;
    mySignalType=           theInst.mySignalType;
    myMultiplierValue=      theInst.myMultiplierValue;
    myWorkingToNode=        theInst.myWorkingToNode;
    myProtectToNode=        theInst.myProtectToNode;
    myWorkingPath=          theInst.myWorkingPath;
    myProtectPath=          theInst.myProtectPath;
    mySrlg=                 theInst.mySrlg;
    mySlpf=                 theInst.mySlpf;
    myExpRate=              theInst.myExpRate;
    myGfpTs=                theInst.myGfpTs;
    myWkgXPath=             theInst.myWkgXPath;
    myProtXPath=            theInst.myProtXPath;

    return *this;
}


bool 
TL1_OprFindRteParameters::operator==( const TL1_OprFindRteParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myAEnd != theInst.myAEnd )
        return false;

    if ( myZEnd != theInst.myZEnd )
        return false;
        
    if ( myAEnd2 != theInst.myAEnd2 )
        return false;

    if ( myZEnd2 != theInst.myZEnd2 )
        return false;

    if ( myNodeAddr !=theInst.myNodeAddr )
        return false;

    if ( myNodeId2 !=theInst.myNodeId2 )
        return false;

    if ( mySignalType != theInst.mySignalType )
         return false;

    if ( myMultiplierValue != theInst.myMultiplierValue )
         return false;

    if ( myWorkingToNode != theInst.myWorkingToNode )
         return false;

    if ( myProtectToNode != theInst.myProtectToNode )
         return false;

    if ( myWorkingPath != theInst.myWorkingPath )
         return false;

    if ( myProtectPath != theInst.myProtectPath )
         return false;

    if ( mySrlg != theInst.mySrlg )
         return false;

    if ( mySlpf != theInst.mySlpf )
        return false;

    if ( myExpRate != theInst.myExpRate )
        return false;

    if ( myGfpTs != theInst.myGfpTs)
        return false;

    if ( myWkgXPath != theInst.myWkgXPath )
        return false;

    if ( myProtXPath != theInst.myProtXPath )
        return false;

    return true;
}
