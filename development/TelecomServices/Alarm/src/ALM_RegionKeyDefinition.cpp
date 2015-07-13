/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Siganl Alarm  
 TARGET   :     All cards
 AUTHOR   :     20 July, 2000 Marc Vendette
 DESCRIPTION:   Signal Alarm blackboard region keys definition.
--------------------------------------------------------------------------*/
#include "../ALM_RegionKeyDefinition.h" 

//Suffix
const string ALM_LINE_SUFFIX ("_LINE");
const string ALM_PORT_SUFFIX ("_PORT");
const string ALM_T1E1_SUFFIX ("_T1E1");
const string ALM_RTR_SUFFIX  ("_RTR");

const string ALM_LINE_0_SUFFIX ("_LINE_0");
const string ALM_LINE_1_SUFFIX ("_LINE_1");
const string ALM_LINE_2_SUFFIX ("_LINE_2");
const string ALM_LINE_3_SUFFIX ("_LINE_3");
const string ALM_LINE_4_SUFFIX ("_LINE_4");
const string ALM_LINE_5_SUFFIX ("_LINE_5");
const string ALM_LINE_6_SUFFIX ("_LINE_6");
const string ALM_LINE_7_SUFFIX ("_LINE_7");
const string ALM_LINE_8_SUFFIX ("_LINE_8");
const string ALM_LINE_9_SUFFIX ("_LINE_9");
const string ALM_LINE_10_SUFFIX ("_LINE_10");
const string ALM_LINE_11_SUFFIX ("_LINE_11");

const string ALM_PORT_0_SUFFIX ("_PORT_0");
const string ALM_PORT_1_SUFFIX ("_PORT_1");
const string ALM_PORT_2_SUFFIX ("_PORT_2");
const string ALM_PORT_3_SUFFIX ("_PORT_3");
const string ALM_PORT_4_SUFFIX ("_PORT_4");
const string ALM_PORT_5_SUFFIX ("_PORT_5");
const string ALM_PORT_6_SUFFIX ("_PORT_6");
const string ALM_PORT_7_SUFFIX ("_PORT_7");
const string ALM_PORT_8_SUFFIX ("_PORT_8");
const string ALM_PORT_9_SUFFIX ("_PORT_9");
const string ALM_PORT_10_SUFFIX ("_PORT_10");
const string ALM_PORT_11_SUFFIX ("_PORT_11");
const string ALM_PORT_12_SUFFIX ("_PORT_12");
const string ALM_PORT_13_SUFFIX ("_PORT_13");
const string ALM_PORT_14_SUFFIX ("_PORT_14");
const string ALM_PORT_15_SUFFIX ("_PORT_15");
const string ALM_PORT_16_SUFFIX ("_PORT_16");
const string ALM_PORT_17_SUFFIX ("_PORT_17");
const string ALM_PORT_18_SUFFIX ("_PORT_18");
const string ALM_PORT_19_SUFFIX ("_PORT_19");
const string ALM_PORT_20_SUFFIX ("_PORT_20");
const string ALM_PORT_21_SUFFIX ("_PORT_21");
const string ALM_PORT_22_SUFFIX ("_PORT_22");
const string ALM_PORT_23_SUFFIX ("_PORT_23");
const string ALM_PORT_24_SUFFIX ("_PORT_24");
const string ALM_PORT_25_SUFFIX ("_PORT_25");
const string ALM_PORT_26_SUFFIX ("_PORT_26");
const string ALM_PORT_27_SUFFIX ("_PORT_27");
const string ALM_PORT_28_SUFFIX ("_PORT_28");
const string ALM_PORT_29_SUFFIX ("_PORT_29");
const string ALM_PORT_30_SUFFIX ("_PORT_30");
const string ALM_PORT_31_SUFFIX ("_PORT_31");
const string ALM_PORT_32_SUFFIX ("_PORT_32");
const string ALM_PORT_33_SUFFIX ("_PORT_33");
const string ALM_PORT_34_SUFFIX ("_PORT_34");
const string ALM_PORT_40_SUFFIX ("_PORT_40");
const string ALM_PORT_41_SUFFIX ("_PORT_41");
const string ALM_PORT_50_SUFFIX ("_PORT_50");
const string ALM_PORT_51_SUFFIX ("_PORT_51");
const string ALM_PORT_60_SUFFIX ("_PORT_60");
const string ALM_PORT_61_SUFFIX ("_PORT_61");
const string ALM_PORT_70_SUFFIX ("_PORT_70");
const string ALM_PORT_71_SUFFIX ("_PORT_71");
const string ALM_PORT_80_SUFFIX ("_PORT_80");
const string ALM_PORT_81_SUFFIX ("_PORT_81");
const string ALM_PORT_85_SUFFIX ("_PORT_85");
const string ALM_PORT_86_SUFFIX ("_PORT_86");
const string ALM_PORT_87_SUFFIX ("_PORT_87");
const string ALM_PORT_88_SUFFIX ("_PORT_88");

