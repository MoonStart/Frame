/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive RSVP Response Class
TARGET:
AUTHOR:         August, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Retrive RSVP Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_RSVP_RESPONSE_BLOCK_H__
#define __TL1_RSVP_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>

class TL1_RsvpRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_RsvpRspBlk( );
	
    TL1_RsvpRspBlk( const string*                theEntityName,
                    const CT_TL1_ControllerAddr* theAddr,
                    const uint32*                theSignalingControllerId,
                    const CT_TL1_LinkAddr*       theInterfaceAid,
                    const CT_SM_PST*             thePST,
                    const CT_SM_PSTQ*            thePSTQ );
	
    TL1_RsvpRspBlk(const TL1_RsvpRspBlk& );
    
    virtual ~TL1_RsvpRspBlk();

    TL1_RsvpRspBlk& operator=( const TL1_RsvpRspBlk& t1Blk );

    bool operator==( const TL1_RsvpRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetRsvpAddr( CT_TL1_ControllerAddr& theAddr ) const;
    bool GetSignalCtlId( uint32& theSignalCtlId ) const;
    bool GetInterfaceAid( CT_TL1_LinkAddr& theInterfaceAid ) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;

    void SetEntityName( string& theEntityName );
    void SetRsvpAddr( const CT_TL1_ControllerAddr& theAddr );
    void SetSignalCtlId( const uint32& theSignalCtlId );
    void SetInterfaceAid( const CT_TL1_LinkAddr& theInterfaceAid );
    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_RsvpAddr,	
        INDEX_SignalCtlId,
        INDEX_InterfaceAid,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_END
    };

    vector<bool>                 myBitSet;

    string                       myEntityName;
    CT_TL1_ControllerAddr        myAddr;
    uint32                       mySignalCtlId; 
    CT_TL1_LinkAddr              myInterfaceAid;
    CT_SM_PST                    myPST;
    CT_SM_PSTQ                   myPSTQ;
};

typedef TL1_Rtv_Response< TL1_RsvpRspBlk > TL1_RsvpResponse;

class TL1_RsvpAdjRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_RsvpAdjRspBlk( );
	
    TL1_RsvpAdjRspBlk( const string*                theEntityName,
                       const CT_TL1_AdjacencyAddr*  theAddr,
                       const uint32*                theNeighborSignalAddr,
                       const uint32*                theNeighborSignalId,
                       const CT_ProfileTableId*     theAlmProfile,
                       const CT_SM_PST*             thePST,
                       const CT_SM_PSTQ*            thePSTQ,
                       const CT_SM_SST*             theSST );
	
    TL1_RsvpAdjRspBlk(const TL1_RsvpAdjRspBlk& );
    
    virtual ~TL1_RsvpAdjRspBlk();

    TL1_RsvpAdjRspBlk& operator=( const TL1_RsvpAdjRspBlk& t1Blk );

    bool operator==( const TL1_RsvpAdjRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetRsvpAdjAddr( CT_TL1_AdjacencyAddr& theAddr ) const;
    bool GetNgbrSignalAddr( uint32& theNgbrSignalAddr ) const;
    bool GetNgbrSignalId( uint32& theNgbrSignalId ) const;
    bool GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );
    void SetRsvpAdjAddr( const CT_TL1_AdjacencyAddr& theAddr );
    void SetNgbrSignalAddr( const uint32& theNgbrSignalAddr );
    void SetNgbrSignalId( const uint32& theNgbrSignalId );
    void SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile );
    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );
    void SetSST( CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_RsvpAdjAddr,	
        INDEX_NgbrSignalAddr,
        INDEX_NgbrSignalId,
        INDEX_AlmProfile,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>                 myBitSet;

    string                       myEntityName;
    CT_TL1_AdjacencyAddr         myAddr;
    uint32                       myNgbrSignalAddr; 
    uint32                       myNgbrSignalId;
    CT_ProfileTableId            myAlmProfile;
    CT_SM_PST                    myPST;
    CT_SM_PSTQ                   myPSTQ;
    CT_SM_SST                    mySST;
};

typedef TL1_Rtv_Response< TL1_RsvpAdjRspBlk > TL1_RsvpAdjResponse;

#endif  // #ifndef __TL1_RSVP_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
