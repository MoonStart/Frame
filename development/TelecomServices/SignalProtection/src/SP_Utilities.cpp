// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_Utilities.h"
#include "../SP_Definitions.h"
#include <ErrorService/FC_Error.h>
#include <XC/TSXC_CrossConnect.h>
#include <TsPii/TSPII_SubApplication.h>

typedef struct slot_pairing_mapping_tbl_entry {
    CT_SlotId  slotId1;     
    CT_SlotId  slotId2;       
} SP_SLOT_PAIRING_MAPPING_ENTRY;

static SP_SLOT_PAIRING_MAPPING_ENTRY SP_UssPairMappingTbl[] =
{
   { SCARD_1,       SCARD_16 },
   { SCARD_2,       SCARD_15 },
   { SCARD_3,       SCARD_14 },
   { SCARD_4,       SCARD_13 },
   { SCARD_5,       SCARD_12 },
   { SCARD_6,       SCARD_11 },
   { SCARD_7,       SCARD_10 },
   { SCARD_8,       SCARD_9  }
};

const int SP_UssPairMappingTbl_Size = sizeof(SP_UssPairMappingTbl)/sizeof(SP_SLOT_PAIRING_MAPPING_ENTRY);

static SP_SLOT_PAIRING_MAPPING_ENTRY SP_NanoPairMappingTbl[] =
{
   { SCARD_1,       SCARD_4 },
   { SCARD_2,       SCARD_5 },
   { SCARD_3,       SCARD_6 }
};

const int SP_NanoPairMappingTbl_Size = sizeof(SP_NanoPairMappingTbl)/sizeof(SP_SLOT_PAIRING_MAPPING_ENTRY);

static SP_SLOT_PAIRING_MAPPING_ENTRY SP_HcssPairMappingTbl[] =
{
   { SCARD_2,       SCARD_12 },
   { SCARD_3,       SCARD_13 },
   { SCARD_4,       SCARD_14 },
   { SCARD_5,       SCARD_15 },
   { SCARD_6,       SCARD_16 },
   { SCARD_7,       SCARD_17 },
   { SCARD_8,       SCARD_18 }
};

const int SP_HcssPairMappingTbl_Size = sizeof(SP_HcssPairMappingTbl)/sizeof(SP_SLOT_PAIRING_MAPPING_ENTRY);

const FC_BbKey SP_RESULT_EXTENSION_KEY = "_RESULT";

const FC_BbKey SP_1PLUS1_CONFIG_KEY         = "SP_1PLUS1_CONFIG_KEY";
const FC_BbKey SP_1PLUS1_STATUS_KEY         = "SP_1PLUS1_STATUS_KEY";
const FC_BbKey SP_1PLUS1_COMMAND_KEY        = "SP_1PLUS1_COMMAND_KEY";
const FC_BbKey SP_1PLUS1_COMMAND_KEY_RESULT = "SP_1PLUS1_COMMAND_KEY_RESULT";
const FC_BbKey SP_1PLUS1_ADMIN_MANAGER      = "SP_1PLUS1_ADMIN_MANAGER";

const FC_BbKey SP_CLSR_CONFIG_KEY              = "SP_CLSR_CONFIG_KEY";
const FC_BbKey SP_CLSR_STATUS_KEY              = "SP_CLSR_STATUS_KEY";
const FC_BbKey SP_CLSR_WEST_COMMAND_KEY        = "SP_CLSR_WEST_COMMAND_KEY";
const FC_BbKey SP_CLSR_EAST_COMMAND_KEY        = "SP_CLSR_EAST_COMMAND_KEY";
const FC_BbKey SP_CLSR_WEST_COMMAND_KEY_RESULT = "SP_CLSR_WEST_COMMAND_KEY_RESULT";
const FC_BbKey SP_CLSR_EAST_COMMAND_KEY_RESULT = "SP_CLSR_EAST_COMMAND_KEY_RESULT";
const FC_BbKey SP_CLSR_ADMIN_MANAGER           = "SP_CLSR_ADMIN_MANAGER";
const FC_BbKey SP_APP_READY_STATUS_KEY         = "SP_APP_READY_STATUS_KEY";
const FC_BbKey SP_DEFECTS_KEY                  = "SP_DEFECTS_KEY";
const FC_BbKey SP_ALT_DEFECTS_W_KEY            = "SP_ALT_DEFECTS_W_KEY";
const FC_BbKey SP_ALT_DEFECTS_P_KEY            = "SP_ALT_DEFECTS_P_KEY";
const FC_BbKey SP_TIMING_MODE_KEY              = "SP_TIMING_MODE_KEY";
const FC_BbKey SP_TIMING_RSCONFIG_KEY          = "SP_TIMING_RSCONFIG_KEY";


