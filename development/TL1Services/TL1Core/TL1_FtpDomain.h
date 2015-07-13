/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 10, 2003- Mathieu Lavoie
DESCRIPTION:    Header file for TL1 FTP domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_FTP_DOMAIN_H__
#define __TL1_FTP_DOMAIN_H__

#include "TL1_Entity.h"
#include <CommonTypes/CT_TL1_SWMgmnt.h>
#include <CommonTypes/CT_Ftp.h>
#include <CommonTypes/CT_PM_Ftp.h>
#include <CommonTypes/CT_Time.h>
#include <CommonTypes/CT_SM_Types.h>

class TL1_Response;


/**
   CLASS TL1_FtpDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of TL1 FTP related commands, that a TL1 Entities
   is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_FtpDomain
{
public:
    
    virtual void Copy (const CT_FileTransferType* theTransferType, const CT_FtpUrl* srcUrl,
          const CT_FtpUrl* destUrl, bool* theOverwriteValue, bool* theProhibitpktsave, uint32* theSeqNum, TL1_Response& theResponse) = 0;

    virtual void Delete (const CT_FtpUrl* fileUrl, TL1_Response& theResponse) = 0;

    virtual void Retrieve (const CT_FtpUrl* fileUrl, bool* theRecursiveValue, bool* storageUsage, TL1_Response& theResponse) = 0;

};

#endif // __TL1_FTP_DOMAIN_H__
