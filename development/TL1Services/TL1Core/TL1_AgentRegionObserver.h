/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 10, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for TL1 Region Observer declaration.
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_AGENTREGIONOBSERVER_H__
#define __TL1_AGENTREGIONOBSERVER_H__

#ifndef __FC_BBREGIONOBSERVER_H__
#include <Blackboard/FC_BbRegionObserver.h>
#endif

#ifndef __FC_ACTION_H__
#include <ExecutionSupport/FC_Action.h>
#endif

#include <TL1Core/TL1_AgentRegionObserverImp.h>

class FC_DbModeRegion;

/** Base class that is used for all agent region observers used to
 *  send notifications.  The interface enable this observer to be
 *  used as an FC_Action or an FC_BbRegionObserver.  There should
 *  be one instance of this observer per observed region.
 */
class TL1_AgentRegionObserver : public FC_Action,
                                public FC_BbRegionObserver
{
public:
    TL1_AgentRegionObserver( FC_BbRegion& theObservedRegion, 
		                     TL1_AgentRegionObserverImp&  theRegionObserverImp);
    virtual ~TL1_AgentRegionObserver();

    virtual void Run( FC_Object* theObject = NULL );

    virtual void RegionModify( FC_BbRegion* theRegion );

    static void SetDbModeRegion(FC_DbModeRegion& theDbModeRegion);

protected:
    /** Template method that does the specific RegionModify work.
     *  It's being called by RegionModify.
     */
    virtual void DoRegionModify( FC_BbRegion& theRegion );

    /** Template method that does the specific Run work.
     *  It's being called by Run() in case the object it receives
     *  is not the observed region.
     */
    virtual void DoRun( FC_Object& theObject );

    /** Template method that will be called right after the database
     *  has been restored. 
     */
    virtual void OnDatabaseRestore();

    FC_BbRegion& GetObservedRegion() { return itsObservedRegion; }

    TL1_AgentRegionObserverImp& GetImp() { return itsAgentRegionObserverImp; }

private:
    FC_DbModeRegion* GetDbModeRegionPtr();

    FC_BbRegion& itsObservedRegion;
    TL1_AgentRegionObserverImp& itsAgentRegionObserverImp;
    static FC_DbModeRegion* theirDbModeRegionPtr;
    bool itsIsDbRestored;
};

#endif