/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 25, 2009 --- Maggie Zhang
DESCRIPTION:    Header file for TL1 control frame Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CFPFDOMAIN_H__
#define __TL1_CFPFDOMAIN_H__


#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif


#include <LumosTypes/LT_System.h>

class TL1_Response;

/**
   CLASS TL1_CfpfDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of Control Frame Profile related TL1 commands, that a TL1 Entities
   for a cfpf is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_CfpfDomain
{
public:

    virtual void RtrvCfpf(const uint32& theProfileId,
                         TL1_Response& theResponse) = 0;

   
    virtual void EdCfpf(  const uint32& theProfileId,
                         bool* theLacp,
                         bool* theLinkOAM,
                         bool* theDot1X,
                         bool* theElmi,
                         bool* theLldp,
                         bool* theGarp,
                         TL1_Response& theResponse) = 0;
    
};

#endif
