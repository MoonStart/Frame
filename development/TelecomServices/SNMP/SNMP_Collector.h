/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_COLLECTOR_H
#define SNMP_COLLECTOR_H

#include <vector>
#include <gdef.h>
#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <CommonTypes/CT_FacilityIds.h>

using namespace std;

// Forward class declaration.
class MON_AppIf;
class FC_Object;
class FC_OneShotProcess;
class T6100_CardActiveRegion;
class T6100_TelecomIf;

class SNMP_Collector : public FC_Action
{
public:

    SNMP_Collector(T6100_TelecomIf& theTelecomIf,
                   MON_AppIf&       theMonApp,
                   char* theCollectorTypeString,
                   CT_IntfId thePortId);

    virtual ~SNMP_Collector();

    virtual void Init() = 0;

    virtual FC_Object* DoRunWithReason(unsigned theRunReason,
                                       FC_Object* theInvokerObj,
                                       FC_Object* theParam= NULL);

    //Obsolete method
    virtual void Run(FC_Object* theObject = NULL);

    void AddProcessor(FC_OneShotProcess* theProcess);

    //TEST MENU COMMANDS

    //Test menu command. Sets warning on/off. The default 
    //value is off. If PM is not execute in time, it will 
    //print a warning.
    void SetWarning(bool theWarning);

    //Returns the instance's name.
    virtual const char*  GetInstanceName( void ) const;

    virtual void ProcessData();
    virtual void ResetData();

protected:

    //Verifies if the Collector executed in time. The 
    //Collector must be executed at each second. If it is executed 
    //before or after 50 ms of its suppose executing time, a 
    //warning message will be display at the console (if 
    //warning is enable).
    //
    //PARAM currentTick: The current tick in millisecond.
    void Verify(FC_Milliseconds currentTick);

    //This method does a WakeUp on the given processor. The 
    //processor handle is given at construction of this class.
    void WakeUpProcessors();

    //This indicates if it is the first execution of Collector.
    bool myFirstTimeRun;

    //This indicates if warning must be printed.
    bool myWarning;
   
    //The tick at the previous execution (need to know 
    // if the Collector is executed in time).
    FC_Milliseconds myLastTick;

    //The name of the instance.
    string myInstanceName;

    MON_AppIf& myMonApp;

    CT_IntfId myIntfId;

private:

    //A reference to the SNMP processors. This process will be 
    //waken up after the collection of data is finished for 
    //the current second.
    vector<FC_OneShotProcess*> myProcessors;

    //The collector string: indicates the name of the 
    //collector. Its layer.
    char* myCollectorTypeString;

    T6100_CardActiveRegion& myCardActiveRegion;
};

#endif //SNMP_COLLECTOR_H
