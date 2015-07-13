// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbAction.h>
#include "../CFG_OtsAutomaticAction.h"
#include "../CFG_OtsAutomatic.h"
#include "../CFG_AppIf.h"
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_OtsOHDefects.h>
#include <Monitoring/MON_OmsDefects.h>
#include <Monitoring/MON_OchDefects.h>
#include <Monitoring/MON_OmsStatus.h>
#include <Monitoring/MON_Region.h>
#include <CSM/CSM_AppIf.h>
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <ITS/ITS_Region.h>
#include <ITS/ITS_Config.h>

CFG_OtsAutomaticAction::CFG_OtsAutomaticAction(CFG_AppIf& theCfgApp,
                                               MON_RsDefectsRegion& theMonRsDefectsRegion,
                                               MON_OtsOHDefectsRegion& theMonOtsOHDefectsRegion,
                                               MON_OmsDefectsRegion& theMonOmsSourceDefectsRegion,
                                               MON_OmsDefectsRegion& theMonOmsDestDefectsRegion,
                                               MON_OchDefectsRegion& theMonOchOutputDefectsRegion,
                                               ITS_ConfigRegion& theItsConfigRegion,
                                               MON_RsDefectsRegion* theOtherSideMonRsDefectsRegion,
                                               MON_OmsDefectsRegion* theOtherSideMonOmsDefectsRegion,
                                               MON_OtsOHDefectsRegion* theOtherSideMonOtsOHDefectsRegion):
    CFG_HwRefreshAction(theCfgApp),
    myMonRsDefectsRegion(theMonRsDefectsRegion),
    myMonOtsOHDefectsRegion(theMonOtsOHDefectsRegion),
    myMonOmsSourceDefectsRegion(theMonOmsSourceDefectsRegion),
    myMonOmsDestDefectsRegion(theMonOmsDestDefectsRegion),
    myOtherSideMonRsDefectsRegion(theOtherSideMonRsDefectsRegion),
    myOtherSideMonOmsDefectsRegion(theOtherSideMonOmsDefectsRegion),
    myOtherSideMonOtsOHDefectsRegion(theOtherSideMonOtsOHDefectsRegion),
    myMonOchOutputDefectsRegion(theMonOchOutputDefectsRegion),
    myItsConfigRegion(theItsConfigRegion)
{
    GetBbAction()->AddInputRegion(&myMonRsDefectsRegion);
    GetBbAction()->AddInputRegion(&myMonOtsOHDefectsRegion);
    GetBbAction()->AddInputRegion(&myMonOmsSourceDefectsRegion);
    GetBbAction()->AddInputRegion(&myMonOmsDestDefectsRegion);
    GetBbAction()->AddInputRegion(&myMonOchOutputDefectsRegion);
    GetBbAction()->AddInputRegion(&myItsConfigRegion);
    if(myOtherSideMonRsDefectsRegion) GetBbAction()->AddInputRegion(myOtherSideMonRsDefectsRegion, false);
    if(myOtherSideMonOmsDefectsRegion) GetBbAction()->AddInputRegion(myOtherSideMonOmsDefectsRegion, false);
    if(myOtherSideMonOtsOHDefectsRegion) GetBbAction()->AddInputRegion(myOtherSideMonOtsOHDefectsRegion, false);
    GetBbAction()->AddOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}

CFG_OtsAutomaticAction::~CFG_OtsAutomaticAction()
{
    GetBbAction()->RemoveInputRegion(&myMonRsDefectsRegion);
    GetBbAction()->RemoveInputRegion(&myMonOtsOHDefectsRegion);
    GetBbAction()->RemoveInputRegion(&myMonOmsSourceDefectsRegion);
    GetBbAction()->RemoveInputRegion(&myMonOmsDestDefectsRegion);
    GetBbAction()->RemoveInputRegion(&myMonOchOutputDefectsRegion);
    GetBbAction()->RemoveInputRegion(&myItsConfigRegion);
    if(myOtherSideMonRsDefectsRegion) GetBbAction()->RemoveInputRegion(myOtherSideMonRsDefectsRegion);
    if(myOtherSideMonOmsDefectsRegion) GetBbAction()->RemoveInputRegion(myOtherSideMonOmsDefectsRegion);
    if(myOtherSideMonOtsOHDefectsRegion) GetBbAction()->RemoveInputRegion(myOtherSideMonOtsOHDefectsRegion);
    GetBbAction()->RemoveOutputRegion(GetCfgIf().GetAutomaticCfgRegion());
}


