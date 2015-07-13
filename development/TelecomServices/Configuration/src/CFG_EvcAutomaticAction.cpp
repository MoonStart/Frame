// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#include "../CFG_EvcAutomaticAction.h"
#include <ErrorService/FC_Error.h>
#include "../CFG_AppIf.h"
#include "../CFG_Evc.h"
#include "../CFG_EvcAutomatic.h"
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_Defects.h>
#include <Monitoring/MON_AltVcgDefects.h>
#include <Monitoring/MON_VcgStatus.h>
#include <T6100_CardIf.h>


#include <Blackboard/FC_BbAction.h>
#include <T6100_Dispatcher.h>

CFG_EvcAutomaticAction::CFG_EvcAutomaticAction(CFG_AppIf&  theCfgIf,
                                               unsigned int theNumEvcs,
                                               MON_AppIf* theGfpMonApp,
                                               MON_AppIf* theVcgMonApp):
    CFG_HwRefreshAction(theCfgIf),
    myNumEvcs(theNumEvcs),
    myGfpMonApp(theGfpMonApp),
    myVcgMonApp(theVcgMonApp)
{
    // register about config changes or defect changes
    GetBbAction()->AddInputRegion(GetCfgIf().GetCfgRegion());
    if (myGfpMonApp) 
    {
        GetBbAction()->AddInputRegion(myGfpMonApp->GetDefectsRegion());
    }
    if (myVcgMonApp) 
    {
        GetBbAction()->AddInputRegion(myVcgMonApp->GetDefectsRegion());
    }
  	GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());

    T6100_CardIf* aCardContext = dynamic_cast<T6100_CardIf*>(GetCfgIf().GetContext().GetParent());
    if (aCardContext)
    {
        mySlotId = aCardContext->GetCardId();      
    }   

}

