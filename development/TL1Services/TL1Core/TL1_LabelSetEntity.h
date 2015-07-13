/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for TL1 Control Plane Label Set Entity Base class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LABELSETENTITY_H__
#define __TL1_LABELSETENTITY_H__

#include "TL1Core/TL1_Entity.h"
#include "TL1Core/TL1_LabelSetDomain.h"

class TL1_LabelSetEntity : public TL1_Entity,        // Base Class
                           public TL1_LabelSetDomain  // Protocol Class
{
public:
    
    TL1_LabelSetEntity( );

    virtual ~TL1_LabelSetEntity( );
};

#endif
