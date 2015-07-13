/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Source file for TL1 Retrieve Router Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_RouterRspBlk.h>


TL1_RouterRspBlk::TL1_RouterRspBlk( const TL1_SmartParameter<uint32>& theRouterIp,
                                    const TL1_SmartParameter<bool>& theASBR,
                                    const TL1_SmartParameter<string>& theOspfVersion,
                                    const TL1_SmartParameter<uint32>& theAreaId,
									const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile,
                                    const TL1_SmartParameter<CT_SM_State>& theRouterState ) :
    itsRouterIp(theRouterIp),
    itsASBR(theASBR),
    itsOspfVersion(theOspfVersion),
    itsAreaId(theAreaId),
	itsAlarmProfile(theAlarmProfile),
    itsRouterState(theRouterState)
{
}

TL1_RouterRspBlk::~TL1_RouterRspBlk()
{
}
  
TL1_RouterRspBlk::TL1_RouterRspBlk( const TL1_RouterRspBlk& theBlock ) :
    itsRouterIp(theBlock.itsRouterIp),
    itsASBR(theBlock.itsASBR),
    itsOspfVersion(theBlock.itsOspfVersion),
    itsAreaId(theBlock.itsAreaId),
	itsAlarmProfile(theBlock.itsAlarmProfile),
    itsRouterState(theBlock.itsRouterState)
{
}

TL1_RouterRspBlk& TL1_RouterRspBlk::operator=( const TL1_RouterRspBlk& theBlock )
{
    itsRouterIp = theBlock.itsRouterIp;
    itsASBR = theBlock.itsASBR;
    itsOspfVersion = theBlock.itsOspfVersion;
    itsAreaId = theBlock.itsAreaId;
	itsAlarmProfile = theBlock.itsAlarmProfile;
    itsRouterState = theBlock.itsRouterState;

    return *this;
}

const TL1_SmartParameter<uint32>& TL1_RouterRspBlk::GetRouterIp() const
{
    return itsRouterIp;
}

const TL1_SmartParameter<bool>& TL1_RouterRspBlk::GetASBR() const
{
    return itsASBR;
}

const TL1_SmartParameter<string>& TL1_RouterRspBlk::GetOspfVersion() const
{
    return itsOspfVersion;
}

const TL1_SmartParameter<uint32>& TL1_RouterRspBlk::GetAreaId() const
{
    return itsAreaId;
}

const TL1_SmartParameter<CT_ProfileTableId>& TL1_RouterRspBlk::GetAlmpf() const
{
    return itsAlarmProfile;
}

const TL1_SmartParameter<CT_SM_State>& TL1_RouterRspBlk::GetRouterState() const
{
    return itsRouterState;
}

