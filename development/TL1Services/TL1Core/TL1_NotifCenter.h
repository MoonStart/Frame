/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 26, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Notification Center declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NOTIFCENTER_H__
#define __TL1_NOTIFCENTER_H__

#ifndef __FC_SINGLETON_H__
#include <Util/FC_Singleton.h>
#endif

#ifndef __TL1_NOTIFOBSERVERIF_H__
#include <TL1Core/TL1_NotifObserverIf.h>
#endif

#ifndef __GDEF_H__
#include <gdef.h>
#endif


#include <vector>

using namespace std;

class TL1_NotifObserverIf;
class TL1_Notification;

class TL1_NotifCenter
{
public:
    // Public Constant
    static const uint32 MAX_ATAG;
    static const uint32 MAX_DBSEQ;

    virtual ~TL1_NotifCenter();

    void AddObserver( TL1_NotifObserverIf& theObs );
    void RemoveObserver( TL1_NotifObserverIf& theObs );

    // Function called for notification generation.
    void Notify( TL1_Notification& theNotif );

    // Get Next Atag
    uint32 GetNextAtag();

    // Get Next Database change sequence
    uint32 GetNextDBSeq();

    // Warning: Every time the notif center will be locked, the Atag and
    // DbChgSeq will be reset.
    void SetLock( bool isLocked );

    static TL1_NotifCenter& Instance()
    {
        return *FC_Singleton<TL1_NotifCenter>::Instance();
    }

private:
    friend class FC_Singleton<TL1_NotifCenter>;
    TL1_NotifCenter();

    struct TL1_NotifFunctor
    {
        TL1_NotifFunctor( TL1_Notification& theNotif ) :
            itsNotif( theNotif ) {}

        void operator()( TL1_NotifObserverIf* theObs )
        {
            theObs->ProcessNotification( itsNotif );
        }
        TL1_Notification& itsNotif;
    };

    typedef vector<TL1_NotifObserverIf*> NotifObsList;
    NotifObsList itsObservers;

    //  For atag, Database Change Sequence
    uint32  itsAtag;
    uint32  itsDBChgSq;

    bool    itsIsLocked;
};

#endif
