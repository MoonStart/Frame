/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OPS Response Class
TARGET:
DESCRIPTION:    Header file for TL1 Retrive WCG Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_WCG_RESPONSE_BLOCK_H_
#define __TL1_WCG_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_WCGRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_WCGRspBlk();

    TL1_WCGRspBlk(const string* entityName,
                  const CT_TL1_FacAddr* facAddr,
                  const CT_FAC_OtsChanMap* theMap);
    
    TL1_WCGRspBlk(const TL1_WCGRspBlk& );
    
    virtual ~TL1_WCGRspBlk();

    TL1_WCGRspBlk& operator=( const TL1_WCGRspBlk& theBlock );

    bool operator==( const TL1_WCGRspBlk& theBlock ) const;

    bool GetEntityName(string & ) const;
    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    bool GetChanAvail(CT_FAC_OtsChanMap&) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_ChanAvail,
        INDEX_END
    };

    vector<bool>       myBitSet;
    string             myEntityName;
    CT_TL1_FacAddr     myFacAddr;
    CT_FAC_OtsChanMap  myChanAvail;
};

typedef TL1_Rtv_Response< TL1_WCGRspBlk > TL1_WCGResponse;

#endif  // #ifndef __TL1_WCG_RESPONSE_BLOCK_H_
#endif  // #ifdef  __cplusplus
