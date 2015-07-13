/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   PM blackboard region keys definition.
--------------------------------------------------------------------------*/

#include <Blackboard/FC_BbKey.h>
#include "../PM_RegionKeyDefinition.h"
#include <ErrorService/FC_Error.h>

// FTP Configuration for the PMXfer on SPM 
FC_BbKey PM_XFER_FTP_CFG                         ("PM_XFER_FTP_CFG");

// Configuration of the X values.
FC_BbKey PM_GENERAL_CFG                          ("PM_GENERAL_CFG");
FC_BbKey PM_END_OF_PERIOD                        ("PM_END_OF_PERIOD");

//---------------------------------------------------------------------------
// PM KEY FOR DATA LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_DATA_DEFECT                               ("PM_DATA_DEFECT");
FC_BbKey PM_DATA_COUNTER                              ("PM_DATA_COUNTER");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_DATA_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_DATA_CONFIG_15M"),
                                                        ("PM_DATA_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_DATA_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_DATA_VALUE_15M_CURRENT"),
                                                         ("PM_DATA_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_DATA_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_DATA_VALUE_15M_PREVIOUS"),
                                                         ("PM_DATA_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_DATA_REQUEST                                 ("PM_DATA_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR NEAR-END SONET/SDH MS LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_MS_NE_DEFECT                               ("PM_MS_NE_DEFECT");
FC_BbKey PM_MS_NE_FAILURE                              ("PM_MS_NE_FAILURE");
FC_BbKey PM_MS_NE_COUNTER                              ("PM_MS_NE_COUNTER");
FC_BbKey PM_MS_NE_STATUS                               ("PM_MS_NE_STATUS");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_MS_NE_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_MS_NE_CONFIG_15M"),
                                                        ("PM_MS_NE_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_MS_NE_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_MS_NE_VALUE_15M_CURRENT"),
                                                         ("PM_MS_NE_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_MS_NE_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_MS_NE_VALUE_15M_PREVIOUS"),
                                                         ("PM_MS_NE_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_MS_NE_REQUEST                                 ("PM_MS_NE_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR FAR-END SONET/SDH MS LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_MS_FE_DEFECT                               ("PM_MS_FE_DEFECT");
FC_BbKey PM_MS_FE_FAILURE                              ("PM_MS_FE_FAILURE");
FC_BbKey PM_MS_FE_COUNTER                              ("PM_MS_FE_COUNTER");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_MS_FE_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_MS_FE_CONFIG_15M"),
                                                        ("PM_MS_FE_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_MS_FE_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_MS_FE_VALUE_15M_CURRENT"),
                                                         ("PM_MS_FE_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_MS_FE_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_MS_FE_VALUE_15M_PREVIOUS"),
                                                         ("PM_MS_FE_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_MS_FE_REQUEST                                 ("PM_MS_FE_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR NEAR-END SONET/SDH HOP LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_HOP_NE_DEFECT                               ("PM_HOP_NE_DEFECT");
FC_BbKey PM_HOP_NE_FAILURE                              ("PM_HOP_NE_FAILURE");
FC_BbKey PM_HOP_NE_COUNTER                              ("PM_HOP_NE_COUNTER");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_HOP_NE_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_HOP_NE_CONFIG_15M"),
                                                        ("PM_HOP_NE_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_HOP_NE_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_HOP_NE_VALUE_15M_CURRENT"),
                                                         ("PM_HOP_NE_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_HOP_NE_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_HOP_NE_VALUE_15M_PREVIOUS"),
                                                         ("PM_HOP_NE_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_HOP_NE_REQUEST                                 ("PM_HOP_NE_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR FAR-END SONET/SDH HOP LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_HOP_FE_DEFECT                               ("PM_HOP_FE_DEFECT");
FC_BbKey PM_HOP_FE_FAILURE                              ("PM_HOP_FE_FAILURE");
FC_BbKey PM_HOP_FE_COUNTER                              ("PM_HOP_FE_COUNTER");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_HOP_FE_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_HOP_FE_CONFIG_15M"),
                                                        ("PM_HOP_FE_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_HOP_FE_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_HOP_FE_VALUE_15M_CURRENT"),
                                                         ("PM_HOP_FE_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_HOP_FE_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_HOP_FE_VALUE_15M_PREVIOUS"),
                                                         ("PM_HOP_FE_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_HOP_FE_REQUEST                                 ("PM_HOP_FE_REQUEST");



//---------------------------------------------------------------------------
// PM KEY FOR NEAR-END SONET/SDH MS LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_GFP_DEFECT                               ("PM_GFP_DEFECT");
FC_BbKey PM_GFP_COUNTER                              ("PM_GFP_COUNTER");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_GFP_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_GFP_CONFIG_15M"),
                                                        ("PM_GFP_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_GFP_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_GFP_VALUE_15M_CURRENT"),
                                                         ("PM_GFP_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_GFP_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_GFP_VALUE_15M_PREVIOUS"),
                                                         ("PM_GFP_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_GFP_REQUEST                                 ("PM_GFP_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR RMON LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_RMON_DEFECT                               ("PM_RMON_DEFECT");
FC_BbKey PM_RMON_COUNTER                              ("PM_RMON_COUNTER");
FC_BbKey PM_RMON_STATUS                               ("PM_RMON_STATUS");


// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_RMON_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_RMON_CONFIG_15M"),
                                                        ("PM_RMON_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_RMON_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_RMON_VALUE_15M_CURRENT"),
                                                         ("PM_RMON_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_RMON_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_RMON_VALUE_15M_PREVIOUS"),
                                                         ("PM_RMON_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_RMON_REQUEST                                 ("PM_RMON_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR OTU LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_OTU_DEFECT                               ("PM_OTU_DEFECT");
FC_BbKey PM_OTU_COUNTER                              ("PM_OTU_COUNTER");
FC_BbKey PM_OTU_STATUS                               ("PM_OTU_STATUS");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_OTU_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_OTU_CONFIG_15M"),
                                                        ("PM_OTU_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_OTU_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_OTU_VALUE_15M_CURRENT"),
                                                         ("PM_OTU_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_OTU_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_OTU_VALUE_15M_PREVIOUS"),
                                                         ("PM_OTU_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_OTU_REQUEST                                 ("PM_OTU_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR ODU LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_ODU_DEFECT                               ("PM_ODU_DEFECT");
FC_BbKey PM_ODU_COUNTER                              ("PM_ODU_COUNTER");
FC_BbKey PM_ODU_STATUS                               ("PM_ODU_STATUS");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_ODU_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_ODU_CONFIG_15M"),
                                                        ("PM_ODU_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_ODU_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_ODU_VALUE_15M_CURRENT"),
                                                         ("PM_ODU_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_ODU_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_ODU_VALUE_15M_PREVIOUS"),
                                                         ("PM_ODU_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_ODU_REQUEST                                 ("PM_ODU_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR TCM LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_TCM_DEFECT                               ("PM_TCM_DEFECT");
FC_BbKey PM_TCM_COUNTER                              ("PM_TCM_COUNTER");
FC_BbKey PM_TCM_STATUS                               ("PM_TCM_STATUS");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_TCM_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_TCM_CONFIG_15M"),
                                                       ("PM_TCM_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_TCM_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_TCM_VALUE_15M_CURRENT"),
                                                        ("PM_TCM_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_TCM_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_TCM_VALUE_15M_PREVIOUS"),
                                                        ("PM_TCM_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_TCM_REQUEST                                 ("PM_TCM_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR OPTICAL POWER.
//---------------------------------------------------------------------------

// COLLECTOR KEY DEFINITION
FC_BbKey PM_OPT_STATUS                  ("PM_OPT_STATUS");
FC_BbKey PM_OPT_DEFECT                  ("PM_OPT_DEFECT");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_OPT_CONFIG[CT_PM_PERIOD_UNKNOWN] = {("PM_OPT_CONFIG_15M"),
                                                ("PM_OPT_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_OPT_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = {("PM_OPT_VALUE_15M_CURRENT"),
                                                       ("PM_OPT_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_OPT_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] = {("PM_OPT_VALUE_15M_PREVIOUS"),
                                                        ("PM_OPT_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_OPT_REQUEST                  ("PM_OPT_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR OMS POWER.
//---------------------------------------------------------------------------

// COLLECTOR KEY DEFINITION
FC_BbKey PM_OMS_STATUS                  ("PM_OMS_STATUS");
FC_BbKey PM_OMS_DEFECT                  ("PM_OMS_DEFECT");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_OMS_CONFIG[CT_PM_PERIOD_UNKNOWN] = {("PM_OMS_CONFIG_15M"),
                                                ("PM_OMS_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_OMS_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = {("PM_OMS_VALUE_15M_CURRENT"),
                                                       ("PM_OMS_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_OMS_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] = {("PM_OMS_VALUE_15M_PREVIOUS"),
                                                        ("PM_OMS_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_OMS_REQUEST                  ("PM_OMS_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR LASER
//---------------------------------------------------------------------------

// COLLECTOR KEY DEFINITION
FC_BbKey PM_LASER_STATUS                  ("PM_LASER_STATUS");

// PROCESSOR KEY DEFINITION
// Configuration of signal reset and inhibition.
FC_BbKey PM_LASER_CONFIG[CT_PM_PERIOD_UNKNOWN] = {("PM_LASER_CONFIG_15M"),
                                                  ("PM_LASER_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_LASER_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = {("PM_LASER_VALUE_15M_CURRENT"),
                                                         ("PM_LASER_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_LASER_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] = {("PM_LASER_VALUE_15M_PREVIOUS"),
                                                          ("PM_LASER_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_LASER_REQUEST                  ("PM_LASER_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR CHANNEL OPTICAL POWER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION
FC_BbKey PM_COP_STATUS                  ("PM_COP_STATUS");
FC_BbKey PM_COP_DEFECT                  ("PM_COP_DEFECT");

// PROCESSOR KEY DEFINITION
// Configuration of signal reset and inhibition.
FC_BbKey PM_COP_CONFIG[CT_PM_PERIOD_UNKNOWN] = {("PM_COP_CONFIG_15M"),
                                                ("PM_COP_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_COP_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = {("PM_COP_VALUE_15M_CURRENT"),
                                                       ("PM_COP_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_COP_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] = {("PM_COP_VALUE_15M_PREVIOUS"),
                                                        ("PM_COP_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_COP_REQUEST                  ("PM_COP_REQUEST");

// Invalid key definition.
FC_BbKey PM_INVALID_BB_KEY               ("PM_INVALID_BB_KEY");

//---------------------------------------------------------------------------
// PM KEY FOR EON LAYER
//---------------------------------------------------------------------------
// COLLECTOR KEY DEFINITION

FC_BbKey PM_EON_COUNTER                              ("PM_EON_COUNTER");

// PROCESSOR KEY DEFINITION

// Configuration of signal reset and inhibition.
FC_BbKey PM_EON_CONFIG[CT_PM_PERIOD_UNKNOWN] =       { ("PM_EON_CONFIG_15M"),
                                                       ("PM_EON_CONFIG_DAY")};

// Current Value, IDF and TCA of signal parameter.
FC_BbKey PM_EON_VALUE_CURRENT[CT_PM_PERIOD_UNKNOWN] = { ("PM_EON_VALUE_15M_CURRENT"),
                                                        ("PM_EON_VALUE_DAY_CURRENT")};

// Previous Value, IDF and TCA of signal parameter.
FC_BbKey PM_EON_VALUE_PREVIOUS[CT_PM_PERIOD_UNKNOWN] ={ ("PM_EON_VALUE_15M_PREVIOUS"),
                                                        ("PM_EON_VALUE_DAY_PREVIOUS")};

// Used to perform get request delayed operation.
FC_BbKey PM_EON_REQUEST                                 ("PM_EON_REQUEST");

//---------------------------------------------------------------------------
// PM KEY FOR HISTORICAL DATA
//---------------------------------------------------------------------------
//
FC_BbKey PM_FILE_LATEST_PERIOD_READY                    ("PM_FILE_LATEST_PERIOD_READY");

FC_BbKey PM_CARD_FILE_READY                         ("PM_CARD_FILE_READY");

// Used to store all 15 minutes historical data for Amplifier on OS1
FC_BbKey PM_AMP_OS1_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_AMP_OS1_15M_0_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_1_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_2_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_3_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_4_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_5_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_6_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_7_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_8_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_9_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_10_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_11_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_12_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_13_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_14_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_15_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_16_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_17_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_18_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_19_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_20_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_21_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_22_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_23_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_24_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_25_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_26_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_27_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_28_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_29_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_30_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_31_HISTORICAL"),
                                                                        ("PM_AMP_OS1_15M_32_HISTORICAL")};

// Used to store all day historical data for Amplifier on OS1
FC_BbKey PM_AMP_OS1_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_AMP_OS1_DAY_0_HISTORICAL"),
                                                                        ("PM_AMP_OS1_DAY_1_HISTORICAL"),
                                                                        ("PM_AMP_OS1_DAY_2_HISTORICAL"),
                                                                        ("PM_AMP_OS1_DAY_3_HISTORICAL"),
                                                                        ("PM_AMP_OS1_DAY_4_HISTORICAL"),
                                                                        ("PM_AMP_OS1_DAY_5_HISTORICAL"),
                                                                        ("PM_AMP_OS1_DAY_6_HISTORICAL"),
                                                                        ("PM_AMP_OS1_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for Amplifier on OS2
FC_BbKey PM_AMP_OS2_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_AMP_OS2_15M_0_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_1_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_2_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_3_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_4_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_5_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_6_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_7_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_8_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_9_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_10_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_11_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_12_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_13_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_14_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_15_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_16_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_17_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_18_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_19_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_20_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_21_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_22_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_23_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_24_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_25_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_26_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_27_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_28_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_29_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_30_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_31_HISTORICAL"),
                                                                        ("PM_AMP_OS2_15M_32_HISTORICAL")};

// Used to store all day historical data for Amplifier on OS2
FC_BbKey PM_AMP_OS2_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_AMP_OS2_DAY_0_HISTORICAL"),
                                                                        ("PM_AMP_OS2_DAY_1_HISTORICAL"),
                                                                        ("PM_AMP_OS2_DAY_2_HISTORICAL"),
                                                                        ("PM_AMP_OS2_DAY_3_HISTORICAL"),
                                                                        ("PM_AMP_OS2_DAY_4_HISTORICAL"),
                                                                        ("PM_AMP_OS2_DAY_5_HISTORICAL"),
                                                                        ("PM_AMP_OS2_DAY_6_HISTORICAL"),
                                                                        ("PM_AMP_OS2_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for OSC on OS1
FC_BbKey PM_OSC_OS1_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_OSC_OS1_15M_0_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_1_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_2_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_3_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_4_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_5_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_6_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_7_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_8_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_9_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_10_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_11_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_12_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_13_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_14_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_15_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_16_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_17_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_18_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_19_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_20_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_21_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_22_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_23_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_24_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_25_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_26_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_27_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_28_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_29_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_30_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_31_HISTORICAL"),
                                                                        ("PM_OSC_OS1_15M_32_HISTORICAL")};

// Used to store all day historical data for OSC on OS1
FC_BbKey PM_OSC_OS1_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_OSC_OS1_DAY_0_HISTORICAL"),
                                                                        ("PM_OSC_OS1_DAY_1_HISTORICAL"),
                                                                        ("PM_OSC_OS1_DAY_2_HISTORICAL"),
                                                                        ("PM_OSC_OS1_DAY_3_HISTORICAL"),
                                                                        ("PM_OSC_OS1_DAY_4_HISTORICAL"),
                                                                        ("PM_OSC_OS1_DAY_5_HISTORICAL"),
                                                                        ("PM_OSC_OS1_DAY_6_HISTORICAL"),
                                                                        ("PM_OSC_OS1_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for OSC on OS2
FC_BbKey PM_OSC_OS2_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_OSC_OS2_15M_0_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_1_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_2_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_3_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_4_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_5_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_6_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_7_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_8_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_9_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_10_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_11_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_12_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_13_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_14_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_15_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_16_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_17_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_18_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_19_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_20_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_21_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_22_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_23_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_24_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_25_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_26_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_27_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_28_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_29_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_30_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_31_HISTORICAL"),
                                                                        ("PM_OSC_OS2_15M_32_HISTORICAL")};

// Used to store all day historical data for OSC on OS2
FC_BbKey PM_OSC_OS2_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_OSC_OS2_DAY_0_HISTORICAL"),
                                                                        ("PM_OSC_OS2_DAY_1_HISTORICAL"),
                                                                        ("PM_OSC_OS2_DAY_2_HISTORICAL"),
                                                                        ("PM_OSC_OS2_DAY_3_HISTORICAL"),
                                                                        ("PM_OSC_OS2_DAY_4_HISTORICAL"),
                                                                        ("PM_OSC_OS2_DAY_5_HISTORICAL"),
                                                                        ("PM_OSC_OS2_DAY_6_HISTORICAL"),
                                                                        ("PM_OSC_OS2_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for MUX on OS1
FC_BbKey PM_MUX_OS1_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_MUX_OS1_15M_0_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_1_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_2_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_3_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_4_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_5_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_6_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_7_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_8_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_9_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_10_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_11_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_12_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_13_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_14_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_15_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_16_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_17_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_18_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_19_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_20_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_21_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_22_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_23_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_24_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_25_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_26_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_27_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_28_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_29_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_30_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_31_HISTORICAL"),
                                                                        ("PM_MUX_OS1_15M_32_HISTORICAL")};

// Used to store all day historical data for MUX on OS1
FC_BbKey PM_MUX_OS1_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_MUX_OS1_DAY_0_HISTORICAL"),
                                                                        ("PM_MUX_OS1_DAY_1_HISTORICAL"),
                                                                        ("PM_MUX_OS1_DAY_2_HISTORICAL"),
                                                                        ("PM_MUX_OS1_DAY_3_HISTORICAL"),
                                                                        ("PM_MUX_OS1_DAY_4_HISTORICAL"),
                                                                        ("PM_MUX_OS1_DAY_5_HISTORICAL"),
                                                                        ("PM_MUX_OS1_DAY_6_HISTORICAL"),
                                                                        ("PM_MUX_OS1_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for MUX on OS2
FC_BbKey PM_MUX_OS2_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_MUX_OS2_15M_0_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_1_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_2_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_3_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_4_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_5_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_6_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_7_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_8_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_9_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_10_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_11_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_12_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_13_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_14_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_15_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_16_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_17_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_18_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_19_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_20_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_21_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_22_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_23_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_24_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_25_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_26_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_27_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_28_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_29_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_30_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_31_HISTORICAL"),
                                                                        ("PM_MUX_OS2_15M_32_HISTORICAL")};

// Used to store all day historical data for MUX on OS2
FC_BbKey PM_MUX_OS2_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_MUX_OS2_DAY_0_HISTORICAL"),
                                                                        ("PM_MUX_OS2_DAY_1_HISTORICAL"),
                                                                        ("PM_MUX_OS2_DAY_2_HISTORICAL"),
                                                                        ("PM_MUX_OS2_DAY_3_HISTORICAL"),
                                                                        ("PM_MUX_OS2_DAY_4_HISTORICAL"),
                                                                        ("PM_MUX_OS2_DAY_5_HISTORICAL"),
                                                                        ("PM_MUX_OS2_DAY_6_HISTORICAL"),
                                                                        ("PM_MUX_OS2_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for OLIM on OS1
FC_BbKey PM_OLIM_OS1_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_OLIM_OS1_15M_0_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_1_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_2_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_3_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_4_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_5_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_6_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_7_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_8_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_9_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_10_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_11_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_12_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_13_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_14_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_15_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_16_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_17_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_18_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_19_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_20_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_21_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_22_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_23_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_24_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_25_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_26_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_27_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_28_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_29_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_30_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_31_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_15M_32_HISTORICAL")};


// Used to store all day historical data for OLIM on OS1
FC_BbKey PM_OLIM_OS1_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_OLIM_OS1_DAY_0_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_DAY_1_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_DAY_2_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_DAY_3_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_DAY_4_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_DAY_5_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_DAY_6_HISTORICAL"),
                                                                         ("PM_OLIM_OS1_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for OLIM on OS2
FC_BbKey PM_OLIM_OS2_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_OLIM_OS2_15M_0_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_1_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_2_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_3_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_4_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_5_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_6_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_7_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_8_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_9_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_10_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_11_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_12_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_13_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_14_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_15_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_16_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_17_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_18_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_19_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_20_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_21_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_22_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_23_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_24_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_25_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_26_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_27_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_28_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_29_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_30_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_31_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_15M_32_HISTORICAL")};


// Used to store all day historical data for OLIM on OS2
FC_BbKey PM_OLIM_OS2_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_OLIM_OS2_DAY_0_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_DAY_1_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_DAY_2_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_DAY_3_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_DAY_4_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_DAY_5_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_DAY_6_HISTORICAL"),
                                                                         ("PM_OLIM_OS2_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for RCMM on OS1
FC_BbKey PM_RCMM_OS1_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_RCMM_OS1_15M_0_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_1_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_2_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_3_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_4_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_5_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_6_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_7_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_8_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_9_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_10_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_11_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_12_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_13_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_14_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_15_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_16_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_17_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_18_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_19_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_20_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_21_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_22_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_23_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_24_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_25_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_26_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_27_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_28_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_29_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_30_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_31_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_15M_32_HISTORICAL")};

// Used to store all day historical data for RCMM on OS1
FC_BbKey PM_RCMM_OS1_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_RCMM_OS1_DAY_0_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_DAY_1_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_DAY_2_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_DAY_3_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_DAY_4_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_DAY_5_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_DAY_6_HISTORICAL"),
                                                                        ("PM_RCMM_OS1_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for RCMM on OS2
FC_BbKey PM_RCMM_OS2_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_RCMM_OS2_15M_0_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_1_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_2_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_3_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_4_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_5_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_6_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_7_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_8_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_9_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_10_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_11_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_12_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_13_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_14_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_15_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_16_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_17_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_18_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_19_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_20_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_21_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_22_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_23_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_24_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_25_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_26_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_27_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_28_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_29_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_30_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_31_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_15M_32_HISTORICAL")};

// Used to store all day historical data for RCMM on OS2
FC_BbKey PM_RCMM_OS2_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_RCMM_OS2_DAY_0_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_DAY_1_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_DAY_2_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_DAY_3_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_DAY_4_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_DAY_5_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_DAY_6_HISTORICAL"),
                                                                        ("PM_RCMM_OS2_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN OS1
FC_BbKey PM_TRN_RAM_OS1_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_OS1_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN OS1
FC_BbKey PM_TRN_RAM_OS1_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_OS1_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_OS1_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS1
FC_BbKey PM_TRN_RAM_PS1_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS1_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS1
FC_BbKey PM_TRN_RAM_PS1_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS1_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS1_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS2
FC_BbKey PM_TRN_RAM_PS2_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS2_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS2
FC_BbKey PM_TRN_RAM_PS2_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS2_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS2_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS3
FC_BbKey PM_TRN_RAM_PS3_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS3_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS3
FC_BbKey PM_TRN_RAM_PS3_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS3_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS3_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS4
FC_BbKey PM_TRN_RAM_PS4_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS4_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS4
FC_BbKey PM_TRN_RAM_PS4_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS4_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS4_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS5
FC_BbKey PM_TRN_RAM_PS5_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS5_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS5
FC_BbKey PM_TRN_RAM_PS5_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS5_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS5_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS6
FC_BbKey PM_TRN_RAM_PS6_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS6_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS6
FC_BbKey PM_TRN_RAM_PS6_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS6_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS6_DAY_7_HISTORICAL")};



// Used to store all 15 minutes historical data for TRN PS7
FC_BbKey PM_TRN_RAM_PS7_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS7_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS7
FC_BbKey PM_TRN_RAM_PS7_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS7_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS7_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS8
FC_BbKey PM_TRN_RAM_PS8_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS8_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS8
FC_BbKey PM_TRN_RAM_PS8_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS8_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS8_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS9
FC_BbKey PM_TRN_RAM_PS9_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS9_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS9
FC_BbKey PM_TRN_RAM_PS9_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS9_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS9_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS10
FC_BbKey PM_TRN_RAM_PS10_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS10_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS10
FC_BbKey PM_TRN_RAM_PS10_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS10_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS10_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS11
FC_BbKey PM_TRN_RAM_PS11_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS11_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS11
FC_BbKey PM_TRN_RAM_PS11_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS11_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS11_DAY_7_HISTORICAL")};


// Used to store all 15 minutes historical data for TRN PS12
FC_BbKey PM_TRN_RAM_PS12_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS12_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS12
FC_BbKey PM_TRN_RAM_PS12_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS12_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS12_DAY_7_HISTORICAL")};

// Used to store all 15 minutes historical data for TRN PS13
FC_BbKey PM_TRN_RAM_PS13_15M_HISTORICAL[CT_PM_NUMBER_OF_15M_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS13_15M_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_7_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_8_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_9_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_10_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_11_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_12_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_13_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_14_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_15_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_16_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_17_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_18_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_19_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_20_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_21_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_22_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_23_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_24_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_25_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_26_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_27_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_28_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_29_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_30_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_31_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_15M_32_HISTORICAL")};

// Used to store all day historical data for TRN PS13
FC_BbKey PM_TRN_RAM_PS13_DAY_HISTORICAL[CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA] = { ("PM_TRN_RAM_PS13_DAY_0_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_DAY_1_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_DAY_2_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_DAY_3_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_DAY_4_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_DAY_5_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_DAY_6_HISTORICAL"),
                                                                                ("PM_TRN_RAM_PS13_DAY_7_HISTORICAL")};


// Used to reset historical data.
FC_BbKey PM_AMP_OS1_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_AMP_OS1_CONFIG_15M_HISTORICAL"),
                                                               ("PM_AMP_OS1_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_AMP_OS2_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_AMP_OS2_CONFIG_15M_HISTORICAL"),
                                                               ("PM_AMP_OS2_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_OSC_OS1_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_OSC_OS1_CONFIG_15M_HISTORICAL"),
                                                               ("PM_OSC_OS1_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_OSC_OS2_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_OSC_OS2_CONFIG_15M_HISTORICAL"),
                                                               ("PM_OSC_OS2_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_MUX_OS1_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_MUX_OS1_CONFIG_15M_HISTORICAL"),
                                                               ("PM_MUX_OS1_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_MUX_OS2_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_MUX_OS2_CONFIG_15M_HISTORICAL"),
                                                               ("PM_MUX_OS2_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_RCMM_OS1_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_RCMM_OS1_CONFIG_15M_HISTORICAL"),
                                                                ("PM_RCMM_OS1_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_RCMM_OS2_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_RCMM_OS2_CONFIG_15M_HISTORICAL"),
                                                                ("PM_RCMM_OS2_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_OLIM_OS1_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_OLIM_OS1_CONFIG_15M_HISTORICAL"),
                                                                ("PM_OLIM_OS1_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_OLIM_OS2_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_OLIM_OS2_CONFIG_15M_HISTORICAL"),
                                                                ("PM_OLIM_OS2_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_OS1_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_OS1_CONFIG_15M_HISTORICAL"),
                                                                   ("PM_TRN_RAM_SMTM_OS1_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS1_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS1_CONFIG_15M_HISTORICAL"),
                                                                   ("PM_TRN_RAM_SMTM_PS1_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS2_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS2_CONFIG_15M_HISTORICAL"),
                                                                   ("PM_TRN_RAM_SMTM_PS2_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS3_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS3_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS3_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS4_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS4_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS4_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS5_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS5_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS5_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS6_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS6_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS6_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS7_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS7_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS7_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS8_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS8_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS8_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS9_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS9_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS9_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS10_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS10_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS10_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS11_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS11_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS11_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS12_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS12_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS12_CONFIG_DAY_HISTORICAL")};

FC_BbKey PM_TRN_RAM_PS13_CONFIG_HISTORICAL[CT_PM_PERIOD_UNKNOWN] = {("PM_TRN_RAM_SMTM_PS13_CONFIG_15M_HISTORICAL"),
                                                               ("PM_TRN_RAM_SMTM_PS13_CONFIG_DAY_HISTORICAL")};


// Table of PM AMP 15 minute historical data arrays
FC_BbKey* PM_AMP_OS_15M_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_AMP_OS1_15M_HISTORICAL,
                                                                PM_AMP_OS2_15M_HISTORICAL };

// Table of PM AMP Day historical data arrays
FC_BbKey* PM_AMP_OS_DAY_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_AMP_OS1_DAY_HISTORICAL,
                                                                PM_AMP_OS2_DAY_HISTORICAL };

// Table of PM AMP historical configuration arrays
FC_BbKey* PM_AMP_OS_CONFIG_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_AMP_OS1_CONFIG_HISTORICAL,
                                                                    PM_AMP_OS2_CONFIG_HISTORICAL };


// Table of PM OSC 15 minute historical data arrays
FC_BbKey* PM_OSC_OS_15M_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_OSC_OS1_15M_HISTORICAL,
                                                                PM_OSC_OS2_15M_HISTORICAL };

// Table of PM OSC Day historical data arrays
FC_BbKey* PM_OSC_OS_DAY_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_OSC_OS1_DAY_HISTORICAL,
                                                                PM_OSC_OS2_DAY_HISTORICAL };

// Table of PM OSC historical configuration arrays
FC_BbKey* PM_OSC_OS_CONFIG_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_OSC_OS1_CONFIG_HISTORICAL,
                                                                   PM_OSC_OS2_CONFIG_HISTORICAL };


// Table of PM MUX 15 minute historical data arrays
FC_BbKey* PM_MUX_OS_15M_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_MUX_OS1_15M_HISTORICAL,
                                                                PM_MUX_OS2_15M_HISTORICAL };

// Table of PM MUX Day historical data arrays
FC_BbKey* PM_MUX_OS_DAY_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_MUX_OS1_DAY_HISTORICAL,
                                                                PM_MUX_OS2_DAY_HISTORICAL };

// Table of PM MUX historical configuration arrays
FC_BbKey* PM_MUX_OS_CONFIG_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_MUX_OS1_CONFIG_HISTORICAL,
                                                                   PM_MUX_OS2_CONFIG_HISTORICAL };


// Table of PM RCMM 15 minute historical data arrays
FC_BbKey* PM_RCMM_OS_15M_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_RCMM_OS1_15M_HISTORICAL,
                                                                 PM_RCMM_OS2_15M_HISTORICAL };

// Table of PM RCMM Day historical data arrays
FC_BbKey* PM_RCMM_OS_DAY_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_RCMM_OS1_DAY_HISTORICAL,
                                                                 PM_RCMM_OS2_DAY_HISTORICAL };

// Table of PM RCMM historical configuration arrays
FC_BbKey* PM_RCMM_OS_CONFIG_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_RCMM_OS1_CONFIG_HISTORICAL,
                                                                    PM_RCMM_OS2_CONFIG_HISTORICAL };


// Table of PM OLIM 15 minute historical data arrays
FC_BbKey* PM_OLIM_OS_15M_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_OLIM_OS1_15M_HISTORICAL,
                                                                 PM_OLIM_OS2_15M_HISTORICAL };

// Table of PM OLIM Day historical data arrays
FC_BbKey* PM_OLIM_OS_DAY_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_OLIM_OS1_DAY_HISTORICAL,
                                                                 PM_OLIM_OS2_DAY_HISTORICAL };

// Table of PM OLIM historical configuration arrays
FC_BbKey* PM_OLIM_OS_CONFIG_HISTORICAL[NUMBER_OF_OPTICAL_SHELF] = { PM_OLIM_OS1_CONFIG_HISTORICAL,
                                                                    PM_OLIM_OS2_CONFIG_HISTORICAL };


// Table of PM TRN_RAM 15 minute historical data arrays
FC_BbKey* PM_TRN_RAM_PS_15M_HISTORICAL[NUMBER_OF_PORT_SHELF] = { PM_TRN_RAM_PS1_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS2_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS3_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS4_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS5_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS6_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS7_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS8_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS9_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS10_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS11_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS12_15M_HISTORICAL,
                                                                 PM_TRN_RAM_PS13_15M_HISTORICAL };

// Table of PM TRN_RAM Day historical data arrays
FC_BbKey* PM_TRN_RAM_PS_DAY_HISTORICAL[NUMBER_OF_PORT_SHELF] = { PM_TRN_RAM_PS1_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS2_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS3_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS4_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS5_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS6_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS7_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS8_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS9_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS10_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS11_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS12_DAY_HISTORICAL,
                                                                 PM_TRN_RAM_PS13_DAY_HISTORICAL };

// Table of PM TRN_RAM historical configuration arrays
FC_BbKey* PM_TRN_RAM_PS_CONFIG_HISTORICAL[NUMBER_OF_PORT_SHELF] = { PM_TRN_RAM_PS1_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS2_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS3_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS4_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS5_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS6_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS7_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS8_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS9_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS10_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS11_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS12_CONFIG_HISTORICAL,
                                                                    PM_TRN_RAM_PS13_CONFIG_HISTORICAL };


const string PM_KeySideTable[] =
{
    "_PORT",
    "_PORT_0",
    "_PORT_1",
    "_PORT_2",
    "_PORT_3",
    "_PORT_4",
    "_PORT_5",
    "_PORT_6",
    "_PORT_7",
    "_PORT_8",
    "_PORT_9",
    "_PORT_10",
    "_PORT_11",
    "_PORT_12",
    "_PORT_13",
    "_PORT_14",
    "_PORT_15",
    "_PORT_16",
    "_PORT_17",
    "_PORT_18",
    "_PORT_19",
    "_PORT_20",
    "_PORT_21",
    "_PORT_22",
    "_PORT_23",
    "_PORT_24",
    "_PORT_25",
    "_PORT_26",
    "_PORT_27",
    "_PORT_28",
    "_PORT_29",
    "_PORT_30",
    "_PORT_31",
    "_PORT_32",
    "_PORT_33",
    "_PORT_34",
    "_PORT_35",
    "_PORT_36",
    "_PORT_37",
    "_PORT_38",
    "_PORT_39",
    "_PORT_40",
    "_PORT_41",
    "_PORT_42",
    "_PORT_43",
    "_PORT_44",
    "_PORT_45",
    "_PORT_46",
    "_PORT_47",
    "_PORT_48",
    "_PORT_49",
    "_PORT_50",
    "_PORT_51",
    "_PORT_52",
    "_PORT_53",
    "_PORT_54",
    "_PORT_55",
    "_PORT_56",
    "_PORT_57",
    "_PORT_58",
    "_PORT_59",
    "_PORT_60",
    "_PORT_61",
    "_PORT_62",
    "_PORT_63",
    "_PORT_64",
    "_PORT_65",
    "_PORT_66",
    "_PORT_67",
    "_PORT_68",
    "_PORT_69",
    "_PORT_70",
    "_PORT_71",
    "_PORT_72",
    "_PORT_73",
    "_PORT_74",
    "_PORT_75",
    "_PORT_76",
    "_PORT_77",
    "_PORT_78",
    "_PORT_79",
    "_PORT_80",
    "_PORT_81",
    "_PORT_82",
    "_PORT_83",
    "_PORT_84",
    "_PORT_85",
    "_PORT_86",
    "_PORT_87",
    "_PORT_88",
    "_LINE",
    "_LINE_0",
    "_LINE_1",
    "_LINE_2",
    "_LINE_3",
    "_LINE_4",
    "_LINE_5",
    "_LINE_6",
    "_LINE_7",
    "_LINE_8",
    "_LINE_9",
    "_A",
    "_B",
    "_C",
    "_D",
    "_E",
    "_F",
    "_G",
    "_H",
};

//---------------------------------------------------------------------------
FC_BbKey& PM_HISTORICAL_AMP(CT_PM_Period thePeriod, CT_PM_HistoryId theHistory, CT_ShelfId theShelf)
{
    switch( theShelf )
    {
    case OPTICAL_SHELF_1:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_AMP_OS1_15M_HISTORICAL[0];
            }
            else
            {
                return PM_AMP_OS1_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_AMP_OS1_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_AMP_OS1_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_AMP_OS1_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case OPTICAL_SHELF_2:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_AMP_OS2_15M_HISTORICAL[0];
            }
            else
            {
                return PM_AMP_OS2_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_AMP_OS2_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_AMP_OS2_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_AMP_OS2_15M_HISTORICAL[0];
            //break;
        }
        //break;

    default:
        FC_THROW_ERROR(FC_SWError, "PM: Shelf not supported!");
        return PM_AMP_OS1_15M_HISTORICAL[0];
        //break;
    }
}

//---------------------------------------------------------------------------
FC_BbKey& PM_HISTORICAL_OSC(CT_PM_Period thePeriod, CT_PM_HistoryId theHistory, CT_ShelfId theShelf)
{
    switch( theShelf )
    {
    case OPTICAL_SHELF_1:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OSC_OS1_15M_HISTORICAL[0];
            }
            else
            {
                return PM_OSC_OS1_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OSC_OS1_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_OSC_OS1_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_OSC_OS1_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case OPTICAL_SHELF_2:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OSC_OS2_15M_HISTORICAL[0];
            }
            else
            {
                return PM_OSC_OS2_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OSC_OS2_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_OSC_OS2_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_OSC_OS2_15M_HISTORICAL[0];
            //break;
        }
        //break;

    default:
        FC_THROW_ERROR(FC_SWError, "PM: Shelf not supported!");
        return PM_OSC_OS1_15M_HISTORICAL[0];
        //break;
    }
}

//---------------------------------------------------------------------------
FC_BbKey& PM_HISTORICAL_MUX(CT_PM_Period thePeriod, CT_PM_HistoryId theHistory, CT_ShelfId theShelf)
{
    switch( theShelf )
    {
    case OPTICAL_SHELF_1:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_MUX_OS1_15M_HISTORICAL[0];
            }
            else
            {
                return PM_MUX_OS1_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_MUX_OS1_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_MUX_OS1_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_MUX_OS1_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case OPTICAL_SHELF_2:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_MUX_OS2_15M_HISTORICAL[0];
            }
            else
            {
                return PM_MUX_OS2_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_MUX_OS2_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_MUX_OS2_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_MUX_OS2_15M_HISTORICAL[0];
            //break;
        }
        //break;

    default:
        FC_THROW_ERROR(FC_SWError, "PM: Shelf not supported!");
        return PM_MUX_OS1_15M_HISTORICAL[0];
        //break;
    }
}

//---------------------------------------------------------------------------
FC_BbKey& PM_HISTORICAL_OLIM(CT_PM_Period thePeriod, CT_PM_HistoryId theHistory, CT_ShelfId theShelf)
{
    switch( theShelf )
    {
    case OPTICAL_SHELF_1:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OLIM_OS1_15M_HISTORICAL[0];
            }
            else
            {
                return PM_OLIM_OS1_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OLIM_OS1_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_OLIM_OS1_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_OLIM_OS1_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case OPTICAL_SHELF_2:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OLIM_OS2_15M_HISTORICAL[0];
            }
            else
            {
                return PM_OLIM_OS2_15M_HISTORICAL[theHistory];
            }
            //break;

        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_OLIM_OS2_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_OLIM_OS2_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_OLIM_OS2_15M_HISTORICAL[0];
            //break;
        }
        //break;

    default:
        FC_THROW_ERROR(FC_SWError, "PM: Shelf not supported!");
        return PM_OLIM_OS1_15M_HISTORICAL[0];
        //break;
    }
}

//---------------------------------------------------------------------------
FC_BbKey& PM_HISTORICAL_TRN_RAM(CT_PM_Period thePeriod, CT_PM_HistoryId theHistory, CT_ShelfId theShelf)
{
    switch( theShelf )
    {
    case OPTICAL_SHELF_1:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_OS1_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_OS1_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_OS1_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_OS1_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_OS1_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_1:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS1_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS1_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS1_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS1_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS1_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_2:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS2_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS2_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS2_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS2_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS2_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_3:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS3_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS3_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS3_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS3_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS3_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_4:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS4_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS4_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS4_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS4_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS4_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_5:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS5_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS5_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS5_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS5_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS5_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_6:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS6_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS6_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS6_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS6_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS6_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_7:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS7_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS7_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS7_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS7_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS7_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_8:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS8_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS8_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS8_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS8_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS8_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_9:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS9_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS9_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS9_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS9_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS9_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_10:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS10_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS10_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS10_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS10_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS10_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_11:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS11_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS11_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS11_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS11_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS11_15M_HISTORICAL[0];
            //break;
        }
        //break;

    case PORT_SHELF_12:
        switch(thePeriod)
        {
        case CT_PM_PERIOD_15_MINUTES:
            if (theHistory >= CT_PM_NUMBER_OF_15M_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS12_15M_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS12_15M_HISTORICAL[theHistory];
            }
            //break;
        case CT_PM_PERIOD_1_DAY:
            if (theHistory >= CT_PM_NUMBER_OF_DAY_HISTORICAL_DATA || theHistory < 0)
            {
                FC_THROW_ERROR(FC_SWError, "PM: Historical not supported!");
                return PM_TRN_RAM_PS12_DAY_HISTORICAL[0];
            }
            else
            {
                return PM_TRN_RAM_PS12_DAY_HISTORICAL[theHistory];
            }
            //break;

        default:
            FC_THROW_ERROR(FC_SWError, "PM: Period not supported!");
            return PM_TRN_RAM_PS12_15M_HISTORICAL[0];
            //break;
        }
        //break;

    default:
           FC_THROW_ERROR(FC_SWError, "PM: Shelf not supported!");
           return PM_TRN_RAM_PS1_15M_HISTORICAL[0];
           //break;
    }

}
