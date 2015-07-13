/*--------------------------------------------------------------------------
Copyright;

 SUBSYSTEM:     Signal Alarm  
 TARGET   :     All cards
 AUTHOR   :     20 July, 2000 Marc Vendette
 DESCRIPTION:   Signal Alarm blackboard region keys definition. 
--------------------------------------------------------------------------*/
#ifndef ALM_REGIONKEYDEFINITION_H
#define ALM_REGIONKEYDEFINITION_H

#include <Blackboard/FC_BbKey.h>

//Suffix
extern const string ALM_LINE_SUFFIX;
extern const string ALM_PORT_SUFFIX;
extern const string ALM_IN_SUFFIX;
extern const string ALM_OUT_SUFFIX;
extern const string ALM_SIDE_A_SUFFIX;
extern const string ALM_SIDE_B_SUFFIX;
extern const string ALM_SIDE_C_SUFFIX;
extern const string ALM_SIDE_D_SUFFIX;
extern const string ALM_SIDE_E_SUFFIX;
extern const string ALM_SIDE_F_SUFFIX;
extern const string ALM_SIDE_G_SUFFIX;
extern const string ALM_SIDE_H_SUFFIX;
extern const string ALM_NULL_SUFFIX;

extern const string ALM_T1E1_SUFFIX;
extern const string ALM_RTR_SUFFIX;

extern const string ALM_LINE_0_SUFFIX;
extern const string ALM_LINE_1_SUFFIX;
extern const string ALM_LINE_2_SUFFIX;
extern const string ALM_LINE_3_SUFFIX;
extern const string ALM_LINE_4_SUFFIX;
extern const string ALM_LINE_5_SUFFIX;
extern const string ALM_LINE_6_SUFFIX;
extern const string ALM_LINE_7_SUFFIX;
extern const string ALM_LINE_8_SUFFIX;
extern const string ALM_LINE_9_SUFFIX;
extern const string ALM_LINE_10_SUFFIX;
extern const string ALM_LINE_11_SUFFIX;

extern const string ALM_PORT_0_SUFFIX;
extern const string ALM_PORT_1_SUFFIX;
extern const string ALM_PORT_2_SUFFIX;
extern const string ALM_PORT_3_SUFFIX;
extern const string ALM_PORT_4_SUFFIX;
extern const string ALM_PORT_5_SUFFIX;
extern const string ALM_PORT_6_SUFFIX;
extern const string ALM_PORT_7_SUFFIX;
extern const string ALM_PORT_8_SUFFIX;
extern const string ALM_PORT_9_SUFFIX;
extern const string ALM_PORT_10_SUFFIX;
extern const string ALM_PORT_11_SUFFIX;
extern const string ALM_PORT_12_SUFFIX;
extern const string ALM_PORT_13_SUFFIX;
extern const string ALM_PORT_14_SUFFIX;
extern const string ALM_PORT_15_SUFFIX;
extern const string ALM_PORT_16_SUFFIX;
extern const string ALM_PORT_17_SUFFIX;
extern const string ALM_PORT_18_SUFFIX;
extern const string ALM_PORT_19_SUFFIX;
extern const string ALM_PORT_20_SUFFIX;
extern const string ALM_PORT_21_SUFFIX;
extern const string ALM_PORT_22_SUFFIX;
extern const string ALM_PORT_23_SUFFIX;
extern const string ALM_PORT_24_SUFFIX;
extern const string ALM_PORT_25_SUFFIX;
extern const string ALM_PORT_26_SUFFIX;
extern const string ALM_PORT_27_SUFFIX;
extern const string ALM_PORT_28_SUFFIX;
extern const string ALM_PORT_29_SUFFIX;
extern const string ALM_PORT_30_SUFFIX;
extern const string ALM_PORT_31_SUFFIX;
extern const string ALM_PORT_32_SUFFIX;
extern const string ALM_PORT_33_SUFFIX;
extern const string ALM_PORT_34_SUFFIX;
extern const string ALM_PORT_40_SUFFIX;
extern const string ALM_PORT_41_SUFFIX;
extern const string ALM_PORT_50_SUFFIX;
extern const string ALM_PORT_51_SUFFIX;
extern const string ALM_PORT_60_SUFFIX;
extern const string ALM_PORT_61_SUFFIX;
extern const string ALM_PORT_70_SUFFIX;
extern const string ALM_PORT_71_SUFFIX;
extern const string ALM_PORT_80_SUFFIX;
extern const string ALM_PORT_81_SUFFIX;
extern const string ALM_PORT_85_SUFFIX; 
extern const string ALM_PORT_86_SUFFIX;
extern const string ALM_PORT_87_SUFFIX;
extern const string ALM_PORT_88_SUFFIX;

extern const string ALM_LINE_DWDM_OCN_A_SUFFIX; // SMTMA Hop Level: each A,B,C,D represents OC48
extern const string ALM_LINE_DWDM_OCN_B_SUFFIX; //                  to limit the transfer data.
extern const string ALM_LINE_DWDM_OCN_C_SUFFIX;
extern const string ALM_LINE_DWDM_OCN_D_SUFFIX;

extern const string ALM_PORT_O192_OCN_A_SUFFIX; // SMTMA Hop Level: each A,B,C,D represents OC48
extern const string ALM_PORT_O192_OCN_B_SUFFIX; //                  to limit the transfer data.
extern const string ALM_PORT_O192_OCN_C_SUFFIX;
extern const string ALM_PORT_O192_OCN_D_SUFFIX;

extern const string ALM_IMUX_LINE_OCN_A_SUFFIX;
extern const string ALM_IMUX_LINE_OCN_B_SUFFIX;
extern const string ALM_IMUX_LINE_OCN_C_SUFFIX;
extern const string ALM_IMUX_LINE_OCN_D_SUFFIX;

extern const string ALM_IMUX_PORT_OCN_A_SUFFIX;
extern const string ALM_IMUX_PORT_OCN_B_SUFFIX;
extern const string ALM_IMUX_PORT_OCN_C_SUFFIX;
extern const string ALM_IMUX_PORT_OCN_D_SUFFIX;

//Filtered failure key definitions 
extern const FC_BbKey ALM_FILTERED_PREFIX;

extern const FC_BbKey ALM_FILTERED_GFP;
extern const FC_BbKey ALM_FILTERED_HOP;
extern const FC_BbKey ALM_FILTERED_OTS;
extern const FC_BbKey ALM_FILTERED_OMS;
extern const FC_BbKey ALM_FILTERED_OSC;
extern const FC_BbKey ALM_FILTERED_OCH;
extern const FC_BbKey ALM_FILTERED_OCHOSC;
extern const FC_BbKey ALM_FILTERED_OPT;
extern const FC_BbKey ALM_FILTERED_OTU;
extern const FC_BbKey ALM_FILTERED_ODU;
extern const FC_BbKey ALM_FILTERED_TCM;
extern const FC_BbKey ALM_FILTERED_RS ;
extern const FC_BbKey ALM_FILTERED_MS ;
extern const FC_BbKey ALM_FILTERED_SYNC ;
extern const FC_BbKey ALM_FILTERED_T1E1 ;
extern const FC_BbKey ALM_FILTERED_DCC;
extern const FC_BbKey ALM_FILTERED_VCG;
extern const FC_BbKey ALM_FILTERED_MAC;
extern const FC_BbKey ALM_FILTERED_GCC;

extern const FC_BbKey ALM_INVALID_BB_KEY;

#endif //ALM_REGIONKEYDEFINITION_H

