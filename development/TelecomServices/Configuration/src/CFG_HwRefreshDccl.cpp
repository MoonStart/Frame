// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_DcclIf.h>
#include "../CFG_HwRefreshDccl.h"
#include "../CFG_Dccl.h"
#include "../CFG_DcclAltConfig.h"
#include "../CFG_DcclAutomatic.h"
#include "../CFG_DcclProt.h"
#include "../CFG_Lprf.h"
#include "../CFG_Pprf.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>


CFG_HwRefreshDccl::CFG_HwRefreshDccl(CFG_AppIf& theCfgIf,
                                     CFG_DcclAutomaticCfgRegion* theAutomaticCfgRegion,
                                     TSPII_DcclRegion& theDcclPiiRegion,
                                     CFG_DcclProtCfgRegion* theProtCfgRegion,
                                     uint8 theNumLinks,
                                     CFG_AppIf* theLprfCfgApp,
                                     CFG_AppIf* thePprfCfgApp):

    CFG_HwRefreshAction(theCfgIf),
    myAutomaticCfgRegion(theAutomaticCfgRegion),
    myDcclPiiRegion(theDcclPiiRegion),
    myProtCfgRegion(theProtCfgRegion),
    myNumLinks(theNumLinks),
    myLprfCfgApp(theLprfCfgApp),
    myPprfCfgApp(thePprfCfgApp),
    myLastSentLinkType(CT_DCC_UNKNOWN_LINK),
    myFirstRefreshAction(true)
{
    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    GetBbAction()->AddInputRegion(theCfgIf.GetAltConfigRegion());
    if (myAutomaticCfgRegion) GetBbAction()->AddInputRegion(myAutomaticCfgRegion);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    // Add the link profies
    if (myLprfCfgApp)
    {
        GetBbAction()->AddInputRegion(myLprfCfgApp->GetCfgRegion());
    }
    if (myPprfCfgApp)
    {
        GetBbAction()->AddInputRegion(myPprfCfgApp->GetCfgRegion());
    }
    if (myProtCfgRegion)
    {
        GetBbAction()->AddInputRegion(myProtCfgRegion);
    }
}

CFG_HwRefreshDccl::~CFG_HwRefreshDccl()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetAltConfigRegion());
    if (myAutomaticCfgRegion) GetBbAction()->RemoveInputRegion(myAutomaticCfgRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    // Add the link profies
    if (myLprfCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myLprfCfgApp->GetCfgRegion());
    }
    if (myPprfCfgApp)
    {
        GetBbAction()->RemoveInputRegion(myPprfCfgApp->GetCfgRegion());
    }
    if (myProtCfgRegion)
    {
        GetBbAction()->RemoveInputRegion(myProtCfgRegion);
    }
}

