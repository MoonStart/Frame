/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     8 Oct 2010   Larry Wolfrum
 DESCRIPTION:   The class to update TCM PM.
--------------------------------------------------------------------------*/

#ifndef PM_RULESTCM_H
#define PM_RULESTCM_H

#include <CommonTypes/CT_Telecom.h>
#include <EPM/PM_TypeTcm.h>
#include <PM/src/PM_Rules.h>

using namespace std;

// Forward declaration of classes
class PM_BbDefectTcm;
class PM_BbCountTcm;
class PM_BbGeneralCfg;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of 
//ODU layer. These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesTcm :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesTcm(PM_GenericApplication& theGenericApplication, 
                uint16                 theIndex);

    //Class default destructor.
    virtual ~PM_RulesTcm();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for ODU. This 
    //method is called every second to update accumulation 
    //rules. It also updates all accumulation periods 
    //affected by these rules. The behavior of this method is 
    //not affected by the end of any accumulation period. All 
    //accumulation period included in myVectorOfAccPeriod are 
    //responsible to re-run itself when the accumulation 
    //period is finished. Note that this method must be 
    //overloaded be the specialized layer to determine to 
    //rules and the overloaded method must call this method 
    //to update the parameters influence by this rules.
    virtual void UpdateRules(bool* theFilteringStateFirstStage,
                             bool* theFilteringStateSecondStage);

private:

    //Reference to the collector's ODU defect BB object.
    PM_BbDefectTcm& myDefectTcm;

    //Reference to the collector's ODU counter BB object.
    PM_BbCountTcm&  myCounterTcm;

    //Pointer to the XY value BB object.
    PM_BbGeneralCfg& myXYvalue;

    //Status of defects that inhibit the accumulation of 
    //parameters for the current second.
    bool myDefect;

    //First time flag.
    bool myFirstTime;

    //Signal type of data.
    CT_TEL_SignalType   mySignalType;

    CT_TCM_Mode myTcmMode;
};

#endif //PM_RULESTCM_H


