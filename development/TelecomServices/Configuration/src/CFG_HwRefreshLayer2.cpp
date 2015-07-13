// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_L2If.h>
#include "../CFG_HwRefreshLayer2.h"
#include "../CFG_Layer2.h"
#include "../CFG_BwPf.h"
#include "../CFG_CfPf.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

CFG_HwRefreshLayer2::CFG_HwRefreshLayer2(CFG_AppIf& theCfgIf,
                                         uint8 theNumLayer2,
                                         TSPII_L2Region& theLayer2PiiRegion,
                                         T6100_TelecomIf* theL2pfMainApp):

    CFG_HwRefreshAction(theCfgIf),
    myNumLayer2(theNumLayer2),
    myLayer2PiiRegion(theLayer2PiiRegion),
    myL2pfMainApp(theL2pfMainApp)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddInputRegion(theL2pfMainApp->GetCfgPortApp().GetCfgRegion());
    // Currently only EVC looks at Port 0 (User BWPF).
    GetBbAction()->AddInputRegion(theL2pfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_1).GetCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshLayer2::~CFG_HwRefreshLayer2()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(myL2pfMainApp->GetCfgPortApp().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(myL2pfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_1).GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshLayer2::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Region* aBwPFCfgRegion = myL2pfMainApp->GetCfgPortApp().GetCfgRegion();
    CFG_Region* aCfPFCfgRegion = myL2pfMainApp->GetCfgPortSideApp(CT_PORT_SIDE_1).GetCfgRegion();

    // Loop thru all of the Layer2's.
    for (int16 anIndex = 0; anIndex < myNumLayer2; anIndex++) 
    {
    
        CFG_Layer2& aCfgObject = static_cast<CFG_Layer2&>((*GetCfgIf().GetCfgRegion())[anIndex]);
        TSPII_L2If& aLayer2PiiObject = myLayer2PiiRegion[anIndex];
 
        int aBwPfIndex = aCfgObject.GetBWPF();

        if (aBwPfIndex != -1)
        {
        
            //CFG_Bwpf& aCfgBwpfObject = static_cast<CFG_Bwpf&>((*GetCfgIf().GetCfgRegion())[aBwPfIndex]);

            CFG_Bwpf&   aCfgBwpfObject = static_cast<CFG_Bwpf&>((*aBwPFCfgRegion)[aBwPfIndex]);

            // Pass down to TSPII the Committed Information Rate.
            aLayer2PiiObject.SetCommittedInfoRate(aCfgBwpfObject.GetComitInfoRate());

            // Pass down to TSPII the Committed Burst Size.
            aLayer2PiiObject.SetCommittedBurstSize(aCfgBwpfObject.GetComitBrstSz());

            // Pass down to TSPII the Excess Information Rate.
            aLayer2PiiObject.SetExcessInfoRate(aCfgBwpfObject.GetExcessInfoRate());

            // Pass down to TSPII the Excess Burst Size
            aLayer2PiiObject.SetExcessBurstSize(aCfgBwpfObject.GetExcessBrstSz());

            // Pass down to TSPII the Color Mode.
            aLayer2PiiObject.SetColorMode(aCfgBwpfObject.GetColorMode());

            // Pass down to TSPII the Meter Type
            aLayer2PiiObject.SetMeterType(aCfgBwpfObject.GetMeterType());

        }

        int aCfPfIndex = aCfgObject.GetCFPF();

        if (aCfPfIndex != -1)
        {

            CFG_Cfpf&   aCfgCfpfObject = static_cast<CFG_Cfpf&>((*aCfPFCfgRegion)[aCfPfIndex]);

            // Pass down to TSPII the Tunneling of Link Aggregation Control Protocol Mode.
            aLayer2PiiObject.SetLACPMode(aCfgCfpfObject.GetLACP());

            // Pass down to TSPII the Tunneling of Link Operations, Administration and Maintenance Protocol Mode.
            aLayer2PiiObject.SetLinkOAMMode(aCfgCfpfObject.GetLinkOAM());

            // Pass down to TSPII the Dot1X authentication Mode.
            aLayer2PiiObject.SetDot1XMode(aCfgCfpfObject.GetDot1X());

            // Pass down to TSPII the Tunneling of Enhanced Local Management Interface protocol Mode
            aLayer2PiiObject.SetELMIMode(aCfgCfpfObject.GetELMI());

            // Pass down to TSPII the Tunneling of Link Layer Discovery Protocol Mode.
            aLayer2PiiObject.SetLLDPMode(aCfgCfpfObject.GetLLDP());

            // Pass down to TSPII the Tunneling of GARP Control Frames.
            //aLayer2PiiObject.SetGARPMode(aCfgCfpfObject.GetGARP());
        }


        // EVPL Parameters.
        aLayer2PiiObject.SetTagmode(aCfgObject.GetTagmode());
        aLayer2PiiObject.SetTPID(aCfgObject.GetTPID());
        aLayer2PiiObject.SetPortMode(aCfgObject.GetPortMode());
        aLayer2PiiObject.SetPVID(aCfgObject.GetPVID());
        aLayer2PiiObject.SetPortLacpPriority(aCfgObject.GetPortLacpPriority());
        aLayer2PiiObject.SetPortLacpPartiMode(aCfgObject.GetPortLacpPartiMode());
        aLayer2PiiObject.SetMateLacpPriority(aCfgObject.GetMateLacpPriority());
        aLayer2PiiObject.SetMateLacpPartiMode(aCfgObject.GetMateLacpPartiMode());

    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}
	

