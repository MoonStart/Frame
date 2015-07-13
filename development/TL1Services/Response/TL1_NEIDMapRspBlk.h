/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive DNS Response Class
TARGET:
AUTHOR:         Jun 22, 2009- Lei Cao
DESCRIPTION:    Header file for TL1 Retrive NEIDMap Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NEIDMAPRSPBLK_H_
#define __TL1_NEIDMAPRSPBLK_H_

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __CT_EON_H__
#include <CommonTypes/CT_EON.h>
#endif

#include <ss_gdef.h>

#include <vector>

using namespace std;


class TL1_NEIDMapRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_NEIDMapRspBlk() {};
    
    TL1_NEIDMapRspBlk(const TL1_NEIDMapRspBlk& );

    TL1_NEIDMapRspBlk(const TL1_SmartParameter<CT_ShelfId>& theShelfNumber,
                            const TL1_SmartParameter<uint32> theIPAddress,
                            const TL1_SmartParameter<string> theTid,
                            const TL1_SmartParameter<string> theEngineid,
                            const TL1_SmartParameter<CT_ProdType> theProdType,
                            const TL1_SmartParameter<CT_LinkInfo> theLink,
                            const TL1_SmartParameter<bool> theMode);
    
    virtual ~TL1_NEIDMapRspBlk();

    TL1_NEIDMapRspBlk& operator=( const TL1_NEIDMapRspBlk& theBlock );

    const TL1_SmartParameter<string>& 
        GetTid() const
    {
        return itsTid;
    }

    const TL1_SmartParameter<string>& 
        GetEngineID() const
    {
        return itsEngineid;
    }

    const TL1_SmartParameter<uint32>& 
        GetIPAddress() const
    {
        return itsIPAddress;
    }

    const TL1_SmartParameter<bool>& 
        GetMode() const
    {
        return itsMode;
    }

    const TL1_SmartParameter<CT_ShelfId>& 
        GetShelfNumber() const
    {
        return itsShelfNumber;
    }

    const TL1_SmartParameter<CT_ProdType>& 
        GetProdType() const
    {
        return itsProdType;
    }

    const TL1_SmartParameter<CT_LinkInfo>& 
        GetLinkInfor() const
    {
        return itsLink;
    }
private:


    TL1_SmartParameter<CT_ShelfId> itsShelfNumber;
    TL1_SmartParameter<uint32> itsIPAddress;
    TL1_SmartParameter<string> itsTid;
    TL1_SmartParameter<string> itsEngineid;
    TL1_SmartParameter<CT_ProdType> itsProdType;
    TL1_SmartParameter<CT_LinkInfo> itsLink;
    TL1_SmartParameter<bool> itsMode;
};

typedef TL1_Rtv_Response< TL1_NEIDMapRspBlk > TL1_NEIDMapResponse;

#endif


