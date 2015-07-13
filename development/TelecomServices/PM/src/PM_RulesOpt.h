/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, February 26, 2003.
 DESCRIPTION:   The class to update Optical parameters.
--------------------------------------------------------------------------*/

#ifndef PM_RULESOPT_H
#define PM_RULESOPT_H

#include <vector>
#include <CommonTypes/CT_Telecom.h>
#include <PM/src/PM_Rules.h>
#include <PM/PM_TypeOpt.h>


// Forward declaration of classes
class PM_BbStatusOpt;

//This class is responsible of the accumulation rules of 
//Laser. These accumulation rules are deduced from the 
//statuses given by the Collector. These rules are used by the 
//Accumulation Period classes that are responsible to update 
//parameters for Optical. 
//##ModelId=3E6E4CC50256
class PM_RulesOpt : public PM_Rules
{
public:

    //Class default constructor.
    //##ModelId=3E6E4CC700FB
    PM_RulesOpt(PM_GenericApplication&  theGenericApplication, 
                uint16                  theIndex);

    //Class default destructor.
    //##ModelId=3E6E4CC70119
    virtual ~PM_RulesOpt();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA1610C017D
    virtual void Init();

    //Updates the accumulation rules for Optical. This 
    //method is called every second to update accumulation 
    //rules. It also updates all accumulation periods 
    //affected by these rules. The behavior of this method is 
    //not affected by the end of any accumulation period. All 
    //accumulation period included in myVectorOfAccPeriod are 
    //responsible to re-run itself when the accumulation 
    //period is finished.
    //##ModelId=3E6E4CC70123
    virtual void UpdateRules(bool* theFilteringStateFirstStage, 
                             bool* theFilteringStageSecondStage);

private:

    //Reference to the collector's Optical status BB object.
    //##ModelId=3E6FC0310360
    PM_BbStatusOpt&  myStatusOpt;

    //First time flag.
	//##ModelId=3FA1610C018E
    bool myFirstTime[PM_TypeOpt::PM_PARAM_NUM];

};

#endif //PM_RULESOPT_H


