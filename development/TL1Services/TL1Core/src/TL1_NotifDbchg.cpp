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

#include <TL1Core/TL1_NotifDbchg.h>
#include <TL1Core/TL1_NotifCenter.h>
#include <TimeService/FC_Time.h>

TL1_NotifDbchg::TL1_NotifDbchg( TL1_Notification::TL1_NotifType theType,
                                const TL1_Response& theResponse ) :
    TL1_Notification( theType, theResponse),
    itsDbChgSeq( TL1_NotifCenter::Instance().GetNextDBSeq() ),
    itsTime()
{
        FC_Time aTime;
        aTime.GetCurrentTime();
        itsTime = aTime.GetCtTime();
        itsHandle = -2; // This value is -2 for a reason.
        itsCtag = "NA";
}

TL1_NotifDbchg::~TL1_NotifDbchg()
{
}
