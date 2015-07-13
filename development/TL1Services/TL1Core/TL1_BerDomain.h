/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 27, 2012 - Leo LU
DESCRIPTION:    Header file for TL1 Switch Domain Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_BERDOMAIN_H__
#define __TL1_BERDOMAIN_H__

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __CT_TL1_EQPTADDR_H__
#include <CommonTypes/CT_TL1_EqptAddr.h>
#endif

#ifndef __CT_AGENTFACILITY_H__
#include <CommonTypes/CT_AgentFacility.h>
#endif

class TL1_Response;

/**
   CLASS TL1_BerDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of BER ALL related TL1 commands, that 
   a TL1 Entities for a BER ALL is expected to implement. 
   This class contains no data member nor any default 
   implementation. 
 */

class TL1_BerDomain
{
public:

    virtual void RtrvBer( const CT_TL1_FacAddr& theFacAddr,
                          TL1_Response& theResponse) = 0;

    virtual void StartBer(const CT_TL1_FacAddr& theFacAddr,
                          CT_FAC_BerType* berType,
                          CT_FAC_BerCtrl* prbsTx,
                          CT_FAC_BerCtrl* prbsRx,
                          CT_TEL_PrbsFormat* prbsCompa,
                          TL1_Response& theResponse)=0;

    virtual void StopBer(const CT_TL1_FacAddr& theFacAddr,
                         CT_FAC_BerType* berType,
                         CT_FAC_BerCtrl* prbsTx,
                         CT_FAC_BerCtrl* prbsRx,
                          TL1_Response& theResponse)=0;

};

#endif

