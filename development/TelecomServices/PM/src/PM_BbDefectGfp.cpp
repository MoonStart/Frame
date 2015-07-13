/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     SMTM.
 AUTHOR   :     22 April 2004 Hemant Thakkar
 DESCRIPTION:   Update and keep the PM defects of GFP layer.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_GfpDefects.h>
#include <PM_BbDefectGfp.h>


//-----------------------------------------------------------------
PM_BbDefectGfp::PM_BbDefectGfp ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
PM_BbDefectGfp::~PM_BbDefectGfp ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
void PM_BbDefectGfp::Update(MON_GfpDefects& theGfpMonitor) 
{
    uint32 count = 0;
    bool state = false;


    // Read the LOFD defect from the monitor
    theGfpMonitor.GetDefectStatus(CT_TEL_GFP_LOFD_DEFECT, &count, &state);
    myLOFDdefect.Update(state, count);

}

//-----------------------------------------------------------------
ostream& PM_BbDefectGfp::WriteObject( ostream& theStream )
{
    return theStream << myLOFDdefect;

}

//-----------------------------------------------------------------
istream& PM_BbDefectGfp::ReadObject( istream& theStream )
{
    return theStream >> myLOFDdefect;

}

//-----------------------------------------------------------------
void PM_BbDefectGfp::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
