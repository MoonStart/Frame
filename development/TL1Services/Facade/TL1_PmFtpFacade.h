/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         May 18, 2006 - Praveen S.Bharathi
DESCRIPTION:    Header file for TL1 Pm Ftp Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PM_FTP_FACADE_H__
#define __TL1_PM_FTP_FACADE_H__

#ifndef __TL1_PMFTPDOMAIN_H__
#include <TL1Core/TL1_PmFtpDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EntFtpServer( theArg, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntFtpServer( theArg, theResponse ))

#define FACI_EdFtpServer( theArg, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdFtpServer( theArg, theResponse ))

#define FACI_RtrvFtpServer( theArg, theResponse, theDltFlag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFtpServer( theArg, theResponse, theDltFlag ))

#define FACI_DltFtpServer( theArg, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltFtpServer( theArg, theResponse ))

#endif //__TL1_PM_FTP_FACADE_H__
