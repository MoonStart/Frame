// Copyright(c) Tellabs Transport Group. All rights reserved.
#ifdef WIN32
#pragma warning( disable : 4786)
#endif

#include <cstring>
#include <cstdlib>
#include <iostream>


#include "../SP_Fsm1plus1TestParser.h"
#include "../SP_FsmGlbTestParser.h"
#include "../SP_1plus1APSController.h"
#include "OS_strtok_r.h"

using namespace std;

//##ModelId=3B8BCA0A028F
SP_Fsm1plus1TestParser::SP_Fsm1plus1TestParser()
{
}


//##ModelId=3B8BCA0A028E
SP_Fsm1plus1TestParser::~SP_Fsm1plus1TestParser()
{
}


//##ModelId=3B8BCA0A028B
void SP_Fsm1plus1TestParser::ParseLine(char* theLine, uint32 * theEmptyToken)
{
    const char* parseDigits = " \t";
    char* lastValue = NULL;
    char** lasts = &lastValue;
    char *tokenPtr = strtok_r(theLine, parseDigits, lasts);
    theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM] = 0;
    theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 0;

    if (tokenPtr == 0)
    {
        theEmptyToken[SP_TOKEN_COMMAND] = UNKNOWN_PARSED;
        return;
    }

    switch (tokenPtr[0])
    {
        case '#':
            theEmptyToken[SP_TOKEN_COMMAND] = PARSED_CMD_REM;
            theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM] = 1;
            theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 1;
            theEmptyToken[3] = 1;
            return;
        break;
        case 'R':
            if (strcmp("Run", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = PARSED_CMD_RUN;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM] = 1;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 1;
                theEmptyToken[3] = 1;
                return;
            }
        break;
        case 'P':
            if (strcmp("Print", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = PARSED_CMD_PRINT;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM] = 1;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 1;
                theEmptyToken[3] = 1;
                return;
            }
        break;
        case 'D':
            if (strcmp("Delete", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_DELETE;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM] = 1;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 1;
                theEmptyToken[3] = 1;
                return;
            }
        break;
        case 'A':
            if (strcmp("Architecture", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = PARSED_CMD_ARCHITECTURE;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 1;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = SP_FsmGlbTestParser::ConvertArchitecture(tokenPtr);
                return;
            }
        break;
        case 'E':
            if (strcmp("Edit", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_EDIT;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 5;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = SP_FsmGlbTestParser::ConvertEditStatus(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[4] = SP_FsmGlbTestParser::ConvertYesNo(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[5] = atoi(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[6] = SP_FsmGlbTestParser::ConvertYesNo(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[7] = SP_FsmGlbTestParser::ConvertYesNo(tokenPtr);

                return;
            }
        break;
        case 'S':
            if (strcmp("Send", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_SEND;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 6;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = ConvertChannel(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[4] = ConvertRequest(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[5] = ConvertChannel(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[6] = atoi(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[7] = SP_FsmGlbTestParser::ConvertArchitecture(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[8] = ConvertDirectionMode(tokenPtr);

                return;
            }
        break;
        case 'W':
            if (strcmp("Wait", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_WAIT;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 3;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = ConvertRequest(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[4] = atoi(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[5] = atoi(tokenPtr);

                return;
            }
        break;
        case 'C':
            if (strcmp("Check", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_CHECK;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 5;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = ConvertRequest(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[4] = ConvertChannel(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[5] = atoi(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[6] = SP_FsmGlbTestParser::ConvertArchitecture(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[7] = ConvertDirectionMode(tokenPtr);

                return;
            }
            if (strcmp("Create", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_CREATE;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 5;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = SP_FsmGlbTestParser::ConvertRate(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[4] = atoi(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[5] = atoi(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[6] = atoi(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[7] = atoi(tokenPtr);

                return;
            }

            if (strcmp("CheckFsm", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_CHECK_FSM;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 1;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = ConvertFsmState(tokenPtr);

                return;
            }
            if (strcmp("Command", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_COMMAND;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 1;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = ConvertCommandRequest(tokenPtr);

                return;
            }
        break;
        case 'F':
            if (strcmp("Failure", tokenPtr) == 0)
            {
                theEmptyToken[SP_TOKEN_COMMAND] = ONE_PARSED_CMD_FAILURE;
                theEmptyToken[SP_TOKEN_NB_OF_PARAM] = 3;

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[3] = ConvertChannel(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[4] = SP_FsmGlbTestParser::ConvertDefect(tokenPtr);

                tokenPtr    = strtok_r(0, parseDigits, lasts);
                if (!SP_FsmGlbTestParser::CheckMissingParamError(tokenPtr)) return;
                theEmptyToken[SP_TOKEN_REAL_NB_OF_PARAM]++;
                theEmptyToken[5] = SP_FsmGlbTestParser::ConvertSwitchDefect(tokenPtr);

                return;
            }
        break;
    }

    theEmptyToken[SP_TOKEN_COMMAND] = UNKNOWN_PARSED;
    return;
}

//##ModelId=3B8BCA0A0262
void SP_Fsm1plus1TestParser::Print1plus1ErrorMessage(ErrorType theError, uint32* params, int theLine)
{
    switch (theError)
    {
        case WAIT_TIMEOUT:
            fc_cout << "\nA time out as occured at line " << theLine << endl;
            fc_cout << "Command line is waiting for"
                 << " request = " << ConvertRequest(params[0]) << " and it never happenned";
            fc_cout << "\n" << "The command is waiting since " << params[1] << " msec" << endl << endl;
        break;
        case WAIT_OUT_OF_MIN_TIME:
            fc_cout << "\nThe signal reach predicted value before minimal time at line "
                 << theLine << endl;
            fc_cout << "Command is waiting for"
                 << " request = " << ConvertRequest(params[0]) << " and it appends "
                 << "before " << params[1] << " msec" << endl << endl;
        break;
        case CHECK_SIGNAL_FAIL:
            fc_cout << "\nWrong Signal at line " << theLine << endl;
            fc_cout << "    Predicted Signal: "
                 << ConvertRequest(params[0]) << "|"
                 << ConvertChannel(params[1]) << "|"
                 << params[2] << "|"
                 << SP_FsmGlbTestParser::ConvertArchitecture(params[3]) << "|"
                 << ConvertDirectionMode(params[4]) << endl;
            fc_cout << "    Real Signal     : "
                 << ConvertRequest(params[5]) << "|"
                 << ConvertChannel(params[6]) << "|"
                 << params[7] << "|"
                 << SP_FsmGlbTestParser::ConvertArchitecture(params[8]) << "|"
                 << ConvertDirectionMode(params[9]) << endl << endl;
        break;
        case CHECK_STATE_FAIL:
            fc_cout << "\nWrong State at line " << theLine << "\n\n";
            fc_cout << "    Predicted State: " << ConvertFsmState((uint8)params[0]) << "\n";
            fc_cout << "    Real State:      " << ConvertFsmState((uint8)params[1]) << endl << endl;
        break;
        default:
            fc_cout << "\nUnknown error" << endl << endl;
        break;
    }
}

///*************************************************************************************
//  Convertion fonctions
//
///*************************************************************************************

//##ModelId=3B8BCA0A0283
int SP_Fsm1plus1TestParser::ConvertRequest(const char* theRequest)
{
    if (strcmp("LP",   theRequest) == 0) return SP_1PLUS1_K1_LP;
    if (strcmp("FS",   theRequest) == 0) return SP_1PLUS1_K1_FS;
    if (strcmp("SF_H", theRequest) == 0) return SP_1PLUS1_K1_SF_H;
    if (strcmp("SF_L", theRequest) == 0) return SP_1PLUS1_K1_SF_L;
    if (strcmp("SD_H", theRequest) == 0) return SP_1PLUS1_K1_SD_H;
    if (strcmp("SD_L", theRequest) == 0) return SP_1PLUS1_K1_SD_L;
    if (strcmp("MS",   theRequest) == 0) return SP_1PLUS1_K1_MS;
    if (strcmp("WTR",  theRequest) == 0) return SP_1PLUS1_K1_WTR;
    if (strcmp("EXER", theRequest) == 0) return SP_1PLUS1_K1_EXER;
    if (strcmp("RR",   theRequest) == 0) return SP_1PLUS1_K1_RR;
    if (strcmp("DNR",  theRequest) == 0) return SP_1PLUS1_K1_DO_NOT_REVERT;
    if (strcmp("NR",   theRequest) == 0) return SP_1PLUS1_K1_NO_REQUEST;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BCA0A0285
const char* SP_Fsm1plus1TestParser::ConvertRequest(int theRequest)
{
    switch (theRequest)
    {
        case SP_1PLUS1_K1_LP:            return "LP";
        case SP_1PLUS1_K1_FS:            return "FS";
        case SP_1PLUS1_K1_SF_H:          return "SF_H";
        case SP_1PLUS1_K1_SF_L:          return "SF_L";
        case SP_1PLUS1_K1_SD_H:          return "SD_H";
        case SP_1PLUS1_K1_SD_L:          return "SD_L";
        case SP_1PLUS1_K1_MS:            return "MS";
        case SP_1PLUS1_K1_WTR:           return "WTR";
        case SP_1PLUS1_K1_EXER:          return "EXER";
        case SP_1PLUS1_K1_RR:            return "RR";
        case SP_1PLUS1_K1_DO_NOT_REVERT: return "DNR" ;
        case SP_1PLUS1_K1_NO_REQUEST:    return "NR";
        default : return "Unknown";
    }
}

//##ModelId=3B8BCA0A0273
int SP_Fsm1plus1TestParser::ConvertCommandRequest(const char* theRequest)
{
    if (strcmp("EOR",   theRequest) == 0) return CT_SP_END_OF_REQUEST;
    if (strcmp("NR",    theRequest) == 0) return CT_SP_NO_REQUEST;
    if (strcmp("LK_P",  theRequest) == 0) return CT_SP_1PLUS1_LK_P;
    if (strcmp("FS_P",  theRequest) == 0) return CT_SP_1PLUS1_FS_P;
    if (strcmp("SF_P",  theRequest) == 0) return CT_SP_1PLUS1_SF_P;
    if (strcmp("SD_P",  theRequest) == 0) return CT_SP_1PLUS1_SD_P;

    if (strcmp("MS_P",  theRequest) == 0) return CT_SP_1PLUS1_MS_P;
    if (strcmp("FS_W",  theRequest) == 0) return CT_SP_1PLUS1_FS_W;
    if (strcmp("SF_W",  theRequest) == 0) return CT_SP_1PLUS1_SF_W;
    if (strcmp("SD_W",  theRequest) == 0) return CT_SP_1PLUS1_SD_W;
    if (strcmp("MS_W",  theRequest) == 0) return CT_SP_1PLUS1_MS_W;
    if (strcmp("CLEAR", theRequest) == 0) return CT_SP_1PLUS1_CLEAR;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BCA0A0275
const char* SP_Fsm1plus1TestParser::ConvertCommandRequest(int theRequest)
{
    switch (theRequest)
    {
        case CT_SP_END_OF_REQUEST:  return "End of request";
        case CT_SP_NO_REQUEST  :    return "NR";
        case CT_SP_1PLUS1_LK_P :    return "LK_P";
        case CT_SP_1PLUS1_FS_P :    return "FS_P";
        case CT_SP_1PLUS1_SF_P :    return "SF_P";
        case CT_SP_1PLUS1_SD_P  :   return "SD_P";
        case CT_SP_1PLUS1_MS_P  :   return "MS_P";
        case CT_SP_1PLUS1_FS_W  :   return "FS_W";
        case CT_SP_1PLUS1_SF_W  :   return "SF_W";
        case CT_SP_1PLUS1_SD_W  :   return "SD_W";
        case CT_SP_1PLUS1_MS_W  :   return "MS_W";
        case CT_SP_1PLUS1_CLEAR  :  return "CLEAR (1+1)";
        default: return "Unknown";
    }
}


//##ModelId=3B8BCA0A027B
int SP_Fsm1plus1TestParser::ConvertChannel(const char* theChannel)
{
    if (strcmp("WORKING",    theChannel) == 0) return ONE_WORKING_CHANNEL;
    if (strcmp("W",          theChannel) == 0) return ONE_WORKING_CHANNEL;
    if (strcmp("PROTECTION", theChannel) == 0) return ONE_PROTECTION_CHANNEL;
    if (strcmp("P",          theChannel) == 0) return ONE_PROTECTION_CHANNEL;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BCA0A0281
const char* SP_Fsm1plus1TestParser::ConvertChannel(int theChannel)
{
    switch(theChannel)
    {
        case ONE_WORKING_CHANNEL:     return "WORKING";
        case ONE_PROTECTION_CHANNEL:  return "PROTECTION";
        default:                      return "Unknown";
    }
}

//##ModelId=3B8BCA0A0277
uint8 SP_Fsm1plus1TestParser::ConvertFsmState(const char* theFsmState)
{
    if (strcmp("S_WORKING_SELECTED",     theFsmState) == 0) return S_WORKING_SELECTED;
    if (strcmp("S_PROTECTION_SELECTED",  theFsmState) == 0) return S_PROTECTION_SELECTED;
    if (strcmp("S_NO_DEFECT_ON_WORKING", theFsmState) == 0) return S_NO_DEFECT_ON_WORKING;
    if (strcmp("S_COMMAND_TO_PROTECTION",theFsmState) == 0) return S_COMMAND_TO_PROTECTION;
    if (strcmp("S_PROTECTION_NO_REQUEST",theFsmState) == 0) return S_PROTECTION_NO_REQUEST;
    if (strcmp("S_WTR",                  theFsmState) == 0) return S_WTR;
    if (strcmp("S_DEFECT_ON_WORKING",    theFsmState) == 0) return S_DEFECT_ON_WORKING;
    if (strcmp("S_1PLUS1_INIT",          theFsmState) == 0) return S_1PLUS1_INIT;

    return UNKNOWN_PARSED;
}

//  ConvertFsmState
//
//  Returns the corresponding string for the int value
//  of an 1+1 fsm state.
///////////////////////////////////////////////////////////////////////
//##ModelId=3B8BCA0A0279
const char* SP_Fsm1plus1TestParser::ConvertFsmState(uint8 theFsmState)
{
    switch(theFsmState)
    {
    case S_WORKING_SELECTED     :return "S_WORKING_SELECTED";
    case S_PROTECTION_SELECTED  :return "S_PROTECTION_SELECTED";
    case S_NO_DEFECT_ON_WORKING :return "S_NO_DEFECT_ON_WORKING";
    case S_COMMAND_TO_PROTECTION:return "S_COMMAND_TO_PROTECTION";
    case S_PROTECTION_NO_REQUEST:return "S_PROTECTION_NO_REQUEST";
    case S_WTR                  :return "S_WTR";
    case S_DEFECT_ON_WORKING    :return "S_DEFECT_ON_WORKING";
    case S_1PLUS1_INIT          :return "S_1PLUS1_INIT";
    default: return "Unknown";
    }
}

//##ModelId=3B8BCA0A0271
const char* SP_Fsm1plus1TestParser::ConvertDirectionMode(int theDirectionMode)
{
    switch(theDirectionMode)
    {
    case SP_1PLUS1_UNIDIR :return "UNIDIR";
    case SP_1PLUS1_BIDIR  :return "BIDIR";
    case SP_1PLUS1_RDI_L  :return "RDI_L";
    case SP_1PLUS1_AIS_L  :return "AIS_L";
    default: return "Unknown";
    }
}

//##ModelId=3B8BCA0A026F
int SP_Fsm1plus1TestParser::ConvertDirectionMode(const char* theDirectionMode)
{
    if (strcmp("UNIDIR", theDirectionMode) == 0) return SP_1PLUS1_UNIDIR;
    if (strcmp("BIDIR",  theDirectionMode) == 0) return SP_1PLUS1_BIDIR;
    if (strcmp("RDI_L",  theDirectionMode) == 0) return SP_1PLUS1_RDI_L;
    if (strcmp("AIS_L",  theDirectionMode) == 0) return SP_1PLUS1_AIS_L;

    return UNKNOWN_PARSED;
}

