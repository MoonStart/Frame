// /*--------------------------------------------------------------------------
// Copyright(c) Tellabs Transport Group. All rights reserved
// 
//  SUBSYSTEM:     Signal Alarm
//  TARGET   :     APM
//  AUTHOR   :     Marc Vendette, Patrick Meehan
//  DESCRIPTION:   Call the AM interface on a region change
// --------------------------------------------------------------------------*/

#include <BaseClass/FC_TextStream.h>
#include <ErrorService/FC_Error.h>
#include <CsPii/CSPII_CardIF.h>

#include <AM/AM_DefectCollector.h>
#include <T6100_MainAppIf.h>
#include <T6100_SlotIf.h>
#include <T6100_CardIf.h>
#include <T6100_TelecomIf.h>

#include <string.h>

#include "../ALM_AppIf.h"
#include "../ALM_FailureBase.h"
#include "../ALM_FailureRegionImp.h"
#include "../ALM_RegionKeyDefinition.h"
#include "Alarm/ALM_SubApplicationOnRpt.h"

#include <Configuration/CFG_AppIf.h>
#include <Configuration/CFG_Region.h>
#include <Configuration/CFG_Rs.h>
#include <Configuration/CFG_Hop.h>
#include <Configuration/CFG_Sync.h>
#include <Configuration/CFG_SyncSubApplication.h>
#include <Configuration/CFG_Definitions.h>
#include <Configuration/CFG_Tcm.h>
#include <CsPii/CSPII_SysCfgParamIF.h>     
#include <SCFG/SCFG_AppIf.h>
#include <SignalProtection/SP_ProtectionGroupConfigRegionImp.h>
#include <SignalProtection/SP_1plus1ProtectionGroupConfig.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>

#include "ALM_FailureModificationAction.h"
#include "../ALM_TcmFailureBase.h"

#include <Alarm/ALM_OduFailureBase.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_OduDefects.h>
#include <Monitoring/MON_OduConfig.h>
#include <Monitoring/MON_RsDefects.h>
#include "ALM_LayerFailures.h"
#include <CommonTypes/CT_PortMap.h>

/**
 * Method used to initialize the the theirUidTable[], which is used to map
 * the common type Signal Alarm failure to an Alarm Management UID.
 */
void ALM_FailureModificationAction::InitUidTable() //line side or supervisory channel 1
{
    //OTS FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_LOS_OTS]       = AM_SG_LOS_OTS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOOSC_OTS]     = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_PMI_OTS]       = AM_SG_PMI_OTS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDI_OTS]       = AM_SG_BDI_OTS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDIO_OTS]      = AM_SG_BDIO_OTS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDIP_OTS]      = AM_SG_BDIP_OTS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_OTS]       = AM_SG_TIM_OTS_UID;

    //OMS FAILURES   
    theirUidTable[CT_TelAlarmCondition::ALM_AOPE_OMS]      = AM_AOPE;
    theirUidTable[CT_TelAlarmCondition::ALM_OPOVLD_OMS]    = AM_OPOVLD;
    theirUidTable[CT_TelAlarmCondition::ALM_LOS_OMS]       = AM_SG_LOS_OMS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOSINT_OMS]    = AM_SG_LOS_INT_OMS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FDIO_OMS]      = AM_SG_FDIO_OMS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FDIP_OMS]      = AM_SG_FDIP_OMS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_PMI_OMS]       = AM_SG_PMI_OMS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDIO_OMS]      = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDIP_OMS]      = AM_INVALID_UID;

    //OPT FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_LOS_OPT]       = AM_SG_LOS_OPT_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SWTH_OPT]      = AM_SG_SWTHRESH_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOC_OPT]       = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_MFA_OPT]       = AM_SG_MFA_OPT_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_OPT]  = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_OPT] = AM_INVALID_UID;

    //OCH FALURES
    theirUidTable[CT_TelAlarmCondition::ALM_LOS_OCH]       = AM_SG_LOS_OCH_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_DTD_OCH]       = AM_SG_DTD_OCH_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_OCI_OCH]       = AM_SG_OCI_OCH_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FDIO_OCH]      = AM_SG_FDIO_OCH_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FDIP_OCH]      = AM_SG_FDIP_OCH_UID;

    //OTU FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_DISP_OTU]      = AM_SG_DISPCOMP_INIT_OTU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOF_OTU]       = AM_SG_LOF_OTU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOM_OTU]       = AM_SG_LOM_OTU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_OTU]       = AM_SG_AIS_OTU_NSA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_NSA_OTU]   = AM_SG_TIM_OTU_NOAIS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_OTU]       = AM_SG_TIM_OTU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FECM_OTU]      = AM_SG_OTU_FECM_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDI_OTU]       = AM_SG_BDI_OTU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BERSD_OTU]     = AM_SG_BERSD_OTU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FEC_SD_OTU]    = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_OTU]  = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_OTU] = AM_INVALID_UID;

    //ODU FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_LOFLOM_ODU]    = AM_SG_LOFLOM_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_MSIM_ODU]      = AM_SG_MSIM_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_GENAIS_ODU]    = AM_SG_GENAIS_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_ODU]       = AM_SG_AIS_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_NSA_ODU]   = AM_SG_TIM_ODU_NOAIS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_ODU]       = AM_SG_TIM_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_PLM_ODU]       = AM_SG_PLM_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LCK_ODU]       = AM_SG_LCK_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_OCI_ODU]       = AM_SG_OCI_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BER_ODU]       = AM_SG_BERSDODU_NSA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDI_ODU]       = AM_SG_BDI_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOOMFI_ODU]       = AM_SG_LOOMFI_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SSF_ODU]       = AM_SG_SSF_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_ODU]  = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_ODU] = AM_INVALID_UID;

    //TCM FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_TCM]       = AM_SG_AIS_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_NSA_TCM]   = AM_SG_TIM_ODU_NOAIS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_TCM]       = AM_SG_TIM_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LTC_TCM]       = AM_SG_LTC_TCM_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LTC_NSA_TCM]       = AM_SG_LTC_TCM_NSA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LCK_TCM]       = AM_SG_LCK_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_OCI_TCM]       = AM_SG_OCI_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BER_TCM]       = AM_SG_BERSDODU_NSA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_BDI_TCM]       = AM_SG_BDI_ODU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_TCM]  = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_TCM] = AM_INVALID_UID;

    //RS FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_CSF_OPU_RS]    = AM_SG_CSF_OPU_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_TX_RS]     = AM_SG_AISTX_RS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOS_RS]        = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_GENAIS_RS] = AM_SG_GENAIS_RS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TAIS_RS]       = AM_SG_TAIS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOF_RS]        = AM_SG_LOF_RS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOF_INT_RS]    = AM_SG_LOF_INT_RS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LF_RS]         = AM_SG_LF_TGLAN_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_RF_RS]         = AM_SG_RF_TGLAN_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_NSA_RS]    = AM_SG_TIM_RS_NOAIS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_RS]        = AM_SG_TIM_RS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_RS]   = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_RS]  = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_INT_SA_RS] = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_GENAIS_INT_RS] = AM_SG_GENAIS_INT_RS_UID;

    //MS FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_INT_MS]    = AM_SG_AIS_L_INT_UID; // SMTMx PortSide
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_MS]        = AM_SG_AIS_L_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_RDI_MS]        = AM_SG_RFI_L_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SFBER_MS]      = AM_SG_BERSF_L_NSA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SDBER_MS]      = AM_SG_BERSD_L_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_MS]   = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_MS]  = AM_INVALID_UID;

    //HOP FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_SDBER_HOP]     = AM_SG_BERSD_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SFBER_HOP]     = AM_SG_BERSF_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_RDI_HOP]       = AM_SG_RFI_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_PLM_HOP]       = AM_SG_PLM_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TIM_HOP]       = AM_SG_TIM_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UNEQ_HOP]      = AM_SG_UNEQ_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOP_HOP]       = AM_SG_LOP_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_HOP]       = AM_SG_AIS_P_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_HOP] = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_HOP]  = AM_INVALID_UID;

	//GFP FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_AUTONEGFAIL_GFP]= AM_SG_ANF_ETH_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_RMTLF_GFP]      = AM_SG_RMTLF_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_CSF_RDI_GFP]    = AM_SG_CSF_RDI_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_CSF_FDI_GFP]    = AM_SG_CSF_FDI_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_CSF_FEFI_GFP]   = AM_SG_CSF_FEFI_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_CSF_LOSYNC_GFP] = AM_SG_CSF_LOSYNC_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_CSF_LOS_GFP]    = AM_SG_CSF_LOS_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOFD_GFP]       = AM_SG_LOFD_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOA_GFP]        = AM_SG_LOA_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SQM_GFP]        = AM_SG_SQM_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_CHEC_GFP]       = AM_SG_CHEC_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_PLI_GFP]        = AM_SG_PLI_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_PLM_GFP]        = AM_SG_PLM_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_INT_SA_GFP] = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_GFP]  = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_GFP]   = AM_INVALID_UID;

    //SYNC FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_FREERUN_SYNC]  = AM_FRNGSYNC_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_HOLDOVER_SYNC] = AM_HLDOVRSYNC_UID;

    //GbE FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_LOSYNC_GBE]    = AM_SG_LOSYNC_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOCSYNC_GBE]   = AM_SG_LOCSYNC_UID;

    //DS1 FAILURES
    theirUidTable[CT_TelAlarmCondition::ALM_LOS_T1E1]      = AM_SG_DS1_LOS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LOF_T1E1]      = AM_SG_DS1_LOF_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_AIS_T1E1]      = AM_SG_DS1_AIS_NSA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FREQOFF_T1E1]  = AM_SG_FREQOFF_NSA_UID;

    //SIGNAL PROTECT DEFECTS
    theirUidTable[CT_TelAlarmCondition::ALM_SP_NOT_SA]           = AM_SP_NOT_SERVICE_AFFECTING_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SP_STRM_A_NR]        = AM_SP_STREAM_ALM_NR_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SP_ALM_MATE_ID]      = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SP_PROTNA_UID]       = AM_SP_PROTNA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SP_ODUKP_PROTNA_UID] = AM_SP_ODUKP_PROTNA_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SP_FOP_PM_UID]       = AM_SP_FOP_PM_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SP_FOP_NR_UID]       = AM_SP_FOP_NR_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SP_ODUKP_NOT_SA]     = AM_SP_ODUKP_NOT_SERVICE_AFFECTING_UID;

    //DCC DEFECTS
    theirUidTable[CT_TelAlarmCondition::ALM_DCC_LINK_INCMPLT] = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_DCC_LINK_DOWN]    = AM_SG_CABS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_DCC]     = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_DCC]    = AM_INVALID_UID;

    //GCC DEFECTS
    theirUidTable[CT_TelAlarmCondition::ALM_GCC_LINK_INCMPLT] = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_GCC_LINK_DOWN]    = AM_SG_CABS_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_GCC]     = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_GCC]    = AM_INVALID_UID;

    //VCG DEFECTS
    //theirUidTable[CT_TelAlarmCondition::ALM_LOS_ALIGN_VCG]    = AM_SG_LOS_ALIGN_UID;
    //theirUidTable[CT_TelAlarmCondition::ALM_TLC_TX_VCG]       = AM_SG_TLC_TX_UID;
    //theirUidTable[CT_TelAlarmCondition::ALM_PLC_TX_VCG]       = AM_SG_PLC_TX_UID;

    theirUidTable[CT_TelAlarmCondition::ALM_LOS_MF_ALIGN_VCG] = AM_SG_VCG_LOM_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_SQM_VCG]          = AM_SG_VCG_SQM_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_MND_VCG]          = AM_SG_VCG_MND_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_TLC_RX_VCG]       = AM_SG_TLC_RX_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_PLC_RX_VCG]       = AM_SG_PLC_RX_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FOP_RX_VCG]       = AM_SG_FOP_RX_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_FOP_TX_VCG]       = AM_SG_FOP_TX_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_VCG]    = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_VCG]     = AM_INVALID_UID;

    // MAC ETH DEFECTS
    theirUidTable[CT_TelAlarmCondition::ALM_RFLINKFAIL_MAC]   = AM_SG_RMTLF_GFP_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_LACPFAIL_MAC]     = AM_SG_MAC_LACPFAIL_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_NSA_MAC]    = AM_INVALID_UID;
    theirUidTable[CT_TelAlarmCondition::ALM_UPPER_SA_MAC]     = AM_INVALID_UID;
}

/**
 * Constructor. Instantiation will create the theirUidTable[] table which maps the
 * common type Signal Alarm failure to an Alarm Management UID. Then specific tweaks
 * can be made to the table, based on the card type.
 */
