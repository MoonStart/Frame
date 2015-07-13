/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OSPF Response Class
TARGET:
AUTHOR:         Keith Halsall - August 8, 2012
DESCRIPTION:    Header file for TL1 Retrive DA Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DARSPBLK_H_
#define __TL1_DARSPBLK_H_

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

#ifndef __CT_TL1_CONTROLPLANEADDR_H__
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>
#endif

#ifndef __CT_CONTROLPLANE_DEFINITIONS_H__
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#endif


using namespace std;


class TL1_DaRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_DaRspBlk();
    
    TL1_DaRspBlk(const TL1_DaRspBlk& );

    TL1_DaRspBlk( const string                      theEntityName,
                  const CT_TL1_DiscoveryAgentAddr   theDaAddr,
                  const CT_TL1_LinkAddr             theDcnLinkAddr,
                  const string                      theMgtDomain,
                  const CT_SM_PST                   thePst,
                  const CT_SM_PSTQ                  thePstq);
                 
    
    virtual ~TL1_DaRspBlk();

    TL1_DaRspBlk& operator=( const TL1_DaRspBlk& theBlock );

    bool operator==( const TL1_DaRspBlk& theRspBlk ) const;
  
    bool GetEntityName(string& theEntityName) const;
    void SetEntityName(const string& theEntityName);

    bool GetAddr(CT_TL1_DiscoveryAgentAddr& theDaAddr) const;
    void SetAddr(const CT_TL1_DiscoveryAgentAddr& theDaAddr);

    bool GetDcnLinkAddr(CT_TL1_LinkAddr& theDcnLinkAddr) const;
    void SetDcnLinkAddr(const CT_TL1_LinkAddr& theDcnLinkAddr);

    bool GetMgtDomain(string& theMgtDomain) const;
    void SetMgtDomain(const string& theMgtDomain);

    bool GetPST(CT_SM_PST& thePst) const;
    void SetPST(const CT_SM_PST& thePst);

    bool GetPSTQ(CT_SM_PSTQ& thePstq) const;
    void SetPSTQ(const CT_SM_PSTQ& thePstq);

private:

    enum
    {
        INDEX_EntityName = 0,
        INDEX_Addr,
        INDEX_DcnLinkAddr,
        INDEX_MgtDomain,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_END
    };

    vector<bool>        myBitSet;
    string              myEntityName;
    CT_TL1_DiscoveryAgentAddr myDaAddr;
    CT_TL1_LinkAddr     myDcnLinkAddr;
    string              myMgtDomain;
    CT_SM_PST           myPst;
    CT_SM_PSTQ          myPstq;

};

typedef TL1_Rtv_Response< TL1_DaRspBlk > TL1_DaResponse;

#endif
