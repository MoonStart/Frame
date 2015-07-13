/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OCH Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive OCH Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_OCH_RESPONSE_BLOCK_H_
#define __TL1_OCH_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_OCHRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OCHRspBlk();
    
    TL1_OCHRspBlk(const string*                         theEntityName,
                  const CT_TL1_FacAddr*                 theAddr,
                  const CT_CardType*                    theCardType,
                  const CT_SubCardType*                 theSubCardType,
                  const bool*                           isAutoAdjustAttenuationEnabled,
                  const bool*                           isOtuMapEnabled,
                  const CT_Fac_TraceString*             theExpectedTrace,
                  const CT_Fac_TraceString*             theSentTrace,
                  const bool*                           isMonitorOtiEnabled,
                  const bool*                           isMonitorTraceEnabled,
                  const bool*                           isInsertAisEnabled,
                  const CT_Fac_TraceString*             theProtFunc,
                  const uint8*                          theNpOwner,
                  const CT_TEL_FecType*                 theFecType,
                  const CT_TEL_SuperFec*                theSuperFec,
                  const CT_FAC_ExternalConnectivity*    theConnectivity,
                  const CT_Fac_ConnectedToString*       theConnectedTo,
                  const CT_TEL_BERLevels*               theSDThreshold,
                  const CT_FAC_RxSsm*                   theSsmReceived,
                  const CT_TEL_MsTref*                  theTimingRef,
                  const int*                            theProtHoldOffTime,
                  const uint32*                         theExtChannel,
                  //const CT_RelativeWavelength*          theExtChannel,
                  const CT_TEL_OEO_REGEN_MODE*          theOeoRegen,
                  const CT_ProfileTableId*              theAlarmProfile,
                  const CT_TEL_ClkType*                 theClkType,
                  const CT_TEL_OTIDStatus*              theOTIDStatus,
                  const CT_TEL_TimCriteriaMode*         theTimDef,
                  const CT_Fac_TraceString*             theExpDapi,
                  const CT_Fac_TraceString*             theExpSapi,
                  const CT_Fac_TraceString*             theTxDapi,
                  const CT_Fac_TraceString*             theTxSapi,
                  const uint16*                         theBurstyBerSdInterval,
                  const uint32*                         theBurstyBerSdThreshold,
                  const CT_Fac_TraceString*             theExpOperator,
                  const CT_Fac_TraceString*             theTxOperator,
                  const CT_SM_PST*                      thePST,
                  const CT_SM_PSTQ*                     thePSTQ,
                  const CT_SM_SST*                      theSST );

    TL1_OCHRspBlk(const TL1_OCHRspBlk& );
    
    virtual ~TL1_OCHRspBlk();

    TL1_OCHRspBlk& operator=( const TL1_OCHRspBlk& theBlock );

    bool operator==( const TL1_OCHRspBlk& theBlock ) const;

    bool GetEntityName(string& ) const;
    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    bool GetCardType(CT_CardType& ) const;
    bool GetSubCardType( CT_SubCardType&) const ;
    bool GetAutoAdjustAttenuationEnabled(bool& ) const;
    bool GetOtuMapEnabled( bool& ) const;
    bool GetExpectedTrace( CT_Fac_TraceString&) const;
    bool GetSentTrace( CT_Fac_TraceString& ) const;
    bool GetProtFunc( CT_Fac_TraceString& ) const;
    bool GetMonitorOtiEnabled( bool& ) const;
    bool GetMonitorTraceEnabled( bool& ) const;
    bool GetInsertAisEnabled( bool& ) const;
    bool GetNpOwner( uint8 &) const;
    bool GetFecType( CT_TEL_FecType& ) const;
    bool GetSuperFec( CT_TEL_SuperFec& ) const;
    bool GetConnectivity( CT_FAC_ExternalConnectivity& ) const;
    bool GetConnectedTo( CT_Fac_ConnectedToString& ) const;
    bool GetSDThreshold( CT_TEL_BERLevels& ) const;
    bool GetSsmReceived( CT_FAC_RxSsm& )const;
    bool GetTimingRef( CT_TEL_MsTref& )const; 
    bool GetProtHoldOffTime( int& ) const;
    bool GetExtChannel(uint32&) const;
    bool GetOeoRegen( CT_TEL_OEO_REGEN_MODE& ) const;
    bool GetClkType( CT_TEL_ClkType& ) const;
    bool GetOTIDStatus( CT_TEL_OTIDStatus& ) const;
    bool GetAlarmProfile( CT_ProfileTableId&) const;
    bool GetPST( CT_SM_PST&) const;
    bool GetPSTQ( CT_SM_PSTQ&) const;
    bool GetSST( CT_SM_SST&) const;    
    bool GetTimDef(CT_TEL_TimCriteriaMode&) const;
    bool GetExpDapi(CT_Fac_TraceString&) const;
    bool GetExpSapi(CT_Fac_TraceString&) const;
    bool GetTxDapi(CT_Fac_TraceString&) const;  
    bool GetTxSapi(CT_Fac_TraceString&) const;
    bool GetBurstyBerSdInterval(uint16&) const;
    bool GetBurstyBerSdThreshold(uint32&) const;
    bool GetExpOperator(CT_Fac_TraceString&) const;
    bool GetTxOperator(CT_Fac_TraceString&) const;

    CT_SM_PST GetPST() const;
    CT_SM_PSTQ GetPSTQ() const;
    CT_SM_SST GetSST() const;    

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_AutoAdjustAttenuationEnabled,
        INDEX_OtuMapEnabled,
        INDEX_ExpectedTrace,
        INDEX_SentTrace,
        INDEX_MonitorOtiEnabled,
        INDEX_MonitorTraceEnabled,
        INDEX_InsertAisEnabled,
        INDEX_ProtFunc,
        INDEX_NpOwner,
        INDEX_FecType,
        INDEX_SuperFec,
        INDEX_Connectivity,
        INDEX_ConnectedTo,
        INDEX_SDThreshold,
        INDEX_SsmReceived,
        INDEX_TimingReference,
        INDEX_ProtHoldOffTime,
        INDEX_ExtChannel,
        INDEX_OeoRegen,
        INDEX_AlarmProfile,
        INDEX_ClkType,
        INDEX_OTIDStatus,
        INDEX_TimDef,
        INDEX_ExpDapi,
        INDEX_ExpSapi,
        INDEX_TxDapi,
        INDEX_TxSapi,
        INDEX_BurstyBerSdInterval,
        INDEX_BurstyBerSdThreshold,
        INDEX_ExpOperator,
        INDEX_TxOperator,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,        
        INDEX_END
    };

    vector<bool>                myBitSet;

    string                      myEntityName;
    CT_TL1_FacAddr              myFacAddr;    
    CT_CardType                 myCardType;
    CT_SubCardType              mySubCardType;
    bool                        myAutoAdjustAttenuationEnabled;
    bool                        myOtuMapEnabled;
    CT_Fac_TraceString          myExpectedTrace;
    CT_Fac_TraceString          mySentTrace;
    CT_Fac_TraceString          myProtFunc;
    bool                        myMonitorOtiEnabled;
    bool                        myMonitorTraceEnabled;
    bool                        myInsertAisEnabled;
    uint8                       myNpOwner;
    CT_TEL_FecType              myFecType;
    CT_TEL_SuperFec             mySuperFec;
    CT_FAC_ExternalConnectivity myConnectivity;
    CT_Fac_ConnectedToString    myConnectedTo;
    CT_TEL_BERLevels            mySDThreshold;
    CT_FAC_RxSsm                mySsmReceived;
    CT_TEL_MsTref               myTimingReference;
    int                         myProtHoldOffTime;
    uint32                      myExtChannel;
    //CT_RelativeWavelength       myExtChannel;
    CT_TEL_OEO_REGEN_MODE       myOeoRegen;
    CT_TEL_ClkType              myClkType;
    CT_TEL_OTIDStatus           myOTIDStatus;
    CT_TEL_TimCriteriaMode      myTimDef;
    CT_Fac_TraceString          myExpDapi;
    CT_Fac_TraceString          myExpSapi;
    CT_Fac_TraceString          myTxDapi;
    CT_Fac_TraceString          myTxSapi;
    uint16                      myBurstyBerSdInterval;
    uint32                      myBurstyBerSdThreshold;
    CT_Fac_TraceString          myExpOperator;
    CT_Fac_TraceString          myTxOperator;
    CT_ProfileTableId           myAlarmProfile;
    CT_SM_PST                   myPST;
    CT_SM_PSTQ                  myPSTQ;
    CT_SM_SST                   mySST;
};

typedef TL1_Rtv_Response< TL1_OCHRspBlk > TL1_OCHResponse;
#endif  // #ifndef __TL1_OCH_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
