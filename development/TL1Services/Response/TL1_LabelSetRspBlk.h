/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive LABELSET Response Class
TARGET:
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Header file for TL1 Retrive LABELSET Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_LABELSET_RESPONSE_BLOCK_H__
#define __TL1_LABELSET_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>

//---------------------------------------------------------------------------------------
class TL1_LabelSetRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_LabelSetRspBlk( );

    virtual ~TL1_LabelSetRspBlk( );

    TL1_LabelSetRspBlk& operator=( const TL1_LabelSetRspBlk& t1Blk );

    bool operator==( const TL1_LabelSetRspBlk& t1Blk ) const;

    bool GetIngress( CT_ControlPlane_LabelSet& theLabelSet ) const;
    void SetIngress( const CT_ControlPlane_LabelSet& theLabelSet );

    bool GetEgress( CT_ControlPlane_LabelSet& theLabelSet ) const;
    void SetEgress( const CT_ControlPlane_LabelSet& theLabelSet );

    bool GetIngressSet( bool& theIngressSet ) const;
    void SetIngressSet( const bool& theIngressSet );

    bool GetEgressSet( bool& theEgressSet ) const;
    void SetEgressSet( const bool& theEgressSet );

    bool GetLabelSetAddr( CT_TL1_LabelSetAddr & theLabelSetAddr ) const;
    void SetLabelSetAddr( const CT_TL1_LabelSetAddr & theLabelSetAddr );

private:

    enum 
    {   
        INDEX_LabelSetAddr  = 0,
        INDEX_Ingress,
        INDEX_Egress,
        INDEX_IngSet,
        INDEX_EgSet,
        INDEX_END
    };

    vector<bool>                    myBitSet;
    CT_TL1_LabelSetAddr             myLabelSetAddr;
    CT_ControlPlane_LabelSet        myIngress;
    CT_ControlPlane_LabelSet        myEgress;
    bool                            IsIngressSet;
    bool                            IsEgressSet;
};
typedef TL1_Rtv_Response< TL1_LabelSetRspBlk > TL1_LabelSetResponse;

#endif  // #ifndef __TL1_LABELSET_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