FC_Object* CFG_HwRefreshDccl::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{

    CFG_Region* aCfgRegion = (GetCfgIf().GetCfgRegion());
    CFG_Region* aAltConfigRegion = (GetCfgIf().GetAltConfigRegion());
    // Use myNumLinks constructor variable rather than size of region
    // due to Context Collapse changes
    // uint32 aCfgRegionSize = 0;
    // if (aCfgRegion)
    // {
    //     aCfgRegionSize = aCfgRegion->Size();
    // }

    for (uint32 anIndex = 0; anIndex < myNumLinks; anIndex++)
    {
        CFG_Dccl& aCfgObject = static_cast<CFG_Dccl&>((*aCfgRegion)[(bbindex_t)anIndex]);
        CFG_Dccp& aAltConfigObject = static_cast<CFG_Dccp&>((*aAltConfigRegion)[(bbindex_t)anIndex]);
        TSPII_DcclIf& aDcclPiiObject = myDcclPiiRegion[(bbindex_t)anIndex];

        // Set Force Internal AIS either from default (false) or, if present, from the Automatic Action
        /*
        bool aDisableLink = false;
        if (myAutomaticCfgRegion)
        {
           CFG_DcclAutomatic& aAutomaticCfgObject = (*myAutomaticCfgRegion)[(bbindex_t)anIndex];

           // Determine whether to Force Internal AIS (set by Automatic Action)
           aDisableLink = aAutomaticCfgObject.GetDisableLink();
        }*/

        //For laps broadcast
        uint8 aRemotePort = DCC_INVALID_PROT_REMOTE_PORT;
        CT_DCC_BroadcastMode aBroadcastMode = CT_DCC_TERMINATE;
        CT_DCC_SelectionMode aSelectionMode = CT_DCC_LOCAL;
        bool aIsRxSelected = true; /*Assume rx dcc traffic selected from this port*/
        bool aFollowProtection = false;

        CT_Link_ProfileId aProfileId = UNKNOWN_Link_Profile_ID;
        // Set up default values for the two most important data values for TSPII
        CT_DCC_LinkType aLinkType = CT_DCC_NOT_CONFIGURED_LINK;
        bool aLinkEnabled = false;


        // First, read the IsProvisioned field to determine which link is active.
        // If neither is provisioned or both are provisioned,
        // keep the link type to Not Configured and keep LinkEnabled at false
        bool aIsLapdLinkType = aCfgObject.GetIsProvisioned();
        bool aIsPPPLinkType  = aAltConfigObject.GetIsProvisioned();

        if (aIsLapdLinkType != aIsPPPLinkType)
        {
            if (aIsLapdLinkType)
            {
                aLinkType = CT_DCC_LAPD_LINK;
            }  // if (aLapdLinkType)
            else if (aIsPPPLinkType)
            {
                aLinkType = CT_DCC_PPP_LINK;
            }
        }


        // Tspii needs to know if the link type changed, If it has, then:
        // (a) set the Link Enabled to false (just in case this didn't already come down)
        // (b) send down a clearing field for each link type,
        // (c) set the Link Type to Not Configured
        // (d) set the Link Enabled to false.
        //if (aLinkType != myLastSentLinkType)
        //{
        //    aDcclPiiObject.SetProtocolLinkEnabled(false);
        //
        //    // aDcclPiiObject.SetIntfID(0);
        //    // aDcclPiiObject.SetSourceIpAddress(0);
        //
        //    aDcclPiiObject.SetDccLinkType(CT_DCC_NOT_CONFIGURED_LINK);
        //    aDcclPiiObject.SetProtocolLinkEnabled(false);
        //}

        // Write Link Type, which are determined above.
        aDcclPiiObject.SetDccLinkType(aLinkType);
        // myLastSentLinkType = aLinkType;


        // Write the other data based on the link type
        if (aLinkType == CT_DCC_LAPD_LINK)
        {
               aLinkEnabled = aCfgObject.GetProtocolLinkEnabled();

               //Set normal Configuration parameters
               //Set the Lapd normal parameters.
               aDcclPiiObject.SetLinkRouterID(aCfgObject.GetLinkRouterID());
               aDcclPiiObject.SetRouterShelfID(aCfgObject.GetRouterShelfID());
               aDcclPiiObject.SetIntfID(aCfgObject.GetIntfID());

               //For LAPS broadcast
               if (myProtCfgRegion)
               {
                   CFG_DcclProt& aProtCfgObject = (*myProtCfgRegion)[(bbindex_t)anIndex];

                   if (aCfgObject.GetFollowProtection())
                   {
                       aFollowProtection = true;
                       // Determine whether paired with a remote port (LAPS broadcast)
                       aRemotePort = aProtCfgObject.GetRemotePort();
                       //Determine whether to select/broadcast (LAPS broadcast)
                       aBroadcastMode = aProtCfgObject.GetBroadcastMode();
                       aSelectionMode = aProtCfgObject.GetSelectionMode();
                       aIsRxSelected = aProtCfgObject.GetRxSelected();
                   }
               }

               // Now we have to find the correct Link Profile and
               // send down that information

               if (myLprfCfgApp)
               {
                   CFG_Region* aLprfCfgRegion = myLprfCfgApp->GetCfgRegion();
                   aProfileId = aCfgObject.GetLinkProfileID();

                   // Make sure Profile ID is in range before accessing the region.
                   if (aProfileId < CT_DCC_MAX_LAPD_PROFILES)
                   {
                       CFG_Lprf&   aLprfCfgObject = static_cast<CFG_Lprf&>((*aLprfCfgRegion)[aProfileId]);;

                       aDcclPiiObject.SetTransferMode(aLprfCfgObject.GetTransferMode());
                       aDcclPiiObject.SetRetransmissionCount(aLprfCfgObject.GetRetransmissionCount());
                       aDcclPiiObject.SetAckWaitTimer(aLprfCfgObject.GetAckWaitTimer());
                       aDcclPiiObject.SetMaxFrameSize(aLprfCfgObject.GetMaxFrameSize());
                       aDcclPiiObject.SetFrameCount(aLprfCfgObject.GetFrameCount());
                       aDcclPiiObject.SetInactivityTimer(aLprfCfgObject.GetInactivityTimer());
                       aDcclPiiObject.SetSideAssignment(aLprfCfgObject.GetSideAssignment());
                       aDcclPiiObject.SetSequenceRange(aLprfCfgObject.GetSequenceRange());
                   }
               }  // if (myLprfCfgApp)

        }  // if (aLapdLinkType)
        else if (aLinkType == CT_DCC_PPP_LINK)
        {
                aLinkEnabled = aAltConfigObject.GetProtocolLinkEnabled();

                //For LAPS broadcast
                if (myProtCfgRegion)
                {
                   CFG_DcclProt& aProtCfgObject = (*myProtCfgRegion)[(bbindex_t)anIndex];

                   if (aAltConfigObject.GetFollowProtection())
                   {
                       aFollowProtection = true;
                       // Determine whether paired with a remote port (LAPS broadcast)
                       aRemotePort = aProtCfgObject.GetRemotePort();
                       //Determine whether to select/broadcast (LAPS broadcast)
                       aBroadcastMode = aProtCfgObject.GetBroadcastMode();
                       aSelectionMode = aProtCfgObject.GetSelectionMode();
                       aIsRxSelected = aProtCfgObject.GetRxSelected();
                   }
                }

                // Set PPP normal parameters (from TL command)
                aDcclPiiObject.SetAddressType(aAltConfigObject.GetAddressType());
                aDcclPiiObject.SetSourceIpAddress(aAltConfigObject.GetSourceIpAddress());
                aDcclPiiObject.SetSubnetMask(aAltConfigObject.GetSubnetMask());
                aDcclPiiObject.SetDestIpAddress(aAltConfigObject.GetDestIpAddress());
                aDcclPiiObject.SetAutoDiscEnabled(aAltConfigObject.GetAutoDiscEnabled());
                aDcclPiiObject.SetIpEnabled(aAltConfigObject.GetIpEnabled());
                aDcclPiiObject.SetIntfID(aAltConfigObject.GetIfIndex());
                
                if (myPprfCfgApp)
                {
                    CFG_Region* aPprfCfgRegion = myPprfCfgApp->GetCfgRegion();
                    aProfileId = aAltConfigObject.GetPppProfileID();

                    // Make sure Profile ID is in range before accessing the region.
                    if (aProfileId < CT_DCC_MAX_PPP_PROFILES)
                    {
                        CFG_Pprf&   aPprfCfgObject = static_cast<CFG_Pprf&>((*aPprfCfgRegion)[aProfileId]);;

                        aDcclPiiObject.SetMaxReceiveUnits(aPprfCfgObject.GetMaxReceiveUnits());
                        aDcclPiiObject.SetRestartTimer(aPprfCfgObject.GetRestartTimer());
                        aDcclPiiObject.SetMaxTerminateValue(aPprfCfgObject.GetMaxTerminateValue());
                        aDcclPiiObject.SetMaxConfigureValue(aPprfCfgObject.GetMaxConfigureValue());
                        aDcclPiiObject.SetMaxFailureValue(aPprfCfgObject.GetMaxFailureValue());
						aDcclPiiObject.SetFCS(aPprfCfgObject.GetFCS());
                    }
                }  // if (myPprfCfgApp)
        }  // else if (aPPPLinkType)

        //Always write the laps broadcast paramters
        aDcclPiiObject.SetDccRemoteSfp(aRemotePort);
        aDcclPiiObject.SetDccBroadcastMode(aBroadcastMode);
        aDcclPiiObject.SetDccSelectionMode(aSelectionMode);
        aDcclPiiObject.SetFollowProtection(aFollowProtection);
        aDcclPiiObject.SetRxSelected(aIsRxSelected);

        // Note: TSPII is using this as a commit, so this must be last
        aDcclPiiObject.SetProtocolLinkEnabled(aLinkEnabled);

    }
    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}


