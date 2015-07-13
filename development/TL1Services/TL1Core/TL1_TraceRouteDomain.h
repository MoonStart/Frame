#ifndef __TL1_TRACEROUTEDOMAIN_H__
#define __TL1_TRACEROUTEDOMAIN_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2009 - Tom Novak
DESCRIPTION:    Header file for TL1 Trace Route Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <CommonTypes/CT_TL1_Base.h>

class TL1_Response;

class TL1_TraceRouteDomain
{
public:

    virtual void OprTraceRoute( const string&   ipAddr,
                                const int       timeout,
                                const int       pktsize,
                                const int       hopcnt,
                                TL1_Response&   tl1RspBlk ) = 0;
};

#endif
