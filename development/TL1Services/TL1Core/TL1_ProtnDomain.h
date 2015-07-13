/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         March 23, 2004 Maggie Zhang
DESCRIPTION:    Header file for TL1 Protection Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_PROTNDOMAIN_H__
#define __TL1_PROTNDOMAIN_H__

#ifndef __CT_TL1_BASE_H__
#include <CommonTypes/CT_TL1_Base.h>
#endif

#ifndef __CT_PROTECTION_H__
#include <CommonTypes/CT_Protection.h>
#endif

#include <LumosTypes/LT_System.h>

class CT_TL1_ProtnAddr;
class TL1_Response;


/**
   CLASS TL1_ProtnDomain

   This is a protocol (pure abstract base class defining an interface)
   that describes the set of Protection and Sync related TL1 commands, that a TL1 Entities
   for a FFP or SYNC is expected to implement. This class contains no
   data member nor any default implementation.
 */


class TL1_ProtnDomain
{
public:

    virtual void RtrvProtn(const CT_TL1_ProtnAddr& theAddr,
						   CT_ProtModifier         theProtMod,
                           CT_FacilitySubType      theFacMod,
                           TL1_Response&           theResponse)const = 0;

    virtual void EntProtn( const CT_TL1_ProtnAddr& theAddr,
                         CT_ProtGpType* theType,
                         bool* theRvrtv,
                         int* theWtr,
                         int* theProtHoldOffTime,
                         CT_ProtGpType* theProtType,
                         bool* theBiDirSwitching,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;

    virtual void EntSync( const CT_TL1_ProtnAddr& theAddr,
						  CT_ProtGpType* theType,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;
    
    virtual void EdProtn(const CT_TL1_ProtnAddr& theAddr,
                         bool* theRvrtv,
                         int* theWtr,
                         int* theProtHoldOffTime,
                         bool* theBiDirSwitching,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;
    
    virtual void DltProtn( const CT_TL1_ProtnAddr& theAddr,
                         TL1_Response& theResponse,
                         LT_Handle theHandle,
                         LT_Ctag   theCtag)= 0;

	virtual void OprProtnSw(const CT_TL1_ProtnAddr& theAddr,
							CT_ProtSwitchRequest* theSwtchCmd,
							TL1_Response& theResponse,
                            LT_Handle theHandle,
                            LT_Ctag   theCtag)=0;

};

#endif
