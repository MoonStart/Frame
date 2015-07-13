/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_INTFSTATSREQACTION_H
#define SNMP_INTFSTATSREQACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ExecutionSupport/FC_Action.h>
#include <SNMP/SNMP_IntfRegion.h>

// Forward class declaration.

class SNMP_ScIntfStatsReqAction : public FC_Action
{
public:
    SNMP_ScIntfStatsReqAction (SNMP_IntfStatsDataRegion* theDataRegion,
                               SNMP_IntfStatsReqRegion*  theReqRegion);
    virtual ~SNMP_ScIntfStatsReqAction();
    virtual void Run(FC_Object* theObject = NULL);

private:
    SNMP_IntfStatsDataRegion*     myDataRegion;
    SNMP_IntfStatsReqRegion*      myReqRegion;
};

#endif //SNMP_INTFSTATSREQUESTACTION_H
 
