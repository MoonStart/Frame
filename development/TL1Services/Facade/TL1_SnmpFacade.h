/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 19, 2007 - Ed Bandyk
DESCRIPTION:    Header file for TL1 SNMP Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SNMPFACADE_H__
#define __TL1_SNMPFACADE_H__

#ifndef __TL1_SNMPENTITY_H__
#include <TL1Core/TL1_SnmpEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif

#define FACI_EdSnmp( theROCname, theRWCname, theSnmpReset, theSnmpPst, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSnmp( theROCname, theRWCname, theSnmpReset, theSnmpPst, theResponse))

#define FACI_RtrvSnmp( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSnmp( theResponse))

#define FACI_EntTrapIp( theIpAddress, theMgrName, thePort, theVersion, theUid, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntTrapIp( theIpAddress, theMgrName, thePort, theVersion,theUid, theResponse))

#define FACI_DltTrapIp( theIpAddress, thePort, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltTrapIp( theIpAddress, thePort, theResponse))

#define FACI_RtrvTrapIp( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvTrapIp( theResponse))

#define FACI_RtrvEngIdMap( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvEngIdMap( theResponse))

#define FACI_DltCnameTidMap( theROCname, theRWCname, theTID, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltCnameTidMap( theROCname, theRWCname, theTID, theResponse))

#define FACI_EntCnameTidMap( theROCname, theRWCname, theTID, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntCnameTidMap( theROCname, theRWCname, theTID, theResponse))

#define FACI_EdCnameTidMap( theROCname, theRWCname, theTID, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdCnameTidMap( theROCname, theRWCname, theTID, theResponse))

#define FACI_RtrvCnameTidMap( theROCname, theRWCname, theTID, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvCnameTidMap( theROCname, theRWCname, theTID, theResponse))

#define FACI_DltSnmpCommPrefix( theAuthCStr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DltSnmpCommPrefix( theAuthCStr, theResponse))

#define FACI_EntSnmpCommPrefix( theAuthCStr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EntSnmpCommPrefix( theAuthCStr, theResponse))

#define FACI_EdSnmpCommPrefix( theOldAuthCStr, theNewAuthCStr, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EdSnmpCommPrefix( theOldAuthCStr, theNewAuthCStr, theResponse))

#define FACI_RtrvSnmpCommPrefix( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSnmpCommPrefix( theResponse))

#define FACI_RtrvSnmpCommStr( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvSnmpCommStr( theResponse))

#define FACI_AlwSnmpV2( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, AlwSnmpV2( theResponse))

#define FACI_InhSnmpV2( theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, InhSnmpV2( theResponse))



#endif //__TL1_EONFACADE_H__
