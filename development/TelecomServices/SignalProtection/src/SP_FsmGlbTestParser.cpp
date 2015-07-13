// Copyright(c) Tellabs Transport Group. All rights reserved.
#ifdef WIN32
#pragma warning( disable : 4786)
#endif

#include <cstring>
#include <cstdlib>
#include <iostream>

#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SignalProtection.h>
#include "../SP_FsmGlbTestParser.h"

using namespace std;

//##ModelId=3B8BC9BC017C
SP_FsmGlbTestParser::SP_FsmGlbTestParser()
{
}


//##ModelId=3B8BC9BC017B
SP_FsmGlbTestParser::~SP_FsmGlbTestParser()
{
}

//##ModelId=3B8BC9BC0175
int SP_FsmGlbTestParser::ConvertDefect(const char* theDefects)
{
        const char defectsStrings[13][5] =
                {"LOS", "LOF", "SEF", "TIM", "AISP", "AISL", "RDI",
         "SD", "SF", "LOPP", "K1K2", "ERRP", "COMM"};

    int i=0;
        for (i = 0; i < 13; i++)
        {
                if (strcmp(defectsStrings[i], theDefects) == 0)
                        return  i;
        }
    return UNKNOWN_PARSED;
}

//##ModelId=3B8BC9BC0177
const char* SP_FsmGlbTestParser::ConvertDefect(int theDefects)
{
        //const char defectsStrings[13][5] =
        //        {"LOS", "LOF", "SEF", "TIM", "AISP", "AISL", "RDI",
        // "SD", "SF", "LOPP", "K1K2", "ERRP", "COMM"};

        return "Unknown";
        //if (theDefects >= 13)
        //        return "Unknown";
        //else
        //        return defectsStrings[theDefects];
}

//##ModelId=3B8BC9BC0171
int SP_FsmGlbTestParser::ConvertSwitchDefect(const char* theSwitchDefect)
{
        if (strcmp("ON",     theSwitchDefect) == 0) return TSPII_DEFECT_ON;
        if (strcmp("OFF",    theSwitchDefect) == 0) return TSPII_DEFECT_OFF;
        if (strcmp("GLITCH", theSwitchDefect) == 0) return TSPII_DEFECT_GLITCH;
        if (strcmp("G",      theSwitchDefect) == 0) return TSPII_DEFECT_GLITCH;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BC9BC0173
const char* SP_FsmGlbTestParser::ConvertSwitchDefect(int theSwitchDefect)
{
        switch(theSwitchDefect)
        {
            case TSPII_DEFECT_ON:     return "ON";
            case TSPII_DEFECT_OFF:    return "OFF";
            case TSPII_DEFECT_GLITCH: return "GLITCH";
            default:                   return "Unknown";
        }
}

//##ModelId=3B8BC9BC016B
const char* SP_FsmGlbTestParser::ConvertArchitecture(int theArchitecture)
{
    if (theArchitecture == ONE_ARCHITECTURE) return "1+1";
    if (theArchitecture == ONEN_ARCHITECTURE) return "1:n";
    return "Unknown";
}

//##ModelId=3B8BC9BC0169
int SP_FsmGlbTestParser::ConvertArchitecture(const char* theArchitecture)
{
    if (strcmp("1PLUS1", theArchitecture) == 0) return ONE_ARCHITECTURE;
    if (strcmp("1TON",   theArchitecture) == 0) return ONEN_ARCHITECTURE;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BC9BC015D
int SP_FsmGlbTestParser::ConvertEditStatus(const char* theEditStatus)
{
    if (strcmp("LOCKED",   theEditStatus) == 0) return CT_SP_LOCKED;
    if (strcmp("NORMAL",   theEditStatus) == 0) return CT_SP_NORMAL_STATE;
    if (strcmp("SHUTDOWN", theEditStatus) == 0) return CT_SP_SHUTTING_DOWN_STATE;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BC9BC015F
const char* SP_FsmGlbTestParser::ConvertEditStatus(int theEditStatus)
{
    if (theEditStatus == CT_SP_LOCKED)              return "LOCKED";
    if (theEditStatus == CT_SP_NORMAL_STATE)        return "NORMAL";
    if (theEditStatus == CT_SP_SHUTTING_DOWN_STATE) return "SHUTDOWN";
    return "Unknown";
}

//##ModelId=3B8BC9BC0167
const char* SP_FsmGlbTestParser::ConvertYesNo(int theYesNo)
{
    if (theYesNo == FLAG_YES) return "Yes";
    if (theYesNo == FLAG_NO)  return "No";
    return "Unknown";
}

//##ModelId=3B8BC9BC0165
int SP_FsmGlbTestParser::ConvertYesNo(const char* theYesNo)
{
    if (strcmp("Yes", theYesNo) == 0) return FLAG_YES;
    if (strcmp("No",  theYesNo) == 0) return FLAG_NO;
    if (strcmp("Y",   theYesNo) == 0) return FLAG_YES;
    if (strcmp("N",   theYesNo) == 0) return FLAG_NO;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BC9BC0161
int SP_FsmGlbTestParser::ConvertRate(const char* theOCNumber)
{
    if (strcmp("OC48",  theOCNumber) == 0) return CT_TEL_SIGNAL_OC48;
    if (strcmp("OC192", theOCNumber) == 0) return CT_TEL_SIGNAL_OC192;

    return UNKNOWN_PARSED;
}

//##ModelId=3B8BC9BC0163
const char* SP_FsmGlbTestParser::ConvertRate(int theOCNumber)
{
    if (theOCNumber == CT_TEL_SIGNAL_OC48) return "OC48";
    if (theOCNumber == CT_TEL_SIGNAL_OC192)  return "OC192";
    return "Unknown";
}

//  CheckMissingParamError
//
//  Check if a string not empty or not created, if it's it mean
//  that there is a missing parameter
////////////////////////////////////////////////////////////////////////
//##ModelId=3B8BC9BC0152
bool SP_FsmGlbTestParser::CheckMissingParamError(const char * theToken)
{
        if (theToken != 0)
        {
                if (strlen(theToken) == 0)
                {
                        return false;
                }
                return true;
        }
        else
        {
                return false;
        }
}

//##ModelId=3B8BC9BC0154
ErrorType SP_FsmGlbTestParser::IsCommandValid(uint32* commandToken)
{
    if (commandToken[SP_TOKEN_COMMAND] == UNKNOWN_PARSED) return PARSER_ERROR;
    if (commandToken[SP_TOKEN_NB_OF_PARAM] != commandToken[SP_TOKEN_REAL_NB_OF_PARAM])
    {
        return MISSING_PARAMETER_ERROR;
    }

    for (uint32 i = 3; i < commandToken[SP_TOKEN_NB_OF_PARAM] + 3;i++)
    {
        if (commandToken[i] == UNKNOWN_PARSED) return WRONG_PARAMETER_ERROR;
    }

    return NO_ERROR;
}









