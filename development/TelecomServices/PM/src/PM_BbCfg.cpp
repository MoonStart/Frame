/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 11, 2002, Sebastien Cossette
 DESCRIPTION:   Configuration class, aggregating all configuration object.
--------------------------------------------------------------------------*/
#include <PM/PM_BbCfg.h>

#include <PM/PM_BbCfgLayer.h>

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE02C2
PM_BbCfg::PM_BbCfg(uint32 dummy1, uint32 dummy2)
    :myInhibitPtr(NULL),
     myThresholdPtr(NULL),
     myResetPtr(NULL),
     myDeleteMemoryFlag(NULL)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE02E0
PM_BbCfg::PM_BbCfg(PM_BbInhibit     &theInhibitRef, 
                   PM_BbThreshold   &theThresholdRef, 
                   PM_BbReset       &theResetRef,
                   bool             deleteMemory)
    :myInhibitPtr(&theInhibitRef),
     myThresholdPtr(&theThresholdRef),
     myResetPtr(&theResetRef),
     myDeleteMemoryFlag(deleteMemory)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
// SPM Controller Termination CFG Object has no Threshold
//-----------------------------------------------------------------
PM_BbCfg::PM_BbCfg(PM_BbInhibit     &theInhibitRef, 
                   PM_BbReset       &theResetRef,
                   bool             deleteMemory)
    :myInhibitPtr(&theInhibitRef),
     myThresholdPtr(NULL),            // PM Profile Feature!
     myResetPtr(&theResetRef),
     myDeleteMemoryFlag(deleteMemory)
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE02FD
PM_BbCfg::~PM_BbCfg()
{
    if(myDeleteMemoryFlag)
    {
        delete myInhibitPtr;
        delete myThresholdPtr;
        delete myResetPtr;
    }

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE031B
void PM_BbCfg::Reset()
{
    CheckPtr();

    myInhibitPtr->Reset();
    if ( myThresholdPtr )
        myThresholdPtr->Reset();
    myResetPtr->Reset();

}

//Reset Methods.
//-----------------------------------------------------------------
//##ModelId=3E6E4CAE0325
char PM_BbCfg::GetResetCurRegisterCounter(PM_ResetCounter theParameterToReset) const 
{
    return myResetPtr->GetResetCurRegisterCounter(theParameterToReset);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE0362
char PM_BbCfg::GetResetMinRegisterCounter(PM_ResetCounter theParameterToReset) const 
{
    return myResetPtr->GetResetMinRegisterCounter(theParameterToReset);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE0376
char PM_BbCfg::GetResetMaxRegisterCounter(PM_ResetCounter theParameterToReset) const 
{
    return myResetPtr->GetResetMaxRegisterCounter(theParameterToReset);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE0381
void PM_BbCfg::ResetCurRegister(CT_PM_Parameter theParameterToReset) 
{
    myResetPtr->ResetCurRegister(theParameterToReset);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE039E
void PM_BbCfg::ResetMinRegister(CT_PM_Parameter theParameterToReset) 
{
    myResetPtr->ResetMinRegister(theParameterToReset);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE03BC
void PM_BbCfg::ResetMaxRegister(CT_PM_Parameter theParameterToReset) 
{
    myResetPtr->ResetMaxRegister(theParameterToReset);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE03D0
void PM_BbCfg::ResetAllCurRegisters(void) 
{
    myResetPtr->ResetAllCurRegisters();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAE03DB
void PM_BbCfg::ResetAllMinRegisters(void)
{
    myResetPtr->ResetAllMinRegisters();

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0006
void PM_BbCfg::ResetAllMaxRegisters(void) 
{
    myResetPtr->ResetAllMaxRegisters();

}

//Inhibit Methods
//-----------------------------------------------------------------
//##ModelId=3E6E4CAF001A
bool PM_BbCfg::GetInhibit(CT_PM_BbControlWord theControlWord) const
{   
    return myInhibitPtr->GetInhibit(theControlWord);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0030
bool PM_BbCfg::GetInhibitParam(CT_PM_Parameter theParameter) const
{
    return myInhibitPtr->GetInhibitParam(theParameter);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0043
bool PM_BbCfg::GetTcaInhibitParam(CT_PM_Parameter theParameter) const 
{
    return myInhibitPtr->GetTcaInhibitParam(theParameter);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0056
void PM_BbCfg::SetInhibit(CT_PM_BbControlWord theControlWord, bool theBoolVal)
{
    myInhibitPtr->SetInhibit(theControlWord, theBoolVal);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0074
void PM_BbCfg::SetInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal)
{
    myInhibitPtr->SetInhibitParam(theParameter, theBoolVal);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0088
void PM_BbCfg::SetTcaInhibitParam(CT_PM_Parameter theParameter, bool theBoolVal) 
{
    myInhibitPtr->SetTcaInhibitParam(theParameter, theBoolVal);

}

//Threshold Methods
//-----------------------------------------------------------------
bool PM_BbCfg::SetThreshold(CT_PM_Parameter theParameter, uint32 theValue ) 
{
    return (myThresholdPtr->SetThreshold(theParameter, theValue));
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF00C4
CT_PM_64bit_ull PM_BbCfg::GetThreshold(CT_PM_Parameter theParameter)
{
    return myThresholdPtr->GetThreshold(theParameter);
}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF00D8
bool PM_BbCfg::HasThresholdChanged(CT_PM_Parameter theParameter) const
{
    return myThresholdPtr->HasThresholdChanged(theParameter);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF00F7
void PM_BbCfg::SetThreshold(CT_PM_Parameter theParameter, 
                            int32           theMinValue, 
                            int32           theMaxValue)
{
    myThresholdPtr->SetThreshold(theParameter, theMinValue, theMaxValue);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0115
void PM_BbCfg::GetThreshold(CT_PM_Parameter theParameter, 
                            int32&          theMinValue, 
                            int32&          theMaxValue) const 
{
    myThresholdPtr->GetThreshold(theParameter, theMinValue, theMaxValue);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0133
void PM_BbCfg::HasThresholdChanged(CT_PM_Parameter  theParameter, 
                                   bool&            theMinFlag, 
                                   bool&            theMaxFlag) const
{
    myThresholdPtr->HasThresholdChanged(theParameter, theMinFlag, theMaxFlag);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF015B
void PM_BbCfg::CheckPtr()
{
    FC_THROW_ERROR_IF(myInhibitPtr == NULL || myResetPtr == NULL, FC_SWError, "PM_BbCfg:CheckPtr: myInhibitPtr||myResetPtr Pointer is NULL");

    /*PM_BbCfgHopPFNearEnd* aHopPFPtr = dynamic_cast<PM_BbCfgHopPFNearEnd*>(this);
    if ( !aHopPFPtr )
    {
        FC_THROW_ERROR_IF( myThresholdPtr == NULL, FC_SWError, "PM_BbCfg:CheckPtr: myThresholdPtr Pointer is NULL");
    }*/

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF016E
FC_Stream& PM_BbCfg::WriteObjectBinary( FC_Stream& theStream )
{
    CheckPtr();

    myInhibitPtr->WriteObjectBinary(theStream);
    if ( myThresholdPtr )
        myThresholdPtr->WriteObjectBinary(theStream);
    myResetPtr->WriteObjectBinary(theStream);
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0183
FC_Stream& PM_BbCfg::ReadObjectBinary( FC_Stream& theStream )
{
    CheckPtr();

    myInhibitPtr->ReadObjectBinary(theStream);
    if ( myThresholdPtr )
        myThresholdPtr->ReadObjectBinary(theStream);
    myResetPtr->ReadObjectBinary(theStream);
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF0197
ostream& PM_BbCfg::WriteObject( ostream& theStream )
{
    CheckPtr();

    myInhibitPtr->WriteObject(theStream);
    if ( myThresholdPtr )
        myThresholdPtr->WriteObject(theStream);
    myResetPtr->WriteObject(theStream);
    
    return theStream;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CAF01AB
istream& PM_BbCfg::ReadObject( istream& theStream )
{
    CheckPtr();

    myInhibitPtr->ReadObject(theStream);
    if ( myThresholdPtr )
        myThresholdPtr->ReadObject(theStream);
    myResetPtr->ReadObject(theStream);

    return theStream;

}

