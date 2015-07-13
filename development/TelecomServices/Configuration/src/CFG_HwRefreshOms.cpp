// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <TsPii/TSPII_PipeIf.h>
#include "../CFG_HwRefreshOms.h"
#include "../CFG_Oms.h"
#include "../CFG_Ots.h"
#include "../CFG_OtsAutomaticTxPwrShut.h"
#include "../CFG_OmsAutomaticShutdown.h"
#include "../CFG_OmsAutomaticPwrAdj.h"
#include "../CFG_CmmOosAutomatic.h"
#include "../CFG_AppIf.h"
#include <Blackboard/FC_BbAction.h>
#include "../CFG_OptAutomatic.h"



CFG_HwRefreshOms::CFG_HwRefreshOms(CFG_AppIf& theCfgIf,
                                   CFG_OtsCfgRegion* theOtsRegion,
                                   CFG_OtsAutomaticTxPwrShutRegion* theAutomaticTxPwrShutRegion,
                                   CFG_OmsAutomaticShutdownRegion& theAutomaticShutdownRegion,
                                   CFG_OmsAutomaticPwrAdjRegion& theAutomaticPwrAdjRegion,
                                   CFG_CmmOosAutomaticRegion* theCmmOosAutomaticRegion,
                                   CFG_OptAutomaticCfgRegion* thePump1Region,
                                   CFG_OptAutomaticCfgRegion* thePump2Region,
                                   TSPII_PipeRegion& thePipePiiRegion):

    CFG_HwRefreshAction(theCfgIf),
    myPump1Region(thePump1Region),
    myPump2Region(thePump2Region),
    myPipePiiRegion(thePipePiiRegion),
    myOtsRegion(theOtsRegion),
    myAutomaticTxPwrShutRegion(theAutomaticTxPwrShutRegion),
    myAutomaticShutdownRegion(theAutomaticShutdownRegion),
    myAutomaticPwrAdjRegion(theAutomaticPwrAdjRegion),
    myCmmOosAutomaticRegion(theCmmOosAutomaticRegion)
{

    GetBbAction()->AddInputRegion(theCfgIf.GetCfgRegion());
    if (myOtsRegion) GetBbAction()->AddInputRegion(myOtsRegion);
    GetBbAction()->AddInputRegion(&myAutomaticShutdownRegion);
    GetBbAction()->AddInputRegion(&myAutomaticPwrAdjRegion, false);

    if(myCmmOosAutomaticRegion)
        GetBbAction()->AddInputRegion(myCmmOosAutomaticRegion, false);

    // false is because OSC could not be installed
    if(myAutomaticTxPwrShutRegion) GetBbAction()->AddInputRegion(myAutomaticTxPwrShutRegion, false);
    GetBbAction()->AddOutputRegion(theCfgIf.GetOutputCfgRegion());
    if (myPump1Region) GetBbAction()->AddOutputRegion(thePump1Region);
    if (myPump2Region) GetBbAction()->AddOutputRegion(thePump2Region);
}


CFG_HwRefreshOms::~CFG_HwRefreshOms()
{
    GetBbAction()->RemoveInputRegion(GetCfgIf().GetCfgRegion());
    if (myOtsRegion) GetBbAction()->RemoveInputRegion(myOtsRegion);
    GetBbAction()->RemoveInputRegion(&myAutomaticShutdownRegion);
    GetBbAction()->RemoveInputRegion(&myAutomaticPwrAdjRegion);
    if(myAutomaticTxPwrShutRegion) GetBbAction()->RemoveInputRegion(myAutomaticTxPwrShutRegion);
    if(myCmmOosAutomaticRegion) GetBbAction()->RemoveInputRegion(myCmmOosAutomaticRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetOutputCfgRegion());
    if (myPump1Region) GetBbAction()->RemoveOutputRegion(myPump1Region);
    if (myPump2Region) GetBbAction()->RemoveOutputRegion(myPump2Region);
}


