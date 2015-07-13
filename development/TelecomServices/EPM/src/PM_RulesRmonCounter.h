/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     TRN
 AUTHOR   :     December 21, 2005   Larry Wolfrum.
 DESCRIPTION:   The class to update RMON counter PM .
--------------------------------------------------------------------------*/

#ifndef PM_RULESRMONCOUNTER_H
#define PM_RULESRMONCOUNTER_H

#include <CommonTypes/CT_Telecom.h>
#include <EPM/PM_TypeRmon.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AutoRateLockRmon.h>

using namespace std;

// Forward declaration of classes
class PM_BbCountRmon;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of the
//RMON Counter layer. These accumulation rules are deduced
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesRmonCounter :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesRmonCounter(PM_GenericApplication& theGenericApplication, 
                uint16                 theIndex);

    //Class default destructor.
    virtual ~PM_RulesRmonCounter();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for RMON Counters. This 
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

	// Returns Auto-Rate Lock inhibit profile array
	virtual bool* GetAutoRateInhibitProfile();

	// Returns an indication that the Auto-Rate state has changed
	virtual bool IsAutoRateStateRefreshed();

private:

    //Reference to the collector's RMON counter BB object.
    PM_BbCountRmon&  myCounterRmon;

    //First time flag.
    bool myFirstTime;

	// Auto Rate Lock control object.
	PM_AutoRateLockRmon myAutoRateLock;

    //Signal type of data.    
    CT_TEL_SignalType   mySignalType;
};

#endif //PM_RULESRMONCOUNTER_H

