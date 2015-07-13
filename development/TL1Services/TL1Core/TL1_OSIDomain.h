/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         August 11, 2005 - Thomas J. Novak
DESCRIPTION:    Header file for TL1 OSI Profile Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_OSIDOMAIN_H__
#define __TL1_OSIDOMAIN_H__

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

#include <CommonTypes/CT_DCC_Definitions.h>

class TL1_OSIRTREdParameters;
class TL1_OSIRTREntParameters;

class TL1_OSIRTRDomain 
{
public:

    virtual void EntOsiRtr( const CT_TL1_FacAddr&      theOsiRtrAddr,
                            TL1_OSIRTREntParameters&   theEntParameters,
                            TL1_Response&              theResponse ) = 0;

    virtual void EdOsiRtr( const CT_TL1_FacAddr&     theOsiRtrAddr,
                           TL1_OSIRTREdParameters&   theEdParameters, 			
                           TL1_Response&             theResponse ) = 0;

    virtual void RtrvOsiRtr( const CT_TL1_FacAddr& theOsiRtrAddr,
                             CT_ProfileTableId*    theAlarmProfile,                        
                             CT_SM_PST*            thePrimaryState,                                    
                             CT_SM_SST*            theSecondaryState,                                    
                             TL1_Response&         theResponse ) const = 0;

    virtual void DltOsiRtr( const CT_TL1_FacAddr&  theOsiRtrAddr,
                            TL1_Response&          theResponse,
                            LT_Handle              theHandle,
                            LT_Ctag                theCtag,
                            bool*                  theForced ) = 0;

    virtual void RtrvOsiRtrMapNeighbor( const CT_TL1_FacAddr& theOsiRtrAddr,
                                        TL1_Response&         theResponse ) const = 0;


    virtual void RtrvOsiRtrMapNetwork( const CT_TL1_FacAddr& theOsiRtrAddr,
                                       TL1_Response&         theResponse ) const = 0;

};      

#endif
