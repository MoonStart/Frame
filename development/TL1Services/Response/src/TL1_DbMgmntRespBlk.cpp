/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         June 11 2003- Mathieu Lavoie
DESCRIPTION:    Implementation file for TL1 DB Mgmnt response block
-----------------------------------------------------------------------------*/ 

#include <Response/TL1_DbMgmntRespBlk.h>

TL1_DbMgmntRspBlk::TL1_DbMgmntRspBlk( const TL1_SmartParameter< CT_BackupMemoryId >& theBackupMemId,
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
                				  const	TL1_SmartParameter< CT_SM_SST >& theSST ) :
	itsBackupMemoryId(theBackupMemId),
	itsBackupDataType(theBackupDataType),
	itsRemoteServerUrl(theRemoteServerUrl),
	itsBackupPeriod(theBackupPeriod),
	itsFirstBackupTime(theFirstBackupTime),
    itsLastBackupTime(theLastBackupTime),
    itsNextBackupTime(theNextBackupTime),
    itsLastUpdateTime(theLastUpdateTime),
    itsLocalBackupTime(theLocalBackupTime),
    itsDbSwVersion(theDbSwVersion),
	itsBackupPermission(theBackupPermission),
	itsProhibitpktsave(theProhibitpktsave),
    itsPST(thePST),
    itsPSTQ(thePSTQ),
    itsSST(theSST)
{
}

TL1_DbMgmntRspBlk::~TL1_DbMgmntRspBlk()
{
}

TL1_DbMgmntRspBlk::TL1_DbMgmntRspBlk( const TL1_DbMgmntRspBlk& theBlock )
{
	*this = theBlock;
}

TL1_DbMgmntRspBlk& TL1_DbMgmntRspBlk::operator=( const TL1_DbMgmntRspBlk& theBlock )
{
	itsBackupMemoryId = theBlock.itsBackupMemoryId;
	itsBackupDataType = theBlock.itsBackupDataType;
	itsRemoteServerUrl = theBlock.itsRemoteServerUrl;
	itsBackupPeriod = theBlock.itsBackupPeriod;
	itsFirstBackupTime = theBlock.itsFirstBackupTime;
    itsLastBackupTime = theBlock.itsLastBackupTime;
    itsNextBackupTime = theBlock.itsNextBackupTime;
    itsLastUpdateTime = theBlock.itsLastUpdateTime;
    itsLocalBackupTime = theBlock.itsLocalBackupTime;
    itsDbSwVersion = theBlock.itsDbSwVersion;
    itsBackupPermission = theBlock.itsBackupPermission;
    itsProhibitpktsave = theBlock.itsProhibitpktsave;
    itsPST = theBlock.itsPST;
    itsPSTQ = theBlock.itsPSTQ;
    itsSST = theBlock.itsSST;

    return *this;
}



TL1_DbBackupResultRspBlk::TL1_DbBackupResultRspBlk( const TL1_SmartParameter< CT_BackupMemoryId >& theBackupMemId,
                                                    const TL1_SmartParameter< CT_BackupDataType >& theBackupDataType,
                                                    const TL1_SmartParameter< CT_BackupResult >& theBackupResult,
                                                    const TL1_SmartParameter< CT_BackupPassFail >&	theBackupPassFail
            				):
	itsBackupMemoryId(theBackupMemId),
	itsBackupDataType(theBackupDataType),
	itsBackupResult(theBackupResult),
    itsBackupPassFail(theBackupPassFail)
{
}

TL1_DbBackupResultRspBlk::~TL1_DbBackupResultRspBlk()
{
}

TL1_DbBackupResultRspBlk::TL1_DbBackupResultRspBlk( const TL1_DbBackupResultRspBlk& theBlock )
{
	*this = theBlock;
}

TL1_DbBackupResultRspBlk& TL1_DbBackupResultRspBlk::operator=( const TL1_DbBackupResultRspBlk& theBlock )
{
    itsBackupMemoryId = theBlock.itsBackupMemoryId;
    itsBackupDataType = theBlock.itsBackupDataType;
    itsBackupResult = theBlock.itsBackupResult;
    itsBackupPassFail = theBlock.itsBackupPassFail;
    return *this;
}
