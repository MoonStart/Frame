/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 05, 2007 - Mike Rodgers
DESCRIPTION:    Header file for TL1 Protocol Profile Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CPPFDOMAIN_H__
#define __TL1_CPPFDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include "CommonTypes/CT_TL1_LogicalAddr.h"
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#include <CommonTypes/CT_ControlPlane_Definitions.h>

class TL1_CppfDomain
{
public:

    virtual void RtrvCppf( const CT_TL1_LogicalAddr& theCppfAddr,
                           TL1_Response&         theResponse ) = 0;

    virtual void EdCppf( const CT_TL1_LogicalAddr& theCppfAddr, 
                         string* profileName,
                         CT_GMPLS_MODE* gmplsMode,
                         uint32* refreshSeconds,
                         CT_Advertisement* theAdvertisement,
                         TL1_Response& theResponse ) = 0;
};


#endif
