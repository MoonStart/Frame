#ifndef __TL1_LINKPARAMETERS_H__
#define __TL1_LINKPARAMETERS_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 5, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Link Parameter classes
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <string>
#include <LumosTypes/LT_System.h>
#include <LumosTypes/LT_Link.h>

#ifndef __CT_TL1_CONTROLPLANEADDR_H__
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#ifndef __CT_TL1_LOGICALID_H__
#include <CommonTypes/CT_TL1_LogicalAddr.h>
#endif

#ifndef __TL1_LINKRSPBLK_H__
#include <Response/TL1_LinkRspBlk.h>
#endif

#include <CommonTypes/CT_ControlPlane_Convert.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>


class TL1_LinkParameters  
{
public:
    
    TL1_LinkParameters();
    virtual ~TL1_LinkParameters();

    TL1_LinkParameters(const TL1_LinkParameters& theInst );
    TL1_LinkParameters& operator=( const TL1_LinkParameters& theInst );
    bool operator==( const TL1_LinkParameters& theInst ) const;

    inline LT_Handle* GetHandle( ) const;
    inline void SetHandle( LT_Handle* theHandle );

    inline LT_Ctag GetCtag( ) const;
    inline void SetCtag( LT_Ctag theCtag );

    inline string* GetTLname() const;
    inline void SetTLname(string* theTLname);

    inline CT_TLNEADDRT* GetNearEndAddrType() const;
    inline void SetNearEndAddrType(CT_TLNEADDRT* theNearEndAddrType);

    inline CT_ControlPlane_TL* GetNearEndAddr() const;
    inline void SetNearEndAddr(CT_ControlPlane_TL* theNearEndAddr);

    inline CT_TL_DISCOVERY_TYPE* GetNeighborDiscovery() const;
    inline void SetNeighborDiscovery(CT_TL_DISCOVERY_TYPE* theNeighborDiscovery);

    inline CT_ControlPlane_Addr* GetNearEndMask() const;
    inline void SetNearEndMask(CT_ControlPlane_Addr* theNearEndMask);

    inline CT_TL1_LinkAddr* GetNearEndParentTL() const;
    inline void SetNearEndParentTL(CT_TL1_LinkAddr* theNearEndParentTL);

    inline uint32* GetCost() const;
    inline void SetCost(uint32* theCost);

    inline CT_ControlPlane_Addr* GetNeighborIfIndex() const;
    inline void SetNeighborIfIndex(CT_ControlPlane_Addr* theNeighborIfIndex);

    inline CT_ControlPlane_Addr* GetNeighborNodeId() const;
    inline void SetNeighborNodeId(CT_ControlPlane_Addr* theNeighborNodeId);

    inline CT_TL1_LogicalAddr* GetLinkPfAid() const;
    inline void SetLinkPfAid(CT_TL1_LogicalAddr* thePrtpfAid);

    inline CT_ControlPlane_Addr* GetNeighborSignalingAddr() const;
    inline void SetNeighborSignalingAddr(CT_ControlPlane_Addr* theNeighborSignalingAddr);

    inline CT_ControlPlane_Addr* GetNeighborSignalingId() const;
    inline void SetNeighborSignalingId(CT_ControlPlane_Addr* theNeighborSignalingId);

    inline CT_TL_ROUTING* GetRouting() const;
    inline void SetRouting(CT_TL_ROUTING* theRouting);

    inline CT_TL_SIGNALING* GetSignaling() const;
    inline void SetSignaling(CT_TL_SIGNALING* theSignaling);

    inline uint32* GetRouterAreaId() const;
    inline void SetRouterAreaId(uint32* theRouterAreaId);

    inline CT_ControlPlane_Srlg* GetSrlg() const;
    inline void SetSrlg(CT_ControlPlane_Srlg* theSrlg);

    inline uint32* GetLatency() const;
    inline void SetLatency(uint32* theLatency);

    inline CT_LatencyMode* GetLatencyMode( ) const;
    inline void SetLatencyMode( CT_LatencyMode* theLatencyMode );

    inline string* GetCarrierId() const;
    inline void SetCarrierId(string* theCarrierId);

    inline uint32* GetResourceClass() const;
    inline void SetResourceClass(uint32* theResourceClass);

    inline CT_TL1_ResourceAddr* GetResource() const;
    inline void SetResource(CT_TL1_ResourceAddr* theResource);

    inline CT_IfNumber* GetIfName() const;
    inline void SetIfName(CT_IfNumber* theIfName);

    inline uint32* GetIfIndex() const;
    inline void SetIfIndex(uint32* theIfIndex);

    inline bool* GetDhcp() const;
    inline void SetDhcp(bool* theGMPLSMode);

    inline CT_SM_PST* GetPrimaryState() const;
    inline void SetPrimaryState(CT_SM_PST* thePrimaryState);

    inline CT_SM_SST* GetSecondaryState() const;
    inline void SetSecondaryState(CT_SM_SST* theSecondaryState);

    inline string* GetBLname() const;
    inline void SetBLname(string* theBLname);

    inline string* GetAddTLList() const;
    inline void SetAddTLList(string* theAddTLList);

    inline string* GetDelTLList() const;
    inline void SetDelTLList(string* theDelTLList);

    inline string* GetProfileName( ) const;
    inline void SetProfileName( string* theProfileName );

