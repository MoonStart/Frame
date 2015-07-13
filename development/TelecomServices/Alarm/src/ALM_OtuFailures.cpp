/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OTU (Optical Transport
                Unit) layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_OtuDefects.h>
#include <CsPii/CSPII_CardIF.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Opt.h>

#include "../ALM_AppIf.h"
#include "../ALM_OtuFailureBase.h"
#include "ALM_OtuFailures.h"
#include <Alarm/ALM_SubApplicationOnCard.h>
#include <Alarm/ALM_RegionKeyDefinition.h>

//To drive LED on LOF
#include <T6100_MainAppIf.h>
#include <T6100_CardIf.h>
#include <AM/AM_DefectCollector.h>
#include <AM/AM_DefectProcessor.h>

//=====================================  ====================================  ======================================
// bit#:     11    10      9       8        7       6       5            4        3       2         1        0
// defect: UP_SA UP_NSA AIS_OTU LOF_OTU  LOM_OTU TIM_OTU TIM_NSA_OTU FECM_OTU  BDI_OTU BERSD_OTU FEC_SD_OTU DISP_OTU
//=====================================  ====================================  ======================================

static const ALM_BitField UP_SA_FilterMask    = 0x0FFF; // 1111 1111 1111
static const ALM_BitField UP_NSA_FilterMask   = 0x0FFF; // 1111 1111 1111
static const ALM_BitField AIS_FilterMask      = 0x0E01; // 1110 0000 0001
static const ALM_BitField LOF_FilterMask      = 0x0F01; // 1111 0000 0001

static const ALM_BitField LOM_FilterMask      = 0x0F81; // 1111 1000 0001
static const ALM_BitField TIM_FilterMask      = 0x0FC1; // 1111 1100 0001
static const ALM_BitField TIM_NSA_FilterMask  = 0x0FFF; // 1111 1111 1111
static const ALM_BitField FECM_FilterMask     = 0x0FF0; // 1111 1111 0000

static const ALM_BitField BDI_FilterMask      = 0x0FFF; // 1111 1111 1111
static const ALM_BitField BERSD_FilterMask    = 0x0FFF; // 1111 1111 1111
static const ALM_BitField FEC_SD_FilterMask   = 0x0FFF; // 1111 1111 1111
static const ALM_BitField DISP_FilterMask     = 0x0FFF; // 1111 1111 1111

static const ALM_BitField ourFailureProtectionMask = 0x0FFF;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures and defects of lower layer if one of the folowing failure
// or defect is declared: AIS, LOF, TIM, FECM
static const ALM_BitField ourFilterAllMask = 0x03D0;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
static const ALM_BitField ourNoFilterMask = 0x0C00;

