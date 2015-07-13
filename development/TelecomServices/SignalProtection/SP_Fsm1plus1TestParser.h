// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_FSM1PLUS1TESTPARSER_INCLUDED
#define _INC_SP_FSM1PLUS1TESTPARSER_INCLUDED

#include <T6100_CardIf.h>
#include "SignalProtection/SP_FsmTestCommon.h"


//##ModelId=3B8BCA0A0226
class SP_Fsm1plus1TestParser  
{
public:
	//##ModelId=3B8BCA0A028F
	SP_Fsm1plus1TestParser();
	//##ModelId=3B8BCA0A028E
	virtual ~SP_Fsm1plus1TestParser();

	//##ModelId=3B8BCA0A028B
    static void ParseLine(char* theLine, uint32 * theEmptyToken);

	//##ModelId=3B8BCA0A0283
	static int ConvertRequest(const char* theRequest);
	//##ModelId=3B8BCA0A0285
	static const char* ConvertRequest(int theRequest);
	//##ModelId=3B8BCA0A027B
	static int ConvertChannel(const char* theChannel);
	//##ModelId=3B8BCA0A0281
	static const char* ConvertChannel(int theChannel);
	//##ModelId=3B8BCA0A0277
	static uint8 ConvertFsmState(const char* theFsmState);
	//##ModelId=3B8BCA0A0279
	static const char* ConvertFsmState(uint8 theFsmState);
	//##ModelId=3B8BCA0A0273
	static int ConvertCommandRequest(const char* theRequest);
	//##ModelId=3B8BCA0A0275
	static const char* ConvertCommandRequest(int theRequest);
	//##ModelId=3B8BCA0A026F
    static int ConvertDirectionMode(const char* theDirectionMode);
	//##ModelId=3B8BCA0A0271
	static const char* ConvertDirectionMode(int theDirectionMode);

	//##ModelId=3B8BCA0A0262
    static void Print1plus1ErrorMessage(ErrorType theError, uint32* params, int theLine);

};

#endif // !defined(_INC_SP_FSMCLSRTESTPARSER_INCLUDED)

