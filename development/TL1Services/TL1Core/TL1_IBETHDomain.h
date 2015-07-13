/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:        
DESCRIPTION:    
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_IBETHDOMAIN_H__
#define __TL1_IBETHDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include "CommonTypes/CT_TL1_Base.h"
#endif

#ifndef __CT_TELECOM_H__
#include <CommonTypes/CT_Telecom.h>
#endif

#ifndef __CT_AGENTFACILITY_H__
#include <CommonTypes/CT_AgentFacility.h>
#endif

#ifndef __TL1_RESPONSE_H__
#include <Response/TL1_Response.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#include <LumosTypes/LT_System.h>

#include <CommonTypes/CT_IBETH_Definitions.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <CommonTypes/CT_TL1_EqptAddr.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>

class TL1_IBETHEdParameters;
class TL1_IBETHEntParameters;

class TL1_IBETHDomain
{
public:

    virtual void EntIBETH( const CT_TL1_FacAddr&  theIBETHAddr,
                          TL1_IBETHEntParameters& theEntParameters,
                          TL1_Response&          theResponse ) = 0;

    virtual void EdIBETH(  const CT_TL1_FacAddr& theIBETHAddr,
                          TL1_IBETHEdParameters& theEdParameters, 			
                          TL1_Response&         theResponse ) = 0;

    virtual void RtrvIBETH( const CT_TL1_FacAddr& theIBETHAddr,
                           TL1_Response&         theResponse ) const = 0;

    virtual void DltIBETH( const CT_TL1_FacAddr&  theIBETHAddr,                         
                          TL1_Response&          theResponse,
                          LT_Handle              theHandle,
                          LT_Ctag                theCtag ) = 0;
};


#endif
