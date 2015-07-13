/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002, Sebastien Cossette
 DESCRIPTION:   PM reset class. Keeps the reset state of PM.
--------------------------------------------------------------------------*/
#ifndef PM_BBRESET_H
#define PM_BBRESET_H

#include <CommonTypes/CT_PM_Definition.h>
#include <PM/PM_Def.h>
#include <PM/PM_BbObject.h>


//This class keeps the reset counter of parameters on parameter 
//basis for near-end parameters.
//##ModelId=3E6E4CA80313
class PM_BbReset : public PM_BbObject
{
public:

    //##ModelId=3E6E4CA9030B
    PM_BbReset(uint32 theNumberOfParam, uint32 dummy = 0);

    //Constructor using a reset count array.
    //##ModelId=3E6E4CA9031F
    PM_BbReset (uint32 theNumberOfParam, PM_ResetCounter* theResetCount);

    //##ModelId=3E6E4CA90332
    virtual ~PM_BbReset();

    //Reset all PM values to zero.
    //##ModelId=3E6E4CA9033C
    virtual void Reset();

    // Calls GetResetRegisterCounter.
    //##ModelId=3E6E4CA90346
    virtual char GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const;

    // Not supported by base class, defined only for gauge.
    //##ModelId=3E6E4CA9036E
    virtual char GetResetMinRegisterCounter(PM_ResetCounter theParameterToReset) const;

    // Not supported by base class, defined only for gauge.
    //##ModelId=3E6E4CA90382
    virtual char GetResetMaxRegisterCounter(PM_ResetCounter theParameterToReset) const;

    // Calls ResetRegister.
    //##ModelId=3E6E4CA90396
    virtual void ResetCurRegister(CT_PM_Parameter theParameterToReset);

    // Not supported by base class, defined only for gauge.
    //##ModelId=3E6E4CA903AA
    virtual void ResetMinRegister(CT_PM_Parameter theParameterToReset);

    // Not supported by base class, defined only for gauge.
    //##ModelId=3E6E4CA903BF
    virtual void ResetMaxRegister(CT_PM_Parameter theParameterToReset);

    // Calls ResetAllRegisters.
    //##ModelId=3E6E4CA903CA
    virtual void ResetAllCurRegisters(void);

    // Not supported by base class, defined only for gauge.
    //##ModelId=3E6E4CA903E7
    virtual void ResetAllMinRegisters(void);

    // Not supported by base class, defined only for gauge.
    //##ModelId=3E6E4CAA0013
    virtual void ResetAllMaxRegisters(void);

    //Stores the values to the binary stream.
    //##ModelId=3E6E4CAA001F
    FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4CAA0032
    FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    //##ModelId=3E6E4CAA0045
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4CAA0059
    virtual istream& ReadObject( istream& theStream );

    PM_ResetCounter GetPMResetCount(CT_PM_Parameter theParam) { return myResetCount[ theParam ]; }
    bool SetPMResetCount(CT_PM_Parameter theParam, PM_ResetCounter theCount);

    uint32 GetNumberOfParam() { return myNumberOfParam; }

protected:

    //The number of parameters supported by the derived class 
    //layer.
    //##ModelId=3E6FC02503D0
    uint32 myNumberOfParam;

    //Free running counters for resetting current registers.
    //##ModelId=3E6FC0260038
    PM_ResetCounter* myResetCount;

};

#endif //PM_BBRESET_H
