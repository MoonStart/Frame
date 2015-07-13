#ifndef __TL1_IPSECENTITY_H__
#define __TL1_IPSECENTITY_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         October 19, 2005 - Mike Rodgers
DESCRIPTION:    Header file for TL1 IPSEC Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_IPSECDOMAIN_H__
#include <TL1Core/TL1_IpSecDomain.h>
#endif


class TL1_IpSecEntity :	public TL1_Entity,			// Base Class
                      	public TL1_IpSecDomain		// Protocol Class
{
public:

    TL1_IpSecEntity() {};
    virtual ~TL1_IpSecEntity() {};

};

#endif
