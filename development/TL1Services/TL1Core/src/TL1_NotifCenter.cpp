/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 26, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Center declaration
-----------------------------------------------------------------------------*/ 

#include <TL1Core/TL1_NotifCenter.h>

#include <algorithm>

const uint32 TL1_NotifCenter::MAX_ATAG = 999999999;
const uint32 TL1_NotifCenter::MAX_DBSEQ = 9999;
extern uint8 debugIgnoreDbchg;


TL1_NotifCenter::TL1_NotifCenter() : itsAtag(0), itsDBChgSq(0), itsIsLocked(true)
{ 

}

TL1_NotifCenter::~TL1_NotifCenter()
{
}


void TL1_NotifCenter::AddObserver( TL1_NotifObserverIf& theObs )
{
    NotifObsList::iterator it = 
        find( itsObservers.begin(), itsObservers.end(), &theObs );
    if ( it == itsObservers.end() )
    {
        itsObservers.push_back( &theObs );
    }
    else
    {
        // Erroneous attemps to register the same observer a second time
    }
}

void TL1_NotifCenter::RemoveObserver( TL1_NotifObserverIf& theObs )
{
    NotifObsList::iterator it = 
        find( itsObservers.begin(), itsObservers.end(), &theObs );
    if ( it != itsObservers.end() )
    {
        itsObservers.erase( it );
    }
    else
    {
        // Erroneous attemps to unregister an unknown observer
    }
}

void TL1_NotifCenter::Notify( TL1_Notification& theNotif )
{
    if (debugIgnoreDbchg)
        return;

    if( !itsIsLocked )
    {
        for_each( itsObservers.begin(),
                  itsObservers.end(),
                  TL1_NotifFunctor( theNotif ) );
    }
    else
    {
        itsAtag = 0;
        itsDBChgSq = 0;
    }
}

uint32 TL1_NotifCenter::GetNextAtag()
{
    return itsAtag = (++itsAtag) % (MAX_ATAG+1);  
}

uint32 TL1_NotifCenter::GetNextDBSeq()
{
    return itsDBChgSq = (++itsDBChgSq) % (MAX_DBSEQ+1);
}

// Warning: Every time the notif center will be locked, the Atag and
// DbChgSeq will be reset.
void TL1_NotifCenter::SetLock( bool isLocked )
{
    itsIsLocked = isLocked;
}
