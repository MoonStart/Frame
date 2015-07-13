/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the PM failures of Far-End SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#include <Alarm/ALM_MsFailureBase.h>
#include <PM_BbFailureMsFarEnd.h>


//-----------------------------------------------------------------
PM_BbFailureMsFarEnd::PM_BbFailureMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbFailureMsFarEnd::~PM_BbFailureMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbFailureMsFarEnd::Update(ALM_FailureBase& theMsMonitor)
{
    bool state = false;


    // Read the RDI failure from the monitor
    state = theMsMonitor.GetStatus(CT_TelAlarmCondition::ALM_RDI_MS);
    myRDIfailure.Update(state);

}

//-----------------------------------------------------------------
ostream& PM_BbFailureMsFarEnd::WriteObject( ostream& theStream )
{
    return theStream << myRDIfailure;

}

//-----------------------------------------------------------------
istream& PM_BbFailureMsFarEnd::ReadObject( istream& theStream )
{
    return theStream >> myRDIfailure;

}

//-----------------------------------------------------------------
void PM_BbFailureMsFarEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
