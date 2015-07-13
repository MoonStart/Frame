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

#ifndef __TL1_AGENTREGIONOBSERVERIMP_H__
#define __TL1_AGENTREGIONOBSERVERIMP_H__

#ifndef __FC_SINGLETON_H__
#include <Util/FC_Singleton.h>
#endif

#include <ss_gdef.h>
#include <TL1Core/TL1_Entity.h>

class AS_Context;
class FC_BbRegion;

class TL1_AgentRegionObserverImp
{
public: 
    TL1_AgentRegionObserverImp();
    virtual ~TL1_AgentRegionObserverImp() = 0;

    /** This method returns the TL1 Entity corresponding to the region.
      * The TL1 Entity is found from the region context.
      */
    virtual TL1_Entity* GetTL1Entity(FC_BbRegion& theRegion) = 0;
    virtual TL1_Entity* GetTL1Entity(AS_Context& theContext) = 0;

    virtual bool IsProvisionned( AS_Context& theContext, const uint32 channel=0 ) = 0;

    virtual AS_Context& GetIf(FC_BbRegion& theRegion) = 0;
};

#endif