ALM_FailureModificationAction::ALM_FailureModificationAction(ALM_AppIf& theAppIf, 
                                                             T6100_CardIf* theCardIf,
                                                             T6100_TelecomIf* theRptIf):
    myAppIf(theAppIf),
    myCardIf(theCardIf),
    myT1E1If(NULL),
    myLOFLOCAlmExists(false),
    myPortOffset(0),
    myRptIf(theRptIf),
    myAmPortType(CT_DIR_INVALID)
{      
    // Init UID table
    InitUidTable();

    // Patch to resolve the fact that the RAM, SMTM, and OPSM implementations use
    // 7 different regions instead of 7 objects within the same region, for each port
    ALM_CalculatePortOffset();
    
    if (theCardIf->GetCardFamily().GetCardFamily() != CARD_FAM_SC)
    {
        // Set the AM PortType
        myAmPortType = CT_ITS_Utility::FindPortType(isOtsOms(), GetCTDirection(), GetCTSide(), myCardIf, true); // SignalAlmInvocation
    }
    else
    {
        //----------------------------------------------------------------------------------
        // ALM_FailureModificationAction() should NEVER run on Controller card
        // with CardFamily() == CARD_FAM_SC! SmartCards run ALM_FailureModificationAction!
        //----------------------------------------------------------------------------------
        fc_cout << "ALM_FailureModificationAction - please notify sharkey immediately!!!" << endl;
        fc_cout << "ALM_FailureModificationAction - please notify sharkey immediately!!!" << endl;
        fc_cout << "ALM_FailureModificationAction - please notify sharkey immediately!!!" << endl;
    }

    if (theCardIf->GetCardFamily().GetCardFamily() == CARD_FAM_OSC)
    {
        // Special UIDs for the OSC  
        theirUidTable[CT_TelAlarmCondition::ALM_LOF_RS]     = AM_SG_LOF_OSC_UID;
        theirUidTable[CT_TelAlarmCondition::ALM_LOS_OPT]    = AM_SG_LOS_OSC_UID;
        theirUidTable[CT_TelAlarmCondition::ALM_AIS_TX_RS]  = AM_INVALID_UID;

        // Set SPMNANO up for SYNC alarming
        if (isSync() == true) 
        {
            myPortOffset = AM_UNKNOWN_INDEX;
            myAmPortType = CT_DIR_DONT_CARE;
        }
    }

    if (GetCTDirection() == CT_DIRECTION_PORT)
    {
        // When signal alarm is instantiated on the port side of the 
        // OLIM/LIAM and OAM cards, only the DTD fault is desired to
        // be reported. Thus to ensure LOS OCH-L is not reported on the
        // port side, the LOS OCH-L UID is over-written as invalid.
        theirUidTable[CT_TelAlarmCondition::ALM_LOS_OCH]  = AM_INVALID_UID;
    }

    //--------------------------------------------------
    // Customize further for SmartCards! IsSCMember()
    //--------------------------------------------------
    if (theCardIf->GetCardFamily().IsSCMember())
    {        
        CustomizeUIDTableForScCardFamily();
    }

    for (uint32 i=0; i<CT_TEL_NB_STS1_AU3_IN_OC48_STM16; i++)
    {
        myStartChannelProvisionedHasDefect[i] = false;
    }
}

/**
 * Constructor. Instantiation will create the theirUidTable[] table which maps the
 * common type Signal Alarm failure to an Alarm Management UID. Then specific tweaks
 * can be made to the table, based on the card type.
 */
ALM_FailureModificationAction::ALM_FailureModificationAction(ALM_AppIf& theAppIf, T6100_TelecomIf* theT1E1If):
    myAppIf(theAppIf),
    myCardIf(NULL),
    myT1E1If(theT1E1If),
    myLOFLOCAlmExists(false),
    myPortOffset(0),
    myRptIf(NULL),
    myAmPortType(CT_DIR_INVALID)
{      
    // Init UID table
    InitUidTable();

    // Patch to resolve the fact that the RAM, SMTM, and OPSM implementations use
    // 7 different regions instead of 7 objects within the same region, for each port
    ALM_CalculatePortOffset();

    for (uint32 i=0; i<CT_TEL_NB_STS1_AU3_IN_OC48_STM16; i++)
    {
        myStartChannelProvisionedHasDefect[i] = false;
    }
}

//-----------------------------------------------------------------
// Customize the theirUidTable[] based upon the provisioned card.
//-----------------------------------------------------------------
void ALM_FailureModificationAction::CustomizeUIDTableForScCardFamily()
{
    // Init UID table
    InitUidTable();

    // Set the AM PortType
    myAmPortType = CT_ITS_Utility::FindPortType(isOtsOms(), GetCTDirection(), GetCTSide(), myCardIf, true); // SignalAlmInvocation
    CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();

    //---------------------------------------------------------------------------------
    // The UID table which maps the Signal Alarm (SA) failure to an Alarm Management
    // (AM) UID defaults all alarms to be Service Affecting (SA). Some cards have
    // requirements that specific alarms be displayed as either SA or Non-Service
    // Affecting (NSA). For those cases, SigAlm will always pass an NSA alarm UID to AM,
    // and AM determines if SA or NSA is reported. This is done here by overwriting
    // the UID table for the specified card instance.
    //---------------------------------------------------------------------------------
    switch (myCardIf->GetCardFamily().GetCardFamily())
    {
        case CARD_FAM_HDTG:
            theirUidTable[CT_TelAlarmCondition::ALM_LOS_OPT] = AM_SG_LOS_OPT_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_LOF_OTU] = AM_SG_LOF_OTU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_TIM_OTU] = AM_SG_TIM_OTU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_LOF_RS]   = AM_SG_LOF_RS_NSA_UID;

            if (GetCTDirection() == CT_DIRECTION_PORT)
            {
                theirUidTable[CT_TelAlarmCondition::ALM_TIM_RS] = AM_SG_TIM_RS_NSA_UID;
            }
            break;

        case CARD_FAM_SSM40:
            theirUidTable[CT_TelAlarmCondition::ALM_LOFLOM_ODU]    = AM_SG_LOFLOM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_MSIM_ODU]      = AM_SG_MSIM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_PLM_ODU]       = AM_SG_PLM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_TIM_ODU]       = AM_SG_TIM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_AIS_OTU]       = AM_SG_AIS_OTU_NSA_UID; // just enable SSM40
            // Sync alarm (Freerun/Hldover) on card should not have a side
            if (isSync() == true) myAmPortType = CT_DIR_DONT_CARE;

            // For OSM20 RMTLF, use the LF defect at the Rs layer and then have Alarm map it into the RMTLF alarm 
            if( aCardType == CARD_TYPE_OSM20 )
            {
                theirUidTable[CT_TelAlarmCondition::ALM_LF_RS]     = AM_SG_RMTLF_GFP_UID;
            }
            break;


        case CARD_FAM_OMM:
            theirUidTable[CT_TelAlarmCondition::ALM_LOFLOM_ODU]    = AM_SG_LOFLOM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_MSIM_ODU]      = AM_SG_MSIM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_PLM_ODU]       = AM_SG_PLM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_TIM_ODU]       = AM_SG_TIM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_AIS_OTU]       = AM_SG_AIS_OTU_NSA_UID;        
            break;

        case CARD_FAM_OSM:
            theirUidTable[CT_TelAlarmCondition::ALM_LOFLOM_ODU]    = AM_SG_LOFLOM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_MSIM_ODU]      = AM_SG_MSIM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_PLM_ODU]       = AM_SG_PLM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_TIM_ODU]       = AM_SG_TIM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_AIS_OTU]       = AM_SG_AIS_OTU_NSA_UID; 
            // Sync alarm (Freerun/Hldover) on card should not have a side
            if (isSync() == true) myAmPortType = CT_DIR_DONT_CARE;
            break;

        case CARD_FAM_PACKET:
        case CARD_FAM_ENH_PACKET:
            // Sync alarm (Freerun/Hldover) on card should not have a side
            if (isSync() == true) myAmPortType = CT_DIR_DONT_CARE;
            break;

        case CARD_FAM_SSM:
            theirUidTable[CT_TelAlarmCondition::ALM_CSF_LOSYNC_GFP] = AM_SG_VCG_CSF_LOSYNC_GFP_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_CSF_FEFI_GFP] = AM_SG_VCG_CSF_FEFI_GFP_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_CSF_LOS_GFP] = AM_SG_VCG_CSF_LOS_GFP_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_LOFD_GFP] = AM_SG_VCG_LOFD_GFP_UID;
            // continue...
        case CARD_FAM_SMTM:
            //--------------------------------------------------------------
            // The following SMTM OPT, OTU and RS alarms must be reported as
            // NSA, for both the line and port sides. Alarm management will
            // decide if the alarm should be escalated to SA.
            //--------------------------------------------------------------
            theirUidTable[CT_TelAlarmCondition::ALM_LOS_OPT]    = AM_SG_LOS_OPT_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_LOF_OTU]    = AM_SG_LOF_OTU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_TIM_OTU]    = AM_SG_TIM_OTU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_LOF_RS]     = AM_SG_LOF_RS_NSA_UID;

            if (GetCTDirection() == CT_DIRECTION_PORT)
            {
                theirUidTable[CT_TelAlarmCondition::ALM_TIM_RS] = AM_SG_TIM_RS_NSA_UID;
            }

            // The following Path alarms must also be reported as NSA.
            theirUidTable[CT_TelAlarmCondition::ALM_SFBER_HOP]  = AM_SG_BERSF_P_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_PLM_HOP]    = AM_SG_PLM_P_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_TIM_HOP]    = AM_SG_TIM_P_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_UNEQ_HOP]   = AM_SG_UNEQ_P_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_LOP_HOP]    = AM_SG_LOP_P_NSA_UID;

            // Sync alarm on SMTM card should not have a side
            if (isSync() == true) myAmPortType = CT_DIR_DONT_CARE;

            // Dccl alarm on card should not have a side
            if ( (isDccl() == true) )
            {
                myAmPortType = CT_DIR_DONT_CARE;
            }

            break;

        case CARD_FAM_OTNM:
            if (GetCTDirection() == CT_DIRECTION_PORT)
            {
                theirUidTable[CT_TelAlarmCondition::ALM_LOS_OPT] = AM_SG_LOS_OPT_NSA_UID;
                theirUidTable[CT_TelAlarmCondition::ALM_LOF_RS]  = AM_SG_LOF_RS_NSA_UID;
                theirUidTable[CT_TelAlarmCondition::ALM_TIM_RS]  = AM_SG_TIM_RS_NSA_UID;
                theirUidTable[CT_TelAlarmCondition::ALM_BER_ODU] = AM_INVALID_UID;
            }
            else if( (myAppIf.GetKeySuffix() == ALM_LINE_2_SUFFIX) || // working GOPT
                     (myAppIf.GetKeySuffix() == ALM_LINE_3_SUFFIX) )  // protect GOPT
            {
                theirUidTable[CT_TelAlarmCondition::ALM_LOS_OPT] = AM_SG_LOS_OPT_NSA_UID;
                // The alarm ALM_SWTH_OPT on GOPT should be reported as NSA 
                // because it will be processed for alarm escalation in AM_PortDeductionRule::ApplyPortRule1()
                // similar as that in OPSM.
                theirUidTable[CT_TelAlarmCondition::ALM_SWTH_OPT] = AM_SG_SWTHRESH_NSA_UID;
            }

            theirUidTable[CT_TelAlarmCondition::ALM_TAIS_RS] = AM_INVALID_UID;

            if (isSync() == true) myAmPortType = CT_DIR_DONT_CARE;

            break;

        case CARD_FAM_OPSM:
            if (GetCTDirection() == CT_DIRECTION_LINE)
            {
                // The following OPSM card line side OPT alarms must
                // be reported as NSA
                theirUidTable[CT_TelAlarmCondition::ALM_LOS_OPT]  = AM_SG_LOS_OPT_NSA_UID;
                theirUidTable[CT_TelAlarmCondition::ALM_SWTH_OPT] = AM_SG_SWTHRESH_NSA_UID;
            }
            break;

		case CARD_FAM_PACKET_FAB:
            // Sync alarm on SPFAB card should not have a side
            if (isSync() == true) myAmPortType = CT_DIR_DONT_CARE;
			break;

        case CARD_FAM_FGSM:
            theirUidTable[CT_TelAlarmCondition::ALM_LOFLOM_ODU]    = AM_SG_LOFLOM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_MSIM_ODU]      = AM_SG_MSIM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_PLM_ODU]       = AM_SG_PLM_ODU_NSA_UID;
            theirUidTable[CT_TelAlarmCondition::ALM_TIM_ODU]       = AM_SG_TIM_ODU_NSA_UID;

            if (isSync() == true) myAmPortType = CT_DIR_DONT_CARE;
            break;

        default: // nothing special to do
            break;
    }

    // Gcc alarm on card should not have a side
    if ( (isGcc() == true) )
    {
        myAmPortType = CT_DIR_DONT_CARE;
    }
}

/**
 * Default destructor.
 */
ALM_FailureModificationAction::~ALM_FailureModificationAction()
{
}

/**
 * Method overloads the base class, is not supported.
 */
void ALM_FailureModificationAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR( FC_NotSupportedError, "Run not supported" );
}

/**
 * Method overloads the base class and is the primary interface to the
 * Alarm Management package from the Signal Alarm reporter application
 * on the APM. The method is invoked each time a Signal Alarm blackboard
 * region is updated or refreshed on the APM card. It will always call
 * either the ReportDefect() or ClearDefect() method of the AM_DefectCollector
 * class for each failure, depending on the current status of that failure.
 * Although a particular failure may have already been reported to Alarm
 * Management at the time of its status change via the ReportDefect() method
 * interface, subsequent refreshes of the Signal Alarm region will result in
 * the repeat execution of the same method. The Alarm Management package has
 * been designed to determine if the reported failure has already been reported,
 * and will indicate this in the methods return value (AM_ReturnResult).
 */
FC_Object* ALM_FailureModificationAction::DoRunWithReason(unsigned theRunReason, FC_Object* theInvoker, FC_Object* theParam)
{
    //---------------------------------------------------------------------------
    // Determine if this action is running for a T1E1 interface.
    //---------------------------------------------------------------------------
    if ( myT1E1If )
    {
        HandleT1E1FailureAction();
        return NULL; ////////////////////////////////////////////////////////////
    }

    CT_CardFamily aCardFamily = myCardIf->GetCardFamily();
    //---------------------------------------------------------------------------
    // Determine the CardFamily. Additionally, do -NOT- continue
    // if the Card is -NOT- provisioned! AM_DeductionAction.cpp
    // relies on the Slot's ProvCardType being set to properly
    // escalate/deescalate alarms. Otherwise, STUCK alarms occur!
    //---------------------------------------------------------------------------
        if ( aCardFamily.IsSCMember() )
        {
            T6100_ShelfIf* aShelfIf = T6100_MainAppIf::Instance().GetShelfPtr(myCardIf->GetShelfId());
            if ( aShelfIf )
            {
                T6100_SlotIf* aSlotIf = aShelfIf->GetSlotPtr(myCardIf->GetCardId());
                if ( aSlotIf )
                {
                    if ( aSlotIf->GetProvCardType() == UNKNOWN )
                    {
                    return NULL; ////////////////////////////////////////////////
                    }
                }
            }
        }

    //---------------------------------------------------------------------------
    // Call Handle() methods to process the different Telecom Layer Defects.
    // If the Telecom Layer being processed has "special" rules, then call special.
    // Otherwise, call the generic HandleGenericFailureAction() method.
    //---------------------------------------------------------------------------
    if /**/ (isOtsOms())
    {
        HandleOtsOmsFailureAction( aCardFamily );
    }
    else if (isOch())
    {
        HandleOchFailureAction( aCardFamily );
    }
    else if (isOpt())
    {
        HandleOptFailureAction( aCardFamily );
    }
    else if (isRs())
    {
        HandleRsFailureAction( aCardFamily );
    }
    else if (isMs())
    {
        HandleMsFailureAction( aCardFamily );
    }
    else if (isOtu())
    {
        HandleOtuFailureAction( aCardFamily );
    }
    else if (isOdu() || isTcm())
    {
        HandleOduFailureAction( aCardFamily );
    }
    else if (isGfp())
    {
        HandleGfpFailureAction( aCardFamily );
    }
    else if (isHop())
    {
        HandleHopFailureAction( aCardFamily );
    }
    else if (isVcg())
    {
        HandleVcgFailureAction( aCardFamily );
    }
    else if (isSync()) 
    {
        HandleSyncFailureAction( aCardFamily );
    }
    else /////////////////////////////////////////
    {
        HandleGenericFailureAction( aCardFamily );
    }

    //---------------------------------------------------------------------------
    // Call Handle() method to process the Signal Protect Defects.
    //---------------------------------------------------------------------------
    HandleSignalProtectFailureAction();

    return NULL;
}

