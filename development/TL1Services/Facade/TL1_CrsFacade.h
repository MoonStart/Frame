/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 16, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 cross-connection Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CRSFACADE_H__
#define __TL1_CRSFACADE_H__

#ifndef __FC_BBOBJECT_H__
#include <Blackboard/FC_BbObject.h>
#endif

#ifndef __TL1_CRSDOMAIN_H__
#include <TL1Core/TL1_CrsDomain.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_RtrvCrs( theHandle, theAddr, theGrpId, theBrtaMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCrs( theHandle, theAddr, theGrpId, theBrtaMode, theResponse ))

#define FACI_RtrvCrsRanging( theFirstAddr, theLastAddr, theGrpId, theBrtaMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCrs( theFirstAddr, theLastAddr, theGrpId, theBrtaMode, theResponse ))

#define FACI_EntCrs( theAddr, theType, theCircuitId, theRdld, thePathData, theGrpId, theSrcProtType, theDstProtType, theResponse, theHandle, theCtag, theCommandMode ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntCrs( theAddr, theType, theCircuitId, theRdld, thePathData, theGrpId, theSrcProtType, theDstProtType, theResponse, theHandle, theCtag, theCommandMode ))

#define FACI_EdCrs( theAddr, theCircuitId, theRdld, theIncl, theSrcProtType, theDstProtType, thePathData, theAddTo, theAddToFacType, theRemoveTo, theRemoveToFacType, theAddProtTo, theAddProtToFacType, theRemoveProtTo, theRemoveProtToFacType, theGrpId, theOldTP, theOldTPFacType, theNewTP, theNewTPFacType, theCommandMode, theAddSrcProt, theAddSrcProtFacType, theAddDstProt, theAddDstProtFacType, theRmvProt, theRmvProtFacType, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdCrs( theAddr, theCircuitId, theRdld, theIncl, theSrcProtType, theDstProtType, thePathData, theAddTo, theAddToFacType, theRemoveTo, theRemoveToFacType, theAddProtTo, theAddProtToFacType, theRemoveProtTo, theRemoveProtToFacType, theGrpId, theOldTP, theOldTPFacType, theNewTP, theNewTPFacType, theCommandMode, theAddSrcProt, theAddSrcProtFacType, theAddDstProt, theAddDstProtFacType, theRmvProt, theRmvProtFacType, theResponse, theHandle, theCtag ))

#define FACI_DltCrs( theAddr, theIncl, theCommandMode, theResponse, theHandle, theCtag ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltCrs( theAddr, theIncl, theCommandMode, theResponse, theHandle, theCtag ))

#define FACI_EntRoll( fromFac, toFac, rollFromFac, rollToFac, ctAutoManual, ctIncl, rspBlk, theHandle, theCtag  ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntRoll( fromFac, toFac, rollFromFac, rollToFac, ctAutoManual, ctIncl, rspBlk, theHandle, theCtag ))

#define FACI_DltRoll( fromFac, toFac, ctIncl, rspBlk, theHandle, theCtag  ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltRoll( fromFac, toFac, ctIncl, rspBlk, theHandle, theCtag ))

#endif
