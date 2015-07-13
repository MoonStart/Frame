#ifndef __TL1_LINK_RESPONSE_BLOCK_H__
#define __TL1_LINK_RESPONSE_BLOCK_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive LINK Response Class
TARGET:
AUTHOR:         July 5, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Retrive LINK Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus
 

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>

#ifndef _CT_CONTROLPLANEDEFS_H_
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#endif

#include <CommonTypes/CT_ControlPlane_Convert.h>

class TL1_LinkRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_LinkRspBlk( );

    TL1_LinkRspBlk( 
                    const CT_TL1_LinkAddr&        theAddr,
                    const string&                 theEntityName,
                    const string&                 theTLname,
                    const CT_TLNEADDRT&           theNearEndAddrType,
                    const CT_ControlPlane_TL&     theNearEndAddr,
                    const uint32                  theNearEndMask,
                    const CT_TL1_LinkAddr&        theNearEndParentTL,
                    const uint32                  theCost,
                    const CT_TL_DISCOVERY_TYPE&   theNeighborDiscovery,
                    const uint32                  theIfIndex,
                    const uint32                  theNodeId,
                    const CT_ControlPlane_Addr&   theNeighborIfIndex,
                    const CT_ControlPlane_Addr&   theNeighborNodeId,
                    const CT_TL1_LogicalAddr&     theLinkPfAid,
                    const CT_ControlPlane_Addr&   theNeighborSignalingAddr,
                    const CT_ControlPlane_Addr&   theNeighborSignalingId,
                    const CT_TL_ROUTING&          theRouting,
                    const CT_TL_SIGNALING&        theSignaling,
                    const CT_ControlPlane_Addr&   theRouterAreaId,
                    const CT_ControlPlane_Srlg&   theSrlg,
                    const uint32                  theLatency,
                    const string&                 theCarrierId,
                    const CT_ControlPlane_Addr&   theResourceClass,
                    const CT_TL1_ResourceAddr&    theResource,
                    const CT_IfNumber&            theIfName,
                    const string&                 theTLList,
                    const CT_LatencyMode&         theLatencyMode,
                    const uint16                  thePmd,
                    const uint16                  theOsnr,
                    const int                     theFwmp,
                    const int                     thePdl,
                    const int                     theResidualCD,
                    const int                     theSpmNoise,
                    const int                     theXpmNoise,
                    const CT_RESOURCE_LAYER&      theResourceLayer,
                    const CT_SM_PST&              thePST,
                    const CT_SM_PSTQ&             thePSTQ,
                    const CT_SM_SST&              theSST ); 

    TL1_LinkRspBlk(const TL1_LinkRspBlk& theRspBlk );

    virtual ~TL1_LinkRspBlk();

    TL1_LinkRspBlk& operator=( const TL1_LinkRspBlk& theRspBlk );

    bool operator==( const TL1_LinkRspBlk& theRspBlk ) const;

    bool GetAddr( CT_TL1_LinkAddr& theAddr ) const;
    void SetAddr( const CT_TL1_LinkAddr& theAddr );

    bool GetEntityName( string& theEntityName ) const;
    void SetEntityName( const string& theEntityName );

    bool GetTLname( string& theTLname ) const;
    void SetTLname( const string& theTLname );

    bool GetNearEndAddrType( CT_TLNEADDRT& theNearEndAddrType ) const;
    void SetNearEndAddrType( const CT_TLNEADDRT& theNearEndAddrType );

    bool GetNearEndAddr( CT_ControlPlane_TL& theNearEndAddr ) const;
    void SetNearEndAddr( const CT_ControlPlane_TL& theNearEndAddr );

    bool GetNearEndMask( CT_ControlPlane_Addr& theNearEndMask ) const;
    void SetNearEndMask( const CT_ControlPlane_Addr& theNearEndMask );

    bool GetNearEndParentTL( CT_TL1_LinkAddr& theNearEndParentTL ) const;
    void SetNearEndParentTL( const CT_TL1_LinkAddr& theNearEndParentTL );

    bool GetCost( uint32& theCost) const;
    void SetCost( const int& theCost);

    bool GetNeighborDiscovery( CT_TL_DISCOVERY_TYPE& theNeighborDiscovery ) const;
    void SetNeighborDiscovery( const CT_TL_DISCOVERY_TYPE& theNeighborDiscovery );

    bool GetIfIndex( uint32& theIfIndex ) const;
    void SetIfIndex( const uint32& theIfIndex );

    bool GetNodeId( uint32& theNodeId ) const;
    void SetNodeId( const uint32& theNodeId );

    bool GetNeighborIfIndex( CT_ControlPlane_Addr& theNeighborIfIndex ) const;
    void SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex );

    bool GetNeighborNodeId( CT_ControlPlane_Addr& theNeighborNodeId ) const;
    void SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId );

    bool GetLinkPfAid( CT_TL1_LogicalAddr& theLinkPfAid ) const;
    void SetLinkPfAid( const CT_TL1_LogicalAddr& theLinkPfAid );

    bool GetNeighborSignalingAddr( CT_ControlPlane_Addr& theNeighborSignalingAddr ) const;
    void SetNeighborSignalingAddr( const CT_ControlPlane_Addr& theNeighborSignalingAddr );

    bool GetNeighborSignalingId( CT_ControlPlane_Addr& theNeighborSignalingId ) const;
    void SetNeighborSignalingId( const CT_ControlPlane_Addr& theNeighborSignalingId );

    bool GetRouting( CT_TL_ROUTING& theRouting ) const;
    void SetRouting( const CT_TL_ROUTING& theRouting );

    bool GetSignaling( CT_TL_SIGNALING& theSignaling ) const;
    void SetSignaling( const CT_TL_SIGNALING& theSignaling );

    bool GetRouterAreaId( CT_ControlPlane_Addr& theRouterAreaId ) const;
    void SetRouterAreaId( const CT_ControlPlane_Addr& theRouterAreaId );

    bool GetSrlg( CT_ControlPlane_Srlg& theSrlg ) const;
    void SetSrlg( const CT_ControlPlane_Srlg& theSrlg );

    bool GetLatency( uint32& theLatency ) const;
    void SetLatency( const uint32& theLatency );

    bool GetLatencyMode( CT_LatencyMode& theLatencyMode ) const;
    void SetLatencyMode( const CT_LatencyMode& theLatencyMode );

    bool GetCarrierId( string& theCarrierId ) const;
    void SetCarrierId( const string& theCarrierId );

    bool GetResourceClass( CT_ControlPlane_Addr& theResourceClass ) const;
    void SetResourceClass( const CT_ControlPlane_Addr& theResourceClass );

    bool GetResource( CT_TL1_ResourceAddr& theResource ) const;
    void SetResource( const CT_TL1_ResourceAddr& theResource );

    bool GetIfName( CT_IfNumber& theIfName ) const;
    void SetIfName( const CT_IfNumber& theIfName );

    bool GetTLList( string& theTLList ) const;
    void SetTLList( const string& theTLList );

    bool GetPmd( uint16& thePmd ) const;
    void SetPmd( const uint16& thePmd );

    bool GetOsnr( uint16& theOsnr ) const;
    void SetOsnr( const uint16& theOsnr );

    bool GetFwmp( int& theFwmp ) const;
    void SetFwmp( const int& theFwmp );

    bool GetPdl( int& thePdl ) const;
    void SetPdl( const int& thePdl );
	
    bool GetResidualCD( int& theResidualCD ) const;
    void SetResidualCD( const int& theResidualCD );
	
    bool GetSpmNoise( int& theSpmNoise ) const;
    void SetSpmNoise( const int& theSpmNoise );
	
    bool GetXpmNoise( int& theXpmNoise ) const;
    void SetXpmNoise( const int& theXpmNoise );

    bool GetResourceLayer( CT_RESOURCE_LAYER& theResourceLayer ) const;
    void SetResourceLayer( const CT_RESOURCE_LAYER& theResourceLayer );

    bool GetPST( CT_SM_PST& thePST ) const;
    void SetPST( const CT_SM_PST& thePST );

    bool GetPSTQ( CT_SM_PSTQ& thePST ) const;
    void SetPSTQ( const CT_SM_PSTQ& thePST );

    bool GetSST( CT_SM_SST& theSST ) const;
    void SetSST( const CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_Addr = 0,
        INDEX_EntityName,
        INDEX_TLname,
        INDEX_NearEndAddrType,
        INDEX_NearEndAddr,
        INDEX_NearEndMask,
        INDEX_NearEndParentTL,
        INDEX_Cost,
        INDEX_NeighborDiscovery,
        INDEX_IfIndex,
        INDEX_NodeId,
        INDEX_NeighborIfIndex,
        INDEX_NeighborNodeId,
        INDEX_LinkPfAid,
        INDEX_NeighborSignalingAddr,
        INDEX_NeighborSignalingId,
        INDEX_Routing,
        INDEX_Signaling,
        INDEX_RouterAreaId,
        INDEX_Srlg,
        INDEX_Latency,
        INDEX_CarrierId,
        INDEX_ResourceClass,
        INDEX_Resource,
        INDEX_IfName,
        INDEX_TLList,
        INDEX_LatencyMode,
        INDEX_Pmd,
        INDEX_Osnr,
        INDEX_Fwmp,
        INDEX_Pdl,
        INDEX_ResidualCD,
        INDEX_SpmNoise,
        INDEX_XpmNoise,
        INDEX_ResourceLayer,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>            myBitSet;

    CT_TL1_LinkAddr         myAddr;
    string                  myEntityName;
    string                  myTLname;
    CT_TLNEADDRT            myNearEndAddrType;
    CT_ControlPlane_TL      myNearEndAddr;
    CT_ControlPlane_Addr    myNearEndMask;
    CT_TL1_LinkAddr         myNearEndParentTL;
    uint32                  myCost;
    CT_TL_DISCOVERY_TYPE    myNeighborDiscovery;
    uint32                  myIfIndex;
    uint32                  myNodeId;
    CT_ControlPlane_Addr    myNeighborIfIndex;
    CT_ControlPlane_Addr    myNeighborNodeId;
    CT_TL1_LogicalAddr      myLinkPfAid;
    CT_ControlPlane_Addr    myNeighborSignalingAddr;
    CT_ControlPlane_Addr    myNeighborSignalingId;
    CT_TL_ROUTING           myRouting;
    CT_TL_SIGNALING         mySignaling;
    CT_ControlPlane_Addr    myRouterAreaId;
    CT_ControlPlane_Srlg    mySrlg;
    uint32                  myLatency;
    string                  myCarrierId;
    CT_ControlPlane_Addr    myResourceClass;
    CT_TL1_ResourceAddr     myResource;
    CT_IfNumber             myIfName;
    string                  myTLList;
    CT_LatencyMode          myLatencyMode;
    uint16                  myPmd;
    uint16                  myOsnr;
    int                     myFwmp;
    int                     myPdl;
    int                     myResidualCD;
    int                     mySpmNoise;
    int                     myXpmNoise;
    CT_RESOURCE_LAYER       myResourceLayer;
    CT_SM_PST               myPST;
    CT_SM_PSTQ              myPSTQ;
    CT_SM_SST               mySST;
};

