/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     Performance Monitoring.
 TARGET   :     Transponders FGTMM and FGTM.
 AUTHOR   :     June, 2009 Larry Wolfrum.
 DESCRIPTION:   Implementation file for new PM_BbStatusOtuGauge class.
--------------------------------------------------------------------------*/

#include <EPM/PM_BbStatusOtuGauge.h>
#include <BaseClass/FC_TextStream.h>
#include <CommonTypes/CT_Float32.h>
#include <PM/PM_TypeOtu.h>
//-----------------------------------------------------------------
PM_BbStatusOtuGauge::PM_BbStatusOtuGauge ()
    :PM_BbStatus(PM_TypeOtuGauge::PM_PARAM_NUM)
{
    CT_Float32 aBer(0.0);
    myBer = aBer.GetValue();
}

//-----------------------------------------------------------------
PM_BbStatusOtuGauge::~PM_BbStatusOtuGauge ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void PM_BbStatusOtuGauge::Update(MON_OtuStatus& theStatusMonitor) 
{
    if(theStatusMonitor.GetBER().IsValid())
    {
    myBer = theStatusMonitor.GetBER().GetValue();
    }
    else
    {
        CT_Float32 aMonBer(1.9E-2);
        myBer = aMonBer.GetValue();
    }
}

//-----------------------------------------------------------------
ostream& PM_BbStatusOtuGauge::WriteObject( ostream& theStream )
{
    return theStream << FC_InsertVar(myBer);
}

//-----------------------------------------------------------------
istream& PM_BbStatusOtuGauge::ReadObject( istream& theStream )
{
    return theStream >> FC_ExtractVar(myBer);
}

//-----------------------------------------------------------------
void PM_BbStatusOtuGauge::Init(restart_type theRestart)
{
    // Nothing to do for now.
}


