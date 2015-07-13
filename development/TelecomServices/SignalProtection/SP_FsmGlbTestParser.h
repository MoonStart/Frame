// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_FSMGLBTESTPARSER_INCLUDED
#define _INC_SP_FSMGLBTESTPARSER_INCLUDED

#include <T6100_CardIf.h>
#include "SignalProtection/SP_FsmTestCommon.h"


//##ModelId=3B8BC9BC0120
class SP_FsmGlbTestParser  
{
public:
	//##ModelId=3B8BC9BC017C
	SP_FsmGlbTestParser();
	//##ModelId=3B8BC9BC017B
	virtual ~SP_FsmGlbTestParser();

	//##ModelId=3B8BC9BC0175
    static int ConvertDefect(const char* theDefects);
	//##ModelId=3B8BC9BC0177
	static const char* ConvertDefect(int theDefects);
	//##ModelId=3B8BC9BC0171
	static int ConvertSwitchDefect(const char* theSwitchDefect);
	//##ModelId=3B8BC9BC0173
	static const char* ConvertSwitchDefect(int theSwitchDefect);
	//##ModelId=3B8BC9BC0169
	static int ConvertArchitecture(const char* theArchitecture);
	//##ModelId=3B8BC9BC016B
	static const char* ConvertArchitecture(int theArchitecture);
	//##ModelId=3B8BC9BC0165
    static int ConvertYesNo(const char* theYesNo);
	//##ModelId=3B8BC9BC0167
	static const char* ConvertYesNo(int theYesNo);
	//##ModelId=3B8BC9BC0161
    static int ConvertRate(const char* theOCNumber);
	//##ModelId=3B8BC9BC0163
	static const char* ConvertRate(int theOCNumber);
	//##ModelId=3B8BC9BC015D
    static int ConvertEditStatus(const char* theEditStatus);
	//##ModelId=3B8BC9BC015F
	static const char* ConvertEditStatus(int theEditStatus);

	//##ModelId=3B8BC9BC0154
    static ErrorType IsCommandValid(uint32* commandToken);
	//##ModelId=3B8BC9BC0152
    static bool CheckMissingParamError(const char * theToken);

};

#endif // !defined

