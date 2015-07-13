/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         June 08, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Service Level Profile Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_SLPFDOMAIN_H__
#define __TL1_SLPFDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include "CommonTypes/CT_TL1_LogicalAddr.h"
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __LT_SLPF_H__
#include "LumosTypes/LT_Slpf.h"
#endif

class TL1_SlpfEdParameters;
class TL1_SlpolicyEdParameters;

class TL1_SlpfDomain
{
public:

    virtual void RtrvSlpf( const CT_TL1_LogicalAddr& theSlpfAddr,
                           const LT_ProfName         theProfileName,
                           TL1_Response&             theResponse ) = 0;

    virtual void EdSlpf( const CT_TL1_LogicalAddr& theSlpfAddr,
                         TL1_SlpfEdParameters& theEdParameters, 			
                         TL1_Response&         theResponse ) = 0;


};

class TL1_SlpolicyDomain
{
public:

    virtual void RtrvSlpolicy( const CT_TL1_LogicalAddr& theSlpolicyAddr,
                               TL1_Response&         theResponse ) = 0;

    virtual void EdSlpolicy( const CT_TL1_LogicalAddr& theSlpolicyAddr,
                             TL1_SlpolicyEdParameters& theEdParameters, 			
                             TL1_Response&         theResponse ) = 0;


};

#endif
