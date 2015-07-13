// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_ATPSFSM_
#define _CFG_ATPSFSM_

#include <TelCommon/TEL_CallbackTimer.h>

class CFG_OtsAutomaticTxPwrShutAction;

class CFG_AtpsFsm
{
public:
    enum State
    {
        INIT,
        OFF,
        STANDBY,
        SHUTDOWN,
        WTR
    };

    CFG_AtpsFsm(CFG_OtsAutomaticTxPwrShutAction& anAction);
    virtual ~CFG_AtpsFsm();
    void Enable();
    void Disable();
    bool IsShutdownActive();
    virtual void Display(FC_Stream& theStream);


private:
    void RunFsm();
    bool GetLosCondition();
    bool GetBdiCondition();
    void ReadConditions();

    CFG_OtsAutomaticTxPwrShutAction& myAction;
    State myState;
    bool myBdiCondition;
    bool myLosCondition;
    TEL_CallbackTimer myTimer;
};

#define DISPLAY_CATPS_STATE(state) ( (state==INIT) ? "INIT" :\
                                     (state==OFF) ? "OFF" :\
                                     (state==STANDBY) ? "STANDBY" :\
                                     (state==SHUTDOWN) ? "SHUTDOWN" :\
                                     (state==WTR) ? "WTR" : "Unexpected state" )


#endif /* _INC_CFG_ATPSFSM_INCLUDED */
