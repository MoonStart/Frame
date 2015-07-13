/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Attenuation Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Attenuation Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_ATTN_RESPONSE_BLOCK_H_
#define __TL1_ATTN_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_AttnRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_AttnRspBlk();
    
    // Construcotr for General Facility
    TL1_AttnRspBlk(const string *, 
                  const CT_TL1_FacAddr *,
                  const bool *, 
                  const CT_TEL_mBm *,
                  const CT_TEL_mBm *,
                  const CT_TEL_mBm *);

    TL1_AttnRspBlk(const TL1_AttnRspBlk& attnBlk);

    virtual ~TL1_AttnRspBlk();

    TL1_AttnRspBlk& operator=( const TL1_AttnRspBlk& theBlock );

    bool operator==( const TL1_AttnRspBlk& theBlock ) const;

    bool operator!=( const TL1_AttnRspBlk& theBlock ) const;

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr &) const ;

    bool GetApao(bool & ) const;

    bool GetAttn(CT_TEL_mBm &) const;
	
    bool GetAttnIngress(CT_TEL_mBm &) const;

        bool GetAttnEgress(CT_TEL_mBm &) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_Apao,
        INDEX_Attn,
        INDEX_AttnIngress,
        INDEX_AttnEgress,
        INDEX_END
    };

    vector<bool>    myBitSet;

    string          myEntityName;
    CT_TL1_FacAddr  myFacAddr;
    bool            myApao;
    CT_TEL_mBm      myAttn;
    CT_TEL_mBm      myAttnIngress;
    CT_TEL_mBm      myAttnEgress;

};

typedef TL1_Rtv_Response< TL1_AttnRspBlk > TL1_AttnResponse;
#endif  // #ifndef __TL1_ATTN_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
