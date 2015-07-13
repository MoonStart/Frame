/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive NP Response Class
TARGET:
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Retrive NP Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif 

#ifdef __cplusplus

#ifndef __TL1_NP_RESPONSE_BLOCK_H__
#define __TL1_NP_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>

class TL1_NPRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_NPRspBlk( );
	
	TL1_NPRspBlk( const string* theEntityName,
                 const CT_TL1_NetworkPartitionAddr* theAddr,
                 const string* theNpName,
                 const uint16* theTimeout,
                 const CT_SM_PST* thePST,
                 const CT_SM_PSTQ* thePSTQ );
	
	TL1_NPRspBlk(const TL1_NPRspBlk& );
    
    virtual ~TL1_NPRspBlk();

    TL1_NPRspBlk& operator=( const TL1_NPRspBlk& t1Blk );

    bool operator==( const TL1_NPRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetNpAddr( CT_TL1_NetworkPartitionAddr& theAddr ) const;
    bool GetNpName( string& theNpName ) const;
    bool GetTimeout( uint16& theTimeout ) const;

    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;

    void SetEntityName( string& theEntityName );
    void SetNpAddr( const CT_TL1_NetworkPartitionAddr& theAddr );
    void SetNpName( const string& theNpName );
    void SetTimeout( const uint16& theTimeout );

    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_NpAddr,	
        INDEX_NpName,
        INDEX_Timeout,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_END
    };

    vector<bool>                 myBitSet;

    string                       myEntityName;
    CT_TL1_NetworkPartitionAddr  myAddr;
    string                       myNpName; 
    uint16                       myTimeout;    
    CT_SM_PST                    myPST;
    CT_SM_PSTQ                   myPSTQ;
};

typedef TL1_Rtv_Response< TL1_NPRspBlk > TL1_NPResponse;

class TL1_NPSTATSRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_NPSTATSRspBlk( );
	
	TL1_NPSTATSRspBlk( const string* theEntityName,
                           const CT_TL1_NetworkPartitionAddr* theAddr,
                           const string* theNpName,
                           const uint32* theCurrActiveCalls,
                           const uint32* theCurrCallAttempts,
                           const uint32* theCurrFailCallAttempts,
                           const uint32* theCurrFailCallAttemptsRoute,
                           const uint32* thePrevCallAttempts,
                           const uint32* thePrevFailCallAttempts,
                           const uint32* thePrevFailCallAttemptsRoute );
	
	TL1_NPSTATSRspBlk(const TL1_NPSTATSRspBlk& );
    
        virtual ~TL1_NPSTATSRspBlk();

        TL1_NPSTATSRspBlk& operator=( const TL1_NPSTATSRspBlk& t1Blk );

        bool operator==( const TL1_NPSTATSRspBlk& t1Blk ) const;

        bool GetEntityName( string& theEntityName ) const;
        bool GetNpAddr( CT_TL1_NetworkPartitionAddr& theAddr ) const;
        bool GetNpName( string& theNpName ) const;
        bool GetCurrActiveCalls( uint32& theCurrActiveCalls ) const;
        bool GetCurrCallAttempts( uint32& theCurrCallAttempts ) const;
        bool GetCurrFailCallAttempts( uint32& theCurrFailCallAttempts ) const;
        bool GetCurrFailCallAttemptsRoute( uint32& theCurrFailCallAttemptRoute ) const;
        bool GetPrevCallAttempts( uint32& thePrevCallAttempts ) const;
        bool GetPrevFailCallAttempts( uint32& thePrevFailCallAttempts ) const;
        bool GetPrevFailCallAttemptsRoute( uint32& thePrevFailCallAttemptsRoute ) const;

        void SetEntityName( string& theEntityName );
        void SetNpAddr( const CT_TL1_NetworkPartitionAddr& theAddr );
        void SetNpName( const string& theNpName );
        void SetCurrActiveCalls( const uint32& theCurrActiveCalls );
        void SetCurrCallAttempts( const uint32& theCurrCallAttempts );
        void SetCurrFailCallAttempts( const uint32& theCurrFailCallAttempts );
        void SetCurrFailCallAttemptsRoute( const uint32& theCurrFailCallAttemptRoute );
        void SetPrevCallAttempts( const uint32& thePrevCallAttempts );
        void SetPrevFailCallAttempts( const uint32& thePrevFailCallAttempts );
        void SetPrevFailCallAttemptsRoute( const uint32& thePrevFailCallAttemptsRoute );

private:
        enum 
        {
            INDEX_EntityName = 0,
            INDEX_NpAddr,	
            INDEX_NpName,
            INDEX_CurrActiveCalls,
            INDEX_CurrCallAttempts,
            INDEX_CurrFailCallAttempts,
            INDEX_CurrFailCallAttemptsRoute,
            INDEX_PrevCallAttempts,
            INDEX_PrevFailCallAttempts,
            INDEX_PrevFailCallAttemptsRoute,
            INDEX_END
        };

        vector<bool>                 myBitSet;

        string                       myEntityName;
        CT_TL1_NetworkPartitionAddr  myAddr;
        string                       myNpName; 
        uint32                       myCurrActiveCalls;    
        uint32                       myCurrCallAttempts;    
        uint32                       myCurrFailCallAttempts;    
        uint32                       myCurrFailCallAttemptsRoute;    
        uint32                       myPrevCallAttempts;    
        uint32                       myPrevFailCallAttempts;    
        uint32                       myPrevFailCallAttemptsRoute;    
};

typedef TL1_Rtv_Response< TL1_NPSTATSRspBlk > TL1_NPSTATSResponse;
#endif  // #ifndef __TL1_NP_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
