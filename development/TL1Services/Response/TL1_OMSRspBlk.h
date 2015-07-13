/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OMS Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive OMS Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_OMS_RESPONSE_BLOCK_H_
#define __TL1_OMS_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_OMSRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OMSRspBlk();
    
    TL1_OMSRspBlk(const string *,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_CardType *,
                  const CT_SubCardType*,
                  const CT_ProfileTableId *,
                  const bool*,
                  const CT_SM_PST *,
                  const CT_SM_PSTQ *,
                  const CT_SM_SST *);

    TL1_OMSRspBlk(const TL1_OMSRspBlk& );
    
    virtual ~TL1_OMSRspBlk();

    TL1_OMSRspBlk& operator=( const TL1_OMSRspBlk& theBlock );

    bool operator==( const TL1_OMSRspBlk& theBlock ) const;

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    
    bool GetCardType(CT_CardType & ) const;

    bool GetSubCardType( CT_SubCardType&) const ;
    
    bool GetALMPF( CT_ProfileTableId &) const;

    bool GetAutoAdjustAttenuationEnabled(bool& ) const;

    bool GetPST( CT_SM_PST &) const;

    bool GetPSTQ( CT_SM_PSTQ &) const;

    bool GetSST( CT_SM_SST &) const;

    CT_SM_PST GetPST() const;

    CT_SM_PSTQ GetPSTQ() const;

    CT_SM_SST GetSST() const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_ID,
        INDEX_AutoAdjustAttenuationEnabled,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>    myBitSet;
    string          myEntityName;
    CT_TL1_FacAddr  myFacAddr;
    
    CT_CardType     myCardType;
    CT_SubCardType  mySubCardType;

    CT_ProfileTableId  myID;
    bool               myAutoAdjustAttenuationEnabled;
    CT_SM_PST          myPST;
    CT_SM_PSTQ         myPSTQ;
    CT_SM_SST          mySST;
};

typedef TL1_Rtv_Response< TL1_OMSRspBlk > TL1_OMSResponse;
#endif  // #ifndef __TL1_OMS_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
