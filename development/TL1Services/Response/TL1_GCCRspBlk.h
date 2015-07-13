/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive GCC Response Class
TARGET:
AUTHOR:         Shawn He
DESCRIPTION:    Header file for TL1 Retrive GCC Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_GCC_RESPONSE_BLOCK_H__
#define __TL1_GCC_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_OduDefinitions.h>
#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_TL1_FacParamAddr.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>

class TL1_GCCRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_GCCRspBlk( );
	
	TL1_GCCRspBlk(const TL1_GCCRspBlk& );
    
    virtual ~TL1_GCCRspBlk();

    TL1_GCCRspBlk& operator=( const TL1_GCCRspBlk& t1Blk );

    bool operator==( const TL1_GCCRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetGCCAddr( CT_TL1_FacAddr& theGCCAddr ) const;
    bool GetProfileAddr( CT_PPPProfAddr& theProfileAddr ) const;
    bool GetAlarmProfile( CT_ProfileTableId&) const;
    bool GetNpOwner( uint8&) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );
    void SetGCCAddr( const CT_TL1_FacAddr& theGCCAddr );
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
        INDEX_GCCAddr,
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
    CT_TL1_FacAddr    myGCCAddr;
    CT_ProfileTableId myAlarmProfile;
    CT_PPPProfAddr    myProfileAddr;
    uint8             myNpOwner;
    CT_SM_PST         myPST;
    CT_SM_PSTQ        myPSTQ;
    CT_SM_SST         mySST;
};

typedef TL1_Rtv_Response< TL1_GCCRspBlk > TL1_GCCResponse;

#endif  // #ifndef __TL1_GCC_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus

