/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 12, 2003- Mathieu Lavoie
DESCRIPTION:    Header file for TL1 Backup result Notification
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFBCKUP_H__
#define __TL1_NOTIFBCKUP_H__

#ifndef __TL1_NOTIFICATION_H__
#include <TL1Core/TL1_Notification.h>
#endif

#include <gdef.h>
#include <time.h>

class TL1_GeneralRspBlk;

class TL1_NotifBckup : public TL1_Notification
{
public:
    TL1_NotifBckup( const TL1_Response& theResponse );

    virtual ~TL1_NotifBckup();

};

#endif
