/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Report event session Response Class
TARGET:
AUTHOR:         July 8, 2003- Christian Halle 
DESCRIPTION:    Header file for TL1 report event session Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EVTSESSIONRSPBLK_H_
#define __TL1_EVTSESSIONRSPBLK_H_

#ifndef __CT_TL1_SYSTREM_H_
#include <CommonTypes/CT_TL1_System.h>
#endif

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#include <ss_gdef.h>

#include <vector>
#include <string>

using namespace std;


class TL1_EvtSessionRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_EvtSessionRspBlk() {};
    
    TL1_EvtSessionRspBlk(const TL1_EvtSessionRspBlk& );

    TL1_EvtSessionRspBlk( const TL1_SmartParameter<string>& theTid,
                          const TL1_SmartParameter<string>& theUserId,
                          const TL1_SmartParameter<CT_TL1_LoginStatus>& theLoginStatus,
#if defined VXWORKS67 || defined LINUX
                          const TL1_SmartParameter<string>& theSessionIPAddress,
#else
                          const TL1_SmartParameter<uint32>& theSessionIPAddress,
#endif
						  const TL1_SmartParameter<time_t>& theTime);
    
    virtual ~TL1_EvtSessionRspBlk();

    TL1_EvtSessionRspBlk& operator=( const TL1_EvtSessionRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetTid() const
    {
        return itsTid;
    }

    const TL1_SmartParameter<string>& 
        GetUserId() const
    {
        return itsUserId;
    }

    const TL1_SmartParameter<CT_TL1_LoginStatus>& 
        GetLoginStatus() const
    {
        return itsLoginStatus;
    }
#if defined VXWORKS67 || defined LINUX
    const TL1_SmartParameter<string>& GetSessionIPAddress() const
    {
        return itsSessionIPAddress;
    }
#else
    const TL1_SmartParameter<uint32>& GetSessionIPAddress() const
	{
		return itsSessionIPAddress;
	}
#endif        
	const TL1_SmartParameter<time_t>& 
        GetTime() const
    {
        return itsTime;
    }

private:

    TL1_SmartParameter<string>                  itsTid;
    TL1_SmartParameter<string>                  itsUserId;
    TL1_SmartParameter<CT_TL1_LoginStatus>      itsLoginStatus;
#if defined VXWORKS67 || defined LINUX
    TL1_SmartParameter<string>                  itsSessionIPAddress;
#else
	TL1_SmartParameter<uint32>					itsSessionIPAddress;
#endif
    TL1_SmartParameter<time_t>                  itsTime;
};

typedef TL1_Rtv_Response< TL1_EvtSessionRspBlk > TL1_EvtSessionResponse;

#endif


