/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 16, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 NTP Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NTPFACADE_H__
#define __TL1_NTPFACADE_H__

#ifndef __TL1_NTPENTITY_H__
#include <TL1Core/TL1_NTPEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvNtpPeer( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvNtpPeer( theId, theResponse ))

#define FACI_EntNtpPeer( theId, theIpAddress, theName, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntNtpPeer( theId, theIpAddress, theName, thePst, theResponse ))

#define FACI_EdNtpPeer( theId, theName, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdNtpPeer( theId, theName, thePst, theResponse ))

#define FACI_DltNtpPeer( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltNtpPeer( theId, theResponse ))


#endif
