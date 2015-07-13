// //Copyright(c) Tellabs Transport Group. All rights reserved.

#include <ErrorService/FC_Error.h>
#include <Blackboard/FC_BbAction.h>
#include <ITS/ITS_Region.h>
#include <ITS/ITS_Config.h>
#include <BEIF/BEIF_MainIf.h>
#include <BEIF/BEIF_OtsIf.h>
#include <BEIF/BEIF_OmsIf.h>
#include <BEIF/BEIF_OchLIf.h>
#include "CFG_OtsOchOHAutomaticAction.h"
#include "CFG_OtsOchOHAutomatic.h"
#include "CFG_AppIf.h"
#include <Monitoring/MON_RsDefects.h>
#include <Monitoring/MON_OtsOHDefects.h>
#include <Monitoring/MON_OtsOchOHDefects.h>
#include <Monitoring/MON_OmsDefects.h>
#include <Monitoring/MON_OchDefects.h>
#include <Monitoring/MON_Region.h>
#include <CsPii/CSPII_SysCfgParamIF.h>


CFG_OtsOchOHAutomaticAction::CFG_OtsOchOHAutomaticAction(CFG_AppIf& theCfgApp,
                                                         MON_OmsDefectsRegion& theOutputMonOmsDefectsRegion,
                                                         MON_OchDefectsRegion& theOutputMonOchDefectsRegion,
                                                         ITS_ConfigRegion& theItsConfigRegion,
                                                         CFG_OtsOchOHAutomaticCfgRegion& theOtsOchOHAutomaticCfgRegion,
                                                         vector<CT_Side>& thePossibleSidesVector,
                                                         uint32 theNumberofPossibleSides):
    CFG_HwRefreshAction(theCfgApp),
    myOutputMonOmsDefectsRegion(theOutputMonOmsDefectsRegion),
    myOutputMonOchDefectsRegion(theOutputMonOchDefectsRegion),
    myItsConfigRegion(theItsConfigRegion),
    myOtsOchOHAutomaticCfgRegion(theOtsOchOHAutomaticCfgRegion),
    myPossibleSidesVector(thePossibleSidesVector),
    myNumberofPossibleSides(theNumberofPossibleSides)
{
    GetBbAction()->AddInputRegion(&myOutputMonOmsDefectsRegion);
    GetBbAction()->AddInputRegion(&myOutputMonOchDefectsRegion);
    GetBbAction()->AddInputRegion(&myItsConfigRegion);

    GetBbAction()->AddOutputRegion(&myOtsOchOHAutomaticCfgRegion);

    // Get the OMS pass thru mode thru BEIF.
    myOmsPassThru = BEIF_MainIf::Instance().GetOtsIf(CT_SIDE_A).GetPassThroughMonDefectsRegion() != NULL;

    uint32 i = 0;
    // Initialize Region Arrays to NULL
    for (i = 0; i < CT_NUMBER_OF_SIDES; i++)
    {
        myPossibleOtherSideMonRsDefectsRegion[i] =       NULL;
        myPossibleOtherSideMonOtsOHDefectsRegion[i] =    NULL;
        myPossibleOtherSideMonOtsOchOHDefectsRegion[i] = NULL;
        myPossibleOtherSideInputMonOmsDefectsRegion[i] = NULL;
    } //   for (uint32 i = 0; i < CT_NUMBER_OF_SIDES; i++)

    // Now fill in the appropriate arrays
    // (based on the number of possible sides)
    for (i = 0; i < myNumberofPossibleSides; i++)
    {
        CT_Side aOtherSideOtsId = myPossibleSidesVector[i];

        myPossibleOtherSideMonRsDefectsRegion[i] =       static_cast <MON_RsDefectsRegion*> (BEIF_MainIf::Instance().GetOtsIf(aOtherSideOtsId).GetMonRsDefectsRegion());
        myPossibleOtherSideMonOtsOHDefectsRegion[i] =    static_cast <MON_OtsOHDefectsRegion*> (BEIF_MainIf::Instance().GetOtsIf(aOtherSideOtsId).GetMonOHDefectsRegion());
        myPossibleOtherSideMonOtsOchOHDefectsRegion[i] = static_cast <MON_OtsOchOHDefectsRegion*> (BEIF_MainIf::Instance().GetOtsIf(aOtherSideOtsId).GetMonOchOHDefectsRegion());
        myPossibleOtherSideInputMonOmsDefectsRegion[i] = static_cast <MON_OmsDefectsRegion*> (BEIF_MainIf::Instance().GetOtsIf(aOtherSideOtsId).GetOmsIf().GetInputMonDefectsRegionPtr());

        // Add the Region as an Input Region
        if(myPossibleOtherSideMonRsDefectsRegion[i])       GetBbAction()->AddInputRegion(myPossibleOtherSideMonRsDefectsRegion[i], false);
        if(myPossibleOtherSideMonOtsOHDefectsRegion[i])    GetBbAction()->AddInputRegion(myPossibleOtherSideMonOtsOHDefectsRegion[i], false);
        if(myPossibleOtherSideMonOtsOchOHDefectsRegion[i]) GetBbAction()->AddInputRegion(myPossibleOtherSideMonOtsOchOHDefectsRegion[i], false);
        if(myPossibleOtherSideInputMonOmsDefectsRegion[i]) GetBbAction()->AddInputRegion(myPossibleOtherSideInputMonOmsDefectsRegion[i], false);
    }  //  for (i = 0; i < myNumberofPossibleSides; i++)

    for (i = 0; i < CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY; i++)
    {
        myPTSourceSide[i] = CT_SIDE_UNKNOWN;
        myOtherSideIndex[i] = 0;
        myPassThruState[i] = 0;
        myFDIOState[i] = 0;
        myOscLosState[i] = 0;
        myOtherSideFDIOState[i] = 0;
        myOtherSideOmsFDIO[i] = 0;
        myFDIPState[i] = 0;
        myInputOmsLosState[i] = 0;
        myOtherSideFDIPState[i] = 0;
        myOtherSideOmsFDIP[i] = 0;
        myOtherSideOtsPMI[i] = 0;
        myOCIState[i] = 0;
        myOutputOmsLosState[i] = 0;
        myOchLossState[i] = 0;
        myOtherSideOCIState[i] = 0;
    }
}

