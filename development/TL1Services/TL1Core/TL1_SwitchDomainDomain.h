/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         February 25, 2009 - Ed Bandyk
DESCRIPTION:    Header file for TL1 Switch Domain Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWITCHDOMAINDOMAIN_H__
#define __TL1_SWITCHDOMAINDOMAIN_H__

#ifndef __CT_Equipment_H__
#include <CommonTypes/CT_Equipment.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#include <TL1Core/TL1_SwitchDomainParameters.h>

class TL1_Response;

/**
   CLASS TL1_SwitchDomainDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of Switch Domain related TL1 commands, that a
   TL1 Entities for a Switch Domain t is expected to implement. This class
   contains no data member nor any default implementation.
 */

class TL1_SwitchDomainDomain
{
public:

    virtual void RtrvSwitchDomain( const CT_SwitchDomain& theSwitchDomain,
                                        TL1_Response& theResponse ) const = 0;

    virtual void EdSwitchDomain( const CT_SwitchDomain& theSwitchDomain,
                                 TL1_SwitchDomainParameters& theParameters,
                                 TL1_Response& theResponse ) = 0;
};

#endif

