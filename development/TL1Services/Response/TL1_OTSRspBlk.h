/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OTS Response Class
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu, Montreal.
DESCRIPTION:    Header file for TL1 Retrive OTS Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_OTS_RESPONSE_BLOCK_H_
#define __TL1_OTS_RESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_OTSRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_OTSRspBlk();
    
    // Ctor for OTS
    TL1_OTSRspBlk(const string* theEntityName,
                  const CT_TL1_FacAddr* theAddr,
                  const CT_CardType* theCardType,
                  const CT_SubCardType* theSubCardType,
                  const bool* isAutoAdjustOutPowerEnabled,
                  const bool* isAutoAdjustInPowerEnabled,
                  const bool* isAutoTxPowerShutdownEnabled,
                  const CT_Fac_TraceString* theExpectedTrace,
                  const CT_Fac_TraceString* theSentTrace,
                  const bool* isMonitorTraceEnabled,
                  const CT_ProfileTableId* theAlarmProfile,
                  const CT_FAC_OtsChanMap* theChanMap,
                  const CT_FAC_OtsChanType* theChanType,
                  const CT_SM_PST*  thePST,
                  const CT_SM_PSTQ* thePSTQ,
                  const CT_SM_SST*  theSST);

    TL1_OTSRspBlk(const TL1_OTSRspBlk& );
    
    virtual ~TL1_OTSRspBlk();

    TL1_OTSRspBlk& operator=( const TL1_OTSRspBlk& theBlock );

    bool operator==( const TL1_OTSRspBlk& theBlock ) const;

    bool GetEntityName(string& ) const;
    bool GetFacAddr( CT_TL1_FacAddr&) const ;
    bool GetCardType(CT_CardType& ) const;
    bool GetSubCardType( CT_SubCardType&) const ;
    bool GetAutoAdjustOutPowerEnabled(bool& ) const;
    bool GetAutoAdjustInPowerEnabled( bool& ) const;
    bool GetAutoTxPowerShutdownEnabled( bool&) const;
    bool GetExpectedTrace( CT_Fac_TraceString&) const;    
    bool GetSentTrace( CT_Fac_TraceString& ) const;
    bool GetMonitorTraceEnabled( bool&) const;
    bool GetAlarmProfile( CT_ProfileTableId&) const;
    bool GetChanMap(CT_FAC_OtsChanMap&) const;
    bool GetChanType(CT_FAC_OtsChanType&) const;
    bool GetPST( CT_SM_PST&) const;
    bool GetPSTQ( CT_SM_PSTQ&) const;
    bool GetSST( CT_SM_SST&) const;
    CT_SM_PST  GetPST() const;
    CT_SM_PSTQ GetPSTQ() const;
    CT_SM_SST  GetSST() const;

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_CardType,
        INDEX_SubCardType,
        INDEX_AutoAdjustOutPowerEnabled,
        INDEX_AutoAdjustInPowerEnabled,
        INDEX_AutoTxPowerShutdownEnabled,
        INDEX_ExpectedTrace,
        INDEX_SentTrace,
        INDEX_MonitorTraceEnabled,
        INDEX_AlarmProfile,
        INDEX_ChanMap,
        INDEX_ChanType,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>      myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myFacAddr;    
    CT_CardType       myCardType;
    CT_SubCardType    mySubCardType;    
    bool              myAutoAdjustOutPowerEnabled;
    bool              myAutoAdjustInPowerEnabled;
    bool              myAutoTxPowerShutdownEnabled;
    CT_Fac_TraceString myExpectedTrace;
    CT_Fac_TraceString mySentTrace;
    bool              myMonitorTraceEnabled;
    CT_ProfileTableId myAlarmProfile;
    CT_FAC_OtsChanMap myChanMap;
    CT_FAC_OtsChanType myChanType;
    CT_SM_PST         myPST;
    CT_SM_PSTQ        myPSTQ;
    CT_SM_SST         mySST;

};

typedef TL1_Rtv_Response< TL1_OTSRspBlk > TL1_OTSResponse;
#endif  // #ifndef __TL1_OTS_RESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
