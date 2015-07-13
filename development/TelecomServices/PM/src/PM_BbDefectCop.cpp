/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Olim, Amplifiers, Multiplexers.
 AUTHOR   :     Steve Thiffault, March 3, 2003.
 DESCRIPTION:   Update and keep the PM defects of Channel Optical Power.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OchDefects.h>
#include <Monitoring/MON_OptDefects.h>
#include <PM_BbDefectCop.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4D01031C
PM_BbDefectCop::PM_BbDefectCop ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D010325
PM_BbDefectCop::~PM_BbDefectCop ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D0103A7
void PM_BbDefectCop::Update(MON_OchDefects& theCopMonitor) 
{
    uint32 count = 0;
    bool state = false;


    // Read the LOP defect from the monitor
    theCopMonitor.GetDefectStatus(CT_TEL_OCH_LOSS_PTONE_DEFECT, &count, &state);
    myLOPdefect.Update(state, count);

}

//-----------------------------------------------------------------
void PM_BbDefectCop::Update(MON_OptDefects& theCopMonitor) 
{
    uint32 count = 0;
    bool state = false;

    // Read the LOS defect from the monitor.
    // Some modulues use the OPT layer to track OCH_LOS, so here
    // the OPT LOS is translated into OCH_LOS using the LOP.
    theCopMonitor.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &count, &state);
    myLOPdefect.Update(state, count);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D0103B2
ostream& PM_BbDefectCop::WriteObject( ostream& theStream )
{
    return theStream << myLOPdefect;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D0103C6
istream& PM_BbDefectCop::ReadObject( istream& theStream )
{
    return theStream >> myLOPdefect;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D01032F
void PM_BbDefectCop::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
