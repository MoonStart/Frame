/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         Oct 5, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 External Control Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONTRSPBLK_H__
#define __TL1_CONTRSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef CT_EQUIPMENT
#include <CommonTypes/CT_Equipment.h>
#endif
 
#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif
 
#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

class TL1_ContRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_ContRspBlk() {}
    
    TL1_ContRspBlk( const TL1_ContRspBlk& );

    TL1_ContRspBlk( const TL1_SmartParameter<CT_TL1_LogicalAddr>& theAddr,
                    const TL1_SmartParameter<CT_ContType>& theType,
                    const TL1_SmartParameter<CT_ContDuration>& theDuration,
                    const TL1_SmartParameter<CT_ContState>& theState );
    
    virtual ~TL1_ContRspBlk();

    TL1_ContRspBlk& operator=( const TL1_ContRspBlk& theBlock );

    const TL1_SmartParameter<CT_TL1_LogicalAddr>& GetAddr() const;

    const TL1_SmartParameter<CT_ContType>& GetType() const;

    const TL1_SmartParameter<CT_ContDuration>& GetDuration() const;    

    const TL1_SmartParameter<CT_ContState>& GetState() const;

private:
    TL1_SmartParameter<CT_TL1_LogicalAddr> itsAddr;
    TL1_SmartParameter<CT_ContType> itsType;
    TL1_SmartParameter<CT_ContDuration> itsDuration;    
    TL1_SmartParameter<CT_ContState> itsState;
};

typedef TL1_Rtv_Response< TL1_ContRspBlk > TL1_ContResponse;

#endif


