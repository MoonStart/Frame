/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         Jun 19, 2007 - Ed Banyk
DESCRIPTION:    Header file for TL1 SNMP Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SNMPDOMAIN_H__
#define __TL1_SNMPDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_SM_TYPES_H__
#include <CommonTypes/CT_SM_Types.h>
#endif

class TL1_Response;


/**
   CLASS TL1_SnmpDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of equipment related TL1 command a TL1 Entity
   for SNMP is expected to implement. This class contains no
   data member nor any default implementation.
 */
class TL1_SnmpDomain
{
public:
    virtual void EdSnmp( string* ctROCname,
                         string* ctRWCname,
                         bool* ctSnmpV3Status,
                         bool* ctSnmpPst,
                         TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvSnmp( TL1_Response& tl1RspBlk ) = 0;

    virtual void EntTrapIp( uint32* theIPAddress,
                            string* theMgrName,
                            uint16* thePort,
                            int* theVersion,
                            string* theUid,
                            TL1_Response& theResponse) = 0;

    virtual void DltTrapIp( uint32* theIPAddress, 
                            uint16* thePort,
                            TL1_Response& theResponse) = 0;

    virtual void RtrvTrapIp( TL1_Response& theResponse) = 0;

    virtual void RtrvEngIdMap( TL1_Response& tl1RspBlk ) = 0;

    virtual void DltCnameTidMap(
                         string* ctROCname,
                         string* ctRWCname,
                         string* ctRemoteTid,
                         TL1_Response& tl1RspBlk) = 0;

    virtual void EntCnameTidMap(
                         string* ctROCname,
                         string* ctRWCname,
                         string* ctRemoteTid,
                         TL1_Response& tl1RspBlk) = 0;

    virtual void EdCnameTidMap(
                         string* ctROCname,
                         string* ctRWCname,
                         string* ctRemoteTid,
                         TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvCnameTidMap(
                         string* ctROCname,
                         string* ctRWCname,
                         string* ctRemoteTid,
                         TL1_Response& tl1RspBlk) = 0;


    virtual void DltSnmpCommPrefix(
                         string* ctAuthStr, 
                         TL1_Response& tl1RspBlk) = 0;

    virtual void EntSnmpCommPrefix(
                         string* ctAuthStr,
                         TL1_Response& tl1RspBlk) = 0;

    virtual void EdSnmpCommPrefix(
                         string* ctOldAuthStr,
                         string* ctNewAuthStr,
                         TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvSnmpCommPrefix( TL1_Response& tl1RspBlk) = 0;

    virtual void RtrvSnmpCommStr( TL1_Response& tl1RspBlk) = 0;
    virtual void InhSnmpV2( TL1_Response& tl1RspBlk) = 0;
    virtual void AlwSnmpV2( TL1_Response& tl1RspBlk) = 0;
};

#endif //__TL1_SNMPDOMAIN_H__