//================================================================================================
// Handle T1E1 Failure Modification Action. Alarming for the T1 entity on the main shelf.
//================================================================================================
bool ALM_FailureModificationAction::HandleT1E1FailureAction()
{
    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[0];

    for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

        ///////////////////////////////////////////////////////////////////////////
        if ( aUid == AM_INVALID_UID )
            continue;
        ///////////////////////////////////////////////////////////////////////////

            if (aFailureBase.GetStatusFromIndex(aFailureIndex))
            {                      
                aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myT1E1If, anOccurTime);
            }
            else 
            {
                aResult = AM_DefectCollector::GetInstance()->ClearDefect(aUid, myT1E1If);
            }
        }
        
    return true;
    }

//================================================================================================
// -NO- Special case processing -ALLOWED- in generic FailureAction() method!
//================================================================================================
bool ALM_FailureModificationAction::HandleGenericFailureAction(CT_CardFamily aCardFamily)
{
    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0, startChannel = 1; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++, startChannel++)
    {
        //-----------------------------------------------------------------------------
        // Now report/clear the failure for each specific failure defined in the object 
        // (ie: the HOP layer has nine layer failure objects: AIS-P, LOP-P, etc.).
        //-----------------------------------------------------------------------------
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            if ( isStartChannelUsed() ) // GCC, DCC, LAPD, etc.
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType, startChannel);
                }                    
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType, startChannel);
                }
            }
            else
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }
            }
        }        
    }

    return true;
}

