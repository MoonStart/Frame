/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Base class for all parameters for an accumulation period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIOD_H
#define PM_ACCUMULATIONPERIOD_H

#include <PM/src/PM_CommandUpdateAction.h>
#include <PM/PM_Def.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbTca.h>


// Forward declaration of classes
class PM_GenericApplication;
class PM_BbValue;
class PM_BbCfg;
class PM_ResetRequestPeriod;
class PM_Rules;
template <class OBJECT_TYPE> class PM_RegionImp;

//This is the base class to accumulates PM parameters for a 
//given accumulation period. It contains the general 
//functionality of all accumulations. It manages the 
//accumulation of parameters and verifies for any 
//configuration changing.
//##ModelId=3C1F6F7701ED
class PM_AccumulationPeriod
{
public:

    //Class default constructor.
    //##ModelId=3C1F6F780035
    PM_AccumulationPeriod(PM_GenericApplication     &theGenericApplication,
                          CT_PM_Value*              theMaxValueTable,
                          PM_Rules&                 theRules,
                          uint32                    theNumberOfParam,
                          uint32                    thePortNumber,
                          CT_PM_Period              thePeriod);

    PM_AccumulationPeriod(PM_GenericApplication     &theGenericApplication,
                          CT_PM_64BitValue*         theMaxValueTable,
                          PM_Rules&                 theRules,
                          uint32                    theNumberOfParam,
                          uint32                    thePortNumber,
                          CT_PM_Period              thePeriod);

    void InitializeData();

    //Class default destructor.
    //##ModelId=3C1F6F780054
    virtual ~PM_AccumulationPeriod();

    //Sets all modification actions on region changing and 
    //setup the attributes according to the actual 
    //configuration of the control region.
    //##ModelId=3C1F6F780056
    virtual void Init(uint16 thePortNumber);

    //This method is responsible to verify if there is a 
    //configuration change and to start the update of 
    //parameter defined by a derived class.
    //##ModelId=3C1F6F780060
    virtual bool AccumulateParameter(bool* theValidityState, 
                                     bool* theFilteringStateFirstStage,
                                     bool* theFilteringStateSecondStage);

    //Updates the PM parameters of a given accumulation 
    //period. This class must be overload by the derived 
    //class.
    //##ModelId=3C1F6F780072
    virtual bool UpdatePeriod(bool* theValidityState, 
                              bool* theFilteringStateFirstStage,
                              bool* theFilteringStateSecondStage);

    //Updates the PM parameters of a given accumulation 
    //period at the end of period.
    //##ModelId=3E6E4CB4016B
    virtual bool UpdateEndPeriod();

    //Updates All parameters for this accumulation 
    //period.
    //##ModelId=3E6E4CB401DA
    virtual bool UpdatePeriodOfAll(PM_BbValue&  theValue, 
                                   PM_BbCfg&    theConfig, 
                                   bool*        theValidityState, 
                                   bool*        theFilteringStateFirstStage,
                                   bool*        theFilteringStateSecondStage,
                                   bool         theEndOfPeriod) = 0;

    //Adjusts the IDF of all parameters according to the 
    //inhibition status. This method is used at the start of 
    //a new accumulation period.
    //##ModelId=3C1F6F78007C
    virtual void AdjustCurrentIdf();

    //Resets the soaking count for the change of UA state. 
    //This method is used at the start of a new accumulation 
    //period.
    //##ModelId=3C1F6F780086
    virtual void RegAdjReset();

    //Resets all PM values to zero, TCA statues are reset,
    //IDF are set to invalid.
    //##ModelId=3E6E4CB500B9
    virtual void ResetAll();

    //Set the availability when monitoring 
    //status is invalid or valid of specifier parameter.
	//##ModelId=3FA1610601FD
    virtual void SetAvailability(CT_PM_Parameter theParameter, bool theAvailability);

	// Get a reference to the associated PM_Rules object.
	virtual PM_Rules& GetRules();

protected:

    //Verifies if threshold has to be reset due to a 
    //threshold configuration changing.
    //##ModelId=3C1F6F7800AE
    virtual bool CheckThresholdChange(PM_BbCfg& theConfig, PM_BbValue& theValue) = 0;

    //Verifies if threshold and values has to be reset due to 
    //a reset request.
    //##ModelId=3C1F6F780112
    virtual bool CheckResetReqChange(PM_BbCfg& theConfig, PM_BbValue& theCurrentValue) = 0;

    //Verifies if there is a pending threshold configuration.
    //##ModelId=3C1F6F7800A4
    virtual bool VerifyConfigChange();

    //Verifies if threshold has to be reset due to an 
    //inhibition configuration changing.
    //##ModelId=3C1F6F7800E0
    virtual bool CheckInhibitionChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

    //Resets to zero all adjustment registers.
    //##ModelId=3C1F6F78016E
    void ResetAllAdjustRegister();

    //Resets to zero the adjustment register of a given 
    //parameter.
    //##ModelId=3C1F6F780176
    void ResetAdjustRegister(CT_PM_Parameter theParam);

