/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Implementation file for new PM_BbStatusOduGauge class.
--------------------------------------------------------------------------*/

#include <EPM/PM_BbStatusOduGauge.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Float32.h>
#include <EPM/PM_TypeOdu.h>

//-----------------------------------------------------------------
PM_BbStatusOduGauge::PM_BbStatusOduGauge():PM_BbStatus(PM_TypeOduGauge::PM_PARAM_NUM)
{
    myDelay = 0;
}

//-----------------------------------------------------------------
PM_BbStatusOduGauge::~PM_BbStatusOduGauge ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbStatusOduGauge::Update(MON_OduStatus& theStatusMonitor) 
{
    myDelay = theStatusMonitor.GetPathDelay();
}

//-----------------------------------------------------------------
ostream& PM_BbStatusOduGauge::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myDelay);
}

//-----------------------------------------------------------------
istream& PM_BbStatusOduGauge::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myDelay);
}

//-----------------------------------------------------------------
void PM_BbStatusOduGauge::Init(restart_type theRestart)
{
    // Nothing to do for now.
}