//================================================================================================
// As a service to Signal Protection, report/clear any SP alarms should this
// layer support signal Protect defects. NOTE: keep special processing for HOP!
//================================================================================================
bool ALM_FailureModificationAction::HandleSignalProtectFailureAction()
{
    AM_UID          aUid;
    AM_ReturnResult aResult;

    // Keep special processing for HOP!
    int anOffset = myAppIf.GetMonElementOffset();
    CFG_Region* aHOPCfgRegion = NULL;
    if ( isHop() ) 
    {
        ALM_SubApplicationOnRpt* aSubAppRpt = dynamic_cast<ALM_SubApplicationOnRpt*>(&myAppIf);
        if ( aSubAppRpt )
        aHOPCfgRegion = aSubAppRpt->GetCfgAppIf()->GetCfgRegion();
    }

    for (int anObjectIndex = 0, startChannel = 1; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++, startChannel++)
    {
        bool forceClearOfDefect = false;
        //===============================================================================
        // For the HOP entities, we want to avoid unnecessary processing, when possible.
        //===============================================================================
        if ( isHop() && aHOPCfgRegion ) // HANDLE HOP application. 
        {
            CFG_Hop* aHopObj = dynamic_cast<CFG_Hop*>(&(*aHOPCfgRegion)[(bbindex_t)((startChannel + anOffset) - 1)]);
            if ( aHopObj && (aHopObj->GetSpeMapping() == CT_TEL_HOP_MAPPING_UNKNOWN) ) 
            {
                forceClearOfDefect = true; // force the clear on non-Provisioned STS.
            }
        }

        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetSigProtNbOfFailure(); aFailureIndex++)
        {
            aUid = GetUIDFromType(aFailureBase.GetSigProtTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            if ( isStartChannelUsed() ) 
            {
                bool  aOdukAltMapping = false;
                uint8 aOdukAltMap = 0;

                if ( myPortOffset == CT_PORT_SIDE_30 || myPortOffset == CT_PORT_SIDE_31 || myPortOffset == CT_PORT_SIDE_32 ||
                     myPortOffset == CT_PORT_SIDE_33 || myPortOffset == CT_PORT_SIDE_34 || myPortOffset == CT_PORT_SIDE_35 )
                {
                    aOdukAltMapping = true; // ODUK pooled entities have special mapping!
                    aOdukAltMap = CT_ALT_MAP_ODUK_IND;
                }

                if (aFailureBase.GetSigProtStatusFromIndex(aFailureIndex) && !forceClearOfDefect)
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect
                              (aUid, myCardIf, 0, myPortOffset, myAmPortType, (startChannel + anOffset),
                                   AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, aOdukAltMapping, aOdukAltMap);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect
                              (aUid, myCardIf,    myPortOffset, myAmPortType, (startChannel + anOffset),
                                   AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, aOdukAltMapping, aOdukAltMap);
                }
            }
            else
            {
                //------------------------------------------------------------------------------------------
                // YCABLE PROTNA: PROTNA posted against a facility with Y-Cable support must report as TDTC!
                // Use AM_AM_YCABLE_PROTNA defect to allow Agent Alarm Management to switch direction to TDTC.
                //------------------------------------------------------------------------------------------
                if ( aUid == AM_SP_PROTNA_UID )
                {
                    AM_UID aCid = AM_AM_YCABLE_PROTNA_UID; // aCounterPartUid!
                    if ( aFailureBase.GetSigProtYCableFromIndex(aFailureIndex) )
                    {
                        aUid = AM_AM_YCABLE_PROTNA_UID;
                        aCid = AM_SP_PROTNA_UID;
                    }

                    if (aFailureBase.GetSigProtStatusFromIndex(aFailureIndex))
                    {
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, 0, myPortOffset, myAmPortType);
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect (aCid, myCardIf,    myPortOffset, myAmPortType);
                    }
                    else // Clear -both- to be safe!
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf,    myPortOffset, myAmPortType);
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect (aCid, myCardIf,    myPortOffset, myAmPortType);
                    }
                }
                else 
                {
                    if (aFailureBase.GetSigProtStatusFromIndex(aFailureIndex))
                    {                      
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, 0, myPortOffset, myAmPortType);
                    }
                    else 
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect(aUid, myCardIf,     myPortOffset, myAmPortType);
                    }
                }
            }
        }
    }

    return true;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleOtsOmsFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isOtsOms() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //-------------------------------------------------------
            // OTS-LOS is detected on OSC/SPM8250Active. However, the
            // DWDM LOS LED is located on the OLIM/LIAM card. Therefore,
            // we will generate the OTS-LOS LED flag from here!
            //-------------------------------------------------------
            if ( aUid == AM_SG_LOS_OTS_UID )
            {
                T6100_CardIf* aDWDMInpCardIf = NULL;

                if ( CSPII_CardIF::GetInstance()->GetCardType() == SPMNANO ) 
                {
                    if ( CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg() == NANO_SBOADM_CH88_N_S ) // config 24
					{
                        //---------------------------------------------------
                        // Find the CCM/LIAM(OLA)/CADM cardIf - for LED control.
                        //---------------------------------------------------
                        CT_SlotId aDWDMInpSlotId;
                        switch (GetCTSide())
                        {
                            case CT_SIDE_A: aDWDMInpSlotId = CADM_NANO_SSOADM_A; break;
                            case CT_SIDE_B: aDWDMInpSlotId = CADM_NANO_SSOADM_B; break;
                            case CT_SIDE_C: aDWDMInpSlotId = CADM_NANO_SSOADM_C; break;
                            case CT_SIDE_D: aDWDMInpSlotId = CADM_NANO_SSOADM_D; break;
                            case CT_SIDE_E: aDWDMInpSlotId = CADM_NANO_SSOADM_E; break;
                            case CT_SIDE_F: aDWDMInpSlotId = CADM_NANO_SSOADM_F; break;
                            case CT_SIDE_G: aDWDMInpSlotId = CADM_NANO_SSOADM_G; break;
                            case CT_SIDE_H: aDWDMInpSlotId = CADM_NANO_SSOADM_H; break;
                            default: continue; // Unknown side, move on
                        }


                        aDWDMInpCardIf = T6100_MainAppIf::Instance().GetShelfPtr(myCardIf->GetShelfId())->
                                                                     GetSlotPtr(aDWDMInpSlotId)->
                                                                     GetProvCardPtr();
					}
					else
					{
                        //---------------------------------------------------
                        // Find the CCM/LIAM(OLA)/CADM cardIf - for LED control.
                        //---------------------------------------------------
                        CT_SlotId aDWDMInpSlotId = (GetCTSide() == CT_SIDE_A || GetCTSide() == CT_SIDE_C ||
                                                    GetCTSide() == CT_SIDE_E || GetCTSide() == CT_SIDE_G) ? CCM_A : CCM_B;

                        aDWDMInpCardIf = T6100_MainAppIf::Instance().GetShelfPtr(myCardIf->GetShelfId())->
                                                                     GetSlotPtr(aDWDMInpSlotId)->
                                                                     GetProvCardPtr();
					}

                    //---------------------------------------------------
                    // NANO CCM module has OTS LOS, then ATPS PtoL occurs.
                    // This makes OCH PtoL detection points all LOS.
                    // Therefore, we must ignore all CCM portside Failures!
                    //---------------------------------------------------
                    if ( aDWDMInpCardIf && 
                         (aDWDMInpCardIf->GetCardFamily() == CCM_FAM || 
                          aDWDMInpCardIf->GetCardFamily() == CADM_FAM ||
                          (aDWDMInpCardIf->GetCardFamily() == LIAM_FAM && CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg().IsNeAmpFoadm())) )
                    {
                        if ( aFailureBase.GetStatusFromIndex(aFailureIndex) )
                        {                      
                            aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_BLOCK_PORTSIDE_FAILURES, aDWDMInpCardIf);
                        }
                        else 
                        {
                            aResult = AM_DefectCollector::GetInstance()->ClearDefect (AM_BLOCK_PORTSIDE_FAILURES, aDWDMInpCardIf);
                        }
                    }
                }
                else
                {
                    bool isCADMSlotId = (CSPII_SysCfgParamIF::GetInstance()->GetSubNodeCfg()==SBOADM_CH88_4D_HCSS) ? true : false;

                    CT_SlotId aDWDMInpSlotId = UNKNOWN_SLOT_ID;

                    if ( (GetCTSide() == CT_SIDE_A ) || (GetCTSide() == CT_SIDE_E) )
                        aDWDMInpSlotId = (isCADMSlotId) ? CADM_FP3_A : LIAM_1;
                    else if ( ( GetCTSide() == CT_SIDE_B ) || (GetCTSide() == CT_SIDE_F) )
                        aDWDMInpSlotId = (isCADMSlotId) ? CADM_FP3_B : LIAM_19;
                    else if ( ( GetCTSide() == CT_SIDE_C ) || (GetCTSide() == CT_SIDE_G) )
                        aDWDMInpSlotId = (isCADMSlotId) ? CADM_FP3_C : LIAM_5;
                    else if ( ( GetCTSide() == CT_SIDE_D ) || (GetCTSide() == CT_SIDE_H) )
                        aDWDMInpSlotId = (isCADMSlotId) ? CADM_FP3_D : LIAM_13;

                    aDWDMInpCardIf = T6100_MainAppIf::Instance().GetShelfPtr(myCardIf->GetShelfId())->
                                                                 GetSlotPtr(aDWDMInpSlotId)->
                                                                 GetProvCardPtr();
                }

                /////////////////////////////////////////////////////////////////////////////////////////////////////////
                if ( aDWDMInpCardIf ) 
                {
                    if ( aFailureBase.GetStatusFromIndex(aFailureIndex) )
                    {                      
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_ITS_LED, aDWDMInpCardIf, anOccurTime, 0, CT_DIR_CARD_LINE);
                    }
                    else 
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect (AM_ITS_LED, aDWDMInpCardIf,              0, CT_DIR_CARD_LINE);
                    }
                }
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect
                              (aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect
                              (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }
            }
        }
    }

    return NULL;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleOchFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isOch() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            if (aFailureBase.GetStatusFromIndex(aFailureIndex))
            {                      
                aResult = AM_DefectCollector::GetInstance()->ReportDefect
                          (aUid, myCardIf, anOccurTime, myPortOffset+anObjectIndex, myAmPortType);
            }
            else 
            {
                aResult = AM_DefectCollector::GetInstance()->ClearDefect
                          (aUid, myCardIf, /* noTime */ myPortOffset+anObjectIndex, myAmPortType);
            }
        }
    }

    return NULL;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleOptFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isOpt() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //---------------------------------------------------------------------------------------------
            // t71mr000 22721 - OPSM to MRTM xcon must INHibit CABL-LOS when OPSM PRT side LOS exists.
            // Because the OPSM has 4 PRT side ports (0-3) and the LINE side ports (0-7), we must add
            // some INTERNAL alarms such that AM_6100Registry rules can be applied properly.
            //         Port side 0 will be mapped to Line side 0,1. 
            //         Port side 1 will be mapped to Line side 2,3. 
            //         Port side 2 will be mapped to Line side 4,5. 
            //         Port side 3 will be mapped to Line side 6,7. 
            //---------------------------------------------------------------------------------------------
            if ( (aCardFamily == OPSM_FAM) && (aUid == AM_SG_LOS_OPT_UID) && (myAmPortType == CT_DIR_WAVE_PORT) )
            {
                uint8 port = myPortOffset * 2;

                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LOS_OPT_OPSM_PRT_UID, myCardIf, anOccurTime, port,   CT_DIR_WAVE_PORT);
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LOS_OPT_OPSM_PRT_UID, myCardIf, anOccurTime, port+1, CT_DIR_WAVE_PORT);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LOS_OPT_OPSM_PRT_UID, myCardIf, port,   CT_DIR_WAVE_PORT);
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LOS_OPT_OPSM_PRT_UID, myCardIf, port+1, CT_DIR_WAVE_PORT);
                }
            }

            //-------------------------------------------------------------------------------------------------------
            // SMTMU and OTNM must block -portside- GFP failures when the OCH-P experiences a LOS OPT!
            //-------------------------------------------------------------------------------------------------------
            if ( ((aCardFamily == SMTM_FAM) && 
                  (aUid == AM_SG_LOS_OPT_NSA_UID) && 
                  (myAmPortType == CT_DIR_WAVE_LINE)) ||

                 ((aCardFamily == OTNM_FAM) &&        // OTNM -must- check LINE_1 because of GOPT-W/P -and-
                  (aUid == AM_SG_LOS_OPT_UID) &&      //      -must- check for LOS_OPT (SA) as well! 
                  (myAppIf.GetKeySuffix() == ALM_LINE_1_SUFFIX)) )
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_INHIBIT_GFP_FAILURES_LOS_LINE1, myCardIf);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (AM_INHIBIT_GFP_FAILURES_LOS_LINE1, myCardIf);
                }
            }

            // FGE/HGE of HGTMMS
            CT_CardType aCardType = CSPII_CardIF::GetInstance()->GetCardType();
            if((aCardType == HGTMMS) && (aUid == AM_SG_LOS_OPT_UID))
            {
                if(NOT_GROUP != GetHgtmmsFgeHgePortGroupType((CT_IntfId)myPortOffset)) // Is FGE/HGE of HGTMMS
                {
                    // process LED behavior for whole group
                    if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                    {
                        SetFgeHgeLedGroupLos(true, anOccurTime);
                    }
                    else if (!IsFgeHgeGroupHasLos())
                    {
                        SetFgeHgeLedGroupLos(false);
                    }
                    // report AM_SG_GROUP_REP_LOS_UID against representative port, it will be deducted as LOS_OPT at controller
                    if((myPortOffset != CT_PORT_SIDE_2) && (myPortOffset != CT_PORT_SIDE_6))
                    {
                        if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                        {
                            AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_GROUP_REP_LOS_UID, myCardIf, anOccurTime, (bbindex_t)GetFgeHgeGroupRepresentPort(), myAmPortType);
                        }
                        else if (!IsFgeHgeGroupHasLos())
                        {
                            AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_GROUP_REP_LOS_UID, myCardIf, (bbindex_t)GetFgeHgeGroupRepresentPort(), myAmPortType);
                        }
                    }
                }
                
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID) 
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }
            }
        }   
    }

    return true;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleRsFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isRs() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //---------------------------------------------------------------------------------------------
            // Special processing needed for UIDs that must switch the DEFECT PortType direction (side: PORT/LINE).
            //---------------------------------------------------------------------------------------------
            if ( aUid == AM_SG_AISTX_RS_UID ||
                 aUid == AM_SG_LOF_INT_RS_UID ||
                 aUid == AM_SG_CSF_OPU_UID ||
                 aUid == AM_SG_GENAIS_INT_RS_UID)
            {
                AM_PortType fakeAmPortType = (myAmPortType == CT_DIR_WAVE_LINE) ? CT_DIR_WAVE_PORT : 
                                             (myAmPortType == CT_DIR_WAVE_PORT) ? CT_DIR_WAVE_LINE : myAmPortType;

                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, fakeAmPortType);
                    
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, fakeAmPortType);
                }

                //---------------------------------------------------------------------------------------------
                // FGTME should inhibit AIS_L_INT (TDTC portSide Facilities) when CSF-OPU is detected.
                //---------------------------------------------------------------------------------------------
                if ( (aCardFamily == ENH_TRN_FAM ) && (aUid == AM_SG_CSF_OPU_UID))
                {
                    if ((aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OC768) || 
                    	    (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_STM256) )
                    {
                        if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                        {                      
                            aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_INH_TDTC_FAILURE_UID, myCardIf);
                        }
                        else 
                        {
                            aResult = AM_DefectCollector::GetInstance()->ClearDefect (AM_INH_TDTC_FAILURE_UID, myCardIf);
                        }
                    }
                }

                if ((aCardFamily == HGTMM_FAM || aCardFamily == OSM_FAM) && (aUid == AM_SG_CSF_OPU_UID))
                {
                    if (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN ||
                    	    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN_FRAME ||
                    	    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN_PREAMBLE ||
                    	    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN_FRAME_STD ||
                    	    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OC192 ||
                    	    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_STM64 ||
                    	    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_HGE_GFP ||
                    	    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_HGE)
                    {
                        if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                        {                      
                            aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_INH_TDTC_FAILURE_UID, myCardIf,  anOccurTime, myPortOffset, fakeAmPortType);
                        }
                        else 
                        {
                            aResult = AM_DefectCollector::GetInstance()->ClearDefect (AM_INH_TDTC_FAILURE_UID, myCardIf, myPortOffset, fakeAmPortType);
                        }
                    }
                }
                
                aUid = AM_INVALID_UID; // report already done
            }

            //-------------------------------------------------------
            // Special case code. The TSPII on the SMTM re-uses the LOF-RS
            // to indicate LOSYNC when the interface is configured as GbE.
            // But the indication going to AM must be LOF-RS for SONET
            // interfaces, and LOSYNC for GbE interfaces. So based on the
            // interface (port) current configuration, the correct alarm
            // type is returned. NOTE: TGLAN on TGTMT follows this logic.
            //-------------------------------------------------------
            if ( aUid == AM_SG_LOF_RS_UID ||    // TRN
                 aUid == AM_SG_LOF_RS_NSA_UID ) // SMTM
            {
                AM_UID theCounterUid = AM_SG_LOSYNC_UID;

                switch (aUid) 
                {
                    case AM_SG_LOF_RS_UID:      theCounterUid = AM_SG_LOSYNC_UID;         break;
                    case AM_SG_LOF_RS_NSA_UID:  theCounterUid = AM_SG_LOSYNC_NSA_UID;     break;
                }

                if (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_GBEP        ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_ETH         ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FGE         ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_HGE         ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_HGE_GFP||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGBEP       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGFC        ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_100BFX      ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FC133M      ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_ESCON       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FC266M      ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_HDSDI30     ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_HDSDI       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_3GSDI30     ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_3GSDI       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_DVBASI      ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_SDI         ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_D1VIDEO     ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FC531M      ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FC1G        ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FICON       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_ISC         ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FC2G        ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FICON2G     ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_ISC2G       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FC4G        ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_FC8G        ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_IBSDR       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_IBDDR       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN_FRAME ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN_FRAME_STD ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN_WFS       ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OTU_TGLAN_WFS   ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OTU_TGLAN_WOFS  ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGLAN_PREAMBLE  ||
                    aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGFC_BMP ||
                   (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_GOPT &&  
                    (aCardFamily == OTNM_FAM || aCardFamily == SSM40_FAM || aCardFamily == OMM_FAM || aCardFamily == OSM_FAM ))) //ONLY if we are a GOPT on an OTNM, OSM20, OMMX or OSM2 (OSM40 doesn't support GOPT)
                {
                    theCounterUid = aUid; // counterpart now is non-GBEP facility

                    switch (theCounterUid) 
                    {
                        case AM_SG_LOF_RS_UID:      aUid = AM_SG_LOSYNC_UID;         break;
                        case AM_SG_LOF_RS_NSA_UID:  aUid = AM_SG_LOSYNC_NSA_UID;     break;
                    }
                }

                //------------------------------------------------------------
                // Because the user could delete non-GBEP facility and create
                // GBEP facility while the LOF/LOSYNC condition remains (TSPII)
                // we will always clear the counter part UID here!!!
                //------------------------------------------------------------
                if ( aFailureBase.GetStatusFromIndex(aFailureIndex) && 
                     aFailureBase.GetSignalType() != CT_TEL_SIGNAL_UNKNOWN ) // don't alarm if unknown!
                {
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (theCounterUid, myCardIf,     myPortOffset, myAmPortType);
                }
                //-------------------------------------------------------------
                // Because the user could delete any facility and a LOF/LOSYNC
                // might have been reported to the user - we will not clear
                // here because a RACE CONDITION exists between TL1 and clear
                // in which the alarm does NOT clear on deleted facility (EMS).
                // Therefore, we will leave current state of alarm if UNKNOWN
                // and this will allow the TL1_AlarmObserver to clear alarm (39818).
                //-------------------------------------------------------------
                else if (aFailureBase.GetSignalType() != CT_TEL_SIGNAL_UNKNOWN) // don't clear if unknown!
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf,              myPortOffset, myAmPortType);
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (theCounterUid, myCardIf,     myPortOffset, myAmPortType);
                }

                aUid = AM_INVALID_UID; // report already done
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }
            }
        }
        
    }

    return true;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleMsFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isMs() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //---------------------------------------------------------------------------------------------
            // Special processing needed for UIDs that must switch the DEFECT PortType direction (side: PORT/LINE).
            //---------------------------------------------------------------------------------------------
            if ( aUid == AM_SG_AIS_L_INT_UID ) // SMTMx w/ AIS Internal on Port Facility!
            {
                AM_PortType fakeAmPortType = (myAmPortType == CT_DIR_WAVE_LINE) ? CT_DIR_WAVE_PORT : 
                                             (myAmPortType == CT_DIR_WAVE_PORT) ? CT_DIR_WAVE_LINE : myAmPortType;

                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, fakeAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, fakeAmPortType);
                }
            
                aUid = AM_INVALID_UID; // report already done
            }

            //---------------------------------------------------------------------------------------------
            // Transponder Modules can detected AIS-L (MS layer) on the LINE side (TDTC).
            // However, we want to alarm the AIS-L (TDTC) on the port side facility.
            // Only OC3/12/48/192, STM1/4/16/64 and TGBEP port side facilities should declare AIS-L.
            // NOTE: we will block AIS-L when detected on the PORT side (TDTN) and invalid SignalType.
            //---------------------------------------------------------------------------------------------
            if ( ((aCardFamily == TRN_FAM) || (aCardFamily == ENH_TRN_FAM)) && (aUid == AM_SG_AIS_L_UID) )
            {
                bool validSignalTypeAISL = false;

                if ( (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OC3)   ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OC12)  ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OC48)  ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OC192) ||
					 (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_OC768) ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_STM1)  ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_STM4)  ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_STM16) ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_STM64) ||
					 (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_STM256) ||
                     (aFailureBase.GetSignalType() == CT_TEL_SIGNAL_TGBEP) )
                {
                    validSignalTypeAISL = true;
                }
                
                if ( validSignalTypeAISL && aFailureBase.GetStatusFromIndex(aFailureIndex) )
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }

                aUid = AM_INVALID_UID; // report already done
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }
            }
        }
    }

    return true;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleOtuFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isOtu() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //---------------------------------------------------------------------------------------------
            // MR 83903...OTNM should inhibit AIS_L_INT (TDTC portSide Facilities) when TIM-OTU is detected.
            //---------------------------------------------------------------------------------------------
            if ( (aCardFamily == OTNM_FAM) && (aUid == AM_SG_TIM_OTU_UID) )
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_INH_TDTC_FAILURE_UID, myCardIf);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (AM_INH_TDTC_FAILURE_UID, myCardIf);
                }
            }

            //-------------------------------------------------------
            // (MR75416)...handle lower OTU layer vs. LOC_OPT.
            //-------------------------------------------------------
            if ( (aUid == AM_SG_LOF_OTU_NSA_UID || aUid == AM_SG_LOF_OTU_UID) && 
                 (((aCardFamily == TRN_FAM    || 
                    aCardFamily == SMTM_FAM   || 
                    aCardFamily == PACKET_FAM ||
                    aCardFamily == SSM_FAM    || 
                    aCardFamily == OTNM_FAM   || 
                    aCardFamily == FGTMM_FAM) &&
                   (myAppIf.GetKeySuffix() == ALM_LINE_1_SUFFIX)) ||
                  ((aCardFamily == HDTG_FAM       || 
                    aCardFamily == ENH_PACKET_FAM || 
                    aCardFamily == ENH_TRN_FAM || 
                    aCardFamily == SSM40_FAM ||
                    aCardFamily == OMM_FAM ||
                    aCardFamily == SSM40_FAM ||
                    aCardFamily == HGTMM_FAM ||
                    aCardFamily == OSM_FAM ||
                    aCardFamily == HDTG2_FAM))) )
            {
                if ( aFailureBase.GetStatusFromIndex(aFailureIndex) )
                {
                    myLOFLOCAlmExists = true;
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else if ( myLOFLOCAlmExists ) // Do NOT clear lower layer LOF_OTU incorrectly here!
                {
                    myLOFLOCAlmExists = false;

                    ALM_SubApplicationOnRpt* aALMOptApp = NULL;
                    if ( myAppIf.GetKeySuffix() == ALM_LINE_1_SUFFIX )
                    {
                        aALMOptApp = dynamic_cast<ALM_SubApplicationOnRpt*>
                                     (myCardIf->GetOptIf().GetAlmLineSideAppPtr(CT_LINE_SIDE_1));
                    }
                    else
                    {
                        aALMOptApp = dynamic_cast<ALM_SubApplicationOnRpt*>
                                     (myCardIf->GetOptIf().GetAlmPortSideAppPtr((CT_IntfId)myPortOffset));
                    }

                    if ( aALMOptApp && !(aALMOptApp->GetFMActionPtr()->isLOFLOCAlmExists()) )
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect(aUid, myCardIf, myPortOffset, myAmPortType);
                    }
                }

                aUid = AM_INVALID_UID; // report already done
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }
            }
        }        
    }

    return true;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleSyncFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isSync() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //---------------------------------------------------------------------------------------------
            // MR 170198: when the OTNM is set to INT (internal) timing mode, the FRNGSYNC alarms shall be suppressed
            //---------------------------------------------------------------------------------------------
            if ( (aCardFamily == OTNM_FAM) && 
                 ((aUid == AM_FRNGSYNC_UID) || (aUid == AM_HLDOVRSYNC_UID)) )
            {
                bool allowDefect = false;
                CFG_SyncSubApplication& theSyncApp = static_cast<CFG_SyncSubApplication&> (myCardIf->GetSyncIf().GetCfgCardApp());
                CFG_Region* theSyncRegion = theSyncApp.GetCfgRegion();

                if ( theSyncRegion && theSyncRegion->IsValid() ) 
                {
                    CFG_Sync& aCfgObject = static_cast<CFG_Sync&>((*theSyncRegion)[0]);
                    if ( aCfgObject.GetTimingMode() != CT_TEL_SELF_TIMING )
                    {
                        allowDefect = true; 
                    }
                }

                if (allowDefect && aFailureBase.GetStatusFromIndex(aFailureIndex))
                {
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }                    
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }

                aUid = AM_INVALID_UID;
            }

            //---------------------------------------------------------------------------------------------
            // MR 190014: when the system is NOT set up for TIMING, the HLDOVER/FRNGSYNC alarms shall be suppressed
            //---------------------------------------------------------------------------------------------
            if ( (aCardFamily == OSC_FAM) && 
                 (CSPII_CardIF::GetInstance()->GetCardType() == SPMNANO ||
                  CSPII_CardIF::GetInstance()->GetCardType() == SPM8547) &&
                 ((aUid == AM_FRNGSYNC_UID) || (aUid == AM_HLDOVRSYNC_UID)) )
            {
                bool allowDefect = false;

                if ( CSPII_CardIF::GetInstance()->GetCardType() == SPMNANO )
                {
                SP_ProtectionGroupConfigRegionImp<SP_1plus1ProtectionGroupConfig>& aConfigProtReg = 
                  myCardIf->GetSyncProtectionIf().GetSyncProtectionApp().GetConfigRegion();

                if ( aConfigProtReg.IsValid() ) 
                {
                    if ( aConfigProtReg[0].GetState() != CT_SP_DEFAULT_CONFIG_STATE )
                    {
                        allowDefect = true; 
                    }
                }
                }
                else if ( CSPII_CardIF::GetInstance()->GetCardType() == SPM8547 )
                {
                    if ( T6100_MainAppIf::Instance().GetSCFGApp().GetParamRegion()[0].GetSyncOsc() == CT_SyncOsc_SOURCE )
                    {
                        allowDefect = true; 
                    }
                }

                if (allowDefect && aFailureBase.GetStatusFromIndex(aFailureIndex))
                {
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }                    
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }

                aUid = AM_INVALID_UID;
            }

            //---------------------------------------------------------------------------------------------
            // MR 225989: the HLDOVRSYNC alarm that was never in the OSM20 requirements should be removed from the software at the same time.
            //---------------------------------------------------------------------------------------------
            if ( CSPII_CardIF::GetInstance()->GetCardType() == OSM20  && aUid == AM_HLDOVRSYNC_UID )
            {
                aUid = AM_INVALID_UID;
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                }
            }
        }        
    }

    return true;
}