    //Resets all PM values to zero, including the adjustment 
    //registers.
    //##ModelId=3C1F6F78018A
    void ResetAll(PM_BbValue& theValue);
    
    //Sets control to know whether a TCA has changed state.
    //##ModelId=3C1F6F780126
    inline void SetSomeTcaChangedState(bool theTcaState) ;

    //Resets the control to know whether a TCA has changed 
    //state.
    //##ModelId=3C1F6F780131
    inline void ResetSomeTcaChangedState();

    //Gets control to know whether a TCA has changed state.
    //##ModelId=3C1F6F780144
    inline bool GetSomeTcaChangedState();

    //Gets the current inhibition status for accumulation of 
    //whole layer.
    //##ModelId=3E6E4CB50285
    inline bool GetCurrentAllInhibit();

    //Sets the current inhibition status for accumulation of 
    //whole layer.
    //##ModelId=3E6E4CB50307
    inline void SetCurrentAllInhibit(bool theNewState);

    //Gets the current inhibition status for TCA of 
    //whole layer.
    //##ModelId=3E6E4CB6002E
    inline bool GetCurrentAllTcaInhibit() { return myCurrentAllTcaInhibit; }

    //Sets the current inhibition status for TCA of 
    //whole layer.
    //##ModelId=3E6E4CB600CE
    inline void SetCurrentAllTcaInhibit(bool theNewState) { myCurrentAllTcaInhibit = theNewState; }

    //Returns a pointer to the associated current value 
    //region.
    //##ModelId=3C1FAF9A0051
    inline PM_RegionImp<PM_BbValue>* GetCurrentValueRegion();

    //Returns a pointer to the associated threshold region.
    //##ModelId=3C1FAF9A00B6
    inline PM_RegionImp<PM_BbCfg>* GetConfigRegion();

    //Start first stage soaking for maximum TCA of specified
    //parameter.
	//##ModelId=3FA16106024B
    inline void StartMaxTcaFirstStageSoaking(CT_PM_Parameter theParameter);

    //Start second stage soaking for maximum TCA of specified
    //parameter.
	//##ModelId=3FA16106027A
    inline void StartMaxTcaSecondStageSoaking(CT_PM_Parameter theParameter);

    //Stop maximum TCA first stage soaking.
	//##ModelId=3FA1610602A9
    inline void StopMaxTcaFirstStageSoaking(CT_PM_Parameter theParameter);

    //Stop maximum TCA second stage soaking.
	//##ModelId=3FA1610602C8
    inline void StopMaxTcaSecondStageSoaking(CT_PM_Parameter theParameter);

    //Return maximum TCA first stage soaking completed status 
    //of specified parameter.
	//##ModelId=3FA1610602F7
    bool IsMaxTcaFirstStageSoakingCompleted(CT_PM_Parameter theParameter);

    //Return maximum TCA second stage soaking completed status 
    //of specified parameter.
	//##ModelId=3FA161060326
    bool IsMaxTcaSecondStageSoakingCompleted(CT_PM_Parameter theParameter);

    //Update TCA soakings.
	//##ModelId=3FA161060355
    virtual void UpdateTcaSoaking(CT_PM_Parameter theParameter);

    //Gets the inhibition verify request flag.
    //##ModelId=3C1F6F7800BA
    inline bool GetConfigVerifyRequest();

    //Sets the inhibition verify request flag.
    //##ModelId=3C1F6F7800C2
    inline void SetConfigVerifyRequest(bool theState);

    //The index of this accumulation period. It can be seen like the port number.
    //##ModelId=3C1F6F78019E
    uint16 myIndex;

    //Reference to the generic PM application.
    //##ModelId=3C1FAF9A003E
    PM_GenericApplication &myGenericApplication;

    //A pointer to a table that holds maximum values of all
    //PM parameters.
    //##ModelId=3C1F6F7903C7
    CT_PM_Value* myMaxValueTable;
    CT_PM_64BitValue* myMaxValueTable64Bit;

    //Period accumulation type.
    //##ModelId=3C1F6F7903DB
    CT_PM_Period myPeriod;

    //The number of PM parameters for this layer.
    //##ModelId=3C1F6F7A009E
    uint32 myNumberOfParam;

    //This class handles the reset request on the current 
    //register
    //##ModelId=3C20A58900CB
    PM_ResetRequestPeriod* myCurrentResetPtr;

    //The previous state of this signal.
    //##ModelId=3C1F6F7A00B2
    PM_BbTca myPreviousUaState;

    //Pointer to an array that contained the adjustement 
    //registers for all value handle by this class.
    //##ModelId=3C1F6F7A00D0
    CT_PM_64bit_ull *myAdjustRegister;

    //Reference to the Rules class. It is uses to get the 
    //accumulation rules for derived class layer.
    //##ModelId=3C501631001E
    PM_Rules& myRules;

    //Counter used for first stage soaking maximum TCA.
	//##ModelId=3FA161060394
    uint8* myMaxTcaFirstStageSoakingCounter;

