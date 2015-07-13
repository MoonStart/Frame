#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_DEFINITIONS_INCLUDED
#define _INC_SP_DEFINITIONS_INCLUDED

#include "gdef.h"
#include "Blackboard/FC_BbKey.h"
#include <vector>
#include <list>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <ITS/ITS_Definitions.h>
#include "bits.h" 
class SP_ProtectionAction;
class SP_1plus1ProtectionAction;
class SP_DefectProcessorAction;
class ALM_AppIf;
class ITS_UpstreamRegion;
class SP_1plus1BaseApplication;
class CSM_CardConfigStatusRegion;
class SP_OptProtCfgAction;


//##ModelId=3BBC9B0C0287
typedef uint8 SP_K1Request;

const SP_K1Request SP_NO_REQUEST = 0;
// CLSR Requests
const SP_K1Request SP_CLSR_K1_LP_S   = 0xF;
const SP_K1Request SP_CLSR_K1_FS_S   = 0xE;
const SP_K1Request SP_CLSR_K1_FS_R   = 0xD;
const SP_K1Request SP_CLSR_K1_SF_S   = 0xC;
const SP_K1Request SP_CLSR_K1_SF_R   = 0xB;
const SP_K1Request SP_CLSR_K1_SD_P   = 0xA;
const SP_K1Request SP_CLSR_K1_SD_S   = 0x9;
const SP_K1Request SP_CLSR_K1_SD_R   = 0x8;
const SP_K1Request SP_CLSR_K1_MS_S   = 0x7;
const SP_K1Request SP_CLSR_K1_MS_R   = 0x6;
const SP_K1Request SP_CLSR_K1_WTR    = 0x5;
const SP_K1Request SP_CLSR_K1_EXER_S = 0x4;
const SP_K1Request SP_CLSR_K1_EXER_R = 0x3;
const SP_K1Request SP_CLSR_K1_RR_S   = 0x2;
const SP_K1Request SP_CLSR_K1_RR_R   = 0x1;
const SP_K1Request SP_CLSR_K1_NO_REQUEST  = SP_NO_REQUEST;
#define DISPLAY_SP_K1Request_CLSR(x) (\
	(x) == SP_CLSR_K1_LP_S       ? "SP_CLSR_K1_LP_S"       :\
	(x) == SP_CLSR_K1_FS_S       ? "SP_CLSR_K1_FS_S"       :\
	(x) == SP_CLSR_K1_FS_R       ? "SP_CLSR_K1_FS_R"       :\
	(x) == SP_CLSR_K1_SF_S       ? "SP_CLSR_K1_SF_S"       :\
	(x) == SP_CLSR_K1_SF_R       ? "SP_CLSR_K1_SF_R"       :\
	(x) == SP_CLSR_K1_SD_P       ? "SP_CLSR_K1_SD_P"       :\
	(x) == SP_CLSR_K1_SD_S       ? "SP_CLSR_K1_SD_S"       :\
	(x) == SP_CLSR_K1_SD_R       ? "SP_CLSR_K1_SD_R"       :\
	(x) == SP_CLSR_K1_MS_S       ? "SP_CLSR_K1_MS_S"       :\
	(x) == SP_CLSR_K1_MS_R       ? "SP_CLSR_K1_MS_R"       :\
	(x) == SP_CLSR_K1_WTR        ? "SP_CLSR_K1_WTR"        :\
	(x) == SP_CLSR_K1_EXER_S     ? "SP_CLSR_K1_EXER_S"     :\
	(x) == SP_CLSR_K1_EXER_R     ? "SP_CLSR_K1_EXER_R"     :\
	(x) == SP_CLSR_K1_RR_S       ? "SP_CLSR_K1_RR_S"       :\
	(x) == SP_CLSR_K1_RR_R       ? "SP_CLSR_K1_RR_R"       :\
	(x) == SP_CLSR_K1_NO_REQUEST ? "SP_CLSR_K1_NO_REQUEST" :\
	"UNKNOWN ERROR")


