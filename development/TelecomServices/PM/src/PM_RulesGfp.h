/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM
 AUTHOR   :     22 April 2004   Hemant Thakkar.
 DESCRIPTION:   The class to update GFP PM .
--------------------------------------------------------------------------*/

#ifndef PM_RULESGFP_H
#define PM_RULESGFP_H

#include <CommonTypes/CT_Telecom.h>
#include <PM/PM_TypeGfp.h>
#include <PM/src/PM_Rules.h>

using namespace std;

// Forward declaration of classes
class PM_BbCountGfp;
class PM_BbDefectGfp;
class PM_BbGeneralCfg;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of 
//GFP layer. These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesGfp :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesGfp(PM_GenericApplication& theGenericApplication, 
                uint16                 theIndex);

    //Class default destructor.
    virtual ~PM_RulesGfp();

    //Initializes rules at beginning of execution or after
    //context becomes available.
    virtual void Init();

    //Updates the accumulation rules for GFP. This 
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

    //Reference to the collector's MS defect BB object.
    PM_BbDefectGfp& myDefectGfp;

    //Reference to the collector's MS counter BB object.
    PM_BbCountGfp&  myCounterGfp;

    //Pointer to the X value BB object.
    PM_BbGeneralCfg& myXvalue;

    //Signal type of data.
    CT_TEL_SignalType   mySignalType;

    //Status of defects that inhibit the accumulation of 
    //parameters for the current second.
    bool    myDefect;

    //First time flag.
    bool myFirstTime;

};

#endif //PM_RULESGFP_H


