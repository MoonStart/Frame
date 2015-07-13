// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_MacIf.h>
#include "../CFG_HwRefreshMac.h"
#include "../CFG_Mac.h"
#include "../CFG_MacAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

CFG_HwRefreshMac::CFG_HwRefreshMac(CFG_AppIf& theCfgIf,
                                   CFG_MacAutomaticCfgRegion* theAutomaticCfgRegion,
                                   TSPII_MacRegion& theMacPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myMacPiiRegion(theMacPiiRegion)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshMac::~CFG_HwRefreshMac()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshMac::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Mac& aCfgObject = static_cast<CFG_Mac&>((*GetCfgIf().GetCfgRegion())[0]);
    TSPII_MacIf& aMacPiiObject = myMacPiiRegion[0];

    // Indicate if auto-negotiation is enabled.
    aMacPiiObject.SetAutoNeg( aCfgObject.GetAutoNeg() );

    // Set the ethernet rate.
    aMacPiiObject.SetCfgRate( aCfgObject.GetEthernetRate() );

    // Set the Duplex mode.
    aMacPiiObject.SetCfgDuplexMode( aCfgObject.GetDuplexMode() );

    // Set the Flow Control Configuration.
    aMacPiiObject.SetCfgFlowCtrl( aCfgObject.GetFlowControl() );

    // Set the Advertised Flow Control.
    aMacPiiObject.SetCfgAdvrtFlowCtrl( aCfgObject.GetAdvrtFlowCtrl() );

    //Set PropFefi mode
    aMacPiiObject.EnableFefiTransparency(true);

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;
}
	

