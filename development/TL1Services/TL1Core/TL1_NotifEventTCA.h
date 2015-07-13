/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 20, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Notification Observer If declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFEVENTTCA_H__
#define __TL1_NOTIFEVENTTCA_H__

#ifndef __TL1_NOTIFEVENT_H__
#include <TL1Core/TL1_NotifEvent.h>
#endif

#include <gdef.h>

class TL1_GeneralRspBlk;

class TL1_NotifEventTCA : public TL1_NotifEvent
{
public:
    TL1_NotifEventTCA( const TL1_Response& theResponse );

    virtual ~TL1_NotifEventTCA();
};

#endif