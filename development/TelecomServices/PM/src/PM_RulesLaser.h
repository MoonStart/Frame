/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring 
 TARGET   :     Transponders.
 AUTHOR   :     Steve Thiffault, February 26, 2003.
 DESCRIPTION:   The class to update Laser parameters.
--------------------------------------------------------------------------*/

#ifndef PM_RULESLASER_H
#define PM_RULESLASER_H

#include <vector>
#include <CommonTypes/CT_Telecom.h>
#include <PM/src/PM_Rules.h>
#include <PM/PM_TypeLaser.h>


// Forward declaration of classes
class PM_BbStatusLaser;

//This class is responsible of the accumulation rules of 
//Laser. These accumulation rules are deduced from the 
//statuses given by the Collector. These rules are used by the 
//Accumulation Period classes that are responsible to update 
//parameters for Laser. 
//##ModelId=3E6E4CD10249
class PM_RulesLaser : public PM_Rules
{
public:

    //Class default constructor.
    //##ModelId=3E6E4CD30012
    PM_RulesLaser(PM_GenericApplication&  theGenericApplication, 
                  uint16                  theIndex);

    //Class default destructor.
    //##ModelId=3E6E4CD30030
    virtual ~PM_RulesLaser();

    //Initializes rules at beginning of execution or after
    //context becomes available.
	//##ModelId=3FA1610D015E
    virtual void Init();

    //Updates the accumulation rules for Laser. This 
    //method is called every second to update accumulation 
    //rules. It also updates all accumulation periods 
    //affected by these rules. The behavior of this method is 
    //not affected by the end of any accumulation period. All 
    //accumulation period included in myVectorOfAccPeriod are 
    //responsible to re-run itself when the accumulation 
    //period is finished.
    //##ModelId=3E6E4CD3003A
    virtual void UpdateRules(bool* theFilteringStateFirstStage,
                             bool* theFilteringStateSecondStage);

private:

    //Reference to the collector's Laser status BB object.
    //##ModelId=3E6FC036035D
    PM_BbStatusLaser&  myStatusLaser;

    //First time flag.
	//##ModelId=3FA1610D016E
    bool myFirstTime[PM_TypeLaser::PM_PARAM_NUM];

};

#endif //PM_RULESLASER_H


