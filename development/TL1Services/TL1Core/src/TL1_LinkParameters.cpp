/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 5, 2007 - Mike Rodgers
DESCRIPTION:    Implementation file for TL1 Link Parameter classes
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LINKPARAMETERS_H__
#include <TL1Core/TL1_LinkParameters.h>
#endif

TL1_LinkParameters::TL1_LinkParameters()
{
    myHandle=                   (LT_Handle*)0;
    myCtag=                     (LT_Ctag)0;
    myTLname=                   (string*)0;
    myNearEndAddrType=          (CT_TLNEADDRT*)0;
    myNearEndAddr=              (CT_ControlPlane_TL*)0;
    myNeighborDiscovery=        (CT_TL_DISCOVERY_TYPE*)0;
    myNearEndMask=              (CT_ControlPlane_Addr*)0;
    myNearEndParentTL=          (CT_TL1_LinkAddr*)0;
    myCost=                     (uint32*)0;
    myNeighborIfIndex=          (CT_ControlPlane_Addr*)0;
    myNeighborNodeId=           (CT_ControlPlane_Addr*)0;
    myLinkPfAid=                (CT_TL1_LogicalAddr*)0;
    myNeighborSignalingAddr=    (CT_ControlPlane_Addr*)0;
    myNeighborSignalingId=      (CT_ControlPlane_Addr*)0;
    myRouting=                  (CT_TL_ROUTING*)0;
    mySignaling=                (CT_TL_SIGNALING*)0;
    myRouterAreaId=             (uint32*)0;
    mySrlg=                     (CT_ControlPlane_Srlg*)0;
    myLatency=                  (uint32*)0;
    myLatencyMode=              (CT_LatencyMode*)0;
    myCarrierId=                (string*)0;
    myResourceClass=            (uint32*)0;
    myResource=                 (CT_TL1_ResourceAddr*)0;
    myIfName=                   (CT_IfNumber*)0;
    myIfIndex=                  (uint32*)0;
    myDhcp=                     (bool*)0;
    myPrimaryState=             (CT_SM_PST*)0;
    mySecondaryState=           (CT_SM_SST*)0;
    myBLname=                   (string*)0;
    myAddTLList=                (string*)0;
    myDelTLList=                (string*)0;
    myProfileName=              (string*)0;
    myNetworkAddressType=       (CT_LINKPF_NAT_TYPE*)0;
    myHelloInterval=            (uint16*)0;
    myRouterDeadInterval=       (uint16*)0;
    myRetransmissionInternal=   (uint16*)0;
    myServiceLevelProfile=      (CT_TL1_LogicalAddr*)0;
    myServiceLevelPolicy=       (CT_TL1_LogicalAddr*)0;
    myGMPLSMode=                (CT_GMPLS_MODE*)0;
    myPmd=                      (uint16*)0;
    myOsnr=                     (uint16*)0;
    myFwmp=                     (int*)0;
    myPdl=                      (int*)0;
    myResidualCD=               (int*)0;
    mySpmNoise=                 (int*)0;
    myXpmNoise=                 (int*)0;	
    myARUSupport=               (bool*)0;
    myG709Mode=                 (CT_G709_MODE*)0;
    myResourceLayer=            (CT_RESOURCE_LAYER*)0;
}

TL1_LinkParameters::TL1_LinkParameters(const TL1_LinkParameters& theInst )
{
    *this = theInst;
}

TL1_LinkParameters::~TL1_LinkParameters()
{
}

