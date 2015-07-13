/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     RAMM and SMTM.
 AUTHOR   :     9 Feb 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the PM defects of Far-End SONET/SDH MS layer.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_MsDefects.h>
#include <PM_BbDefectMsFarEnd.h>


//-----------------------------------------------------------------
PM_BbDefectMsFarEnd::PM_BbDefectMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbDefectMsFarEnd::~PM_BbDefectMsFarEnd ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbDefectMsFarEnd::Update(MON_MsDefects& theMsMonitor) 
{
    uint32 count = 0;
    bool state = false;

    // Read the RDI defect from the monitor
    theMsMonitor.GetDefectStatus(CT_TEL_MS_RDI_DEFECT, &count, &state);
    myRDIdefect.Update(state, count);

    // Read the AIS defect from the monitor
    theMsMonitor.GetDefectStatus(CT_TEL_MS_AIS_DEFECT, &count, &state);
    myAISdefect.Update(state, count);
}

//-----------------------------------------------------------------
ostream& PM_BbDefectMsFarEnd::WriteObject( ostream& theStream )
{
    return theStream << myRDIdefect << myAISdefect;

}

//-----------------------------------------------------------------
istream& PM_BbDefectMsFarEnd::ReadObject( istream& theStream )
{
    return theStream >> myRDIdefect >> myAISdefect;

}

//-----------------------------------------------------------------
void PM_BbDefectMsFarEnd::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
