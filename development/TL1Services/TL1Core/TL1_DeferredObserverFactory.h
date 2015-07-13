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

#ifndef __TL1_DEFERREDOBSERVERFACTORY_H__
#define __TL1_DEFERREDOBSERVERFACTORY_H__

#ifndef __TL1_DEFERREDOBSERVERFACTORYIF_H__
#include <TL1Core/TL1_DeferredObserverFactoryIf.h>
#endif

class TL1_DeferredObserverBuilderHelper;

template <class TheObserverObj>
class TL1_DeferredObserverFactory : public TL1_DeferredObserverFactoryIf
{
    virtual TL1_WakeUpAction* CreateObserver( FC_BbRegion& theObservedRegion );
};

template <class TheObserverObj>
TL1_WakeUpAction* TL1_DeferredObserverFactory<TheObserverObj>::CreateObserver( FC_BbRegion& theObservedRegion )
{
    return TL1_DeferredObserverBuilderHelper()( new TheObserverObj(theObservedRegion) );
}

/** A deferred observer builder.
  * @param TL1_RegionObserver* theImmediateObserver:  The observer to be
  * deferred until all immediate actions are performed.
  */
class TL1_DeferredObserverBuilderHelper
{
public:
    TL1_WakeUpAction* operator()( TL1_AgentRegionObserver* theImmediateObserver );
};

#endif // __TL1_DEFERREDOBSERVERFACTORY_H__
