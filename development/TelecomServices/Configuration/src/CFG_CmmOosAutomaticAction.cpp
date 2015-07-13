/*******************************************************************************
 *
 *             Copyright:  (c)2005 Tellabs Operations, Inc.
 *                         All Rights Reserved.
 *
 * -----------------------------------------------------------------------------
 *
 *    MODULE:        CFG_CmmOosAutomaticAction.cpp
 *    DATE:          11/16/2005
 *    AUTHOR:        qdurrani
 *
 *    SUBSYSTEM:     Configuration
 *    OVERVIEW:      CMM Out-of-service processing action
 *    FEATURE PACK:  FP3.3
 *
 * -----------------------------------------------------------------------------
 *
 *    NOTES:         Since inorder to support OLA to SBOADM upgrade feature
 *                   context for all the DUMP modules is created even in the
 *                   OLA configuration, a check is made everytime this action
 *                   runs to verify that its not running in the context of OLA.
 *                   If in the OLA configuration then this action does NO-OP.
 *
 ******************************************************************************/
#include "../CFG_CmmOosAutomaticAction.h"
#include "../CFG_CmmOosAutomatic.h"
#include <Configuration/CFG_OmsSubApplication.h>
#include <Blackboard/FC_BbAction.h>
#include <CSM/CSM_AppIf.h>
#include <CSM/CSM_CardStatusRegion.h>
#include <T6100_MainAppIf.h>
#include <T6100_OpticalShelfSlotIf.h>
#include <T6100_OpticalShelfIf.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <T6100_TelecomIf.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <CsPii/CSPII_CardIF.h>

///////////////////////////////////////////////////////////////////////////////
CFG_CmmOosAutomaticAction::CFG_CmmOosAutomaticAction(CFG_OmsSubApplication&     theCfgApp,
                                                     CFG_CmmOosAutomaticRegion* theCmmOosAutomaticRegion) :
    myBbAction(NULL),
    myCfgApp(theCfgApp),
    myCmmOosAutomaticRegion(theCmmOosAutomaticRegion),
    myIamMonDefectRegion(NULL),
    myIamCardStatusRegion(NULL)
{
    myBbAction  = new FC_BbAction(this);
    uint32 i =0;
    int j=0;
    for (i=0; i< CMM_OOS_MAX_CSM_REGIONS; i++)
    {
        myCmmCardStatusRegions[i] = NULL;
        myCmmCardConfigRegions[i] = NULL;
    }


    //-----------------------------------------------------------------------------------
    // register to RCMM CSM regions
    //-----------------------------------------------------------------------------------
    CT_SubNodeConfiguration aSubNodeCfg = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg();
    CT_ShelfId curShelfId = (CT_ShelfId)CSPII_CardIF::GetInstance()->GetShelfId();
    uint32 numberOfSlotInOpticalShelf = aSubNodeCfg.GetNumberOfSlotsInOpticalShelf();

    T6100_MainAppIf& aMainApp = T6100_MainAppIf::Instance();
    for(i = 1; i <= numberOfSlotInOpticalShelf; ++i)
    {
        //scan each slot in shelf to find quad, scad or cmm/rcmm
        T6100_OpticalShelfSlotIf& aSlotIf = aMainApp.GetOpticalShelf(curShelfId).GetOSSlotIf((CT_SlotId)i);

        // for now only monitor the RCMMs, in ECMM type of system
        // requires it then we can add it.
        T6100_CardIf* aCardIf = aSlotIf.GetCardPtr(RCMM_FAM);

        //match the family and side
        if( aCardIf &&
            aCardIf->GetCardFamily() == RCMM_FAM &&
            aCardIf->GetSupportedSide() == myCfgApp.GetOmsSubAppContext().GetSupportedSide() )
        {
            // register for card state
            myCmmCardStatusRegions[j] = &aSlotIf.GetCsmApp().GetCardStatusRegion();
            myCmmCardConfigRegions[j] = &aSlotIf.GetCsmApp().GetCardConfigStatusRegion();

            if(myCmmCardStatusRegions[j])
                myBbAction->AddInputRegion(myCmmCardStatusRegions[j]);
            if(myCmmCardConfigRegions[j])
                myBbAction->AddInputRegion(myCmmCardConfigRegions[j]);

            j++;

            if (j == CMM_OOS_MAX_CSM_REGIONS)
                break; //we have found what we were looking for
        }
    }

    //-----------------------------------------------------------------------------------
    // register the output region
    //-----------------------------------------------------------------------------------
    if(myCmmOosAutomaticRegion)
        myBbAction->AddOutputRegion(myCmmOosAutomaticRegion, false);
}

