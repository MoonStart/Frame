/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 3, 2003- Jean-Francois Tremblay
DESCRIPTION:    Header file for TL1 Retrieve Internal IP Address Response
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_INTIPRSPBLK_H_
#define __TL1_INTIPRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif
 
#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif


class TL1_IntIpRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_IntIpRspBlk() {}
    
    TL1_IntIpRspBlk( const TL1_IntIpRspBlk& );

    TL1_IntIpRspBlk( const TL1_SmartParameter<CT_TL1_SlotAddr>& theSlotAddr,
                     const TL1_SmartParameter<uint32>&  theIpAddress);
    
    virtual ~TL1_IntIpRspBlk();

    TL1_IntIpRspBlk& operator=( const TL1_IntIpRspBlk& theBlock );

    const TL1_SmartParameter<uint32>& GetIPAddress() const;

    const TL1_SmartParameter<CT_TL1_SlotAddr>& GetSlotAddr() const;

private:

    TL1_SmartParameter<CT_TL1_SlotAddr> itsSlotAddr;    
    TL1_SmartParameter<uint32>          itsIpAddress;

};

typedef TL1_Rtv_Response< TL1_IntIpRspBlk > TL1_IntIpResponse;

#endif


