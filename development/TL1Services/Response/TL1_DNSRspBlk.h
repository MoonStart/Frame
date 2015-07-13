/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive DNS Response Class
TARGET:
AUTHOR:         Jun 5, 2003- Stephen Wu
DESCRIPTION:    Header file for TL1 Retrive DNS Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DNSRSPBLK_H_
#define __TL1_DNSRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#include <ss_gdef.h>

#include <vector>

using namespace std;


class TL1_DNSRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_DNSRspBlk() {};
    
    TL1_DNSRspBlk(const TL1_DNSRspBlk& );

    TL1_DNSRspBlk( const TL1_SmartParameter<string>& theTid,
                   const TL1_SmartParameter<uint32>& theIPAddress,
                   const TL1_SmartParameter<bool>& theRneMode);
    
    virtual ~TL1_DNSRspBlk();

    TL1_DNSRspBlk& operator=( const TL1_DNSRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetTid() const
    {
        return itsTid;
    }

    const TL1_SmartParameter<uint32>& 
        GetIPAddress() const
    {
        return itsIPAddress;
    }

    const TL1_SmartParameter<bool>& 
        GetRneMode() const
    {
        return itsRneMode;
    }

private:

	TL1_SmartParameter<string>     itsTid;
	TL1_SmartParameter<uint32>     itsIPAddress;
	TL1_SmartParameter<bool>       itsRneMode;
};

typedef TL1_Rtv_Response< TL1_DNSRspBlk > TL1_DNSResponse;

#endif


