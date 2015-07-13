/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Steve Thiffault, May 16, 2002.
 DESCRIPTION:   PM Gauge control.
--------------------------------------------------------------------------*/

#include "../PM_BbGaugeReset.h"
#include <ErrorService/FC_Error.h>


using namespace std;

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB0157
PM_BbGaugeReset::PM_BbGaugeReset (int theNumberOfParam, int dummy):
    PM_BbReset(theNumberOfParam, dummy)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB016B
PM_BbGaugeReset::PM_BbGaugeReset (int theNumberOfParam, PM_ResetCounter* theResetCount):
    PM_BbReset(theNumberOfParam, theResetCount)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB0177
PM_BbGaugeReset::~PM_BbGaugeReset()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB0180
char PM_BbGaugeReset::GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const
{
    return (myResetCount[theParameterToReset] & 0x03);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB01A0
char PM_BbGaugeReset::GetResetMinRegisterCounter(PM_ResetCounter theParameterToReset) const
{
    return ((myResetCount[theParameterToReset] & 0x1c) >> 2);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB01B3
char PM_BbGaugeReset::GetResetMaxRegisterCounter(PM_ResetCounter theParameterToReset) const
{
    return ((myResetCount[theParameterToReset] & 0xe0) >> 5);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB01C6
void PM_BbGaugeReset::ResetCurRegister(CT_PM_Parameter theParameterToReset)
{
    ResetCurRegisterCounter(myResetCount[theParameterToReset]);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB01E4
void PM_BbGaugeReset::ResetMinRegister(CT_PM_Parameter theParameterToReset)
{
    ResetMinRegisterCounter(myResetCount[theParameterToReset]);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB01EF
void PM_BbGaugeReset::ResetMaxRegister(CT_PM_Parameter theParameterToReset)
{
    ResetMaxRegisterCounter(myResetCount[theParameterToReset]);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB020C
void PM_BbGaugeReset::ResetAllCurRegisters(void)
{
    uint32 param;


    // Reset all supported parameters.    
    for (param=0; param < myNumberOfParam; param++)
    {
        ResetCurRegisterCounter(myResetCount[param]);
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB0217
void PM_BbGaugeReset::ResetAllMinRegisters(void)
{
    uint32 param;


    // Reset all supported parameters.    
    for (param=0; param < myNumberOfParam; param++)
    {
        ResetMinRegisterCounter(myResetCount[param]);
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB023E
void PM_BbGaugeReset::ResetAllMaxRegisters(void)
{
    uint32 param;


    // Reset all supported parameters.    
    for (param=0; param < myNumberOfParam; param++)
    {
        ResetMaxRegisterCounter(myResetCount[param]);
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB0252
void PM_BbGaugeReset::ResetCurRegisterCounter(PM_ResetCounter& theResetCount)
{
    uint8 resetCount;


    // Current counter is only 2 least signifiant bits.
    resetCount = theResetCount & 0x03;


    // Wrap counter.
    if (resetCount == 0x03)
    {
        resetCount = 0;
    }
    
    resetCount++;

    // Clear current counter.
    theResetCount &= 0xfc;

    // Set current counter to new value.
    theResetCount |= resetCount;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB025D
void PM_BbGaugeReset::ResetMinRegisterCounter(PM_ResetCounter& theResetCount)
{
    uint8 resetCount;


    // Minimum counter is only 3 bits.
    resetCount = (theResetCount & 0x1c) >> 2;


    // Wrap counter.
    if (resetCount == 0x07)
    {
        resetCount = 0;
    }
    
    resetCount++;

    // Clear minimum counter.
    theResetCount &= 0xe3;

    // Set minimum counter to new value.
    theResetCount |= (resetCount << 2);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CBB027A
void PM_BbGaugeReset::ResetMaxRegisterCounter(PM_ResetCounter& theResetCount)
{
    uint8 resetCount;


    // Maximum counter is only 3 most signifiant bits.
    resetCount = (theResetCount & 0xe0) >> 5;


    // Wrap counter.
    if (resetCount == 0x07)
    {
        resetCount = 0;
    }
    
    resetCount++;

    // Clear maximum counter.
    theResetCount &= 0x1f;

    // Set maximum counter to new value.
    theResetCount |= (resetCount << 5);

}