CFG_OtsOchOHAutomaticAction::~CFG_OtsOchOHAutomaticAction()
{
    GetBbAction()->RemoveInputRegion(&myOutputMonOmsDefectsRegion);
    GetBbAction()->RemoveInputRegion(&myOutputMonOchDefectsRegion);
    GetBbAction()->RemoveInputRegion(&myItsConfigRegion);

    for (uint32 i = 0; i < myNumberofPossibleSides; i++)
    {
        if(myPossibleOtherSideMonRsDefectsRegion[i])       GetBbAction()->RemoveInputRegion(myPossibleOtherSideMonRsDefectsRegion[i]);
        if(myPossibleOtherSideMonOtsOHDefectsRegion[i])    GetBbAction()->RemoveInputRegion(myPossibleOtherSideMonOtsOHDefectsRegion[i]);
        if(myPossibleOtherSideMonOtsOchOHDefectsRegion[i]) GetBbAction()->RemoveInputRegion(myPossibleOtherSideMonOtsOchOHDefectsRegion[i]);
        if(myPossibleOtherSideInputMonOmsDefectsRegion[i]) GetBbAction()->RemoveInputRegion(myPossibleOtherSideInputMonOmsDefectsRegion[i]);
    }  //  for (uint32 i = 0; i < myNumberofPossibleSides; i++)

    GetBbAction()->RemoveOutputRegion(&myOtsOchOHAutomaticCfgRegion);
}


