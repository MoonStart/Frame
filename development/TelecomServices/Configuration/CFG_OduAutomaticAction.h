// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_ODUAUTOMATICACTION_
#define _CFG_ODUAUTOMATICACTION_

#include <CommonTypes/CT_FacilityIds.h> 
#include <CommonTypes/CT_OduDefinitions.h>
#include <T6100_TelecomIf.h>
#include <T6100_SMTMIf.h> 
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_OduStatus.h>
#include <Monitoring/MON_Region.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Definitions.h>

#include "CFG_HwRefreshAction.h"

class CFG_Odu;
class CFG_AppIf;
class MON_Region;
class CFG_Region;
class MON_AppIf;

//This action is used to ...
class CFG_OduAutomaticAction
: public CFG_HwRefreshAction
{
    typedef vector<CFG_AppIf*> CFG_AppVector;

public:
	//Constructor
	CFG_OduAutomaticAction(CFG_AppIf&      theCfgIf,
                           MON_AppIf*      theIncomingMonApp,
                           MON_AppIf*      theOtherSideIncomingMonRegion,
                           CFG_AppIf*      theOptCfgApp,
                           CFG_AppIf*      theOptOtherSideCfgRegion,
                           MON_AppIf*      theIMUXOduMonApp,
                           MON_AppIf*      theOtherSideOduMonApp = NULL,
                           bool            theIsLineSideFlag = true,
                           CT_NumberOfOdus theOdusOnCard = NUMBER_OF_DEFAULT_ODUS,
                           bool            theCreateGlueFlag = false);

    //Virtual destructor
	virtual ~CFG_OduAutomaticAction();

	//This method do ...
    virtual FC_Object* Process(unsigned theRunReason,
                               FC_Object* theInvokerObj,
                               FC_Object* theParam= NULL);

protected:

private:
    
    MON_AppIf*  myIncomingMonApp;
    MON_AppIf*  myOtherSideIncomingMonApp;
    CFG_AppIf*  myOptOtherSideCfgApp;
    CFG_AppIf*  myOptCfgApp;
    MON_AppIf*  myIMUXOduMonApp;

    MON_AppIf*      myOtherSideOduMonApp;
    bool            myIsLineSideFlag;
    bool            myCreateGlueFlag;

    CT_NumberOfOdus myOdusOnCard;
    bool            myAllowNoOtherSide;
};

#endif /* _CFG_ODUAUTOMATICACTION_*/
