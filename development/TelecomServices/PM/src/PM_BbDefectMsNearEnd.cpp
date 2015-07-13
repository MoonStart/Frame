/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the PM defects of Near-End SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_MsDefects.h>
#include <PM_BbDefectMsNearEnd.h>


//-----------------------------------------------------------------
PM_BbDefectMsNearEnd::PM_BbDefectMsNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbDefectMsNearEnd::~PM_BbDefectMsNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbDefectMsNearEnd::Update(MON_MsDefects& theMsMonitor) 
{
    uint32 count = 0;
    bool state = false;


    // Read the AIS defect from the monitor
    theMsMonitor.GetDefectStatus(CT_TEL_MS_AIS_DEFECT, &count, &state);
    myAISdefect.Update(state, count);

}

//-----------------------------------------------------------------
ostream& PM_BbDefectMsNearEnd::WriteObject( ostream& theStream )
{
    return theStream << myAISdefect;

}

//-----------------------------------------------------------------
istream& PM_BbDefectMsNearEnd::ReadObject( istream& theStream )
{
    return theStream >> myAISdefect;

}

//-----------------------------------------------------------------
void PM_BbDefectMsNearEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
