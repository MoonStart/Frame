/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Signal Alarm  
 TARGET   :     All cards
 AUTHOR   :     Marc Vendette
 DESCRIPTION:   This class set the failure status according to the defect
                condition (status and counter) for a soaking failure.
--------------------------------------------------------------------------*/
#ifndef ALMSOAKINGFAILURE_H
#define ALMSOAKINGFAILURE_H

#include <ExecutionSupport/FC_BaseTimer.h>

#include "src/ALM_NormalFailure.h"

//This offset is used because of the polling process.
const FC_Milliseconds ALM_ADJUSTMENT_FACTOR(400);

// Soaking timer default value
const FC_Milliseconds ALM_DEFAULT_SOAKING_TIME(2500 - ALM_ADJUSTMENT_FACTOR);

// Recovery timer default value
const FC_Milliseconds ALM_DEFAULT_RECOVERY_TIME(10000 - ALM_ADJUSTMENT_FACTOR);

//This class is responsible to manage the failure condition of a soaking failure according to its defect condition and the requirements relate to that failure. This class is essentially a finite state machine. This fsm is used to accomplish the soaking and recovery time of a failure. As information, it uses timer service.
//##ModelId=3C506C320359
class ALM_SoakingFailure:   public ALM_NormalFailure
{
public:

	//Class default constructor.
    //
    //PARAM FC_Milliseconds theSoakingTime = ALM_DEFAULT_SOAKING_TIME: the default soaking time.
    //
    //PARAM FC_Milliseconds theRecoveryTime = ALM_DEFAULT_RECOVERY_TIME: the default recovery time.
	//##ModelId=3C506C3203BE
    ALM_SoakingFailure (FC_Milliseconds theSoakingTime = ALM_DEFAULT_SOAKING_TIME , 
                        FC_Milliseconds theRecoveryTime = ALM_DEFAULT_RECOVERY_TIME);

	//Class destructor.
	//##ModelId=3C506C3203C9
    virtual ~ALM_SoakingFailure();

    //Definition of state for soaking failure.
    enum ALM_StateId
    {
        //There is no anomaly detected. No failure is reported.
        ALM_NORMAL_S,
        
        //There is an anomaly detected, start the soaking timer. No failure is reported.
        ALM_DEFECT_S,

        //The anomaly was detected for the period of soaking time. Failure is reported.
        ALM_FAILURE_S,

        //The anomaly is not detected anymore, start the erocovery timer. Failure is reported.
        ALM_RECOVERY_S
    };

	//Reset the state machine (itsState, itsPreviousTCount and itsFailureStatus).
	//##ModelId=3DBFFAE601AF
    virtual void Reset();

	//External interface to use this fsm. A call to this method runs one iteration of the state machine and returns the failure condition.
    //
    //PARAM bool theStatus: the status of the defect.
    //
    //PARAM ALM_TCount theTCount: the transition counter of the defect.
    //
    //PARAM bool theRecoveryOverride = false: flag to bypass the recovery timer.
    //
    //RETURN bool: the status of the failure.
	//##ModelId=3C506C3203CB
    virtual bool DefectUpdated (bool theStatus, ALM_TCount theTCount,
                                bool theRecoveryOverride = false);

	//Set the soaking and recovery time of a failure.
    //
    //PARAM FC_Milliseconds theSoakingTime: the soaking time.
    //
    //PARAM FC_Milliseconds theRecoveryTime: the recovery time.
	//##ModelId=3C506C3203DC
    inline void SetSoakingRecoveryTime (FC_Milliseconds theSoakingTime, 
                                        FC_Milliseconds theRecoveryTime);

	//Set the recovery time of a failure.
    //
    //PARAM FC_Milliseconds theRecoveryTime: the recovery time.
	//##ModelId=3C506C3203DF
    inline void SetRecoveryTime (FC_Milliseconds theRecoveryTime);

    inline ALM_SoakingFailure::ALM_StateId GetCurrentState() const;

private:

	//Base timer that privide Soaking and Recovery timer.
	//##ModelId=3C515E2B00A0
    FC_BaseTimer itsTimer;

	//Soaking timer value in millisecond.
	//##ModelId=3C63B83000C5
    FC_Milliseconds itsSoakingTime;

	//Recovery timer value in millisecond.
	//##ModelId=3C60A20A0005
    FC_Milliseconds itsRecoveryTime;

	//The transition counter of the previous call to run() method.
	//##ModelId=3C60A20A0109
    ALM_TCount itsPreviousTCount;

	//The failure status to return.
	//##ModelId=3C506C33004E
    bool itsFailureStatus;

	//Current state of the state machine.
	//##ModelId=3C515E2B00FA
    ALM_StateId itsState;
};

//-----------------------------------------------------------------
//##ModelId=3C506C3203DC
inline void ALM_SoakingFailure::SetSoakingRecoveryTime (
    FC_Milliseconds theSoakingTime, FC_Milliseconds theRecoveryTime)
{
    itsSoakingTime = theSoakingTime;
    itsRecoveryTime = theRecoveryTime;
}

//-----------------------------------------------------------------
//##ModelId=3C506C3203DF
inline void ALM_SoakingFailure::SetRecoveryTime (FC_Milliseconds theRecoveryTime)
{
    itsRecoveryTime = theRecoveryTime;
}

//-----------------------------------------------------------------
inline ALM_SoakingFailure::ALM_StateId ALM_SoakingFailure::GetCurrentState() const
{
    return itsState;
}

#endif //ALMSOAKINGFAILURE_H
