/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Sebastien Cossette, March 07, 2002.
 DESCRIPTION:   PM End of service Action.
--------------------------------------------------------------------------*/

#ifndef PM_ENDOFPERIOD_ACTION_H
#define PM_ENDOFPERIOD_ACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <ExecutionSupport/FC_ListOfAction.h>
#include <CommonTypes/CT_PM_Definition.h>
#include <TimeService/FC_Time.h>

#include <PM/PM_Def.h>


using namespace std;

class PM_BbEndOfPeriod;
class PM_BbGeneralCfg;

//End of period action executed every 30 seconds. This action 
//verifies if period has ended or if time has changed since 
//last time of day reading. If these cases clients registered 
//to call back are invoked using their actions.
//##ModelId=3C9255A2001B
class PM_EndOfPeriodAction : public FC_Action
{
public :

    //Returns an instance of end of period action. This 
    //allows client to register or unregister to callback 
    //service.
    //##ModelId=3C9255A201FA
    static PM_EndOfPeriodAction& GetInstance();

    //Virtual destructor.
    //##ModelId=3C9255A201FC
    virtual ~PM_EndOfPeriodAction();

    //Initializes all attributes when creating end of period 
    //action.
    //##ModelId=3C9255A20205
    void Init(PM_BbEndOfPeriod& theEndOfPeriod,
              PM_BbGeneralCfg&  theGeneralCfg);

    //Not supported.
    //##ModelId=3C9255A20218
    virtual void Run(FC_Object* theObject = NULL);

    //Executed periodically to verify end of period or time 
    //change.
    //##ModelId=3C9255A20222
    virtual FC_Object* DoRunWithReason(unsigned   theRunReason,
                                       FC_Object* theInvokerObj,
                                       FC_Object* theParam= NULL);

    //Permits client to register to end of period call back 
    //service for the specified period.
    //##ModelId=3C9255A20236
    void RegisterCallback(CT_PM_Period thePeriod, 
                          FC_Action    &theWakeupAction);

    //Permits client to un-register to end of period call 
    //back service for the specified period.
    //##ModelId=3C9255A20241
    void UnregisterCallback(CT_PM_Period thePeriod, 
                            FC_Action    &theWakeupAction);

private:

    //End of period action instance pointer.
    //##ModelId=3C9260850092
    static PM_EndOfPeriodAction* myInstance;

    //Constructor.
    //##ModelId=3C9255A20268
    PM_EndOfPeriodAction();

    //Wakes-up all client's actions.
    //##ModelId=3C9255A20272
    void WakeUpCallback(CT_PM_Period thePeriod);
    
    //Pointer to the end of period object.
    //##ModelId=3C92608500AE
    PM_BbEndOfPeriod*       myEndOfPeriodObject;
    //Pointer to the general configuration region.
    //##ModelId=3C92608500C2
    PM_BbGeneralCfg*        myGeneralCfg;

    //Last period start time.
    //##ModelId=3E6FC0170358
    FC_Time                 myLastPeriod[CT_PM_PERIOD_UNKNOWN];

    //Array of list of client action to invoke when calling back client.
    //##ModelId=3C92608500F3
    FC_ListOfAction         myWakeupProcess[CT_PM_PERIOD_UNKNOWN];

    //The last time the time of day was read.
    //##ModelId=3C9255A202D6
    FC_Time  myTime;

};

#endif //PM_ENDOFPERIOD_ACTION_H
