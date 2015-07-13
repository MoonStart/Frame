/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Jun 5, 2003- Stephen Wu
DESCRIPTION:    Header file for TL1 EON Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_EONDOMAIN_H__
#define __TL1_EONDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_EON_H__
#include <CommonTypes/CT_EON.h>
#endif

#ifndef __CT_AM_DEFINITIONS_H__
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#include <CommonTypes/CT_IBETH_Definitions.h>

class TL1_Response;


/**
   CLASS TL1_EONDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of equipment related TL1 command a TL1 Entity
   for EON is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_EONDomain
{
public:
    virtual void EdNET( CT_EONType      *theEONType,
                        CT_EONState     *theEONState,
                        uint32*         theLocalIf,
                        uint32*         theLocalIfMask,
                        uint32*         theManageIf,
                        uint32*         theManageIfMask,
                        uint32*         theRouterIf,
                        uint32*         theRouterIfMask,
                        uint32*         theDCNIf,
                        uint32*         theDCNIfMask,
                        CT_IfSpeed*     theDcnIfSpeed,
                        CT_IfDuplex*    theDcnIfDuplex,
                        uint32*         theGNEIf,
                        uint32*         theGNEIfMask,
                        uint32*         theGateway,
                        bool*           theDhcpClient,
                        string*         theIpSubnet,
                        string*         theNESubnet,
                        bool*           theRadClient,
                        uint32*         theRadIter,
                        uint32*         theRadTmout,
                        CT_NM_ROUTING_CONFIG *theDcnRoutingConfig,
                        TL1_Response&   theResponse ) = 0;

    virtual void RtrvNET( TL1_Response& theResponse ) = 0;

    virtual void EntDNS( string* theTid, 
                         uint32* theIPAddress, 
                         TL1_Response& theResponse ) = 0;

    virtual void EdDNS( string* theTid, 
                        uint32* theIPAddress, 
                        TL1_Response& theResponse ) = 0;

    virtual void DltDNS( string* theTid, 
                         uint32* theIPAddress,  
                   bool* theRneMode,
                         TL1_Response& theResponse ) = 0;

    virtual void RtrvDNS( string* theTid, 
                          uint32* theIPAddress, 
                          TL1_Response& theResponse ) = 0;

    virtual void EdRouter(CT_ProfileTableId* theAlarmProfile,
                          TL1_Response& theResponse ) = 0;

    virtual void RtrvRouter( TL1_Response& theResponse ) = 0;

    virtual void RtrvAdjRouter( uint32* theNeighborIp,
                                CT_IfNumber* theIfName,
                                TL1_Response& theResponse ) = 0;

    virtual void EdIfRouter( bool* theSWstatus,
                             bool* thePSstatus,
                             CT_IfNumber* theIfName,
                             CT_InterfaceType* theIfType,
                             CT_InterfaceMode* theIfMode,
                             uint32* theHelloInt,
                             uint32* theRouterDeadInterval,
                             TL1_Response& theResponse ) = 0;

    virtual void RtrvIfRouter( CT_IfNumber* theIfName,
                               TL1_Response& theResponse ) = 0;

    virtual void RtrvIpRoutingTable( TL1_Response& theResponse ) = 0;

    virtual void GetRadiusStatus(TL1_Response& theResponse) const = 0;

    virtual void EntNEIDMap( string* theTid, 
                         uint32* theIPAddress, 
                         string* theEngineId,
                         CT_ProdType* theProdType,
                         CT_LinkInfo* theLinkInfo,
                         TL1_Response& theResponse) = 0;

    virtual void EdNEIDMap( string* theTid, 
                         uint32* theIPAddress, 
                         string* theEngineId,
                         CT_ProdType* theProdType,
                         CT_LinkInfo* theLinkInfo,
                         TL1_Response& theResponse) = 0;

    virtual void DltNEIDMap( uint32* theIPAddress, 
                         TL1_Response& theResponse) = 0;

    virtual void RtrvNEIDMap( CT_ShelfId* theShelfId, 
                          TL1_Response& theResponse) = 0;
                          
    virtual void EntIfConfig(string theIfIpAddr, 
                           CT_IfName *theIfname,
                           CT_IfType *theIftype,
                           TL1_Response& theResponse) = 0;

    virtual void EdIfConfig(string theIfIpAddr, 
                           CT_IfName *theIfname,
                           CT_IfType *theIftype,
                           TL1_Response& theResponse) = 0;

    virtual void DltIfConfig(CT_IfName *theIfname,
                             CT_IfType *theIftype,
                             TL1_Response& theResponse) = 0;

    virtual void RtrvIfConfig(string theAid, 
                              CT_IfName *theIfname,
                              TL1_Response& theResponse) = 0;

    virtual void EntIppg(string theIfIpAddr, 
                           string theIfname,
                           TL1_Response& theResponse) = 0;

    virtual void EdIppg(string theIppgAid, 
                           string theIfname,
                           TL1_Response& theResponse) = 0;

    virtual void DltIppg(string theIfIpAddr, 
                           TL1_Response& theResponse) = 0;

    virtual void RtrvIppg(string theIppgAid, 
                           TL1_Response& theResponse) = 0;

    virtual void EdProxy(CT_ProxyMode* theProxyMode, 
                         TL1_Response& theResponse) = 0;

    virtual void RtrvProxy(TL1_Response& theResponse) = 0;


    virtual void RenewIfConfig(CT_IfName *theIfname,
                              TL1_Response& theResponse) = 0;

	virtual void EdMtera(uint32*         theLocalIf,
                        uint32*         theLocalIfMask,
                        uint32*         theLocalIfGtw,
                        TL1_Response&   theResponse ) = 0;

    virtual void RtrvMtera( TL1_Response& theResponse ) = 0;

	
	virtual void EdDcnEthPort(CT_DCNETHPORTType*		 theIfname,
							bool* 		theIfstate,
                            bool* 		theZtcstate,
							bool* 		theCmdmde,
							TL1_Response&	theResponse ) = 0;
	
    virtual void RtrvDcnEthPort(CT_DCNETHPORTType*		 theIfname,
		                            TL1_Response& theResponse ) = 0;

	virtual void EntIBBR(CT_Bridge* theBridge,CT_VS* theVs,CT_BridgeVlan* theBridgeVlan,
		                   uint32* theIp,uint32* theIpmask,CT_SM_PST* thePrimaryState,
		                   TL1_Response&   theResponse ) = 0;
	virtual void EdIBBR(CT_Bridge* theBridge,
		                   uint32* theIp,uint32* theIpmask,CT_SM_PST* thePrimaryState,
		                   TL1_Response&   theResponse) = 0;
	virtual void DltIBBR(CT_Bridge* theBridge,TL1_Response&   theResponse) = 0;
	virtual void RtrvIBBR(CT_Bridge* theBridge,TL1_Response&   theResponse) = 0;

};

#endif //__TL1_EONDOMAIN_H__