typedef TL1_Rtv_Response< TL1_LinkRspBlk > TL1_LinkResponse;


//
// TNALNKMAP
//


class TL1_TnaLnkMapRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_TnaLnkMapRspBlk( );

    TL1_TnaLnkMapRspBlk( const uint32*  theTnaValue,
                         const CT_Call_Tna_Types*  theTnaType,
                         const CT_TL1_LinkAddr*   theLinkAddr);

    TL1_TnaLnkMapRspBlk(const TL1_TnaLnkMapRspBlk& theRspBlk );

    virtual ~TL1_TnaLnkMapRspBlk();

    TL1_TnaLnkMapRspBlk& operator=( const TL1_TnaLnkMapRspBlk& theRspBlk );

    bool operator==( const TL1_TnaLnkMapRspBlk& theRspBlk ) const;


    bool GetTnaValue( uint32& theTnaValue ) const;
    void SetTnaValue( uint32& theTnaValue );
    bool GetTnaType( CT_Call_Tna_Types& theTnaType ) const;
    void SetTnaType( CT_Call_Tna_Types& theTnaType );
    bool GetLinkAddr( CT_TL1_LinkAddr& theAddr ) const;
    void SetLinkAddr( CT_TL1_LinkAddr& theAddr );

private:
    enum 
    {
        INDEX_TnaValue = 0,
        INDEX_TnaType,
        INDEX_LinkAddr,
        INDEX_END
    };

    vector<bool>                 myBitSet;
    uint32                       myTnaValue;
    CT_Call_Tna_Types            myTnaType;
    CT_TL1_LinkAddr              myLinkAddr;
};

