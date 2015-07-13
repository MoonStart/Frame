/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Control period class.
--------------------------------------------------------------------------*/

#ifndef PM_CONTROLPERIOD_H
#define PM_CONTROLPERIOD_H

#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <PM/PM_GenericApplication.h>


using namespace std;

// Forward declaration of classes
template <class OBJECT_TYPE> class PM_RegionImp;
class PM_GenericApplication;
class PM_BbValue;
class PM_BbCfg;
class PM_BbValueOpr;
class PM_AccumulationPeriod;

//This class derives the PM parameters with the data given by 
//PM collector. Then it updates the blackboard regions owned 
//by PM processor with the current PM parameter values.
//##ModelId=3C1F6F6C029B
class PM_ControlPeriod
{
public:

    //Class default constructor.
    //##ModelId=3C1FAF860338
    PM_ControlPeriod(PM_GenericApplication      &theGenericApplication,
                     CT_PM_Period               thePeriod,
                     PM_AccumulationPeriod&     theAccPeriod,
                     uint16                     theIndex,
                     char*                      theProcessorTypeString,
                     time_t                     thePstOffset = 0,
					 bool						theUpdatePreviousValue = true);

    //Class default destructor.
    //##ModelId=3C1F6F6D0103
    virtual ~PM_ControlPeriod();

    //Initialization of the control period.
    //##ModelId=3E6E4CE703C8
    void Init();

    //Controls the end of period of all accumulation periods.
    //##ModelId=3C1F6F6D010C
    virtual void ControlPeriod(long    theCurrentTimeChanged, 
                               FC_Time theCurrentTime, 
                               time_t  thePstOffset = 0,
                               time_t  theDstOffset = 0);

    //Sets warning on/off. This method allows printing of 
    //warning message to help the debug of PM. The default 
    //value is off (false). 
    //##ModelId=3C1F6F6D0120
    inline void SetWarning(bool theWarning);
   
protected:

    //Returns a pointer to the associated current value 
    //region.
	//##ModelId=3FA1611002C4
    inline PM_RegionImp<PM_BbValue>* GetCurrentValueRegion();

    //Returns a pointer to the associated previous value 
    //region.
	//##ModelId=3FA1611002D3
    inline PM_RegionImp<PM_BbValue>* GetPreviousValueRegion();

    //Returns a pointer to the associated threshold region.
	//##ModelId=3FA1611002E3
    inline PM_RegionImp<PM_BbCfg>* GetConfigRegion();

    //Starts a new period, resets data and prepared for next 
    //accumulation period. When invalid flag is set to true,
    //the new accumulation period is set to invalid, i.e.
    //all IDF of all parameters are set to invalid.
    //##ModelId=3C1F6F6D013E
    virtual void StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag = false);

    //This method switches the content of the current and 
    //previous register.
    //##ModelId=3C1F6F6D0134
    virtual void SwitchOnPeriod(FC_Time theCurrentPeriod);
	virtual bool IsSameDate(FC_Time theStartPeriod, FC_Time theEndPeriod);

    //Reference to the generic PM application.
	//##ModelId=3FA1611002F3
    PM_GenericApplication &myGenericApplication;

    //The accumulation period type of this instance.
    //##ModelId=3C1F6F6D0370
    CT_PM_Period myPeriod;

	// Flag to indicate the need to update notify the previous value
	// region at the end of a control period.
	bool myUpdatePreviousValue;

    //The index of this control period. It can be seen like the port number.
    //##ModelId=3C1F6F6D0352
    uint16 myIndex;

    //The first time execution flag.
    //##ModelId=3E6E4CEA03C2
    bool myFirstTime;

    //The current period. This the time at which the current 
    //period start.
    //##ModelId=3C1F6F6D02BB
    FC_Time myCurrentPeriod;

    //The period start time offset.
    //##ModelId=3C1F6F6D0315
    time_t myPeriodStartTimeOffset;

    //The day light saving time offset (generally 1 or 0 hr).
    //##ModelId=3E6E4CEA0191
    time_t myDayLightSavingTimeOffset;

    //A reference to the accumulation period controled by this instance.
    //##ModelId=3C1F6F6D02A8
    PM_AccumulationPeriod& myAccPeriod;

    //The accumulation period duration. This parameter is the 
    //only one that has a different value regarding that this 
    //is a 15 minute or a 1 day period.
    //##ModelId=3C1F6F6D02D9
    time_t myPeriodInSecond;

    //This indicates if warning must be printed if PM is not 
    //executed in time.
    //##ModelId=3C1F6F6D0329
    bool myWarning;

    //For test purpose only.
    //##ModelId=3C1F6F6D0333
    char* myPeriodString;

    //String identifying the processor.
    //##ModelId=3C1F6F6D038D
    char* myProcessorTypeString;
};

//-----------------------------------------------------------------
//##ModelId=3C1F6F6D0120
inline void PM_ControlPeriod::SetWarning(bool theWarning)
{
    myWarning = theWarning;

}

//-----------------------------------------------------------------
//##ModelId=3FA1611002C4
inline PM_RegionImp<PM_BbValue>* PM_ControlPeriod::GetCurrentValueRegion()
{
    return myGenericApplication.GetCurrentRegionValue(myPeriod);

}

//-----------------------------------------------------------------
//##ModelId=3FA1611002D3
inline PM_RegionImp<PM_BbValue>* PM_ControlPeriod::GetPreviousValueRegion()
{
    return myGenericApplication.GetPreviousRegionValue(myPeriod);

}

//-----------------------------------------------------------------
//##ModelId=3FA1611002E3
inline PM_RegionImp<PM_BbCfg>* PM_ControlPeriod::GetConfigRegion()
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

#endif //PM_CONTROLPERIOD_H
