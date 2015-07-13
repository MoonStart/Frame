/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders MRTM and 10G.
 AUTHOR   :     September 16, 2002. Steve Thiffault
 DESCRIPTION:   Update and keep the PM defects of Optical 
                Transport Unit or FEC.
--------------------------------------------------------------------------*/

#include <Monitoring/MON_OtuDefects.h>
#include <Monitoring/MON_OptDefects.h>
#include <PM_BbDefectOtu.h>


//-----------------------------------------------------------------
//##ModelId=3E6E4D200280
PM_BbDefectOtu::PM_BbDefectOtu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D200289
PM_BbDefectOtu::~PM_BbDefectOtu ()
{
    // Nothing to do for now.

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D20032A
void PM_BbDefectOtu::Update(MON_OtuDefects& theOtuMonitor) 
{
    uint32 count = 0;
    bool state = false;

    theOtuMonitor.GetDefectStatus(CT_TEL_OTU_LOF_DEFECT, &count, &state);
    myLOFdefect.Update(state, count);

    theOtuMonitor.GetDefectStatus(CT_TEL_OTU_LOMF_DEFECT, &count, &state);
    myLOMdefect.Update(state, count);

    theOtuMonitor.GetDefectStatus(CT_TEL_OTU_TIM_DEFECT, &count, &state);
    myTIMdefect.Update(state, count);

    theOtuMonitor.GetDefectStatus(CT_TEL_OTU_IAE_DEFECT, &count, &state);
    myIAEdefect.Update(state, count);
}

//-----------------------------------------------------------------
void PM_BbDefectOtu::Update(MON_OptDefects& theOptMonitor) 
{
    uint32 count = 0;
    bool state = false;

    // Read the LOS defect from the monitor
    theOptMonitor.GetDefectStatus(CT_TEL_OPT_LOSS_LIGHT_DEFECT, &count, &state);
    myLOSdefect.Update(state, count);

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D20033D
ostream& PM_BbDefectOtu::WriteObject( ostream& theStream )
{
    return theStream << myLOFdefect
					 << myLOMdefect
					 << myLOSdefect
                     << myTIMdefect
                     << myIAEdefect;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D200351
istream& PM_BbDefectOtu::ReadObject( istream& theStream )
{
    return theStream >> myLOFdefect
					 >> myLOMdefect
					 >> myLOSdefect
                     >> myTIMdefect
                     >> myIAEdefect;

}

//-----------------------------------------------------------------
//##ModelId=3E6E4D200293
void PM_BbDefectOtu::Init(restart_type theRestart)
{
    // Nothing to do for now.

}
