/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders, RAMs  and OSCs.
 AUTHOR   :     20 July, 2000 Marc Vendette.
 DESCRIPTION:   The class to update Data (RS, FICON, ESCON, GbE, GOPT)
                parameters.
--------------------------------------------------------------------------*/

#ifndef PM_RULESDATA_H
#define PM_RULESDATA_H

#include <CommonTypes/CT_Telecom.h>
#include <Configuration/CFG_OptAutoRateLock.h>
#include <PM/PM_TypeData.h>
#include <PM/src/PM_Rules.h>
#include <EPM/src/PM_AutoRateLockData.h>

using namespace std;

// Forward declaration of classes
class PM_BbDefectData;
class PM_BbCountData;
class PM_BbGeneralCfg;
class PM_GenericApplication;

//This class is responsible of the accumulation rules of 
//Data (RS, FICON...). These accumulation rules are deduces 
//from the counters and defects given by the Collector. These 
//rules are used by the Accumulation Period classes that are 
//responsible to accumulate parameters for the signal listed 
//above.
//##ModelId=3C1F6F5903A2
class PM_RulesData :  public PM_Rules
{
public:

    //Class default constructor.
    //##ModelId=3C1F6F5A01EB
    PM_RulesData(PM_GenericApplication& theGenericApplication, 
                 uint16                 theIndex);

    //Class default destructor.
    //##ModelId=3C1F6F5A01F5
    virtual ~PM_RulesData();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA1610E015D
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
    //##ModelId=3C1F6F5A01F7
    virtual void UpdateRules(bool* theFilteringStateFirstStage,
                             bool* theFilteringStateSecondStage);

	// Returns Auto-Rate Lock inhibit profile array
	virtual bool* GetAutoRateInhibitProfile();

	// Returns an indication that the Auto-Rate state has changed
	virtual bool IsAutoRateStateRefreshed();

private:

    //Reference to the collector's Data defect BB object.
    //##ModelId=3C20AB670021
    PM_BbDefectData& myDefectData;

    //Reference to the collector's Data counter BB object.
    //##ModelId=3C20AB670053
    PM_BbCountData& myCounterData;

    //Pointer to the X/Y value BB object.
    //##ModelId=3C1F6F5A028C
    PM_BbGeneralCfg& myXYvalue;

    //Status of defects that inhibit the accumulation of 
    //parameters for the current second.
    //##ModelId=3C1F6F5A035E
    bool    myDefect;

    //Signal type of data.
    //##ModelId=3E6E4CDD01A7
    CT_TEL_SignalType   mySignalType;

    //First time flag.
	//##ModelId=3FA1610E017D
    bool myFirstTime;

	// Auto Rate Lock control object.
	PM_AutoRateLockData myAutoRateLock;
};

#endif //PM_RULESDATA_H


