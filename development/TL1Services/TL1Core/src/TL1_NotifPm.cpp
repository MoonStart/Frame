/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 28, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Base implementation
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include <TL1Core/TL1_NotifPm.h>

#include <TL1Core/TL1_NotifCenter.h>

TL1_NotifPm::TL1_NotifPm( const TL1_Response& theResponse ) :
    TL1_Notification( TL1_Notification::PM, theResponse)
{
}

TL1_NotifPm::~TL1_NotifPm()
{
}