// 1+1 Requests
const SP_K1Request SP_1PLUS1_K1_LP   = 0xF;
const SP_K1Request SP_1PLUS1_K1_FS   = 0xE;
const SP_K1Request SP_1PLUS1_K1_SF_H = 0xD; //SDH
const SP_K1Request SP_1PLUS1_K1_SF_L = 0xC; //SONET
const SP_K1Request SP_1PLUS1_K1_SD_H = 0xB; //SDH
const SP_K1Request SP_1PLUS1_K1_SD_L = 0xA; //SONET
const SP_K1Request SP_1PLUS1_K1_MS   = 0x8;
const SP_K1Request SP_1PLUS1_K1_WTR  = 0x6;
const SP_K1Request SP_1PLUS1_K1_EXER = 0x4;
const SP_K1Request SP_1PLUS1_K1_RR   = 0x2;
const SP_K1Request SP_1PLUS1_K1_DO_NOT_REVERT = 0x1;
const SP_K1Request SP_1PLUS1_K1_NO_REQUEST  = SP_NO_REQUEST;
#define DISPLAY_SP_K1Request_1PLUS1(x) (\
	(x) == SP_1PLUS1_K1_LP            ? "SP_1PLUS1_K1_LP"            :\
	(x) == SP_1PLUS1_K1_FS            ? "SP_1PLUS1_K1_FS"            :\
	(x) == SP_1PLUS1_K1_SF_H          ? "SP_1PLUS1_K1_SF_H"          :\
	(x) == SP_1PLUS1_K1_SF_L          ? "SP_1PLUS1_K1_SF_L"          :\
	(x) == SP_1PLUS1_K1_SD_H          ? "SP_1PLUS1_K1_SD_H"          :\
	(x) == SP_1PLUS1_K1_SD_L          ? "SP_1PLUS1_K1_SD_L"          :\
	(x) == SP_1PLUS1_K1_MS            ? "SP_1PLUS1_K1_MS"            :\
	(x) == SP_1PLUS1_K1_WTR           ? "SP_1PLUS1_K1_WTR"           :\
	(x) == SP_1PLUS1_K1_EXER          ? "SP_1PLUS1_K1_EXER"          :\
	(x) == SP_1PLUS1_K1_RR            ? "SP_1PLUS1_K1_RR"            :\
	(x) == SP_1PLUS1_K1_DO_NOT_REVERT ? "SP_1PLUS1_K1_DO_NOT_REVERT" :\
	(x) == SP_1PLUS1_K1_NO_REQUEST    ? "SP_1PLUS1_K1_NO_REQUEST"    :\
	"UNKNOWN ERROR")

//CLSR Destination :indicates if a request is destined to myself or to another node.
//##ModelId=3BBC9B0C0331
typedef bool SP_Destination;
const SP_Destination SP_DESTINED_TO_MYSELF = 0;
const SP_Destination SP_DESTINED_TO_ANOTHER = 1;
#define DISPLAY_SP_Destination(x) (\
	(x) == SP_DESTINED_TO_ANOTHER ? "SP_DESTINED_TO_ANOTHER" : "SP_DESTINED_TO_MYSELF")

//CLSR request path: long or short.
//##ModelId=3BBC9B0D0008
typedef bool SP_ClsrPath;
const SP_ClsrPath SP_CLSR_LONG_PATH = 1;
const SP_ClsrPath SP_CLSR_SHORT_PATH = 0;
#define DISPLAY_SP_ClsrPath(x) (\
	(x) == SP_CLSR_LONG_PATH ? "SP_CLSR_LONG_PATH" : "SP_CLSR_SHORT_PATH")

//CLSR request origin.
//##ModelId=3BBC9B0D00BC
typedef uint8 SP_RequestOrigin;
const SP_RequestOrigin SP_LOCAL_DEFECT = 0;
const SP_RequestOrigin SP_EXTERNAL_COMMAND = 1;
const SP_RequestOrigin SP_KBYTES_REQUEST = 2;
#define DISPLAY_SP_RequestOrigin(x) (\
	(x) == SP_LOCAL_DEFECT     ? "SP_LOCAL_DEFECT"     :\
	(x) == SP_EXTERNAL_COMMAND ? "SP_EXTERNAL_COMMAND" :\
	(x) == SP_KBYTES_REQUEST   ? "SP_KBYTES_REQUEST"   :\
	"UNKNOWN ERROR")


//##ModelId=3BBC9B0D0170
typedef uint8 SP_Status;

