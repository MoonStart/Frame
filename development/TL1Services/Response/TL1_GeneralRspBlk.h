/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response Base Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Response base class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_GENERALRESPONSEBLK_H_
#define __TL1_GENERALRESPONSEBLK_H_

#include <CommonTypes/CT_TL1_ErrorIndex.h>

class TL1_GeneralRspBlk
{
public:
    TL1_GeneralRspBlk();
    virtual ~TL1_GeneralRspBlk();
    
    void SetError( const CT_TL1_ErrorIndex::EC_Index&, const CT_TL1_ErrorIndex::ER_Index&);
    bool IsSuccess() const;
    CT_TL1_ErrorIndex::EC_Index GetErrorCode() const;
    CT_TL1_ErrorIndex::ER_Index GetErrorReason() const;

    // This default == operator always return false.  It should be
    // overloaded to define specific behaviour.
    bool operator==( const TL1_GeneralRspBlk& theBlock ) const;
    
private:
    CT_TL1_ErrorIndex::EC_Index myEC;
    CT_TL1_ErrorIndex::ER_Index myER;
};

inline CT_TL1_ErrorIndex::EC_Index TL1_GeneralRspBlk::GetErrorCode() const { return myEC; }
inline CT_TL1_ErrorIndex::ER_Index TL1_GeneralRspBlk::GetErrorReason() const { return myER; }
inline bool TL1_GeneralRspBlk::IsSuccess() const { return (myEC == CT_TL1_ErrorIndex::EC_NO_ERROR); }

#endif  // #ifndef __TL1_GENERALRESPONSEBLK_H_  

#endif // #ifdef __cplusplus
