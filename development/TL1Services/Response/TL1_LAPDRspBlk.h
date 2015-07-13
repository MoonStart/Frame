/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OCH Response Class
TARGET:
AUTHOR:         July 25, 2006 - Thomas Novak
DESCRIPTION:    Header file for TL1 Retrive LAPD Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_LPAD_RESPONSE_BLOCK_H__
#define __TL1_LPAD_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_LAPDRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_LAPDRspBlk( );
	
	TL1_LAPDRspBlk(const TL1_LAPDRspBlk& );
    
    virtual ~TL1_LAPDRspBlk();

    TL1_LAPDRspBlk& operator=( const TL1_LAPDRspBlk& t1Blk );

    bool operator==( const TL1_LAPDRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetLapdAddr( CT_TL1_FacAddr& theLapdAddr ) const;

    bool GetProfileAddr( CT_LapdProfAddr& theProfileAddr ) const;
    bool GetRouterAddr( CT_OSIRtrAddr& theRouterAddr ) const;
    bool GetFlwProtection( CT_LAPD_FlwProt& theFlwProtection ) const;
    bool GetChkSumEnable( CT_LAPD_CheckSum& theChkSumEnable ) const;
    bool GetHldTmrMult( uint16& theHldTmrMult ) const;
    bool GetConfigTmr( uint16& theConfigTmr ) const;
    bool GetHelloTmr( uint16& theHelloTmr ) const;
    bool GetLMetric( uint16& theLMetric ) const;
    bool GetReDirectHldTmr( uint16& theReDirectHldTmr ) const;
    bool GetRoutingLevel( uint16& theRoutingLevel ) const;
    bool GetEsConfigTmr( uint16& theEsConfigTmr ) const;

    bool GetAlarmProfile( CT_ProfileTableId&) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );
    void SetLapdAddr( const CT_TL1_FacAddr& theLapdAddr );

    void SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile);
    void SetProfileAddr( const CT_LapdProfAddr& theProfileAddr );
    void SetRouterAddr( const CT_OSIRtrAddr& theRouterAddr );
    void SetFlwProtection( const CT_LAPD_FlwProt& theFlwProtection );
    void SetChkSumEnable( const CT_LAPD_CheckSum& theChkSumEnable );
    void SetHldTmrMult( const uint16& theHldTmrMult );
    void SetConfigTmr( const uint16& theConfigTmr );
    void SetHelloTmr( const uint16& theHelloTmr );
    void SetLMetric( const uint16& theLMetric );
    void SetReDirectHldTmr( const uint16& theReDirectHldTmr );
    void SetRoutingLevel( const uint16& theRoutingLevel );
    void SetEsConfigTmr( const uint16& theEsConfigTmr );

    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );
    void SetSST( CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_LapdAddr,
        INDEX_ProfileAddr,
        INDEX_RouterAddr,
        INDEX_FlwProtection,
        INDEX_ChkSumEnable,
        INDEX_HldTmrMult,
        INDEX_ConfigTmr,
        INDEX_HelloTmr,
		INDEX_LMetric,
        INDEX_ReDirectHldTmr,
        INDEX_RoutingLevel,
        INDEX_EsConfigTmr, 
        INDEX_AlarmProfile,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>        myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myLapdAddr;
    CT_ProfileTableId myAlarmProfile;


    CT_LapdProfAddr   myProfileAddr;
    CT_OSIRtrAddr     myRouterAddr;
    CT_LAPD_FlwProt   myFlwProtection;
    CT_LAPD_CheckSum  myChkSumEnable;
    uint16            myHldTmrMult;
    uint16            myConfigTmr;
    uint16            myHelloTmr;
    uint16            myLMetric;
    uint16            myReDirectHldTmr;
    uint16            myRoutingLevel;
    uint16            myEsConfigTmr;

    CT_SM_PST         myPST;
    CT_SM_PSTQ        myPSTQ;
    CT_SM_SST         mySST;
};

typedef TL1_Rtv_Response< TL1_LAPDRspBlk > TL1_LAPDResponse;
#endif  // #ifndef __TL1_LPAD_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