FC_Object* CFG_OtsOchOHAutomaticAction::Process(unsigned theRunReason,
                                           FC_Object* theInvokerObj,
                                           FC_Object* theParam)
{
    uint32 aSize = myOtsOchOHAutomaticCfgRegion.Size();

    //Size may need to be adjusted based on the size of the input myItsConfigRegion. There are situations
    //during controller module swaps where the oms wavelength capacity changes. Since the input region may be transferred
    //from a different module (APM), the size of the input region may reflect the a different wavelength capacity than we expect.
    //We adjust the size here to pick the lower number of the two.
    uint32 inputItsRegionSize = myItsConfigRegion.Size();
    if (inputItsRegionSize < aSize)
        aSize = inputItsRegionSize;

    // Just being paranoid.  Check the myOutputMonOchDefectsRegion size because it
    // is referenced in the UpdateObject method.
    // Therefore, take the smallest value of the three static regions passed into the constructor.
    // Note:  In the UpdateObject method, there are specific checks on the region size 
    // that are opposite sides.  Only one has multiple instances (myPossibleOtherSideMonOtsOchOHDefectsRegion)
    uint32 outputMonRegionSize = myOutputMonOchDefectsRegion.Size();
    if (outputMonRegionSize < aSize)
        aSize = outputMonRegionSize;

    //Update all objects of the region.
    for(uint8 aIndex=0; aIndex<aSize; aIndex++)
    {
        UpdateObject(theRunReason, aIndex);
    }

    return NULL;
}

