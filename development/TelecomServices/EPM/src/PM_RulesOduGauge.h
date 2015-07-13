/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   The class to update ODU PM gauges.
--------------------------------------------------------------------------*/

#ifndef PM_RULESODUGAUGE_H
#define PM_RULESODUGAUGE_H

#include <CommonTypes/CT_Telecom.h>
#include <EPM/PM_TypeOdu.h>
#include <PM/src/PM_Rules.h>

using namespace std;

// Forward declaration of classes
class PM_BbStatusOduGauge;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of the
//ODU Gauge layer. These accumulation rules are deduced from
//the status given by the Collector. These rules are used by
//the Accumulation Period classes that are responsible to
//accumulate parameters for the signal listed above.
class PM_RulesOduGauge :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesOduGauge(PM_GenericApplication& theGenericApplication, uint16 theIndex);

    //Class default destructor.
    virtual ~PM_RulesOduGauge();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for Odu Gauges. This 
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

    //Reference to the collector's Odu status BB object.
    PM_BbStatusOduGauge& myStatusOduGauge;

    //First time flag.
    bool myFirstTime;
};

#endif //PM_RULESODUGAUGE_H

