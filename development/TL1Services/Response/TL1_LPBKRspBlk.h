/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive LPBK Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive LPBK Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_LPBK_RESPONSE_BLOCK_H_
#define __TL1_LPBK_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_LPBKRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_LPBKRspBlk(const string *, 
                  const CT_TL1_LoopbackType *);

    TL1_LPBKRspBlk(const TL1_LPBKRspBlk& );
    
    virtual ~TL1_LPBKRspBlk();

    TL1_LPBKRspBlk& operator=( const TL1_LPBKRspBlk& theBlock );

    bool GetEntityName(string & ) const;

    bool GetLoopbackType( CT_TL1_LoopbackType& ) const;

private:
    string          myEntityName;
    CT_TL1_LoopbackType myType;

};

#endif  // #ifndef __TL1_LPBK_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
