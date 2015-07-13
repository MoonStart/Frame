/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   Base class of SNMP Processing.
--------------------------------------------------------------------------*/

#ifndef SNMP_PROCESSOR_H
#define SNMP_PROCESSOR_H

#include <vector>
#include <TimeService/FC_Time.h>
#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_Milliseconds.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <SNMP/SNMP_RmonEtherHistController.h>

using namespace std;

// Forward class declaration.

class SNMP_Processor:    public FC_Action
{

public:

    SNMP_Processor(char* theProcessorTypeString);
    
    virtual ~SNMP_Processor();
    virtual void Init();
    virtual void CreateActionsInstances();
    virtual void DeleteActionsInstances();
    virtual void Run(FC_Object* theObject = NULL);
    void SetWarning(bool theWarning);

protected:
    FC_Milliseconds myLastTick;
    char* myProcessorTypeString;

    //The name of the instance.
    string myInstanceName;

private:

    //This indicates if warning must be printed if Processor 
    //is not executed in time.
    bool myWarning;

    //The system time at the last execution of the Processor.
    FC_Time myLastTime;

};

#endif //SNMP_PROCESSOR_H
 
