/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OSPF Response Class
TARGET:
AUTHOR:         May 31, 2007 - Lee Gernes
DESCRIPTION:    Header file for TL1 Retrive OSPF Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSPFRSPBLK_H_
#define __TL1_OSPFRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_TL1_BASE_H_
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_TL1_CONTROLPLANEADDR_H__
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#ifndef __CT_CONTROLPLANE_DEFINITIONS_H__
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#endif

#ifndef __CT_OSPF_H__
#include <CommonTypes/CT_EON.h>
#endif

#include <vector>

using namespace std;


// OSPF RC
class TL1_OspfRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OspfRspBlk() {}
    
    TL1_OspfRspBlk(const TL1_OspfRspBlk& );

    TL1_OspfRspBlk( const TL1_SmartParameter<string>&            theEntityName,
                   const TL1_SmartParameter<CT_TL1_ControllerAddr>& theOspfAddr,
                   const TL1_SmartParameter<uint32>&             theRouterId,
                   const TL1_SmartParameter<bool>&               theASBRouterFlag,
                   const TL1_SmartParameter<CT_SM_PST>&          thePst,
                   const TL1_SmartParameter<CT_SM_PSTQ>&         thePstq);
                 
    
    virtual ~TL1_OspfRspBlk();

    TL1_OspfRspBlk& operator=( const TL1_OspfRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter<CT_TL1_ControllerAddr>& 
        GetOspfAddr() const
    {
        return itsOspfAddr;
    }

    const TL1_SmartParameter<uint32>& 
        GetRouterId() const
    {
        return itsRouterId;
    }

    const TL1_SmartParameter<bool>& 
        GetASBRouterFlag() const
    {
        return itsASBRouterFlag;
    }

    const TL1_SmartParameter<CT_SM_PST>& 
        GetPst() const
    {
        return itsPst;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>& 
        GetPstq() const
    {
        return itsPstq;
    }

private:

    TL1_SmartParameter<string>             itsEntityName;
    TL1_SmartParameter<CT_TL1_ControllerAddr> itsOspfAddr;
    TL1_SmartParameter<uint32>             itsRouterId;
    TL1_SmartParameter<bool>               itsASBRouterFlag;
    TL1_SmartParameter<CT_SM_PST>          itsPst;
    TL1_SmartParameter<CT_SM_PSTQ>         itsPstq;
};

typedef TL1_Rtv_Response< TL1_OspfRspBlk > TL1_OspfResponse;


// OSPF ADJ
class TL1_OspfAdjRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OspfAdjRspBlk() {}
    
    TL1_OspfAdjRspBlk(const TL1_OspfAdjRspBlk& );

    TL1_OspfAdjRspBlk( const TL1_SmartParameter<string>&         theEntityName,
                   const TL1_SmartParameter<CT_TL1_AdjacencyAddr>& theAdjAddr,
                   const TL1_SmartParameter<CT_TL1_LinkAddr>&    theInterfaceAddr,
                   const TL1_SmartParameter<CT_TL1_AreaAddr>&    theAreaAddr,
                   const TL1_SmartParameter<CT_InterfaceType>&   theInterfaceType,
                   const TL1_SmartParameter<CT_Adj_Status>&		 theAdjStatus,
				   const TL1_SmartParameter<uint32>&             theNghbrId,
                   const TL1_SmartParameter<uint32>&             theIPAddr,
                   const TL1_SmartParameter<CT_SM_PST>&          thePst,
                   const TL1_SmartParameter<CT_SM_PSTQ>&         thePstq,
                   const TL1_SmartParameter<CT_SM_SST>&          theSst);
                 
    
    virtual ~TL1_OspfAdjRspBlk();

    TL1_OspfAdjRspBlk& operator=( const TL1_OspfAdjRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter<CT_TL1_AdjacencyAddr>& 
        GetAdjAddr() const
    {
        return itsAdjAddr;
    }

    const TL1_SmartParameter<CT_TL1_LinkAddr>& 
        GetInterfaceAddr() const
    {
        return itsInterfaceAddr;
    }

    const TL1_SmartParameter<CT_TL1_AreaAddr>& 
        GetAreaAddr() const
    {
        return itsAreaAddr;
    }

    const TL1_SmartParameter<CT_InterfaceType>& 
        GetInterfaceType() const
    {
        return itsInterfaceType;
    }

    const TL1_SmartParameter<CT_Adj_Status>& 
        GetAdjStatus() const
    {
        return itsAdjStatus;
    }

	const TL1_SmartParameter<uint32>& 
        GetNghbrId() const
    {
        return itsNghbrId;
    }

    const TL1_SmartParameter<uint32>& 
        GetIPAddr() const
    {
        return itsIPAddr;
    }

    const TL1_SmartParameter<CT_SM_PST>& 
        GetPst() const
    {
        return itsPst;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>& 
        GetPstq() const
    {
        return itsPstq;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSst() const
    {
        return itsSst;
    }

private:

    TL1_SmartParameter<string>					itsEntityName;
    TL1_SmartParameter<CT_TL1_AdjacencyAddr>	itsAdjAddr;
    TL1_SmartParameter<CT_TL1_LinkAddr>			itsInterfaceAddr;
    TL1_SmartParameter<CT_TL1_AreaAddr>			itsAreaAddr;
    TL1_SmartParameter<CT_InterfaceType>		itsInterfaceType;
    TL1_SmartParameter<CT_Adj_Status>			itsAdjStatus;
	TL1_SmartParameter<uint32>					itsNghbrId;
    TL1_SmartParameter<uint32>					itsIPAddr;
    TL1_SmartParameter<CT_SM_PST>				itsPst;
    TL1_SmartParameter<CT_SM_PSTQ>				itsPstq;
    TL1_SmartParameter<CT_SM_PST>				itsSst;
};

typedef TL1_Rtv_Response< TL1_OspfAdjRspBlk > TL1_OspfAdjResponse;

// OSPF AREA
class TL1_OspfAreaRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OspfAreaRspBlk() {}
    
    TL1_OspfAreaRspBlk(const TL1_OspfAreaRspBlk& );

    TL1_OspfAreaRspBlk( const TL1_SmartParameter<string>&               theEntityName,
                        const TL1_SmartParameter<CT_TL1_AreaAddr>&      theAreaAddr,
                        const TL1_SmartParameter<uint32>&               theRouterAreaId,
                        const TL1_SmartParameter<CT_TL1_LogicalId>&     theProfileId,
                        const TL1_SmartParameter<bool>&                 theHub,
                        const TL1_SmartParameter<CT_RROVisibilityType>& theRroVisibility,
                        const TL1_SmartParameter<CT_SM_PST>&            thePst,
                        const TL1_SmartParameter<CT_SM_PSTQ>&           thePstq,
                        const TL1_SmartParameter<CT_SM_SST>&            theSst);
                 
    
    virtual ~TL1_OspfAreaRspBlk();

    TL1_OspfAreaRspBlk& operator=( const TL1_OspfAreaRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter<CT_TL1_AreaAddr>& 
        GetAreaAddr() const
    {
        return itsAreaAddr;
    }

    const TL1_SmartParameter<CT_TL1_LogicalId>& 
        GetProfileId() const
    {
        return itsProfileId;
    }

    const TL1_SmartParameter<uint32>& 
        GetRouterAreaId() const
    {
        return itsRouterAreaId;
    }

    const TL1_SmartParameter<bool>& 
        GetHub() const
    {
        return itsHub;
    }

    const TL1_SmartParameter<CT_RROVisibilityType>& 
        GetRroVisibility() const
    {
        return itsRroVisibility;
    }

    const TL1_SmartParameter<CT_SM_PST>& 
        GetPst() const
    {
        return itsPst;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>& 
        GetPstq() const
    {
        return itsPstq;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSst() const
    {
        return itsSst;
    }

private:

    TL1_SmartParameter<string>                  itsEntityName;
    TL1_SmartParameter<CT_TL1_AreaAddr>         itsAreaAddr;
    TL1_SmartParameter<uint32>                  itsRouterAreaId;
    TL1_SmartParameter<CT_TL1_LogicalId>        itsProfileId;
    TL1_SmartParameter<bool>                    itsHub;
    TL1_SmartParameter<CT_RROVisibilityType>    itsRroVisibility;
    TL1_SmartParameter<CT_SM_PST>               itsPst;
    TL1_SmartParameter<CT_SM_PSTQ>              itsPstq;
    TL1_SmartParameter<CT_SM_PST>               itsSst;
};

typedef TL1_Rtv_Response< TL1_OspfAreaRspBlk > TL1_OspfAreaResponse;


class TL1_OspfrpmapRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_OspfrpmapRspBlk( );
	
    TL1_OspfrpmapRspBlk(const string* theEntityName,
                        const CT_TL1_RpMapAddr* theAddr );
	
    TL1_OspfrpmapRspBlk(const TL1_OspfrpmapRspBlk& );
    
    virtual ~TL1_OspfrpmapRspBlk();

    TL1_OspfrpmapRspBlk& operator=( const TL1_OspfrpmapRspBlk& t1Blk );

    bool operator==( const TL1_OspfrpmapRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetOspfrpmapAddr( CT_TL1_RpMapAddr& theAddr ) const;
        
    void SetEntityName( string& theEntityName );
    void SetOspfrpmapAddr( const CT_TL1_RpMapAddr& theAddr );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_OspfrpmapAddr,	
        INDEX_END
    };

    vector<bool>                 myBitSet;

    string                       myEntityName;
    CT_TL1_RpMapAddr             myAddr;
};

typedef TL1_Rtv_Response< TL1_OspfrpmapRspBlk > TL1_OspfrpmapResponse;

class TL1_OspfrpRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_OspfrpRspBlk( );
	
    TL1_OspfrpRspBlk(const string*               theEntityName,
                     const CT_TL1_RpAddr*        theAddr,
                     const uint32*               theChildRtAreaId,
                     const uint32*               theParentRtAreaId,
                     const CT_Ospfrp_Entry_Type* theEntryType,
                     const uint32*               theParentNodeId,
                     const uint32*               theParentTgtAddr,
                     const uint32*               theParentTgtAddrMask,
                     const uint32*               theChildTgtAddr,
                     const uint32*               theChildTgtAddrMask,
                     const uint32*               theParentLinkAddr,
                     const uint32*               theParentLinkIfIdx,
                     const uint32*               theChildLinkAddr,
                     const uint32*               theChildLinkIfIdx,
                     const uint8*                thePrecedence );
	
    TL1_OspfrpRspBlk(const TL1_OspfrpRspBlk& );
    
    virtual ~TL1_OspfrpRspBlk();

    TL1_OspfrpRspBlk& operator=( const TL1_OspfrpRspBlk& t1Blk );

    bool operator==( const TL1_OspfrpRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetOspfrpAddr( CT_TL1_RpAddr& theAddr ) const;
    bool GetChildRtAreaId( uint32& theChildRtAreaId ) const;
    bool GetParentRtAreaId( uint32& theParentRtAreaId ) const;
    bool GetEntryType( CT_Ospfrp_Entry_Type& theEntryType ) const;
    bool GetParentNodeId( uint32& theParentNodeId ) const;
    bool GetParentTgtAddr( uint32& theParentTgtAddr ) const;
    bool GetParentTgtAddrMask( uint32& theParentTgtAddrMask ) const;
    bool GetChildTgtAddr( uint32& theChildTgtAddr ) const;
    bool GetChildTgtAddrMask( uint32& theChildTgtAddrMask ) const;
    bool GetParentLinkAddr( uint32& theParentLinkAddr ) const;
    bool GetParentLinkIfIdx( uint32& theParentLinkIfIdx ) const;
    bool GetChildLinkAddr( uint32& theChildLinkAddr ) const;
    bool GetChildLinkIfIdx( uint32& theChildLinkIfIdx ) const;
    bool GetPrecedence( uint8& thePrecedence ) const;

    void SetEntityName( string& theEntityName );
    void SetOspfrpAddr( const CT_TL1_RpAddr& theAddr );
    void SetChildRtAreaId( const uint32& theChildRtAreaId );
    void SetParentRtAreaId( const uint32& theParentRtAreaId );
    void SetEntryType( const CT_Ospfrp_Entry_Type& theEntryType );
    void SetParentNodeId( const uint32& theParentNodeId );
    void SetParentTgtAddr( const uint32& theParentTgtAddr );
    void SetParentTgtAddrMask( const uint32& theParentTgtAddrMask );
    void SetChildTgtAddr( const uint32& theChildTgtAddr );
    void SetChildTgtAddrMask( const uint32& theChildTgtAddrMask );
    void SetParentLinkAddr( const uint32& theParentLinkAddr );
    void SetParentLinkIfIdx( const uint32& theParentLinkIfIdx );
    void SetChildLinkAddr( const uint32& theChildLinkAddr );
    void SetChildLinkIfIdx( const uint32& theChildLinkIfIdx );
    void SetPrecedence( const uint8& thePrecedence );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_OspfrpAddr,
        INDEX_ChildRtAreaId,
        INDEX_ParentRtAreaId,
        INDEX_EntryType,
        INDEX_ParentNodeId,
        INDEX_ParentTgtAddr,
        INDEX_ParentTgtAddrMask,
        INDEX_ChildTgtAddr,
        INDEX_ChildTgtAddrMask,
        INDEX_ParentLinkAddr,
        INDEX_ParentLinkIfIdx,
        INDEX_ChildLinkAddr,
        INDEX_ChildLinkIfIdx,
        INDEX_Precedence,	
        INDEX_END
    };

    vector<bool>                 myBitSet;

    string                       myEntityName;
    CT_TL1_RpAddr                myAddr;
    uint32                       myChildRoutingAreaId;
    uint32                       myParentRoutingAreaId;
    CT_Ospfrp_Entry_Type         myEntryType;
    uint32                       myParentNodeId;
    uint32                       myParentTgtAddr;
    uint32                       myParentTgtAddrMask;
    uint32                       myChildTgtAddr;
    uint32                       myChildTgtAddrMask;
    uint32                       myParentLinkAddr;
    uint32                       myParentLinkIfIdx;
    uint32                       myChildLinkAddr;
    uint32                       myChildLinkIfIdx;
    uint8                        myPrecedence;
    
};

typedef TL1_Rtv_Response< TL1_OspfrpRspBlk > TL1_OspfrpResponse;

#endif



