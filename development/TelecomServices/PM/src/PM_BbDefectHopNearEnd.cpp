/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the PM defects of Near-End SONET/SDH HOP layer.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_HopDefects.h>
#include <PM_BbDefectHopNearEnd.h>


//-----------------------------------------------------------------
PM_BbDefectHopNearEnd::PM_BbDefectHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbDefectHopNearEnd::~PM_BbDefectHopNearEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbDefectHopNearEnd::Update(MON_HopDefects& theHopMonitor) 
{
    uint32 count = 0;
    bool state = false;

    // Read the defects from the monitor
    theHopMonitor.GetDefectStatus(CT_TEL_HOP_AIS_DEFECT, &count, &state);
    myAISdefect.Update(state, count);
    theHopMonitor.GetDefectStatus(CT_TEL_HOP_LOP_DEFECT, &count, &state);
    myLOPdefect.Update(state, count);
    theHopMonitor.GetDefectStatus(CT_TEL_HOP_UNEQ_DEFECT, &count, &state);
    myUNEQdefect.Update(state, count);
    theHopMonitor.GetDefectStatus(CT_TEL_HOP_PLM_DEFECT, &count, &state);
    myPLMdefect.Update(state, count);

}

//-----------------------------------------------------------------
ostream& PM_BbDefectHopNearEnd::WriteObject( ostream& theStream )
{
    return (theStream << myAISdefect
                      << myLOPdefect
                      << myUNEQdefect
                      << myPLMdefect);

}

//-----------------------------------------------------------------
istream& PM_BbDefectHopNearEnd::ReadObject( istream& theStream )
{
    return (theStream >> myAISdefect
                      >> myLOPdefect
                      >> myUNEQdefect
                      >> myPLMdefect);

}

//-----------------------------------------------------------------
void PM_BbDefectHopNearEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
