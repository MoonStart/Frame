/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive BER Response Class
TARGET:
AUTHOR:         Nov. 9, 2005 -- Maggie Zhang 
DESCRIPTION:    Header file for TL1 Retrive BER Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_BER_RESPONSE_BLOCK_H_
#define __TL1_BER_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_AgentFacility.h>

class TL1_BerRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_BerRspBlk();
    
    // Construcotr for General Facility
    TL1_BerRspBlk(const string *, 
                  const CT_TL1_FacAddr *,
                  const CT_FAC_BerType *,
				  const bool *, 
                  const bool *, 
                  const CT_TEL_PrbsFormat *,
				  const uint32 *,
                  const CT_FAC_PrbsState *, 
                  const uint32 *,
				  const uint8 *,
				  const uint32 *);

    TL1_BerRspBlk(const TL1_BerRspBlk& berBlk);

    virtual ~TL1_BerRspBlk();

    TL1_BerRspBlk& operator=( const TL1_BerRspBlk& theBlock );
	bool operator==( const TL1_BerRspBlk& theBlock)const;

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr &) const ;

    bool GetBerType(CT_FAC_BerType &) const;
    bool GetPrbsTx(bool & ) const;
    bool GetPrbsRx(bool & ) const;
    bool GetPrbsCompa(CT_TEL_PrbsFormat &) const;
	bool GetPrbsRate(uint32 & ) const;
    bool GetPrbsSync(CT_FAC_PrbsState & ) const;
	bool GetPrbsDuration(uint32 & ) const;
	bool GetPrbsCalcRate(uint8 & ) const;
	bool GetPrbsCount(uint32 & ) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_BerType,
        INDEX_PrbsTx,
        INDEX_PrbsRx,
        INDEX_PrbsCompa,
		INDEX_PrbsRate,
        INDEX_PrbsSync,
        INDEX_PrbsDuration,
        INDEX_PrbsCalcRate,
        INDEX_PrbsCount,
        INDEX_END
    };

    vector<bool>     myBitSet;

    string           myEntityName;
    CT_TL1_FacAddr   myFacAddr;
    CT_FAC_BerType   myBerType;
    bool             myPrbsTx;
    bool             myPrbsRx;
    CT_TEL_PrbsFormat myPrbsCompa;
    uint32           myPrbsRate;
    CT_FAC_PrbsState myPrbsSync;
    uint32           myPrbsDuration;
    uint8            myPrbsCalcRate;
    uint32           myPrbsCount;


};

typedef TL1_Rtv_Response< TL1_BerRspBlk > TL1_BerResponse;
#endif  // #ifndef __TL1_BER_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