CT_FacilitySubType GetImuxFacType(CT_FacilitySubType theFacType)
{
    CT_FacilitySubType result = FAC_SUBTYPE_UNKNOWN;
	switch (theFacType)
	{
	    case FAC_SUBTYPE_OC3:
		    result = FAC_SUBTYPE_OC3M;
		    break;
		case FAC_SUBTYPE_STM1:
			result = FAC_SUBTYPE_STM1M;
		    break;
		case FAC_SUBTYPE_OC12:
			result = FAC_SUBTYPE_OC12M;
		    break;
		case FAC_SUBTYPE_STM4:
			result = FAC_SUBTYPE_STM4M;
		    break;
        case FAC_SUBTYPE_OC48:
			result = FAC_SUBTYPE_OC48M;
			break;
		case FAC_SUBTYPE_STM16:
			result = FAC_SUBTYPE_STM16M;
		    break;
		case FAC_SUBTYPE_OC192:
			result = FAC_SUBTYPE_OC192M;
			break;
        case FAC_SUBTYPE_STM64:
			result = FAC_SUBTYPE_STM64M;
			break;
		case FAC_SUBTYPE_OPTD:
		case FAC_SUBTYPE_OPTD3:
            result = FAC_SUBTYPE_OPTDM;
			break;
		case FAC_SUBTYPE_OCH_P:
            result = FAC_SUBTYPE_OCH_M;
			break;
		case FAC_SUBTYPE_STS1:
		case FAC_SUBTYPE_STS3C:
		case FAC_SUBTYPE_STS12C:
        case FAC_SUBTYPE_STS48C:
		case FAC_SUBTYPE_STS192C:
		case FAC_SUBTYPE_STS1CNV:
		case FAC_SUBTYPE_STS3CNV:
			result = theFacType; //return what was passed in. No conversion required
			break;
		default:
			//FC_THROW_ERROR(FC_RuntimeError,
            //          "SP_Utlities:GetImuxFacType: Invalid fac type passed in");
			break;
	}
    return result;
}


CT_IntfId GetImuxIntfIdFromPort(CT_IntfId thePortId, CT_SP_1plus1Type the1plus1Type, CT_CardFamily theFam)
{
	CT_IntfId port = CT_INTF_ID_UNKNOWN;

	//For port side UPSR, all ports match up to IMUX-P
	if (the1plus1Type == CT_SP_UPSR)
	{
		if (thePortId == CT_PORT_SIDE_0 ||
            thePortId == CT_PORT_SIDE_1 ||
            thePortId == CT_PORT_SIDE_2 ||
            thePortId == CT_PORT_SIDE_3 ||
            thePortId == CT_PORT_SIDE_4 ||
            thePortId == CT_PORT_SIDE_5 ||
            thePortId == CT_PORT_SIDE_6 ||
            thePortId == CT_PORT_SIDE_7 ||
            thePortId == CT_PORT_SIDE_8 ||
            thePortId == CT_PORT_SIDE_9 ||
			thePortId == CT_PORT_SIDE_10 ||
			thePortId == CT_PORT_SIDE_11 ||
			thePortId == CT_PORT_SIDE_12 ||
            thePortId == CT_PORT_SIDE_13 ||
            thePortId == CT_PORT_SIDE_14 ||
            thePortId == CT_PORT_SIDE_15 ||
            thePortId == CT_PORT_SIDE_32)
		{
			return CT_LINE_SIDE_4;
		}
	}

	if (theFam == CARD_FAM_SSM)
	{
	    switch (thePortId) 
		{
	    case CT_PORT_SIDE_0:
	        port = CT_PORT_SIDE_13;
		    break;
        case CT_PORT_SIDE_1:
			port = CT_PORT_SIDE_14;
		    break;
        case CT_PORT_SIDE_2:
			port = CT_PORT_SIDE_15;
		    break;
        case CT_PORT_SIDE_3:
			port = CT_PORT_SIDE_16;
		    break;
        case CT_PORT_SIDE_4:
			port = CT_PORT_SIDE_17;
		    break;
	    case CT_PORT_SIDE_5:
			port = CT_PORT_SIDE_18;
		    break;
        case CT_PORT_SIDE_6:
			port = CT_PORT_SIDE_19;
		    break;
	    case CT_PORT_SIDE_7:
			port = CT_PORT_SIDE_20;
			break;
		case CT_PORT_SIDE_8:
			port = CT_PORT_SIDE_21;
			break;
		case CT_PORT_SIDE_9:
			port = CT_PORT_SIDE_22;
			break;
		case CT_PORT_SIDE_10:
			port = CT_PORT_SIDE_23;
			break;
		case CT_PORT_SIDE_11:
			port = CT_PORT_SIDE_24;
			break;
		case CT_PORT_SIDE_12:
			port = CT_PORT_SIDE_25;
			break;
		case CT_LINE_SIDE_0:
            port = CT_LINE_SIDE_3;
			break;
		case CT_LINE_SIDE_1:
			port = CT_LINE_SIDE_2;
			break;
		case CT_LINE_SIDE_4:
			port = CT_LINE_SIDE_4; //IMUX port intfid is itself
			break;
		default: //unknown protection scheme
			//FC_THROW_ERROR(FC_RuntimeError,
            //          "SP_Utilities::GetImuxIntfIdFromPort: Invalid port passed in");
			break;
		}
	}
	else
	{
	    switch (thePortId) 
		{
	    case CT_PORT_SIDE_0:
	        port = CT_PORT_SIDE_10;
		    break;
        case CT_PORT_SIDE_1:
			port = CT_PORT_SIDE_11;
		    break;
        case CT_PORT_SIDE_2:
			port = CT_PORT_SIDE_12;
		    break;
        case CT_PORT_SIDE_3:
			port = CT_PORT_SIDE_13;
		    break;
        case CT_PORT_SIDE_4:
			port = CT_PORT_SIDE_14;
		    break;
	    case CT_PORT_SIDE_5:
			port = CT_PORT_SIDE_15;
		    break;
        case CT_PORT_SIDE_6:
			port = CT_PORT_SIDE_16;
		    break;
	    case CT_PORT_SIDE_7:
			port = CT_PORT_SIDE_17;
			break;
		case CT_PORT_SIDE_8:
			port = CT_PORT_SIDE_18;
			break;
		case CT_PORT_SIDE_9:
			port = CT_PORT_SIDE_19;
			break;
		case CT_LINE_SIDE_0:
            port = CT_LINE_SIDE_3;
			break;
		case CT_LINE_SIDE_1:
			port = CT_LINE_SIDE_2;
			break;
		case CT_LINE_SIDE_4:
			port = CT_LINE_SIDE_4; //IMUX port intfid is itself
			break;
		default: //unknown protection scheme
			//FC_THROW_ERROR(FC_RuntimeError,
            //          "SP_Utilities::GetImuxIntfIdFromPort: Invalid port passed in");
			break;
		}
	}

	return port;

}

