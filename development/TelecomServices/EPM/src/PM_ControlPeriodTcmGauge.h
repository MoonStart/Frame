
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     December 6, 2010, Larry Wolfrum.
 DESCRIPTION:   TCM Control period class.
--------------------------------------------------------------------------*/

#ifndef PM_CONTROLPERIODTCMGAUGE_H
#define PM_CONTROLPERIODTCMGAUGE_H

#include <TimeService/FC_Time.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <PM/PM_GenericApplication.h>
#include <PM/src/PM_ControlPeriod.h>


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
class PM_ControlPeriodTcmGauge : public PM_ControlPeriod
{
public:

    //Class default constructor.
    PM_ControlPeriodTcmGauge(
                        PM_GenericApplication      &theGenericApplication,
                        CT_PM_Period               thePeriod,
                        PM_AccumulationPeriod&     theAccPeriod,
                        uint16                     theIndex,
                        char*                      theProcessorTypeString,
                        time_t                     thePstOffset = 0);

    //Class default destructor.
    virtual ~PM_ControlPeriodTcmGauge();

    //Controls the end of period of all accumulation periods.
    virtual void ControlPeriod(long    theCurrentTimeChanged, 
                               FC_Time theCurrentTime, 
                               time_t  thePstOffset = 0,
                               time_t  theDstOffset = 0);
   
protected:

    //Starts a new period, resets data and prepared for next 
    //accumulation period. When invalid flag is set to true,
    //the new accumulation period is set to invalid, i.e.
    //all IDF of all parameters are set to invalid.
    virtual void StartNewCurrentPeriod(FC_Time newCurrentPeriod, bool theInvalidFlag = false);

    //This method switches the content of the current and 
    //previous register.
    virtual void SwitchOnPeriod(FC_Time theCurrentPeriod);

private:

    uint16 myDynamicIndex;

};


#endif //PM_CONTROLPERIODTCMGAUGE_H
