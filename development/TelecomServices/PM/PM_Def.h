/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     11 June, 1998 Jean-Francois Birtz.
 DESCRIPTION:   This file contains global definitions for PM
                used internally.
--------------------------------------------------------------------------*/

#ifndef PM_DEF_H
#define PM_DEF_H

#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <T6100_Services.h>


// Threshold value for counter that will not cause a TCA to be raised.
#define PM_NO_TCA_COUNTER_THRES_VALUE   0
// Threshold value for gauge that will not cause a TCA to be raised.
#define PM_NO_TCA_GAUGE_THRES_VALUE     0xFFFFFFF
// Threshold value for xvalue that will not cause a defect to be raised.
#define PM_NO_TCA_X_VALUE               0xFFFFFFFF
// Threshold value for yvalue that will not cause a defect to be raised.
#define PM_NO_TCA_Y_VALUE               PM_NO_TCA_X_VALUE

// For SONET/SDH PM, MS and HOP layer PM implements the concept of Unavailability.
// During transition to/from/during unavailability period, certain PM parameters
// are adjusted. How the parameter is adjusted depends on the sematics of the PM 
// parameter. These define the type of PM parameter in terms of a bitmap flag.
#define PM_BASIC_PARAMETER         0x00
#define PM_UAS_PARAMETER           0x01
#define PM_UAS_ADJUSTED_PARAMETER  0x02

// Default X values.
#define PM_XVAL_SES_RS_OC3      PM_NO_TCA_X_VALUE   // 155, Number of CV to have SES in OC3.
#define PM_XVAL_SES_RS_OC12     PM_NO_TCA_X_VALUE   // 616, Number of CV to have SES in OC12.
#define PM_XVAL_SES_RS_E1       PM_NO_TCA_X_VALUE   // 805, Number of CV to have SES in E1.
#define PM_XVAL_SES_RS_OC48     PM_NO_TCA_X_VALUE   // 2392, Number of CV to have SES in OC48.
#define PM_XVAL_SES_RS_OC192    PM_NO_TCA_X_VALUE   // 8554, Number of CV to have SES in OC192.
#define PM_XVAL_SES_RS_OC768    PM_NO_TCA_X_VALUE   // Number of CV to have SES in OC768.
                                                    // 
#define PM_XVAL_SES_OTU_ODU_0     PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODU layer 2.
#define PM_XVAL_SES_OTU_ODU_1     PM_NO_TCA_X_VALUE   // 2392, Number of BE to have SES in OTU/ODU layer 1.
#define PM_XVAL_SES_OTU_ODU_2     PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODU layer 2.
#define PM_XVAL_SES_OTU_ODU_2e    PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODU layer 2.
#define PM_XVAL_SES_OTU_ODU_3     PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODU layer 2.
#define PM_XVAL_SES_OTU_ODU_3e2   PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODU layer 2.
#define PM_XVAL_SES_OTU_ODU_4     PM_NO_TCA_X_VALUE   //       Number of BE to have SES in OTU/ODU layer 2.
#define PM_XVAL_SES_OTU_ODU_F     PM_NO_TCA_X_VALUE   //       Number of BE to have SES in OTU/ODU layer 2.

#define PM_XVAL_SES_OTU_ODU_0T  PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODUT layer 0.
#define PM_XVAL_SES_OTU_ODU_1T  PM_NO_TCA_X_VALUE   // 2392, Number of BE to have SES in OTU/ODUT layer 1.
#define PM_XVAL_SES_OTU_ODU_2T  PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODUT layer 2.
#define PM_XVAL_SES_OTU_ODU_3T  PM_NO_TCA_X_VALUE   // 8854, Number of BE to have SES in OTU/ODUT layer 3.
#define PM_XVAL_SES_OTU_ODU_4T  PM_NO_TCA_X_VALUE   //       Number of BE to have SES in OTU/ODUT layer 3.
          
#define PM_XVAL_SES_MS_OC3      PM_NO_TCA_X_VALUE   // 155, Number of CV to have SES in OC3.
#define PM_XVAL_SES_MS_OC12     PM_NO_TCA_X_VALUE   // 616, Number of CV to have SES in OC12.
#define PM_XVAL_SES_MS_OC48     PM_NO_TCA_X_VALUE   // 2392, Number of CV to have SES in OC48.
#define PM_XVAL_SES_MS_OC192    PM_NO_TCA_X_VALUE   // 8554, Number of CV to have SES in OC192.
#define PM_XVAL_SES_MS_OC768    PM_NO_TCA_X_VALUE   // Number of CV to have SES in OC768.

