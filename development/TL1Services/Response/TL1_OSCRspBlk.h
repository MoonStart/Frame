/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OSC Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive OSC Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_OSC_RESPONSE_BLOCK_H_
#define __TL1_OSC_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_OSCRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OSCRspBlk();
    
    // Ctor for OSC
    TL1_OSCRspBlk(const string *,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_CardType *,
                  const CT_SubCardType*,
                  const bool *,
                  const CT_FAC_RxSsm* theSsmReceived,
                  const CT_TEL_MsTref* theTimingReference,
                  const CT_TEL_TxTiming* theTxTiming,
                  const CT_ProfileTableId *,
                  const CT_SM_PST *,
                  const CT_SM_PSTQ *,
                  const CT_SM_SST *);

    TL1_OSCRspBlk(const TL1_OSCRspBlk& );
    
    virtual ~TL1_OSCRspBlk();

    TL1_OSCRspBlk& operator=( const TL1_OSCRspBlk& theBlock );

    bool operator==( const TL1_OSCRspBlk& theBlock ) const;

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    
    bool GetCardType(CT_CardType & ) const;

    bool GetSubCardType( CT_SubCardType&) const ;

    bool GetIsEonMsgEnabled( bool &) const;

    bool GetALMPF( CT_ProfileTableId &) const;

    bool GetPST( CT_SM_PST &) const;

    bool GetPSTQ( CT_SM_PSTQ &) const;

    bool GetSST( CT_SM_SST &) const;

    bool GetSsmReceived( CT_FAC_RxSsm& ) const;

    bool GetTimingRef( CT_TEL_MsTref& ) const;

    bool GetTxTiming( CT_TEL_TxTiming& ) const;

    CT_SM_PST GetPST() const;

    CT_SM_PSTQ GetPSTQ() const;

    CT_SM_SST GetSST( ) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_IsEonMsgEnabled,
        INDEX_ID,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_SsmReceived,
        INDEX_TimingRef,
        INDEX_TxTiming,
        INDEX_END
    };

    vector<bool>       myBitSet;
    string             myEntityName;
    CT_TL1_FacAddr     myFacAddr;
    
    CT_CardType        myCardType;
    CT_SubCardType     mySubCardType;

    bool               myIsEonMsgEnabled;
    CT_ProfileTableId  myID;
    CT_SM_PST          myPST;
    CT_SM_PSTQ         myPSTQ;
    CT_SM_SST          mySST;
    CT_FAC_RxSsm       mySsmReceived;
    CT_TEL_MsTref      myTimingRef;
    CT_TEL_TxTiming    myTxTiming;
};

typedef TL1_Rtv_Response< TL1_OSCRspBlk > TL1_OSCResponse;

// OSCX
class TL1_OSCXRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OSCXRspBlk();
    
    // Ctor for OSC
    TL1_OSCXRspBlk(const string *,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_CardType *,
                  const CT_SubCardType*,
                  const bool *,
                  const bool *,
                  const uint8 *,
                  const CT_SM_PST *,
                  const CT_SM_PSTQ *,
                  const CT_SM_SST *);

    TL1_OSCXRspBlk(const TL1_OSCXRspBlk& );
    
    virtual ~TL1_OSCXRspBlk();

    TL1_OSCXRspBlk& operator=( const TL1_OSCXRspBlk& theBlock );

    bool operator==( const TL1_OSCXRspBlk& theBlock ) const;

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    
    bool GetCardType(CT_CardType & ) const;

    bool GetSubCardType( CT_SubCardType&) const ;

    bool GetIsTrafficEnabled( bool &) const;

    bool GetIsEonMsgEnabled( bool &) const;

    bool GetNpOwner( uint8 &) const;

    bool GetPST( CT_SM_PST &) const;

    bool GetPSTQ( CT_SM_PSTQ &) const;

    bool GetSST( CT_SM_SST &) const;

    CT_SM_PST GetPST() const;

    CT_SM_PSTQ GetPSTQ() const;

    CT_SM_SST GetSST( ) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_IsTrafficEnabled,
        INDEX_IsEonMsgEnabled,
        INDEX_NpOwner,
        INDEX_ID,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>       myBitSet;
    string             myEntityName;
    CT_TL1_FacAddr     myFacAddr;
    
    CT_CardType        myCardType;
    CT_SubCardType     mySubCardType;

    bool               myIsTrafficEnabled;
    bool               myIsEonMsgEnabled;
    uint8              myNpOwner;
    CT_ProfileTableId  myID;
    CT_SM_PST          myPST;
    CT_SM_PSTQ         myPSTQ;
    CT_SM_SST          mySST;

};

typedef TL1_Rtv_Response< TL1_OSCXRspBlk > TL1_OSCXResponse;
#endif  // #ifndef __TL1_OSC_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