/*
//Get AM mappings from CT_IntfId
void GetAMMappingFromIntfId(CT_DirectionFlag * thePortType, int * thePort, CT_IntfId theIntfId)
{
	
	switch (theIntfId)
	{
		case CT_LINE_SIDE_0:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 0;
		    break;
		case CT_LINE_SIDE_1:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 1;
			break;
		case CT_LINE_SIDE_2:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 2;
			break;
		case CT_LINE_SIDE_3:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 3;
			break;
		case CT_LINE_SIDE_4:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 4;
			break;
		case CT_LINE_SIDE_5:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 5;
			break;
		case CT_LINE_SIDE_6:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 6;
			break;
		case CT_LINE_SIDE_7:
			*thePortType = CT_DIR_CARD_LINE;
			*thePort = 7;
			break;

		//port interfaces
		case CT_PORT_SIDE_0:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 0;
			break;
		case CT_PORT_SIDE_1:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 1;
			break;
		case CT_PORT_SIDE_2:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 2;
			break;
		case CT_PORT_SIDE_3:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 3;
			break;
		case CT_PORT_SIDE_4:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 4;
			break;
		case CT_PORT_SIDE_5:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 5;
			break;
		case CT_PORT_SIDE_6:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 6;
			break;
		case CT_PORT_SIDE_7:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 7;
			break;
		case CT_PORT_SIDE_8:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 8;
			break;
		case CT_PORT_SIDE_9:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 9;
			break;
		case CT_PORT_SIDE_10:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 10;
			break;
		case CT_PORT_SIDE_11:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 11;
			break;
		case CT_PORT_SIDE_12:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 12;
			break;
		case CT_PORT_SIDE_13:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 13;
			break;
		case CT_PORT_SIDE_14:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 14;
			break;
		case CT_PORT_SIDE_15:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 15;
			break;
		case CT_PORT_SIDE_16:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 16;
			break;
		case CT_PORT_SIDE_17:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 17;
			break;
		case CT_PORT_SIDE_18:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 18;
			break;
		case CT_PORT_SIDE_19:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 19;
			break;
		case CT_PORT_SIDE_20:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 20;
			break;
		case CT_PORT_SIDE_21:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 21;
			break;
		case CT_PORT_SIDE_22:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 22;
			break;
		case CT_PORT_SIDE_23:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 23;
			break;
		case CT_PORT_SIDE_24:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 24;
			break;
		case CT_PORT_SIDE_25:
			*thePortType = CT_DIR_CARD_PORT;
			*thePort = 25;
			break;
		default:
		    FC_THROW_ERROR(FC_SWError, "Unknown Interface Id");
			break;
	}
}
*/
void GetXConnTypeFromPortType(CT_XC_ConnectType * theConnType, CT_FacilitySubType thePortType)
{
	switch(thePortType)
	{
		case FAC_SUBTYPE_OC3:
		case FAC_SUBTYPE_STM1:
			*theConnType = CT_XC_TYPE_OC3M;
			break;
	    case FAC_SUBTYPE_OC12:
		case FAC_SUBTYPE_STM4:
		    *theConnType = CT_XC_TYPE_OC12M;
			break;
		case FAC_SUBTYPE_OC48:
		case FAC_SUBTYPE_STM16:
			*theConnType = CT_XC_TYPE_OC48M;
			break;
		case FAC_SUBTYPE_OC192:
		case FAC_SUBTYPE_STM64:
			*theConnType = CT_XC_TYPE_OC192M;
			break;
		case FAC_SUBTYPE_OPTD:
            *theConnType = CT_XC_TYPE_OPTD1M;
			break;
		case FAC_SUBTYPE_OPTD3:
			*theConnType = CT_XC_TYPE_OPTD3M;
			break;
		case FAC_SUBTYPE_OCH_P:
			*theConnType = CT_XC_TYPE_OCHM;
			break;
		default:
			break;
	}
}

