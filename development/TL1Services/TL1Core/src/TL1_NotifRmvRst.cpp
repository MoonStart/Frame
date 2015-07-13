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

#include <TL1Core/TL1_NotifRmvRst.h>

#include <TL1Core/TL1_NotifCenter.h>

TL1_NotifRmvRst::TL1_NotifRmvRst( TL1_Notification::TL1_NotifType theNotifType, 
                                  const TL1_Response& theResponse ) :
    TL1_Notification( theNotifType, theResponse )
{
}

TL1_NotifRmvRst::~TL1_NotifRmvRst()
{
}