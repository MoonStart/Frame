/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     Sebastien Cossette, March 07, 2002.
 DESCRIPTION:   PM End of service Action.
--------------------------------------------------------------------------*/

#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#include <T6100_MainAppIf.h>
#include <TelCommon/TEL_BbRegionBaseImp.h>

#include <PM_Def.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/PM_BbEndOfPeriod.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_EndOfPeriodAction.h>


//##ModelId=3C9260850092
PM_EndOfPeriodAction* PM_EndOfPeriodAction::myInstance = NULL;


//-----------------------------------------------------------------
//##ModelId=3C9255A201FA
PM_EndOfPeriodAction& PM_EndOfPeriodAction::GetInstance()
{
    if(myInstance == NULL)
        myInstance = new PM_EndOfPeriodAction();

    return *myInstance;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A20268
PM_EndOfPeriodAction::PM_EndOfPeriodAction()
    :myEndOfPeriodObject(NULL),
     myGeneralCfg(NULL),
     myTime(0)
{
    for (int i = 0; i < CT_PM_PERIOD_UNKNOWN; i++)
    {
        myLastPeriod[i] = 0;
    }

}

//-----------------------------------------------------------------
//##ModelId=3C9255A201FC
PM_EndOfPeriodAction::~PM_EndOfPeriodAction()
{
    delete myInstance;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A20205
void PM_EndOfPeriodAction::Init(PM_BbEndOfPeriod& theEndOfPeriod,
                                PM_BbGeneralCfg&  theGeneralCfg)
{
    FC_Time currentTime;


    myGeneralCfg = &theGeneralCfg;
    myEndOfPeriodObject = &theEndOfPeriod;

    // Get the actual time.
    currentTime.GetCurrentTime();

    myTime = currentTime;

    FC_Time current15M(currentTime / CT_PM_NUMBER_OF_SEC_IN_15M);
    FC_Time currentDay((currentTime.GetUTCTime() - myGeneralCfg->GetPeriodOffset(CT_PM_PERIOD_1_DAY)) / 
                        CT_PM_NUMBER_OF_SEC_IN_1DAY);

    myEndOfPeriodObject->SetPeriod(CT_PM_PERIOD_15_MINUTES, current15M);
    myEndOfPeriodObject->SetPeriod(CT_PM_PERIOD_1_DAY, currentDay);
    
    myLastPeriod[CT_PM_PERIOD_15_MINUTES] = current15M;
    myLastPeriod[CT_PM_PERIOD_1_DAY] = currentDay;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A20218
void PM_EndOfPeriodAction::Run(FC_Object* theObject)
{
    FC_THROW_ERROR(FC_SWError, "PM : Run method not supported!");

}

//-----------------------------------------------------------------
//##ModelId=3C9255A20222
FC_Object* PM_EndOfPeriodAction::DoRunWithReason(unsigned   theRunReason,
                                                 FC_Object* theInvokerObj,
                                                 FC_Object* theParam)
{
    FC_Time currentTime;
    FC_Time currentPeriod[CT_PM_PERIOD_UNKNOWN];
    bool    regionHasChanged = false;

    // Get the actual time.
    currentTime.GetCurrentTime();


    for (int i = 0; i < CT_PM_PERIOD_UNKNOWN; i++)
    {
        // Get the current accumulation period start time.
        currentPeriod[(CT_PM_Period)i] = PM_GetAccumulationPeriod((CT_PM_Period)i, currentTime, myGeneralCfg->GetPeriodOffset((CT_PM_Period)i));

        // If period has changed.
        
        //To check whether the time on both TARGET and QEMU is accurate. Can be removed after MR188601 fixed.
        //fc_cout<<"currentTime.GetUTCTime() - myTime.GetUTCTime()="<<currentTime.GetUTCTime() - myTime.GetUTCTime()<<endl;
        if(currentPeriod[i] != myLastPeriod[i])
        {
            myLastPeriod[i] = currentPeriod[i];
            myEndOfPeriodObject->SetPeriod((CT_PM_Period)i, currentPeriod[i]);
            WakeUpCallback((CT_PM_Period)i);
            regionHasChanged = true;
        }
        // If time has changed by more than PM_END_OF_PERIOD_REFRESH_SEC + 5 seconds.
        else if (abs((int)(currentTime.GetUTCTime() - myTime.GetUTCTime())) > (PM_END_OF_PERIOD_REFRESH_SEC + 5))
        {
            WakeUpCallback((CT_PM_Period)i);
        }
    }

    if(regionHasChanged)
    {
        T6100_MainAppIf::Instance().GetPmMainApp().GetRegionEndOfPeriod()->IncModificationCounter();
        T6100_MainAppIf::Instance().GetPmMainApp().GetRegionEndOfPeriod()->UpdateNotify();
    }

    // Update time.
    myTime = currentTime;

    return NULL;

}

//-----------------------------------------------------------------
//##ModelId=3C9255A20236
void PM_EndOfPeriodAction::RegisterCallback(CT_PM_Period thePeriod, 
                                            FC_Action    &theWakeupAction)
{
    myWakeupProcess[thePeriod].Insert(theWakeupAction);

}

//-----------------------------------------------------------------
//##ModelId=3C9255A20241
void PM_EndOfPeriodAction::UnregisterCallback(CT_PM_Period thePeriod, 
                                              FC_Action    &theWakeupAction)
{
    myWakeupProcess[thePeriod].Remove(theWakeupAction);

}

//-----------------------------------------------------------------
//##ModelId=3C9255A20272
void PM_EndOfPeriodAction::WakeUpCallback(CT_PM_Period thePeriod)
{
    myWakeupProcess[thePeriod].Run();

}