// CLSR Status
const SP_Status SP_CLSR_IDLE             = 0x0;
const SP_Status SP_CLSR_BRIDGED          = 0x1;
const SP_Status SP_CLSR_BRIDGED_SWITCHED = 0x2;
const SP_Status SP_CLSR_EXTRA_TRAFFIC    = 0x3;
const SP_Status SP_CLSR_RDI_L            = 0x6;
const SP_Status SP_CLSR_AIS_L            = 0x7;
#define DISPLAY_SP_Status_CLSR(x) (\
	(x) == SP_CLSR_IDLE             ? "SP_CLSR_IDLE"             :\
	(x) == SP_CLSR_BRIDGED          ? "SP_CLSR_BRIDGED"          :\
	(x) == SP_CLSR_BRIDGED_SWITCHED ? "SP_CLSR_BRIDGED_SWITCHED" :\
	(x) == SP_CLSR_EXTRA_TRAFFIC    ? "SP_CLSR_EXTRA_TRAFFIC"    :\
	(x) == SP_CLSR_RDI_L            ? "SP_CLSR_RDI_L"            :\
	(x) == SP_CLSR_AIS_L            ? "SP_CLSR_AIS_L"            :\
	"UNKNOWN ERROR")

// 1+1 Status
const SP_Status SP_1PLUS1_UNIDIR = 0x4;
const SP_Status SP_1PLUS1_BIDIR  = 0x5;
const SP_Status SP_1PLUS1_RDI_L  = 0x6;
const SP_Status SP_1PLUS1_AIS_L  = 0x7;
#define DISPLAY_SP_Status_1PLUS1(x) (\
	(x) == SP_1PLUS1_UNIDIR ? "SP_1PLUS1_UNIDIR" :\
	(x) == SP_1PLUS1_BIDIR  ? "SP_1PLUS1_BIDIR"  :\
	(x) == SP_1PLUS1_RDI_L  ? "SP_1PLUS1_RDI_L"  :\
	(x) == SP_1PLUS1_AIS_L  ? "SP_1PLUS1_AIS_L"  :\
	"UNKNOWN ERROR")

const uint32 SP_MAX_FSM_ITERATION_COUNT = 10;
const uint32 SP_NB_OF_STS48_IN_OC192 = 4;
const uint32 SP_MAX_NUMBER_SQUELCH_TABLE_ITEMS = SP_NB_OF_STS48_IN_OC192;

#define SHELF_MODULE_PORT(facility) facility.GetShelfID(), facility.GetModuleID(), facility.GetPortID()

// bb keys
extern const FC_BbKey SP_RESULT_EXTENSION_KEY;

extern const FC_BbKey SP_1PLUS1_CONFIG_KEY;
extern const FC_BbKey SP_1PLUS1_STATUS_KEY;
extern const FC_BbKey SP_1PLUS1_COMMAND_KEY;
extern const FC_BbKey SP_1PLUS1_COMMAND_KEY_RESULT;
extern const FC_BbKey SP_1PLUS1_ADMIN_MANAGER;

extern const FC_BbKey SP_CLSR_CONFIG_KEY;
extern const FC_BbKey SP_CLSR_STATUS_KEY;
extern const FC_BbKey SP_CLSR_WEST_COMMAND_KEY;
extern const FC_BbKey SP_CLSR_EAST_COMMAND_KEY;
extern const FC_BbKey SP_CLSR_WEST_COMMAND_KEY_RESULT;
extern const FC_BbKey SP_CLSR_EAST_COMMAND_KEY_RESULT;
extern const FC_BbKey SP_CLSR_ADMIN_MANAGER;
extern const FC_BbKey SP_APP_READY_STATUS_KEY;
extern const FC_BbKey SP_DEFECTS_KEY;
extern const FC_BbKey SP_ALT_DEFECTS_W_KEY;
extern const FC_BbKey SP_ALT_DEFECTS_P_KEY;
extern const FC_BbKey SP_TIMING_MODE_KEY;
extern const FC_BbKey SP_TIMING_RSCONFIG_KEY;

