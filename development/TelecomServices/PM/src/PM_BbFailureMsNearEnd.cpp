/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the PM failures of Near-End SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#include <Alarm/ALM_MsFailureBase.h>
#include <PM_BbFailureMsNearEnd.h>


//-----------------------------------------------------------------
PM_BbFailureMsNearEnd::PM_BbFailureMsNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbFailureMsNearEnd::~PM_BbFailureMsNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbFailureMsNearEnd::Update(ALM_FailureBase& theMsAlm) 
{
    bool state = false;

    // Read the AIS failure from the monitor
    state = theMsAlm.GetStatus(CT_TelAlarmCondition::ALM_AIS_MS);
    myAISfailure.Update(state);
    
	state = theMsAlm.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_MS);
    myUpperSAfailure.Update(state);
}

//-----------------------------------------------------------------
ostream& PM_BbFailureMsNearEnd::WriteObject( ostream& theStream )
{
    return (theStream << myAISfailure 
					  << myUpperSAfailure);
}

//-----------------------------------------------------------------
istream& PM_BbFailureMsNearEnd::ReadObject( istream& theStream )
{
    return (theStream >> myAISfailure 
			          >> myUpperSAfailure);
}

//-----------------------------------------------------------------
void PM_BbFailureMsNearEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
