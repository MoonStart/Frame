/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:
AUTHOR:         June 10, 2003- Mathieu Lavoie
DESCRIPTION:    Header file for TL1 Software management response block
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_NETYPE_RSPBLK_H__
#define __TL1_NETYPE_RSPBLK_H__

#ifndef __TL1_RESPONSE_H_
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#ifndef __TL1_GENERALRESPONSEBLK_H_
#include <Response/TL1_GeneralRspBlk.h>
#endif

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_TL1DB_H__
#include <CommonTypes/CT_TL1_SWMgmnt.h>
#endif

#ifndef _CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif


#ifndef __CT_SM_TYPES_H_
#include <CommonTypes/CT_CardInventory.h>
#endif

#ifndef __CT_SMAA_H__
#include <CommonTypes/CT_SMAA.h>
#endif




class TL1_RtrvNETypeRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RtrvNETypeRspBlk(){}

    TL1_RtrvNETypeRspBlk( const TL1_RtrvNETypeRspBlk& theBlock );

    TL1_RtrvNETypeRspBlk( const TL1_SmartParameter< string >&       theVendor,
                      const TL1_SmartParameter< string >&       theSwType,
                      const TL1_SmartParameter< string >&       theSwVersion,
                          const CT_NodeConfiguration  theNodeCfg);

    virtual ~TL1_RtrvNETypeRspBlk();

    TL1_RtrvNETypeRspBlk& operator=( const TL1_RtrvNETypeRspBlk& theBlock );

    const TL1_SmartParameter< string >&
        GetVendor() const
    {
        return itsVendor;
    }

    const TL1_SmartParameter< string >&
        GetSwType() const
    {
        return itsSwType;
    }

    const TL1_SmartParameter< string >&
        GetSwVersion() const
    {
        return itsSwVersion;
    }

    CT_NodeConfiguration
        GetNodeCfg() const
    {
        return itsNodeCfg;
    }

private:
    TL1_SmartParameter< string >        itsVendor;
    TL1_SmartParameter< string >        itsSwType;
    TL1_SmartParameter< string >        itsSwVersion;
    CT_NodeConfiguration                itsNodeCfg;
};

typedef TL1_Rtv_Response< TL1_RtrvNETypeRspBlk > TL1_RtrvNETypeResponse;



#endif //__TL1_NETYPE_RSPBLK_H__
