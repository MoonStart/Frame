/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Static Route Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_STATICROUTEFACADE_H__
#define __TL1_STATICROUTEFACADE_H__

#ifndef __TL1_STATRTEENTITY_H__
#include <TL1Core/TL1_StatRteEntity.h>
#endif

//State Rte
#define FACI_DltStatRte( theDltParameters, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltStatRte(  theDltParameters, tl1RspBlk) )

#define FACI_DltStatRteIpv6( theDltParameters, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltStatRteIpv6(  theDltParameters, tl1RspBlk) )

#define FACI_EntStatRte( theEntParameters, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntStatRte( theEntParameters, tl1RspBlk) )

#define FACI_EntStatRteIpv6( theEntParameters, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntStatRteIpv6( theEntParameters, tl1RspBlk) )

#define FACI_EdStatRte( theEdParameters, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdStatRte( theEdParameters, tl1RspBlk) )

#define FACI_RtrvStatRte( theDestination, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvStatRte( theDestination, tl1RspBlk) )

#define FACI_RtrvRteAll( tl1RspBlk ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvRteAll( tl1RspBlk ) )

                                    
#endif
