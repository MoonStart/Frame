/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive GCC Response Class
TARGET:
AUTHOR:         
DESCRIPTION:   
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_IBBR_RESPONSE_BLOCK_H__
#define __TL1_IBBR_RESPONSE_BLOCK_H__

#ifndef __TL1_SMARTPARAMETER_H__
#include <Response/TL1_SmartParameter.h>
#endif

#include <Response/TL1_Response.h>


#include <CommonTypes/CT_IBETH_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_TL1_FacParamAddr.h>


class TL1_IBBRRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_IBBRRspBlk( );
	
	TL1_IBBRRspBlk(const TL1_IBBRRspBlk& );

	TL1_IBBRRspBlk(const TL1_SmartParameter<string>& theBridgeAid,
                   const TL1_SmartParameter<int>& theVs,
                   const TL1_SmartParameter<int>& theBridgeVlan,
                   const TL1_SmartParameter<string>& theIp,
                   const TL1_SmartParameter<string>& theIpmask,
                   const TL1_SmartParameter<CT_SM_PST>& thePST,
                   const TL1_SmartParameter<CT_SM_SST>& theSST,
                   const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ);
    
    virtual ~TL1_IBBRRspBlk();

    TL1_IBBRRspBlk& operator=( const TL1_IBBRRspBlk& t1Blk );

    const TL1_SmartParameter<string>& GetBridgeAid() const;

    const TL1_SmartParameter<int>& GetVs() const;

    const TL1_SmartParameter<int>& GetBridgeVlan() const;

    const TL1_SmartParameter<string>& GetIp() const;

	const TL1_SmartParameter<string>& GetIpmask() const;

    const TL1_SmartParameter<CT_SM_PST>& GetPST() const;

	const TL1_SmartParameter<CT_SM_SST>& GetSST() const;

    const TL1_SmartParameter<CT_SM_PSTQ>& GetPSTQ() const;

private:
  
    TL1_SmartParameter<string>     myBridgeAid;
    TL1_SmartParameter<int>        myVs;
    TL1_SmartParameter<int>        myBridgeVlan;
    TL1_SmartParameter<string>     myIp;
	TL1_SmartParameter<string>     myIpmask;
    TL1_SmartParameter<CT_SM_PST>    myPST;
	TL1_SmartParameter<CT_SM_SST>    mySST;
	TL1_SmartParameter<CT_SM_PSTQ>    myPSTQ;
};

typedef TL1_Rtv_Response< TL1_IBBRRspBlk > TL1_IBBRResponse;

#endif  

#endif 

