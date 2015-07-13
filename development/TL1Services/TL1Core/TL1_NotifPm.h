/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 28, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Notification Observer declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFPM_H__
#define __TL1_NOTIFPM_H__

#ifndef __TL1_NOTIFICATION_H__
#include <TL1Core/TL1_Notification.h>
#endif

#include <gdef.h>

class TL1_Response;

class TL1_NotifPm : public TL1_Notification
{
public:
    TL1_NotifPm( const TL1_Response& theResponse);

    virtual ~TL1_NotifPm();

};

#endif //__TL1_NOTIFPM_H__
