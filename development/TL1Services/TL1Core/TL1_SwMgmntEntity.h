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

#ifndef __TL1_SW_MGMNT_ENTITY_H__
#define __TL1_SW_MGMNT_ENTITY_H__

#include "TL1_Entity.h"
#include <CommonTypes/CT_TL1_SWMgmnt.h>
#include <CommonTypes/CT_Ftp.h>
#include <CommonTypes/CT_Time.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_SCSATypes.h>

class TL1_Response;


/**
   CLASS TL1_SwMgmntEntity

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of SW Management related TL1 commands, that a TL1 Entities
   for a SW is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_SwMgmntEntity: public TL1_Entity
{
public:

    virtual void OperateUpgAbort(TL1_Response& theResponse) = 0;
    
    virtual void OperateUpgCheck(CT_FtpUrl*	theSrcUrl,
                                 TL1_Response& theResponse) = 0;
    
    virtual void OperateUpgCommit(bool* theCommandMode, TL1_Response& theResponse) = 0;
    
    virtual void OperateUpgExecute(bool* theCommandMode, TL1_Response& theResponse) = 0;
    
    virtual void OperateUpgInstall(TL1_Response& theResponse) = 0;

    virtual void InstallCef(string theCefFile, TL1_Response& theResponse) = 0;

    virtual void RtrvCef(CT_CEFType, TL1_Response& theResponse) = 0;

    virtual void RetrieveUpgState(TL1_Response& theResponse) = 0;

    virtual void RetrieveSW(TL1_Response& theResponse) = 0;

    virtual void RetrieveNEType(TL1_Response& theResponse) = 0;

    virtual void OperatePatchApply(TL1_Response& theResponse) = 0;

    virtual void RtrvFpgaVerMap( TL1_Response& theResponse  ) = 0;

    virtual void RtrvSwVerMap( TL1_Response& theResponse  ) = 0;

};

#endif // __TL1_SW_MGMNT_ENTITY_H__
