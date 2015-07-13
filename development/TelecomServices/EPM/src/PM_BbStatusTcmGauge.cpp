/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     HGTM
 DESCRIPTION:   Implementation file for new PM_BbStatusTcmGauge class.
--------------------------------------------------------------------------*/

#include <EPM/PM_BbStatusTcmGauge.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Float32.h>
#include <EPM/PM_TypeTcm.h>

//-----------------------------------------------------------------
PM_BbStatusTcmGauge::PM_BbStatusTcmGauge():PM_BbStatus(PM_TypeTcmGauge::PM_PARAM_NUM)
{
    myDelay = 0;
}

//-----------------------------------------------------------------
PM_BbStatusTcmGauge::~PM_BbStatusTcmGauge ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbStatusTcmGauge::Update(MON_TcmStatus& theStatusMonitor) 
{
    myDelay = theStatusMonitor.GetTcmDelay();
}

//-----------------------------------------------------------------
ostream& PM_BbStatusTcmGauge::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myDelay);
}

//-----------------------------------------------------------------
istream& PM_BbStatusTcmGauge::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myDelay);
}

//-----------------------------------------------------------------
void PM_BbStatusTcmGauge::Init(restart_type theRestart)
{
    // Nothing to do for now.
}