typedef TL1_Rtv_Response< TL1_TnaLnkMapRspBlk > TL1_TnaLnkMapResponse;

class TL1_LinkProfileRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_LinkProfileRspBlk( );

    TL1_LinkProfileRspBlk( CT_TL1_LogicalAddr  theAddr,
                           string              theEntityName,
                           string              theProfileName,
                           CT_LINKPF_NAT_TYPE  theNetworkAddressType,
                           uint16              theHelloInterval,
                           uint16              theRouterDeadInterval,
                           uint16              theRetransmissionInternal,
                           CT_TL1_LogicalAddr  theServiceLevelProfile,
                           CT_TL1_LogicalAddr  theServiceLevelPolicy,
                           CT_GMPLS_MODE       theGMPLSMode,
                           bool                theARUSupport,
                           CT_G709_MODE        theG709Mode); 

    TL1_LinkProfileRspBlk(const TL1_LinkProfileRspBlk& theRspBlk );

    virtual ~TL1_LinkProfileRspBlk();

    TL1_LinkProfileRspBlk& operator=( const TL1_LinkProfileRspBlk& theRspBlk );

    bool operator==( const TL1_LinkProfileRspBlk& theRspBlk ) const;

    bool GetAddr( CT_TL1_LogicalAddr& theAddr ) const;
    void SetAddr( const CT_TL1_LogicalAddr& theAddr );

    bool GetEntityName( string& theEntityName ) const;
    void SetEntityName( const string& theEntityName );

    bool GetProfileName( string& theProfileName ) const;
    void SetProfileName( const string& theProfileName );

    bool GetNetworkAddressType( CT_LINKPF_NAT_TYPE& theNetworkAddressType ) const;
    void SetNetworkAddressType( const CT_LINKPF_NAT_TYPE& theNetworkAddressType );

    bool GetHelloInterval( uint16& theHelloInterval ) const;
    void SetHelloInterval( const uint16& theHelloInterval );

    bool GetRouterDeadInterval( uint16& theRouterDeadInterval ) const;
    void SetRouterDeadInterval( const uint16& theRouterDeadInterval );

    bool GetRetransmissionInternal( uint16& theRetransmissionInternal ) const;
    void SetRetransmissionInternal( const uint16& theRetransmissionInternal );

    bool GetServiceLevelProfile( CT_TL1_LogicalAddr& theServiceLevelProfile ) const;
    void SetServiceLevelProfile( const CT_TL1_LogicalAddr& theServiceLevelProfile );

    bool GetServiceLevelPolicy( CT_TL1_LogicalAddr& theServiceLevelPolicy ) const;
    void SetServiceLevelPolicy( const CT_TL1_LogicalAddr& theServiceLevelPolicy );

    bool GetGMPLSMode( CT_GMPLS_MODE& theGMPLSMode ) const;
    void SetGMPLSMode( const CT_GMPLS_MODE& theGMPLSMode );

    bool GetARUSupport( bool& theARUSupport ) const;
    void SetARUSupport( const bool theARUSupport );

    bool GetG709Mode( CT_G709_MODE& theG709Mode ) const;
    void SetG709Mode( const CT_G709_MODE& theG709Mode );

