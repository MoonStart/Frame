/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 5, 2003- Stephen Wu
DESCRIPTION:    Header file for TL1 EON Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EONFACADE_H__
#define __TL1_EONFACADE_H__

#ifndef __TL1_EONENTITY_H__
#include <TL1Core/TL1_EONEntity.h>
#endif

#ifndef __TL1_DHCPENTITY_H__
#include <TL1Core/TL1_DhcpEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_EdNET( theEONType, theEONState, theLocalIf, theLocalIfMask, theManageIf, theManageIfMask, theRouterIf, theRouterIfMask, theDCNIf_2_0, theDCNIf_2_0Mask, theDcnIfSpeed, theDcnIfDuplex, theGNEIf, theGNEIfMask, theGateway, theDhcpClient, theIpSubnet, theNESubnet, theRadClient, theRadIter, theRadTmout, theDcnRoutingConfig, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdNET( theEONType, theEONState, theLocalIf, theLocalIfMask, theManageIf, theManageIfMask, theRouterIf, theRouterIfMask, theDCNIf_2_0, theDCNIf_2_0Mask, theDcnIfSpeed, theDcnIfDuplex, theGNEIf, theGNEIfMask, theGateway, theDhcpClient, theIpSubnet, theNESubnet, theRadClient, theRadIter, theRadTmout, theDcnRoutingConfig, theResponse ))

#define FACI_RtrvNET( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvNET( theResponse ))

#define FACI_EntDNS( theTid, theIPAddress, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntDNS( theTid, theIPAddress, theResponse ))

#define FACI_EdDNS( theTid, theIPAddress, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdDNS( theTid, theIPAddress, theResponse ))

#define FACI_DltDNS( theTid, theIPAddress, theRneMode, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltDNS( theTid, theIPAddress, theRneMode, theResponse ))

#define FACI_RtrvDNS( theTid, theIPAddress, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvDNS( theTid, theIPAddress, theResponse ))

#define FACI_EdRouter( theAlarmProfile, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdRouter( theAlarmProfile, theResponse ))

#define FACI_RtrvRouter( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvRouter( theResponse ))

#define FACI_RtrvAdjRouter( theNeighborIp, theIfName, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvAdjRouter( theNeighborIp, theIfName, theResponse ))

#define FACI_EdIfRouter( theSWstatus, thePSstatus, theIfName, theIfType, theIfMode, theHelloInt, theRouterDeadInterval, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdIfRouter( theSWstatus, thePSstatus, theIfName, theIfType, theIfMode, theHelloInt, theRouterDeadInterval, theResponse ))

#define FACI_RtrvIfRouter( theIfName, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIfRouter( theIfName, theResponse ))

#define FACI_RtrvIpRoutingTable( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIpRoutingTable( theResponse ))

#define FACI_EdDhcp( theAid, theAlarmProfile,ctOption82,ctSrvrIp, theDhcpStatus, theMinIpAddr, theMaxIpAddr, theCmdMod, thePst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdDhcp( theAid, theAlarmProfile, ctOption82,ctSrvrIp,theDhcpStatus, theMinIpAddr, theMaxIpAddr, theCmdMod, thePst, theResponse))

#define FACI_DltDhcpipaddr( theAid, theRneIpAddr, theCmdMod, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltDhcpIpaddr( theAid, theRneIpAddr, theCmdMod, theResponse))

#define FACI_RtrvDhcp( theAid, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvDhcp( theAid, theResponse))

#define FACI_RtrvDhcpIpaddr( theAid, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvDhcpIpaddr( theAid, theResponse))

#define FACI_RadiusEnabled( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, GetRadiusStatus( theResponse ))

#define FACI_EntNEIDMap( theTid, theIPAddress,theEngineId,theProdType,theLinkInfor,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntNEIDMap( theTid, theIPAddress, theEngineId,theProdType,theLinkInfor,theResponse ))

#define FACI_EdNEIDMap( theTid, theIPAddress,theEngineId,theProdType,theLinkInfor,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdNEIDMap( theTid, theIPAddress,theEngineId,theProdType,theLinkInfor,theResponse ))

#define FACI_DltNEIDMap(theIPAddress,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltNEIDMap(theIPAddress,theResponse ))

#define FACI_RtrvNEIDMap( theShelfId, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvNEIDMap( theShelfId, theResponse ))

#define FACI_EntIfConfig(theIfIpAddr, theIfname, theIftype, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntIfConfig(theIfIpAddr, theIfname, theIftype, theResponse))

#define FACI_EdIfConfig(theIfIpAddr, theIfname, theIftype, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdIfConfig(theIfIpAddr, theIfname, theIftype, theResponse))

#define FACI_DltIfConfig(theIfname, theIftype, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltIfConfig(theIfname, theIftype, theResponse))

#define FACI_RtrvIfConfig(theAid, theIfname, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIfConfig(theAid, theIfname, theResponse))

#define FACI_EntIppg(theIppgAid, theIfname, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntIppg(theIppgAid, theIfname, theResponse))

#define FACI_EdIppg(theIppgAid, theIfname, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdIppg(theIppgAid, theIfname, theResponse))

#define FACI_DltIppg(theIppgAid, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltIppg(theIppgAid, theResponse))

#define FACI_RtrvIppg(theIppgAid, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIppg(theIppgAid, theResponse))

#define FACI_EdProxy(theProxyMode, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdProxy(theProxyMode, theResponse))

#define FACI_RtrvProxy(theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvProxy(theResponse))

#define FACI_RenewIfConfig(theIfname, theResponse) \
FAC_OP_CONST( NO_SUB_RGN_ID, RenewIfConfig(theIfname, theResponse))

#define FACI_EdMtera(theLocalIf, theLocalIfMask, theLocalIfGtw, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdMtera(theLocalIf, theLocalIfMask, theLocalIfGtw, theResponse ))

#define FACI_RtrvMtera( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvMtera( theResponse ))

#define FACI_EdDcnEthPort(theIfname, theIfstate, theZtcstate, theCmdmde, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdDcnEthPort(theIfname, theIfstate, theZtcstate, theCmdmde, theResponse ))
	
#define FACI_RtrvDcnEthPort( theIfname,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvDcnEthPort( theIfname,theResponse ))

#define FACI_EntIBBR(theBridge, theVs,theBridgeVlan,theIp,theIpmask,thePrimaryState, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntIBBR(theBridge, theVs,theBridgeVlan,theIp,theIpmask,thePrimaryState, theResponse ))

#define FACI_EdIBBR(theBridge,theIp,theIpmask,thePrimaryState, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdIBBR(theBridge,theIp,theIpmask,thePrimaryState, theResponse ))

#define FACI_DltIBBR(theBridge,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltIBBR(theBridge,theResponse ))

#define FACI_RtrvIBBR(theBridge,theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvIBBR(theBridge,theResponse ))


#endif //__TL1_EONFACADE_H__
