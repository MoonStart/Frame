/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     February 1, 2001
 DESCRIPTION:   The class to update OTU parameters.
--------------------------------------------------------------------------*/

#ifndef PM_RULESOTU_H
#define PM_RULESOTU_H

#include <vector>
#include <CommonTypes/CT_Telecom.h>
#include <PM/src/PM_Rules.h>


// Forward declaration of classes
class PM_BbDefectOtu;
class PM_BbCountOtu;
class PM_BbStatusOtu;
class PM_BbIdf;
class PM_BbGeneralCfg;

//This class is responsible of the accumulation rules of 
//Optical Transport Unit layer. These accumulation rules are 
//deduced from the counters and defects given by the 
//Collector. These rules are used by the Accumulation Period 
//classes that are responsible to update parameters for OTU 
//layer.
//##ModelId=3C9255A80221
class PM_RulesOtu : public PM_Rules
{
public:

    //Class default constructor.
    //##ModelId=3C9255A90092
    PM_RulesOtu(PM_GenericApplication& theGenericApplication, 
                uint16                 theIndex);

    //Class default destructor.
    //##ModelId=3C9255A900BA
    virtual ~PM_RulesOtu();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA1610C03BF
    virtual void Init();

    //Updates the accumulation rules for OTU. This 
    //method is called every second to update accumulation 
    //rules. It also updates all accumulation periods 
    //affected by these rules. The behavior of this method is 
    //not affected by the end of any accumulation period. All 
    //accumulation period included in myVectorOfAccPeriod are 
    //responsible to re-run itself when the accumulation 
    //period is finished.
    //##ModelId=3C9255A900BC
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

    //Reference to the collector's Otu defect BB object.
    //##ModelId=3E6E4CCC038E
    PM_BbDefectOtu& myDefectOtu;

    //Reference to the collector's Otu counter BB object.
    //##ModelId=3E6E4CCC03D4
    PM_BbCountOtu& myCounterOtu;

    //Reference to the collector's OTU status BB object.
    PM_BbStatusOtu& myStatusOtu;

    //Pointer to the Y value BB object.
    PM_BbGeneralCfg& myYvalue;

    //Signal type of data.
    CT_TEL_SignalType   mySignalType;

    //First time flag.
	//##ModelId=3FA1610C03D1
    bool myFirstTime;

    // Array of IDF objects for all parameters.
    PM_BbIdf* my15MIdf;
    PM_BbIdf* myDayIdf;

};

#endif //PM_RULESOTU_H


