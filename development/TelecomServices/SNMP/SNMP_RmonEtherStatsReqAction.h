/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_RMONETHERSTATSREQACTION_H
#define SNMP_RMONETHERSTATSREQACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ExecutionSupport/FC_Action.h>
#include <SNMP/SNMP_RmonRegion.h>


typedef struct PMD_SnmpEtherStats
{
    int index;
    int dropEvents;
    int octets;
    int pkts;
    int broadcastPkts;
    int multicastPkts;
    int CRCalignErrors;
    int undersizePkts;
    int oversizePkts;
    int fragments;
    int jabbers;
    int collisions;
    int pkts64;
    int pkts65to127;
    int pkts128to255;
    int pkts256to511;
    int pkts512to1023;
    int pkts1024to1518;
    int droppedFrames;
    int createTime;
}
PMD_SnmpEtherStatsBuffer;


// Forward class declaration.
class SNMP_ScRmonSubApplication;

class SNMP_ScRmonEtherStatsReqAction : public FC_Action
{
public:
//    SNMP_ScRmonEtherStatsReqAction (SNMP_ScRmonSubApplication* theScSubApp);
    SNMP_ScRmonEtherStatsReqAction (SNMP_RmonEtherStatsDataRegion*  theDataRegion,
                                    SNMP_RmonEtherStatsReqRegion*  theReqRegion,
                                    SNMP_ScRmonSubApplication* theScSubApp);
    virtual ~SNMP_ScRmonEtherStatsReqAction();
    virtual void Run(FC_Object* theObject = NULL);

private:
    SNMP_RmonEtherStatsDataRegion*     myDataRegion;
    SNMP_RmonEtherStatsReqRegion*      myReqRegion;
    SNMP_ScRmonSubApplication*         myScSubApp;
};

#endif //SNMP_RMONETHERSTATSREQUESTACTION_H
 
