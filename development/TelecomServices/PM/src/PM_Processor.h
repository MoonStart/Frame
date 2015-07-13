/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   Base class of PM Processing.
--------------------------------------------------------------------------*/

#ifndef PM_PROCESSOR_H
#define PM_PROCESSOR_H

#include <vector>
#include <TimeService/FC_Time.h>
#include <TimeService/FC_TimeService.h>
#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_GenericApplication.h>
#include <PM/PM_BbGeneralCfg.h>


using namespace std;

// Forward class declaration.
class PM_BbValue;
class PM_ControlPeriod;
class PM_GenericApplication;
class PM_AccumulationPeriod;
class PM_Rules;
class PM_RequestAction;

template <class OBJECT_TYPE> class PM_RegionImp;

//The Processor is the base class of Performance Monitoring 
//processing. His child has to compute the parameters. These 
//parameters are derived from the data supplied by the 
//Collector. The process of Processor is waked up by the 
//Collector every second.
//##ModelId=3C1F9DEF004E
class PM_Processor:    public FC_Action
{

public:

    //The default constructor of the Processor.
    //
    //PARAM theContext: The application context in which this 
    //class is used.
    //##ModelId=3C1F9DEF0210
    PM_Processor(PM_GenericApplication& theGenericApplication,
                 uint16                 theNumberOfPort, 
                 char*                  theProcessorTypeString);
    
    //The default destructor of the Processor.
    //##ModelId=3C1F9DEF022E
    virtual ~PM_Processor();

    //Initializes the Processor.
    //##ModelId=3C1F9DEF0230
    virtual void Init();

    //Creates actions used by the Processor. This class must 
    //be overloaded by the derived class.
    //##ModelId=3CBC723C01CE
    virtual void CreateActionsInstances() = 0;

    //Deletes actions used by the Processor.
    //##ModelId=3CBC723C01F6
    virtual void DeleteActionsInstances();

    //This method is responsible for detecting a system time 
    //change and prints an error message if "warning" is on. 
    //It is also responsible of the change of period and 
    //adjusts the current/previous regions via the 
    //ControlPeriod object for all accumulation period 
    //supported. Note that, this method must be called at the 
    //end of the Run of the derived Processor class.
    //##ModelId=3C1F9DEF0239
    virtual void Run(FC_Object* theObject = NULL);

    //Sets warning on/off. The default value is off. If PM is 
    //not execute in time, it will print a warning.
    //##ModelId=3C1F9DEF0244
    void SetWarning(bool theWarning);

	// Initializes the delay counter to invoke UpdateNotify()
	// on the previous value regions.
	virtual void InitPreviousValueUpdateDelay();

	// Method to determine if the processor is running.
	virtual bool GetRunningState();

protected:

    //Returns a reference to the generic configuration object.
    //##ModelId=3C9255BE013C
    PM_BbGeneralCfg& GetGenericConfigObject()
    {
        return (*myGenericApplication.GetPmMainApplication().GetRegionGeneralCfgvalue())[0];
    }

    //The system tick timer at the last execution of the 
    //processor.
    //##ModelId=3C1F9DEF028A
    FC_Milliseconds myLastTick;

    //This vector contains control period instance that is 
    //responsible for the 15-minutes accumulation period. The 
    //number of element in that vector is the same as the 
    //number of port handled by the Processor.
    //##ModelId=3C1F9DEF02A8
    vector<PM_ControlPeriod*> myControl15m;

    //This vector contains control period instance that is 
    //responsible for the 1-day accumulation period. The 
    //number of element in that vector is the same as the 
    //number of port handled by the Processor.
    //##ModelId=3C1F9DF0021C
    vector<PM_ControlPeriod*> myControlDay;

    //The string specifying the processor type.
    //##ModelId=3C1F9DF0023A
    char* myProcessorTypeString;

    //A reference to the PM generic application.
    //##ModelId=3C1F9DF00263
    PM_GenericApplication& myGenericApplication;

    //This vector contains Accumulation Period object 
    //instance for 15 minute period. The number of element in 
    //that vector is the same as the number of port handled 
    //by the specialized Processor.
    //##ModelId=3C1F9DF00277
    vector<PM_AccumulationPeriod*>  myAccPeriod15m;

    //This vector contains Accumulation Period object 
    //instance for 1 Day period. The number of element in 
    //that vector is the same as the number of port handled 
    //by //the specialized Processor.
    //##ModelId=3C1F9DF002A9
    vector<PM_AccumulationPeriod*>  myAccPeriodDay;

    //Pointer to the request action used to process the 
    //request of registers for 15-minutes period.
    //##ModelId=3C1F9DF002D1
    PM_RequestAction* myRegionRequestAction;

    //The index number.
    //##ModelId=3C1F9DF002F9
    uint32 myNumberOfPort;

    //This vector contains Parameter object instance. The 
    //number of element in that vector is the same as the 
    //number of port handled by the specialized Processor.
    //##ModelId=3C50162C0162
    vector<PM_Rules*>  myRules;

    //The name of the instance.
	//##ModelId=3E6E4CA200CF
    string myInstanceName;

    //This indicates if warning must be printed if Processor 
    //is not executed in time.
    //##ModelId=3C1F9DF00316
    bool myWarning;

    //The system time at the last execution of the Processor.
    //##ModelId=3C1F9DF00348
    FC_Time myLastTime;

	// Delay to invoke UpdateNotify() on previous value regions.
	uint32 myPreviousValueUpdateDelay;

	// Count of remaining seconds to invoke UpdateNotify()
	// on previous value regions.
	uint32 myPreviousValueUpdateCount;

	// Flag to indicate that the processor has started running.
	bool myFirstTime;

};

#endif //PM_PROCESSOR_H
 
