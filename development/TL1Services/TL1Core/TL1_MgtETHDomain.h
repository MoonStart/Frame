/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         2013.9.16 - Gang Zhu
DESCRIPTION:    Header file for TL1 MGTETH Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_MGTETHDOMAIN_H__
#define __TL1_MGTETHDOMAIN_H__

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


#include "CommonTypes/CT_AM_Definitions.h"
#include <LumosTypes/LT_System.h>

class TL1_MgtETHParameters;

class TL1_MgtETHDomain
{
	public:
	
		virtual void EntMgtETH( const CT_TL1_FacAddr&  theMgtETHAddr,
							  TL1_MgtETHParameters& theEntParameters,
							  TL1_Response& 		 theResponse ) = 0;
	
		virtual void EdMgtETH(  const CT_TL1_FacAddr& theMgtETHAddr,
							  TL1_MgtETHParameters& theEdParameters,			
							  TL1_Response& 		theResponse ) = 0;
	
		virtual void RtrvMgtETH( const CT_TL1_FacAddr& theMgtETHAddr,
							   CT_ProfileTableId*	 theAlarmProfile,						 
							   CT_SM_PST*			 thePrimaryState,									 
							   CT_SM_SST*			 theSecondaryState, 								   
							   TL1_Response&		 theResponse ) const = 0;
	
		virtual void DltMgtETH( const CT_TL1_FacAddr&  theMgtETHAddr,
							  TL1_Response& 		 theResponse,
							  LT_Handle 			 theHandle,
							  LT_Ctag				 theCtag ) = 0;

};

#endif

