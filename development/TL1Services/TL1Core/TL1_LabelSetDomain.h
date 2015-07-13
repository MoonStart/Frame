/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         November 16, 2010 - Tom novak
DESCRIPTION:    Header file for TL1 LABELSET Domain declaration
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_LABELSETDOMAIN_H__
#define __TL1_LABELSETDOMAIN_H__

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

#include <LumosTypes/LT_System.h>
#include "CommonTypes/CT_ControlPlane_Definitions.h"

class TL1_LabelSetParameters;
class CT_TL1_LabelSetAddr;

class TL1_LabelSetDomain
{
public:

    virtual void EntLabelSet( CT_TL1_LabelSetAddr&      theLabelSetAddr,
                              TL1_LabelSetParameters&   theEntParameters,
                              TL1_Response&             theResponse ) = 0;

    virtual void EdLabelSet( CT_TL1_LabelSetAddr&       theLabelSetAddr,
                             TL1_LabelSetParameters&    theEntParameters,
                             TL1_Response&              theResponse ) = 0;

    virtual void DltLabelSet( CT_TL1_LabelSetAddr&      theLabelSetAddr,
                              TL1_LabelSetParameters&   theEntParameters,
                              TL1_Response&             theResponse ) = 0;

    virtual void RtrvLabelSet( CT_TL1_LabelSetAddr&     theLabelSetAddr,
                               TL1_LabelSetParameters&  theEntParameters,
                               TL1_Response&            theResponse ) = 0;
}; 

#endif