private:
    enum 
    {
        INDEX_Addr = 0,
        INDEX_EntityName,
        INDEX_ProfileName,
        INDEX_NetworkAddressType,
        INDEX_HelloInterval,
        INDEX_RouterDeadInterval,
        INDEX_RetransmissionInternal,
        INDEX_ServiceLevelProfile,
        INDEX_ServiceLevelPolicy,
        INDEX_GMPLSMode,
        INDEX_ARUSupport,
        INDEX_G709Mode,
        INDEX_END
    };

    vector<bool>        myBitSet;

    CT_TL1_LogicalAddr  myAddr;
    string              myEntityName;
    string              myProfileName;
    CT_LINKPF_NAT_TYPE  myNetworkAddressType;
    uint16              myHelloInterval;
    uint16              myRouterDeadInterval;
    uint16              myRetransmissionInternal;
    CT_TL1_LogicalAddr  myServiceLevelProfile;
    CT_TL1_LogicalAddr  myServiceLevelPolicy;
    CT_GMPLS_MODE       myGMPLSMode;
    bool                myARUSupport;
    CT_G709_MODE        myG709Mode;
};

typedef TL1_Rtv_Response< TL1_LinkProfileRspBlk > TL1_LinkProfilefResponse;


class TL1_TrLinkRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_TrLinkRspBlk( );

    TL1_TrLinkRspBlk( CT_TL1_LinkAddr       theAddr,
                      string                theEntityName,
                      string                theTrlName,
                      uint32                theCost,
                      uint32                theIfIndex,
                      uint32                theNodeId,
                      CT_ControlPlane_Addr  theNeighborIfIndex,
                      CT_ControlPlane_Addr  theNeighborNodeId,
                      CT_TL1_LogicalAddr    theLinkPfAid,
                      CT_ControlPlane_Addr  theNeighborSignalingAddr,
                      CT_ControlPlane_Addr  theNeighborSignalingId,
                      CT_ControlPlane_Addr  theRouterAreaId,
                      CT_ControlPlane_Addr  theResourceClass,
                      CT_TL1_ModuleAddr     theModuleAddr,
                      CT_TL1_Port           thePortNum,
                      CT_FacilitySubType    theFacSubType,
                      CT_Adaptation         theAdapt,
                      uint16                thePmd,
                      uint16                theOsnr,
                      int                   thePdl,
                      CT_TL1_LinkAddr       theParentTL,
                      CT_SM_PST             thePST,
                      CT_SM_PSTQ            thePSTQ,
                      CT_SM_SST             theSST ); 

    TL1_TrLinkRspBlk(const TL1_TrLinkRspBlk& );

    virtual ~TL1_TrLinkRspBlk();

    TL1_TrLinkRspBlk& operator=( const TL1_TrLinkRspBlk& theRspBlk );

    bool operator==( const TL1_TrLinkRspBlk& theRspBlk ) const;

    bool GetAddr( CT_TL1_LinkAddr& theAddr ) const;
    void SetAddr( const CT_TL1_LinkAddr& theAddr );

    bool GetEntityName( string& theEntityName ) const;
    void SetEntityName( const string& theEntityName );

    bool GetTrlName( string& theTrlName ) const;
    void SetTrlName( const string& theTrlName );

    bool GetCost( uint32& theCost) const;
    void SetCost( const int& theCost);

    bool GetIfIndex( uint32& theIfIndex ) const;
    void SetIfIndex( const uint32& theIfIndex );

    bool GetNodeId( uint32& theNodeId ) const;
    void SetNodeId( const uint32& theNodeId );

    bool GetNeighborIfIndex( CT_ControlPlane_Addr& theNeighborIfIndex ) const;
    void SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex );

    bool GetNeighborNodeId( CT_ControlPlane_Addr& theNeighborNodeId ) const;
    void SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId );

    bool GetLinkPfAid( CT_TL1_LogicalAddr& theLinkPfAid ) const;
    void SetLinkPfAid( const CT_TL1_LogicalAddr& theLinkPfAid );

    bool GetNeighborSignalingAddr( CT_ControlPlane_Addr& theNeighborSignalingAddr ) const;
    void SetNeighborSignalingAddr( const CT_ControlPlane_Addr& theNeighborSignalingAddr );

    bool GetNeighborSignalingId( CT_ControlPlane_Addr& theNeighborSignalingId ) const;
    void SetNeighborSignalingId( const CT_ControlPlane_Addr& theNeighborSignalingId );

    bool GetRouterAreaId( CT_ControlPlane_Addr& theRouterAreaId ) const;
    void SetRouterAreaId( const CT_ControlPlane_Addr& theRouterAreaId );

    bool GetResourceClass( CT_ControlPlane_Addr& theResourceClass ) const;
    void SetResourceClass( const CT_ControlPlane_Addr& theResourceClass );

    bool GetModuleAddr( CT_TL1_ModuleAddr& theModuleAddr ) const;
    void SetModuleAddr( const CT_TL1_ModuleAddr& theModuleAddr );

    bool GetPortNum( CT_TL1_Port& thePortNum ) const;
    void SetPortNum( const CT_TL1_Port& thePortNum );

    bool GetFacSubType( CT_FacilitySubType& theFacSubType ) const;
    void SetFacSubType( const CT_FacilitySubType& theFacSubType );

    bool GetAdaptation( CT_Adaptation& theAdapt ) const;
    void SetAdaptation( const CT_Adaptation& theAdapt );

    bool GetPmd( uint16& thePmd ) const;
    void SetPmd( const uint16& thePmd );

    bool GetOsnr( uint16& theOsnr ) const;
    void SetOsnr( const uint16& theOsnr );

    bool GetPdl( int& theOsnr ) const;
    void SetPdl( const int& theOsnr );

    bool GetParentTL( CT_TL1_LinkAddr& theParentTL ) const;
    void SetParentTL( const CT_TL1_LinkAddr& theParentTL );

    bool GetPST( CT_SM_PST& thePST ) const;
    void SetPST( const CT_SM_PST& thePST );

    bool GetPSTQ( CT_SM_PSTQ& thePST ) const;
    void SetPSTQ( const CT_SM_PSTQ& thePST );

    bool GetSST( CT_SM_SST& theSST ) const;
    void SetSST( const CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_Addr = 0,
        INDEX_EntityName,
        INDEX_TrlName,
        INDEX_Cost,
        INDEX_IfIndex,
        INDEX_NodeId,
        INDEX_NeighborIfIndex,
        INDEX_NeighborNodeId,
        INDEX_LinkPfAid,
        INDEX_NeighborSignalingAddr,
        INDEX_NeighborSignalingId,
        INDEX_RouterAreaId,
        INDEX_ResourceClass,
        INDEX_ModuleAddr,
        INDEX_PortNum,
        INDEX_FacSubType,
        INDEX_Adaptation,
        INDEX_IfName,
        INDEX_Pmd,
        INDEX_Osnr,
        INDEX_Pdl,
        INDEX_ParentTL,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>            myBitSet;

    CT_TL1_LinkAddr         myAddr;
    string                  myEntityName;
    string                  myTrlName;
    uint32                  myCost;
    uint32                  myIfIndex;
    uint32                  myNodeId;
    CT_ControlPlane_Addr    myNeighborIfIndex;
    CT_ControlPlane_Addr    myNeighborNodeId;
    CT_TL1_LogicalAddr      myLinkPfAid;
    CT_ControlPlane_Addr    myNeighborSignalingAddr;
    CT_ControlPlane_Addr    myNeighborSignalingId;
    CT_ControlPlane_Addr    myRouterAreaId;
    CT_ControlPlane_Addr    myResourceClass;
    CT_TL1_ModuleAddr       myModuleAddr;
    CT_TL1_Port             myPortNum;
    CT_FacilitySubType      myFacSubType;
    CT_Adaptation           myAdapt;
    uint16                  myPmd;
    uint16                  myOsnr;
    int                     myPdl;
    CT_TL1_LinkAddr         myParentTL;
    CT_SM_PST               myPST;
    CT_SM_PSTQ              myPSTQ;
    CT_SM_SST               mySST;
};

