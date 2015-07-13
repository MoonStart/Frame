// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_TEST_MENU_INCLUDED
#define _INC_SP_TEST_MENU_INCLUDED

#include "Shell/FC_CmdProcessor.h"
#include <SignalProtection/SP_Definitions.h>
#include <CommonTypes/CT_SignalProtection.h>

//##ModelId=39ACEFB00253
class SP_TestMenu  
{
public:
	//##ModelId=39ACEFB0034F
	SP_TestMenu();
	//##ModelId=39ACEFB0034E
	virtual ~SP_TestMenu();

	//##ModelId=39ACEFB00343
    static const char* K1Request1plus1ToText(SP_K1Request req);
	//##ModelId=39ACEFB0031D
    static const char* K2Status1plus1ToText(SP_Status status);
	//##ModelId=39ACEFB00311
    static const char* RequestToText(CT_SP_Request req);
	//##ModelId=39ACEFB00308
    static const char* AutoSwitchToText(CT_SP_AutoSwitchDefect defect);

	//##ModelId=39ACEFB00307
    static bool mySpDebug;
	static bool mySpEventLog;

protected:


};

#endif // _INC_SP_TEST_MENU_INCLUDED
