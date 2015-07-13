/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Protection Response Class
TARGET:
AUTHOR:        August 12, 2004 Maggie Zhang 
DESCRIPTION:    Header file for TL1 Retrive Sync Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SYNCRSPBLK_H_
#define __TL1_SYNCRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif
 
#ifndef __CT_PROTECTION_H__
#include <CommonTypes/CT_Protection.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif


#include <vector>

using namespace std;


class TL1_SyncRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SyncRspBlk() {}
    
    TL1_SyncRspBlk(const TL1_SyncRspBlk& );

    TL1_SyncRspBlk(const CT_TL1_ProtnAddr* theAddr,
                  const CT_SM_PST*  thePST,
                  const CT_SM_PSTQ* thePSTQ,
                  const CT_SM_SST*  theSST);
   
    virtual ~TL1_SyncRspBlk();

    TL1_SyncRspBlk& operator=( const TL1_SyncRspBlk& theBlock );

	bool operator==(const TL1_SyncRspBlk& theBlock) const;

    
	bool GetAddr(CT_TL1_ProtnAddr&) const;

    bool GetPST(CT_SM_PST&) const;

    bool GetPSTQ(CT_SM_PSTQ&) const;

    bool GetSST(CT_SM_SST&) const;


private:

	enum {
		INDEX_Addr = 0,
		INDEX_PST,
		INDEX_PSTQ,
		INDEX_SST,
		INDEX_END
	};

	vector<bool>      itsBitSet;
	CT_TL1_ProtnAddr  itsAddr;
    CT_SM_PST       itsPST;
    CT_SM_PSTQ      itsPSTQ;
    CT_SM_SST       itsSST;

};

typedef TL1_Rtv_Response< TL1_SyncRspBlk > TL1_SyncResponse;

#endif