typedef TL1_Rtv_Response< TL1_TrLinkRspBlk > TL1_TrLinkResponse;

class TL1_LadjLinkRspBlk : public TL1_GeneralRspBlk
{
public:
        TL1_LadjLinkRspBlk( );

        TL1_LadjLinkRspBlk( CT_TL1_LinkAddr     theAddr,
                            CT_LadState         theLadState,
                            string              theTransmitTTI,
                            string              theReceiveTTI);

        TL1_LadjLinkRspBlk(const TL1_LadjLinkRspBlk& theRspBlk );

        virtual ~TL1_LadjLinkRspBlk();

        TL1_LadjLinkRspBlk& operator=( const TL1_LadjLinkRspBlk& theRspBlk );

        bool operator==( const TL1_LadjLinkRspBlk& theRspBlk ) const;

        bool GetAddr( CT_TL1_LinkAddr& theAddr ) const;
        void SetAddr( const CT_TL1_LinkAddr& theAddr);

        bool GetLadState( CT_LadState& theLadState ) const;
        void SetLadState( const CT_LadState& theLadState );

        bool GetTransmitTTI( string& theTransmitTTI ) const;
        void SetTransmitTTI( const string& theTransmitTTI);

        bool GetReceiveTTI( string& theReceiveTTI ) const;
        void SetReceiveTTI( const string& theReceiveTTI );

private:
        enum
        {
            INDEX_Addr = 0,
            INDEX_LadState,
            INDEX_TransmitTTI,
            INDEX_ReceiveTTI,
            INDEX_END
        };