//-----------------------------------------------------------------
//##ModelId=3C506C30025D
ALM_OtuFailures::ALM_OtuFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_OtuDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OtuFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),

    //Set the monitor
    myMonitor(theMonitor),

    myLed4LOFOTU(1000, 1000), // Soak set/clear times
    myLed4LOMOTU(1000, 1000), // Soak set/clear times
    myLedStatus(false),
    myCardIf(NULL),

    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_OTU_SOAKING_TIME)
{
    myPortOffset = 0; // Default

    // Add all failures to LayerFailures object
    AddAt (ALM_OtuFailureBase::UPPER_SA_OTU, &myUpperSa);
    AddAt (ALM_OtuFailureBase::UPPER_NSA_OTU, &myUpperNsa);
    AddAt (ALM_OtuFailureBase::LOF_OTU, &myLof);
    AddAt (ALM_OtuFailureBase::LOM_OTU, &myLom);
    AddAt (ALM_OtuFailureBase::AIS_OTU, &myAis);
    AddAt (ALM_OtuFailureBase::TIM_OTU, &myTim);
    AddAt (ALM_OtuFailureBase::TIM_NSA_OTU, &myTimNsa);
    AddAt (ALM_OtuFailureBase::FECM_OTU, &myFecm);
    AddAt (ALM_OtuFailureBase::BDI_OTU, &myBdi);
    AddAt (ALM_OtuFailureBase::BERSD_OTU, &myBersd);
    AddAt (ALM_OtuFailureBase::FEC_SD_OTU, &myFecsd);
    AddAt (ALM_OtuFailureBase::DISP_OTU, &myDisp);

    if ( theApplication.GetContext().GetParent() )
    {    
        myCardIf = dynamic_cast<T6100_CardIf*>(theApplication.GetContext().GetParent());
        const string sKey = myApplication.GetKeySuffix();

        if      (sKey == ALM_LINE_1_SUFFIX) {  myPortOffset = 1; }
        else if (sKey == ALM_PORT_0_SUFFIX) {  myPortOffset = 0; }
        else if (sKey == ALM_PORT_1_SUFFIX) {  myPortOffset = 1; }
        else if (sKey == ALM_PORT_2_SUFFIX) {  myPortOffset = 2; }
        else if (sKey == ALM_PORT_3_SUFFIX) {  myPortOffset = 3; }
        else if (sKey == ALM_PORT_4_SUFFIX) {  myPortOffset = 4; }
        else if (sKey == ALM_PORT_5_SUFFIX) {  myPortOffset = 5; }
        else if (sKey == ALM_PORT_6_SUFFIX) {  myPortOffset = 6; }
        else if (sKey == ALM_PORT_7_SUFFIX) {  myPortOffset = 7; }
        else if (sKey == ALM_PORT_8_SUFFIX) {  myPortOffset = 8; }
        else if (sKey == ALM_PORT_9_SUFFIX) {  myPortOffset = 9; }
        else if (sKey == ALM_PORT_10_SUFFIX){  myPortOffset = 10;}
        else if (sKey == ALM_PORT_11_SUFFIX){  myPortOffset = 11;}
        else if (sKey == ALM_PORT_12_SUFFIX){  myPortOffset = 12;}
        else if (sKey == ALM_PORT_13_SUFFIX){  myPortOffset = 13;}
        else if (sKey == ALM_PORT_14_SUFFIX){  myPortOffset = 14;}
        else if (sKey == ALM_PORT_15_SUFFIX){  myPortOffset = 15;}
        else if (sKey == ALM_PORT_16_SUFFIX){  myPortOffset = 16;}
        else if (sKey == ALM_PORT_17_SUFFIX){  myPortOffset = 17;}
        else if (sKey == ALM_PORT_18_SUFFIX){  myPortOffset = 18;}
        else if (sKey == ALM_PORT_19_SUFFIX){  myPortOffset = 19;}
        else if (sKey == ALM_PORT_20_SUFFIX){  myPortOffset = 20;}
        else if (sKey == ALM_PORT_21_SUFFIX){  myPortOffset = 21;}
        else if (sKey == ALM_PORT_22_SUFFIX){  myPortOffset = 22;}
        else if (sKey == ALM_PORT_23_SUFFIX){  myPortOffset = 23;}
        else if (sKey == ALM_PORT_24_SUFFIX){  myPortOffset = 24;}
        else if (sKey == ALM_PORT_25_SUFFIX){  myPortOffset = 25;}
        else if (sKey == ALM_PORT_26_SUFFIX){  myPortOffset = 26;}
        else if (sKey == ALM_PORT_27_SUFFIX){  myPortOffset = 27;}
        else if (sKey == ALM_PORT_28_SUFFIX){  myPortOffset = 28;}
        else if (sKey == ALM_PORT_29_SUFFIX){  myPortOffset = 29;}
        else if (sKey == ALM_PORT_30_SUFFIX){  myPortOffset = 30;}
        else if (sKey == ALM_PORT_31_SUFFIX){  myPortOffset = 31;}

        else if (sKey == ALM_PORT_88_SUFFIX){  myPortOffset = 88;}
        else if (sKey == ALM_PORT_87_SUFFIX){  myPortOffset = 87;}
        else if (sKey == ALM_PORT_86_SUFFIX){  myPortOffset = 86;}
        else if (sKey == ALM_PORT_85_SUFFIX){  myPortOffset = 85;}

        //---------------------------------------------------------
        // Special case for TRN/FGTMM which map LINE_1 to offset_0.
        //---------------------------------------------------------
        if ( (myCardIf) && (myApplication.GetKeySuffix() == ALM_LINE_1_SUFFIX) &&
             (myCardIf->GetCardFamily() == TRN_FAM || myCardIf->GetCardFamily() == FGTMM_FAM) )
        {
            myPortOffset = 0;
        }
    }
}

