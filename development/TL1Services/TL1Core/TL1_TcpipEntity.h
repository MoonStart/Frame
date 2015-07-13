#ifndef __TL1_TCPIPENTITY_H__
#define __TL1_TCPIPENTITY_H__

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
DESCRIPTION:    Header file for TL1 TCPIP Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif


#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_TCPIPDOMAIN_H__
#include <TL1Core/TL1_TcpipDomain.h>
#endif


class TL1_TcpipEntity :	public TL1_Entity,			// Base Class
                      	public TL1_TcpipDomain		// Protocol Class
{
public:

    TL1_TcpipEntity() {};
    virtual ~TL1_TcpipEntity() {};

};

#endif