    inline CT_LINKPF_NAT_TYPE* GetNetworkAddressType( ) const;
    inline void SetNetworkAddressType( CT_LINKPF_NAT_TYPE* theNetworkAddressType );

    inline uint16* GetHelloInterval( ) const;
    inline void SetHelloInterval( uint16* theHelloInterval );

    inline uint16* GetRouterDeadInterval( ) const;
    inline void SetRouterDeadInterval( uint16* theRouterDeadInterval );

    inline uint16* GetRetransmissionInternal( ) const;
    inline void SetRetransmissionInternal( uint16* theRetransmissionInternal );

    inline CT_TL1_LogicalAddr* GetServiceLevelProfile( ) const;
    inline void SetServiceLevelProfile( CT_TL1_LogicalAddr* theServiceLevelProfile );

    inline CT_TL1_LogicalAddr* GetServiceLevelPolicy( ) const;
    inline void SetServiceLevelPolicy( CT_TL1_LogicalAddr* theServiceLevelPolicy );

    inline CT_GMPLS_MODE* GetGMPLSMode( ) const;
    inline void SetGMPLSMode( CT_GMPLS_MODE* theGMPLSMode );

    inline uint16* GetPmd( ) const;
    inline void    SetPmd( uint16* thePmd );

    inline uint16* GetOsnr( ) const;
    inline void    SetOsnr( uint16* theOsnr );

    inline int*    GetFwmp( ) const;                
    inline void    SetFwmp( int* theFwmp );
	
    inline int* GetPdl( ) const;
    inline void SetPdl( int* thePdl );
	
    inline int* GetResidualCD( ) const;
    inline void SetResidualCD( int* theResidualCD );
	
    inline int* GetSpmNoise( ) const;
    inline void SetSpmNoise( int* theSpmNoise );
	
    inline int* GetXpmNoise( ) const;
    inline void SetXpmNoise( int* theXpmNoise );

    inline bool*   GetARUSupport( ) const;
    inline void    SetARUSupport( bool* theARUSupport );

    inline CT_G709_MODE* GetG709Mode( ) const;
    inline void SetG709Mode( CT_G709_MODE* theG709Mode );

    inline CT_RESOURCE_LAYER* GetResourceLayer( ) const;
    inline void SetResourceLayer( CT_RESOURCE_LAYER* theResourceLayer );

private:

    LT_Handle*              myHandle;
    LT_Ctag                 myCtag;
    string*                 myTLname;
    CT_TLNEADDRT*           myNearEndAddrType;
    CT_ControlPlane_TL*     myNearEndAddr;
    CT_TL_DISCOVERY_TYPE*   myNeighborDiscovery;
    CT_ControlPlane_Addr*   myNearEndMask;
    CT_TL1_LinkAddr*        myNearEndParentTL;
    uint32*                 myCost;
    CT_ControlPlane_Addr*   myNeighborIfIndex;
    CT_ControlPlane_Addr*   myNeighborNodeId;
    CT_TL1_LogicalAddr*     myLinkPfAid;
    CT_ControlPlane_Addr*   myNeighborSignalingAddr;
    CT_ControlPlane_Addr*   myNeighborSignalingId;
    CT_TL_ROUTING*          myRouting;
    CT_TL_SIGNALING*        mySignaling;
    uint32*                 myRouterAreaId;
    CT_ControlPlane_Srlg*   mySrlg;
    uint32*                 myLatency;
    CT_LatencyMode*         myLatencyMode;
    string*                 myCarrierId;
    uint32*                 myResourceClass;
    CT_TL1_ResourceAddr*    myResource;
    CT_IfNumber*            myIfName;
    uint32*                 myIfIndex;
    bool*                   myDhcp;
    CT_SM_PST*              myPrimaryState;
    CT_SM_SST*              mySecondaryState;
    string*                 myBLname;
    string*                 myAddTLList;
    string*                 myDelTLList;
    string*                 myProfileName;
    CT_LINKPF_NAT_TYPE*     myNetworkAddressType;
    uint16*                 myHelloInterval;
    uint16*                 myRouterDeadInterval;
    uint16*                 myRetransmissionInternal;
    CT_TL1_LogicalAddr*     myServiceLevelProfile;
    CT_TL1_LogicalAddr*     myServiceLevelPolicy;
    CT_GMPLS_MODE*          myGMPLSMode;
    uint16*                 myPmd;
    uint16*                 myOsnr;
    int*                    myFwmp;
    int*                    myPdl;
    int*                    myResidualCD;
    int*                    mySpmNoise;
    int*                    myXpmNoise;
    bool*                   myARUSupport;
    CT_G709_MODE*           myG709Mode;
    CT_RESOURCE_LAYER*      myResourceLayer;
};

//--------------------------------------------------------------------------------
inline LT_Handle* TL1_LinkParameters::GetHandle( ) const
{
    return myHandle;
}

inline void TL1_LinkParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag TL1_LinkParameters::GetCtag( ) const
{
    return myCtag;
}

inline void TL1_LinkParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//---------------------------------------------------------------------------
inline string* TL1_LinkParameters::GetTLname() const
{
    return myTLname;
}
inline void TL1_LinkParameters::SetTLname(string* theTLname)
{
    myTLname = theTLname;
} 