//================================================================================================
// NOTE: startChannel is -CONDITIONALLY- used for ODU (e.g. Pooled vs. ODUs on TRN facility).
//================================================================================================
bool ALM_FailureModificationAction::HandleOduFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isOdu() && !isTcm() ) return true;
    ////////////////////////////////////////////////////////
    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0, startChannel = 1; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++, startChannel++)
    {
        if (isTcm())
        {
            CFG_TcmCfgRegion* aConfigRegion = static_cast<CFG_TcmCfgRegion*>(myCardIf->GetTcmIf().GetCfgPortSideApp(CT_PORT_SIDE_40).GetCfgRegion());
            if (anObjectIndex < aConfigRegion->Size())    
            {
                CFG_Tcm& aCfgObject = static_cast<CFG_Tcm&>((*aConfigRegion)[anObjectIndex]); 
                CT_ODU_Identifier aOduId = aCfgObject.GetTcmIdentifier();
                myPortOffset = 40;
            }
        }
        
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];
        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //----------------------------------------------------------------------------------------
            // FGTME report ODU on OTU
            //----------------------------------------------------------------------------------------
            if ( CSPII_CardIF::GetInstance()->GetCardType() == FGTME)
            {
                bbindex_t aOtuPort  = anObjectIndex;

                if( (aOtuPort == CT_PORT_SIDE_0) || (aOtuPort == CT_PORT_SIDE_1) )
                {
                    if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                    {                      
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, 0/*time*/,
                                                                                  aOtuPort, myAmPortType);
                    }
                    else 
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf,
                                                                                  aOtuPort, myAmPortType);
                    }
                }
                aUid = AM_INVALID_UID;
            }

            if ( (aCardFamily == FGTMM_FAM) && 
                 (myAppIf.GetKeySuffix() == ALM_LINE_8_SUFFIX ||
                  myAppIf.GetKeySuffix() == ALM_LINE_9_SUFFIX || 
                  myAppIf.GetKeySuffix() == ALM_LINE_10_SUFFIX || 
                  myAppIf.GetKeySuffix() == ALM_LINE_11_SUFFIX) &&
                 (aUid == AM_SG_AIS_ODU_UID ||
                  aUid == AM_SG_LCK_ODU_UID ||
                  aUid == AM_SG_OCI_ODU_UID) ) 
            {
                bbindex_t aPortSideXCONPort /* default to LINE_8 PORT_0 mapping */   = CT_PORT_SIDE_0;
                if ( myAppIf.GetKeySuffix() == ALM_LINE_9_SUFFIX ) aPortSideXCONPort = CT_PORT_SIDE_1;
                if ( myAppIf.GetKeySuffix() == ALM_LINE_10_SUFFIX) aPortSideXCONPort = CT_PORT_SIDE_2;
                if ( myAppIf.GetKeySuffix() == ALM_LINE_11_SUFFIX) aPortSideXCONPort = CT_PORT_SIDE_3;

                AM_UID aTempUid = AM_ODU2_MIDLINE_FAIL_AIS;
                if ( aUid == AM_SG_LCK_ODU_UID ) aTempUid = AM_ODU2_MIDLINE_FAIL_LCK;
                if ( aUid == AM_SG_OCI_ODU_UID ) aTempUid = AM_ODU2_MIDLINE_FAIL_OCI;

                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aTempUid, myCardIf, 0/*time*/,
                                                                              aPortSideXCONPort, myAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aTempUid, myCardIf,
                                                                              aPortSideXCONPort, myAmPortType);
                }
            }

            //-------------------------------------------------------
            // FGTMM ODU2 LINE side failures (8,9,10,11) must set 
            // the StartChannel field, so the Agent can map to 
            // single ODUK_LINE region (8-1, 9-2, 10-3, 11-4).
            // NOTE: this block -MUST- be the last block for FGTMM!
            //-------------------------------------------------------
            if ( (aCardFamily == FGTMM_FAM) && (myAmPortType == CT_DIR_WAVE_LINE) )
            {
                uint32 mapIndex = 0;

                if ( (strncmp(myAppIf.GetInstanceName(), "ODU",  3) == 0 ) )
                {
                    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_8_SUFFIX  )
                        mapIndex = 1;
                    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_9_SUFFIX  )
                        mapIndex = 2;
                    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_10_SUFFIX )
                        mapIndex = 3;
                    if ( myAppIf.GetKeySuffix() ==  ALM_LINE_11_SUFFIX )
                        mapIndex = 4;
                }

                if ( mapIndex )
                {
                    if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                    {
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect
                                  (aUid, myCardIf, anOccurTime, myPortOffset, CT_DIR_RCV, mapIndex);
                    }
                    else 
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect
                                  (aUid, myCardIf, /* noTime */ myPortOffset, CT_DIR_RCV, mapIndex);
                    }

                    aUid = AM_INVALID_UID; // report already done ///////////////////////////////////
                }
            }

            //----------------------------------------------------------------------------------------
            // HGTM PLM-ODU reports -only- if HGE is provisioned (terminated ODU)
            //----------------------------------------------------------------------------------------
            if ( (CSPII_CardIF::GetInstance()->GetCardType() == HGTM ||
                  CSPII_CardIF::GetInstance()->GetCardType() == HGTMS) && (aUid == AM_SG_PLM_ODU_UID) ) // Coriant HGTMS
            {
                bool allowDefect = false;
                CT_IntfId portSide = CT_PORT_SIDE_0;

                if(CSPII_CardIF::GetInstance()->GetCardType() == HGTMS)
                {
                    portSide = CT_Map_PortId::GetHgtmsClientPortSide();
                }
                
                CFG_AppIf* aConfigAppIf = myCardIf->GetRsIf().GetCfgPortSideAppPtr(portSide);

                if ( aConfigAppIf && aConfigAppIf->GetCfgRegion() && aConfigAppIf->GetCfgRegion()->IsValid() )
                {
                    CFG_Rs& aCfgObject = static_cast<CFG_Rs&>((*aConfigAppIf->GetCfgRegion())[0]);
                    if ( aCfgObject.GetSignalType() == CT_TEL_SIGNAL_HGE  || aCfgObject.GetSignalType() == CT_TEL_SIGNAL_HGE_GFP)
                    {
                        allowDefect = true; //////////////////////////////
                    }
                }

                if (allowDefect && aFailureBase.GetStatusFromIndex(aFailureIndex))
                {
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect
                                  (aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType, startChannel,
                                    AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, true, CT_ALT_MAP_ODUK_IND);
                }                    
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect
                                  (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType, startChannel,
                                    AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, true, CT_ALT_MAP_ODUK_IND);
                }

                aUid = AM_INVALID_UID;
            }

            //----------------------------------------------------------------------------------------
            // suppress ODU-LCK -only- if a non-terminated ODU0 or ODUF is in the OOS state 
            //----------------------------------------------------------------------------------------
            if ( ( CSPII_CardIF::GetInstance()->GetCardType() == OSM20 || 
                   CSPII_CardIF::GetInstance()->GetCardType() == OMMX  || 
                   CSPII_CardIF::GetInstance()->GetCardType() == OSM2S || 
                   CSPII_CardIF::GetInstance()->GetCardType() == OSM2C ||
                   CSPII_CardIF::GetInstance()->GetCardType() == OSM1S) 
                 && myPortOffset == CT_PORT_SIDE_30
                 && aUid == AM_SG_LCK_ODU_UID )
            {
                MON_AppIf* aMonOduAppPtr = NULL;
                MON_OduDefects* aMonOduObj = NULL;
                ALM_TCount aCountOduLck = 0;
                bool       aDefectOduLck = false;
                ALM_TCount aCountUpperOduLck = 0;
                bool       aDefectUpperOduLck = false;
                bool       inhibit_defect = false;

                aMonOduAppPtr = myCardIf->GetOduIf().GetMonPortSideAppPtr((CT_IntfId) myPortOffset );

                if ( aMonOduAppPtr ) 
                {
                    MON_Region* aMonOduBcReg = aMonOduAppPtr->GetDefectsRegion();
                    if ( aMonOduBcReg )
                    {
                        aMonOduObj = dynamic_cast<MON_OduDefects*>(&((*aMonOduBcReg)[(bbindex_t) startChannel - 1 ]));
                    }
                }

                if ( aMonOduObj && (aMonOduObj->GetIsOduNonTerm() == true) )
                {
                    aMonOduObj->GetDefectStatus(CT_TEL_ODU_LOCK, &aCountOduLck, &aDefectOduLck);
                    aMonOduObj->GetDefectStatus(CT_TEL_ODU_UPPER_LAYER_LOCK, &aCountUpperOduLck, &aDefectUpperOduLck);
                    if ( aDefectOduLck && !aDefectUpperOduLck ) 
                    {
                        inhibit_defect = true;
                    }
                }

                if ( aFailureBase.GetStatusFromIndex(aFailureIndex) )
                {
                    if ( inhibit_defect == true )
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect(aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType, startChannel,
                                                                                 AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, true, CT_ALT_MAP_ODUK_IND);
                    } 
                    else
                    {
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType, startChannel,
                                                                                  AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, true, CT_ALT_MAP_ODUK_IND);
                    }
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect(aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType, startChannel,
                                                                             AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, true, CT_ALT_MAP_ODUK_IND);
                }
                
                aUid = AM_INVALID_UID;
                    
            }

            if (CSPII_CardIF::GetInstance()->GetCardType() == HDTG2)
            {
                bool isSignalFC8G = false;
                bool isSignalOTN = false;
                if (anObjectIndex % 2 == 0) // current index is line side
                {
                    // Get the signal type from client side
                    CFG_AppIf*   aRsConfigAppIf = myCardIf->GetRsIf().GetCfgPortSideAppPtr((CT_IntfId)(anObjectIndex + 1));
                    if (aRsConfigAppIf)
                    {
                        CFG_Region* aRsConfigRegion = aRsConfigAppIf->GetCfgRegion();
                        if (aRsConfigRegion && aRsConfigRegion->IsValid())
                        {
                            CFG_Rs& aCfgObject = static_cast<CFG_Rs&>((*aRsConfigRegion)[0]);
                            CT_TEL_SignalType aSignalType = aCfgObject.GetSignalType();
                            isSignalFC8G = (aSignalType == CT_TEL_SIGNAL_FC8G ? true : false);
                            isSignalOTN = (aSignalType == CT_TEL_SIGNAL_OTU2 || aSignalType == CT_TEL_SIGNAL_OTU_TGLAN_WFS ? true : false);
                        }
                    }
                }
                
                if ((isSignalFC8G && myPortOffset == CT_PORT_SIDE_30)
                    || (!isSignalFC8G && !isSignalOTN && myPortOffset == CT_PORT_SIDE_32))
                {
                    MON_AppIf* aMonOduAppPtr = myCardIf->GetOduIf().GetMonPortSideAppPtr((CT_IntfId) myPortOffset);
                    MON_OduDefects* aMonOdudefect = NULL;
                    MON_OduConfigRegion* MonRegion 
                        = static_cast<MON_OduConfigRegion*>(myCardIf->GetOduIf().GetMonPortSideApp((CT_IntfId) myPortOffset).GetConfigRegion());
                    if (MonRegion)
                    {
                        if (aMonOduAppPtr)
                        {
                            MON_Region* aMonOduReg = aMonOduAppPtr->GetDefectsRegion();
                            if (aMonOduReg)
                            {
                                aMonOdudefect = dynamic_cast<MON_OduDefects*>(&((*aMonOduReg)[(bbindex_t) (anObjectIndex)]));
                                ALM_TCount aCountTim = 0;
                                bool       aDefectTim = false;
                                if (aMonOdudefect)
                                {
                                    aMonOdudefect->GetDefectStatus(CT_TEL_ODU_TIM_DEFECT, &aCountTim, &aDefectTim);
                                }
                                
                                MON_OduConfig& aMonOduCfgObj = (*MonRegion)[(bbindex_t) startChannel - 1];
                                if ((aMonOduCfgObj.GetLayerFailOnTIM() == true)
                                    && (aMonOduCfgObj.GetTIMMonitoringEnable() == true)
                                    && ((startChannel - 1) % 2 == 0)
                                    && aDefectTim) 
                                {
                                    if (aUid == AM_SG_TIM_ODU_UID || aUid == AM_SG_TIM_ODU_NOAIS_UID)
                                    {
                                        aUid = AM_SG_TIM_ODU_UID;
                                    }
                                    
                                    AM_DefectCollector::GetInstance()->ReportDefect
                                        (AM_TIM_ODU_INHABIT_FAILURE_UID, myCardIf, 0, myPortOffset, CT_DIR_WAVE_PORT, startChannel);
                                }
                                else
                                {
                                    AM_DefectCollector::GetInstance()->ClearDefect 
                                        (AM_TIM_ODU_INHABIT_FAILURE_UID, myCardIf, myPortOffset, CT_DIR_WAVE_PORT, startChannel);
                                    if (aDefectTim && ((startChannel - 1) % 2 == 0) && (aMonOduCfgObj.GetTIMMonitoringEnable() == true))
                                    {
                                        if (aUid == AM_SG_TIM_ODU_UID || aUid == AM_SG_TIM_ODU_NOAIS_UID)
                                        {
                                            aResult = AM_DefectCollector::GetInstance()->ClearDefect
                                                    (AM_SG_TIM_ODU_UID, myCardIf, /* noTime */ myPortOffset, myAmPortType, startChannel,
                                                    AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, true, CT_ALT_MAP_ODUK_IND);
                                            
                                            aUid = AM_SG_TIM_ODU_NOAIS_UID;
                                        }
                                    }
                                }

                                
                            }
                        }
                    }

                    
                    if ( aMonOduAppPtr ) 
                    {
                        MON_Region* aMonOduReg = aMonOduAppPtr->GetDefectsRegion();
                        if (aMonOduReg && anObjectIndex % 2 == 0)
                        {
                            aMonOdudefect = dynamic_cast<MON_OduDefects*>(&((*aMonOduReg)[(bbindex_t) (anObjectIndex + 1)]));
                            if (aMonOdudefect && aUid == AM_SG_PLM_ODU_UID)
                            {
                                if (aMonOdudefect->IsFilterPlmDefect())
                                {
                                    AM_DefectCollector::GetInstance()->ReportDefect
                                                (AM_INH_PLM_FAILURE_UID, myCardIf, 0, myPortOffset, CT_DIR_WAVE_PORT, startChannel);
                                }
                                else
                                {
                                    AM_DefectCollector::GetInstance()->ClearDefect 
                                                (AM_INH_PLM_FAILURE_UID, myCardIf, myPortOffset, CT_DIR_WAVE_PORT, startChannel);
                                }
                            }
                        }
                    }
                }
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if ( isStartChannelUsed() ) 
                {
                    bool  aOdukAltMapping = false;
                    uint8 aOdukAltMap = 0;

                    if ( myPortOffset == CT_PORT_SIDE_30 || myPortOffset == CT_PORT_SIDE_31 || myPortOffset == CT_PORT_SIDE_32 ||
                         myPortOffset == CT_PORT_SIDE_33 || myPortOffset == CT_PORT_SIDE_34 || myPortOffset == CT_PORT_SIDE_35 )
                    {
                        aOdukAltMapping = true; // ODUK pooled entities have special mapping!
                        aOdukAltMap = CT_ALT_MAP_ODUK_IND;
                    }

                    if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                    {
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect
                                  (aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType, startChannel,
                                   AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, aOdukAltMapping, aOdukAltMap);
                    }                    
                    else 
                    {
                        if (CSPII_CardIF::GetInstance()->GetCardType() == HDTG2 
                            && (aFailureIndex == ALM_OduFailureBase::TIM_NSA_ODU || aFailureIndex == ALM_OduFailureBase::TIM_ODU)
                            && aFailureBase.GetStatusFromIndex(ALM_OduFailureBase::TIM_NSA_ODU))
                        {
                            // do nothing
                        }
                        else
                        {
                            aResult = AM_DefectCollector::GetInstance()->ClearDefect
                                      (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType, startChannel,
                                       AM_UNKNOWN_INDEX, CT_DIR_DONT_CARE, 0, aOdukAltMapping, aOdukAltMap);
                        }
                    }
                }
                else // no startChannel (e.g. ODU on TRN).
                {
                    if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                    {                      
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                    }
                    else 
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType);
                    }
                }
            }
        }
    }

    return true;
}

