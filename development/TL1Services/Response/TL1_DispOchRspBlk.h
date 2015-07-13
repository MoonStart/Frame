/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrieve OCH Dispersion Response Class
TARGET:
AUTHOR:         February 6, 2008
DESCRIPTION:    Header file for TL1 Retrieve OCH Dispersion Response class
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_DISP_OCH_RESPONSE_BLOCK_H_
#define __TL1_DISP_OCH_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_TL1_Base.h>

class TL1_DispOchRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_DispOchRspBlk();
    
    // Constructor for General Facility
    TL1_DispOchRspBlk(const string *, 
                      const CT_TL1_FacAddr *,
                      const int16 * theCD,
                      const int16 * theDGD);

    TL1_DispOchRspBlk(const TL1_DispOchRspBlk& theBlock);

    virtual ~TL1_DispOchRspBlk();

    TL1_DispOchRspBlk& operator=( const TL1_DispOchRspBlk& theBlock );

    bool operator==( const TL1_DispOchRspBlk& theBlock ) const;

    bool operator!=( const TL1_DispOchRspBlk& theBlock ) const;

    bool GetEntityName(string & ) const;

    bool GetFacAddr( CT_TL1_FacAddr &) const ;

    bool GetChromDisp(int16 & ) const;

    bool GetDiffGroupDelay(int16 & ) const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_ChromDisp,
        INDEX_DiffGroupDelay,
        INDEX_END
    };

    vector<bool>    myBitSet;

    string          myEntityName;
    CT_TL1_FacAddr  myFacAddr;
    int16           myChromDisp;
    int16           myDiffGroupDelay;

};

typedef TL1_Rtv_Response< TL1_DispOchRspBlk > TL1_DispOchResponse;
#endif  // #ifndef __TL1_ATTN_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
