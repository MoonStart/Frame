/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 12, 2003- Mathieu Lavoie
DESCRIPTION:    Implementation file for TL1 Backup result Notification
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_NotifBckup.h>

#include <TL1Core/TL1_NotifCenter.h>

TL1_NotifBckup::TL1_NotifBckup( const TL1_Response& theResponse ) :
    TL1_Notification( BCKUP, theResponse)
{
}

TL1_NotifBckup::~TL1_NotifBckup()
{
}
