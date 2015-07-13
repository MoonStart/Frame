/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 15, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 cross-connection Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_BWPFDOMAIN_H__
#define __TL1_BWPFDOMAIN_H__


#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif


#include <LumosTypes/LT_System.h>

class TL1_Response;

/**
   CLASS TL1_BwpfDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of Bandwidth Profile related TL1 commands, that a TL1 Entities
   for a bwpf is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_BwpfDomain
{
public:

    virtual void RtrvBwpf(const uint32& theProfileId,
                         TL1_Response& theResponse) = 0;

    virtual void EntBwpf( const uint32& theProfileId,
                         int* theCir,
                         int* theCbs,
                         TL1_Response& theResponse) = 0;
    
    virtual void EdBwpf(  const uint32& theProfileId,
                         int* theCir,
                         int* theCbs,
                         TL1_Response& theResponse) = 0;
    
    virtual void DltBwpf( const uint32& theProfileId,
                         TL1_Response& theResponse) = 0;

};

#endif
