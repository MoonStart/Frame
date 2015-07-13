/*-----------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive CFPF Response Class
TARGET:
AUTHOR:         Maggie Zhang
DESCRIPTION:    Header file for TL1 Retrive CFPF Response class declaration
-----------------------------------------------------------------------------*/
#ifndef __TL1_CFPFRSPBLK_H_
#define __TL1_CFPFRSPBLK_H_

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
//	RtrvCfpf
//

class TL1_CfpfRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_CfpfRspBlk() {}
    
    TL1_CfpfRspBlk(const TL1_CfpfRspBlk&);

    TL1_CfpfRspBlk(
                    const uint32*   theProfileId,
                    const bool*      theLacp,
                    const bool*      theLinkOAM,
                    const bool*      theDot1X,
                    const bool*      theElmi,
                    const bool*      theLldp,
                    const bool*      theGarp);
    
    virtual ~TL1_CfpfRspBlk();

    TL1_CfpfRspBlk& operator=( const TL1_CfpfRspBlk& theBlock );

    bool GetProfileId( uint32&) const;
    bool GetLacp( bool&) const;
    bool GetLinkOAM( bool&) const;
    bool GetDot1X( bool&) const;
    bool GetElmi( bool&) const;
    bool GetLldp( bool&) const;
    bool GetGarp( bool&) const;

private:

    enum {
        INDEX_ProfileId,
        INDEX_Lacp,
        INDEX_LinkOAM,
        INDEX_Dot1X,
        INDEX_Elmi,
        INDEX_Lldp,
        INDEX_Garp,
        INDEX_END
    };

    vector<bool>       myBitSet;
    uint32             myProfileId;
    bool            myLacp;
    bool            myLinkOAM;
    bool            myDot1X;
    bool            myElmi;
    bool            myLldp;
    bool            myGarp;
};

typedef TL1_Rtv_Response< TL1_CfpfRspBlk > TL1_CfpfResponse;

#endif
