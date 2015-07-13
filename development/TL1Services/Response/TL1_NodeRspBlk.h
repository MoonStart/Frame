#ifndef __TL1_NODE_RESPONSE_BLOCK_H__
#define __TL1_NODE_RESPONSE_BLOCK_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive NODE Response Class
TARGET:
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Retrive NODE Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_NodeRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_NodeRspBlk( );
	
	TL1_NodeRspBlk( const string* theEntityName,
                   const CT_TL1_NodeAddr* theAddr,
                   const string* theNodeName,
                   const uint32* theNodeId,
                   const string* theAreaName,
                   const CT_SM_PST* thePST,
                   const CT_SM_PSTQ* thePSTQ);
	
	TL1_NodeRspBlk(const TL1_NodeRspBlk& );
    
    virtual ~TL1_NodeRspBlk();

    TL1_NodeRspBlk& operator=( const TL1_NodeRspBlk& theRspBlk );

    bool operator==( const TL1_NodeRspBlk& theRspBlk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetNodeAddr( CT_TL1_NodeAddr& theAddr ) const;
    bool GetNodeName( string& theNodeName ) const;
    bool GetNodeId( uint32& theNodeId ) const;
    bool GetAreaName( string& theAreaName ) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;

    void SetEntityName( string& theEntityName );
    void SetNodeAddr( const CT_TL1_NodeAddr& theAddr );
    void SetNodeName( const string& theNodeName );
    void SetNodeId( const uint32& theNodeId );
    void SetAreaName( const string& theAreaName );
    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_NodeAddr,	
        INDEX_NodeName,
        INDEX_NodeId,
        INDEX_AreaName,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_END
    };

    vector<bool>                 myBitSet;
    string                       myEntityName;
    CT_TL1_NodeAddr              myAddr;
    string                       myNodeName; 
    uint32                       myNodeId; 
    string                       myAreaName; 

    CT_SM_PST                    myPST;
    CT_SM_PSTQ                   myPSTQ;
};

typedef TL1_Rtv_Response< TL1_NodeRspBlk > TL1_NodeResponse;


#endif  // #ifdef  __cplusplus
#endif  // #ifndef __TL1_NODE_RESPONSE_BLOCK_H__
