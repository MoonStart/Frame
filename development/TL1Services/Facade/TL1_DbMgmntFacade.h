/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Services
TARGET:          
AUTHOR:         June 10, 2003- Mathieu
DESCRIPTION:    Header file for TL1 Database Facade declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_DBFACADE_H__
#define __TL1_DBFACADE_H__

#ifndef __TL1_DBENTITY_H__
#include <TL1Core/TL1_DbMgmntEntity.h>
#endif

#ifndef _FACADE_OPERATIONIF_H_
#include <Facade/FC_FacadeOperationIf.h>
#endif


#define FACI_AlwBckup( theBackupMemId, theBackupDataType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, AlwBkupSchedMem( theBackupMemId, theBackupDataType, theResponse ))

#define FACI_InhBckup( theBackupMemId, theBackupDataType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, InhBkupSchedMem( theBackupMemId, theBackupDataType, theResponse ))

#define FACI_RtrvBckupSched( theBackupMemId, theBackupDataType, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtrvBkupSchedMem( theBackupMemId, theBackupDataType, theResponse ))

#define FACI_SetBckupSched( theBackupMemId, theBackupDataType, theRemoteServerUrl, theBackupPeriod, theFirstBackup, theProhibitpktsave, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, SetBkupSchedMem( theBackupMemId, theBackupDataType, theRemoteServerUrl, theBackupPeriod, theFirstBackup, theProhibitpktsave, theResponse ))

#define FACI_RtrvDB(theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, RtvDB( theResponse ))

#define FACI_EditDB(thePrimaryState, theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, EditDB( thePrimaryState, theResponse ))

#define FACI_DeleteDB(theResponse ) \
FAC_OP_CONST( NO_SUB_RGN_ID, DeleteDB( theResponse ))


#endif //__TL1_DBFACADE_H__
