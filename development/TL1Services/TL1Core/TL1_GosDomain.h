/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 27, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Grade Of Service Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_GOSDOMAIN_H__
#define __TL1_GOSDOMAIN_H__

//#ifndef __CT_TL1_GOS_H__
//#include <CommonTypes/CT_TL1_GOS.h>
//#endif

/**
   CLASS TL1_GosDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of GOS related TL1 commands, that a TL1 Entities
   for a GOS is expected to implement. This class contains no
   data member nor any default implementation.
 */


// Not completetely defined for AP100, to be updated later.

class TL1_GosDomain
{
public:

    virtual void DltGos(  ) = 0;      //AP200

    virtual void EdGos(   ) = 0;      //AP200

    virtual void EntGos(  ) = 0;      //AP200

    virtual void RtrvGos( )const = 0; //AP200
};

#endif