// run reason
const unsigned SP_REASON_BASE                       = 0x8000; 
const unsigned SP_SWITCHING_COMMAND_REASON          = SP_REASON_BASE + 1;
const unsigned SP_SWITCHING_COMMAND_REASON_IMMEDIAT = SP_REASON_BASE + 2;
const unsigned SP_DEFECT_GLITCH_REASON              = SP_REASON_BASE + 3;
const unsigned SP_CONFIG_REFRESH_REASON             = SP_REASON_BASE + 4;
const unsigned SP_CONFIG_REFRESH_REASON_IMMEDIAT    = SP_REASON_BASE + 5;
const unsigned SP_SYNCHRONIZATION_REASON            = SP_REASON_BASE + 6;
const unsigned SP_DEFECT_REASON_COMMIT              = SP_REASON_BASE + 7;
const unsigned SP_DEFECT_REASON_NO_COMMIT           = SP_REASON_BASE + 8;

//layer signal protect is protecting
//##ModelId=3BBC9B0D0170
typedef uint8 SP_ProtectionLayer;

const SP_ProtectionLayer SP_MS           = 0x0;
const SP_ProtectionLayer SP_HOP          = 0x1;
const SP_ProtectionLayer SP_VCG          = 0x2;
const SP_ProtectionLayer SP_SYNC         = 0x3;
const SP_ProtectionLayer SP_ODU          = 0x4;
const SP_ProtectionLayer SP_OPT          = 0x5;
#define DISPLAY_SP_ProtectionLayer(x) (\
	(x) == SP_MS                ? "SP_MS"             :\
	(x) == SP_HOP               ? "SP_HOP"            :\
	(x) == SP_VCG               ? "SP_VCG"            :\
	(x) == SP_SYNC              ? "SP_SYNC"           :\
	(x) == SP_ODU               ? "SP_ODU"            :\
    (x) == SP_OPT               ? "SP_OPT"            :\
	"UNKNOWN ERROR")
    
//typedefs for collections of actions   
typedef vector<SP_ProtectionAction*> SP_ProtectionActions;
typedef vector<SP_1plus1ProtectionAction*> SP_1plus1ProtectionActions;
typedef vector<SP_DefectProcessorAction*> SP_DefectProcessorActions;
typedef vector<ALM_AppIf*> SP_AlmAppIfCollection;
typedef vector<ITS_ConfigRegionOnTrn*> SP_ITSConfigRegionCollection;
typedef vector<ITS_UpstreamRegion*> SP_ITSUpstreamRegionCollection;
typedef vector<SP_1plus1BaseApplication*> SP_1plus1ProtectionApps;
typedef vector<uint16> SP_HopCollection;
typedef list<SP_ProtectionAction*> ListOfProtectionActions;
typedef vector<CT_AdministrativeConfigType> SP_CardAdminstateCollection;
typedef vector<CSM_CardConfigStatusRegion*> SP_CSMCardConfigRegionCollection;
typedef vector<SP_OptProtCfgAction*> SP_OptProtCfgActions;

const CT_FAC_RxSsm SP_FREE_RUN_SSM = CT_RxSsm_ST3; //Stratum 3
const CT_FAC_RxSsm SP_SDH_FREE_RUN_SSM = CT_RxSsm_SEC;

// HOP consts
typedef uint16 SP_NumberOfHops;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_OC3   = 3;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_OC12  = 12;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_OC48  = 48;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_OC192 = 192;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_GBEP = 22;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_HOP  = 1;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_STS1  = 1;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_STS3C  = 3;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_STS12C  = 12;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_STS48C  = 48;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_IN_STS192C  = 192;
const SP_NumberOfHops SP_NUMBER_OF_HOPS_UKNOWN  = 0;


