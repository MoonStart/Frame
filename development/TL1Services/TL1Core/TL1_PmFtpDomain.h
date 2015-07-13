/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 23, 2006 - Praveen S.Bharathi
DESCRIPTION:    Header file for TL1 PM FTP domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PM_FTP_DOMAIN_H__
#define __TL1_PM_FTP_DOMAIN_H__

#include "TL1_Entity.h"
#include <CommonTypes/CT_TL1_SWMgmnt.h>
#include <CommonTypes/CT_Ftp.h>
#include <CommonTypes/CT_PM_Ftp.h>
#include <CommonTypes/CT_Time.h>
#include <CommonTypes/CT_SM_Types.h>

class TL1_Response;


/**
   CLASS TL1_PmFtpDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of TL1 PmFTP related commands, that a TL1 Entities
   is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_PmFtpDomain : public TL1_Entity
{
public:

    virtual void EntFtpServer( CT_PM_Ftp& theArg, TL1_Response& theResponse ) = 0;

    virtual void EdFtpServer( CT_PM_Ftp& theArg, TL1_Response& theResponse ) = 0;

    virtual void DltFtpServer( CT_PM_Ftp& theArg, TL1_Response& theResponse ) = 0;

    virtual void RtrvFtpServer( CT_PM_Ftp& theArg, TL1_Response& theResponse, bool theDltFlag ) = 0;

};

#endif // __TL1_PM_FTP_DOMAIN_H__
