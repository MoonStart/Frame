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

#ifndef __TL1_SW_MGMNT_RSPBLK_H__
#define __TL1_SW_MGMNT_RSPBLK_H__

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

#ifndef CT_TIME_H
#include <CommonTypes/CT_Time.h>
#endif

#ifndef _CT_FTP_H__
#include <CommonTypes/CT_Ftp.h>
#endif

#ifndef _CT_SM_TYPES_H_
#include <CommonTypes/CT_SM_Types.h>
#endif

#ifndef __CT_SMAA_H__
#include <CommonTypes/CT_SMAA.h>
#endif

#include <CommonTypes/CT_SCSATypes.h>

#include <vector>

using namespace std;


class TL1_RtvUpgStateRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RtvUpgStateRspBlk(){}

    TL1_RtvUpgStateRspBlk( const TL1_RtvUpgStateRspBlk& theBlock );

	TL1_RtvUpgStateRspBlk( const TL1_SmartParameter< CT_SMAA_SubState >& theState);

	virtual ~TL1_RtvUpgStateRspBlk();

    TL1_RtvUpgStateRspBlk& operator=( const TL1_RtvUpgStateRspBlk& theBlock );

    const TL1_SmartParameter< CT_SMAA_SubState >&
        GetState() const
    {
        return itsState;
    }

private:
	TL1_SmartParameter< CT_SMAA_SubState >	itsState;
};

typedef TL1_Rtv_Response< TL1_RtvUpgStateRspBlk > TL1_RtvUpgStateResponse;



class TL1_RtvFileRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RtvFileRspBlk(){}

    TL1_RtvFileRspBlk( const TL1_RtvFileRspBlk& theBlock );

	TL1_RtvFileRspBlk(const TL1_SmartParameter<uint32>& theStorageSize,
                      const TL1_SmartParameter<uint32>& theStorageUsed,
                      const TL1_SmartParameter<uint32>& theStorageFree,
                      const TL1_SmartParameter<string>& theFileName,
                      const TL1_SmartParameter<uint32>& theFileSize,
                      const TL1_SmartParameter<CT_TimeTm>& theFileDate);


	virtual ~TL1_RtvFileRspBlk();

    TL1_RtvFileRspBlk& operator=( const TL1_RtvFileRspBlk& theBlock );

    const TL1_SmartParameter< uint32 >&
        GetStorageSize() const
    {
        return itsStorageSize;
    }

    const TL1_SmartParameter< uint32 >&
        GetStorageUsed() const
    {
        return itsStorageUsed;
    }

    const TL1_SmartParameter< uint32 >&
        GetStorageFree() const
    {
        return itsStorageFree;
    }

    const TL1_SmartParameter< string >&
        GetFileName() const
    {
        return itsFileName;
    }

    const TL1_SmartParameter< uint32 >&
        GetFileSize() const
    {
        return itsFileSize;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetFileDate() const
    {
        return itsFileDate;
    }

private:
    TL1_SmartParameter<uint32> itsStorageSize;
    TL1_SmartParameter<uint32> itsStorageUsed;
    TL1_SmartParameter<uint32> itsStorageFree;
    TL1_SmartParameter<string> itsFileName;
    TL1_SmartParameter<uint32> itsFileSize;
    TL1_SmartParameter<CT_TimeTm> itsFileDate;
 
};

typedef TL1_Rtv_Response< TL1_RtvFileRspBlk > TL1_RtvFileResponse;



class TL1_RtvSwStateRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RtvSwStateRspBlk(){}

    TL1_RtvSwStateRspBlk( const TL1_RtvSwStateRspBlk& theBlock );

	TL1_RtvSwStateRspBlk( const	TL1_SmartParameter< CT_SM_PST >& thePST,
				          const	TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
				          const	TL1_SmartParameter< CT_SM_SST >& theSST);


	virtual ~TL1_RtvSwStateRspBlk();

    TL1_RtvSwStateRspBlk& operator=( const TL1_RtvSwStateRspBlk& theBlock );

    const TL1_SmartParameter< CT_SM_PST >&
        GetPST() const
    {
        return itsPST;
    }

    const TL1_SmartParameter< CT_SM_PSTQ >&
        GetPSTQ() const
    {
        return itsPSTQ;
    }

    const TL1_SmartParameter< CT_SM_SST >&
        GetSST() const
    {
        return itsSST;
    }

private:
    TL1_SmartParameter< CT_SM_PST > itsPST;
	TL1_SmartParameter< CT_SM_PSTQ > itsPSTQ;
	TL1_SmartParameter< CT_SM_SST > itsSST;
 
};

typedef TL1_Rtv_Response< TL1_RtvSwStateRspBlk > TL1_RtvSwStateResponse;


class TL1_ReportFxFrRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_ReportFxFrRspBlk(){}

    TL1_ReportFxFrRspBlk( const TL1_ReportFxFrRspBlk& theBlock );

	TL1_ReportFxFrRspBlk( const TL1_SmartParameter< CT_FileTransferType >& theFileTransferType,
                            const TL1_SmartParameter< string >& theFileName,
				            const TL1_SmartParameter< CT_FxFrStatus >& theStatus,
				            const TL1_SmartParameter< CT_FxFrResult >& theResult,
                            const TL1_SmartParameter< int >& thePercentage,
                            const TL1_SmartParameter< int >& theBytesTransfered);


	virtual ~TL1_ReportFxFrRspBlk();

    TL1_ReportFxFrRspBlk& operator=( const TL1_ReportFxFrRspBlk& theBlock );

    const TL1_SmartParameter< CT_FileTransferType >&
        GetFileTransferType() const
    {
        return itsFileTransferType;
    }

    const TL1_SmartParameter< string >&
        GetFileName() const
    {
        return itsFileName;
    }

    const TL1_SmartParameter< CT_FxFrStatus >&
        GetStatus() const
    {
        return itsStatus;
    }

    const TL1_SmartParameter< CT_FxFrResult >&
        GetResult() const
    {
        return itsResult;
    }

    const TL1_SmartParameter< int >&
        GetPercentage() const
    {
        return itsPercentage;
    }

    const TL1_SmartParameter< int >&
        GetByteTransfered() const
    {
        return itsBytesTransfered;
    }
private:
    TL1_SmartParameter< CT_FileTransferType > itsFileTransferType;
    TL1_SmartParameter< string > itsFileName;
	TL1_SmartParameter< CT_FxFrStatus > itsStatus;
	TL1_SmartParameter< CT_FxFrResult > itsResult;
    TL1_SmartParameter< int > itsPercentage;
    TL1_SmartParameter< int > itsBytesTransfered;
 
};

typedef TL1_Rtv_Response< TL1_ReportFxFrRspBlk > TL1_ReportFxFrResponse;

class TL1_RtvCefRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_RtvCefRspBlk(){}
    TL1_RtvCefRspBlk( const TL1_RtvCefRspBlk& theBlock );
    TL1_RtvCefRspBlk( const string& theVersion, CT_CEFType itsCefType );
    virtual ~TL1_RtvCefRspBlk();
    TL1_RtvCefRspBlk& operator=( const TL1_RtvCefRspBlk& theBlock);

    const string& GetVersion() const
    {
        return itsVersion;
    }

    CT_CEFType GetCefType() const { return itsCefType; }

private:
    string      itsVersion;
    CT_CEFType  itsCefType;
};

typedef TL1_Rtv_Response< TL1_RtvCefRspBlk > TL1_RtvCefResponse;

#endif //__TL1_SW_MGMNT_RSPBLK_H__
