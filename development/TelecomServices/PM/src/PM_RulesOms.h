/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Olim, Amplifiers.
 AUTHOR   :     Steve Thiffault, March 4, 2003.
 DESCRIPTION:   The class to update Oms parameters.
--------------------------------------------------------------------------*/

#ifndef PM_RULESOMS_H
#define PM_RULESOMS_H

#include <vector>
#include <CommonTypes/CT_Telecom.h>
#include <PM/src/PM_Rules.h>
#include <PM/PM_TypeOms.h>


// Forward declaration of classes
class PM_BbStatusOms;

//This class is responsible of the accumulation rules of 
//Laser. These accumulation rules are deduced from the 
//statuses given by the Collector. These rules are used by the 
//Accumulation Period classes that are responsible to update 
//parameters for Oms. 
//##ModelId=3E6E4C940167
class PM_RulesOms : public PM_Rules
{
public:

    //Class default constructor.
    //##ModelId=3E6E4C9600A0
    PM_RulesOms(PM_GenericApplication&  theGenericApplication, 
                uint16                  theIndex);

    //Class default destructor.
    //##ModelId=3E6E4C9600B5
    virtual ~PM_RulesOms();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA1610B02C6
    virtual void Init();

    //Updates the accumulation rules for Oms. This 
    //method is called every second to update accumulation 
    //rules. It also updates all accumulation periods 
    //affected by these rules. The behavior of this method is 
    //not affected by the end of any accumulation period. All 
    //accumulation period included in myVectorOfAccPeriod are 
    //responsible to re-run itself when the accumulation 
    //period is finished.
    //##ModelId=3E6E4C9600DC
    virtual void UpdateRules(bool* theFilteringStateFirstStage,
                             bool* theFilteringStateSecondStage);

private:

    //Reference to the collector's Oms status BB object.
    //##ModelId=3E6FC01C0083
    PM_BbStatusOms&  myStatusOms;

    //First time flag.
	//##ModelId=3FA1610B02D6
    bool myFirstTime[PM_TypeOms::PM_PARAM_NUM];

};

#endif //PM_RULESOMS_H