FC_Object* CFG_HwRefreshOms::Process(unsigned theRunReason,
                                 FC_Object* theInvokerObj,
                                 FC_Object* theParam)
{
    CFG_Oms& aOmsConfig = static_cast<CFG_Oms&>((*GetCfgIf().GetCfgRegion())[0]);
    CFG_OmsAutomaticShutdown& aOmsAutomaticShutdown = myAutomaticShutdownRegion[0];
    TSPII_PipeIf& aPipePii = myPipePiiRegion[0];

    bool aAutoShutdownOrder = aOmsAutomaticShutdown.GetAmplifierShutdown();
    bool aATPSShutdownOrder = false;
    bool aAutoCmmOosOrder = false;

    // Get the ATPS shutdown order if available
    if(myAutomaticTxPwrShutRegion)
    {
        // if CATPS is not enable, ignore content of CATPS region
        // This allows us to keep operating even if user is not using an OSC card
        CFG_Ots& aOtsConfig   = (*myOtsRegion)[0];
        CFG_OtsAutomaticTxPwrShut& aAutoTxPwrShut = (*myAutomaticTxPwrShutRegion)[0];
        if (aOtsConfig.GetCatpsEnable())
        {
            if (myAutomaticTxPwrShutRegion->IsValid())
                aATPSShutdownOrder = aAutoTxPwrShut.GetAtpsActive();
            else
                //wait for this status to become valid
                return NULL;
        }
    }

    // Get the Cmm Oos shutdown order if available
    if(myCmmOosAutomaticRegion)
    {
        CFG_CmmOosAutomatic& aCmmOosAutomatic = (*myCmmOosAutomaticRegion)[0];
        aAutoCmmOosOrder = aCmmOosAutomatic.GetAmplifierShutdown(); 
    }

    // update state of pumps
    if (myPump1Region)
    {
        bool hasChanged = false;
        CFG_OptAutomatic& aAutomaticCfgObject = static_cast<CFG_OptAutomatic&>((*myPump1Region)[0]);
        hasChanged = aAutomaticCfgObject.SetAutomaticLaserShutdown(aAutoShutdownOrder ||
                                                                   aATPSShutdownOrder ||
                                                                   aAutoCmmOosOrder);
        if(hasChanged)
        {
            myPump1Region->IncModificationCounter();
        }
    }

    if (myPump2Region)
    {
        bool hasChanged = false;
        CFG_OptAutomatic& aAutomaticCfgObject = static_cast<CFG_OptAutomatic&>((*myPump2Region)[0]);
        hasChanged = aAutomaticCfgObject.SetAutomaticLaserShutdown(aAutoShutdownOrder ||
                                                                   aATPSShutdownOrder ||
                                                                   aAutoCmmOosOrder);
        if(hasChanged)
        {
            myPump2Region->IncModificationCounter();
        }
    }

    CT_TEL_mBm aGain = 0;
    CT_TEL_mBm aTilt = 0;

    bool aGainValid=true;
    //Update gain according to configuration or automatic power control
    if (aOmsConfig.GetPowerControlEnable())
    {
        // update only if region is valid
        if (myAutomaticPwrAdjRegion.IsValid())
        {
            aGain      = myAutomaticPwrAdjRegion[0].GetGain();
            aTilt      = myAutomaticPwrAdjRegion[0].GetGainTilt();
        }
        else
        {
            aGainValid = false;
        }
    }
    else
    {
        aGain      = aOmsConfig.GetGain();
    }

    // Apply gain only if source of gain are valid
    if (aGainValid)
    {
          // I don't know why this was ever included removed mr38767
          // Causes LRAME to not be programmed to correct gain
          //        if (aGain > aOmsAutomaticShutdown.GetMaximumGain())
          //            aGain = aOmsAutomaticShutdown.GetMaximumGain();
        aPipePii.SetGain(aGain);
        aPipePii.SetGainTilt(aTilt);
    }


    // Group EVOA is being added for a special case where we are applying an EVOA 
    // to a group of wavelenghts on the Express / Pass Through channels.
    // This can be used for other situations in the future. 
    CT_TEL_mBm aGroupEvoa = 0;

    bool anEvoaValid = true;
    //Update Evoa according to configuration or automatic power control
    if (aOmsConfig.GetGroupEvoaPowerControlEnable())
    {
        // update only if region is valid
        if (myAutomaticPwrAdjRegion.IsValid())
        {
            aGroupEvoa = myAutomaticPwrAdjRegion[0].GetGroupEvoa();
        }
        else
        {
            anEvoaValid = false;
        }
    }
    else
    {
        aGroupEvoa = aOmsConfig.GetGroupEvoa();
    }

    // Apply Evoa only if source of Evoa is valid
    if (anEvoaValid)
    {
        aPipePii.SetGroupEvoa(aGroupEvoa);
    }




    GetCfgIf().GetOutputCfgRegion()->IncModificationCounter();

    return NULL;

}

void CFG_HwRefreshOms::UpdateInputRegions(CFG_OtsCfgRegion* theOtsRegion,
                                          CFG_OtsAutomaticTxPwrShutRegion* theAutomaticTxPwrShutRegion)
{
    //Dynamically add and remove regions to support conversion from OLA to SBOADM
    if(myAutomaticTxPwrShutRegion) GetBbAction()->RemoveInputRegion(myAutomaticTxPwrShutRegion);
    if (myOtsRegion) GetBbAction()->RemoveInputRegion(myOtsRegion);

    myAutomaticTxPwrShutRegion = NULL;
    myOtsRegion = NULL;

    myOtsRegion = theOtsRegion;
    myAutomaticTxPwrShutRegion = theAutomaticTxPwrShutRegion;

    if (myOtsRegion) GetBbAction()->AddInputRegion(myOtsRegion);
    if(myAutomaticTxPwrShutRegion) GetBbAction()->AddInputRegion(myAutomaticTxPwrShutRegion, false);

}