CT_TEL_SignalType GetSignalType(CT_FacilitySubType theFacType)
{
	CT_TEL_SignalType theSignalType = CT_TEL_SIGNAL_UNKNOWN;
	switch (theFacType)
	{
	    case FAC_SUBTYPE_OC3M:
		case FAC_SUBTYPE_STM1M:
		    theSignalType = CT_TEL_SIGNAL_OC3M;
		    break;
		case FAC_SUBTYPE_OC12M:
		case FAC_SUBTYPE_STM4M:
			theSignalType = CT_TEL_SIGNAL_OC12M;
		    break;
		case FAC_SUBTYPE_OC48M:
		case FAC_SUBTYPE_STM16M:
			theSignalType = CT_TEL_SIGNAL_OC48M;
			break;
		case FAC_SUBTYPE_OC192M:
		case FAC_SUBTYPE_STM64M:
			theSignalType = CT_TEL_SIGNAL_OC192M;
			break;
		case FAC_SUBTYPE_OPTDM:
            theSignalType = CT_TEL_SIGNAL_OPTDM;
			break;
		case FAC_SUBTYPE_OCH_M:
            theSignalType = CT_TEL_SIGNAL_OTU2;
			break;
		default:
		    FC_THROW_ERROR(FC_RuntimeError,
                      "SP_Utilities::GetSignalType: Invalid signal type passed in");
			break;
	}
	return theSignalType;
}

CT_FAC_RxSsm GetFreeRunSsm (CT_TEL_FacilityStandard theFacStandard)
{
	CT_FAC_RxSsm theSsm = SP_FREE_RUN_SSM; //Assume SONET by default
	switch(theFacStandard)
	{
	case CT_TEL_SDH:
		theSsm = SP_SDH_FREE_RUN_SSM;
		break;
	default:
		break;
	}

	return theSsm;
}

