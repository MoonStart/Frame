// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_EvcIf.h>
#include "../CFG_HwRefreshEvc.h"
#include "../CFG_Evc.h"
#include "../CFG_EvcAutomatic.h"
#include "../CFG_Vcg.h"
#include "../CFG_BwPf.h"
#include "../CFG_CfPf.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

CFG_HwRefreshEvc::CFG_HwRefreshEvc(CFG_AppIf& theCfgIf,
                                   CFG_EvcAutomaticCfgRegion* theAutomaticCfgRegion,
                                   unsigned int theNumEvcs,
                                   TSPII_EvcRegion& theEvcPiiRegion,
                                   T6100_TelecomIf* theBwpfMainApp,
                                   T6100_TelecomIf* theVcgApp):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myNumEvcs(theNumEvcs),
    myEvcPiiRegion(theEvcPiiRegion),
    myBwpfMainApp(theBwpfMainApp),
    myVcgApp(theVcgApp)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    GetBbAction()->AddInputRegion(theBwpfMainApp->GetCfgPortApp().GetCfgRegion());
    GetBbAction()->AddInputRegion(theBwpfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_0).GetCfgRegion());
    GetBbAction()->AddInputRegion(theBwpfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_1).GetCfgRegion()); // Port 1 is CFPF
    GetBbAction()->AddInputRegion(theVcgApp->GetCfgPortSideApp(CT_PORT_SIDE_32).GetCfgRegion(),
                                  true,    // Make sure region is valid before action runs
                                  false);  // Don't run action when region is updated
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshEvc::~CFG_HwRefreshEvc()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    GetBbAction()->RemoveInputRegion(myBwpfMainApp->GetCfgPortApp().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(myBwpfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_0).GetCfgRegion());
    GetBbAction()->RemoveInputRegion(myBwpfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_1).GetCfgRegion());
    GetBbAction()->RemoveInputRegion(myVcgApp->GetCfgPortSideApp(CT_PORT_SIDE_32).GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshEvc::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Region* aBwPFCfgRegion = myBwpfMainApp->GetCfgPortApp().GetCfgRegion();
    CFG_Region* aBwPFCOS0CfgRegion = myBwpfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_0).GetCfgRegion();
    CFG_Region* aCfPFCfgRegion = myBwpfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_1).GetCfgRegion();
    bool aGarpMode = true; // Default of this parameter is to enable.

    // Loop thru all of the EVCs.
    for (unsigned int anIndex = 0; anIndex < myNumEvcs; anIndex++) 
    {
        CFG_Evc& aCfgObject = static_cast<CFG_Evc&>((*GetCfgIf().GetCfgRegion())[anIndex]);
        TSPII_EvcIf& aEvcPiiObject = myEvcPiiRegion[anIndex];

        int aBwPfIndex = aCfgObject.GetBWPF();

        if (aBwPfIndex != -1)
        {
            if (aBwPfIndex < CT_TEL_NBR_OF_BWPFS)
            {
                CFG_Bwpf&   aCfgBwpfObject = static_cast<CFG_Bwpf&>((*aBwPFCfgRegion)[aBwPfIndex]);
                
                // Pass down to TSPII the Committed Information Rate.
                aEvcPiiObject.SetCommittedInfoRate(aCfgBwpfObject.GetComitInfoRate());

                // Pass down to TSPII the Committed Burst Size.
                aEvcPiiObject.SetCommittedBurstSize(aCfgBwpfObject.GetComitBrstSz());
            }
            else
            {
                aBwPfIndex = aBwPfIndex - CT_TEL_NBR_OF_BWPFS;

                CFG_Bwpf&   aCfgBwpfObject = static_cast<CFG_Bwpf&>((*aBwPFCOS0CfgRegion)[aBwPfIndex]);

                // Pass down to TSPII the Committed Information Rate.
                aEvcPiiObject.SetCommittedInfoRate(aCfgBwpfObject.GetComitInfoRate());

                // Pass down to TSPII the Committed Burst Size.
                aEvcPiiObject.SetCommittedBurstSize(aCfgBwpfObject.GetComitBrstSz());

            }

        }

        int aCfPfIndex = aCfgObject.GetCFPF();

        if (aCfPfIndex != -1)
        {

            CFG_Cfpf&   aCfgCfpfObject = static_cast<CFG_Cfpf&>((*aCfPFCfgRegion)[aCfPfIndex]);

            // Read the Tunneling of GARP Control Frames. Pass down to TSPII after the SetEvc.
            aGarpMode = aCfgCfpfObject.GetGARP();
        }

        // Indicate All frames should be set i.e. Epl.
        //aEvcPiiObject.SetIsEpl(aCfgObject.GetAllFrames());
   
        // Pass down destination port and slot of EVC.
        //aEvcPiiObject.SetDestPort(aCfgObject.GetDestPort());

        // Pass down source port and slot of EVC.
        //aEvcPiiObject.SetSrcPort(aCfgObject.GetSrcPort());

        // EVPL Parameters.
        aEvcPiiObject.SetSTAG(aCfgObject.GetSTAG());
        aEvcPiiObject.SetSVID(aCfgObject.GetSVID());
        aEvcPiiObject.SetCVID(aCfgObject.GetCVID());

        if (aCfgObject.GetIsProvisioned())
        {
            if (aCfgObject.GetIsProtected())
            {
                uint8 aVcgIdx = aCfgObject.GetDestPort().GetChannelId();

                if (aVcgIdx != CT_TEL_INVALID_VCG_IDX)
                {
                    CFG_Region* aCfgVcgRegion = myVcgApp->GetCfgPortSideApp(CT_PORT_SIDE_32).GetCfgRegion();
                    CFG_Vcg&    aCfgVcg = static_cast<CFG_Vcg&>((*aCfgVcgRegion)[aVcgIdx]);

                    if ( (aCfgVcg.GetVcatType() == CT_TEL_VCAT_STS1) || (aCfgVcg.GetVcatType() == CT_TEL_VCAT_STS3C)  || (aCfgVcg.GetVcatType() == CT_TEL_VCAT_STS12C))
                    {
                        // Moved to beginning of the list because EVPL needs this parameter set before EVC is created!
                        aEvcPiiObject.SetGARPMode(aGarpMode);

                        // Pass down destination and source port/slot and indicate if this EVC is provisioned.
                        aEvcPiiObject.SetEvc(aCfgObject.GetSrcPort(), aCfgObject.GetDestPort(), aCfgObject.GetIsProvisioned(), aCfgObject.GetEvcPairId(), 
                                             aCfgObject.GetAllFrames(), aCfgObject.GetSrcIncludedInAnyEVC(), aCfgObject.GetDestIncludedInAnyEVC(),
                                             aCfgObject.GetIsProtected());

                        aEvcPiiObject.EnablePauseFrameTransparency(!aCfgObject.GetPauseDiscardEnabled());
                        aEvcPiiObject.SetPbitRegen(aCfgObject.GetPbitRegen());
                    }
                }
            }
            else
            {
                // Moved to beginning of the list because EVPL needs this parameter set before EVC is created!
                aEvcPiiObject.SetGARPMode(aGarpMode);

                // Pass down destination and source port/slot and indicate if this EVC is provisioned.
                aEvcPiiObject.SetEvc(aCfgObject.GetSrcPort(), aCfgObject.GetDestPort(), aCfgObject.GetIsProvisioned(), aCfgObject.GetEvcPairId(), 
                                     aCfgObject.GetAllFrames(), aCfgObject.GetSrcIncludedInAnyEVC(), aCfgObject.GetDestIncludedInAnyEVC(), 
                                     aCfgObject.GetIsProtected());
                                        
                aEvcPiiObject.EnablePauseFrameTransparency(!aCfgObject.GetPauseDiscardEnabled());
                aEvcPiiObject.SetPbitRegen(aCfgObject.GetPbitRegen());
            }
        }
        else 
        {
            // Moved to beginning of the list because EVPL needs this parameter set before EVC is created!
            aEvcPiiObject.SetGARPMode(aGarpMode);
            aEvcPiiObject.EnablePauseFrameTransparency(!aCfgObject.GetPauseDiscardEnabled());

            // Pass down destination and source port/slot and indicate if this EVC is provisioned.
            aEvcPiiObject.SetEvc(aCfgObject.GetSrcPort(), aCfgObject.GetDestPort(), aCfgObject.GetIsProvisioned(), aCfgObject.GetEvcPairId(), 
                                 aCfgObject.GetAllFrames(), aCfgObject.GetSrcIncludedInAnyEVC(), aCfgObject.GetDestIncludedInAnyEVC(), 
                                 aCfgObject.GetIsProtected());

            aEvcPiiObject.SetPbitRegen(aCfgObject.GetPbitRegen());
        }

        aEvcPiiObject.SetAisEnabled(aCfgObject.GetAisEnabled());
        aEvcPiiObject.SetAisInterval(aCfgObject.GetAisInterval());
        aEvcPiiObject.SetAisMegLevel(aCfgObject.GetAisMegLevel());
        aEvcPiiObject.SetAisDestMacMode(aCfgObject.GetAisDestMacMode());
        aEvcPiiObject.SetAisDestMacAddr(aCfgObject.GetAisDestMacAddr());
        aEvcPiiObject.SetFacilityLoopBackEnable(aCfgObject.GetFacilityLoopBackEnable());
        aEvcPiiObject.SetTerminalLoopBackEnable(aCfgObject.GetTerminalLoopBackEnable());

        // If AIS Enabled and terminal loopback is active Force AIS,
        // else look at Automatic Action for Force AIS. 
        bool forceAis = false;
        if (aCfgObject.GetAisEnabled())
        {
            if (aCfgObject.GetTerminalLoopBackEnable())
            {
                forceAis = true;
            }
            else if (myAutomaticCfgRegion)
            {
                CFG_EvcAutomatic& aAutomaticCfgObject = (*myAutomaticCfgRegion)[0];
                forceAis = aAutomaticCfgObject.GetForceAIS(anIndex);
            }
        }
        
        aEvcPiiObject.SetForceAis(forceAis);

        aEvcPiiObject.SetAis(); // Call this after all AIS parms have been configured

    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}
    

