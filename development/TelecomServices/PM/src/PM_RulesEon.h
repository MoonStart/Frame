/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     All.
 AUTHOR   :     June 13, 2003 Steve Thiffault.
 DESCRIPTION:   The class to update EON parameters.
--------------------------------------------------------------------------*/

#ifndef PM_RULESEON_H
#define PM_RULESEON_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_TypeEon.h>
#include <PM/src/PM_Rules.h>

using namespace std;

// Forward declaration of classes
class PM_BbCountEon;
class PM_BbGeneralCfg;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of 
//EON. These accumulation rules are deduces from the counters 
//given by the Collector. These rules are used by the Accumulation 
//Period classes that are responsible to accumulate parameters 
//for the signal listed above.
//##ModelId=3FA161090140
class PM_RulesEon :  public PM_Rules
{
public:

    //Class default constructor.
	//##ModelId=3FA1610902A9
    PM_RulesEon(PM_GenericApplication& theGenericApplication, uint16 theIndex);

    //Class default destructor.
	//##ModelId=3FA1610902AC
    virtual ~PM_RulesEon();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA1610902AE
    virtual void Init();

    //Updates the accumulation rules for Data. This 
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
	//##ModelId=3FA1610902B8
    virtual void UpdateRules(bool* theFilteringStateFirstStage,
                             bool* theFilteringStateSecondStage);

private:

    //Reference to the collector's EON counter BB object.
	//##ModelId=3FA164BE02B0
    PM_BbCountEon& myCounterEon;

    //First time flag.
	//##ModelId=3FA1610902C7
    bool myFirstTime;

};

#endif //PM_RULESEON_H


