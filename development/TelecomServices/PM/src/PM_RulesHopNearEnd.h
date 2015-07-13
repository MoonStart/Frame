/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     9 Feb 2004   Hemant Thakkar.
 DESCRIPTION:   The class to update Near-End SONET/SDH HOP PM .
--------------------------------------------------------------------------*/

#ifndef PM_RULESHOPNEAREND_H
#define PM_RULESHOPNEAREND_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_TypeHopNearEnd.h>
#include <PM/src/PM_Rules.h>

using namespace std;

// Forward declaration of classes
class PM_BbDefectHopNearEnd;
class PM_BbFailureHopNearEnd;
class PM_BbCountHopNearEnd;
class PM_BbGeneralCfg;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of 
//Near-End SONET/SDH HOP layer. These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesHopNearEnd :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesHopNearEnd(PM_GenericApplication& theGenericApplication, 
                       uint16                 theIndex,
                       CT_PM_Sts_Offset		 theSts1Offset);

    //Class default destructor.
    virtual ~PM_RulesHopNearEnd();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for Near-End SONET/SDH HOP. This 
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

    //Reference to the collector's HOP defect BB object.
    PM_BbDefectHopNearEnd& myDefectHopNearEnd;

    //Reference to the collector's HOP counter BB object.
    PM_BbCountHopNearEnd&  myCounterHopNearEnd;

    //Reference to the collector's HOP failure BB object.
    PM_BbFailureHopNearEnd& myFailureHopNearEnd;

    //Pointer to the X value BB object.
    PM_BbGeneralCfg& myXYvalue;

    //Signal type of data.
    CT_TEL_HopSpeMapping   mySpeMapping;

    //Status of defects that inhibit the accumulation of 
    //parameters for the current second.
    bool    myDefect;

    //First time flag.
    bool myFirstTime;

    // Offset of the starting STS-1 into the set of STS-1s contained
    // in the OC-192.
    CT_PM_Sts_Offset mySts1Offset;
};

#endif //PM_RULESHOPNEAREND_H


