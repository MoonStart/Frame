/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 8, 2003- Christian Halle 
DESCRIPTION:    Header file for TL1 report event session 
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFEVTSESSION_H__
#define __TL1_NOTIFEVTSESSION_H__

#ifndef __TL1_NOTIFICATION_H__
#include <TL1Core/TL1_Notification.h>
#endif

#include <gdef.h>
#include <time.h>

class TL1_GeneralRspBlk;

class TL1_NotifEvtSession : public TL1_Notification
{
public:
    TL1_NotifEvtSession( const TL1_Response& theResponse );

    virtual ~TL1_NotifEvtSession();

};

#endif //__TL1_NOTIFEVTSESSION_H__
