/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Retrieve Router Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ROUTERRSPBLK_H__
#define __TL1_ROUTERRSPBLK_H__

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

#ifndef _CT_AM_DEFINITIONS_H_
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif


class TL1_RouterRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RouterRspBlk() {}
    
    TL1_RouterRspBlk( const TL1_RouterRspBlk& );

    TL1_RouterRspBlk( const TL1_SmartParameter<uint32>& theRouterIp,
                      const TL1_SmartParameter<bool>& theASBR,
                      const TL1_SmartParameter<string>& theOspfVersion,
                      const TL1_SmartParameter<uint32>& theAreaId,
					  const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile,
                      const TL1_SmartParameter<CT_SM_State>& theRouterState );
    
    virtual ~TL1_RouterRspBlk();

    TL1_RouterRspBlk& operator=( const TL1_RouterRspBlk& theBlock );

    const TL1_SmartParameter<uint32>& GetRouterIp() const;

    const TL1_SmartParameter<bool>& GetASBR() const;

    const TL1_SmartParameter<string>& GetOspfVersion() const;

    const TL1_SmartParameter<uint32>& GetAreaId() const;

	const TL1_SmartParameter<CT_ProfileTableId>& GetAlmpf() const;

    const TL1_SmartParameter<CT_SM_State>& GetRouterState() const;

private:
    TL1_SmartParameter<uint32> itsRouterIp;
    TL1_SmartParameter<bool> itsASBR;
    TL1_SmartParameter<string> itsOspfVersion;
    TL1_SmartParameter<uint32> itsAreaId;
	TL1_SmartParameter<CT_ProfileTableId> itsAlarmProfile;
    TL1_SmartParameter<CT_SM_State> itsRouterState;
};

typedef TL1_Rtv_Response< TL1_RouterRspBlk > TL1_RouterResponse;

#endif