TL1_LinkParameters& 
TL1_LinkParameters::operator=( const TL1_LinkParameters& theInst )
{
    myHandle= theInst.myHandle;    
    myCtag= theInst.myCtag;
    myTLname = theInst.myTLname;
    myNearEndAddrType = theInst.myNearEndAddrType;
    myNearEndAddr = theInst.myNearEndAddr;
    myNeighborDiscovery = theInst.myNeighborDiscovery;
    myNearEndMask = theInst.myNearEndMask;
    myNearEndParentTL = theInst.myNearEndParentTL;
    myCost = theInst.myCost;
    myNeighborIfIndex = theInst.myNeighborIfIndex;
    myNeighborNodeId = theInst.myNeighborNodeId;
    myLinkPfAid = theInst.myLinkPfAid;
    myNeighborSignalingAddr = theInst.myNeighborSignalingAddr;
    myNeighborSignalingId = theInst.myNeighborSignalingId;
    myRouting = theInst.myRouting;
    mySignaling = theInst.mySignaling;
    myRouterAreaId = theInst.myRouterAreaId;
    mySrlg = theInst.mySrlg;
    myLatency = theInst.myLatency;
    myLatencyMode = theInst.myLatencyMode;
    myCarrierId = theInst.myCarrierId;
    myResourceClass = theInst.myResourceClass;
    myResource = theInst.myResource;
    myIfName = theInst.myIfName;
    myIfIndex = theInst.myIfIndex;
    myDhcp = theInst.myDhcp;
    myPrimaryState = theInst.myPrimaryState;
    mySecondaryState = theInst.mySecondaryState;
    myBLname = theInst.myBLname;
    myAddTLList = theInst.myAddTLList;
    myDelTLList = theInst.myDelTLList;
    myProfileName = theInst.myProfileName;
    myNetworkAddressType = theInst.myNetworkAddressType;
    myHelloInterval = theInst.myHelloInterval;
    myRouterDeadInterval = theInst.myRouterDeadInterval;
    myRetransmissionInternal = theInst.myRetransmissionInternal;
    myServiceLevelProfile = theInst.myServiceLevelProfile;
    myServiceLevelPolicy = theInst.myServiceLevelPolicy;
    myGMPLSMode = theInst.myGMPLSMode;
    myPmd= theInst.myPmd;
    myOsnr= theInst.myOsnr;
    myFwmp= theInst.myFwmp;
    myPdl= theInst.myPdl;
    myResidualCD= theInst.myResidualCD;
    mySpmNoise= theInst.mySpmNoise;
    myXpmNoise= theInst.myXpmNoise;
    myARUSupport= theInst.myARUSupport;
    myG709Mode = theInst.myG709Mode;
    myResourceLayer = theInst.myResourceLayer;

    return *this;
}

bool 
TL1_LinkParameters::operator==( const TL1_LinkParameters& theInst ) const
{
    if(myHandle != theInst.myHandle)                                    return false;   
    if(myCtag != theInst.myCtag)                                        return false;
    if(myTLname != theInst.myTLname)                                    return false;
    if(myNearEndAddrType != theInst.myNearEndAddrType)                  return false;
    if(myNearEndAddr != theInst.myNearEndAddr)                          return false;
    if(myNeighborDiscovery != theInst.myNeighborDiscovery)              return false;
    if(myNearEndMask != theInst.myNearEndMask)                          return false;
    if(myNearEndParentTL != theInst.myNearEndParentTL)                  return false;
    if(myCost != theInst.myCost)                                        return false;
    if(myNeighborIfIndex != theInst.myNeighborIfIndex)                  return false;
    if(myNeighborNodeId != theInst.myNeighborNodeId)                    return false;
    if(myLinkPfAid != theInst.myLinkPfAid)                              return false;
    if(myNeighborSignalingAddr != theInst.myNeighborSignalingAddr)      return false;
    if(myNeighborSignalingId != theInst.myNeighborSignalingId)          return false;
    if(myRouting != theInst.myRouting)                                  return false;
    if(mySignaling != theInst.mySignaling)                              return false;
    if(myRouterAreaId != theInst.myRouterAreaId)                        return false;
    if(mySrlg != theInst.mySrlg)                                        return false;
    if(myLatency != theInst.myLatency)                                  return false;
    if(myLatencyMode != theInst.myLatencyMode)                          return false;
    if(myCarrierId != theInst.myCarrierId)                              return false;
    if(myResourceClass != theInst.myResourceClass)                      return false;
    if(myResource != theInst.myResource)                                return false;
    if(myIfName != theInst.myIfName)                                    return false;
    if(myIfIndex != theInst.myIfIndex)                                  return false;
    if(myDhcp != theInst.myDhcp)                                        return false;
    if(myPrimaryState != theInst.myPrimaryState)                        return false;
    if(mySecondaryState != theInst.mySecondaryState)                    return false;
    if(myBLname != theInst.myBLname)                                    return false;
    if(myAddTLList != theInst.myAddTLList)                              return false;
    if(myDelTLList != theInst.myDelTLList)                              return false;
    if(myProfileName != theInst.myProfileName)                          return false;
    if(myNetworkAddressType != theInst.myNetworkAddressType)            return false;
    if(myHelloInterval != theInst.myHelloInterval)                      return false;
    if(myRouterDeadInterval != theInst.myRouterDeadInterval)            return false;
    if(myRetransmissionInternal != theInst.myRetransmissionInternal)    return false;
    if(myServiceLevelProfile != theInst.myServiceLevelProfile)          return false;
    if(myServiceLevelPolicy != theInst.myServiceLevelPolicy)            return false;
    if(myGMPLSMode != theInst.myGMPLSMode)                              return false;
    if(myPmd != theInst.myPmd)                                          return false;
    if(myOsnr != theInst.myOsnr)                                        return false;
    if(myFwmp != theInst.myFwmp)                                        return false;
    if(myPdl != theInst.myPdl)                                          return false;
    if(myResidualCD != theInst.myResidualCD)                            return false;
    if(mySpmNoise != theInst.mySpmNoise)                                return false;
    if(myXpmNoise != theInst.myXpmNoise)                                return false;
    if(myARUSupport != theInst.myARUSupport)                            return false;
    if(myG709Mode != theInst.myG709Mode)                                return false;
    if(myResourceLayer != theInst.myResourceLayer)                      return false;

    return true;
}

