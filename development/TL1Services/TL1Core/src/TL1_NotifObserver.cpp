/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 26, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Observer Base declaration
-----------------------------------------------------------------------------*/ 

#include <TL1Core/TL1_NotifObserver.h>

#include <TL1Core/TL1_NotifCenter.h>


TL1_NotifObserver::TL1_NotifObserver()
{
    TL1_NotifCenter::Instance().AddObserver( *this );
}

TL1_NotifObserver::~TL1_NotifObserver()
{
    TL1_NotifCenter::Instance().RemoveObserver( *this );
}