//number of protection schemes that can exist
//on a card
//SMTM
const uint32 SP_NUM_NODES_PORT_SMTM = 10;
const uint32 SP_NUM_PORT_PROT_SMTM = 192 + SP_NUM_NODES_PORT_SMTM;
const uint32 SP_NUM_LINE_PROT_SMTM = 192;
const uint32 SP_NUM_TIMING_SMTM = 1;
const uint32 SP_PORT_NODE_BASE_SMTM = 192;
//OPSM
const uint32 SP_NUM_LINE_PROT_OPSM = 4;
//RAM
const uint32 SP_NUM_LINE_PROT_RAM = 1;
//AIM
const uint32 SP_NUM_LINE_PROT_AIM = 4;
//SSM
const uint32 SP_NUM_NODES_PORT_SSM = 14; /*13 real ports +1 ttp port*/
const uint32 SP_NUM_PORT_PROT_SSM = 192 + SP_NUM_NODES_PORT_SSM;
const uint32 SP_NUM_LINE_PROT_SSM = 192;
const uint32 SP_NUM_TIMING_SSM = 1;
const uint32 SP_PORT_NODE_BASE_SSM = 192;
//OTNM
const uint32 SP_NUM_LINE_PROT_OTNM = 1;
const uint32 SP_NUM_TIMING_OTNM = 1;
const uint32 SP_NUM_NODES_PORT_OTNM = 9;
const uint32 SP_PORT_NODE_BASE_OTNM = 0;
const uint32 SP_NUM_PORT_PROT_OTNM = SP_NUM_NODES_PORT_OTNM;
//FGTM
const uint32 SP_NUM_NODES_PORT_FGTM = 1;
const uint32 SP_PORT_NODE_BASE_FGTM = 0;
const uint32 SP_NUM_PORT_PROT_FGTM = SP_NUM_NODES_PORT_FGTM;
//FGTME
const uint32 SP_NUM_NODES_PORT_FGTME = 1;
const uint32 SP_PORT_NODE_BASE_FGTME = 0;
const uint32 SP_NUM_PORT_PROT_FGTME = SP_NUM_NODES_PORT_FGTME;
//FGTMM
const uint32 SP_NUM_NODES_PORT_FGTMM = 4;
const uint32 SP_PORT_NODE_BASE_FGTMM = 0;
const uint32 SP_NUM_PORT_PROT_FGTMM = SP_NUM_NODES_PORT_FGTMM;
//HDTG
const uint32 SP_NUM_NODES_PORT_HDTG = 10;
const uint32 SP_PORT_NODE_BASE_HDTG = 0;
const uint32 SP_NUM_PORT_PROT_HDTG  = SP_NUM_NODES_PORT_HDTG;
//HDTG2
const uint32 SP_NUM_NODES_PORT_HDTG2 = 16;
const uint32 SP_PORT_NODE_BASE_HDTG2 = 0;
const uint32 SP_NUM_PORT_PROT_HDTG2  = SP_NUM_NODES_PORT_HDTG2;
//SSM40
const uint32 SP_NUM_NODES_PORT_SSM40        = 20;
const uint32 SP_PORT_NODE_BASE_SSM40        = 32;
const uint32 SP_NUM_PORT_PROT_SSM40         = 32 + SP_NUM_NODES_PORT_SSM40; /*Max NUM SNC 32 ODU0 + 20 Y-cable*/
const uint32 SP_LOW_SPEED_PORT_OFFSET_SSM40 = 15;
const uint32 SP_NUM_TIMING_SSM40            = 1;
//FGSM
const uint32 SP_NUM_NODES_PORT_FGSM = 1;
const uint32 SP_PORT_NODE_BASE_FGSM = 0;
const uint32 SP_NUM_PORT_PROT_FGSM  = 32; /*Max Num SNC 32 ODU0 */
const uint32 SP_NUM_TIMING_FGSM     = 1;
//HGTM
const uint32 SP_NUM_NODES_PORT_HGTM = 1;
const uint32 SP_PORT_NODE_BASE_HGTM = 0;
const uint32 SP_NUM_PORT_PROT_HGTM = SP_NUM_NODES_PORT_HGTM;
//OMM
const uint32 SP_NUM_NODES_PORT_OMM        = 10;
const uint32 SP_PORT_NODE_BASE_OMM        = 16;
const uint32 SP_NUM_PORT_PROT_OMM         = 16 + SP_NUM_NODES_PORT_OMM; /*Max NUM SNC 16 ODU0 + 10 Y-cable*/
const uint32 SP_LOW_SPEED_PORT_OFFSET_OMM = 7;
//HGTMM
const uint32 SP_NUM_NODES_PORT_HGTMM = 12;
const uint32 SP_PORT_NODE_BASE_HGTMM = 0;
const uint32 SP_NUM_PORT_PROT_HGTMM  = SP_NUM_NODES_PORT_HGTMM;
//OSM
const uint32 SP_NUM_NODES_PORT_OSM        = 20;
const uint32 SP_PORT_NODE_BASE_OSM        = 160;
const uint32 SP_NUM_PORT_PROT_OSM         = 160 + SP_NUM_NODES_PORT_OSM; /*Max NUM SNC 160 ODUF/ODU0 + 20 Y-cable*/

