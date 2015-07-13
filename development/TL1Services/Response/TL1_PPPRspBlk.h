/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive PPP, PPPPF Response Class
TARGET:
AUTHOR:         Lee Gernes
DESCRIPTION:    Header file for TL1 Retrive PPP, PPPPF Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_PPP_RESPONSE_BLOCK_H__
#define __TL1_PPP_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>


class TL1_PPPRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_PPPRspBlk( );
	
	TL1_PPPRspBlk(const TL1_PPPRspBlk& );
    
    virtual ~TL1_PPPRspBlk();

    TL1_PPPRspBlk& operator=( const TL1_PPPRspBlk& t1Blk );

    bool operator==( const TL1_PPPRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetPPPAddr( CT_TL1_FacAddr& thePPPAddr ) const;
    bool GetProfileAddr( CT_PPPProfAddr& theProfileAddr ) const;
    bool GetAlarmProfile( CT_ProfileTableId&) const;
    bool GetNpOwner( uint8&) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );
    void SetPPPAddr( const CT_TL1_FacAddr& thePPPAddr );
    void SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile);
    void SetNpOwner( const uint8& theNpOwner);
    void SetProfileAddr( const CT_PPPProfAddr& theProfileAddr );
    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );
    void SetSST( CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_PPPAddr,
        INDEX_ProfileAddr,
        INDEX_AlarmProfile,
        INDEX_NpOwner,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>        myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myPPPAddr;
    CT_ProfileTableId myAlarmProfile;
    CT_PPPProfAddr    myProfileAddr;
    uint8	      myNpOwner;
    CT_SM_PST         myPST;
    CT_SM_PSTQ        myPSTQ;
    CT_SM_SST         mySST;
};

typedef TL1_Rtv_Response< TL1_PPPRspBlk > TL1_PPPResponse;


class TL1_PPPPFRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_PPPPFRspBlk( );
	
    TL1_PPPPFRspBlk(const TL1_PPPPFRspBlk& );
    
    virtual ~TL1_PPPPFRspBlk();

    TL1_PPPPFRspBlk& operator=( const TL1_PPPPFRspBlk& t1Blk );

    bool operator==( const TL1_PPPPFRspBlk& t1Blk ) const;

    bool GetEntityName( string& ) const;
    bool GetPFAddr( CT_TL1_LogicalAddr& ) const;
    bool GetPFname( string& ) const;
    bool GetMaxRcvUnits( uint16& ) const;
    bool GetFCS( CT_FCS& ) const;
    bool GetRestartTimer( uint16& ) const;
    bool GetMaxFailureCount( uint16& ) const;

    void SetEntityName( const string& theEntityName );
    void SetPFAddr( const CT_TL1_LogicalAddr& theAddr );
    void SetPFname( const string& thePFname );
    void SetMaxRcvUnits( const uint16& theMaxRcvUnits );
    void SetFCS( const CT_FCS& theFCS );
    void SetRestartTimer( const uint16& theRestartTimer );
    void SetMaxFailureCount( const uint16& theMaxFailureCount );


private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_PFAddr,
        INDEX_PFname,
        INDEX_MaxRcvUnits,
        INDEX_FCS,
        INDEX_RestartTimer,
        INDEX_MaxFailureCount,
        INDEX_END
    };

    vector<bool>         myBitSet;
    string               myEntityName;
    CT_TL1_LogicalAddr   myPFAddr;
    string               myPFname;
    uint16               myMaxRcvUnits;
    CT_FCS               myFCS;
    uint16               myRestartTimer;
    uint16               myMaxFailureCount;
};

typedef TL1_Rtv_Response< TL1_PPPPFRspBlk > TL1_PPPPFResponse;

#endif  // #ifndef __TL1_PPP_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
