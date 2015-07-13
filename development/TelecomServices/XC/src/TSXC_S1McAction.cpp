/*----------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage One Multicast Action Implementaion.
----------------------------------------------*/
#include <XC/TSXC_S1McAction.h>
#include <XC/TSXC_BaseApplication.h>
#include <CommonTypes/CT_FabMulticast.h>
#include <TsPii/TSPII_SsmIf.h>
#include <TsPii/TSPII_FabIf.h>
#include <TsPii/TSPII_SubApplication.h>

//-----------------------------------------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------------------------------------
TSXC_S1McAction::TSXC_S1McAction(T6100_CardIf& theCardContext) :
    TSXC_BaseAction(theCardContext),
    myS1McCfg_Region(NULL),
    myXCBrMCastMask_Region(NULL),
    myMiscConfig_Region(NULL)
{

}

//-----------------------------------------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------------------------------------
TSXC_S1McAction::~TSXC_S1McAction()
{

}

//-----------------------------------------------------------------------------------------------------------
// Get Methods
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
// Set Methods
//-----------------------------------------------------------------------------------------------------------
void TSXC_S1McAction::SetS1McCfgRegion(TSXC_S1McRegion<TSXC_S1MCast>* theS1McCfgRegion)
{
    myS1McCfg_Region = theS1McCfgRegion;
}

void TSXC_S1McAction::SetBrMaskRegion(TSXC_BrMCastMaskRegion<TSXC_BrMCastMask>* theBrMaskRegion)
{
    myXCBrMCastMask_Region = theBrMaskRegion;
}

void TSXC_S1McAction::SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion)
{
    myMiscConfig_Region = theMiscCfgRegion;
}


//-----------------------------------------------------------------------------------------------------------
// Do the work
//-----------------------------------------------------------------------------------------------------------
FC_Object* TSXC_S1McAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    bool           ValidCardProvisioned;
    bool           aSsmInMeshMode = false;
    CT_CardType    aCardType;

    aCardType              = myS1McCfg_Region->GetMyCardType();
    ValidCardProvisioned   = ( aCardType == CARD_TYPE_SSMX || 
                               aCardType == CARD_TYPE_SSMD ||
                               aCardType == CARD_TYPE_OSM20);

    if (myMiscConfig_Region != NULL)
    {
        aSsmInMeshMode = (*myMiscConfig_Region)[0].IsMeshMode();
    }

    if (aSsmInMeshMode && ValidCardProvisioned)
    {
        // NANO Mesh processing for multicast connections

        TSXC_S1MCast*     MC_CfgObjectPtr;
        TSXC_BrMCastMask* MC_BrMaskObjectPtr;
        CT_FabMcMember    aFabMember;
        int               idx;
        int               slotIndex;
        uint16            mcastId;
        uint16            maskMcastId;
        bool              isMaskSet;
        int               maxMcastRegionIdx = (*myS1McCfg_Region).Size();
        uint8             aMaskAction = CT_XC_BR_MASK_NONE;
        uint32            aMCastImuxLMask = 0;
        uint32            aMCastImuxPMask = 0;
        TSPII_FabIf&      tspiiFabIf = (*(TSPII_SubApplication::GetInstance()->GetFab()))[0];

        // set start time if debug level was set.
        START_TIME(TSXC_DEBUG_LEVEL01);

        // Get Mask info and store it for efficiency
        MC_BrMaskObjectPtr = &((*myXCBrMCastMask_Region)[0]);
        maskMcastId = MC_BrMaskObjectPtr->GetMCastId();
        isMaskSet = MC_BrMaskObjectPtr->IsMaskSet();

        // Delete all Mc Groups.  Will add necessary ones below.
        tspiiFabIf.DeleteAllMcGroups();

        for (idx = 0; idx < maxMcastRegionIdx; idx++)
        {
            aMaskAction = CT_XC_BR_MASK_NONE;
            aMCastImuxLMask = 0;
            aMCastImuxPMask = 0;

            MC_CfgObjectPtr = &((*myS1McCfg_Region)[idx]);

            // Only process this object if multicast exists
            if (MC_CfgObjectPtr->IsImuxSet())
            {
                // Ingress SSM
                mcastId = MC_CfgObjectPtr->GetMCastId();
                vector<CT_FabMcMember> aFabMemberList;
            
                // If mask is set and Id matches, retrieve mask info
                if ( (isMaskSet) && (mcastId == maskMcastId) )
                {
                    aMaskAction = MC_BrMaskObjectPtr->GetMaskAction();
                    aMCastImuxLMask = MC_BrMaskObjectPtr->GetMCastImuxLMask();
                    aMCastImuxPMask = MC_BrMaskObjectPtr->GetMCastImuxPMask();
                }

                // Build FabMember info.
                for (slotIndex = 0; slotIndex < NUMBER_OF_SSM_IN_NANO_PORT_SHELF; slotIndex++)
                {
                    aFabMember.RemShelf = (uint8)(1);
                    aFabMember.RemSlot = slotIndex;
                    aFabMember.RemImux = 0xff;
        
                    if ( MC_CfgObjectPtr->IsImuxSet(CT_XC_IMUXL, slotIndex, aMCastImuxLMask, aMaskAction) )
                    {
                        aFabMember.RemImux = CT_XC_IMUXL;
                        aFabMemberList.push_back(aFabMember);
                    }
        
                    if ( MC_CfgObjectPtr->IsImuxSet(CT_XC_IMUXP, slotIndex, aMCastImuxPMask, aMaskAction) )
                    {
                        aFabMember.RemImux = CT_XC_IMUXP;
                        aFabMemberList.push_back(aFabMember);
                    }
                }

                // Add this Mc Group
                tspiiFabIf.SetMcGroup( mcastId, aFabMemberList );
            }
        }

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage one MCAST provision time : ");

        START_TIME(TSXC_DEBUG_LEVEL01);

        tspiiFabIf.CommitMcGroups();

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage one MCAST commit time : ");        

        Respond(myS1McCfg_Region->GetCQMRequest());

    }
    return NULL;
}

//-----------------------------------------------------------------------------------------------------------
