/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Equipment Response Class
TARGET:
AUTHOR:         November 7, 2005 - Ed Bandyk
DESCRIPTION:    Header file for TL1 Retrieve OPTPWR
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_RTRVOPTPWRESPONSE_BLOCK_H_
#define __TL1_RTRVOPTPWRESPONSE_BLOCK_H_

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_Equipment.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardStatusMonitoring.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_SystemIds.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_ITS_Definitions.h>
#include <CommonTypes/CT_Time.h>

#include <vector>
using namespace std;

class TL1_RtrvOptPwrRspBlk: public TL1_GeneralRspBlk
{
public:
    TL1_RtrvOptPwrRspBlk();

    TL1_RtrvOptPwrRspBlk( const string* theEntityName,
                            const CT_TL1_SlotAddr* theSlotAddr,
                            const CT_MeasOptChanNum* theChannel,
                            const CT_TL1_Port* thePort,
                            const CT_MeasOptChanNum* theLane,
                            CT_TEL_mBm* theAttn,               
                            CT_TEL_mBm* theIGain,              
                            CT_TEL_mBm* theOGain,
                            CT_TEL_mBm* theEstOptPwr,
                            CT_TEL_mBm* theLsrOptPwr,          
                            CT_TEL_mBm* theLstOptPwr,          
	                        CT_TEL_mBm* thePsrOptPwr,			
                            CT_TEL_mBm* thePstOptPwr,		
                            CT_TEL_mBm* thePsrLLOptPwr,
                            CT_TEL_mBm* thePsrLHOptPwr,
                            CT_TEL_mBm* thePstLLOptPwr,
                            CT_TEL_mBm* thePstLHOptPwr,
                            CT_TEL_mBm* thePsrLNOptPwr,
                            CT_TEL_mBm* thePstLNOptPwr,                            
                            CT_TEL_mBm* theDsrOptPwr,
                            CT_TEL_mBm* theDstOptPwr,
                            CT_TimeTm* theDateTime );

                     
    TL1_RtrvOptPwrRspBlk(const TL1_RtrvOptPwrRspBlk& eqBlk);
    
    virtual ~TL1_RtrvOptPwrRspBlk();

    TL1_RtrvOptPwrRspBlk& operator=( const TL1_RtrvOptPwrRspBlk& theBlock );

    bool operator==( const TL1_RtrvOptPwrRspBlk& theBlock ) const;

    bool GetEntityName( string&) const;

    bool GetSlotAddr( CT_TL1_SlotAddr&) const;

    bool GetChannel(CT_MeasOptChanNum& theChannel) const;

    bool GetPort(CT_TL1_Port& thePort) const;

    bool GetLane(CT_MeasOptChanNum& theLane) const;	

    bool GetAttn(CT_TEL_mBm&) const;

    bool GetIGain(CT_TEL_mBm&) const;

    bool GetOGain(CT_TEL_mBm&) const;

    bool GetEstOptPwr(CT_TEL_mBm&) const;

    bool GetLsrOptPwr(CT_TEL_mBm&) const;

    bool GetLstOptPwr(CT_TEL_mBm&) const;

    bool GetPsrOptPwr(CT_TEL_mBm&) const;

    bool GetPstOptPwr(CT_TEL_mBm&) const;

    bool GetPsrLaneLowOptPwr(CT_TEL_mBm&) const;

    bool GetPsrLaneHighOptPwr(CT_TEL_mBm&) const;

    bool GetPstLaneLowOptPwr(CT_TEL_mBm&) const;

    bool GetPstLaneHighOptPwr(CT_TEL_mBm&) const;

    bool GetPsrLaneNumOptPwr(CT_TEL_mBm&) const;

    bool GetPstLaneNumOptPwr(CT_TEL_mBm&) const;	

    bool GetDsrOptPwr(CT_TEL_mBm&) const;

    bool GetDstOptPwr(CT_TEL_mBm&) const;

    bool GetDateTime(CT_TimeTm&) const;
    

private:
    enum {
        INDEX_EntityName = 0,
        INDEX_SlotAddr,
        INDEX_Channel,
        INDEX_Port,
        INDEX_Attn,
        INDEX_IGain,
        INDEX_OGain,
        INDEX_EstOptPwr,
        INDEX_LsrOptPwr,
        INDEX_LstOptPwr,
        INDEX_PsrOptPwr,
        INDEX_PstOptPwr,
        INDEX_PsrLaneLowOptPwr,
        INDEX_PsrLaneHighOptPwr,
        INDEX_PstLaneLowOptPwr,
        INDEX_PstLaneHighOptPwr,
        INDEX_DsrOptPwr,
        INDEX_DstOptPwr,
        INDEX_DateTime,
        INDEX_Lane,
        INDEX_PsrLaneNumOptPwr,
        INDEX_PstLaneNumOptPwr,
        INDEX_END
	    };

        vector<bool>        myBitSet;
        string              myEntityName;
        CT_TL1_SlotAddr     mySlotAddr;
        CT_MeasOptChanNum   myChannel;
        CT_TL1_Port         myPort;
		CT_MeasOptChanNum   myLane;
        CT_TEL_mBm          myAttn;               
        CT_TEL_mBm          myIGain;              
        CT_TEL_mBm          myOGain;
        CT_TEL_mBm          myEstOptPwr;
        CT_TEL_mBm          myLsrOptPwr;          
        CT_TEL_mBm          myLstOptPwr;          
	    CT_TEL_mBm          myPsrOptPwr;			
        CT_TEL_mBm          myPstOptPwr;		
        CT_TEL_mBm          myPsrLaneLowOptPwr;			
        CT_TEL_mBm          myPsrLaneHighOptPwr;		
        CT_TEL_mBm          myPstLaneLowOptPwr;			
        CT_TEL_mBm          myPstLaneHighOptPwr;
        CT_TEL_mBm          myPsrLaneNumOptPwr;			
        CT_TEL_mBm          myPstLaneNumOptPwr;		
        CT_TEL_mBm          myDsrOptPwr;
        CT_TEL_mBm          myDstOptPwr;

        CT_TimeTm           myDateTime;

};

typedef TL1_Rtv_Response< TL1_RtrvOptPwrRspBlk > TL1_RtrvOptPwrResponse;

#endif  // #ifndef __TL1_RTRVOPTPWRESPONSE_BLOCK_H_

#endif  // #ifdef  __cplusplus
