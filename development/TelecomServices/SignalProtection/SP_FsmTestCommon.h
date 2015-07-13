// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_FSMTESTCOMMON_INCLUDED
#define _INC_SP_FSMTESTCOMMON_INCLUDED

const int SP_SCENARIO_MAX_LINE_LENGTH = 256;
const int SP_SCENARIO_MAX_TOKEN_PARAM = 25;

const int UNKNOWN_PARSED = -1; // Unknown symbol

const int ONE_PROTECTION_CHANNEL = 1; // Channel selection
const int ONE_WORKING_CHANNEL    = 0; //
const int CLSR_PROTECTION_CHANNEL = 0; // Channel selection
const int CLSR_WORKING_CHANNEL    = 1; //

const int ONE_ARCHITECTURE = 0;
const int ONEN_ARCHITECTURE = 1;

const int TSPII_DEFECT_ON = 0;
const int TSPII_DEFECT_OFF = 1;
const int TSPII_DEFECT_GLITCH = 2;

const int FLAG_YES = 3;
const int FLAG_NO = 4;

//##ModelId=3BBC9B0A03C5
enum TokenElement
{
	//##ModelId=3BBC9B0B0087
    SP_TOKEN_COMMAND = 0,
	//##ModelId=3BBC9B0B0091
    SP_TOKEN_REAL_NB_OF_PARAM = 1,
	//##ModelId=3BBC9B0B0092
    SP_TOKEN_NB_OF_PARAM = 2
};

//##ModelId=3BBC9B0B00C3
enum ParsedCommandId
{
	//##ModelId=3BBC9B0B016D
    PARSED_CMD_PRINT = 1,           // Global commands
	//##ModelId=3BBC9B0B0177
    PARSED_CMD_RUN,                 //
	//##ModelId=3BBC9B0B0181
    PARSED_CMD_REM,                 //
	//##ModelId=3BBC9B0B018B
    PARSED_CMD_ARCHITECTURE,        //


	//##ModelId=3BBC9B0B020E
    ONE_PARSED_CMD_CREATE,       //
	//##ModelId=3BBC9B0B0218
    ONE_PARSED_CMD_EDIT,         //
	//##ModelId=3BBC9B0B0222
    ONE_PARSED_CMD_CHECK,        // 1+1 exclusive commands
	//##ModelId=3BBC9B0B022C
    ONE_PARSED_CMD_CHECK_FSM,    //
	//##ModelId=3BBC9B0B0236
    ONE_PARSED_CMD_SEND,         //
	//##ModelId=3BBC9B0B0237
    ONE_PARSED_CMD_WAIT,         //
	//##ModelId=3BBC9B0B0240
    ONE_PARSED_CMD_COMMAND,      //
	//##ModelId=3BBC9B0B024A
    ONE_PARSED_CMD_FAILURE,      //
	//##ModelId=3BBC9B0B025E
    ONE_PARSED_CMD_DELETE        //
};

// Possible error of the parser
//##ModelId=3BBC9B0B0286
enum ErrorType
{
	//##ModelId=3BBC9B0B0330
    NO_ERROR = 0,
	//##ModelId=3BBC9B0B033A
	PARSER_ERROR,
	//##ModelId=3BBC9B0B0344
	WRONG_PARAMETER_ERROR,
	//##ModelId=3BBC9B0B034E
	MISSING_PARAMETER_ERROR,
	//##ModelId=3BBC9B0B034F
	WAIT_TIMEOUT,
	//##ModelId=3BBC9B0B0358
	WAIT_OUT_OF_MIN_TIME,
	//##ModelId=3BBC9B0B0362
	CHECK_SIGNAL_FAIL,
	//##ModelId=3BBC9B0B0376
	CHECK_STATE_FAIL
};

#endif // !defined(_INC_SP_FSMCLSRTESTPARSER_INCLUDED)

