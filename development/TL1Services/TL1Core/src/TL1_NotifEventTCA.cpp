/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 28, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Notification Base implementation
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_NotifEventTCA.h>

#include <TL1Core/TL1_NotifCenter.h>

TL1_NotifEventTCA::TL1_NotifEventTCA( const TL1_Response& theResponse ) :
    TL1_NotifEvent( TL1_Notification::EVT_TCA, theResponse )
{
}

TL1_NotifEventTCA::~TL1_NotifEventTCA()
{
}