// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_OTUAUTOMATICACTION_
#define _CFG_OTUAUTOMATICACTION_

#include "CFG_HwRefreshAction.h"
#include "CFG_Opt.h"
#include "CFG_OptAutomatic.h"
#include <Monitoring/MON_RsConfig.h>
#include <list>

class CFG_Otu;
class CFG_AppIf;
class MON_AppIf;

//This action is used to ...
class CFG_OtuAutomaticAction
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_OtuAutomaticAction(CFG_AppIf& theCfgIf,
                           MON_AppIf& theIncomingMonApp,
                           CFG_AppIf* theRsPortSideCfgApp = NULL,
                           CFG_AppIf* theOptCfgApp = NULL,
                           MON_AppIf* theRsIncomingMonApp = NULL);

	//Virtual destructor
	virtual ~CFG_OtuAutomaticAction();

	//This method do ...
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

protected:

private:

    MON_AppIf& myIncomingMonApp;

    CFG_AppIf* myRsPortSideCfgApp; 
    CFG_AppIf* myOptCfgApp;

    MON_AppIf* myRsIncomingMonApp;
};

#endif /* _CFG_OTUAUTOMATICACTION_ */
