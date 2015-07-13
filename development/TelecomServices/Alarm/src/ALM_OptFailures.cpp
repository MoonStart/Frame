/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm 
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class manages the failures of OPT (Optical) layer.
--------------------------------------------------------------------------*/

#include <CommonTypes/CT_Telecom.h>
#include <Monitoring/MON_OptDefects.h>
#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Opt.h>
#include <Configuration/CFG_Rs.h>

#include <T6100_MainAppIf.h>
#include <T6100_CardIf.h>
#include <T6100_SlotIf.h>
#include <T6100_OscChanIf.h>

#include <ErrorService/FC_Error.h>
#include <AM/AM_DefectCollector.h>
#include <Alarm/ALM_RegionKeyDefinition.h>

#include <Alarm/ALM_SubApplicationOnCard.h>

#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_OptFailureBase.h"
#include "../ALM_FailureRegionImp.h"

#include "ALM_OptFailures.h"
#include "ALM_LayerFailures.h"
#include <CsPii/CSPII_SysCfgParamIF.h>     
#include <CsPii/CSPII_CardIF.h>

/* OPT filtering table. This table contained the failure conditions
once they are filtered. The table entry (index) is a combination of
bits that represent the failure conditions. For OPT, there is 6
failures, so the table contained all possible combinations give by these 
failures. That means the table will have 2^6 (64) combinations. 

bit#:     5       4      3      2        1      0
defect: UP_SA   UP_NSA  LOS   SW_THR    LOC    MFA
*/
static const ALM_BitField ourFilteredFailureTable[] = 
{
    // Bit 0 - MFA filters nothing.
    0x00, 0x01,
    // Bit 1 - LOC filters nothing.
    0x02, 0x03,
    // Bit 2 - SW_THR (SignalDegrade) filters nothing.
    0x04, 0x05, 0x06, 0x07,
    //=========================================
    // Bit 3 - LOS filters SW_THR, LOC and MFA.
    //=========================================
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    //------------------------------------------------
    // Bit 4 - UPPER_NSA filters nothing.
    //------------------------------------------------
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    //------------------------------------------------
    // Bit 5 - UPPER_SA does NOT filter LOS.
    //------------------------------------------------
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28
};


static const ALM_BitField ourFailureProtectionMask = 0x003f;

/*------- Mask to set the filter type of lower layer --------*/
// Filter all failures & defect of lower layer if one of the following 
// failure or defect is declared: UP_SA, LOS
static const ALM_BitField ourFilterAllMask = 0x0028;

/*------- Mask specifying which defect/failure are not filtered by upper layer -----*/
// Do not filter the following failures & defect if upper layer is in 
// failure or defect: UP_SA and UP_NSA.
static const ALM_BitField ourNoFilterMask = 0x0030;

//-----------------------------------------------------------------
//##ModelId=3C506C3101F9
ALM_OptFailures::ALM_OptFailures (ALM_IndexNb theIndex,
                                  ALM_AppIf& theApplication,
                                  MON_OptDefects& theMonitor,
                                  ALM_LayerFailures* theHigherLayerPtr):
    // Calls base class constructor
    ALM_LayerFailures 
    ( 
        ALM_OptFailureBase::ALM_NB_OF_FAILURE,
        theIndex,
        theApplication,
        theHigherLayerPtr,
        ALM_LayerFailures::ALM_SP_NB_OF_SOAK_DEFECT
    ),
    //Set the monitor
    myMonitor(theMonitor),

    //Upper None Service Affecting has a soaking time of 90s.
    myUpperNsa(ALM_UPPER_NSA_OPT_SOAKING_TIME),

    //-------------------------------------------
    // Signal Protection Not Service Affecting
    // must report NSA flag after 10 second soak
    // and clear   NSA flag after 2  second soak.
    // NOTE: this is the opposite of reporting/clearing
    //       defects, because SP-NSA is REPORTED
    //       when defects are CLEARED!
    //-------------------------------------------
    mySigProtNSA(ALM_DEFAULT_RECOVERY_TIME, ALM_DEFAULT_SOAKING_TIME)

