/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         June 19, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for the Generic TL1 observer factory
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OBSERVERFACTORY_H__
#define __TL1_OBSERVERFACTORY_H__

#ifndef __TL1_OBSERVERFACTORYIF_H__
#include <TL1Core/TL1_ObserverFactoryIf.h>
#endif

template <class TheObserverObj>
class TL1_ObserverFactory : public TL1_ObserverFactoryIf
{
public:
    virtual TL1_AgentRegionObserver* CreateObserver(FC_BbRegion& theObservedRegion);
};

template <class TheObserverObj>
TL1_AgentRegionObserver* TL1_ObserverFactory<TheObserverObj>::CreateObserver( FC_BbRegion& theObservedRegion )
{
    return new TheObserverObj(theObservedRegion);
};

#endif