//OSM1S
const uint32 SP_NUM_NODES_PORT_OSM1S        = 32;
const uint32 SP_PORT_NODE_BASE_OSM1S        = 128;
const uint32 SP_NUM_PORT_PROT_OSM1S         = 128 + SP_NUM_NODES_PORT_OSM1S; /*Max NUM SNC 128 ODUF/ODU0 + 32 Y-cable(for support Y-cable later)*/

//MAX #APS on port side
const uint32 SP_NUM_NODES_PORT_MAX = SP_NUM_NODES_PORT_SSM;

//number of objects in Signal Protect regions.
const uint32 SP_NUM_OBJECTS_LINE_PROT = 192;
const uint32 SP_NUM_OBJECTS_PORT_PROT = 192 + SP_NUM_NODES_PORT_MAX;
const uint32 SP_NUM_OBJECTS_TIMING_PROT = 1;

//max number of subapplications per shelf
const uint16 MAX_NUM_APPS_SHELF = 19;

//max slot # that support SPFAB based protection
const CT_SlotId SP_SPFAB_NUM_SMTM_SLOTS = 16;

//max number of opsm line side protection supported
const uint32 SP_MAX_NUM_LSP = 10;

const uint8 SP_MAX_ARR_DEFECT_PORT_COUNT = 20 + 2; /* max port facilities + 2 line facilities*/

//the side that signal protect is protecting
typedef uint8 SP_ProtectionSide;
const FC_Milliseconds SP_STATUS_COLLECTION_DELAY_DURATION = 100; //ms
const FC_Milliseconds SP_STATUS_COLLECTION_LONG_DELAY_DURATION = 10 *1000; //10 seconds

const SP_ProtectionSide SP_LINE           = 0x0;
const SP_ProtectionSide SP_PORT           = 0x1;
const SP_ProtectionSide SP_CARD           = 0x2;
#define DISPLAY_SP_ProtectionSide(x) (\
	(x) == SP_LINE                ? "SP_LINE"             :\
	(x) == SP_PORT                ? "SP_PORT"             :\
	(x) == SP_CARD                ? "SP_CARD"             :\
    "UNKNOWN ERROR")

typedef uint8 SP_AlarmReason;
const SP_AlarmReason SP_ESCALATION        = 0x0;
const SP_AlarmReason SP_PROTNA            = 0x1;
const SP_AlarmReason SP_ARC               = 0x2;

typedef uint8 SP_ResourceId;
const SP_ResourceId SP_RESOURCE_ID_DEFAULT = 0xFF;

const uint8 SP_MODULE_OOS_CSI = 50;
const uint8 SP_FAIL_CSI = 0;

typedef uint8 SP_TimingMode;
const SP_TimingMode SP_TMG_UNKNOWN  = 0x0;
const SP_TimingMode SP_TMG_MASTER   = 0x1;
const SP_TimingMode SP_TMG_SLAVE    = 0x2;
const SP_TimingMode SP_TMG_HOLD     = 0x3;

const uint8 SP_TIMING_MODE_MASK = 0xC0;
const uint8 SP_TIMING_MODE_SHIFT = 6;
const uint8 SP_CSI_SHIFT = 2;

typedef uint8 SP_TimingSelection;
const SP_TimingSelection SP_SEL_UNKNOWN  = 0x0;
const SP_TimingSelection SP_SEL_PRI      = 0x1;
const SP_TimingSelection SP_SEL_SEC      = 0x2;
const SP_TimingSelection SP_SEL_HOLD     = 0x3;

const uint8 SP_TIMING_SEL_MASK = SP_TIMING_MODE_MASK;
const uint8 SP_TIMING_SEL_SHIFT = SP_TIMING_MODE_SHIFT;

