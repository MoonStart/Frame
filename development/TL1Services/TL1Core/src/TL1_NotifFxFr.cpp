/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 16, 2003- Mathieu Lavoie
DESCRIPTION:    Implementation file for TL1 file transfer result Notification
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_NotifFxFr.h>

#include <TL1Core/TL1_NotifCenter.h>

TL1_NotifFxFr::TL1_NotifFxFr( const TL1_Response& theResponse ) :
    TL1_Notification( FXFR, theResponse)
{
}

TL1_NotifFxFr::~TL1_NotifFxFr()
{
}
