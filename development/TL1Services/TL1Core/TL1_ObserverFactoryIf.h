/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 14, 2003- Jean-Francois Emond
DESCRIPTION:    Header file for the Generic TL1 observer factory
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OBSERVERFACTORYIF_H__
#define __TL1_OBSERVERFACTORYIF_H__

class TL1_AgentRegionObserver;

/** This factory will simply create an instance of an observer
  */
class TL1_ObserverFactoryIf
{
public:
    virtual TL1_AgentRegionObserver* CreateObserver(FC_BbRegion& theObservedRegion) = 0;
};

#endif // __TL1_OBSERVERFACTORY_H__