void CFG_OtsOchOHAutomaticAction::UpdateObject(unsigned theRunReason, uint32 theIndex)
{
    bool hasChanged = false;
    MON_RsDefects* aOtherSideRsDefects = NULL;
    MON_OtsOHDefects* aOtherSideOtsOHDefects = NULL;
    MON_OtsOchOHDefects* aOtherSideOtsOchOHDefects  = NULL;
    MON_OmsDefects* aOtherSideInputOmsDefects = NULL;
    bool isOLA = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsNeOLA();
    bool isAmpFoadm = CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsNeAmpFoadm();

    if (myPossibleOtherSideMonRsDefectsRegion[0] && myPossibleOtherSideMonRsDefectsRegion[0]->IsValid())
        aOtherSideRsDefects       = &(*myPossibleOtherSideMonRsDefectsRegion[0])[0];
    if (myPossibleOtherSideMonOtsOHDefectsRegion[0] && myPossibleOtherSideMonOtsOHDefectsRegion[0]->IsValid())
        aOtherSideOtsOHDefects    = &(*myPossibleOtherSideMonOtsOHDefectsRegion[0])[0];
    if (myPossibleOtherSideMonOtsOchOHDefectsRegion[0] && 
        myPossibleOtherSideMonOtsOchOHDefectsRegion[0]->IsValid() &&
        theIndex < myPossibleOtherSideMonOtsOchOHDefectsRegion[0]->Size())
        aOtherSideOtsOchOHDefects = &(*myPossibleOtherSideMonOtsOchOHDefectsRegion[0])[(bbindex_t)theIndex];
    if (myPossibleOtherSideInputMonOmsDefectsRegion[0] && myPossibleOtherSideInputMonOmsDefectsRegion[0]->IsValid())
        aOtherSideInputOmsDefects = &(*myPossibleOtherSideInputMonOmsDefectsRegion[0])[0];

    MON_OmsDefects& aOutputOmsDefects = myOutputMonOmsDefectsRegion[0];
    MON_OchDefects& aOutputOchDefects = myOutputMonOchDefectsRegion[(bbindex_t)theIndex];

    CFG_OtsOchOHAutomatic& aOtsOchOHAutomaticConfig = static_cast<CFG_OtsOchOHAutomatic&>((myOtsOchOHAutomaticCfgRegion)[(bbindex_t)theIndex]);
    ITS_Config& aItsConfig = myItsConfigRegion[(bbindex_t)theIndex];

    uint32 aCount; // Variable to store counters

    bool aPassThruState = aItsConfig.GetInfo(ITS_PT);

    if (aPassThruState)
    {
        //Check whether it is a real pass through connection. The pass through
        //flag in ITS is also set when the connection type is regen
        CT_CardFamily theMuxSrcFam = aItsConfig.GetMuxSrcCardFam();
        if( theMuxSrcFam != CARD_FAM_UNKNOWN &&
            theMuxSrcFam != BPM_FAM  &&
            theMuxSrcFam != CMM_FAM  &&
            theMuxSrcFam != CCM_FAM  &&  // NANO
            theMuxSrcFam != CADM_FAM &&
            theMuxSrcFam != RCMM_FAM  )
        {
            aPassThruState = false;
        }

        // add Config 23
        if(theMuxSrcFam == LIAM_FAM && isAmpFoadm)
        {
            aPassThruState = true;
        }
    }

    // See if there is another side that is connected
    // if (aPassThruState && (myItsConfigRegion->IsValid()) &&
    //                       (myNumberofPossibleSides > 1))
    if (aPassThruState && (myNumberofPossibleSides > 1))
    {
        CT_Side aPTSourceSide = aItsConfig.GetPTSourceSide();

        bool found = false;
        int indexFound = 0;
        for (uint32 i = 0; i < myNumberofPossibleSides; i++)
        {
            if (aPTSourceSide == myPossibleSidesVector[i])
            {
                found = true;
                indexFound = i;
                break;
            }  //  if (aPTSourceSide == myPossibleSidesVector[i])
        }  // for (uint32 i = 0; i < myNumberofPossibleSides; i++)

        //For Debugging.
        myOtherSideIndex[theIndex] = indexFound;
        myPTSourceSide[theIndex] = aPTSourceSide;

        if (found)
        {
            if (myPossibleOtherSideMonRsDefectsRegion[indexFound] && myPossibleOtherSideMonRsDefectsRegion[indexFound]->IsValid())
                aOtherSideRsDefects = &(*myPossibleOtherSideMonRsDefectsRegion[indexFound])[0];
            else
                aOtherSideRsDefects = NULL;

            if (myPossibleOtherSideMonOtsOHDefectsRegion[indexFound] && myPossibleOtherSideMonOtsOHDefectsRegion[indexFound]->IsValid())
                aOtherSideOtsOHDefects = &(*myPossibleOtherSideMonOtsOHDefectsRegion[indexFound])[0];
            else
                aOtherSideOtsOHDefects = NULL;

            if (myPossibleOtherSideMonOtsOchOHDefectsRegion[indexFound] && 
                myPossibleOtherSideMonOtsOchOHDefectsRegion[indexFound]->IsValid() &&
                theIndex < myPossibleOtherSideMonOtsOchOHDefectsRegion[indexFound]->Size())
                aOtherSideOtsOchOHDefects = &(*myPossibleOtherSideMonOtsOchOHDefectsRegion[indexFound])[(bbindex_t)theIndex];
            else
                aOtherSideOtsOchOHDefects = NULL;

            if (myPossibleOtherSideInputMonOmsDefectsRegion[indexFound] && myPossibleOtherSideInputMonOmsDefectsRegion[indexFound]->IsValid())
                aOtherSideInputOmsDefects = &(*myPossibleOtherSideInputMonOmsDefectsRegion[indexFound])[0];
            else
                aOtherSideInputOmsDefects = NULL;
        }  //  if (found)
        else
        {
            aOtherSideRsDefects       = NULL;
            aOtherSideOtsOHDefects    = NULL;
            aOtherSideOtsOchOHDefects = NULL;
            aOtherSideInputOmsDefects = NULL;
        }  //  else of if (found)
    }  //  if (aPassThruState && (myNumberofPossibleSides > 1))

    ///////////////////////////////////////////////////////////////////////
    // FDI-O update
    // Automatically send OCH-FDI-O on LOS-OF-OOS or OCH-FDI-O(input) if Channel is Pass-Thru.

    bool aFDIOState = false;
    bool aOscLosState = false;
    bool aOtherSideFDIOState = false;
    bool aOtherSideOmsFDIO = false;

    if(aOtherSideRsDefects)
        aOtherSideRsDefects->GetDefectStatus(CT_TEL_RS_LOS_DEFECT, &aCount, &aOscLosState);
    if(aOtherSideOtsOchOHDefects)
        aOtherSideOtsOchOHDefects->GetDefectStatus(CT_TEL_OCH_FDIO_DEFECT, &aCount, &aOtherSideFDIOState);
    if(aOtherSideOtsOHDefects)
    {
        aOtherSideOtsOHDefects->GetDefectStatus(CT_TEL_OMS_FDIO_DEFECT, &aCount, &aOtherSideOmsFDIO);
    }

    //if not an OLA (second case covers inservice conversion from OLA<->SBOADM)
    if((!myOmsPassThru) || (myOmsPassThru && !isOLA))
        aFDIOState = aPassThruState && (aOscLosState || aOtherSideFDIOState || aOtherSideOmsFDIO);
    else
        aFDIOState = aOtherSideFDIOState;

    hasChanged |= aOtsOchOHAutomaticConfig.SetForceFDIO(aFDIOState);

    ///////////////////////////////////////////////////////////////////////
    // FDI-P update
    // Automatically send OCH-FDI-P on OTS layer failure or OCH-FDI-P(input) or OMS-LOS if Channel is Pass-Thru
    // or send it if the OCH Layer in failure at the output of the system. .
    bool aFDIPState = false;
    bool aFDIPStateOS = false;
    bool aInputOmsLosState = false;
    bool aOtherSideFDIPState = false;
    bool aOtherSideOmsFDIP = false;
    bool aOtherSideOtsPMI = false;
    bool aOutputOmsLosState = false;
    bool aOchLossState = false;

    if(aOtherSideInputOmsDefects)
        aOtherSideInputOmsDefects->GetDefectStatus(CT_TEL_OMS_LOS_DEFECT, &aCount, &aInputOmsLosState);
    if(aOtherSideOtsOchOHDefects)
        aOtherSideOtsOchOHDefects->GetDefectStatus(CT_TEL_OCH_FDIP_DEFECT, &aCount, &aOtherSideFDIPState);
    if(aOtherSideOtsOHDefects)
    {
        aOtherSideOtsOHDefects->GetDefectStatus(CT_TEL_OMS_FDIP_DEFECT, &aCount, &aOtherSideOmsFDIP);
        aOtherSideOtsOHDefects->GetDefectStatus(CT_TEL_OTS_PMI_DEFECT, &aCount, &aOtherSideOtsPMI);
    }

    aOutputOchDefects.GetDefectStatus(CT_TEL_OCH_LOSS_PTONE_DEFECT, &aCount, &aOchLossState);
    aOutputOmsDefects.GetDefectStatus(CT_TEL_OMS_LOS_DEFECT, &aCount, &aOutputOmsLosState);

    //if not an OLA (second case covers inservice conversion from OLA<->SBOADM)
    if((!myOmsPassThru) || (myOmsPassThru && !isOLA))
    {
        aFDIPState = (aPassThruState && (aInputOmsLosState || aOtherSideFDIPState || aOtherSideOmsFDIP || aOtherSideOtsPMI || aOutputOmsLosState)) || aOchLossState;
        aFDIPStateOS = (aPassThruState && (aInputOmsLosState || aOtherSideFDIPState || aOtherSideOmsFDIP || aOtherSideOtsPMI));
    }
    else
    {
        aFDIPState = aOtherSideFDIPState;
        aFDIPStateOS = aOtherSideFDIPState;
    }

    hasChanged |= aOtsOchOHAutomaticConfig.SetForceFDIP(aFDIPState);
    hasChanged |= aOtsOchOHAutomaticConfig.SetForceFDIPOS(aFDIPStateOS);


    ///////////////////////////////////////////////////////////////////////
    // OCI update
    // Automatically send OCH-OCI on OCH-OCI(input) if Channel is Pass-Thru
    bool aOCIState = false;
    bool aOtherSideOCIState = false;


    if(aOtherSideOtsOchOHDefects)
        aOtherSideOtsOchOHDefects->GetDefectStatus(CT_TEL_OCH_OCI_DEFECT, &aCount, &aOtherSideOCIState);

     //if not an OLA (second case covers inservice conversion from OLA<->SBOADM)
    if((!myOmsPassThru) || (myOmsPassThru && !isOLA))
        aOCIState = (aPassThruState && aOtherSideOCIState);
    else
        aOCIState = aOtherSideOCIState;

    hasChanged |= aOtsOchOHAutomaticConfig.SetForceOCI(aOCIState);

    if (hasChanged)
    {
        myOtsOchOHAutomaticCfgRegion.IncModificationCounter();

        //Store all of this data for debugging.
        myPassThruState[theIndex] = aPassThruState;
        myFDIOState[theIndex] = aFDIOState;
        myOscLosState[theIndex] = aOscLosState;
        myOtherSideFDIOState[theIndex] = aOtherSideFDIOState;
        myOtherSideOmsFDIO[theIndex] = aOtherSideOmsFDIO;
        myFDIPState[theIndex] = aFDIPState;
        myInputOmsLosState[theIndex] = aInputOmsLosState;
        myOtherSideFDIPState[theIndex] = aOtherSideFDIPState;
        myOtherSideOmsFDIP[theIndex] = aOtherSideOmsFDIP;
        myOtherSideOtsPMI[theIndex] = aOtherSideOtsPMI;
        myOCIState[theIndex] = aOCIState;
        myOutputOmsLosState[theIndex] = aOutputOmsLosState;
        myOchLossState[theIndex] = aOchLossState;
        myOtherSideOCIState[theIndex] = aOtherSideOCIState;
    }
}


