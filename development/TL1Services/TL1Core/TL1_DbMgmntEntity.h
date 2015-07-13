/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 10, 2003- Mathieu Lavoie
DESCRIPTION:    Header file for TL1 Software Management entity declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DB_MGMNT_ENTITY_H__
#define __TL1_DB_MGMNT_ENTITY_H__

#include "TL1_Entity.h"
#include <CommonTypes/CT_TL1_SWMgmnt.h>
#include <CommonTypes/CT_Ftp.h>
#include <CommonTypes/CT_Time.h>
#include <CommonTypes/CT_SM_Types.h>

class TL1_Response;


/**
   CLASS TL1_DbMgmntEntity

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of DB and SW Management related TL1 commands, that a TL1 Entities
   for a DB is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_DbMgmntEntity: public TL1_Entity
{
public:

    virtual void AlwBkupSchedMem( CT_BackupMemoryId* theBackupMemId,
								  CT_BackupDataType* theBackupDataType,
								  TL1_Response& theResponse) = 0;

    virtual void InhBkupSchedMem(CT_BackupMemoryId* theBackupMemId,
								 CT_BackupDataType* theBackupDataType,
								 TL1_Response& theResponse) = 0;

    virtual void RtrvBkupSchedMem(CT_BackupMemoryId* theBackupMemId,
								  CT_BackupDataType* theBackupDataType,
                                  TL1_Response& theResponse) = 0;

    virtual void SetBkupSchedMem(CT_BackupMemoryId* theBackupMemId,
								 CT_BackupDataType* theBackupDataType,
								 CT_FtpUrl*	theRemoteServerUrl,
								 CT_TimeTm* theBackupPeriod,
							     CT_TimeTm* theFirstBackup,
                                 bool* theProhibitpktsave,
								 TL1_Response& theResponse) = 0;

    virtual void RtvDB(TL1_Response& theResponse) = 0;

	virtual void EditDB(CT_SM_PST* thePrimaryState,	
                        TL1_Response& theResponse) = 0; 

  	virtual void DeleteDB(TL1_Response& theResponse) = 0; 


};

#endif // __TL1_DB_MGMNT_ENTITY_H__
