/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Link Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LINKFACADE_H__
#define __TL1_LINKFACADE_H__

#ifndef __TL1_LINKENTITY_H__
#include <TL1Core/TL1_LinkEntity.h>
#endif

// Link
#define FACI_DltLink( aHandle, aAddr,  tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltLink( aHandle, aAddr,  tl1RspBlk) )

#define FACI_EdLink( aAddr, linkParms, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdLink( aAddr, linkParms, tl1RspBlk) )

#define FACI_EntLink( aAddr, linkParms, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntLink( aAddr, linkParms, tl1RspBlk) )

#define FACI_RtrvLink( aAddr, ctIfIndex, ctResource, ctNodeAddr, ctNpAddr, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLink( aAddr, ctIfIndex, ctResource, ctNodeAddr, ctNpAddr, tl1RspBlk) )

// TNA Link Map
#define FACI_DltTnaLnkMap( theTnaValue, theTnaType, theLinkAddr, theRspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltTnaLnkMap( theTnaValue, theTnaType, theLinkAddr, theRspBlk) )

#define FACI_EntTnaLnkMap( theTnaValue, theTnaType, theLinkAddr, theRspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntTnaLnkMap( theTnaValue, theTnaType, theLinkAddr, theRspBlk) )

#define FACI_RtrvTnaLnkMap( theTnaValue, theTnaType, theLinkAddr, theRspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTnaLnkMap( theTnaValue, theTnaType, theLinkAddr, theRspBlk) )

// LinkPF
#define FACI_EdLinkProfile( theAddr, \
                            theEdParameters, \
                            theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdLinkProfile( \
                             theAddr, \
                             theEdParameters, \
                             theResponse ) )

#define FACI_RtrvLinkProfile( theAddr, \
                              theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLinkProfile( \
                             theAddr, \
                             theResponse ) )

// TrLink
#define FACI_DltTrLink( aHandle, aAddr,  tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltTrLink( aHandle, aAddr,  tl1RspBlk) )

#define FACI_EdTrLink( aAddr, linkParms, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdTrLink( aAddr, linkParms, tl1RspBlk) )

#define FACI_EntTrLink( aAddr, linkParms, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntTrLink( aAddr, linkParms, tl1RspBlk) )

#define FACI_RtrvTrLink( aAddr, theModuleAddr, theFacSubType, theAdaptation, theIfIndex, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTrLink( aAddr, \
                                         theModuleAddr, \
                                         theFacSubType, \
                                         theAdaptation, \
                                         theIfIndex, \
                                         tl1RspBlk) )

// TceLink
#define FACI_RtrvTceLink( aAddr, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTceLink( aAddr, tl1RspBlk) )

//LadjLink
#define FACI_RtrvLadjLink( aAddr, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvLadjLink( aAddr, tl1RspBlk) )

// Bundled Link                                                                
#define FACI_DltBLink( aHandle, aAddr,  tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltBLink( aHandle, aAddr, tl1RspBlk) )

#define FACI_EdBLink( aAddr, bLinkParms, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdBLink( aAddr, bLinkParms, tl1RspBlk) )

#define FACI_EntBLink( aAddr, bLinkParms, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntBLink( aAddr, bLinkParms, tl1RspBlk) )

#define FACI_RtrvBLink( aAddr, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvBLink( aAddr, tl1RspBlk) )

#define FACI_EdBLinkMember( aAddr, bLinkParms, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdBLinkMember( aAddr, bLinkParms, tl1RspBlk) )

#define FACI_RtrvBLinkMember( aAddr, tl1RspBlk) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvBLinkMember( aAddr, tl1RspBlk) )

#endif
