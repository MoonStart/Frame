/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004   Hemant Thakkar.
 DESCRIPTION:   The class to update Near-End SONET/SDH MS PM .
--------------------------------------------------------------------------*/

#ifndef PM_RULESMSNEAREND_H
#define PM_RULESMSNEAREND_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_TypeMsNearEnd.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AutoRateLockMsNearEnd.h>

using namespace std;

// Forward declaration of classes
class PM_BbDefectMsNearEnd;
class PM_BbFailureMsNearEnd;
class PM_BbCountMsNearEnd;
class PM_BbStatusMsNearEnd;
class PM_BbGeneralCfg;
class PM_GenericApplication;
class PM_BbIdf;

//This class is responsible of the accumulation rules of 
//Near-End SONET/SDH MS layer. These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesMsNearEnd :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesMsNearEnd(PM_GenericApplication& theGenericApplication, 
               uint16                 theIndex);

    //Class default destructor.
    virtual ~PM_RulesMsNearEnd();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for Near-End SONET/SDH MS. This 
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

    //Reference to the collector's MS defect BB object.
    PM_BbDefectMsNearEnd& myDefectMsNearEnd;

    //Reference to the collector's MS counter BB object.
    PM_BbCountMsNearEnd&  myCounterMsNearEnd;

    //Reference to the collector's MS failure BB object.
    PM_BbFailureMsNearEnd& myFailureMsNearEnd;

    //Reference to the collector's MS status BB object.
    PM_BbStatusMsNearEnd& myStatusMsNearEnd;

    //Pointer to the X value BB object.
    PM_BbGeneralCfg& myXYvalue;

    //Signal type of data.
    CT_TEL_SignalType   mySignalType;

    //Status of defects that inhibit the accumulation of 
    //parameters for the current second.
    bool    myDefect;

    //First time flag.
    bool myFirstTime;

    // Array of IDF objects for all parameters.
    PM_BbIdf* my15MIdf;
    PM_BbIdf* myDayIdf;

	// Auto Rate Lock control object.
	PM_AutoRateLockMsNearEnd myAutoRateLock;

};

#endif //PM_RULESMSNEAREND_H


