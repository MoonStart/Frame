/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM   : PWR
 TARGET      : CX16U
 AUTHOR      : Gareth Zhang 2014/02
 DESCRIPTION : CX16U specific class for automatic power control.  
--------------------------------------------------------------------------*/


#ifndef PWR_HISTORY_H
#define PWR_HISTORY_H

#include <time.h>
#include "CommonTypes/CT_Telecom.h"

class FC_Stream;

class PWR_OchHistory
{
public:
    /* Constructor */ PWR_OchHistory();
    virtual           ~PWR_OchHistory();
    static void       DisplayHeader(FC_Stream & theStream);

    time_t            myTimestamp;
    char              myEvent;
    bool              myControllable;
    bool              myObservable;
    bool              myOchReady;
    CT_TEL_mBm        myOchPower;
    CT_TEL_mBm        myOchMinPwr;
    CT_TEL_mBm        myOchTarget;
    CT_TEL_mBm        myError;
    CT_TEL_mBm        myOchCommand;
};

FC_Stream & operator<<(FC_Stream & theStream, const PWR_OchHistory & theHistory);

#endif // PWR_HISTORY_H
