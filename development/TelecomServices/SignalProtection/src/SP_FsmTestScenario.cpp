// SP_FsmTestScenario.cpp: implementation of the SP_FsmTestScenario class.
//
//////////////////////////////////////////////////////////////////////
#include <cstring>
#include <BaseClass/FC_Stream.h>
#include "SP_FsmTestScenario.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=3B8BC9F700C1
SP_FsmTestScenario::SP_FsmTestScenario(char* theFileName, char* thePath) :
    myState(SP_SCENARIO_NOT_OPEN),
    mySubScenario(NULL),
    myParentScenario(NULL),
    noInterruptFlag(false),
    numOfLine(0),
	waitFlag(false)
{
	char aFullName[SP_SCENARIO_MAX_LINE_LENGTH];
	strncpy(aFullName, thePath,SP_SCENARIO_MAX_LINE_LENGTH-1);
	strncpy(myFileName, theFileName,SP_SCENARIO_MAX_LINE_LENGTH-1);
	strcat(aFullName, myFileName);
	
	myInputReader = new ifstream(aFullName);

	if (myInputReader)
	{
        if (!myInputReader->fail())
        {
		    myState     = SP_SCENARIO_OPEN;
        }
        else
        {
		    fc_cout << "Bad file name" << endl;
        }
	}
	else
	{
		fc_cout << "Error when opening file" << endl;
	}

}

//##ModelId=3B8BC9F700C0
SP_FsmTestScenario::~SP_FsmTestScenario()
{
	if (myInputReader)
	{
		myInputReader->close();
	}
	delete(myInputReader);
}

//##ModelId=3B8BC9F700B6
void SP_FsmTestScenario::Insert(char* theFileName, char* thePath)
{
	mySubScenario = new SP_FsmTestScenario(theFileName, thePath);
}

//##ModelId=3B8BC9F700AE
void SP_FsmTestScenario::RemoveSubScenario()
{
	delete(mySubScenario);
}

//##ModelId=3B8BC9F700AD
SP_FsmTestScenario* SP_FsmTestScenario::GetSubScenario()
{
	return mySubScenario;
}

//##ModelId=3B8BC9F700AC
SP_FsmTestScenario* SP_FsmTestScenario::GetParentScenario()
{
	return myParentScenario;
}


