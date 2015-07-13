/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of RS (Regenerator
                Section) layer
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_RsDefects.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Opt.h>


//To drive LED on LOF
#include <T6100_MainAppIf.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <T6100_OscChanIf.h>

#include <ErrorService/FC_Error.h>
#include <AM/AM_DefectCollector.h>
#include <AM/AM_DefectProcessor.h>
#include <AM/AM_AppIf.h>

#include <Alarm/ALM_RegionKeyDefinition.h>

#include <Alarm/ALM_SubApplicationOnCard.h>

#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_RsFailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include "ALM_RsFailures.h"
#include "ALM_LayerFailures.h"
#include <CsPii/CSPII_SysCfgParamIF.h>
#include <CsPii/CSPII_CardIF.h>

//==============  ================================  =======================  ==========================
//bit#:    14         13          12               11          10       9              8        7       6     5     4      3           2                   1           0
//defect: UP_SA   UP_NSA  UP_INT_SA  AIS-TX    LOS    GEN-AIS  TAIS    LOF   RF   LF    TIM  TIMNSA  GEN-AIS-INT LOF_INT CSF-OPU
//==============  ================================  =======================  ==========================

static const ALM_BitField UP_SA_FilterMask    = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField UP_NSA_FilterMask   = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField UP_INT_SA_FilterMask= 0x7FF8; // 111 1111 1111 1000 // UP_INT_SA and CSF-OPU TDTC
static const ALM_BitField AISTX_FilterMask    = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField LOS_FilterMask      = 0x7C07; // 111 1100 0000 0111
static const ALM_BitField GENAIS_FilterMask = 0x7F67;  // 111 1111 0110 0111 GEN-AIS inhabit LOF, TIM
static const ALM_BitField TAIS_FilterMask     = 0x7F07; // 111 1111 0000 0111
static const ALM_BitField LOF_FilterMask      = 0x7F87; // 111 1111 1000 0111
static const ALM_BitField RF_FilterMask       = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField LF_FilterMask       = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField TIM_FilterMask      = 0x7FF7; // 111 1111 1111 0111
static const ALM_BitField TIM_NSA_FilterMask  = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField GENAIS_INT_FilterMask = 0x7FFD; // 111 1111 1111 1101 Internal GEN-AIS inhabit internal LOF
static const ALM_BitField LOF_INT_FilterMask  = 0x7FFF; // 111 1111 1111 1111
static const ALM_BitField CSFOPU_FilterMask   = 0x7FF9; // 111 1111 1111 1001 //CSF-OPU inhibit LOF_INT and GEN-AIS-INT

static const ALM_BitField ourFailureProtectionMask = 0x7FFF;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures and defects of lower layer if one of the folowing failure
// or defect is declared: LOS, TAIS, LOF, TIM-R.
static const ALM_BitField ourFilterAllMask = 0x0790;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA and UP_INT_SA.
static const ALM_BitField ourNoFilterMask = 0x7007;

