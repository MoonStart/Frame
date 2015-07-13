// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_HopIf.h>
#include "../CFG_HwRefreshHop.h"
#include "../CFG_Hop.h"
#include "../CFG_HopAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>



CFG_HwRefreshHop::CFG_HwRefreshHop(CFG_AppIf&                 theCfgIf,
                                   CFG_HopAutomaticCfgRegion* theAutomaticCfgRegion,
                                   TSPII_HopRegion&           theHopPiiRegion,
                                   CT_NumberOfHops            theHopsOnCard,
                                   uint8                      theXcFacilityID,
                                   TSXC_ConfigRegion<TSXC_Connect>*  theXcConfigRegion,
                                   TSXC_RsReadyRegion<TSXC_RsReady>* theXcRsReadyRegion):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myHopPiiRegion(theHopPiiRegion),
    myHopsOnCard(theHopsOnCard),
    myXCFacilityID(theXcFacilityID),
    myXcConfigRegion(theXcConfigRegion),
    myXcRsReadyRegion(theXcRsReadyRegion),
    myFirstRefreshAction(true)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    if (myXcConfigRegion) GetBbAction()->AddInputRegion(myXcConfigRegion);
    if (myXcRsReadyRegion) GetBbAction()->AddInputRegion(myXcRsReadyRegion);
}

CFG_HwRefreshHop::~CFG_HwRefreshHop()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    if (myXcConfigRegion) GetBbAction()->RemoveInputRegion(myXcConfigRegion);
    if (myXcRsReadyRegion) GetBbAction()->RemoveInputRegion(myXcRsReadyRegion);
}

FC_Object* CFG_HwRefreshHop::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{

    CFG_Region* aCfgRegion = (GetCfgIf().GetCfgRegion());
    // Use myHopsOnCard constructor variable rather than size of region
    // due to Context Collapse changes
    // uint32 aCfgRegionSize = 0;
    // if (aCfgRegion)
    // {
    //     aCfgRegionSize = aCfgRegion->Size();
    // }

    for (uint32 anIndex = 0; anIndex < myHopsOnCard; anIndex++)
    {
        CFG_Hop& aCfgObject = static_cast<CFG_Hop&>((*aCfgRegion)[(bbindex_t)anIndex]);
        TSPII_HopIf& aHopPiiObject = myHopPiiRegion[(bbindex_t)anIndex];

        // Set Force Internal AIS either from default (false) or, if present, from the Automatic Action
        bool aForceInternalAIS = false;
        if (myAutomaticCfgRegion)
        {
           CFG_HopAutomatic& aAutomaticCfgObject = (*myAutomaticCfgRegion)[(bbindex_t)anIndex];

           // Determine whether to Force Internal AIS (set by Automatic Action)
           aForceInternalAIS = aAutomaticCfgObject.GetForceInternalAIS();
        }
        aHopPiiObject.SetForceInternalAisEnabled(aForceInternalAIS);


        //Set normal Configuration parameters
        //Set the HOP parameters.
        CT_TEL_HopSpeMapping aMapping = aCfgObject.GetSpeMapping();
        aHopPiiObject.SetSpeMapping(aMapping);

        // Only send Tspii UNEQ when there is a valid mapping.
        // With MR 121559, add the pssibility to override what Agent configures for UNEQ 
        // because we want speed up the forcing of UNEQ when the cross connect is deleted.
        // Therefore, if Agent isn't already sending UNEQ, check XC and only override Agent
        // by forcing UNEQ when the Hop instance is not connected.
        if (aMapping != CT_TEL_HOP_MAPPING_UNKNOWN)
        {
            bool aForceUNEQ = aCfgObject.GetForceUNEQ(); 
            if ((myXcConfigRegion) && (!aForceUNEQ))
            {
                if (myXcConfigRegion->Size() > 0) 
                {
                    bool aIsConnected = myXcConfigRegion->IsConnectedAsOutput(myXCFacilityID, uint8(anIndex+1));
                    if (!aIsConnected) 
                    {
                        aForceUNEQ = true;
                    }
                }
            }
            aHopPiiObject.SetForceUneqEnabled(aForceUNEQ);
        }

        // Temporarily do not confiugre generated path trace as it
        // is the prime suspect in excessive CPU usage.
        //aHopPiiObject.SetTxTrace(aCfgObject.GetSentTrace());

        //aHopPiiObject.SetTimMmMonitorEnabled(aCfgObject.GetSendTraceFlag());


        //Set Monitoring Configuration parmaters
        //Set BER Signal Fail Threshold
        aHopPiiObject.SetBerSfThreshold(aCfgObject.GetBerSfThreshold());
        aHopPiiObject.SetBerSdThreshold(aCfgObject.GetBerSdThreshold());
        aHopPiiObject.SetExpectedC2(aCfgObject.GetExpectedC2());

        aHopPiiObject.SetPointerJustEnabled(aCfgObject.GetPointerJustEnabled());

    }
    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}