{
    // Add all failures to LayerFailures object
    AddAt (ALM_OptFailureBase::UPPER_SA_OPT, &myUpperSa);
    AddAt (ALM_OptFailureBase::UPPER_NSA_OPT, &myUpperNsa);
    AddAt (ALM_OptFailureBase::LOS_OPT, &myLos);
    AddAt (ALM_OptFailureBase::SWTH_OPT, &mySwThresh);
    AddAt (ALM_OptFailureBase::LOC_OPT, &myLoc);
    AddAt (ALM_OptFailureBase::MFA_OPT, &myMfa);

    // Add all SP Soak failures to LayerFailures object
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_NOT_SA,     &mySigProtNSA);
    AddSigProtSoakAt (ALM_LayerFailures::SOAK_SP_PROTNA_UID, &mySigProtProtna);

    // default the signal type to unknown
    mySignalType = (int)CT_TEL_SIGNAL_UNKNOWN;

    //To drive LED on LOS
    myLedStatus = false;
    myLedStatusAuditCnt = 0;

    myCardIf = NULL;
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
    }
}

//-----------------------------------------------------------------
//##ModelId=3C506C310206
ALM_OptFailures::~ALM_OptFailures ()
{
}

//-----------------------------------------------------------------
//##ModelId=3C506C31020D
ALM_BitField ALM_OptFailures::ReadDefects() const
{
    bool aStatus = false;
    ALM_TCount aTCount = 0;

    ALM_BitField aBitFieldDefect = 0;

    // Read the UPPER_SA_OPT defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OPT_UPPER_LAYER_FAIL_TA_DEFECT, ALM_OptFailureBase::UPPER_SA_OPT)

    // Read the UPPER_NSA_OPT defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OPT_UPPER_LAYER_FAIL_NTA_DEFECT, ALM_OptFailureBase::UPPER_NSA_OPT)

    //-------------------------------------------------------------
    // Read the LOS_OPT defect from the monitor.
    // NOTE: read the PII value because MON will hardcode the
    //       LOS_OPT to TRUE when EQPT::OOS; but we want to 
    //       maintain the correct LOS/LED behavior to user.
    //-------------------------------------------------------------
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_PII_OPT_LOSS_LIGHT_DEFECT, ALM_OptFailureBase::LOS_OPT)

    // Read the SWTH_OPT defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OPT_SDPWR_DEFECT, ALM_OptFailureBase::SWTH_OPT)

    //----------------MR 167315------------------------------------
    // Read the LOS_LOC defect from the monitor
    // ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OPT_LOSS_CLK_DEFECT, ALM_OptFailureBase::LOC_OPT)
    //----------------MR 167315------------------------------------

    // Read the MFA_OPT defect from the monitor
    ALM_GET_DEFECT_STATUS(myMonitor, CT_TEL_OPT_MISMATCH_FACILITY_DEFECT, ALM_OptFailureBase::MFA_OPT)

    return aBitFieldDefect;
}

//-----------------------------------------------------------------
//##ModelId=3C506C310218
ALM_BitField ALM_OptFailures::Filter(ALM_BitField theFailure) const
{
    return ourFilteredFailureTable[theFailure & ourFailureProtectionMask];
}

//-----------------------------------------------------------------
//##ModelId=3C506C31020F
ALM_BitField ALM_OptFailures::GetFilterAllMask() const
{
    // Directive to filter the lower layer
    return ourFilterAllMask;
}