unsigned int GetTspiiIntfFromCTIntfId(CT_IntfId thePortId)
{
	unsigned int result = 0;
	switch (thePortId)
	{
	//port interfaces
	case CT_PORT_SIDE_0:
		result = TSPII_PORT_SIDE_0;
		break;
	case CT_PORT_SIDE_1:
		result = TSPII_PORT_SIDE_1;
		break;
	case CT_PORT_SIDE_2:
		result = TSPII_PORT_SIDE_2;
		break;
	case CT_PORT_SIDE_3:
		result = TSPII_PORT_SIDE_3;
		break;
	case CT_PORT_SIDE_4:
		result = TSPII_PORT_SIDE_4;
		break;
	case CT_PORT_SIDE_5:
		result = TSPII_PORT_SIDE_5;
		break;
    case CT_PORT_SIDE_6:
		result = TSPII_PORT_SIDE_6;
		break;
	case CT_PORT_SIDE_7:
		result = TSPII_PORT_SIDE_7;
		break;
	case CT_PORT_SIDE_8:
		result = TSPII_PORT_SIDE_8;
		break;
	case CT_PORT_SIDE_9:
		result = TSPII_PORT_SIDE_9;
		break;
	case CT_PORT_SIDE_10:
		result = TSPII_PORT_SIDE_10;
		break;
	case CT_PORT_SIDE_11:
		result = TSPII_PORT_SIDE_11;
		break;
	case CT_PORT_SIDE_12:
		result = TSPII_PORT_SIDE_12;
		break;
    case CT_PORT_SIDE_13:
		result = TSPII_PORT_SIDE_13;
		break;
    case CT_PORT_SIDE_14:
		result = TSPII_PORT_SIDE_14;
		break;
    case CT_PORT_SIDE_15:
		result = TSPII_PORT_SIDE_15;
		break;
    case CT_PORT_SIDE_32:
        result = TSPII_PORT_SIDE_26;
        break;

	//line interfaces
	case CT_LINE_SIDE_0:
		result = TSPII_LINE_SIDE_0;
		break;
	case CT_LINE_SIDE_1:
		result = TSPII_LINE_SIDE_1;
		break;
	case CT_LINE_SIDE_2:
		result = TSPII_LINE_SIDE_2;
		break;
	case CT_LINE_SIDE_3:
		result = TSPII_LINE_SIDE_3;
		break;
	case CT_LINE_SIDE_4:
		result = TSPII_LINE_SIDE_4;
		break;
	case CT_LINE_SIDE_5:
		result = TSPII_LINE_SIDE_5;
		break;
    case CT_LINE_SIDE_6:
		result = TSPII_LINE_SIDE_6;
		break;
	case CT_LINE_SIDE_7:
		result = TSPII_LINE_SIDE_7;
		break;
	case CT_LINE_SIDE_8:
		result = TSPII_LINE_SIDE_8;
		break;
	case CT_LINE_SIDE_9:
		result = TSPII_LINE_SIDE_9;
		break;
	case CT_LINE_SIDE_10:
		result = TSPII_LINE_SIDE_10;
		break;
	case CT_LINE_SIDE_11:
		result = TSPII_LINE_SIDE_11;
		break;
	case CT_LINE_SIDE_12:
		result = TSPII_LINE_SIDE_12;
		break;
	case CT_LINE_SIDE_13:
		result = TSPII_LINE_SIDE_13;
		break;
    case CT_LINE_SIDE_14:
		result = TSPII_LINE_SIDE_14;
		break;
	case CT_LINE_SIDE_15:
		result = TSPII_LINE_SIDE_15;
		break;
	default:
		FC_THROW_ERROR(FC_SWError, "Unknown Interface Id");
		break;
	}

	return result;

}

bool IsMFacility(CT_FacilitySubType theFacType)
{
	bool result = false;
	switch (theFacType)
	{
	case FAC_SUBTYPE_OC3M:
	case FAC_SUBTYPE_OC12M:
	case FAC_SUBTYPE_OC48M:
	case FAC_SUBTYPE_OPTDM:
	case FAC_SUBTYPE_STM1M:
	case FAC_SUBTYPE_STM4M:
	case FAC_SUBTYPE_STM16M:
	case FAC_SUBTYPE_OCH_M:
	case FAC_SUBTYPE_OC192M:
	case FAC_SUBTYPE_STM64M:
		result = true;
		break;
	default:
		break;
	}

	return result;
}

bool IsPortFacility(CT_IntfId thePortId)
{
	bool result = false;
	switch (thePortId)
	{
    case CT_PORT_SIDE_0:
    case CT_PORT_SIDE_1:
    case CT_PORT_SIDE_2:
    case CT_PORT_SIDE_3:
	case CT_PORT_SIDE_4:
    case CT_PORT_SIDE_5:
	case CT_PORT_SIDE_6:
	case CT_PORT_SIDE_7:
	case CT_PORT_SIDE_8:
	case CT_PORT_SIDE_9:
    case CT_PORT_SIDE_10:
	case CT_PORT_SIDE_11:
	case CT_PORT_SIDE_12:
	case CT_PORT_SIDE_13:
	case CT_PORT_SIDE_14:
	case CT_PORT_SIDE_15:
    case CT_PORT_SIDE_16:
    case CT_PORT_SIDE_17:
    case CT_PORT_SIDE_18:
    case CT_PORT_SIDE_19:
    case CT_PORT_SIDE_20:
    case CT_PORT_SIDE_21:
    case CT_PORT_SIDE_22:
    case CT_PORT_SIDE_23:
    case CT_PORT_SIDE_24:
    case CT_PORT_SIDE_25:
    case CT_PORT_SIDE_26:
    case CT_PORT_SIDE_27:
    case CT_PORT_SIDE_28:
    case CT_PORT_SIDE_29:
    case CT_PORT_SIDE_32:
    case CT_PORT_SIDE_85:
    case CT_PORT_SIDE_86:
    case CT_PORT_SIDE_87:
    case CT_PORT_SIDE_88:
		result = true;
		break;
	default:
		break;
	}

	return result;
}

bool IsLineFacility(CT_IntfId thePortId)
{
	bool result = false;
	switch (thePortId)
	{
	case CT_LINE_SIDE_0:
	case CT_LINE_SIDE_1:
    case CT_LINE_SIDE_2:
    case CT_LINE_SIDE_3:
    case CT_LINE_SIDE_4:
    case CT_LINE_SIDE_5:
    case CT_LINE_SIDE_6:
	case CT_LINE_SIDE_7:
	case CT_LINE_SIDE_8:
	case CT_LINE_SIDE_9:
	case CT_LINE_SIDE_10:
	case CT_LINE_SIDE_11:
	case CT_LINE_SIDE_12:
	case CT_LINE_SIDE_13:
	case CT_LINE_SIDE_14:
	case CT_LINE_SIDE_15:
		result = true;
		break;
	default:
		break;
	}

	return result;
}

