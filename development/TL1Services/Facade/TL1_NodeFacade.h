/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Node Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NODEFACADE_H__
#define __TL1_NODEFACADE_H__

#ifndef __TL1_NODEENTITY_H__
#include <TL1Core/TL1_NodeEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


// Node

#define FACI_DltNode( aAddr,  tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltNode( aAddr,  tl1RspBlk) )

#define FACI_EdNode( aAddr, ctNodeName, ctAreaId, ctPst, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdNode( aAddr, ctNodeName, ctAreaId, ctPst, tl1RspBlk) )

#define FACI_EntNode( aAddr, ctNodeName, ctNodeIp, ctAreaId, ctPst, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntNode( aAddr, ctNodeName, ctNodeIp, ctAreaId, ctPst, tl1RspBlk) )

#define FACI_RtrvNode( aAddr, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvNode( aAddr, tl1RspBlk) )
                                 
#endif
