// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbAction.h>
#include <TsPii/TSPII_OtsOHIf.h>
#include <TsPii/TSPII_OmsOHIf.h>
#include <TsPii/TSPII_OchOHIf.h>
#include "../CFG_HwRefreshOts.h"
#include "../CFG_Ots.h"
#include "../CFG_OtsOH.h"
#include "../CFG_OtsAutomatic.h"
#include "../CFG_OtsOchOHAutomatic.h"
#include "../CFG_AppIf.h"



CFG_HwRefreshOts::CFG_HwRefreshOts(CFG_AppIf& theCfgIf, 
                                   CFG_OtsOHCfgRegion& theCfgOtsOHRegion,
                                   CFG_OtsOchOHAutomaticCfgRegion& theOtsOchOHAutomaticCfgRegion,
                                   TSPII_OtsOHRegion& theOtsPiiRegion,
                                   TSPII_OmsOHRegion* theOmsPiiRegion,
                                   TSPII_OchOHRegion* theOchPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myCfgOtsOHRegion(theCfgOtsOHRegion),
    myOtsOchOHAutomaticCfgRegion(theOtsOchOHAutomaticCfgRegion),
    myOtsPiiRegion(theOtsPiiRegion),
    myOmsPiiRegion(theOmsPiiRegion),
    myOchPiiRegion(theOchPiiRegion)
{
	GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());
	GetBbAction()->AddInputRegion(&myCfgOtsOHRegion);
	GetBbAction()->AddInputRegion(GetCfgIf().GetAutomaticCfgRegion());
	GetBbAction()->AddInputRegion(&myOtsOchOHAutomaticCfgRegion);
	GetBbAction()->AddOutputRegion(GetCfgIf().GetOutputCfgRegion());
}


CFG_HwRefreshOts::~CFG_HwRefreshOts()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetAutomaticCfgRegion());
	GetBbAction()->RemoveInputRegion(&myOtsOchOHAutomaticCfgRegion);
	GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}


FC_Object* CFG_HwRefreshOts::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Ots& aOtsConfig   = static_cast<CFG_Ots&>((*GetCfgIf().GetCfgRegion())[0]);
    CFG_OtsOH& aOtsOHConfig = myCfgOtsOHRegion[0];
    CFG_OtsAutomatic& aOtsAutomaticConfig   = static_cast<CFG_OtsAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    TSPII_OtsOHIf& aOtsPii = myOtsPiiRegion[0];

    aOtsPii.SetTxTTI(aOtsConfig.GetTxTrace());

    //OTS Signaling
    aOtsPii.ForceBDIO(aOtsAutomaticConfig.GetForceOtsBDIO());
    aOtsPii.ForceBDIP(aOtsAutomaticConfig.GetForceOtsBDIP());
    aOtsPii.ForcePMI((aOtsAutomaticConfig.GetForceOtsPMI() || aOtsOHConfig.GetForceOtsPMI()) && (aOtsOHConfig.GetPMIGenerationEnabled()));

    //OMS Signaling
    if (myOmsPiiRegion)
    {
        TSPII_OmsOHIf& aOmsPii = (*myOmsPiiRegion)[0];
        aOmsPii.ForceFDIO(aOtsAutomaticConfig.GetForceOmsFDIO());
        aOmsPii.ForceFDIP(aOtsAutomaticConfig.GetForceOmsFDIP() || aOtsOHConfig.GetForceOmsFDIP());
    }

    //OCH Signaling
    if (myOchPiiRegion)
    {
        uint32 aSize = myOtsOchOHAutomaticCfgRegion.Size();

        for(uint8 aIndex=0; aIndex<aSize; aIndex++)
        {
            TSPII_OchOHIf& aOchPii = (*myOchPiiRegion)[aIndex];
            CFG_OtsOchOHAutomatic& aOchOHAutomaticCfg = myOtsOchOHAutomaticCfgRegion[aIndex];
            aOchPii.ForceFDIO(aOchOHAutomaticCfg.GetForceFDIO());
            aOchPii.ForceFDIP( (aOchOHAutomaticCfg.GetForceFDIP() || aOtsOHConfig.GetForceOchFDIP(aIndex)) && (!aOtsOHConfig.GetForceOchOCI(aIndex)) );
            aOchPii.ForceOCI(aOchOHAutomaticCfg.GetForceOCI() || aOtsOHConfig.GetForceOchOCI(aIndex));
        }    
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;
}

