/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Path Trace Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Path Trace Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_PTH_RESPONSE_BLOCK_H_
#define __TL1_PTH_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_AgentFacility.h>

class TL1_PTHRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_PTHRspBlk();
    
    // Construcotr for General Facility
    TL1_PTHRspBlk(const string *, 
                  const CT_TL1_FacAddr *,
                  const CT_Fac_TraceString* ExpectedTrace, 
                  const CT_Fac_TraceString* IncomingTrace, 
                  const CT_Fac_TraceString* Trace,
                  const CT_Fac_TraceString* RxSapi,
                  const CT_Fac_TraceString* RxDapi,
                  const CT_Fac_TraceString* RxOper,
                  const CT_Fac_TraceString* ExpDapi,
                  const CT_Fac_TraceString* ExpSapi,
                  const CT_Fac_TraceString* TxDapi,
                  const CT_Fac_TraceString* TxSapi,
                  const CT_Fac_TraceString* ExpOper,
                  const CT_Fac_TraceString* TxOper);

    TL1_PTHRspBlk(const TL1_PTHRspBlk& PTHBlk);

    virtual ~TL1_PTHRspBlk();

    TL1_PTHRspBlk& operator=( const TL1_PTHRspBlk& theBlock );

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr &) const ;

    bool GetExpectedTrace(CT_Fac_TraceString&) const;

    bool GetIncomingTrace(CT_Fac_TraceString&) const;

    bool GetTrace(CT_Fac_TraceString&) const;

    bool GetRxSapi(CT_Fac_TraceString&) const;

    bool GetRxDapi(CT_Fac_TraceString&) const;

    bool GetRxOper(CT_Fac_TraceString&) const;

    bool GetExpDapi(CT_Fac_TraceString&) const;

    bool GetExpSapi(CT_Fac_TraceString&) const;

    bool GetTxDapi(CT_Fac_TraceString&) const;
    
    bool GetTxSapi(CT_Fac_TraceString&) const;

    bool GetExpOper(CT_Fac_TraceString&) const;
    
    bool GetTxOper(CT_Fac_TraceString&) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_ExpectedTrace,
        INDEX_IncomingTrace,
        INDEX_Trace,
        INDEX_RxSapi,
        INDEX_RxDapi,
        INDEX_RxOper,
        INDEX_ExpDapi,
        INDEX_ExpSapi,
        INDEX_TxDapi,
        INDEX_TxSapi,
        INDEX_ExpOper,
        INDEX_TxOper,
        INDEX_END
    };

    vector<bool>       myBitSet;

    string             myEntityName;
    CT_TL1_FacAddr     myFacAddr;
    CT_Fac_TraceString myExpectedTrace;
    CT_Fac_TraceString myIncomingTrace;
    CT_Fac_TraceString myTrace;
    CT_Fac_TraceString myRxSapi;
    CT_Fac_TraceString myRxDapi;
    CT_Fac_TraceString myRxOper;
    CT_Fac_TraceString myExpDapi;
    CT_Fac_TraceString myExpSapi;
    CT_Fac_TraceString myTxDapi;
    CT_Fac_TraceString myTxSapi;
    CT_Fac_TraceString myExpOper;
    CT_Fac_TraceString myTxOper;
};

typedef TL1_Rtv_Response< TL1_PTHRspBlk > TL1_PTHResponse;

class TL1_PTHOtsRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_PTHOtsRspBlk();
    
    // Construcotr for General Facility
    TL1_PTHOtsRspBlk(const string *, 
                  const CT_TL1_FacAddr *,
                  const CT_Fac_TraceString* ExpectedTrace, 
                  const CT_Fac_TraceString* IncomingTrace, 
                  const CT_Fac_TraceString* Trace);

    TL1_PTHOtsRspBlk(const TL1_PTHOtsRspBlk& PTHBlk);

    virtual ~TL1_PTHOtsRspBlk();

    TL1_PTHOtsRspBlk& operator=( const TL1_PTHOtsRspBlk& theBlock );

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr &) const ;

    bool GetExpectedTrace(CT_Fac_TraceString&) const;

    bool GetIncomingTrace(CT_Fac_TraceString&) const;

    bool GetTrace(CT_Fac_TraceString&) const;
private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_ExpectedTrace,
        INDEX_IncomingTrace,
        INDEX_Trace,
        INDEX_END
    };

    vector<bool>       myBitSet;

    string             myEntityName;
    CT_TL1_FacAddr     myFacAddr;
    CT_Fac_TraceString myExpectedTrace;
    CT_Fac_TraceString myIncomingTrace;
    CT_Fac_TraceString myTrace;
};

typedef TL1_Rtv_Response< TL1_PTHOtsRspBlk > TL1_PTHOtsResponse;

class TL1_PTHOtuOduRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_PTHOtuOduRspBlk();
    
    // Construcotr for General Facility
    TL1_PTHOtuOduRspBlk(const string *, 
                  const CT_TL1_FacAddr *,
                  const CT_Fac_TraceString* ExpectedTrace, 
                  const CT_Fac_TraceString* Trace,
                  const CT_Fac_TraceString* RxSapi,
                  const CT_Fac_TraceString* RxDapi,
                  const CT_Fac_TraceString* RxOper,
                  const CT_Fac_TraceString* ExpDapi,
                  const CT_Fac_TraceString* ExpSapi,
                  const CT_Fac_TraceString* TxDapi,
                  const CT_Fac_TraceString* TxSapi);

    TL1_PTHOtuOduRspBlk(const TL1_PTHOtuOduRspBlk& PTHBlk);

    virtual ~TL1_PTHOtuOduRspBlk();

    TL1_PTHOtuOduRspBlk& operator=( const TL1_PTHOtuOduRspBlk& theBlock );

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr &) const ;

    bool GetExpectedTrace(CT_Fac_TraceString&) const;

    bool GetIncomingTrace(CT_Fac_TraceString&) const;

    bool GetTrace(CT_Fac_TraceString&) const;

    bool GetRxSapi(CT_Fac_TraceString&) const;

    bool GetRxDapi(CT_Fac_TraceString&) const;

    bool GetRxOper(CT_Fac_TraceString&) const;

    bool GetExpDapi(CT_Fac_TraceString&) const;

    bool GetExpSapi(CT_Fac_TraceString&) const;

    bool GetTxDapi(CT_Fac_TraceString&) const;
    
    bool GetTxSapi(CT_Fac_TraceString&) const;
private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_ExpectedTrace,
        INDEX_Trace,
        INDEX_RxSapi,
        INDEX_RxDapi,
        INDEX_RxOper,
        INDEX_ExpDapi,
        INDEX_ExpSapi,
        INDEX_TxDapi,
        INDEX_TxSapi,
        INDEX_END
    };

    vector<bool>       myBitSet;

    string             myEntityName;
    CT_TL1_FacAddr     myFacAddr;
    CT_Fac_TraceString myExpectedTrace;
    CT_Fac_TraceString myTrace;
    CT_Fac_TraceString myRxSapi;
    CT_Fac_TraceString myRxDapi;
    CT_Fac_TraceString myRxOper;
    CT_Fac_TraceString myExpDapi;
    CT_Fac_TraceString myExpSapi;
    CT_Fac_TraceString myTxDapi;
    CT_Fac_TraceString myTxSapi;
};

typedef TL1_Rtv_Response< TL1_PTHOtuOduRspBlk > TL1_PTHOtuOduResponse;

#endif  // #ifndef __TL1_PTH_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
