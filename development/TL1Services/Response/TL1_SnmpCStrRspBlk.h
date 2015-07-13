/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive SNMP Response Class
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Header file for TL1 Retrive SNMP Response class declaration
-----------------------------------------------------------------------------*/
#ifndef __TL1_SNMPCSTRRSPBLK_H_
#define __TL1_SNMPCSTRRSPBLK_H_

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

class TL1_SnmpCStrRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SnmpCStrRspBlk() {}
    
    TL1_SnmpCStrRspBlk(const TL1_SnmpCStrRspBlk&);

    TL1_SnmpCStrRspBlk(
					const string*				theCommStr);
    
    virtual ~TL1_SnmpCStrRspBlk();

    TL1_SnmpCStrRspBlk& operator=( const TL1_SnmpCStrRspBlk& theBlock );

    bool GetCStr( string&) const;

private:

    enum {
        INDEX_CommStr,
        INDEX_END
	};

    vector<bool>      	 myBitSet;
    string				 myCommStr;
};

typedef TL1_Rtv_Response< TL1_SnmpCStrRspBlk > TL1_SnmpCStrResponse;

#endif
