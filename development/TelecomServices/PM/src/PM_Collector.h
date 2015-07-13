/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     February 15, 1999 Marc-Andre Ledoux.
 DESCRIPTION:   Collect the data needed by the PM Processor.
--------------------------------------------------------------------------*/

#ifndef PM_COLLECTOR_H
#define PM_COLLECTOR_H

#include <gdef.h>
#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_Milliseconds.h>


// Forward class declaration.
class FC_Object;
class FC_OneShotProcess;
class PM_GenericApplication;

//The Collector collects data need by the Processor. This 
//data are needed once every second. All the data coming from 
//the Facility Monitoring are in form of a free running 
//counter. To provide the Processor with this data, the 
//Collector has to memorizing the values of the free running 
//counters for the previous and current second.
//##ModelId=3C1F6F850084
class PM_Collector: public FC_Action
{
public:

    //The Collector's constructor.
    //##ModelId=3C1F6F8503A5
    PM_Collector(PM_GenericApplication& theGenericApplication,
                 FC_OneShotProcess&     theProcessorProcess,
                 char*                  theCollectorTypeString,
                 uint32                 theNumberOfPort);

    //The Collector's destructor.
    //##ModelId=3C1F6F8503B9
    virtual ~PM_Collector();

    //This method initializes region reference's used by the 
    //Collector. The collector must be initialized prior the 
    //execution of the process for the first time.
    //##ModelId=3C1F6F8503BB
    virtual void Init() = 0;

    //Updates PM statuses contain in the blackboard when the 
    //card region is active. Otherwise reset the data.
    //
	//##ModelId=3E6E4D2B03B1
    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                       FC_Object* theInvokerObj,
                                       FC_Object* theParam= NULL);

    //Obsolete method
    //##ModelId=3C1F6F8503C4
    virtual void Run(FC_Object* theObject = NULL);

    //TEST MENU COMMANDS

    //Test menu command. Sets warning on/off. The default 
    //value is off. If PM is not execute in time, it will 
    //print a warning.
    //##ModelId=3C1F6F8503D0
    void SetWarning(bool theWarning);

    //Returns the instance's name.
    //##ModelId=3C9255C8005A
    virtual const char*  GetInstanceName( void ) const;

    //Updates PM statuses contain in the blackboard. The data 
    //is derived from the Facility Monitoring . The Collector 
    //blackboard regions will be used by the Processor.
	//##ModelId=3E6E4D2C03DB
    virtual void ProcessData();

    //Resets data since card region is inactive.
	//##ModelId=3E6E4D2D00B1
    virtual void ResetData();

protected:

    //Verifies if the Collector executed in time. The 
    //Collector 
    //must be executed at each second. If it is executed 
    //before or after 50 ms of its suppose executing time, a 
    //warning message will be display at the console (if 
    //warning is enable).
    //
    //PARAM currentTick: The current tick in millisecond.
    //##ModelId=3C1F6F86000E
    void Verify(FC_Milliseconds currentTick);

    //This method does a WakeUp on the given processor. The 
    //processor handle is given at construction of this class.
    //##ModelId=3C1F6F860019
    void WakeUpProcessor();

    //A reference to the generic application.
    //##ModelId=3C1F6F86002D
    PM_GenericApplication& myGenericApplication;

    //This indicates if it is the first execution of Collector.
    //##ModelId=3C1F6F860040
    bool myFirstTimeRun;

    //This indicates if warning must be printed.
    //##ModelId=3C1F6F86005E
    bool myWarning;
   
    //The tick at the previous execution (need to know if the Collector is executed in time).
    //##ModelId=3C1F6F860073
    FC_Milliseconds myLastTick;

    //The number of port supported by this collector instance.
    //##ModelId=3C5016340268
    uint32 myNumberOfPort;
    
    //The name of the instance.
    //##ModelId=3C9255C8012D
    string myInstanceName;

    // Flag indicating that the time on the module has been
    // synchronized with the active controller.
    bool myIsTimeSyncedWithController;

private:

    //A reference to the PM processor. This process will be 
    //waken up after the collection of data is finished for 
    //the current second.
    //##ModelId=3C1F6F860091
    FC_OneShotProcess& myProcessorProcess;

    //The collector string: indicates the name of the 
    //collector. Its layer.
    //##ModelId=3C1F6F8600A4
    char* myCollectorTypeString;

};

#endif //PM_COLLECTOR_H
