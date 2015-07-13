// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_FabIf.h>
#include "../CFG_HwRefreshMisc.h"
#include "../CFG_Misc.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include <CommonTypes/CT_FacilityIds.h>
#include <CsPii/CSPII_CardIF.h>

#include <list>

CFG_HwRefreshMisc::CFG_HwRefreshMisc(CFG_AppIf& theCfgIf,
                                     TSPII_FabRegion* theFabPiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myFabPiiRegion(theFabPiiRegion)
{
	GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    myCardFamily = CSPII_CardIF::GetInstance()->GetCardFamily();
}


CFG_HwRefreshMisc::~CFG_HwRefreshMisc()
{
	GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
}

FC_Object* CFG_HwRefreshMisc::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Misc& aCfgObject = static_cast<CFG_Misc&>((*GetCfgIf().GetCfgRegion())[0]);
    int aNbrOfSlots = aCfgObject.GetNbrOfSlots();

    if (myFabPiiRegion != NULL)
    {
        TSPII_FabIf& aFabPiiObject = (*myFabPiiRegion)[0];
          
        CT_TEL_SwitchMode aSwitchMode = aCfgObject.GetSwitchMode();

        if ((aSwitchMode != CT_TEL_SwitchMode_None) && (aNbrOfSlots != 0))
        {
            CT_ShelfType theShelfType = aCfgObject.GetShelfType();

            if ((theShelfType == OPTICAL_SHELF_NANO_TYPE) || (theShelfType == PORT_SHELF_NANO_TYPE))
            {
                if (aSwitchMode == CT_TEL_SwitchMode_Mesh)
                {
                    aFabPiiObject.SetSwitchMode(CT_TEL_SwitchMode_Mesh); 
                    for (int aSlot = 0; aSlot < aNbrOfSlots; aSlot++) 
                    {
                        aFabPiiObject.SetSlotEnabled(aSlot,aCfgObject.GetLinkStatus(aSlot));
                        CT_TEL_LinkRate aLinkRate = aCfgObject.GetLinkRate(aSlot);

                        if ((aLinkRate == CT_TEL_LinkRate6Gbs) || (aLinkRate == CT_TEL_LinkRate3Gbs))
                        {
                            aFabPiiObject.SetSlotSpeed(aSlot, false, aLinkRate);
                            aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_CesPacket);
                        }
                        else
                        {   
                            aFabPiiObject.SetSlotSpeed(aSlot, false, CT_TEL_LinkRateNone);
                            aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_Unknown);
                        }
                    }
                }
            }
            else //Not a nano shelf
            {
                
                aFabPiiObject.SetSwitchMode(aCfgObject.GetSwitchMode());
                aFabPiiObject.SetSwitchDomainMode(aCfgObject.GetSwitchDomainMode());

                vector<uint8> aMbrList;
                aMbrList.erase(aMbrList.begin(), aMbrList.end());

                for (int i = 0; i < MAX_HCSS_SWFAB_SHELF; i++)
                {
                    CT_ShelfId aShelfId = aCfgObject.GetDomainMbrShelfId(i);
                    if (aShelfId != UNKNOWN_SHELF_ID)
                    {
                        aMbrList.push_back(uint8(aShelfId));
                    }
                }

                aFabPiiObject.SetTopologyMap(aMbrList);

                for (int aSlot = 0; aSlot < aNbrOfSlots; aSlot++) 
                {
                    bool aSlotEnable = false;
                    CT_TEL_LinkRate aLinkRate = aCfgObject.GetLinkRate(aSlot);

                    aSlotEnable = ((aLinkRate != CT_TEL_LinkRateNone) && 
                                   (aCfgObject.GetLinkOperState(aSlot) == true));
                            
                    aFabPiiObject.SetSlotEnabled(aSlot,aSlotEnable);    

                    if ((aLinkRate == CT_TEL_LinkRate6Gbs) || 
                        (aLinkRate == CT_TEL_LinkRate5_75Gbs) ||
                        (aLinkRate == CT_TEL_LinkRate5Gbs) ||
                        (aLinkRate == CT_TEL_LinkRate4Gbs) ||
                        (aLinkRate == CT_TEL_LinkRateMtera) ||
                        (aLinkRate == CT_TEL_LinkRate3Gbs))
                    {
                        bool aFecEnabled = false;
                        aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_CesPacket);
                        aFabPiiObject.SetSlotSpeed(aSlot, false, aLinkRate);
                        if(aLinkRate == CT_TEL_LinkRate5_75Gbs)
                        {
                            aFecEnabled = true;
                        }
                        aFabPiiObject.SetSlotFecEnabled(aSlot, false, aFecEnabled);
                    }
                    else if (aLinkRate == CT_TEL_LinkRatePkt)
                    {
                        aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_Packet);
                        if (aCfgObject.GetCardType(aSlot) == CARD_TYPE_ESM40)
                        {
                            aFabPiiObject.SetSlotSpeed(aSlot, false, CT_TEL_LinkRate4Gbs);
                        }
                        else if(aCfgObject.GetCardType(aSlot) == CARD_TYPE_ESM20)
                        {
                            if (theShelfType == PORT_SHELF_HCSS_TYPE)
                            {
                                aFabPiiObject.SetSlotSpeed(aSlot, false, CT_TEL_LinkRate4Gbs);
                            }
                            else
                            {
                                aFabPiiObject.SetSlotSpeed(aSlot, false, CT_TEL_LinkRate5Gbs);
                            }
                        }
                        else
                        {
                            aFabPiiObject.SetSlotSpeed(aSlot, false, CT_TEL_LinkRate3Gbs);
                        }
                        aFabPiiObject.SetSlotFecEnabled(aSlot, false, false);
                    }
                    else if (aLinkRate == CT_TEL_LinkRateSonet)
                    {
                        aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_Sonet);
                    }
                    else
                    {
                        //NOTE+++++NOTE++++++++++NOTE++++++++++++++++NOTE
                        //NOTE: The following is temporary code until we clean this up in the next release
                        //On the fabric card, an SSM in paired mode has to be treated like it is in switched mode
                        //to avoid traffic hits during transitions
                        if (myCardFamily == CARD_FAM_PACKET_FAB)
                        {
                            CT_CardType aCardType = aCfgObject.GetCardType(aSlot);
                            if (aCardType == CARD_TYPE_SSMX ||
                                aCardType == CARD_TYPE_SSMD)
                            {
                                aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_CesPacket);
                                aFabPiiObject.SetSlotSpeed(aSlot, false, ( (theShelfType == PORT_SHELF_HCSS_TYPE) ? CT_TEL_DEFAULT_LINK_RATE_HCSS : CT_TEL_DEFAULT_LINK_RATE_USS));
                                aFabPiiObject.SetSlotFecEnabled(aSlot, false, false);
                            }
                            else
                            {
                                // The slot is unequipped
                                aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_Unknown);
                                aFabPiiObject.SetSlotSpeed(aSlot, false, CT_TEL_LinkRateNone);
                                aFabPiiObject.SetSlotFecEnabled(aSlot, false, false);
                            }
                        }
                        else
                        {
                        
                            // The slot either contains an SSM in paired mode or is unequipped
                            aFabPiiObject.SetSlotTrafficType(aSlot,false,TSPII_FabIf_Traffic_Unknown);

                            // Needed for SSM in paired mode. Do not remove.
                            aFabPiiObject.SetSlotSpeed(aSlot, false, CT_TEL_LinkRateNone);
                            aFabPiiObject.SetSlotFecEnabled(aSlot, false, false);
                        }
                    }                    
                                        
                }

                if ((aSwitchMode == CT_TEL_SwitchMode_Cntr_Switch) && (theShelfType == PORT_SHELF_HCSS_TYPE))
                {
                    for (int aSlot = 0; aSlot < aNbrOfSlots; aSlot++) 
                    {
                        CT_TEL_LinkRate aLinkRate = aCfgObject.GetRemoteLinkRate(aSlot);

                        if ((aLinkRate == CT_TEL_LinkRate6Gbs) || 
                            (aLinkRate == CT_TEL_LinkRate5_75Gbs) ||
                            (aLinkRate == CT_TEL_LinkRate5Gbs) ||
                            (aLinkRate == CT_TEL_LinkRate4Gbs) ||
                            (aLinkRate == CT_TEL_LinkRate3Gbs))
                        {
                            bool aFecEnabled = false;
                            aFabPiiObject.SetSlotTrafficType(aSlot,true,TSPII_FabIf_Traffic_CesPacket);
                            aFabPiiObject.SetSlotSpeed(aSlot, true, aLinkRate);
                            if(aLinkRate == CT_TEL_LinkRate5_75Gbs)
                            {
                                aFecEnabled = true;
                            }
                            aFabPiiObject.SetSlotFecEnabled(aSlot, true, aFecEnabled);
                        }
                        else if (aLinkRate == CT_TEL_LinkRatePkt)
                        {
                            aFabPiiObject.SetSlotTrafficType(aSlot,true,TSPII_FabIf_Traffic_Packet);
                            if ((aCfgObject.GetRemoteCardType(aSlot) == CARD_TYPE_ESM40) ||
                                (aCfgObject.GetRemoteCardType(aSlot) == CARD_TYPE_ESM20))
                            {
                                aFabPiiObject.SetSlotSpeed(aSlot, true, CT_TEL_LinkRate4Gbs);
                            }
                            else
                            {
                                aFabPiiObject.SetSlotSpeed(aSlot, true, CT_TEL_LinkRate3Gbs);
                            }
                            aFabPiiObject.SetSlotFecEnabled(aSlot, true, false);
                        }
                        else
                        {   
                            //NOTE+++++NOTE++++++++++NOTE++++++++++++++++NOTE
                            //NOTE: The following is temporary code until we clean this up in the next release
                            //On the fabric card, an SSM in paired mode has to be treated like it is in switched mode
                            //to avoid traffic hits during transitions
                            if (myCardFamily == CARD_FAM_PACKET_FAB)
                            {
                                CT_CardType aCardType = aCfgObject.GetRemoteCardType(aSlot);
                                if (aCardType == CARD_TYPE_SSMX ||
                                    aCardType == CARD_TYPE_SSMD)
                                {
                                    aFabPiiObject.SetSlotTrafficType(aSlot,true,TSPII_FabIf_Traffic_CesPacket);
                                    aFabPiiObject.SetSlotSpeed(aSlot, true, CT_TEL_DEFAULT_LINK_RATE_HCSS);
                                    aFabPiiObject.SetSlotFecEnabled(aSlot, true, false);
                                }
                                else
                                {
                                    // The slot is unequipped
                                    aFabPiiObject.SetSlotTrafficType(aSlot,true,TSPII_FabIf_Traffic_Unknown);
                                    aFabPiiObject.SetSlotSpeed(aSlot, true, CT_TEL_LinkRateNone);
                                    aFabPiiObject.SetSlotFecEnabled(aSlot, true, false);
                                }
                            }
                            else
                            {
                                // The slot either contains an SSM in paired mode or is unequipped
                                aFabPiiObject.SetSlotTrafficType(aSlot,true,TSPII_FabIf_Traffic_Unknown);

                                // Needed for SSM in paired mode. Do not remove.
                                aFabPiiObject.SetSlotSpeed(aSlot, true, CT_TEL_LinkRateNone);
                                aFabPiiObject.SetSlotFecEnabled(aSlot, true, false);
                            }
                        }
                    }
                }               
            }
   
        }
        else
        {
            // Default Mode for TSPII, will cause all links to be disabled.
            aFabPiiObject.SetSwitchMode(CT_TEL_SwitchMode_None);
        }
    }

    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}


