/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         July 15, 2010- Kevin, Wang
DESCRIPTION:    Header file for TL1 Retrieve IF Config Table Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IFCONFIGTBLRSPBLK_H_
#define __TL1_IFCONFIGTBLRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif
 
#ifndef __CT_EON_H__
#include <CommonTypes/CT_EON.h>
#endif


class TL1_IfConfigRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IfConfigRspBlk() {}
    
    TL1_IfConfigRspBlk( const TL1_IfConfigRspBlk& );

    TL1_IfConfigRspBlk( const TL1_SmartParameter<string>     theAidStr,
                        const TL1_SmartParameter<string>     theIfName,
                        const TL1_SmartParameter<string>     theIfType,
                        const TL1_SmartParameter<string>     theIpv6Addr,
                        const TL1_SmartParameter<int>        theIfStatus,
                        const TL1_SmartParameter<string>     theIfVldTmr,
                        const TL1_SmartParameter<int>        theIfRouterAddr );
    
    virtual ~TL1_IfConfigRspBlk();

    TL1_IfConfigRspBlk& operator=( const TL1_IfConfigRspBlk& theBlock );

    const TL1_SmartParameter<string>& GetIfAid() const;

    const TL1_SmartParameter<string>& GetIfName() const;

    const TL1_SmartParameter<string>& GetIfType() const;
    
    const TL1_SmartParameter<string>& GetIpv6Addr() const;

    const TL1_SmartParameter<int>& GetIfStatus() const;

    const TL1_SmartParameter<string>& GetIfVldTmr() const;

    const TL1_SmartParameter<int>& GetIfRouterAddr() const;

private:
    TL1_SmartParameter<string>       myAidStr;
    TL1_SmartParameter<string>       myIfName;
    TL1_SmartParameter<string>       myIfType;
    TL1_SmartParameter<string>       myIpv6Addr;
    TL1_SmartParameter<int>          myIfStatus;
    TL1_SmartParameter<string>       myIfVldTmr;
    TL1_SmartParameter<int>          myIfRouterAddr;
    

};

typedef TL1_Rtv_Response< TL1_IfConfigRspBlk > TL1_IfConfigResponse;

#endif