#define PM_XVAL_SES_HOP_STS1    PM_NO_TCA_X_VALUE   // 2400, Number of CV to have SES in STS1.
#define PM_XVAL_SES_HOP_STS3C   PM_NO_TCA_X_VALUE   // 2400, Number of CV to have SES in STS3C.
#define PM_XVAL_SES_HOP_STS12C  PM_NO_TCA_X_VALUE   // 2400, Number of CV to have SES in STS12C.
#define PM_XVAL_SES_HOP_STS48C  PM_NO_TCA_X_VALUE   // 2400, Number of CV to have SES in STS48C.
#define PM_XVAL_SES_HOP_STS192C PM_NO_TCA_X_VALUE   // 2400, Number of CV to have SES in STS192C.



// Default Y values.
#define PM_YVAL_SES_RS_STM1		PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_RS_STM4     PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_RS_STM16	PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_RS_STM64    PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_RS_STM256   PM_NO_TCA_Y_VALUE
          
#define PM_YVAL_SES_MS_STM1		PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_MS_STM4		PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_MS_STM16	PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_MS_STM64    PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_MS_STM256   PM_NO_TCA_Y_VALUE

#define PM_YVAL_SES_HOP_VC3		PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_HOP_VC4		PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_HOP_VC4_4C	PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_HOP_VC4_16C  PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_HOP_VC4_64C  PM_NO_TCA_Y_VALUE

#define PM_YVAL_SES_OTU_OTU1    PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_OTU_OTU2    PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_OTU_OTU3    PM_NO_TCA_Y_VALUE
#define PM_YVAL_SES_OTU_OTU4    PM_NO_TCA_Y_VALUE

// PM Min and Max threshold values for optical power transmitted.
// Note that threshold values are multiplied by CT_TEL_POWER_FACTOR = 100.
#define PM_LOW_MIN_THRES_POWER_VALUE    -PM_NO_TCA_GAUGE_THRES_VALUE    // dB.
#define PM_HIGH_MAX_THRES_POWER_VALUE   PM_NO_TCA_GAUGE_THRES_VALUE     // dB.
#define PM_LOW_MIN_THRES_DGD_VALUE      -PM_NO_TCA_GAUGE_THRES_VALUE    // dB.
#define PM_HIGH_MAX_THRES_DGD_VALUE     PM_NO_TCA_GAUGE_THRES_VALUE     // dB.
#define PM_LOW_MIN_THRES_CD_VALUE       -PM_NO_TCA_GAUGE_THRES_VALUE    //
#define PM_HIGH_MAX_THRES_CD_VALUE      PM_NO_TCA_GAUGE_THRES_VALUE     //
#define PM_LOW_MIN_THRES_OSNR_VALUE     -PM_NO_TCA_GAUGE_THRES_VALUE    //
#define PM_HIGH_MAX_THRES_OSNR_VALUE    PM_NO_TCA_GAUGE_THRES_VALUE     //
#define PM_MAX_THRES_PSC_15M            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_PSD_15M            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_PSC_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_PSD_DAY            PM_NO_TCA_COUNTER_THRES_VALUE

// PM Min and Max threshold values for laser temperature.
#define PM_LOW_MIN_THRES_LT_VALUE       -PM_NO_TCA_GAUGE_THRES_VALUE    // milliCelcius
#define PM_HIGH_MAX_THRES_LT_VALUE      PM_NO_TCA_GAUGE_THRES_VALUE     // milliCelcius

// PM Min and Max threshold values for laser bias current.
#define PM_LOW_MIN_THRES_LBC_VALUE      -PM_NO_TCA_GAUGE_THRES_VALUE    // %
#define PM_HIGH_MAX_THRES_LBC_VALUE     PM_NO_TCA_GAUGE_THRES_VALUE     // %