FC_CmdProcessor::STATUS CFG_OtsOchOHAutomaticAction::Debug(int argc, char **argv)
{
    char aParam[32];
    char aParamIndex[16];
    int index = 0;

    //We need at least 2 arguments
    if (argc < 2)
        goto OPTERROR;

    //Copy arguments
    strcpy(aParam, argv[0]);
    strcpy(aParamIndex, argv[1]);
    index = atoi(aParamIndex);
    if ((!strncmp(aParam,"dump",4)) && (index < CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY))
    {
        fc_cout   << "PTSourceSide        = " << DISPLAY_SIDE(myPTSourceSide[index]) << endl;
        fc_cout   << "OtherSide Index     = " << uint32(myOtherSideIndex[index]) << endl;
        fc_cout   << "Pass Thru           = " << DISPLAY_BOOL(myPassThruState[index]) << endl;
        fc_cout   << "FDIO                = " << DISPLAY_BOOL(myFDIOState[index]) << endl;
        fc_cout   << "OSC LOS             = " << DISPLAY_BOOL(myOscLosState[index]) << endl;
        fc_cout   << "OtherSide FDIO      = " << DISPLAY_BOOL(myOtherSideFDIOState[index]) << endl;
        fc_cout   << "OtherSide Oms FDIO  = " << DISPLAY_BOOL(myOtherSideOmsFDIO[index]) << endl;
        fc_cout   << "FDIP                = " << DISPLAY_BOOL(myFDIPState[index]) << endl;
        fc_cout   << "Input OMS LOS       = " << DISPLAY_BOOL(myInputOmsLosState[index]) << endl;
        fc_cout   << "OtherSide FDIP      = " << DISPLAY_BOOL(myOtherSideFDIPState[index]) << endl;
        fc_cout   << "OtherSide OMS FDIP  = " << DISPLAY_BOOL(myOtherSideOmsFDIP[index]) << endl;
        fc_cout   << "OtherSide OTS PMI   = " << DISPLAY_BOOL(myOtherSideOtsPMI[index]) << endl;
        fc_cout   << "OCI                 = " << DISPLAY_BOOL(myOCIState[index]) << endl;
        fc_cout   << "Output OMS LOS      = " << DISPLAY_BOOL(myOutputOmsLosState[index]) << endl;
        fc_cout   << "OCH LOS             = " << DISPLAY_BOOL(myOchLossState[index]) << endl;
        fc_cout   << "OtherSide OCI       = " << DISPLAY_BOOL(myOtherSideOCIState[index]) << endl;

    }
    else
    {
        goto OPTERROR;
    }

    return FC_CmdProcessor::E_SUCCESS;

OPTERROR:
    {
        fc_cout << "ots dump [index]  " << endl;
        fc_cout << "    index is 0 thru " << (CT_TEL_MAX_OMS_WAVELENGTH_CAPACITY-1) << endl;
        fc_cout << endl;
        return FC_CmdProcessor::E_FAILURE;
    }

    //return FC_CmdProcessor::E_FAILURE;
}
