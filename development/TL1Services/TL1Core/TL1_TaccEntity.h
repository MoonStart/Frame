/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 22, 2006, Michael Rodgers
DESCRIPTION:    Header file for TL1 TACC Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TACCENTITY_H__
#define __TL1_TACCENTITY_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_TACCDOMAIN_H__
#include <TL1Core/TL1_TaccDomain.h>
#endif


class TL1_TaccEntity :	public TL1_Entity,			// Base Class
                      	public TL1_TaccDomain		// Protocol Class
{
public:

    TL1_TaccEntity() {};
    virtual ~TL1_TaccEntity() {};

};

#endif
