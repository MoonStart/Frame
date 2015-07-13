/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the PM failures of Near-End SONET/SDH HOP layer.
--------------------------------------------------------------------------*/

#include <Alarm/ALM_HopFailureBase.h>
#include <PM_BbFailureHopNearEnd.h>


//-----------------------------------------------------------------
PM_BbFailureHopNearEnd::PM_BbFailureHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbFailureHopNearEnd::~PM_BbFailureHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbFailureHopNearEnd::Update(ALM_FailureBase& theHopAlm)
{
    bool state = false;

    // Update failure status from the monitors
    state = theHopAlm.GetStatus(CT_TelAlarmCondition::ALM_AIS_HOP);
    myAISfailure.Update(state);

    state = theHopAlm.GetStatus(CT_TelAlarmCondition::ALM_LOP_HOP);
    myLOPfailure.Update(state);

    state = theHopAlm.GetStatus(CT_TelAlarmCondition::ALM_UNEQ_HOP);
    myUNEQfailure.Update(state);

    state = theHopAlm.GetStatus(CT_TelAlarmCondition::ALM_PLM_HOP);
    myPLMfailure.Update(state);

    state = theHopAlm.GetStatus(CT_TelAlarmCondition::ALM_UPPER_SA_HOP);
    myUpperSAfailure.Update(state);

}

//-----------------------------------------------------------------
ostream& PM_BbFailureHopNearEnd::WriteObject( ostream& theStream )
{
    return (theStream << myAISfailure
                      << myLOPfailure
                      << myUNEQfailure
                      << myPLMfailure
                      << myUpperSAfailure);

}

//-----------------------------------------------------------------
istream& PM_BbFailureHopNearEnd::ReadObject( istream& theStream )
{
    return (theStream >> myAISfailure
                      >> myLOPfailure
                      >> myUNEQfailure
                      >> myPLMfailure
                      >> myUpperSAfailure);

}

//-----------------------------------------------------------------
void PM_BbFailureHopNearEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
