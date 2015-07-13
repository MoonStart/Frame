/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive OCH Response Class
TARGET:
AUTHOR:         July 10, 2006 - Thomas Novak
DESCRIPTION:    Header file for TL1 Retrive LAPDPF Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_LPADPF_RESPONSE_BLOCK_H__
#define __TL1_LPADPF_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_DCC_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_LAPDPFRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_LAPDPFRspBlk( );
	
	TL1_LAPDPFRspBlk(const TL1_LAPDPFRspBlk& );
    
    virtual ~TL1_LAPDPFRspBlk();

    TL1_LAPDPFRspBlk& operator=( const TL1_LAPDPFRspBlk& t1Blk );

    bool operator==( const TL1_LAPDPFRspBlk& t1Blk ) const;

    bool GetEntityName( string& ) const;
    bool GetFacAddr( CT_TL1_FacAddr& ) const;
    bool GetTxMode( CT_LPF_TxMode& ) const;
    bool GetSide( CT_LPF_Side& ) const;
    bool GetSeqNum( CT_LPF_SeqNum& ) const;
    bool GetPFname( CT_Fac_TraceString& ) const;
    bool GetRtranscnt( uint16& ) const;
    bool GetAcktmr( CT_LapdProfile_Timer& ) const;
    bool GetMxfrm( uint16& ) const;
    bool GetFrmcnt( uint16& ) const;
    bool GetInacttmr( uint16& ) const;

    void SetEntityName( const string& theEntityName );
    void SetFacAddr( const CT_TL1_FacAddr& theAddr );
    void SetTxMode( const CT_LPF_TxMode& theTxMode );
    void SetSide( const CT_LPF_Side& theSide );
    void SetSeqNum( const CT_LPF_SeqNum& theSeqNum );
    void SetPFname( const CT_Fac_TraceString& thePFname);
    void SetRtranscnt( const uint16& theRtranscnt );
    void SetAcktmr( const CT_LapdProfile_Timer& theAcktmr );
    void SetMxfrm( const uint16& theMxfrm );
    void SetFrmcnt( const uint16& theFrmcnt );
    void SetInacttmr( const uint16& theInacttmr );

private:
    enum 
    {
        INDEX_EntityName = 0,
        INDEX_FacAddr,
        INDEX_TxMode,
        INDEX_Side,
        INDEX_SeqNum,
        INDEX_PFname,
        INDEX_Rtranscnt,
		INDEX_Acktmr,
        INDEX_Mxfrm,
        INDEX_Frmcnt,
        INDEX_SST,        
        INDEX_Inacttmr,
        INDEX_END
    };

    vector<bool>        myBitSet;

    string               myEntityName;
    CT_TL1_FacAddr       myAddr;
    CT_LPF_TxMode		 myTxMode;
    CT_LPF_Side		     mySide;
    CT_LPF_SeqNum		 mySeqNum;
    CT_Fac_TraceString	 myPFname;
    uint16			     myRtranscnt;
    CT_LapdProfile_Timer myAcktmr;
    uint16			     myMxfrm;
    uint16				 myFrmcnt;
    uint16				 myInacttmr;
};

typedef TL1_Rtv_Response< TL1_LAPDPFRspBlk > TL1_LAPDPFResponse;
#endif  // #ifndef __TL1_LAPDPF_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
