/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Equipment Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive Equipment Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_DLTRESPONSE_BLOCK_H_
#define __TL1_DLTRESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

class TL1_DLTRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_DLTRspBlk(){}

    TL1_DLTRspBlk(const string* entityName);
                 
    TL1_DLTRspBlk(const TL1_DLTRspBlk& );
    
    virtual ~TL1_DLTRspBlk();

    TL1_DLTRspBlk& operator=( const TL1_DLTRspBlk& theBlock );

    bool GetEntityName( string&) const ;

private:
    string          myEntityName; 
};

#endif  // #ifndef __TL1_DLTRESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