    //Counter used for second stage soaking maximum TCA.
	//##ModelId=3FA1610603A4
    uint8* myMaxTcaSecondStageSoakingCounter;

    //Flag to enable or disable the first stage soaking maximum TCA.
	//##ModelId=3FA1610603C2
    bool* myMaxTcaFirstStageSoakingEnable;

    //Flag to enable or disable the second stage soaking maximum TCA.
	//##ModelId=3FA1610603E1
    bool* myMaxTcaSecondStageSoakingEnable;

    //Array that contains all time stamp as when maximum TCA 
    //for given parameter occured.
	//##ModelId=3FA161070029
    FC_Time* myMaxTcaOccurTime;

    //Array that contains all crossed value when maximum TCA 
    //for given parameter occured.
	//##ModelId=3FA161070039
    CT_PM_64BitValue* myMaxTcaCrossedValue;

    //Current accumulation inhibition for the whole layer
    //##ModelId=3E6E4CB603B3
    bool myCurrentAllInhibit;

private:

    //Current TCA inhibition for the whole layer
    //##ModelId=3E6E4CB700A7
    bool myCurrentAllTcaInhibit;

    //Flag to control and to know whether a TCA has changed 
    //state.
    //##ModelId=3C1F6F7A0006
    bool mySomeTcaChangedState;

    //Action to run when control (this is for reset request) region changed.
    //##ModelId=3C1F6F7A0089
    PM_CommandUpdateAction myConfigUpdateAction;

};

//-----------------------------------------------------------------
//##ModelId=3FA16106024B
inline void PM_AccumulationPeriod::StartMaxTcaFirstStageSoaking(CT_PM_Parameter theParameter) 
{
    myMaxTcaFirstStageSoakingEnable[theParameter] = true;
    myMaxTcaFirstStageSoakingCounter[theParameter] = 0;

}

//-----------------------------------------------------------------
//##ModelId=3FA16106027A
inline void PM_AccumulationPeriod::StartMaxTcaSecondStageSoaking(CT_PM_Parameter theParameter) 
{
    myMaxTcaSecondStageSoakingEnable[theParameter] = true;
    myMaxTcaSecondStageSoakingCounter[theParameter] = 0;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610602A9
inline void PM_AccumulationPeriod::StopMaxTcaFirstStageSoaking(CT_PM_Parameter theParameter) 
{
    myMaxTcaFirstStageSoakingEnable[theParameter] = false;
    myMaxTcaFirstStageSoakingCounter[theParameter] = 0;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610602C8
inline void PM_AccumulationPeriod::StopMaxTcaSecondStageSoaking(CT_PM_Parameter theParameter) 
{
    myMaxTcaSecondStageSoakingEnable[theParameter] = false;
    myMaxTcaSecondStageSoakingCounter[theParameter] = 0;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7800BA
inline bool PM_AccumulationPeriod::GetConfigVerifyRequest() 
{ 
    return myConfigUpdateAction.GetState();

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F7800C2
inline void PM_AccumulationPeriod::SetConfigVerifyRequest(bool theState) 
{ 
    myConfigUpdateAction.SetState(theState);

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780126
inline void PM_AccumulationPeriod::SetSomeTcaChangedState(bool theTcaState) 
{ 
    mySomeTcaChangedState |= theTcaState;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780131
inline void PM_AccumulationPeriod::ResetSomeTcaChangedState() 
{ 
    mySomeTcaChangedState = false;

}

//-----------------------------------------------------------------
//##ModelId=3C1F6F780144
inline bool PM_AccumulationPeriod::GetSomeTcaChangedState() 
{ 
    return mySomeTcaChangedState;

}


//-----------------------------------------------------------------
//##ModelId=3E6E4CB50285
inline bool PM_AccumulationPeriod::GetCurrentAllInhibit() 
{ 
    return myCurrentAllInhibit;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4CB50307
inline void PM_AccumulationPeriod::SetCurrentAllInhibit(bool theNewState) 
{ 
    myCurrentAllInhibit = theNewState;

}

//-----------------------------------------------------------------
//##ModelId=3C1FAF9A0051
inline PM_RegionImp<PM_BbValue>* PM_AccumulationPeriod::GetCurrentValueRegion()
{
    return myGenericApplication.GetCurrentRegionValue(myPeriod);

}

//-----------------------------------------------------------------
//##ModelId=3C1FAF9A00B6
inline PM_RegionImp<PM_BbCfg>* PM_AccumulationPeriod::GetConfigRegion()
{
    switch (myPeriod)
    {
    case CT_PM_PERIOD_15_MINUTES:
        return myGenericApplication.Get15MRegionConfig();
    case CT_PM_PERIOD_1_DAY:
        return myGenericApplication.GetDayRegionConfig();
    case CT_PM_PERIOD_UNKNOWN:
    default:
        FC_THROW_ERROR( FC_InvalidArgumentError, "PM: invalid period type" );
        return NULL;
    }

}

#endif //PM_ACCUMULATIONPERIOD_H
