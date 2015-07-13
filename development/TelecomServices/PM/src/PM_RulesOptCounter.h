/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004   Hemant Thakkar.
 DESCRIPTION:   The class to update Opt SONET/SDH MS PM .
--------------------------------------------------------------------------*/

#ifndef PM_RULESOPTCOUNTER_H
#define PM_RULESOPTCOUNTER_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_TypeOpt.h>
#include <PM/src/PM_Rules.h>
#include <PM/PM_BbStatusOptCounter.h>

using namespace std;

class PM_BbStatusOptCounter;
class PM_BbGeneralCfg;
class PM_GenericApplication;
class PM_BbIdf;

//This class is responsible of the accumulation rules of 
//OPT SONET/SDH MS layer. These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesOptCounter :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesOptCounter(PM_GenericApplication& theGenericApplication, 
               uint16                 theIndex);

    //Class default destructor.
    virtual ~PM_RulesOptCounter();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for OPT SONET/SDH MS. This 
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

    //Returns the status of a change in revertive mode of
    //signal protection mode.
    bool EverPresentRevertiveMode();

    //Was the facility ever present in a protection scheme.
    bool EverPresentInProtectionScheme();

	// Was the state of the protection scheme changed?
	bool EverChangedProtectionScheme();

	// Was the revertive mode changed?
	bool EverChangedRevertiveMode();

private:

    //Reference to the collector's MS status BB object.
    PM_BbStatusOptCounter& myStatusOpt;

    //Signal type of data.
    CT_TEL_SignalType   mySignalType;

    //First time flag.
    bool myFirstTime;

    // Array of IDF objects for all parameters.
    PM_BbIdf* my15MIdf;
    PM_BbIdf* myDayIdf;

};

#endif //PM_RULESOPTCOUNTER_H


