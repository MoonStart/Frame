/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Nov 14, 2003- Christian Halle 
DESCRIPTION:    Header file for TL1 Notification Base implementation
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_NotifAlarmEnv.h>

#include <TL1Core/TL1_NotifCenter.h>

TL1_NotifAlarmEnv::TL1_NotifAlarmEnv( const TL1_Response& theResponse ) :
TL1_Notification( TL1_Notification::ALMENV, theResponse)
{
}

TL1_NotifAlarmEnv::~TL1_NotifAlarmEnv()
{
}