///////////////////////////////////////////////////////////////////////////////
CFG_CmmOosAutomaticAction::~CFG_CmmOosAutomaticAction()
{
    if(myCmmOosAutomaticRegion)
        myBbAction->RemoveOutputRegion(myCmmOosAutomaticRegion);
        
    delete myBbAction;
}

///////////////////////////////////////////////////////////////////////////////
bool CFG_CmmOosAutomaticAction::IsActionValid()
{
    bool rVal = false;

    int i= 0;

    if (!myCmmOosAutomaticRegion)
        return false;

    for (i=0; i< CMM_OOS_MAX_CSM_REGIONS; i++)
    {
        //if atleast one set of regions are present, return true
        if(myCmmCardStatusRegions[i] && myCmmCardConfigRegions[i])
        {
            rVal = true;
        }
    }

    return(rVal);
}

///////////////////////////////////////////////////////////////////////////////
void CFG_CmmOosAutomaticAction::Run(FC_Object* theObject)
{
    if(!IsActionValid() ||
       CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsNeOLA())
    {
        return;
    }

    //With the addition of spurs, the algorithm to mute the input amplifier
    //is changed as follows:
    //If a slot has RCMM4/8/44S/S provisioned, consider this slot for amp shutdown logic
    //If a slot has CMM-44 provisioned check to make sure mate slot does not have RCMMx provisioned.
    //Consider a CMM44 slot for amp shutdown if mate slot does not have RCMMx provisioned.
    //If neither slot has anything provisioned, then shutdown the amplifier
    CSM_CardConfigStatusRegion* aConfigRegion = NULL;
    CSM_CardStatusRegion* aStatusRegion = NULL;
    CT_CardType cards[CMM_OOS_MAX_CSM_REGIONS] = {CARD_TYPE_UNKNOWN, CARD_TYPE_UNKNOWN};
    CT_Status cardStatus[CMM_OOS_MAX_CSM_REGIONS] = {CT_ABSENT, CT_ABSENT};

    int i=0;

    for (i=0; i< CMM_OOS_MAX_CSM_REGIONS; i++)
    {
        if (myCmmCardConfigRegions[i])
        {
            aConfigRegion = myCmmCardConfigRegions[i];
            CSM_PersistentConfigStatus&  aCSMCfg = (*aConfigRegion)[0];
            if (aCSMCfg.IsCardProvisionned() == true)
            {
                list<CT_PartNumber>* aPnList = aCSMCfg.GetProvisionConfigList();
                cards[i] = aPnList->front().GetCardType();
                aStatusRegion = myCmmCardStatusRegions[i];
                CSM_CardStatus&      aCsm    = (*aStatusRegion)[0];
                cardStatus[i] = aCsm.GetCardStatus();
            }
        }
    }

    bool hasChanged = false;
    CFG_CmmOosAutomatic& aCmmOos = (*myCmmOosAutomaticRegion)[0];

    int otherSlot = 0;
    CT_CardType otherSlotCardType = CARD_TYPE_UNKNOWN;
    bool isComplete = false;

    for (i=0; i< CMM_OOS_MAX_CSM_REGIONS; i++)
    {
        switch (cards[i])
        {
        case CARD_TYPE_RCMM:
        case CARD_TYPE_RCMMS:
        case CARD_TYPE_RCMMS44:
        case CARD_TYPE_MRCMMCX8:
            if (cardStatus[i] != CT_ABSENT)
            {
                hasChanged |= aCmmOos.SetAmplifierShutdown(false);
            }
            else
            {
                hasChanged |= aCmmOos.SetAmplifierShutdown(true);
            }
            isComplete = true;
            break;
        case CARD_TYPE_CMM44:
            otherSlot = (i==0 ? 1: 0);
            otherSlotCardType = cards[otherSlot];
            if (otherSlotCardType != CARD_TYPE_RCMM &&
                otherSlotCardType != CARD_TYPE_RCMMS &&
                otherSlotCardType != CARD_TYPE_RCMMS44 &&
                otherSlotCardType != CARD_TYPE_MRCMMCX8)
            {
                if (cardStatus[i] != CT_ABSENT)
                {
                    hasChanged |= aCmmOos.SetAmplifierShutdown(false);
                }
                else
                {
                    hasChanged |= aCmmOos.SetAmplifierShutdown(true);
                }
                isComplete = true;
            }
            break;
        default:
            break;
        }

        if (isComplete)
            break;
    }

    if (isComplete == false)
    {
        //If both slots are missing CMM, then shutdown amplifier
        if (cardStatus[0] == CT_ABSENT && cardStatus[1] == CT_ABSENT)
        {
            hasChanged |= aCmmOos.SetAmplifierShutdown(true);
        }
    }

    if(hasChanged)
        myCmmOosAutomaticRegion->IncModificationCounter();
}
