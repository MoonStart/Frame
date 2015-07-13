/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Gain Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Gain Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_GAIN_RESPONSE_BLOCK_H_
#define __TL1_GAIN_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_GainRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_GainRspBlk();
    
    // Ctor for Gain
    TL1_GainRspBlk(const string*,
                  const CT_TL1_FacAddr* FacAddr,
                  const bool* Apai,
                  const CT_TEL_mBm* IGain,
                  const bool* Apao,
                  const CT_TEL_mBm* OGain);

    TL1_GainRspBlk(const TL1_GainRspBlk& );
    
    virtual ~TL1_GainRspBlk();

    TL1_GainRspBlk& operator=( const TL1_GainRspBlk& theBlock );

    bool GetEntityName(string& ) const;

    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    
    bool GetApai(bool& ) const;

    bool GetIGain(CT_TEL_mBm& ) const;

    bool GetApao(bool& ) const;

    bool GetOGain(CT_TEL_mBm& ) const;
private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_Apai,
        INDEX_IGain,
        INDEX_Apao,
        INDEX_OGain,
        INDEX_END
    };

    vector<bool>    myBitSet;
    string          myEntityName;
    CT_TL1_FacAddr  myFacAddr;
    
    bool       myApai;
    CT_TEL_mBm myIGain;
    bool       myApao;
    CT_TEL_mBm myOGain;
};

typedef TL1_Rtv_Response< TL1_GainRspBlk > TL1_GainResponse;
#endif  // #ifndef __TL1_GAIN_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
