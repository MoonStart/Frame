/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     November 15, 2002 Sebastien Cossette.
 DESCRIPTION:   Base class for all gauge parameters for an accumulation 
                period.
--------------------------------------------------------------------------*/

#ifndef PM_ACCUMULATIONPERIODGAUGE_H
#define PM_ACCUMULATIONPERIODGAUGE_H

#include <PM/src/PM_AccPeriod.h>
#include <PM/PM_GenericApplication.h>


// Forward declaration of classes
class PM_BbCfg;
class PM_BbValue;
class PM_Rules;
class PM_GenericApplication;
template <class OBJECT_TYPE> class PM_RegionImp;

//##ModelId=3E6E4CBB02CA
class PM_AccumulationPeriodGauge : public PM_AccumulationPeriod
{
public:

    //##ModelId=3E6E4CBC034E
    PM_AccumulationPeriodGauge(PM_GenericApplication    &theGenericApplication,
                               CT_PM_Value*             theMaxValueTable,
                               PM_Rules&                theRules,
                               uint32                   theNumberOfParam,
                               uint32                   thePortNumber,
                               CT_PM_Period             thePeriod);

    //##ModelId=3E6E4CBC036D
    virtual ~PM_AccumulationPeriodGauge();

    //Updates All parameters for this accumulation 
    //period.
    //##ModelId=3E6E4CBC0376
    virtual bool UpdatePeriodOfAll(PM_BbValue& theValue, 
                                   PM_BbCfg&   theConfig,
                                   bool*       theValidityState,
                                   bool*       theFilteringStateFirstStage,
                                   bool*       theFilteringStateSecondStage,
                                   bool        theEndOfPeriod);

    //Adds a number to a PM value.
    //##ModelId=3E6E4CBC039F
    virtual CT_PM_64BitValue AddValue(
                                 PM_BbValue&        theValue, 
                                 CT_PM_Parameter    theParam, 
                                 CT_PM_64BitValue   theNumber, 
                                 CT_PM_Value        theMaxValue, 
                                 bool               theUaState, 
                                 bool               thePotential2ChgState, 
                                 bool               theEndOfPeriod);

protected:

    //Start first stage soaking for minimum TCA of specified
    //parameter.
	//##ModelId=3FA161070364
    inline void StartMinTcaFirstStageSoaking(CT_PM_Parameter theParameter);

    //Start second stage soaking for minimum TCA of specified
    //parameter.
	//##ModelId=3FA161070374
    inline void StartMinTcaSecondStageSoaking(CT_PM_Parameter theParameter);

    //Return minimum TCA first stage soaking completed status 
    //of specified parameter.
	//##ModelId=3FA161070393
    bool IsMinTcaFirstStageSoakingCompleted(CT_PM_Parameter theParameter);

    //Stop minimum TCA first stage soaking.
	//##ModelId=3FA1610703A3
    inline void StopMinTcaFirstStageSoaking(CT_PM_Parameter theParameter);

    //Stop minimum TCA second stage soaking.
	//##ModelId=3FA1610703B3
    inline void StopMinTcaSecondStageSoaking(CT_PM_Parameter theParameter);

    //Return minimum TCA second stage soaking completed status 
    //of specified parameter.
	//##ModelId=3FA1610703D1
    bool IsMinTcaSecondStageSoakingCompleted(CT_PM_Parameter theParameter);

    //Update TCA soakings.
	//##ModelId=3FA1610703E1
    void UpdateTcaSoaking(CT_PM_Parameter theParameter);

    //Verifies if threshold has to be reset due to a 
    //threshold configuration changing.
    //##ModelId=3E6E4CBC03D0
    virtual bool CheckThresholdChange(PM_BbCfg& theConfig, PM_BbValue& theValue);

    //Verifies if threshold and values has to be reset due to 
    //a reset request.
    //##ModelId=3E6E4CBC03E6
    virtual bool CheckResetReqChange(PM_BbCfg& theConfig, PM_BbValue& theCurrentValue);

    //Counter used for first stage soaking minimum TCA.
	//##ModelId=3FA161080019
    uint8* myMinTcaFirstStageSoakingCounter;

    //Counter used for second stage soaking minimum TCA.
	//##ModelId=3FA161080029
    uint8* myMinTcaSecondStageSoakingCounter;

    //Flag to enable or disable the first stage soaking minimum TCA.
	//##ModelId=3FA161080037
    bool* myMinTcaFirstStageSoakingEnable;

    //Flag to enable or disable the second stage soaking minimum TCA.
	//##ModelId=3FA161080047
    bool* myMinTcaSecondStageSoakingEnable;

    //Array that contains all time stamp as when minimum TCA 
    //for given parameter occured.
	//##ModelId=3FA161080067
    FC_Time* myMinTcaOccurTime;

    //Array that contains all crossed value when minimum TCA 
    //for given parameter occured.
	//##ModelId=3FA161080077
    CT_PM_Value* myMinTcaCrossedValue;

    //Previous first stage and and second stage filter states
    bool* myPrevFilteringStateFirstStage;
    bool* myPrevFilteringStateSecondStage;

};

//-----------------------------------------------------------------
//##ModelId=3FA161070364
inline void PM_AccumulationPeriodGauge::StartMinTcaFirstStageSoaking(CT_PM_Parameter theParameter) 
{
    myMinTcaFirstStageSoakingEnable[theParameter] = true;
    myMinTcaFirstStageSoakingCounter[theParameter] = 0;

}

//-----------------------------------------------------------------
//##ModelId=3FA161070374
inline void PM_AccumulationPeriodGauge::StartMinTcaSecondStageSoaking(CT_PM_Parameter theParameter) 
{
    myMinTcaSecondStageSoakingEnable[theParameter] = true;
    myMinTcaSecondStageSoakingCounter[theParameter] = 0;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610703A3
inline void PM_AccumulationPeriodGauge::StopMinTcaFirstStageSoaking(CT_PM_Parameter theParameter) 
{
    myMinTcaFirstStageSoakingEnable[theParameter] = false;
    myMinTcaFirstStageSoakingCounter[theParameter] = 0;

}

//-----------------------------------------------------------------
//##ModelId=3FA1610703B3
inline void PM_AccumulationPeriodGauge::StopMinTcaSecondStageSoaking(CT_PM_Parameter theParameter) 
{
    myMinTcaSecondStageSoakingEnable[theParameter] = false;
    myMinTcaSecondStageSoakingCounter[theParameter] = 0;

}

#endif //PM_ACCUMULATIONPERIODGAUGE_H
