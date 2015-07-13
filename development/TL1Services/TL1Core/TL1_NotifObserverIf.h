/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 26, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Observer If declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFOBSERVERIF_H__
#define __TL1_NOTIFOBSERVERIF_H__

class TL1_Notification;

class TL1_NotifObserverIf
{
public:
    virtual void ProcessNotification( const TL1_Notification& theNotif ) = 0;
};

#endif
