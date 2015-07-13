/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM: Telecom Services/Facility AM subsystem
 TARGET   : SPM controller on first main shelf only
 AUTHOR   : Teresa Chen
 DESCRIPTION:
    Header file for the CFG_MiscAlarmAction class.
--------------------------------------------------------------------------*/
#ifndef CFG_MISCALARMACTION_H
#define CFG_MISCALARMACTION_H

#include <AM/AM_Definitions.h>
#include <AM/AM_6100Registry.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <ErrorService/FC_Error.h>
#include <ExecutionSupport/FC_Action.h>

// Forward declaration of class.
class CFG_AppIf;
class FC_BbAction;

typedef struct switch_domain_alm_cond
{
    CT_ProtLevel protLvl;
    uint8        numFabSlice;
    AM_UID       almCond;
} CFG_SwitchDomain_Alarm;

static CFG_SwitchDomain_Alarm CFG_HCSS_AlmCond[] =
{
    { CT_1FOR1, 0, AM_SWD_FAILURE_UID  },
    { CT_1FOR1, 1, AM_SWD_PROTNA_UID   },
    { CT_1FOR2, 0, AM_SWD_FAILURE_UID  },
    { CT_1FOR2, 1, AM_SWD_DEGRADED_UID },
    { CT_1FOR2, 2, AM_SWD_PROTNA_UID   }
};

const int CFG_HCSS_AlmCond_Size = sizeof(CFG_HCSS_AlmCond)/sizeof(CFG_SwitchDomain_Alarm);

class CFG_MiscAlarmAction : public FC_Action
{

public:

	// Constructor for CFG_MiscAlarmAction
    CFG_MiscAlarmAction(CFG_AppIf& theCfgIf, CT_ShelfId theShelfId);

	// Virtual destructor of the class.
    virtual ~CFG_MiscAlarmAction();

    CFG_AppIf& GetCfgIf() { return myCfgIf; }

    FC_BbAction* GetBbAction() { return myBbAction; }

    virtual void Run(FC_Object* theObject = NULL) {}

    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                       FC_Object* theInvokerObj,
                                       FC_Object* theParam= NULL);
private:
    AM_UID GetAlm2ProtLvl( CT_ProtLevel aProtLvl, uint8 numFabSlice );
    AM_UID GetCurrAlarm(   CT_ProtLevel aProtLvl, uint8 numFabSlice,
                            bool& setAlm, bool& clrAlm );

    CFG_AppIf& myCfgIf;
    FC_BbAction* myBbAction;
    CT_ShelfId myShelfId;
    AM_UID myLastSwitchDomainAlarm;
};
#endif  // CFG_MISCALARMACTION_H
