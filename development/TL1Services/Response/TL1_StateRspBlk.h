/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 7, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Report remove restore response block
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_STATERSPBLK_H__
#define __TL1_STATERSPBLK_H__

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

#ifndef _CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef CT_NTPTYPES_H
#include <CommonTypes/CT_NtpTypes.h>
#endif

#ifndef CT_EVCDATA_H
#include <CommonTypes/CT_EvcData.h>
#endif

#ifndef CT_TL1_CONTROLPLANEADDR_H
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#include <vector>

using namespace std;

#include <CommonTypes/CT_TL1_EvcAddr.h>


class TL1_StateRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_StateRspBlk(){}

    TL1_StateRspBlk( const TL1_StateRspBlk& theBlock );

	TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

	TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_CrsAddr >& theCrsAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_ProtnAddr >& theProtnAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_LogicalAddr >& theNtpAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_RpMapAddr >& theRpMapAddr );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_RpAddr >& theRpAddr );
  
    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_NetworkPartitionAddr >& theNpAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_NodeAddr >& theNodeAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_DiscoveryAgentAddr >& theDaAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_LinkAddr >& theLinkAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_ControllerAddr >& theControllerAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

	TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_AdjacencyAddr >& theAdjacencyAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

	TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_TL1_AreaAddr >& theAreaAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_EvcData >& theEvcAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                     const TL1_SmartParameter< CT_SwitchDomain >& theSwitchDomainAddr,
                     const TL1_SmartParameter< CT_SM_PST >& thePST,
                     const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                     const TL1_SmartParameter< CT_SM_SST >& theSST );

    TL1_StateRspBlk( const TL1_SmartParameter< string >& theFtpServer );
    virtual ~TL1_StateRspBlk();

    TL1_StateRspBlk& operator=( const TL1_StateRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter< string >&
        GetFtpServer() const
    {
        return itsFtpServer;
    }

    const TL1_SmartParameter< CT_TL1_SlotAddr >&
        GetSlotAddr() const
    {
        return itsSlotAddr;
    }

    const TL1_SmartParameter< CT_TL1_FacAddr >&
        GetFacAddr() const
    {
        return itsFacAddr;
    }

    const TL1_SmartParameter< CT_TL1_CrsAddr >&
        GetCrsAddr() const
    {
        return itsCrsAddr;
    }

    const TL1_SmartParameter< CT_EvcData >&
        GetEvcAddr() const
    {
        return itsEvcAddr;
    }

    const TL1_SmartParameter< CT_TL1_ProtnAddr >&
        GetProtnAddr() const
    {
        return itsProtnAddr;
    }

    const TL1_SmartParameter< CT_TL1_LogicalAddr >&
        GetNtpAddr() const
    {
        return itsNtpAddr;
    }

    const TL1_SmartParameter< CT_TL1_RpMapAddr >&
        GetRpMapAddr() const
    {
        return itsRpMapAddr;
    }

    const TL1_SmartParameter< CT_TL1_RpAddr >&
        GetRpAddr() const
    {
        return itsRpAddr;
    }

    const TL1_SmartParameter< CT_TL1_NetworkPartitionAddr >&
        GetNetworkPartitionAddr() const
    {
        return itsNpAddr;
    }

    const TL1_SmartParameter< CT_TL1_NodeAddr >&
        GetNodeAddr() const
    {
        return itsNodeAddr;
    }

    const TL1_SmartParameter< CT_TL1_DiscoveryAgentAddr >&
        GetDaAddr() const
    {
        return itsDaAddr;
    }

    const TL1_SmartParameter< CT_TL1_LinkAddr >&
        GetLinkAddr() const
    {
        return itsLinkAddr;
    }

    const TL1_SmartParameter< CT_TL1_ControllerAddr >&
        GetControllerAddr() const
    {
        return itsControllerAddr;
    }

	const TL1_SmartParameter< CT_TL1_AdjacencyAddr >&
        GetAdjacencyAddr() const
    {
        return itsAdjacencyAddr;
    }

	const TL1_SmartParameter< CT_TL1_AreaAddr >&
        GetAreaAddr() const
    {
        return itsAreaAddr;
    }

    const TL1_SmartParameter< CT_SwitchDomain >&
        GetSwitchDomainAddr() const
    {
        return itsSwitchDomainAddr;
    }

    const TL1_SmartParameter< CT_SM_PST >&
        GetPST() const
    {
        return itsPST;
    }

    const TL1_SmartParameter< CT_SM_PSTQ >&
        GetPSTQ() const
    {
        return itsPSTQ;
    }

    const TL1_SmartParameter< CT_SM_SST >&
        GetSST() const
    {
        return itsSST;
    }

private:
    TL1_SmartParameter< string >                         itsEntityName;
    TL1_SmartParameter< string >                         itsFtpServer;
    TL1_SmartParameter< CT_TL1_SlotAddr >                itsSlotAddr;
    TL1_SmartParameter< CT_TL1_FacAddr >                 itsFacAddr;
    TL1_SmartParameter< CT_TL1_CrsAddr >                 itsCrsAddr;
    TL1_SmartParameter< CT_EvcData >                         itsEvcAddr;
    TL1_SmartParameter< CT_TL1_ProtnAddr >               itsProtnAddr;
    TL1_SmartParameter< CT_TL1_LogicalAddr >             itsNtpAddr;
    TL1_SmartParameter< CT_TL1_RpMapAddr >               itsRpMapAddr;
    TL1_SmartParameter< CT_TL1_RpAddr >                  itsRpAddr;
    TL1_SmartParameter< CT_TL1_NetworkPartitionAddr >    itsNpAddr;
    TL1_SmartParameter< CT_TL1_NodeAddr >                itsNodeAddr;
    TL1_SmartParameter< CT_TL1_DiscoveryAgentAddr >      itsDaAddr;
    TL1_SmartParameter< CT_TL1_LinkAddr >                itsLinkAddr;
    TL1_SmartParameter< CT_TL1_ControllerAddr >          itsControllerAddr;
    TL1_SmartParameter< CT_TL1_AdjacencyAddr >	         itsAdjacencyAddr;
    TL1_SmartParameter< CT_TL1_AreaAddr >                itsAreaAddr;
    TL1_SmartParameter< CT_SwitchDomain >                itsSwitchDomainAddr;
    TL1_SmartParameter< CT_SM_PST >                      itsPST;
    TL1_SmartParameter< CT_SM_PSTQ >                     itsPSTQ;
    TL1_SmartParameter< CT_SM_SST >                      itsSST;
};


typedef TL1_Rtv_Response< TL1_StateRspBlk > TL1_ReportStateResponse;


#endif