FC_Object* CFG_OtsAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{

    UpdateObject(theRunReason);
    return NULL;
}

void CFG_OtsAutomaticAction::UpdateObject(unsigned theRunReason)
{
    bool hasChanged = false;
    MON_RsDefects& aRsDefects = myMonRsDefectsRegion[0];
    MON_OtsOHDefects& aOtsOHDefects = myMonOtsOHDefectsRegion[0];
    CFG_OtsAutomatic& aOtsAutomaticConfig = static_cast<CFG_OtsAutomatic&>((*GetCfgIf().GetAutomaticCfgRegion())[0]);
    MON_OmsDefects& aOmsSourceDefects = myMonOmsSourceDefectsRegion[0];
    MON_OmsDefects& aOmsDestinationDefects = myMonOmsDestDefectsRegion[0];
    bool isOLA = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsNeOLA();

    uint32 aCount; // Variable to store counters
    uint32 i;


    ///////////////////////////////////////////////////////////////////////
    // BDI-O update
    // get actual Los defect
    bool aOtsLossState = false;
    bool aOtsTimState = false;
    aRsDefects.GetDefectStatus(CT_TEL_RS_LOS_DEFECT, &aCount, &aOtsLossState);
    aOtsOHDefects.GetDefectStatus(CT_TEL_OTS_TIM_DEFECT, &aCount, &aOtsTimState);
    // automatically send OTS-BDI-O on OSC-LOS
    hasChanged |= aOtsAutomaticConfig.SetForceOtsBDIO(aOtsLossState);

    ///////////////////////////////////////////////////////////////////////
    // BDI-P update
    bool aOmsLossState = false;
    bool aOtsPmiState = false;
    aOmsSourceDefects.GetDefectStatus(CT_TEL_OMS_LOS_DEFECT, &aCount, &aOmsLossState);
    aOtsOHDefects.GetDefectStatus(CT_TEL_OTS_PMI_DEFECT, &aCount, &aOtsPmiState);

    // update BDI-P according to OMS-LOS
    hasChanged |= aOtsAutomaticConfig.SetForceOtsBDIP(aOmsLossState||aOtsPmiState);

    ///////////////////////////////////////////////////////////////////////
    // PMI FDI-O FDI-P update
    bool aPMIState = false;
    bool aOmsFDIPState = false;
    bool aOmsFDIOState = false;
    string aOtsPmiReason = "";

    // if applicable to sub node config (should be OLA only)
    if(myOtherSideMonRsDefectsRegion && myOtherSideMonRsDefectsRegion->IsValid() &&
       myOtherSideMonOmsDefectsRegion && myOtherSideMonOmsDefectsRegion->IsValid() &&
       myOtherSideMonOtsOHDefectsRegion && myOtherSideMonOtsOHDefectsRegion->IsValid() &&
       isOLA == true)
    {
        MON_OtsOHDefects& aOtsOHOtherSideDefects = (*myOtherSideMonOtsOHDefectsRegion)[0];
        MON_RsDefects& aOtherSideRsDefects       = (*myOtherSideMonRsDefectsRegion)[0];
        MON_OmsDefects& aOmsOtherSideDefects     = (*myOtherSideMonOmsDefectsRegion)[0];

        // Propagate OTS-PMI from one side to the other to cover case where LOS would not raise
        // because of amp noise .
        bool aOtherSideOtsPmiState = false;
        bool aOtherSideOmsLosState = false;
        aOtsOHOtherSideDefects.GetDefectStatus(CT_TEL_OTS_PMI_DEFECT, &aCount, &aOtherSideOtsPmiState);
        aOmsOtherSideDefects.GetDefectStatus  (CT_TEL_OMS_LOS_DEFECT, &aCount, &aOtherSideOmsLosState);

        if(aOtherSideOtsPmiState || aOtherSideOmsLosState)
        {
            aPMIState = true;
            aOtsPmiReason += "Forwarded from other side;";
        }

        // Generate OMS-FDI-P if OMS-LOS or OTS-TIM on opposite side or if already OMS-FDI-P
        bool aOtsOtherSideFDIPState = false;
        aOtsOHOtherSideDefects.GetDefectStatus(CT_TEL_OMS_FDIP_DEFECT, &aCount, &aOtsOtherSideFDIPState);

        aOmsFDIPState |= aOtherSideOmsLosState || aOtsOtherSideFDIPState || aOtherSideOtsPmiState;

        // Generate OMS-FDI-O if OSC-LOS or OTS-TIM on opposite side or if already OMS-FDI-O
        bool aOtsOtherSideFDIOState = false;
        bool aOtherSideOscLosState  = false;
        aOtsOHOtherSideDefects.GetDefectStatus(CT_TEL_OMS_FDIO_DEFECT, &aCount, &aOtsOtherSideFDIOState);
        aOtherSideRsDefects.GetDefectStatus   (CT_TEL_RS_LOS_DEFECT,   &aCount, &aOtherSideOscLosState);

        aOmsFDIOState |= aOtherSideOscLosState || aOtsOtherSideFDIOState;
    }

    // Transmit PMI if there is a LOS after the ampli (Pump off or OMS-LOS at input)
    bool aOmsLosAfterAmpliState = false;
    aOmsDestinationDefects.GetDefectStatus(CT_TEL_OMS_LOS_AFTER_AMPLI_DEFECT, &aCount, &aOmsLosAfterAmpliState);
    if(aOmsLosAfterAmpliState)
    {
        aPMIState = true;
        aOtsPmiReason += "OMS LOS after ampli;";
    }


    // Transmit PMI if there is OCH-LOS for all OCH
    bool aOchLosOnAll = true;
    for(i=0;i<myMonOchOutputDefectsRegion.Size();i++)
    {
        bool aOchLOS = false;
        myMonOchOutputDefectsRegion[(bbindex_t)i].GetDefectStatus(CT_TEL_OCH_LOSS_PTONE_DEFECT, &aCount, &aOchLOS);
        if(!aOchLOS)
        {
            aOchLosOnAll = false;
            break;
        }
    }

    if(aOchLosOnAll)
    {
        aPMIState = true;
        aOtsPmiReason += "OCH-LOS on all channels;";
    }


    // PMI shall not be generated if there are no crossconnects in the P2L direction (out of the system)
    bool p2lXCExists = false;
    for (i=0;i<myItsConfigRegion.Size();i++)
    {
        ITS_Config& aItsConfig = myItsConfigRegion[(bbindex_t)i];
        if (aItsConfig.GetInfo(ITS_PtoL) == true)
        {
            p2lXCExists = true;
            break;
        }

    }

    if (p2lXCExists == false)
    {
        aPMIState = false;
    }

    aOtsAutomaticConfig.SetForceOtsPMIReason(aOtsPmiReason);

    //Update generation of PMI and FDI on automatic region
    hasChanged |= aOtsAutomaticConfig.SetForceOtsPMI(aPMIState);
    hasChanged |= aOtsAutomaticConfig.SetForceOmsFDIO(aOmsFDIOState);
    hasChanged |= aOtsAutomaticConfig.SetForceOmsFDIP(aOmsFDIPState);

    if (hasChanged)
    {
        GetCfgIf().GetAutomaticCfgRegion()->IncModificationCounter();
    }
}


