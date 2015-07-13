#ifndef __TL1_OSPFENTITY_H__
#define __TL1_OSPFENTITY_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Header file for TL1 OSPF Profile Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENTITY_H__
#include "TL1Core/TL1_Entity.h"
#endif

#ifndef __TL1_OSPFDOMAIN_H__
#include "TL1Core/TL1_OspfDomain.h"
#endif


class TL1_OspfEntity : public TL1_Entity,        // Base Class
                       public TL1_OspfDomain     // Protocol Class
{
public:
    
    TL1_OspfEntity() {};

    virtual ~TL1_OspfEntity() {};
};

class TL1_OspfAdjEntity : public TL1_Entity,        // Base Class
                       public TL1_OspfAdjDomain    // Protocol Class
{
public:
    
    TL1_OspfAdjEntity() {};

    virtual ~TL1_OspfAdjEntity() {};
};

class TL1_OspfAreaEntity : public TL1_Entity,        // Base Class
                       public TL1_OspfAreaDomain    // Protocol Class
{
public:
    
    TL1_OspfAreaEntity() {};

    virtual ~TL1_OspfAreaEntity() {};
};

class TL1_OspfrpmapEntity : public TL1_Entity,             // Base Class
                            public TL1_OspfrpmapDomain     // Protocol Class
{
public:
    
    TL1_OspfrpmapEntity() {};

    virtual ~TL1_OspfrpmapEntity() {};
};

class TL1_OspfrpEntity : public TL1_Entity,          // Base Class
                         public TL1_OspfrpDomain    // Protocol Class
{
public:
    
    TL1_OspfrpEntity() {};

    virtual ~TL1_OspfrpEntity() {};
};

#endif
