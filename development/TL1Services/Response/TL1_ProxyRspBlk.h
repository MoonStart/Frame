/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Mtera Response Class
TARGET:
AUTHOR:         2013.11.8 - Gang zhu
DESCRIPTION:    Header file for TL1 Retrive mtera Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PROXYRSPBLK_H_
#define __TL1_PROXYRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_EON_H__
#include <CommonTypes/CT_EON.h>
#endif

#include <vector>

#include <cstring>

using namespace std;


class TL1_ProxyRspBlk : public TL1_GeneralRspBlk
{
public: 
    TL1_ProxyRspBlk() {};
    
    TL1_ProxyRspBlk(const TL1_ProxyRspBlk& );

    TL1_ProxyRspBlk(const TL1_SmartParameter<CT_ProxyMode>& theProxyMode);
    
    virtual ~TL1_ProxyRspBlk();

    TL1_ProxyRspBlk& operator=( const TL1_ProxyRspBlk& theBlock );

    const TL1_SmartParameter<CT_ProxyMode>& GetProxyMode() const;

private:
    
    TL1_SmartParameter<CT_ProxyMode>    myProxyMode;
};

typedef TL1_Rtv_Response< TL1_ProxyRspBlk > TL1_ProxyResponse;

#endif


