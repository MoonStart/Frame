/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         Nov. 12, 2003- Stevens Gerber
DESCRIPTION:    Header for Retreive System Security Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SECUSYSRSPBLK_H_
#define __TL1_SECUSYSRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#include <CommonTypes/CT_SystemIds.h>

#include <vector>

using namespace std;

class TL1_SecuSysRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SecuSysRspBlk() {}
    
    TL1_SecuSysRspBlk(const TL1_SecuSysRspBlk& );

    TL1_SecuSysRspBlk(const TL1_SmartParameter<int>&  theLoginTries,
                      const TL1_SmartParameter<int>&  theSuspensionDuration,
                      const TL1_SmartParameter<int>&  thePasswordCount,
					  const TL1_SmartParameter<bool>& thePwdCompl,
                      const TL1_SmartParameter<bool>& theInvalidUIDNotLogged,
                      const TL1_SmartParameter<int>&  theInactivityTimeout,
                      const TL1_SmartParameter<int>&  theWarningPeriod,
                      CT_SecureMode                   theSecureMode );
                 
    virtual ~TL1_SecuSysRspBlk();

    TL1_SecuSysRspBlk& operator=( const TL1_SecuSysRspBlk& theBlock );

    const TL1_SmartParameter<int>&
        GetInactivityTimeout() const
    {
        return itsInactivityTimeout;
    }

    const TL1_SmartParameter<int>&
        GetWarningPeriod() const
    {
        return itsWarningPeriod;
    }

    const TL1_SmartParameter<int>& 
        GetLoginTries() const
    {
        return itsLoginTries;
    }

    const TL1_SmartParameter<int>& 
        GetSuspensionDuration() const
    {
        return itsSuspensionDuration;
    }

    const TL1_SmartParameter<int>& 
        GetPasswordCount() const
    {
        return itsPasswordCount;
    }

	const TL1_SmartParameter<bool>&
		GetPwdCompl() const
	{
		return itsPwdCompl;
	}

	const TL1_SmartParameter<bool>&
		GetInvalidUIDNotLogged() const
	{
		return itsInvalidUIDNotLogged;
	}

    CT_SecureMode GetSecureMode( ) const
    {
        return itsSecureMode;
    }


private:

    TL1_SmartParameter<int>     itsLoginTries;
    TL1_SmartParameter<int>     itsSuspensionDuration;
    TL1_SmartParameter<int>     itsPasswordCount;
    TL1_SmartParameter<int>     itsWarningPeriod;
    TL1_SmartParameter<int>     itsInactivityTimeout;
	TL1_SmartParameter<bool>    itsPwdCompl;
	TL1_SmartParameter<bool>    itsInvalidUIDNotLogged;
    CT_SecureMode               itsSecureMode;
};

typedef TL1_Rtv_Response< TL1_SecuSysRspBlk > TL1_SecuSysResponse;

#endif



