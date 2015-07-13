// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_1PLUS1DCCCONFIGACTION_38E35B0900D0_INCLUDED
#define _INC_SP_1PLUS1DCCCONFIGACTION_38E35B0900D0_INCLUDED

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SignalProtection.h>
//#include "SP_Definitions.h"
#include <CommonTypes/CT_DCC_Definitions.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>
#include "SP_ApplicationStatus.h"
#include <TsPii/TSPII_Region.h>

class T6100_CardIf;
class FC_TimedProcess;
class FC_BbAction;
class CFG_Region;
class T6100_ControllerStatusRegion;

//This action is responsible for LAPS broadcast DCC configuration
class SP_1plus1DccConfigAction
: public FC_Action
{
public:

	static SP_1plus1DccConfigAction & GetInstance(T6100_CardIf* theCardContext);
    static void DeleteInstance();

	//Not implemented.
    //##ModelId=3B8BC9D30390
    virtual void Run( FC_Object* theObject = NULL );

    //##ModelId=38F232640235
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

    void SetLapsData(uint8 remotePort, 
                     bool isSelected, 
                     uint8 index);

    void ApplyConfiguration();

    FC_BbAction* GetBbAction() { return myBbAction; };

    void SetModeRegion(T6100_ControllerStatusRegion* theModeRegion);

protected:
    //Constructor. 
    //##ModelId=3BBC9B0F02A0
    SP_1plus1DccConfigAction (T6100_CardIf* theCardContext);

    //Destructor.
    //##ModelId=38EDF51800A6
    virtual ~SP_1plus1DccConfigAction();

	
private:
    static SP_1plus1DccConfigAction *myInstance;
    T6100_CardIf* myCardContext;
    bool mySelection[CT_TEL_LAPD_IN_SC];
    uint8 myRemotePort[CT_TEL_LAPD_IN_SC];
    FC_TimedProcess* myProcess;
    FC_BbAction* myBbAction;
    TEL_BbRegionBaseImp<SP_ApplicationStatus> * myAppStatusRegionPort;
    TEL_BbRegionBaseImp<SP_ApplicationStatus> * myAppStatusRegionLine;
    T6100_ControllerStatusRegion* myModeRegion;

    //Helper method
    bool Configure(CFG_Region* aProtCfgRegion);
};

#endif /* _INC_SP_1PLUS1PERSMONITORACTION_38E35B0900D0_INCLUDED */