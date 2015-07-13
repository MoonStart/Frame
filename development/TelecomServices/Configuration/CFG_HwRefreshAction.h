/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM: Telecom Services/Facility Configuration.
 TARGET   : OCCS(OPM), platform independent.
 AUTHOR   : Steve Thiffault
 DESCRIPTION:
    Header file for the CFG_FacilityHwRefreshAction class.
--------------------------------------------------------------------------*/
#ifndef CFG_HWREFRESHACTION_H
#define CFG_HWREFRESHACTION_H

#include "CFG_Object.h"

#include <ExecutionSupport/FC_Action.h>
#include <ErrorService/FC_Error.h>

// Forward declaration of class.
class CFG_AppIf;
class FC_BbAction;

//This action is invoked periodically in order to update 
//generic hardware registers with current generic 
//configuration.
//##ModelId=3C0FE6300065
class CFG_HwRefreshAction : public FC_Action
{

public:

	//Constructor for CFG_FacilityHwRefreshAction.
	//##ModelId=3C0FE6300070
    CFG_HwRefreshAction(CFG_AppIf& theCfgIf);

	//Virtual destructor of the class.
	//##ModelId=3C0FE630008F
    virtual ~CFG_HwRefreshAction();

	//##ModelId=3C3B463B0031
    CFG_AppIf& GetCfgIf() { return myCfgIf;}

    virtual FC_CmdProcessor::STATUS Debug(int argc, char **argv);

	//##ModelId=3C716FF40304
    FC_BbAction* GetBbAction() { return myBbAction; }

    virtual void Run(FC_Object* theObject = NULL);
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL) = 0;
    virtual FC_Object* Suspend(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);
    static bool myEnable;

private:

	//##ModelId=3C3B463B0046
    CFG_AppIf& myCfgIf;
	//##ModelId=3C716FF40319
    FC_BbAction* myBbAction;

    uint32 myInstance;

};
#endif  // CFG_HWREFRESHACTION_H