// PM Max threshold values for Data, SONET/SDH RS and MS layer parameters for 15m.
#define PM_MAX_THRES_LOSS_15M           PM_NO_TCA_COUNTER_THRES_VALUE   // 2
#define PM_MAX_THRES_AISS_15M           PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_CV_15M_156M        PM_NO_TCA_COUNTER_THRES_VALUE   // 140         // OC3
#define PM_MAX_THRES_CV_15M_625M        PM_NO_TCA_COUNTER_THRES_VALUE   // 560         // OC12
#define PM_MAX_THRES_CV_15M_2_5G        PM_NO_TCA_COUNTER_THRES_VALUE   // 2240        // OC48
#define PM_MAX_THRES_CV_15M_10G         PM_NO_TCA_COUNTER_THRES_VALUE   // 8960        // OC192
#define PM_MAX_THRES_CV_15M_STS1        PM_NO_TCA_COUNTER_THRES_VALUE   // 140         // STS1
#define PM_MAX_THRES_CV_15M_STS3C       PM_NO_TCA_COUNTER_THRES_VALUE   // 560         // STS3C
#define PM_MAX_THRES_CV_15M_STS12C      PM_NO_TCA_COUNTER_THRES_VALUE   // 2240        // STS12C
#define PM_MAX_THRES_CV_15M_STS48C      PM_NO_TCA_COUNTER_THRES_VALUE   // 8960        // STS48C
#define PM_MAX_THRES_CV_15M_STS192C     PM_NO_TCA_COUNTER_THRES_VALUE   // 35840       // STS192C
#define PM_MAX_THRES_SE_15M             PM_NO_TCA_COUNTER_THRES_VALUE   // 2147483647             
#define PM_MAX_THRES_SEFS_15M           PM_NO_TCA_COUNTER_THRES_VALUE   // 2
#define PM_MAX_THRES_SES_15M            PM_NO_TCA_COUNTER_THRES_VALUE   // 4
#define PM_MAX_THRES_ES_15M             PM_NO_TCA_COUNTER_THRES_VALUE   // 25
#define PM_MAX_THRES_ESA_15M            PM_NO_TCA_COUNTER_THRES_VALUE   // 25
#define PM_MAX_THRES_ESB_15M            PM_NO_TCA_COUNTER_THRES_VALUE   // 25
#define PM_MAX_THRES_UAS_15M            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_PSC_15M            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_PSD_15M            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_FC_15M             PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PPJCGEN_15M		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_NPJCGEN_15M		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PPJCDET_15M		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_NPJCDET_15M		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PJCSGEN_15M		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PJCSDET_15M		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PJCSDIFF_15M		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_10B_ERR_15M        PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_DROP_15M           PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PKT_15M            PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_BCPKT_15M          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_MCPKT_15M          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_CRCAE_15M          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_USPKT_15M          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_OSPKT_15M          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_FRAG_15M           PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_JABR_15M           PM_NO_TCA_COUNTER_THRES_VALUE

// PM Max threshold values for SONET/SDH RS and MS parameters for 1 Day.
#define PM_MAX_THRES_LOSS_DAY           PM_NO_TCA_COUNTER_THRES_VALUE   // 8
#define PM_MAX_THRES_AISS_DAY           PM_NO_TCA_COUNTER_THRES_VALUE   // 8
#define PM_MAX_THRES_CV_DAY_156M        PM_NO_TCA_COUNTER_THRES_VALUE   // 13440       // OC3
#define PM_MAX_THRES_CV_DAY_625M        PM_NO_TCA_COUNTER_THRES_VALUE   // 53760       // OC12
#define PM_MAX_THRES_CV_DAY_2_5G        PM_NO_TCA_COUNTER_THRES_VALUE   // 215040      // OC48
#define PM_MAX_THRES_CV_DAY_10G         PM_NO_TCA_COUNTER_THRES_VALUE   // 860160      // OC192
#define PM_MAX_THRES_CV_DAY_STS1        PM_NO_TCA_COUNTER_THRES_VALUE   // 140         // STS1
#define PM_MAX_THRES_CV_DAY_STS3C       PM_NO_TCA_COUNTER_THRES_VALUE   // 560         // STS3C
#define PM_MAX_THRES_CV_DAY_STS12C      PM_NO_TCA_COUNTER_THRES_VALUE   // 2240        // STS12C
#define PM_MAX_THRES_CV_DAY_STS48C      PM_NO_TCA_COUNTER_THRES_VALUE   // 8960        // STS48C
#define PM_MAX_THRES_CV_DAY_STS192C     PM_NO_TCA_COUNTER_THRES_VALUE   // 35840       // STS192C
#define PM_MAX_THRES_SE_DAY             PM_NO_TCA_COUNTER_THRES_VALUE   // 2147483647
#define PM_MAX_THRES_SEFS_DAY           PM_NO_TCA_COUNTER_THRES_VALUE   // 8
#define PM_MAX_THRES_SES_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   // 40
#define PM_MAX_THRES_ES_DAY             PM_NO_TCA_COUNTER_THRES_VALUE   // 250
#define PM_MAX_THRES_ESA_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   // 250
#define PM_MAX_THRES_ESB_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   // 250
#define PM_MAX_THRES_UAS_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_PSC_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_PSD_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_FC_DAY             PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PPJCGEN_DAY		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_NPJCGEN_DAY		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PPJCDET_DAY		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_NPJCDET_DAY		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PJCSGEN_DAY		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PJCSDET_DAY		PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PJCDIFF_DAY		PM_NO_TCA_COUNTER_THRES_VALUE   
#define PM_MAX_THRES_10B_ERR_DAY        PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_DROP_DAY           PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_PKT_DAY            PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_BCPKT_DAY          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_MCPKT_DAY          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_CRCAE_DAY          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_USPKT_DAY          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_OSPKT_DAY          PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_FRAG_DAY           PM_NO_TCA_COUNTER_THRES_VALUE
#define PM_MAX_THRES_JABR_DAY           PM_NO_TCA_COUNTER_THRES_VALUE