const string ALM_LINE_DWDM_OCN_A_SUFFIX  ("_LINE_DWDM_OCN_A");
const string ALM_LINE_DWDM_OCN_B_SUFFIX  ("_LINE_DWDM_OCN_B");
const string ALM_LINE_DWDM_OCN_C_SUFFIX  ("_LINE_DWDM_OCN_C");
const string ALM_LINE_DWDM_OCN_D_SUFFIX  ("_LINE_DWDM_OCN_D");

const string ALM_PORT_O192_OCN_A_SUFFIX  ("_PORT_O192_OCN_A");
const string ALM_PORT_O192_OCN_B_SUFFIX  ("_PORT_O192_OCN_B");
const string ALM_PORT_O192_OCN_C_SUFFIX  ("_PORT_O192_OCN_C");
const string ALM_PORT_O192_OCN_D_SUFFIX  ("_PORT_O192_OCN_D");

const string ALM_IMUX_LINE_OCN_A_SUFFIX  ("_IMUX_LINE_OCN_A");
const string ALM_IMUX_LINE_OCN_B_SUFFIX  ("_IMUX_LINE_OCN_B");
const string ALM_IMUX_LINE_OCN_C_SUFFIX  ("_IMUX_LINE_OCN_C");
const string ALM_IMUX_LINE_OCN_D_SUFFIX  ("_IMUX_LINE_OCN_D");

const string ALM_IMUX_PORT_OCN_A_SUFFIX  ("_IMUX_PORT_OCN_A");
const string ALM_IMUX_PORT_OCN_B_SUFFIX  ("_IMUX_PORT_OCN_B");
const string ALM_IMUX_PORT_OCN_C_SUFFIX  ("_IMUX_PORT_OCN_C");
const string ALM_IMUX_PORT_OCN_D_SUFFIX  ("_IMUX_PORT_OCN_D");

const string ALM_IN_SUFFIX ("_IN");
const string ALM_OUT_SUFFIX ("_OUT");
const string ALM_SIDE_A_SUFFIX ("_A");
const string ALM_SIDE_B_SUFFIX ("_B");
const string ALM_SIDE_C_SUFFIX ("_C");
const string ALM_SIDE_D_SUFFIX ("_D");
const string ALM_SIDE_E_SUFFIX ("_E");
const string ALM_SIDE_F_SUFFIX ("_F");
const string ALM_SIDE_G_SUFFIX ("_G");
const string ALM_SIDE_H_SUFFIX ("_H");
const string ALM_NULL_SUFFIX ("");

//Filtered failure key definitions 
const FC_BbKey ALM_FILTERED_PREFIX  ("ALM_FILTERED");

const FC_BbKey ALM_FILTERED_GFP ("ALM_FILTERED_GFP");
const FC_BbKey ALM_FILTERED_HOP ("ALM_FILTERED_HOP");
const FC_BbKey ALM_FILTERED_OTS ("ALM_FILTERED_OTS");
const FC_BbKey ALM_FILTERED_OMS ("ALM_FILTERED_OMS");
const FC_BbKey ALM_FILTERED_OSC ("ALM_FILTERED_OSC");
const FC_BbKey ALM_FILTERED_OCH ("ALM_FILTERED_OCH");
const FC_BbKey ALM_FILTERED_OCHOSC ("ALM_FILTERED_OCHOSC");
const FC_BbKey ALM_FILTERED_OPT ("ALM_FILTERED_OPT");
const FC_BbKey ALM_FILTERED_OTU ("ALM_FILTERED_OTU");
const FC_BbKey ALM_FILTERED_ODU ("ALM_FILTERED_ODU");
const FC_BbKey ALM_FILTERED_TCM ("ALM_FILTERED_TCM");
const FC_BbKey ALM_FILTERED_RS  ("ALM_FILTERED_RS");
const FC_BbKey ALM_FILTERED_MS  ("ALM_FILTERED_MS");
const FC_BbKey ALM_FILTERED_SYNC ("ALM_FILTERED_SYNC");
const FC_BbKey ALM_FILTERED_T1E1 ("ALM_FILTERED");
const FC_BbKey ALM_FILTERED_DCC  ("ALM_FILTERED_DCC");
const FC_BbKey ALM_FILTERED_VCG  ("ALM_FILTERED_VCG");
const FC_BbKey ALM_FILTERED_MAC  ("ALM_FILTERED_MAC");
const FC_BbKey ALM_FILTERED_GCC  ("ALM_FILTERED_GCC");

const FC_BbKey ALM_INVALID_BB_KEY ("ALM_INVALID_BB_KEY");

