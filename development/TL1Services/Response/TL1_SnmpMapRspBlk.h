/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive SNMP Response Class
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Header file for TL1 Retrive SNMP Response class declaration
-----------------------------------------------------------------------------*/
#ifndef __TL1_SNMPMAPRSPBLK_H_
#define __TL1_SNMPMAPRSPBLK_H_

#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_TL1_BASE_H_
#include <CommonTypes/CT_TL1_Base.h>
#endif

#include <vector>

using namespace std;

//
//	RtrvSnmpMap
//

class TL1_SnmpMapRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SnmpMapRspBlk() {}
    
    TL1_SnmpMapRspBlk(const TL1_SnmpMapRspBlk&);

    TL1_SnmpMapRspBlk(
					const string*				theROCname,
					const string*				theRWCname,
					const string*			    theRemoteTid);
    
    virtual ~TL1_SnmpMapRspBlk();

    TL1_SnmpMapRspBlk& operator=( const TL1_SnmpMapRspBlk& theBlock );

    bool GetROCname( string&) const;
    bool GetRWCname( string&) const;
    bool GetRemoteTid( string&) const;

private:

    enum {
        INDEX_ROCname,
        INDEX_RWCname,
        INDEX_RemoteTid,
        INDEX_END
	};

    vector<bool>      	 myBitSet;
    string				 myROCname;
    string				 myRWCname;
    string				 myRemoteTid;
};

typedef TL1_Rtv_Response< TL1_SnmpMapRspBlk > TL1_SnmpMapResponse;

#endif
