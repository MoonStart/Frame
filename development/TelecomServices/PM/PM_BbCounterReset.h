/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Steve Thiffault, May 16, 2002.
 DESCRIPTION:   PM Counter control.
--------------------------------------------------------------------------*/
#ifndef PM_BBCOUNTERRESET_H
#define PM_BBCOUNTERRESET_H

#include <PM/PM_BbReset.h>

using namespace std;


//This class keeps the PM Counter Control, which corresponds 
//to inhibition of entity layer and reset of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3E6E4CC0000A
class PM_BbCounterReset : public PM_BbReset
{
public:

    //Class default constructor.
    //##ModelId=3E6E4CC1011B
    PM_BbCounterReset (uint32 theNumberOfParam, uint32 dummy = 0);

    //Constructor using a reset count array.
    //##ModelId=3E6E4CC10139
    PM_BbCounterReset (uint32 theNumberOfParam, PM_ResetCounter* theResetCount);

    //Class default destructor.
    //##ModelId=3E6E4CC10143
    virtual ~PM_BbCounterReset();

    //Gets the reset register counter for the specified 
    //parameter.
    //##ModelId=3E6E4CC10156
    virtual char GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const;

    //Resets the register for the specified parameter.
    //##ModelId=3E6E4CC10162
    virtual void ResetCurRegister(CT_PM_Parameter theParameterToReset);

    //Resets the all the registers for all the parameters.
    //##ModelId=3E6E4CC1017E
    virtual void ResetAllCurRegisters(void);

private:

    //Resets the registers for the reset count.
    //##ModelId=3E6E4CC10193
    void ResetRegisterCounter(PM_ResetCounter& theResetCount);

};

#endif //PM_BBCOUNTERRESET_H

