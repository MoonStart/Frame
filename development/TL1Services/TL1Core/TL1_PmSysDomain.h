/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         April 28, 2003- Marc Vendette
DESCRIPTION:    Header file for TL1 Performance Monitoring Domain declaration
                for system wide entity.
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PMSYSTEMDOMAIN_H__
#define __TL1_PMSYSTEMDOMAIN_H__

class TL1_Response;
class CT_TL1_PmArg;

/**
   CLASS TL1_PmDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of PM related TL1 commands, that a TL1 system
   wide Entities for a PM is expected to implement. This class contains no
   data member nor any default implementation.
 */

// Not completetely defined for AP100, to be updated later.

class TL1_PmSystemDomain
{
public:

    virtual void RtrvPmDay(CT_TL1_PmArg& theArg,
                           TL1_Response& theResponse)const = 0;    // AP200

    virtual void SetPmDay(CT_TL1_PmArg& theArg,
                          TL1_Response& theResponse) = 0;              // AP200
};

#endif
