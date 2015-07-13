/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         June , 2003- Mathieu Lavoie
DESCRIPTION:    Header file for TL1 FTP Facade declaration
----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FTPFACADE_H__
#define __TL1_FTPFACADE_H__

#ifndef __TL1_FTP_DOMAIN_H__
#include <TL1Core/TL1_FtpDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_Copy(theTransferType, theSrcUrl, theDestUrl, theOverwriteValue, theProhibitpktsave, theSeqNum, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, Copy( theTransferType, theSrcUrl, theDestUrl, theOverwriteValue, theProhibitpktsave, theSeqNum, theResponse ))

#define FACI_Delete(theFileUrl, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, Delete( theFileUrl, theResponse ))

#define FACI_Retrieve(theFileUrl, theRecursiveValue, theStorageUsage, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, Retrieve( theFileUrl, theRecursiveValue, theStorageUsage, theResponse ))

#endif //__TL1_DBFACADE_H__
