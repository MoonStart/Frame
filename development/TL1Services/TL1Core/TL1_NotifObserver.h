/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 26, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Observer Base declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFOBSERVER_H__
#define __TL1_NOTIFOBSERVER_H__

#ifndef __TL1_NOTIFOBSERVERIF_H__
#include <TL1Core/TL1_NotifObserverIf.h>
#endif

class TL1_NotifObserver : public TL1_NotifObserverIf
{
public:
    TL1_NotifObserver();
    virtual ~TL1_NotifObserver();
};

#endif
