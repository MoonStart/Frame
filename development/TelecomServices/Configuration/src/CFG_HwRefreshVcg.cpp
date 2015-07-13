// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_VcgIf.h>
#include "../CFG_HwRefreshVcg.h"
#include "../CFG_Vcg.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>

//extern "C"
//{
//    extern uint32 TMBget_timestamp( void );
//    extern uint32 TMBusec_since( uint32 timestamp );
//}


CFG_HwRefreshVcg::CFG_HwRefreshVcg(CFG_AppIf& theCfgIf,
                                   uint8 theNumVcg,
                                   TSPII_VcgRegion& theVcgPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myNumVcg(theNumVcg),
    myVcgPiiRegion(theVcgPiiRegion)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
}

CFG_HwRefreshVcg::~CFG_HwRefreshVcg()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshVcg::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
//    bool   aDebug = false;
//    CFG_Vcg& aFirstCfgObject = static_cast<CFG_Vcg&>((*GetCfgIf().GetCfgRegion())[0]);
//    if(aFirstCfgObject.IsDebugFlagSet())
//        aDebug = true;
    //int16  aBrkDwnIdx = aFirstCfgObject.GetBrkDwnIdx();

//    if (aDebug)
//        aStartTime = TMBget_timestamp();

//    fc_cout <<" Starting Cfg_HwRefeshVcg"<<endl;
    // Loop thru all of the Vcg's.
    for (int16 anIndex = 0; anIndex < myNumVcg; anIndex++) 
    {
//        aStartTime  = 0;
//        uint32 aPt1 = 0;
//        uint32 aPt2 = 0;
//        uint32 aPt3 = 0;
//        uint32 aPt4 = 0;
//        uint32 aPt5 = 0;
//        uint32 aPt6 = 0;
//        uint32 aPt7 = 0;


//        if (aDebug)
//            aStartTime = TMBget_timestamp();
        
        CFG_Vcg& aCfgObject = static_cast<CFG_Vcg&>((*GetCfgIf().GetCfgRegion())[anIndex]);
        TSPII_VcgIf& aVcgPiiObject = myVcgPiiRegion[anIndex];

        // There is a different order for sending down Tspii methods based on when
        // the vcg is provisioned or not provisioned

        if (!aCfgObject.GetIsProvisioned()) 
        {
            // Not Provisioned case

            // Set Members of the TTP list.
            aVcgPiiObject.SetMembers(aCfgObject.GetTTPList());
//            if (aDebug)
//                aPt1 = TMBusec_since(aStartTime);
        
            // Set Members of the Source TTP list.
            aVcgPiiObject.SetSrcMembers(aCfgObject.GetSourceTTPList());
            // Set Members of the Sink TTP list.
            aVcgPiiObject.SetSnkMembers(aCfgObject.GetSinkTTPList());

            // Set Lcas Enabled.
            aVcgPiiObject.SetLcasEnabled(aCfgObject.GetLcasEnabled());

            // Set Hold Off Timer.
            aVcgPiiObject.SetHoldOffTimer(aCfgObject.GetHoldOffTmr());

            // Set Wait to Restore Timer.
            aVcgPiiObject.SetWaitToRestoreTimer(aCfgObject.GetWaitToRetoreTmr());
//            if (aDebug)
//                aPt2 = TMBusec_since(aStartTime);

            // Set Partial Loss of Capacity Threshold.
            aVcgPiiObject.SetPlcThres(uint16(aCfgObject.GetPartialLossCpyTH()));

            // Set Total Loss of Capacity Threshold.
            aVcgPiiObject.SetTlcThres(uint16(aCfgObject.GetTotalLossCpyTH()));

            // Set Differental Delay Threshold.
            aVcgPiiObject.SetDiffDelayThres(aCfgObject.GetDiffDelay());

            // Set Vcat Type.
            aVcgPiiObject.SetVcatType(aCfgObject.GetVcatType());

            // Set XC connected as Source.
            aVcgPiiObject.SetIsConnAsSrc(aCfgObject.GetIsConnectedAsSrc());

            // Set XC connected as Destination.
            aVcgPiiObject.SetIsConnAsDest(aCfgObject.GetIsConnectedAsDest());
//            if (aDebug)
//                aPt3 = TMBusec_since(aStartTime);

            // Set Protected VCG Index.
            aVcgPiiObject.SetProtectedVcgID(aCfgObject.GetProtectVcgIdx(),aCfgObject.GetProtectVcgSlot());
//            if (aDebug)
//                aPt7 = TMBusec_since(aStartTime);

        } // if (aCfgObject.GetIsProvisioned())
        else
        {
            // Provisioned case
        
            // Set Lcas Enabled.
            aVcgPiiObject.SetLcasEnabled(aCfgObject.GetLcasEnabled());

            // Set Hold Off Timer.
            aVcgPiiObject.SetHoldOffTimer(aCfgObject.GetHoldOffTmr());

            // Set Wait to Restore Timer.
            aVcgPiiObject.SetWaitToRestoreTimer(aCfgObject.GetWaitToRetoreTmr());
//            if (aDebug)
//                aPt4 = TMBusec_since(aStartTime);

            // Set Partial Loss of Capacity Threshold.
            aVcgPiiObject.SetPlcThres(uint16(aCfgObject.GetPartialLossCpyTH()));

            // Set Total Loss of Capacity Threshold.
            aVcgPiiObject.SetTlcThres(uint16(aCfgObject.GetTotalLossCpyTH()));

            // Set Differental Delay Threshold.
            aVcgPiiObject.SetDiffDelayThres(aCfgObject.GetDiffDelay());

            // Set Vcat Type.
            aVcgPiiObject.SetVcatType(aCfgObject.GetVcatType());
//            if (aDebug)
//                aPt5 = TMBusec_since(aStartTime);

            // Set XC connected as Source.
            aVcgPiiObject.SetIsConnAsSrc(aCfgObject.GetIsConnectedAsSrc());

            // Set XC connected as Destination.
            aVcgPiiObject.SetIsConnAsDest(aCfgObject.GetIsConnectedAsDest());

            // Set Members of the TTP list.
            aVcgPiiObject.SetMembers(aCfgObject.GetTTPList());
//            if (aDebug)
//                aPt6 = TMBusec_since(aStartTime);
// 
            // Set Members of the Source TTP list.
            aVcgPiiObject.SetSrcMembers(aCfgObject.GetSourceTTPList());
            // Set Members of the Sink TTP list.
            aVcgPiiObject.SetSnkMembers(aCfgObject.GetSinkTTPList());

            // Set Protected VCG Index.
            aVcgPiiObject.SetProtectedVcgID(aCfgObject.GetProtectVcgIdx(),aCfgObject.GetProtectVcgSlot());
//            if (aDebug)
//                aPt7 = TMBusec_since(aStartTime);
        }

//        if(aDebug)
//        {
//            aCfgObject.SetProcessTime(aPt7);
//            aCfgObject.SetBreakdown(aPt1, aPt2, aPt3, aPt4, aPt5, aPt6, aPt7);
//       }

    }
    
    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    // No need to kick the refresh since MON will run at a later time and
    // discover that evc refresh is necessary.  
    //myVcgPiiRegion[0].KickEvcRefresh();

    //fc_cout <<" Ending Cfg_HwRefeshVcg"<<endl;
//    if (aDebug)
//    {
//        CFG_Vcg& aCfgObject = static_cast<CFG_Vcg&>((*GetCfgIf().GetCfgRegion())[63]);
//        uint32 aPt7 = TMBusec_since(aStartTime);
//        aCfgObject.SetProcessTime(aPt7);
//    }

    return NULL;

}
	

