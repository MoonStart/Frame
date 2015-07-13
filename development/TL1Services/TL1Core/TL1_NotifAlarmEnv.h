/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Nov 14, 2003- Christian Halle 
DESCRIPTION:    Header file for TL1 Notification Observer If declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFALARMENV_H__
#define __TL1_NOTIFALARMENV_H__

#ifndef __TL1_NOTIFICATION_H__
#include <TL1Core/TL1_Notification.h>
#endif

#include <gdef.h>

class TL1_GeneralRspBlk;

class TL1_NotifAlarmEnv : public TL1_Notification
{
public:
    TL1_NotifAlarmEnv( const TL1_Response& theResponse );

    virtual ~TL1_NotifAlarmEnv();
};

#endif
