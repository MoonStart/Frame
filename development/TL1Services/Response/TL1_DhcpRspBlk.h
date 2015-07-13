#ifndef __TL1_DHCPRSPBLK_H_
#define __TL1_DHCPRSPBLK_H_

/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive DHCP Response Class
TARGET:
AUTHOR:         October 19, 2005 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Retrive DHCP Response class declaration
-----------------------------------------------------------------------------*/
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
//	RtrvDhcp
//

class TL1_DhcpRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_DhcpRspBlk() {}
    
    TL1_DhcpRspBlk(const TL1_DhcpRspBlk&);

    TL1_DhcpRspBlk(	const string*				theAid,
							const string*				theHWID,
							const CT_ProfileTableId*	theProfileId,
							const bool*                 theOption82,
                            const uint32*				theServerIp,
							const uint32*				theMinIp,
							const uint32*				theMaxIp,
							const bool*					theStatus,
							const CT_SM_PST*			thePst,
							const CT_SM_PSTQ*			thePstq,
							const CT_SM_SST*			theSst	);
                 
    
    virtual ~TL1_DhcpRspBlk();

    TL1_DhcpRspBlk& operator=( const TL1_DhcpRspBlk& theBlock );

    bool GetAid(string&) const;
    bool GetHWID( string&) const;
    bool GetProfileId(CT_ProfileTableId&) const;
    bool GetMinIp(uint32&) const;
    bool GetMaxIp(uint32&) const;
    bool GetStatus(bool&) const;
    bool GetOption82(bool&) const;
    bool GetServerIp(uint32&) const;
    bool GetPst(CT_SM_PST&) const;
    bool GetPstq(CT_SM_PSTQ&) const;
    bool GetSst(CT_SM_SST&) const;

private:

    enum {
        INDEX_Aid = 0,
        INDEX_HWID,
        INDEX_ProfileId,
        INDEX_Option82,
        INDEX_ServerIp,
        INDEX_MinIp,
        INDEX_MaxIp,
        INDEX_Status,  
        INDEX_Pst,
        INDEX_Pstq,
        INDEX_Sst,
        INDEX_END
	};

    vector<bool>      myBitSet;
    string				 myAid;
    string				 myHWID;
    CT_ProfileTableId	myProfileId;
    bool			     myOption82;
    uint32				 myServerIp;
    uint32				 myMinIp;
    uint32				 myMaxIp;
    bool			     myStatus;
    CT_SM_PST			 myPst;
    CT_SM_PSTQ			 myPstq;
    CT_SM_SST			 mySst;
};

typedef TL1_Rtv_Response< TL1_DhcpRspBlk > TL1_DhcpResponse;


//
//	RtrvDhcpIpaddr
//

class TL1_DhcpIpaddrRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_DhcpIpaddrRspBlk() {}
    
    TL1_DhcpIpaddrRspBlk(const TL1_DhcpIpaddrRspBlk& );

    TL1_DhcpIpaddrRspBlk(
							const string*				theHwid,
							const string*				theRneTid,
							const uint32*				theRneIp);
                 
    
    virtual ~TL1_DhcpIpaddrRspBlk();

    TL1_DhcpIpaddrRspBlk& operator=( const TL1_DhcpIpaddrRspBlk& theBlock );

    bool GetHwid(string&) const;
    bool GetRneTid(string&) const;
    bool GetRneIp(uint32&) const;


private:

    enum {
        INDEX_Aid = 0,
        INDEX_Hwid,
        INDEX_RneTid,
        INDEX_RneIp,
        INDEX_END
	};

    vector<bool>     myBitSet;
    string				myHwid;
    string				myRneTid;
    uint32				myRneIp;
};

typedef TL1_Rtv_Response< TL1_DhcpIpaddrRspBlk > TL1_DhcpIpaddrResponse;

#endif