int GetResourceIndex( CT_SP_1plus1Type the1plus1Type, SP_ProtectionSide theSide, CT_CardFamily theFam, CT_IntfId thePortId)
{
	int result = -1;
	
	if (the1plus1Type == CT_SP_LINEAR ||
        the1plus1Type == CT_SP_YCABLE ||
        the1plus1Type == CT_SP_DPRING ||
        the1plus1Type == CT_SP_OAPS)
	{
        if (theSide == SP_PORT)
		{
			int base = SP_PORT_NODE_BASE_SMTM;
            int offset = 0;
			if (theFam == SSM_FAM)
				base = SP_PORT_NODE_BASE_SSM;
            else if (theFam == OTNM_FAM)
                base = SP_PORT_NODE_BASE_OTNM;
            else if (theFam == FGTMM_FAM)
                base = SP_PORT_NODE_BASE_FGTMM;
            else if (theFam == HDTG_FAM)
                base = SP_PORT_NODE_BASE_HDTG;
            else if (theFam == HDTG2_FAM)
                base = SP_PORT_NODE_BASE_HDTG2;
            else if (theFam == HGTMM_FAM)
                base = SP_PORT_NODE_BASE_HGTMM;
            else if (theFam == SSM40_FAM)
                base = SP_PORT_NODE_BASE_SSM40;
			else if (theFam == FGSM_FAM)
				base = SP_PORT_NODE_BASE_FGSM;
            else if (theFam == OMM_FAM)
                base = SP_PORT_NODE_BASE_OMM;
            else if (theFam == OSM_FAM)
                base = SP_PORT_NODE_BASE_OSM;

            if (theFam == SSM40_FAM)
                offset = SP_LOW_SPEED_PORT_OFFSET_SSM40;
            else if (theFam == OMM_FAM)
                offset = SP_LOW_SPEED_PORT_OFFSET_OMM;

			switch (thePortId) 
			{
			case CT_PORT_SIDE_0:
				result = base + 0;
				break;
			case CT_PORT_SIDE_1:
				result = base + 1;
				break;
			case CT_PORT_SIDE_2:
				result = base + 2;
				break;
			case CT_PORT_SIDE_3:
				result = base + 3;
				break;
			case CT_PORT_SIDE_4:
				result = base + 4;
				break;
			case CT_PORT_SIDE_5:
				result = base + 5;
				break;
			case CT_PORT_SIDE_6:
				result = base + 6;
				break;
			case CT_PORT_SIDE_7:
				result = base + 7;
				break;
			case CT_PORT_SIDE_8:
				result = base + 8;
				break;
			case CT_PORT_SIDE_9:
				result = base + 9;
				break;
			case CT_PORT_SIDE_10:
			    result = base + 10;
			    break;
			case CT_PORT_SIDE_11:
			    result = base + 11;
			    break;
			case CT_PORT_SIDE_12:
			    result = base + 12;
			    break;
            case CT_PORT_SIDE_13:
			    result = base + 13;
			    break;
            case CT_PORT_SIDE_14:
			    result = base + 14;
			    break;
            case CT_PORT_SIDE_15:
			    result = base + 15;
			    break;
            case CT_PORT_SIDE_16:
			    result = base + 16;
			    break;
            case CT_PORT_SIDE_17:
			    result = base + 17;
			    break;
            case CT_PORT_SIDE_18:
			    result = base + 18;
			    break;
            case CT_PORT_SIDE_19:
			    result = base + 19;
			    break;
            case CT_PORT_SIDE_85:
                result = base + offset + 1;
                break;
            case CT_PORT_SIDE_86:
                result = base + offset + 2;
                break;
            case CT_PORT_SIDE_87:
                result = base + offset + 3;
                break;
            case CT_PORT_SIDE_88:
                result = base + offset + 4;
                break;
			default: //unknown protection scheme
				break;
			}
		}
		else //LINE
		{
			result = 0;
		}
	}

	return result;
}

bool IsSdhFacility(CT_FacilitySubType theFacType)
{
	bool result = false;
	switch (theFacType)
	{
	case FAC_SUBTYPE_STM1:
	case FAC_SUBTYPE_STM4:
	case FAC_SUBTYPE_STM16:
	case FAC_SUBTYPE_STM64:
	case FAC_SUBTYPE_STM1M:
	case FAC_SUBTYPE_STM4M:
	case FAC_SUBTYPE_STM16M:
	case FAC_SUBTYPE_STM64M:
		result = true;
		break;
	default:
		break;
	}

	return result;
}

