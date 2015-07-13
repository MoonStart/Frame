/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive NET Response Class
TARGET:
AUTHOR:         Jun 5, 2003- Stephen Wu
DESCRIPTION:    Header file for TL1 Retrive NET Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NETRSPBLK_H_
#define __TL1_NETRSPBLK_H_

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

using namespace std;


class TL1_NETRspBlk : public TL1_GeneralRspBlk
{
public: 
    TL1_NETRspBlk() {};
    
    TL1_NETRspBlk(const TL1_NETRspBlk& );

    TL1_NETRspBlk( const TL1_SmartParameter<CT_EONType>& theEONType,
                   const TL1_SmartParameter<CT_EONState>& theEONState,
                   const TL1_SmartParameter<uint32>& theLocalIf,
                   const TL1_SmartParameter<uint32>& theLocalIfMask,
                   const TL1_SmartParameter<uint32>& theManageIf,
                   const TL1_SmartParameter<uint32>& theManageIfMask,
                   const TL1_SmartParameter<uint32>& theRouterIf,
                   const TL1_SmartParameter<uint32>& theRouterIfMask,
                   const TL1_SmartParameter<uint32>& theDCNIf,
                   const TL1_SmartParameter<uint32>& theDCNIfMask,
                   const TL1_SmartParameter<CT_IfSpeed>&  theDcnIfSpeed,
                   const TL1_SmartParameter<CT_IfDuplex>& theDcnIfDuplex,
                   const TL1_SmartParameter<uint32>& theGNEIf,
                   const TL1_SmartParameter<uint32>& theGNEIfMask,
                   const TL1_SmartParameter<uint32>& theGateway,
                   const TL1_SmartParameter<bool>&   theDhcpClient,
                   const TL1_SmartParameter<string>& theIpSubnet,
                   const TL1_SmartParameter<string>& theNESubnet,
                   const TL1_SmartParameter<bool>&   theRadClient,
                   const TL1_SmartParameter<uint32>& theRadIter,
                   const TL1_SmartParameter<uint32>& theRadTmout,
                   const TL1_SmartParameter<bool>&   theNatDcn,
                   const TL1_SmartParameter<uint32>& thePrimaryGNE,
                   const TL1_SmartParameter<uint32>& theSecondaryGNE,
                   const TL1_SmartParameter<CT_NM_ROUTING_CONFIG>& theDcnRoutingConfig);
    
    virtual ~TL1_NETRspBlk();

    TL1_NETRspBlk& operator=( const TL1_NETRspBlk& theBlock );

    const TL1_SmartParameter<CT_EONType>& 
        GetEONType() const
    {
        return itsEONType;
    }

    const TL1_SmartParameter<CT_EONState>& 
        GetEONState() const
    {
        return itsEONState;
    }

    const TL1_SmartParameter<uint32>& 
        GetLocalIf() const
    {
        return itsLocalIf;
    }

    const TL1_SmartParameter<uint32>& 
        GetLocalIfMask() const
    {
        return itsLocalIfMask;
    }
    const TL1_SmartParameter<uint32>& 
        GetManageIf() const
    {
        return itsManageIf;
    }

    const TL1_SmartParameter<uint32>& 
        GetManageIfMask() const
    {
        return itsManageIfMask;
    }

    const TL1_SmartParameter<uint32>& 
        GetRouterIf() const
    {
        return itsRouterIf;
    }

    const TL1_SmartParameter<uint32>& 
        GetRouterIfMask() const
    {
        return itsRouterIfMask;
    }

        const TL1_SmartParameter<uint32>& 
        GetDCNIf() const
    {
        return itsDCNIf;
    }

        const TL1_SmartParameter<uint32>& 
        GetDCNIfMask() const
    {
        return itsDCNIfMask;
    }
    const TL1_SmartParameter<CT_IfSpeed>& 
        GetDCNIfSpeed() const
    {
        return itsDCNIfSpeed;
    }
    const TL1_SmartParameter<CT_IfDuplex>& 
        GetDCNIfDuplex() const
    {
        return itsDCNIfDuplex;
    }
    const TL1_SmartParameter<uint32>& 
        GetGNEIf() const
    {
        return itsGNEIf;
    }

    const TL1_SmartParameter<uint32>& 
        GetGNEIfMask() const
    {
        return itsGNEIfMask;
    }

    const TL1_SmartParameter<uint32>& 
        GetGateway() const
    {
        return itsGateway;
    }

    const TL1_SmartParameter<bool>& 
        GetDhcpClient() const
    {
        return itsDhcpClient;
    }

    const TL1_SmartParameter<string>&
        GetIpSubnet() const
    {
        return itsIpSubnet;
    }


    const TL1_SmartParameter<string>&
        GetNESubnet() const
    {
        return itsNESubnet;
    }

    const TL1_SmartParameter<bool>& 
        GetRadClient() const
    {
        return itsRadClient;
    }

    const TL1_SmartParameter<uint32>& 
        GetRadIter() const
    {
        return itsRadIter;
    }

    const TL1_SmartParameter<uint32>& 
        GetRadTmout() const
    {
        return itsRadTmout;
    }

    const TL1_SmartParameter<bool>& 
        GetDcnNat() const
    {
        return itsDcnNat;
    }

    const TL1_SmartParameter<uint32>& 
        GetPriGneAddr() const
    {
        return itsPriGneAddr;
    }

    const TL1_SmartParameter<uint32>& 
        GetSecGneAddr() const
    {
        return itsSecGneAddr;
    }

    const TL1_SmartParameter<CT_NM_ROUTING_CONFIG>& 
        GetDcnRoutingConfig() const
    {
        return itsDcnRoutingConfig;
    }


private:

    TL1_SmartParameter<CT_EONType> itsEONType;
    TL1_SmartParameter<CT_EONState> itsEONState;
    TL1_SmartParameter<uint32>     itsLocalIf;
    TL1_SmartParameter<uint32>     itsLocalIfMask;
    TL1_SmartParameter<uint32>     itsManageIf;
    TL1_SmartParameter<uint32>     itsManageIfMask;
    TL1_SmartParameter<uint32>     itsRouterIf;
    TL1_SmartParameter<uint32>     itsRouterIfMask;
    TL1_SmartParameter<uint32>     itsDCNIf;
    TL1_SmartParameter<uint32>     itsDCNIfMask;
    TL1_SmartParameter<CT_IfSpeed> itsDCNIfSpeed;
    TL1_SmartParameter<CT_IfDuplex> itsDCNIfDuplex;
    TL1_SmartParameter<uint32>     itsGNEIf;
    TL1_SmartParameter<uint32>     itsGNEIfMask;
    TL1_SmartParameter<uint32>     itsGateway;
    TL1_SmartParameter<bool>       itsDhcpClient;
    TL1_SmartParameter<string>     itsIpSubnet;
    TL1_SmartParameter<string>     itsNESubnet;
    TL1_SmartParameter<bool>       itsRadClient;
    TL1_SmartParameter<uint32>     itsRadIter;
    TL1_SmartParameter<uint32>     itsRadTmout;
    TL1_SmartParameter<bool>       itsDcnNat;
    TL1_SmartParameter<uint32>     itsPriGneAddr;
    TL1_SmartParameter<uint32>     itsSecGneAddr;
    TL1_SmartParameter<CT_NM_ROUTING_CONFIG> itsDcnRoutingConfig;
};

typedef TL1_Rtv_Response< TL1_NETRspBlk > TL1_NETResponse;

#endif