//-----------------------------------------------------------------
//##ModelId=3C506C300269
ALM_OtuFailures::~ALM_OtuFailures ()
{

}

//-----------------------------------------------------------------
//##ModelId=3C506C300271
ALM_BitField ALM_OtuFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_OTU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_UPPER_LAYER_FAIL_TA_DEFECT, ALM_OtuFailureBase::UPPER_SA_OTU)

    // Read the UPPER_NSA_OTU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_OtuFailureBase::UPPER_NSA_OTU)

    // Read the AIS_OTU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_AIS_DEFECT, ALM_OtuFailureBase::AIS_OTU)

    // Read the LOF_OTU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_LOF_DEFECT, ALM_OtuFailureBase::LOF_OTU)

    // Read the LOM_OTU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_LOMF_DEFECT, ALM_OtuFailureBase::LOM_OTU)

    //=====================================================================================
    // TIM_OTU is a special case scenario where it is ServiceAffecting(SA) or NSA
    // based on the provisioned MONTRCOTU attribute (AIS, NOAIS). Must process special!
    //=====================================================================================
    myMonitor.GetDefectStatusSpecial(CT_TEL_OTU_TIM_DEFECT, &aTCount, &aStatus, true); // TIM_OTU
    itsDefect[ALM_OtuFailureBase::TIM_OTU].SetTCount(aTCount);
    itsDefect[ALM_OtuFailureBase::TIM_OTU].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_OtuFailureBase::TIM_OTU); }

    myMonitor.GetDefectStatusSpecial(CT_TEL_OTU_TIM_DEFECT, &aTCount, &aStatus, false); // TIM_NSA_OTU
    itsDefect[ALM_OtuFailureBase::TIM_NSA_OTU].SetTCount(aTCount);
    itsDefect[ALM_OtuFailureBase::TIM_NSA_OTU].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_OtuFailureBase::TIM_NSA_OTU); }

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_FECM_DEFECT, ALM_OtuFailureBase::FECM_OTU)

    // Read the BDI_OTU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_BDI_DEFECT, ALM_OtuFailureBase::BDI_OTU)

    // Read the BERSD_OTU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_SDBER_DEFECT, ALM_OtuFailureBase::BERSD_OTU)

    // Read the FEC_SD_OTU defect from the monitor
    //ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_FEC_SD_DEFECT, ALM_OtuFailureBase::FEC_SD_OTU)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OTU_DISP_COMP_INIT, ALM_OtuFailureBase::DISP_OTU)

    return aBitFieldDefect;
}

//=====================================  ====================================  ======================================
// bit#:     11    10      9       8        7       6       5            4        3       2         1        0
// defect: UP_SA UP_NSA AIS_OTU LOF_OTU  LOM_OTU TIM_OTU TIM_NSA_OTU FECM_OTU  BDI_OTU BERSD_OTU FEC_SD_OTU DISP_OTU
//=====================================  ====================================  ======================================
ALM_BitField ALM_OtuFailures::Filter(ALM_BitField theFailure) const
{
    ALM_BitField tempFailureFilterResults = (theFailure & ourFailureProtectionMask);
 
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::UPPER_SA_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_SA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::UPPER_NSA_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::AIS_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & AIS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::LOF_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOF_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::LOM_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::TIM_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::TIM_NSA_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::FECM_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & FECM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::BDI_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & BDI_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::BERSD_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & BERSD_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::FEC_SD_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & FEC_SD_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_OtuFailureBase::DISP_OTU) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & DISP_FilterMask);
    }
 
    return tempFailureFilterResults;
}

