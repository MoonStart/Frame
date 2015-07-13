/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OSI Response Class
TARGET:
AUTHOR:         August 11, 2006 - Thomas Novak
DESCRIPTION:    Header file for TL1 Retrive OSI Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_OSI_RESPONSE_BLOCK_H__
#define __TL1_OSI_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_OSIRTRRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_OSIRTRRspBlk( );
	
	TL1_OSIRTRRspBlk(const TL1_OSIRTRRspBlk& );
    
    virtual ~TL1_OSIRTRRspBlk();

    TL1_OSIRTRRspBlk& operator=( const TL1_OSIRTRRspBlk& t1Blk );

    bool operator==( const TL1_OSIRTRRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetOsiRtrAddr( CT_TL1_FacAddr& theOsiRtrAddr ) const;

    bool GetPrimaryAddress( string& thePrimaryAddr ) const;
    bool GetAuxillaryAddress1(  string& theAuxAddr1 ) const;
    bool GetAuxillaryAddress2(  string& theAuxAddr2 ) const;
    bool GetRoutingSysId( string& theRSysId ) const;
    bool GetMaxLifetimeControl( uint16& theMaxLifetime ) const;
    bool GetRoutingLevel( uint16& theLevel ) const;
    bool GetMaxAreaAddress( uint16& theNumMaxArea ) const;
    bool GetLevel1State( uint16& theLevel1State ) const;
    bool GetLevel2State( uint16& theLevel2State ) const;
    bool GetNSAP( string& theNSAP ) const;
    bool GetEonGre( bool& theEonGre ) const;

    bool GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );
    void SetOsiRtrAddr( const CT_TL1_FacAddr& theOsiRtrAddr );

    void SetPrimaryAddress( const string& thePrimaryAddr );
    void SetAuxillaryAddress1( const string& theAuxAddr1 );
    void SetAuxillaryAddress2 ( const string& theAuxAddr2 );
    void SetRoutingSysId( const string& theRSysId );
    void SetMaxLifetimeControl( const uint16& theMaxLifetime );
    void SetRoutingLevel( const uint16& theLevel );
    void SetMaxAreaAddress( const uint16& theNumMaxArea );
    void SetLevel1State( const uint16& theLevel1State );
    void SetLevel2State( const uint16& theLevel2State );
    void SetNSAP( const string& theNSAP );
    void SetEonGre( const bool& theEonGre );

    void SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile );
    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );
    void SetSST( CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_OsiRtrAddr,
        INDEX_PrimaryAddr,
        INDEX_AuxAddr1,
        INDEX_AuxAddr2,
        INDEX_RSysId,
        INDEX_MaxLifetime,
        INDEX_Level,
        INDEX_NumMaxArea,
        INDEX_AlarmProfile,
        INDEX_Level1State,
        INDEX_Level2State,
        INDEX_NSAP,
        INDEX_EONGRE,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>      myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myOsiRtrAddr;
    CT_ProfileTableId myAlarmProfile;

    string            myPrimaryAddr; 
    string            myAuxAddr1; 
    string            myAuxAddr2; 
    string            myRSysId; 
    uint16            myMaxLifetime; 
    uint16            myLevel; 
    uint16            myNumMaxArea; 
    uint16            myLevel1State;
    uint16            myLevel2State;
    string            myNSAP;
    bool			  myEonGre;

    CT_SM_PST         myPST;
    CT_SM_PSTQ        myPSTQ;
    CT_SM_SST         mySST;
};

class TL1_OsiRtrMapNeighborRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_OsiRtrMapNeighborRspBlk( );
	
	TL1_OsiRtrMapNeighborRspBlk(const TL1_OsiRtrMapNeighborRspBlk& theBlk );
    
    virtual ~TL1_OsiRtrMapNeighborRspBlk( );

    TL1_OsiRtrMapNeighborRspBlk& operator=( const TL1_OsiRtrMapNeighborRspBlk& theBlk );

    bool operator==( const TL1_OsiRtrMapNeighborRspBlk& theBlk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetOsiRtrAddr( CT_TL1_FacAddr& theOsiRtrAddr ) const;

    bool GetLapdName( string& theLapdName ) const;
    bool GetLapdAddr( CT_TL1_FacAddr& theLapdAddr ) const;

    bool GetNsapAddress( string& theNsapAddr ) const;
    bool GetRouterLevel( uint8& theRoutingLevel ) const;

    bool GetTid( string& theTid ) const;

    void SetEntityName( string& theEntityName );
    void SetOsiRtrAddr( const CT_TL1_FacAddr& theOsiRtrAddr );

    void SetLapdName( const string& theLapdName );
    void SetLapdAddr( const CT_TL1_FacAddr& theLapdAddr );

    void SetNsapAddress( const string& theNsapAddr );
    void SetRouterLevel( const uint8& theRouterLevel );

    void SetTid( const string& theTid );

private:

    enum 
    {
        INDEX_EntityName = 0,
        INDEX_OsiRtrAddr,
        INDEX_LapdName,
        INDEX_LapdAddr,
        INDEX_NsapAddress,
        INDEX_RouterLevel,
        INDEX_Tid,
        INDEX_END
    };

    vector<bool>      myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myOsiRtrAddr;

    string            myLapdName; 
    CT_TL1_FacAddr    myLapdAddr;

    string            myNsapAddress; 
    uint8             myRouterLevel;

    string            myTid;
};

class TL1_OsiRtrMapNetworkRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_OsiRtrMapNetworkRspBlk( );
	
	TL1_OsiRtrMapNetworkRspBlk(const TL1_OsiRtrMapNetworkRspBlk& theBlk );
    
    virtual ~TL1_OsiRtrMapNetworkRspBlk( );

    TL1_OsiRtrMapNetworkRspBlk& operator=( const TL1_OsiRtrMapNetworkRspBlk& theBlk );

    bool operator==( const TL1_OsiRtrMapNetworkRspBlk& theBlk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetOsiRtrAddr( CT_TL1_FacAddr& theOsiRtrAddr ) const;

    bool GetLapdName( string& theLapdName ) const;
    bool GetLapdAddr( CT_TL1_FacAddr& theLapdAddr ) const;

    bool GetNsapAddress( string& theNsapAddr ) const;
    bool GetTid( string& theTid ) const;

    void SetEntityName( string& theEntityName );
    void SetOsiRtrAddr( const CT_TL1_FacAddr& theOsiRtrAddr );

    void SetLapdName( const string& theLapdName );
    void SetLapdAddr( const CT_TL1_FacAddr& theLapdAddr );

    void SetNsapAddress( const string& theNsapAddr );
    void SetTid( const string& theTid );


private:

    enum 
    {
        INDEX_EntityName = 0,
        INDEX_OsiRtrAddr,
        INDEX_LapdName,
        INDEX_LapdAddr,
        INDEX_NsapAddress,
        INDEX_Tid,
        INDEX_END
    };

    vector<bool>      myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myOsiRtrAddr;

    string            myLapdName; 
    CT_TL1_FacAddr    myLapdAddr;

    string            myNsapAddress; 
    string            myTid;

};

typedef TL1_Rtv_Response< TL1_OSIRTRRspBlk > TL1_OSIRTRResponse;
typedef TL1_Rtv_Response< TL1_OsiRtrMapNeighborRspBlk > TL1_OsiRtrMapNeighborResponse;
typedef TL1_Rtv_Response< TL1_OsiRtrMapNetworkRspBlk > TL1_OsiRtrMapNetworkResponse;

#endif  // #ifndef __TL1_OSI_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
