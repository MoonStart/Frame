/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004   Hemant Thakkar.
 DESCRIPTION:   The class to update Far-End SONET/SDH MS PM .
--------------------------------------------------------------------------*/

#ifndef PM_RULESMSFAREND_H
#define PM_RULESMSFAREND_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_TypeMsFarEnd.h>
#include <PM/src/PM_Rules.h>

using namespace std;

// Forward declaration of classes
class PM_BbDefectMsFarEnd;
class PM_BbFailureMsFarEnd;
class PM_BbCountMsFarEnd;
class PM_BbGeneralCfg;
class PM_GenericApplication;
class PM_BbIdf;

//This class is responsible of the accumulation rules of 
//Far-End SONET/SDH MS layer. These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesMsFarEnd :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesMsFarEnd(PM_GenericApplication& theGenericApplication, 
               uint16                 theIndex);

    //Class default destructor.
    virtual ~PM_RulesMsFarEnd();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for Far-End SONET/SDH MS. This 
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

    //Reference to the collector's Far-End MS defect BB object.
    PM_BbDefectMsFarEnd& myDefectMsFarEnd;

    //Reference to the collector's MS counter BB object.
    PM_BbCountMsFarEnd&  myCounterMsFarEnd;

    //Reference to the collector's MS failure BB object.
    PM_BbFailureMsFarEnd& myFailureMsFarEnd;

    //Pointer to the X value BB object.
    PM_BbGeneralCfg& myXvalue;

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

};

#endif //PM_RULESMSFAREND_H