CFG_EvcAutomaticAction::~CFG_EvcAutomaticAction()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myGfpMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myGfpMonApp->GetDefectsRegion());
    }
    if (myVcgMonApp) 
    {
        GetBbAction()->RemoveInputRegion(myVcgMonApp->GetDefectsRegion());
    }
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_EvcAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{
    bool aPortInUse[CT_TEL_NBR_OF_ETH_PORTS];
    bool aGfpInUse[CT_TEL_NBR_OF_GFPS];
    bool hasChanged = false;

     
    for (int16 anIndex = 0; anIndex < CT_TEL_NBR_OF_ETH_PORTS; anIndex++) 
    {
        aPortInUse[anIndex] = false;
    }
    
    for (int16 anIndex = 0; anIndex < CT_TEL_NBR_OF_GFPS; anIndex++) 
    {
        aGfpInUse[anIndex] = false;
    }

    CFG_EvcAutomatic& aAutomaticCfgObject  = static_cast<CFG_EvcAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]); 
    
    // Loop thru all of the EVC's to find any ETH facilities. If we find a provisioned ETH facility then update
    // the port to GFP index map to indicate the linkage between them.
    for (unsigned int anIndex = 0; anIndex < myNumEvcs; anIndex++) 
    {
        CFG_Evc& aEvcCfgObject = static_cast<CFG_Evc&>((*GetCfgIf().GetCfgRegion())[anIndex]);
        
        if (aEvcCfgObject.GetSrcPort().GetPortId() != CT_INTF_ID_UNKNOWN)
        {
            // Check if we are provisioned and an Eth facility is being used. As, if we are a LAG then we don't
            // perform any logic such as turning off the laser.
            if ((aEvcCfgObject.GetIsProvisioned()) && (aEvcCfgObject.GetSrcPort().GetPortType() == FAC_SUBTYPE_ETH) && (aEvcCfgObject.GetAllFrames()))
            {
                // Found a provisioned EVC that has an ETH, update port to GFP array.
                hasChanged |= aAutomaticCfgObject.SetGfpIdx(aEvcCfgObject.GetDestPort().GetChannelId(),aEvcCfgObject.GetSrcPort().GetPortId()); 
                aPortInUse[aEvcCfgObject.GetSrcPort().GetPortId()] = true;

                // Update the GFP to port array as well.
                hasChanged |= aAutomaticCfgObject.SetPortIdx(aEvcCfgObject.GetSrcPort().GetPortId(),aEvcCfgObject.GetDestPort().GetChannelId()); 

                aGfpInUse[aEvcCfgObject.GetDestPort().GetChannelId()] = true;

            }
        }

        // Check for defects that will force ETH-AIS 
        // Also check if Evc should be refreshed based on Vcg Status field
        if ((myVcgMonApp) && (myGfpMonApp)) 
        {
            bool   aGfpLayerDefects = false;
            bool   aTxTlcState      = false; 
            uint32 aTxTlcCount      = 0;
            bool   aRxTlcState      = false; 
            uint32 aRxTlcCount      = 0;

            if (aEvcCfgObject.GetIsProvisioned())
            {
                uint16 aGfpIdx = CT_TEL_INVALID_VCG_IDX;
                aGfpIdx = aEvcCfgObject.GetDestPort().GetChannelId();

                CT_SlotId aProvSlotId = UNKNOWN_SLOT_ID;
                aProvSlotId = aEvcCfgObject.GetDestPort().GetSlotId();

                // Check for defects that will force ETH-AIS 
                if ((aGfpIdx != CT_TEL_INVALID_VCG_IDX) && (aProvSlotId == mySlotId))
                {
                    // Check Vcg for Total Loss of Capacity
                    MON_Defects& aVcgDefects = static_cast<MON_Defects&>((*myVcgMonApp->GetDefectsRegion())[aGfpIdx]);
                    aVcgDefects.GetDefectStatus(CT_TEL_VCG_TX_TLC, &aTxTlcCount, &aTxTlcState);
                    aVcgDefects.GetDefectStatus(CT_TEL_VCG_RX_TLC, &aRxTlcCount, &aRxTlcState);

                    // Check if Gfp Layer has defects.
                    // If present, treat like defects from the RS layer.
                    MON_Defects& aGfpDefects = static_cast<MON_Defects&>((*myGfpMonApp->GetDefectsRegion())[aGfpIdx]); 
                    aGfpLayerDefects = aGfpDefects.IsLayerInDefects();
                }

                // Also check if Evc should be refreshed based on Vcg Status field
                if (aGfpIdx != CT_TEL_INVALID_VCG_IDX)
                {   
                    MON_VcgStatus& aVcgStatus = static_cast<MON_VcgStatus&>((*myVcgMonApp->GetStatusRegion())[aGfpIdx]);
                    bool aRefreshNeeded = aVcgStatus.GetForceEvcRefresh();
                    if (aRefreshNeeded) 
                    {
                        hasChanged |= aRefreshNeeded;
                        //fc_cout<<"CFG EvcAutomaticAction - refresh triggered "<<endl;
                    }
                }
            }  // if (aEvcCfgObject.GetIsProvisioned())
            
            // Set the Force AIS flag is eith TLC or Gfp Layer defects
            hasChanged |= aAutomaticCfgObject.SetForceAIS((aGfpLayerDefects || aTxTlcState || aRxTlcState), anIndex);
        } // if ((myVcgMonApp) && (myGfpMonApp))
          // 
    } // for (unsigned int anIndex = 0; anIndex < myNumEvcs; anIndex++)

    // Now find any ports that are not in an EVC and if we found any remove port to GFP linkage.
    for (int8 anIndex = 0; anIndex < CT_TEL_NBR_OF_ETH_PORTS; anIndex++) 
    {
        if (aPortInUse[anIndex] == false)
        {
            hasChanged |= aAutomaticCfgObject.SetGfpIdx(CT_TEL_INVALID_VCG_IDX,anIndex); 
        }
    }

    // Now find any GFPs that are not in an EVC and if we found any remove GFP to port linkage.
    for (int8 anIndex = 0; anIndex < CT_TEL_NBR_OF_GFPS; anIndex++) 
    {
        if (aGfpInUse[anIndex] == false)
        {
            hasChanged |= aAutomaticCfgObject.SetPortIdx(CT_INTF_ID_UNKNOWN,anIndex);  
        }
    }

    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }

    return NULL;
}