//================================================================================================
// NOTE: StartChannel is -CONDITIONALLY- used for GFP based on module type (SSM).
//================================================================================================
bool ALM_FailureModificationAction::HandleGfpFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isGfp() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0, startChannel = 1; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++, startChannel++)
    {
        //-----------------------------------------------------------------------------
        // Now report/clear the failure for each specific failure defined in the object 
        // (ie: the HOP layer has nine layer failure objects: AIS-P, LOP-P, etc.).
        //-----------------------------------------------------------------------------
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //---------------------------------------------------------------------------------------------
            // Special processing needed for UIDs that must switch the DEFECT PortType direction (side: PORT/LINE).
            // For example, on the SMTM port facility GBEP, LOFD/CSF-x failures are detected by Signal Alarm
            // and the myAmPortType is CT_DIR_WAVE_PORT. However, Alarm Management needs to be told that the
            // direction is CT_DIR_WAVE_LINE, so that it will properly report TDTC direction to user/TL1!
            // Careful...SMTM-P (PacketFam) and SSM needs to report GFP alarms against its OCH-P (LINE_1).
            //---------------------------------------------------------------------------------------------
            if ( ((aCardFamily != PACKET_FAM) && 
                  (aCardFamily != SSM_FAM)) &&
                 (aUid == AM_SG_LOFD_GFP_UID       ||
                  aUid == AM_SG_PLM_GFP_UID        ||
                  aUid == AM_SG_CSF_LOS_GFP_UID    ||
                  aUid == AM_SG_CSF_LOSYNC_GFP_UID ||
                  aUid == AM_SG_CSF_FEFI_GFP_UID   ||
                  aUid == AM_SG_CSF_FDI_GFP_UID    ||
                  aUid == AM_SG_CSF_RDI_GFP_UID    ||
                  aUid == AM_SG_LOA_GFP_UID    ||
                  aUid == AM_SG_SQM_GFP_UID    ||
                  aUid == AM_SG_CHEC_GFP_UID    ||
                  aUid == AM_SG_PLI_GFP_UID) )
            {
                AM_PortType fakeAmPortType = (myAmPortType == CT_DIR_WAVE_LINE) ? CT_DIR_WAVE_PORT : 
                                             (myAmPortType == CT_DIR_WAVE_PORT) ? CT_DIR_WAVE_LINE : myAmPortType;

                if (aCardFamily == HDTG2_FAM)
                {
                    MON_AppIf* aMonRsAppPtr = NULL;
                    ALM_TCount aBlkAISLCount = 0;
                    bool       aBlkAISLDefect = false;
                    aMonRsAppPtr = myCardIf->GetRsIf().GetMonPortSideAppPtr((CT_IntfId)myPortOffset);
                    if (aMonRsAppPtr)
                    {
                        MON_Region* aMonRsReg = aMonRsAppPtr->GetDefectsRegion();
                        if (aMonRsReg)
                        {
                            MON_RsDefects* aMonRsObj = dynamic_cast<MON_RsDefects*>(&((*aMonRsReg)[0]));
                            if (aMonRsObj)
                            {
                                aMonRsObj->GetDefectStatus(CT_TEL_RS_INTERNAL_CSF_OPU_DEFECT, &aBlkAISLCount, &aBlkAISLDefect);
                                if (aBlkAISLDefect)
                                {
                                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(AM_CSFOPU_INH_GFP_FAILURE_UID, myCardIf,  anOccurTime, myPortOffset, fakeAmPortType);
                                }
                                else
                                {
                                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (AM_CSFOPU_INH_GFP_FAILURE_UID, myCardIf, myPortOffset, fakeAmPortType);
                                }
                            }
                        }
                    }
                }

                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, fakeAmPortType);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect(aUid, myCardIf, /* noTime */  myPortOffset, fakeAmPortType);
                }
            
                aUid = AM_INVALID_UID; // report already done
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if ( isStartChannelUsed() ) 
                {
                    if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                    {
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect
                                  (aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType, startChannel);
                    }                    
                    else 
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect
                                  (aUid, myCardIf, /* noTime */ myPortOffset, myAmPortType, startChannel);
                    }
                }
                else // No StartChannel (SMTMU, e.g.).
                {
                    if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                    {
                        aResult = AM_DefectCollector::GetInstance()->ReportDefect
                                  (aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType);
                    }
                    else 
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect
                                  (aUid, myCardIf, /*noTime*/   myPortOffset, myAmPortType);
                    }
                }
            }
        }
    }

    return true;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleHopFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isHop() ) return true;
    ////////////////////////////////////////////////////////

    AM_ReturnResult aResult;
    int anOffset = myAppIf.GetMonElementOffset(); // _A,_B,_C,_D (0-47,48-95,etc).

    ALM_SubApplicationOnRpt* aSubAppRpt = dynamic_cast<ALM_SubApplicationOnRpt*>(&myAppIf);
    if ( !aSubAppRpt ) return false;

    CFG_Region* aHOPCfgRegion = aSubAppRpt->GetCfgAppIf()->GetCfgRegion();
    if ( !aHOPCfgRegion ) return false;

    for (int anObjectIndex = 0, startChannel = 1; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++, startChannel++)
    {
        //===============================================================================
        // For the HOP entities, we want to avoid unnecessary processing, when possible.
        //===============================================================================
        bool forceClearOfDefect = false;
        bool hopHasDefect       = false; // will be used at the end of the loop per STS.

        CFG_Hop* aHopObj = dynamic_cast<CFG_Hop*>(&(*aHOPCfgRegion)[(bbindex_t)((startChannel + anOffset) - 1)]);
        if ( aHopObj && (aHopObj->GetSpeMapping() == CT_TEL_HOP_MAPPING_UNKNOWN) ) 
        {
            if ( myStartChannelProvisionedHasDefect[startChannel-1] )
            {
                forceClearOfDefect = true; // force the clear on non-Provisioned STS.
            }
            else
            {
                continue; // Go to next STS because this is NOT Provisioned w/ no alms.
            }
        }

        //-----------------------------------------------------------------------------
        // Now report/clear the failure for each specific failure defined in the object 
        // (ie: the HOP layer has nine layer failure objects: AIS-P, LOP-P, etc.).
        //-----------------------------------------------------------------------------
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            time_t anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            AM_UID aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            if (aUid != AM_INVALID_UID)
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex) && !forceClearOfDefect)
                {
                    hopHasDefect = true;
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect
                              (aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType, (startChannel + anOffset));
                }
                else // ClearDefect
                {
                    if ( myStartChannelProvisionedHasDefect[startChannel-1] )
                    {
                        aResult = AM_DefectCollector::GetInstance()->ClearDefect
                              (aUid, myCardIf, /*noTime*/   myPortOffset, myAmPortType, (startChannel + anOffset));
                    }
                }
            }
        }

        //------------------------------------------------------------------------------
        // We are finished processing all alarms for the specific HOP entity/STS.
        // Now determine/update the status of the myStartChannelProvisionedHasDefect[].
        //------------------------------------------------------------------------------
        myStartChannelProvisionedHasDefect[startChannel-1] = ( hopHasDefect ) ? true : false;
    }

    return true;
}

//================================================================================================
//================================================================================================
bool ALM_FailureModificationAction::HandleVcgFailureAction(CT_CardFamily aCardFamily)
{
    ////////////////////////////////////////////////////////
    if ( !isVcg() ) return true;
    ////////////////////////////////////////////////////////

    time_t          anOccurTime;
    AM_UID          aUid;
    AM_ReturnResult aResult;

    for (int anObjectIndex = 0, startChannel = 1; anObjectIndex < (int)myAppIf.GetFilteredRegionPtr()->Size(); anObjectIndex++, startChannel++)
    {
        ALM_FailureBase& aFailureBase = (*myAppIf.GetFilteredRegionPtr())[anObjectIndex];

        for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
        {
            anOccurTime = aFailureBase.GetOccurTimeFromIndex(aFailureIndex);
            aUid        = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));

            ///////////////////////////////////////////////////////////////////////////
            if ( aUid == AM_INVALID_UID )
                continue;
            ///////////////////////////////////////////////////////////////////////////

            //---------------------------------------------------------------------------------------------
            // SSM/VCG alarm Failure Of Protocol Transmit does NOT have a side/PortType associated with it.
            //---------------------------------------------------------------------------------------------
            if ( (aCardFamily == SSM_FAM) && (aUid == AM_SG_FOP_TX_UID) )
            {
                AM_PortType fakeAmPortType = CT_DIR_DONT_CARE;

                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {                      
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, fakeAmPortType, startChannel);
                }
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect (aUid, myCardIf, /* noTime*/  myPortOffset, fakeAmPortType, startChannel);
                }
                
                aUid = AM_INVALID_UID; // report already done
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (aUid != AM_INVALID_UID)
            {
                if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                {
                    aResult = AM_DefectCollector::GetInstance()->ReportDefect(aUid, myCardIf, anOccurTime, myPortOffset, myAmPortType, startChannel);
                }                    
                else 
                {
                    aResult = AM_DefectCollector::GetInstance()->ClearDefect(aUid, myCardIf, /* noTime */  myPortOffset, myAmPortType, startChannel);
                }
            }
        }
    }

    return true;
}

