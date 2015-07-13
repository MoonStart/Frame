// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_GccIf.h>
#include <TsPii/TSPII_GccMapIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include "../CFG_HwRefreshGcc.h"
#include "../CFG_Gcc.h"
#include "../CFG_GccAutomatic.h"
#include "../CFG_Pprf.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>


CFG_HwRefreshGcc::CFG_HwRefreshGcc(CFG_AppIf& theCfgIf,
                                   CFG_GccAutomaticCfgRegion* theAutomaticCfgRegion,
                                   TSPII_GccRegion& theGccPiiRegion,
                                   TSPII_GccMapRegion& theGccMapPiiRegion,
                                   uint8 theNumLinks,
                                   CFG_AppIf* thePprfCfgApp):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myGccPiiRegion(theGccPiiRegion),
    myGccMapPiiRegion(theGccMapPiiRegion),
    myNumLinks(theNumLinks),
    myPprfCfgApp(thePprfCfgApp),
    myLastSentLinkType(CT_DCC_UNKNOWN_LINK),
    myFirstRefreshAction(true)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());

    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
   
    // Add the link profies
    if (myPprfCfgApp)
    {
        GetBbAction()->AddInputRegion(myPprfCfgApp->GetCfgRegion());
    }

    for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)
    {
        myTspiiGccMapRecords.push_back(TSPII_GccMapRecord());
    }
}

CFG_HwRefreshGcc::~CFG_HwRefreshGcc()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());

    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());

    if (myPprfCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myPprfCfgApp->GetCfgRegion());
    }
}

FC_Object* CFG_HwRefreshGcc::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Region* aCfgRegion = (GetCfgIf().GetCfgRegion());
    TSPII_GccMapIf& aGccMapPiiObject = myGccMapPiiRegion[0];
    bool aGccProcessEnabled = false;
    
    for (uint16 anIndex = 0; anIndex < myNumLinks; anIndex++)
    {
        CFG_Gcc& aCfgObject = static_cast<CFG_Gcc&>((*aCfgRegion)[(bbindex_t)anIndex]);
        TSPII_GccIf& aGccPiiObject       = myGccPiiRegion[(bbindex_t)anIndex];
        
        TSPII_GccMapRecord aTspiiGccMap;

        CT_Link_ProfileId aProfileId = UNKNOWN_Link_Profile_ID;
        bool aLinkEnabled = false;
        bool aIsProvisioned  = aCfgObject.GetIsProvisioned();

        if (!aIsProvisioned)
        {
            //reset the Configuration attributes    
            aGccPiiObject.SetGCCLinkEnabled(false);
            aGccPiiObject.SetIntfID(0xFFFFFFFF);
            aGccPiiObject.SetVlanChannel(0,0);

            //reset the PPP specific Configuration attributes
            aGccPiiObject.SetAddressType(CT_DCC_TL_UNKNOWN_TYPE);
            aGccPiiObject.SetSourceIpAddress(0);
            aGccPiiObject.SetSubnetMask(0);
            aGccPiiObject.SetDestIpAddress(0);
            aGccPiiObject.SetAutoDiscEnabled(false);
            aGccPiiObject.SetIpEnabled(false);
            aGccPiiObject.SetMaxReceiveUnits(1500);
            aGccPiiObject.SetRestartTimer(10);
            aGccPiiObject.SetMaxTerminateValue(2);
            aGccPiiObject.SetMaxConfigureValue(10);
            aGccPiiObject.SetMaxFailureValue(5); 
            aGccPiiObject.SetFCS(16);  

            // Delete the mapping            
            if(myTspiiGccMapRecords[anIndex].GccType != CT_GCC_UNKNOWN) 
            {
                aGccMapPiiObject.DeleteGccMap(myTspiiGccMapRecords[anIndex]);
                myTspiiGccMapRecords[anIndex].GccType = CT_GCC_UNKNOWN;
            }            

            continue;
        }

        CT_ODU_Identifier aGccIdentifier = aCfgObject.GetGccIdentifier();
        if(aGccIdentifier == CT_DEFAULT_ODU_ID) 
        {
            continue;
        }
        aGccPiiObject.SetVlanChannel(aCfgObject.GetVlanTag(),aCfgObject.GetChannel());
        

        aLinkEnabled = aCfgObject.GetProtocolLinkEnabled();
        if(aLinkEnabled)
        {
            aTspiiGccMap.GccIndex  = anIndex;
            aTspiiGccMap.GccType   = aGccIdentifier.GetGccTypeEnum();

            // Set Gcc & ODU Map        
            aTspiiGccMap.OduIndex  = TSPII_SubApplication::GetInstance()->GetOduPoolIndex(aGccIdentifier.GetIdValue());
            aTspiiGccMap.OduKLevel = aGccIdentifier.GetOduKvalue();
            aGccMapPiiObject.AddGccMap(aTspiiGccMap);

            // Save the record which will be used for deletion.
            myTspiiGccMapRecords[anIndex] = aTspiiGccMap;		
        }

        // Set PPP normal parameters (from TL command)
        aGccPiiObject.SetAddressType(aCfgObject.GetAddressType());
        aGccPiiObject.SetSourceIpAddress(aCfgObject.GetSourceIpAddress());
        aGccPiiObject.SetSubnetMask(aCfgObject.GetSubnetMask());
        aGccPiiObject.SetDestIpAddress(aCfgObject.GetDestIpAddress());
        aGccPiiObject.SetAutoDiscEnabled(aCfgObject.GetAutoDiscEnabled());
        aGccPiiObject.SetIpEnabled(aCfgObject.GetIpEnabled());
        aGccPiiObject.SetIntfID(aCfgObject.GetIfIndex());

        /*        
            aGccPiiObject.SetChannel(aCfgObject.GetChannel());
            aGccPiiObject.SetVlanTag(aCfgObject.GetVlanTag());
           */

        if (myPprfCfgApp)
        {
            CFG_Region* aPprfCfgRegion = myPprfCfgApp->GetCfgRegion();
            aProfileId = aCfgObject.GetPppProfileID();

            // Make sure Profile ID is in range before accessing the region.
            if (aProfileId < CT_DCC_MAX_PPP_PROFILES)
            {
                CFG_Pprf&   aPprfCfgObject = static_cast<CFG_Pprf&>((*aPprfCfgRegion)[aProfileId]);;

                aGccPiiObject.SetMaxReceiveUnits(aPprfCfgObject.GetMaxReceiveUnits());
                aGccPiiObject.SetRestartTimer(aPprfCfgObject.GetRestartTimer());
                aGccPiiObject.SetMaxTerminateValue(aPprfCfgObject.GetMaxTerminateValue());
                aGccPiiObject.SetMaxConfigureValue(aPprfCfgObject.GetMaxConfigureValue());
                aGccPiiObject.SetMaxFailureValue(aPprfCfgObject.GetMaxFailureValue());
                aGccPiiObject.SetFCS(aPprfCfgObject.GetFCS());
            }
        }  // if (myPprfCfgApp)

        // Note: TSPII is using this as a commit, so this must be last
        aGccPiiObject.SetGCCLinkEnabled(aLinkEnabled);

        //Turn on TOH global GCC enable flag if any GCC is configured not matter in IS/OOS, TL.
        aGccProcessEnabled = true;                                 
    }
    
    aGccMapPiiObject.SetGCCProcessEnabled(aGccProcessEnabled);  
    
    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;
}


