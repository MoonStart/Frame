/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     
 TARGET   :     
 AUTHOR   :     
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#include <PII_TickTimer.h>
#include <SNMP/SNMP_IntfStatsRequestAction.h>
#include <SNMP/SNMP_IntfStatsData.h>
#include <SNMP/SNMP_IntfStatsRequest.h>

//-----------------------------------------------------------------
// Class constructor.
SNMP_ScIntfStatsReqAction::SNMP_ScIntfStatsReqAction (SNMP_IntfStatsDataRegion*  theDataRegion,
                                 SNMP_IntfStatsReqRegion*  theReqRegion) :
myReqRegion(theReqRegion),
myDataRegion(theDataRegion)
{
}

//-----------------------------------------------------------------
SNMP_ScIntfStatsReqAction::~SNMP_ScIntfStatsReqAction ()
{
    // Nothing to do for now.
}

//-----------------------------------------------------------------
void SNMP_ScIntfStatsReqAction::Run (FC_Object* theObject) 
{
    SNMP_BbIntfStatsRequest& intfReq = (*myReqRegion)[0];
    SNMP_BbIntfStatsData& intfData = (*myDataRegion)[0];
    intfData.SetRequestId(intfReq.GetRequestId());
    myDataRegion->IncModificationCounter();
    myDataRegion->UpdateNotify();
}
