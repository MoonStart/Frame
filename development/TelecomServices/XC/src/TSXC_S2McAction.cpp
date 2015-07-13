/*------------------------------------------------------------
    Copyright(c) Tellabs Transport Group. All rights reserved

    SUBSYSTEM:     Cross Connect
    TARGET   :     All
    AUTHOR   :     April, 2009 Kumar Solai 
    DESCRIPTION:   TSXC Stage Two Multicast Action Implementaion.
------------------------------------------------------------*/
#include <XC/TSXC_S2McAction.h>
#include <XC/TSXC_BaseApplication.h>
#include <CommonTypes/CT_FabMulticast.h>
#include <TsPii/TSPII_SsmIf.h>
#include <TsPii/TSPII_Region.h>
#include <TsPii/TSPII_FabIf.h>
#include <TsPii/TSPII_SwitchIf.h>
#include <TsPii/TSPII_SubApplication.h>
#include <CsPii/CSPII_CardIF.h>

//--------------------------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------------------------
TSXC_S2McAction::TSXC_S2McAction(T6100_CardIf& theCardContext, uint16 theFirstMcastId) :
    TSXC_BaseAction(theCardContext),
    myS2McCfg_Region(NULL),
    myMiscConfig_Region(NULL),
    myFirstMcastId(theFirstMcastId)
{
    // Create local/private region for cacheing
    myPrevS2McCfg_Region = new TSXC_S2McRegion<TSXC_S2MCast>("noname");
    //--- Make sure the region size is set correctly.
    //    Note:  S2MCast region is same size for all fabric cards
    myPrevS2McCfg_Region->SetMyCardType(CSPII_CardIF::GetInstance()->GetCardType());

    // To force initial invocations to TSPII, info in previous region 
    // is set as invalid.
    for (size_t regionIndex = 0; regionIndex < myPrevS2McCfg_Region->Size(); regionIndex++)
    {
        (*myPrevS2McCfg_Region)[regionIndex].InitMCastPrev();
    }
}

//--------------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------------
TSXC_S2McAction::~TSXC_S2McAction()
{
    delete myPrevS2McCfg_Region;
    myPrevS2McCfg_Region = NULL;
}

//--------------------------------------------------------------------------------------------------------
// Get Methods
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
// Set Methods
//--------------------------------------------------------------------------------------------------------
void TSXC_S2McAction::SetS2McRegion(TSXC_S2McRegion<TSXC_S2MCast>*   theS2McCfgRegion)
{
    myS2McCfg_Region = theS2McCfgRegion;
}

void TSXC_S2McAction::SetMiscCfgRegion(CFG_MiscCfgRegion* theMiscCfgRegion)
{
    myMiscConfig_Region = theMiscCfgRegion;
}

//--------------------------------------------------------------------------------------------------------
// Helper Methods
//--------------------------------------------------------------------------------------------------------
uint8 TSXC_S2McAction::BitPositionToTspiiSlot(uint8   theBitPos, CT_CardType  theCardType)
{
    uint8   tspiiSlot;
    char    errMsg[80];

    /**** tspiiSlot is 0-based ****/

    switch (theCardType)
    {
        case CARD_TYPE_SPFAB:
            tspiiSlot = theBitPos;
            break;

        case CARD_TYPE_UFAB:
            switch(theBitPos)
            {
                case 0:  tspiiSlot = 1;    break;
                case 1:  tspiiSlot = 2;    break;
                case 2:  tspiiSlot = 3;    break;
                case 3:  tspiiSlot = 4;    break;
                case 4:  tspiiSlot = 5;    break;
                case 5:  tspiiSlot = 6;    break;
                case 6:  tspiiSlot = 7;    break;

                case 7:  tspiiSlot = 11;   break;
                case 8:  tspiiSlot = 12;   break;
                case 9:  tspiiSlot = 13;   break;
                case 10: tspiiSlot = 14;   break;
                case 11: tspiiSlot = 15;   break;
                case 12: tspiiSlot = 16;   break;
                case 13: tspiiSlot = 17;   break;

                default: 
                    tspiiSlot = 0xff;
                    sprintf(errMsg, "Invalid BitPosition = %d", theBitPos);
                    FC_THROW_ERROR(FC_RuntimeError, errMsg);
                    break;
            }
            break;

        case CARD_TYPE_MFAB:
            switch(theBitPos)
            {
                case 0:  tspiiSlot = 0;    break;
                case 1:  tspiiSlot = 1;    break;
                case 2:  tspiiSlot = 2;    break;
                case 3:  tspiiSlot = 3;    break;
                case 4:  tspiiSlot = 4;    break;
                case 5:  tspiiSlot = 5;    break;
                case 6:  tspiiSlot = 6;    break;

                case 7:  tspiiSlot = 9;    break;
                case 8:  tspiiSlot = 10;   break;
                case 9:  tspiiSlot = 11;   break;
                case 10: tspiiSlot = 12;   break;
                case 11: tspiiSlot = 13;   break;
                case 12: tspiiSlot = 14;   break;
                case 13: tspiiSlot = 15;   break;

                default: 
                    tspiiSlot = 0xff;
                    sprintf(errMsg, "Invalid BitPosition = %d", theBitPos);
                    FC_THROW_ERROR(FC_RuntimeError, errMsg);
                    break;
            }
            break;

        default:
            tspiiSlot = 0xff;
            sprintf(errMsg, "Invalid CardType = %d", theCardType);
            FC_THROW_ERROR(FC_RuntimeError, errMsg);
            break;
    }

    return tspiiSlot;
}

