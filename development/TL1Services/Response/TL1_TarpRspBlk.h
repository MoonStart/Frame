/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OCH Response Class
TARGET:
AUTHOR:         August 23, 2006 - Thomas Novak
DESCRIPTION:    Header file for TL1 Retrive Tarp Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_TARP_RESPONSE_BLOCK_H__
#define __TL1_TARP_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_TarpRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_TarpRspBlk( );
	
	TL1_TarpRspBlk(const TL1_TarpRspBlk& );
    
    virtual ~TL1_TarpRspBlk();

    TL1_TarpRspBlk& operator=( const TL1_TarpRspBlk& t1Blk );

    bool operator==( const TL1_TarpRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetTarpAddr( CT_TL1_FacAddr& theTarpAddr ) const;

    bool GetFlushTmr( uint16& theFlushTmr ) const;
    bool GetEntryTmr( uint16& theEntryTmr ) const;
    bool GetT1Tmr( uint16& theT1Tmr ) const;
    bool GetT2Tmr( uint16& theT2Tmr ) const;
    bool GetT3Tmr( uint16& theT3Tmr ) const;
    bool GetT4Tmr( uint16& theT4Tmr ) const;
    bool GetProtAddr( uint16& theProtAddr ) const;
    bool GetSeqNum( uint16& theSeqNum ) const;
    bool GetLFTarpMsg( uint32& theLFTarpMsg ) const;
    bool GetNSEL( string& theNSEL ) const;
    bool GetTarpReset( CT_TarpResetType&  theTarpReset ) const;

    bool GetAlarmProfile( CT_ProfileTableId&) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );
    void SetTarpAddr( const CT_TL1_FacAddr& theTarpAddr );

    void SetFlushTmr( const uint16& theFlushTmr );
    void SetEntryTmr( const uint16& theEntryTmr );
    void SetT1Tmr( const uint16& theT1Tmr );
    void SetT2Tmr( const uint16& theT2Tmr );
    void SetT3Tmr( const uint16& theT3Tmr );
    void SetT4Tmr( const uint16& theT4Tmr );
    void SetProtAddr( const uint16& theProtAddr );
    void SetSeqNum( const uint16& theSeqNum );
    void SetLFTarpMsg( const uint32& theLFTarpMsg );
    void SetNSEL( const string& theNSEL );
    void SetTarpReset( CT_TarpResetType&  theTarpReset );

    void SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile);
    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );
    void SetSST( CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_TarpAddr,
        INDEX_FlushTmr,
        INDEX_EntryTmr,
        INDEX_T1Tmr,
        INDEX_T2Tmr,
        INDEX_T3Tmr,
        INDEX_T4Tmr,
        INDEX_ProtAddr,
        INDEX_SeqNum,
        INDEX_LFTarpMsg,
        INDEX_NSEL,
        INDEX_TarpReset,
        INDEX_AlarmProfile,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>      myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myTarpAddr;

    uint16            myFlushTmr;
    uint16            myEntryTmr;
    uint16            myT1Tmr;
    uint16            myT2Tmr;
    uint16            myT3Tmr;
    uint16            myT4Tmr;
    uint16            myProtAddr;
    uint16            mySeqNum;
    uint32            myLFTarpMsg;
    string            myNSEL;
    CT_TarpResetType  myTarpReset;

    CT_ProfileTableId myAlarmProfile;
    CT_SM_PST         myPST;
    CT_SM_PSTQ        myPSTQ;
    CT_SM_SST         mySST;

};

typedef TL1_Rtv_Response< TL1_TarpRspBlk > TL1_TarpResponse;
#endif  // #ifndef __TL1_TARP_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
