// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_IBETHIf.h>
#include <Blackboard/FC_BbReason.h>
#include <Monitoring/MON_Region.h>
#include <CommonTypes/CT_IBETH_Definitions.h>
#include "../MON_AppIf.h"
#include "../MON_IBETHUpdateStatusAction.h"
#include "../MON_IBETHStatus.h"
#include "../MON_IBETHConfig.h"
#include "../MON_Region.h"

MON_IBETHUpdateStatusAction::MON_IBETHUpdateStatusAction(MON_AppIf& theMonIf,
                                                     TSPII_IBETHRegion& theIBETHPiiRegion,
                                                     MON_AppIf* theUpstreamLayerIf,
                                                     uint8      theNumLinks):
    MON_UpdateStatusAction(theMonIf, theUpstreamLayerIf),
    myIBETHPiiRegion(theIBETHPiiRegion),
    myNumLinks(theNumLinks)
{
  
}

MON_IBETHUpdateStatusAction::~MON_IBETHUpdateStatusAction()
{
  
}

FC_Object* MON_IBETHUpdateStatusAction::Suspend(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
 
    return NULL;
}


FC_Object* MON_IBETHUpdateStatusAction::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
   
    return NULL;
}