        vector<bool>            myBitSet;

        CT_TL1_LinkAddr         myAddr;
        CT_LadState             myLadState;
        string                  myTransmitTTI;
        string                  myReceiveTTI;
};

typedef TL1_Rtv_Response<TL1_LadjLinkRspBlk> TL1_LadjLinkResponse;

class TL1_TceLinkRspBlk : public TL1_GeneralRspBlk
{
public:
        TL1_TceLinkRspBlk( );

        TL1_TceLinkRspBlk( CT_TL1_LinkAddr       theAddr,
                           CT_LcpState           theLcpState,
                           CT_LcpState           theMpState,
                           string                theMgtDomain,
                           string                theMgtNodeName,
                           string                theMgtPortName,
                           CT_LcpState           theCpNameState,
                           CT_ControlPlane_Addr  theRoutingAreaId,
                           CT_LcpState           theCpConfigState,
                           CT_ControlPlane_Addr  theNeighborNodeId,
                           CT_ControlPlane_Addr  theNeighborIfIndex,
                           CT_GMPLS_MODE         theSigProtocol,
                           CT_GMPLS_MODE         theRoutingProtocol,
                           CT_ControlPlane_Addr  theNeighborSigAddr,
                           CT_ControlPlane_Addr  theNeighborSigId); 

        TL1_TceLinkRspBlk(const TL1_TceLinkRspBlk& theRspBlk);

        virtual ~TL1_TceLinkRspBlk();

        TL1_TceLinkRspBlk& operator=( const TL1_TceLinkRspBlk& theRspBlk );

        bool operator==( const TL1_TceLinkRspBlk& theRspBlk ) const;

        bool GetAddr( CT_TL1_LinkAddr& theAddr ) const;
        void SetAddr( const CT_TL1_LinkAddr& theAddr );

        bool GetLcpState( CT_LcpState& theLcpState ) const;
        void SetLcpState( const CT_LcpState& theLcpState );

        bool GetMpState( CT_LcpState& theMpState ) const;
        void SetMpState( const CT_LcpState& theMpState );

        bool GetMgtDomain( string& theMgtDomain ) const;
        void SetMgtDomain( const string& theMgtDomain );

        bool GetMgtNodeName( string& theMgtNodeName ) const;
        void SetMgtNodeName( const string& theMgtNodeName );

        bool GetMgtPortName( string& theMgtPortName ) const;
        void SetMgtPortName( const string& theMgtPortName );

        bool GetCpNameState( CT_LcpState& theCpNameState ) const;
        void SetCpNameState( const CT_LcpState& theCpNameState );

        bool GetRoutingAreaId( CT_ControlPlane_Addr& theRoutingAreaId ) const;
        void SetRoutingAreaId( const CT_ControlPlane_Addr& theRoutingAreaId );

        bool GetCpConfigState( CT_LcpState& theCpConfigState ) const;
        void SetCpConfigState( const CT_LcpState& theCpConfigState );