TL1_TrLinkParameters::TL1_TrLinkParameters( ) :
 myHandle((LT_Handle*)0)
,myCtag((LT_Ctag)0)
,myTLname((string*)0 )
,myCost((uint32*)0)
,myNeighborIfIndex((CT_ControlPlane_Addr*)0)
,myNeighborNodeId((CT_ControlPlane_Addr*)0)
,myLinkPfAid((CT_TL1_LogicalAddr*)0)
,myNeighborSignalingAddr((CT_ControlPlane_Addr*)0)
,myNeighborSignalingId((CT_ControlPlane_Addr*)0)
,myRouterAreaId((uint32*)0)
,myResourceClass((uint32*)0)
,myModuleAddr((CT_TL1_ModuleAddr*)0)
,myPortId((CT_TL1_Port*)0)
,myFacSubType((CT_FacilitySubType*) 0)
,myAdaptation((CT_Adaptation*) 0)
,myPmd((uint16*) 0)
,myOsnr((uint16*) 0)
,myIfIndex((uint32*)0)
,myPdl((int*) 0)
,myNearEndParentTL((CT_TL1_LinkAddr*)0)
,myPrimaryState((CT_SM_PST*) 0) 
,mySecondaryState((CT_SM_SST*) 0)
{
}

TL1_TrLinkParameters::~TL1_TrLinkParameters()
{

}

TL1_TrLinkParameters::TL1_TrLinkParameters(const TL1_TrLinkParameters& theInst )
{
    *this = theInst;
}

TL1_TrLinkParameters& 
TL1_TrLinkParameters::operator=( const TL1_TrLinkParameters& theInst )
{
    myHandle=                   theInst.myHandle;
    myCtag=                     theInst.myCtag;
    myTLname=                   theInst.myTLname;
    myCost=                     theInst.myCost;
    myNeighborIfIndex=          theInst.myNeighborIfIndex;
    myNeighborNodeId=           theInst.myNeighborNodeId;
    myLinkPfAid=                theInst.myLinkPfAid;
    myNeighborSignalingAddr=    theInst.myNeighborSignalingAddr;   
    myNeighborSignalingId=      theInst.myNeighborSignalingId;
    myRouterAreaId=             theInst.myRouterAreaId;
    myResourceClass=            theInst.myResourceClass;
    myModuleAddr=               theInst.myModuleAddr;
    myPortId=                   theInst.myPortId;
    myFacSubType=               theInst.myFacSubType;
    myAdaptation=               theInst.myAdaptation;
    myPmd=                      theInst.myPmd;
    myOsnr=                     theInst.myOsnr;
    myIfIndex=                  theInst.myIfIndex;
    myPdl=                      theInst.myPdl;
    myNearEndParentTL=          theInst.myNearEndParentTL;
    myPrimaryState=             theInst.myPrimaryState;
    mySecondaryState=           theInst.mySecondaryState;

    return *this;
}

