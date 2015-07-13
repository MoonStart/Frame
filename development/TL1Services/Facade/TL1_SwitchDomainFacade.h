/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         February 25, 2009 - Ed Bandyk
DESCRIPTION:    Header file for TL1 Switch Domain facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWITCHDOMAINFACADE_H__
#define __TL1_SWITCHDOMAINFACADE_H__

#ifndef __TL1_SWITCHDOMAINENTITY_H__
#include <TL1Core/TL1_SwitchDomainEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvSwitchDomain( theSwitchDomain, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSwitchDomain( theSwitchDomain, theResponse ))

#define FACI_EdSwitchDomain( theSwitchDomain, theParameters, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSwitchDomain( theSwitchDomain, theParameters, theResponse ))

#endif //__TL1_SWITCHDOMAINFACADE_H__