//--------------------------------------------------------------------------------------------------------
void TSXC_S2McAction::ProcessUFABE()
{
    TSXC_S2MCast*            MC_CfgObjectPtr;
    TSXC_S2MCast*            MC_PrevCfgObjectPtr;
    int                      maxMcastRegionIdx = myS2McCfg_Region->Size();
    int                      idx;
    int                      trueIdx;

    TSPII_FabIf&    tspiiFabIf      = (*(TSPII_SubApplication::GetInstance()->GetFab()))[0];
    CT_CardType     aCardType       = myPrevS2McCfg_Region->GetMyCardType();

    for (idx = 0; idx < maxMcastRegionIdx; idx++)
    {
        trueIdx = myFirstMcastId + idx;
        // Skip McIds 16382 and 16383 since they are reserved
        if ( trueIdx < 16382 )
        {
            MC_CfgObjectPtr     = &((*myS2McCfg_Region)[idx]);
            MC_PrevCfgObjectPtr = &((*myPrevS2McCfg_Region)[idx]);
                
            if (*MC_CfgObjectPtr != *MC_PrevCfgObjectPtr)
            {
                if (MC_CfgObjectPtr->IsEmpty())
                {
                    // Call TSPII to delete this mcastId, commit immediately
                    tspiiFabIf.DeleteMcGroup( trueIdx, true );
                }
                else
                {
                    CT_FabMcMember           aFabMember;
                    vector<CT_FabMcMember>   aFabMemberList;
                    uint16                   aShelfImuxSlotMap;
                    uint8                    shelf;
                    uint8                    bitPos;
                    TSXC_DESTINATION         mcastDest[TSXC_MAX_SHELF_PER_MCAST];

                    // Retrieve destinations for mcast group
                    MC_CfgObjectPtr->GetShelfSlots(mcastDest);
                    // Iterate through all dest shelves
                    for(shelf = 0; shelf < TSXC_MAX_SHELF_PER_MCAST; shelf++)
                    {
                        // Only handle this entry if it is associated with a valid shelf.
                        if (mcastDest[shelf].Shelf != 0)
                        {
                            // convert shelf to logical (if necessary)
                            aFabMember.RemShelf = PhysToLogicalShelf(mcastDest[shelf].Shelf,                // PhysicalShelf (1-based)
                                                        (*myMiscConfig_Region)[0].GetSwitchMode(),          // switchMode
                                                        (*myMiscConfig_Region)[0].GetSwitchDomainMode());   // SwitchDomain Mode
                            aShelfImuxSlotMap   = mcastDest[shelf].ImuxSlotMap;
                            // Iterate through all dest slots on this shelf
                            for(bitPos = 0; bitPos < TSXC_MAX_SLOT_PER_SLOTMAP; bitPos++)
                            {
                                // If this dest slot is set, add it to the list of members
                                if ( ((1 << bitPos) & (aShelfImuxSlotMap)) != 0 )
                                {
                                    aFabMember.RemSlot = BitPositionToTspiiSlot(bitPos, aCardType);
                                    aFabMemberList.push_back(aFabMember);
                                }
                            }
                        } 
                        // Call TSPII to add this mcastId, commit immediately
                        tspiiFabIf.SetMcGroup( trueIdx, aFabMemberList, true );
                    }
                }
                // Copy new to previous info
                *MC_PrevCfgObjectPtr = *MC_CfgObjectPtr;
            }
        }
    }
    // Note: A single commit for all McGroups is not performed since multiple
    //       actions modify McGroups.  At lower layers, all McGroups are treated
    //       as a unit.  Committing all McGroups in one action before other 
    //       actions run could result in an incomplete McGroup unit.                                       
}