CT_SlotId SP_PairMappingTblLookup::GetProtectionPairSlot(
        CT_SlotId  theSlot,
        CT_ShelfType theShelfType)
{
    CT_SlotId pairSlot = UNKNOWN_SLOT_ID;
    int i;

	if (theShelfType == OPTICAL_SHELF_FP3_TYPE ||
        theShelfType == PORT_SHELF_FP3_TYPE)
    {
        // Iterate through table searching for a matching entry
        for (i = 0; i < SP_UssPairMappingTbl_Size; i++)
        {
            if ( SP_UssPairMappingTbl[i].slotId1 == theSlot )
            {
                pairSlot = SP_UssPairMappingTbl[i].slotId2;
            }
            else if (SP_UssPairMappingTbl[i].slotId2 == theSlot )
            {
                pairSlot = SP_UssPairMappingTbl[i].slotId1;
            }

            if (pairSlot != UNKNOWN_SLOT_ID)
                break;
        }
    }
    else if (theShelfType == OPTICAL_SHELF_NANO_TYPE ||
             theShelfType == PORT_SHELF_NANO_TYPE)
    {
        for (i = 0; i < SP_NanoPairMappingTbl_Size; i++)
        {
            if ( SP_NanoPairMappingTbl[i].slotId1 == theSlot )
            {
                pairSlot = SP_NanoPairMappingTbl[i].slotId2;
            }
            else if (SP_NanoPairMappingTbl[i].slotId2 == theSlot )
            {
                pairSlot = SP_NanoPairMappingTbl[i].slotId1;
            }

            if (pairSlot != UNKNOWN_SLOT_ID)
                break;
        }
    }
    else if (theShelfType == PORT_SHELF_HCSS_TYPE)
    {
        for (i = 0; i < SP_HcssPairMappingTbl_Size; i++)
        {
            if ( SP_HcssPairMappingTbl[i].slotId1 == theSlot )
            {
                pairSlot = SP_HcssPairMappingTbl[i].slotId2;
            }
            else if (SP_HcssPairMappingTbl[i].slotId2 == theSlot )
            {
                pairSlot = SP_HcssPairMappingTbl[i].slotId1;
            }

            if (pairSlot != UNKNOWN_SLOT_ID)
                break;
        }
    }

	FC_THROW_ERROR_IF(pairSlot == UNKNOWN_SLOT_ID, FC_RuntimeError, "Unable to find paired slot mapping");

    return pairSlot;
}

uint8 GetOPDefectObjIndex(CT_IntfId thePortId)
{
	uint8 result = 0xFF;

    switch (thePortId) 
	{
	case CT_PORT_SIDE_0:
	case CT_LINE_SIDE_0:
	case CT_LINE_SIDE_1:
	case CT_PORT_SIDE_88:
	case CT_PORT_SIDE_12: //HGTMM
	    result = 0;
	    break;
	case CT_PORT_SIDE_1:
	case CT_PORT_SIDE_87:
		result = 1;
		break;
	case CT_PORT_SIDE_2:
	case CT_PORT_SIDE_86:
		result = 2;
		break;
	case CT_PORT_SIDE_3:
	case CT_PORT_SIDE_85:
		result = 3;
		break;
	case CT_PORT_SIDE_4:
		result = 4;
		break;
	case CT_PORT_SIDE_5:
		result = 5;
		break;
	case CT_PORT_SIDE_6:
		result = 6;
		break;
	case CT_PORT_SIDE_7:
		result = 7;
		break;
	case CT_PORT_SIDE_8:
		result = 8;
        break;
    case CT_PORT_SIDE_9:
		result = 9;
		break;
	default: //unknown port
		break;
	}

	return result;
}

uint32 GetRerouteObjectMask(CT_IntfId thePortId)
{
	uint32 mask = 0;
	uint32 value = 1;

    switch (thePortId) 
	{
	case CT_PORT_SIDE_0:
	    mask = (value << 0);
	    break;
	case CT_PORT_SIDE_1:
		mask = (value << 1);
		break;
	case CT_PORT_SIDE_2:
		mask = (value << 2);
		break;
	case CT_PORT_SIDE_3:
		mask = (value << 3);
		break;
	case CT_PORT_SIDE_4:
		mask = (value << 4);
		break;
	case CT_PORT_SIDE_5:
		mask = (value << 5);
		break;
	case CT_PORT_SIDE_6:
		mask = (value << 6);
		break;
	case CT_PORT_SIDE_7:
		mask = (value << 7);
		break;
	case CT_PORT_SIDE_8:
		mask = (value << 8);
        break;
    case CT_PORT_SIDE_9:
		mask = (value << 9);
		break;
	case CT_PORT_SIDE_10:
		mask = (value << 10);
		break;
	case CT_PORT_SIDE_11:
		mask = (value << 11);
		break;
	case CT_PORT_SIDE_12:
		mask = (value << 12);
		break;
	case CT_PORT_SIDE_13:
		mask = (value << 13);
		break;
	case CT_PORT_SIDE_14:
		mask = (value << 14);
		break;
	case CT_PORT_SIDE_15:
		mask = (value << 15);
		break;
	case CT_PORT_SIDE_85:
	case CT_PORT_SIDE_16:
		mask = (value << 16);
		break;
	case CT_PORT_SIDE_86:
	case CT_PORT_SIDE_17:
		mask = (value << 17);
		break;
	case CT_PORT_SIDE_87:
	case CT_PORT_SIDE_18:
		mask = (value << 18);
		break;
	case CT_PORT_SIDE_88:
	case CT_PORT_SIDE_19:
		mask = (value << 19);
		break;
	case CT_LINE_SIDE_0:
		mask = (value << 20);
		break;
	case CT_LINE_SIDE_1:
		mask = (value << 21);
        break;
	default: //unknown port
		break;
	}

	return mask;
}

