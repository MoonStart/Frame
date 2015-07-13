/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Retrieve IF Router Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IFROUTERRSPBLK_H_
#define __TL1_IFROUTERRSPBLK_H_

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

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif


class TL1_IfRouterRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IfRouterRspBlk() {}
    
    TL1_IfRouterRspBlk( const TL1_IfRouterRspBlk& );

    TL1_IfRouterRspBlk( const TL1_SmartParameter<CT_IfNumber>& theIfName,
                        const TL1_SmartParameter<CT_InterfaceType>& theIfType,
                        const TL1_SmartParameter<CT_InterfaceMode>& theIfMode,
                        const TL1_SmartParameter<CT_InterfaceState>& theIfState,
                        const TL1_SmartParameter<uint32>& theHelloInt,
                        const TL1_SmartParameter<uint32>& theRouterDeadInterval,
                        const TL1_SmartParameter<uint32>& theLinkCost,
                        const TL1_SmartParameter<bool>& theSWstatus,
                        const TL1_SmartParameter<bool>& thePSstatus);
    
    virtual ~TL1_IfRouterRspBlk();

    TL1_IfRouterRspBlk& operator=( const TL1_IfRouterRspBlk& theBlock );

    const TL1_SmartParameter<CT_IfNumber>& GetIfName() const;

    const TL1_SmartParameter<CT_InterfaceType>& GetIfType() const;

    const TL1_SmartParameter<CT_InterfaceMode>& GetIfMode() const;

    const TL1_SmartParameter<CT_InterfaceState>& GetIfState() const;

    const TL1_SmartParameter<uint32>& GetHelloInt() const;

    const TL1_SmartParameter<uint32>& GetRouterDeadInterval() const;

    const TL1_SmartParameter<uint32>& GetLinkCost() const;

    const TL1_SmartParameter<bool>& GetSWstatus() const;

    const TL1_SmartParameter<bool>& GetPSstatus() const;

private:
    TL1_SmartParameter<CT_IfNumber> itsIfName;
    TL1_SmartParameter<CT_InterfaceType> itsIfType;
    TL1_SmartParameter<CT_InterfaceMode> itsIfMode;
    TL1_SmartParameter<CT_InterfaceState> itsIfState;
    TL1_SmartParameter<uint32> itsHelloInt;
    TL1_SmartParameter<uint32> itsRouterDeadInterval;
    TL1_SmartParameter<uint32> itsLinkCost;
    TL1_SmartParameter<bool> itsSWstatus;
    TL1_SmartParameter<bool> itsPSstatus;
};

typedef TL1_Rtv_Response< TL1_IfRouterRspBlk > TL1_IfRouterResponse;

#endif


