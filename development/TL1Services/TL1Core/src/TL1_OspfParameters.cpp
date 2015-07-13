/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Implementation file for OSPF TL1 ENT/ED Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSPFPARAMETERS_H__
#include <TL1Core/TL1_OspfParameters.h>
#endif

TL1_OspfParameters::TL1_OspfParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myPrimaryState=     (CT_SM_PST*)0;

    myAdjacencyAddr=    (CT_TL1_AdjacencyAddr*)0;
    myInterfaceAddr=    (CT_TL1_LinkAddr*)0;
    myAreaAddr=         (CT_TL1_AreaAddr*)0;
    myInterfaceType=    (CT_InterfaceType*)0;
    myIPAddr=           (uint32*)0;
    myCommandMode=      (bool*)0;
}

TL1_OspfParameters::TL1_OspfParameters(const TL1_OspfParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myPrimaryState=     theInst.myPrimaryState;

    myAdjacencyAddr=    theInst.myAdjacencyAddr;
    myInterfaceAddr=    theInst.myInterfaceAddr;
    myAreaAddr=         theInst.myAreaAddr;
    myInterfaceType=    theInst.myInterfaceType;
    myIPAddr=           theInst.myIPAddr;
    myCommandMode=      theInst.myCommandMode;
}

TL1_OspfParameters::~TL1_OspfParameters()
{
}

TL1_OspfParameters& 
TL1_OspfParameters::operator=( const TL1_OspfParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myPrimaryState=     theInst.myPrimaryState;

    myAdjacencyAddr=    theInst.myAdjacencyAddr;
    myInterfaceAddr=    theInst.myInterfaceAddr;
    myAreaAddr=         theInst.myAreaAddr;
    myInterfaceType=    theInst.myInterfaceType;
    myIPAddr=           theInst.myIPAddr;
    myCommandMode=      theInst.myCommandMode;

    return *this;
}

bool 
TL1_OspfParameters::operator==( const TL1_OspfParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;

    if ( myAdjacencyAddr != theInst.myAdjacencyAddr )
        return false;

    if ( myInterfaceAddr != theInst.myInterfaceAddr )
        return false;

    if ( myAreaAddr != theInst.myAreaAddr )
        return false;

    if ( myInterfaceType != theInst.myInterfaceType )
        return false;

    if ( myIPAddr != theInst.myIPAddr )
        return false;

    if ( myCommandMode != theInst.myCommandMode )
        return false;

    return true;
}

TL1_OspfrpEntParameters::TL1_OspfrpEntParameters()
{
    myHandle=                 (LT_Handle*)0;
    myCtag=                   (LT_Ctag)0;
    myChildRoutingAreaId=     (uint32*)0;
    myParentRoutingAreaId=    (uint32*)0;
    myEntryType=              (CT_Ospfrp_Entry_Type*)0;
    myParentNodeId=           (uint32*)0;
    myParentTgtAddr=          (uint32*)0;
    myParentTgtAddrMask=      (uint32*)0;
    myChildTgtAddr=           (uint32*)0;
    myChildTgtAddrMask=       (uint32*)0;
    myParentLinkAddr=         (uint32*)0;
    myParentLinkIfIdx=        (uint32*)0;
    myChildLinkAddr=          (uint32*)0;
    myChildLinkIfIdx=         (uint32*)0;
    myPrecedence=             (uint8*)0;
}

TL1_OspfrpEntParameters::TL1_OspfrpEntParameters(const TL1_OspfrpEntParameters& theInst )
{
    myHandle=                 theInst.myHandle;    
    myCtag=                   theInst.myCtag;
    myChildRoutingAreaId=     theInst.myChildRoutingAreaId;
    myParentRoutingAreaId=    theInst.myParentRoutingAreaId;
    myEntryType=              theInst.myEntryType;
    myParentNodeId=           theInst.myParentNodeId;
    myParentTgtAddr=          theInst.myParentTgtAddr;
    myParentTgtAddrMask=      theInst.myParentTgtAddrMask;
    myChildTgtAddr=           theInst.myChildTgtAddr;
    myChildTgtAddrMask=       theInst.myChildTgtAddrMask;
    myParentLinkAddr=         theInst.myParentLinkAddr;
    myParentLinkIfIdx=        theInst.myParentLinkIfIdx;
    myChildLinkAddr=          theInst.myChildLinkAddr;
    myChildLinkIfIdx=         theInst.myChildLinkIfIdx;
    myPrecedence=             theInst.myPrecedence;
}

TL1_OspfrpEntParameters::~TL1_OspfrpEntParameters()
{
}

TL1_OspfrpEntParameters& 
TL1_OspfrpEntParameters::operator=( const TL1_OspfrpEntParameters& theInst )
{
    myHandle=                 theInst.myHandle;    
    myCtag=                   theInst.myCtag;
    myChildRoutingAreaId=     theInst.myChildRoutingAreaId;
    myParentRoutingAreaId=    theInst.myParentRoutingAreaId;
    myEntryType=              theInst.myEntryType;
    myParentNodeId=           theInst.myParentNodeId;
    myParentTgtAddr=          theInst.myParentTgtAddr;
    myParentTgtAddrMask=      theInst.myParentTgtAddrMask;
    myChildTgtAddr=           theInst.myChildTgtAddr;
    myChildTgtAddrMask=       theInst.myChildTgtAddrMask;
    myParentLinkAddr=         theInst.myParentLinkAddr;
    myParentLinkIfIdx=        theInst.myParentLinkIfIdx;
    myChildLinkAddr=          theInst.myChildLinkAddr;
    myChildLinkIfIdx=         theInst.myChildLinkIfIdx;
    myPrecedence=             theInst.myPrecedence;

    return *this;
}

