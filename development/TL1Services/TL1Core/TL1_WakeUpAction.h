/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 1st, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for 7100 Specific TL1 Db Change Wake up
                action declaration.
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_WAKEUPACTION_H__
#define __TL1_WAKEUPACTION_H__

#ifndef __TL1_AGENTREGIONOBSERVER_H__
#include <TL1Core/TL1_AgentRegionObserver.h>
#endif

#ifndef FC_WAKEUPPROCESSACTION_H
#include <ExecutionSupport/FC_WakeUpProcessAction.h>
#endif

/** A wake up action used here to defer the execution of an observer.
  * In the framework, no assumption can be made on the order of the
  * changes.  So the purpose of this wake up action is to delay the
  * execution of the observer util the system stabilize so all immediate
  * action have runned and then run the notification observer.  Then,
  * we can assume that the region contains valid information to build
  * the TL1 notification.
  */
class TL1_WakeUpAction : public FC_BbRegionObserver,
                         public FC_WakeUpProcessAction
{
public:
    /** Constructor.
     * @param FC_OneShotProcess& theProcess: The process that will run the 
     *        observer.
     * @param FC_BbRegionObserver& theImmediateRegionObserver: An instance of the 
     *        region observer that will be deffered until all immediate actions
     *        are completed.
     */
    TL1_WakeUpAction( FC_OneShotProcess& theProcess, 
		              TL1_AgentRegionObserver& theImmediateObserver );

    virtual ~TL1_WakeUpAction();

    TL1_AgentRegionObserver& GetImmediateObserver() { return itsImmediateObserver; }

    FC_OneShotProcess& GetOneShotProcess() { return itsProcess; }

    virtual void RegionModify( FC_BbRegion* theRegion );

    virtual void Run( FC_Object* theObject );

private:
    FC_OneShotProcess& itsProcess;
    TL1_AgentRegionObserver& itsImmediateObserver;
};

#endif