        bool GetNeighborNodeId( CT_ControlPlane_Addr& theNeighborNodeId ) const;
        void SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId );

        bool GetNeighborIfIndex( CT_ControlPlane_Addr& theNeighborIfIndex ) const;
        void SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex );

        bool GetSigProtocol( CT_GMPLS_MODE& theSigProtocol ) const;
        void SetSigProtocol( const CT_GMPLS_MODE& theSigProtocol );

        bool GetRoutingProtocol( CT_GMPLS_MODE& theRoutingProtocol ) const;
        void SetRoutingProtocol( const CT_GMPLS_MODE& theRoutingProtocol );

        bool GetNeighborSigAddr( CT_ControlPlane_Addr& theNeighborSigAddr ) const;
        void SetNeighborSigAddr( const CT_ControlPlane_Addr& theNeighborSigAddr );

        bool GetNeighborSigId( CT_ControlPlane_Addr& theNeighborSigId ) const;
        void SetNeighborSigId( const CT_ControlPlane_Addr& theNeighborSigId );

private:
        enum
        {
            INDEX_Addr = 0,
            INDEX_LcpState,
            INDEX_MpState,
            INDEX_MgtDomain,
            INDEX_MgtNodeName,
            INDEX_MgtPortName,
            INDEX_CpNameState,
            INDEX_RoutingAreaId,
            INDEX_CpConfigState,
            INDEX_NeighborNodeId,
            INDEX_NeighborIfIndex,
            INDEX_SigProtocol,
            INDEX_RoutingProtocol,
            INDEX_NeighborSigAddr,
            INDEX_NeighborSigId,
            INDEX_END
        };

        vector<bool>            myBitSet;

        CT_TL1_LinkAddr         myAddr;
        CT_LcpState             myLcpState;
        CT_LcpState             myMpState;
        string                  myMgtDomain;
        string                  myMgtNodeName;
        string                  myMgtPortName;
        CT_LcpState             myCpNameState;
        CT_ControlPlane_Addr    myRoutingAreaId;
        CT_LcpState             myCpConfigState;
        CT_ControlPlane_Addr    myNeighborNodeId;
        CT_ControlPlane_Addr    myNeighborIfIndex;
        CT_GMPLS_MODE           mySigProtocol;
        CT_GMPLS_MODE           myRoutingProtocol;
        CT_ControlPlane_Addr    myNeighborSigAddr;
        CT_ControlPlane_Addr    myNeighborSigId;

};

typedef TL1_Rtv_Response<TL1_TceLinkRspBlk> TL1_TceLinkResponse;

