/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         April 10, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for the Generic TL1 Deferred observer factory
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DEFERREDOBSERVERFACTORYIF_H__
#define __TL1_DEFERREDOBSERVERFACTORYIF_H__

class TL1_WakeUpAction;
class FC_BbRegion;
class FC_BbRegionObserver;
class TL1_AgentRegionObserver;

/** This factory will create TL1_WakeUpActions that defer the execution of 
  * TL1 Region observers.  It shall be used in conjunction with the 
  * TL1_DeferredObserverBuilder that automates the process of creating the
  * one shot process and the WakeUpAction.
  */

class TL1_DeferredObserverFactoryIf
{
public:
    virtual TL1_WakeUpAction* CreateObserver(FC_BbRegion& theObservedRegion) = 0;
};

#endif // __TL1_NOTIFOBSERVERFACTORY_H__