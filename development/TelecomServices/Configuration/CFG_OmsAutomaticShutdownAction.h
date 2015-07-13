// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_OMSAUTOMATICSHUTDOWNACTION_
#define _CFG_OMSAUTOMATICSHUTDOWNACTION_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include "Monitoring/MON_Definitions.h"
#include <Alarm/ALM_SoakingFailure.h>


// Forward declaration of class.
class CFG_AppIf;
class MON_AppIf;
class FC_TimedProcess;

//This class is an action that automatically shutdown amplifiers when
//no signal is detected at their input.
class CFG_OmsAutomaticShutdownAction 
: public CFG_HwRefreshAction
{
public:
	//Constructor.
	CFG_OmsAutomaticShutdownAction(CFG_AppIf& theCfgIf,
                                   MON_AppIf& theMonIf,
                                   CFG_OmsAutomaticShutdownRegion& theRegion);

  	//Virtual destructor of the class.
	virtual ~CFG_OmsAutomaticShutdownAction();

	//Override of Run method from FC_Action.
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

private:

    MON_AppIf& myUpStreamMonAppIf;
    CFG_OmsAutomaticShutdownRegion& myAutomaticShutdownRegion;
	ALM_SoakingFailure myOmsLossSoaking;
    FC_TimedProcess* myTimedProcess;

};


#endif /* _CFG_OMSAUTOMATICSHUTDOWNACTION_ */
