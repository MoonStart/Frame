/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Mtera Response Class
TARGET:
AUTHOR:         2013.11.8 - Gang zhu
DESCRIPTION:    Header file for TL1 Retrive mtera Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IPPGRSPBLK_H_
#define __TL1_IPPGRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_EON_H__
#include <CommonTypes/CT_EON.h>
#endif

#include <vector>

#include <cstring>

using namespace std;


class TL1_IppgRspBlk : public TL1_GeneralRspBlk
{
public: 
    TL1_IppgRspBlk() {};
    
    TL1_IppgRspBlk(const TL1_IppgRspBlk& );

    TL1_IppgRspBlk(const TL1_SmartParameter<string>& theIfAid,
                   const TL1_SmartParameter<string>& theIfName,
                   const TL1_SmartParameter<string>& theIppgMems,
                   const TL1_SmartParameter<string>& theActiveMem,
                   const TL1_SmartParameter<LT_PrimaryState>& thePrimaryState);
    
    virtual ~TL1_IppgRspBlk();

    TL1_IppgRspBlk& operator=( const TL1_IppgRspBlk& theBlock );

    const TL1_SmartParameter<string>& GetIfAid() const;

    const TL1_SmartParameter<string>& GetIfName() const;

    const TL1_SmartParameter<string>& GetIfIppgMems() const;

    const TL1_SmartParameter<string>& GetIfActiveMem() const;

    const TL1_SmartParameter<LT_PrimaryState>& GetPrimaryState() const;

private:
    
    TL1_SmartParameter<string>     myIfAid;
    TL1_SmartParameter<string>     myIfName;
    TL1_SmartParameter<string>     myIppgMems;
    TL1_SmartParameter<string>     myActiveMem;
    TL1_SmartParameter<LT_PrimaryState>    myPrimaryState;
};

typedef TL1_Rtv_Response< TL1_IppgRspBlk > TL1_IppgResponse;

#endif


