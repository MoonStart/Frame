/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         July 8, 2003- Christian Halle 
DESCRIPTION:    Implementation file for TL1 report evebt session Notification
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_NotifEvtSession.h>

#include <TL1Core/TL1_NotifCenter.h>

TL1_NotifEvtSession::TL1_NotifEvtSession( const TL1_Response& theResponse ) :
    TL1_Notification( EVT_SESSION, theResponse)
{
}

TL1_NotifEvtSession::~TL1_NotifEvtSession()
{
}