#define PM_LOW_MIN_THRES_UTIL_VALUE     -PM_NO_TCA_GAUGE_THRES_VALUE
#define PM_HIGH_MAX_THRES_UTIL_VALUE    PM_NO_TCA_GAUGE_THRES_VALUE

// PM Max threshold values for EON parameters for 15m.
#define PM_MAX_THRES_ICMPDUR_15M        PM_NO_TCA_COUNTER_THRES_VALUE   // 10
#define PM_MAX_THRES_ICMPDUT_15M        PM_NO_TCA_COUNTER_THRES_VALUE   // 10
#define PM_MAX_THRES_ICMPER_15M         PM_NO_TCA_COUNTER_THRES_VALUE   // 10
#define PM_MAX_THRES_ICMPTTLER_15M      PM_NO_TCA_COUNTER_THRES_VALUE   // 4
#define PM_MAX_THRES_IPADDER_15M        PM_NO_TCA_COUNTER_THRES_VALUE   // 10
#define PM_MAX_THRES_IPDISCR_15M        PM_NO_TCA_COUNTER_THRES_VALUE   // 25
#define PM_MAX_THRES_IPDISCT_15M        PM_NO_TCA_COUNTER_THRES_VALUE   // 25
#define PM_MAX_THRES_IPHDRR_15M         PM_NO_TCA_COUNTER_THRES_VALUE   // 25
#define PM_MAX_THRES_IPNOROUTEST_15M    PM_NO_TCA_COUNTER_THRES_VALUE   // 4

// PM Max threshold values for EON parameters for 1 Day.
#define PM_MAX_THRES_ICMPDUR_DAY        PM_NO_TCA_COUNTER_THRES_VALUE   // 100
#define PM_MAX_THRES_ICMPDUT_DAY        PM_NO_TCA_COUNTER_THRES_VALUE   // 100
#define PM_MAX_THRES_ICMPER_DAY         PM_NO_TCA_COUNTER_THRES_VALUE   // 100
#define PM_MAX_THRES_ICMPTTLER_DAY      PM_NO_TCA_COUNTER_THRES_VALUE   // 40
#define PM_MAX_THRES_IPADDER_DAY        PM_NO_TCA_COUNTER_THRES_VALUE   // 100
#define PM_MAX_THRES_IPDISCR_DAY        PM_NO_TCA_COUNTER_THRES_VALUE   // 250
#define PM_MAX_THRES_IPDISCT_DAY        PM_NO_TCA_COUNTER_THRES_VALUE   // 250
#define PM_MAX_THRES_IPHDRR_DAY         PM_NO_TCA_COUNTER_THRES_VALUE   // 250
#define PM_MAX_THRES_IPNOROUTEST_DAY    PM_NO_TCA_COUNTER_THRES_VALUE   // 40

