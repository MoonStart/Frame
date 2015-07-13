#ifndef __TL1_NODEENTITY_H__
#define __TL1_NODEENTITY_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 15, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 NODE Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_NODEDOMAIN_H__
#include <TL1Core/TL1_NodeDomain.h>
#endif


class TL1_NodeEntity :  public TL1_Entity,          // Base Class
                        public TL1_NodeDomain       // Protocol Class
{
public:

    TL1_NodeEntity() {};
    virtual ~TL1_NodeEntity() {};

};

#endif
