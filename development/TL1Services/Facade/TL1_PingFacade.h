/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2009 - Tom Novak
DESCRIPTION:    Header file for TL1 Ping Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PINGFACADE_H__
#define __TL1_PINGFACADE_H__

#ifndef __TL1_PINGENTITY_H__
#include <TL1Core/TL1_PingEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_OprPing( ipAddr, timeout, pktsize, pktcnt, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, OprPing( ipAddr, timeout, pktsize, pktcnt, tl1RspBlk) )
                     
#endif
