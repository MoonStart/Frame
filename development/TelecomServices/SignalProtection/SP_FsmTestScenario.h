// Copyright(c) Tellabs Transport Group. All rights reserved.

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SP_FSMTESTSCENARIO_INCLUDED
#define _INC_SP_FSMTESTSCENARIO_INCLUDED

#include <iostream>
#include <fstream>
#include "SP_FsmTestCommon.h"

using namespace std;

// Enum that defined the state of the parsed file
//////////////////////////////////////////////////////////////////////
//##ModelId=3BBC9B0803C2
enum SP_ScenarioState
{
	//##ModelId=3BBC9B090084
	SP_SCENARIO_NOT_OPEN =1,
	//##ModelId=3BBC9B09008E
	SP_SCENARIO_OPEN,
	//##ModelId=3BBC9B090098
	SP_SCENARIO_RUNNING,
	//##ModelId=3BBC9B0900A2
	SP_SCENARIO_COMPLETE,
	//##ModelId=3BBC9B0900AC
	SP_SCENARIO_FAILURE
};

//##ModelId=3B8BC9F70016
class SP_FsmTestScenario  
{
public:

	//##ModelId=3B8BC9F7008E
	char currentLine[256];
	//##ModelId=3B8BC9F70085
	int	 numOfLine;  
	//##ModelId=3B8BC9F70084
	bool waitFlag;
	//##ModelId=3B8BC9F7007A
    bool noInterruptFlag;

	//##ModelId=3B8BC9F700C1
	SP_FsmTestScenario(char* theFileName, char* thePath);
	//##ModelId=3B8BC9F700C0
	virtual ~SP_FsmTestScenario();

	//##ModelId=3B8BC9F700B6
	void Insert(char* theFileName, char* thePath);
	//##ModelId=3B8BC9F700AE
	void RemoveSubScenario();
	//##ModelId=3B8BC9F700AD
	SP_FsmTestScenario* GetSubScenario();
	//##ModelId=3B8BC9F700AC
	SP_FsmTestScenario* GetParentScenario();
	//##ModelId=3B8BC9F700A3
	void SetParentScenario(SP_FsmTestScenario* theParent) { myParentScenario = theParent; }

	//##ModelId=3B8BC9F700A2
	SP_ScenarioState GetState() { return myState; }
	//##ModelId=3B8BC9F7009A
	void SetState(SP_ScenarioState theState) { myState = theState; }

	//##ModelId=3B8BC9F70099
	ifstream* GetFile() { return myInputReader; }

	//##ModelId=3B8BC9F70098
	const char* GetFileName() { return myFileName;}


private:

	//##ModelId=3B8BC9F70072
	SP_FsmTestScenario* mySubScenario;
	//##ModelId=3B8BC9F70068
	SP_FsmTestScenario* myParentScenario;
	//##ModelId=3BBC9B090266
	SP_ScenarioState myState; 
    
	//##ModelId=3B8BC9F7005D
	char        myFileName[SP_SCENARIO_MAX_LINE_LENGTH];
	//##ModelId=3B8BC9F7005C
	char        myPath[SP_SCENARIO_MAX_LINE_LENGTH];

	//##ModelId=3B8BC9F70054
    ifstream*   myInputReader;

};

#endif 
