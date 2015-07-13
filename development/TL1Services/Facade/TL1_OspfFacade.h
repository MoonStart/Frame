/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Lee Gernes
DESCRIPTION:    Header file for TL1 OSPF Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSPFFACADE_H__
#define __TL1_OSPFFACADE_H__

#ifndef __TL1_OSPFENTITY_H__
#include <TL1Core/TL1_OspfEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


// OSPF
#define FACI_EntOspf( theAddr, theRouterId, theAsbr, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntOspf( theAddr, theRouterId, theAsbr, thePst, theResponse ))

#define FACI_EdOspf( theId, theRouterId, theCMode, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdOspf( theId, theRouterId, theCMode, thePst, theResponse ))

#define FACI_DltOspf( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltOspf( theId, theResponse ))

#define FACI_RtrvOspf( theId, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOspf( theId, thePst, theResponse ))

//OSPF ADJ
#define FACI_EntOspfAdj( theAdjAddr, theParams, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntOspfAdj( theAdjAddr, theParams, theResponse ))

#define FACI_EdOspfAdj( theAdjAddr, theParams, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdOspfAdj( theAdjAddr, theParams, theResponse ))

#define FACI_DltOspfAdj( theAdjAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltOspfAdj( theAdjAddr, theResponse ))

#define FACI_RtrvOspfAdj( theAdjAddr, theInterfaceAddr, theAreaAddr, ctAdjStatus, ctPst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOspfAdj( theAdjAddr, theInterfaceAddr, theAreaAddr, ctAdjStatus, ctPst, theResponse )) 

//OSPF AREA
#define FACI_EntOspfArea( theAddr, theRouterAreaId, thePrtPfAddr, theHub, theRroVisibility, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntOspfArea( theAddr, theRouterAreaId, thePrtPfAddr, theHub, theRroVisibility, thePst, theResponse ))

#define FACI_EdOspfArea( theAreaAddr, thePrtPfAddr, theCMode, theHub, theRroVisibility, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdOspfArea( theAreaAddr, thePrtPfAddr, theCMode, theHub, theRroVisibility, thePst, theResponse ))

#define FACI_DltOspfArea( theAreaAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltOspfArea( theAreaAddr, theResponse ))

#define FACI_RtrvOspfArea( theAreaAddr, ctPst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOspfArea( theAreaAddr, ctPst, theResponse )) 

// OSPFRPMAP
#define FACI_EntOspfrpmap( theAddr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntOspfrpmap( theAddr, theResponse ))

#define FACI_DltOspfrpmap( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltOspfrpmap( theId, theResponse ))

#define FACI_RtrvOspfrpmap( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOspfrpmap( theId, theResponse ))

// OSPFRP
#define FACI_EntOspfrp( theAddr, theEntParameters, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntOspfrp( theAddr, theEntParameters, theResponse ))

#define FACI_EdOspfrp( theId, theEdParameters, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdOspfrp( theId, theEdParameters, theResponse ))

#define FACI_DltOspfrp( theId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltOspfrp( theId, theResponse ))

#define FACI_RtrvOspfrp( theId, theChildRtAreaId, theParentRtAreaId, theEntryType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvOspfrp( theId, theChildRtAreaId, theParentRtAreaId, theEntryType,theResponse ))

#endif