//-----------------------------------------------------------------
//##ModelId=3F954C2D0080
ALM_BitField ALM_OptFailures::GetNoFilterMask() const
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
void ALM_OptFailures::ProcessAfterSoaking()
{
    //---------------------------------------------------------------------------------
    // Use the LOS defect to drive LED. NOTE: for certain subnodes, the OSC led
    // is actually controlled on the corresponding LIAM module. Account for this here!
    //---------------------------------------------------------------------------------
    if ( ((myCardIf) && (myCardIf->GetCardFamily() == OSC_FAM)) &&
         (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsOscLedOnLiamControlledBySPM()) )
    {
        myLedStatusAuditCnt++;

        bool aLedStatus = myLos.DefectUpdated(itsDefect[ALM_OptFailureBase::LOS_OPT].GetStatus(), itsDefect[ALM_OptFailureBase::LOS_OPT].GetTCount());

        if ( (myLedStatus != aLedStatus) || (myLedStatusAuditCnt == 20) ) // Audit every 10 seconds!
        {
            myLedStatus = aLedStatus;
            myLedStatusAuditCnt = 0;  // reset Audit.

            AM_PortType calctheDirn = CT_DIR_CARD_LINE_A;
            const string sKey = myApplication.GetKeySuffix();
   
            if      (sKey == ALM_SIDE_A_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_A;
            else if (sKey == ALM_SIDE_B_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_B;
            else if (sKey == ALM_SIDE_C_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_C;
            else if (sKey == ALM_SIDE_D_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_D;
            else if (sKey == ALM_SIDE_E_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_E;
            else if (sKey == ALM_SIDE_F_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_F;
            else if (sKey == ALM_SIDE_G_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_A;
            else if (sKey == ALM_SIDE_H_SUFFIX) calctheDirn = CT_DIR_CARD_LINE_B;

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
                            aDWDMInpSlotId = myCardIf->GetShelfId() == OPTICAL_SHELF_2 ? CADM_NANO_SSOADM_G : CADM_NANO_SSOADM_A;
                        }
                        else if (calctheDirn == CT_DIR_CARD_LINE_B)
                        {
                            aDWDMInpSlotId = myCardIf->GetShelfId() == OPTICAL_SHELF_2 ? CADM_NANO_SSOADM_H : CADM_NANO_SSOADM_B;
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
                        AM_DefectCollector::GetInstance()->ClearDefect (AM_SG_LED_OPT_UID, aDWDMInpCardIf);
                    }
                    else
                    {
                        if (myLedStatus)
                        {
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_OPT_UID, aDWDMInpCardIf);
                        }
                        else
                        {
                            AM_DefectCollector::GetInstance()->ClearDefect (AM_SG_LED_OPT_UID, aDWDMInpCardIf);
                        }
                    }
                }
            }
        }
    }

    //----------------------------------------------------------------------------------
    // For the signal alarm OPT layer, we additionally need to read the CFG signal type
    // currently assigned to the port and update the BB if there was a change in the
    // configuration. The signal type is used to determine if a SONET(LOC) or GbE(LOSYNC) 
    // alarm is to be reported to AM (only in the port direction).
    // NOTE: CFG_RS is intentionally being used here, as the CFG_OPT layer's use
    //       of SignalType doesn't seem to be as easily understood by me :(
    //----------------------------------------------------------------------------------

    CFG_AppIf* aConfigAppIf = myApplication.GetCfgApp();

    // If the config application is valid, determine the signal type
    if (aConfigAppIf != NULL )
    {
        CFG_Region* aConfigRegion = aConfigAppIf->GetCfgRegion();
        if (aConfigRegion->IsValid())
        {
            CFG_Rs& aCfgObject = static_cast<CFG_Rs&>((*aConfigRegion)[0]);
            CT_TEL_SignalType aSignalType = aCfgObject.GetSignalType();

            // If the signal type retrieved from CFG is different from what is currently
            // stored in the signal alarms OPT filtered region, then update the region.
            if (itsFilteredFailureBase.GetSignalType() != aSignalType)
            {
                // Set the signal type into the BB
                itsFilteredFailureBase.SetSignalType(aSignalType);
                // Increment assiciated region modification counter
                itsFilteredFailureRegionPtr->IncModificationCounter();
            }
        }
    }
}

