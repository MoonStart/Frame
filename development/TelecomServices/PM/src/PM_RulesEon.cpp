/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   The class to update EON parameters.
--------------------------------------------------------------------------*/

#include <TelCommon/TEL_BbRegionBaseImp.h>
#include <Monitoring/MON_AppIf.h>
#include <Monitoring/MON_RsCounters.h>

#include <PM_GenericApplication.h>
#include <PM/PM_BbCountEon.h>
#include <PM/PM_BbGeneralCfg.h>
#include <PM/PM_RegionImp.h>
#include <PM/PM_MainBaseSubApplication.h>
#include <PM/src/PM_AccPeriod.h>
#include <PM/src/PM_RulesEon.h>


//-----------------------------------------------------------------
// Class default constructor.
//##ModelId=3FA1610902A9
PM_RulesEon::PM_RulesEon (PM_GenericApplication& theGenericApplication, uint16 theIndex):
    PM_Rules(theGenericApplication, theIndex, PM_TypeEon::PM_PARAM_NUM),
    myCounterEon( (*myGenericApplication.GetRegionCountEon())[theIndex])
{
    Init();

}

//-----------------------------------------------------------------
// Class default destructor.
//##ModelId=3FA1610902AC
PM_RulesEon::~PM_RulesEon ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3FA1610902AE
void PM_RulesEon::Init()
{
    myFirstTime = true;

    // Call base class method.
    PM_Rules::Init();

}

//-----------------------------------------------------------------
//##ModelId=3FA1610902B8
void PM_RulesEon::UpdateRules(bool* theFilteringStateFirstStage, bool* theFilteringStateSecondStage) 
{
    // Parameter index.
    uint32          param;
    // Iteraror of Accumulation Period
    vector<PM_AccumulationPeriod*>::iterator    i;


    //
    // Determine validity state:
    //

    // At first iteration only.
    if (myFirstTime)
    {
        // For all parameters.
        for (param = 0; param < PM_TypeEon::PM_PARAM_NUM; param++)
        {
            // Set availability for all Accumulation periods.
            // IDF is available if monitoring status is valid, otherwise it is not available.
            for (i = myVectorOfAccumulationPeriod.begin(); i != myVectorOfAccumulationPeriod.end(); i++)
            {
                (*i)->SetAvailability(param, myValidityState[param]);
            }
        }
        // Update first time flag.
        myFirstTime = false;
    }

    //
    // Apply rules:
    //

    myCurrentValueParam[PM_TypeEon::PM_ICMPDUR].UnsignedValue = myCounterEon.GetIcmpDur();
    myCurrentValueParam[PM_TypeEon::PM_ICMPDUT].UnsignedValue = myCounterEon.GetIcmpDut();
    myCurrentValueParam[PM_TypeEon::PM_ICMPER].UnsignedValue = myCounterEon.GetIcmpEr();
    myCurrentValueParam[PM_TypeEon::PM_ICMPTTLER].UnsignedValue = myCounterEon.GetIcmpTtler();
    myCurrentValueParam[PM_TypeEon::PM_IPADDER].UnsignedValue = myCounterEon.GetIpAdder();
    myCurrentValueParam[PM_TypeEon::PM_IPDISCR].UnsignedValue = myCounterEon.GetIpDiscr();
    myCurrentValueParam[PM_TypeEon::PM_IPDISCT].UnsignedValue = myCounterEon.GetIpDisct();
    myCurrentValueParam[PM_TypeEon::PM_IPHDRR].UnsignedValue = myCounterEon.GetIpHdrr();
    myCurrentValueParam[PM_TypeEon::PM_IPNOROUTEST].UnsignedValue = myCounterEon.GetIpNoroutest();

    //
    // Determine TCA filtering state:
    //

    // No filtering at all.

    //Call the method of the base class.
    PM_Rules::UpdateRules();

}