bool 
TL1_OspfrpEntParameters::operator==( const TL1_OspfrpEntParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myChildRoutingAreaId != theInst.myChildRoutingAreaId )
        return false;

    if ( myParentRoutingAreaId != theInst.myParentRoutingAreaId )
        return false;

    if ( myEntryType != theInst.myEntryType )
        return false;

    if ( myParentNodeId != theInst.myParentNodeId )
        return false;

    if ( myParentTgtAddr != theInst.myParentTgtAddr )
        return false;

    if ( myParentTgtAddrMask != theInst.myParentTgtAddrMask )
        return false;

    if ( myChildTgtAddr != theInst.myChildTgtAddr )
        return false;

    if ( myChildTgtAddrMask != theInst.myChildTgtAddrMask )
        return false;

    if ( myParentLinkAddr != theInst.myParentLinkAddr )
        return false;

    if ( myParentLinkIfIdx != theInst.myParentLinkIfIdx )
        return false;

    if ( myChildLinkAddr != theInst.myChildLinkAddr )
        return false;

    if ( myChildLinkIfIdx != theInst.myChildLinkIfIdx )
        return false;

    if ( myPrecedence != theInst.myPrecedence )
        return false;

    return true;
}

TL1_OspfrpEdParameters::TL1_OspfrpEdParameters()
{
    myHandle=                 (LT_Handle*)0;
    myCtag=                   (LT_Ctag)0;
    myChildRoutingAreaId=     (uint32*)0;
    myParentRoutingAreaId=    (uint32*)0;
    myParentNodeId=           (uint32*)0;
    myParentTgtAddr=          (uint32*)0;
    myParentTgtAddrMask=      (uint32*)0;
    myChildTgtAddr=           (uint32*)0;
    myChildTgtAddrMask=       (uint32*)0;
    myParentLinkAddr=         (uint32*)0;
    myParentLinkIfIdx=        (uint32*)0;
    myChildLinkAddr=          (uint32*)0;
    myChildLinkIfIdx=         (uint32*)0;
    myPrecedence=             (uint8*)0;
}

TL1_OspfrpEdParameters::TL1_OspfrpEdParameters(const TL1_OspfrpEdParameters& theInst )
{
    myHandle=                 theInst.myHandle;    
    myCtag=                   theInst.myCtag;
    myChildRoutingAreaId=     theInst.myChildRoutingAreaId;
    myParentRoutingAreaId=    theInst.myParentRoutingAreaId;
    myParentNodeId=           theInst.myParentNodeId;
    myParentTgtAddr=          theInst.myParentTgtAddr;
    myParentTgtAddrMask=      theInst.myParentTgtAddrMask;
    myChildTgtAddr=           theInst.myChildTgtAddr;
    myChildTgtAddrMask=       theInst.myChildTgtAddrMask;
    myParentLinkAddr=         theInst.myParentLinkAddr;
    myParentLinkIfIdx=        theInst.myParentLinkIfIdx;
    myChildLinkAddr=          theInst.myChildLinkAddr;
    myChildLinkIfIdx=         theInst.myChildLinkIfIdx;
    myPrecedence=             theInst.myPrecedence;
}

TL1_OspfrpEdParameters::~TL1_OspfrpEdParameters()
{
}

TL1_OspfrpEdParameters& 
TL1_OspfrpEdParameters::operator=( const TL1_OspfrpEdParameters& theInst )
{
    myHandle=                 theInst.myHandle;    
    myCtag=                   theInst.myCtag;
    myChildRoutingAreaId=     theInst.myChildRoutingAreaId;
    myParentRoutingAreaId=    theInst.myParentRoutingAreaId;
    myParentNodeId=           theInst.myParentNodeId;
    myParentTgtAddr=          theInst.myParentTgtAddr;
    myParentTgtAddrMask=      theInst.myParentTgtAddrMask;
    myChildTgtAddr=           theInst.myChildTgtAddr;
    myChildTgtAddrMask=       theInst.myChildTgtAddrMask;
    myParentLinkAddr=         theInst.myParentLinkAddr;
    myParentLinkIfIdx=        theInst.myParentLinkIfIdx;
    myChildLinkAddr=          theInst.myChildLinkAddr;
    myChildLinkIfIdx=         theInst.myChildLinkIfIdx;
    myPrecedence=             theInst.myPrecedence;

    return *this;
}

bool 
TL1_OspfrpEdParameters::operator==( const TL1_OspfrpEdParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myChildRoutingAreaId != theInst.myChildRoutingAreaId )
        return false;

    if ( myParentRoutingAreaId != theInst.myParentRoutingAreaId )
        return false;

    if ( myParentNodeId != theInst.myParentNodeId )
        return false;

    if ( myParentTgtAddr != theInst.myParentTgtAddr )
        return false;

    if ( myParentTgtAddrMask != theInst.myParentTgtAddrMask )
        return false;

    if ( myChildTgtAddr != theInst.myChildTgtAddr )
        return false;

    if ( myChildTgtAddrMask != theInst.myChildTgtAddrMask )
        return false;

    if ( myParentLinkAddr != theInst.myParentLinkAddr )
        return false;

    if ( myParentLinkIfIdx != theInst.myParentLinkIfIdx )
        return false;

    if ( myChildLinkAddr != theInst.myChildLinkAddr )
        return false;

    if ( myChildLinkIfIdx != theInst.myChildLinkIfIdx )
        return false;

    if ( myPrecedence != theInst.myPrecedence )
        return false;

    return true;
}
