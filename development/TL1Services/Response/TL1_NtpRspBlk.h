/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive NTP Response Class
TARGET:
AUTHOR:         June 11, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Retrive NTP Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NTPRSPBLK_H_
#define __TL1_NTPRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_NTPTYPES_H_
#include <CommonTypes/CT_NtpTypes.h>
#endif

#ifndef __CT_TL1_BASE_H_
#include <CommonTypes/CT_TL1_Base.h>
#endif

#include <vector>

using namespace std;

class TL1_NtpRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_NtpRspBlk();
    
    TL1_NtpRspBlk(const TL1_NtpRspBlk& );

    TL1_NtpRspBlk( const TL1_SmartParameter<string>&             theEntityName,
                   const TL1_SmartParameter<CT_TL1_LogicalAddr>& theNtpAddr,
                   const TL1_SmartParameter<string>&             thePeerIP,
                   const TL1_SmartParameter<string>&             thePeerDescription,
                   const TL1_SmartParameter<int>&                theVersion,
                   const TL1_SmartParameter<int>&                thePort,
                   const TL1_SmartParameter<CT_NtpMode>&         theHostMode,
                   const TL1_SmartParameter<uint16>&             thePollingInterval,
                   const TL1_SmartParameter<uint8>&              theStratum,
                   const TL1_SmartParameter<float>&              thePrecision,
                   const TL1_SmartParameter<bool>&               theReachability,
                   const TL1_SmartParameter<float>&              theDelay,
                   const TL1_SmartParameter<float>&              theDispersion,
                   const TL1_SmartParameter<float>&              theRootDelay,
                   const TL1_SmartParameter<float>&              theRootDispersion,
                   const TL1_SmartParameter<CT_SM_PST>&          thePst,
                   const TL1_SmartParameter<CT_SM_PSTQ>&         thePstq,
                   const TL1_SmartParameter<CT_SM_SST>&          theSst,
                   const TL1_SmartParameter<CT_NtpPeerConfigType>& thePeerConfigMode);
                 
    
    virtual ~TL1_NtpRspBlk();

    TL1_NtpRspBlk& operator=( const TL1_NtpRspBlk& theBlock );

    bool operator==( const TL1_NtpRspBlk& theBlock );
    bool operator!=( const TL1_NtpRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter<CT_TL1_LogicalAddr>& 
        GetNtpAddr() const
    {
        return itsNtpAddr;
    }

    const TL1_SmartParameter<string>& 
        GetPeerIP() const
    {
        return itsPeerIP;
    }

    const TL1_SmartParameter<string>& 
        GetPeerDescription() const
    {
        return itsPeerDescription;
    }

    const TL1_SmartParameter<int>& 
        GetVersion() const
    {
        return itsVersion;
    }

    const TL1_SmartParameter<int>& 
        GetPort() const
    {
        return itsPort;
    }

    const TL1_SmartParameter<CT_NtpMode>& 
        GetHostMode() const
    {
        return itsHostMode;
    }

    const TL1_SmartParameter<uint16>& 
        GetPollingInterval() const
    {
        return itsPollingInterval;
    }

    const TL1_SmartParameter<uint8>& 
        GetStratum() const
    {
        return itsStratum;
    }

    const TL1_SmartParameter<float>& 
        GetPrecision() const
    {
        return itsPrecision;
    }

    const TL1_SmartParameter<bool>& 
        GetReachability() const
    {
        return itsReachability;
    }

    const TL1_SmartParameter<float>& 
        GetDelay() const
    {
        return itsDelay;
    }

    const TL1_SmartParameter<float>& 
        GetDispersion() const
    {
        return itsDispersion;
    }

    const TL1_SmartParameter<float>& 
        GetRootDelay() const
    {
        return itsRootDelay;
    }

    const TL1_SmartParameter<float>& 
        GetRootDispersion() const
    {
        return itsRootDispersion;
    }

    const TL1_SmartParameter<CT_SM_PST>& 
        GetPst() const
    {
        return itsPst;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>& 
        GetPstq() const
    {
        return itsPstq;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSst() const
    {
        return itsSst;
    }

    const TL1_SmartParameter<CT_NtpPeerConfigType>& 
        GetPeerConfigMode() const
    {
        return itsPeerConfigMode;
    }


private:

    TL1_SmartParameter<string>             itsEntityName;
    TL1_SmartParameter<CT_TL1_LogicalAddr> itsNtpAddr;
    TL1_SmartParameter<string>             itsPeerIP;
    TL1_SmartParameter<string>             itsPeerDescription;
    TL1_SmartParameter<int>                itsVersion;
    TL1_SmartParameter<int>                itsPort;
    TL1_SmartParameter<CT_NtpMode>         itsHostMode;
    TL1_SmartParameter<uint16>             itsPollingInterval;
    TL1_SmartParameter<uint8>              itsStratum;
    TL1_SmartParameter<float>              itsPrecision;
    TL1_SmartParameter<bool>               itsReachability;
    TL1_SmartParameter<float>              itsDelay;
    TL1_SmartParameter<float>              itsDispersion;
    TL1_SmartParameter<float>              itsRootDelay;
    TL1_SmartParameter<float>              itsRootDispersion;
    TL1_SmartParameter<CT_SM_PST>          itsPst;
    TL1_SmartParameter<CT_SM_PSTQ>         itsPstq;
    TL1_SmartParameter<CT_SM_SST>          itsSst;
    TL1_SmartParameter<CT_NtpPeerConfigType> itsPeerConfigMode;
};

typedef TL1_Rtv_Response< TL1_NtpRspBlk > TL1_NtpResponse;

#endif



