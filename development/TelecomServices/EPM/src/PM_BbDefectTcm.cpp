/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     8 Oct 2010   Larry Wolfrum
 DESCRIPTION:   Update and keep the PM defects of TCM layer.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_TcmDefects.h>
#include <EPM/PM_BbDefectTcm.h>


//-----------------------------------------------------------------
PM_BbDefectTcm::PM_BbDefectTcm ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbDefectTcm::~PM_BbDefectTcm ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbDefectTcm::Update(MON_TcmDefects& theTcmMonitor) 
{
    uint32 count = 0;
    bool state = false;

    // Read the defects from the monitor
    theTcmMonitor.GetDefectStatus(CT_TEL_TCM_AIS_DEFECT, &count, &state);
    myAISdefect.Update(state, count);
    theTcmMonitor.GetDefectStatus(CT_TEL_TCM_LCK_DEFECT, &count, &state);
    myLCKdefect.Update(state, count);
    theTcmMonitor.GetDefectStatus(CT_TEL_TCM_OCI_DEFECT, &count, &state);
    myOCIdefect.Update(state, count);
    theTcmMonitor.GetDefectStatus(CT_TEL_TCM_TIM_DEFECT, &count, &state);
    myTIMdefect.Update(state, count);
    theTcmMonitor.GetDefectStatus(CT_TEL_TCM_LTC_DEFECT, &count, &state);
    myLTCdefect.Update(state, count);
    theTcmMonitor.GetDefectStatus(CT_TEL_TCM_IAE_DEFECT, &count, &state);
    myIAEdefect.Update(state, count);
}

//-----------------------------------------------------------------
ostream& PM_BbDefectTcm::WriteObject( ostream& theStream )
{
    return (theStream << myAISdefect
                      << myLCKdefect
                      << myOCIdefect
                      << myTIMdefect
                      << myLTCdefect
                      << myIAEdefect);

}

//-----------------------------------------------------------------
istream& PM_BbDefectTcm::ReadObject( istream& theStream )
{
    return (theStream >> myAISdefect
                      >> myLCKdefect
                      >> myOCIdefect
                      >> myTIMdefect
                      >> myLTCdefect
                      >> myIAEdefect);

}

//-----------------------------------------------------------------
void PM_BbDefectTcm::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
