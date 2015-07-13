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

#ifndef __TL1_IBETH_RESPONSE_BLOCK_H__
#define __TL1_IBETH_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>


#include <CommonTypes/CT_IBETH_Definitions.h>
#include <CommonTypes/CT_TL1_LogicalAddr.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_TL1_FacParamAddr.h>
#include <CommonTypes/CT_TL1_ControlPlaneAddr.h>

class TL1_IBETHRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_IBETHRspBlk( );
	
	TL1_IBETHRspBlk(const TL1_IBETHRspBlk& );
    
    virtual ~TL1_IBETHRspBlk();

    TL1_IBETHRspBlk& operator=( const TL1_IBETHRspBlk& t1Blk );

    bool operator==( const TL1_IBETHRspBlk& t1Blk ) const;

    bool GetEntityName( string& theEntityName ) const;
    bool GetIBETHAddr( CT_TL1_FacAddr& theIBETHAddr ) const;
	bool GetLkType( CT_LkType& theLktype) const;
    bool GetBridge( CT_Bridge& theBridge ) const;
    bool GetPST( CT_SM_PST& thePST ) const;
    bool GetPSTQ( CT_SM_PSTQ& thePSTQ ) const;
    bool GetSST( CT_SM_SST& theSST ) const;

    void SetEntityName( string& theEntityName );
    void SetIBETHAddr(CT_TL1_FacAddr& theIBETHAddr );
    void SetLkType(CT_LkType& theLktype);
    void SetBridge(CT_Bridge& theBridge );
    void SetPST( CT_SM_PST& thePST );
    void SetPSTQ( CT_SM_PSTQ& thePSTQ );
    void SetSST( CT_SM_SST& theSST );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_IBETHAddr,
        INDEX_LkType,
        INDEX_Bridge,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>        myBitSet;

    string            myEntityName;
    CT_TL1_FacAddr    myIBETHAddr;
    CT_LkType         myLkType;
    CT_Bridge            myBridge;
    CT_SM_PST         myPST;
    CT_SM_PSTQ        myPSTQ;
    CT_SM_SST         mySST;
};

typedef TL1_Rtv_Response< TL1_IBETHRspBlk > TL1_IBETHResponse;

#endif  

#endif 

