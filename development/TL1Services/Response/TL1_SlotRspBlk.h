/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Slot Response Class
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Retrive Slot Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLOTRSPBLK_H_
#define __TL1_SLOTRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef _INC_CT_AM_DEFINITIONS_INCLUDED
#include <CommonTypes/CT_AM_Definitions.h>
#endif
 
#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif
 
#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_ACCEPTABLECPLIST_H_
#include <CommonTypes/CT_AcceptableCPList.h>
#endif

#include <vector>

using namespace std;


class TL1_SlotRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_SlotRspBlk() {}
    
    TL1_SlotRspBlk(const TL1_SlotRspBlk& );

    TL1_SlotRspBlk(const TL1_SmartParameter<string>& theEntityName,
                   const TL1_SmartParameter<CT_TL1_SlotAddr>& theSlotAddr,
                   const TL1_SmartParameter<CT_AcceptableCpList>& thePartNumberList,
                   const TL1_SmartParameter<CT_ProfileTableId>& theAlarmProfile,
                   const TL1_SmartParameter<CT_SM_PST>&  thePST,
                   const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                   const TL1_SmartParameter<CT_SM_SST>&  theSST);
    
    virtual ~TL1_SlotRspBlk();

    TL1_SlotRspBlk& operator=( const TL1_SlotRspBlk& theBlock );

    bool operator==( const TL1_SlotRspBlk& theBlock ) const;

    const TL1_SmartParameter<string>& 
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter<CT_TL1_SlotAddr>& 
        GetSlotAddr() const
    {
        return itsSlotAddr;
    }

    const TL1_SmartParameter<CT_AcceptableCpList>& 
        GetPartNumberList() const
    {
        return itsPartNumberList;
    }

    const TL1_SmartParameter<CT_ProfileTableId>&
        GetAlarmProfile() const
    {
        return itsAlarmProfile;
    }

    const TL1_SmartParameter<CT_SM_PST>&
        GetPST() const
    {
        return itsPST;
    }

    const TL1_SmartParameter<CT_SM_PSTQ>&
        GetPSTQ() const
    {
        return itsPSTQ;
    }

    const TL1_SmartParameter<CT_SM_SST>& 
        GetSST() const
    {
        return itsSST;
    }


private:

    TL1_SmartParameter<string>              itsEntityName;
    TL1_SmartParameter<CT_TL1_SlotAddr>     itsSlotAddr;    
    TL1_SmartParameter<CT_AcceptableCpList> itsPartNumberList;
    TL1_SmartParameter<CT_ProfileTableId>   itsAlarmProfile;
    TL1_SmartParameter<CT_SM_PST>           itsPST;
    TL1_SmartParameter<CT_SM_PSTQ>          itsPSTQ;
    TL1_SmartParameter<CT_SM_SST>           itsSST;

};

typedef TL1_Rtv_Response< TL1_SlotRspBlk > TL1_SlotResponse;

#endif