bool TL1_TrLinkParameters::operator==( const TL1_TrLinkParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myTLname != theInst.myTLname )
        return false;

    if ( myCost != theInst.myCost )
        return false;

    if ( myNeighborIfIndex != theInst.myNeighborIfIndex )
        return false;

    if ( myNeighborNodeId != theInst.myNeighborNodeId )
        return false;

    if ( myLinkPfAid != theInst.myLinkPfAid )
        return false;

    if ( myNeighborSignalingAddr != theInst.myNeighborSignalingAddr )
        return false;
  
    if ( myNeighborSignalingId != theInst.myNeighborSignalingId )
        return false;

    if ( myRouterAreaId != theInst.myRouterAreaId )
        return false;

    if ( myResourceClass != theInst.myResourceClass )
        return false;

    if ( myModuleAddr != theInst.myModuleAddr )
        return false;

    if ( myPortId != theInst.myPortId )
        return false;

    if ( myFacSubType != theInst.myFacSubType )
        return false;

    if ( myAdaptation != theInst.myAdaptation )
        return false;

    if ( myPmd != theInst.myPmd )
        return false;

    if ( myOsnr != theInst.myOsnr )
        return false;

    if ( myIfIndex != theInst.myIfIndex )
        return false;

    if ( myPdl != theInst.myPdl )
        return false;

    if ( myNearEndParentTL != theInst.myNearEndParentTL )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;

    if ( mySecondaryState != theInst.mySecondaryState )
        return false;

    return true;
}

TL1_BLinkParameters::TL1_BLinkParameters()
{
    myHandle=                   (LT_Handle*)0;
    myCtag=                     (LT_Ctag)0;
    myBLname=                   (string*)0;
    myBLType=                   (CT_BLType*)0;
    myCost=                     (uint32*)0;
    myNeighborIfIndex=          (CT_ControlPlane_Addr*)0;
    myRouting=                  (CT_TL_ROUTING*)0;
    mySrlg=                     (CT_ControlPlane_Srlg*)0;
    myLatencyMode=              (CT_LatencyMode*)0;
    myLatency=                  (uint32*)0;
    myResourceClass=            (uint32*)0;
    myPrimaryState=             (CT_SM_PST*)0;
    myAddTLList.clear();
    myDelTLList.clear();
}

TL1_BLinkParameters::TL1_BLinkParameters(const TL1_BLinkParameters& theInst )
{
    *this = theInst;
}

TL1_BLinkParameters::~TL1_BLinkParameters()
{
}

TL1_BLinkParameters& 
TL1_BLinkParameters::operator=( const TL1_BLinkParameters& theInst )
{
    myHandle= theInst.myHandle;    
    myCtag= theInst.myCtag;
    myCost = theInst.myCost;
    myBLname = theInst.myBLname;
    myBLType = theInst.myBLType;
    myNeighborIfIndex = theInst.myNeighborIfIndex;
    myRouting = theInst.myRouting;
    mySrlg = theInst.mySrlg;
    myLatencyMode = theInst.myLatencyMode;
    myLatency = theInst.myLatency;
    myResourceClass = theInst.myResourceClass;
    myPrimaryState = theInst.myPrimaryState;
    myAddTLList = theInst.myAddTLList;
    myDelTLList = theInst.myDelTLList;

    return *this;
}

bool 
TL1_BLinkParameters::operator==( const TL1_BLinkParameters& theInst ) const
{
    if(myHandle != theInst.myHandle)                                    return false;   
    if(myCtag != theInst.myCtag)                                        return false;
    if(myBLname != theInst.myBLname)                                    return false;
    if(myBLType != theInst.myBLType)                                    return false;
    if(myCost != theInst.myCost)                                        return false;
    if(myNeighborIfIndex != theInst.myNeighborIfIndex)                  return false;
    if(myRouting != theInst.myRouting)                                  return false;
    if(mySrlg != theInst.mySrlg)                                        return false;
    if(myLatencyMode != theInst.myLatencyMode)                          return false;
    if(myLatency != theInst.myLatency)                                  return false;
    if(myResourceClass != theInst.myResourceClass)                      return false;
    if(myPrimaryState != theInst.myPrimaryState)                        return false;
    if(myAddTLList != theInst.myAddTLList)                              return false;
    if(myDelTLList != theInst.myDelTLList)                              return false;

    return true;
}

