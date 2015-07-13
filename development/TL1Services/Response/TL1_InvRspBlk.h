/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive INV Response Class
TARGET:
AUTHOR:         May 14, 2003- Stevens Gerber
DESCRIPTION:    Header file for TL1 Retrive INV Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_INVRSPBLK_H_
#define __TL1_INVRSPBLK_H_

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


class TL1_InvRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_InvRspBlk() {}
    
    TL1_InvRspBlk(const TL1_InvRspBlk& );

    TL1_InvRspBlk(const TL1_SmartParameter<string>&          theEntityName,
                  const TL1_SmartParameter<CT_TL1_SlotAddr>& theAddr,
                  const TL1_SmartParameter<CT_PartNumber>&   thePartNumber,
                  const TL1_SmartParameter<string>&          theType,
                  const TL1_SmartParameter<string>&          theSerialNumber,
                  const TL1_SmartParameter<string>&          theHWRevLevel,
                  const TL1_SmartParameter<string>&          theCLEICode,
                  const TL1_SmartParameter<CT_LaserReach>&   theLaserReach,
                  const TL1_SmartParameter<string>&          theSfpType,
                  const TL1_SmartParameter<string>&          theSfpVendor,
                  const TL1_SmartParameter<string>&          theSfpVendorPN,
                  const TL1_SmartParameter<string>&          theXfpVendor,
                  const TL1_SmartParameter<string>&          theXfpVendorPN,
                  const TL1_SmartParameter<CT_FirmwareStatus>& theFirmwareStatus,
                    const TL1_SmartParameter<CT_SoftwareStatus>& theSoftwareStatus);
    
    virtual ~TL1_InvRspBlk();

    TL1_InvRspBlk& operator=( const TL1_InvRspBlk& theBlock );

    bool operator==( const TL1_InvRspBlk& theBlock ) const;
    
    const TL1_SmartParameter<string>& 
        GetEntityName() const
    {
        return itsEntityName;
    }

    const TL1_SmartParameter<CT_TL1_SlotAddr>& 
        GetAddr() const
    {
        return itsAddr;
    }

    const TL1_SmartParameter<CT_PartNumber>& 
        GetPartNumber() const
    {
        return itsPartNumber;
    }

    const TL1_SmartParameter<string>& 
        GetType() const
    {
        return itsType;
    }

    const TL1_SmartParameter<string>& 
        GetSerialNumber() const
    {
        return itsSerialNumber;
    }

    const TL1_SmartParameter<string>& 
        GetHWRevLevel() const
    {
        return itsHWRevLevel;
    }

    const TL1_SmartParameter<string>&
        GetCLEICode() const
    {
        return itsCLEICode;
    }

    const TL1_SmartParameter<CT_LaserReach>&
        GetLaserReach() const
    {
        return itsLaserReach;
    }

    const TL1_SmartParameter<string>&
        GetSfpType() const
    {
        return itsSfpType;
    }

    const TL1_SmartParameter<string>&
        GetSfpVendor() const
    {
        return itsSfpVendor;
    }

    const TL1_SmartParameter<string>&
        GetSfpVendorPN() const
    {
        return itsSfpVendorPN;
    }

    const TL1_SmartParameter<string>&
        GetXfpVendor() const
    {
        return itsXfpVendor;
    }

    const TL1_SmartParameter<string>&
        GetXfpVendorPN() const
    {
        return itsXfpVendorPN;
    }

    const TL1_SmartParameter<CT_FirmwareStatus>&
        GetFirmwareStatus() const
    {
        return itsFirmwareStatus;
    }

    const TL1_SmartParameter<CT_SoftwareStatus>&
        GetSoftwareStatus() const
    {
        return itsSoftwareStatus;
    }

private:

    TL1_SmartParameter<string>          itsEntityName;
    TL1_SmartParameter<CT_TL1_SlotAddr> itsAddr;
    TL1_SmartParameter<CT_PartNumber>   itsPartNumber;
    TL1_SmartParameter<string>          itsType;
    TL1_SmartParameter<string>          itsSerialNumber;
    TL1_SmartParameter<string>          itsHWRevLevel;
    TL1_SmartParameter<string>          itsCLEICode;
    TL1_SmartParameter<CT_LaserReach>   itsLaserReach;
    TL1_SmartParameter<string>          itsSfpType;
    TL1_SmartParameter<string>          itsSfpVendor;
    TL1_SmartParameter<string>          itsSfpVendorPN;
    TL1_SmartParameter<string>          itsXfpVendor;
    TL1_SmartParameter<string>          itsXfpVendorPN;
    TL1_SmartParameter<CT_FirmwareStatus> itsFirmwareStatus;
    TL1_SmartParameter<CT_SoftwareStatus> itsSoftwareStatus;

};

typedef TL1_Rtv_Response< TL1_InvRspBlk > TL1_InvResponse;

#endif


