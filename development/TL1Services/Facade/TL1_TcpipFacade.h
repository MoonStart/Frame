/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         
DESCRIPTION:    Header file for TL1 Tcpip Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_TCPIPFACADE_H__
#define __TL1_TCPIPFACADE_H__

#ifndef __TL1_TCPIPENTITY_H__
#include <TL1Core/TL1_TcpipEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EdTcpipReq( theTcpipAid, theDupAddrDetCnt, theDupAddrDetTmr, theTelnetEnable, theFtpEnable, theHttpEnable, theSshAuthentication, theSshKeyStrength, theCommandMode, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdTcpipReq( theTcpipAid,  theDupAddrDetCnt, theDupAddrDetTmr, theTelnetEnable, theFtpEnable, theHttpEnable, theSshAuthentication, theSshKeyStrength, theCommandMode, theResponse))


#define FACI_RtrvTcpipReq( theTcpipAid, theShowFP, theShowKey, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTcpipReq( theTcpipAid, theShowFP, theShowKey, theResponse))

#endif // __TL1_TCPIPFACADE_H__