//-----------------------------------------------------------------
//##ModelId=3C506C300273
ALM_BitField ALM_OtuFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
//##ModelId=3F954C2A03AC
ALM_BitField ALM_OtuFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//=================================================================================
// DRIVE LED with LOF-OTU for the SCMemberCards! LED is FALSE w/ UpperLayer Failure!
//=================================================================================
void ALM_OtuFailures::ProcessAfterSoaking()
{
    bool aLedStatus = false;

    if ( myCardIf && myCardIf->GetCardFamily().IsSCMember() )
    {
        //Separate soaking instances for LOF-OTU and LOM-OTU are needed to avoid interferences.
        aLedStatus = aLedStatus || myLed4LOFOTU.DefectUpdated( itsDefect[ALM_OtuFailureBase::LOF_OTU].GetStatus(), 
                                                               itsDefect[ALM_OtuFailureBase::LOF_OTU].GetTCount());

        aLedStatus = aLedStatus || myLed4LOMOTU.DefectUpdated( itsDefect[ALM_OtuFailureBase::LOM_OTU].GetStatus(), 
                                                               itsDefect[ALM_OtuFailureBase::LOM_OTU].GetTCount());

        //--------------------------------------------------------------------------
        // Verify that no UpperLayer Defect exists!
        //--------------------------------------------------------------------------
        if ( aLedStatus )
        {
            ALM_TCount upperLayerSACount  = 0;
            bool       upperLayerSADefect = false;
            myMonitor.GetDefectStatus(CT_TEL_OTU_UPPER_LAYER_FAIL_TA_DEFECT, &upperLayerSACount, &upperLayerSADefect);

            if ( upperLayerSADefect )
            {
                aLedStatus = false;
            }

            //----------------------------------------------------------------------
            // Additionally, AIS_OTU should -NOT- trigger the LED to report.
            //----------------------------------------------------------------------
            if ( aLedStatus )
            {
                ALM_TCount AISCount  = 0;
                bool       AISDefect = false;
                myMonitor.GetDefectStatus(CT_TEL_OTU_AIS_DEFECT, &AISCount, &AISDefect);

                if ( AISDefect )
                {
                    aLedStatus = false;
                }
            }
            //-------------------------------------------------------------
            // If PRBS test, then aLedStatus is false and LOF is suppressed
            //-------------------------------------------------------------
            if ( aLedStatus )
            {
                CFG_AppIf*   aConfigAppIf = myCardIf->GetOptIf().GetCfgPortSideAppPtr((CT_IntfId)myPortOffset);
                CFG_Region* aConfigRegion = aConfigAppIf->GetCfgRegion();
                if(aConfigRegion->IsValid())
                {
                    CFG_Opt& aCFG_Opt = static_cast<CFG_Opt&>((*aConfigRegion)[0]);
                    if(aCFG_Opt.GetPrbsTxEnable() || aCFG_Opt.GetPrbsRxEnable())
                    {
                        aLedStatus = false;
                    }
                }
            }

        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( myLedStatus != aLedStatus )
        {
            myLedStatus = aLedStatus;

            CT_DirectionFlag aLEDDirection = (myApplication.GetKeySuffix()==ALM_LINE_1_SUFFIX) ? CT_DIR_CARD_LINE: 
                                                                                                 CT_DIR_CARD_PORT;
            if ( myLedStatus )
            {
                AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_OTU_UID, 
                   myCardIf, 0/*time*/, myPortOffset, aLEDDirection);
            }
            else 
            {
                AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LED_OTU_UID, 
                   myCardIf,            myPortOffset, aLEDDirection);
            }
        }
    }
}

