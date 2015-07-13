/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OCH Response Class
TARGET:
AUTHOR:         February 20, 2004 - Thomas Novak
DESCRIPTION:    Header file for TL1 Retrive OCH Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_T1_RESPONSE_BLOCK_H__
#define __TL1_T1_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_T1RspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_T1RspBlk( );

	TL1_T1RspBlk( const string*              	theEntityName,
                  const CT_TL1_FacAddr*      	theAddr,
                  const CT_CardType*         	theCardType,
                  const CT_SubCardType*      	theSubCardType,
				  const CT_FAC_LineCode*     	theLineCode,
				  const CT_FAC_FrameFormat*     theFrameFormat,
				  const CT_FAC_RxSsm*          	theClockQuality,
				  const CT_ProfileTableId* 		theAlarmProfile,
                  const CT_SM_PST*    			thePST,
                  const CT_SM_PSTQ* 			thePSTQ,
                  const CT_SM_SST*  			theSST );
	
	TL1_T1RspBlk(const TL1_T1RspBlk& );
    
    virtual ~TL1_T1RspBlk();

    TL1_T1RspBlk& operator=( const TL1_T1RspBlk& theBlock );

    bool operator==( const TL1_T1RspBlk& theBlock ) const;

    bool GetEntityName( string& ) const;
    bool GetFacAddr( CT_TL1_FacAddr& ) const;
    bool GetCardType(CT_CardType& ) const;
    bool GetSubCardType( CT_SubCardType& ) const;
    bool GetLineCode( CT_FAC_LineCode& ) const;
	bool GetFrameFormat ( CT_FAC_FrameFormat& ) const;
	bool GetClockQuality( CT_FAC_RxSsm& ) const;
    bool GetAlarmProfile( CT_ProfileTableId& ) const;
    bool GetPST( CT_SM_PST& ) const;
    bool GetPSTQ( CT_SM_PSTQ& ) const;
    bool GetSST( CT_SM_SST& ) const;    

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_LineCode,
        INDEX_FrameFormat,
        INDEX_ClockQuality,
		INDEX_AlarmProfile,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,        
        INDEX_END
    };

    vector<bool>        myBitSet;

    string              myEntityName;
    CT_TL1_FacAddr      myFacAddr;    
    CT_CardType         myCardType;
    CT_SubCardType      mySubCardType;
    CT_FAC_LineCode     myLineCode;
    CT_FAC_FrameFormat  myFrameFormat;
	CT_FAC_RxSsm         myClockQuality;
    CT_ProfileTableId   myAlarmProfile;
    CT_SM_PST           myPST;
    CT_SM_PSTQ          myPSTQ;
    CT_SM_SST           mySST;
 
};

typedef TL1_Rtv_Response< TL1_T1RspBlk > TL1_T1Response;
#endif  // #ifndef __TL1_OCH_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
