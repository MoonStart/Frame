// Copyright(c) Tellabs Transport Group. All rights reserved.

#include "../SP_TestMenu.h"
#include <CSM/CSM_AppIf.h>
#include <SignalProtection/SP_ProtectionGroupConfigRegionImp.h>
#include <SignalProtection/SP_1plus1ProtectionGroupConfig.h>
#include <SignalProtection/SP_1plus1ProtectionGroupStatus.h>
#include <SignalProtection/SP_1plus1BaseApplication.h>
#include <T6100_CardIf.h>

//##ModelId=39ACEFB00307
bool SP_TestMenu::mySpDebug = false;
bool SP_TestMenu::mySpEventLog = false;

//##ModelId=39ACEFB0034F
SP_TestMenu::SP_TestMenu()
{

}

//##ModelId=39ACEFB0034E
SP_TestMenu::~SP_TestMenu()
{

}


//##ModelId=39ACEFB00343
const char* SP_TestMenu::K1Request1plus1ToText(SP_K1Request req)
{
    switch(req)
    {
    case SP_1PLUS1_K1_LP  :     return "LP";
    case SP_1PLUS1_K1_FS  :     return "FS";
    case SP_1PLUS1_K1_SF_H:     return "SF_H";
    case SP_1PLUS1_K1_SF_L:     return "SF_L";
    case SP_1PLUS1_K1_SD_H:     return "SD_H";
    case SP_1PLUS1_K1_SD_L:     return "SD_L";
    case SP_1PLUS1_K1_MS  :     return "MS"  ;
    case SP_1PLUS1_K1_WTR :     return "WTR" ;
    case SP_1PLUS1_K1_EXER:     return "EXER";
    case SP_1PLUS1_K1_RR  :     return "RR"  ;
    case SP_1PLUS1_K1_DO_NOT_REVERT:    return "DNR";
    case SP_1PLUS1_K1_NO_REQUEST   : return "NR";
    default : return "INVALID 1+1 K1 request";
    }
}

//##ModelId=39ACEFB0031D
const char* SP_TestMenu::K2Status1plus1ToText(SP_Status status)
{
    switch(status)
    {
    case SP_1PLUS1_UNIDIR        : return "UNIDIR";
    case SP_1PLUS1_BIDIR         : return "BIDIR"; 
    case SP_1PLUS1_RDI_L         : return "RDI-L"; 
    case SP_1PLUS1_AIS_L         : return "AIS-L"; 
    default : return "INVALID 1+1 status code";
    }
}

//##ModelId=39ACEFB00311
const char* SP_TestMenu::RequestToText(CT_SP_Request req)
{
    switch (req)
    {
    case CT_SP_END_OF_REQUEST: return "Invalid request";
    case CT_SP_NO_REQUEST  : return "NR";
    case CT_SP_CLSR_CLEAR : return "CLEAR (CLSR)";
    case CT_SP_CLSR_LOW_R : return "LOW-R";
    case CT_SP_CLSR_LOW_S : return "LOW-S";
    case CT_SP_CLSR_LP_S  : return "LP-S";
    case CT_SP_CLSR_FS_S  : return "FS-S";
    case CT_SP_CLSR_FS_R  : return "FS-R";
    case CT_SP_CLSR_SF_S  : return "SF-S";
    case CT_SP_CLSR_SF_R  : return "SF-R";
    case CT_SP_CLSR_SD_P  : return "SD-P";
    case CT_SP_CLSR_SD_S  : return "SD-S";
    case CT_SP_CLSR_SD_R  : return "SD-R";
    case CT_SP_CLSR_MS_S  : return "MS-S";
    case CT_SP_CLSR_MS_R  : return "MS-R";
    case CT_SP_CLSR_WTR   : return "WTR";
    case CT_SP_CLSR_EXER_S: return "EXER-S";
    case CT_SP_CLSR_EXER_R: return "EXER-R";
    case CT_SP_CLSR_RR_S  : return "RR-S";
    case CT_SP_CLSR_RR_R  : return "RR-R";
    case CT_SP_1PLUS1_LK_P: return "LK-P";
    case CT_SP_1PLUS1_FS_P: return "FS-P";
    case CT_SP_1PLUS1_SF_P: return "SF-P";
	case CT_SP_1PLUS1_SF_LOW_W: return "SF-W-LOW";
	case CT_SP_1PLUS1_SF_LOW_P: return "SF-P-LOW";
    case CT_SP_1PLUS1_SD_P: return "SD-P";
    case CT_SP_1PLUS1_MS_P: return "MS-P";
    case CT_SP_1PLUS1_FS_W: return "FS-W";
    case CT_SP_1PLUS1_SF_W: return "SF-W";
    case CT_SP_1PLUS1_SD_W: return "SD-W";
    case CT_SP_1PLUS1_MS_W: return "MS-W";
    case CT_SP_1PLUS1_CLEAR: return "CLEAR (1+1)";
    case CT_SP_1PLUS1_DO_NOT_REVERT: return "DO NOT REVERT";
    case CT_SP_1PLUS1_WTR:  return "WTR";
    default : return "Invalid request";
    }
}

//##ModelId=39ACEFB00308
const char* SP_TestMenu::AutoSwitchToText(CT_SP_AutoSwitchDefect defect)
{
    switch (defect)
    {
    case CT_SP_AUTO_SD:     return "SD";
    case CT_SP_AUTO_SF:     return "SF";
    case CT_SP_AUTO_SF_LOW: return "SF_LOW";
    case CT_SP_AUTO_NONE:   return "NO";
    default: return "Invalid";
    }
}