// PM Max threshold values for OTU (FEC) parameters for 15 m.
#define PM_MAX_THRES_BE_15M             PM_NO_TCA_COUNTER_THRES_VALUE   // 875
#define PM_MAX_THRES_UBE_15M            PM_NO_TCA_COUNTER_THRES_VALUE   // 875

// PM Max threshold values for OTU (FEC) parameters for 1 Day.
#define PM_MAX_THRES_BE_DAY             PM_NO_TCA_COUNTER_THRES_VALUE   // 84000
#define PM_MAX_THRES_UBE_DAY            PM_NO_TCA_COUNTER_THRES_VALUE   // 84000

// PM Max threshold values for ODU layer parameters for 15m.
#define PM_MAX_THRES_CV_15M_ODU         PM_NO_TCA_COUNTER_THRES_VALUE   

// PM Max threshold values for ODU layer parameters for 1 Day.
#define PM_MAX_THRES_CV_DAY_ODU          PM_NO_TCA_COUNTER_THRES_VALUE

// PM Max threshold values for TCM layer parameters for 15m.
#define PM_MAX_THRES_CV_15M_TCM         PM_NO_TCA_COUNTER_THRES_VALUE   

// PM Max threshold values for TCM layer parameters for 1 Day.
#define PM_MAX_THRES_CV_DAY_TCM          PM_NO_TCA_COUNTER_THRES_VALUE      

#define PM_LOW_MIN_THRES_DELAY_VALUE     -PM_NO_TCA_GAUGE_THRES_VALUE
#define PM_HIGH_MAX_THRES_DELAY_VALUE    PM_NO_TCA_GAUGE_THRES_VALUE



// PM collector interval in second.
#define PM_COLLECT_INTERVAL_SEC         1

// PM TRN/OSC SPECIFIC
#define PM_NUMBER_OF_15M_HISTORICAL_DATA_ON_NON_APM     1
#define PM_NUMBER_OF_DAY_HISTORICAL_DATA_ON_NON_APM     1

// PM max time change.
#define PM_MAX_TIME_CHANGE_SEC          10

// PM refresh rate for end of period detection.
#define PM_END_OF_PERIOD_REFRESH_SEC    30

// PM soaking time before storage after end-of-period.
#define PM_STORAGE_SOAKING_TIME_SEC     360         // 6 minutes

// PM soaking of TCA unfiltered for first stage filtering (failures of 2.5 seconds soaking).
#define PM_TCA_SOAKING_FIRST_STAGE_TIME_SEC         8

// PM soaking of TCA unfiltered for second stage filtering (failures of 90 seconds soaking).
#define PM_TCA_SOAKING_SECOND_STAGE_TIME_SEC        95

// PM Maximum number of parameters supported by an entity.
#define PM_MAX_NUMBER_OF_PARAMETERS     16

#define PM_OPT_STRING   "Optical"
#define PM_OMS_STRING   "Optical Multiplex Section"
#define PM_COP_STRING   "Optical Channel"
#define PM_OTU_STRING   "Optical Transport Unit"
#define PM_LASER_STRING "Laser"
#define PM_DATA_STRING  "Data"
#define PM_EON_STRING   "Eon"
#define PM_MS_NE_STRING  "MsNearEnd"
#define PM_HOP_NE_STRING "HopNearEnd"
#define PM_MS_FE_STRING  "MsFarEnd"
#define PM_HOP_FE_STRING "HopFarEnd"
#define PM_GFP_STRING    "Gfp"
#define PM_RMON_STRING   "Rmon"
#define PM_ODU_STRING   "Optical Data Unit"
#define PM_TCM_STRING   "Tandem Connection Monitoring"


#define PM_PORT_SIDE_STRING "Port"
#define PM_LINE_SIDE_STRING "Line"

//Used when resetting counters or gauges.
//##ModelId=3C9255A301F1
typedef uint8  PM_ResetCounter;

//Gets the start time of the current accumulation period 
//based on the system time.
FC_Time PM_GetAccumulationPeriod(CT_PM_Period thePeriod, FC_Time theCurrentTime, time_t thePstOffset);

// Maps the PM side argument to a simple CT_PM_PORT_SIDE or CT_PM_LINE_SIDE value
CT_PM_Side PM_GetGenericSide( CT_PM_Side thePmSide );


#endif  //PM_DEF_H