//-----------------------------------------------------------------
//##ModelId=3C506C300158
ALM_RsFailures::ALM_RsFailures (ALM_IndexNb theIndex,
                                ALM_AppIf& theApplication,
                                MON_RsDefects& theMonitor,
                                ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_RsFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr
    ),
    //Set the monitor
    myMonitor(theMonitor),
    //Set the configuration
    myLed(1000, 1000),
    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_RS_SOAKING_TIME)
{
    // Add all failures to LayerFailures object
    AddAt (ALM_RsFailureBase::UPPER_SA_RS, &myUpperSa);
    AddAt (ALM_RsFailureBase::UPPER_NSA_RS, &myUpperNsa);
    AddAt (ALM_RsFailureBase::UPPER_INT_SA_RS, &myUpperIntSa);
    AddAt (ALM_RsFailureBase::AIS_TX_RS, &myAisTx);
    AddAt (ALM_RsFailureBase::LOS_RS, &myLos);
    AddAt (ALM_RsFailureBase::TAIS_RS, &myTais);
    AddAt (ALM_RsFailureBase::LOF_RS, &myLof);
    AddAt (ALM_RsFailureBase::LOF_INT_RS, &myLofInt);
    AddAt (ALM_RsFailureBase::TIM_RS, &myTim);
    AddAt (ALM_RsFailureBase::TIM_NSA_RS, &myTimNsa);
    AddAt (ALM_RsFailureBase::LF_RS, &myLf);
    AddAt (ALM_RsFailureBase::RF_RS, &myRf);
    AddAt (ALM_RsFailureBase::CSF_OPU_RS, &myCsfOpu);
    AddAt (ALM_RsFailureBase::GEN_AIS_RS, &myGenAis);
    AddAt (ALM_RsFailureBase::GEN_AIS_INT_RS, &myGenAisInt);

    //To drive LED on LOF
    myLedStatus = false;
    myLedStatusAuditCnt = 0;

    // default the signal type to unknown
    mySignalType = (int)CT_TEL_SIGNAL_UNKNOWN;
        
    const string sKey = myApplication.GetKeySuffix();
    
    if      (sKey == ALM_LINE_SUFFIX)               {  myPortOffset = 0;  theDirn = CT_DIR_CARD_LINE; }
    else if (sKey == ALM_LINE_0_SUFFIX)             {  myPortOffset = 0;  theDirn = CT_DIR_CARD_LINE; }
    else if (sKey == ALM_LINE_1_SUFFIX)             {  myPortOffset = 1;  theDirn = CT_DIR_CARD_LINE; }
    else if (sKey == ALM_LINE_3_SUFFIX)             {  myPortOffset = 3;  theDirn = CT_DIR_CARD_LINE; }
    else if (sKey == ALM_LINE_4_SUFFIX)             {  myPortOffset = 4;  theDirn = CT_DIR_CARD_LINE; }

    else if (sKey == ALM_PORT_SUFFIX)               {  myPortOffset = 0;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_0_SUFFIX)             {  myPortOffset = 0;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_1_SUFFIX)             {  myPortOffset = 1;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_2_SUFFIX)             {  myPortOffset = 2;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_3_SUFFIX)             {  myPortOffset = 3;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_4_SUFFIX)             {  myPortOffset = 4;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_5_SUFFIX)             {  myPortOffset = 5;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_6_SUFFIX)             {  myPortOffset = 6;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_7_SUFFIX)             {  myPortOffset = 7;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_8_SUFFIX)             {  myPortOffset = 8;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_9_SUFFIX)             {  myPortOffset = 9;  theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_10_SUFFIX)            {  myPortOffset = 10; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_11_SUFFIX)            {  myPortOffset = 11; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_12_SUFFIX)            {  myPortOffset = 12; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_13_SUFFIX)            {  myPortOffset = 13; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_14_SUFFIX)            {  myPortOffset = 14; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_15_SUFFIX)            {  myPortOffset = 15; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_16_SUFFIX)            {  myPortOffset = 16; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_17_SUFFIX)            {  myPortOffset = 17; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_18_SUFFIX)            {  myPortOffset = 18; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_19_SUFFIX)            {  myPortOffset = 19; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_20_SUFFIX)            {  myPortOffset = 20; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_21_SUFFIX)            {  myPortOffset = 21; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_22_SUFFIX)            {  myPortOffset = 22; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_23_SUFFIX)            {  myPortOffset = 23; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_24_SUFFIX)            {  myPortOffset = 24; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_25_SUFFIX)            {  myPortOffset = 25; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_26_SUFFIX)            {  myPortOffset = 26; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_27_SUFFIX)            {  myPortOffset = 27; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_28_SUFFIX)            {  myPortOffset = 28; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_29_SUFFIX)            {  myPortOffset = 29; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_30_SUFFIX)            {  myPortOffset = 30; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_31_SUFFIX)            {  myPortOffset = 31; theDirn = CT_DIR_CARD_PORT; }

    else if (sKey == ALM_PORT_85_SUFFIX)            {  myPortOffset = 85; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_86_SUFFIX)            {  myPortOffset = 86; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_87_SUFFIX)            {  myPortOffset = 87; theDirn = CT_DIR_CARD_PORT; }
    else if (sKey == ALM_PORT_88_SUFFIX)            {  myPortOffset = 88; theDirn = CT_DIR_CARD_PORT; }
    else                                            {  myPortOffset = 0;  theDirn = CT_DIR_CARD_PORT; } 
    
    if (theApplication.GetContext().GetParent())
    {
		T6100_CardIf* theCardIf = NULL;
		theCardIf = dynamic_cast<T6100_CardIf*>(theApplication.GetContext().GetParent());
		if (!theCardIf)
		{
			//Could be an alternate telecom layer context. Check for card interface there.
			T6100_OscChanIf* theOscChanIf = dynamic_cast<T6100_OscChanIf*>(theApplication.GetContext().GetParent());
			if (theOscChanIf)
			{
				theCardIf = theOscChanIf->GetCardIf();
			}
		}
		myCardIf = theCardIf;

        if (myCardIf == NULL)
        {
            FC_THROW_ERROR(FC_SWError, "Cannot drive LED on TRN");
        }
    }
    else
    {
        myCardIf = NULL;
        FC_THROW_ERROR(FC_SWError, "Cannot drive LED on TRN");
    }
}