//=================================================================================================================
//=================================================================================================================
//=================================================================================================================

/**
 * Method which returns the Alarm Management UID defect value assigned
 * to the common type Signal Alarm.
 */
AM_UID ALM_FailureModificationAction::GetUIDFromType(CT_TelAlarmCondition::CT_FacilityAlarmType theAlarmType) const
{
    if(theAlarmType < CT_TelAlarmCondition::ALM_NB_OF_ALARM)
    {
        return theirUidTable[theAlarmType];
    }

    return AM_INVALID_UID;
}

/**
 * Method which returns the Alarm Management common type direction for
 * the current applications Signal Alarm region.
 */
CT_Direction  ALM_FailureModificationAction::GetCTDirection() const
{
    CT_Direction aDir = CT_DIRECTION_UNKNOWN;
    const string sKey = myAppIf.GetKeySuffix();

    if (sKey == ALM_LINE_SUFFIX   || sKey == ALM_LINE_0_SUFFIX || sKey == ALM_LINE_1_SUFFIX ||
        sKey == ALM_LINE_2_SUFFIX || sKey == ALM_LINE_3_SUFFIX || sKey == ALM_LINE_4_SUFFIX ||
        sKey == ALM_LINE_5_SUFFIX || sKey == ALM_LINE_6_SUFFIX || sKey == ALM_LINE_7_SUFFIX ||
        sKey == ALM_LINE_8_SUFFIX || sKey == ALM_LINE_9_SUFFIX || sKey == ALM_LINE_10_SUFFIX ||
        sKey == ALM_LINE_11_SUFFIX ||

        sKey == ALM_SIDE_A_SUFFIX || sKey == ALM_SIDE_B_SUFFIX ||
        sKey == ALM_SIDE_C_SUFFIX || sKey == ALM_SIDE_D_SUFFIX ||
        sKey == ALM_SIDE_E_SUFFIX || sKey == ALM_SIDE_F_SUFFIX ||
        sKey == ALM_SIDE_G_SUFFIX || sKey == ALM_SIDE_H_SUFFIX ||

        sKey == ALM_LINE_DWDM_OCN_A_SUFFIX || sKey == ALM_LINE_DWDM_OCN_B_SUFFIX  ||
        sKey == ALM_LINE_DWDM_OCN_C_SUFFIX || sKey == ALM_LINE_DWDM_OCN_D_SUFFIX  ||
        sKey == ALM_IMUX_LINE_OCN_A_SUFFIX || sKey == ALM_IMUX_LINE_OCN_B_SUFFIX  ||
        sKey == ALM_IMUX_LINE_OCN_C_SUFFIX || sKey == ALM_IMUX_LINE_OCN_D_SUFFIX  ||
        sKey == ALM_IMUX_PORT_OCN_A_SUFFIX || sKey == ALM_IMUX_PORT_OCN_B_SUFFIX  ||
        sKey == ALM_IMUX_PORT_OCN_C_SUFFIX || sKey == ALM_IMUX_PORT_OCN_D_SUFFIX )
    {
        aDir =  CT_DIRECTION_LINE;
    } 
    else if (sKey == ALM_PORT_SUFFIX    || sKey == ALM_PORT_0_SUFFIX  || sKey == ALM_PORT_1_SUFFIX || 
             sKey == ALM_PORT_2_SUFFIX  || sKey == ALM_PORT_3_SUFFIX  || sKey == ALM_PORT_4_SUFFIX || 
             sKey == ALM_PORT_5_SUFFIX  || sKey == ALM_PORT_6_SUFFIX  || sKey == ALM_PORT_7_SUFFIX ||
             sKey == ALM_PORT_8_SUFFIX  || sKey == ALM_PORT_9_SUFFIX  || sKey == ALM_PORT_10_SUFFIX ||
             sKey == ALM_PORT_11_SUFFIX || sKey == ALM_PORT_12_SUFFIX || sKey == ALM_PORT_13_SUFFIX ||
             sKey == ALM_PORT_14_SUFFIX || sKey == ALM_PORT_15_SUFFIX || sKey == ALM_PORT_16_SUFFIX || 
             sKey == ALM_PORT_17_SUFFIX || sKey == ALM_PORT_18_SUFFIX || sKey == ALM_PORT_19_SUFFIX ||
             sKey == ALM_PORT_20_SUFFIX || sKey == ALM_PORT_21_SUFFIX || sKey == ALM_PORT_22_SUFFIX ||
             sKey == ALM_PORT_23_SUFFIX || sKey == ALM_PORT_24_SUFFIX || sKey == ALM_PORT_25_SUFFIX ||
             sKey == ALM_PORT_26_SUFFIX || sKey == ALM_PORT_27_SUFFIX || sKey == ALM_PORT_28_SUFFIX || 
             sKey == ALM_PORT_29_SUFFIX ||
             sKey == ALM_T1E1_SUFFIX ||

             sKey == ALM_PORT_30_SUFFIX || sKey == ALM_PORT_31_SUFFIX || sKey == ALM_PORT_32_SUFFIX ||
             sKey == ALM_PORT_33_SUFFIX || sKey == ALM_PORT_34_SUFFIX ||

             sKey == ALM_PORT_40_SUFFIX || sKey == ALM_PORT_41_SUFFIX ||

             sKey == ALM_PORT_50_SUFFIX || sKey == ALM_PORT_51_SUFFIX ||

             sKey == ALM_PORT_60_SUFFIX || sKey == ALM_PORT_61_SUFFIX ||

             sKey == ALM_PORT_85_SUFFIX || sKey == ALM_PORT_86_SUFFIX || sKey == ALM_PORT_87_SUFFIX || sKey == ALM_PORT_88_SUFFIX ||

             sKey == ALM_PORT_O192_OCN_A_SUFFIX || sKey == ALM_PORT_O192_OCN_B_SUFFIX ||
             sKey == ALM_PORT_O192_OCN_C_SUFFIX || sKey == ALM_PORT_O192_OCN_D_SUFFIX)
    {
        aDir =  CT_DIRECTION_PORT;
    }
    
    return aDir;
}

/**
 * Method which maps the suffix string of a Signal Alarm region to
 * a 0-based port offset.
 */
void  ALM_FailureModificationAction::ALM_CalculatePortOffset()
{
    const string sKey = myAppIf.GetKeySuffix();

    if (     sKey == ALM_PORT_1_SUFFIX || sKey == ALM_LINE_1_SUFFIX)
    {
        myPortOffset = 1;

        //----------------------------------------------------------
        // Special case for TRN family. To make things consistent
        // between the SMTMU and TRN, the decision was made to 
        // create TRN ALM subapplications with LINE_1 - OPT/OTU/ODU.
        // However, we want the alarm (e.g. LOS) to be posted on LINE_0!
        //----------------------------------------------------------
        if ( (sKey == ALM_LINE_1_SUFFIX) && (myCardIf) && 
             (myCardIf->GetCardFamily() == TRN_FAM ||
              myCardIf->GetCardFamily() == FGTMM_FAM) ) 
        {
            myPortOffset = 0;
        }
    }
    else if (sKey == ALM_PORT_2_SUFFIX || sKey == ALM_LINE_2_SUFFIX)
    {
        myPortOffset = 2;
    }
    else if (sKey == ALM_PORT_3_SUFFIX || sKey == ALM_LINE_3_SUFFIX ||
             sKey == ALM_IMUX_LINE_OCN_A_SUFFIX ||
             sKey == ALM_IMUX_LINE_OCN_B_SUFFIX ||
             sKey == ALM_IMUX_LINE_OCN_C_SUFFIX ||
             sKey == ALM_IMUX_LINE_OCN_D_SUFFIX )   
    {
        myPortOffset = 3;
    }
    else if (sKey == ALM_PORT_4_SUFFIX || sKey == ALM_LINE_4_SUFFIX ||
             sKey == ALM_T1E1_SUFFIX ||
             sKey == ALM_IMUX_PORT_OCN_A_SUFFIX ||
             sKey == ALM_IMUX_PORT_OCN_B_SUFFIX ||
             sKey == ALM_IMUX_PORT_OCN_C_SUFFIX ||
             sKey == ALM_IMUX_PORT_OCN_D_SUFFIX )
    {
        myPortOffset = 4;
    }
    else if (sKey == ALM_PORT_5_SUFFIX || sKey == ALM_LINE_5_SUFFIX)          
    {
        myPortOffset = 5;
    }
    else if (sKey == ALM_PORT_6_SUFFIX || sKey == ALM_LINE_6_SUFFIX)          
    {
        myPortOffset = 6;
    }
    else if (sKey == ALM_PORT_7_SUFFIX || sKey == ALM_LINE_7_SUFFIX)          
    {
        myPortOffset = 7;
    }
    else if (sKey == ALM_PORT_8_SUFFIX || sKey == ALM_LINE_8_SUFFIX)
    {
        myPortOffset = 8;
    }
    else if (sKey == ALM_PORT_9_SUFFIX || sKey == ALM_LINE_9_SUFFIX)
    {
        myPortOffset = 9;
    }
    else if (sKey == ALM_PORT_10_SUFFIX || sKey == ALM_LINE_10_SUFFIX)
    {
        myPortOffset = 10;
    }
    else if (sKey == ALM_PORT_11_SUFFIX || sKey == ALM_LINE_11_SUFFIX)
    {
        myPortOffset = 11;
    }
    else if (sKey == ALM_PORT_12_SUFFIX ||
             sKey == ALM_PORT_O192_OCN_A_SUFFIX ||
             sKey == ALM_PORT_O192_OCN_B_SUFFIX ||
             sKey == ALM_PORT_O192_OCN_C_SUFFIX ||
             sKey == ALM_PORT_O192_OCN_D_SUFFIX)
    {
        myPortOffset = 12;
    }
    else if (sKey == ALM_PORT_13_SUFFIX)
    {
        myPortOffset = 13;
    }
    else if (sKey == ALM_PORT_14_SUFFIX)
    {
        myPortOffset = 14;
    }
    else if (sKey == ALM_PORT_15_SUFFIX)
    {
        myPortOffset = 15;
    }
    else if (sKey == ALM_PORT_16_SUFFIX)
    {
        myPortOffset = 16;
    }
    else if (sKey == ALM_PORT_17_SUFFIX)
    {
        myPortOffset = 17;
    }
    else if (sKey == ALM_PORT_18_SUFFIX)
    {
        myPortOffset = 18;
    }
    else if (sKey == ALM_PORT_19_SUFFIX)
    {
        myPortOffset = 19;
    }
    else if (sKey == ALM_PORT_20_SUFFIX)
    {
        myPortOffset = 20;
    }
    else if (sKey == ALM_PORT_21_SUFFIX)
    {
        myPortOffset = 21;
    }
    else if (sKey == ALM_PORT_22_SUFFIX)
    {
        myPortOffset = 22;
    }
    else if (sKey == ALM_PORT_23_SUFFIX)
    {
        myPortOffset = 23;
    }
    else if (sKey == ALM_PORT_24_SUFFIX)
    {
        myPortOffset = 24;
    }
    else if (sKey == ALM_PORT_25_SUFFIX)
    {
        myPortOffset = 25;
    }
    else if (sKey == ALM_PORT_26_SUFFIX)
    {
        myPortOffset = 26;
    }
    else if (sKey == ALM_PORT_27_SUFFIX)
    {
        myPortOffset = 27;
    }
    else if (sKey == ALM_PORT_28_SUFFIX)
    {
        myPortOffset = 28;
    }
    else if (sKey == ALM_PORT_29_SUFFIX)
    {
        myPortOffset = 29;
    }
    else if (sKey == ALM_PORT_30_SUFFIX)
    {
        myPortOffset = 30;
    }
    else if (sKey == ALM_PORT_31_SUFFIX)
    {
        myPortOffset = 31;
    }
    else if (sKey == ALM_PORT_32_SUFFIX)
    {
        myPortOffset = 32;
    }
    else if (sKey == ALM_PORT_33_SUFFIX)
    {
        myPortOffset = 33;
    }
    else if (sKey == ALM_PORT_34_SUFFIX)
    {
        myPortOffset = 34;
    }

    else if (sKey == ALM_PORT_40_SUFFIX)
    {
        myPortOffset = 40;
    }
    else if (sKey == ALM_PORT_85_SUFFIX)
    {
        myPortOffset = 85;
    }
    else if (sKey == ALM_PORT_86_SUFFIX)
    {
        myPortOffset = 86;
    }
    else if (sKey == ALM_PORT_87_SUFFIX)
    {
        myPortOffset = 87;
    }
    else if (sKey == ALM_PORT_88_SUFFIX)
    {
        myPortOffset = 88;
    }
    else
    {
        myPortOffset = 0;
    }
}

/**
 * Method returns CT_Side
 */
CT_Side  ALM_FailureModificationAction::GetCTSide() const
{
    CT_Side aSide = CT_SIDE_UNKNOWN;

    if ( myAppIf.GetKeySuffix() == ALM_SIDE_A_SUFFIX )
        aSide = CT_SIDE_A;
    else
    if ( myAppIf.GetKeySuffix() == ALM_SIDE_B_SUFFIX )
        aSide = CT_SIDE_B;
    else
    if ( myAppIf.GetKeySuffix() == ALM_SIDE_C_SUFFIX )
        aSide = CT_SIDE_C;
    else
    if ( myAppIf.GetKeySuffix() == ALM_SIDE_D_SUFFIX )
        aSide = CT_SIDE_D;
    else
    if ( myAppIf.GetKeySuffix() == ALM_SIDE_E_SUFFIX )
        aSide = CT_SIDE_E;
    else
    if ( myAppIf.GetKeySuffix() == ALM_SIDE_F_SUFFIX )
        aSide = CT_SIDE_F;
    else
    if ( myAppIf.GetKeySuffix() == ALM_SIDE_G_SUFFIX )
        aSide = CT_SIDE_G;
    else
    if ( myAppIf.GetKeySuffix() == ALM_SIDE_H_SUFFIX )
        aSide = CT_SIDE_H;

    return aSide;
}

