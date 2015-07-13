/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     26 Oct 2009   Larry Wolfrum
 DESCRIPTION:   The class to update ODU PM.
--------------------------------------------------------------------------*/

#ifndef PM_RULESODU_H
#define PM_RULESODU_H

#include <CommonTypes/CT_Telecom.h>
#include <EPM/PM_TypeOdu.h>
#include <PM/src/PM_Rules.h>

using namespace std;

// Forward declaration of classes
class PM_BbDefectOdu;
class PM_BbCountOdu;
class PM_BbStatusOdu;
class PM_BbGeneralCfg;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of 
//ODU layer. These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
class PM_RulesOdu :  public PM_Rules
{
public:

    //Class default constructor.
    PM_RulesOdu(PM_GenericApplication& theGenericApplication, 
                uint16                 theIndex);

    //Class default destructor.
    virtual ~PM_RulesOdu();

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

    //Reference to the collector's ODU defect BB object.
    PM_BbDefectOdu& myDefectOdu;

    //Reference to the collector's ODU counter BB object.
    PM_BbCountOdu&  myCounterOdu;

    //Reference to the collector's ODU Status BB object.
    PM_BbStatusOdu&  myStatusOdu;

    //Pointer to the XY value BB object.
    PM_BbGeneralCfg& myXYvalue;

    //Status of defects that inhibit the accumulation of 
    //parameters for the current second.
    bool myDefect;

    //First time flag.
    bool myFirstTime;

    //Signal type of data.
    CT_TEL_SignalType   mySignalType;
};

#endif //PM_RULESODU_H


