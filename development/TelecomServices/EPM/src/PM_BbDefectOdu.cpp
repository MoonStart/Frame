/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     OSM40 and SSM40.
 AUTHOR   :     22 Oct 2009   Larry Wolfrum
 DESCRIPTION:   Update and keep the PM defects of ODU layer.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OduDefects.h>
#include <EPM/PM_BbDefectOdu.h>


//-----------------------------------------------------------------
PM_BbDefectOdu::PM_BbDefectOdu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbDefectOdu::~PM_BbDefectOdu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbDefectOdu::Update(MON_OduDefects& theOduMonitor) 
{
    uint32 count = 0;
    bool state = false;

    // Read the defects from the monitor
    theOduMonitor.GetDefectStatus(CT_TEL_ODU_AIS_DEFECT, &count, &state);
    myAISdefect.Update(state, count);
    theOduMonitor.GetDefectStatus(CT_TEL_ODU_LCK_DEFECT, &count, &state);
    myLCKdefect.Update(state, count);
    theOduMonitor.GetDefectStatus(CT_TEL_ODU_OCI_DEFECT, &count, &state);
    myOCIdefect.Update(state, count);
    theOduMonitor.GetDefectStatus(CT_TEL_ODU_TIM_DEFECT, &count, &state);
    myTIMdefect.Update(state, count);
}

//-----------------------------------------------------------------
ostream& PM_BbDefectOdu::WriteObject( ostream& theStream )
{
    return (theStream << myAISdefect
                      << myLCKdefect
                      << myOCIdefect
                      << myTIMdefect
);

}

//-----------------------------------------------------------------
istream& PM_BbDefectOdu::ReadObject( istream& theStream )
{
    return (theStream >> myAISdefect
                      >> myLCKdefect
                      >> myOCIdefect
                      >> myTIMdefect);

}

//-----------------------------------------------------------------
void PM_BbDefectOdu::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
