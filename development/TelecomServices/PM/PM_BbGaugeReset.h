/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Steve Thiffault, May 16, 2002.
 DESCRIPTION:   PM Gauge control.
--------------------------------------------------------------------------*/
#ifndef PM_BBGAUGERESET_H
#define PM_BBGAUGERESET_H

#include <PM/PM_BbReset.h>

//This class keeps the PM Gauge Control, which corresponds 
//to inhibition of entity layer and reset of parameters on 
//parameter basis for near-end parameters.
//##ModelId=3E6E4CBA00DE
class PM_BbGaugeReset : public PM_BbReset
{
public:

    //Class default constructor.
    //##ModelId=3E6E4CBB0157
    PM_BbGaugeReset (int theNumberOfParam, int dummy = 0);

    //Constructor using a reset count array.
    //##ModelId=3E6E4CBB016B
    PM_BbGaugeReset (int theNumberOfParam, PM_ResetCounter* theResetCount);

    //Class default destructor.
    //##ModelId=3E6E4CBB0177
    virtual ~PM_BbGaugeReset();

    //Gets the reset current register counter for the specified 
    //parameter.
    //##ModelId=3E6E4CBB0180
    virtual char GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const;

    //Gets the reset minimum register counter for the specified 
    //parameter.
    //##ModelId=3E6E4CBB01A0
    virtual char GetResetMinRegisterCounter(PM_ResetCounter theParameterToReset) const;

    //Gets the reset maximum register counter for the specified 
    //parameter.
    //##ModelId=3E6E4CBB01B3
    virtual char GetResetMaxRegisterCounter(PM_ResetCounter theParameterToReset) const;
    
    //Resets the current register for the specified parameter.
    //##ModelId=3E6E4CBB01C6
    virtual void ResetCurRegister(CT_PM_Parameter theParameterToReset);

    //Resets the minimum register for the specified parameter.
    //##ModelId=3E6E4CBB01E4
    virtual void ResetMinRegister(CT_PM_Parameter theParameterToReset);

    //Resets the maximum register for the specified parameter.
    //##ModelId=3E6E4CBB01EF
    virtual void ResetMaxRegister(CT_PM_Parameter theParameterToReset);

    //Resets the all the current registers for all the parameters.
    //##ModelId=3E6E4CBB020C
    virtual void ResetAllCurRegisters(void);

    //Resets the all the minimum registers for all the parameters.
    //##ModelId=3E6E4CBB0217
    virtual void ResetAllMinRegisters(void);

    //Resets the all the maximum registers for all the parameters.
    //##ModelId=3E6E4CBB023E
    virtual void ResetAllMaxRegisters(void);

private:

    //Resets the current registers for the reset count.
    //##ModelId=3E6E4CBB0252
    void ResetCurRegisterCounter(PM_ResetCounter& theResetCount);

    //Resets the minimum registers for the reset count.
    //##ModelId=3E6E4CBB025D
    void ResetMinRegisterCounter(PM_ResetCounter& theResetCount);

    //Resets the maximum registers for the reset count.
    //##ModelId=3E6E4CBB027A
    void ResetMaxRegisterCounter(PM_ResetCounter& theResetCount);

};

#endif //PM_BBGAUGERESET_H