uint8 GetRerouteObjectIndex(CT_IntfId thePortId)
{
	uint8 index = 0xFF;

    switch (thePortId) 
	{
	case CT_PORT_SIDE_0:
	    index =0;
	    break;
	case CT_PORT_SIDE_1:
		index =1;
		break;
	case CT_PORT_SIDE_2:
		index =2;
		break;
	case CT_PORT_SIDE_3:
		index =3;
		break;
	case CT_PORT_SIDE_4:
		index =4;
		break;
	case CT_PORT_SIDE_5:
		index =5;
		break;
	case CT_PORT_SIDE_6:
		index =6;
		break;
	case CT_PORT_SIDE_7:
		index =7;
		break;
	case CT_PORT_SIDE_8:
		index =8;
        break;
    case CT_PORT_SIDE_9:
		index =9;
		break;
	case CT_PORT_SIDE_10:
		index =10;
		break;
	case CT_PORT_SIDE_11:
		index =11;
		break;
	case CT_PORT_SIDE_12:
		index =12;
		break;
	case CT_PORT_SIDE_13:
		index =13;
		break;
	case CT_PORT_SIDE_14:
		index =14;
		break;
	case CT_PORT_SIDE_15:
		index =15;
		break;
	case CT_PORT_SIDE_85:
	case CT_PORT_SIDE_16:
		index =16;
		break;
	case CT_PORT_SIDE_86:
	case CT_PORT_SIDE_17:
		index =17;
		break;
	case CT_PORT_SIDE_87:
	case CT_PORT_SIDE_18:
		index =18;
		break;
	case CT_PORT_SIDE_88:
	case CT_PORT_SIDE_19:
		index =19;
		break;
	case CT_LINE_SIDE_0:
		index =20;
		break;
	case CT_LINE_SIDE_1:
		index =21;
        break;
	default: //unknown port
		break;
	}

    FC_THROW_ERROR_IF(index == 0xFF, FC_RuntimeError, "SP_Utilities::GetRerouteObjectIndex() Unable to find index");
	return index;
}

CT_SP_DefectLayer GetRerouteLayerMask(SP_ArrDefectLayer_Enum theLayer)
{
	CT_SP_DefectLayer mask = 0xFF;

    switch (theLayer) 
	{
	case Defect_Layer_OPT:
	    mask =CT_SP_LAYER_OPT;
	    break;
	case Defect_Layer_OTU:
		mask =CT_SP_LAYER_OTU;
		break;
	case Defect_Layer_ODU:
		mask =CT_SP_LAYER_ODU;
        break;
    case Defect_Layer_RS:
		mask =CT_SP_LAYER_RS;
        break;
    case Defect_Layer_MS:
		mask =CT_SP_LAYER_MS;
        break;
    default: //unknown port
		break;
	}

    FC_THROW_ERROR_IF(mask == 0xFF, FC_RuntimeError, "SP_Utilities::GetRerouteLayerMask() Unable to find nask");
	return mask;
}

unsigned int GetTspiiIntfFromSlotId(CT_CardType theCardType, CT_SlotId theSlotId)
{
	unsigned int result = 0xFF;
	if (theCardType == SPMH)
	{
		if (theSlotId >= TRN_2 && theSlotId <= TRN_8)
		{
			result = TSPII_PORT_SIDE_12 + (theSlotId-TRN_2);
		}
		else if (theSlotId >=TRN_12 && theSlotId <=TRN_18)
		{
			result = TSPII_PORT_SIDE_19 + (theSlotId-TRN_12);
		}
	}
    else if (theCardType == SPMNANO)
	{
		if (theSlotId >= TRN_1 && theSlotId <= TRN_6)
		{
			result = TSPII_PORT_SIDE_15 + (theSlotId-TRN_1);
		}
	}

	return result;
}