//---------------------------------------------------------------------------
inline CT_TLNEADDRT* TL1_LinkParameters::GetNearEndAddrType() const
{
    return myNearEndAddrType;
}
inline void TL1_LinkParameters::SetNearEndAddrType(CT_TLNEADDRT* theNearEndAddrType)
{
    myNearEndAddrType = theNearEndAddrType;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_TL* TL1_LinkParameters::GetNearEndAddr() const
{
    return myNearEndAddr;
}
inline void TL1_LinkParameters::SetNearEndAddr(CT_ControlPlane_TL* theNearEndAddr)
{
    myNearEndAddr = theNearEndAddr;
} 

//---------------------------------------------------------------------------
inline CT_TL_DISCOVERY_TYPE* TL1_LinkParameters::GetNeighborDiscovery() const
{
    return myNeighborDiscovery;
}
inline void TL1_LinkParameters::SetNeighborDiscovery(CT_TL_DISCOVERY_TYPE* theNeighborDiscovery)
{
    myNeighborDiscovery = theNeighborDiscovery;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_Addr* TL1_LinkParameters::GetNearEndMask() const
{
    return myNearEndMask;
}
inline void TL1_LinkParameters::SetNearEndMask(CT_ControlPlane_Addr* theNearEndMask)
{
    myNearEndMask = theNearEndMask;
} 

//---------------------------------------------------------------------------
inline CT_TL1_LinkAddr* TL1_LinkParameters::GetNearEndParentTL() const
{
    return myNearEndParentTL;
}
inline void TL1_LinkParameters::SetNearEndParentTL(CT_TL1_LinkAddr* theNearEndParentTL)
{
    myNearEndParentTL = theNearEndParentTL;
} 

//---------------------------------------------------------------------------
inline uint32* TL1_LinkParameters::GetCost() const
{
    return myCost;
}
inline void TL1_LinkParameters::SetCost(uint32* theCost)
{
    myCost = theCost;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_Addr* TL1_LinkParameters::GetNeighborIfIndex() const
{
    return myNeighborIfIndex;
}
inline void TL1_LinkParameters::SetNeighborIfIndex(CT_ControlPlane_Addr* theNeighborIfIndex)
{
    myNeighborIfIndex = theNeighborIfIndex;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_Addr* TL1_LinkParameters::GetNeighborNodeId() const
{
    return myNeighborNodeId;
}
inline void TL1_LinkParameters::SetNeighborNodeId(CT_ControlPlane_Addr* theNeighborNodeId)
{
    myNeighborNodeId = theNeighborNodeId;
} 

//---------------------------------------------------------------------------
inline CT_TL1_LogicalAddr* TL1_LinkParameters::GetLinkPfAid() const
{
    return myLinkPfAid;
}
inline void TL1_LinkParameters::SetLinkPfAid(CT_TL1_LogicalAddr* theLinkPfAid) 
{
    myLinkPfAid = theLinkPfAid;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_Addr* TL1_LinkParameters::GetNeighborSignalingAddr() const
{
    return myNeighborSignalingAddr;
}
inline void TL1_LinkParameters::SetNeighborSignalingAddr(CT_ControlPlane_Addr* theNeighborSignalingAddr)
{
    myNeighborSignalingAddr = theNeighborSignalingAddr;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_Addr* TL1_LinkParameters::GetNeighborSignalingId() const
{
    return myNeighborSignalingId;
}
inline void TL1_LinkParameters::SetNeighborSignalingId(CT_ControlPlane_Addr* theNeighborSignalingId)
{
    myNeighborSignalingId = theNeighborSignalingId;
} 

//---------------------------------------------------------------------------
inline CT_TL_ROUTING* TL1_LinkParameters::GetRouting() const
{
    return myRouting;
}
inline void TL1_LinkParameters::SetRouting(CT_TL_ROUTING* theRouting)
{
    myRouting = theRouting;
} 

//---------------------------------------------------------------------------
inline CT_TL_SIGNALING* TL1_LinkParameters::GetSignaling() const
{
    return mySignaling;
}
inline void TL1_LinkParameters::SetSignaling(CT_TL_SIGNALING* theSignaling)
{
    mySignaling = theSignaling;
} 

//---------------------------------------------------------------------------
inline uint32* TL1_LinkParameters::GetRouterAreaId() const
{
    return myRouterAreaId;
}
inline void TL1_LinkParameters::SetRouterAreaId(uint32* theRouterAreaId)
{
    myRouterAreaId = theRouterAreaId;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_Srlg* TL1_LinkParameters::GetSrlg() const
{
    return mySrlg;
}
inline void TL1_LinkParameters::SetSrlg(CT_ControlPlane_Srlg* theSrlg)
{
    mySrlg = theSrlg;
} 

//---------------------------------------------------------------------------
inline uint32* TL1_LinkParameters::GetLatency() const
{
    return myLatency;
}
inline void TL1_LinkParameters::SetLatency(uint32* theLatency)
{
    myLatency = theLatency;
} 

//---------------------------------------------------------------------------
inline CT_LatencyMode* TL1_LinkParameters::GetLatencyMode( ) const
{
    return myLatencyMode;
}
inline void TL1_LinkParameters::SetLatencyMode( CT_LatencyMode* theLatencyMode )
{
    myLatencyMode = theLatencyMode;
}

//---------------------------------------------------------------------------
inline string* TL1_LinkParameters::GetCarrierId() const
{
    return myCarrierId;
}
inline void TL1_LinkParameters::SetCarrierId(string* theCarrierId)
{
    myCarrierId = theCarrierId;
} 

//---------------------------------------------------------------------------
inline uint32* TL1_LinkParameters::GetResourceClass() const
{
    return myResourceClass;
}
inline void TL1_LinkParameters::SetResourceClass(uint32* theResourceClass)
{
    myResourceClass = theResourceClass;
} 

//---------------------------------------------------------------------------
inline CT_TL1_ResourceAddr* TL1_LinkParameters::GetResource() const
{
    return myResource;
}
inline void TL1_LinkParameters::SetResource(CT_TL1_ResourceAddr* theResource)
{
    myResource = theResource;
} 

//---------------------------------------------------------------------------
inline CT_IfNumber* TL1_LinkParameters::GetIfName() const
{
    return myIfName;
}
inline void TL1_LinkParameters::SetIfName(CT_IfNumber* theIfName)
{
    myIfName = theIfName;
} 

//---------------------------------------------------------------------------
inline uint32* TL1_LinkParameters::GetIfIndex() const
{
    return myIfIndex;
}
inline void TL1_LinkParameters::SetIfIndex(uint32* theIfIndex)
{
    myIfIndex = theIfIndex;
} 

//---------------------------------------------------------------------------
inline bool* TL1_LinkParameters::GetDhcp() const
{
    return myDhcp;
}
inline void TL1_LinkParameters::SetDhcp(bool* theDhcp)
{
    myDhcp = theDhcp;
} 

//---------------------------------------------------------------------------
inline CT_SM_PST* TL1_LinkParameters::GetPrimaryState() const
{
    return myPrimaryState;
}
inline void TL1_LinkParameters::SetPrimaryState(CT_SM_PST* thePrimaryState)
{
    myPrimaryState = thePrimaryState;
} 

//---------------------------------------------------------------------------
inline CT_SM_SST* TL1_LinkParameters::GetSecondaryState() const
{
    return mySecondaryState;
}
inline void TL1_LinkParameters::SetSecondaryState(CT_SM_SST* theSecondaryState)
{
    mySecondaryState = theSecondaryState;
} 

//---------------------------------------------------------------------------
inline string* TL1_LinkParameters::GetBLname() const
{
    return myBLname;
}
inline void TL1_LinkParameters::SetBLname(string* theBLname)
{
    myBLname = theBLname;
} 

//---------------------------------------------------------------------------
inline string* TL1_LinkParameters::GetAddTLList() const
{
    return myAddTLList;
}
inline void TL1_LinkParameters::SetAddTLList(string* theAddTLList)
{
    myAddTLList = theAddTLList;
} 

//---------------------------------------------------------------------------
inline string* TL1_LinkParameters::GetDelTLList() const
{
    return myDelTLList;
}
inline void TL1_LinkParameters::SetDelTLList(string* theDelTLList)
{
    myDelTLList = theDelTLList;
} 

//---------------------------------------------------------------------------
inline string* 
TL1_LinkParameters::GetProfileName( ) const
{
    return myProfileName;
}
inline void 
TL1_LinkParameters::SetProfileName( string* theProfileName )
{
    myProfileName = theProfileName;
}

//---------------------------------------------------------------------------
inline CT_LINKPF_NAT_TYPE* 
TL1_LinkParameters::GetNetworkAddressType( ) const
{
    return myNetworkAddressType;
}
inline void 
TL1_LinkParameters::SetNetworkAddressType( CT_LINKPF_NAT_TYPE* theNetworkAddressType )
{
    myNetworkAddressType = theNetworkAddressType;
}

//---------------------------------------------------------------------------
inline uint16* 
TL1_LinkParameters::GetHelloInterval( ) const
{
    return myHelloInterval;
}
inline void 
TL1_LinkParameters::SetHelloInterval( uint16* theHelloInterval )
{
    myHelloInterval = theHelloInterval;
}

//---------------------------------------------------------------------------
inline uint16* 
TL1_LinkParameters::GetRouterDeadInterval( ) const
{
    return myRouterDeadInterval;
}
inline void 
TL1_LinkParameters::SetRouterDeadInterval( uint16* theRouterDeadInterval )
{
    myRouterDeadInterval = theRouterDeadInterval;
}

//---------------------------------------------------------------------------
inline uint16* 
TL1_LinkParameters::GetRetransmissionInternal( ) const
{
    return myRetransmissionInternal;
}
inline void 
TL1_LinkParameters::SetRetransmissionInternal( uint16* theRetransmissionInternal )
{
    myRetransmissionInternal = theRetransmissionInternal;
}

//---------------------------------------------------------------------------
inline CT_TL1_LogicalAddr* 
TL1_LinkParameters::GetServiceLevelProfile( ) const
{
    return myServiceLevelProfile;
}
inline void 
TL1_LinkParameters::SetServiceLevelProfile( CT_TL1_LogicalAddr* theServiceLevelProfile )
{
    myServiceLevelProfile = theServiceLevelProfile;
}

//---------------------------------------------------------------------------
inline CT_TL1_LogicalAddr* 
TL1_LinkParameters::GetServiceLevelPolicy( ) const
{
    return myServiceLevelPolicy;
}
inline void 
TL1_LinkParameters::SetServiceLevelPolicy( CT_TL1_LogicalAddr* theServiceLevelPolicy )
{
    myServiceLevelPolicy = theServiceLevelPolicy;
}

//---------------------------------------------------------------------------
inline CT_GMPLS_MODE* 
TL1_LinkParameters::GetGMPLSMode( ) const
{
    return myGMPLSMode;
}
inline void 
TL1_LinkParameters::SetGMPLSMode( CT_GMPLS_MODE* theGMPLSMode )
{
    myGMPLSMode = theGMPLSMode;
}

//--------------------------------------------------------------------------------
inline uint16*                      
TL1_LinkParameters::GetPmd( ) const
{
    return myPmd;
}

inline void                        
TL1_LinkParameters::SetPmd( uint16* thePmd )
{
    myPmd = thePmd;
}

//--------------------------------------------------------------------------------
inline uint16*                      
TL1_LinkParameters::GetOsnr( ) const
{
    return myOsnr;
}

inline void                         
TL1_LinkParameters::SetOsnr( uint16* theOsnr )
{
    myOsnr = theOsnr;
}

//--------------------------------------------------------------------------------
inline int*    
TL1_LinkParameters::GetFwmp( ) const
{
    return myFwmp;
}

inline void    
TL1_LinkParameters::SetFwmp( int* theFwmp )
{
    myFwmp = theFwmp;
}

//--------------------------------------------------------------------------------
inline int*                      
TL1_LinkParameters::GetPdl( ) const
{
    return myPdl;
}

inline void                         
TL1_LinkParameters::SetPdl( int* thePdl )
{
    myPdl = thePdl;
}

//--------------------------------------------------------------------------------
inline int*                      
TL1_LinkParameters::GetResidualCD( ) const
{
    return myResidualCD;
}

inline void                         
TL1_LinkParameters::SetResidualCD( int* theResidualCD )
{
    myResidualCD = theResidualCD;
}

//--------------------------------------------------------------------------------
inline int*                      
TL1_LinkParameters::GetSpmNoise( ) const
{
    return mySpmNoise;
}

inline void                         
TL1_LinkParameters::SetSpmNoise( int* theSpmNoise )
{
    mySpmNoise = theSpmNoise;
}

//--------------------------------------------------------------------------------
inline int*                      
TL1_LinkParameters::GetXpmNoise( ) const
{
    return myXpmNoise;
}

inline void                         
TL1_LinkParameters::SetXpmNoise( int* theXpmNoise )
{
    myXpmNoise = theXpmNoise;
}

//--------------------------------------------------------------------------------
inline bool*   
TL1_LinkParameters::GetARUSupport( ) const
{
    return myARUSupport;
}

inline void    
TL1_LinkParameters::SetARUSupport( bool* theARUSupport )
{
    myARUSupport = theARUSupport;
}

//---------------------------------------------------------------------------
inline CT_G709_MODE* 
TL1_LinkParameters::GetG709Mode( ) const
{
    return myG709Mode;
}
inline void 
TL1_LinkParameters::SetG709Mode( CT_G709_MODE* theG709Mode )
{
    myG709Mode = theG709Mode;
}

//---------------------------------------------------------------------------
inline CT_RESOURCE_LAYER* 
TL1_LinkParameters::GetResourceLayer( ) const
{
    return myResourceLayer;
}
inline void 
TL1_LinkParameters::SetResourceLayer( CT_RESOURCE_LAYER* theResourceLayer )
{
    myResourceLayer = theResourceLayer;
}

//--------------------------------------------------------------------------------
class TL1_TrLinkParameters  
{
public:

    TL1_TrLinkParameters();
    virtual ~TL1_TrLinkParameters();

    TL1_TrLinkParameters(const TL1_TrLinkParameters& theInst );
    TL1_TrLinkParameters& operator=( const TL1_TrLinkParameters& theInst );
    bool operator==( const TL1_TrLinkParameters& theInst ) const;

    inline LT_Handle* GetHandle( ) const;
    inline void SetHandle( LT_Handle* theHandle );

    inline LT_Ctag GetCtag( ) const;
    inline void SetCtag( LT_Ctag theCtag );

    inline string* GetTLname() const;
    inline void SetTLname(string* theTLname);

    inline uint32* GetCost() const;
    inline void SetCost(uint32* theCost);

    inline CT_ControlPlane_Addr* GetNeighborIfIndex() const;
    inline void SetNeighborIfIndex(CT_ControlPlane_Addr* theNeighborIfIndex);

    inline CT_ControlPlane_Addr* GetNeighborNodeId() const;
    inline void SetNeighborNodeId(CT_ControlPlane_Addr* theNeighborNodeId);

    inline CT_TL1_LogicalAddr* GetLinkPfAid() const;
    inline void SetLinkPfAid(CT_TL1_LogicalAddr* thePrtpfAid);

    inline CT_ControlPlane_Addr* GetNeighborSignalingAddr() const;
    inline void SetNeighborSignalingAddr(CT_ControlPlane_Addr* theNeighborSignalingAddr);

    inline CT_ControlPlane_Addr* GetNeighborSignalingId() const;
    inline void SetNeighborSignalingId(CT_ControlPlane_Addr* theNeighborSignalingId);

    inline uint32* GetRouterAreaId() const;
    inline void SetRouterAreaId(uint32* theRouterAreaId);

    inline uint32* GetResourceClass() const;
    inline void SetResourceClass(uint32* theResourceClass);

    inline CT_TL1_ModuleAddr* GetModuleAddr( ) const;
    inline void SetModuleAddr( CT_TL1_ModuleAddr* theModuleAddr );

    inline CT_TL1_Port* GetPortId( ) const;
    inline void SetPortId( CT_TL1_Port* thePortId );

    inline CT_FacilitySubType* GetFacSubType() const;
    inline void SetFacSubType( CT_FacilitySubType* theFacSubType);

    inline CT_Adaptation* GetAdaptation() const;
    inline void SetAdaptation( CT_Adaptation* theAdaptation );

    inline uint16* GetPmd( ) const;
    inline void    SetPmd( uint16* thePmd );

    inline uint16* GetOsnr( ) const;
    inline void    SetOsnr( uint16* theOsnr );

    inline uint32* GetIfIndex() const;
    inline void SetIfIndex(uint32* theIfIndex);
    
    inline int* GetPdl( ) const;
    inline void SetPdl( int* thePdl );

    inline CT_TL1_LinkAddr* GetNearEndParentTL() const;
    inline void SetNearEndParentTL(CT_TL1_LinkAddr* theNearEndParentTL);

    inline CT_SM_PST* GetPrimaryState() const;
    inline void SetPrimaryState(CT_SM_PST* thePrimaryState);

    inline CT_SM_SST* GetSecondaryState() const;
    inline void SetSecondaryState(CT_SM_SST* theSecondaryState);

private:

    LT_Handle*              myHandle;
    LT_Ctag                 myCtag;
    string*                 myTLname;
    uint32*                 myCost;
    CT_ControlPlane_Addr*   myNeighborIfIndex;
    CT_ControlPlane_Addr*   myNeighborNodeId;
    CT_TL1_LogicalAddr*     myLinkPfAid;
    CT_ControlPlane_Addr*   myNeighborSignalingAddr;
    CT_ControlPlane_Addr*   myNeighborSignalingId;
    uint32*                 myRouterAreaId;
    uint32*                 myResourceClass;
    CT_TL1_ModuleAddr*      myModuleAddr;
    CT_TL1_Port*            myPortId;
    CT_FacilitySubType*     myFacSubType;
    CT_Adaptation*          myAdaptation;
    uint16*                 myPmd;
    uint16*                 myOsnr;
    uint32*                 myIfIndex;
    int*                    myPdl;
    CT_TL1_LinkAddr*        myNearEndParentTL;
    CT_SM_PST*              myPrimaryState;
    CT_SM_SST*              mySecondaryState;
};

//--------------------------------------------------------------------------------
LT_Handle* 
TL1_TrLinkParameters::GetHandle( ) const
{
    return myHandle;
}

void 
TL1_TrLinkParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
LT_Ctag 
TL1_TrLinkParameters::GetCtag( ) const
{
    return myCtag;
}

void 
TL1_TrLinkParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
string* 
TL1_TrLinkParameters::GetTLname() const
{
    return myTLname;
}

void 
TL1_TrLinkParameters::SetTLname(string* theTLname)
{
    myTLname = theTLname;
}

//--------------------------------------------------------------------------------
uint32* 
TL1_TrLinkParameters::GetCost() const
{
    return myCost;
}

void 
TL1_TrLinkParameters::SetCost(uint32* theCost)
{
    myCost = theCost;
}

//--------------------------------------------------------------------------------
CT_ControlPlane_Addr* 
TL1_TrLinkParameters::GetNeighborIfIndex() const
{
    return myNeighborIfIndex;
}

void 
TL1_TrLinkParameters::SetNeighborIfIndex(CT_ControlPlane_Addr* theNeighborIfIndex)
{
    myNeighborIfIndex = theNeighborIfIndex;
}

//--------------------------------------------------------------------------------
CT_ControlPlane_Addr* 
TL1_TrLinkParameters::GetNeighborNodeId() const
{
    return myNeighborNodeId;
}

void 
TL1_TrLinkParameters::SetNeighborNodeId(CT_ControlPlane_Addr* theNeighborNodeId)
{
    myNeighborNodeId = theNeighborNodeId;
}

//--------------------------------------------------------------------------------
CT_TL1_LogicalAddr* TL1_TrLinkParameters::GetLinkPfAid() const
{
    return myLinkPfAid;
}

void TL1_TrLinkParameters::SetLinkPfAid(CT_TL1_LogicalAddr* thePrtpfAid)
{
    myLinkPfAid = thePrtpfAid;
}

//--------------------------------------------------------------------------------
CT_ControlPlane_Addr* 
TL1_TrLinkParameters::GetNeighborSignalingAddr() const
{
    return myNeighborSignalingAddr;
}

void TL1_TrLinkParameters::SetNeighborSignalingAddr(CT_ControlPlane_Addr* theNeighborSignalingAddr)
{
    myNeighborSignalingAddr = theNeighborSignalingAddr;
}

//--------------------------------------------------------------------------------
CT_ControlPlane_Addr* 
TL1_TrLinkParameters::GetNeighborSignalingId() const
{
    return myNeighborSignalingId;
}

void 
TL1_TrLinkParameters::SetNeighborSignalingId(CT_ControlPlane_Addr* theNeighborSignalingId)
{
    myNeighborSignalingId = theNeighborSignalingId;
}

//--------------------------------------------------------------------------------
inline uint32* TL1_TrLinkParameters::GetRouterAreaId() const
{
    return myRouterAreaId;
}

inline void TL1_TrLinkParameters::SetRouterAreaId(uint32* theRouterAreaId)
{
    myRouterAreaId = theRouterAreaId;
}

//--------------------------------------------------------------------------------
uint32* TL1_TrLinkParameters::GetResourceClass() const
{
    return myResourceClass;
}

void TL1_TrLinkParameters::SetResourceClass(uint32* theResourceClass)
{
    myResourceClass = theResourceClass;
}

//--------------------------------------------------------------------------------
CT_TL1_ModuleAddr* 
TL1_TrLinkParameters::GetModuleAddr( ) const
{
    return myModuleAddr;
}

void 
TL1_TrLinkParameters::SetModuleAddr( CT_TL1_ModuleAddr* theModuleAddr )
{
    myModuleAddr = theModuleAddr;
}

//--------------------------------------------------------------------------------
CT_TL1_Port* 
TL1_TrLinkParameters::GetPortId() const
{
    return myPortId;
}

void 
TL1_TrLinkParameters::SetPortId( CT_TL1_Port* thePortId )
{
    myPortId = thePortId;
}

//--------------------------------------------------------------------------------
CT_FacilitySubType* 
TL1_TrLinkParameters::GetFacSubType() const
{
    return myFacSubType;
}

void 
TL1_TrLinkParameters::SetFacSubType( CT_FacilitySubType* theFacSubType)
{
    myFacSubType = theFacSubType;
}

//--------------------------------------------------------------------------------
CT_Adaptation* 
TL1_TrLinkParameters::GetAdaptation() const
{
    return myAdaptation;
}

void 
TL1_TrLinkParameters::SetAdaptation( CT_Adaptation* theAdaptation )
{
    myAdaptation = theAdaptation;
}

//--------------------------------------------------------------------------------
uint16* 
TL1_TrLinkParameters::GetPmd( ) const
{
    return myPmd;
}

void    
TL1_TrLinkParameters::SetPmd( uint16* thePmd )
{
    myPmd = thePmd;
}

//--------------------------------------------------------------------------------
uint16* 
TL1_TrLinkParameters::GetOsnr( ) const
{
    return myOsnr;
}

void    
TL1_TrLinkParameters::SetOsnr( uint16* theOsnr )
{
    myOsnr = theOsnr;
}

//--------------------------------------------------------------------------------
uint32* 
TL1_TrLinkParameters::GetIfIndex() const
{
    return myIfIndex;
}

void 
TL1_TrLinkParameters::SetIfIndex(uint32* theIfIndex)
{
    myIfIndex = theIfIndex;
}

//--------------------------------------------------------------------------------
inline int*                      
TL1_TrLinkParameters::GetPdl( ) const
{
    return myPdl;
}

inline void                         
TL1_TrLinkParameters::SetPdl( int* thePdl )
{
    myPdl = thePdl;
}

//--------------------------------------------------------------------------------
inline CT_TL1_LinkAddr*                      
TL1_TrLinkParameters::GetNearEndParentTL( ) const
{
    return myNearEndParentTL;
}

inline void                         
TL1_TrLinkParameters::SetNearEndParentTL( CT_TL1_LinkAddr* theNearEndParentTL )
{
    myNearEndParentTL = theNearEndParentTL;
}

//--------------------------------------------------------------------------------
CT_SM_PST* 
TL1_TrLinkParameters::GetPrimaryState() const
{
    return myPrimaryState;
}

void 
TL1_TrLinkParameters::SetPrimaryState(CT_SM_PST* thePrimaryState)
{
    myPrimaryState = thePrimaryState;
}

//--------------------------------------------------------------------------------
CT_SM_SST* 
TL1_TrLinkParameters::GetSecondaryState() const
{
    return mySecondaryState;
}

void 
TL1_TrLinkParameters::SetSecondaryState(CT_SM_SST* theSecondaryState)
{
    mySecondaryState = theSecondaryState;
}

//--------------------------------------------------------------------------------
class TL1_BLinkParameters  
{
public:

    TL1_BLinkParameters();
    TL1_BLinkParameters(const TL1_BLinkParameters& theInst );
    virtual ~TL1_BLinkParameters();

    TL1_BLinkParameters& operator=( const TL1_BLinkParameters& theInst );
    bool operator==( const TL1_BLinkParameters& theInst ) const;

    inline LT_Handle* GetHandle( ) const;
    inline void SetHandle( LT_Handle* theHandle );

    inline LT_Ctag GetCtag( ) const;
    inline void SetCtag( LT_Ctag theCtag );

    inline string* GetBLname() const;
    inline void SetBLname(string* theBLname);

    inline CT_BLType* GetBLinkType() const;
    inline void SetBLinkType(CT_BLType* theBLname);

    inline uint32* GetCost() const;
    inline void SetCost(uint32* theCost);

    inline CT_ControlPlane_Addr* GetNeighborIfIndex() const;
    inline void SetNeighborIfIndex(CT_ControlPlane_Addr* theNeighborIfIndex);

    inline CT_TL_ROUTING* GetRouting() const;
    inline void SetRouting(CT_TL_ROUTING* theRouting);

    inline CT_ControlPlane_Srlg* GetSrlg() const;
    inline void SetSrlg(CT_ControlPlane_Srlg* theSrlg);

    inline CT_LatencyMode* GetLatencyMode( ) const;
    inline void SetLatencyMode( CT_LatencyMode* theLatencyMode );

    inline uint32* GetLatency() const;
    inline void SetLatency(uint32* theLatency);

    inline uint32* GetResourceClass() const;
    inline void SetResourceClass(uint32* theResourceClass);

    inline CT_SM_PST* GetPrimaryState() const;
    inline void SetPrimaryState(CT_SM_PST* thePrimaryState);

    inline set< CT_TL1_LinkAddr > GetAddTLinkList() const;
    inline void SetAddTLinkList(set< CT_TL1_LinkAddr >& theAddTLList);

    inline set< CT_TL1_LinkAddr > GetDelTLinkList() const;
    inline void SetDelTLinkList(set< CT_TL1_LinkAddr >& theDelTLList);

private:

    LT_Handle*                 myHandle;
    LT_Ctag                    myCtag;
    string*                    myBLname;
    CT_BLType*                 myBLType;
    uint32*                    myCost;
    CT_ControlPlane_Addr*      myNeighborIfIndex;
    CT_TL_ROUTING*             myRouting;
    CT_ControlPlane_Srlg*      mySrlg;
    CT_LatencyMode*            myLatencyMode;
    uint32*                    myLatency;
    uint32*                    myResourceClass;
    CT_SM_PST*                 myPrimaryState;
    set< CT_TL1_LinkAddr >     myAddTLList;
    set< CT_TL1_LinkAddr >     myDelTLList;
};

//--------------------------------------------------------------------------------
inline LT_Handle* TL1_BLinkParameters::GetHandle( ) const
{
    return myHandle;
}

inline void TL1_BLinkParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag TL1_BLinkParameters::GetCtag( ) const
{
    return myCtag;
}

inline void TL1_BLinkParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
} 

//---------------------------------------------------------------------------
inline string* TL1_BLinkParameters::GetBLname() const
{
    return myBLname;
}
inline void TL1_BLinkParameters::SetBLname(string* theBLname)
{
    myBLname = theBLname;
}

//---------------------------------------------------------------------------
inline CT_BLType* TL1_BLinkParameters::GetBLinkType() const
{
    return myBLType;
}
inline void TL1_BLinkParameters::SetBLinkType(CT_BLType* theBLType)
{
    myBLType = theBLType;
}  

//---------------------------------------------------------------------------
inline uint32* TL1_BLinkParameters::GetCost() const
{
    return myCost;
}
inline void TL1_BLinkParameters::SetCost(uint32* theCost)
{
    myCost = theCost;
} 

//---------------------------------------------------------------------------
inline CT_ControlPlane_Addr* TL1_BLinkParameters::GetNeighborIfIndex() const
{
    return myNeighborIfIndex;
}
inline void TL1_BLinkParameters::SetNeighborIfIndex(CT_ControlPlane_Addr* theNeighborIfIndex)
{
    myNeighborIfIndex = theNeighborIfIndex;
}

//---------------------------------------------------------------------------
inline CT_TL_ROUTING* TL1_BLinkParameters::GetRouting() const
{
    return myRouting;
}
inline void TL1_BLinkParameters::SetRouting(CT_TL_ROUTING* theRouting)
{
    myRouting = theRouting;
}

//---------------------------------------------------------------------------
inline CT_ControlPlane_Srlg* TL1_BLinkParameters::GetSrlg() const
{
    return mySrlg;
}
inline void TL1_BLinkParameters::SetSrlg(CT_ControlPlane_Srlg* theSrlg)
{
    mySrlg = theSrlg;
}

//---------------------------------------------------------------------------
inline CT_LatencyMode* TL1_BLinkParameters::GetLatencyMode( ) const
{
    return myLatencyMode;
}
inline void TL1_BLinkParameters::SetLatencyMode( CT_LatencyMode* theLatencyMode )
{
    myLatencyMode = theLatencyMode;
}

//---------------------------------------------------------------------------
inline uint32* TL1_BLinkParameters::GetLatency() const
{
    return myLatency;
}
inline void TL1_BLinkParameters::SetLatency(uint32* theLatency)
{
    myLatency = theLatency;
} 

//---------------------------------------------------------------------------
inline uint32* TL1_BLinkParameters::GetResourceClass() const
{
    return myResourceClass;
}
inline void TL1_BLinkParameters::SetResourceClass(uint32* theResourceClass)
{
    myResourceClass = theResourceClass;
}

//---------------------------------------------------------------------------
inline CT_SM_PST* TL1_BLinkParameters::GetPrimaryState() const
{
    return myPrimaryState;
}
inline void TL1_BLinkParameters::SetPrimaryState(CT_SM_PST* thePrimaryState)
{
    myPrimaryState = thePrimaryState;
} 

//---------------------------------------------------------------------------
inline set< CT_TL1_LinkAddr > TL1_BLinkParameters::GetAddTLinkList() const
{
    return myAddTLList;
}
inline void TL1_BLinkParameters::SetAddTLinkList(set< CT_TL1_LinkAddr >& theAddTLList)
{
    myAddTLList = theAddTLList;
} 

//---------------------------------------------------------------------------
inline set< CT_TL1_LinkAddr > TL1_BLinkParameters::GetDelTLinkList() const
{
    return myDelTLList;
}

inline void TL1_BLinkParameters::SetDelTLinkList(set< CT_TL1_LinkAddr >& theDelTLList)
{
    myDelTLList = theDelTLList;
} 

#endif
