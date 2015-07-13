/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:     SNMP/RMON
 TARGET   :     All.
 AUTHOR   :     Hemant Thakkar   November 7, 2005
 DESCRIPTION:   
--------------------------------------------------------------------------*/

#ifndef SNMP_RMONETHERHISTREQACTION_H
#define SNMP_RMONETHERHISTREQACTION_H

#include <ExecutionSupport/FC_Action.h>
#include <CommonTypes/CT_SNMP_Definition.h>
#include <ExecutionSupport/FC_Action.h>
#include <SNMP/SNMP_RmonRegion.h>

// Forward class declaration.
typedef struct PMD_SnmpEtherHist 
{
    int Index;
    int SampleIndex;
    int IntervalStart;
    int DropEvents;
    int Octets;
    int Pkts;
    int BroadcastPkts;
    int MulticastPkts;
    int CRCAlignErrors;
    int UndersizePkts;
    int OversizePkts;
    int Fragments;
    int Jabbers;
    int Collisions;
    int Utilization;
}PMD_SnmpEtherHistBuffer;


class SNMP_ScRmonSubApplication;
class SNMP_ScRmonEtherHistReqAction : public FC_Action
{

public:

//    SNMP_ScRmonEtherHistReqAction (SNMP_RmonEtherHistStorageRegion* theStorageRegion,
//                                 SNMP_ScRmonSubApplication * theScSubApp);
    SNMP_ScRmonEtherHistReqAction (SNMP_RmonEtherHistDataRegion*  theDataRegion,
                                 SNMP_RmonEtherHistStorageRegion* theStorageRegion,
                                 SNMP_RmonEtherHistReqRegion*  theReqRegion,
                                 SNMP_ScRmonSubApplication * theScSubApp);
    virtual ~SNMP_ScRmonEtherHistReqAction();
    virtual void Run(FC_Object* theObject = NULL);

private:
    SNMP_RmonEtherHistStorageRegion*  myStorageRegion;
    SNMP_RmonEtherHistDataRegion*     myDataRegion;
    SNMP_RmonEtherHistReqRegion*      myReqRegion;
    SNMP_ScRmonSubApplication*        myScSubApp;
};

#endif //SNMP_RMONETHERHISTREQUESTACTION_H
 
