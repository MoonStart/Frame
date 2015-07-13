/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, February 26, 2003.
 DESCRIPTION:   The class to update Channel Optical Power parameters.
--------------------------------------------------------------------------*/

#ifndef PM_RULESCOP_H
#define PM_RULESCOP_H

#include <vector>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_SystemIds.h>
#include <PM/src/PM_Rules.h>


// Forward declaration of classes
class PM_BbStatusCop;
class PM_BbDefectCop;

//This class is responsible of the accumulation rules of 
//Laser. These accumulation rules are deduced from the 
//statuses given by the Collector. These rules are used by the 
//Accumulation Period classes that are responsible to update 
//parameters for Channel Optical Power. 
//##ModelId=3E6E4CD601E2
class PM_RulesCop : public PM_Rules
{
public:

    //Class default constructor.
    //##ModelId=3E6E4CD7037F
    PM_RulesCop(PM_GenericApplication&  theGenericApplication, 
                uint16                  theIndex,
                CT_CardFamily           theCardFamily,
                CT_PM_Side              theSide);

    //Class default destructor.
    //##ModelId=3E6E4CD70393
    virtual ~PM_RulesCop();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA1610D02B6
    virtual void Init();

    //Updates the accumulation rules for Channel Optical. This 
    //method is called every second to update accumulation 
    //rules. It also updates all accumulation periods 
    //affected by these rules. The behavior of this method is 
    //not affected by the end of any accumulation period. All 
    //accumulation period included in myVectorOfAccPeriod are 
    //responsible to re-run itself when the accumulation 
    //period is finished.
    //##ModelId=3E6E4CD7039D
    virtual void UpdateRules(bool* theFilteringStateFirstStage,
                             bool* theFilteringStateSecondStage);

private:

    //Reference to the collector's Cop status BB object.
    //##ModelId=3E6FC03900C1
    PM_BbStatusCop&  myStatusCop;

    //Reference to the collector's Cop defect BB object.
    //##ModelId=3E6FC0390111
    PM_BbDefectCop&  myDefectCop;

    //First time flag.
	//##ModelId=3FA1610D02C6
    bool myFirstTime;

    // Card family associated with the processor context.
	//##ModelId=3FA1610D02D6
    CT_CardFamily myCardFamily;

    // My side.
    CT_PM_Side mySide;

};

#endif //PM_RULESCOP_H


