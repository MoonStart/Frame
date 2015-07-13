/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Cross Connect
 TARGET   :     All
 AUTHOR   :     March, 2004  Jai Harpalani
 DESCRIPTION:   XC general definitions
   NOTE: The TSXC_Connect object bit-field defines were modified when 88
         channels were introduced (see MR 73743).  Specifically, the new 
         scheme affects the 'input facility', 'output facility' and 'connect 
         state' fields.
 LAST REVISION:
    Date    Description
    ----    -----------
  04-17-09  t71mr00093595:Add CADM family facility Id's.
--------------------------------------------------------------------------*/


#ifndef TSXC_CROSSCONNECT_H
#define TSXC_CROSSCONNECT_H
#include <CommonTypes/CT_CrossConnect.h>


// *************************  Common Definitions *********************

// Common
#define TSXC_S2MC_REGION_SIZE        (1024)
#define TSXC_NUM_S2MC_REGIONS_MAX    (64)

// Non-MTERA
#define TSXC_NUM_S2MC_REGIONS        (8)
#define TSXC_MAX_SHELF_PER_MCAST     (8)
#define TSXC_MAX_SLOT_PER_SLOTMAP    (16)
#define TSXC_UFAB_MCASTID_START      (8192)

// MTERA
#define TSXC_NUM_S2MC_REGIONS_MTERA  (64)


const UINT8  XC_MAX_MCASTID = 2;
const UINT8  XC_MAX_SRC_ENDPT = 4;
const UINT16 XC_MCASTID_UNKNOWN = MULTICASTID_INVALID;
        
enum XC_ConnAction
{
    XC_NOACTION = 0,
    XC_CONNECT,
    XC_DISCONNECT
};

#define TSXC_MUX_BITMAP_LENGTH (5)    // ODU4 total 80 channels, 5 * uint16

//---- TSXC Config action debug defines   
#define TSXC_DEBUG_LEVEL01  (0x000001)
#define TSXC_DEBUG_LEVEL02  (0x000002)
#define TSXC_DEBUG_LEVEL03  (0x000004)
#define TSXC_DEBUG_LEVEL04  (0x000008)

//--- TSXC Connect Service debug defines
#define TSXC_DEBUG_LEVEL05  (0x000010)
#define TSXC_DEBUG_LEVEL06  (0x000020)
#define TSXC_DEBUG_LEVEL07  (0x000040)
#define TSXC_DEBUG_LEVEL08  (0x000080)

//--- Nano Mesh Multicast debug defines  
#define TSXC_DEBUG_LEVEL09  (0x000100)
#define TSXC_DEBUG_LEVEL10  (0x000200)
#define TSXC_DEBUG_LEVEL11  (0x000400)
#define TSXC_DEBUG_LEVEL12  (0x000800)

//--- Roll Service debug defines
#define TSXC_DEBUG_LEVEL13  (0x001000)
#define TSXC_DEBUG_LEVEL14  (0x002000)
#define TSXC_DEBUG_LEVEL15  (0x004000)
#define TSXC_DEBUG_LEVEL16  (0x008000)

//--- Roll action debug and time info
#define TSXC_DEBUG_LEVEL17  (0x010000)
#define TSXC_DEBUG_LEVEL18  (0x020000)
#define TSXC_DEBUG_LEVEL19  (0x040000)
#define TSXC_DEBUG_LEVEL20  (0x080000)

// -------------------------------------------------------------------------------
//
// Bit positions definitions for information stored in TSXC_Connect object
//
#define XC_BIT_POS_MAP      (5)
#define XC_BIT_POS_CONNECTSTATE (7)

//
// Bit field definitions for information stored in TSXC_Connect object
//
#define XC_BITS_TYPE      (0x1f)
#define XC_BITS_MAP       (0x60)
#define XC_BITS_CONNECTSTATE  (0x80)

//
// Definitions for information stored in IF, IFE, OF, OFE
//
#define XC_INVALID_FAC       (0xFF)
#define XC_INVALID_FAC_ENDPT (0xFF)

// -------------------------------------------------------------------------------
//
// Max port definitions that is possible on any module family SMTM and SSM 
//
#define XC_MAX_PORT_INTF    (90)

// *************************  TGIM E Definitions *********************

//
// Maximum number of each TGIME interface type
//
#define XC_MAX_TGIME_DWDM_INTF     (1)
#define XC_MAX_TGIME_IM_LINE_INTF  (1)
#define XC_MAX_TGIME_IM_PORT_INTF  (1)
#define XC_MAX_TGIME_PORT_INTF     (1)

//
// Maximum number of connections allowed on each TGIME interface
//
#define XC_MAX_XC_TGIME_DWDM       (192)
#define XC_MAX_XC_TGIME_IM_LINE    (192)
#define XC_MAX_XC_TGIME_IM_PORT    (192)
#define XC_MAX_XC_TGIME_PORT       (192)

//
// Maximum number of connections on TGIME
//
#define XC_MAX_XC_TGIME            ( (XC_MAX_TGIME_DWDM_INTF * XC_MAX_XC_TGIME_DWDM) + \
                                    (XC_MAX_TGIME_IM_LINE_INTF * XC_MAX_XC_TGIME_IM_LINE) + \
                                    (XC_MAX_TGIME_IM_PORT_INTF * XC_MAX_XC_TGIME_IM_PORT) + \
                                    (XC_MAX_TGIME_PORT_INTF * XC_MAX_XC_TGIME_PORT) )

// 
// Breakdown of TGIME XC CFG Region
//

#define XC_TGIME_CFG_PORT0_START   (0)
#define XC_TGIME_CFG_PORT0_END     (XC_TGIME_CFG_PORT0_START + XC_MAX_XC_TGIME_PORT - 1)

#define XC_TGIME_CFG_DWDM_START    (XC_TGIME_CFG_PORT0_END + 1)
#define XC_TGIME_CFG_DWDM_END      (XC_TGIME_CFG_DWDM_START + XC_MAX_XC_TGIME_DWDM - 1)

#define XC_TGIME_CFG_IM_LINE_START (XC_TGIME_CFG_DWDM_END + 1)
#define XC_TGIME_CFG_IM_LINE_END   (XC_TGIME_CFG_IM_LINE_START + XC_MAX_XC_TGIME_IM_LINE - 1)

#define XC_TGIME_CFG_IM_PORT_START (XC_TGIME_CFG_IM_LINE_END + 1)
#define XC_TGIME_CFG_IM_PORT_END   (XC_TGIME_CFG_IM_PORT_START + XC_MAX_XC_TGIME_IM_PORT - 1)

//
// Identifiers for each TGIME facility
//
#define XC_TGIME_PORT0_FACILITY_ID    (1)
#define XC_TGIME_DWDM_FACILITY_ID     (2)
#define XC_TGIME_IM_LINE_FACILITY_ID  (3)
#define XC_TGIME_IM_PORT_FACILITY_ID  (4)

// Constant Array for use with indexing into
// the AG/SP Config Region. SP will
// use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as TGIME facility identifiers ***
const int TGIMEConfigMap[] = {0,
                             XC_TGIME_CFG_PORT0_START,
                             XC_TGIME_CFG_DWDM_START,
                             XC_TGIME_CFG_IM_LINE_START,
                             XC_TGIME_CFG_IM_PORT_START};
                             
// *************************  SPFAB Definitions *********************
#define SPFAB_PRI_SLOT 8
#define SPFAB_SEC_SLOT 9

//
// Maximum number of each SPFAB interface type
//
#define XC_MAX_SPFAB_LINE_INTF      (28)

//
// Maximum number of connections allowed on each SPFAB interface
//

#define XC_MAX_XC_SPFAB_LINE        (192)

//
// Maximum number of connections on SPFAB
//
#define XC_MAX_XC_SPFAB             (XC_MAX_SPFAB_LINE_INTF * XC_MAX_XC_SPFAB_LINE) 
                                    
// 
// Breakdown of SPFAB XC CFG Region
//
        
#define XC_SPFAB_CFG_LINE0_START (0)
#define XC_SPFAB_CFG_LINE0_END   (XC_SPFAB_CFG_LINE0_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE1_START (XC_SPFAB_CFG_LINE0_END + 1)
#define XC_SPFAB_CFG_LINE1_END   (XC_SPFAB_CFG_LINE1_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE2_START (XC_SPFAB_CFG_LINE1_END + 1)
#define XC_SPFAB_CFG_LINE2_END   (XC_SPFAB_CFG_LINE2_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE3_START (XC_SPFAB_CFG_LINE2_END + 1)
#define XC_SPFAB_CFG_LINE3_END   (XC_SPFAB_CFG_LINE3_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE4_START (XC_SPFAB_CFG_LINE3_END + 1)
#define XC_SPFAB_CFG_LINE4_END   (XC_SPFAB_CFG_LINE4_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE5_START (XC_SPFAB_CFG_LINE4_END + 1)
#define XC_SPFAB_CFG_LINE5_END   (XC_SPFAB_CFG_LINE5_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE6_START (XC_SPFAB_CFG_LINE5_END + 1)
#define XC_SPFAB_CFG_LINE6_END   (XC_SPFAB_CFG_LINE6_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE7_START (XC_SPFAB_CFG_LINE6_END + 1)
#define XC_SPFAB_CFG_LINE7_END   (XC_SPFAB_CFG_LINE7_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE8_START (XC_SPFAB_CFG_LINE7_END + 1)
#define XC_SPFAB_CFG_LINE8_END   (XC_SPFAB_CFG_LINE8_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE9_START (XC_SPFAB_CFG_LINE8_END + 1)
#define XC_SPFAB_CFG_LINE9_END   (XC_SPFAB_CFG_LINE9_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE10_START (XC_SPFAB_CFG_LINE9_END + 1)
#define XC_SPFAB_CFG_LINE10_END   (XC_SPFAB_CFG_LINE10_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE11_START (XC_SPFAB_CFG_LINE10_END + 1)
#define XC_SPFAB_CFG_LINE11_END   (XC_SPFAB_CFG_LINE11_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE12_START (XC_SPFAB_CFG_LINE11_END + 1)
#define XC_SPFAB_CFG_LINE12_END   (XC_SPFAB_CFG_LINE12_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE13_START (XC_SPFAB_CFG_LINE12_END + 1)
#define XC_SPFAB_CFG_LINE13_END   (XC_SPFAB_CFG_LINE13_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE14_START (XC_SPFAB_CFG_LINE13_END + 1)
#define XC_SPFAB_CFG_LINE14_END   (XC_SPFAB_CFG_LINE14_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE15_START (XC_SPFAB_CFG_LINE14_END + 1)
#define XC_SPFAB_CFG_LINE15_END   (XC_SPFAB_CFG_LINE15_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE16_START (XC_SPFAB_CFG_LINE15_END + 1)
#define XC_SPFAB_CFG_LINE16_END   (XC_SPFAB_CFG_LINE16_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE17_START (XC_SPFAB_CFG_LINE16_END + 1)
#define XC_SPFAB_CFG_LINE17_END   (XC_SPFAB_CFG_LINE17_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE18_START (XC_SPFAB_CFG_LINE17_END + 1)
#define XC_SPFAB_CFG_LINE18_END   (XC_SPFAB_CFG_LINE18_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE19_START (XC_SPFAB_CFG_LINE18_END + 1)
#define XC_SPFAB_CFG_LINE19_END   (XC_SPFAB_CFG_LINE19_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE20_START (XC_SPFAB_CFG_LINE19_END + 1)
#define XC_SPFAB_CFG_LINE20_END   (XC_SPFAB_CFG_LINE20_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE21_START (XC_SPFAB_CFG_LINE20_END + 1)
#define XC_SPFAB_CFG_LINE21_END   (XC_SPFAB_CFG_LINE21_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE22_START (XC_SPFAB_CFG_LINE21_END + 1)
#define XC_SPFAB_CFG_LINE22_END   (XC_SPFAB_CFG_LINE22_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE23_START (XC_SPFAB_CFG_LINE22_END + 1)
#define XC_SPFAB_CFG_LINE23_END   (XC_SPFAB_CFG_LINE23_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE24_START (XC_SPFAB_CFG_LINE23_END + 1)
#define XC_SPFAB_CFG_LINE24_END   (XC_SPFAB_CFG_LINE24_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE25_START (XC_SPFAB_CFG_LINE24_END + 1)
#define XC_SPFAB_CFG_LINE25_END   (XC_SPFAB_CFG_LINE25_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE26_START (XC_SPFAB_CFG_LINE25_END + 1)
#define XC_SPFAB_CFG_LINE26_END   (XC_SPFAB_CFG_LINE26_START + XC_MAX_XC_SPFAB_LINE - 1)

#define XC_SPFAB_CFG_LINE27_START (XC_SPFAB_CFG_LINE26_END + 1)
#define XC_SPFAB_CFG_LINE27_END   (XC_SPFAB_CFG_LINE27_START + XC_MAX_XC_SPFAB_LINE - 1)


//
// Identifiers for each SPFAB facility
//

#define XC_SPFAB_LINE0_FACILITY_ID  (1)
#define XC_SPFAB_LINE1_FACILITY_ID  (2)
#define XC_SPFAB_LINE2_FACILITY_ID  (3)
#define XC_SPFAB_LINE3_FACILITY_ID  (4)
#define XC_SPFAB_LINE4_FACILITY_ID  (5)
#define XC_SPFAB_LINE5_FACILITY_ID  (6)
#define XC_SPFAB_LINE6_FACILITY_ID  (7)
#define XC_SPFAB_LINE7_FACILITY_ID  (8)
#define XC_SPFAB_LINE8_FACILITY_ID  (9)
#define XC_SPFAB_LINE9_FACILITY_ID  (10)
#define XC_SPFAB_LINE10_FACILITY_ID  (11)
#define XC_SPFAB_LINE11_FACILITY_ID  (12)
#define XC_SPFAB_LINE12_FACILITY_ID  (13)
#define XC_SPFAB_LINE13_FACILITY_ID  (14)
#define XC_SPFAB_LINE14_FACILITY_ID  (15)
#define XC_SPFAB_LINE15_FACILITY_ID  (16)
#define XC_SPFAB_LINE16_FACILITY_ID  (17)
#define XC_SPFAB_LINE17_FACILITY_ID  (18)
#define XC_SPFAB_LINE18_FACILITY_ID  (19)
#define XC_SPFAB_LINE19_FACILITY_ID  (20)
#define XC_SPFAB_LINE20_FACILITY_ID  (21)
#define XC_SPFAB_LINE21_FACILITY_ID  (22)
#define XC_SPFAB_LINE22_FACILITY_ID  (23)
#define XC_SPFAB_LINE23_FACILITY_ID  (24)
#define XC_SPFAB_LINE24_FACILITY_ID  (25)
#define XC_SPFAB_LINE25_FACILITY_ID  (26)
#define XC_SPFAB_LINE26_FACILITY_ID  (27)
#define XC_SPFAB_LINE27_FACILITY_ID  (28)

//
// Constant Array for use with indexing into the AG/SP Config Region. SP will
// use 1 based Ports when using this method. Therefore the array starts with zero.
// *** Must be kept in same order as SPFAB facility identifiers ***
//
const int SPFABConfigMap[] =    {   0,
                                     XC_SPFAB_CFG_LINE0_START,
                                     XC_SPFAB_CFG_LINE1_START,
                                     XC_SPFAB_CFG_LINE2_START, 
                                     XC_SPFAB_CFG_LINE3_START, 
                                     XC_SPFAB_CFG_LINE4_START, 
                                     XC_SPFAB_CFG_LINE5_START, 
                                     XC_SPFAB_CFG_LINE6_START, 
                                     XC_SPFAB_CFG_LINE7_START, 
                                     XC_SPFAB_CFG_LINE8_START, 
                                     XC_SPFAB_CFG_LINE9_START, 
                                     XC_SPFAB_CFG_LINE10_START,
                                     XC_SPFAB_CFG_LINE11_START,
                                     XC_SPFAB_CFG_LINE12_START,
                                     XC_SPFAB_CFG_LINE13_START,
                                     XC_SPFAB_CFG_LINE14_START,
                                     XC_SPFAB_CFG_LINE15_START,
                                     XC_SPFAB_CFG_LINE16_START, 
                                     XC_SPFAB_CFG_LINE17_START, 
                                     XC_SPFAB_CFG_LINE18_START, 
                                     XC_SPFAB_CFG_LINE19_START, 
                                     XC_SPFAB_CFG_LINE20_START, 
                                     XC_SPFAB_CFG_LINE21_START, 
                                     XC_SPFAB_CFG_LINE22_START, 
                                     XC_SPFAB_CFG_LINE23_START, 
                                     XC_SPFAB_CFG_LINE24_START,
                                     XC_SPFAB_CFG_LINE25_START,
                                     XC_SPFAB_CFG_LINE26_START,
                                     XC_SPFAB_CFG_LINE27_START
                                };
// -----------------------------------------------------------------------------------------------
// *************************  SSM Definitions *********************

//
// Identifiers for each SSM facility
//
#define XC_SSM_PORT0_FACILITY_ID    (1)
#define XC_SSM_PORT1_FACILITY_ID    (2)
#define XC_SSM_PORT2_FACILITY_ID    (3)
#define XC_SSM_PORT3_FACILITY_ID    (4)
#define XC_SSM_PORT4_FACILITY_ID    (5)
#define XC_SSM_PORT5_FACILITY_ID    (6)
#define XC_SSM_PORT6_FACILITY_ID    (7)
#define XC_SSM_PORT7_FACILITY_ID    (8)
#define XC_SSM_PORT8_FACILITY_ID    (9)
#define XC_SSM_PORT9_FACILITY_ID    (10)
#define XC_SSM_PORT10_FACILITY_ID   (11)
#define XC_SSM_PORT11_FACILITY_ID   (12)
#define XC_SSM_PORT12_FACILITY_ID   (13)

#define XC_SSM_DWDM_FACILITY_ID     (14)
#define XC_SSM_IM_LINE_FACILITY_ID  (15)
#define XC_SSM_IM_PORT_FACILITY_ID  (16)
#define XC_SSM_TTP_FACILITY_ID      (17)

// The Maximum number of each SSM interface type defined

#define XC_MAX_SSM_DWDM_INTF        (1)
#define XC_MAX_SSM_IM_LINE_INTF     (1)
#define XC_MAX_SSM_IM_PORT_INTF     (1)
#define XC_MAX_SSM_TTP_INTF         (1)
#define XC_MAX_SSM_PORTN_INTF       (12)
#define XC_MAX_SSM_PORTX_INTF       (1)
#define XC_MAX_SSM_PORT_INTF        (13)

// The maximum number of connections allowed on each SSM interface

#define XC_MAX_XC_SSM_DWDM       (192)
#define XC_MAX_XC_SSM_IM_LINE    (192)
#define XC_MAX_XC_SSM_IM_PORT    (192)
#define XC_MAX_XC_SSM_PORT       (48)
#define XC_MAX_XC_SSM_PORTX      (192)
#define XC_MAX_XC_SSM_IM_ALL     (XC_MAX_XC_SSM_IM_LINE+XC_MAX_XC_SSM_IM_PORT)
const UINT16 XC_MAX_FIXED_MCASTID = (XC_MAX_XC_SSM_IM_LINE+XC_MAX_XC_SSM_IM_PORT);

// The maximum number of connections on SSM 

#define XC_MAX_XC_SSM \
            ((XC_MAX_SSM_DWDM_INTF    * XC_MAX_XC_SSM_DWDM)    + \
             (XC_MAX_SSM_IM_LINE_INTF * XC_MAX_XC_SSM_IM_LINE) + \
             (XC_MAX_SSM_IM_PORT_INTF * XC_MAX_XC_SSM_IM_PORT) + \
             (XC_MAX_SSM_PORTN_INTF   * XC_MAX_XC_SSM_PORT)    + \
             (XC_MAX_SSM_PORTX_INTF   * XC_MAX_XC_SSM_PORTX)   + \
             (XC_MAX_SSM_TTP_INTF     * XC_MAX_XC_SSM_DWDM)      )

// 
// Breakdown of SSM XC CFG Region
//

#define XC_SSM_CFG_PORT0_START   (0)
#define XC_SSM_CFG_PORT0_END     (XC_SSM_CFG_PORT0_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT1_START   (XC_SSM_CFG_PORT0_END + 1)
#define XC_SSM_CFG_PORT1_END     (XC_SSM_CFG_PORT1_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT2_START   (XC_SSM_CFG_PORT1_END + 1)
#define XC_SSM_CFG_PORT2_END     (XC_SSM_CFG_PORT2_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT3_START   (XC_SSM_CFG_PORT2_END + 1)
#define XC_SSM_CFG_PORT3_END     (XC_SSM_CFG_PORT3_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT4_START   (XC_SSM_CFG_PORT3_END + 1)
#define XC_SSM_CFG_PORT4_END     (XC_SSM_CFG_PORT4_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT5_START   (XC_SSM_CFG_PORT4_END + 1)
#define XC_SSM_CFG_PORT5_END     (XC_SSM_CFG_PORT5_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT6_START   (XC_SSM_CFG_PORT5_END + 1)
#define XC_SSM_CFG_PORT6_END     (XC_SSM_CFG_PORT6_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT7_START   (XC_SSM_CFG_PORT6_END + 1)
#define XC_SSM_CFG_PORT7_END     (XC_SSM_CFG_PORT7_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT8_START   (XC_SSM_CFG_PORT7_END + 1)
#define XC_SSM_CFG_PORT8_END     (XC_SSM_CFG_PORT8_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT9_START   (XC_SSM_CFG_PORT8_END + 1)
#define XC_SSM_CFG_PORT9_END     (XC_SSM_CFG_PORT9_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT10_START   (XC_SSM_CFG_PORT9_END + 1)
#define XC_SSM_CFG_PORT10_END     (XC_SSM_CFG_PORT10_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT11_START   (XC_SSM_CFG_PORT10_END + 1)
#define XC_SSM_CFG_PORT11_END     (XC_SSM_CFG_PORT11_START + XC_MAX_XC_SSM_PORT - 1)

#define XC_SSM_CFG_PORT12_START   (XC_SSM_CFG_PORT11_END + 1)
#define XC_SSM_CFG_PORT12_END     (XC_SSM_CFG_PORT12_START + XC_MAX_XC_SSM_PORTX - 1)

#define XC_SSM_CFG_DWDM_START    (XC_SSM_CFG_PORT12_END + 1)
#define XC_SSM_CFG_DWDM_END      (XC_SSM_CFG_DWDM_START + XC_MAX_XC_SSM_DWDM - 1)

#define XC_SSM_CFG_IM_LINE_START (XC_SSM_CFG_DWDM_END + 1)
#define XC_SSM_CFG_IM_LINE_END   (XC_SSM_CFG_IM_LINE_START + XC_MAX_XC_SSM_IM_LINE - 1)

#define XC_SSM_CFG_IM_PORT_START (XC_SSM_CFG_IM_LINE_END + 1)
#define XC_SSM_CFG_IM_PORT_END   (XC_SSM_CFG_IM_PORT_START + XC_MAX_XC_SSM_IM_PORT - 1)

#define XC_SSM_CFG_TTP_START     (XC_SSM_CFG_IM_PORT_END + 1)
#define XC_SSM_CFG_TTP_END       (XC_SSM_CFG_TTP_START   + XC_MAX_XC_SSM_DWDM - 1)

// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as SSM facility identifiers ***
const int SSMConfigMap[] = {0,
                             XC_SSM_CFG_PORT0_START,
                             XC_SSM_CFG_PORT1_START,
                             XC_SSM_CFG_PORT2_START,
                             XC_SSM_CFG_PORT3_START,
                             XC_SSM_CFG_PORT4_START,
                             XC_SSM_CFG_PORT5_START,
                             XC_SSM_CFG_PORT6_START,
                             XC_SSM_CFG_PORT7_START,
                             XC_SSM_CFG_PORT8_START,
                             XC_SSM_CFG_PORT9_START,
                             XC_SSM_CFG_PORT10_START,
                             XC_SSM_CFG_PORT11_START,
                             XC_SSM_CFG_PORT12_START,
                             XC_SSM_CFG_DWDM_START,
                             XC_SSM_CFG_IM_LINE_START,
                             XC_SSM_CFG_IM_PORT_START,
                             XC_SSM_CFG_TTP_START};


// -----------------------------------------------------------------------------------------------
// *************************  FGSM Definitions *********************
//

//
// Identifiers for each FGSM facility
//

// ODU XC Facilities:  ODU <--> ODU
#define XC_FGSM_ODUXC_ODU_OTNOTU0_FACILITY_ID    (1)
#define XC_FGSM_ODUXC_ODU_OTNOTU1_FACILITY_ID    (2)
#define XC_FGSM_ODUXC_ODU_OTNOTU2_FACILITY_ID    (3)
#define XC_FGSM_ODUXC_ODU_IMUX_FACILITY_ID       (4)

// ODU32 XC Facilities: ODU3 <--> ODU2
#define XC_FGSM_ODU32XC_ODU3_0_FACILITY_ID       (5)

#define XC_FGSM_ODU32XC_ODU2_0_FACILITY_ID       (6)
#define XC_FGSM_ODU32XC_ODU2_1_FACILITY_ID       (7)
#define XC_FGSM_ODU32XC_ODU2_2_FACILITY_ID       (8)
#define XC_FGSM_ODU32XC_ODU2_3_FACILITY_ID       (9)

// ODU31 XC Facilities: ODU3 <--> ODU1
#define XC_FGSM_ODU31XC_ODU3_0_FACILITY_ID       (10)

#define XC_FGSM_ODU31XC_ODU1_0_FACILITY_ID       (11)
#define XC_FGSM_ODU31XC_ODU1_1_FACILITY_ID       (12)
#define XC_FGSM_ODU31XC_ODU1_2_FACILITY_ID       (13)
#define XC_FGSM_ODU31XC_ODU1_3_FACILITY_ID       (14)
#define XC_FGSM_ODU31XC_ODU1_4_FACILITY_ID       (15)
#define XC_FGSM_ODU31XC_ODU1_5_FACILITY_ID       (16)
#define XC_FGSM_ODU31XC_ODU1_6_FACILITY_ID       (17)
#define XC_FGSM_ODU31XC_ODU1_7_FACILITY_ID       (18)
#define XC_FGSM_ODU31XC_ODU1_8_FACILITY_ID       (19)
#define XC_FGSM_ODU31XC_ODU1_9_FACILITY_ID       (20)
#define XC_FGSM_ODU31XC_ODU1_10_FACILITY_ID      (21)
#define XC_FGSM_ODU31XC_ODU1_11_FACILITY_ID      (22)
#define XC_FGSM_ODU31XC_ODU1_12_FACILITY_ID      (23)
#define XC_FGSM_ODU31XC_ODU1_13_FACILITY_ID      (24)
#define XC_FGSM_ODU31XC_ODU1_14_FACILITY_ID      (25)
#define XC_FGSM_ODU31XC_ODU1_15_FACILITY_ID      (26)

// ODU30 XC Facilities: ODU3 <--> ODU0
#define XC_FGSM_ODU30XC_ODU3_0_FACILITY_ID       (27)

#define XC_FGSM_ODU30XC_ODU0_0_FACILITY_ID       (28)
#define XC_FGSM_ODU30XC_ODU0_1_FACILITY_ID       (29)
#define XC_FGSM_ODU30XC_ODU0_2_FACILITY_ID       (30)
#define XC_FGSM_ODU30XC_ODU0_3_FACILITY_ID       (31)
#define XC_FGSM_ODU30XC_ODU0_4_FACILITY_ID       (32)
#define XC_FGSM_ODU30XC_ODU0_5_FACILITY_ID       (33)
#define XC_FGSM_ODU30XC_ODU0_6_FACILITY_ID       (34)
#define XC_FGSM_ODU30XC_ODU0_7_FACILITY_ID       (35)
#define XC_FGSM_ODU30XC_ODU0_8_FACILITY_ID       (36)
#define XC_FGSM_ODU30XC_ODU0_9_FACILITY_ID       (37)
#define XC_FGSM_ODU30XC_ODU0_10_FACILITY_ID      (38)
#define XC_FGSM_ODU30XC_ODU0_11_FACILITY_ID      (39)
#define XC_FGSM_ODU30XC_ODU0_12_FACILITY_ID      (40)
#define XC_FGSM_ODU30XC_ODU0_13_FACILITY_ID      (41)
#define XC_FGSM_ODU30XC_ODU0_14_FACILITY_ID      (42)
#define XC_FGSM_ODU30XC_ODU0_15_FACILITY_ID      (43)
#define XC_FGSM_ODU30XC_ODU0_16_FACILITY_ID      (44)
#define XC_FGSM_ODU30XC_ODU0_17_FACILITY_ID      (45)
#define XC_FGSM_ODU30XC_ODU0_18_FACILITY_ID      (46)
#define XC_FGSM_ODU30XC_ODU0_19_FACILITY_ID      (47)
#define XC_FGSM_ODU30XC_ODU0_20_FACILITY_ID      (48)
#define XC_FGSM_ODU30XC_ODU0_21_FACILITY_ID      (49)
#define XC_FGSM_ODU30XC_ODU0_22_FACILITY_ID      (50)
#define XC_FGSM_ODU30XC_ODU0_23_FACILITY_ID      (51)
#define XC_FGSM_ODU30XC_ODU0_24_FACILITY_ID      (52)
#define XC_FGSM_ODU30XC_ODU0_25_FACILITY_ID      (53)
#define XC_FGSM_ODU30XC_ODU0_26_FACILITY_ID      (54)
#define XC_FGSM_ODU30XC_ODU0_27_FACILITY_ID      (55)
#define XC_FGSM_ODU30XC_ODU0_28_FACILITY_ID      (56)
#define XC_FGSM_ODU30XC_ODU0_29_FACILITY_ID      (57)
#define XC_FGSM_ODU30XC_ODU0_30_FACILITY_ID      (58)
#define XC_FGSM_ODU30XC_ODU0_31_FACILITY_ID      (59)

// ODU21 XC Facilities: ODU2 <--> ODU1
#define XC_FGSM_ODU21XC_ODU2_0_FACILITY_ID       (60)
#define XC_FGSM_ODU21XC_ODU2_1_FACILITY_ID       (61)
#define XC_FGSM_ODU21XC_ODU2_2_FACILITY_ID       (62)
#define XC_FGSM_ODU21XC_ODU2_3_FACILITY_ID       (63)

#define XC_FGSM_ODU21XC_ODU1_0_FACILITY_ID       (64)
#define XC_FGSM_ODU21XC_ODU1_1_FACILITY_ID       (65)
#define XC_FGSM_ODU21XC_ODU1_2_FACILITY_ID       (66)
#define XC_FGSM_ODU21XC_ODU1_3_FACILITY_ID       (67)
#define XC_FGSM_ODU21XC_ODU1_4_FACILITY_ID       (68)
#define XC_FGSM_ODU21XC_ODU1_5_FACILITY_ID       (69)
#define XC_FGSM_ODU21XC_ODU1_6_FACILITY_ID       (70)
#define XC_FGSM_ODU21XC_ODU1_7_FACILITY_ID       (71)
#define XC_FGSM_ODU21XC_ODU1_8_FACILITY_ID       (72)
#define XC_FGSM_ODU21XC_ODU1_9_FACILITY_ID       (73)
#define XC_FGSM_ODU21XC_ODU1_10_FACILITY_ID      (74)
#define XC_FGSM_ODU21XC_ODU1_11_FACILITY_ID      (75)
#define XC_FGSM_ODU21XC_ODU1_12_FACILITY_ID      (76)
#define XC_FGSM_ODU21XC_ODU1_13_FACILITY_ID      (77)
#define XC_FGSM_ODU21XC_ODU1_14_FACILITY_ID      (78)
#define XC_FGSM_ODU21XC_ODU1_15_FACILITY_ID      (79)

// ODU20 XC Facilities: ODU2 <--> ODU0
#define XC_FGSM_ODU20XC_ODU2_0_FACILITY_ID       (80)
#define XC_FGSM_ODU20XC_ODU2_1_FACILITY_ID       (81)
#define XC_FGSM_ODU20XC_ODU2_2_FACILITY_ID       (82)
#define XC_FGSM_ODU20XC_ODU2_3_FACILITY_ID       (83)

#define XC_FGSM_ODU20XC_ODU0_0_FACILITY_ID       (84)
#define XC_FGSM_ODU20XC_ODU0_1_FACILITY_ID       (85)
#define XC_FGSM_ODU20XC_ODU0_2_FACILITY_ID       (86)
#define XC_FGSM_ODU20XC_ODU0_3_FACILITY_ID       (87)
#define XC_FGSM_ODU20XC_ODU0_4_FACILITY_ID       (88)
#define XC_FGSM_ODU20XC_ODU0_5_FACILITY_ID       (89)
#define XC_FGSM_ODU20XC_ODU0_6_FACILITY_ID       (90)
#define XC_FGSM_ODU20XC_ODU0_7_FACILITY_ID       (91)
#define XC_FGSM_ODU20XC_ODU0_8_FACILITY_ID       (92)
#define XC_FGSM_ODU20XC_ODU0_9_FACILITY_ID       (93)
#define XC_FGSM_ODU20XC_ODU0_10_FACILITY_ID      (94)
#define XC_FGSM_ODU20XC_ODU0_11_FACILITY_ID      (95)
#define XC_FGSM_ODU20XC_ODU0_12_FACILITY_ID      (96)
#define XC_FGSM_ODU20XC_ODU0_13_FACILITY_ID      (97)
#define XC_FGSM_ODU20XC_ODU0_14_FACILITY_ID      (98)
#define XC_FGSM_ODU20XC_ODU0_15_FACILITY_ID      (99)
#define XC_FGSM_ODU20XC_ODU0_16_FACILITY_ID      (100)
#define XC_FGSM_ODU20XC_ODU0_17_FACILITY_ID      (101)
#define XC_FGSM_ODU20XC_ODU0_18_FACILITY_ID      (102)
#define XC_FGSM_ODU20XC_ODU0_19_FACILITY_ID      (103)
#define XC_FGSM_ODU20XC_ODU0_20_FACILITY_ID      (104)
#define XC_FGSM_ODU20XC_ODU0_21_FACILITY_ID      (105)
#define XC_FGSM_ODU20XC_ODU0_22_FACILITY_ID      (106)
#define XC_FGSM_ODU20XC_ODU0_23_FACILITY_ID      (107)
#define XC_FGSM_ODU20XC_ODU0_24_FACILITY_ID      (108)
#define XC_FGSM_ODU20XC_ODU0_25_FACILITY_ID      (109)
#define XC_FGSM_ODU20XC_ODU0_26_FACILITY_ID      (110)
#define XC_FGSM_ODU20XC_ODU0_27_FACILITY_ID      (111)
#define XC_FGSM_ODU20XC_ODU0_28_FACILITY_ID      (112)
#define XC_FGSM_ODU20XC_ODU0_29_FACILITY_ID      (113)
#define XC_FGSM_ODU20XC_ODU0_30_FACILITY_ID      (114)
#define XC_FGSM_ODU20XC_ODU0_31_FACILITY_ID      (115)

// ODU10 XC Facilities: ODU1 <--> ODU0
#define XC_FGSM_ODU10XC_ODU1_0_FACILITY_ID       (116)
#define XC_FGSM_ODU10XC_ODU1_1_FACILITY_ID       (117)
#define XC_FGSM_ODU10XC_ODU1_2_FACILITY_ID       (118)
#define XC_FGSM_ODU10XC_ODU1_3_FACILITY_ID       (119)
#define XC_FGSM_ODU10XC_ODU1_4_FACILITY_ID       (120)
#define XC_FGSM_ODU10XC_ODU1_5_FACILITY_ID       (121)
#define XC_FGSM_ODU10XC_ODU1_6_FACILITY_ID       (122)
#define XC_FGSM_ODU10XC_ODU1_7_FACILITY_ID       (123)
#define XC_FGSM_ODU10XC_ODU1_8_FACILITY_ID       (124)
#define XC_FGSM_ODU10XC_ODU1_9_FACILITY_ID       (125)
#define XC_FGSM_ODU10XC_ODU1_10_FACILITY_ID      (126)
#define XC_FGSM_ODU10XC_ODU1_11_FACILITY_ID      (127)
#define XC_FGSM_ODU10XC_ODU1_12_FACILITY_ID      (128)
#define XC_FGSM_ODU10XC_ODU1_13_FACILITY_ID      (129)
#define XC_FGSM_ODU10XC_ODU1_14_FACILITY_ID      (130)
#define XC_FGSM_ODU10XC_ODU1_15_FACILITY_ID      (131)

#define XC_FGSM_ODU10XC_ODU0_0_FACILITY_ID       (132)
#define XC_FGSM_ODU10XC_ODU0_1_FACILITY_ID       (133)
#define XC_FGSM_ODU10XC_ODU0_2_FACILITY_ID       (134)
#define XC_FGSM_ODU10XC_ODU0_3_FACILITY_ID       (135)
#define XC_FGSM_ODU10XC_ODU0_4_FACILITY_ID       (136)
#define XC_FGSM_ODU10XC_ODU0_5_FACILITY_ID       (137)
#define XC_FGSM_ODU10XC_ODU0_6_FACILITY_ID       (138)
#define XC_FGSM_ODU10XC_ODU0_7_FACILITY_ID       (139)
#define XC_FGSM_ODU10XC_ODU0_8_FACILITY_ID       (140)
#define XC_FGSM_ODU10XC_ODU0_9_FACILITY_ID       (141)
#define XC_FGSM_ODU10XC_ODU0_10_FACILITY_ID      (142)
#define XC_FGSM_ODU10XC_ODU0_11_FACILITY_ID      (143)
#define XC_FGSM_ODU10XC_ODU0_12_FACILITY_ID      (144)
#define XC_FGSM_ODU10XC_ODU0_13_FACILITY_ID      (145)
#define XC_FGSM_ODU10XC_ODU0_14_FACILITY_ID      (146)
#define XC_FGSM_ODU10XC_ODU0_15_FACILITY_ID      (147)
#define XC_FGSM_ODU10XC_ODU0_16_FACILITY_ID      (148)
#define XC_FGSM_ODU10XC_ODU0_17_FACILITY_ID      (149)
#define XC_FGSM_ODU10XC_ODU0_18_FACILITY_ID      (150)
#define XC_FGSM_ODU10XC_ODU0_19_FACILITY_ID      (151)
#define XC_FGSM_ODU10XC_ODU0_20_FACILITY_ID      (152)
#define XC_FGSM_ODU10XC_ODU0_21_FACILITY_ID      (153)
#define XC_FGSM_ODU10XC_ODU0_22_FACILITY_ID      (154)
#define XC_FGSM_ODU10XC_ODU0_23_FACILITY_ID      (155)
#define XC_FGSM_ODU10XC_ODU0_24_FACILITY_ID      (156)
#define XC_FGSM_ODU10XC_ODU0_25_FACILITY_ID      (157)
#define XC_FGSM_ODU10XC_ODU0_26_FACILITY_ID      (158)
#define XC_FGSM_ODU10XC_ODU0_27_FACILITY_ID      (159)
#define XC_FGSM_ODU10XC_ODU0_28_FACILITY_ID      (160)
#define XC_FGSM_ODU10XC_ODU0_29_FACILITY_ID      (161)
#define XC_FGSM_ODU10XC_ODU0_30_FACILITY_ID      (162)
#define XC_FGSM_ODU10XC_ODU0_31_FACILITY_ID      (163)


// The Maximum number of each FGSM interface type

#define XC_MAX_FGSM_ODUXC_OTN0_INTF              (1)
#define XC_MAX_FGSM_ODUXC_OTN1_INTF              (1)
#define XC_MAX_FGSM_ODUXC_OTN2_INTF              (1)
#define XC_MAX_FGSM_ODUXC_IMUX_INTF              (1)

#define XC_MAX_FGSM_ODU32XC_ODU3_INTF            (1)
#define XC_MAX_FGSM_ODU32XC_ODU2_INTF            (4)

#define XC_MAX_FGSM_ODU31XC_ODU3_INTF            (1)
#define XC_MAX_FGSM_ODU31XC_ODU1_INTF            (16)

#define XC_MAX_FGSM_ODU30XC_ODU3_INTF            (1)
#define XC_MAX_FGSM_ODU30XC_ODU0_INTF            (32)

#define XC_MAX_FGSM_ODU21XC_ODU2_INTF            (4)
#define XC_MAX_FGSM_ODU21XC_ODU1_INTF            (16)

#define XC_MAX_FGSM_ODU20XC_ODU2_INTF            (4)
#define XC_MAX_FGSM_ODU20XC_ODU0_INTF            (32)

#define XC_MAX_FGSM_ODU10XC_ODU1_INTF            (16)
#define XC_MAX_FGSM_ODU10XC_ODU0_INTF            (32)

// The Maximum number of connections allowed on each 
// FGSM interface type

#define XC_MAX_XC_FGSM_ODUXC_OTN0                 (32)
#define XC_MAX_XC_FGSM_ODUXC_OTN1                 (16)
#define XC_MAX_XC_FGSM_ODUXC_OTN2                 (4)
#define XC_MAX_XC_FGSM_ODUXC_IMUX                 (32)

#define XC_MAX_XC_FGSM_ODU32XC_ODU3              (32)
#define XC_MAX_XC_FGSM_ODU32XC_ODU2              (9)

#define XC_MAX_XC_FGSM_ODU31XC_ODU3              (32)
#define XC_MAX_XC_FGSM_ODU31XC_ODU1              (2)

#define XC_MAX_XC_FGSM_ODU30XC_ODU3              (32)
#define XC_MAX_XC_FGSM_ODU30XC_ODU0              (1)

#define XC_MAX_XC_FGSM_ODU21XC_ODU2              (8)
#define XC_MAX_XC_FGSM_ODU21XC_ODU1              (2)

#define XC_MAX_XC_FGSM_ODU20XC_ODU2              (8)
#define XC_MAX_XC_FGSM_ODU20XC_ODU0              (1)

#define XC_MAX_XC_FGSM_ODU10XC_ODU1              (2)
#define XC_MAX_XC_FGSM_ODU10XC_ODU0              (1)

// The maximum number of connections on FGSM, 472 CRS records

#define XC_MAX_XC_FGSM (\
    (XC_MAX_FGSM_ODUXC_OTN0_INTF            * XC_MAX_XC_FGSM_ODUXC_OTN0)        +\
    (XC_MAX_FGSM_ODUXC_OTN1_INTF            * XC_MAX_XC_FGSM_ODUXC_OTN1)        +\
    (XC_MAX_FGSM_ODUXC_OTN2_INTF            * XC_MAX_XC_FGSM_ODUXC_OTN2)        +\
    (XC_MAX_FGSM_ODUXC_IMUX_INTF            * XC_MAX_XC_FGSM_ODUXC_IMUX)        +\
    (XC_MAX_FGSM_ODU32XC_ODU3_INTF          * XC_MAX_XC_FGSM_ODU32XC_ODU3)      +\
    (XC_MAX_FGSM_ODU32XC_ODU2_INTF          * XC_MAX_XC_FGSM_ODU32XC_ODU2)      +\
    (XC_MAX_FGSM_ODU31XC_ODU3_INTF          * XC_MAX_XC_FGSM_ODU31XC_ODU3)      +\
    (XC_MAX_FGSM_ODU31XC_ODU1_INTF          * XC_MAX_XC_FGSM_ODU31XC_ODU1)      +\
    (XC_MAX_FGSM_ODU30XC_ODU3_INTF          * XC_MAX_XC_FGSM_ODU30XC_ODU3)      +\
    (XC_MAX_FGSM_ODU30XC_ODU0_INTF          * XC_MAX_XC_FGSM_ODU30XC_ODU0)      +\
    (XC_MAX_FGSM_ODU21XC_ODU2_INTF          * XC_MAX_XC_FGSM_ODU21XC_ODU2)      +\
    (XC_MAX_FGSM_ODU21XC_ODU1_INTF          * XC_MAX_XC_FGSM_ODU21XC_ODU1)      +\
    (XC_MAX_FGSM_ODU20XC_ODU2_INTF          * XC_MAX_XC_FGSM_ODU20XC_ODU2)      +\
    (XC_MAX_FGSM_ODU20XC_ODU0_INTF          * XC_MAX_XC_FGSM_ODU20XC_ODU0)      +\
    (XC_MAX_FGSM_ODU10XC_ODU1_INTF          * XC_MAX_XC_FGSM_ODU10XC_ODU1)      +\
    (XC_MAX_FGSM_ODU10XC_ODU0_INTF          * XC_MAX_XC_FGSM_ODU10XC_ODU0)      )

#define XC_MAX_FGSM_FIXED_MCASTID (\
    (XC_MAX_FGSM_ODUXC_IMUX_INTF            * XC_MAX_XC_FGSM_ODUXC_IMUX)        )

#define XC_MAX_FGSM_XC_IM_ALL (\
    (XC_MAX_FGSM_ODUXC_IMUX_INTF            * XC_MAX_XC_FGSM_ODUXC_IMUX)        )


// 
// Breakdown of FGSM XC CFG Region
//

#define XC_FGSM_ODUXC_ODU_OTNOTU0_START         (0)
#define XC_FGSM_ODUXC_ODU_OTNOTU0_END           (31)
#define XC_FGSM_ODUXC_ODU_OTNOTU1_START         (32)
#define XC_FGSM_ODUXC_ODU_OTNOTU1_END           (47)
#define XC_FGSM_ODUXC_ODU_OTNOTU2_START         (48)
#define XC_FGSM_ODUXC_ODU_OTNOTU2_END           (51)
#define XC_FGSM_ODUXC_ODU_IMUX_START            (52)
#define XC_FGSM_ODUXC_ODU_IMUX_END              (83)

#define XC_FGSM_ODU32XC_ODU3_0_START            (84)
#define XC_FGSM_ODU32XC_ODU3_0_END              (115)
#define XC_FGSM_ODU32XC_ODU2_0_START            (116)
#define XC_FGSM_ODU32XC_ODU2_0_END              (124)
#define XC_FGSM_ODU32XC_ODU2_1_START            (125)
#define XC_FGSM_ODU32XC_ODU2_1_END              (133)
#define XC_FGSM_ODU32XC_ODU2_2_START            (134)
#define XC_FGSM_ODU32XC_ODU2_2_END              (142)
#define XC_FGSM_ODU32XC_ODU2_3_START            (143)
#define XC_FGSM_ODU32XC_ODU2_3_END              (151)

#define XC_FGSM_ODU31XC_ODU3_0_START            (152)
#define XC_FGSM_ODU31XC_ODU3_0_END              (183)
#define XC_FGSM_ODU31XC_ODU1_0_START            (184)
#define XC_FGSM_ODU31XC_ODU1_0_END              (185)
#define XC_FGSM_ODU31XC_ODU1_1_START            (186)
#define XC_FGSM_ODU31XC_ODU1_1_END              (187)
#define XC_FGSM_ODU31XC_ODU1_2_START            (188)
#define XC_FGSM_ODU31XC_ODU1_2_END              (189)
#define XC_FGSM_ODU31XC_ODU1_3_START            (190)
#define XC_FGSM_ODU31XC_ODU1_3_END              (191)
#define XC_FGSM_ODU31XC_ODU1_4_START            (192)
#define XC_FGSM_ODU31XC_ODU1_4_END              (193)
#define XC_FGSM_ODU31XC_ODU1_5_START            (194)
#define XC_FGSM_ODU31XC_ODU1_5_END              (195)
#define XC_FGSM_ODU31XC_ODU1_6_START            (196)
#define XC_FGSM_ODU31XC_ODU1_6_END              (197)
#define XC_FGSM_ODU31XC_ODU1_7_START            (198)
#define XC_FGSM_ODU31XC_ODU1_7_END              (199)
#define XC_FGSM_ODU31XC_ODU1_8_START            (200)
#define XC_FGSM_ODU31XC_ODU1_8_END              (201)
#define XC_FGSM_ODU31XC_ODU1_9_START            (202)
#define XC_FGSM_ODU31XC_ODU1_9_END              (203)
#define XC_FGSM_ODU31XC_ODU1_10_START           (204)
#define XC_FGSM_ODU31XC_ODU1_10_END             (205)
#define XC_FGSM_ODU31XC_ODU1_11_START           (206)
#define XC_FGSM_ODU31XC_ODU1_11_END             (207)
#define XC_FGSM_ODU31XC_ODU1_12_START           (208)
#define XC_FGSM_ODU31XC_ODU1_12_END             (209)
#define XC_FGSM_ODU31XC_ODU1_13_START           (210)
#define XC_FGSM_ODU31XC_ODU1_13_END             (211)
#define XC_FGSM_ODU31XC_ODU1_14_START           (212)
#define XC_FGSM_ODU31XC_ODU1_14_END             (213)
#define XC_FGSM_ODU31XC_ODU1_15_START           (214)
#define XC_FGSM_ODU31XC_ODU1_15_END             (215)

#define XC_FGSM_ODU30XC_ODU3_0_START            (216)
#define XC_FGSM_ODU30XC_ODU3_0_END              (247)
#define XC_FGSM_ODU30XC_ODU0_0_START            (248)
#define XC_FGSM_ODU30XC_ODU0_0_END              (248)
#define XC_FGSM_ODU30XC_ODU0_1_START            (249)
#define XC_FGSM_ODU30XC_ODU0_1_END              (249)
#define XC_FGSM_ODU30XC_ODU0_2_START            (250)
#define XC_FGSM_ODU30XC_ODU0_2_END              (250)
#define XC_FGSM_ODU30XC_ODU0_3_START            (251)
#define XC_FGSM_ODU30XC_ODU0_3_END              (251)
#define XC_FGSM_ODU30XC_ODU0_4_START            (252)
#define XC_FGSM_ODU30XC_ODU0_4_END              (252)
#define XC_FGSM_ODU30XC_ODU0_5_START            (253)
#define XC_FGSM_ODU30XC_ODU0_5_END              (253)
#define XC_FGSM_ODU30XC_ODU0_6_START            (254)
#define XC_FGSM_ODU30XC_ODU0_6_END              (254)
#define XC_FGSM_ODU30XC_ODU0_7_START            (255)
#define XC_FGSM_ODU30XC_ODU0_7_END              (255)
#define XC_FGSM_ODU30XC_ODU0_8_START            (256)
#define XC_FGSM_ODU30XC_ODU0_8_END              (256)
#define XC_FGSM_ODU30XC_ODU0_9_START            (257)
#define XC_FGSM_ODU30XC_ODU0_9_END              (257)
#define XC_FGSM_ODU30XC_ODU0_10_START           (258)
#define XC_FGSM_ODU30XC_ODU0_10_END             (258)
#define XC_FGSM_ODU30XC_ODU0_11_START           (259)
#define XC_FGSM_ODU30XC_ODU0_11_END             (259)
#define XC_FGSM_ODU30XC_ODU0_12_START           (260)
#define XC_FGSM_ODU30XC_ODU0_12_END             (260)
#define XC_FGSM_ODU30XC_ODU0_13_START           (261)
#define XC_FGSM_ODU30XC_ODU0_13_END             (261)
#define XC_FGSM_ODU30XC_ODU0_14_START           (262)
#define XC_FGSM_ODU30XC_ODU0_14_END             (262)
#define XC_FGSM_ODU30XC_ODU0_15_START           (263)
#define XC_FGSM_ODU30XC_ODU0_15_END             (263)
#define XC_FGSM_ODU30XC_ODU0_16_START           (264)
#define XC_FGSM_ODU30XC_ODU0_16_END             (264)
#define XC_FGSM_ODU30XC_ODU0_17_START           (265)
#define XC_FGSM_ODU30XC_ODU0_17_END             (265)
#define XC_FGSM_ODU30XC_ODU0_18_START           (266)
#define XC_FGSM_ODU30XC_ODU0_18_END             (266)
#define XC_FGSM_ODU30XC_ODU0_19_START           (267)
#define XC_FGSM_ODU30XC_ODU0_19_END             (267)
#define XC_FGSM_ODU30XC_ODU0_20_START           (268)
#define XC_FGSM_ODU30XC_ODU0_20_END             (268)
#define XC_FGSM_ODU30XC_ODU0_21_START           (269)
#define XC_FGSM_ODU30XC_ODU0_21_END             (269)
#define XC_FGSM_ODU30XC_ODU0_22_START           (270)
#define XC_FGSM_ODU30XC_ODU0_22_END             (270)
#define XC_FGSM_ODU30XC_ODU0_23_START           (271)
#define XC_FGSM_ODU30XC_ODU0_23_END             (271)
#define XC_FGSM_ODU30XC_ODU0_24_START           (272)
#define XC_FGSM_ODU30XC_ODU0_24_END             (272)
#define XC_FGSM_ODU30XC_ODU0_25_START           (273)
#define XC_FGSM_ODU30XC_ODU0_25_END             (273)
#define XC_FGSM_ODU30XC_ODU0_26_START           (274)
#define XC_FGSM_ODU30XC_ODU0_26_END             (274)
#define XC_FGSM_ODU30XC_ODU0_27_START           (275)
#define XC_FGSM_ODU30XC_ODU0_27_END             (275)
#define XC_FGSM_ODU30XC_ODU0_28_START           (276)
#define XC_FGSM_ODU30XC_ODU0_28_END             (276)
#define XC_FGSM_ODU30XC_ODU0_29_START           (277)
#define XC_FGSM_ODU30XC_ODU0_29_END             (277)
#define XC_FGSM_ODU30XC_ODU0_30_START           (278)
#define XC_FGSM_ODU30XC_ODU0_30_END             (278)
#define XC_FGSM_ODU30XC_ODU0_31_START           (279)
#define XC_FGSM_ODU30XC_ODU0_31_END             (279)

/*
The compiler has a limit of 256 levels of nested macros, therefore, we have to use number to instead.

#define XC_FGSM_ODUXC_ODU_OTNOTU0_START         (0)
#define XC_FGSM_ODUXC_ODU_OTNOTU0_END           (XC_FGSM_ODUXC_ODU_OTNOTU0_START        + XC_MAX_XC_FGSM_ODUXC_OTN0-1)
#define XC_FGSM_ODUXC_ODU_OTNOTU1_START         (XC_FGSM_ODUXC_ODU_OTNOTU0_END+1)
#define XC_FGSM_ODUXC_ODU_OTNOTU1_END           (XC_FGSM_ODUXC_ODU_OTNOTU1_START        + XC_MAX_XC_FGSM_ODUXC_OTN1-1)
#define XC_FGSM_ODUXC_ODU_OTNOTU2_START         (XC_FGSM_ODUXC_ODU_OTNOTU1_END+1)
#define XC_FGSM_ODUXC_ODU_OTNOTU2_END           (XC_FGSM_ODUXC_ODU_OTNOTU2_START        + XC_MAX_XC_FGSM_ODUXC_OTN2-1)
#define XC_FGSM_ODUXC_ODU_IMUX_START            (XC_FGSM_ODUXC_ODU_OTNOTU2_END+1)
#define XC_FGSM_ODUXC_ODU_IMUX_END              (XC_FGSM_ODUXC_ODU_IMUX_START           + XC_MAX_XC_FGSM_ODUXC_IMUX_OTN0+\
                                                                                          XC_MAX_XC_FGSM_ODUXC_IMUX_OTN1+\
                                                                                          XC_MAX_XC_FGSM_ODUXC_IMUX_OTN2-1)

#define XC_FGSM_ODU32XC_ODU3_0_START            (XC_FGSM_ODUXC_ODU_IMUX_END+1)
#define XC_FGSM_ODU32XC_ODU3_0_END              (XC_FGSM_ODU32XC_ODU3_0_START           + XC_MAX_XC_FGSM_ODU32XC_ODU3-1)
#define XC_FGSM_ODU32XC_ODU2_0_START            (XC_FGSM_ODU32XC_ODU3_0_END+1)
#define XC_FGSM_ODU32XC_ODU2_0_END              (XC_FGSM_ODU32XC_ODU2_0_START           + XC_MAX_XC_FGSM_ODU32XC_ODU2-1)
#define XC_FGSM_ODU32XC_ODU2_1_START            (XC_FGSM_ODU32XC_ODU2_0_END+1)
#define XC_FGSM_ODU32XC_ODU2_1_END              (XC_FGSM_ODU32XC_ODU2_1_START           + XC_MAX_XC_FGSM_ODU32XC_ODU2-1)
#define XC_FGSM_ODU32XC_ODU2_2_START            (XC_FGSM_ODU32XC_ODU2_1_END+1)
#define XC_FGSM_ODU32XC_ODU2_2_END              (XC_FGSM_ODU32XC_ODU2_2_START           + XC_MAX_XC_FGSM_ODU32XC_ODU2-1)
#define XC_FGSM_ODU32XC_ODU2_3_START            (XC_FGSM_ODU32XC_ODU2_2_END+1)
#define XC_FGSM_ODU32XC_ODU2_3_END              (XC_FGSM_ODU32XC_ODU2_3_START           + XC_MAX_XC_FGSM_ODU32XC_ODU2-1)

#define XC_FGSM_ODU31XC_ODU3_0_START            (XC_FGSM_ODU32XC_ODU2_3_END+1)
#define XC_FGSM_ODU31XC_ODU3_0_END              (XC_FGSM_ODU31XC_ODU3_0_START           + XC_MAX_XC_FGSM_ODU31XC_ODU3-1)
#define XC_FGSM_ODU31XC_ODU1_0_START            (XC_FGSM_ODU31XC_ODU3_0_END+1)
#define XC_FGSM_ODU31XC_ODU1_0_END              (XC_FGSM_ODU31XC_ODU1_0_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_1_START            (XC_FGSM_ODU31XC_ODU1_0_END+1)
#define XC_FGSM_ODU31XC_ODU1_1_END              (XC_FGSM_ODU31XC_ODU1_1_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_2_START            (XC_FGSM_ODU31XC_ODU1_1_END+1)
#define XC_FGSM_ODU31XC_ODU1_2_END              (XC_FGSM_ODU31XC_ODU1_2_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_3_START            (XC_FGSM_ODU31XC_ODU1_2_END+1)
#define XC_FGSM_ODU31XC_ODU1_3_END              (XC_FGSM_ODU31XC_ODU1_3_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_4_START            (XC_FGSM_ODU31XC_ODU1_3_END+1)
#define XC_FGSM_ODU31XC_ODU1_4_END              (XC_FGSM_ODU31XC_ODU1_4_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_5_START            (XC_FGSM_ODU31XC_ODU1_4_END+1)
#define XC_FGSM_ODU31XC_ODU1_5_END              (XC_FGSM_ODU31XC_ODU1_5_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_6_START            (XC_FGSM_ODU31XC_ODU1_5_END+1)
#define XC_FGSM_ODU31XC_ODU1_6_END              (XC_FGSM_ODU31XC_ODU1_6_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_7_START            (XC_FGSM_ODU31XC_ODU1_6_END+1)
#define XC_FGSM_ODU31XC_ODU1_7_END              (XC_FGSM_ODU31XC_ODU1_7_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_8_START            (XC_FGSM_ODU31XC_ODU1_7_END+1)
#define XC_FGSM_ODU31XC_ODU1_8_END              (XC_FGSM_ODU31XC_ODU1_8_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_9_START            (XC_FGSM_ODU31XC_ODU1_8_END+1)
#define XC_FGSM_ODU31XC_ODU1_9_END              (XC_FGSM_ODU31XC_ODU1_9_START           + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_10_START           (XC_FGSM_ODU31XC_ODU1_9_END+1)
#define XC_FGSM_ODU31XC_ODU1_10_END             (XC_FGSM_ODU31XC_ODU1_10_START          + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_11_START           (XC_FGSM_ODU31XC_ODU1_10_END+1)
#define XC_FGSM_ODU31XC_ODU1_11_END             (XC_FGSM_ODU31XC_ODU1_11_START          + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_12_START           (XC_FGSM_ODU31XC_ODU1_11_END+1)
#define XC_FGSM_ODU31XC_ODU1_12_END             (XC_FGSM_ODU31XC_ODU1_12_START          + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_13_START           (XC_FGSM_ODU31XC_ODU1_12_END+1)
#define XC_FGSM_ODU31XC_ODU1_13_END             (XC_FGSM_ODU31XC_ODU1_13_START          + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_14_START           (XC_FGSM_ODU31XC_ODU1_13_END+1)
#define XC_FGSM_ODU31XC_ODU1_14_END             (XC_FGSM_ODU31XC_ODU1_14_START          + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)
#define XC_FGSM_ODU31XC_ODU1_15_START           (XC_FGSM_ODU31XC_ODU1_14_END+1)
#define XC_FGSM_ODU31XC_ODU1_15_END             (XC_FGSM_ODU31XC_ODU1_15_START          + XC_MAX_XC_FGSM_ODU31XC_ODU1-1)

#define XC_FGSM_ODU30XC_ODU3_0_START            (XC_FGSM_ODU31XC_ODU1_15_END+1)
#define XC_FGSM_ODU30XC_ODU3_0_END              (XC_FGSM_ODU30XC_ODU3_0_START           + XC_MAX_XC_FGSM_ODU30XC_ODU3-1)
#define XC_FGSM_ODU30XC_ODU0_0_START            (XC_FGSM_ODU30XC_ODU3_0_END+1)
#define XC_FGSM_ODU30XC_ODU0_0_END              (XC_FGSM_ODU30XC_ODU0_0_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_1_START            (XC_FGSM_ODU30XC_ODU0_0_END+1)
#define XC_FGSM_ODU30XC_ODU0_1_END              (XC_FGSM_ODU30XC_ODU0_1_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_2_START            (XC_FGSM_ODU30XC_ODU0_1_END+1)
#define XC_FGSM_ODU30XC_ODU0_2_END              (XC_FGSM_ODU30XC_ODU0_2_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_3_START            (XC_FGSM_ODU30XC_ODU0_2_END+1)
#define XC_FGSM_ODU30XC_ODU0_3_END              (XC_FGSM_ODU30XC_ODU0_3_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_4_START            (XC_FGSM_ODU30XC_ODU0_3_END+1)
#define XC_FGSM_ODU30XC_ODU0_4_END              (XC_FGSM_ODU30XC_ODU0_4_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_5_START            (XC_FGSM_ODU30XC_ODU0_4_END+1)
#define XC_FGSM_ODU30XC_ODU0_5_END              (XC_FGSM_ODU30XC_ODU0_5_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_6_START            (XC_FGSM_ODU30XC_ODU0_5_END+1)
#define XC_FGSM_ODU30XC_ODU0_6_END              (XC_FGSM_ODU30XC_ODU0_6_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_7_START            (XC_FGSM_ODU30XC_ODU0_6_END+1)
#define XC_FGSM_ODU30XC_ODU0_7_END              (XC_FGSM_ODU30XC_ODU0_7_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_8_START            (XC_FGSM_ODU30XC_ODU0_7_END+1)
#define XC_FGSM_ODU30XC_ODU0_8_END              (XC_FGSM_ODU30XC_ODU0_8_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_9_START            (XC_FGSM_ODU30XC_ODU0_8_END+1)
#define XC_FGSM_ODU30XC_ODU0_9_END              (XC_FGSM_ODU30XC_ODU0_9_START           + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_10_START           (XC_FGSM_ODU30XC_ODU0_9_END+1)
#define XC_FGSM_ODU30XC_ODU0_10_END             (XC_FGSM_ODU30XC_ODU0_10_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_11_START           (XC_FGSM_ODU30XC_ODU0_10_END+1)
#define XC_FGSM_ODU30XC_ODU0_11_END             (XC_FGSM_ODU30XC_ODU0_11_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_12_START           (XC_FGSM_ODU30XC_ODU0_11_END+1)
#define XC_FGSM_ODU30XC_ODU0_12_END             (XC_FGSM_ODU30XC_ODU0_12_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_13_START           (XC_FGSM_ODU30XC_ODU0_12_END+1)
#define XC_FGSM_ODU30XC_ODU0_13_END             (XC_FGSM_ODU30XC_ODU0_13_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_14_START           (XC_FGSM_ODU30XC_ODU0_13_END+1)
#define XC_FGSM_ODU30XC_ODU0_14_END             (XC_FGSM_ODU30XC_ODU0_14_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_15_START           (XC_FGSM_ODU30XC_ODU0_14_END+1)
#define XC_FGSM_ODU30XC_ODU0_15_END             (XC_FGSM_ODU30XC_ODU0_15_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_16_START           (XC_FGSM_ODU30XC_ODU0_15_END+1)
#define XC_FGSM_ODU30XC_ODU0_16_END             (XC_FGSM_ODU30XC_ODU0_16_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_17_START           (XC_FGSM_ODU30XC_ODU0_16_END+1)
#define XC_FGSM_ODU30XC_ODU0_17_END             (XC_FGSM_ODU30XC_ODU0_17_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_18_START           (XC_FGSM_ODU30XC_ODU0_17_END+1)
#define XC_FGSM_ODU30XC_ODU0_18_END             (XC_FGSM_ODU30XC_ODU0_18_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_19_START           (XC_FGSM_ODU30XC_ODU0_18_END+1)
#define XC_FGSM_ODU30XC_ODU0_19_END             (XC_FGSM_ODU30XC_ODU0_19_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_20_START           (XC_FGSM_ODU30XC_ODU0_19_END+1)
#define XC_FGSM_ODU30XC_ODU0_20_END             (XC_FGSM_ODU30XC_ODU0_20_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_21_START           (XC_FGSM_ODU30XC_ODU0_20_END+1)
#define XC_FGSM_ODU30XC_ODU0_21_END             (XC_FGSM_ODU30XC_ODU0_21_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_22_START           (XC_FGSM_ODU30XC_ODU0_21_END+1)
#define XC_FGSM_ODU30XC_ODU0_22_END             (XC_FGSM_ODU30XC_ODU0_22_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_23_START           (XC_FGSM_ODU30XC_ODU0_22_END+1)
#define XC_FGSM_ODU30XC_ODU0_23_END             (XC_FGSM_ODU30XC_ODU0_23_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_24_START           (XC_FGSM_ODU30XC_ODU0_23_END+1)
#define XC_FGSM_ODU30XC_ODU0_24_END             (XC_FGSM_ODU30XC_ODU0_24_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_25_START           (XC_FGSM_ODU30XC_ODU0_24_END+1)
#define XC_FGSM_ODU30XC_ODU0_25_END             (XC_FGSM_ODU30XC_ODU0_25_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_26_START           (XC_FGSM_ODU30XC_ODU0_25_END+1)
#define XC_FGSM_ODU30XC_ODU0_26_END             (XC_FGSM_ODU30XC_ODU0_26_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_27_START           (XC_FGSM_ODU30XC_ODU0_26_END+1)
#define XC_FGSM_ODU30XC_ODU0_27_END             (XC_FGSM_ODU30XC_ODU0_27_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_28_START           (XC_FGSM_ODU30XC_ODU0_27_END+1)
#define XC_FGSM_ODU30XC_ODU0_28_END             (XC_FGSM_ODU30XC_ODU0_28_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_29_START           (XC_FGSM_ODU30XC_ODU0_28_END+1)
#define XC_FGSM_ODU30XC_ODU0_29_END             (XC_FGSM_ODU30XC_ODU0_29_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_30_START           (XC_FGSM_ODU30XC_ODU0_29_END+1)
#define XC_FGSM_ODU30XC_ODU0_30_END             (XC_FGSM_ODU30XC_ODU0_30_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)
#define XC_FGSM_ODU30XC_ODU0_31_START           (XC_FGSM_ODU30XC_ODU0_30_END+1)
#define XC_FGSM_ODU30XC_ODU0_31_END             (XC_FGSM_ODU30XC_ODU0_31_START          + XC_MAX_XC_FGSM_ODU30XC_ODU0-1)

*/

#define XC_FGSM_ODU21XC_ODU2_0_START            (XC_FGSM_ODU30XC_ODU0_31_END+1)
#define XC_FGSM_ODU21XC_ODU2_0_END              (XC_FGSM_ODU21XC_ODU2_0_START           + XC_MAX_XC_FGSM_ODU21XC_ODU2-1)
#define XC_FGSM_ODU21XC_ODU2_1_START            (XC_FGSM_ODU21XC_ODU2_0_END+1)
#define XC_FGSM_ODU21XC_ODU2_1_END              (XC_FGSM_ODU21XC_ODU2_1_START           + XC_MAX_XC_FGSM_ODU21XC_ODU2-1)
#define XC_FGSM_ODU21XC_ODU2_2_START            (XC_FGSM_ODU21XC_ODU2_1_END+1)
#define XC_FGSM_ODU21XC_ODU2_2_END              (XC_FGSM_ODU21XC_ODU2_2_START           + XC_MAX_XC_FGSM_ODU21XC_ODU2-1)
#define XC_FGSM_ODU21XC_ODU2_3_START            (XC_FGSM_ODU21XC_ODU2_2_END+1)
#define XC_FGSM_ODU21XC_ODU2_3_END              (XC_FGSM_ODU21XC_ODU2_3_START           + XC_MAX_XC_FGSM_ODU21XC_ODU2-1)
#define XC_FGSM_ODU21XC_ODU1_0_START            (XC_FGSM_ODU21XC_ODU2_3_END+1)
#define XC_FGSM_ODU21XC_ODU1_0_END              (XC_FGSM_ODU21XC_ODU1_0_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_1_START            (XC_FGSM_ODU21XC_ODU1_0_END+1)
#define XC_FGSM_ODU21XC_ODU1_1_END              (XC_FGSM_ODU21XC_ODU1_1_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_2_START            (XC_FGSM_ODU21XC_ODU1_1_END+1)
#define XC_FGSM_ODU21XC_ODU1_2_END              (XC_FGSM_ODU21XC_ODU1_2_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_3_START            (XC_FGSM_ODU21XC_ODU1_2_END+1)
#define XC_FGSM_ODU21XC_ODU1_3_END              (XC_FGSM_ODU21XC_ODU1_3_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_4_START            (XC_FGSM_ODU21XC_ODU1_3_END+1)
#define XC_FGSM_ODU21XC_ODU1_4_END              (XC_FGSM_ODU21XC_ODU1_4_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_5_START            (XC_FGSM_ODU21XC_ODU1_4_END+1)
#define XC_FGSM_ODU21XC_ODU1_5_END              (XC_FGSM_ODU21XC_ODU1_5_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_6_START            (XC_FGSM_ODU21XC_ODU1_5_END+1)
#define XC_FGSM_ODU21XC_ODU1_6_END              (XC_FGSM_ODU21XC_ODU1_6_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_7_START            (XC_FGSM_ODU21XC_ODU1_6_END+1)
#define XC_FGSM_ODU21XC_ODU1_7_END              (XC_FGSM_ODU21XC_ODU1_7_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_8_START            (XC_FGSM_ODU21XC_ODU1_7_END+1)
#define XC_FGSM_ODU21XC_ODU1_8_END              (XC_FGSM_ODU21XC_ODU1_8_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_9_START            (XC_FGSM_ODU21XC_ODU1_8_END+1)
#define XC_FGSM_ODU21XC_ODU1_9_END              (XC_FGSM_ODU21XC_ODU1_9_START           + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_10_START           (XC_FGSM_ODU21XC_ODU1_9_END+1)
#define XC_FGSM_ODU21XC_ODU1_10_END             (XC_FGSM_ODU21XC_ODU1_10_START          + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_11_START           (XC_FGSM_ODU21XC_ODU1_10_END+1)
#define XC_FGSM_ODU21XC_ODU1_11_END             (XC_FGSM_ODU21XC_ODU1_11_START          + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_12_START           (XC_FGSM_ODU21XC_ODU1_11_END+1)
#define XC_FGSM_ODU21XC_ODU1_12_END             (XC_FGSM_ODU21XC_ODU1_12_START          + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_13_START           (XC_FGSM_ODU21XC_ODU1_12_END+1)
#define XC_FGSM_ODU21XC_ODU1_13_END             (XC_FGSM_ODU21XC_ODU1_13_START          + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_14_START           (XC_FGSM_ODU21XC_ODU1_13_END+1)
#define XC_FGSM_ODU21XC_ODU1_14_END             (XC_FGSM_ODU21XC_ODU1_14_START          + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)
#define XC_FGSM_ODU21XC_ODU1_15_START           (XC_FGSM_ODU21XC_ODU1_14_END+1)
#define XC_FGSM_ODU21XC_ODU1_15_END             (XC_FGSM_ODU21XC_ODU1_15_START          + XC_MAX_XC_FGSM_ODU21XC_ODU1-1)

#define XC_FGSM_ODU20XC_ODU2_0_START            (XC_FGSM_ODU21XC_ODU1_15_END+1)
#define XC_FGSM_ODU20XC_ODU2_0_END              (XC_FGSM_ODU20XC_ODU2_0_START           + XC_MAX_XC_FGSM_ODU20XC_ODU2-1)
#define XC_FGSM_ODU20XC_ODU2_1_START            (XC_FGSM_ODU20XC_ODU2_0_END+1)
#define XC_FGSM_ODU20XC_ODU2_1_END              (XC_FGSM_ODU20XC_ODU2_1_START           + XC_MAX_XC_FGSM_ODU20XC_ODU2-1)
#define XC_FGSM_ODU20XC_ODU2_2_START            (XC_FGSM_ODU20XC_ODU2_1_END+1)
#define XC_FGSM_ODU20XC_ODU2_2_END              (XC_FGSM_ODU20XC_ODU2_2_START           + XC_MAX_XC_FGSM_ODU20XC_ODU2-1)
#define XC_FGSM_ODU20XC_ODU2_3_START            (XC_FGSM_ODU20XC_ODU2_2_END+1)
#define XC_FGSM_ODU20XC_ODU2_3_END              (XC_FGSM_ODU20XC_ODU2_3_START           + XC_MAX_XC_FGSM_ODU20XC_ODU2-1)
#define XC_FGSM_ODU20XC_ODU0_0_START            (XC_FGSM_ODU20XC_ODU2_3_END+1)
#define XC_FGSM_ODU20XC_ODU0_0_END              (XC_FGSM_ODU20XC_ODU0_0_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_1_START            (XC_FGSM_ODU20XC_ODU0_0_END+1)
#define XC_FGSM_ODU20XC_ODU0_1_END              (XC_FGSM_ODU20XC_ODU0_1_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_2_START            (XC_FGSM_ODU20XC_ODU0_1_END+1)
#define XC_FGSM_ODU20XC_ODU0_2_END              (XC_FGSM_ODU20XC_ODU0_2_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_3_START            (XC_FGSM_ODU20XC_ODU0_2_END+1)
#define XC_FGSM_ODU20XC_ODU0_3_END              (XC_FGSM_ODU20XC_ODU0_3_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_4_START            (XC_FGSM_ODU20XC_ODU0_3_END+1)
#define XC_FGSM_ODU20XC_ODU0_4_END              (XC_FGSM_ODU20XC_ODU0_4_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_5_START            (XC_FGSM_ODU20XC_ODU0_4_END+1)
#define XC_FGSM_ODU20XC_ODU0_5_END              (XC_FGSM_ODU20XC_ODU0_5_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_6_START            (XC_FGSM_ODU20XC_ODU0_5_END+1)
#define XC_FGSM_ODU20XC_ODU0_6_END              (XC_FGSM_ODU20XC_ODU0_6_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_7_START            (XC_FGSM_ODU20XC_ODU0_6_END+1)
#define XC_FGSM_ODU20XC_ODU0_7_END              (XC_FGSM_ODU20XC_ODU0_7_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_8_START            (XC_FGSM_ODU20XC_ODU0_7_END+1)
#define XC_FGSM_ODU20XC_ODU0_8_END              (XC_FGSM_ODU20XC_ODU0_8_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_9_START            (XC_FGSM_ODU20XC_ODU0_8_END+1)
#define XC_FGSM_ODU20XC_ODU0_9_END              (XC_FGSM_ODU20XC_ODU0_9_START           + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_10_START           (XC_FGSM_ODU20XC_ODU0_9_END+1)
#define XC_FGSM_ODU20XC_ODU0_10_END             (XC_FGSM_ODU20XC_ODU0_10_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_11_START           (XC_FGSM_ODU20XC_ODU0_10_END+1)
#define XC_FGSM_ODU20XC_ODU0_11_END             (XC_FGSM_ODU20XC_ODU0_11_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_12_START           (XC_FGSM_ODU20XC_ODU0_11_END+1)
#define XC_FGSM_ODU20XC_ODU0_12_END             (XC_FGSM_ODU20XC_ODU0_12_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_13_START           (XC_FGSM_ODU20XC_ODU0_12_END+1)
#define XC_FGSM_ODU20XC_ODU0_13_END             (XC_FGSM_ODU20XC_ODU0_13_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_14_START           (XC_FGSM_ODU20XC_ODU0_13_END+1)
#define XC_FGSM_ODU20XC_ODU0_14_END             (XC_FGSM_ODU20XC_ODU0_14_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_15_START           (XC_FGSM_ODU20XC_ODU0_14_END+1)
#define XC_FGSM_ODU20XC_ODU0_15_END             (XC_FGSM_ODU20XC_ODU0_15_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_16_START           (XC_FGSM_ODU20XC_ODU0_15_END+1)
#define XC_FGSM_ODU20XC_ODU0_16_END             (XC_FGSM_ODU20XC_ODU0_16_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_17_START           (XC_FGSM_ODU20XC_ODU0_16_END+1)
#define XC_FGSM_ODU20XC_ODU0_17_END             (XC_FGSM_ODU20XC_ODU0_17_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_18_START           (XC_FGSM_ODU20XC_ODU0_17_END+1)
#define XC_FGSM_ODU20XC_ODU0_18_END             (XC_FGSM_ODU20XC_ODU0_18_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_19_START           (XC_FGSM_ODU20XC_ODU0_18_END+1)
#define XC_FGSM_ODU20XC_ODU0_19_END             (XC_FGSM_ODU20XC_ODU0_19_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_20_START           (XC_FGSM_ODU20XC_ODU0_19_END+1)
#define XC_FGSM_ODU20XC_ODU0_20_END             (XC_FGSM_ODU20XC_ODU0_20_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_21_START           (XC_FGSM_ODU20XC_ODU0_20_END+1)
#define XC_FGSM_ODU20XC_ODU0_21_END             (XC_FGSM_ODU20XC_ODU0_21_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_22_START           (XC_FGSM_ODU20XC_ODU0_21_END+1)
#define XC_FGSM_ODU20XC_ODU0_22_END             (XC_FGSM_ODU20XC_ODU0_22_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_23_START           (XC_FGSM_ODU20XC_ODU0_22_END+1)
#define XC_FGSM_ODU20XC_ODU0_23_END             (XC_FGSM_ODU20XC_ODU0_23_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_24_START           (XC_FGSM_ODU20XC_ODU0_23_END+1)
#define XC_FGSM_ODU20XC_ODU0_24_END             (XC_FGSM_ODU20XC_ODU0_24_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_25_START           (XC_FGSM_ODU20XC_ODU0_24_END+1)
#define XC_FGSM_ODU20XC_ODU0_25_END             (XC_FGSM_ODU20XC_ODU0_25_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_26_START           (XC_FGSM_ODU20XC_ODU0_25_END+1)
#define XC_FGSM_ODU20XC_ODU0_26_END             (XC_FGSM_ODU20XC_ODU0_26_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_27_START           (XC_FGSM_ODU20XC_ODU0_26_END+1)
#define XC_FGSM_ODU20XC_ODU0_27_END             (XC_FGSM_ODU20XC_ODU0_27_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_28_START           (XC_FGSM_ODU20XC_ODU0_27_END+1)
#define XC_FGSM_ODU20XC_ODU0_28_END             (XC_FGSM_ODU20XC_ODU0_28_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_29_START           (XC_FGSM_ODU20XC_ODU0_28_END+1)
#define XC_FGSM_ODU20XC_ODU0_29_END             (XC_FGSM_ODU20XC_ODU0_29_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_30_START           (XC_FGSM_ODU20XC_ODU0_29_END+1)
#define XC_FGSM_ODU20XC_ODU0_30_END             (XC_FGSM_ODU20XC_ODU0_30_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)
#define XC_FGSM_ODU20XC_ODU0_31_START           (XC_FGSM_ODU20XC_ODU0_30_END+1)
#define XC_FGSM_ODU20XC_ODU0_31_END             (XC_FGSM_ODU20XC_ODU0_31_START          + XC_MAX_XC_FGSM_ODU20XC_ODU0-1)

#define XC_FGSM_ODU10XC_ODU1_0_START            (XC_FGSM_ODU20XC_ODU0_31_END+1)
#define XC_FGSM_ODU10XC_ODU1_0_END              (XC_FGSM_ODU10XC_ODU1_0_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_1_START            (XC_FGSM_ODU10XC_ODU1_0_END+1)
#define XC_FGSM_ODU10XC_ODU1_1_END              (XC_FGSM_ODU10XC_ODU1_1_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_2_START            (XC_FGSM_ODU10XC_ODU1_1_END+1)
#define XC_FGSM_ODU10XC_ODU1_2_END              (XC_FGSM_ODU10XC_ODU1_2_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_3_START            (XC_FGSM_ODU10XC_ODU1_2_END+1)
#define XC_FGSM_ODU10XC_ODU1_3_END              (XC_FGSM_ODU10XC_ODU1_3_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_4_START            (XC_FGSM_ODU10XC_ODU1_3_END+1)
#define XC_FGSM_ODU10XC_ODU1_4_END              (XC_FGSM_ODU10XC_ODU1_4_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_5_START            (XC_FGSM_ODU10XC_ODU1_4_END+1)
#define XC_FGSM_ODU10XC_ODU1_5_END              (XC_FGSM_ODU10XC_ODU1_5_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_6_START            (XC_FGSM_ODU10XC_ODU1_5_END+1)
#define XC_FGSM_ODU10XC_ODU1_6_END              (XC_FGSM_ODU10XC_ODU1_6_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_7_START            (XC_FGSM_ODU10XC_ODU1_6_END+1)
#define XC_FGSM_ODU10XC_ODU1_7_END              (XC_FGSM_ODU10XC_ODU1_7_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_8_START            (XC_FGSM_ODU10XC_ODU1_7_END+1)
#define XC_FGSM_ODU10XC_ODU1_8_END              (XC_FGSM_ODU10XC_ODU1_8_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_9_START            (XC_FGSM_ODU10XC_ODU1_8_END+1)
#define XC_FGSM_ODU10XC_ODU1_9_END              (XC_FGSM_ODU10XC_ODU1_9_START           + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_10_START           (XC_FGSM_ODU10XC_ODU1_9_END+1)
#define XC_FGSM_ODU10XC_ODU1_10_END             (XC_FGSM_ODU10XC_ODU1_10_START          + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_11_START           (XC_FGSM_ODU10XC_ODU1_10_END+1)
#define XC_FGSM_ODU10XC_ODU1_11_END             (XC_FGSM_ODU10XC_ODU1_11_START          + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_12_START           (XC_FGSM_ODU10XC_ODU1_11_END+1)
#define XC_FGSM_ODU10XC_ODU1_12_END             (XC_FGSM_ODU10XC_ODU1_12_START          + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_13_START           (XC_FGSM_ODU10XC_ODU1_12_END+1)
#define XC_FGSM_ODU10XC_ODU1_13_END             (XC_FGSM_ODU10XC_ODU1_13_START          + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_14_START           (XC_FGSM_ODU10XC_ODU1_13_END+1)
#define XC_FGSM_ODU10XC_ODU1_14_END             (XC_FGSM_ODU10XC_ODU1_14_START          + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU1_15_START           (XC_FGSM_ODU10XC_ODU1_14_END+1)
#define XC_FGSM_ODU10XC_ODU1_15_END             (XC_FGSM_ODU10XC_ODU1_15_START          + XC_MAX_XC_FGSM_ODU10XC_ODU1-1)
#define XC_FGSM_ODU10XC_ODU0_0_START            (XC_FGSM_ODU10XC_ODU1_15_END+1)
#define XC_FGSM_ODU10XC_ODU0_0_END              (XC_FGSM_ODU10XC_ODU0_0_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_1_START            (XC_FGSM_ODU10XC_ODU0_0_END+1)
#define XC_FGSM_ODU10XC_ODU0_1_END              (XC_FGSM_ODU10XC_ODU0_1_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_2_START            (XC_FGSM_ODU10XC_ODU0_1_END+1)
#define XC_FGSM_ODU10XC_ODU0_2_END              (XC_FGSM_ODU10XC_ODU0_2_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_3_START            (XC_FGSM_ODU10XC_ODU0_2_END+1)
#define XC_FGSM_ODU10XC_ODU0_3_END              (XC_FGSM_ODU10XC_ODU0_3_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_4_START            (XC_FGSM_ODU10XC_ODU0_3_END+1)
#define XC_FGSM_ODU10XC_ODU0_4_END              (XC_FGSM_ODU10XC_ODU0_4_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_5_START            (XC_FGSM_ODU10XC_ODU0_4_END+1)
#define XC_FGSM_ODU10XC_ODU0_5_END              (XC_FGSM_ODU10XC_ODU0_5_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_6_START            (XC_FGSM_ODU10XC_ODU0_5_END+1)
#define XC_FGSM_ODU10XC_ODU0_6_END              (XC_FGSM_ODU10XC_ODU0_6_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_7_START            (XC_FGSM_ODU10XC_ODU0_6_END+1)
#define XC_FGSM_ODU10XC_ODU0_7_END              (XC_FGSM_ODU10XC_ODU0_7_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_8_START            (XC_FGSM_ODU10XC_ODU0_7_END+1)
#define XC_FGSM_ODU10XC_ODU0_8_END              (XC_FGSM_ODU10XC_ODU0_8_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_9_START            (XC_FGSM_ODU10XC_ODU0_8_END+1)
#define XC_FGSM_ODU10XC_ODU0_9_END              (XC_FGSM_ODU10XC_ODU0_9_START           + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_10_START           (XC_FGSM_ODU10XC_ODU0_9_END+1)
#define XC_FGSM_ODU10XC_ODU0_10_END             (XC_FGSM_ODU10XC_ODU0_10_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_11_START           (XC_FGSM_ODU10XC_ODU0_10_END+1)
#define XC_FGSM_ODU10XC_ODU0_11_END             (XC_FGSM_ODU10XC_ODU0_11_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_12_START           (XC_FGSM_ODU10XC_ODU0_11_END+1)
#define XC_FGSM_ODU10XC_ODU0_12_END             (XC_FGSM_ODU10XC_ODU0_12_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_13_START           (XC_FGSM_ODU10XC_ODU0_12_END+1)
#define XC_FGSM_ODU10XC_ODU0_13_END             (XC_FGSM_ODU10XC_ODU0_13_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_14_START           (XC_FGSM_ODU10XC_ODU0_13_END+1)
#define XC_FGSM_ODU10XC_ODU0_14_END             (XC_FGSM_ODU10XC_ODU0_14_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_15_START           (XC_FGSM_ODU10XC_ODU0_14_END+1)
#define XC_FGSM_ODU10XC_ODU0_15_END             (XC_FGSM_ODU10XC_ODU0_15_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_16_START           (XC_FGSM_ODU10XC_ODU0_15_END+1)
#define XC_FGSM_ODU10XC_ODU0_16_END             (XC_FGSM_ODU10XC_ODU0_16_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_17_START           (XC_FGSM_ODU10XC_ODU0_16_END+1)
#define XC_FGSM_ODU10XC_ODU0_17_END             (XC_FGSM_ODU10XC_ODU0_17_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_18_START           (XC_FGSM_ODU10XC_ODU0_17_END+1)
#define XC_FGSM_ODU10XC_ODU0_18_END             (XC_FGSM_ODU10XC_ODU0_18_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_19_START           (XC_FGSM_ODU10XC_ODU0_18_END+1)
#define XC_FGSM_ODU10XC_ODU0_19_END             (XC_FGSM_ODU10XC_ODU0_19_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_20_START           (XC_FGSM_ODU10XC_ODU0_19_END+1)
#define XC_FGSM_ODU10XC_ODU0_20_END             (XC_FGSM_ODU10XC_ODU0_20_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_21_START           (XC_FGSM_ODU10XC_ODU0_20_END+1)
#define XC_FGSM_ODU10XC_ODU0_21_END             (XC_FGSM_ODU10XC_ODU0_21_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_22_START           (XC_FGSM_ODU10XC_ODU0_21_END+1)
#define XC_FGSM_ODU10XC_ODU0_22_END             (XC_FGSM_ODU10XC_ODU0_22_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_23_START           (XC_FGSM_ODU10XC_ODU0_22_END+1)
#define XC_FGSM_ODU10XC_ODU0_23_END             (XC_FGSM_ODU10XC_ODU0_23_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_24_START           (XC_FGSM_ODU10XC_ODU0_23_END+1)
#define XC_FGSM_ODU10XC_ODU0_24_END             (XC_FGSM_ODU10XC_ODU0_24_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_25_START           (XC_FGSM_ODU10XC_ODU0_24_END+1)
#define XC_FGSM_ODU10XC_ODU0_25_END             (XC_FGSM_ODU10XC_ODU0_25_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_26_START           (XC_FGSM_ODU10XC_ODU0_25_END+1)
#define XC_FGSM_ODU10XC_ODU0_26_END             (XC_FGSM_ODU10XC_ODU0_26_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_27_START           (XC_FGSM_ODU10XC_ODU0_26_END+1)
#define XC_FGSM_ODU10XC_ODU0_27_END             (XC_FGSM_ODU10XC_ODU0_27_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_28_START           (XC_FGSM_ODU10XC_ODU0_27_END+1)
#define XC_FGSM_ODU10XC_ODU0_28_END             (XC_FGSM_ODU10XC_ODU0_28_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_29_START           (XC_FGSM_ODU10XC_ODU0_28_END+1)
#define XC_FGSM_ODU10XC_ODU0_29_END             (XC_FGSM_ODU10XC_ODU0_29_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_30_START           (XC_FGSM_ODU10XC_ODU0_29_END+1)
#define XC_FGSM_ODU10XC_ODU0_30_END             (XC_FGSM_ODU10XC_ODU0_30_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)
#define XC_FGSM_ODU10XC_ODU0_31_START           (XC_FGSM_ODU10XC_ODU0_30_END+1)
#define XC_FGSM_ODU10XC_ODU0_31_END             (XC_FGSM_ODU10XC_ODU0_31_START          + XC_MAX_XC_FGSM_ODU10XC_ODU0-1)


// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as FGSM facility identifiers ***
const int FGSMConfigMap[] = {0,
        // ODUXC
        XC_FGSM_ODUXC_ODU_OTNOTU0_START,
        XC_FGSM_ODUXC_ODU_OTNOTU1_START,
        XC_FGSM_ODUXC_ODU_OTNOTU2_START,
        XC_FGSM_ODUXC_ODU_IMUX_START,
        // ODU32XC
        XC_FGSM_ODU32XC_ODU3_0_START,
        XC_FGSM_ODU32XC_ODU2_0_START,
        XC_FGSM_ODU32XC_ODU2_1_START,
        XC_FGSM_ODU32XC_ODU2_2_START,
        XC_FGSM_ODU32XC_ODU2_3_START,
        // ODU31XC
        XC_FGSM_ODU31XC_ODU3_0_START,
        XC_FGSM_ODU31XC_ODU1_0_START,
        XC_FGSM_ODU31XC_ODU1_1_START,
        XC_FGSM_ODU31XC_ODU1_2_START,
        XC_FGSM_ODU31XC_ODU1_3_START,
        XC_FGSM_ODU31XC_ODU1_4_START,
        XC_FGSM_ODU31XC_ODU1_5_START,
        XC_FGSM_ODU31XC_ODU1_6_START,
        XC_FGSM_ODU31XC_ODU1_7_START,
        XC_FGSM_ODU31XC_ODU1_8_START,
        XC_FGSM_ODU31XC_ODU1_9_START,
        XC_FGSM_ODU31XC_ODU1_10_START,
        XC_FGSM_ODU31XC_ODU1_11_START,
        XC_FGSM_ODU31XC_ODU1_12_START,
        XC_FGSM_ODU31XC_ODU1_13_START,
        XC_FGSM_ODU31XC_ODU1_14_START,
        XC_FGSM_ODU31XC_ODU1_15_START,
        // OUD30XC
        XC_FGSM_ODU30XC_ODU3_0_START,
        XC_FGSM_ODU30XC_ODU0_0_START,
        XC_FGSM_ODU30XC_ODU0_1_START,
        XC_FGSM_ODU30XC_ODU0_2_START,
        XC_FGSM_ODU30XC_ODU0_3_START,
        XC_FGSM_ODU30XC_ODU0_4_START,
        XC_FGSM_ODU30XC_ODU0_5_START,
        XC_FGSM_ODU30XC_ODU0_6_START,
        XC_FGSM_ODU30XC_ODU0_7_START,
        XC_FGSM_ODU30XC_ODU0_8_START,
        XC_FGSM_ODU30XC_ODU0_9_START,
        XC_FGSM_ODU30XC_ODU0_10_START,
        XC_FGSM_ODU30XC_ODU0_11_START,
        XC_FGSM_ODU30XC_ODU0_12_START,
        XC_FGSM_ODU30XC_ODU0_13_START,
        XC_FGSM_ODU30XC_ODU0_14_START,
        XC_FGSM_ODU30XC_ODU0_15_START,
        XC_FGSM_ODU30XC_ODU0_16_START,
        XC_FGSM_ODU30XC_ODU0_17_START,
        XC_FGSM_ODU30XC_ODU0_18_START,
        XC_FGSM_ODU30XC_ODU0_19_START,
        XC_FGSM_ODU30XC_ODU0_20_START,
        XC_FGSM_ODU30XC_ODU0_21_START,
        XC_FGSM_ODU30XC_ODU0_22_START,
        XC_FGSM_ODU30XC_ODU0_23_START,
        XC_FGSM_ODU30XC_ODU0_24_START,
        XC_FGSM_ODU30XC_ODU0_25_START,
        XC_FGSM_ODU30XC_ODU0_26_START,
        XC_FGSM_ODU30XC_ODU0_27_START,
        XC_FGSM_ODU30XC_ODU0_28_START,
        XC_FGSM_ODU30XC_ODU0_29_START,
        XC_FGSM_ODU30XC_ODU0_30_START,
        XC_FGSM_ODU30XC_ODU0_31_START,
        // ODU21XC
        XC_FGSM_ODU21XC_ODU2_0_START,
        XC_FGSM_ODU21XC_ODU2_1_START,
        XC_FGSM_ODU21XC_ODU2_2_START,
        XC_FGSM_ODU21XC_ODU2_3_START,
        XC_FGSM_ODU21XC_ODU1_0_START,
        XC_FGSM_ODU21XC_ODU1_1_START,
        XC_FGSM_ODU21XC_ODU1_2_START,
        XC_FGSM_ODU21XC_ODU1_3_START,
        XC_FGSM_ODU21XC_ODU1_4_START,
        XC_FGSM_ODU21XC_ODU1_5_START,
        XC_FGSM_ODU21XC_ODU1_6_START,
        XC_FGSM_ODU21XC_ODU1_7_START,
        XC_FGSM_ODU21XC_ODU1_8_START,
        XC_FGSM_ODU21XC_ODU1_9_START,
        XC_FGSM_ODU21XC_ODU1_10_START,
        XC_FGSM_ODU21XC_ODU1_11_START,
        XC_FGSM_ODU21XC_ODU1_12_START,
        XC_FGSM_ODU21XC_ODU1_13_START,
        XC_FGSM_ODU21XC_ODU1_14_START,
        XC_FGSM_ODU21XC_ODU1_15_START,
        // ODU20XC
        XC_FGSM_ODU20XC_ODU2_0_START,
        XC_FGSM_ODU20XC_ODU2_1_START,
        XC_FGSM_ODU20XC_ODU2_2_START,
        XC_FGSM_ODU20XC_ODU2_3_START,
        XC_FGSM_ODU20XC_ODU0_0_START,
        XC_FGSM_ODU20XC_ODU0_1_START,
        XC_FGSM_ODU20XC_ODU0_2_START,
        XC_FGSM_ODU20XC_ODU0_3_START,
        XC_FGSM_ODU20XC_ODU0_4_START,
        XC_FGSM_ODU20XC_ODU0_5_START,
        XC_FGSM_ODU20XC_ODU0_6_START,
        XC_FGSM_ODU20XC_ODU0_7_START,
        XC_FGSM_ODU20XC_ODU0_8_START,
        XC_FGSM_ODU20XC_ODU0_9_START,
        XC_FGSM_ODU20XC_ODU0_10_START,
        XC_FGSM_ODU20XC_ODU0_11_START,
        XC_FGSM_ODU20XC_ODU0_12_START,
        XC_FGSM_ODU20XC_ODU0_13_START,
        XC_FGSM_ODU20XC_ODU0_14_START,
        XC_FGSM_ODU20XC_ODU0_15_START,
        XC_FGSM_ODU20XC_ODU0_16_START,
        XC_FGSM_ODU20XC_ODU0_17_START,
        XC_FGSM_ODU20XC_ODU0_18_START,
        XC_FGSM_ODU20XC_ODU0_19_START,
        XC_FGSM_ODU20XC_ODU0_20_START,
        XC_FGSM_ODU20XC_ODU0_21_START,
        XC_FGSM_ODU20XC_ODU0_22_START,
        XC_FGSM_ODU20XC_ODU0_23_START,
        XC_FGSM_ODU20XC_ODU0_24_START,
        XC_FGSM_ODU20XC_ODU0_25_START,
        XC_FGSM_ODU20XC_ODU0_26_START,
        XC_FGSM_ODU20XC_ODU0_27_START,
        XC_FGSM_ODU20XC_ODU0_28_START,
        XC_FGSM_ODU20XC_ODU0_29_START,
        XC_FGSM_ODU20XC_ODU0_30_START,
        XC_FGSM_ODU20XC_ODU0_31_START,
        // ODU10XC
        XC_FGSM_ODU10XC_ODU1_0_START,
        XC_FGSM_ODU10XC_ODU1_1_START,
        XC_FGSM_ODU10XC_ODU1_2_START,
        XC_FGSM_ODU10XC_ODU1_3_START,
        XC_FGSM_ODU10XC_ODU1_4_START,
        XC_FGSM_ODU10XC_ODU1_5_START,
        XC_FGSM_ODU10XC_ODU1_6_START,
        XC_FGSM_ODU10XC_ODU1_7_START,
        XC_FGSM_ODU10XC_ODU1_8_START,
        XC_FGSM_ODU10XC_ODU1_9_START,
        XC_FGSM_ODU10XC_ODU1_10_START,
        XC_FGSM_ODU10XC_ODU1_11_START,
        XC_FGSM_ODU10XC_ODU1_12_START,
        XC_FGSM_ODU10XC_ODU1_13_START,
        XC_FGSM_ODU10XC_ODU1_14_START,
        XC_FGSM_ODU10XC_ODU1_15_START,
        XC_FGSM_ODU10XC_ODU0_0_START,
        XC_FGSM_ODU10XC_ODU0_1_START,
        XC_FGSM_ODU10XC_ODU0_2_START,
        XC_FGSM_ODU10XC_ODU0_3_START,
        XC_FGSM_ODU10XC_ODU0_4_START,
        XC_FGSM_ODU10XC_ODU0_5_START,
        XC_FGSM_ODU10XC_ODU0_6_START,
        XC_FGSM_ODU10XC_ODU0_7_START,
        XC_FGSM_ODU10XC_ODU0_8_START,
        XC_FGSM_ODU10XC_ODU0_9_START,
        XC_FGSM_ODU10XC_ODU0_10_START,
        XC_FGSM_ODU10XC_ODU0_11_START,
        XC_FGSM_ODU10XC_ODU0_12_START,
        XC_FGSM_ODU10XC_ODU0_13_START,
        XC_FGSM_ODU10XC_ODU0_14_START,
        XC_FGSM_ODU10XC_ODU0_15_START,
        XC_FGSM_ODU10XC_ODU0_16_START,
        XC_FGSM_ODU10XC_ODU0_17_START,
        XC_FGSM_ODU10XC_ODU0_18_START,
        XC_FGSM_ODU10XC_ODU0_19_START,
        XC_FGSM_ODU10XC_ODU0_20_START,
        XC_FGSM_ODU10XC_ODU0_21_START,
        XC_FGSM_ODU10XC_ODU0_22_START,
        XC_FGSM_ODU10XC_ODU0_23_START,
        XC_FGSM_ODU10XC_ODU0_24_START,
        XC_FGSM_ODU10XC_ODU0_25_START,
        XC_FGSM_ODU10XC_ODU0_26_START,
        XC_FGSM_ODU10XC_ODU0_27_START,
        XC_FGSM_ODU10XC_ODU0_28_START,
        XC_FGSM_ODU10XC_ODU0_29_START,
        XC_FGSM_ODU10XC_ODU0_30_START,
        XC_FGSM_ODU10XC_ODU0_31_START};


// -----------------------------------------------------------------------------------------------
// *************************  SSM40 Definitions *********************
//

//
// Identifiers for each SSM40 facility
//

// ODU XC Facilities:  ODU <--> ODU
#define XC_SSM40_ODUXC_ODU_OTNOTU0_0_FACILITY_ID    (1)
#define XC_SSM40_ODUXC_ODU_OTNOTU1_0_FACILITY_ID    (2)
#define XC_SSM40_ODUXC_ODU_OTNOTU2_0_FACILITY_ID    (3)
#define XC_SSM40_ODUXC_ODU_VCAT0A_0_FACILITY_ID     (4)
#define XC_SSM40_ODUXC_ODU_VCAT0B_0_FACILITY_ID     (5)
#define XC_SSM40_ODUXC_ODU_VCATA_0_FACILITY_ID      (6)
#define XC_SSM40_ODUXC_ODU_VCATB_0_FACILITY_ID      (7)
#define XC_SSM40_ODUXC_ODU_IMUX_0_FACILITY_ID       (8)

#define XC_SSM40_ODUXC_ODU_OTNOTU0_1_FACILITY_ID    (9)
#define XC_SSM40_ODUXC_ODU_OTNOTU1_1_FACILITY_ID    (10)
#define XC_SSM40_ODUXC_ODU_OTNOTU2_1_FACILITY_ID    (11)
#define XC_SSM40_ODUXC_ODU_VCAT0A_1_FACILITY_ID     (12)
#define XC_SSM40_ODUXC_ODU_VCAT0B_1_FACILITY_ID     (13)
#define XC_SSM40_ODUXC_ODU_VCATA_1_FACILITY_ID      (14)
#define XC_SSM40_ODUXC_ODU_VCATB_1_FACILITY_ID      (15)
#define XC_SSM40_ODUXC_ODU_IMUX_1_FACILITY_ID       (16)

// FRMODUXC Facilities:  FRM <--> ODU
#define XC_SSM40_FRMODUXC_FRM_OTU0_0_FACILITY_ID    (17)
#define XC_SSM40_FRMODUXC_FRM_OTU1_0_FACILITY_ID    (18)
#define XC_SSM40_FRMODUXC_FRM_OTU2_0_FACILITY_ID    (19)
#define XC_SSM40_FRMODUXC_FRM_CBR_0_FACILITY_ID     (20)
#define XC_SSM40_FRMODUXC_FRM_CBR10G_0_FACILITY_ID  (21)
#define XC_SSM40_FRMODUXC_FRM_GE_0_FACILITY_ID      (22)
#define XC_SSM40_FRMODUXC_FRM_GE10G_0_FACILITY_ID   (23)

#define XC_SSM40_FRMODUXC_FRM_OTU0_1_FACILITY_ID    (24)
#define XC_SSM40_FRMODUXC_FRM_OTU1_1_FACILITY_ID    (25)
#define XC_SSM40_FRMODUXC_FRM_OTU2_1_FACILITY_ID    (26)
#define XC_SSM40_FRMODUXC_FRM_CBR_1_FACILITY_ID     (27)
#define XC_SSM40_FRMODUXC_FRM_CBR10G_1_FACILITY_ID  (28)
#define XC_SSM40_FRMODUXC_FRM_GE_1_FACILITY_ID      (29)
#define XC_SSM40_FRMODUXC_FRM_GE10G_1_FACILITY_ID   (30)

#define XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_FACILITY_ID (31)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_FACILITY_ID (32)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_FACILITY_ID (33)
#define XC_SSM40_FRMODUXC_ODU_VCATA_0_FACILITY_ID   (34)
#define XC_SSM40_FRMODUXC_ODU_VCATB_0_FACILITY_ID   (35)

#define XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_FACILITY_ID (36)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_FACILITY_ID (37)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_FACILITY_ID (38)
#define XC_SSM40_FRMODUXC_ODU_VCATA_1_FACILITY_ID   (39)
#define XC_SSM40_FRMODUXC_ODU_VCATB_1_FACILITY_ID   (40)

// ODU21 XC Facilities: ODU2 <--> ODU1
#define XC_SSM40_ODU21XC_ODU2_0_0_FACILITY_ID       (41)
#define XC_SSM40_ODU21XC_ODU2_1_0_FACILITY_ID       (42)
#define XC_SSM40_ODU21XC_ODU2_0_1_FACILITY_ID       (43)
#define XC_SSM40_ODU21XC_ODU2_1_1_FACILITY_ID       (44)

#define XC_SSM40_ODU21XC_ODU1_0_0_FACILITY_ID       (45)
#define XC_SSM40_ODU21XC_ODU1_1_0_FACILITY_ID       (46)
#define XC_SSM40_ODU21XC_ODU1_2_0_FACILITY_ID       (47)
#define XC_SSM40_ODU21XC_ODU1_3_0_FACILITY_ID       (48)
#define XC_SSM40_ODU21XC_ODU1_4_0_FACILITY_ID       (49)
#define XC_SSM40_ODU21XC_ODU1_5_0_FACILITY_ID       (50)
#define XC_SSM40_ODU21XC_ODU1_6_0_FACILITY_ID       (51)
#define XC_SSM40_ODU21XC_ODU1_7_0_FACILITY_ID       (52)
#define XC_SSM40_ODU21XC_ODU1_0_1_FACILITY_ID       (53)
#define XC_SSM40_ODU21XC_ODU1_1_1_FACILITY_ID       (54)
#define XC_SSM40_ODU21XC_ODU1_2_1_FACILITY_ID       (55)
#define XC_SSM40_ODU21XC_ODU1_3_1_FACILITY_ID       (56)
#define XC_SSM40_ODU21XC_ODU1_4_1_FACILITY_ID       (57)
#define XC_SSM40_ODU21XC_ODU1_5_1_FACILITY_ID       (58)
#define XC_SSM40_ODU21XC_ODU1_6_1_FACILITY_ID       (59)
#define XC_SSM40_ODU21XC_ODU1_7_1_FACILITY_ID       (60)


// The Maximum number of each SSM40 interface type

#define XC_MAX_SSM40_ODUXC_OTN0_INTF                (2)
#define XC_MAX_SSM40_ODUXC_OTN1_INTF                (2)
#define XC_MAX_SSM40_ODUXC_OTN2_INTF                (2)
#define XC_MAX_SSM40_ODUXC_VCAT_INTF                (4)
#define XC_MAX_SSM40_ODUXC_VCAT0_INTF               (4)
#define XC_MAX_SSM40_ODUXC_IMUX_INTF                (2)

#define XC_MAX_SSM40_FRMODUXC_FRM_OTU0_INTF         (2)
#define XC_MAX_SSM40_FRMODUXC_FRM_OTU1_INTF         (2)
#define XC_MAX_SSM40_FRMODUXC_FRM_OTU2_INTF         (2)
#define XC_MAX_SSM40_FRMODUXC_FRM_CBR_INTF          (2)
#define XC_MAX_SSM40_FRMODUXC_FRM_CBR10G_INTF       (2)
#define XC_MAX_SSM40_FRMODUXC_FRM_GE_INTF           (2)
#define XC_MAX_SSM40_FRMODUXC_FRM_GE10G_INTF        (2)
#define XC_MAX_SSM40_FRMODUXC_ODU_OTNOTU0_INTF      (2)
#define XC_MAX_SSM40_FRMODUXC_ODU_OTNOTU1_INTF      (2)
#define XC_MAX_SSM40_FRMODUXC_ODU_OTNOTU2_INTF      (2)
#define XC_MAX_SSM40_FRMODUXC_ODU_VCAT_INTF         (4)

#define XC_MAX_SSM40_ODU21XC_ODU2_INTF              (4)
#define XC_MAX_SSM40_ODU21XC_ODU1_INTF              (16)

// The Maximum number of connections allowed on each 
// SSM40 interface type

#define XC_MAX_XC_SSM40_ODUXC_OTN0                  (16)
#define XC_MAX_XC_SSM40_ODUXC_OTN1                  (8)
#define XC_MAX_XC_SSM40_ODUXC_OTN2                  (2)
#define XC_MAX_XC_SSM40_ODUXC_VCAT                  (4)
#define XC_MAX_XC_SSM40_ODUXC_VCAT0                 (8)
#define XC_MAX_XC_SSM40_ODUXC_IMUX                  (16)

#define XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU0           (16)
#define XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU1           (8)
#define XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU2           (2)
#define XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR            (16)
#define XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR10G         (2)
#define XC_MAX_XC_SSM40_FRMODUXC_FRM_GE             (16)
#define XC_MAX_XC_SSM40_FRMODUXC_FRM_GE10G          (2)
#define XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU0        (16)
#define XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU1        (8)
#define XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU2        (2)
#define XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT           (8)

#define XC_MAX_XC_SSM40_ODU21XC_ODU2                (4)
#define XC_MAX_XC_SSM40_ODU21XC_ODU1                (1)

// The maximum number of connections on SSM40/SSM40 

#define XC_MAX_XC_SSM40 (\
    (XC_MAX_SSM40_ODUXC_OTN0_INTF           * XC_MAX_XC_SSM40_ODUXC_OTN0)           +\
    (XC_MAX_SSM40_ODUXC_OTN1_INTF           * XC_MAX_XC_SSM40_ODUXC_OTN1)           +\
    (XC_MAX_SSM40_ODUXC_OTN2_INTF           * XC_MAX_XC_SSM40_ODUXC_OTN2)           +\
    (XC_MAX_SSM40_ODUXC_VCAT_INTF           * XC_MAX_XC_SSM40_ODUXC_VCAT)           +\
    (XC_MAX_SSM40_ODUXC_VCAT0_INTF          * XC_MAX_XC_SSM40_ODUXC_VCAT0)          +\
    (XC_MAX_SSM40_ODUXC_IMUX_INTF           * XC_MAX_XC_SSM40_ODUXC_IMUX)           +\
    (XC_MAX_SSM40_FRMODUXC_FRM_OTU0_INTF    * XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU0)    +\
    (XC_MAX_SSM40_FRMODUXC_FRM_OTU1_INTF    * XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU1)    +\
    (XC_MAX_SSM40_FRMODUXC_FRM_OTU2_INTF    * XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU2)    +\
    (XC_MAX_SSM40_FRMODUXC_FRM_CBR_INTF     * XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR)     +\
    (XC_MAX_SSM40_FRMODUXC_FRM_CBR10G_INTF  * XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR10G)  +\
    (XC_MAX_SSM40_FRMODUXC_FRM_GE_INTF      * XC_MAX_XC_SSM40_FRMODUXC_FRM_GE)      +\
    (XC_MAX_SSM40_FRMODUXC_FRM_GE10G_INTF   * XC_MAX_XC_SSM40_FRMODUXC_FRM_GE10G)   +\
    (XC_MAX_SSM40_FRMODUXC_ODU_OTNOTU0_INTF * XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU0) +\
    (XC_MAX_SSM40_FRMODUXC_ODU_OTNOTU1_INTF * XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU1) +\
    (XC_MAX_SSM40_FRMODUXC_ODU_OTNOTU2_INTF * XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU2) +\
    (XC_MAX_SSM40_FRMODUXC_ODU_VCAT_INTF    * XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT)    +\
    (XC_MAX_SSM40_ODU21XC_ODU2_INTF         * XC_MAX_XC_SSM40_ODU21XC_ODU2)         +\
    (XC_MAX_SSM40_ODU21XC_ODU1_INTF         * XC_MAX_XC_SSM40_ODU21XC_ODU1)     )

#define XC_MAX_SSM40_FIXED_MCASTID (\
    (XC_MAX_SSM40_ODUXC_IMUX_INTF           * XC_MAX_XC_SSM40_ODUXC_IMUX)       )

#define XC_MAX_SSM40_XC_IM_ALL (\
    (XC_MAX_SSM40_ODUXC_IMUX_INTF           * XC_MAX_XC_SSM40_ODUXC_IMUX)       )


// 
// Breakdown of SSM40 XC CFG Region
//

#define XC_SSM40_ODUXC_ODU_OTNOTU0_0_START    (0)
#define XC_SSM40_ODUXC_ODU_OTNOTU0_0_END      (XC_SSM40_ODUXC_ODU_OTNOTU0_0_START    + XC_MAX_XC_SSM40_ODUXC_OTN0-1)
#define XC_SSM40_ODUXC_ODU_OTNOTU1_0_START    (XC_SSM40_ODUXC_ODU_OTNOTU0_0_END+1)
#define XC_SSM40_ODUXC_ODU_OTNOTU1_0_END      (XC_SSM40_ODUXC_ODU_OTNOTU1_0_START    + XC_MAX_XC_SSM40_ODUXC_OTN1-1)
#define XC_SSM40_ODUXC_ODU_OTNOTU2_0_START    (XC_SSM40_ODUXC_ODU_OTNOTU1_0_END+1)
#define XC_SSM40_ODUXC_ODU_OTNOTU2_0_END      (XC_SSM40_ODUXC_ODU_OTNOTU2_0_START    + XC_MAX_XC_SSM40_ODUXC_OTN2-1)
#define XC_SSM40_ODUXC_ODU_VCAT0A_0_START     (XC_SSM40_ODUXC_ODU_OTNOTU2_0_END+1)
#define XC_SSM40_ODUXC_ODU_VCAT0A_0_END       (XC_SSM40_ODUXC_ODU_VCAT0A_0_START    + XC_MAX_XC_SSM40_ODUXC_VCAT0-1)
#define XC_SSM40_ODUXC_ODU_VCAT0B_0_START     (XC_SSM40_ODUXC_ODU_VCAT0A_0_END+1)
#define XC_SSM40_ODUXC_ODU_VCAT0B_0_END       (XC_SSM40_ODUXC_ODU_VCAT0B_0_START    + XC_MAX_XC_SSM40_ODUXC_VCAT0-1)
#define XC_SSM40_ODUXC_ODU_VCATA_0_START      (XC_SSM40_ODUXC_ODU_VCAT0B_0_END+1)
#define XC_SSM40_ODUXC_ODU_VCATA_0_END        (XC_SSM40_ODUXC_ODU_VCATA_0_START      + XC_MAX_XC_SSM40_ODUXC_VCAT-1)
#define XC_SSM40_ODUXC_ODU_VCATB_0_START      (XC_SSM40_ODUXC_ODU_VCATA_0_END+1)
#define XC_SSM40_ODUXC_ODU_VCATB_0_END        (XC_SSM40_ODUXC_ODU_VCATB_0_START      + XC_MAX_XC_SSM40_ODUXC_VCAT-1)
#define XC_SSM40_ODUXC_ODU_IMUX_0_START       (XC_SSM40_ODUXC_ODU_VCATB_0_END+1)
#define XC_SSM40_ODUXC_ODU_IMUX_0_END         (XC_SSM40_ODUXC_ODU_IMUX_0_START       + XC_MAX_XC_SSM40_ODUXC_IMUX-1)

#define XC_SSM40_ODUXC_ODU_OTNOTU0_1_START    (XC_SSM40_ODUXC_ODU_IMUX_0_END+1)
#define XC_SSM40_ODUXC_ODU_OTNOTU0_1_END      (XC_SSM40_ODUXC_ODU_OTNOTU0_1_START    + XC_MAX_XC_SSM40_ODUXC_OTN0-1)
#define XC_SSM40_ODUXC_ODU_OTNOTU1_1_START    (XC_SSM40_ODUXC_ODU_OTNOTU0_1_END+1)
#define XC_SSM40_ODUXC_ODU_OTNOTU1_1_END      (XC_SSM40_ODUXC_ODU_OTNOTU1_1_START    + XC_MAX_XC_SSM40_ODUXC_OTN1-1)
#define XC_SSM40_ODUXC_ODU_OTNOTU2_1_START    (XC_SSM40_ODUXC_ODU_OTNOTU1_1_END+1)
#define XC_SSM40_ODUXC_ODU_OTNOTU2_1_END      (XC_SSM40_ODUXC_ODU_OTNOTU2_1_START    + XC_MAX_XC_SSM40_ODUXC_OTN2-1)
#define XC_SSM40_ODUXC_ODU_VCAT0A_1_START     (XC_SSM40_ODUXC_ODU_OTNOTU2_1_END+1)
#define XC_SSM40_ODUXC_ODU_VCAT0A_1_END       (XC_SSM40_ODUXC_ODU_VCAT0A_1_START    + XC_MAX_XC_SSM40_ODUXC_VCAT0-1)
#define XC_SSM40_ODUXC_ODU_VCAT0B_1_START     (XC_SSM40_ODUXC_ODU_VCAT0A_1_END+1)
#define XC_SSM40_ODUXC_ODU_VCAT0B_1_END       (XC_SSM40_ODUXC_ODU_VCAT0B_1_START    + XC_MAX_XC_SSM40_ODUXC_VCAT0-1)
#define XC_SSM40_ODUXC_ODU_VCATA_1_START      (XC_SSM40_ODUXC_ODU_VCAT0B_1_END+1)
#define XC_SSM40_ODUXC_ODU_VCATA_1_END        (XC_SSM40_ODUXC_ODU_VCATA_1_START      + XC_MAX_XC_SSM40_ODUXC_VCAT-1)
#define XC_SSM40_ODUXC_ODU_VCATB_1_START      (XC_SSM40_ODUXC_ODU_VCATA_1_END+1)
#define XC_SSM40_ODUXC_ODU_VCATB_1_END        (XC_SSM40_ODUXC_ODU_VCATB_1_START      + XC_MAX_XC_SSM40_ODUXC_VCAT-1)
#define XC_SSM40_ODUXC_ODU_IMUX_1_START       (XC_SSM40_ODUXC_ODU_VCATB_1_END+1)
#define XC_SSM40_ODUXC_ODU_IMUX_1_END         (XC_SSM40_ODUXC_ODU_IMUX_1_START       + XC_MAX_XC_SSM40_ODUXC_IMUX-1)

#define XC_SSM40_FRMODUXC_FRM_OTU0_0_START    (XC_SSM40_ODUXC_ODU_IMUX_1_END+1)
#define XC_SSM40_FRMODUXC_FRM_OTU0_0_END      (XC_SSM40_FRMODUXC_FRM_OTU0_0_START    + XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU0-1)
#define XC_SSM40_FRMODUXC_FRM_OTU1_0_START    (XC_SSM40_FRMODUXC_FRM_OTU0_0_END+1)
#define XC_SSM40_FRMODUXC_FRM_OTU1_0_END      (XC_SSM40_FRMODUXC_FRM_OTU1_0_START    + XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU1-1)
#define XC_SSM40_FRMODUXC_FRM_OTU2_0_START    (XC_SSM40_FRMODUXC_FRM_OTU1_0_END+1)
#define XC_SSM40_FRMODUXC_FRM_OTU2_0_END      (XC_SSM40_FRMODUXC_FRM_OTU2_0_START    + XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU2-1)
#define XC_SSM40_FRMODUXC_FRM_CBR_0_START     (XC_SSM40_FRMODUXC_FRM_OTU2_0_END+1)
#define XC_SSM40_FRMODUXC_FRM_CBR_0_END       (XC_SSM40_FRMODUXC_FRM_CBR_0_START     + XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR-1)
#define XC_SSM40_FRMODUXC_FRM_CBR10G_0_START  (XC_SSM40_FRMODUXC_FRM_CBR_0_END+1)
#define XC_SSM40_FRMODUXC_FRM_CBR10G_0_END    (XC_SSM40_FRMODUXC_FRM_CBR10G_0_START  + XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR10G-1)
#define XC_SSM40_FRMODUXC_FRM_GE_0_START      (XC_SSM40_FRMODUXC_FRM_CBR10G_0_END+1)
#define XC_SSM40_FRMODUXC_FRM_GE_0_END        (XC_SSM40_FRMODUXC_FRM_GE_0_START      + XC_MAX_XC_SSM40_FRMODUXC_FRM_GE-1)
#define XC_SSM40_FRMODUXC_FRM_GE10G_0_START   (XC_SSM40_FRMODUXC_FRM_GE_0_END+1)
#define XC_SSM40_FRMODUXC_FRM_GE10G_0_END     (XC_SSM40_FRMODUXC_FRM_GE10G_0_START   + XC_MAX_XC_SSM40_FRMODUXC_FRM_GE10G-1)

#define XC_SSM40_FRMODUXC_FRM_OTU0_1_START    (XC_SSM40_FRMODUXC_FRM_GE10G_0_END+1)
#define XC_SSM40_FRMODUXC_FRM_OTU0_1_END      (XC_SSM40_FRMODUXC_FRM_OTU0_1_START    + XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU0-1)
#define XC_SSM40_FRMODUXC_FRM_OTU1_1_START    (XC_SSM40_FRMODUXC_FRM_OTU0_1_END+1)
#define XC_SSM40_FRMODUXC_FRM_OTU1_1_END      (XC_SSM40_FRMODUXC_FRM_OTU1_1_START    + XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU1-1)
#define XC_SSM40_FRMODUXC_FRM_OTU2_1_START    (XC_SSM40_FRMODUXC_FRM_OTU1_1_END+1)
#define XC_SSM40_FRMODUXC_FRM_OTU2_1_END      (XC_SSM40_FRMODUXC_FRM_OTU2_1_START    + XC_MAX_XC_SSM40_FRMODUXC_FRM_OTU2-1)
#define XC_SSM40_FRMODUXC_FRM_CBR_1_START     (XC_SSM40_FRMODUXC_FRM_OTU2_1_END+1)
#define XC_SSM40_FRMODUXC_FRM_CBR_1_END       (XC_SSM40_FRMODUXC_FRM_CBR_1_START     + XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR-1)
#define XC_SSM40_FRMODUXC_FRM_CBR10G_1_START  (XC_SSM40_FRMODUXC_FRM_CBR_1_END+1)
#define XC_SSM40_FRMODUXC_FRM_CBR10G_1_END    (XC_SSM40_FRMODUXC_FRM_CBR10G_1_START  + XC_MAX_XC_SSM40_FRMODUXC_FRM_CBR10G-1)
#define XC_SSM40_FRMODUXC_FRM_GE_1_START      (XC_SSM40_FRMODUXC_FRM_CBR10G_1_END+1)
#define XC_SSM40_FRMODUXC_FRM_GE_1_END        (XC_SSM40_FRMODUXC_FRM_GE_1_START      + XC_MAX_XC_SSM40_FRMODUXC_FRM_GE-1)
#define XC_SSM40_FRMODUXC_FRM_GE10G_1_START   (XC_SSM40_FRMODUXC_FRM_GE_1_END+1)
#define XC_SSM40_FRMODUXC_FRM_GE10G_1_END     (XC_SSM40_FRMODUXC_FRM_GE10G_1_START   + XC_MAX_XC_SSM40_FRMODUXC_FRM_GE10G-1)

#define XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_START (XC_SSM40_FRMODUXC_FRM_GE10G_1_END+1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_END   (XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_START + XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU0-1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_START (XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_END+1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_END   (XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_START + XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU1-1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_START (XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_END+1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_END   (XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_START + XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU2-1)
#define XC_SSM40_FRMODUXC_ODU_VCATA_0_START   (XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_END+1)
#define XC_SSM40_FRMODUXC_ODU_VCATA_0_END     (XC_SSM40_FRMODUXC_ODU_VCATA_0_START   + XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT-1)
#define XC_SSM40_FRMODUXC_ODU_VCATB_0_START   (XC_SSM40_FRMODUXC_ODU_VCATA_0_END+1)
#define XC_SSM40_FRMODUXC_ODU_VCATB_0_END     (XC_SSM40_FRMODUXC_ODU_VCATB_0_START   + XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT-1)

#define XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_START (XC_SSM40_FRMODUXC_ODU_VCATB_0_END+1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_END   (XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_START + XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU0-1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_START (XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_END+1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_END   (XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_START + XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU1-1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_START (XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_END+1)
#define XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_END   (XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_START + XC_MAX_XC_SSM40_FRMODUXC_ODU_OTNOTU2-1)
#define XC_SSM40_FRMODUXC_ODU_VCATA_1_START   (XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_END+1)
#define XC_SSM40_FRMODUXC_ODU_VCATA_1_END     (XC_SSM40_FRMODUXC_ODU_VCATA_1_START   + XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT-1)
#define XC_SSM40_FRMODUXC_ODU_VCATB_1_START   (XC_SSM40_FRMODUXC_ODU_VCATA_1_END+1)
#define XC_SSM40_FRMODUXC_ODU_VCATB_1_END     (XC_SSM40_FRMODUXC_ODU_VCATB_1_START   + XC_MAX_XC_SSM40_FRMODUXC_ODU_VCAT-1)

#define XC_SSM40_ODU21XC_ODU2_0_0_START       (XC_SSM40_FRMODUXC_ODU_VCATB_1_END+1)
#define XC_SSM40_ODU21XC_ODU2_0_0_END         (XC_SSM40_ODU21XC_ODU2_0_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU2-1)
#define XC_SSM40_ODU21XC_ODU2_1_0_START       (XC_SSM40_ODU21XC_ODU2_0_0_END+1)
#define XC_SSM40_ODU21XC_ODU2_1_0_END         (XC_SSM40_ODU21XC_ODU2_1_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU2-1)
#define XC_SSM40_ODU21XC_ODU2_0_1_START       (XC_SSM40_ODU21XC_ODU2_1_0_END+1)
#define XC_SSM40_ODU21XC_ODU2_0_1_END         (XC_SSM40_ODU21XC_ODU2_0_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU2-1)
#define XC_SSM40_ODU21XC_ODU2_1_1_START       (XC_SSM40_ODU21XC_ODU2_0_1_END+1)
#define XC_SSM40_ODU21XC_ODU2_1_1_END         (XC_SSM40_ODU21XC_ODU2_1_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU2-1)
#define XC_SSM40_ODU21XC_ODU1_0_0_START       (XC_SSM40_ODU21XC_ODU2_1_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_0_0_END         (XC_SSM40_ODU21XC_ODU1_0_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_1_0_START       (XC_SSM40_ODU21XC_ODU1_0_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_1_0_END         (XC_SSM40_ODU21XC_ODU1_1_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_2_0_START       (XC_SSM40_ODU21XC_ODU1_1_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_2_0_END         (XC_SSM40_ODU21XC_ODU1_2_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_3_0_START       (XC_SSM40_ODU21XC_ODU1_2_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_3_0_END         (XC_SSM40_ODU21XC_ODU1_3_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_4_0_START       (XC_SSM40_ODU21XC_ODU1_3_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_4_0_END         (XC_SSM40_ODU21XC_ODU1_4_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_5_0_START       (XC_SSM40_ODU21XC_ODU1_4_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_5_0_END         (XC_SSM40_ODU21XC_ODU1_5_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_6_0_START       (XC_SSM40_ODU21XC_ODU1_5_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_6_0_END         (XC_SSM40_ODU21XC_ODU1_6_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_7_0_START       (XC_SSM40_ODU21XC_ODU1_6_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_7_0_END         (XC_SSM40_ODU21XC_ODU1_7_0_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_0_1_START       (XC_SSM40_ODU21XC_ODU1_7_0_END+1)
#define XC_SSM40_ODU21XC_ODU1_0_1_END         (XC_SSM40_ODU21XC_ODU1_0_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_1_1_START       (XC_SSM40_ODU21XC_ODU1_0_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_1_1_END         (XC_SSM40_ODU21XC_ODU1_1_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_2_1_START       (XC_SSM40_ODU21XC_ODU1_1_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_2_1_END         (XC_SSM40_ODU21XC_ODU1_2_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_3_1_START       (XC_SSM40_ODU21XC_ODU1_2_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_3_1_END         (XC_SSM40_ODU21XC_ODU1_3_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_4_1_START       (XC_SSM40_ODU21XC_ODU1_3_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_4_1_END         (XC_SSM40_ODU21XC_ODU1_4_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_5_1_START       (XC_SSM40_ODU21XC_ODU1_4_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_5_1_END         (XC_SSM40_ODU21XC_ODU1_5_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_6_1_START       (XC_SSM40_ODU21XC_ODU1_5_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_6_1_END         (XC_SSM40_ODU21XC_ODU1_6_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)
#define XC_SSM40_ODU21XC_ODU1_7_1_START       (XC_SSM40_ODU21XC_ODU1_6_1_END+1)
#define XC_SSM40_ODU21XC_ODU1_7_1_END         (XC_SSM40_ODU21XC_ODU1_7_1_START       + XC_MAX_XC_SSM40_ODU21XC_ODU1-1)


// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as SSM40 facility identifiers ***
const int SSM40ConfigMap[] = {0,

      // ODUXC
      XC_SSM40_ODUXC_ODU_OTNOTU0_0_START,
      XC_SSM40_ODUXC_ODU_OTNOTU1_0_START,
      XC_SSM40_ODUXC_ODU_OTNOTU2_0_START,
      XC_SSM40_ODUXC_ODU_VCAT0A_0_START,
      XC_SSM40_ODUXC_ODU_VCAT0B_0_START,
      XC_SSM40_ODUXC_ODU_VCATA_0_START,
      XC_SSM40_ODUXC_ODU_VCATB_0_START,
      XC_SSM40_ODUXC_ODU_IMUX_0_START,
      XC_SSM40_ODUXC_ODU_OTNOTU0_1_START,
      XC_SSM40_ODUXC_ODU_OTNOTU1_1_START,
      XC_SSM40_ODUXC_ODU_OTNOTU2_1_START,
      XC_SSM40_ODUXC_ODU_VCAT0A_1_START,
      XC_SSM40_ODUXC_ODU_VCAT0B_1_START,
      XC_SSM40_ODUXC_ODU_VCATA_1_START,
      XC_SSM40_ODUXC_ODU_VCATB_1_START,
      XC_SSM40_ODUXC_ODU_IMUX_1_START,

      // FRMODUXC
      XC_SSM40_FRMODUXC_FRM_OTU0_0_START,
      XC_SSM40_FRMODUXC_FRM_OTU1_0_START,
      XC_SSM40_FRMODUXC_FRM_OTU2_0_START,
      XC_SSM40_FRMODUXC_FRM_CBR_0_START,
      XC_SSM40_FRMODUXC_FRM_CBR10G_0_START,
      XC_SSM40_FRMODUXC_FRM_GE_0_START,
      XC_SSM40_FRMODUXC_FRM_GE10G_0_START,
      XC_SSM40_FRMODUXC_FRM_OTU0_1_START,
      XC_SSM40_FRMODUXC_FRM_OTU1_1_START,
      XC_SSM40_FRMODUXC_FRM_OTU2_1_START,
      XC_SSM40_FRMODUXC_FRM_CBR_1_START,
      XC_SSM40_FRMODUXC_FRM_CBR10G_1_START,
      XC_SSM40_FRMODUXC_FRM_GE_1_START,
      XC_SSM40_FRMODUXC_FRM_GE10G_1_START,
      XC_SSM40_FRMODUXC_ODU_OTNOTU0_0_START,
      XC_SSM40_FRMODUXC_ODU_OTNOTU1_0_START,
      XC_SSM40_FRMODUXC_ODU_OTNOTU2_0_START,
      XC_SSM40_FRMODUXC_ODU_VCATA_0_START,
      XC_SSM40_FRMODUXC_ODU_VCATB_0_START,
      XC_SSM40_FRMODUXC_ODU_OTNOTU0_1_START,
      XC_SSM40_FRMODUXC_ODU_OTNOTU1_1_START,
      XC_SSM40_FRMODUXC_ODU_OTNOTU2_1_START,
      XC_SSM40_FRMODUXC_ODU_VCATA_1_START,
      XC_SSM40_FRMODUXC_ODU_VCATB_1_START,

      // ODU21XC
      XC_SSM40_ODU21XC_ODU2_0_0_START,
      XC_SSM40_ODU21XC_ODU2_1_0_START,
      XC_SSM40_ODU21XC_ODU2_0_1_START,
      XC_SSM40_ODU21XC_ODU2_1_1_START,
      XC_SSM40_ODU21XC_ODU1_0_0_START,
      XC_SSM40_ODU21XC_ODU1_1_0_START,
      XC_SSM40_ODU21XC_ODU1_2_0_START,
      XC_SSM40_ODU21XC_ODU1_3_0_START,
      XC_SSM40_ODU21XC_ODU1_4_0_START,
      XC_SSM40_ODU21XC_ODU1_5_0_START,
      XC_SSM40_ODU21XC_ODU1_6_0_START,
      XC_SSM40_ODU21XC_ODU1_7_0_START,
      XC_SSM40_ODU21XC_ODU1_0_1_START,
      XC_SSM40_ODU21XC_ODU1_1_1_START,
      XC_SSM40_ODU21XC_ODU1_2_1_START,
      XC_SSM40_ODU21XC_ODU1_3_1_START,
      XC_SSM40_ODU21XC_ODU1_4_1_START,
      XC_SSM40_ODU21XC_ODU1_5_1_START,
      XC_SSM40_ODU21XC_ODU1_6_1_START,
      XC_SSM40_ODU21XC_ODU1_7_1_START };

// -----------------------------------------------------------------------------------------------
// *************************  HGTMM Definitions *********************
//

#define HGTMM_XC_ODU3_CLIENT_1_FACILITY_ID            (1)
#define HGTMM_XC_ODU3_CLIENT_2_FACILITY_ID            (2)
#define HGTMM_XC_ODU2F_CLIENT_3_FACILITY_ID           (3)
#define HGTMM_XC_ODU2F_CLIENT_4_FACILITY_ID           (4)
#define HGTMM_XC_ODU2F_CLIENT_5_FACILITY_ID           (5)
#define HGTMM_XC_ODU2F_CLIENT_6_FACILITY_ID           (6)
#define HGTMM_XC_ODU2F_CLIENT_7_FACILITY_ID           (7)
#define HGTMM_XC_ODU2F_CLIENT_8_FACILITY_ID           (8)
#define HGTMM_XC_ODU2F_CLIENT_9_FACILITY_ID           (9)
#define HGTMM_XC_ODU2F_CLIENT_10_FACILITY_ID         (10)
#define HGTMM_XC_ODU2F_CLIENT_11_FACILITY_ID         (11)
#define HGTMM_XC_ODU2F_CLIENT_12_FACILITY_ID         (12)
#define HGTMM_XC_ODU4_LINE_FACILITY_ID               (13)
#define HGTMM_XC_ODU4_MUX_FACILITY_ID                (14)
#define HGTMM_XC_ODU4_DEMUX_ODU2_FACILITY_ID         (15)
#define HGTMM_XC_ODU4_DEMUX_ODUF_FACILITY_ID         (16)
#define HGTMM_XC_ODU4_DEMUX_ODU3_FACILITY_ID         (17)

#define XC_MAX_XC_HGTMM_ODU43XC_ODU3	             (2)
#define XC_MAX_XC_HGTMM_ODU42XC_ODU2	             (10)
#define XC_MAX_XC_HGTMM_ODU4FXC_ODUF	             (10)
#define XC_MAX_XC_HGTMM_CLIENT_FACILITY	             (12)
#define XC_MAX_XC_HGTMM_TRIB_PORT_COUNT              (80)
#define XC_MAX_XC_HGTMM_TRIB_SLOT_COUNT              (80)

// HGTM-M ODU XC
#define XC_HGTMM_ODU3_CLIENT_1_START                 (0) 
#define XC_HGTMM_ODU3_CLIENT_1_END                   (XC_HGTMM_ODU3_CLIENT_1_START)
#define XC_HGTMM_ODU3_CLIENT_2_START                 (XC_HGTMM_ODU3_CLIENT_1_END + 1) 
#define XC_HGTMM_ODU3_CLIENT_2_END                   (XC_HGTMM_ODU3_CLIENT_2_START)
#define XC_HGTMM_ODU2F_CLIENT_3_START                (XC_HGTMM_ODU3_CLIENT_2_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_3_END                  (XC_HGTMM_ODU2F_CLIENT_3_START)
#define XC_HGTMM_ODU2F_CLIENT_4_START                (XC_HGTMM_ODU2F_CLIENT_3_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_4_END                  (XC_HGTMM_ODU2F_CLIENT_4_START)
#define XC_HGTMM_ODU2F_CLIENT_5_START                (XC_HGTMM_ODU2F_CLIENT_4_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_5_END                  (XC_HGTMM_ODU2F_CLIENT_5_START)
#define XC_HGTMM_ODU2F_CLIENT_6_START                (XC_HGTMM_ODU2F_CLIENT_5_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_6_END                  (XC_HGTMM_ODU2F_CLIENT_6_START)
#define XC_HGTMM_ODU2F_CLIENT_7_START                (XC_HGTMM_ODU2F_CLIENT_6_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_7_END                  (XC_HGTMM_ODU2F_CLIENT_7_START)
#define XC_HGTMM_ODU2F_CLIENT_8_START                (XC_HGTMM_ODU2F_CLIENT_7_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_8_END                  (XC_HGTMM_ODU2F_CLIENT_8_START)
#define XC_HGTMM_ODU2F_CLIENT_9_START                (XC_HGTMM_ODU2F_CLIENT_8_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_9_END                  (XC_HGTMM_ODU2F_CLIENT_9_START)
#define XC_HGTMM_ODU2F_CLIENT_10_START               (XC_HGTMM_ODU2F_CLIENT_9_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_10_END                 (XC_HGTMM_ODU2F_CLIENT_10_START)
#define XC_HGTMM_ODU2F_CLIENT_11_START               (XC_HGTMM_ODU2F_CLIENT_10_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_11_END                 (XC_HGTMM_ODU2F_CLIENT_11_START)
#define XC_HGTMM_ODU2F_CLIENT_12_START               (XC_HGTMM_ODU2F_CLIENT_11_END + 1)
#define XC_HGTMM_ODU2F_CLIENT_12_END                 (XC_HGTMM_ODU2F_CLIENT_12_START)
#define XC_HGTMM_ODU4_LINE_TRIB_PORT_START           (XC_HGTMM_ODU2F_CLIENT_12_END + 1) 
#define XC_HGTMM_ODU4_LINE_TRIB_PORT_END             (XC_HGTMM_ODU4_LINE_TRIB_PORT_START + XC_MAX_XC_HGTMM_TRIB_PORT_COUNT - 1) 

// HGTM-M ODU4 80 TRIB SLOTS
#define HGTMM_XC_ODU4_MUX_TRIBSLOT_START             (XC_HGTMM_ODU4_LINE_TRIB_PORT_END + 1)
#define HGTMM_XC_ODU4_MUX_TRIBSLOT_END               (HGTMM_XC_ODU4_MUX_TRIBSLOT_START + XC_MAX_XC_HGTMM_TRIB_SLOT_COUNT - 1)

#define XC_MAX_XC_HGTMM                              (HGTMM_XC_ODU4_MUX_TRIBSLOT_END + 1)

const int HGTMMConfigMap[] = {0,

    XC_HGTMM_ODU3_CLIENT_1_START, 
    XC_HGTMM_ODU3_CLIENT_2_START, 
    XC_HGTMM_ODU2F_CLIENT_3_START, 
    XC_HGTMM_ODU2F_CLIENT_4_START, 
    XC_HGTMM_ODU2F_CLIENT_5_START, 
    XC_HGTMM_ODU2F_CLIENT_6_START, 
    XC_HGTMM_ODU2F_CLIENT_7_START, 
    XC_HGTMM_ODU2F_CLIENT_8_START, 
    XC_HGTMM_ODU2F_CLIENT_9_START, 
    XC_HGTMM_ODU2F_CLIENT_10_START, 
    XC_HGTMM_ODU2F_CLIENT_11_START, 
    XC_HGTMM_ODU2F_CLIENT_12_START, 

    XC_HGTMM_ODU4_LINE_TRIB_PORT_START,

    HGTMM_XC_ODU4_MUX_TRIBSLOT_START, 
};

// -----------------------------------------------------------------------------------------------
// *************************  OSM20 Definitions *********************
//

//
// Identifiers for each OSM20 facility
//

// ODU XC Facilities:  ODU <--> ODU
#define XC_OSM20_ODUXC_ODUK_0_FACILITY_ID               (1)    //8*ODU0/flex CRS
#define XC_OSM20_ODUXC_ODUK_1_FACILITY_ID               (2)    //8*ODU0/flex CRS
#define XC_OSM20_ODUXC_ODUK_2_FACILITY_ID               (3)    //8*ODU0/flex CRS
#define XC_OSM20_ODUXC_ODUK_3_FACILITY_ID               (4)    //8*ODU0/flex CRS
#define XC_OSM20_ODUXC_ODU1_FACILITY_ID                 (5)    //8*ODU1 CRS
#define XC_OSM20_ODUXC_ODU2_FACILITY_ID                 (6)    //2*ODU2 CRS

#define XC_OSM20_ODUXC_ODUKPP_ODUK0_FACILITY_ID         (7)    //8*CBR CRS
#define XC_OSM20_ODUXC_ODUKPP_ODUK1_FACILITY_ID         (8)    //8*CBR CRS
#define XC_OSM20_ODUXC_ODUKPP_ODU1_FACILITY_ID          (9)    //8*CBR CRS
#define XC_OSM20_ODUXC_ODUKPP_ODU2_FACILITY_ID          (10)   //8*CBR CRS

#define XC_OSM20_ODUXC_IMUX_FACILITY_ID                 (11)   //16*CRS(MAX for 20G)

// FRMODUXC Facilities:  FRM <--> ODU
#define XC_OSM20_FRMODUXC_FRM_OTUK_FACILITY_ID          (12)   //32*ODU0/flex Frame CRS
#define XC_OSM20_FRMODUXC_FRM_OTU1_FACILITY_ID          (13)   //16*OTU1 Frame CRS
#define XC_OSM20_FRMODUXC_FRM_OTU2_FACILITY_ID          (14)   //2*OTU2 Frame CRS

#define XC_OSM20_FRMODUXC_FRM_CBR_FACILITY_ID           (15)   //16*OC48/STM16 CRS
#define XC_OSM20_FRMODUXC_FRM_CBR10G_FACILITY_ID        (16)   //2*OC192/STM64 CRS
#define XC_OSM20_FRMODUXC_FRM_GE_FACILITY_ID            (17)   //16*GE CRS
#define XC_OSM20_FRMODUXC_FRM_GE10G_FACILITY_ID         (18)   //2*10 GE CRS

#define XC_OSM20_FRMODUXC_ODU_OTUK_FACILITY_ID          (19)   //32
#define XC_OSM20_FRMODUXC_ODU_OTU1_FACILITY_ID          (20)   //16
#define XC_OSM20_FRMODUXC_ODU_OTU2_FACILITY_ID          (21)   //2

#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID    (22)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID    (23)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID    (24)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID    (25)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID    (26)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID    (27)

// ODU21 MUX
#define XC_OSM20_ODU21XC_ODU2_0_FACILITY_ID             (28)
#define XC_OSM20_ODU21XC_ODU2_1_FACILITY_ID             (29)

#define XC_OSM20_ODU21XC_ODU1_0_FACILITY_ID             (30)
#define XC_OSM20_ODU21XC_ODU1_1_FACILITY_ID             (31)
#define XC_OSM20_ODU21XC_ODU1_2_FACILITY_ID             (32)
#define XC_OSM20_ODU21XC_ODU1_3_FACILITY_ID             (33)
#define XC_OSM20_ODU21XC_ODU1_4_FACILITY_ID             (34)
#define XC_OSM20_ODU21XC_ODU1_5_FACILITY_ID             (35)
#define XC_OSM20_ODU21XC_ODU1_6_FACILITY_ID             (36)
#define XC_OSM20_ODU21XC_ODU1_7_FACILITY_ID             (37)
#define XC_OSM20_ODU21XC_ODU1_8_FACILITY_ID             (38)
#define XC_OSM20_ODU21XC_ODU1_9_FACILITY_ID             (39)
#define XC_OSM20_ODU21XC_ODU1_10_FACILITY_ID            (40)
#define XC_OSM20_ODU21XC_ODU1_11_FACILITY_ID            (41)
#define XC_OSM20_ODU21XC_ODU1_12_FACILITY_ID            (42)
#define XC_OSM20_ODU21XC_ODU1_13_FACILITY_ID            (43)
#define XC_OSM20_ODU21XC_ODU1_14_FACILITY_ID            (44)
#define XC_OSM20_ODU21XC_ODU1_15_FACILITY_ID            (45)

// ODU20 MUX
#define XC_OSM20_ODU20XC_ODU2_0_FACILITY_ID             (46)
#define XC_OSM20_ODU20XC_ODU2_1_FACILITY_ID             (47)

#define XC_OSM20_ODU20XC_ODU0_0_FACILITY_ID             (48)
#define XC_OSM20_ODU20XC_ODU0_1_FACILITY_ID             (49)
#define XC_OSM20_ODU20XC_ODU0_2_FACILITY_ID             (50)
#define XC_OSM20_ODU20XC_ODU0_3_FACILITY_ID             (51)
#define XC_OSM20_ODU20XC_ODU0_4_FACILITY_ID             (52)
#define XC_OSM20_ODU20XC_ODU0_5_FACILITY_ID             (53)
#define XC_OSM20_ODU20XC_ODU0_6_FACILITY_ID             (54)
#define XC_OSM20_ODU20XC_ODU0_7_FACILITY_ID             (55)
#define XC_OSM20_ODU20XC_ODU0_8_FACILITY_ID             (56)
#define XC_OSM20_ODU20XC_ODU0_9_FACILITY_ID             (57)
#define XC_OSM20_ODU20XC_ODU0_10_FACILITY_ID            (58)
#define XC_OSM20_ODU20XC_ODU0_11_FACILITY_ID            (59)
#define XC_OSM20_ODU20XC_ODU0_12_FACILITY_ID            (60)
#define XC_OSM20_ODU20XC_ODU0_13_FACILITY_ID            (61)
#define XC_OSM20_ODU20XC_ODU0_14_FACILITY_ID            (62)
#define XC_OSM20_ODU20XC_ODU0_15_FACILITY_ID            (63)
#define XC_OSM20_ODU20XC_ODU0_16_FACILITY_ID            (64)
#define XC_OSM20_ODU20XC_ODU0_17_FACILITY_ID            (65)
#define XC_OSM20_ODU20XC_ODU0_18_FACILITY_ID            (66)
#define XC_OSM20_ODU20XC_ODU0_19_FACILITY_ID            (67)
#define XC_OSM20_ODU20XC_ODU0_20_FACILITY_ID            (68)
#define XC_OSM20_ODU20XC_ODU0_21_FACILITY_ID            (69)
#define XC_OSM20_ODU20XC_ODU0_22_FACILITY_ID            (70)
#define XC_OSM20_ODU20XC_ODU0_23_FACILITY_ID            (71)
#define XC_OSM20_ODU20XC_ODU0_24_FACILITY_ID            (72)
#define XC_OSM20_ODU20XC_ODU0_25_FACILITY_ID            (73)
#define XC_OSM20_ODU20XC_ODU0_26_FACILITY_ID            (74)
#define XC_OSM20_ODU20XC_ODU0_27_FACILITY_ID            (75)
#define XC_OSM20_ODU20XC_ODU0_28_FACILITY_ID            (76)
#define XC_OSM20_ODU20XC_ODU0_29_FACILITY_ID            (77)
#define XC_OSM20_ODU20XC_ODU0_30_FACILITY_ID            (78)
#define XC_OSM20_ODU20XC_ODU0_31_FACILITY_ID            (79)

// ODU2F MUX
#define XC_OSM20_ODU2FXC_ODU2_0_FACILITY_ID             (80)
#define XC_OSM20_ODU2FXC_ODU2_1_FACILITY_ID             (81)

#define XC_OSM20_ODU2FXC_ODUF_0_FACILITY_ID             (82)
#define XC_OSM20_ODU2FXC_ODUF_1_FACILITY_ID             (83)
#define XC_OSM20_ODU2FXC_ODUF_2_FACILITY_ID             (84)
#define XC_OSM20_ODU2FXC_ODUF_3_FACILITY_ID             (85)
#define XC_OSM20_ODU2FXC_ODUF_4_FACILITY_ID             (86)
#define XC_OSM20_ODU2FXC_ODUF_5_FACILITY_ID             (87)
#define XC_OSM20_ODU2FXC_ODUF_6_FACILITY_ID             (88)
#define XC_OSM20_ODU2FXC_ODUF_7_FACILITY_ID             (89)
#define XC_OSM20_ODU2FXC_ODUF_8_FACILITY_ID             (90)
#define XC_OSM20_ODU2FXC_ODUF_9_FACILITY_ID             (91)
#define XC_OSM20_ODU2FXC_ODUF_10_FACILITY_ID            (92)
#define XC_OSM20_ODU2FXC_ODUF_11_FACILITY_ID            (93)
#define XC_OSM20_ODU2FXC_ODUF_12_FACILITY_ID            (94)
#define XC_OSM20_ODU2FXC_ODUF_13_FACILITY_ID            (95)
#define XC_OSM20_ODU2FXC_ODUF_14_FACILITY_ID            (96)
#define XC_OSM20_ODU2FXC_ODUF_15_FACILITY_ID            (97)
#define XC_OSM20_ODU2FXC_ODUF_16_FACILITY_ID            (98)
#define XC_OSM20_ODU2FXC_ODUF_17_FACILITY_ID            (99)
#define XC_OSM20_ODU2FXC_ODUF_18_FACILITY_ID            (100)
#define XC_OSM20_ODU2FXC_ODUF_19_FACILITY_ID            (101)
#define XC_OSM20_ODU2FXC_ODUF_20_FACILITY_ID            (102)
#define XC_OSM20_ODU2FXC_ODUF_21_FACILITY_ID            (103)
#define XC_OSM20_ODU2FXC_ODUF_22_FACILITY_ID            (104)
#define XC_OSM20_ODU2FXC_ODUF_23_FACILITY_ID            (105)
#define XC_OSM20_ODU2FXC_ODUF_24_FACILITY_ID            (106)
#define XC_OSM20_ODU2FXC_ODUF_25_FACILITY_ID            (107)
#define XC_OSM20_ODU2FXC_ODUF_26_FACILITY_ID            (108)
#define XC_OSM20_ODU2FXC_ODUF_27_FACILITY_ID            (109)
#define XC_OSM20_ODU2FXC_ODUF_28_FACILITY_ID            (110)
#define XC_OSM20_ODU2FXC_ODUF_29_FACILITY_ID            (111)
#define XC_OSM20_ODU2FXC_ODUF_30_FACILITY_ID            (112)
#define XC_OSM20_ODU2FXC_ODUF_31_FACILITY_ID            (113)

// ODU10 MUX
#define XC_OSM20_ODU10XC_ODU1_0_FACILITY_ID             (114)
#define XC_OSM20_ODU10XC_ODU1_1_FACILITY_ID             (115)
#define XC_OSM20_ODU10XC_ODU1_2_FACILITY_ID             (116)
#define XC_OSM20_ODU10XC_ODU1_3_FACILITY_ID             (117)
#define XC_OSM20_ODU10XC_ODU1_4_FACILITY_ID             (118)
#define XC_OSM20_ODU10XC_ODU1_5_FACILITY_ID             (119)
#define XC_OSM20_ODU10XC_ODU1_6_FACILITY_ID             (120)
#define XC_OSM20_ODU10XC_ODU1_7_FACILITY_ID             (121)
#define XC_OSM20_ODU10XC_ODU1_8_FACILITY_ID             (122)
#define XC_OSM20_ODU10XC_ODU1_9_FACILITY_ID             (123)
#define XC_OSM20_ODU10XC_ODU1_10_FACILITY_ID            (124)
#define XC_OSM20_ODU10XC_ODU1_11_FACILITY_ID            (125)
#define XC_OSM20_ODU10XC_ODU1_12_FACILITY_ID            (126)
#define XC_OSM20_ODU10XC_ODU1_13_FACILITY_ID            (127)
#define XC_OSM20_ODU10XC_ODU1_14_FACILITY_ID            (128)
#define XC_OSM20_ODU10XC_ODU1_15_FACILITY_ID            (129)

#define XC_OSM20_ODU10XC_ODU0_0_FACILITY_ID             (130)
#define XC_OSM20_ODU10XC_ODU0_1_FACILITY_ID             (131)
#define XC_OSM20_ODU10XC_ODU0_2_FACILITY_ID             (132)
#define XC_OSM20_ODU10XC_ODU0_3_FACILITY_ID             (133)
#define XC_OSM20_ODU10XC_ODU0_4_FACILITY_ID             (134)
#define XC_OSM20_ODU10XC_ODU0_5_FACILITY_ID             (135)
#define XC_OSM20_ODU10XC_ODU0_6_FACILITY_ID             (136)
#define XC_OSM20_ODU10XC_ODU0_7_FACILITY_ID             (137)
#define XC_OSM20_ODU10XC_ODU0_8_FACILITY_ID             (138)
#define XC_OSM20_ODU10XC_ODU0_9_FACILITY_ID             (139)
#define XC_OSM20_ODU10XC_ODU0_10_FACILITY_ID            (140)
#define XC_OSM20_ODU10XC_ODU0_11_FACILITY_ID            (141)
#define XC_OSM20_ODU10XC_ODU0_12_FACILITY_ID            (142)
#define XC_OSM20_ODU10XC_ODU0_13_FACILITY_ID            (143)
#define XC_OSM20_ODU10XC_ODU0_14_FACILITY_ID            (144)
#define XC_OSM20_ODU10XC_ODU0_15_FACILITY_ID            (145)
#define XC_OSM20_ODU10XC_ODU0_16_FACILITY_ID            (146)
#define XC_OSM20_ODU10XC_ODU0_17_FACILITY_ID            (147)
#define XC_OSM20_ODU10XC_ODU0_18_FACILITY_ID            (148)
#define XC_OSM20_ODU10XC_ODU0_19_FACILITY_ID            (149)
#define XC_OSM20_ODU10XC_ODU0_20_FACILITY_ID            (150)
#define XC_OSM20_ODU10XC_ODU0_21_FACILITY_ID            (151)
#define XC_OSM20_ODU10XC_ODU0_22_FACILITY_ID            (152)
#define XC_OSM20_ODU10XC_ODU0_23_FACILITY_ID            (153)
#define XC_OSM20_ODU10XC_ODU0_24_FACILITY_ID            (154)
#define XC_OSM20_ODU10XC_ODU0_25_FACILITY_ID            (155)
#define XC_OSM20_ODU10XC_ODU0_26_FACILITY_ID            (156)
#define XC_OSM20_ODU10XC_ODU0_27_FACILITY_ID            (157)
#define XC_OSM20_ODU10XC_ODU0_28_FACILITY_ID            (158)
#define XC_OSM20_ODU10XC_ODU0_29_FACILITY_ID            (159)
#define XC_OSM20_ODU10XC_ODU0_30_FACILITY_ID            (160)
#define XC_OSM20_ODU10XC_ODU0_31_FACILITY_ID            (161)


// The Maximum number of each OSM20 interface type
#define XC_MAX_OSM20_ODUXC_OTNK_INTF                (4)
#define XC_MAX_OSM20_ODUXC_OTN1_INTF                (1)
#define XC_MAX_OSM20_ODUXC_OTN2_INTF                (1)
#define XC_MAX_OSM20_ODUXC_ODUKPP_ODUK_INTF         (2)
#define XC_MAX_OSM20_ODUXC_ODUKPP_ODU1_INTF         (1)
#define XC_MAX_OSM20_ODUXC_ODUKPP_ODU2_INTF         (1)
#define XC_MAX_OSM20_ODUXC_IMUX_INTF                (1)

#define XC_MAX_OSM20_FRMODUXC_FRM_OTUK_INTF         (1)
#define XC_MAX_OSM20_FRMODUXC_FRM_OTU1_INTF         (1)
#define XC_MAX_OSM20_FRMODUXC_FRM_OTU2_INTF         (1)
#define XC_MAX_OSM20_FRMODUXC_FRM_CBR_INTF          (1)
#define XC_MAX_OSM20_FRMODUXC_FRM_CBR10G_INTF       (1)
#define XC_MAX_OSM20_FRMODUXC_FRM_GE_INTF           (1)
#define XC_MAX_OSM20_FRMODUXC_FRM_GE10G_INTF        (1)
#define XC_MAX_OSM20_FRMODUXC_ODU_OTUK_INTF         (1)
#define XC_MAX_OSM20_FRMODUXC_ODU_OTU1_INTF         (1)
#define XC_MAX_OSM20_FRMODUXC_ODU_OTU2_INTF         (1)
#define XC_MAX_OSM20_FRMODUXC_ODU_VCAT_ODU2_INTF    (2)
#define XC_MAX_OSM20_FRMODUXC_ODU_VCAT_ODU1_INTF    (2)
#define XC_MAX_OSM20_FRMODUXC_ODU_VCAT_ODUK_INTF    (2)

#define XC_MAX_OSM20_ODU21XC_ODU2_INTF              (2)
#define XC_MAX_OSM20_ODU21XC_ODU1_INTF              (16)

#define XC_MAX_OSM20_ODU20XC_ODU2_INTF              (2)
#define XC_MAX_OSM20_ODU20XC_ODU0_INTF              (32)

#define XC_MAX_OSM20_ODU2FXC_ODU2_INTF              (2)
#define XC_MAX_OSM20_ODU2FXC_ODUF_INTF              (32)

#define XC_MAX_OSM20_ODU10XC_ODU1_INTF              (16)
#define XC_MAX_OSM20_ODU10XC_ODU0_INTF              (32)


// The Maximum number of connections allowed on each OSM20 interface type
#define XC_MAX_XC_OSM20_ODUXC_OTNK                  (8)
#define XC_MAX_XC_OSM20_ODUXC_OTN1                  (8)
#define XC_MAX_XC_OSM20_ODUXC_OTN2                  (2)
#define XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODUK           (8)
#define XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU1           (8)
#define XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU2           (2)
#define XC_MAX_XC_OSM20_ODUXC_IMUX                  (16)

#define XC_MAX_XC_OSM20_FRMODUXC_FRM_OTUK           (32)
#define XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU1           (16)
#define XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU2           (2)
#define XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR            (16)
#define XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR10G         (2)
#define XC_MAX_XC_OSM20_FRMODUXC_FRM_GE             (16)
#define XC_MAX_XC_OSM20_FRMODUXC_FRM_GE10G          (2)
#define XC_MAX_XC_OSM20_FRMODUXC_ODU_OTUK           (32)
#define XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU1           (16)
#define XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU2           (2)
#define XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU2      (1)
#define XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU1      (4)
#define XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODUK      (8)

#define XC_MAX_XC_OSM20_ODU21XC_ODU2                (8)
#define XC_MAX_XC_OSM20_ODU21XC_ODU1                (2)

#define XC_MAX_XC_OSM20_ODU20XC_ODU2                (8)
#define XC_MAX_XC_OSM20_ODU20XC_ODU0                (1)

#define XC_MAX_XC_OSM20_ODU2FXC_ODU2                (8)
#define XC_MAX_XC_OSM20_ODU2FXC_ODUF                (8)

#define XC_MAX_XC_OSM20_ODU10XC_ODU1                (2)
#define XC_MAX_XC_OSM20_ODU10XC_ODU0                (1)


// The maximum number of connections on OSM20
#define XC_MAX_XC_OSM20 (\
    (XC_MAX_OSM20_ODUXC_OTNK_INTF             * XC_MAX_XC_OSM20_ODUXC_OTNK)              +\
    (XC_MAX_OSM20_ODUXC_OTN1_INTF             * XC_MAX_XC_OSM20_ODUXC_OTN1)              +\
    (XC_MAX_OSM20_ODUXC_OTN2_INTF             * XC_MAX_XC_OSM20_ODUXC_OTN2)              +\
    (XC_MAX_OSM20_ODUXC_ODUKPP_ODUK_INTF      * XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODUK)       +\
    (XC_MAX_OSM20_ODUXC_ODUKPP_ODU1_INTF      * XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU1)       +\
    (XC_MAX_OSM20_ODUXC_ODUKPP_ODU2_INTF      * XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU2)       +\
    (XC_MAX_OSM20_ODUXC_IMUX_INTF             * XC_MAX_XC_OSM20_ODUXC_IMUX)              +\
    (XC_MAX_OSM20_FRMODUXC_FRM_OTUK_INTF      * XC_MAX_XC_OSM20_FRMODUXC_FRM_OTUK)       +\
    (XC_MAX_OSM20_FRMODUXC_FRM_OTU1_INTF      * XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU1)       +\
    (XC_MAX_OSM20_FRMODUXC_FRM_OTU2_INTF      * XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU2)       +\
    (XC_MAX_OSM20_FRMODUXC_FRM_CBR_INTF       * XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR)        +\
    (XC_MAX_OSM20_FRMODUXC_FRM_CBR10G_INTF    * XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR10G)     +\
    (XC_MAX_OSM20_FRMODUXC_FRM_GE_INTF        * XC_MAX_XC_OSM20_FRMODUXC_FRM_GE)         +\
    (XC_MAX_OSM20_FRMODUXC_FRM_GE10G_INTF     * XC_MAX_XC_OSM20_FRMODUXC_FRM_GE10G)      +\
    (XC_MAX_OSM20_FRMODUXC_ODU_OTUK_INTF      * XC_MAX_XC_OSM20_FRMODUXC_ODU_OTUK)       +\
    (XC_MAX_OSM20_FRMODUXC_ODU_OTU1_INTF      * XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU1)       +\
    (XC_MAX_OSM20_FRMODUXC_ODU_OTU2_INTF      * XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU2)       +\
    (XC_MAX_OSM20_FRMODUXC_ODU_VCAT_ODU2_INTF * XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU2)  +\
    (XC_MAX_OSM20_FRMODUXC_ODU_VCAT_ODU1_INTF * XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU1)  +\
    (XC_MAX_OSM20_FRMODUXC_ODU_VCAT_ODUK_INTF * XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODUK)  +\
    (XC_MAX_OSM20_ODU21XC_ODU2_INTF           * XC_MAX_XC_OSM20_ODU21XC_ODU2)            +\
    (XC_MAX_OSM20_ODU21XC_ODU1_INTF           * XC_MAX_XC_OSM20_ODU21XC_ODU1)            +\
    (XC_MAX_OSM20_ODU20XC_ODU2_INTF           * XC_MAX_XC_OSM20_ODU20XC_ODU2)            +\
    (XC_MAX_OSM20_ODU20XC_ODU0_INTF           * XC_MAX_XC_OSM20_ODU20XC_ODU0)            +\
    (XC_MAX_OSM20_ODU2FXC_ODU2_INTF           * XC_MAX_XC_OSM20_ODU2FXC_ODU2)            +\
    (XC_MAX_OSM20_ODU2FXC_ODUF_INTF           * XC_MAX_XC_OSM20_ODU2FXC_ODUF)            +\
    (XC_MAX_OSM20_ODU10XC_ODU1_INTF           * XC_MAX_XC_OSM20_ODU10XC_ODU1)            +\
    (XC_MAX_OSM20_ODU10XC_ODU0_INTF           * XC_MAX_XC_OSM20_ODU10XC_ODU0)            )

#define XC_MAX_OSM20_FIXED_MCASTID (\
    (XC_MAX_OSM20_ODUXC_IMUX_INTF             * XC_MAX_XC_OSM20_ODUXC_IMUX)              )

#define XC_MAX_OSM20_XC_IM_ALL (\
    (XC_MAX_OSM20_ODUXC_IMUX_INTF             * XC_MAX_XC_OSM20_ODUXC_IMUX)              )

// 
// Breakdown of OSM20 XC CFG Region
//

/*
The compiler has a limit of 256 levels of nested macros, therefore, we have to use number to instead.
// ODUXC
#define XC_OSM20_ODUXC_ODUK_0_START             (0)
#define XC_OSM20_ODUXC_ODUK_0_END               (XC_OSM20_ODUXC_ODUK_0_START         + XC_MAX_XC_OSM20_ODUXC_OTNK-1)
#define XC_OSM20_ODUXC_ODUK_1_START             (XC_OSM20_ODUXC_ODUK_0_END+1)
#define XC_OSM20_ODUXC_ODUK_1_END               (XC_OSM20_ODUXC_ODUK_1_START         + XC_MAX_XC_OSM20_ODUXC_OTNK-1)
#define XC_OSM20_ODUXC_ODUK_2_START             (XC_OSM20_ODUXC_ODUK_1_END+1)
#define XC_OSM20_ODUXC_ODUK_2_END               (XC_OSM20_ODUXC_ODUK_2_START         + XC_MAX_XC_OSM20_ODUXC_OTNK-1)
#define XC_OSM20_ODUXC_ODUK_3_START             (XC_OSM20_ODUXC_ODUK_2_END+1)
#define XC_OSM20_ODUXC_ODUK_3_END               (XC_OSM20_ODUXC_ODUK_3_START         + XC_MAX_XC_OSM20_ODUXC_OTNK-1)
#define XC_OSM20_ODUXC_ODU1_START               (XC_OSM20_ODUXC_ODUK_3_END+1)
#define XC_OSM20_ODUXC_ODU1_END                 (XC_OSM20_ODUXC_ODU1_START           + XC_MAX_XC_OSM20_ODUXC_OTN1-1)
#define XC_OSM20_ODUXC_ODU2_START               (XC_OSM20_ODUXC_ODU1_END+1)
#define XC_OSM20_ODUXC_ODU2_END                 (XC_OSM20_ODUXC_ODU2_START           + XC_MAX_XC_OSM20_ODUXC_OTN2-1)
#define XC_OSM20_ODUXC_ODUKPP_ODUK0_START       (XC_OSM20_ODUXC_ODU2_END+1)
#define XC_OSM20_ODUXC_ODUKPP_ODUK0_END         (XC_OSM20_ODUXC_ODUKPP_ODUK0_START   + XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODUK-1)
#define XC_OSM20_ODUXC_ODUKPP_ODUK1_START       (XC_OSM20_ODUXC_ODUKPP_ODUK0_END+1)
#define XC_OSM20_ODUXC_ODUKPP_ODUK1_END         (XC_OSM20_ODUXC_ODUKPP_ODUK1_START   + XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODUK-1)
#define XC_OSM20_ODUXC_ODUKPP_ODU1_START        (XC_OSM20_ODUXC_ODUKPP_ODUK1_END+1)
#define XC_OSM20_ODUXC_ODUKPP_ODU1_END          (XC_OSM20_ODUXC_ODUKPP_ODU1_START    + XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU1-1)
#define XC_OSM20_ODUXC_ODUKPP_ODU2_START        (XC_OSM20_ODUXC_ODUKPP_ODU1_END+1)
#define XC_OSM20_ODUXC_ODUKPP_ODU2_END          (XC_OSM20_ODUXC_ODUKPP_ODU2_START    + XC_MAX_XC_OSM20_ODUXC_ODUKPP_ODU2-1)
#define XC_OSM20_ODUXC_IMUX_START               (XC_OSM20_ODUXC_ODUKPP_ODU2_END+1)
#define XC_OSM20_ODUXC_IMUX_END                 (XC_OSM20_ODUXC_IMUX_START           + XC_MAX_XC_OSM20_ODUXC_IMUX-1)

// FRMODUXC
#define XC_OSM20_FRMODUXC_FRM_OTUK_START        (XC_OSM20_ODUXC_IMUX_END+1)
#define XC_OSM20_FRMODUXC_FRM_OTUK_END          (XC_OSM20_FRMODUXC_FRM_OTUK_START    + XC_MAX_XC_OSM20_FRMODUXC_FRM_OTUK-1)
#define XC_OSM20_FRMODUXC_FRM_OTU1_START        (XC_OSM20_FRMODUXC_FRM_OTUK_END+1)
#define XC_OSM20_FRMODUXC_FRM_OTU1_END          (XC_OSM20_FRMODUXC_FRM_OTU1_START    + XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU1-1)
#define XC_OSM20_FRMODUXC_FRM_OTU2_START        (XC_OSM20_FRMODUXC_FRM_OTU1_END+1)
#define XC_OSM20_FRMODUXC_FRM_OTU2_END          (XC_OSM20_FRMODUXC_FRM_OTU2_START    + XC_MAX_XC_OSM20_FRMODUXC_FRM_OTU2-1)

#define XC_OSM20_FRMODUXC_FRM_CBR_START         (XC_OSM20_FRMODUXC_FRM_OTU2_END+1)
#define XC_OSM20_FRMODUXC_FRM_CBR_END           (XC_OSM20_FRMODUXC_FRM_CBR_START     + XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR-1)
#define XC_OSM20_FRMODUXC_FRM_CBR10G_START      (XC_OSM20_FRMODUXC_FRM_CBR_END+1)
#define XC_OSM20_FRMODUXC_FRM_CBR10G_END        (XC_OSM20_FRMODUXC_FRM_CBR10G_START  + XC_MAX_XC_OSM20_FRMODUXC_FRM_CBR10G-1)
#define XC_OSM20_FRMODUXC_FRM_GE_START          (XC_OSM20_FRMODUXC_FRM_CBR10G_END+1)
#define XC_OSM20_FRMODUXC_FRM_GE_END            (XC_OSM20_FRMODUXC_FRM_GE_START      + XC_MAX_XC_OSM20_FRMODUXC_FRM_GE-1)
#define XC_OSM20_FRMODUXC_FRM_GE10G_START       (XC_OSM20_FRMODUXC_FRM_GE_END+1)
#define XC_OSM20_FRMODUXC_FRM_GE10G_END         (XC_OSM20_FRMODUXC_FRM_GE10G_START   + XC_MAX_XC_OSM20_FRMODUXC_FRM_GE10G-1)
#define XC_OSM20_FRMODUXC_ODU_OTUK_START        (XC_OSM20_FRMODUXC_FRM_GE10G_END+1)
#define XC_OSM20_FRMODUXC_ODU_OTUK_END          (XC_OSM20_FRMODUXC_ODU_OTUK_START    + XC_MAX_XC_OSM20_FRMODUXC_ODU_OTUK-1)
#define XC_OSM20_FRMODUXC_ODU_OTU1_START        (XC_OSM20_FRMODUXC_ODU_OTUK_END+1)
#define XC_OSM20_FRMODUXC_ODU_OTU1_END          (XC_OSM20_FRMODUXC_ODU_OTU1_START    + XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU1-1)
#define XC_OSM20_FRMODUXC_ODU_OTU2_START        (XC_OSM20_FRMODUXC_ODU_OTU1_END+1)
#define XC_OSM20_FRMODUXC_ODU_OTU2_END          (XC_OSM20_FRMODUXC_ODU_OTU2_START    + XC_MAX_XC_OSM20_FRMODUXC_ODU_OTU2-1)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_START  (XC_OSM20_FRMODUXC_ODU_OTU2_END+1)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_END    (XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_START   + XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU2-1)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_START  (XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_END+1)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_END    (XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_START   + XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU1-1)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_START  (XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_END+1)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_END    (XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_START   + XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODUK-1)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_START  (XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_END+1)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_END    (XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_START   + XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU2-1)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_START  (XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_END+1)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_END    (XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_START   + XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODU1-1)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_START  (XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_END+1)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_END    (XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_START   + XC_MAX_XC_OSM20_FRMODUXC_ODU_VCAT_ODUK-1)

// ODU21 MUX
#define XC_OSM20_ODU21XC_ODU2_0_START           (XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_END+1)
#define XC_OSM20_ODU21XC_ODU2_0_END             (XC_OSM20_ODU21XC_ODU2_0_START + XC_MAX_XC_OSM20_ODU21XC_ODU2-1)
#define XC_OSM20_ODU21XC_ODU2_1_START           (XC_OSM20_ODU21XC_ODU2_0_END+1)
#define XC_OSM20_ODU21XC_ODU2_1_END             (XC_OSM20_ODU21XC_ODU2_1_START + XC_MAX_XC_OSM20_ODU21XC_ODU2-1)

#define XC_OSM20_ODU21XC_ODU1_0_START           (XC_OSM20_ODU21XC_ODU2_1_END+1)
#define XC_OSM20_ODU21XC_ODU1_0_END             (XC_OSM20_ODU21XC_ODU1_0_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_1_START           (XC_OSM20_ODU21XC_ODU1_0_END+1)
#define XC_OSM20_ODU21XC_ODU1_1_END             (XC_OSM20_ODU21XC_ODU1_1_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_2_START           (XC_OSM20_ODU21XC_ODU1_1_END+1)
#define XC_OSM20_ODU21XC_ODU1_2_END             (XC_OSM20_ODU21XC_ODU1_2_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_3_START           (XC_OSM20_ODU21XC_ODU1_2_END+1)
#define XC_OSM20_ODU21XC_ODU1_3_END             (XC_OSM20_ODU21XC_ODU1_3_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_4_START           (XC_OSM20_ODU21XC_ODU1_3_END+1)
#define XC_OSM20_ODU21XC_ODU1_4_END             (XC_OSM20_ODU21XC_ODU1_4_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_5_START           (XC_OSM20_ODU21XC_ODU1_4_END+1)
#define XC_OSM20_ODU21XC_ODU1_5_END             (XC_OSM20_ODU21XC_ODU1_5_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_6_START           (XC_OSM20_ODU21XC_ODU1_5_END+1)
#define XC_OSM20_ODU21XC_ODU1_6_END             (XC_OSM20_ODU21XC_ODU1_6_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_7_START           (XC_OSM20_ODU21XC_ODU1_6_END+1)
#define XC_OSM20_ODU21XC_ODU1_7_END             (XC_OSM20_ODU21XC_ODU1_7_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_8_START           (XC_OSM20_ODU21XC_ODU1_7_END+1)
#define XC_OSM20_ODU21XC_ODU1_8_END             (XC_OSM20_ODU21XC_ODU1_8_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_9_START           (XC_OSM20_ODU21XC_ODU1_8_END+1)
#define XC_OSM20_ODU21XC_ODU1_9_END             (XC_OSM20_ODU21XC_ODU1_9_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_10_START          (XC_OSM20_ODU21XC_ODU1_9_END+1)
#define XC_OSM20_ODU21XC_ODU1_10_END            (XC_OSM20_ODU21XC_ODU1_10_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_11_START          (XC_OSM20_ODU21XC_ODU1_10_END+1)
#define XC_OSM20_ODU21XC_ODU1_11_END            (XC_OSM20_ODU21XC_ODU1_11_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_12_START          (XC_OSM20_ODU21XC_ODU1_11_END+1)
#define XC_OSM20_ODU21XC_ODU1_12_END            (XC_OSM20_ODU21XC_ODU1_12_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_13_START          (XC_OSM20_ODU21XC_ODU1_12_END+1)
#define XC_OSM20_ODU21XC_ODU1_13_END            (XC_OSM20_ODU21XC_ODU1_13_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_14_START          (XC_OSM20_ODU21XC_ODU1_13_END+1)
#define XC_OSM20_ODU21XC_ODU1_14_END            (XC_OSM20_ODU21XC_ODU1_14_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
#define XC_OSM20_ODU21XC_ODU1_15_START          (XC_OSM20_ODU21XC_ODU1_14_END+1)
#define XC_OSM20_ODU21XC_ODU1_15_END            (XC_OSM20_ODU21XC_ODU1_15_START + XC_MAX_XC_OSM20_ODU21XC_ODU1-1)
*/

#define XC_OSM20_ODUXC_ODUK_0_START             (0)
#define XC_OSM20_ODUXC_ODUK_0_END               (7)
#define XC_OSM20_ODUXC_ODUK_1_START             (8)
#define XC_OSM20_ODUXC_ODUK_1_END               (15)
#define XC_OSM20_ODUXC_ODUK_2_START             (16)
#define XC_OSM20_ODUXC_ODUK_2_END               (23)
#define XC_OSM20_ODUXC_ODUK_3_START             (24)
#define XC_OSM20_ODUXC_ODUK_3_END               (31)
#define XC_OSM20_ODUXC_ODU1_START               (32)
#define XC_OSM20_ODUXC_ODU1_END                 (39)
#define XC_OSM20_ODUXC_ODU2_START               (40)
#define XC_OSM20_ODUXC_ODU2_END                 (41)
#define XC_OSM20_ODUXC_ODUKPP_ODUK0_START       (42)
#define XC_OSM20_ODUXC_ODUKPP_ODUK0_END         (49)
#define XC_OSM20_ODUXC_ODUKPP_ODUK1_START       (50)
#define XC_OSM20_ODUXC_ODUKPP_ODUK1_END         (57)
#define XC_OSM20_ODUXC_ODUKPP_ODU1_START        (58)
#define XC_OSM20_ODUXC_ODUKPP_ODU1_END          (65)
#define XC_OSM20_ODUXC_ODUKPP_ODU2_START        (66)
#define XC_OSM20_ODUXC_ODUKPP_ODU2_END          (67)
#define XC_OSM20_ODUXC_IMUX_START               (68)
#define XC_OSM20_ODUXC_IMUX_END                 (83)

// FRMODUXC
#define XC_OSM20_FRMODUXC_FRM_OTUK_START        (84)
#define XC_OSM20_FRMODUXC_FRM_OTUK_END          (115)
#define XC_OSM20_FRMODUXC_FRM_OTU1_START        (116)
#define XC_OSM20_FRMODUXC_FRM_OTU1_END          (131)
#define XC_OSM20_FRMODUXC_FRM_OTU2_START        (132)
#define XC_OSM20_FRMODUXC_FRM_OTU2_END          (133)

#define XC_OSM20_FRMODUXC_FRM_CBR_START         (134)
#define XC_OSM20_FRMODUXC_FRM_CBR_END           (149)
#define XC_OSM20_FRMODUXC_FRM_CBR10G_START      (150)
#define XC_OSM20_FRMODUXC_FRM_CBR10G_END        (151)
#define XC_OSM20_FRMODUXC_FRM_GE_START          (152)
#define XC_OSM20_FRMODUXC_FRM_GE_END            (167)
#define XC_OSM20_FRMODUXC_FRM_GE10G_START       (168)
#define XC_OSM20_FRMODUXC_FRM_GE10G_END         (169)
#define XC_OSM20_FRMODUXC_ODU_OTUK_START        (170)
#define XC_OSM20_FRMODUXC_ODU_OTUK_END          (201)
#define XC_OSM20_FRMODUXC_ODU_OTU1_START        (202)
#define XC_OSM20_FRMODUXC_ODU_OTU1_END          (217)
#define XC_OSM20_FRMODUXC_ODU_OTU2_START        (218)
#define XC_OSM20_FRMODUXC_ODU_OTU2_END          (219)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_START  (220)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_END    (220)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_START  (221)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_END    (224)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_START  (225)
#define XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_END    (232)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_START  (233)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_END    (233)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_START  (234)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_END    (237)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_START  (238)
#define XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_END    (245)

// ODU21 MUX
#define XC_OSM20_ODU21XC_ODU2_0_START           (246)
#define XC_OSM20_ODU21XC_ODU2_0_END             (253)
#define XC_OSM20_ODU21XC_ODU2_1_START           (254)
#define XC_OSM20_ODU21XC_ODU2_1_END             (261)

#define XC_OSM20_ODU21XC_ODU1_0_START           (262)
#define XC_OSM20_ODU21XC_ODU1_0_END             (263)
#define XC_OSM20_ODU21XC_ODU1_1_START           (264)
#define XC_OSM20_ODU21XC_ODU1_1_END             (265)
#define XC_OSM20_ODU21XC_ODU1_2_START           (266)
#define XC_OSM20_ODU21XC_ODU1_2_END             (267)
#define XC_OSM20_ODU21XC_ODU1_3_START           (268)
#define XC_OSM20_ODU21XC_ODU1_3_END             (269)
#define XC_OSM20_ODU21XC_ODU1_4_START           (270)
#define XC_OSM20_ODU21XC_ODU1_4_END             (271)
#define XC_OSM20_ODU21XC_ODU1_5_START           (272)
#define XC_OSM20_ODU21XC_ODU1_5_END             (273)
#define XC_OSM20_ODU21XC_ODU1_6_START           (274)
#define XC_OSM20_ODU21XC_ODU1_6_END             (275)
#define XC_OSM20_ODU21XC_ODU1_7_START           (276)
#define XC_OSM20_ODU21XC_ODU1_7_END             (277)
#define XC_OSM20_ODU21XC_ODU1_8_START           (278)
#define XC_OSM20_ODU21XC_ODU1_8_END             (279)
#define XC_OSM20_ODU21XC_ODU1_9_START           (280)
#define XC_OSM20_ODU21XC_ODU1_9_END             (281)
#define XC_OSM20_ODU21XC_ODU1_10_START          (282)
#define XC_OSM20_ODU21XC_ODU1_10_END            (283)
#define XC_OSM20_ODU21XC_ODU1_11_START          (284)
#define XC_OSM20_ODU21XC_ODU1_11_END            (285)
#define XC_OSM20_ODU21XC_ODU1_12_START          (286)
#define XC_OSM20_ODU21XC_ODU1_12_END            (287)
#define XC_OSM20_ODU21XC_ODU1_13_START          (288)
#define XC_OSM20_ODU21XC_ODU1_13_END            (289)
#define XC_OSM20_ODU21XC_ODU1_14_START          (290)
#define XC_OSM20_ODU21XC_ODU1_14_END            (291)
#define XC_OSM20_ODU21XC_ODU1_15_START          (292)
#define XC_OSM20_ODU21XC_ODU1_15_END            (293)

// ODU20 MUX
#define XC_OSM20_ODU20XC_ODU2_0_START           (XC_OSM20_ODU21XC_ODU1_15_END+1)
#define XC_OSM20_ODU20XC_ODU2_0_END             (XC_OSM20_ODU20XC_ODU2_0_START + XC_MAX_XC_OSM20_ODU20XC_ODU2-1)
#define XC_OSM20_ODU20XC_ODU2_1_START           (XC_OSM20_ODU20XC_ODU2_0_END+1)
#define XC_OSM20_ODU20XC_ODU2_1_END             (XC_OSM20_ODU20XC_ODU2_1_START + XC_MAX_XC_OSM20_ODU20XC_ODU2-1)

#define XC_OSM20_ODU20XC_ODU0_0_START           (XC_OSM20_ODU20XC_ODU2_1_END+1)
#define XC_OSM20_ODU20XC_ODU0_0_END             (XC_OSM20_ODU20XC_ODU0_0_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_1_START           (XC_OSM20_ODU20XC_ODU0_0_END+1)
#define XC_OSM20_ODU20XC_ODU0_1_END             (XC_OSM20_ODU20XC_ODU0_1_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_2_START           (XC_OSM20_ODU20XC_ODU0_1_END+1)
#define XC_OSM20_ODU20XC_ODU0_2_END             (XC_OSM20_ODU20XC_ODU0_2_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_3_START           (XC_OSM20_ODU20XC_ODU0_2_END+1)
#define XC_OSM20_ODU20XC_ODU0_3_END             (XC_OSM20_ODU20XC_ODU0_3_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_4_START           (XC_OSM20_ODU20XC_ODU0_3_END+1)
#define XC_OSM20_ODU20XC_ODU0_4_END             (XC_OSM20_ODU20XC_ODU0_4_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_5_START           (XC_OSM20_ODU20XC_ODU0_4_END+1)
#define XC_OSM20_ODU20XC_ODU0_5_END             (XC_OSM20_ODU20XC_ODU0_5_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_6_START           (XC_OSM20_ODU20XC_ODU0_5_END+1)
#define XC_OSM20_ODU20XC_ODU0_6_END             (XC_OSM20_ODU20XC_ODU0_6_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_7_START           (XC_OSM20_ODU20XC_ODU0_6_END+1)
#define XC_OSM20_ODU20XC_ODU0_7_END             (XC_OSM20_ODU20XC_ODU0_7_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_8_START           (XC_OSM20_ODU20XC_ODU0_7_END+1)
#define XC_OSM20_ODU20XC_ODU0_8_END             (XC_OSM20_ODU20XC_ODU0_8_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_9_START           (XC_OSM20_ODU20XC_ODU0_8_END+1)
#define XC_OSM20_ODU20XC_ODU0_9_END             (XC_OSM20_ODU20XC_ODU0_9_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_10_START          (XC_OSM20_ODU20XC_ODU0_9_END+1)
#define XC_OSM20_ODU20XC_ODU0_10_END            (XC_OSM20_ODU20XC_ODU0_10_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_11_START          (XC_OSM20_ODU20XC_ODU0_10_END+1)
#define XC_OSM20_ODU20XC_ODU0_11_END            (XC_OSM20_ODU20XC_ODU0_11_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_12_START          (XC_OSM20_ODU20XC_ODU0_11_END+1)
#define XC_OSM20_ODU20XC_ODU0_12_END            (XC_OSM20_ODU20XC_ODU0_12_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_13_START          (XC_OSM20_ODU20XC_ODU0_12_END+1)
#define XC_OSM20_ODU20XC_ODU0_13_END            (XC_OSM20_ODU20XC_ODU0_13_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_14_START          (XC_OSM20_ODU20XC_ODU0_13_END+1)
#define XC_OSM20_ODU20XC_ODU0_14_END            (XC_OSM20_ODU20XC_ODU0_14_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_15_START          (XC_OSM20_ODU20XC_ODU0_14_END+1)
#define XC_OSM20_ODU20XC_ODU0_15_END            (XC_OSM20_ODU20XC_ODU0_15_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_16_START          (XC_OSM20_ODU20XC_ODU0_15_END+1)
#define XC_OSM20_ODU20XC_ODU0_16_END            (XC_OSM20_ODU20XC_ODU0_16_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_17_START          (XC_OSM20_ODU20XC_ODU0_16_END+1)
#define XC_OSM20_ODU20XC_ODU0_17_END            (XC_OSM20_ODU20XC_ODU0_17_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_18_START          (XC_OSM20_ODU20XC_ODU0_17_END+1)
#define XC_OSM20_ODU20XC_ODU0_18_END            (XC_OSM20_ODU20XC_ODU0_18_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_19_START          (XC_OSM20_ODU20XC_ODU0_18_END+1)
#define XC_OSM20_ODU20XC_ODU0_19_END            (XC_OSM20_ODU20XC_ODU0_19_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_20_START          (XC_OSM20_ODU20XC_ODU0_19_END+1)
#define XC_OSM20_ODU20XC_ODU0_20_END            (XC_OSM20_ODU20XC_ODU0_20_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_21_START          (XC_OSM20_ODU20XC_ODU0_20_END+1)
#define XC_OSM20_ODU20XC_ODU0_21_END            (XC_OSM20_ODU20XC_ODU0_21_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_22_START          (XC_OSM20_ODU20XC_ODU0_21_END+1)
#define XC_OSM20_ODU20XC_ODU0_22_END            (XC_OSM20_ODU20XC_ODU0_22_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_23_START          (XC_OSM20_ODU20XC_ODU0_22_END+1)
#define XC_OSM20_ODU20XC_ODU0_23_END            (XC_OSM20_ODU20XC_ODU0_23_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_24_START          (XC_OSM20_ODU20XC_ODU0_23_END+1)
#define XC_OSM20_ODU20XC_ODU0_24_END            (XC_OSM20_ODU20XC_ODU0_24_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_25_START          (XC_OSM20_ODU20XC_ODU0_24_END+1)
#define XC_OSM20_ODU20XC_ODU0_25_END            (XC_OSM20_ODU20XC_ODU0_25_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_26_START          (XC_OSM20_ODU20XC_ODU0_25_END+1)
#define XC_OSM20_ODU20XC_ODU0_26_END            (XC_OSM20_ODU20XC_ODU0_26_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_27_START          (XC_OSM20_ODU20XC_ODU0_26_END+1)
#define XC_OSM20_ODU20XC_ODU0_27_END            (XC_OSM20_ODU20XC_ODU0_27_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_28_START          (XC_OSM20_ODU20XC_ODU0_27_END+1)
#define XC_OSM20_ODU20XC_ODU0_28_END            (XC_OSM20_ODU20XC_ODU0_28_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_29_START          (XC_OSM20_ODU20XC_ODU0_28_END+1)
#define XC_OSM20_ODU20XC_ODU0_29_END            (XC_OSM20_ODU20XC_ODU0_29_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_30_START          (XC_OSM20_ODU20XC_ODU0_29_END+1)
#define XC_OSM20_ODU20XC_ODU0_30_END            (XC_OSM20_ODU20XC_ODU0_30_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)
#define XC_OSM20_ODU20XC_ODU0_31_START          (XC_OSM20_ODU20XC_ODU0_30_END+1)
#define XC_OSM20_ODU20XC_ODU0_31_END            (XC_OSM20_ODU20XC_ODU0_31_START + XC_MAX_XC_OSM20_ODU20XC_ODU0-1)

// ODU2F MUX
#define XC_OSM20_ODU2FXC_ODU2_0_START           (XC_OSM20_ODU20XC_ODU0_31_END+1)
#define XC_OSM20_ODU2FXC_ODU2_0_END             (XC_OSM20_ODU2FXC_ODU2_0_START + XC_MAX_XC_OSM20_ODU2FXC_ODU2-1)
#define XC_OSM20_ODU2FXC_ODU2_1_START           (XC_OSM20_ODU2FXC_ODU2_0_END+1)
#define XC_OSM20_ODU2FXC_ODU2_1_END             (XC_OSM20_ODU2FXC_ODU2_1_START + XC_MAX_XC_OSM20_ODU2FXC_ODU2-1)

#define XC_OSM20_ODU2FXC_ODUF_0_START           (XC_OSM20_ODU2FXC_ODU2_1_END+1)
#define XC_OSM20_ODU2FXC_ODUF_0_END             (XC_OSM20_ODU2FXC_ODUF_0_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_1_START           (XC_OSM20_ODU2FXC_ODUF_0_END+1)
#define XC_OSM20_ODU2FXC_ODUF_1_END             (XC_OSM20_ODU2FXC_ODUF_1_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_2_START           (XC_OSM20_ODU2FXC_ODUF_1_END+1)
#define XC_OSM20_ODU2FXC_ODUF_2_END             (XC_OSM20_ODU2FXC_ODUF_2_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_3_START           (XC_OSM20_ODU2FXC_ODUF_2_END+1)
#define XC_OSM20_ODU2FXC_ODUF_3_END             (XC_OSM20_ODU2FXC_ODUF_3_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_4_START           (XC_OSM20_ODU2FXC_ODUF_3_END+1)
#define XC_OSM20_ODU2FXC_ODUF_4_END             (XC_OSM20_ODU2FXC_ODUF_4_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_5_START           (XC_OSM20_ODU2FXC_ODUF_4_END+1)
#define XC_OSM20_ODU2FXC_ODUF_5_END             (XC_OSM20_ODU2FXC_ODUF_5_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_6_START           (XC_OSM20_ODU2FXC_ODUF_5_END+1)
#define XC_OSM20_ODU2FXC_ODUF_6_END             (XC_OSM20_ODU2FXC_ODUF_6_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_7_START           (XC_OSM20_ODU2FXC_ODUF_6_END+1)
#define XC_OSM20_ODU2FXC_ODUF_7_END             (XC_OSM20_ODU2FXC_ODUF_7_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_8_START           (XC_OSM20_ODU2FXC_ODUF_7_END+1)
#define XC_OSM20_ODU2FXC_ODUF_8_END             (XC_OSM20_ODU2FXC_ODUF_8_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_9_START           (XC_OSM20_ODU2FXC_ODUF_8_END+1)
#define XC_OSM20_ODU2FXC_ODUF_9_END             (XC_OSM20_ODU2FXC_ODUF_9_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_10_START          (XC_OSM20_ODU2FXC_ODUF_9_END+1)
#define XC_OSM20_ODU2FXC_ODUF_10_END            (XC_OSM20_ODU2FXC_ODUF_10_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_11_START          (XC_OSM20_ODU2FXC_ODUF_10_END+1)
#define XC_OSM20_ODU2FXC_ODUF_11_END            (XC_OSM20_ODU2FXC_ODUF_11_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_12_START          (XC_OSM20_ODU2FXC_ODUF_11_END+1)
#define XC_OSM20_ODU2FXC_ODUF_12_END            (XC_OSM20_ODU2FXC_ODUF_12_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_13_START          (XC_OSM20_ODU2FXC_ODUF_12_END+1)
#define XC_OSM20_ODU2FXC_ODUF_13_END            (XC_OSM20_ODU2FXC_ODUF_13_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_14_START          (XC_OSM20_ODU2FXC_ODUF_13_END+1)
#define XC_OSM20_ODU2FXC_ODUF_14_END            (XC_OSM20_ODU2FXC_ODUF_14_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_15_START          (XC_OSM20_ODU2FXC_ODUF_14_END+1)
#define XC_OSM20_ODU2FXC_ODUF_15_END            (XC_OSM20_ODU2FXC_ODUF_15_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_16_START          (XC_OSM20_ODU2FXC_ODUF_15_END+1)
#define XC_OSM20_ODU2FXC_ODUF_16_END            (XC_OSM20_ODU2FXC_ODUF_16_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_17_START          (XC_OSM20_ODU2FXC_ODUF_16_END+1)
#define XC_OSM20_ODU2FXC_ODUF_17_END            (XC_OSM20_ODU2FXC_ODUF_17_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_18_START          (XC_OSM20_ODU2FXC_ODUF_17_END+1)
#define XC_OSM20_ODU2FXC_ODUF_18_END            (XC_OSM20_ODU2FXC_ODUF_18_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_19_START          (XC_OSM20_ODU2FXC_ODUF_18_END+1)
#define XC_OSM20_ODU2FXC_ODUF_19_END            (XC_OSM20_ODU2FXC_ODUF_19_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_20_START          (XC_OSM20_ODU2FXC_ODUF_19_END+1)
#define XC_OSM20_ODU2FXC_ODUF_20_END            (XC_OSM20_ODU2FXC_ODUF_20_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_21_START          (XC_OSM20_ODU2FXC_ODUF_20_END+1)
#define XC_OSM20_ODU2FXC_ODUF_21_END            (XC_OSM20_ODU2FXC_ODUF_21_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_22_START          (XC_OSM20_ODU2FXC_ODUF_21_END+1)
#define XC_OSM20_ODU2FXC_ODUF_22_END            (XC_OSM20_ODU2FXC_ODUF_22_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_23_START          (XC_OSM20_ODU2FXC_ODUF_22_END+1)
#define XC_OSM20_ODU2FXC_ODUF_23_END            (XC_OSM20_ODU2FXC_ODUF_23_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_24_START          (XC_OSM20_ODU2FXC_ODUF_23_END+1)
#define XC_OSM20_ODU2FXC_ODUF_24_END            (XC_OSM20_ODU2FXC_ODUF_24_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_25_START          (XC_OSM20_ODU2FXC_ODUF_24_END+1)
#define XC_OSM20_ODU2FXC_ODUF_25_END            (XC_OSM20_ODU2FXC_ODUF_25_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_26_START          (XC_OSM20_ODU2FXC_ODUF_25_END+1)
#define XC_OSM20_ODU2FXC_ODUF_26_END            (XC_OSM20_ODU2FXC_ODUF_26_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_27_START          (XC_OSM20_ODU2FXC_ODUF_26_END+1)
#define XC_OSM20_ODU2FXC_ODUF_27_END            (XC_OSM20_ODU2FXC_ODUF_27_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_28_START          (XC_OSM20_ODU2FXC_ODUF_27_END+1)
#define XC_OSM20_ODU2FXC_ODUF_28_END            (XC_OSM20_ODU2FXC_ODUF_28_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_29_START          (XC_OSM20_ODU2FXC_ODUF_28_END+1)
#define XC_OSM20_ODU2FXC_ODUF_29_END            (XC_OSM20_ODU2FXC_ODUF_29_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_30_START          (XC_OSM20_ODU2FXC_ODUF_29_END+1)
#define XC_OSM20_ODU2FXC_ODUF_30_END            (XC_OSM20_ODU2FXC_ODUF_30_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)
#define XC_OSM20_ODU2FXC_ODUF_31_START          (XC_OSM20_ODU2FXC_ODUF_30_END+1)
#define XC_OSM20_ODU2FXC_ODUF_31_END            (XC_OSM20_ODU2FXC_ODUF_31_START + XC_MAX_XC_OSM20_ODU2FXC_ODUF-1)

// ODU10 MUX
#define XC_OSM20_ODU10XC_ODU1_0_START           (XC_OSM20_ODU2FXC_ODUF_31_END+1)
#define XC_OSM20_ODU10XC_ODU1_0_END             (XC_OSM20_ODU10XC_ODU1_0_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_1_START           (XC_OSM20_ODU10XC_ODU1_0_END+1)
#define XC_OSM20_ODU10XC_ODU1_1_END             (XC_OSM20_ODU10XC_ODU1_1_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_2_START           (XC_OSM20_ODU10XC_ODU1_1_END+1)
#define XC_OSM20_ODU10XC_ODU1_2_END             (XC_OSM20_ODU10XC_ODU1_2_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_3_START           (XC_OSM20_ODU10XC_ODU1_2_END+1)
#define XC_OSM20_ODU10XC_ODU1_3_END             (XC_OSM20_ODU10XC_ODU1_3_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_4_START           (XC_OSM20_ODU10XC_ODU1_3_END+1)
#define XC_OSM20_ODU10XC_ODU1_4_END             (XC_OSM20_ODU10XC_ODU1_4_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_5_START           (XC_OSM20_ODU10XC_ODU1_4_END+1)
#define XC_OSM20_ODU10XC_ODU1_5_END             (XC_OSM20_ODU10XC_ODU1_5_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_6_START           (XC_OSM20_ODU10XC_ODU1_5_END+1)
#define XC_OSM20_ODU10XC_ODU1_6_END             (XC_OSM20_ODU10XC_ODU1_6_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_7_START           (XC_OSM20_ODU10XC_ODU1_6_END+1)
#define XC_OSM20_ODU10XC_ODU1_7_END             (XC_OSM20_ODU10XC_ODU1_7_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_8_START           (XC_OSM20_ODU10XC_ODU1_7_END+1)
#define XC_OSM20_ODU10XC_ODU1_8_END             (XC_OSM20_ODU10XC_ODU1_8_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_9_START           (XC_OSM20_ODU10XC_ODU1_8_END+1)
#define XC_OSM20_ODU10XC_ODU1_9_END             (XC_OSM20_ODU10XC_ODU1_9_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_10_START          (XC_OSM20_ODU10XC_ODU1_9_END+1)
#define XC_OSM20_ODU10XC_ODU1_10_END            (XC_OSM20_ODU10XC_ODU1_10_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_11_START          (XC_OSM20_ODU10XC_ODU1_10_END+1)
#define XC_OSM20_ODU10XC_ODU1_11_END            (XC_OSM20_ODU10XC_ODU1_11_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_12_START          (XC_OSM20_ODU10XC_ODU1_11_END+1)
#define XC_OSM20_ODU10XC_ODU1_12_END            (XC_OSM20_ODU10XC_ODU1_12_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_13_START          (XC_OSM20_ODU10XC_ODU1_12_END+1)
#define XC_OSM20_ODU10XC_ODU1_13_END            (XC_OSM20_ODU10XC_ODU1_13_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_14_START          (XC_OSM20_ODU10XC_ODU1_13_END+1)
#define XC_OSM20_ODU10XC_ODU1_14_END            (XC_OSM20_ODU10XC_ODU1_14_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)
#define XC_OSM20_ODU10XC_ODU1_15_START          (XC_OSM20_ODU10XC_ODU1_14_END+1)
#define XC_OSM20_ODU10XC_ODU1_15_END            (XC_OSM20_ODU10XC_ODU1_15_START + XC_MAX_XC_OSM20_ODU10XC_ODU1-1)

#define XC_OSM20_ODU10XC_ODU0_0_START           (XC_OSM20_ODU10XC_ODU1_15_END+1)
#define XC_OSM20_ODU10XC_ODU0_0_END             (XC_OSM20_ODU10XC_ODU0_0_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_1_START           (XC_OSM20_ODU10XC_ODU0_0_END+1)
#define XC_OSM20_ODU10XC_ODU0_1_END             (XC_OSM20_ODU10XC_ODU0_1_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_2_START           (XC_OSM20_ODU10XC_ODU0_1_END+1)
#define XC_OSM20_ODU10XC_ODU0_2_END             (XC_OSM20_ODU10XC_ODU0_2_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_3_START           (XC_OSM20_ODU10XC_ODU0_2_END+1)
#define XC_OSM20_ODU10XC_ODU0_3_END             (XC_OSM20_ODU10XC_ODU0_3_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_4_START           (XC_OSM20_ODU10XC_ODU0_3_END+1)
#define XC_OSM20_ODU10XC_ODU0_4_END             (XC_OSM20_ODU10XC_ODU0_4_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_5_START           (XC_OSM20_ODU10XC_ODU0_4_END+1)
#define XC_OSM20_ODU10XC_ODU0_5_END             (XC_OSM20_ODU10XC_ODU0_5_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_6_START           (XC_OSM20_ODU10XC_ODU0_5_END+1)
#define XC_OSM20_ODU10XC_ODU0_6_END             (XC_OSM20_ODU10XC_ODU0_6_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_7_START           (XC_OSM20_ODU10XC_ODU0_6_END+1)
#define XC_OSM20_ODU10XC_ODU0_7_END             (XC_OSM20_ODU10XC_ODU0_7_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_8_START           (XC_OSM20_ODU10XC_ODU0_7_END+1)
#define XC_OSM20_ODU10XC_ODU0_8_END             (XC_OSM20_ODU10XC_ODU0_8_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_9_START           (XC_OSM20_ODU10XC_ODU0_8_END+1)
#define XC_OSM20_ODU10XC_ODU0_9_END             (XC_OSM20_ODU10XC_ODU0_9_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_10_START          (XC_OSM20_ODU10XC_ODU0_9_END+1)
#define XC_OSM20_ODU10XC_ODU0_10_END            (XC_OSM20_ODU10XC_ODU0_10_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_11_START          (XC_OSM20_ODU10XC_ODU0_10_END+1)
#define XC_OSM20_ODU10XC_ODU0_11_END            (XC_OSM20_ODU10XC_ODU0_11_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_12_START          (XC_OSM20_ODU10XC_ODU0_11_END+1)
#define XC_OSM20_ODU10XC_ODU0_12_END            (XC_OSM20_ODU10XC_ODU0_12_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_13_START          (XC_OSM20_ODU10XC_ODU0_12_END+1)
#define XC_OSM20_ODU10XC_ODU0_13_END            (XC_OSM20_ODU10XC_ODU0_13_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_14_START          (XC_OSM20_ODU10XC_ODU0_13_END+1)
#define XC_OSM20_ODU10XC_ODU0_14_END            (XC_OSM20_ODU10XC_ODU0_14_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_15_START          (XC_OSM20_ODU10XC_ODU0_14_END+1)
#define XC_OSM20_ODU10XC_ODU0_15_END            (XC_OSM20_ODU10XC_ODU0_15_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_16_START          (XC_OSM20_ODU10XC_ODU0_15_END+1)
#define XC_OSM20_ODU10XC_ODU0_16_END            (XC_OSM20_ODU10XC_ODU0_16_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_17_START          (XC_OSM20_ODU10XC_ODU0_16_END+1)
#define XC_OSM20_ODU10XC_ODU0_17_END            (XC_OSM20_ODU10XC_ODU0_17_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_18_START          (XC_OSM20_ODU10XC_ODU0_17_END+1)
#define XC_OSM20_ODU10XC_ODU0_18_END            (XC_OSM20_ODU10XC_ODU0_18_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_19_START          (XC_OSM20_ODU10XC_ODU0_18_END+1)
#define XC_OSM20_ODU10XC_ODU0_19_END            (XC_OSM20_ODU10XC_ODU0_19_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_20_START          (XC_OSM20_ODU10XC_ODU0_19_END+1)
#define XC_OSM20_ODU10XC_ODU0_20_END            (XC_OSM20_ODU10XC_ODU0_20_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_21_START          (XC_OSM20_ODU10XC_ODU0_20_END+1)
#define XC_OSM20_ODU10XC_ODU0_21_END            (XC_OSM20_ODU10XC_ODU0_21_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_22_START          (XC_OSM20_ODU10XC_ODU0_21_END+1)
#define XC_OSM20_ODU10XC_ODU0_22_END            (XC_OSM20_ODU10XC_ODU0_22_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_23_START          (XC_OSM20_ODU10XC_ODU0_22_END+1)
#define XC_OSM20_ODU10XC_ODU0_23_END            (XC_OSM20_ODU10XC_ODU0_23_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_24_START          (XC_OSM20_ODU10XC_ODU0_23_END+1)
#define XC_OSM20_ODU10XC_ODU0_24_END            (XC_OSM20_ODU10XC_ODU0_24_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_25_START          (XC_OSM20_ODU10XC_ODU0_24_END+1)
#define XC_OSM20_ODU10XC_ODU0_25_END            (XC_OSM20_ODU10XC_ODU0_25_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_26_START          (XC_OSM20_ODU10XC_ODU0_25_END+1)
#define XC_OSM20_ODU10XC_ODU0_26_END            (XC_OSM20_ODU10XC_ODU0_26_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_27_START          (XC_OSM20_ODU10XC_ODU0_26_END+1)
#define XC_OSM20_ODU10XC_ODU0_27_END            (XC_OSM20_ODU10XC_ODU0_27_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_28_START          (XC_OSM20_ODU10XC_ODU0_27_END+1)
#define XC_OSM20_ODU10XC_ODU0_28_END            (XC_OSM20_ODU10XC_ODU0_28_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_29_START          (XC_OSM20_ODU10XC_ODU0_28_END+1)
#define XC_OSM20_ODU10XC_ODU0_29_END            (XC_OSM20_ODU10XC_ODU0_29_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_30_START          (XC_OSM20_ODU10XC_ODU0_29_END+1)
#define XC_OSM20_ODU10XC_ODU0_30_END            (XC_OSM20_ODU10XC_ODU0_30_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)
#define XC_OSM20_ODU10XC_ODU0_31_START          (XC_OSM20_ODU10XC_ODU0_30_END+1)
#define XC_OSM20_ODU10XC_ODU0_31_END            (XC_OSM20_ODU10XC_ODU0_31_START + XC_MAX_XC_OSM20_ODU10XC_ODU0-1)


// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as OSM20 facility identifiers ***
const int OSM20ConfigMap[] = {0,

        // ODUXC
        XC_OSM20_ODUXC_ODUK_0_START,
        XC_OSM20_ODUXC_ODUK_1_START,
        XC_OSM20_ODUXC_ODUK_2_START,
        XC_OSM20_ODUXC_ODUK_3_START,
        XC_OSM20_ODUXC_ODU1_START,
        XC_OSM20_ODUXC_ODU2_START,
        XC_OSM20_ODUXC_ODUKPP_ODUK0_START,
        XC_OSM20_ODUXC_ODUKPP_ODUK1_START,
        XC_OSM20_ODUXC_ODUKPP_ODU1_START,
        XC_OSM20_ODUXC_ODUKPP_ODU2_START,
        XC_OSM20_ODUXC_IMUX_START,

        // FRMODUXC
        XC_OSM20_FRMODUXC_FRM_OTUK_START,
        XC_OSM20_FRMODUXC_FRM_OTU1_START,
        XC_OSM20_FRMODUXC_FRM_OTU2_START,
        XC_OSM20_FRMODUXC_FRM_CBR_START,
        XC_OSM20_FRMODUXC_FRM_CBR10G_START,
        XC_OSM20_FRMODUXC_FRM_GE_START,
        XC_OSM20_FRMODUXC_FRM_GE10G_START,
        XC_OSM20_FRMODUXC_ODU_OTUK_START,
        XC_OSM20_FRMODUXC_ODU_OTU1_START,
        XC_OSM20_FRMODUXC_ODU_OTU2_START,
        XC_OSM20_FRMODUXC_ODU_VCAT0_ODU2_START,
        XC_OSM20_FRMODUXC_ODU_VCAT0_ODU1_START,
        XC_OSM20_FRMODUXC_ODU_VCAT0_ODUK_START,
        XC_OSM20_FRMODUXC_ODU_VCAT1_ODU2_START,
        XC_OSM20_FRMODUXC_ODU_VCAT1_ODU1_START,
        XC_OSM20_FRMODUXC_ODU_VCAT1_ODUK_START,

        // ODU21 MUX
        XC_OSM20_ODU21XC_ODU2_0_START,
        XC_OSM20_ODU21XC_ODU2_1_START,
        
        XC_OSM20_ODU21XC_ODU1_0_START,
        XC_OSM20_ODU21XC_ODU1_1_START,
        XC_OSM20_ODU21XC_ODU1_2_START,
        XC_OSM20_ODU21XC_ODU1_3_START,
        XC_OSM20_ODU21XC_ODU1_4_START,
        XC_OSM20_ODU21XC_ODU1_5_START,
        XC_OSM20_ODU21XC_ODU1_6_START,
        XC_OSM20_ODU21XC_ODU1_7_START,
        XC_OSM20_ODU21XC_ODU1_8_START,
        XC_OSM20_ODU21XC_ODU1_9_START,
        XC_OSM20_ODU21XC_ODU1_10_START,
        XC_OSM20_ODU21XC_ODU1_11_START,
        XC_OSM20_ODU21XC_ODU1_12_START,
        XC_OSM20_ODU21XC_ODU1_13_START,
        XC_OSM20_ODU21XC_ODU1_14_START,
        XC_OSM20_ODU21XC_ODU1_15_START,
        
        // ODU20 MUX
        XC_OSM20_ODU20XC_ODU2_0_START,
        XC_OSM20_ODU20XC_ODU2_1_START,
        
        XC_OSM20_ODU20XC_ODU0_0_START,
        XC_OSM20_ODU20XC_ODU0_1_START,
        XC_OSM20_ODU20XC_ODU0_2_START,
        XC_OSM20_ODU20XC_ODU0_3_START,
        XC_OSM20_ODU20XC_ODU0_4_START,
        XC_OSM20_ODU20XC_ODU0_5_START,
        XC_OSM20_ODU20XC_ODU0_6_START,
        XC_OSM20_ODU20XC_ODU0_7_START,
        XC_OSM20_ODU20XC_ODU0_8_START,
        XC_OSM20_ODU20XC_ODU0_9_START,
        XC_OSM20_ODU20XC_ODU0_10_START,
        XC_OSM20_ODU20XC_ODU0_11_START,
        XC_OSM20_ODU20XC_ODU0_12_START,
        XC_OSM20_ODU20XC_ODU0_13_START,
        XC_OSM20_ODU20XC_ODU0_14_START,
        XC_OSM20_ODU20XC_ODU0_15_START,
        XC_OSM20_ODU20XC_ODU0_16_START,
        XC_OSM20_ODU20XC_ODU0_17_START,
        XC_OSM20_ODU20XC_ODU0_18_START,
        XC_OSM20_ODU20XC_ODU0_19_START,
        XC_OSM20_ODU20XC_ODU0_20_START,
        XC_OSM20_ODU20XC_ODU0_21_START,
        XC_OSM20_ODU20XC_ODU0_22_START,
        XC_OSM20_ODU20XC_ODU0_23_START,
        XC_OSM20_ODU20XC_ODU0_24_START,
        XC_OSM20_ODU20XC_ODU0_25_START,
        XC_OSM20_ODU20XC_ODU0_26_START,
        XC_OSM20_ODU20XC_ODU0_27_START,
        XC_OSM20_ODU20XC_ODU0_28_START,
        XC_OSM20_ODU20XC_ODU0_29_START,
        XC_OSM20_ODU20XC_ODU0_30_START,
        XC_OSM20_ODU20XC_ODU0_31_START,
        
        // ODU2F MUX
        XC_OSM20_ODU2FXC_ODU2_0_START,
        XC_OSM20_ODU2FXC_ODU2_1_START,
        
        XC_OSM20_ODU2FXC_ODUF_0_START,
        XC_OSM20_ODU2FXC_ODUF_1_START,
        XC_OSM20_ODU2FXC_ODUF_2_START,
        XC_OSM20_ODU2FXC_ODUF_3_START,
        XC_OSM20_ODU2FXC_ODUF_4_START,
        XC_OSM20_ODU2FXC_ODUF_5_START,
        XC_OSM20_ODU2FXC_ODUF_6_START,
        XC_OSM20_ODU2FXC_ODUF_7_START,
        XC_OSM20_ODU2FXC_ODUF_8_START,
        XC_OSM20_ODU2FXC_ODUF_9_START,
        XC_OSM20_ODU2FXC_ODUF_10_START,
        XC_OSM20_ODU2FXC_ODUF_11_START,
        XC_OSM20_ODU2FXC_ODUF_12_START,
        XC_OSM20_ODU2FXC_ODUF_13_START,
        XC_OSM20_ODU2FXC_ODUF_14_START,
        XC_OSM20_ODU2FXC_ODUF_15_START,
        XC_OSM20_ODU2FXC_ODUF_16_START,
        XC_OSM20_ODU2FXC_ODUF_17_START,
        XC_OSM20_ODU2FXC_ODUF_18_START,
        XC_OSM20_ODU2FXC_ODUF_19_START,
        XC_OSM20_ODU2FXC_ODUF_20_START,
        XC_OSM20_ODU2FXC_ODUF_21_START,
        XC_OSM20_ODU2FXC_ODUF_22_START,
        XC_OSM20_ODU2FXC_ODUF_23_START,
        XC_OSM20_ODU2FXC_ODUF_24_START,
        XC_OSM20_ODU2FXC_ODUF_25_START,
        XC_OSM20_ODU2FXC_ODUF_26_START,
        XC_OSM20_ODU2FXC_ODUF_27_START,
        XC_OSM20_ODU2FXC_ODUF_28_START,
        XC_OSM20_ODU2FXC_ODUF_29_START,
        XC_OSM20_ODU2FXC_ODUF_30_START,
        XC_OSM20_ODU2FXC_ODUF_31_START,
        
        // ODU10 MUX
        XC_OSM20_ODU10XC_ODU1_0_START,
        XC_OSM20_ODU10XC_ODU1_1_START,
        XC_OSM20_ODU10XC_ODU1_2_START,
        XC_OSM20_ODU10XC_ODU1_3_START,
        XC_OSM20_ODU10XC_ODU1_4_START,
        XC_OSM20_ODU10XC_ODU1_5_START,
        XC_OSM20_ODU10XC_ODU1_6_START,
        XC_OSM20_ODU10XC_ODU1_7_START,
        XC_OSM20_ODU10XC_ODU1_8_START,
        XC_OSM20_ODU10XC_ODU1_9_START,
        XC_OSM20_ODU10XC_ODU1_10_START,
        XC_OSM20_ODU10XC_ODU1_11_START,
        XC_OSM20_ODU10XC_ODU1_12_START,
        XC_OSM20_ODU10XC_ODU1_13_START,
        XC_OSM20_ODU10XC_ODU1_14_START,
        XC_OSM20_ODU10XC_ODU1_15_START,
        
        XC_OSM20_ODU10XC_ODU0_0_START,
        XC_OSM20_ODU10XC_ODU0_1_START,
        XC_OSM20_ODU10XC_ODU0_2_START,
        XC_OSM20_ODU10XC_ODU0_3_START,
        XC_OSM20_ODU10XC_ODU0_4_START,
        XC_OSM20_ODU10XC_ODU0_5_START,
        XC_OSM20_ODU10XC_ODU0_6_START,
        XC_OSM20_ODU10XC_ODU0_7_START,
        XC_OSM20_ODU10XC_ODU0_8_START,
        XC_OSM20_ODU10XC_ODU0_9_START,
        XC_OSM20_ODU10XC_ODU0_10_START,
        XC_OSM20_ODU10XC_ODU0_11_START,
        XC_OSM20_ODU10XC_ODU0_12_START,
        XC_OSM20_ODU10XC_ODU0_13_START,
        XC_OSM20_ODU10XC_ODU0_14_START,
        XC_OSM20_ODU10XC_ODU0_15_START,
        XC_OSM20_ODU10XC_ODU0_16_START,
        XC_OSM20_ODU10XC_ODU0_17_START,
        XC_OSM20_ODU10XC_ODU0_18_START,
        XC_OSM20_ODU10XC_ODU0_19_START,
        XC_OSM20_ODU10XC_ODU0_20_START,
        XC_OSM20_ODU10XC_ODU0_21_START,
        XC_OSM20_ODU10XC_ODU0_22_START,
        XC_OSM20_ODU10XC_ODU0_23_START,
        XC_OSM20_ODU10XC_ODU0_24_START,
        XC_OSM20_ODU10XC_ODU0_25_START,
        XC_OSM20_ODU10XC_ODU0_26_START,
        XC_OSM20_ODU10XC_ODU0_27_START,
        XC_OSM20_ODU10XC_ODU0_28_START,
        XC_OSM20_ODU10XC_ODU0_29_START,
        XC_OSM20_ODU10XC_ODU0_30_START,
        XC_OSM20_ODU10XC_ODU0_31_START
    };



// -----------------------------------------------------------------------------------------------
// *************************  OMMX Definitions *********************
//

//
// Identifiers for each OMMX facility
//

// ODU XC Facilities:  ODU <--> ODU
#define XC_OMMX_ODUXC_ODUK_0_FACILITY_ID               (1)    //8*ODU0/flex CRS
#define XC_OMMX_ODUXC_ODUK_0_VIRTUAL_FACILITY_ID       (2)
#define XC_OMMX_ODUXC_ODUK_1_FACILITY_ID               (3)    //8*ODU0/flex CRS
#define XC_OMMX_ODUXC_ODUK_1_VIRTUAL_FACILITY_ID       (4)
#define XC_OMMX_ODUXC_ODUK_2_FACILITY_ID               (5)    //8*ODU0/flex CRS
#define XC_OMMX_ODUXC_ODUK_2_VIRTUAL_FACILITY_ID       (6)
#define XC_OMMX_ODUXC_ODUK_3_FACILITY_ID               (7)    //8*ODU0/flex CRS
#define XC_OMMX_ODUXC_ODUK_3_VIRTUAL_FACILITY_ID       (8)
#define XC_OMMX_ODUXC_ODU1_FACILITY_ID                 (9)    //8*ODU1 CRS
#define XC_OMMX_ODUXC_ODU1_VIRTUAL_FACILITY_ID         (10)
#define XC_OMMX_ODUXC_ODU2_FACILITY_ID                 (11)    //2*ODU2 CRS
#define XC_OMMX_ODUXC_ODU2_VIRTUAL_FACILITY_ID         (12)

#define XC_OMMX_ODUXC_ODUKPP_ODUK0_FACILITY_ID         (13)    //8*CBR CRS
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_FACILITY_ID (14)
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_FACILITY_ID         (15)    //8*CBR CRS
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_FACILITY_ID (16)
#define XC_OMMX_ODUXC_ODUKPP_ODU1_FACILITY_ID          (17)    //8*CBR CRS
#define XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_FACILITY_ID  (18)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_FACILITY_ID          (19)   //2*CBR CRS
#define XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_FACILITY_ID  (20)

// FRMODUXC Facilities:  FRM <--> ODU
#define XC_OMMX_FRMODUXC_FRM_OTUK_FACILITY_ID          (21)   //32*ODU0/flex Frame CRS
#define XC_OMMX_FRMODUXC_FRM_OTU1_FACILITY_ID          (22)   //16*OTU1 Frame CRS
#define XC_OMMX_FRMODUXC_FRM_OTU2_FACILITY_ID          (23)   //2*OTU2 Frame CRS

#define XC_OMMX_FRMODUXC_FRM_CBR_FACILITY_ID           (24)   //8*OC48/STM16 CRS
#define XC_OMMX_FRMODUXC_FRM_CBR10G_FACILITY_ID        (25)   //2*OC192/STM64 CRS
#define XC_OMMX_FRMODUXC_FRM_GE_FACILITY_ID            (26)   //8*GE CRS
#define XC_OMMX_FRMODUXC_FRM_GE10G_FACILITY_ID         (27)   //2*10 GE CRS

#define XC_OMMX_FRMODUXC_ODU_OTUK_FACILITY_ID          (28)   //32
#define XC_OMMX_FRMODUXC_ODU_OTU1_FACILITY_ID          (29)   //16
#define XC_OMMX_FRMODUXC_ODU_OTU2_FACILITY_ID          (30)   //2

#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_FACILITY_ID    (31)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_FACILITY_ID    (32)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_FACILITY_ID    (33)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_FACILITY_ID    (34)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_FACILITY_ID    (35)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_FACILITY_ID    (36)

// ODU21 MUX
#define XC_OMMX_ODU21XC_ODU2_0_FACILITY_ID             (37)
#define XC_OMMX_ODU21XC_ODU2_1_FACILITY_ID             (38)

#define XC_OMMX_ODU21XC_ODU1_0_FACILITY_ID             (39)
#define XC_OMMX_ODU21XC_ODU1_1_FACILITY_ID             (40)
#define XC_OMMX_ODU21XC_ODU1_2_FACILITY_ID             (41)
#define XC_OMMX_ODU21XC_ODU1_3_FACILITY_ID             (42)
#define XC_OMMX_ODU21XC_ODU1_4_FACILITY_ID             (43)
#define XC_OMMX_ODU21XC_ODU1_5_FACILITY_ID             (44)
#define XC_OMMX_ODU21XC_ODU1_6_FACILITY_ID             (45)
#define XC_OMMX_ODU21XC_ODU1_7_FACILITY_ID             (46)
#define XC_OMMX_ODU21XC_ODU1_8_FACILITY_ID             (47)
#define XC_OMMX_ODU21XC_ODU1_9_FACILITY_ID             (48)
#define XC_OMMX_ODU21XC_ODU1_10_FACILITY_ID            (49)
#define XC_OMMX_ODU21XC_ODU1_11_FACILITY_ID            (50)
#define XC_OMMX_ODU21XC_ODU1_12_FACILITY_ID            (51)
#define XC_OMMX_ODU21XC_ODU1_13_FACILITY_ID            (52)
#define XC_OMMX_ODU21XC_ODU1_14_FACILITY_ID            (53)
#define XC_OMMX_ODU21XC_ODU1_15_FACILITY_ID            (54)

// ODU20 MUX
#define XC_OMMX_ODU20XC_ODU2_0_FACILITY_ID             (55)
#define XC_OMMX_ODU20XC_ODU2_1_FACILITY_ID             (56)

#define XC_OMMX_ODU20XC_ODU0_0_FACILITY_ID             (57)
#define XC_OMMX_ODU20XC_ODU0_1_FACILITY_ID             (58)
#define XC_OMMX_ODU20XC_ODU0_2_FACILITY_ID             (59)
#define XC_OMMX_ODU20XC_ODU0_3_FACILITY_ID             (60)
#define XC_OMMX_ODU20XC_ODU0_4_FACILITY_ID             (61)
#define XC_OMMX_ODU20XC_ODU0_5_FACILITY_ID             (62)
#define XC_OMMX_ODU20XC_ODU0_6_FACILITY_ID             (63)
#define XC_OMMX_ODU20XC_ODU0_7_FACILITY_ID             (64)
#define XC_OMMX_ODU20XC_ODU0_8_FACILITY_ID             (65)
#define XC_OMMX_ODU20XC_ODU0_9_FACILITY_ID             (66)
#define XC_OMMX_ODU20XC_ODU0_10_FACILITY_ID            (67)
#define XC_OMMX_ODU20XC_ODU0_11_FACILITY_ID            (68)
#define XC_OMMX_ODU20XC_ODU0_12_FACILITY_ID            (69)
#define XC_OMMX_ODU20XC_ODU0_13_FACILITY_ID            (70)
#define XC_OMMX_ODU20XC_ODU0_14_FACILITY_ID            (71)
#define XC_OMMX_ODU20XC_ODU0_15_FACILITY_ID            (72)
#define XC_OMMX_ODU20XC_ODU0_16_FACILITY_ID            (73)
#define XC_OMMX_ODU20XC_ODU0_17_FACILITY_ID            (74)
#define XC_OMMX_ODU20XC_ODU0_18_FACILITY_ID            (75)
#define XC_OMMX_ODU20XC_ODU0_19_FACILITY_ID            (76)
#define XC_OMMX_ODU20XC_ODU0_20_FACILITY_ID            (77)
#define XC_OMMX_ODU20XC_ODU0_21_FACILITY_ID            (78)
#define XC_OMMX_ODU20XC_ODU0_22_FACILITY_ID            (79)
#define XC_OMMX_ODU20XC_ODU0_23_FACILITY_ID            (80)
#define XC_OMMX_ODU20XC_ODU0_24_FACILITY_ID            (81)
#define XC_OMMX_ODU20XC_ODU0_25_FACILITY_ID            (82)
#define XC_OMMX_ODU20XC_ODU0_26_FACILITY_ID            (83)
#define XC_OMMX_ODU20XC_ODU0_27_FACILITY_ID            (84)
#define XC_OMMX_ODU20XC_ODU0_28_FACILITY_ID            (85)
#define XC_OMMX_ODU20XC_ODU0_29_FACILITY_ID            (86)
#define XC_OMMX_ODU20XC_ODU0_30_FACILITY_ID            (87)
#define XC_OMMX_ODU20XC_ODU0_31_FACILITY_ID            (88)

// ODU2F MUX
#define XC_OMMX_ODU2FXC_ODU2_0_FACILITY_ID             (89)
#define XC_OMMX_ODU2FXC_ODU2_1_FACILITY_ID             (90)

#define XC_OMMX_ODU2FXC_ODUF_0_FACILITY_ID             (91)
#define XC_OMMX_ODU2FXC_ODUF_1_FACILITY_ID             (92)
#define XC_OMMX_ODU2FXC_ODUF_2_FACILITY_ID             (93)
#define XC_OMMX_ODU2FXC_ODUF_3_FACILITY_ID             (94)
#define XC_OMMX_ODU2FXC_ODUF_4_FACILITY_ID             (95)
#define XC_OMMX_ODU2FXC_ODUF_5_FACILITY_ID             (96)
#define XC_OMMX_ODU2FXC_ODUF_6_FACILITY_ID             (97)
#define XC_OMMX_ODU2FXC_ODUF_7_FACILITY_ID             (98)
#define XC_OMMX_ODU2FXC_ODUF_8_FACILITY_ID             (99)
#define XC_OMMX_ODU2FXC_ODUF_9_FACILITY_ID             (100)
#define XC_OMMX_ODU2FXC_ODUF_10_FACILITY_ID            (101)
#define XC_OMMX_ODU2FXC_ODUF_11_FACILITY_ID            (102)
#define XC_OMMX_ODU2FXC_ODUF_12_FACILITY_ID            (103)
#define XC_OMMX_ODU2FXC_ODUF_13_FACILITY_ID            (104)
#define XC_OMMX_ODU2FXC_ODUF_14_FACILITY_ID            (105)
#define XC_OMMX_ODU2FXC_ODUF_15_FACILITY_ID            (106)
#define XC_OMMX_ODU2FXC_ODUF_16_FACILITY_ID            (107)
#define XC_OMMX_ODU2FXC_ODUF_17_FACILITY_ID            (108)
#define XC_OMMX_ODU2FXC_ODUF_18_FACILITY_ID            (109)
#define XC_OMMX_ODU2FXC_ODUF_19_FACILITY_ID            (110)
#define XC_OMMX_ODU2FXC_ODUF_20_FACILITY_ID            (111)
#define XC_OMMX_ODU2FXC_ODUF_21_FACILITY_ID            (112)
#define XC_OMMX_ODU2FXC_ODUF_22_FACILITY_ID            (113)
#define XC_OMMX_ODU2FXC_ODUF_23_FACILITY_ID            (114)
#define XC_OMMX_ODU2FXC_ODUF_24_FACILITY_ID            (115)
#define XC_OMMX_ODU2FXC_ODUF_25_FACILITY_ID            (116)
#define XC_OMMX_ODU2FXC_ODUF_26_FACILITY_ID            (117)
#define XC_OMMX_ODU2FXC_ODUF_27_FACILITY_ID            (118)
#define XC_OMMX_ODU2FXC_ODUF_28_FACILITY_ID            (119)
#define XC_OMMX_ODU2FXC_ODUF_29_FACILITY_ID            (120)
#define XC_OMMX_ODU2FXC_ODUF_30_FACILITY_ID            (121)
#define XC_OMMX_ODU2FXC_ODUF_31_FACILITY_ID            (122)

// ODU10 MUX
#define XC_OMMX_ODU10XC_ODU1_0_FACILITY_ID             (123)
#define XC_OMMX_ODU10XC_ODU1_1_FACILITY_ID             (124)
#define XC_OMMX_ODU10XC_ODU1_2_FACILITY_ID             (125)
#define XC_OMMX_ODU10XC_ODU1_3_FACILITY_ID             (126)
#define XC_OMMX_ODU10XC_ODU1_4_FACILITY_ID             (127)
#define XC_OMMX_ODU10XC_ODU1_5_FACILITY_ID             (128)
#define XC_OMMX_ODU10XC_ODU1_6_FACILITY_ID             (129)
#define XC_OMMX_ODU10XC_ODU1_7_FACILITY_ID             (130)
#define XC_OMMX_ODU10XC_ODU1_8_FACILITY_ID             (131)
#define XC_OMMX_ODU10XC_ODU1_9_FACILITY_ID             (132)
#define XC_OMMX_ODU10XC_ODU1_10_FACILITY_ID            (133)
#define XC_OMMX_ODU10XC_ODU1_11_FACILITY_ID            (134)
#define XC_OMMX_ODU10XC_ODU1_12_FACILITY_ID            (135)
#define XC_OMMX_ODU10XC_ODU1_13_FACILITY_ID            (136)
#define XC_OMMX_ODU10XC_ODU1_14_FACILITY_ID            (137)
#define XC_OMMX_ODU10XC_ODU1_15_FACILITY_ID            (138)

#define XC_OMMX_ODU10XC_ODU0_0_FACILITY_ID             (139)
#define XC_OMMX_ODU10XC_ODU0_1_FACILITY_ID             (140)
#define XC_OMMX_ODU10XC_ODU0_2_FACILITY_ID             (141)
#define XC_OMMX_ODU10XC_ODU0_3_FACILITY_ID             (142)
#define XC_OMMX_ODU10XC_ODU0_4_FACILITY_ID             (143)
#define XC_OMMX_ODU10XC_ODU0_5_FACILITY_ID             (144)
#define XC_OMMX_ODU10XC_ODU0_6_FACILITY_ID             (145)
#define XC_OMMX_ODU10XC_ODU0_7_FACILITY_ID             (146)
#define XC_OMMX_ODU10XC_ODU0_8_FACILITY_ID             (147)
#define XC_OMMX_ODU10XC_ODU0_9_FACILITY_ID             (148)
#define XC_OMMX_ODU10XC_ODU0_10_FACILITY_ID            (149)
#define XC_OMMX_ODU10XC_ODU0_11_FACILITY_ID            (150)
#define XC_OMMX_ODU10XC_ODU0_12_FACILITY_ID            (151)
#define XC_OMMX_ODU10XC_ODU0_13_FACILITY_ID            (152)
#define XC_OMMX_ODU10XC_ODU0_14_FACILITY_ID            (153)
#define XC_OMMX_ODU10XC_ODU0_15_FACILITY_ID            (154)
#define XC_OMMX_ODU10XC_ODU0_16_FACILITY_ID            (155)
#define XC_OMMX_ODU10XC_ODU0_17_FACILITY_ID            (156)
#define XC_OMMX_ODU10XC_ODU0_18_FACILITY_ID            (157)
#define XC_OMMX_ODU10XC_ODU0_19_FACILITY_ID            (158)
#define XC_OMMX_ODU10XC_ODU0_20_FACILITY_ID            (159)
#define XC_OMMX_ODU10XC_ODU0_21_FACILITY_ID            (160)
#define XC_OMMX_ODU10XC_ODU0_22_FACILITY_ID            (161)
#define XC_OMMX_ODU10XC_ODU0_23_FACILITY_ID            (162)
#define XC_OMMX_ODU10XC_ODU0_24_FACILITY_ID            (163)
#define XC_OMMX_ODU10XC_ODU0_25_FACILITY_ID            (164)
#define XC_OMMX_ODU10XC_ODU0_26_FACILITY_ID            (165)
#define XC_OMMX_ODU10XC_ODU0_27_FACILITY_ID            (166)
#define XC_OMMX_ODU10XC_ODU0_28_FACILITY_ID            (167)
#define XC_OMMX_ODU10XC_ODU0_29_FACILITY_ID            (168)
#define XC_OMMX_ODU10XC_ODU0_30_FACILITY_ID            (169)
#define XC_OMMX_ODU10XC_ODU0_31_FACILITY_ID            (170)


// The Maximum number of each OMMX interface type
#define XC_MAX_OMMX_ODUXC_OTNK_INTF                (4)
#define XC_MAX_OMMX_ODUXC_OTN1_INTF                (1)
#define XC_MAX_OMMX_ODUXC_OTN2_INTF                (1)
#define XC_MAX_OMMX_ODUXC_ODUKPP_ODUK_INTF         (2)
#define XC_MAX_OMMX_ODUXC_ODUKPP_ODU1_INTF         (1)
#define XC_MAX_OMMX_ODUXC_ODUKPP_ODU2_INTF         (1)

#define XC_MAX_OMMX_ODUXC_OTNK_VIRTUAL_INTF        (4)
#define XC_MAX_OMMX_ODUXC_OTN1_VIRTUAL_INTF        (1)
#define XC_MAX_OMMX_ODUXC_OTN2_VIRTUAL_INTF        (1)
#define XC_MAX_OMMX_ODUXC_ODUKPP_VIRTUAL_ODUK_INTF (2)
#define XC_MAX_OMMX_ODUXC_ODUKPP_VIRTUAL_ODU1_INTF (1)
#define XC_MAX_OMMX_ODUXC_ODUKPP_VIRTUAL_ODU2_INTF (1)

#define XC_MAX_OMMX_FRMODUXC_FRM_OTUK_INTF         (1)
#define XC_MAX_OMMX_FRMODUXC_FRM_OTU1_INTF         (1)
#define XC_MAX_OMMX_FRMODUXC_FRM_OTU2_INTF         (1)
#define XC_MAX_OMMX_FRMODUXC_FRM_CBR_INTF          (1)
#define XC_MAX_OMMX_FRMODUXC_FRM_CBR10G_INTF       (1)
#define XC_MAX_OMMX_FRMODUXC_FRM_GE_INTF           (1)
#define XC_MAX_OMMX_FRMODUXC_FRM_GE10G_INTF        (1)
#define XC_MAX_OMMX_FRMODUXC_ODU_OTUK_INTF         (1)
#define XC_MAX_OMMX_FRMODUXC_ODU_OTU1_INTF         (1)
#define XC_MAX_OMMX_FRMODUXC_ODU_OTU2_INTF         (1)
#define XC_MAX_OMMX_FRMODUXC_ODU_VCAT_ODU2_INTF    (2)
#define XC_MAX_OMMX_FRMODUXC_ODU_VCAT_ODU1_INTF    (2)
#define XC_MAX_OMMX_FRMODUXC_ODU_VCAT_ODUK_INTF    (2)

#define XC_MAX_OMMX_ODU21XC_ODU2_INTF              (2)
#define XC_MAX_OMMX_ODU21XC_ODU1_INTF              (16)

#define XC_MAX_OMMX_ODU20XC_ODU2_INTF              (2)
#define XC_MAX_OMMX_ODU20XC_ODU0_INTF              (32)

#define XC_MAX_OMMX_ODU2FXC_ODU2_INTF              (2)
#define XC_MAX_OMMX_ODU2FXC_ODUF_INTF              (32)

#define XC_MAX_OMMX_ODU10XC_ODU1_INTF              (16)
#define XC_MAX_OMMX_ODU10XC_ODU0_INTF              (32)


// The Maximum number of connections allowed on each OMMX interface type
#define XC_MAX_XC_OMMX_ODUXC_OTNK                  (8)
#define XC_MAX_XC_OMMX_ODUXC_OTN1                  (16)
#define XC_MAX_XC_OMMX_ODUXC_OTN2                  (2)
#define XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK           (8)
#define XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU1           (8)
#define XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU2           (2)

#define XC_MAX_XC_OMMX_FRMODUXC_FRM_OTUK           (32)
#define XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU1           (16)
#define XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU2           (2)
#define XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR            (8)
#define XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR10G         (2)
#define XC_MAX_XC_OMMX_FRMODUXC_FRM_GE             (8)
#define XC_MAX_XC_OMMX_FRMODUXC_FRM_GE10G          (2)
#define XC_MAX_XC_OMMX_FRMODUXC_ODU_OTUK           (32)
#define XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU1           (16)
#define XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU2           (2)
#define XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU2      (1)
#define XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU1      (4)
#define XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODUK      (8)

#define XC_MAX_XC_OMMX_ODU21XC_ODU2                (8)
#define XC_MAX_XC_OMMX_ODU21XC_ODU1                (2)

#define XC_MAX_XC_OMMX_ODU20XC_ODU2                (8)
#define XC_MAX_XC_OMMX_ODU20XC_ODU0                (1)

#define XC_MAX_XC_OMMX_ODU2FXC_ODU2                (8)
#define XC_MAX_XC_OMMX_ODU2FXC_ODUF                (8)

#define XC_MAX_XC_OMMX_ODU10XC_ODU1                (2)
#define XC_MAX_XC_OMMX_ODU10XC_ODU0                (1)

#define XC_MAX_OMMX_MCAST_MEMBER                   (2)    // 2 Line side port protect each other

// The maximum number of connections on OMMX
#define XC_MAX_XC_OMMX (\
    (XC_MAX_OMMX_ODUXC_OTNK_INTF                * XC_MAX_XC_OMMX_ODUXC_OTNK)           +\
    (XC_MAX_OMMX_ODUXC_OTN1_INTF                * XC_MAX_XC_OMMX_ODUXC_OTN1)           +\
    (XC_MAX_OMMX_ODUXC_OTN2_INTF                * XC_MAX_XC_OMMX_ODUXC_OTN2)           +\
    (XC_MAX_OMMX_ODUXC_ODUKPP_ODUK_INTF         * XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK)    +\
    (XC_MAX_OMMX_ODUXC_ODUKPP_ODU1_INTF         * XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU1)    +\
    (XC_MAX_OMMX_ODUXC_ODUKPP_ODU2_INTF         * XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU2)    +\
    (XC_MAX_OMMX_ODUXC_OTNK_VIRTUAL_INTF        * XC_MAX_XC_OMMX_ODUXC_OTNK)           +\
    (XC_MAX_OMMX_ODUXC_OTN1_VIRTUAL_INTF        * XC_MAX_XC_OMMX_ODUXC_OTN1)           +\
    (XC_MAX_OMMX_ODUXC_OTN2_VIRTUAL_INTF        * XC_MAX_XC_OMMX_ODUXC_OTN2)           +\
    (XC_MAX_OMMX_ODUXC_ODUKPP_VIRTUAL_ODUK_INTF * XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK)    +\
    (XC_MAX_OMMX_ODUXC_ODUKPP_VIRTUAL_ODU1_INTF * XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU1)    +\
    (XC_MAX_OMMX_ODUXC_ODUKPP_VIRTUAL_ODU2_INTF * XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU2)    +\
    (XC_MAX_OMMX_FRMODUXC_FRM_OTUK_INTF      * XC_MAX_XC_OMMX_FRMODUXC_FRM_OTUK)       +\
    (XC_MAX_OMMX_FRMODUXC_FRM_OTU1_INTF      * XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU1)       +\
    (XC_MAX_OMMX_FRMODUXC_FRM_OTU2_INTF      * XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU2)       +\
    (XC_MAX_OMMX_FRMODUXC_FRM_CBR_INTF       * XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR)        +\
    (XC_MAX_OMMX_FRMODUXC_FRM_CBR10G_INTF    * XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR10G)     +\
    (XC_MAX_OMMX_FRMODUXC_FRM_GE_INTF        * XC_MAX_XC_OMMX_FRMODUXC_FRM_GE)         +\
    (XC_MAX_OMMX_FRMODUXC_FRM_GE10G_INTF     * XC_MAX_XC_OMMX_FRMODUXC_FRM_GE10G)      +\
    (XC_MAX_OMMX_FRMODUXC_ODU_OTUK_INTF      * XC_MAX_XC_OMMX_FRMODUXC_ODU_OTUK)       +\
    (XC_MAX_OMMX_FRMODUXC_ODU_OTU1_INTF      * XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU1)       +\
    (XC_MAX_OMMX_FRMODUXC_ODU_OTU2_INTF      * XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU2)       +\
    (XC_MAX_OMMX_FRMODUXC_ODU_VCAT_ODU2_INTF * XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU2)  +\
    (XC_MAX_OMMX_FRMODUXC_ODU_VCAT_ODU1_INTF * XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU1)  +\
    (XC_MAX_OMMX_FRMODUXC_ODU_VCAT_ODUK_INTF * XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODUK)  +\
    (XC_MAX_OMMX_ODU21XC_ODU2_INTF           * XC_MAX_XC_OMMX_ODU21XC_ODU2)            +\
    (XC_MAX_OMMX_ODU21XC_ODU1_INTF           * XC_MAX_XC_OMMX_ODU21XC_ODU1)            +\
    (XC_MAX_OMMX_ODU20XC_ODU2_INTF           * XC_MAX_XC_OMMX_ODU20XC_ODU2)            +\
    (XC_MAX_OMMX_ODU20XC_ODU0_INTF           * XC_MAX_XC_OMMX_ODU20XC_ODU0)            +\
    (XC_MAX_OMMX_ODU2FXC_ODU2_INTF           * XC_MAX_XC_OMMX_ODU2FXC_ODU2)            +\
    (XC_MAX_OMMX_ODU2FXC_ODUF_INTF           * XC_MAX_XC_OMMX_ODU2FXC_ODUF)            +\
    (XC_MAX_OMMX_ODU10XC_ODU1_INTF           * XC_MAX_XC_OMMX_ODU10XC_ODU1)            +\
    (XC_MAX_OMMX_ODU10XC_ODU0_INTF           * XC_MAX_XC_OMMX_ODU10XC_ODU0)            )

// 
// Breakdown of OMMX XC CFG Region
//

/*
The compiler has a limit of 256 levels of nested macros, therefore, we have to use number to instead.
// ODUXC
#define XC_OMMX_ODUXC_ODUK_0_START                  (0)
#define XC_OMMX_ODUXC_ODUK_0_END                    (XC_OMMX_ODUXC_ODUK_0_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1) 
#define XC_OMMX_ODUXC_ODUK_0_VIRTUAL_START          (XC_OMMX_ODUXC_ODUK_0_END+1)
#define XC_OMMX_ODUXC_ODUK_0_VIRTUAL_END            (XC_OMMX_ODUXC_ODUK_0_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1) 
#define XC_OMMX_ODUXC_ODUK_1_START                  (XC_OMMX_ODUXC_ODUK_0_VIRTUAL_END+1)
#define XC_OMMX_ODUXC_ODUK_1_END                    (XC_OMMX_ODUXC_ODUK_1_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1)
#define XC_OMMX_ODUXC_ODUK_1_VIRTUAL_START          (XC_OMMX_ODUXC_ODUK_1_END+1)
#define XC_OMMX_ODUXC_ODUK_1_VIRTUAL_END            (XC_OMMX_ODUXC_ODUK_1_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1) 
#define XC_OMMX_ODUXC_ODUK_2_START                  (XC_OMMX_ODUXC_ODUK_1_VIRTUAL_END+1)
#define XC_OMMX_ODUXC_ODUK_2_END                    (XC_OMMX_ODUXC_ODUK_2_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1) 
#define XC_OMMX_ODUXC_ODUK_2_VIRTUAL_START          (XC_OMMX_ODUXC_ODUK_2_END+1)
#define XC_OMMX_ODUXC_ODUK_2_VIRTUAL_END            (XC_OMMX_ODUXC_ODUK_2_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1) 
#define XC_OMMX_ODUXC_ODUK_3_START                  (XC_OMMX_ODUXC_ODUK_2_VIRTUAL_END+1)
#define XC_OMMX_ODUXC_ODUK_3_END                    (XC_OMMX_ODUXC_ODUK_3_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1)
#define XC_OMMX_ODUXC_ODUK_3_VIRTUAL_START          (XC_OMMX_ODUXC_ODUK_3_END+1)
#define XC_OMMX_ODUXC_ODUK_3_VIRTUAL_END            (XC_OMMX_ODUXC_ODUK_3_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_OTNK-1) 
#define XC_OMMX_ODUXC_ODU1_START                    (XC_OMMX_ODUXC_ODUK_3_VIRTUAL_END+1)
#define XC_OMMX_ODUXC_ODU1_END                      (XC_OMMX_ODUXC_ODU1_START + XC_MAX_XC_OMMX_ODUXC_OTN1-1)
#define XC_OMMX_ODUXC_ODU1_VIRTUAL_START            (XC_OMMX_ODUXC_ODU1_END+1)
#define XC_OMMX_ODUXC_ODU1_VIRTUAL_END              (XC_OMMX_ODUXC_ODU1_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_OTN1-1) 
#define XC_OMMX_ODUXC_ODU2_START                    (XC_OMMX_ODUXC_ODU1_VIRTUAL_END+1)
#define XC_OMMX_ODUXC_ODU2_END                      (XC_OMMX_ODUXC_ODU2_START + XC_MAX_XC_OMMX_ODUXC_OTN2-1) 
#define XC_OMMX_ODUXC_ODU2_VIRTUAL_START            (XC_OMMX_ODUXC_ODU2_END+1)
#define XC_OMMX_ODUXC_ODU2_VIRTUAL_END              (XC_OMMX_ODUXC_ODU2_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_OTN2-1)
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_START            (XC_OMMX_ODUXC_ODU2_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_END              (XC_OMMX_ODUXC_ODUKPP_ODUK0_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK-1) 
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_START    (XC_OMMX_ODUXC_ODUKPP_ODUK0_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_END      (XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK-1) 
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_START            (XC_OMMX_ODUXC_ODUKPP_ODUK0_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_END              (XC_OMMX_ODUXC_ODUKPP_ODUK1_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK-1) 
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_START    (XC_OMMX_ODUXC_ODUKPP_ODUK1_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_END      (XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODUK-1) 
#define XC_OMMX_ODUXC_ODUKPP_ODU1_START             (XC_OMMX_ODUXC_ODUKPP_ODUK1_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODU1_END               (XC_OMMX_ODUXC_ODUKPP_ODU1_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU1-1) 
#define XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_START     (XC_OMMX_ODUXC_ODUKPP_ODU1_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_END       (XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU1-1) 
#define XC_OMMX_ODUXC_ODUKPP_ODU2_START             (XC_OMMX_ODUXC_ODUKPP_ODU1_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_END               (XC_OMMX_ODUXC_ODUKPP_ODU2_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU2-1)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_START     (XC_OMMX_ODUXC_ODUKPP_ODU2_END+1)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_END       (XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_START + XC_MAX_XC_OMMX_ODUXC_ODUKPP_ODU2-1) 
 
// FRMODUXC
#define XC_OMMX_FRMODUXC_FRM_OTUK_START        (XC_OMMX_ODUXC_ODUKPP_ODU2_END+1)
#define XC_OMMX_FRMODUXC_FRM_OTUK_END          (XC_OMMX_FRMODUXC_FRM_OTUK_START    + XC_MAX_XC_OMMX_FRMODUXC_FRM_OTUK-1)
#define XC_OMMX_FRMODUXC_FRM_OTU1_START        (XC_OMMX_FRMODUXC_FRM_OTUK_END+1)
#define XC_OMMX_FRMODUXC_FRM_OTU1_END          (XC_OMMX_FRMODUXC_FRM_OTU1_START    + XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU1-1)
#define XC_OMMX_FRMODUXC_FRM_OTU2_START        (XC_OMMX_FRMODUXC_FRM_OTU1_END+1)
#define XC_OMMX_FRMODUXC_FRM_OTU2_END          (XC_OMMX_FRMODUXC_FRM_OTU2_START    + XC_MAX_XC_OMMX_FRMODUXC_FRM_OTU2-1)

#define XC_OMMX_FRMODUXC_FRM_CBR_START         (XC_OMMX_FRMODUXC_FRM_OTU2_END+1)
#define XC_OMMX_FRMODUXC_FRM_CBR_END           (XC_OMMX_FRMODUXC_FRM_CBR_START     + XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR-1)
#define XC_OMMX_FRMODUXC_FRM_CBR10G_START      (XC_OMMX_FRMODUXC_FRM_CBR_END+1)
#define XC_OMMX_FRMODUXC_FRM_CBR10G_END        (XC_OMMX_FRMODUXC_FRM_CBR10G_START  + XC_MAX_XC_OMMX_FRMODUXC_FRM_CBR10G-1)
#define XC_OMMX_FRMODUXC_FRM_GE_START          (XC_OMMX_FRMODUXC_FRM_CBR10G_END+1)
#define XC_OMMX_FRMODUXC_FRM_GE_END            (XC_OMMX_FRMODUXC_FRM_GE_START      + XC_MAX_XC_OMMX_FRMODUXC_FRM_GE-1)
#define XC_OMMX_FRMODUXC_FRM_GE10G_START       (XC_OMMX_FRMODUXC_FRM_GE_END+1)
#define XC_OMMX_FRMODUXC_FRM_GE10G_END         (XC_OMMX_FRMODUXC_FRM_GE10G_START   + XC_MAX_XC_OMMX_FRMODUXC_FRM_GE10G-1)
#define XC_OMMX_FRMODUXC_ODU_OTUK_START        (XC_OMMX_FRMODUXC_FRM_GE10G_END+1)
#define XC_OMMX_FRMODUXC_ODU_OTUK_END          (XC_OMMX_FRMODUXC_ODU_OTUK_START    + XC_MAX_XC_OMMX_FRMODUXC_ODU_OTUK-1)
#define XC_OMMX_FRMODUXC_ODU_OTU1_START        (XC_OMMX_FRMODUXC_ODU_OTUK_END+1)
#define XC_OMMX_FRMODUXC_ODU_OTU1_END          (XC_OMMX_FRMODUXC_ODU_OTU1_START    + XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU1-1)
#define XC_OMMX_FRMODUXC_ODU_OTU2_START        (XC_OMMX_FRMODUXC_ODU_OTU1_END+1)
#define XC_OMMX_FRMODUXC_ODU_OTU2_END          (XC_OMMX_FRMODUXC_ODU_OTU2_START    + XC_MAX_XC_OMMX_FRMODUXC_ODU_OTU2-1)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_START  (XC_OMMX_FRMODUXC_ODU_OTU2_END+1)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_END    (XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_START   + XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU2-1)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_START  (XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_END+1)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_END    (XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_START   + XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU1-1)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_START  (XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_END+1)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_END    (XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_START   + XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODUK-1)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_START  (XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_END+1)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_END    (XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_START   + XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU2-1)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_START  (XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_END+1)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_END    (XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_START   + XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODU1-1)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_START  (XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_END+1)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_END    (XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_START   + XC_MAX_XC_OMMX_FRMODUXC_ODU_VCAT_ODUK-1)

// ODU21 MUX
#define XC_OMMX_ODU21XC_ODU2_0_START           (XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_END+1)
#define XC_OMMX_ODU21XC_ODU2_0_END             (XC_OMMX_ODU21XC_ODU2_0_START + XC_MAX_XC_OMMX_ODU21XC_ODU2-1)
#define XC_OMMX_ODU21XC_ODU2_1_START           (XC_OMMX_ODU21XC_ODU2_0_END+1)
#define XC_OMMX_ODU21XC_ODU2_1_END             (XC_OMMX_ODU21XC_ODU2_1_START + XC_MAX_XC_OMMX_ODU21XC_ODU2-1)

#define XC_OMMX_ODU21XC_ODU1_0_START           (XC_OMMX_ODU21XC_ODU2_1_END+1)
#define XC_OMMX_ODU21XC_ODU1_0_END             (XC_OMMX_ODU21XC_ODU1_0_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_1_START           (XC_OMMX_ODU21XC_ODU1_0_END+1)
#define XC_OMMX_ODU21XC_ODU1_1_END             (XC_OMMX_ODU21XC_ODU1_1_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_2_START           (XC_OMMX_ODU21XC_ODU1_1_END+1)
#define XC_OMMX_ODU21XC_ODU1_2_END             (XC_OMMX_ODU21XC_ODU1_2_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_3_START           (XC_OMMX_ODU21XC_ODU1_2_END+1)
#define XC_OMMX_ODU21XC_ODU1_3_END             (XC_OMMX_ODU21XC_ODU1_3_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_4_START           (XC_OMMX_ODU21XC_ODU1_3_END+1)
#define XC_OMMX_ODU21XC_ODU1_4_END             (XC_OMMX_ODU21XC_ODU1_4_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_5_START           (XC_OMMX_ODU21XC_ODU1_4_END+1)
#define XC_OMMX_ODU21XC_ODU1_5_END             (XC_OMMX_ODU21XC_ODU1_5_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_6_START           (XC_OMMX_ODU21XC_ODU1_5_END+1)
#define XC_OMMX_ODU21XC_ODU1_6_END             (XC_OMMX_ODU21XC_ODU1_6_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_7_START           (XC_OMMX_ODU21XC_ODU1_6_END+1)
#define XC_OMMX_ODU21XC_ODU1_7_END             (XC_OMMX_ODU21XC_ODU1_7_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_8_START           (XC_OMMX_ODU21XC_ODU1_7_END+1)
#define XC_OMMX_ODU21XC_ODU1_8_END             (XC_OMMX_ODU21XC_ODU1_8_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_9_START           (XC_OMMX_ODU21XC_ODU1_8_END+1)
#define XC_OMMX_ODU21XC_ODU1_9_END             (XC_OMMX_ODU21XC_ODU1_9_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_10_START          (XC_OMMX_ODU21XC_ODU1_9_END+1)
#define XC_OMMX_ODU21XC_ODU1_10_END            (XC_OMMX_ODU21XC_ODU1_10_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_11_START          (XC_OMMX_ODU21XC_ODU1_10_END+1)
#define XC_OMMX_ODU21XC_ODU1_11_END            (XC_OMMX_ODU21XC_ODU1_11_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_12_START          (XC_OMMX_ODU21XC_ODU1_11_END+1)
#define XC_OMMX_ODU21XC_ODU1_12_END            (XC_OMMX_ODU21XC_ODU1_12_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_13_START          (XC_OMMX_ODU21XC_ODU1_12_END+1)
#define XC_OMMX_ODU21XC_ODU1_13_END            (XC_OMMX_ODU21XC_ODU1_13_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_14_START          (XC_OMMX_ODU21XC_ODU1_13_END+1)
#define XC_OMMX_ODU21XC_ODU1_14_END            (XC_OMMX_ODU21XC_ODU1_14_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
#define XC_OMMX_ODU21XC_ODU1_15_START          (XC_OMMX_ODU21XC_ODU1_14_END+1)
#define XC_OMMX_ODU21XC_ODU1_15_END            (XC_OMMX_ODU21XC_ODU1_15_START + XC_MAX_XC_OMMX_ODU21XC_ODU1-1)
*/

#define XC_OMMX_ODUXC_ODUK_0_START                  (0)
#define XC_OMMX_ODUXC_ODUK_0_END                    (7)
#define XC_OMMX_ODUXC_ODUK_0_VIRTUAL_START          (8)
#define XC_OMMX_ODUXC_ODUK_0_VIRTUAL_END            (15)
#define XC_OMMX_ODUXC_ODUK_1_START                  (16)
#define XC_OMMX_ODUXC_ODUK_1_END                    (23)
#define XC_OMMX_ODUXC_ODUK_1_VIRTUAL_START          (24)
#define XC_OMMX_ODUXC_ODUK_1_VIRTUAL_END            (31)
#define XC_OMMX_ODUXC_ODUK_2_START                  (32)
#define XC_OMMX_ODUXC_ODUK_2_END                    (39)
#define XC_OMMX_ODUXC_ODUK_2_VIRTUAL_START          (40)
#define XC_OMMX_ODUXC_ODUK_2_VIRTUAL_END            (47)
#define XC_OMMX_ODUXC_ODUK_3_START                  (48)
#define XC_OMMX_ODUXC_ODUK_3_END                    (55)
#define XC_OMMX_ODUXC_ODUK_3_VIRTUAL_START          (56)
#define XC_OMMX_ODUXC_ODUK_3_VIRTUAL_END            (63)
#define XC_OMMX_ODUXC_ODU1_START                    (64)
#define XC_OMMX_ODUXC_ODU1_END                      (79)
#define XC_OMMX_ODUXC_ODU1_VIRTUAL_START            (80)
#define XC_OMMX_ODUXC_ODU1_VIRTUAL_END              (95)
#define XC_OMMX_ODUXC_ODU2_START                    (96)
#define XC_OMMX_ODUXC_ODU2_END                      (97)
#define XC_OMMX_ODUXC_ODU2_VIRTUAL_START            (98)
#define XC_OMMX_ODUXC_ODU2_VIRTUAL_END              (99)
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_START            (100)
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_END              (107)
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_START    (108)
#define XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_END      (115)
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_START            (116)
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_END              (123)
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_START    (124)
#define XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_END      (131)
#define XC_OMMX_ODUXC_ODUKPP_ODU1_START             (132)
#define XC_OMMX_ODUXC_ODUKPP_ODU1_END               (139)
#define XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_START     (140)
#define XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_END       (147)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_START             (148)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_END               (149)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_START     (150)
#define XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_END       (151)

// FRMODUXC
#define XC_OMMX_FRMODUXC_FRM_OTUK_START             (152)
#define XC_OMMX_FRMODUXC_FRM_OTUK_END               (183)
#define XC_OMMX_FRMODUXC_FRM_OTU1_START             (184)
#define XC_OMMX_FRMODUXC_FRM_OTU1_END               (199)
#define XC_OMMX_FRMODUXC_FRM_OTU2_START             (200)
#define XC_OMMX_FRMODUXC_FRM_OTU2_END               (201)

#define XC_OMMX_FRMODUXC_FRM_CBR_START              (202)
#define XC_OMMX_FRMODUXC_FRM_CBR_END                (209)
#define XC_OMMX_FRMODUXC_FRM_CBR10G_START           (210)
#define XC_OMMX_FRMODUXC_FRM_CBR10G_END             (211)
#define XC_OMMX_FRMODUXC_FRM_GE_START               (212)
#define XC_OMMX_FRMODUXC_FRM_GE_END                 (219)
#define XC_OMMX_FRMODUXC_FRM_GE10G_START            (220)
#define XC_OMMX_FRMODUXC_FRM_GE10G_END              (221)
#define XC_OMMX_FRMODUXC_ODU_OTUK_START             (222)
#define XC_OMMX_FRMODUXC_ODU_OTUK_END               (253)
#define XC_OMMX_FRMODUXC_ODU_OTU1_START             (254)
#define XC_OMMX_FRMODUXC_ODU_OTU1_END               (269)
#define XC_OMMX_FRMODUXC_ODU_OTU2_START             (270)
#define XC_OMMX_FRMODUXC_ODU_OTU2_END               (271)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_START       (272)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_END         (272)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_START       (273)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_END         (276)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_START       (277)
#define XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_END         (284)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_START       (285)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_END         (285)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_START       (286)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_END         (289)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_START       (290)
#define XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_END         (297)

// ODU21 MUX
#define XC_OMMX_ODU21XC_ODU2_0_START                (298)
#define XC_OMMX_ODU21XC_ODU2_0_END                  (305)
#define XC_OMMX_ODU21XC_ODU2_1_START                (306)
#define XC_OMMX_ODU21XC_ODU2_1_END                  (313)

#define XC_OMMX_ODU21XC_ODU1_0_START                (314)
#define XC_OMMX_ODU21XC_ODU1_0_END                  (315)
#define XC_OMMX_ODU21XC_ODU1_1_START                (316)
#define XC_OMMX_ODU21XC_ODU1_1_END                  (317)
#define XC_OMMX_ODU21XC_ODU1_2_START                (318)
#define XC_OMMX_ODU21XC_ODU1_2_END                  (319)
#define XC_OMMX_ODU21XC_ODU1_3_START                (320)
#define XC_OMMX_ODU21XC_ODU1_3_END                  (321)
#define XC_OMMX_ODU21XC_ODU1_4_START                (322)
#define XC_OMMX_ODU21XC_ODU1_4_END                  (323)
#define XC_OMMX_ODU21XC_ODU1_5_START                (324)
#define XC_OMMX_ODU21XC_ODU1_5_END                  (325)
#define XC_OMMX_ODU21XC_ODU1_6_START                (326)
#define XC_OMMX_ODU21XC_ODU1_6_END                  (327)
#define XC_OMMX_ODU21XC_ODU1_7_START                (328)
#define XC_OMMX_ODU21XC_ODU1_7_END                  (329)
#define XC_OMMX_ODU21XC_ODU1_8_START                (330)
#define XC_OMMX_ODU21XC_ODU1_8_END                  (331)
#define XC_OMMX_ODU21XC_ODU1_9_START                (332)
#define XC_OMMX_ODU21XC_ODU1_9_END                  (333)
#define XC_OMMX_ODU21XC_ODU1_10_START               (334)
#define XC_OMMX_ODU21XC_ODU1_10_END                 (335)
#define XC_OMMX_ODU21XC_ODU1_11_START               (336)
#define XC_OMMX_ODU21XC_ODU1_11_END                 (337)
#define XC_OMMX_ODU21XC_ODU1_12_START               (338)
#define XC_OMMX_ODU21XC_ODU1_12_END                 (339)
#define XC_OMMX_ODU21XC_ODU1_13_START               (340)
#define XC_OMMX_ODU21XC_ODU1_13_END                 (341)
#define XC_OMMX_ODU21XC_ODU1_14_START               (342)
#define XC_OMMX_ODU21XC_ODU1_14_END                 (343)
#define XC_OMMX_ODU21XC_ODU1_15_START               (344)
#define XC_OMMX_ODU21XC_ODU1_15_END                 (345)

// ODU20 MUX
#define XC_OMMX_ODU20XC_ODU2_0_START                (XC_OMMX_ODU21XC_ODU1_15_END+1)
#define XC_OMMX_ODU20XC_ODU2_0_END                  (XC_OMMX_ODU20XC_ODU2_0_START + XC_MAX_XC_OMMX_ODU20XC_ODU2-1)
#define XC_OMMX_ODU20XC_ODU2_1_START                (XC_OMMX_ODU20XC_ODU2_0_END+1)
#define XC_OMMX_ODU20XC_ODU2_1_END                  (XC_OMMX_ODU20XC_ODU2_1_START + XC_MAX_XC_OMMX_ODU20XC_ODU2-1)

#define XC_OMMX_ODU20XC_ODU0_0_START                (XC_OMMX_ODU20XC_ODU2_1_END+1)
#define XC_OMMX_ODU20XC_ODU0_0_END                  (XC_OMMX_ODU20XC_ODU0_0_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_1_START                (XC_OMMX_ODU20XC_ODU0_0_END+1)
#define XC_OMMX_ODU20XC_ODU0_1_END                  (XC_OMMX_ODU20XC_ODU0_1_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_2_START                (XC_OMMX_ODU20XC_ODU0_1_END+1)
#define XC_OMMX_ODU20XC_ODU0_2_END                  (XC_OMMX_ODU20XC_ODU0_2_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_3_START                (XC_OMMX_ODU20XC_ODU0_2_END+1)
#define XC_OMMX_ODU20XC_ODU0_3_END                  (XC_OMMX_ODU20XC_ODU0_3_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_4_START                (XC_OMMX_ODU20XC_ODU0_3_END+1)
#define XC_OMMX_ODU20XC_ODU0_4_END                  (XC_OMMX_ODU20XC_ODU0_4_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_5_START                (XC_OMMX_ODU20XC_ODU0_4_END+1)
#define XC_OMMX_ODU20XC_ODU0_5_END                  (XC_OMMX_ODU20XC_ODU0_5_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_6_START                (XC_OMMX_ODU20XC_ODU0_5_END+1)
#define XC_OMMX_ODU20XC_ODU0_6_END                  (XC_OMMX_ODU20XC_ODU0_6_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_7_START                (XC_OMMX_ODU20XC_ODU0_6_END+1)
#define XC_OMMX_ODU20XC_ODU0_7_END                  (XC_OMMX_ODU20XC_ODU0_7_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_8_START                (XC_OMMX_ODU20XC_ODU0_7_END+1)
#define XC_OMMX_ODU20XC_ODU0_8_END                  (XC_OMMX_ODU20XC_ODU0_8_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_9_START                (XC_OMMX_ODU20XC_ODU0_8_END+1)
#define XC_OMMX_ODU20XC_ODU0_9_END                  (XC_OMMX_ODU20XC_ODU0_9_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_10_START               (XC_OMMX_ODU20XC_ODU0_9_END+1)
#define XC_OMMX_ODU20XC_ODU0_10_END                 (XC_OMMX_ODU20XC_ODU0_10_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_11_START               (XC_OMMX_ODU20XC_ODU0_10_END+1)
#define XC_OMMX_ODU20XC_ODU0_11_END                 (XC_OMMX_ODU20XC_ODU0_11_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_12_START               (XC_OMMX_ODU20XC_ODU0_11_END+1)
#define XC_OMMX_ODU20XC_ODU0_12_END                 (XC_OMMX_ODU20XC_ODU0_12_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_13_START               (XC_OMMX_ODU20XC_ODU0_12_END+1)
#define XC_OMMX_ODU20XC_ODU0_13_END                 (XC_OMMX_ODU20XC_ODU0_13_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_14_START               (XC_OMMX_ODU20XC_ODU0_13_END+1)
#define XC_OMMX_ODU20XC_ODU0_14_END                 (XC_OMMX_ODU20XC_ODU0_14_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_15_START               (XC_OMMX_ODU20XC_ODU0_14_END+1)
#define XC_OMMX_ODU20XC_ODU0_15_END                 (XC_OMMX_ODU20XC_ODU0_15_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_16_START               (XC_OMMX_ODU20XC_ODU0_15_END+1)
#define XC_OMMX_ODU20XC_ODU0_16_END                 (XC_OMMX_ODU20XC_ODU0_16_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_17_START               (XC_OMMX_ODU20XC_ODU0_16_END+1)
#define XC_OMMX_ODU20XC_ODU0_17_END                 (XC_OMMX_ODU20XC_ODU0_17_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_18_START               (XC_OMMX_ODU20XC_ODU0_17_END+1)
#define XC_OMMX_ODU20XC_ODU0_18_END                 (XC_OMMX_ODU20XC_ODU0_18_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_19_START               (XC_OMMX_ODU20XC_ODU0_18_END+1)
#define XC_OMMX_ODU20XC_ODU0_19_END                 (XC_OMMX_ODU20XC_ODU0_19_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_20_START               (XC_OMMX_ODU20XC_ODU0_19_END+1)
#define XC_OMMX_ODU20XC_ODU0_20_END                 (XC_OMMX_ODU20XC_ODU0_20_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_21_START               (XC_OMMX_ODU20XC_ODU0_20_END+1)
#define XC_OMMX_ODU20XC_ODU0_21_END                 (XC_OMMX_ODU20XC_ODU0_21_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_22_START               (XC_OMMX_ODU20XC_ODU0_21_END+1)
#define XC_OMMX_ODU20XC_ODU0_22_END                 (XC_OMMX_ODU20XC_ODU0_22_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_23_START               (XC_OMMX_ODU20XC_ODU0_22_END+1)
#define XC_OMMX_ODU20XC_ODU0_23_END                 (XC_OMMX_ODU20XC_ODU0_23_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_24_START               (XC_OMMX_ODU20XC_ODU0_23_END+1)
#define XC_OMMX_ODU20XC_ODU0_24_END                 (XC_OMMX_ODU20XC_ODU0_24_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_25_START               (XC_OMMX_ODU20XC_ODU0_24_END+1)
#define XC_OMMX_ODU20XC_ODU0_25_END                 (XC_OMMX_ODU20XC_ODU0_25_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_26_START               (XC_OMMX_ODU20XC_ODU0_25_END+1)
#define XC_OMMX_ODU20XC_ODU0_26_END                 (XC_OMMX_ODU20XC_ODU0_26_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_27_START               (XC_OMMX_ODU20XC_ODU0_26_END+1)
#define XC_OMMX_ODU20XC_ODU0_27_END                 (XC_OMMX_ODU20XC_ODU0_27_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_28_START               (XC_OMMX_ODU20XC_ODU0_27_END+1)
#define XC_OMMX_ODU20XC_ODU0_28_END                 (XC_OMMX_ODU20XC_ODU0_28_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_29_START               (XC_OMMX_ODU20XC_ODU0_28_END+1)
#define XC_OMMX_ODU20XC_ODU0_29_END                 (XC_OMMX_ODU20XC_ODU0_29_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_30_START               (XC_OMMX_ODU20XC_ODU0_29_END+1)
#define XC_OMMX_ODU20XC_ODU0_30_END                 (XC_OMMX_ODU20XC_ODU0_30_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)
#define XC_OMMX_ODU20XC_ODU0_31_START               (XC_OMMX_ODU20XC_ODU0_30_END+1)
#define XC_OMMX_ODU20XC_ODU0_31_END                 (XC_OMMX_ODU20XC_ODU0_31_START + XC_MAX_XC_OMMX_ODU20XC_ODU0-1)

// ODU2F MUX
#define XC_OMMX_ODU2FXC_ODU2_0_START                (XC_OMMX_ODU20XC_ODU0_31_END+1)
#define XC_OMMX_ODU2FXC_ODU2_0_END                  (XC_OMMX_ODU2FXC_ODU2_0_START + XC_MAX_XC_OMMX_ODU2FXC_ODU2-1)
#define XC_OMMX_ODU2FXC_ODU2_1_START                (XC_OMMX_ODU2FXC_ODU2_0_END+1)
#define XC_OMMX_ODU2FXC_ODU2_1_END                  (XC_OMMX_ODU2FXC_ODU2_1_START + XC_MAX_XC_OMMX_ODU2FXC_ODU2-1)

#define XC_OMMX_ODU2FXC_ODUF_0_START                (XC_OMMX_ODU2FXC_ODU2_1_END+1)
#define XC_OMMX_ODU2FXC_ODUF_0_END                  (XC_OMMX_ODU2FXC_ODUF_0_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_1_START                (XC_OMMX_ODU2FXC_ODUF_0_END+1)
#define XC_OMMX_ODU2FXC_ODUF_1_END                  (XC_OMMX_ODU2FXC_ODUF_1_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_2_START                (XC_OMMX_ODU2FXC_ODUF_1_END+1)
#define XC_OMMX_ODU2FXC_ODUF_2_END                  (XC_OMMX_ODU2FXC_ODUF_2_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_3_START                (XC_OMMX_ODU2FXC_ODUF_2_END+1)
#define XC_OMMX_ODU2FXC_ODUF_3_END                  (XC_OMMX_ODU2FXC_ODUF_3_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_4_START                (XC_OMMX_ODU2FXC_ODUF_3_END+1)
#define XC_OMMX_ODU2FXC_ODUF_4_END                  (XC_OMMX_ODU2FXC_ODUF_4_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_5_START                (XC_OMMX_ODU2FXC_ODUF_4_END+1)
#define XC_OMMX_ODU2FXC_ODUF_5_END                  (XC_OMMX_ODU2FXC_ODUF_5_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_6_START                (XC_OMMX_ODU2FXC_ODUF_5_END+1)
#define XC_OMMX_ODU2FXC_ODUF_6_END                  (XC_OMMX_ODU2FXC_ODUF_6_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_7_START                (XC_OMMX_ODU2FXC_ODUF_6_END+1)
#define XC_OMMX_ODU2FXC_ODUF_7_END                  (XC_OMMX_ODU2FXC_ODUF_7_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_8_START                (XC_OMMX_ODU2FXC_ODUF_7_END+1)
#define XC_OMMX_ODU2FXC_ODUF_8_END                  (XC_OMMX_ODU2FXC_ODUF_8_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_9_START                (XC_OMMX_ODU2FXC_ODUF_8_END+1)
#define XC_OMMX_ODU2FXC_ODUF_9_END                  (XC_OMMX_ODU2FXC_ODUF_9_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_10_START               (XC_OMMX_ODU2FXC_ODUF_9_END+1)
#define XC_OMMX_ODU2FXC_ODUF_10_END                 (XC_OMMX_ODU2FXC_ODUF_10_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_11_START               (XC_OMMX_ODU2FXC_ODUF_10_END+1)
#define XC_OMMX_ODU2FXC_ODUF_11_END                 (XC_OMMX_ODU2FXC_ODUF_11_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_12_START               (XC_OMMX_ODU2FXC_ODUF_11_END+1)
#define XC_OMMX_ODU2FXC_ODUF_12_END                 (XC_OMMX_ODU2FXC_ODUF_12_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_13_START               (XC_OMMX_ODU2FXC_ODUF_12_END+1)
#define XC_OMMX_ODU2FXC_ODUF_13_END                 (XC_OMMX_ODU2FXC_ODUF_13_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_14_START               (XC_OMMX_ODU2FXC_ODUF_13_END+1)
#define XC_OMMX_ODU2FXC_ODUF_14_END                 (XC_OMMX_ODU2FXC_ODUF_14_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_15_START               (XC_OMMX_ODU2FXC_ODUF_14_END+1)
#define XC_OMMX_ODU2FXC_ODUF_15_END                 (XC_OMMX_ODU2FXC_ODUF_15_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_16_START               (XC_OMMX_ODU2FXC_ODUF_15_END+1)
#define XC_OMMX_ODU2FXC_ODUF_16_END                 (XC_OMMX_ODU2FXC_ODUF_16_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_17_START               (XC_OMMX_ODU2FXC_ODUF_16_END+1)
#define XC_OMMX_ODU2FXC_ODUF_17_END                 (XC_OMMX_ODU2FXC_ODUF_17_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_18_START               (XC_OMMX_ODU2FXC_ODUF_17_END+1)
#define XC_OMMX_ODU2FXC_ODUF_18_END                 (XC_OMMX_ODU2FXC_ODUF_18_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_19_START               (XC_OMMX_ODU2FXC_ODUF_18_END+1)
#define XC_OMMX_ODU2FXC_ODUF_19_END                 (XC_OMMX_ODU2FXC_ODUF_19_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_20_START               (XC_OMMX_ODU2FXC_ODUF_19_END+1)
#define XC_OMMX_ODU2FXC_ODUF_20_END                 (XC_OMMX_ODU2FXC_ODUF_20_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_21_START               (XC_OMMX_ODU2FXC_ODUF_20_END+1)
#define XC_OMMX_ODU2FXC_ODUF_21_END                 (XC_OMMX_ODU2FXC_ODUF_21_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_22_START               (XC_OMMX_ODU2FXC_ODUF_21_END+1)
#define XC_OMMX_ODU2FXC_ODUF_22_END                 (XC_OMMX_ODU2FXC_ODUF_22_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_23_START               (XC_OMMX_ODU2FXC_ODUF_22_END+1)
#define XC_OMMX_ODU2FXC_ODUF_23_END                 (XC_OMMX_ODU2FXC_ODUF_23_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_24_START               (XC_OMMX_ODU2FXC_ODUF_23_END+1)
#define XC_OMMX_ODU2FXC_ODUF_24_END                 (XC_OMMX_ODU2FXC_ODUF_24_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_25_START               (XC_OMMX_ODU2FXC_ODUF_24_END+1)
#define XC_OMMX_ODU2FXC_ODUF_25_END                 (XC_OMMX_ODU2FXC_ODUF_25_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_26_START               (XC_OMMX_ODU2FXC_ODUF_25_END+1)
#define XC_OMMX_ODU2FXC_ODUF_26_END                 (XC_OMMX_ODU2FXC_ODUF_26_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_27_START               (XC_OMMX_ODU2FXC_ODUF_26_END+1)
#define XC_OMMX_ODU2FXC_ODUF_27_END                 (XC_OMMX_ODU2FXC_ODUF_27_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_28_START               (XC_OMMX_ODU2FXC_ODUF_27_END+1)
#define XC_OMMX_ODU2FXC_ODUF_28_END                 (XC_OMMX_ODU2FXC_ODUF_28_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_29_START               (XC_OMMX_ODU2FXC_ODUF_28_END+1)
#define XC_OMMX_ODU2FXC_ODUF_29_END                 (XC_OMMX_ODU2FXC_ODUF_29_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_30_START               (XC_OMMX_ODU2FXC_ODUF_29_END+1)
#define XC_OMMX_ODU2FXC_ODUF_30_END                 (XC_OMMX_ODU2FXC_ODUF_30_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)
#define XC_OMMX_ODU2FXC_ODUF_31_START               (XC_OMMX_ODU2FXC_ODUF_30_END+1)
#define XC_OMMX_ODU2FXC_ODUF_31_END                 (XC_OMMX_ODU2FXC_ODUF_31_START + XC_MAX_XC_OMMX_ODU2FXC_ODUF-1)

// ODU10 MUX
#define XC_OMMX_ODU10XC_ODU1_0_START                (XC_OMMX_ODU2FXC_ODUF_31_END+1)
#define XC_OMMX_ODU10XC_ODU1_0_END                  (XC_OMMX_ODU10XC_ODU1_0_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_1_START                (XC_OMMX_ODU10XC_ODU1_0_END+1)
#define XC_OMMX_ODU10XC_ODU1_1_END                  (XC_OMMX_ODU10XC_ODU1_1_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_2_START                (XC_OMMX_ODU10XC_ODU1_1_END+1)
#define XC_OMMX_ODU10XC_ODU1_2_END                  (XC_OMMX_ODU10XC_ODU1_2_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_3_START                (XC_OMMX_ODU10XC_ODU1_2_END+1)
#define XC_OMMX_ODU10XC_ODU1_3_END                  (XC_OMMX_ODU10XC_ODU1_3_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_4_START                (XC_OMMX_ODU10XC_ODU1_3_END+1)
#define XC_OMMX_ODU10XC_ODU1_4_END                  (XC_OMMX_ODU10XC_ODU1_4_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_5_START                (XC_OMMX_ODU10XC_ODU1_4_END+1)
#define XC_OMMX_ODU10XC_ODU1_5_END                  (XC_OMMX_ODU10XC_ODU1_5_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_6_START                (XC_OMMX_ODU10XC_ODU1_5_END+1)
#define XC_OMMX_ODU10XC_ODU1_6_END                  (XC_OMMX_ODU10XC_ODU1_6_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_7_START                (XC_OMMX_ODU10XC_ODU1_6_END+1)
#define XC_OMMX_ODU10XC_ODU1_7_END                  (XC_OMMX_ODU10XC_ODU1_7_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_8_START                (XC_OMMX_ODU10XC_ODU1_7_END+1)
#define XC_OMMX_ODU10XC_ODU1_8_END                  (XC_OMMX_ODU10XC_ODU1_8_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_9_START                (XC_OMMX_ODU10XC_ODU1_8_END+1)
#define XC_OMMX_ODU10XC_ODU1_9_END                  (XC_OMMX_ODU10XC_ODU1_9_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_10_START               (XC_OMMX_ODU10XC_ODU1_9_END+1)
#define XC_OMMX_ODU10XC_ODU1_10_END                 (XC_OMMX_ODU10XC_ODU1_10_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_11_START               (XC_OMMX_ODU10XC_ODU1_10_END+1)
#define XC_OMMX_ODU10XC_ODU1_11_END                 (XC_OMMX_ODU10XC_ODU1_11_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_12_START               (XC_OMMX_ODU10XC_ODU1_11_END+1)
#define XC_OMMX_ODU10XC_ODU1_12_END                 (XC_OMMX_ODU10XC_ODU1_12_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_13_START               (XC_OMMX_ODU10XC_ODU1_12_END+1)
#define XC_OMMX_ODU10XC_ODU1_13_END                 (XC_OMMX_ODU10XC_ODU1_13_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_14_START               (XC_OMMX_ODU10XC_ODU1_13_END+1)
#define XC_OMMX_ODU10XC_ODU1_14_END                 (XC_OMMX_ODU10XC_ODU1_14_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)
#define XC_OMMX_ODU10XC_ODU1_15_START               (XC_OMMX_ODU10XC_ODU1_14_END+1)
#define XC_OMMX_ODU10XC_ODU1_15_END                 (XC_OMMX_ODU10XC_ODU1_15_START + XC_MAX_XC_OMMX_ODU10XC_ODU1-1)

#define XC_OMMX_ODU10XC_ODU0_0_START                (XC_OMMX_ODU10XC_ODU1_15_END+1)
#define XC_OMMX_ODU10XC_ODU0_0_END                  (XC_OMMX_ODU10XC_ODU0_0_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_1_START                (XC_OMMX_ODU10XC_ODU0_0_END+1)
#define XC_OMMX_ODU10XC_ODU0_1_END                  (XC_OMMX_ODU10XC_ODU0_1_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_2_START                (XC_OMMX_ODU10XC_ODU0_1_END+1)
#define XC_OMMX_ODU10XC_ODU0_2_END                  (XC_OMMX_ODU10XC_ODU0_2_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_3_START                (XC_OMMX_ODU10XC_ODU0_2_END+1)
#define XC_OMMX_ODU10XC_ODU0_3_END                  (XC_OMMX_ODU10XC_ODU0_3_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_4_START                (XC_OMMX_ODU10XC_ODU0_3_END+1)
#define XC_OMMX_ODU10XC_ODU0_4_END                  (XC_OMMX_ODU10XC_ODU0_4_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_5_START                (XC_OMMX_ODU10XC_ODU0_4_END+1)
#define XC_OMMX_ODU10XC_ODU0_5_END                  (XC_OMMX_ODU10XC_ODU0_5_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_6_START                (XC_OMMX_ODU10XC_ODU0_5_END+1)
#define XC_OMMX_ODU10XC_ODU0_6_END                  (XC_OMMX_ODU10XC_ODU0_6_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_7_START                (XC_OMMX_ODU10XC_ODU0_6_END+1)
#define XC_OMMX_ODU10XC_ODU0_7_END                  (XC_OMMX_ODU10XC_ODU0_7_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_8_START                (XC_OMMX_ODU10XC_ODU0_7_END+1)
#define XC_OMMX_ODU10XC_ODU0_8_END                  (XC_OMMX_ODU10XC_ODU0_8_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_9_START                (XC_OMMX_ODU10XC_ODU0_8_END+1)
#define XC_OMMX_ODU10XC_ODU0_9_END                  (XC_OMMX_ODU10XC_ODU0_9_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_10_START               (XC_OMMX_ODU10XC_ODU0_9_END+1)
#define XC_OMMX_ODU10XC_ODU0_10_END                 (XC_OMMX_ODU10XC_ODU0_10_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_11_START               (XC_OMMX_ODU10XC_ODU0_10_END+1)
#define XC_OMMX_ODU10XC_ODU0_11_END                 (XC_OMMX_ODU10XC_ODU0_11_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_12_START               (XC_OMMX_ODU10XC_ODU0_11_END+1)
#define XC_OMMX_ODU10XC_ODU0_12_END                 (XC_OMMX_ODU10XC_ODU0_12_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_13_START               (XC_OMMX_ODU10XC_ODU0_12_END+1)
#define XC_OMMX_ODU10XC_ODU0_13_END                 (XC_OMMX_ODU10XC_ODU0_13_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_14_START               (XC_OMMX_ODU10XC_ODU0_13_END+1)
#define XC_OMMX_ODU10XC_ODU0_14_END                 (XC_OMMX_ODU10XC_ODU0_14_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_15_START               (XC_OMMX_ODU10XC_ODU0_14_END+1)
#define XC_OMMX_ODU10XC_ODU0_15_END                 (XC_OMMX_ODU10XC_ODU0_15_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_16_START               (XC_OMMX_ODU10XC_ODU0_15_END+1)
#define XC_OMMX_ODU10XC_ODU0_16_END                 (XC_OMMX_ODU10XC_ODU0_16_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_17_START               (XC_OMMX_ODU10XC_ODU0_16_END+1)
#define XC_OMMX_ODU10XC_ODU0_17_END                 (XC_OMMX_ODU10XC_ODU0_17_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_18_START               (XC_OMMX_ODU10XC_ODU0_17_END+1)
#define XC_OMMX_ODU10XC_ODU0_18_END                 (XC_OMMX_ODU10XC_ODU0_18_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_19_START               (XC_OMMX_ODU10XC_ODU0_18_END+1)
#define XC_OMMX_ODU10XC_ODU0_19_END                 (XC_OMMX_ODU10XC_ODU0_19_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_20_START               (XC_OMMX_ODU10XC_ODU0_19_END+1)
#define XC_OMMX_ODU10XC_ODU0_20_END                 (XC_OMMX_ODU10XC_ODU0_20_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_21_START               (XC_OMMX_ODU10XC_ODU0_20_END+1)
#define XC_OMMX_ODU10XC_ODU0_21_END                 (XC_OMMX_ODU10XC_ODU0_21_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_22_START               (XC_OMMX_ODU10XC_ODU0_21_END+1)
#define XC_OMMX_ODU10XC_ODU0_22_END                 (XC_OMMX_ODU10XC_ODU0_22_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_23_START               (XC_OMMX_ODU10XC_ODU0_22_END+1)
#define XC_OMMX_ODU10XC_ODU0_23_END                 (XC_OMMX_ODU10XC_ODU0_23_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_24_START               (XC_OMMX_ODU10XC_ODU0_23_END+1)
#define XC_OMMX_ODU10XC_ODU0_24_END                 (XC_OMMX_ODU10XC_ODU0_24_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_25_START               (XC_OMMX_ODU10XC_ODU0_24_END+1)
#define XC_OMMX_ODU10XC_ODU0_25_END                 (XC_OMMX_ODU10XC_ODU0_25_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_26_START               (XC_OMMX_ODU10XC_ODU0_25_END+1)
#define XC_OMMX_ODU10XC_ODU0_26_END                 (XC_OMMX_ODU10XC_ODU0_26_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_27_START               (XC_OMMX_ODU10XC_ODU0_26_END+1)
#define XC_OMMX_ODU10XC_ODU0_27_END                 (XC_OMMX_ODU10XC_ODU0_27_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_28_START               (XC_OMMX_ODU10XC_ODU0_27_END+1)
#define XC_OMMX_ODU10XC_ODU0_28_END                 (XC_OMMX_ODU10XC_ODU0_28_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_29_START               (XC_OMMX_ODU10XC_ODU0_28_END+1)
#define XC_OMMX_ODU10XC_ODU0_29_END                 (XC_OMMX_ODU10XC_ODU0_29_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_30_START               (XC_OMMX_ODU10XC_ODU0_29_END+1)
#define XC_OMMX_ODU10XC_ODU0_30_END                 (XC_OMMX_ODU10XC_ODU0_30_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)
#define XC_OMMX_ODU10XC_ODU0_31_START               (XC_OMMX_ODU10XC_ODU0_30_END+1)
#define XC_OMMX_ODU10XC_ODU0_31_END                 (XC_OMMX_ODU10XC_ODU0_31_START + XC_MAX_XC_OMMX_ODU10XC_ODU0-1)


// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as OMMX facility identifiers ***
const int OMMXConfigMap[] = {0,

        // ODUXC
        XC_OMMX_ODUXC_ODUK_0_START,
        XC_OMMX_ODUXC_ODUK_0_VIRTUAL_START,
        XC_OMMX_ODUXC_ODUK_1_START,
        XC_OMMX_ODUXC_ODUK_1_VIRTUAL_START,
        XC_OMMX_ODUXC_ODUK_2_START,
        XC_OMMX_ODUXC_ODUK_2_VIRTUAL_START,
        XC_OMMX_ODUXC_ODUK_3_START,
        XC_OMMX_ODUXC_ODUK_3_VIRTUAL_START,
        XC_OMMX_ODUXC_ODU1_START,
        XC_OMMX_ODUXC_ODU1_VIRTUAL_START,
        XC_OMMX_ODUXC_ODU2_START,
        XC_OMMX_ODUXC_ODU2_VIRTUAL_START,
        XC_OMMX_ODUXC_ODUKPP_ODUK0_START,
        XC_OMMX_ODUXC_ODUKPP_ODUK0_VIRTUAL_START,
        XC_OMMX_ODUXC_ODUKPP_ODUK1_START,
        XC_OMMX_ODUXC_ODUKPP_ODUK1_VIRTUAL_START,
        XC_OMMX_ODUXC_ODUKPP_ODU1_START,
        XC_OMMX_ODUXC_ODUKPP_ODU1_VIRTUAL_START,
        XC_OMMX_ODUXC_ODUKPP_ODU2_START,
        XC_OMMX_ODUXC_ODUKPP_ODU2_VIRTUAL_START,

        // FRMODUXC
        XC_OMMX_FRMODUXC_FRM_OTUK_START,
        XC_OMMX_FRMODUXC_FRM_OTU1_START,
        XC_OMMX_FRMODUXC_FRM_OTU2_START,
        XC_OMMX_FRMODUXC_FRM_CBR_START,
        XC_OMMX_FRMODUXC_FRM_CBR10G_START,
        XC_OMMX_FRMODUXC_FRM_GE_START,
        XC_OMMX_FRMODUXC_FRM_GE10G_START,
        XC_OMMX_FRMODUXC_ODU_OTUK_START,
        XC_OMMX_FRMODUXC_ODU_OTU1_START,
        XC_OMMX_FRMODUXC_ODU_OTU2_START,
        XC_OMMX_FRMODUXC_ODU_VCAT0_ODU2_START,
        XC_OMMX_FRMODUXC_ODU_VCAT0_ODU1_START,
        XC_OMMX_FRMODUXC_ODU_VCAT0_ODUK_START,
        XC_OMMX_FRMODUXC_ODU_VCAT1_ODU2_START,
        XC_OMMX_FRMODUXC_ODU_VCAT1_ODU1_START,
        XC_OMMX_FRMODUXC_ODU_VCAT1_ODUK_START,

        // ODU21 MUX
        XC_OMMX_ODU21XC_ODU2_0_START,
        XC_OMMX_ODU21XC_ODU2_1_START,
        
        XC_OMMX_ODU21XC_ODU1_0_START,
        XC_OMMX_ODU21XC_ODU1_1_START,
        XC_OMMX_ODU21XC_ODU1_2_START,
        XC_OMMX_ODU21XC_ODU1_3_START,
        XC_OMMX_ODU21XC_ODU1_4_START,
        XC_OMMX_ODU21XC_ODU1_5_START,
        XC_OMMX_ODU21XC_ODU1_6_START,
        XC_OMMX_ODU21XC_ODU1_7_START,
        XC_OMMX_ODU21XC_ODU1_8_START,
        XC_OMMX_ODU21XC_ODU1_9_START,
        XC_OMMX_ODU21XC_ODU1_10_START,
        XC_OMMX_ODU21XC_ODU1_11_START,
        XC_OMMX_ODU21XC_ODU1_12_START,
        XC_OMMX_ODU21XC_ODU1_13_START,
        XC_OMMX_ODU21XC_ODU1_14_START,
        XC_OMMX_ODU21XC_ODU1_15_START,
        
        // ODU20 MUX
        XC_OMMX_ODU20XC_ODU2_0_START,
        XC_OMMX_ODU20XC_ODU2_1_START,
        
        XC_OMMX_ODU20XC_ODU0_0_START,
        XC_OMMX_ODU20XC_ODU0_1_START,
        XC_OMMX_ODU20XC_ODU0_2_START,
        XC_OMMX_ODU20XC_ODU0_3_START,
        XC_OMMX_ODU20XC_ODU0_4_START,
        XC_OMMX_ODU20XC_ODU0_5_START,
        XC_OMMX_ODU20XC_ODU0_6_START,
        XC_OMMX_ODU20XC_ODU0_7_START,
        XC_OMMX_ODU20XC_ODU0_8_START,
        XC_OMMX_ODU20XC_ODU0_9_START,
        XC_OMMX_ODU20XC_ODU0_10_START,
        XC_OMMX_ODU20XC_ODU0_11_START,
        XC_OMMX_ODU20XC_ODU0_12_START,
        XC_OMMX_ODU20XC_ODU0_13_START,
        XC_OMMX_ODU20XC_ODU0_14_START,
        XC_OMMX_ODU20XC_ODU0_15_START,
        XC_OMMX_ODU20XC_ODU0_16_START,
        XC_OMMX_ODU20XC_ODU0_17_START,
        XC_OMMX_ODU20XC_ODU0_18_START,
        XC_OMMX_ODU20XC_ODU0_19_START,
        XC_OMMX_ODU20XC_ODU0_20_START,
        XC_OMMX_ODU20XC_ODU0_21_START,
        XC_OMMX_ODU20XC_ODU0_22_START,
        XC_OMMX_ODU20XC_ODU0_23_START,
        XC_OMMX_ODU20XC_ODU0_24_START,
        XC_OMMX_ODU20XC_ODU0_25_START,
        XC_OMMX_ODU20XC_ODU0_26_START,
        XC_OMMX_ODU20XC_ODU0_27_START,
        XC_OMMX_ODU20XC_ODU0_28_START,
        XC_OMMX_ODU20XC_ODU0_29_START,
        XC_OMMX_ODU20XC_ODU0_30_START,
        XC_OMMX_ODU20XC_ODU0_31_START,
        
        // ODU2F MUX
        XC_OMMX_ODU2FXC_ODU2_0_START,
        XC_OMMX_ODU2FXC_ODU2_1_START,
        
        XC_OMMX_ODU2FXC_ODUF_0_START,
        XC_OMMX_ODU2FXC_ODUF_1_START,
        XC_OMMX_ODU2FXC_ODUF_2_START,
        XC_OMMX_ODU2FXC_ODUF_3_START,
        XC_OMMX_ODU2FXC_ODUF_4_START,
        XC_OMMX_ODU2FXC_ODUF_5_START,
        XC_OMMX_ODU2FXC_ODUF_6_START,
        XC_OMMX_ODU2FXC_ODUF_7_START,
        XC_OMMX_ODU2FXC_ODUF_8_START,
        XC_OMMX_ODU2FXC_ODUF_9_START,
        XC_OMMX_ODU2FXC_ODUF_10_START,
        XC_OMMX_ODU2FXC_ODUF_11_START,
        XC_OMMX_ODU2FXC_ODUF_12_START,
        XC_OMMX_ODU2FXC_ODUF_13_START,
        XC_OMMX_ODU2FXC_ODUF_14_START,
        XC_OMMX_ODU2FXC_ODUF_15_START,
        XC_OMMX_ODU2FXC_ODUF_16_START,
        XC_OMMX_ODU2FXC_ODUF_17_START,
        XC_OMMX_ODU2FXC_ODUF_18_START,
        XC_OMMX_ODU2FXC_ODUF_19_START,
        XC_OMMX_ODU2FXC_ODUF_20_START,
        XC_OMMX_ODU2FXC_ODUF_21_START,
        XC_OMMX_ODU2FXC_ODUF_22_START,
        XC_OMMX_ODU2FXC_ODUF_23_START,
        XC_OMMX_ODU2FXC_ODUF_24_START,
        XC_OMMX_ODU2FXC_ODUF_25_START,
        XC_OMMX_ODU2FXC_ODUF_26_START,
        XC_OMMX_ODU2FXC_ODUF_27_START,
        XC_OMMX_ODU2FXC_ODUF_28_START,
        XC_OMMX_ODU2FXC_ODUF_29_START,
        XC_OMMX_ODU2FXC_ODUF_30_START,
        XC_OMMX_ODU2FXC_ODUF_31_START,
        
        // ODU10 MUX
        XC_OMMX_ODU10XC_ODU1_0_START,
        XC_OMMX_ODU10XC_ODU1_1_START,
        XC_OMMX_ODU10XC_ODU1_2_START,
        XC_OMMX_ODU10XC_ODU1_3_START,
        XC_OMMX_ODU10XC_ODU1_4_START,
        XC_OMMX_ODU10XC_ODU1_5_START,
        XC_OMMX_ODU10XC_ODU1_6_START,
        XC_OMMX_ODU10XC_ODU1_7_START,
        XC_OMMX_ODU10XC_ODU1_8_START,
        XC_OMMX_ODU10XC_ODU1_9_START,
        XC_OMMX_ODU10XC_ODU1_10_START,
        XC_OMMX_ODU10XC_ODU1_11_START,
        XC_OMMX_ODU10XC_ODU1_12_START,
        XC_OMMX_ODU10XC_ODU1_13_START,
        XC_OMMX_ODU10XC_ODU1_14_START,
        XC_OMMX_ODU10XC_ODU1_15_START,
        
        XC_OMMX_ODU10XC_ODU0_0_START,
        XC_OMMX_ODU10XC_ODU0_1_START,
        XC_OMMX_ODU10XC_ODU0_2_START,
        XC_OMMX_ODU10XC_ODU0_3_START,
        XC_OMMX_ODU10XC_ODU0_4_START,
        XC_OMMX_ODU10XC_ODU0_5_START,
        XC_OMMX_ODU10XC_ODU0_6_START,
        XC_OMMX_ODU10XC_ODU0_7_START,
        XC_OMMX_ODU10XC_ODU0_8_START,
        XC_OMMX_ODU10XC_ODU0_9_START,
        XC_OMMX_ODU10XC_ODU0_10_START,
        XC_OMMX_ODU10XC_ODU0_11_START,
        XC_OMMX_ODU10XC_ODU0_12_START,
        XC_OMMX_ODU10XC_ODU0_13_START,
        XC_OMMX_ODU10XC_ODU0_14_START,
        XC_OMMX_ODU10XC_ODU0_15_START,
        XC_OMMX_ODU10XC_ODU0_16_START,
        XC_OMMX_ODU10XC_ODU0_17_START,
        XC_OMMX_ODU10XC_ODU0_18_START,
        XC_OMMX_ODU10XC_ODU0_19_START,
        XC_OMMX_ODU10XC_ODU0_20_START,
        XC_OMMX_ODU10XC_ODU0_21_START,
        XC_OMMX_ODU10XC_ODU0_22_START,
        XC_OMMX_ODU10XC_ODU0_23_START,
        XC_OMMX_ODU10XC_ODU0_24_START,
        XC_OMMX_ODU10XC_ODU0_25_START,
        XC_OMMX_ODU10XC_ODU0_26_START,
        XC_OMMX_ODU10XC_ODU0_27_START,
        XC_OMMX_ODU10XC_ODU0_28_START,
        XC_OMMX_ODU10XC_ODU0_29_START,
        XC_OMMX_ODU10XC_ODU0_30_START,
        XC_OMMX_ODU10XC_ODU0_31_START
    };



// -----------------------------------------------------------------------------------------------
// *************************  OSM Definitions *********************
//

//
// Identifiers for each OSM facility
//

// ODU XC Facilities:  ODU <--> ODU
// DIGI120 chip 0
#define XC_OSM_ODUXC_ODUK_DIGI0_FACILITY_ID           (1)    // Used/Capability 80/96
#define XC_OSM_ODUXC_ODU1_DIGI0_FACILITY_ID           (2)    // 40/48
#define XC_OSM_ODUXC_ODU2_DIGI0_FACILITY_ID           (3)    // 10/12
#define XC_OSM_ODUXC_ODU3_DIGI0_FACILITY_ID           (4)    // 2/3
#define XC_OSM_ODUXC_ODU4_DIGI0_FACILITY_ID           (5)    // 1/1
#define XC_OSM_ODUXC_CLIENT_DIGI0_FACILITY_ID         (6)    // 10/12

#define XC_OSM_ODUXC_IMUX_DIGI0_FACILITY_ID           (7)   // 80/96

// DIGI120 chip 1
#define XC_OSM_ODUXC_ODUK_DIGI1_FACILITY_ID           (8)    // 80/96
#define XC_OSM_ODUXC_ODU1_DIGI1_FACILITY_ID           (9)    // 40/48
#define XC_OSM_ODUXC_ODU2_DIGI1_FACILITY_ID           (10)    // 10/12
#define XC_OSM_ODUXC_ODU3_DIGI1_FACILITY_ID           (11)   // 2/3
#define XC_OSM_ODUXC_ODU4_DIGI1_FACILITY_ID           (12)   // 1/1
#define XC_OSM_ODUXC_CLIENT_DIGI1_FACILITY_ID         (13)   // 10/12

#define XC_OSM_ODUXC_IMUX_DIGI1_FACILITY_ID           (14)   // 80/96


// ODU MUX Facilities
#define XC_OSM_ODUMUX_ODU4_0_FACILITY_ID              (39)
#define XC_OSM_ODUMUX_ODU4_1_FACILITY_ID              (40)

#define XC_OSM_ODUMUX_ODU3_0_FACILITY_ID              (41)
#define XC_OSM_ODUMUX_ODU3_2_FACILITY_ID              (43)
#define XC_OSM_ODUMUX_ODU3_3_FACILITY_ID              (44)

#define XC_OSM_ODUMUX_ODU2_0_FACILITY_ID              (45)
#define XC_OSM_ODUMUX_ODU2_10_FACILITY_ID             (55)
#define XC_OSM_ODUMUX_ODU2_19_FACILITY_ID             (64)

#define XC_OSM_ODUMUX_ODU2E_0_FACILITY_ID             (65)
#define XC_OSM_ODUMUX_ODU2E_10_FACILITY_ID            (75)
#define XC_OSM_ODUMUX_ODU2E_19_FACILITY_ID            (84)

#define XC_OSM_ODUMUX_ODU1_0_FACILITY_ID              (85)
#define XC_OSM_ODUMUX_ODU1_40_FACILITY_ID             (125)
#define XC_OSM_ODUMUX_ODU1_79_FACILITY_ID             (164)

#define XC_OSM_ODUMUX_ODU0_0_FACILITY_ID              (165)
#define XC_OSM_ODUMUX_ODU0_80_FACILITY_ID             (245)
#define XC_OSM_ODUMUX_ODU0_159_FACILITY_ID            (324)

#define XC_OSM_ODUMUX_ODUF_0_FACILITY_ID              (325)
#define XC_OSM_ODUMUX_ODUF_80_FACILITY_ID             (405)
#define XC_OSM_ODUMUX_ODUF_159_FACILITY_ID            (484)


// The Maximum number of each OSM interface type
#define XC_MAX_OSM_ODUXC_ODUK_INTF                    (2)
#define XC_MAX_OSM_ODUXC_ODU1_INTF                    (2)
#define XC_MAX_OSM_ODUXC_ODU2_INTF                    (2)
#define XC_MAX_OSM_ODUXC_ODU3_INTF                    (2)
#define XC_MAX_OSM_ODUXC_ODU4_INTF                    (2)
#define XC_MAX_OSM_ODUXC_CLIENT_INTF                  (2)
#define XC_MAX_OSM_ODUXC_IMUX_INTF                    (2)

// The Maximum number of connections allowed on each OSM interface type
#define XC_MAX_XC_OSM_ODUXC_ODUK                      (80)
#define XC_MAX_XC_OSM_ODUXC_ODU1                      (40)
#define XC_MAX_XC_OSM_ODUXC_ODU2                      (10)
#define XC_MAX_XC_OSM_ODUXC_ODU3                      (2)
#define XC_MAX_XC_OSM_ODUXC_ODU4                      (1)
#define XC_MAX_XC_OSM_ODUXC_CLIENT                    (10)
#define XC_MAX_XC_OSM_ODUXC_IMUX                      (80)

#define XC_MAX_XC_OSM_MUX_ODU4                        (2)
#define XC_MAX_XC_OSM_MUX_ODU3                        (4)
#define XC_MAX_XC_OSM_MUX_ODU2                        (20)
#define XC_MAX_XC_OSM_MUX_ODU1                        (80)
#define XC_MAX_XC_OSM_MUX_ODU0                        (160)
#define XC_MAX_XC_OSM_MUX_ODUF                        (160)


// The maximum number of connections on OSM
#define XC_MAX_ODUXC_OSM (\
    (XC_MAX_OSM_ODUXC_ODUK_INTF   * XC_MAX_XC_OSM_ODUXC_ODUK)   +\
    (XC_MAX_OSM_ODUXC_ODU1_INTF   * XC_MAX_XC_OSM_ODUXC_ODU1)   +\
    (XC_MAX_OSM_ODUXC_ODU2_INTF   * XC_MAX_XC_OSM_ODUXC_ODU2)   +\
    (XC_MAX_OSM_ODUXC_ODU3_INTF   * XC_MAX_XC_OSM_ODUXC_ODU3)   +\
    (XC_MAX_OSM_ODUXC_ODU4_INTF   * XC_MAX_XC_OSM_ODUXC_ODU4)   +\
    (XC_MAX_OSM_ODUXC_CLIENT_INTF * XC_MAX_XC_OSM_ODUXC_CLIENT) +\
    (XC_MAX_OSM_ODUXC_IMUX_INTF   * XC_MAX_XC_OSM_ODUXC_IMUX)   )

#define XC_MAX_OSM_FIXED_MCASTID (\
    (XC_MAX_OSM_ODUXC_IMUX_INTF   * XC_MAX_XC_OSM_ODUXC_IMUX)   )

#define XC_MAX_OSM_XC_IM_ALL (\
    (XC_MAX_OSM_ODUXC_IMUX_INTF   * XC_MAX_XC_OSM_ODUXC_IMUX)   )


// 
// Breakdown of OSM XC CFG Region
//
#define XC_OSM_ODUXC_ODUK_DIGI0_START      (0)
#define XC_OSM_ODUXC_ODUK_DIGI0_END        (XC_OSM_ODUXC_ODUK_DIGI0_START + XC_MAX_XC_OSM_ODUXC_ODUK - 1)
#define XC_OSM_ODUXC_ODU1_DIGI0_START      (XC_OSM_ODUXC_ODUK_DIGI0_END + 1)
#define XC_OSM_ODUXC_ODU1_DIGI0_END        (XC_OSM_ODUXC_ODU1_DIGI0_START + XC_MAX_XC_OSM_ODUXC_ODU1 - 1)
#define XC_OSM_ODUXC_ODU2_DIGI0_START      (XC_OSM_ODUXC_ODU1_DIGI0_END + 1)
#define XC_OSM_ODUXC_ODU2_DIGI0_END        (XC_OSM_ODUXC_ODU2_DIGI0_START + XC_MAX_XC_OSM_ODUXC_ODU2 - 1)
#define XC_OSM_ODUXC_ODU3_DIGI0_START      (XC_OSM_ODUXC_ODU2_DIGI0_END + 1)
#define XC_OSM_ODUXC_ODU3_DIGI0_END        (XC_OSM_ODUXC_ODU3_DIGI0_START + XC_MAX_XC_OSM_ODUXC_ODU3 - 1)
#define XC_OSM_ODUXC_ODU4_DIGI0_START      (XC_OSM_ODUXC_ODU3_DIGI0_END + 1)
#define XC_OSM_ODUXC_ODU4_DIGI0_END        (XC_OSM_ODUXC_ODU4_DIGI0_START + XC_MAX_XC_OSM_ODUXC_ODU4 - 1)
#define XC_OSM_ODUXC_CLIENT_DIGI0_START    (XC_OSM_ODUXC_ODU4_DIGI0_END + 1)
#define XC_OSM_ODUXC_CLIENT_DIGI0_END      (XC_OSM_ODUXC_CLIENT_DIGI0_START + XC_MAX_XC_OSM_ODUXC_CLIENT - 1)
#define XC_OSM_ODUXC_IMUX_DIGI0_START      (XC_OSM_ODUXC_CLIENT_DIGI0_END + 1)
#define XC_OSM_ODUXC_IMUX_DIGI0_END        (XC_OSM_ODUXC_IMUX_DIGI0_START + XC_MAX_XC_OSM_ODUXC_IMUX - 1)
#define XC_OSM_ODUXC_ODUK_DIGI1_START      (XC_OSM_ODUXC_IMUX_DIGI0_END + 1)
#define XC_OSM_ODUXC_ODUK_DIGI1_END        (XC_OSM_ODUXC_ODUK_DIGI1_START + XC_MAX_XC_OSM_ODUXC_ODUK - 1)
#define XC_OSM_ODUXC_ODU1_DIGI1_START      (XC_OSM_ODUXC_ODUK_DIGI1_END + 1)
#define XC_OSM_ODUXC_ODU1_DIGI1_END        (XC_OSM_ODUXC_ODU1_DIGI1_START + XC_MAX_XC_OSM_ODUXC_ODU1 - 1)
#define XC_OSM_ODUXC_ODU2_DIGI1_START      (XC_OSM_ODUXC_ODU1_DIGI1_END + 1)
#define XC_OSM_ODUXC_ODU2_DIGI1_END        (XC_OSM_ODUXC_ODU2_DIGI1_START + XC_MAX_XC_OSM_ODUXC_ODU2 - 1)
#define XC_OSM_ODUXC_ODU3_DIGI1_START      (XC_OSM_ODUXC_ODU2_DIGI1_END + 1)
#define XC_OSM_ODUXC_ODU3_DIGI1_END        (XC_OSM_ODUXC_ODU3_DIGI1_START + XC_MAX_XC_OSM_ODUXC_ODU3 - 1)
#define XC_OSM_ODUXC_ODU4_DIGI1_START      (XC_OSM_ODUXC_ODU3_DIGI1_END + 1)
#define XC_OSM_ODUXC_ODU4_DIGI1_END        (XC_OSM_ODUXC_ODU4_DIGI1_START + XC_MAX_XC_OSM_ODUXC_ODU4 - 1)
#define XC_OSM_ODUXC_CLIENT_DIGI1_START    (XC_OSM_ODUXC_ODU4_DIGI1_END + 1)
#define XC_OSM_ODUXC_CLIENT_DIGI1_END      (XC_OSM_ODUXC_CLIENT_DIGI1_START + XC_MAX_XC_OSM_ODUXC_CLIENT - 1)
#define XC_OSM_ODUXC_IMUX_DIGI1_START      (XC_OSM_ODUXC_CLIENT_DIGI1_END + 1)
#define XC_OSM_ODUXC_IMUX_DIGI1_END        (XC_OSM_ODUXC_IMUX_DIGI1_START + XC_MAX_XC_OSM_ODUXC_IMUX - 1)


// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as OSM facility identifiers ***
const int OSMOduXcConfigMap[] = {0,
        // digi120 chip 0
        XC_OSM_ODUXC_ODUK_DIGI0_START,
        XC_OSM_ODUXC_ODU1_DIGI0_START,
        XC_OSM_ODUXC_ODU2_DIGI0_START,
        XC_OSM_ODUXC_ODU3_DIGI0_START,
        XC_OSM_ODUXC_ODU4_DIGI0_START,
        XC_OSM_ODUXC_CLIENT_DIGI0_START,
        XC_OSM_ODUXC_IMUX_DIGI0_START,
        // digi120 chip 1
        XC_OSM_ODUXC_ODUK_DIGI1_START,
        XC_OSM_ODUXC_ODU1_DIGI1_START,
        XC_OSM_ODUXC_ODU2_DIGI1_START,
        XC_OSM_ODUXC_ODU3_DIGI1_START,
        XC_OSM_ODUXC_ODU4_DIGI1_START,
        XC_OSM_ODUXC_CLIENT_DIGI1_START,
        XC_OSM_ODUXC_IMUX_DIGI1_START
    };


#define XC_OSM_MUX_MAX_SIZE (240)  // max scene is ODU4 <-80-> ODU1 <-160-> ODU0



// -----------------------------------------------------------------------------------------------
// *************************  OSM1S Definitions *********************
//

//
// Identifiers for each OSM1S facility
//

// HyPHYflex chip 0
#define XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_FACILITY_ID             (1)    // 8 * ODU0/F CRS
#define XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_FACILITY_ID             (2)    // 8 * ODU0/F CRS
#define XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_FACILITY_ID              (3)    // 8 * ODU1 CRS
#define XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_FACILITY_ID      (4)    // 8 * ODU0/F CBR CRS
#define XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_FACILITY_ID      (5)    // 8 * ODU0/F CBR CRS
#define XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_FACILITY_ID       (6)    // 8 * ODU1 CBR CRS

#define XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_FACILITY_ID              (7)    // 16 * CRS(MAX for 20G)

// HyPHYflex chip 1
#define XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_FACILITY_ID             (8)    // 8 * ODU0/F CRS
#define XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_FACILITY_ID             (9)    // 8 * ODU0/F CRS
#define XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_FACILITY_ID              (10)   // 8 * ODU1 CRS
#define XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_FACILITY_ID      (11)   // 8 * ODU0/F CBR CRS
#define XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_FACILITY_ID      (12)   // 8 * ODU0/F CBR CRS
#define XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_FACILITY_ID       (13)   // 8 * ODU1 CBR CRS

#define XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_FACILITY_ID              (14)   // 16 * CRS(MAX for 20G)


// FRM XC Facilities:  FRM <--> ODU
// HyPHYflex chip 0
#define XC_OSM1S_FRMXC_FRM_ODUK_HYPHYFLEX0_FACILITY_ID          (15)   // 16 * ODU0/F Frame CRS(max 32 CRS)
#define XC_OSM1S_FRMXC_FRM_ODU1_HYPHYFLEX0_FACILITY_ID          (16)   // 8 * ODU1 Frame CRS
#define XC_OSM1S_FRMXC_FRM_CBR_HYPHYFLEX0_FACILITY_ID           (17)   // 8 * OC48/STM16 CRS or 16 * OC3/OC12/STM4/STM16 CRS
#define XC_OSM1S_FRMXC_FRM_GE_HYPHYFLEX0_FACILITY_ID            (18)   // 16 * GE CRS

#define XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_FACILITY_ID          (19)   // 16 * ODU0/F Frame CRS(max 32 CRS)
#define XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_FACILITY_ID          (20)   // 8 * ODU1 Frame CRS
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_FACILITY_ID    (21)   // 8 * OC3/OC12/STM4/STM16/GE CRS
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_FACILITY_ID    (22)   // 4 * OC48/STM16 CRS
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_FACILITY_ID    (23)   // 8 * OC3/OC12/STM4/STM16/GE CRS
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_FACILITY_ID    (24)   // 4 * OC48/STM16 CRS

// HyPHYflex chip 1
#define XC_OSM1S_FRMXC_FRM_ODUK_HYPHYFLEX1_FACILITY_ID          (25)   // 16 * ODU0/F Frame CRS(max 32 CRS)
#define XC_OSM1S_FRMXC_FRM_ODU1_HYPHYFLEX1_FACILITY_ID          (26)   // 8 * ODU1 Frame CRS
#define XC_OSM1S_FRMXC_FRM_CBR_HYPHYFLEX1_FACILITY_ID           (27)   // 8 * OC48/STM16 CRS or 16 * OC3/OC12/STM4/STM16 CRS
#define XC_OSM1S_FRMXC_FRM_GE_HYPHYFLEX1_FACILITY_ID            (28)   // 16 * GE CRS

#define XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_FACILITY_ID          (29)   // 16 * ODU0/F Frame CRS(max 32 CRS)
#define XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_FACILITY_ID          (30)   // 8 * ODU1 Frame CRS
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_FACILITY_ID    (31)   // 8 * OC3/OC12/STM4/STM16/GE CRS
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_FACILITY_ID    (32)   // 4 * OC48/STM16 CRS
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_FACILITY_ID    (33)   // 8 * OC3/OC12/STM4/STM16/GE CRS
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_FACILITY_ID    (34)   // 4 * OC48/STM16 CRS


// ODU MUX Facilities
#define XC_OSM1S_ODUMUX_ODU1_0_FACILITY_ID                      (35)
#define XC_OSM1S_ODUMUX_ODU1_8_FACILITY_ID                      (43)
#define XC_OSM1S_ODUMUX_ODU1_15_FACILITY_ID                     (50)

#define XC_OSM1S_ODUMUX_ODUK_0_FACILITY_ID                      (51)
#define XC_OSM1S_ODUMUX_ODUK_8_FACILITY_ID                      (59)
#define XC_OSM1S_ODUMUX_ODUK_16_FACILITY_ID                     (67)
#define XC_OSM1S_ODUMUX_ODUK_24_FACILITY_ID                     (75)
#define XC_OSM1S_ODUMUX_ODUK_31_FACILITY_ID                     (82)


// The Maximum number of each OSM1S interface type
#define XC_MAX_OSM1S_ODUXC_ODUK_INTF                            (4)
#define XC_MAX_OSM1S_ODUXC_ODU1_INTF                            (2)
#define XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK_INTF                     (4)
#define XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1_INTF                     (2)
#define XC_MAX_OSM1S_ODUXC_IMUX_INTF                            (2)

#define XC_MAX_OSM1S_FRMXC_FRM_ODUK_INTF                        (2)
#define XC_MAX_OSM1S_FRMXC_FRM_ODU1_INTF                        (2)
#define XC_MAX_OSM1S_FRMXC_FRM_CBR_INTF                         (2)
#define XC_MAX_OSM1S_FRMXC_FRM_GE_INTF                          (2)
#define XC_MAX_OSM1S_FRMXC_ODU_ODUK_INTF                        (2)
#define XC_MAX_OSM1S_FRMXC_ODU_ODU1_INTF                        (2)
#define XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK_INTF                   (4)
#define XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1_INTF                   (4)


// The Maximum number of connections allowed on each OSM1S interface type
#define XC_MAX_OSM1S_ODUXC_ODUK                                 (8)
#define XC_MAX_OSM1S_ODUXC_ODU1                                 (8)
#define XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK                          (8)
#define XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1                          (8)
#define XC_MAX_OSM1S_ODUXC_IMUX                                 (16)

#define XC_MAX_OSM1S_FRMXC_FRM_ODUK                             (16)
#define XC_MAX_OSM1S_FRMXC_FRM_ODU1                             (8)
#define XC_MAX_OSM1S_FRMXC_FRM_CBR                              (16)
#define XC_MAX_OSM1S_FRMXC_FRM_GE                               (16)
#define XC_MAX_OSM1S_FRMXC_ODU_ODUK                             (16)
#define XC_MAX_OSM1S_FRMXC_ODU_ODU1                             (8)
#define XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK                        (8)
#define XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1                        (4)

#define XC_MAX_OSM1S_MUX_ODU1                                   (16)
#define XC_MAX_OSM1S_MUX_ODUK                                   (32)


// The maximum number of connections on OSM1S
#define XC_MAX_ODUXC_OSM1S (\
    (XC_MAX_OSM1S_ODUXC_ODUK_INTF        * XC_MAX_OSM1S_ODUXC_ODUK)        +\
    (XC_MAX_OSM1S_ODUXC_ODU1_INTF        * XC_MAX_OSM1S_ODUXC_ODU1)        +\
    (XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK_INTF * XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK) +\
    (XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1_INTF * XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1) +\
    (XC_MAX_OSM1S_ODUXC_IMUX_INTF        * XC_MAX_OSM1S_ODUXC_IMUX)        )

#define XC_MAX_OSM1S_FIXED_MCASTID (XC_MAX_OSM1S_ODUXC_IMUX_INTF * XC_MAX_OSM1S_ODUXC_IMUX)

#define XC_MAX_OSM1S_IM_ALL        (XC_MAX_OSM1S_ODUXC_IMUX_INTF * XC_MAX_OSM1S_ODUXC_IMUX)


// 
// Breakdown of OSM1S XC CFG Region
//
#define XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_START           (0)
#define XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_END             (XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_START        + XC_MAX_OSM1S_ODUXC_ODUK - 1)
#define XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_START           (XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_END          + 1)
#define XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_END             (XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_START        + XC_MAX_OSM1S_ODUXC_ODUK - 1)
#define XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_START            (XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_END          + 1)
#define XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_END              (XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_START         + XC_MAX_OSM1S_ODUXC_ODU1 - 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_START    (XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_END           + 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_END      (XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_START + XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK - 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_START    (XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_END   + 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_END      (XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_START + XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK - 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_START     (XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_END   + 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_END       (XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_START  + XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1 - 1)
#define XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_START            (XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_END    + 1)
#define XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_END              (XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_START         + XC_MAX_OSM1S_ODUXC_IMUX - 1)
#define XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_START           (XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_END           + 1)
#define XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_END             (XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_START        + XC_MAX_OSM1S_ODUXC_ODUK - 1)
#define XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_START           (XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_END          + 1)
#define XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_END             (XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_START        + XC_MAX_OSM1S_ODUXC_ODUK - 1)
#define XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_START            (XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_END          + 1)
#define XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_END              (XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_START         + XC_MAX_OSM1S_ODUXC_ODU1 - 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_START    (XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_END           + 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_END      (XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_START + XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK - 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_START    (XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_END   + 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_END      (XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_START + XC_MAX_OSM1S_ODUXC_ODUKPP_ODUK - 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_START     (XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_END   + 1)
#define XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_END       (XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_START  + XC_MAX_OSM1S_ODUXC_ODUKPP_ODU1 - 1)
#define XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_START            (XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_END    + 1)
#define XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_END              (XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_START         + XC_MAX_OSM1S_ODUXC_IMUX - 1)


// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as OSM1S facility identifiers ***
const int OSM1SOduXcConfigMap[] = {0,
    // HyPHYflex chip 0
    XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX0_START,
    XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX0_START,
    XC_OSM1S_ODUXC_ODU1_HYPHYFLEX0_START,
    XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX0_START,
    XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX0_START,
    XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX0_START,
    XC_OSM1S_ODUXC_IMUX_HYPHYFLEX0_START,
    // HyPHYflex chip 1
    XC_OSM1S_ODUXC_ODUK0_HYPHYFLEX1_START,
    XC_OSM1S_ODUXC_ODUK1_HYPHYFLEX1_START,
    XC_OSM1S_ODUXC_ODU1_HYPHYFLEX1_START,
    XC_OSM1S_ODUXC_ODUKPP_ODUK0_HYPHYFLEX1_START,
    XC_OSM1S_ODUXC_ODUKPP_ODUK1_HYPHYFLEX1_START,
    XC_OSM1S_ODUXC_ODUKPP_ODU1_HYPHYFLEX1_START,
    XC_OSM1S_ODUXC_IMUX_HYPHYFLEX1_START
    };


// 
// Breakdown of OSM1S FRM CFG Region
//
#define XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_START          (0)
#define XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_END            (XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_START       + XC_MAX_OSM1S_FRMXC_ODU_ODUK - 1)
#define XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_START          (XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX0_END         + 1)
#define XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_END            (XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_START       + XC_MAX_OSM1S_FRMXC_FRM_ODU1 - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_START    (XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX0_END         + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_END      (XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_START    (XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX0_END   + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_END      (XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1 - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_START    (XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX0_END   + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_END      (XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_START    (XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX0_END   + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_END      (XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1 - 1)
#define XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_START          (XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX0_END   + 1)
#define XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_END            (XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_START       + XC_MAX_OSM1S_FRMXC_ODU_ODUK - 1)
#define XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_START          (XC_OSM1S_FRMXC_ODU_ODUK_HYPHYFLEX1_END         + 1)
#define XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_END            (XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_START       + XC_MAX_OSM1S_FRMXC_FRM_ODU1 - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_START    (XC_OSM1S_FRMXC_ODU_ODU1_HYPHYFLEX1_END         + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_END      (XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_START    (XC_OSM1S_FRMXC_ODU_VCAT0_ODUK_HYPHYFLEX1_END   + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_END      (XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1 - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_START    (XC_OSM1S_FRMXC_ODU_VCAT0_ODU1_HYPHYFLEX1_END   + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_END      (XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODUK - 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_START    (XC_OSM1S_FRMXC_ODU_VCAT1_ODUK_HYPHYFLEX1_END   + 1)
#define XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_END      (XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_START + XC_MAX_OSM1S_FRMXC_ODU_VCAT_ODU1 - 1)

#define XC_OSM1S_FRMXC_MAX_SIZE (XC_OSM1S_FRMXC_ODU_VCAT1_ODU1_HYPHYFLEX1_END + 1)

#define XC_OSM1S_MUX_MAX_SIZE (32)  // max scene is ODU1 <-32-> ODU0



// -----------------------------------------------------------------------------------------------
// *************************  FGTMM Definitions *********************

//
// Identifiers for each FGTMM facility
//
#define XC_FGTMM_ODU2_PORT0_FACILITY_ID    (1)
#define XC_FGTMM_ODU2_PORT1_FACILITY_ID    (2)
#define XC_FGTMM_ODU2_PORT2_FACILITY_ID    (3)
#define XC_FGTMM_ODU2_PORT3_FACILITY_ID    (4)

// For ODU2 Midline Cross Connect
#define XC_FGTMM_DWDM_FACILITY_ID          (5)   

// The Maximum number of each FGTMM interface type defined

#define XC_MAX_FGTMM_ODU2_DWDM_INTF	        (1)
#define XC_MAX_FGTMM_ODU2_PORT_INTF	        (4)

// The maximum number of connections allowed on each FGTMM interface
#define XC_MAX_XC_FGTMM_ODU2_DWDM           (4)
#define XC_MAX_XC_FGTMM_ODU2_PORT           (1)

// The maximum number of connections on FGTMM 

#define XC_MAX_XC_FGTMM \
            ((XC_MAX_FGTMM_ODU2_DWDM_INTF    * XC_MAX_XC_FGTMM_ODU2_DWDM)    + \
             (XC_MAX_FGTMM_ODU2_PORT_INTF   * XC_MAX_XC_FGTMM_ODU2_PORT))

// 
// Breakdown of FGTMM XC CFG Region
//

#define XC_FGTMM_CFG_ODU2_PORT0_START   (0)
#define XC_FGTMM_CFG_ODU2_PORT0_END     (XC_FGTMM_CFG_ODU2_PORT0_START + XC_MAX_XC_FGTMM_ODU2_PORT - 1)

#define XC_FGTMM_CFG_ODU2_PORT1_START   (XC_FGTMM_CFG_ODU2_PORT0_END + 1)
#define XC_FGTMM_CFG_ODU2_PORT1_END     (XC_FGTMM_CFG_ODU2_PORT1_START + XC_MAX_XC_FGTMM_ODU2_PORT - 1)

#define XC_FGTMM_CFG_ODU2_PORT2_START   (XC_FGTMM_CFG_ODU2_PORT1_END + 1)
#define XC_FGTMM_CFG_ODU2_PORT2_END     (XC_FGTMM_CFG_ODU2_PORT2_START + XC_MAX_XC_FGTMM_ODU2_PORT - 1)

#define XC_FGTMM_CFG_ODU2_PORT3_START   (XC_FGTMM_CFG_ODU2_PORT2_END + 1)
#define XC_FGTMM_CFG_ODU2_PORT3_END     (XC_FGTMM_CFG_ODU2_PORT3_START + XC_MAX_XC_FGTMM_ODU2_PORT - 1)

#define XC_FGTMM_CFG_ODU2_DWDM_START    (XC_FGTMM_CFG_ODU2_PORT3_END + 1)
#define XC_FGTMM_CFG_ODU2_DWDM_END      (XC_FGTMM_CFG_ODU2_DWDM_START + XC_MAX_XC_FGTMM_ODU2_DWDM - 1)

// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as FGTMM facility identifiers ***
const int FGTMMConfigMap[] = {0,
                             XC_FGTMM_CFG_ODU2_PORT0_START,
                             XC_FGTMM_CFG_ODU2_PORT1_START,
                             XC_FGTMM_CFG_ODU2_PORT2_START,
                             XC_FGTMM_CFG_ODU2_PORT3_START,
                             XC_FGTMM_CFG_ODU2_DWDM_START};

// -----------------------------------------------------------------------------------------------
// *************************  HDTG Definitions *********************

//
// Identifiers for each HDTG facility
//
#define XC_HDTG_ODU2_PORT0_FACILITY_ID    (1)
#define XC_HDTG_ODU2_PORT1_FACILITY_ID    (2)
#define XC_HDTG_ODU2_PORT2_FACILITY_ID    (3)
#define XC_HDTG_ODU2_PORT3_FACILITY_ID    (4)
#define XC_HDTG_ODU2_PORT4_FACILITY_ID    (5)
#define XC_HDTG_ODU2_PORT5_FACILITY_ID    (6)
#define XC_HDTG_ODU2_PORT6_FACILITY_ID    (7)
#define XC_HDTG_ODU2_PORT7_FACILITY_ID    (8)
#define XC_HDTG_ODU2_PORT8_FACILITY_ID    (9)
#define XC_HDTG_ODU2_PORT9_FACILITY_ID    (10)
#define XC_HDTG_ODU2_PORT10_FACILITY_ID    (11)
#define XC_HDTG_ODU2_PORT11_FACILITY_ID    (12)
#define XC_HDTG_ODU2_PORT12_FACILITY_ID    (13)
#define XC_HDTG_ODU2_PORT13_FACILITY_ID    (14)
#define XC_HDTG_ODU2_PORT14_FACILITY_ID    (15)

// The Maximum number of each FGTMM interface type defined

#define XC_MAX_HDTG_PORT_INTF	        (15)

// The maximum number of connections allowed on each HDTG interface
#define XC_MAX_XC_HDTG_ODU2_PORT           (1)

// The maximum number of connections on HDTG 

#define XC_MAX_XC_HDTG \
            ((XC_MAX_HDTG_PORT_INTF    * XC_MAX_XC_HDTG_ODU2_PORT))

// 
// Breakdown of HDTG XC CFG Region
//

#define XC_HDTG_CFG_ODU2_PORT0_START   (0)
#define XC_HDTG_CFG_ODU2_PORT0_END     (XC_HDTG_CFG_ODU2_PORT0_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT1_START   (XC_HDTG_CFG_ODU2_PORT0_END + 1)
#define XC_HDTG_CFG_ODU2_PORT1_END     (XC_HDTG_CFG_ODU2_PORT1_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT2_START   (XC_HDTG_CFG_ODU2_PORT1_END + 1)
#define XC_HDTG_CFG_ODU2_PORT2_END     (XC_HDTG_CFG_ODU2_PORT2_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT3_START   (XC_HDTG_CFG_ODU2_PORT2_END + 1)
#define XC_HDTG_CFG_ODU2_PORT3_END     (XC_HDTG_CFG_ODU2_PORT3_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT4_START   (XC_HDTG_CFG_ODU2_PORT3_END + 1)
#define XC_HDTG_CFG_ODU2_PORT4_END     (XC_HDTG_CFG_ODU2_PORT4_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT5_START   (XC_HDTG_CFG_ODU2_PORT4_END + 1)
#define XC_HDTG_CFG_ODU2_PORT5_END     (XC_HDTG_CFG_ODU2_PORT5_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT6_START   (XC_HDTG_CFG_ODU2_PORT5_END + 1)
#define XC_HDTG_CFG_ODU2_PORT6_END     (XC_HDTG_CFG_ODU2_PORT6_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT7_START   (XC_HDTG_CFG_ODU2_PORT6_END + 1)
#define XC_HDTG_CFG_ODU2_PORT7_END     (XC_HDTG_CFG_ODU2_PORT7_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT8_START   (XC_HDTG_CFG_ODU2_PORT7_END + 1)
#define XC_HDTG_CFG_ODU2_PORT8_END     (XC_HDTG_CFG_ODU2_PORT8_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT9_START   (XC_HDTG_CFG_ODU2_PORT8_END + 1)
#define XC_HDTG_CFG_ODU2_PORT9_END     (XC_HDTG_CFG_ODU2_PORT9_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

//11~15
#define XC_HDTG_CFG_ODU2_PORT10_START   (XC_HDTG_CFG_ODU2_PORT9_END + 1)
#define XC_HDTG_CFG_ODU2_PORT10_END     (XC_HDTG_CFG_ODU2_PORT10_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT11_START   (XC_HDTG_CFG_ODU2_PORT10_END + 1)
#define XC_HDTG_CFG_ODU2_PORT11_END     (XC_HDTG_CFG_ODU2_PORT11_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT12_START   (XC_HDTG_CFG_ODU2_PORT11_END + 1)
#define XC_HDTG_CFG_ODU2_PORT12_END     (XC_HDTG_CFG_ODU2_PORT12_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT13_START   (XC_HDTG_CFG_ODU2_PORT12_END + 1)
#define XC_HDTG_CFG_ODU2_PORT13_END     (XC_HDTG_CFG_ODU2_PORT13_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

#define XC_HDTG_CFG_ODU2_PORT14_START   (XC_HDTG_CFG_ODU2_PORT13_END + 1)
#define XC_HDTG_CFG_ODU2_PORT14_END     (XC_HDTG_CFG_ODU2_PORT14_START + XC_MAX_XC_HDTG_ODU2_PORT - 1)

// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as HDTG facility identifiers ***
const int HDTGConfigMap[] = {0,
                             XC_HDTG_CFG_ODU2_PORT0_START,
                             XC_HDTG_CFG_ODU2_PORT1_START,
                             XC_HDTG_CFG_ODU2_PORT2_START,
                             XC_HDTG_CFG_ODU2_PORT3_START,
                             XC_HDTG_CFG_ODU2_PORT4_START,
                             XC_HDTG_CFG_ODU2_PORT5_START,
                             XC_HDTG_CFG_ODU2_PORT6_START,
                             XC_HDTG_CFG_ODU2_PORT7_START,
                             XC_HDTG_CFG_ODU2_PORT8_START,
                             XC_HDTG_CFG_ODU2_PORT9_START,
                             XC_HDTG_CFG_ODU2_PORT10_START,
                             XC_HDTG_CFG_ODU2_PORT11_START,
                             XC_HDTG_CFG_ODU2_PORT12_START,
                             XC_HDTG_CFG_ODU2_PORT13_START,
                             XC_HDTG_CFG_ODU2_PORT14_START};

// -----------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------
// *************************  HDTG2 Definitions *********************

//
// Identifiers for each HDTG2 facility
//
#define XC_HDTG2_ODU2F_PORT0_FACILITY_ID     (1)
#define XC_HDTG2_ODU2F_PORT1_FACILITY_ID     (2)
#define XC_HDTG2_ODU2F_PORT2_FACILITY_ID     (3)
#define XC_HDTG2_ODU2F_PORT3_FACILITY_ID     (4)
#define XC_HDTG2_ODU2F_PORT4_FACILITY_ID     (5)
#define XC_HDTG2_ODU2F_PORT5_FACILITY_ID     (6)
#define XC_HDTG2_ODU2F_PORT6_FACILITY_ID     (7)
#define XC_HDTG2_ODU2F_PORT7_FACILITY_ID     (8)
#define XC_HDTG2_ODU2F_PORT8_FACILITY_ID     (9)
#define XC_HDTG2_ODU2F_PORT9_FACILITY_ID     (10)
#define XC_HDTG2_ODU2F_PORT10_FACILITY_ID    (11)
#define XC_HDTG2_ODU2F_PORT11_FACILITY_ID    (12)
#define XC_HDTG2_ODU2F_PORT12_FACILITY_ID    (13)
#define XC_HDTG2_ODU2F_PORT13_FACILITY_ID    (14)
#define XC_HDTG2_ODU2F_PORT14_FACILITY_ID    (15)
#define XC_HDTG2_ODU2F_PORT15_FACILITY_ID    (16)
#define XC_HDTG2_ODU2F_MUX0_FACILITY_ID      (17)
#define XC_HDTG2_ODU2F_MUX1_FACILITY_ID      (18)
#define XC_HDTG2_ODU2F_MUX2_FACILITY_ID      (19)
#define XC_HDTG2_ODU2F_MUX3_FACILITY_ID      (20)
#define XC_HDTG2_ODU2F_MUX4_FACILITY_ID      (21)
#define XC_HDTG2_ODU2F_MUX5_FACILITY_ID      (22)
#define XC_HDTG2_ODU2F_MUX6_FACILITY_ID      (23)
#define XC_HDTG2_ODU2F_MUX7_FACILITY_ID      (24)
#define XC_HDTG2_ODU2_DEMUX_ODUF_FACILITY_ID (25)

#define XC_MAX_HDTG2_PORT_INTF	             (16)

// The maximum number of connections allowed on each HDTG2 interface
#define XC_MAX_XC_HDTG2_ODU2F_PORT           (1)
// The maximum number of tribslots allowed on each HDTG2 ODU2 port
#define XC_MAX_HDTG2_ODU2_TRIBSLOTS          (8)
// The maximum number of trib port allowed on each HDTG2 ODUF facilityId
#define XC_MAX_HDTG2_ODU2_TRIBPORT_ID        (1)

// 
// Breakdown of HDTG2 XC Region
//

#define XC_HDTG2_ODU2F_PORT0_START   (0)
#define XC_HDTG2_ODU2F_PORT0_END     (XC_HDTG2_ODU2F_PORT0_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT1_START   (XC_HDTG2_ODU2F_PORT0_END + 1)
#define XC_HDTG2_ODU2F_PORT1_END     (XC_HDTG2_ODU2F_PORT1_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT2_START   (XC_HDTG2_ODU2F_PORT1_END + 1)
#define XC_HDTG2_ODU2F_PORT2_END     (XC_HDTG2_ODU2F_PORT2_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT3_START   (XC_HDTG2_ODU2F_PORT2_END + 1)
#define XC_HDTG2_ODU2F_PORT3_END     (XC_HDTG2_ODU2F_PORT3_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT4_START   (XC_HDTG2_ODU2F_PORT3_END + 1)
#define XC_HDTG2_ODU2F_PORT4_END     (XC_HDTG2_ODU2F_PORT4_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT5_START   (XC_HDTG2_ODU2F_PORT4_END + 1)
#define XC_HDTG2_ODU2F_PORT5_END     (XC_HDTG2_ODU2F_PORT5_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT6_START   (XC_HDTG2_ODU2F_PORT5_END + 1)
#define XC_HDTG2_ODU2F_PORT6_END     (XC_HDTG2_ODU2F_PORT6_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT7_START   (XC_HDTG2_ODU2F_PORT6_END + 1)
#define XC_HDTG2_ODU2F_PORT7_END     (XC_HDTG2_ODU2F_PORT7_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT8_START   (XC_HDTG2_ODU2F_PORT7_END + 1)
#define XC_HDTG2_ODU2F_PORT8_END     (XC_HDTG2_ODU2F_PORT8_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT9_START   (XC_HDTG2_ODU2F_PORT8_END + 1)
#define XC_HDTG2_ODU2F_PORT9_END     (XC_HDTG2_ODU2F_PORT9_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT10_START   (XC_HDTG2_ODU2F_PORT9_END + 1)
#define XC_HDTG2_ODU2F_PORT10_END     (XC_HDTG2_ODU2F_PORT10_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT11_START   (XC_HDTG2_ODU2F_PORT10_END + 1)
#define XC_HDTG2_ODU2F_PORT11_END     (XC_HDTG2_ODU2F_PORT11_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT12_START   (XC_HDTG2_ODU2F_PORT11_END + 1)
#define XC_HDTG2_ODU2F_PORT12_END     (XC_HDTG2_ODU2F_PORT12_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT13_START   (XC_HDTG2_ODU2F_PORT12_END + 1)
#define XC_HDTG2_ODU2F_PORT13_END     (XC_HDTG2_ODU2F_PORT13_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT14_START   (XC_HDTG2_ODU2F_PORT13_END + 1)
#define XC_HDTG2_ODU2F_PORT14_END     (XC_HDTG2_ODU2F_PORT14_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

#define XC_HDTG2_ODU2F_PORT15_START   (XC_HDTG2_ODU2F_PORT14_END + 1)
#define XC_HDTG2_ODU2F_PORT15_END     (XC_HDTG2_ODU2F_PORT15_START + XC_MAX_XC_HDTG2_ODU2F_PORT - 1)

// 
// HDTG2 MUX Region
//
#define XC_HDTG2_ODUF_MUX0_START      (XC_HDTG2_ODU2F_PORT15_END + 1)
#define XC_HDTG2_ODUF_MUX0_END        (XC_HDTG2_ODUF_MUX0_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

#define XC_HDTG2_ODUF_MUX1_START      (XC_HDTG2_ODUF_MUX0_END + 1)
#define XC_HDTG2_ODUF_MUX1_END        (XC_HDTG2_ODUF_MUX1_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

#define XC_HDTG2_ODUF_MUX2_START      (XC_HDTG2_ODUF_MUX1_END + 1)
#define XC_HDTG2_ODUF_MUX2_END        (XC_HDTG2_ODUF_MUX2_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

#define XC_HDTG2_ODUF_MUX3_START      (XC_HDTG2_ODUF_MUX2_END + 1)
#define XC_HDTG2_ODUF_MUX3_END        (XC_HDTG2_ODUF_MUX3_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

#define XC_HDTG2_ODUF_MUX4_START      (XC_HDTG2_ODUF_MUX3_END + 1)
#define XC_HDTG2_ODUF_MUX4_END        (XC_HDTG2_ODUF_MUX4_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

#define XC_HDTG2_ODUF_MUX5_START      (XC_HDTG2_ODUF_MUX4_END + 1)
#define XC_HDTG2_ODUF_MUX5_END        (XC_HDTG2_ODUF_MUX5_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

#define XC_HDTG2_ODUF_MUX6_START      (XC_HDTG2_ODUF_MUX5_END + 1)
#define XC_HDTG2_ODUF_MUX6_END        (XC_HDTG2_ODUF_MUX6_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

#define XC_HDTG2_ODUF_MUX7_START      (XC_HDTG2_ODUF_MUX6_END + 1)
#define XC_HDTG2_ODUF_MUX7_END        (XC_HDTG2_ODUF_MUX7_START + XC_MAX_HDTG2_ODU2_TRIBSLOTS - 1)

// The maximum number of connections on HDTG2
#define XC_MAX_XC_HDTG2               (XC_HDTG2_ODUF_MUX7_END + 1)

// Constant Array for use with indexing into the AG/SP Config Region. 
// SP will use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as HDTG facility identifiers ***
const int HDTG2ConfigMap[] = {0,
                             XC_HDTG2_ODU2F_PORT0_START,
                             XC_HDTG2_ODU2F_PORT1_START,
                             XC_HDTG2_ODU2F_PORT2_START,
                             XC_HDTG2_ODU2F_PORT3_START,
                             XC_HDTG2_ODU2F_PORT4_START,
                             XC_HDTG2_ODU2F_PORT5_START,
                             XC_HDTG2_ODU2F_PORT6_START,
                             XC_HDTG2_ODU2F_PORT7_START,
                             XC_HDTG2_ODU2F_PORT8_START,
                             XC_HDTG2_ODU2F_PORT9_START,
                             XC_HDTG2_ODU2F_PORT10_START,
                             XC_HDTG2_ODU2F_PORT11_START,
                             XC_HDTG2_ODU2F_PORT12_START,
                             XC_HDTG2_ODU2F_PORT13_START,
                             XC_HDTG2_ODU2F_PORT14_START,
                             XC_HDTG2_ODU2F_PORT15_START,
                             XC_HDTG2_ODUF_MUX0_START,      
                             XC_HDTG2_ODUF_MUX1_START,      
                             XC_HDTG2_ODUF_MUX2_START,      
                             XC_HDTG2_ODUF_MUX3_START,      
                             XC_HDTG2_ODUF_MUX4_START,      
                             XC_HDTG2_ODUF_MUX5_START,      
                             XC_HDTG2_ODUF_MUX6_START,      
                             XC_HDTG2_ODUF_MUX7_START,      
                             };

// -----------------------------------------------------------------------------------------------
// *************************  SMTM U Definitions *********************

//
// Maximum number of each SMTMU interface type
//
#define XC_MAX_SMTMU_DWDM_INTF     (1)
#define XC_MAX_SMTMU_IM_LINE_INTF  (1)
#define XC_MAX_SMTMU_IM_PORT_INTF  (1)
#define XC_MAX_SMTMU_PORT_INTF     (10)

//
// Maximum number of connections allowed on each SMTMU interface
//
#define XC_MAX_XC_SMTMU_DWDM       (192)
#define XC_MAX_XC_SMTMU_IM_LINE    (192)
#define XC_MAX_XC_SMTMU_IM_PORT    (192)
#define XC_MAX_XC_SMTMU_PORT       (76)

//
// Maximum number of connections on SMTMU
//
#define XC_MAX_XC_SMTMU            ( (XC_MAX_SMTMU_DWDM_INTF * XC_MAX_XC_SMTMU_DWDM) + \
                                    (XC_MAX_SMTMU_IM_LINE_INTF * XC_MAX_XC_SMTMU_IM_LINE) + \
                                    (XC_MAX_SMTMU_IM_PORT_INTF * XC_MAX_XC_SMTMU_IM_PORT) + \
                                    (XC_MAX_SMTMU_PORT_INTF * XC_MAX_XC_SMTMU_PORT) )

// 
// Breakdown of SMTMU XC CFG Region
//

#define XC_SMTMU_CFG_PORT0_START   (0)
#define XC_SMTMU_CFG_PORT0_END     (XC_SMTMU_CFG_PORT0_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT1_START   (XC_SMTMU_CFG_PORT0_END + 1)
#define XC_SMTMU_CFG_PORT1_END     (XC_SMTMU_CFG_PORT1_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT2_START   (XC_SMTMU_CFG_PORT1_END + 1)
#define XC_SMTMU_CFG_PORT2_END     (XC_SMTMU_CFG_PORT2_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT3_START   (XC_SMTMU_CFG_PORT2_END + 1)
#define XC_SMTMU_CFG_PORT3_END     (XC_SMTMU_CFG_PORT3_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT4_START   (XC_SMTMU_CFG_PORT3_END + 1)
#define XC_SMTMU_CFG_PORT4_END     (XC_SMTMU_CFG_PORT4_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT5_START   (XC_SMTMU_CFG_PORT4_END + 1)
#define XC_SMTMU_CFG_PORT5_END     (XC_SMTMU_CFG_PORT5_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT6_START   (XC_SMTMU_CFG_PORT5_END + 1)
#define XC_SMTMU_CFG_PORT6_END     (XC_SMTMU_CFG_PORT6_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT7_START   (XC_SMTMU_CFG_PORT6_END + 1)
#define XC_SMTMU_CFG_PORT7_END     (XC_SMTMU_CFG_PORT7_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT8_START   (XC_SMTMU_CFG_PORT7_END + 1)
#define XC_SMTMU_CFG_PORT8_END     (XC_SMTMU_CFG_PORT8_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_PORT9_START   (XC_SMTMU_CFG_PORT8_END + 1)
#define XC_SMTMU_CFG_PORT9_END     (XC_SMTMU_CFG_PORT9_START + XC_MAX_XC_SMTMU_PORT - 1)

#define XC_SMTMU_CFG_DWDM_START    (XC_SMTMU_CFG_PORT9_END + 1)
#define XC_SMTMU_CFG_DWDM_END      (XC_SMTMU_CFG_DWDM_START + XC_MAX_XC_SMTMU_DWDM - 1)

#define XC_SMTMU_CFG_IM_LINE_START (XC_SMTMU_CFG_DWDM_END + 1)
#define XC_SMTMU_CFG_IM_LINE_END   (XC_SMTMU_CFG_IM_LINE_START + XC_MAX_XC_SMTMU_IM_LINE - 1)

#define XC_SMTMU_CFG_IM_PORT_START (XC_SMTMU_CFG_IM_LINE_END + 1)
#define XC_SMTMU_CFG_IM_PORT_END   (XC_SMTMU_CFG_IM_PORT_START + XC_MAX_XC_SMTMU_IM_PORT - 1)

//
// Identifiers for each SMTMU facility
//
#define XC_SMTMU_PORT0_FACILITY_ID    (1)
#define XC_SMTMU_PORT1_FACILITY_ID    (2)
#define XC_SMTMU_PORT2_FACILITY_ID    (3)
#define XC_SMTMU_PORT3_FACILITY_ID    (4)
#define XC_SMTMU_PORT4_FACILITY_ID    (5)
#define XC_SMTMU_PORT5_FACILITY_ID    (6)
#define XC_SMTMU_PORT6_FACILITY_ID    (7)
#define XC_SMTMU_PORT7_FACILITY_ID    (8)
#define XC_SMTMU_PORT8_FACILITY_ID    (9)
#define XC_SMTMU_PORT9_FACILITY_ID    (10)
#define XC_SMTMU_DWDM_FACILITY_ID     (11)
#define XC_SMTMU_IM_LINE_FACILITY_ID  (12)
#define XC_SMTMU_IM_PORT_FACILITY_ID  (13)

// Constant Array for use with indexing into
// the AG/SP Config Region. SP will
// use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as SMTMU facility identifiers ***
const int SMTMUConfigMap[] = {0,
                             XC_SMTMU_CFG_PORT0_START,
                             XC_SMTMU_CFG_PORT1_START,
                             XC_SMTMU_CFG_PORT2_START,
                             XC_SMTMU_CFG_PORT3_START,
                             XC_SMTMU_CFG_PORT4_START,
                             XC_SMTMU_CFG_PORT5_START,
                             XC_SMTMU_CFG_PORT6_START,
                             XC_SMTMU_CFG_PORT7_START,
                             XC_SMTMU_CFG_PORT8_START,
                             XC_SMTMU_CFG_PORT9_START,
                             XC_SMTMU_CFG_DWDM_START,
                             XC_SMTMU_CFG_IM_LINE_START,
                             XC_SMTMU_CFG_IM_PORT_START};
// *************************  End of SMTM U Definitions *********************

// *************************  SMTM UD/SD Definitions *********************

//
// Maximum number of each SMTMUDSD interface type
//
#define XC_MAX_SMTMUDSD_DWDM_INTF     (1)
#define XC_MAX_SMTMUDSD_PORT_INTF     (10)

//
// Maximum number of connections allowed on each SMTMUDSD interface
//
#define XC_MAX_XC_SMTMUDSD_DWDM       (192)
#define XC_MAX_XC_SMTMUDSD_PORT       (76)

//
// Maximum number of connections on SMTMUDSD
//
#define XC_MAX_XC_SMTMUDSD            ( (XC_MAX_SMTMUDSD_DWDM_INTF * XC_MAX_XC_SMTMUDSD_DWDM) + \
                                        (XC_MAX_SMTMUDSD_PORT_INTF * XC_MAX_XC_SMTMUDSD_PORT) )

// 
// Breakdown of SMTMUDSD XC CFG Region
//

#define XC_SMTMUDSD_CFG_PORT0_START   (0)
#define XC_SMTMUDSD_CFG_PORT0_END     (XC_SMTMUDSD_CFG_PORT0_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT1_START   (XC_SMTMUDSD_CFG_PORT0_END + 1)
#define XC_SMTMUDSD_CFG_PORT1_END     (XC_SMTMUDSD_CFG_PORT1_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT2_START   (XC_SMTMUDSD_CFG_PORT1_END + 1)
#define XC_SMTMUDSD_CFG_PORT2_END     (XC_SMTMUDSD_CFG_PORT2_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT3_START   (XC_SMTMUDSD_CFG_PORT2_END + 1)
#define XC_SMTMUDSD_CFG_PORT3_END     (XC_SMTMUDSD_CFG_PORT3_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT4_START   (XC_SMTMUDSD_CFG_PORT3_END + 1)
#define XC_SMTMUDSD_CFG_PORT4_END     (XC_SMTMUDSD_CFG_PORT4_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT5_START   (XC_SMTMUDSD_CFG_PORT4_END + 1)
#define XC_SMTMUDSD_CFG_PORT5_END     (XC_SMTMUDSD_CFG_PORT5_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT6_START   (XC_SMTMUDSD_CFG_PORT5_END + 1)
#define XC_SMTMUDSD_CFG_PORT6_END     (XC_SMTMUDSD_CFG_PORT6_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT7_START   (XC_SMTMUDSD_CFG_PORT6_END + 1)
#define XC_SMTMUDSD_CFG_PORT7_END     (XC_SMTMUDSD_CFG_PORT7_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT8_START   (XC_SMTMUDSD_CFG_PORT7_END + 1)
#define XC_SMTMUDSD_CFG_PORT8_END     (XC_SMTMUDSD_CFG_PORT8_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_PORT9_START   (XC_SMTMUDSD_CFG_PORT8_END + 1)
#define XC_SMTMUDSD_CFG_PORT9_END     (XC_SMTMUDSD_CFG_PORT9_START + XC_MAX_XC_SMTMUDSD_PORT - 1)

#define XC_SMTMUDSD_CFG_DWDM_START    (XC_SMTMUDSD_CFG_PORT9_END + 1)
#define XC_SMTMUDSD_CFG_DWDM_END      (XC_SMTMUDSD_CFG_DWDM_START + XC_MAX_XC_SMTMUDSD_DWDM - 1)

//
// Identifiers for each SMTMUDSD facility
//
#define XC_SMTMUDSD_PORT0_FACILITY_ID    (1)
#define XC_SMTMUDSD_PORT1_FACILITY_ID    (2)
#define XC_SMTMUDSD_PORT2_FACILITY_ID    (3)
#define XC_SMTMUDSD_PORT3_FACILITY_ID    (4)
#define XC_SMTMUDSD_PORT4_FACILITY_ID    (5)
#define XC_SMTMUDSD_PORT5_FACILITY_ID    (6)
#define XC_SMTMUDSD_PORT6_FACILITY_ID    (7)
#define XC_SMTMUDSD_PORT7_FACILITY_ID    (8)
#define XC_SMTMUDSD_PORT8_FACILITY_ID    (9)
#define XC_SMTMUDSD_PORT9_FACILITY_ID    (10)
#define XC_SMTMUDSD_DWDM_FACILITY_ID     (11)

// Constant Array for use with indexing into the AG/SP Config Region. SP will
// use 1 based Ports when using this method.  Therefore the array starts with zero.
// *** Must be kept in same order as SMTMUDSD facility identifiers ***
const int SMTMUDSDConfigMap[] = {0,
                             XC_SMTMUDSD_CFG_PORT0_START,
                             XC_SMTMUDSD_CFG_PORT1_START,
                             XC_SMTMUDSD_CFG_PORT2_START,
                             XC_SMTMUDSD_CFG_PORT3_START,
                             XC_SMTMUDSD_CFG_PORT4_START,
                             XC_SMTMUDSD_CFG_PORT5_START,
                             XC_SMTMUDSD_CFG_PORT6_START,
                             XC_SMTMUDSD_CFG_PORT7_START,
                             XC_SMTMUDSD_CFG_PORT8_START,
                             XC_SMTMUDSD_CFG_PORT9_START,
                             XC_SMTMUDSD_CFG_DWDM_START};
                             
// *************************  end of SMTM UD/SD Definitions *********************


// *************************  OTNM Definitions *********************

//
// Identifiers for each OTNM facility
//
// For Bachelor 192x192 Cross Connect
#define XC_OTNM_PORT1_FACILITY_ID    (1)
#define XC_OTNM_PORT2_FACILITY_ID    (2)
#define XC_OTNM_PORT3_FACILITY_ID    (3)
#define XC_OTNM_PORT4_FACILITY_ID    (4)
#define XC_OTNM_PORT5_FACILITY_ID    (5)
#define XC_OTNM_PORT6_FACILITY_ID    (6)
#define XC_OTNM_PORT7_FACILITY_ID    (7)
#define XC_OTNM_PORT8_FACILITY_ID    (8)

#define XC_OTNM_OC192_FACILITY_ID    (9)

// For ODU1 Midline Cross Connect
#define XC_OTNM_ODU1_MIDLINE1_FACILITY_ID    (10)   // OC-48 ByPass
#define XC_OTNM_ODU1_MIDLINE2_FACILITY_ID    (11)   // OC-48 ByPass
#define XC_OTNM_ODU1_MIDLINE3_FACILITY_ID    (12)   // OC-48 ByPass
#define XC_OTNM_ODU1_MIDLINE4_FACILITY_ID    (13)   // OC-48 ByPass
#define XC_OTNM_ODU1_MIDLINE5_FACILITY_ID    (14)   // STS 1-48 From Bachelor
#define XC_OTNM_ODU1_MIDLINE6_FACILITY_ID    (15)   // STS 49-96 From Bachelor
#define XC_OTNM_ODU1_MIDLINE7_FACILITY_ID    (16)   // STS 97-144 From Bachelor
#define XC_OTNM_ODU1_MIDLINE8_FACILITY_ID    (17)   // STS 145-192 From Bachelor

#define XC_OTNM_ODU1_MIDLINE9_FACILITY_ID    (18)   // Selected for OCH-P
#define XC_OTNM_ODU1_MIDLINE10_FACILITY_ID   (19)   // Selected for OCH-P
#define XC_OTNM_ODU1_MIDLINE11_FACILITY_ID   (20)   // Selected for OCH-P
#define XC_OTNM_ODU1_MIDLINE12_FACILITY_ID   (21)   // Selected for OCH-P

#define XC_OTNM_ODU1_IMUX1_FACILITY_ID       (22)   // Backplane
#define XC_OTNM_ODU1_IMUX2_FACILITY_ID       (23)   // Backplane
#define XC_OTNM_ODU1_IMUX3_FACILITY_ID       (24)   // Backplane 
#define XC_OTNM_ODU1_IMUX4_FACILITY_ID       (25)   // Backplane

// For ODU2 Cross Connect - Not in 5.1
#define XC_OTNM_ODU2_HIGHSPEED_FACILITY_ID   (26)   // From ODU2  (High Speed)
#define XC_OTNM_ODU2_ODU12MUX_FACILITY_ID    (27)   // Four ODU1s into ODU2 (Lower Speeds)

#define XC_OTNM_ODU2_OCHP_FACILITY_ID        (28)   // OCH-P Facility
#define XC_OTNM_ODU2_IMUX_FACILITY_ID        (29)   // Backplane


//
// Maximum number of each OTNM interface type
//
#define XC_MAX_OTNM_OC192_INTF    (1)
#define XC_MAX_OTNM_PORT_INTF     (8)

// For the OMUX ODU1 cross connect
#define XC_MAX_OTNM_ODU1_INTF     (16)
// For the ODU2 cross connect
#define XC_MAX_OTNM_ODU2_INTF     (4)


//
// Maximum number of connections allowed on each OTNM interface
//
#define XC_MAX_XC_OTNM_OC192      (192)
#define XC_MAX_XC_OTNM_PORT       (76)
#define XC_MAX_XC_OTNM_ODU1       (1)
#define XC_MAX_XC_OTNM_ODU2       (1)


//
// Maximum number of connections on OTNM
//
#define XC_MAX_XC_OTNM            ( (XC_MAX_OTNM_OC192_INTF * XC_MAX_XC_OTNM_OC192) + \
                                    (XC_MAX_OTNM_PORT_INTF * XC_MAX_XC_OTNM_PORT) + \
                                    (XC_MAX_OTNM_ODU1_INTF * XC_MAX_XC_OTNM_ODU1) + \
                                    (XC_MAX_OTNM_ODU2_INTF * XC_MAX_XC_OTNM_ODU2) )

// 
// Breakdown of OTNM XC CFG Region
//

#define XC_OTNM_CFG_PORT1_START   (0)
#define XC_OTNM_CFG_PORT1_END     (XC_OTNM_CFG_PORT1_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_PORT2_START   (XC_OTNM_CFG_PORT1_END + 1)
#define XC_OTNM_CFG_PORT2_END     (XC_OTNM_CFG_PORT2_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_PORT3_START   (XC_OTNM_CFG_PORT2_END + 1)
#define XC_OTNM_CFG_PORT3_END     (XC_OTNM_CFG_PORT3_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_PORT4_START   (XC_OTNM_CFG_PORT3_END + 1)
#define XC_OTNM_CFG_PORT4_END     (XC_OTNM_CFG_PORT4_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_PORT5_START   (XC_OTNM_CFG_PORT4_END + 1)
#define XC_OTNM_CFG_PORT5_END     (XC_OTNM_CFG_PORT5_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_PORT6_START   (XC_OTNM_CFG_PORT5_END + 1)
#define XC_OTNM_CFG_PORT6_END     (XC_OTNM_CFG_PORT6_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_PORT7_START   (XC_OTNM_CFG_PORT6_END + 1)
#define XC_OTNM_CFG_PORT7_END     (XC_OTNM_CFG_PORT7_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_PORT8_START   (XC_OTNM_CFG_PORT7_END + 1)
#define XC_OTNM_CFG_PORT8_END     (XC_OTNM_CFG_PORT8_START + XC_MAX_XC_OTNM_PORT - 1)

#define XC_OTNM_CFG_OC192_START   (XC_OTNM_CFG_PORT8_END + 1)
#define XC_OTNM_CFG_OC192_END     (XC_OTNM_CFG_OC192_START + XC_MAX_XC_OTNM_OC192 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE1_START    (XC_OTNM_CFG_OC192_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE1_END      (XC_OTNM_CFG_ODU1_MIDLINE1_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE2_START    (XC_OTNM_CFG_ODU1_MIDLINE1_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE2_END      (XC_OTNM_CFG_ODU1_MIDLINE2_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE3_START    (XC_OTNM_CFG_ODU1_MIDLINE2_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE3_END      (XC_OTNM_CFG_ODU1_MIDLINE3_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE4_START    (XC_OTNM_CFG_ODU1_MIDLINE3_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE4_END      (XC_OTNM_CFG_ODU1_MIDLINE4_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE5_START    (XC_OTNM_CFG_ODU1_MIDLINE4_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE5_END      (XC_OTNM_CFG_ODU1_MIDLINE5_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE6_START    (XC_OTNM_CFG_ODU1_MIDLINE5_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE6_END      (XC_OTNM_CFG_ODU1_MIDLINE6_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE7_START    (XC_OTNM_CFG_ODU1_MIDLINE6_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE7_END      (XC_OTNM_CFG_ODU1_MIDLINE7_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE8_START    (XC_OTNM_CFG_ODU1_MIDLINE7_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE8_END      (XC_OTNM_CFG_ODU1_MIDLINE8_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE9_START    (XC_OTNM_CFG_ODU1_MIDLINE8_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE9_END      (XC_OTNM_CFG_ODU1_MIDLINE9_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE10_START   (XC_OTNM_CFG_ODU1_MIDLINE9_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE10_END     (XC_OTNM_CFG_ODU1_MIDLINE10_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE11_START   (XC_OTNM_CFG_ODU1_MIDLINE10_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE11_END     (XC_OTNM_CFG_ODU1_MIDLINE11_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_MIDLINE12_START   (XC_OTNM_CFG_ODU1_MIDLINE11_END + 1)
#define XC_OTNM_CFG_ODU1_MIDLINE12_END     (XC_OTNM_CFG_ODU1_MIDLINE12_START + XC_MAX_XC_OTNM_ODU1 - 1)

// Post 5.1 ODU1 Backplane (IMUX) Ports
#define XC_OTNM_CFG_ODU1_IMUX1_START       (XC_OTNM_CFG_ODU1_MIDLINE12_END + 1)
#define XC_OTNM_CFG_ODU1_IMUX1_END         (XC_OTNM_CFG_ODU1_IMUX1_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_IMUX2_START       (XC_OTNM_CFG_ODU1_IMUX1_END + 1)
#define XC_OTNM_CFG_ODU1_IMUX2_END         (XC_OTNM_CFG_ODU1_IMUX2_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_IMUX3_START       (XC_OTNM_CFG_ODU1_IMUX2_END + 1)
#define XC_OTNM_CFG_ODU1_IMUX3_END         (XC_OTNM_CFG_ODU1_IMUX3_START + XC_MAX_XC_OTNM_ODU1 - 1)

#define XC_OTNM_CFG_ODU1_IMUX4_START       (XC_OTNM_CFG_ODU1_IMUX3_END + 1)
#define XC_OTNM_CFG_ODU1_IMUX4_END         (XC_OTNM_CFG_ODU1_IMUX4_START + XC_MAX_XC_OTNM_ODU1 - 1)

// Post 5.1 ODU2 Cross Connect
#define XC_OTNM_CFG_ODU2_HIGHSPEED_START   (XC_OTNM_CFG_ODU1_IMUX4_END + 1)
#define XC_OTNM_CFG_ODU2_HIGHSPEED_END     (XC_OTNM_CFG_ODU2_HIGHSPEED_START + XC_MAX_XC_OTNM_ODU2 - 1)

#define XC_OTNM_CFG_ODU2_ODU12MUX_START    (XC_OTNM_CFG_ODU2_HIGHSPEED_END + 1)
#define XC_OTNM_CFG_ODU2_ODU12MUX_END      (XC_OTNM_CFG_ODU2_ODU12MUX_START + XC_MAX_XC_OTNM_ODU2 - 1)

#define XC_OTNM_CFG_ODU2_OCHP_START        (XC_OTNM_CFG_ODU2_ODU12MUX_END + 1)
#define XC_OTNM_CFG_ODU2_OCHP_END          (XC_OTNM_CFG_ODU2_OCHP_START + XC_MAX_XC_OTNM_ODU2 - 1)

#define XC_OTNM_CFG_ODU2_IMUX_START        (XC_OTNM_CFG_ODU2_OCHP_END + 1)
#define XC_OTNM_CFG_ODU2_IMUX_END          (XC_OTNM_CFG_ODU2_IMUX_START + XC_MAX_XC_OTNM_ODU2 - 1)


// Constant Array for use with indexing into the AG/SP Config Region. SP will
// use 1 based Ports when using this method.  Therefore the array starts with zero.
// *** Must be kept in same order as OTNM facility identifiers ***
const int OTNMConfigMap[] = {0,
                             XC_OTNM_CFG_PORT1_START,
                             XC_OTNM_CFG_PORT2_START,
                             XC_OTNM_CFG_PORT3_START,
                             XC_OTNM_CFG_PORT4_START,
                             XC_OTNM_CFG_PORT5_START,
                             XC_OTNM_CFG_PORT6_START,
                             XC_OTNM_CFG_PORT7_START,
                             XC_OTNM_CFG_PORT8_START,
                             XC_OTNM_CFG_OC192_START,
                             XC_OTNM_CFG_ODU1_MIDLINE1_START,
                             XC_OTNM_CFG_ODU1_MIDLINE2_START,
                             XC_OTNM_CFG_ODU1_MIDLINE3_START,
                             XC_OTNM_CFG_ODU1_MIDLINE4_START,
                             XC_OTNM_CFG_ODU1_MIDLINE5_START,
                             XC_OTNM_CFG_ODU1_MIDLINE6_START,
                             XC_OTNM_CFG_ODU1_MIDLINE7_START,
                             XC_OTNM_CFG_ODU1_MIDLINE8_START,
                             XC_OTNM_CFG_ODU1_MIDLINE9_START,
                             XC_OTNM_CFG_ODU1_MIDLINE10_START,
                             XC_OTNM_CFG_ODU1_MIDLINE11_START,
                             XC_OTNM_CFG_ODU1_MIDLINE12_START,
                             XC_OTNM_CFG_ODU1_IMUX1_START,
                             XC_OTNM_CFG_ODU1_IMUX2_START,
                             XC_OTNM_CFG_ODU1_IMUX3_START,
                             XC_OTNM_CFG_ODU1_IMUX4_START,
                             XC_OTNM_CFG_ODU2_HIGHSPEED_START,
                             XC_OTNM_CFG_ODU2_ODU12MUX_START,
                             XC_OTNM_CFG_ODU2_IMUX_START,
                             XC_OTNM_CFG_ODU2_IMUX_END};
                             
// *************************  end of OTNM Definitions *********************



// *************************  DCMM Definitions *********************

//
// Maximum number of each DCMM interface type
//
#define XC_MAX_DCMM_LINE_INTF     (1)
#define XC_MAX_DCMM_EXPRESS_INTF  (1)
#define XC_MAX_DCMM_PORT_INTF     (8)

//
// Maximum number of connections allowed on each DCMM interface
//
#define XC_MAX_XC_DCMM_LINE       (32)
#define XC_MAX_XC_DCMM_EXPRESS    (32)
#define XC_MAX_XC_DCMM_PORT       (32)

//
// Maximum number of connections on DCMM
//
#define XC_MAX_XC_DCMM            ( (XC_MAX_DCMM_LINE_INTF * XC_MAX_XC_DCMM_LINE) + \
                                    (XC_MAX_DCMM_EXPRESS_INTF * XC_MAX_XC_DCMM_EXPRESS) + \
                                    (XC_MAX_XC_DCMM_PORT * XC_MAX_DCMM_PORT_INTF) )

// 
// Breakdown of DCMM XC CFG Region
//
#define XC_DCMM_CFG_LINE_START    (0)
#define XC_DCMM_CFG_LINE_END      (XC_DCMM_CFG_LINE_START + XC_MAX_XC_DCMM_LINE - 1)

#define XC_DCMM_CFG_EXPRESS_START (XC_DCMM_CFG_LINE_END + 1)
#define XC_DCMM_CFG_EXPRESS_END   (XC_DCMM_CFG_EXPRESS_START + XC_MAX_XC_DCMM_EXPRESS - 1)

#define XC_DCMM_CFG_PORT0_START   (XC_DCMM_CFG_EXPRESS_END + 1)
#define XC_DCMM_CFG_PORT0_END     (XC_DCMM_CFG_PORT0_START + XC_MAX_XC_DCMM_PORT - 1)

#define XC_DCMM_CFG_PORT1_START   (XC_DCMM_CFG_PORT0_END + 1)
#define XC_DCMM_CFG_PORT1_END     (XC_DCMM_CFG_PORT1_START + XC_MAX_XC_DCMM_PORT - 1)

#define XC_DCMM_CFG_PORT2_START   (XC_DCMM_CFG_PORT1_END + 1)
#define XC_DCMM_CFG_PORT2_END     (XC_DCMM_CFG_PORT2_START + XC_MAX_XC_DCMM_PORT - 1)

#define XC_DCMM_CFG_PORT3_START   (XC_DCMM_CFG_PORT2_END + 1)
#define XC_DCMM_CFG_PORT3_END     (XC_DCMM_CFG_PORT3_START + XC_MAX_XC_DCMM_PORT - 1)

#define XC_DCMM_CFG_PORT4_START   (XC_DCMM_CFG_PORT3_END + 1)
#define XC_DCMM_CFG_PORT4_END     (XC_DCMM_CFG_PORT4_START + XC_MAX_XC_DCMM_PORT - 1)

#define XC_DCMM_CFG_PORT5_START   (XC_DCMM_CFG_PORT4_END + 1)
#define XC_DCMM_CFG_PORT5_END     (XC_DCMM_CFG_PORT5_START + XC_MAX_XC_DCMM_PORT - 1)

#define XC_DCMM_CFG_PORT6_START   (XC_DCMM_CFG_PORT5_END + 1)
#define XC_DCMM_CFG_PORT6_END     (XC_DCMM_CFG_PORT6_START + XC_MAX_XC_DCMM_PORT - 1)

#define XC_DCMM_CFG_PORT7_START   (XC_DCMM_CFG_PORT6_END + 1)
#define XC_DCMM_CFG_PORT7_END     (XC_DCMM_CFG_PORT7_START + XC_MAX_XC_DCMM_PORT - 1)

//
// Identifiers for each DCMM facility
//
#define XC_DCMM_PORT0_FACILITY_ID    (1)
#define XC_DCMM_PORT1_FACILITY_ID    (2)
#define XC_DCMM_PORT2_FACILITY_ID    (3)
#define XC_DCMM_PORT3_FACILITY_ID    (4)
#define XC_DCMM_PORT4_FACILITY_ID    (5)
#define XC_DCMM_PORT5_FACILITY_ID    (6)
#define XC_DCMM_PORT6_FACILITY_ID    (7)
#define XC_DCMM_PORT7_FACILITY_ID    (8)
#define XC_DCMM_LINE_FACILITY_ID     (9)
#define XC_DCMM_EXPRESS_FACILITY_ID  (10)

// Constant Array for use with indexing into
// the AG Config Region. AG will
// use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as DCMM facility identifiers ***
const int DCMMConfigMap[] = {0,
                             XC_DCMM_CFG_PORT0_START,
                             XC_DCMM_CFG_PORT1_START,
                             XC_DCMM_CFG_PORT2_START,
                             XC_DCMM_CFG_PORT3_START,
                             XC_DCMM_CFG_PORT4_START,
                             XC_DCMM_CFG_PORT5_START,
                             XC_DCMM_CFG_PORT6_START,
                             XC_DCMM_CFG_PORT7_START,
                             XC_DCMM_CFG_LINE_START,
                             XC_DCMM_CFG_EXPRESS_START};


// *************************  RCMM Definitions *********************

//
// Maximum number of each RCMM interface type
//
#define XC_MAX_RCMM_LINE_INTF     (1)
#define XC_MAX_RCMM_EXPRESS_INTF  (8)
#define XC_MAX_RCMM_PORT_INTF     (88)

//
// Maximum number of connections allowed on each RCMM interface
//
#define XC_MAX_XC_RCMM_LINE       (88)
#define XC_MAX_XC_RCMM_EXPRESS    (88)
#define XC_MAX_XC_RCMM_PORT       (88)

//
// Maximum number of connections on RCMM
//
#define XC_MAX_XC_RCMM            ( (XC_MAX_RCMM_LINE_INTF * XC_MAX_XC_RCMM_LINE) + \
                                    (XC_MAX_RCMM_EXPRESS_INTF * XC_MAX_XC_RCMM_EXPRESS) + \
                                    (XC_MAX_XC_RCMM_PORT * XC_MAX_RCMM_PORT_INTF) )

// 
// Breakdown of RCMM XC CFG Region
//

#define XC_RCMM_CFG_PORT0_START      (0)
#define XC_RCMM_CFG_PORT0_END        (XC_RCMM_CFG_PORT0_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT1_START      (XC_RCMM_CFG_PORT0_END + 1)
#define XC_RCMM_CFG_PORT1_END        (XC_RCMM_CFG_PORT1_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT2_START      (XC_RCMM_CFG_PORT1_END + 1)
#define XC_RCMM_CFG_PORT2_END        (XC_RCMM_CFG_PORT2_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT3_START      (XC_RCMM_CFG_PORT2_END + 1)
#define XC_RCMM_CFG_PORT3_END        (XC_RCMM_CFG_PORT3_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT4_START      (XC_RCMM_CFG_PORT3_END + 1)
#define XC_RCMM_CFG_PORT4_END        (XC_RCMM_CFG_PORT4_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT5_START      (XC_RCMM_CFG_PORT4_END + 1)
#define XC_RCMM_CFG_PORT5_END        (XC_RCMM_CFG_PORT5_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT6_START      (XC_RCMM_CFG_PORT5_END + 1)
#define XC_RCMM_CFG_PORT6_END        (XC_RCMM_CFG_PORT6_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT7_START      (XC_RCMM_CFG_PORT6_END + 1)
#define XC_RCMM_CFG_PORT7_END        (XC_RCMM_CFG_PORT7_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT8_START      (XC_RCMM_CFG_PORT7_END + 1)
#define XC_RCMM_CFG_PORT8_END        (XC_RCMM_CFG_PORT8_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT9_START      (XC_RCMM_CFG_PORT8_END + 1)
#define XC_RCMM_CFG_PORT9_END        (XC_RCMM_CFG_PORT9_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT10_START     (XC_RCMM_CFG_PORT9_END + 1)
#define XC_RCMM_CFG_PORT10_END       (XC_RCMM_CFG_PORT10_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT11_START     (XC_RCMM_CFG_PORT10_END + 1)
#define XC_RCMM_CFG_PORT11_END       (XC_RCMM_CFG_PORT11_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT12_START     (XC_RCMM_CFG_PORT11_END + 1)
#define XC_RCMM_CFG_PORT12_END       (XC_RCMM_CFG_PORT12_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT13_START     (XC_RCMM_CFG_PORT12_END + 1)
#define XC_RCMM_CFG_PORT13_END       (XC_RCMM_CFG_PORT13_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT14_START     (XC_RCMM_CFG_PORT13_END + 1)
#define XC_RCMM_CFG_PORT14_END       (XC_RCMM_CFG_PORT14_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT15_START     (XC_RCMM_CFG_PORT14_END + 1)
#define XC_RCMM_CFG_PORT15_END       (XC_RCMM_CFG_PORT15_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT16_START     (XC_RCMM_CFG_PORT15_END + 1)
#define XC_RCMM_CFG_PORT16_END       (XC_RCMM_CFG_PORT16_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT17_START     (XC_RCMM_CFG_PORT16_END + 1)
#define XC_RCMM_CFG_PORT17_END       (XC_RCMM_CFG_PORT17_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT18_START     (XC_RCMM_CFG_PORT17_END + 1)
#define XC_RCMM_CFG_PORT18_END       (XC_RCMM_CFG_PORT18_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT19_START     (XC_RCMM_CFG_PORT18_END + 1)
#define XC_RCMM_CFG_PORT19_END       (XC_RCMM_CFG_PORT19_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT20_START     (XC_RCMM_CFG_PORT19_END + 1)
#define XC_RCMM_CFG_PORT20_END       (XC_RCMM_CFG_PORT20_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT21_START     (XC_RCMM_CFG_PORT20_END + 1)
#define XC_RCMM_CFG_PORT21_END       (XC_RCMM_CFG_PORT21_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT22_START     (XC_RCMM_CFG_PORT21_END + 1)
#define XC_RCMM_CFG_PORT22_END       (XC_RCMM_CFG_PORT22_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT23_START     (XC_RCMM_CFG_PORT22_END + 1)
#define XC_RCMM_CFG_PORT23_END       (XC_RCMM_CFG_PORT23_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT24_START     (XC_RCMM_CFG_PORT23_END + 1)
#define XC_RCMM_CFG_PORT24_END       (XC_RCMM_CFG_PORT24_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT25_START     (XC_RCMM_CFG_PORT24_END + 1)
#define XC_RCMM_CFG_PORT25_END       (XC_RCMM_CFG_PORT25_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT26_START     (XC_RCMM_CFG_PORT25_END + 1)
#define XC_RCMM_CFG_PORT26_END       (XC_RCMM_CFG_PORT26_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT27_START     (XC_RCMM_CFG_PORT26_END + 1)
#define XC_RCMM_CFG_PORT27_END       (XC_RCMM_CFG_PORT27_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT28_START     (XC_RCMM_CFG_PORT27_END + 1)
#define XC_RCMM_CFG_PORT28_END       (XC_RCMM_CFG_PORT28_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT29_START     (XC_RCMM_CFG_PORT28_END + 1)
#define XC_RCMM_CFG_PORT29_END       (XC_RCMM_CFG_PORT29_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT30_START     (XC_RCMM_CFG_PORT29_END + 1)
#define XC_RCMM_CFG_PORT30_END       (XC_RCMM_CFG_PORT30_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT31_START     (XC_RCMM_CFG_PORT30_END + 1)
#define XC_RCMM_CFG_PORT31_END       (XC_RCMM_CFG_PORT31_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT32_START     (XC_RCMM_CFG_PORT31_END + 1)
#define XC_RCMM_CFG_PORT32_END       (XC_RCMM_CFG_PORT32_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT33_START     (XC_RCMM_CFG_PORT32_END + 1)
#define XC_RCMM_CFG_PORT33_END       (XC_RCMM_CFG_PORT33_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT34_START     (XC_RCMM_CFG_PORT33_END + 1)
#define XC_RCMM_CFG_PORT34_END       (XC_RCMM_CFG_PORT34_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT35_START     (XC_RCMM_CFG_PORT34_END + 1)
#define XC_RCMM_CFG_PORT35_END       (XC_RCMM_CFG_PORT35_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT36_START     (XC_RCMM_CFG_PORT35_END + 1)
#define XC_RCMM_CFG_PORT36_END       (XC_RCMM_CFG_PORT36_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT37_START     (XC_RCMM_CFG_PORT36_END + 1)
#define XC_RCMM_CFG_PORT37_END       (XC_RCMM_CFG_PORT37_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT38_START     (XC_RCMM_CFG_PORT37_END + 1)
#define XC_RCMM_CFG_PORT38_END       (XC_RCMM_CFG_PORT38_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT39_START     (XC_RCMM_CFG_PORT38_END + 1)
#define XC_RCMM_CFG_PORT39_END       (XC_RCMM_CFG_PORT39_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT40_START     (XC_RCMM_CFG_PORT39_END + 1)
#define XC_RCMM_CFG_PORT40_END       (XC_RCMM_CFG_PORT40_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT41_START     (XC_RCMM_CFG_PORT40_END + 1)
#define XC_RCMM_CFG_PORT41_END       (XC_RCMM_CFG_PORT41_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT42_START     (XC_RCMM_CFG_PORT41_END + 1)
#define XC_RCMM_CFG_PORT42_END       (XC_RCMM_CFG_PORT42_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT43_START     (XC_RCMM_CFG_PORT42_END + 1)
#define XC_RCMM_CFG_PORT43_END       (XC_RCMM_CFG_PORT43_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT44_START     (XC_RCMM_CFG_PORT43_END + 1)
#define XC_RCMM_CFG_PORT44_END       (XC_RCMM_CFG_PORT44_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT45_START     (XC_RCMM_CFG_PORT44_END + 1)
#define XC_RCMM_CFG_PORT45_END       (XC_RCMM_CFG_PORT45_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT46_START     (XC_RCMM_CFG_PORT45_END + 1)
#define XC_RCMM_CFG_PORT46_END       (XC_RCMM_CFG_PORT46_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT47_START     (XC_RCMM_CFG_PORT46_END + 1)
#define XC_RCMM_CFG_PORT47_END       (XC_RCMM_CFG_PORT47_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT48_START     (XC_RCMM_CFG_PORT47_END + 1)
#define XC_RCMM_CFG_PORT48_END       (XC_RCMM_CFG_PORT48_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT49_START     (XC_RCMM_CFG_PORT48_END + 1)
#define XC_RCMM_CFG_PORT49_END       (XC_RCMM_CFG_PORT49_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT50_START     (XC_RCMM_CFG_PORT49_END + 1)
#define XC_RCMM_CFG_PORT50_END       (XC_RCMM_CFG_PORT50_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT51_START     (XC_RCMM_CFG_PORT50_END + 1)
#define XC_RCMM_CFG_PORT51_END       (XC_RCMM_CFG_PORT51_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT52_START     (XC_RCMM_CFG_PORT51_END + 1)
#define XC_RCMM_CFG_PORT52_END       (XC_RCMM_CFG_PORT52_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT53_START     (XC_RCMM_CFG_PORT52_END + 1)
#define XC_RCMM_CFG_PORT53_END       (XC_RCMM_CFG_PORT53_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT54_START     (XC_RCMM_CFG_PORT53_END + 1)
#define XC_RCMM_CFG_PORT54_END       (XC_RCMM_CFG_PORT54_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT55_START     (XC_RCMM_CFG_PORT54_END + 1)
#define XC_RCMM_CFG_PORT55_END       (XC_RCMM_CFG_PORT55_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT56_START     (XC_RCMM_CFG_PORT55_END + 1)
#define XC_RCMM_CFG_PORT56_END       (XC_RCMM_CFG_PORT56_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT57_START     (XC_RCMM_CFG_PORT56_END + 1)
#define XC_RCMM_CFG_PORT57_END       (XC_RCMM_CFG_PORT57_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT58_START     (XC_RCMM_CFG_PORT57_END + 1)
#define XC_RCMM_CFG_PORT58_END       (XC_RCMM_CFG_PORT58_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT59_START     (XC_RCMM_CFG_PORT58_END + 1)
#define XC_RCMM_CFG_PORT59_END       (XC_RCMM_CFG_PORT59_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT60_START     (XC_RCMM_CFG_PORT59_END + 1)
#define XC_RCMM_CFG_PORT60_END       (XC_RCMM_CFG_PORT60_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT61_START     (XC_RCMM_CFG_PORT60_END + 1)
#define XC_RCMM_CFG_PORT61_END       (XC_RCMM_CFG_PORT61_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT62_START     (XC_RCMM_CFG_PORT61_END + 1)
#define XC_RCMM_CFG_PORT62_END       (XC_RCMM_CFG_PORT62_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT63_START     (XC_RCMM_CFG_PORT62_END + 1)
#define XC_RCMM_CFG_PORT63_END       (XC_RCMM_CFG_PORT63_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT64_START     (XC_RCMM_CFG_PORT63_END + 1)
#define XC_RCMM_CFG_PORT64_END       (XC_RCMM_CFG_PORT64_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT65_START     (XC_RCMM_CFG_PORT64_END + 1)
#define XC_RCMM_CFG_PORT65_END       (XC_RCMM_CFG_PORT65_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT66_START     (XC_RCMM_CFG_PORT65_END + 1)
#define XC_RCMM_CFG_PORT66_END       (XC_RCMM_CFG_PORT66_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT67_START     (XC_RCMM_CFG_PORT66_END + 1)
#define XC_RCMM_CFG_PORT67_END       (XC_RCMM_CFG_PORT67_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT68_START     (XC_RCMM_CFG_PORT67_END + 1)
#define XC_RCMM_CFG_PORT68_END       (XC_RCMM_CFG_PORT68_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT69_START     (XC_RCMM_CFG_PORT68_END + 1)
#define XC_RCMM_CFG_PORT69_END       (XC_RCMM_CFG_PORT69_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT70_START     (XC_RCMM_CFG_PORT69_END + 1)
#define XC_RCMM_CFG_PORT70_END       (XC_RCMM_CFG_PORT70_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT71_START     (XC_RCMM_CFG_PORT70_END + 1)
#define XC_RCMM_CFG_PORT71_END       (XC_RCMM_CFG_PORT71_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT72_START     (XC_RCMM_CFG_PORT71_END + 1)
#define XC_RCMM_CFG_PORT72_END       (XC_RCMM_CFG_PORT72_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT73_START     (XC_RCMM_CFG_PORT72_END + 1)
#define XC_RCMM_CFG_PORT73_END       (XC_RCMM_CFG_PORT73_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT74_START     (XC_RCMM_CFG_PORT73_END + 1)
#define XC_RCMM_CFG_PORT74_END       (XC_RCMM_CFG_PORT74_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT75_START     (XC_RCMM_CFG_PORT74_END + 1)
#define XC_RCMM_CFG_PORT75_END       (XC_RCMM_CFG_PORT75_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT76_START     (XC_RCMM_CFG_PORT75_END + 1)
#define XC_RCMM_CFG_PORT76_END       (XC_RCMM_CFG_PORT76_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT77_START     (XC_RCMM_CFG_PORT76_END + 1)
#define XC_RCMM_CFG_PORT77_END       (XC_RCMM_CFG_PORT77_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT78_START     (XC_RCMM_CFG_PORT77_END + 1)
#define XC_RCMM_CFG_PORT78_END       (XC_RCMM_CFG_PORT78_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT79_START     (XC_RCMM_CFG_PORT78_END + 1)
#define XC_RCMM_CFG_PORT79_END       (XC_RCMM_CFG_PORT79_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT80_START     (XC_RCMM_CFG_PORT79_END + 1)
#define XC_RCMM_CFG_PORT80_END       (XC_RCMM_CFG_PORT80_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT81_START     (XC_RCMM_CFG_PORT80_END + 1)
#define XC_RCMM_CFG_PORT81_END       (XC_RCMM_CFG_PORT81_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT82_START     (XC_RCMM_CFG_PORT81_END + 1)
#define XC_RCMM_CFG_PORT82_END       (XC_RCMM_CFG_PORT82_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT83_START     (XC_RCMM_CFG_PORT82_END + 1)
#define XC_RCMM_CFG_PORT83_END       (XC_RCMM_CFG_PORT83_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT84_START     (XC_RCMM_CFG_PORT83_END + 1)
#define XC_RCMM_CFG_PORT84_END       (XC_RCMM_CFG_PORT84_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT85_START     (XC_RCMM_CFG_PORT84_END + 1)
#define XC_RCMM_CFG_PORT85_END       (XC_RCMM_CFG_PORT85_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT86_START     (XC_RCMM_CFG_PORT85_END + 1)
#define XC_RCMM_CFG_PORT86_END       (XC_RCMM_CFG_PORT86_START + XC_MAX_XC_RCMM_PORT - 1)

#define XC_RCMM_CFG_PORT87_START     (XC_RCMM_CFG_PORT86_END + 1)
#define XC_RCMM_CFG_PORT87_END       (XC_RCMM_CFG_PORT87_START + XC_MAX_XC_RCMM_PORT - 1)


#define XC_RCMM_CFG_LINE_START       (XC_RCMM_CFG_PORT87_END + 1)
#define XC_RCMM_CFG_LINE_END         (XC_RCMM_CFG_LINE_START + XC_MAX_XC_RCMM_LINE - 1)


#define XC_RCMM_CFG_EXPRESS0_START   (XC_RCMM_CFG_LINE_END + 1)
#define XC_RCMM_CFG_EXPRESS0_END     (XC_RCMM_CFG_EXPRESS0_START + XC_MAX_XC_RCMM_EXPRESS - 1)

#define XC_RCMM_CFG_EXPRESS1_START   (XC_RCMM_CFG_EXPRESS0_END + 1)
#define XC_RCMM_CFG_EXPRESS1_END     (XC_RCMM_CFG_EXPRESS1_START + XC_MAX_XC_RCMM_EXPRESS - 1)

#define XC_RCMM_CFG_EXPRESS2_START   (XC_RCMM_CFG_EXPRESS1_END + 1)
#define XC_RCMM_CFG_EXPRESS2_END     (XC_RCMM_CFG_EXPRESS2_START + XC_MAX_XC_RCMM_EXPRESS - 1)

#define XC_RCMM_CFG_EXPRESS3_START   (XC_RCMM_CFG_EXPRESS2_END + 1)
#define XC_RCMM_CFG_EXPRESS3_END     (XC_RCMM_CFG_EXPRESS3_START + XC_MAX_XC_RCMM_EXPRESS - 1)

#define XC_RCMM_CFG_EXPRESS4_START   (XC_RCMM_CFG_EXPRESS3_END + 1)
#define XC_RCMM_CFG_EXPRESS4_END     (XC_RCMM_CFG_EXPRESS4_START + XC_MAX_XC_RCMM_EXPRESS - 1)

#define XC_RCMM_CFG_EXPRESS5_START   (XC_RCMM_CFG_EXPRESS4_END + 1)
#define XC_RCMM_CFG_EXPRESS5_END     (XC_RCMM_CFG_EXPRESS5_START + XC_MAX_XC_RCMM_EXPRESS - 1)

#define XC_RCMM_CFG_EXPRESS6_START   (XC_RCMM_CFG_EXPRESS5_END + 1)
#define XC_RCMM_CFG_EXPRESS6_END     (XC_RCMM_CFG_EXPRESS6_START + XC_MAX_XC_RCMM_EXPRESS - 1)

#define XC_RCMM_CFG_EXPRESS7_START   (XC_RCMM_CFG_EXPRESS6_END + 1)
#define XC_RCMM_CFG_EXPRESS7_END     (XC_RCMM_CFG_EXPRESS7_START + XC_MAX_XC_RCMM_EXPRESS - 1)


//
// Identifiers for each RCMM facility
//
#define XC_RCMM_PORT0_FACILITY_ID      (1)
#define XC_RCMM_PORT1_FACILITY_ID      (2)
#define XC_RCMM_PORT2_FACILITY_ID      (3)
#define XC_RCMM_PORT3_FACILITY_ID      (4)
#define XC_RCMM_PORT4_FACILITY_ID      (5)
#define XC_RCMM_PORT5_FACILITY_ID      (6)
#define XC_RCMM_PORT6_FACILITY_ID      (7)
#define XC_RCMM_PORT7_FACILITY_ID      (8)
#define XC_RCMM_PORT8_FACILITY_ID      (9)
#define XC_RCMM_PORT9_FACILITY_ID      (10)

#define XC_RCMM_PORT10_FACILITY_ID     (11)
#define XC_RCMM_PORT11_FACILITY_ID     (12)
#define XC_RCMM_PORT12_FACILITY_ID     (13)
#define XC_RCMM_PORT13_FACILITY_ID     (14)
#define XC_RCMM_PORT14_FACILITY_ID     (15)
#define XC_RCMM_PORT15_FACILITY_ID     (16)
#define XC_RCMM_PORT16_FACILITY_ID     (17)
#define XC_RCMM_PORT17_FACILITY_ID     (18)
#define XC_RCMM_PORT18_FACILITY_ID     (19)
#define XC_RCMM_PORT19_FACILITY_ID     (20)

#define XC_RCMM_PORT20_FACILITY_ID     (21)
#define XC_RCMM_PORT21_FACILITY_ID     (22)
#define XC_RCMM_PORT22_FACILITY_ID     (23)
#define XC_RCMM_PORT23_FACILITY_ID     (24)
#define XC_RCMM_PORT24_FACILITY_ID     (25)
#define XC_RCMM_PORT25_FACILITY_ID     (26)
#define XC_RCMM_PORT26_FACILITY_ID     (27)
#define XC_RCMM_PORT27_FACILITY_ID     (28)
#define XC_RCMM_PORT28_FACILITY_ID     (29)
#define XC_RCMM_PORT29_FACILITY_ID     (30)

#define XC_RCMM_PORT30_FACILITY_ID     (31)
#define XC_RCMM_PORT31_FACILITY_ID     (32)
#define XC_RCMM_PORT32_FACILITY_ID     (33)
#define XC_RCMM_PORT33_FACILITY_ID     (34)
#define XC_RCMM_PORT34_FACILITY_ID     (35)
#define XC_RCMM_PORT35_FACILITY_ID     (36)
#define XC_RCMM_PORT36_FACILITY_ID     (37)
#define XC_RCMM_PORT37_FACILITY_ID     (38)
#define XC_RCMM_PORT38_FACILITY_ID     (39)
#define XC_RCMM_PORT39_FACILITY_ID     (40)

#define XC_RCMM_PORT40_FACILITY_ID     (41)
#define XC_RCMM_PORT41_FACILITY_ID     (42)
#define XC_RCMM_PORT42_FACILITY_ID     (43)
#define XC_RCMM_PORT43_FACILITY_ID     (44)
#define XC_RCMM_PORT44_FACILITY_ID     (45)
#define XC_RCMM_PORT45_FACILITY_ID     (46)
#define XC_RCMM_PORT46_FACILITY_ID     (47)
#define XC_RCMM_PORT47_FACILITY_ID     (48)
#define XC_RCMM_PORT48_FACILITY_ID     (49)
#define XC_RCMM_PORT49_FACILITY_ID     (50)

#define XC_RCMM_PORT50_FACILITY_ID     (51)
#define XC_RCMM_PORT51_FACILITY_ID     (52)
#define XC_RCMM_PORT52_FACILITY_ID     (53)
#define XC_RCMM_PORT53_FACILITY_ID     (54)
#define XC_RCMM_PORT54_FACILITY_ID     (55)
#define XC_RCMM_PORT55_FACILITY_ID     (56)
#define XC_RCMM_PORT56_FACILITY_ID     (57)
#define XC_RCMM_PORT57_FACILITY_ID     (58)
#define XC_RCMM_PORT58_FACILITY_ID     (59)
#define XC_RCMM_PORT59_FACILITY_ID     (60)

#define XC_RCMM_PORT60_FACILITY_ID     (61)
#define XC_RCMM_PORT61_FACILITY_ID     (62)
#define XC_RCMM_PORT62_FACILITY_ID     (63)
#define XC_RCMM_PORT63_FACILITY_ID     (64)
#define XC_RCMM_PORT64_FACILITY_ID     (65)
#define XC_RCMM_PORT65_FACILITY_ID     (66)
#define XC_RCMM_PORT66_FACILITY_ID     (67)
#define XC_RCMM_PORT67_FACILITY_ID     (68)
#define XC_RCMM_PORT68_FACILITY_ID     (69)
#define XC_RCMM_PORT69_FACILITY_ID     (70)

#define XC_RCMM_PORT70_FACILITY_ID     (71)
#define XC_RCMM_PORT71_FACILITY_ID     (72)
#define XC_RCMM_PORT72_FACILITY_ID     (73)
#define XC_RCMM_PORT73_FACILITY_ID     (74)
#define XC_RCMM_PORT74_FACILITY_ID     (75)
#define XC_RCMM_PORT75_FACILITY_ID     (76)
#define XC_RCMM_PORT76_FACILITY_ID     (77)
#define XC_RCMM_PORT77_FACILITY_ID     (78)
#define XC_RCMM_PORT78_FACILITY_ID     (79)
#define XC_RCMM_PORT79_FACILITY_ID     (80)

#define XC_RCMM_PORT80_FACILITY_ID     (81)
#define XC_RCMM_PORT81_FACILITY_ID     (82)
#define XC_RCMM_PORT82_FACILITY_ID     (83)
#define XC_RCMM_PORT83_FACILITY_ID     (84)
#define XC_RCMM_PORT84_FACILITY_ID     (85)
#define XC_RCMM_PORT85_FACILITY_ID     (86)
#define XC_RCMM_PORT86_FACILITY_ID     (87)
#define XC_RCMM_PORT87_FACILITY_ID     (88)


#define XC_RCMM_LINE_FACILITY_ID       (89)
#define XC_RCMM_EXPRESS_FACILITY_ID    (90)
#define XC_RCMM_EXPRESS0_FACILITY_ID   (90)
#define XC_RCMM_EXPRESS1_FACILITY_ID   (91)
#define XC_RCMM_EXPRESS2_FACILITY_ID   (92)
#define XC_RCMM_EXPRESS3_FACILITY_ID   (93)
#define XC_RCMM_EXPRESS4_FACILITY_ID   (94)
#define XC_RCMM_EXPRESS5_FACILITY_ID   (95)
#define XC_RCMM_EXPRESS6_FACILITY_ID   (96)
#define XC_RCMM_EXPRESS7_FACILITY_ID   (97)

// Constant Array for use with indexing into
// the AG Config Region. AG will
// use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as RCMM facility identifiers ***
const int RCMMConfigMap[] = {0,
                             XC_RCMM_CFG_PORT0_START,
                             XC_RCMM_CFG_PORT1_START,
                             XC_RCMM_CFG_PORT2_START,
                             XC_RCMM_CFG_PORT3_START,
                             XC_RCMM_CFG_PORT4_START,
                             XC_RCMM_CFG_PORT5_START,
                             XC_RCMM_CFG_PORT6_START,
                             XC_RCMM_CFG_PORT7_START,
                             XC_RCMM_CFG_PORT8_START,
                             XC_RCMM_CFG_PORT9_START,
                             XC_RCMM_CFG_PORT10_START,
                             XC_RCMM_CFG_PORT11_START,
                             XC_RCMM_CFG_PORT12_START,
                             XC_RCMM_CFG_PORT13_START,
                             XC_RCMM_CFG_PORT14_START,
                             XC_RCMM_CFG_PORT15_START,
                             XC_RCMM_CFG_PORT16_START,
                             XC_RCMM_CFG_PORT17_START,
                             XC_RCMM_CFG_PORT18_START,
                             XC_RCMM_CFG_PORT19_START,
                             XC_RCMM_CFG_PORT20_START,
                             XC_RCMM_CFG_PORT21_START,
                             XC_RCMM_CFG_PORT22_START,
                             XC_RCMM_CFG_PORT23_START,
                             XC_RCMM_CFG_PORT24_START,
                             XC_RCMM_CFG_PORT25_START,
                             XC_RCMM_CFG_PORT26_START,
                             XC_RCMM_CFG_PORT27_START,
                             XC_RCMM_CFG_PORT28_START,
                             XC_RCMM_CFG_PORT29_START,
                             XC_RCMM_CFG_PORT30_START,
                             XC_RCMM_CFG_PORT31_START,
                             XC_RCMM_CFG_PORT32_START,
                             XC_RCMM_CFG_PORT33_START,
                             XC_RCMM_CFG_PORT34_START,
                             XC_RCMM_CFG_PORT35_START,
                             XC_RCMM_CFG_PORT36_START,
                             XC_RCMM_CFG_PORT37_START,
                             XC_RCMM_CFG_PORT38_START,
                             XC_RCMM_CFG_PORT39_START,
                             XC_RCMM_CFG_PORT40_START,
                             XC_RCMM_CFG_PORT41_START,
                             XC_RCMM_CFG_PORT42_START,
                             XC_RCMM_CFG_PORT43_START,
                             XC_RCMM_CFG_PORT44_START,
                             XC_RCMM_CFG_PORT45_START,
                             XC_RCMM_CFG_PORT46_START,
                             XC_RCMM_CFG_PORT47_START,
                             XC_RCMM_CFG_PORT48_START,
                             XC_RCMM_CFG_PORT49_START,
                             XC_RCMM_CFG_PORT50_START,
                             XC_RCMM_CFG_PORT51_START,
                             XC_RCMM_CFG_PORT52_START,
                             XC_RCMM_CFG_PORT53_START,
                             XC_RCMM_CFG_PORT54_START,
                             XC_RCMM_CFG_PORT55_START,
                             XC_RCMM_CFG_PORT56_START,
                             XC_RCMM_CFG_PORT57_START,
                             XC_RCMM_CFG_PORT58_START,
                             XC_RCMM_CFG_PORT59_START,
                             XC_RCMM_CFG_PORT60_START,
                             XC_RCMM_CFG_PORT61_START,
                             XC_RCMM_CFG_PORT62_START,
                             XC_RCMM_CFG_PORT63_START,
                             XC_RCMM_CFG_PORT64_START,
                             XC_RCMM_CFG_PORT65_START,
                             XC_RCMM_CFG_PORT66_START,
                             XC_RCMM_CFG_PORT67_START,
                             XC_RCMM_CFG_PORT68_START,
                             XC_RCMM_CFG_PORT69_START,
                             XC_RCMM_CFG_PORT70_START,
                             XC_RCMM_CFG_PORT71_START,
                             XC_RCMM_CFG_PORT72_START,
                             XC_RCMM_CFG_PORT73_START,
                             XC_RCMM_CFG_PORT74_START,
                             XC_RCMM_CFG_PORT75_START,
                             XC_RCMM_CFG_PORT76_START,
                             XC_RCMM_CFG_PORT77_START,
                             XC_RCMM_CFG_PORT78_START,
                             XC_RCMM_CFG_PORT79_START,
                             XC_RCMM_CFG_PORT80_START,
                             XC_RCMM_CFG_PORT81_START,
                             XC_RCMM_CFG_PORT82_START,
                             XC_RCMM_CFG_PORT83_START,
                             XC_RCMM_CFG_PORT84_START,
                             XC_RCMM_CFG_PORT85_START,
                             XC_RCMM_CFG_PORT86_START,
                             XC_RCMM_CFG_PORT87_START,
                             XC_RCMM_CFG_LINE_START,
                             XC_RCMM_CFG_EXPRESS0_START,
                             XC_RCMM_CFG_EXPRESS1_START,
                             XC_RCMM_CFG_EXPRESS2_START,
                             XC_RCMM_CFG_EXPRESS3_START,
                             XC_RCMM_CFG_EXPRESS4_START,
                             XC_RCMM_CFG_EXPRESS5_START,
                             XC_RCMM_CFG_EXPRESS6_START,
                             XC_RCMM_CFG_EXPRESS7_START};

// *************************  NANO_CCM Definitions *********************

//
// Maximum number of each NANO_CCM interface type
//
#define XC_MAX_NANO_CCM_LINE_INTF     (1)
#define XC_MAX_NANO_CCM_EXPRESS_INTF  (1)
#define XC_MAX_NANO_CCM_PORT_INTF     (8)

//
// Maximum number of connections allowed on each NANO_CCM interface
//
#define XC_MAX_XC_NANO_CCM_LINE       (44)
#define XC_MAX_XC_NANO_CCM_EXPRESS    (44)
#define XC_MAX_XC_NANO_CCM_PORT       (44)

//
// Maximum number of connections on NANO_CCM
//
#define XC_MAX_XC_NANO_CCM        ( (XC_MAX_NANO_CCM_LINE_INTF * XC_MAX_XC_NANO_CCM_LINE) + \
                                    (XC_MAX_NANO_CCM_EXPRESS_INTF * XC_MAX_XC_NANO_CCM_EXPRESS) + \
                                    (XC_MAX_XC_NANO_CCM_PORT * XC_MAX_NANO_CCM_PORT_INTF) )

// 
// Breakdown of NANO_CCM XC CFG Region
//

#define XC_NANO_CCM_CFG_PORT0_START      (0)
#define XC_NANO_CCM_CFG_PORT0_END        (XC_NANO_CCM_CFG_PORT0_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_PORT1_START      (XC_NANO_CCM_CFG_PORT0_END + 1)
#define XC_NANO_CCM_CFG_PORT1_END        (XC_NANO_CCM_CFG_PORT1_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_PORT2_START      (XC_NANO_CCM_CFG_PORT1_END + 1)
#define XC_NANO_CCM_CFG_PORT2_END        (XC_NANO_CCM_CFG_PORT2_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_PORT3_START      (XC_NANO_CCM_CFG_PORT2_END + 1)
#define XC_NANO_CCM_CFG_PORT3_END        (XC_NANO_CCM_CFG_PORT3_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_PORT4_START      (XC_NANO_CCM_CFG_PORT3_END + 1)
#define XC_NANO_CCM_CFG_PORT4_END        (XC_NANO_CCM_CFG_PORT4_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_PORT5_START      (XC_NANO_CCM_CFG_PORT4_END + 1)
#define XC_NANO_CCM_CFG_PORT5_END        (XC_NANO_CCM_CFG_PORT5_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_PORT6_START      (XC_NANO_CCM_CFG_PORT5_END + 1)
#define XC_NANO_CCM_CFG_PORT6_END        (XC_NANO_CCM_CFG_PORT6_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_PORT7_START      (XC_NANO_CCM_CFG_PORT6_END + 1)
#define XC_NANO_CCM_CFG_PORT7_END        (XC_NANO_CCM_CFG_PORT7_START + XC_MAX_XC_NANO_CCM_PORT - 1)

#define XC_NANO_CCM_CFG_EXPRESS_START    (XC_NANO_CCM_CFG_PORT7_END + 1)
#define XC_NANO_CCM_CFG_EXPRESS_END      (XC_NANO_CCM_CFG_EXPRESS_START + XC_MAX_XC_NANO_CCM_EXPRESS - 1)

#define XC_NANO_CCM_CFG_LINE_START       (XC_NANO_CCM_CFG_EXPRESS_END + 1)
#define XC_NANO_CCM_CFG_LINE_END         (XC_NANO_CCM_CFG_LINE_START + XC_MAX_XC_NANO_CCM_LINE - 1)

// Identifiers for each NANO_CCM facility
//
#define XC_NANO_CCM_PORT0_FACILITY_ID      (1)
#define XC_NANO_CCM_PORT1_FACILITY_ID      (2)
#define XC_NANO_CCM_PORT2_FACILITY_ID      (3)
#define XC_NANO_CCM_PORT3_FACILITY_ID      (4)
#define XC_NANO_CCM_PORT4_FACILITY_ID      (5)
#define XC_NANO_CCM_PORT5_FACILITY_ID      (6)
#define XC_NANO_CCM_PORT6_FACILITY_ID      (7)
#define XC_NANO_CCM_PORT7_FACILITY_ID      (8)
#define XC_NANO_CCM_EXPRESS_FACILITY_ID    (9)
#define XC_NANO_CCM_LINE_FACILITY_ID       (10)


// Constant Array for use with indexing into
// the AG Config Region. AG will
// use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as NANO_CCM facility identifiers ***
const int NANO_CCMConfigMap[] = {0,
                             XC_NANO_CCM_CFG_PORT0_START,
                             XC_NANO_CCM_CFG_PORT1_START,
                             XC_NANO_CCM_CFG_PORT2_START,
                             XC_NANO_CCM_CFG_PORT3_START,
                             XC_NANO_CCM_CFG_PORT4_START,
                             XC_NANO_CCM_CFG_PORT5_START,
                             XC_NANO_CCM_CFG_PORT6_START,
                             XC_NANO_CCM_CFG_PORT7_START,
                             XC_NANO_CCM_CFG_EXPRESS_START,
                             XC_NANO_CCM_CFG_LINE_START};




// *************************  CADM Definitions *********************

//
// Maximum number of each CADM interface type
//
#define XC_MAX_CADM_LINE_INTF      (1)
#define XC_MAX_CADM_EXPRESS_INTF   (7)
#define XC_MAX_CADM_AUXILIARY_INTF (2)
#define XC_MAX_CADM_PORT_INTF      (8)

//
// Maximum number of connections allowed on each CADM interface
//
#define XC_MAX_XC_CADM_LINE       (88)
#define XC_MAX_XC_CADM_EXPRESS    (88)
#define XC_MAX_XC_CADM_AUXILIARY  (88)
#define XC_MAX_XC_CADM_PORT       (88)

//
// Maximum number of connections on a CADM
//
#define XC_MAX_XC_CADM        ( (XC_MAX_CADM_LINE_INTF * XC_MAX_XC_CADM_LINE)           + \
                                (XC_MAX_CADM_EXPRESS_INTF * XC_MAX_XC_CADM_EXPRESS)     + \
                                (XC_MAX_CADM_AUXILIARY_INTF * XC_MAX_XC_CADM_AUXILIARY) + \
                                (XC_MAX_XC_CADM_PORT * XC_MAX_CADM_PORT_INTF) )

// 
// Breakdown of CADM XC CFG Region
//

#define XC_CADM_CFG_LINE_START       (0)
#define XC_CADM_CFG_LINE_END         (XC_CADM_CFG_LINE_START + XC_MAX_XC_CADM_LINE - 1)


#define XC_CADM_CFG_PORT0_START      (XC_CADM_CFG_LINE_END + 1)
#define XC_CADM_CFG_PORT0_END        (XC_CADM_CFG_PORT0_START + XC_MAX_XC_CADM_PORT - 1)

#define XC_CADM_CFG_PORT1_START      (XC_CADM_CFG_PORT0_END + 1)
#define XC_CADM_CFG_PORT1_END        (XC_CADM_CFG_PORT1_START + XC_MAX_XC_CADM_PORT - 1)

#define XC_CADM_CFG_PORT2_START      (XC_CADM_CFG_PORT1_END + 1)
#define XC_CADM_CFG_PORT2_END        (XC_CADM_CFG_PORT2_START + XC_MAX_XC_CADM_PORT - 1)

#define XC_CADM_CFG_PORT3_START      (XC_CADM_CFG_PORT2_END + 1)
#define XC_CADM_CFG_PORT3_END        (XC_CADM_CFG_PORT3_START + XC_MAX_XC_CADM_PORT - 1)

#define XC_CADM_CFG_PORT4_START      (XC_CADM_CFG_PORT3_END + 1)
#define XC_CADM_CFG_PORT4_END        (XC_CADM_CFG_PORT4_START + XC_MAX_XC_CADM_PORT - 1)

#define XC_CADM_CFG_PORT5_START      (XC_CADM_CFG_PORT4_END + 1)
#define XC_CADM_CFG_PORT5_END        (XC_CADM_CFG_PORT5_START + XC_MAX_XC_CADM_PORT - 1)

#define XC_CADM_CFG_PORT6_START      (XC_CADM_CFG_PORT5_END + 1)
#define XC_CADM_CFG_PORT6_END        (XC_CADM_CFG_PORT6_START + XC_MAX_XC_CADM_PORT - 1)

#define XC_CADM_CFG_PORT7_START      (XC_CADM_CFG_PORT6_END + 1)
#define XC_CADM_CFG_PORT7_END        (XC_CADM_CFG_PORT7_START + XC_MAX_XC_CADM_PORT - 1)


#define XC_CADM_CFG_EXPRESS0_START   (XC_CADM_CFG_PORT7_END + 1)
#define XC_CADM_CFG_EXPRESS0_END     (XC_CADM_CFG_EXPRESS0_START + XC_MAX_XC_CADM_EXPRESS - 1)

#define XC_CADM_CFG_EXPRESS1_START   (XC_CADM_CFG_EXPRESS0_END + 1)
#define XC_CADM_CFG_EXPRESS1_END     (XC_CADM_CFG_EXPRESS1_START + XC_MAX_XC_CADM_EXPRESS - 1)

#define XC_CADM_CFG_EXPRESS2_START   (XC_CADM_CFG_EXPRESS1_END + 1)
#define XC_CADM_CFG_EXPRESS2_END     (XC_CADM_CFG_EXPRESS2_START + XC_MAX_XC_CADM_EXPRESS - 1)

#define XC_CADM_CFG_EXPRESS3_START   (XC_CADM_CFG_EXPRESS2_END + 1)
#define XC_CADM_CFG_EXPRESS3_END     (XC_CADM_CFG_EXPRESS3_START + XC_MAX_XC_CADM_EXPRESS - 1)

#define XC_CADM_CFG_EXPRESS4_START   (XC_CADM_CFG_EXPRESS3_END + 1)
#define XC_CADM_CFG_EXPRESS4_END     (XC_CADM_CFG_EXPRESS4_START + XC_MAX_XC_CADM_EXPRESS - 1)

#define XC_CADM_CFG_EXPRESS5_START   (XC_CADM_CFG_EXPRESS4_END + 1)
#define XC_CADM_CFG_EXPRESS5_END     (XC_CADM_CFG_EXPRESS5_START + XC_MAX_XC_CADM_EXPRESS - 1)

#define XC_CADM_CFG_EXPRESS6_START   (XC_CADM_CFG_EXPRESS5_END + 1)
#define XC_CADM_CFG_EXPRESS6_END     (XC_CADM_CFG_EXPRESS6_START + XC_MAX_XC_CADM_EXPRESS - 1)


#define XC_CADM_CFG_AUXILIARY0_START (XC_CADM_CFG_EXPRESS6_END + 1)
#define XC_CADM_CFG_AUXILIARY0_END   (XC_CADM_CFG_AUXILIARY0_START + XC_MAX_XC_CADM_AUXILIARY - 1)

#define XC_CADM_CFG_AUXILIARY1_START (XC_CADM_CFG_AUXILIARY0_END + 1)
#define XC_CADM_CFG_AUXILIARY1_END   (XC_CADM_CFG_AUXILIARY1_START + XC_MAX_XC_CADM_AUXILIARY - 1)



// Identifiers for each CADM facility
//
#define XC_CADM_LINE_FACILITY_ID       (1)    // DWDM Line

#define XC_CADM_PORT0_FACILITY_ID      (2)    // A/D 1
#define XC_CADM_PORT1_FACILITY_ID      (3)
#define XC_CADM_PORT2_FACILITY_ID      (4)
#define XC_CADM_PORT3_FACILITY_ID      (5)
#define XC_CADM_PORT4_FACILITY_ID      (6)
#define XC_CADM_PORT5_FACILITY_ID      (7)
#define XC_CADM_PORT6_FACILITY_ID      (8)
#define XC_CADM_PORT7_FACILITY_ID      (9)    // A/D 8

#define XC_CADM_EXPRESS0_FACILITY_ID   (10)   // EXP1
#define XC_CADM_EXPRESS1_FACILITY_ID   (11)   // EXP2
#define XC_CADM_EXPRESS2_FACILITY_ID   (12)   // EXP3/AUX3
#define XC_CADM_EXPRESS3_FACILITY_ID   (13)   // Future EXP expansion begin
#define XC_CADM_EXPRESS4_FACILITY_ID   (14)
#define XC_CADM_EXPRESS5_FACILITY_ID   (15)
#define XC_CADM_EXPRESS6_FACILITY_ID   (16)   // Future EXP expansion end

#define XC_CADM_AUXILIARY0_FACILITY_ID (17)   // AUX 1
#define XC_CADM_AUXILIARY1_FACILITY_ID (18)   // AUX 2



// Constant Array for use with indexing into
// the AG Config Region. AG will
// use 1 based Ports when using this method.
// Therefore the array starts with zero.
// *** Must be kept in same order as CADM facility identifiers ***
const int CADMConfigMap[] = {0,
                             XC_CADM_CFG_LINE_START,
                             XC_CADM_CFG_PORT0_START,
                             XC_CADM_CFG_PORT1_START,
                             XC_CADM_CFG_PORT2_START,
                             XC_CADM_CFG_PORT3_START,
                             XC_CADM_CFG_PORT4_START,
                             XC_CADM_CFG_PORT5_START,
                             XC_CADM_CFG_PORT6_START,
                             XC_CADM_CFG_PORT7_START,
                             XC_CADM_CFG_EXPRESS0_START,
                             XC_CADM_CFG_EXPRESS1_START,
                             XC_CADM_CFG_EXPRESS2_START,
                             XC_CADM_CFG_EXPRESS3_START,
                             XC_CADM_CFG_EXPRESS4_START,
                             XC_CADM_CFG_EXPRESS4_START,
                             XC_CADM_CFG_EXPRESS6_START,
                             XC_CADM_CFG_AUXILIARY0_START,
                             XC_CADM_CFG_AUXILIARY1_START};
//------------------ Start of the Roll Service definitions ----------------------    
typedef struct conn_elements {
    UINT8   srcFacPort;
    UINT8   srcFacChan;
    UINT8   dstFacPort;
    UINT8   dstFacChan;
} TSXC_ConnectElements;

typedef union	connection {
 	UINT32 			        aCKey;
	TSXC_ConnectElements	aCE; 
} TSXC_Connection;

//-------------------------------------------------------------------------------
typedef struct roll_info {
    UINT8   OldSrcShelf;
    UINT8   OldSrcSlot;
    UINT8   NewSrcShelf;    
    UINT8   NewSrcSlot;
    UINT8   RemoteDstSlot;
    bool    IsProtected;
    bool    IsResponseExpected;
    UINT8   RemoteSrcSlot;
    UINT16  RemoteSrcChan;                     
    UINT16  DestChanIndex;                    
    UINT16  MulticastId;         
} TSXC_Roll_Info;

//--------------------------------------------------------------------------------------------------	
enum TSXC_RollCmdFsmState
{
   ROLL_CMD_IDLE=0x0100,
   ROLL_CMD_INPROGRESS,
   ROLL_CMD_COMPLETE,
   ROLL_CMD_STATE_INVALID
};

//--- Roll Command/Response
#define ROLL_CMD_NOREQ      (0x100)
#define ROLL_CMD_REQ        (0x101)
#define ROLL_RES_NONE       (0x102)
#define ROLL_RES_DONE       (0x103)
#define ROLL_CMD_REQ_RMV    (0x104)
#define ROLL_CMD_REQ_ADD    (0x105) 
#define ROLL_CMD_REQ_ASQ    (0x106) 
#define ROLL_CMD_REQ_RSQ    (0x107)
   
//------------------ End of the Roll Service definitions ------------------------    

//--- Macro defines for the purpose of debug 
//--- and to displaying the execution time within a section of code when enabled

#define XCDEBUG_INFO(DBG_L,X) if ((myDebugLevel & DBG_L) != 0)\
                                fc_cout << X << endl
                                
#if (defined(__SIMULATION__) | defined(LINUX)) 

#define START_TIME(DBG_L)   if ((myDebugLevel & DBG_L) != 0)\
                                myTimeStart = PII_TickTimer::readTimer()

#define END_TIME(DBG_L)     if ((myDebugLevel & DBG_L) != 0)\
                                myTimeEnd = PII_TickTimer::readTimer()
                                
#define PRINT_TIME(DBG_L,X) if ((myDebugLevel & DBG_L) != 0)\
                                fc_cout << X << myTimeEnd - myTimeStart << " ms" << endl
#else
#include <CommonPlatforms/CardServices/BspCommon/TMButilities.h>
#define START_TIME(DBG_L)   if ((myDebugLevel & DBG_L) != 0)\
                                myTimeStart = TMBget_timestamp()

#define END_TIME(DBG_L)     if ((myDebugLevel & DBG_L) != 0)\
                                myTimeEnd = TMBget_timestamp()
                                
#define PRINT_TIME(DBG_L,X) if ((myDebugLevel & DBG_L) != 0)\
                                fc_cout << X << TMBusec_between(myTimeStart, myTimeEnd) << " us" << endl	
                      
#endif
//------------------ End of the Macro definitions ------------------------
 
  
#endif // TSXC_CROSSCONNECT_H