//--------------------------------------------------------------------------------------------------------
void TSXC_S2McAction::ProcessMFAB()
{
    TSXC_S2MCast*            MC_CfgObjectPtr;
    TSXC_S2MCast*            MC_PrevCfgObjectPtr;
    int                      maxMcastRegionIdx = myS2McCfg_Region->Size();
    int                      idx;
    int                      trueIdx;

    TSPII_FabIf&    tspiiFabIf      = (*(TSPII_SubApplication::GetInstance()->GetFab()))[0];
    CT_CardType     aCardType       = myPrevS2McCfg_Region->GetMyCardType();

    for (idx = 0; idx < maxMcastRegionIdx; idx++)
    {
        trueIdx = myFirstMcastId + idx;

        // McastId 64*1024 - 3 = 65533 is reserved for PQW so leave
        // mcastIds 65533 and higher alone.
        if ( trueIdx < ((64*1024) - 3) ) 
        {
            MC_CfgObjectPtr     = &((*myS2McCfg_Region)[idx]);
            MC_PrevCfgObjectPtr = &((*myPrevS2McCfg_Region)[idx]);
                
            if (*MC_CfgObjectPtr != *MC_PrevCfgObjectPtr)
            {
                if (MC_CfgObjectPtr->IsEmpty())
                {
                    // Call TSPII to delete this mcastId, commit immediately
                    tspiiFabIf.DeleteMcGroup( trueIdx, true );
                }
                else
                {
                    CT_FabMcMember           aFabMember;
                    vector<CT_FabMcMember>   aFabMemberList;
                    uint16                   aShelfImuxSlotMap;
                    uint8                    shelf;
                    uint8                    bitPos;
                    TSXC_DESTINATION         mcastDest[TSXC_MAX_SHELF_PER_MCAST];

                    // Retrieve destinations for mcast group
                    MC_CfgObjectPtr->GetShelfSlots(mcastDest);

                    // MFABs only exist on single shelf
                    shelf = 0;

                    aFabMember.RemShelf = 0;
                    aFabMember.RemImux = 0;
                    aShelfImuxSlotMap   = mcastDest[shelf].ImuxSlotMap;

                    // Iterate through all dest slots on this shelf
                    for(bitPos = 0; bitPos < TSXC_MAX_SLOT_PER_SLOTMAP; bitPos++)
                    {
                        // If this dest slot is set, add it to the list of members
                        if ( ((1 << bitPos) & (aShelfImuxSlotMap)) != 0 )
                        {
                            aFabMember.RemSlot = BitPositionToTspiiSlot(bitPos, aCardType);
                            aFabMemberList.push_back(aFabMember);
                        }
                    }

                    // Call TSPII to add this mcastId, commit immediately
                    tspiiFabIf.SetMcGroup( trueIdx, aFabMemberList, true );
                }
                // Copy new to previous info
                *MC_PrevCfgObjectPtr = *MC_CfgObjectPtr;
            }
        }
    }
    // Note: A single commit for all McGroups is not performed since multiple
    //       actions modify McGroups.  At lower layers, all McGroups are treated
    //       as a unit.  Committing all McGroups in one action before other 
    //       actions run could result in an incomplete McGroup unit.                                       
}

//--------------------------------------------------------------------------------------------------------
// Do the work
//--------------------------------------------------------------------------------------------------------
FC_Object* TSXC_S2McAction::DoRunWithReason(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam)
{
    bool ValidCardProvisioned;
    CT_CardType aCardType = myPrevS2McCfg_Region->GetMyCardType();
    ValidCardProvisioned = ( (aCardType == CARD_TYPE_UFAB)  || 
                             (aCardType == CARD_TYPE_SPFAB) || 
                             (aCardType == CARD_TYPE_MFAB) );
 
    //
    // Iterate through regions only if valid card is provisioned.
    //
    if (ValidCardProvisioned  == true)
    {
        // set start time if debug level was set.
        START_TIME(TSXC_DEBUG_LEVEL01);

        switch(aCardType)
        {
            case CARD_TYPE_UFAB:
            case CARD_TYPE_SPFAB:
                ProcessUFABE();
                break;
            case CARD_TYPE_MFAB:
                ProcessMFAB();
                break;
        }

        END_TIME(TSXC_DEBUG_LEVEL01);
        PRINT_TIME(TSXC_DEBUG_LEVEL01,"TSXC_DEBUG_INFO: Stage two MCAST provision time : ");

        Respond(myS2McCfg_Region->GetCQMRequest());
    }
    return NULL;
}