//-----------------------------------------------------------------
//##ModelId=3C506C300164
ALM_RsFailures::~ALM_RsFailures ()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C30016C
ALM_BitField ALM_RsFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_RS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_UPPER_LAYER_FAIL_TA_DEFECT, ALM_RsFailureBase::UPPER_SA_RS)

    // Read the UPPER_NSA_RS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_RsFailureBase::UPPER_NSA_RS)

    // Read the UPPER_INT_SA_RS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_INTERNAL_UPPER_LAYER_FAIL_TA_DEFECT, ALM_RsFailureBase::UPPER_INT_SA_RS)

    // Read the AIS_TX_RS defect status from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_AIS_TX_DEFECT, ALM_RsFailureBase::AIS_TX_RS)

    // Read the TAIS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_TLABAIS_DEFECT, ALM_RsFailureBase::TAIS_RS)

    // Read the LOF defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_LOF_DEFECT, ALM_RsFailureBase::LOF_RS)

    // Read the LF_RS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_LOCAL_FAULT_DEFECT, ALM_RsFailureBase::LF_RS)

    // Read the RF_RS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_REMOTE_FAULT_DEFECT, ALM_RsFailureBase::RF_RS)

    // Read the LOF defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_INTERNAL_LOF_DEFECT, ALM_RsFailureBase::LOF_INT_RS)

    // Read the CSF_OPU defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_INTERNAL_CSF_OPU_DEFECT, ALM_RsFailureBase::CSF_OPU_RS)

    // Read the GEN-AIS defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_GENAIS_DEFECT, ALM_RsFailureBase::GEN_AIS_RS)

    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_RS_INTERNAL_GENAIS_DEFECT, ALM_RsFailureBase::GEN_AIS_INT_RS)

    //=====================================================================================
    // TIM_RS is a special case scenario where it is ServiceAffecting(SA) or NSA
    // based on the provisioned MONTRCRS attribute (AIS, NOAIS). Must process special!
    //=====================================================================================
    myMonitor.GetDefectStatusSpecial(CT_TEL_RS_TIM_DEFECT, &aTCount, &aStatus, true);
    itsDefect[ALM_RsFailureBase::TIM_RS].SetTCount(aTCount);
    itsDefect[ALM_RsFailureBase::TIM_RS].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_RsFailureBase::TIM_RS); }
 
    myMonitor.GetDefectStatusSpecial(CT_TEL_RS_TIM_DEFECT, &aTCount, &aStatus, false);
    itsDefect[ALM_RsFailureBase::TIM_NSA_RS].SetTCount(aTCount);
    itsDefect[ALM_RsFailureBase::TIM_NSA_RS].SetStatus(aStatus);
    if (aStatus) { aBitFieldDefect += (1 << ALM_RsFailureBase::TIM_NSA_RS); }
 
    return aBitFieldDefect;
}

