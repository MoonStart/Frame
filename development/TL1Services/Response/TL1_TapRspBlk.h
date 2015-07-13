/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TAP Response Class
TARGET:
AUTHOR:         October, 2006 - Brian Clever
DESCRIPTION:    Header file for TL1 Retrive Tap Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_TAP_RESPONSE_BLOCK_H__
#define __TL1_TAP_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>
#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_XcTypes.h>

class TL1_TapRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_TapRspBlk( ) {}
	
	TL1_TapRspBlk(const TL1_TapRspBlk& );
    
	TL1_TapRspBlk(const TL1_SmartParameter<CT_TL1_FacAddr>& theEQAddr,
                  const TL1_SmartParameter<CT_XcFacType>& theEQType,
                  const TL1_SmartParameter<CT_TL1_FacAddr>& theFAAddr,
                  const TL1_SmartParameter<CT_XcFacType>& theFAType,
                  const TL1_SmartParameter<CT_SM_PST>&  thePST,
                  const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ,
                  const TL1_SmartParameter<CT_SM_SST>&  theSST );


    virtual ~TL1_TapRspBlk(){}

    TL1_TapRspBlk& operator=( const TL1_TapRspBlk& t1Blk );

    bool operator==( const TL1_TapRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetTapAddr( CT_TL1_FacAddr& theEQTapAddr,  CT_TL1_FacAddr& theFATapAddr ) const;

    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );

    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );
    void SetSST( CT_SM_SST& theSST );

private:

    const TL1_SmartParameter<CT_TL1_FacAddr> itsEQTapAddr;
    const TL1_SmartParameter<CT_XcFacType>   itsEQType;
    const TL1_SmartParameter<CT_TL1_FacAddr> itsFATapAddr;
    const TL1_SmartParameter<CT_XcFacType>   itsFAType;
    const TL1_SmartParameter<CT_SM_PST>      itsPST;
    const TL1_SmartParameter<CT_SM_PSTQ>     itsPSTQ;
    const TL1_SmartParameter<CT_SM_SST>      itsSST;

};

typedef TL1_Rtv_Response< TL1_TapRspBlk > TL1_TapResponse;
#endif  // #ifndef __TL1_TAP_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
