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

#ifndef __TL1_SIMPLERESPONSE_H_
#define __TL1_SIMPLERESPONSE_H_

#include <Response/TL1_Response.h>

class TL1_SimpleRspBlk 
{
public:
    enum TL1_COMPLETION_CODE
    {
       TL1_COMPLD,
       TL1_DENY
    };
    enum TL1_ERROR_CODE
    {
       TL1E_NOERROR = 0,
       TL1E_EQWT,
       TL1E_IBEX,
       TL1E_IBMS
    };
    TL1_SimpleRspBlk( TL1_COMPLETION_CODE tcc, TL1_ERROR_CODE tec = TL1E_NOERROR );
    ~TL1_SimpleRspBlk();
private:
    TL1_COMPLETION_CODE mytcc;
    TL1_ERROR_CODE  mytec;
};

typedef TL1_Rtv_Response< TL1_SimpleRspBlk > TL1_SimpleResponse;
#endif  // #ifndef __TL1_SIMPLERESPONSE_H_  

#endif // #ifdef __cplusplus