/*
 * Used to handle both OPT and OTU layer mapping of LOC/LOF to LOF_OTU
 */
bool  ALM_FailureModificationAction::isLOFLOCAlmExists()
{
    return myLOFLOCAlmExists;
}

/**
 * Method returns true if the instance is a StartChannelUsed sub-application 
 */
bool  ALM_FailureModificationAction::isStartChannelUsed() const
{
    bool isStartChannelUsed = false;
    
    const char* instname = myAppIf.GetInstanceName();

    //--------------------------------------------------------------------------
    // These entities -ALWAYS- use startChannel!
    //--------------------------------------------------------------------------
    isStartChannelUsed = (strncmp(instname, "HOP", 3) == 0 ) ? true : false;

    if (isStartChannelUsed == false) // try DCCL
        isStartChannelUsed = (strncmp(instname, "DCC", 3) == 0 ) ? true : false;

    if (isStartChannelUsed == false) // try GCC
        isStartChannelUsed = (strncmp(instname, "GCC", 3) == 0 ) ? true : false;

    if (isStartChannelUsed == false) // try VCG
        isStartChannelUsed = (strncmp(instname, "VCG", 3) == 0 ) ? true : false;

    if (isStartChannelUsed == false) // try TCM
        isStartChannelUsed = (strncmp(instname, "TCM", 3) == 0 ) ? true : false;

    //--------------------------------------------------------------------------
    // These entities -CONDITIONALLY- use startChannel!
    //--------------------------------------------------------------------------
    if ( (isStartChannelUsed == false) &&                     // try GFP
         (myCardIf && myCardIf->GetCardFamily() == SSM_FAM)) // on SSM
    {
        isStartChannelUsed = (strncmp(instname, "GFP", 3) == 0 ) ? true : false;
    }
    
    if ( (isStartChannelUsed == false) && // try ODUKPOOL
         (myCardIf) && 
         (myCardIf->GetCardFamily() == HDTG_FAM ||
          myCardIf->GetCardFamily() == ENH_PACKET_FAM ||
          myCardIf->GetCardFamily() == ENH_TRN_FAM ||
          myCardIf->GetCardFamily() == SSM40_FAM ||
          myCardIf->GetCardFamily() == FGSM_FAM ||
          myCardIf->GetCardFamily() == OMM_FAM ||
          myCardIf->GetCardFamily() == FGSM_FAM ||
          myCardIf->GetCardFamily() == HGTMM_FAM||
          myCardIf->GetCardFamily() == OSM_FAM ||
          myCardIf->GetCardFamily() == HDTG2_FAM) )
    {
        isStartChannelUsed = (strncmp(instname, "ODU", 3) == 0 ) ? true : false;
    }

    return isStartChannelUsed;
}

/**
 * Method returns true if the instance is an OMS or OTS sub-application 
 */
bool  ALM_FailureModificationAction::isOtsOms() const
{
    bool isOtsOms = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isOtsOms =  ((strncmp(instname, "OMS", 3) == 0 ) || 
                 (strncmp(instname, "OTS", 3) == 0 ) || 
                 (strncmp(instname, "RS:OSC", 6) == 0 ) || 
                 (strncmp(instname, "OPT:OSC", 7) == 0 )) ? true : false;
    
    return isOtsOms;
}

/**
 * Method returns true if the instance is a OCH sub-application 
 */
bool  ALM_FailureModificationAction::isOch() const
{
    bool isOch = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isOch =  (strncmp(instname, "OCH", 3) == 0 ) ? true : false;
    
    return isOch;
}

/**
 * Method returns true if the instance is a OPT sub-application 
 */
bool  ALM_FailureModificationAction::isOpt() const
{
    bool isOpt = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isOpt =  (strncmp(instname, "OPT:SC", 6) == 0 ) ? true : false;
    
    return isOpt;
}

/**
 * Method returns true if the instance is a OTU sub-application
 */
bool  ALM_FailureModificationAction::isOtu() const
{
    bool isOtu = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isOtu =  (strncmp(instname, "OTU", 3) == 0 ) ? true : false;
    
    return isOtu;
}

/**
 * Method returns true if the instance is a RS sub-application
 */
bool  ALM_FailureModificationAction::isRs() const
{
    bool isRs = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isRs =  (strncmp(instname, "RS:SC", 5) == 0 ) ? true : false;
    
    return isRs;
}

/**
 * Method returns true if the instance is a MS sub-application
 */
bool  ALM_FailureModificationAction::isMs() const
{
    bool isMs = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isMs =  (strncmp(instname, "MS:SC", 5) == 0 ) ? true : false;
    
    return isMs;
}

/**
 * Method returns true if the instance is a ODU sub-application
 */
bool  ALM_FailureModificationAction::isOdu() const
{
    bool isOdu = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isOdu =  (strncmp(instname, "ODU", 3) == 0 ) ? true : false;
    
    return isOdu;
}

/**
 * Method returns true if the instance is a SYNC sub-application 
 */
bool  ALM_FailureModificationAction::isSync() const
{
    bool isSync = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isSync =  (strncmp(instname, "SYNC", 4) == 0 ) ? true : false;
    
    return isSync;
}

/**
 * Method returns true if the instance is a DCCL sub-application 
 */
bool  ALM_FailureModificationAction::isDccl() const
{
    bool isDccl = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isDccl = (strncmp(instname, "DCC", 3) == 0 ) ? true : false;
    
    return isDccl;
}

/**
 * Method returns true if the instance is a GCC sub-application 
 */
bool  ALM_FailureModificationAction::isGcc() const
{
    bool isGcc = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isGcc = (strncmp(instname, "GCC", 3) == 0 ) ? true : false;
    
    return isGcc;
}

/**
 * Method returns true if the instance is a VCG sub-application 
 */
bool  ALM_FailureModificationAction::isVcg() const
{
    bool isVcg = false;
    
    const char* instname = myAppIf.GetInstanceName();

    isVcg = (strncmp(instname, "VCG", 3) == 0 ) ? true : false;
    
    return isVcg;
}

/**
 * Method returns true if the instance is a GFP sub-application
 */
bool  ALM_FailureModificationAction::isGfp() const
{
    bool isGfp = false;

    const char* instname = myAppIf.GetInstanceName();

    isGfp = (strncmp(instname, "GFP", 3) == 0 ) ? true : false;

    return isGfp;
}

/**
 * Method returns true if the instance is a TCM sub-application
 */
bool  ALM_FailureModificationAction::isTcm() const
{
    bool isTcm = false;

    const char* instname = myAppIf.GetInstanceName();

    isTcm = (strncmp(instname, "TCM", 3) == 0 ) ? true : false;

    return isTcm;
}

/**
 * Method returns true if the instance is a HOP sub-application
 */
bool  ALM_FailureModificationAction::isHop() const
{
    bool isHop = false;

    const char* instname = myAppIf.GetInstanceName();

    isHop = (strncmp(instname, "HOP", 3) == 0 ) ? true : false;

    return isHop;
}

HGTMMS_FGEHGE_PORTGROUP_TYPE ALM_FailureModificationAction::GetHgtmmsFgeHgePortGroupType(CT_IntfId thePort)
{
    HGTMMS_FGEHGE_PORTGROUP_TYPE theFac = NOT_GROUP;
    int theSignalType;

    

    if( (CT_PORT_SIDE_2 <= thePort && thePort <= CT_PORT_SIDE_5) ||
        (CT_PORT_SIDE_10 <= thePort && thePort <= CT_PORT_SIDE_11)  )
    {
        ALM_AppIf* theAlmAppIfPtr = myCardIf->GetOptIfPtr()->GetAlmPortSideAppPtr(CT_PORT_SIDE_2);
        ALM_FailureBase& aFailureBase = (*theAlmAppIfPtr->GetFilteredRegionPtr())[0];
        theSignalType = aFailureBase.GetSignalType();
        if(theSignalType == CT_TEL_SIGNAL_FGE) // FGE2
        {
            theFac = PORT_GROUP_FGE_2;
        }
        else if(theSignalType == CT_TEL_SIGNAL_HGE || theSignalType == CT_TEL_SIGNAL_HGE_GFP) // HGE2
        {
            theFac = PORT_GROUP_HGE_2;
        }
    }
    else if(CT_PORT_SIDE_6 <= thePort && thePort <= CT_PORT_SIDE_9)
    {
        ALM_AppIf* theAlmAppIfPtr = myCardIf->GetOptIfPtr()->GetAlmPortSideAppPtr(CT_PORT_SIDE_2);
        ALM_FailureBase& aFailureBase = (*theAlmAppIfPtr->GetFilteredRegionPtr())[0];
        theSignalType = aFailureBase.GetSignalType();
        if(theSignalType == CT_TEL_SIGNAL_HGE || theSignalType == CT_TEL_SIGNAL_HGE_GFP) // HGE2
        {
            theFac = PORT_GROUP_HGE_2;
        }
        else
        {
            theAlmAppIfPtr = myCardIf->GetOptIfPtr()->GetAlmPortSideAppPtr(CT_PORT_SIDE_6);
            ALM_FailureBase& aFailureBase = (*theAlmAppIfPtr->GetFilteredRegionPtr())[0];
            theSignalType = aFailureBase.GetSignalType();
            if(theSignalType == CT_TEL_SIGNAL_FGE) // FGE6
            {
                theFac = PORT_GROUP_FGE_6;
            }
        }
    }

    return theFac;
}

void ALM_FailureModificationAction::SetFgeHgeLedGroupLos(bool isSet, time_t anOccurTime)
{
    HGTMMS_FGEHGE_PORTGROUP_MAP thePortBitMap = GetHgtmmsFgeHgePortGroupMap((CT_IntfId)myPortOffset);
    if(thePortBitMap != NOT_PORTGROUP_MAP)
    {
        if(isSet)  // report against other sub ports
        {
            thePortBitMap -= (0x1 << myPortOffset);
            for(int i = 0; i < CT_PORT_SIDE_12; i++)
            {
                if(((thePortBitMap >> i) & 0x1) == 0x1)
                {
                    AM_DefectCollector::GetInstance()->ReportDefect(AM_SG_LED_GROUP_LOS_UID, myCardIf, anOccurTime, i, myAmPortType);
                }
            }
        }
        else  // clear all sub ports
        {
            for(int i = 0; i < CT_PORT_SIDE_12; i++)
            {
                if(((thePortBitMap >> i) & 0x1) == 0x1)
                {
                    AM_DefectCollector::GetInstance()->ClearDefect(AM_SG_LED_GROUP_LOS_UID, myCardIf,  i, myAmPortType);
                }
            }
        }
    }
}

bool ALM_FailureModificationAction::IsFgeHgeGroupHasLos()
{
    bool ret = false;
    HGTMMS_FGEHGE_PORTGROUP_MAP thePortGroupMap = GetHgtmmsFgeHgePortGroupMap((CT_IntfId)myPortOffset);
    AM_UID aUid;

    if(thePortGroupMap != NOT_PORTGROUP_MAP)
    {
        for(int i = 0; i<CT_PORT_SIDE_12; i++)
        {
            if((((thePortGroupMap >> i) & 0x1) & 0x1))
            {
                ALM_AppIf* theAlmAppIfPtr = myCardIf->GetOptIfPtr()->GetAlmPortSideAppPtr((CT_IntfId)i);
                ALM_FailureBase& aFailureBase = (*theAlmAppIfPtr->GetFilteredRegionPtr())[0];
                for (int aFailureIndex = 0; aFailureIndex < aFailureBase.GetNbOfFailure(); aFailureIndex++)
                {
                    aUid = GetUIDFromType(aFailureBase.GetTypeFromIndex(aFailureIndex));
                    if(aUid == AM_SG_LOS_OPT_UID)
                    {
                        if (aFailureBase.GetStatusFromIndex(aFailureIndex))
                        {
                            ret = true;
                            break;
                        }
                        
                    }
                }
                if(ret == true)
                {
                    break;
                }
            }
        }
    }
    return ret;
}

HGTMMS_FGEHGE_PORTGROUP_MAP ALM_FailureModificationAction::GetHgtmmsFgeHgePortGroupMap(CT_IntfId thePort)
{
    HGTMMS_FGEHGE_PORTGROUP_MAP theMap = NOT_PORTGROUP_MAP;
    HGTMMS_FGEHGE_PORTGROUP_TYPE theType = GetHgtmmsFgeHgePortGroupType(thePort);
    switch(theType)
    {
        case PORT_GROUP_FGE_2:
            theMap = FGE_2_PORTGROUP_MAP;
            break;
        case PORT_GROUP_FGE_6:
            theMap = FGE_6_PORTGROUP_MAP;
            break;
        case PORT_GROUP_HGE_2:
            theMap = HGE_2_PORTGROUP_MAP;
            break;
        default:
            break;
    }
    return theMap;
}

CT_IntfId ALM_FailureModificationAction::GetFgeHgeGroupRepresentPort()
{
    CT_IntfId ret = CT_INTF_ID_UNKNOWN;
    HGTMMS_FGEHGE_PORTGROUP_TYPE theType = GetHgtmmsFgeHgePortGroupType((CT_IntfId)myPortOffset);
    switch(theType)
    {
        case PORT_GROUP_FGE_2:
            ret = CT_PORT_SIDE_2;
            break;
        case PORT_GROUP_FGE_6:
            ret = CT_PORT_SIDE_6;
            break;
        case PORT_GROUP_HGE_2:
            ret = CT_PORT_SIDE_2;
            break;
        default:
            break;
    }
    return ret;
}