//==============  ================================  =======================  ==========================
//bit#:     12      11      10       9         8       7    6     5    4      3     2        1       0
//defect: UP_SA   UP_NSA  UP_INT_SA AIS-TX    LOS    TAIS   LOF   RF   LF    TIM  TIMNSA  LOF_INT CSF-OPU
//==============  ================================  =======================  ==========================
ALM_BitField ALM_RsFailures::Filter(ALM_BitField theFailure) const
{
    ALM_BitField tempFailureFilterResults = (theFailure & ourFailureProtectionMask);
 
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::UPPER_SA_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_SA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::UPPER_NSA_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::UPPER_INT_SA_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & UP_INT_SA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::AIS_TX_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & AISTX_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::LOS_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::GEN_AIS_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & GENAIS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::TAIS_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TAIS_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::LOF_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOF_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::RF_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & RF_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::LF_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LF_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::TIM_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::TIM_NSA_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & TIM_NSA_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::GEN_AIS_INT_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & GENAIS_INT_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::LOF_INT_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & LOF_INT_FilterMask);
    }
    if ( tempFailureFilterResults & (1 << ALM_RsFailureBase::CSF_OPU_RS) )
    {
        tempFailureFilterResults = (tempFailureFilterResults & CSFOPU_FilterMask);
    }

    return tempFailureFilterResults;
}

//-----------------------------------------------------------------
//##ModelId=3C506C30016E
ALM_BitField ALM_RsFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer.
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
//##ModelId=3F954C2A012B
ALM_BitField ALM_RsFailures::GetNoFilterMask() const
{
    // Directive to filter according to higher layer.
    return ourNoFilterMask;
}

