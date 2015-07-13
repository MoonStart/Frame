/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         June 10, 2003- Mathieu Lavoie 
DESCRIPTION:    Header file for TL1 Database management response block
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DB_MGMNT_RSPBLK_H__
#define __TL1_DB_MGMNT_RSPBLK_H__

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


#include <vector>

using namespace std;


class TL1_DbMgmntRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_DbMgmntRspBlk(){}

    TL1_DbMgmntRspBlk( const TL1_DbMgmntRspBlk& theBlock );

	TL1_DbMgmntRspBlk( const TL1_SmartParameter< CT_BackupMemoryId >& theBackupMemId,
                  const TL1_SmartParameter< CT_BackupDataType >& theBackupDataType,
				  const TL1_SmartParameter< CT_FtpUrl >&	theRemoteServerUrl,
				  const TL1_SmartParameter< CT_TimeTm >& theBackupPeriod,
				  const TL1_SmartParameter< CT_TimeTm >& theFirstBackupTime,
                  const TL1_SmartParameter< CT_TimeTm >& theLastBackupTime,
                  const TL1_SmartParameter< CT_TimeTm >& theNextBackupTime,
                  const TL1_SmartParameter< CT_TimeTm >& theLastUpdateTime,
                  const TL1_SmartParameter< CT_TimeTm >& theLocalBackupTime,
                  const TL1_SmartParameter< string >& theDbSwVersion,
				  const TL1_SmartParameter< CT_BackupPermission >& theBackupPermission,
                  const TL1_SmartParameter< CT_Prohibitpktsave >& theProhibitpktsave,
				  const	TL1_SmartParameter< CT_SM_PST >& thePST,
				  const	TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
				  const	TL1_SmartParameter< CT_SM_SST >& theSST
				);

	virtual ~TL1_DbMgmntRspBlk();

    TL1_DbMgmntRspBlk& operator=( const TL1_DbMgmntRspBlk& theBlock );

    const TL1_SmartParameter< CT_BackupMemoryId >&
        GetBackupMemoryId() const
    {
        return itsBackupMemoryId;
    }

    const TL1_SmartParameter< CT_BackupDataType >&
        GetBackupDataType() const
    {
        return itsBackupDataType;
    }

    const TL1_SmartParameter< CT_FtpUrl >&
        GetRemoteServerUrl() const
    {
        return itsRemoteServerUrl;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetBackupPeriod() const
    {
        return itsBackupPeriod;
    }

    const TL1_SmartParameter< CT_BackupPermission >&
        GetBackupPermission() const
    {
        return itsBackupPermission;
    }

    const TL1_SmartParameter< CT_Prohibitpktsave >&
        GetProhibitpktsave() const
    {
        return itsProhibitpktsave;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetFirstBackupTime() const
    {
        return itsFirstBackupTime;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetLastBackupTime() const
    {
        return itsLastBackupTime;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetNextBackupTime() const
    {
        return itsNextBackupTime;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetLastUpdateTime() const
    {
        return itsLastUpdateTime;
    }

    const TL1_SmartParameter< CT_TimeTm >&
        GetLocalBackupTime() const
    {
        return itsLocalBackupTime;
    }

    const TL1_SmartParameter< string >&
        GetDBSwVersion() const
    {
        return itsDbSwVersion;
    }

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
	TL1_SmartParameter< CT_BackupMemoryId >		itsBackupMemoryId;
	TL1_SmartParameter< CT_BackupDataType >     itsBackupDataType;
	TL1_SmartParameter< CT_FtpUrl >				itsRemoteServerUrl;
	TL1_SmartParameter< CT_TimeTm >				itsBackupPeriod;
	TL1_SmartParameter< CT_TimeTm >				itsFirstBackupTime;
    TL1_SmartParameter< CT_TimeTm >             itsLastBackupTime;
    TL1_SmartParameter< CT_TimeTm >             itsNextBackupTime;
    TL1_SmartParameter< CT_TimeTm >             itsLastUpdateTime;
    TL1_SmartParameter< CT_TimeTm >             itsLocalBackupTime;
    TL1_SmartParameter< string >                itsDbSwVersion;
	TL1_SmartParameter< CT_BackupPermission >	itsBackupPermission;
	TL1_SmartParameter< CT_Prohibitpktsave >	itsProhibitpktsave;
	TL1_SmartParameter< CT_SM_PST >				itsPST;
	TL1_SmartParameter< CT_SM_PSTQ >			itsPSTQ;
	TL1_SmartParameter< CT_SM_SST >				itsSST;

};


typedef TL1_Rtv_Response< TL1_DbMgmntRspBlk > TL1_DbMgmntResponse;



class TL1_DbBackupResultRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_DbBackupResultRspBlk(){}

    TL1_DbBackupResultRspBlk( const TL1_DbBackupResultRspBlk& theBlock );

	TL1_DbBackupResultRspBlk( const TL1_SmartParameter< CT_BackupMemoryId >& theBackupMemId,
                              const TL1_SmartParameter< CT_BackupDataBundle >& theBackupDataBundle,
			            	  const TL1_SmartParameter< CT_BackupResult >&	theBackupResult,
                              const TL1_SmartParameter< CT_BackupPassFail >&	theBackupPassFail
            				);

	virtual ~TL1_DbBackupResultRspBlk();

    TL1_DbBackupResultRspBlk& operator=( const TL1_DbBackupResultRspBlk& theBlock );

    const TL1_SmartParameter< CT_BackupMemoryId >&
        GetBackupMemoryId() const
    {
        return itsBackupMemoryId;
    }

    const TL1_SmartParameter< CT_BackupDataType >&
        GetDataType() const
    {
        return itsBackupDataType;
    }

    const TL1_SmartParameter< CT_BackupResult >&
        GetBackupResult() const
    {
        return itsBackupResult;
    }

    const TL1_SmartParameter< CT_BackupPassFail >&
        GetPassFail() const
    {
        return itsBackupPassFail;
    }

private:
	TL1_SmartParameter< CT_BackupMemoryId >		itsBackupMemoryId;
	TL1_SmartParameter< CT_BackupDataType >     itsBackupDataType;
	TL1_SmartParameter< CT_BackupResult >       itsBackupResult;
    TL1_SmartParameter< CT_BackupPassFail >     itsBackupPassFail;
};

typedef TL1_Rtv_Response< TL1_DbBackupResultRspBlk > TL1_DbBackupResultResponse;


#endif //__TL1_DB_MGMNT_RSPBLK_H__
