/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive SNMP Response Class
TARGET:
AUTHOR:         Michael Sharkey
DESCRIPTION:    Header file for TL1 Retrive SNMP Response class declaration
-----------------------------------------------------------------------------*/
#ifndef __TL1_BWPFRSPBLK_H_
#define __TL1_BWPFRSPBLK_H_

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
//	RtrvBwpf
//

class TL1_BwpfRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_BwpfRspBlk() {}
    
    TL1_BwpfRspBlk(const TL1_BwpfRspBlk&);

    TL1_BwpfRspBlk(
                    const uint32*   theProfileId,
                    const int*      theCir,
                    const int*      theCbs);
    
    virtual ~TL1_BwpfRspBlk();

    TL1_BwpfRspBlk& operator=( const TL1_BwpfRspBlk& theBlock );

    bool GetProfileId( uint32&) const;
    bool GetCir( int&) const;
    bool GetCbs( int&) const;

private:

    enum {
        INDEX_ProfileId,
        INDEX_Cir,
        INDEX_Cbs,
        INDEX_END
    };

    vector<bool>       myBitSet;
    uint32             myProfileId;
    int                myCir;
    int                myCbs;
};

typedef TL1_Rtv_Response< TL1_BwpfRspBlk > TL1_BwpfResponse;

#endif
