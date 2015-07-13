/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive SNMP Response Class
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Header file for TL1 Retrive SNMP Response class declaration
-----------------------------------------------------------------------------*/
#ifndef __TL1_SNMPRSPBLK_H_
#define __TL1_SNMPRSPBLK_H_

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_TL1_BASE_H_
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef _INC_CT_AM_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_AM_Definitions.h>
#endif

#include <vector>

using namespace std;

//
//	RtrvSnmp
//

class TL1_SnmpRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SnmpRspBlk() {}
    
    TL1_SnmpRspBlk(const TL1_SnmpRspBlk&);

    TL1_SnmpRspBlk(	const string*              theAid,
                    const string*              theROCname,
                    const string*              theRWCname,
                    const bool*                thePst);
    
    virtual ~TL1_SnmpRspBlk();

    TL1_SnmpRspBlk& operator=( const TL1_SnmpRspBlk& theBlock );

    bool GetAid(string&) const;
    bool GetROCname( string&) const;
    bool GetRWCname( string&) const;
    bool GetPst(bool&) const;

private:

    enum {
        INDEX_Aid = 0,
        INDEX_ROCname,
        INDEX_RWCname,
        INDEX_Pst,
        INDEX_END
    };

    vector<bool>        myBitSet;
    string              myAid;
    string              myROCname;
    string              myRWCname;
    bool                myPst;
};

typedef TL1_Rtv_Response< TL1_SnmpRspBlk > TL1_SnmpResponse;


//
//	RtrvEngIdMap
//

class TL1_EngIdMapRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_EngIdMapRspBlk() {}
    
    TL1_EngIdMapRspBlk(const TL1_EngIdMapRspBlk&);

    TL1_EngIdMapRspBlk(	const string* theAid,
                             const CT_ShelfId* theShelfId,
                             const string* theEngIdString);
    
    virtual ~TL1_EngIdMapRspBlk();

    TL1_EngIdMapRspBlk& operator=( const TL1_EngIdMapRspBlk& theBlock );

    bool GetAid(string&) const;
    bool GetShelfId(CT_ShelfId&) const;
    bool GetEngIdString(string&) const;

private:

    enum {
        INDEX_Aid = 0,
        INDEX_ShelfId,
        INDEX_EngIdString,
        INDEX_END
    };

    vector<bool> myBitSet;
    string       myAid;
    CT_ShelfId   myShelfId;
    string       myEngIdString;
};

typedef TL1_Rtv_Response< TL1_EngIdMapRspBlk > TL1_EngIdMapResponse;

//
//	Rtrv TrapIp
//

class TL1_TrapIpRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_TrapIpRspBlk() {}
    
    TL1_TrapIpRspBlk(const TL1_TrapIpRspBlk&);

    TL1_TrapIpRspBlk(   const uint32* theIpAddr,
                        const string* theName,
                        const uint16* thePort,
                        const int* theVersion,
                        const string* theUid);
    
    virtual ~TL1_TrapIpRspBlk();

    TL1_TrapIpRspBlk& operator=( const TL1_TrapIpRspBlk& theBlock );

    bool GetIpAddr(uint32*) const;
    bool GetName(string&) const;
    bool GetPort(uint16&) const;
    bool GetVersion(int&) const;
    bool GetUid(string&) const;

private:

    enum {
        INDEX_IpAddr = 0,
        INDEX_Name,
        INDEX_Port,
        INDEX_Version,
        INDEX_Uid,
        INDEX_END
    };

    vector<bool>    myBitSet;
    uint32          myIpAddr[4];
    string          myName;
    uint16          myPort;
    int             myVersion;
    string          myUid;
};

typedef TL1_Rtv_Response< TL1_TrapIpRspBlk > TL1_TrapIpResponse;

#endif