class TL1_BLinkRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_BLinkRspBlk( );

    TL1_BLinkRspBlk( 
                    const CT_TL1_LinkAddr&         theBLAddr,
                    const string&                  theBLName,
                    const CT_BLType&               theBLType,
                    const uint32                   theCost,
                    const uint32&                  theIfIndex,
                    const CT_ControlPlane_Addr&    theNeighborIfIndex,
                    const CT_TL_ROUTING&           theRouting,
                    const CT_ControlPlane_Srlg&    theSrlg,
                    const CT_LatencyMode&          theLatencyMode,
                    const uint32                   theLatency,
                    const CT_ControlPlane_Addr&    theResourceClass,
                    const CT_SM_PST&               thePST,
                    const CT_SM_PSTQ&              thePSTQ,
                    const CT_SM_SST&               theSST,
                    const set< CT_TL1_LinkAddr >&  theTLList,
                    const CT_TL1_LinkAddr&         theTLAddr,
                    const CT_ControlPlane_Addr&    theNeighborNodeId,
                    const CT_ControlPlane_Addr&    theNeighborSignalingAddr,
                    const CT_ControlPlane_Addr&    theNeighborSignalingId,
                    const CT_TL_DISCOVERY_TYPE&    theNeighborDiscovery,
                    const CT_TL1_LogicalAddr&      theLinkPfAid,
                    const CT_ControlPlane_Addr&    theRouterAreaId );

    TL1_BLinkRspBlk(const TL1_BLinkRspBlk& theRspBlk );

    virtual ~TL1_BLinkRspBlk();

    TL1_BLinkRspBlk& operator=( const TL1_BLinkRspBlk& theRspBlk );

    bool operator==( const TL1_BLinkRspBlk& theRspBlk ) const;

    bool GetBLinkAddr( CT_TL1_LinkAddr& theBLAddr ) const;
    void SetBLinkAddr( const CT_TL1_LinkAddr& theBLAddr );

    bool GetBLinkName( string& theBLName ) const;
    void SetBLinkName( const string& theBLName );

    bool GetBLinkType( CT_BLType& theBLType ) const;
    void SetBLinkType( const CT_BLType& theBLType );

    bool GetCost( uint32& theCost) const;
    void SetCost( const uint32& theCost);

    bool GetIfIndex( uint32& theBLIfIndex ) const;
    void SetIfIndex( const uint32& theBLIfIndex );

    bool GetNeighborIfIndex( CT_ControlPlane_Addr& theNeighborIfIndex ) const;
    void SetNeighborIfIndex( const CT_ControlPlane_Addr& theNeighborIfIndex );

    bool GetRouting( CT_TL_ROUTING& theRouting ) const;
    void SetRouting( const CT_TL_ROUTING& theRouting );

    bool GetSrlg( CT_ControlPlane_Srlg& theSrlg ) const;
    void SetSrlg( const CT_ControlPlane_Srlg& theSrlg );

    bool GetLatencyMode( CT_LatencyMode& theLatencyMode ) const;
    void SetLatencyMode( const CT_LatencyMode& theLatencyMode );

    bool GetLatency( uint32& theLatency ) const;
    void SetLatency( const uint32& theLatency );

    bool GetResourceClass( CT_ControlPlane_Addr& theResourceClass ) const;
    void SetResourceClass( const CT_ControlPlane_Addr& theResourceClass );

    bool GetPST( CT_SM_PST& thePST ) const;
    void SetPST( const CT_SM_PST& thePST );

    bool GetPSTQ( CT_SM_PSTQ& thePST ) const;
    void SetPSTQ( const CT_SM_PSTQ& thePST );

    bool GetSST( CT_SM_SST& theSST ) const;
    void SetSST( const CT_SM_SST& theSST );

    bool GetTLinkList( set< CT_TL1_LinkAddr >& theTLList ) const;
    void SetTLinkList( const set< CT_TL1_LinkAddr >& theTLList );

    bool GetTLinkAddr( CT_TL1_LinkAddr& theTLAddr ) const;
    void SetTLinkAddr( const CT_TL1_LinkAddr& theTLAddr );

    bool GetNeighborNodeId( CT_ControlPlane_Addr& theNeighborNodeId ) const;
    void SetNeighborNodeId( const CT_ControlPlane_Addr& theNeighborNodeId );

    bool GetNeighborSignalingAddr( CT_ControlPlane_Addr& theNeighborSignalingAddr ) const;
    void SetNeighborSignalingAddr( const CT_ControlPlane_Addr& theNeighborSignalingAddr );

    bool GetNeighborSignalingId( CT_ControlPlane_Addr& theNeighborSignalingId ) const;
    void SetNeighborSignalingId( const CT_ControlPlane_Addr& theNeighborSignalingId );

    bool GetNeighborDiscovery( CT_TL_DISCOVERY_TYPE& theNeighborDiscovery ) const;
    void SetNeighborDiscovery( const CT_TL_DISCOVERY_TYPE& theNeighborDiscovery );

    bool GetLinkPfAid( CT_TL1_LogicalAddr& theLinkPfAid ) const;
    void SetLinkPfAid( const CT_TL1_LogicalAddr& theLinkPfAid );

    bool GetRouterAreaId( CT_ControlPlane_Addr& theRouterAreaId ) const;
    void SetRouterAreaId( const CT_ControlPlane_Addr& theRouterAreaId );
	
private:
    enum 
    {
        INDEX_BLAddr = 0,
        INDEX_BLName,
        INDEX_BLType,
        INDEX_Cost,
        INDEX_IfIndex,
        INDEX_NeighborIfIndex,
        INDEX_Routing,
        INDEX_Srlg,
        INDEX_LatencyMode,
        INDEX_Latency,
        INDEX_ResourceClass,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_TLList,
        INDEX_TLAddr,
        INDEX_NeighborNodeId,
        INDEX_NeighborSignalingAddr,
        INDEX_NeighborSignalingId,
        INDEX_NeighborDiscovery,
        INDEX_LinkPfAid,
        INDEX_RouterAreaId,
        INDEX_END
    };

    vector<bool>            myBitSet;

    CT_TL1_LinkAddr         myBLAddr;
    string                  myBLName;
    CT_BLType               myBLType;
    uint32                  myCost;
    uint32                  myIfIndex;
    CT_ControlPlane_Addr    myNeighborIfIndex;
    CT_TL_ROUTING           myRouting;
    CT_ControlPlane_Srlg    mySrlg;
    CT_LatencyMode          myLatencyMode;
    uint32                  myLatency;
    CT_ControlPlane_Addr    myResourceClass;
    CT_SM_PST               myPST;
    CT_SM_PSTQ              myPSTQ;
    CT_SM_SST               mySST;
    set< CT_TL1_LinkAddr >  myTLList;
    CT_TL1_LinkAddr         myTLAddr;
    CT_ControlPlane_Addr    myNeighborNodeId;
    CT_ControlPlane_Addr    myNeighborSignalingAddr;
    CT_ControlPlane_Addr    myNeighborSignalingId;
    CT_TL_DISCOVERY_TYPE    myNeighborDiscovery;
    CT_TL1_LogicalAddr      myLinkPfAid;
    CT_ControlPlane_Addr    myRouterAreaId;
};

typedef TL1_Rtv_Response< TL1_BLinkRspBlk > TL1_BLinkResponse;

#endif  // #ifdef  __cplusplus
#endif  // #ifndef __TL1_LINK_RESPONSE_BLOCK_H__

