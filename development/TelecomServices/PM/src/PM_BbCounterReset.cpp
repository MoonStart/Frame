/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Steve Thiffault, May 16, 2002.
 DESCRIPTION:   PM Counter control.
--------------------------------------------------------------------------*/

#include "../PM_BbCounterReset.h"
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3E6E4CC1011B
PM_BbCounterReset::PM_BbCounterReset (uint32 theNumberOfParam, uint32 dummy):
    PM_BbReset(theNumberOfParam, dummy)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC10139
PM_BbCounterReset::PM_BbCounterReset (uint32            theNumberOfParam, 
                                      PM_ResetCounter*  theResetCount):
    PM_BbReset(theNumberOfParam, theResetCount)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC10143
PM_BbCounterReset::~PM_BbCounterReset()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC10156
char PM_BbCounterReset::GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const
{
    return (myResetCount[theParameterToReset]);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC10162
void PM_BbCounterReset::ResetCurRegister(CT_PM_Parameter theParameterToReset)
{
    ResetRegisterCounter(myResetCount[theParameterToReset]);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC1017E
void PM_BbCounterReset::ResetAllCurRegisters(void)
{
    uint32 param;


    // Reset all supported parameters.    
    for (param=0; param < myNumberOfParam; param++)
    {
        ResetRegisterCounter(myResetCount[param]);
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CC10193
void PM_BbCounterReset::ResetRegisterCounter(PM_ResetCounter& theResetCount)
{
    theResetCount++;


    // Ensure that 0 is not part of the free running counter
    // serialized, since this value is a power up value only.
    if (theResetCount == 0)
    {
        theResetCount++;
    }

}