//=================================================================================
// ProcessAfterSoaking() method is called every .5 seconds (ALM_LayerFailures).
// We want to "audit" the myLedStatus every 10 seconds to ensure it is set properly.
// This also will solve the issue of a LIAM - which uses OSC LOS/LOF information -
// being removed and reinserted during the time that the OSC LOS/LOF exists.
//=================================================================================
void ALM_RsFailures::ProcessAfterSoaking()
{
    myLedStatusAuditCnt++;

    bool aLedStatus = myLed.DefectUpdated(itsDefect[ALM_RsFailureBase::LOF_RS].GetStatus(), 
                                          itsDefect[ALM_RsFailureBase::LOF_RS].GetTCount());

    //------------------------------------------------------------------
    // For the case of the SCMemberCards (TRN, SMTMU, etc.), we need to
    // verify there is -NO- upper layer defect (ULD) that forced the LOF_RS.
    // Otherwise, we will -NOT- use the LOF_RS to trigger LED_RS w/ ULD.
    //------------------------------------------------------------------
    if ( aLedStatus )
    {
        if ( myCardIf && myCardIf->GetCardFamily().IsSCMember() )
        {
            ALM_TCount upperLayerSACount  = 0;
            bool       upperLayerSADefect = false;
            myMonitor.GetDefectStatus(CT_TEL_RS_UPPER_LAYER_FAIL_TA_DEFECT, &upperLayerSACount, &upperLayerSADefect);

            if ( upperLayerSADefect )
            {
                aLedStatus = false;
            }

            //-------------------------------------------------------------
            // If TAIS exists in RS Layer, then aLedStatus is false!
            //-------------------------------------------------------------
            if ( aLedStatus )
            {
                ALM_TCount taisCount  = 0;
                bool       taisDefect = false;
                myMonitor.GetDefectStatus(CT_TEL_RS_TLABAIS_DEFECT, &taisCount, &taisDefect);

                if ( taisDefect )
                {
                    aLedStatus = false;
                }
            }
            //-------------------------------------------------------------
            // If PRBS test, then aLedStatus is false and LOF is suppressed
            //-------------------------------------------------------------
            if ( aLedStatus )
            {
                CFG_AppIf*	 aConfigAppIf = myCardIf->GetOptIf().GetCfgPortSideAppPtr((CT_IntfId)myPortOffset);
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
    }

    if ( myCardIf && ((myLedStatus != aLedStatus) || (myLedStatusAuditCnt == 20)) ) // Audit every 10 seconds!
    {
        myLedStatus = aLedStatus;
        myLedStatusAuditCnt = 0;  // reset Audit.
            
        //------------------------------------------------------
        // Ensure that for the OSC the correct direction
        // is sent when calling AM Report or Clear Defect.
        //------------------------------------------------------
        AM_PortType calctheDirn = theDirn;

        if (myCardIf->GetCardFamily() == OSC_FAM)
        {
            const string sKey = myApplication.GetKeySuffix();

            if      (sKey == ALM_SIDE_A_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_A;
            else if (sKey == ALM_SIDE_B_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_B;
            else if (sKey == ALM_SIDE_C_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_C;
            else if (sKey == ALM_SIDE_D_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_D;
			else if (sKey == ALM_SIDE_E_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_E;
            else if (sKey == ALM_SIDE_F_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_F;
            else if (sKey == ALM_SIDE_G_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_A;
            else if (sKey == ALM_SIDE_H_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_B;
        }

        //---------------------------------------------------------------------------------
        // Use the LOF defect to drive LED. NOTE: for certain subnodes, the OSC led
        // is actually controlled on the corresponding LIAM module. Account for this here!
        //---------------------------------------------------------------------------------
        if ( (myCardIf->GetCardFamily() == OSC_FAM) && CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsOscLedOnLiamControlledBySPM() )
        {
            CT_SlotId     aDWDMInpSlotId  = UNKNOWN_SLOT_ID;  
            CT_CardFamily aDWDMInpCardFam = LIAM_FAM;
            T6100_CardIf* aDWDMInpCardIf  = NULL;
            //-------------------------------------------------------------------------
            // Find the LIAM cardIf - which is enough information for LED control.
            //-------------------------------------------------------------------------
            if      ( calctheDirn == CT_DIR_CARD_LINE_A ) aDWDMInpSlotId = LIAM_1;
            else if ( calctheDirn == CT_DIR_CARD_LINE_B ) aDWDMInpSlotId = LIAM_19;
            else if ( calctheDirn == CT_DIR_CARD_LINE_C ) aDWDMInpSlotId = LIAM_5;
            else if ( calctheDirn == CT_DIR_CARD_LINE_D ) aDWDMInpSlotId = LIAM_13;
            //-------------------------------------------------------------------------
            // If we are a NANO system, then the DWDMInputSlotId is different here!
            //-------------------------------------------------------------------------
            if ( CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsHwVer4() ) 
            {
                if ( CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsNeOLA() ) 
                {
                    if (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == NANO_OLA_CH88_N_OADM)
                    {
                        aDWDMInpCardFam = CADM_FAM;
                        if ( (calctheDirn == CT_DIR_CARD_LINE_A) || (calctheDirn == CT_DIR_CARD_LINE_C) )
                        {
                            aDWDMInpSlotId = CCM_A;
                        }
                        else if ( (calctheDirn == CT_DIR_CARD_LINE_B) || (calctheDirn == CT_DIR_CARD_LINE_D) )
                        {
                            aDWDMInpSlotId = CCM_B;
                        }
                    }
                    else
                    {
                        if ( calctheDirn == CT_DIR_CARD_LINE_B ) aDWDMInpSlotId = OLA_B; // SideA is o.k.
                    }
                }
                else // handle NANO SBOADM.
                {
                    if((CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == NANO_SBOADM_CH88_N) ||  //CONFIG 20
                       (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == NANO_SBOADM_CH88_N_S))  //CONFIG 24
                        aDWDMInpCardFam = CADM_FAM;
                    else if (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == NANO_SBOADM_CH44_N_F)//CONFIG 23
                        aDWDMInpCardFam = LIAM_FAM;
                    else
                        aDWDMInpCardFam = CCM_FAM;

                    if (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == NANO_SBOADM_CH88_N_S)  //CONFIG 24
                    {
                        if (calctheDirn == CT_DIR_CARD_LINE_A)
                        {
                            aDWDMInpSlotId = myCardIf->GetShelfId() == OPTICAL_SHELF_1 ? CADM_NANO_SSOADM_A : CADM_NANO_SSOADM_G;
                        }
                        else if (calctheDirn == CT_DIR_CARD_LINE_B)
                        {
                            aDWDMInpSlotId = myCardIf->GetShelfId() == OPTICAL_SHELF_1 ? CADM_NANO_SSOADM_B : CADM_NANO_SSOADM_H;
                        }
						else if (calctheDirn == CT_DIR_CARD_LINE_C)
                        {
                            aDWDMInpSlotId = CADM_NANO_SSOADM_C;
                        }
                        else if (calctheDirn == CT_DIR_CARD_LINE_D)
                        {
                            aDWDMInpSlotId = CADM_NANO_SSOADM_D;
                        }
						else if (calctheDirn == CT_DIR_CARD_LINE_E)
                        {
                            aDWDMInpSlotId = CADM_NANO_SSOADM_E;
                        }
                        else if (calctheDirn == CT_DIR_CARD_LINE_F)
                        {
                            aDWDMInpSlotId = CADM_NANO_SSOADM_F;
                        }
                    }
                    else
                    {
                        if ( (calctheDirn == CT_DIR_CARD_LINE_A) || (calctheDirn == CT_DIR_CARD_LINE_C) )
                        {
                            aDWDMInpSlotId = CCM_A;
                        }
                        else if ( (calctheDirn == CT_DIR_CARD_LINE_B) || (calctheDirn == CT_DIR_CARD_LINE_D) )
                        {
                            aDWDMInpSlotId = CCM_B;
                        }
                    }
                }
            }
            else
            {
                if(CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == SBOADM_CH88_4D_HCSS)
                {
                    aDWDMInpCardFam = CADM_FAM;
                    if ( (calctheDirn == CT_DIR_CARD_LINE_A))
                    {
                        aDWDMInpSlotId = CADM_FP3_A;
                    }
                    else if ( (calctheDirn == CT_DIR_CARD_LINE_B) )
                    {
                        aDWDMInpSlotId = CADM_FP3_B;
                    }
                    else if ( (calctheDirn == CT_DIR_CARD_LINE_C) )
                    {
                        aDWDMInpSlotId = CADM_FP3_C;
                    }
                    else if ( (calctheDirn == CT_DIR_CARD_LINE_D) )
                    {
                        aDWDMInpSlotId = CADM_FP3_D;
                    }
                }
            }

            T6100_SlotIf* aDWDMInpSlotIf = T6100_MainAppIf::Instance().GetShelfPtr(myCardIf->GetShelfId())->GetSlotPtr(aDWDMInpSlotId);
            if ( aDWDMInpSlotIf )
            {
                aDWDMInpCardIf = aDWDMInpSlotIf->GetCardPtr(aDWDMInpCardFam);
                if ( aDWDMInpCardIf )
                {
                    if ( aDWDMInpSlotIf->GetProvCardType() == DXOADM ) // DXOADM does NOT have OSC LED!
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_SG_LED_RS_UID, aDWDMInpCardIf);
                    }
                    else
                    {
                        if (myLedStatus)
                        {
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_RS_UID, aDWDMInpCardIf);
                        }
                        else 
                        {
                            AM_DefectCollector::GetInstance()->ClearDefect (AM_SG_LED_RS_UID, aDWDMInpCardIf);
                        }
                    }
                }
            }
        }
        else
        {
            
            if (myCardIf)
            {
                CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
                int thePortGroupSize = 1;
                if(aCardType == HGTMMS)
                {
                    if(mySignalType == CT_TEL_SIGNAL_FGE)
                    {
                        thePortGroupSize = 4;
                    }
                    else if(mySignalType == CT_TEL_SIGNAL_HGE || mySignalType == CT_TEL_SIGNAL_HGE_GFP)
                    {
                        thePortGroupSize = 10;
                    }
                }

                if (myLedStatus)
                {
                    for(int i = 0; i < thePortGroupSize; i++)
                    {
                        AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_RS_UID, myCardIf, 0, myPortOffset+i, calctheDirn);
                    }
                }
                else 
                {
                    for(int i = 0; i < thePortGroupSize; i++)
                    {
                        AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LED_RS_UID, myCardIf, myPortOffset+i, calctheDirn);
                    }
                }
            }
        }
    }

    //----------------------------------------------------------------------------------
    // For the signal alarm RS layer, we additionally need to read the CFG signal type
    // currently assigned to the port and update the BB if there was a change in the
    // configuration. The signal type is used to determine if a SONET or GbE alarm
    // is to be reported to AM.
    //----------------------------------------------------------------------------------
    
    // Get a pointer to the layers port Config application.
    CFG_AppIf* rsConfigAppIf = myApplication.GetCfgApp();

    // If the config application is valid, determine the signal type
    if (rsConfigAppIf != NULL )
    {
        CFG_Region* rsConfigRegion = rsConfigAppIf->GetCfgRegion();

        if (rsConfigRegion->IsValid())
        {
            CFG_Rs& aRsCfgObject = static_cast<CFG_Rs&>((*rsConfigRegion)[0]);
            CT_TEL_SignalType aSignalType = aRsCfgObject.GetSignalType();

            // If the signal type retrieved from CFG is different from what is currently
            // stored in the signal alarms RS filtered region, then update the region.
            if (itsFilteredFailureBase.GetSignalType() != aSignalType)
            {
                // Set the signal type into the BB
                itsFilteredFailureBase.SetSignalType(aSignalType);
                // Increment assiciated region modification counter
                itsFilteredFailureRegionPtr->IncModificationCounter();
            }
        }
    }

    if(myCardIf && myCardIf->GetCardFamily() == HDTG2_FAM)
    {
        uint8 aOppositId = (myPortOffset & 0x1) ? myPortOffset -1 : myPortOffset + 1;
        CFG_AppIf* aConfigAppIf = myCardIf->GetRsIf().GetCfgPortSideAppPtr((CT_IntfId)myPortOffset);
        CFG_AppIf* aOppositeConfigAppIf = myCardIf->GetRsIf().GetCfgPortSideAppPtr((CT_IntfId)aOppositId);
        if (aConfigAppIf && aOppositeConfigAppIf)
        {
            CFG_Rs& aCfgObject = static_cast<CFG_Rs&>((*aConfigAppIf->GetCfgRegion())[0]);
            CFG_Rs& aOppositeCfgObject = static_cast<CFG_Rs&>((*aOppositeConfigAppIf->GetCfgRegion())[0]);
            if ((aCfgObject.GetSignalType() == CT_TEL_SIGNAL_TGFC_BMP 
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_OC192
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_STM64
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_FC8G
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_TGLAN
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_TGLAN_FRAME
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_TGLAN_PREAMBLE
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_TGLAN_WFS
                || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_TGLAN_FRAME_STD) 
                && aCfgObject.GetSignalType() == aOppositeCfgObject.GetSignalType())
            {
                AM_DefectCollector::GetInstance()->ReportDefect(AM_INH_CSFGFP_OEO_FAIILURE_UID, myCardIf, 0, myPortOffset, CT_DIR_WAVE_LINE);
            }
            else
            {
                AM_DefectCollector::GetInstance()->ClearDefect (AM_INH_CSFGFP_OEO_FAIILURE_UID, myCardIf, myPortOffset, CT_DIR_WAVE_LINE);
            }
        }
    }
}
