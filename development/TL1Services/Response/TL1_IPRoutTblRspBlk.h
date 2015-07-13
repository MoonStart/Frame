/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Retrieve IP Routing Table Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IPROUTTBLRSPBLK_H_
#define __TL1_IPROUTTBLRSPBLK_H_

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


class TL1_IPRoutTblRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IPRoutTblRspBlk() {}
    
    TL1_IPRoutTblRspBlk( const TL1_IPRoutTblRspBlk& );

    TL1_IPRoutTblRspBlk( const TL1_SmartParameter<uint32>& theDestAddress,
                         const TL1_SmartParameter<uint32>& theNetMask,
                         const TL1_SmartParameter<uint32>& theNexHopAddr,
                         const TL1_SmartParameter<CT_LinkStatus>& theLinkStatus,
                         const TL1_SmartParameter<CT_RouteType>& theRouterType,
                         const TL1_SmartParameter<CT_IfNumber>& theIfName );
    
    virtual ~TL1_IPRoutTblRspBlk();

    TL1_IPRoutTblRspBlk& operator=( const TL1_IPRoutTblRspBlk& theBlock );

    const TL1_SmartParameter<uint32>& GetDestAddress() const;

    const TL1_SmartParameter<uint32>& GetNetMask() const;

    const TL1_SmartParameter<uint32>& GetNextHopAddr() const;

    const TL1_SmartParameter<CT_LinkStatus>& GetLinkStatus() const;

    const TL1_SmartParameter<CT_RouteType>& GetRouteType() const;

    const TL1_SmartParameter<CT_IfNumber>& GetIfName() const;

private:
    TL1_SmartParameter<uint32> itsDestAddress;
    TL1_SmartParameter<uint32> itsNetMask;
    TL1_SmartParameter<uint32> itsNextHopAddr;
    TL1_SmartParameter<CT_LinkStatus> itsLinkStatus;
    TL1_SmartParameter<CT_RouteType> itsRouteType;
    TL1_SmartParameter<CT_IfNumber> itsIfName;
};

typedef TL1_Rtv_Response< TL1_IPRoutTblRspBlk > TL1_IPRoutTblResponse;

#endif