//Y CABLE MSG FORMAT
//8 bit
//Bit 0: Reserved (for laser state tx)
//Bit 1: Indicates SF-High
//Bit 2: Indicates SD
//Bits 3,4,5: User Command
//Bits 6-7: Unused
const uint8 SP_RESERVED_7     = 0x80;   
const uint8 SP_RESERVED_6     = 0x40;   
const uint8 SP_USR_CMD_2      = 0x20;   
const uint8 SP_USR_CMD_1      = 0x10;   
const uint8 SP_USR_CMD_0      = 0x8;   
const uint8 SP_AUTO_CMD_1     = 0x4;   
const uint8 SP_AUTO_CMD_0     = 0x2;   
const uint8 SP_LASER_STATE    = 0x1;

// bit field
const uint8 SP_USR_CMD  =  (SP_USR_CMD_2 | SP_USR_CMD_1 |
                            SP_USR_CMD_0);
const uint8 SP_AUTO_CMD = (SP_AUTO_CMD_1 | SP_AUTO_CMD_0);

const uint8 SP_AUTO_CMD_SHIFT = 1;
const uint8 SP_USER_CMD_SHIFT = 3;

//PQW MSG FORMAT
//16 bit
//Bit 0: (Valid/Invalid)
//Bit 1/2: AUTO CMD  --see y cable defines above
//Bit 3/4/5: User command -- see y cable defines above
//Bits 6-12 - Unused for now
//Bit 13/14/15 -- Reserved for general messaging
const uint16 SP_PQW_GEN_MSG_2      = 0x8000;
const uint16 SP_PQW_GEN_MSG_1      = 0x4000;
const uint16 SP_PQW_GEN_MSG_0      = 0x2000;
const uint16 SP_PQW_CLK_HOLD       = 0x80;
const uint16 SP_PQW_SRC_ENABLED    = 0x40;
const uint16 SP_PQW_USR_CMD_2      = 0x20;   
const uint16 SP_PQW_USR_CMD_1      = 0x10;   
const uint16 SP_PQW_USR_CMD_0      = 0x8;   
const uint16 SP_PQW_AUTO_CMD_1     = 0x4;   
const uint16 SP_PQW_AUTO_CMD_0     = 0x2;  
const uint16 SP_PQW_MSG_VALID      = 0x1;

const uint16 SP_PQW_USR_CMD  =  (SP_PQW_USR_CMD_2 | SP_PQW_USR_CMD_1 |
                                SP_PQW_USR_CMD_0);
const uint16 SP_PQW_AUTO_CMD = (SP_PQW_AUTO_CMD_1 | SP_PQW_AUTO_CMD_0);

const uint16 SP_PQW_AUTO_CMD_SHIFT = 1;
const uint16 SP_PQW_USER_CMD_SHIFT = 3;
const uint16 SP_PQW_SRC_ENAB_SHIFT = 6;
const uint16 SP_PQW_CLK_HOLD_SHIFT = 7;
const uint16 SP_GEN_MSG_SHIFT      = 13;
const uint16 SP_PQW_ALL_MASK = (SP_PQW_AUTO_CMD_1 | SP_PQW_AUTO_CMD_0 |
                                SP_PQW_USR_CMD_2 | SP_PQW_USR_CMD_1 |
                                SP_PQW_USR_CMD_0 | SP_PQW_MSG_VALID |
                                SP_PQW_SRC_ENABLED);
const uint16 SP_GEN_MSG_MASK = (SP_PQW_GEN_MSG_2 | SP_PQW_GEN_MSG_1 |
                                SP_PQW_GEN_MSG_0);

#define INPUT_SETS_CLK 0x0
#define INPUT_UNFILTERED 0x5
#define INPUT_MATE 0xFE
#define INPUT_DISCONNECT 0xFF


#define SP_MULTI_SHELF_TMG 0x1
#define SP_SINGLE_PAIRED_TMG 0x2

typedef enum SP_ArrDefectLayer_Enum
{
    Defect_Layer_OPT,
    Defect_Layer_OTU,
    Defect_Layer_ODU,
    Defect_Layer_RS,
    Defect_Layer_MS,
    Defect_Layer_NONE
} SP_ArrDefectLayer;

#endif /* _INC_SP_DEFINITIONS_INCLUDED */

