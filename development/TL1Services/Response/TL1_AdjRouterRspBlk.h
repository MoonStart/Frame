/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 4, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Retrieve Adj Router Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ADJROUTERRSPBLK_H__
#define __TL1_ADJROUTERRSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif
 
#ifndef __CT_EON_H__
#include <CommonTypes/CT_EON.h>
#endif

#ifndef _CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif


class TL1_AdjRouterRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_AdjRouterRspBlk() {}
    
    TL1_AdjRouterRspBlk( const TL1_AdjRouterRspBlk& );

    TL1_AdjRouterRspBlk( const TL1_SmartParameter<uint32>& theNeighborIp,
                         const TL1_SmartParameter<CT_Adj_Status>& theAdjacencyStatus,
                         const TL1_SmartParameter<CT_IfNumber>& theIfName );
    
    virtual ~TL1_AdjRouterRspBlk();

    TL1_AdjRouterRspBlk& operator=( const TL1_AdjRouterRspBlk& theBlock );

    const TL1_SmartParameter<uint32>& GetNeighborIp() const;

    const TL1_SmartParameter<CT_Adj_Status>& GetAdjacencyStatus() const;

    const TL1_SmartParameter<CT_IfNumber>& GetIfName() const;

private:
    TL1_SmartParameter<uint32> itsNeighborIp;
    TL1_SmartParameter<CT_Adj_Status> itsAdjacencyStatus;
    TL1_SmartParameter<CT_IfNumber> itsIfName;
};

typedef TL1_Rtv_Response< TL1_AdjRouterRspBlk > TL1_AdjRouterResponse;

#endif


