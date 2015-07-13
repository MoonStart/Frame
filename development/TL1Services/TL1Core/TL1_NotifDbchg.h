/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 28, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Observer If declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFDBCHG_H__
#define __TL1_NOTIFDBCHG_H__

#ifndef __TL1_NOTIFICATION_H__
#include <TL1Core/TL1_Notification.h>
#endif

#ifndef CT_TIME_H
#include <CommonTypes/CT_Time.h>
#endif

#include <LumosTypes/LT_System.h>

#include <gdef.h>
#include <time.h>

class TL1_GeneralRspBlk;

class TL1_NotifDbchg : public TL1_Notification
{
public:
    TL1_NotifDbchg( TL1_Notification::TL1_NotifType theType, 
                    const TL1_Response& theResponse );

    virtual ~TL1_NotifDbchg();

    uint32 GetDbChgSeq() const { return itsDbChgSeq; }
    CT_TimeTm GetTime() const { return itsTime; }
    void SetHandle(LT_Handle theHandle) { itsHandle = theHandle; }
    void SetCtag(LT_Ctag theCtag) { itsCtag = theCtag; };
    LT_Handle GetHandle() const { return itsHandle; }
    LT_Ctag   GetCtag()   const { return itsCtag; };

private:
    uint32 itsDbChgSeq;
    CT_TimeTm itsTime;
    LT_Handle itsHandle;
    LT_Ctag   itsCtag;
};

#endif
