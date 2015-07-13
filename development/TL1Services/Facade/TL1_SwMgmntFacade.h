/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         June 10, 2003- Mathieu Lavoie
DESCRIPTION:    Header file for TL1 Sw facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SWFACADE_H__
#define __TL1_SWFACADE_H__

#ifndef __TL1_SWENTITY_H__
#include <TL1Core/TL1_SwMgmntEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_OprUpgAbort( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateUpgAbort( theResponse ))

#define FACI_OprUpgCheck( theSrcUrl, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateUpgCheck( theSrcUrl, theResponse ))

#define FACI_OprUpgCommit( theCommandMode,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateUpgCommit( theCommandMode, theResponse ))

#define FACI_OprUpgExecute( theCommandMode,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateUpgExecute( theCommandMode, theResponse ))

#define FACI_OprUpgInstall( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperateUpgInstall( theResponse ))

#define FACI_InstallCef( theFile, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, InstallCef(theFile, theResponse))

#define FACI_RtvCef( theCefType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCef(theCefType, theResponse))

#define FACI_RtvUpgState( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RetrieveUpgState( theResponse ))

#define FACI_RtvSW( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RetrieveSW( theResponse ))

#define FACI_RtvNEType( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RetrieveNEType( theResponse ))

#define FACI_OprPatchApply( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, OperatePatchApply( theResponse ))

#define FACI_RtrvFpgaVerMap( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvFpgaVerMap( theResponse ))

#define FACI_RtrvSwVerMap( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSwVerMap( theResponse ))

#endif //__TL1_SWFACADE_H__
