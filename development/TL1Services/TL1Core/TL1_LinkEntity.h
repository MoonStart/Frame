#ifndef __TL1_LINKENTITY_H__
#define __TL1_LINKENTITY_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 15, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Topological and Bundled LINK Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_LINKDOMAIN_H__
#include <TL1Core/TL1_LinkDomain.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif


class TL1_LinkEntity :  public TL1_Entity,          // Base Class
                        public TL1_LinkDomain,      // Protocol Class
                        public TL1_AlarmDomain
{
public:

    TL1_LinkEntity() {};
    virtual ~TL1_LinkEntity() {};

};

class TL1_TnaLinkEntity :  public TL1_Entity,          // Base Class
                           public TL1_TnaLinkDomain    // Protocol Class
{
public:

    TL1_TnaLinkEntity() {};
    virtual ~TL1_TnaLinkEntity() {};

};

class TL1_TrLinkEntity :  public TL1_Entity,          // Base Class
                          public TL1_TrLinkDomain       // Protocol Class
{
public:

    TL1_TrLinkEntity() {};
    virtual ~TL1_TrLinkEntity() {};

};

class TL1_BLinkEntity :  public TL1_Entity,          // Base Class
                          public TL1_BLinkDomain       // Protocol Class
{
public:

    TL1_BLinkEntity() {};
    virtual ~TL1_BLinkEntity() {};
};

#endif
