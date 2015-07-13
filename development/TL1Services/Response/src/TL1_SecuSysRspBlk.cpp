/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.
 
SUBSYSTEM:      TL1 
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Source file for TL1 Retrive System Security Response
-----------------------------------------------------------------------------*/

#include <Response/TL1_SecuSysRspBlk.h>


TL1_SecuSysRspBlk::TL1_SecuSysRspBlk(
    const TL1_SmartParameter<int>&  theLoginTries,                             
    const TL1_SmartParameter<int>&  theSuspensionDuration,
    const TL1_SmartParameter<int>&  thePasswordCount,
    const TL1_SmartParameter<bool>& thePwdCompl,
    const TL1_SmartParameter<bool>& theInvalidUIDNotLogged,
    const TL1_SmartParameter<int>&  theInactivityTimeout,
    const TL1_SmartParameter<int>&  theWarningPeriod,
    CT_SecureMode                   theSecureMode )

    :itsLoginTries(theLoginTries)
    ,itsSuspensionDuration(theSuspensionDuration)
    ,itsPasswordCount(thePasswordCount)
	,itsPwdCompl(thePwdCompl)
    ,itsInvalidUIDNotLogged(theInvalidUIDNotLogged)
    ,itsInactivityTimeout(theInactivityTimeout)
    ,itsWarningPeriod(theWarningPeriod)
    ,itsSecureMode(theSecureMode)
{
}

TL1_SecuSysRspBlk::~TL1_SecuSysRspBlk()
{
}
  
TL1_SecuSysRspBlk::TL1_SecuSysRspBlk(const TL1_SecuSysRspBlk& theBlock)

    :itsLoginTries(theBlock.itsLoginTries)
    ,itsSuspensionDuration(theBlock.itsSuspensionDuration)
    ,itsPasswordCount(theBlock.itsPasswordCount)
	,itsPwdCompl(theBlock.itsPwdCompl)
    ,itsInvalidUIDNotLogged(theBlock.itsInvalidUIDNotLogged)
    ,itsInactivityTimeout(theBlock.itsInactivityTimeout)
    ,itsWarningPeriod(theBlock.itsWarningPeriod)
    ,itsSecureMode(theBlock.itsSecureMode)
{
}

TL1_SecuSysRspBlk& TL1_SecuSysRspBlk::operator=( const TL1_SecuSysRspBlk& theBlock )
{
    itsLoginTries           = theBlock.itsLoginTries;
    itsSuspensionDuration   = theBlock.itsSuspensionDuration;
    itsPasswordCount        = theBlock.itsPasswordCount;
	itsPwdCompl             = theBlock.itsPwdCompl;
    itsInvalidUIDNotLogged  = theBlock.itsInvalidUIDNotLogged;
    itsInactivityTimeout    = theBlock.itsInactivityTimeout;
    itsWarningPeriod        = theBlock.itsWarningPeriod;
    itsSecureMode           = theBlock.itsSecureMode;

    return *this;
}
