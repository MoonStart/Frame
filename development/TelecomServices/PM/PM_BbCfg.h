/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002, Sebastien Cossette
 DESCRIPTION:   Configuration class, aggregating all configuration object.
--------------------------------------------------------------------------*/
#ifndef PM_BBCFG_H
#define PM_BBCFG_H

#include <PM/PM_BbInhibit.h>
#include <PM/PM_BbThreshold.h>
#include <PM/PM_BbReset.h>
#include <PM/PM_BbObject.h>

//##ModelId=3E6E4CAD0143
class PM_BbCfg : public PM_BbObject
{
public:

    //Default constructor.
    //##ModelId=3E6E4CAE02C2
    PM_BbCfg(uint32 dummy1 = 0, uint32 dummy2 = 0);

    //Memory constructor.
    //##ModelId=3E6E4CAE02E0
    PM_BbCfg(PM_BbInhibit   &theInhibitRef, 
             PM_BbThreshold &theThresholdRef, 
             PM_BbReset     &theResetRef, 
             bool           deleteMemory = false);

    // SPM Controller has Termination CFG region w/o Threshold (PM Profile)
    PM_BbCfg(PM_BbInhibit   &theInhibitRef, 
             PM_BbReset     &theResetRef, 
             bool           deleteMemory = false);

    //Destructor.
    //##ModelId=3E6E4CAE02FD
    virtual ~PM_BbCfg();

    //This method reset this object.
    //##ModelId=3E6E4CAE031B
    virtual void Reset();

    //Reset Method
    //##ModelId=3E6E4CAE0325
    virtual char GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const;
    //##ModelId=3E6E4CAE0362
    virtual char GetResetMinRegisterCounter(PM_ResetCounter theParameterToReset) const;
    //##ModelId=3E6E4CAE0376
    virtual char GetResetMaxRegisterCounter(PM_ResetCounter theParameterToReset) const;
    
    //##ModelId=3E6E4CAE0381
    virtual void ResetCurRegister(CT_PM_Parameter theParameterToReset);
    //##ModelId=3E6E4CAE039E
    virtual void ResetMinRegister(CT_PM_Parameter theParameterToReset);
    //##ModelId=3E6E4CAE03BC
    virtual void ResetMaxRegister(CT_PM_Parameter theParameterToReset);

    //##ModelId=3E6E4CAE03D0
    virtual void ResetAllCurRegisters(void);
    //##ModelId=3E6E4CAE03DB
    virtual void ResetAllMinRegisters(void);
    //##ModelId=3E6E4CAF0006
    virtual void ResetAllMaxRegisters(void);
    
    //Inhibit Method
    //##ModelId=3E6E4CAF001A
    virtual bool GetInhibit(CT_PM_BbControlWord theControlWord) const;
    //##ModelId=3E6E4CAF0030
    virtual bool GetInhibitParam(CT_PM_Parameter theParameter) const;
    //##ModelId=3E6E4CAF0043
    virtual bool GetTcaInhibitParam(CT_PM_Parameter theParameter) const;

    //##ModelId=3E6E4CAF0056
    virtual void SetInhibit(CT_PM_BbControlWord theControlWord, bool theBoolVal);
    //##ModelId=3E6E4CAF0074
    virtual void SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);
    //##ModelId=3E6E4CAF0088
    virtual void SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal);

    //Threshold Method
    //##ModelId=3E6E4CAF00B0
    virtual bool SetThreshold(CT_PM_Parameter theParameter, uint32 theValue); 
    //##ModelId=3E6E4CAF00C4
    virtual CT_PM_64bit_ull GetThreshold(CT_PM_Parameter theParameter);
    //##ModelId=3E6E4CAF00D8
    virtual bool HasThresholdChanged(CT_PM_Parameter theParameter) const;

    //##ModelId=3E6E4CAF00F7
    virtual void SetThreshold(CT_PM_Parameter theParameter, int32 theMinValue, int32 theMaxValue);
    //##ModelId=3E6E4CAF0115
    virtual void GetThreshold(CT_PM_Parameter theParameter, int32& theMinValue, int32& theMaxValue) const;
    //##ModelId=3E6E4CAF0133
    virtual void HasThresholdChanged(CT_PM_Parameter theParameter, bool& theMinFlag, bool& theMaxFlag) const;

    PM_BbInhibit* GetInhibitPtr() {return myInhibitPtr;}
    PM_BbThreshold* GetThresholdPtr() {return myThresholdPtr;}
    PM_BbReset* GetResetPtr() {return myResetPtr;}
    
protected:

    //This method verifies pointers validity.
    //##ModelId=3E6E4CAF015B
    void CheckPtr();

    //Writes the states to the binary stream.
    //##ModelId=3E6E4CAF016E
    virtual FC_Stream& WriteObjectBinary( FC_Stream& theStream );

    //Reads the states from a binary stream.
    //##ModelId=3E6E4CAF0183
    virtual FC_Stream& ReadObjectBinary( FC_Stream& theStream );

    //Stores the values to the stream.
    //##ModelId=3E6E4CAF0197
    virtual ostream& WriteObject( ostream& theStream );

    //Reads the values from the stream.
    //##ModelId=3E6E4CAF01AB
    virtual istream& ReadObject( istream& theStream );

private:

    // Pointer to the inhibition object.
    //##ModelId=3E6FC0290335
    PM_BbInhibit    *myInhibitPtr;

    // Pointer to the threshold object.
    //##ModelId=3E6FC029037C
    PM_BbThreshold  *myThresholdPtr;

    // Pointer to the reset object.
    //##ModelId=3E6FC02A0001
    PM_BbReset      *myResetPtr;

    // Flag indicating if mememory was deleted.
    //##ModelId=3E6E4CAF029B
    bool            myDeleteMemoryFlag;

};

#endif //PM_BBCFG_H
