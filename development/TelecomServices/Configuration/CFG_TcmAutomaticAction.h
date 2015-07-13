// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_TCMAUTOMATICACTION_
#define _CFG_TCMAUTOMATICACTION_

#include <CommonTypes/CT_FacilityIds.h> 
#include <CommonTypes/CT_OduDefinitions.h>
#include <T6100_TelecomIf.h>
#include <T6100_SMTMIf.h> 
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Definitions.h>
#include <Monitoring/MON_TcmDefects.h>

#include "CFG_HwRefreshAction.h"

class CFG_Tcm;
class CFG_AppIf;
class MON_Region;
class CFG_Region;
class MON_AppIf;

//This action is used to ...
class CFG_TcmAutomaticAction
: public CFG_HwRefreshAction
{
    typedef vector<CFG_AppIf*> CFG_AppVector;

public:
	//Constructor
	CFG_TcmAutomaticAction(CFG_AppIf&      theCfgIf,
                           MON_TcmDefectsRegion&     theIncomingMonRegion,
                           CT_NumberOfOdus theTcmsOnCard);

    //Virtual destructor
	virtual ~CFG_TcmAutomaticAction();

	//This method do ...
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

protected:

private:
    MON_TcmDefectsRegion& myIncomingMonRegion;
    CT_NumberOfOdus myTcmsOnCard;

};

#endif /* _CFG_TCMAUTOMATICACTION_*/
