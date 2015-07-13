/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive CALL Response Class
TARGET:
AUTHOR:         May 02, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Retrive CALL Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_CALL_RESPONSE_BLOCK_H__
#define __TL1_CALL_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>

#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>

#ifndef __LT_CALL_H__
#include <LumosTypes/LT_Call.h>
#endif

class TL1_CallRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_CallRspBlk( );

    TL1_CallRspBlk( const CT_TL1_CallAddr               theAddr,
                    const CT_ControlPlane_CallId        theCallId,
                    const string                        theCallName,
                    const CT_ControlPlane_TNA&          theAEnd,
                    const CT_ControlPlane_TNA&          theZend,
                    const CT_TL1_NodeAddr               theNodeAid,
                    const CT_ControlPlane_TNA&          theAEnd2,
                    const CT_ControlPlane_TNA&          theZend2,
                    const uint32                        theNodeId2,
                    const CT_Call_SignalType            theSigType,
                    const int16                         theMultiplier,
                    const CT_Call_Directionality        theDirectionality,
                    const CT_ControlPlane_LabelSet&     theIngress,
                    const CT_ControlPlane_LabelSet&     theEgress,
                    const CT_ControlPlane_LabelSet&     theCpIngress,
                    const CT_ControlPlane_LabelSet&     theCpEgress,
                    const CT_ControlPlane_LabelSet&     theIngress2,
                    const CT_ControlPlane_LabelSet&     theEgress2,
                    const CT_ControlPlane_LabelSet&     theCpIngress2,
                    const CT_ControlPlane_LabelSet&     theCpEgress2,
                    const CT_LabelSetType               theLabelSetType,
                    const CT_TL1_LabelSetAddr           theLabelSet,
                    const CT_ControlPlane_Srlg&         theSrlg,
                    const uint16                        theTimeout,
                    const CT_TL1_LogicalAddr            theSlpf,
                    const CT_SLPF_ProtLvl               theProtLvl,
                    const CT_SLPF_PRIORITY              thePriority,
                    const CT_Call_Location              theCallLoc,
                    const CT_SM_PST*                    thePST,
                    const CT_SM_PSTQ*                   thePSTQ,
                    const CT_SM_SST*                    theSST,
                    const CT_TL1_ExppathAddr            theWkgPrp1,
                    const CT_TL1_ExppathAddr            theWkgPrp2,
                    const CT_TL1_ExppathAddr            theProtPrp1,
                    const CT_TL1_ExppathAddr            theProtPrp2,
                    const CT_TEL_daHz                   theExpRate,
                    const uint8                         theGfpTs,
                    const CT_TL1_ExdpathAddr            theWkgXPath,
                    const CT_TL1_ExdpathAddr            theProtXPath );
                   
    TL1_CallRspBlk(const TL1_CallRspBlk& );
    
    virtual ~TL1_CallRspBlk();

    TL1_CallRspBlk& operator=( const TL1_CallRspBlk& t1Blk );

    bool operator==( const TL1_CallRspBlk& t1Blk ) const;

    bool GetAddr(CT_TL1_CallAddr& theAddr) const;
    bool GetCallId( CT_ControlPlane_CallId& theCallId ) const;
    bool GetCallName( string& theCallName ) const;
    bool GetaEndPoint( CT_ControlPlane_TNA& theAEnd ) const;
    bool GetzEndPoint( CT_ControlPlane_TNA& theZend ) const;
    bool GetNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const;
    bool GetaEndPoint2( CT_ControlPlane_TNA& theAEnd2 ) const;
    bool GetzEndPoint2( CT_ControlPlane_TNA& theZend2 ) const;
    bool GetNodeId2( uint32& theNodeId2 ) const;
    bool GetSignalType( CT_Call_SignalType& theSigType ) const;
    bool GetMultiplier( int16& theMultiplier ) const;
    bool GetDirection( CT_Call_Directionality& theDirectionality ) const;
    bool GetIngress( CT_ControlPlane_LabelSet& theIngress ) const;
    bool GetEgress( CT_ControlPlane_LabelSet& theEgress ) const;
    bool GetCpIngress( CT_ControlPlane_LabelSet& theCpIngress ) const;
    bool GetCpEgress( CT_ControlPlane_LabelSet& theCpEgress ) const;
    bool GetIngress2( CT_ControlPlane_LabelSet& theIngress2 ) const;
    bool GetEgress2( CT_ControlPlane_LabelSet& theEgress2 ) const;
    bool GetCpIngress2( CT_ControlPlane_LabelSet& theCpIngress2 ) const;
    bool GetCpEgress2( CT_ControlPlane_LabelSet& theCpEgress2 ) const;
    bool GetLabelSetType(CT_LabelSetType& theLabelSetType) const;
    bool GetLabelSet(CT_TL1_LabelSetAddr& theLabelSetAddr) const;
    bool GetSrlg( CT_ControlPlane_Srlg& theSrlg ) const;
    bool GetTimeout( uint16& theTimeout ) const;
    bool GetSlpf( CT_TL1_LogicalAddr& theSlpf ) const;
    bool GetProtLvl( CT_SLPF_ProtLvl& theProtLvl ) const;
    bool GetPriority( CT_SLPF_PRIORITY& thePriority ) const;
    bool GetCallLoc( CT_Call_Location& theCallLoc ) const;
    bool GetWkgPrp1( CT_TL1_ExppathAddr& theExppath ) const;
    bool GetWkgPrp2( CT_TL1_ExppathAddr& theExppath ) const;
    bool GetProtPrp1( CT_TL1_ExppathAddr& theExppath ) const;
    bool GetProtPrp2( CT_TL1_ExppathAddr& theExppath ) const;
    bool GetExpRate( CT_TEL_daHz& theExpRate) const;
    bool GetGfpTs( uint8& theGfpTs) const;
    bool GetWkgXPath( CT_TL1_ExdpathAddr& theWkgXPath ) const;
    bool GetProtXPath( CT_TL1_ExdpathAddr& theProtXPath ) const;
    bool GetPST( CT_SM_PST&) const;
    bool GetPSTQ( CT_SM_PSTQ&) const;
    bool GetSST( CT_SM_SST&) const;

    void SetAddr( const CT_TL1_CallAddr& theAddr);
    void SetCallId( const CT_ControlPlane_CallId& theCallId );
    void SetCallName( const string& theCallName );
    void SetaEndPoint( const CT_ControlPlane_TNA& theAEnd );
    void SetzEndPoint( const CT_ControlPlane_TNA& theZend );
    void SetNodeAddr( const CT_TL1_NodeAddr& theNodeAid );
    void SetaEndPoint2( const CT_ControlPlane_TNA& theAEnd2 );
    void SetzEndPoint2( const CT_ControlPlane_TNA& theZend2 );
    void SetNodeId2( const uint32& theNodeId2 );
    void SetSignalType( const CT_Call_SignalType& theSigType );
    void SetMultiplier( const int16& theMultiplier );
    void SetDirection( const CT_Call_Directionality& theDirectionality );
    void SetIngress( const CT_ControlPlane_LabelSet& theIngress );
    void SetEgress( const CT_ControlPlane_LabelSet& theEgress );
    void SetCpIngress( const CT_ControlPlane_LabelSet& theCpIngress );
    void SetCpEgress( const CT_ControlPlane_LabelSet& theCpEgress );
    void SetIngress2( const CT_ControlPlane_LabelSet& theIngress2 );
    void SetEgress2( const CT_ControlPlane_LabelSet& theEgress2 );
    void SetCpIngress2( const CT_ControlPlane_LabelSet& theCpIngress2 );
    void SetCpEgress2( const CT_ControlPlane_LabelSet& theCpEgress2 );
    void SetLabelSetType(const CT_LabelSetType& theLabelSetType);
    void SetLabelSet(const CT_TL1_LabelSetAddr& theLabelSetAddr);
    void SetSrlg( const CT_ControlPlane_Srlg& theSrlg );
    void SetTimeout( const uint16& theTimeout );
    void SetSlpf( const CT_TL1_LogicalAddr& theSlpf );
    void SetProtLvl( const CT_SLPF_ProtLvl theProtLvl );
    void SetPriority( const CT_SLPF_PRIORITY& thePriority );
    void SetCallLoc( const CT_Call_Location& theCallLoc );
    void SetWkgPrp1( const CT_TL1_ExppathAddr& theExppath );
    void SetWkgPrp2( const CT_TL1_ExppathAddr& theExppath );
    void SetProtPrp1( const CT_TL1_ExppathAddr& theExppath );
    void SetProtPrp2( const CT_TL1_ExppathAddr& theExppath );
    void SetExpRate(const CT_TEL_daHz& theExpRate);
    void SetGfpTs(const uint8& theGfpTs);
    void SetWkgXPath( const CT_TL1_ExdpathAddr& theWkgXPath );
    void SetProtXPath( const CT_TL1_ExdpathAddr& theProtXPath );
    void SetPST( const CT_SM_PST& thePST);
    void SetPSTQ( const CT_SM_PSTQ& thePSTQ);
    void SetSST( const CT_SM_SST& theSST);


private:

    enum 
    {
        INDEX_Addr = 0,
        INDEX_CallId,
        INDEX_CallName,
        INDEX_AEnd,
        INDEX_ZEnd,
        INDEX_NodeId,
        INDEX_AEnd2,
        INDEX_ZEnd2,
        INDEX_NodeId2,
        INDEX_SigType,
        INDEX_Multiple,
        INDEX_Direction,
        INDEX_Ingrss,
        INDEX_Egrss,
        INDEX_CpIngrss,
        INDEX_CpEgrss,
        INDEX_Ingrss2,
        INDEX_Egrss2,
        INDEX_CpIngrss2,
        INDEX_CpEgrss2,
        INDEX_LabelSetType,
        INDEX_LabelSet,
        INDEX_Srlg,
        INDEX_Timeout,
        INDEX_Slpf,
        INDEX_ProtLvl,
        INDEX_Priority,
        INDEX_CallLoc,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_WkgPrp1,
        INDEX_WkgPrp2,
        INDEX_ProtPrp1,
        INDEX_ProtPrp2,
        INDEX_ExpRate,
        INDEX_GfpTs,
        INDEX_WkgXPath,
        INDEX_ProtXPath,
        INDEX_END
    };

    vector<bool>                myBitSet;

    CT_TL1_CallAddr             myAddr;
    CT_ControlPlane_CallId      myCallId;
    string                      myCallName;
    CT_ControlPlane_TNA         myAEnd;
    CT_ControlPlane_TNA         myZend;
    CT_TL1_NodeAddr             myNodeAid;
    CT_ControlPlane_TNA         myAEnd2;
    CT_ControlPlane_TNA         myZend2;
    uint32                      myNodeId2;
    CT_Call_SignalType          mySigType;
    int16                       myMultiplier;
    CT_Call_Directionality      myDirectionality;
    CT_ControlPlane_LabelSet    myIngress;
    CT_ControlPlane_LabelSet    myEgress;
    CT_ControlPlane_LabelSet    myCpIngress;
    CT_ControlPlane_LabelSet    myCpEgress;
    CT_ControlPlane_LabelSet    myIngress2;
    CT_ControlPlane_LabelSet    myEgress2;
    CT_ControlPlane_LabelSet    myCpIngress2;
    CT_ControlPlane_LabelSet    myCpEgress2;
    CT_LabelSetType             myLabelSetType;
    CT_TL1_LabelSetAddr         myLabelSet;
    CT_ControlPlane_Srlg        mySrlg;
    uint16                      myTimeout;
    CT_TL1_LogicalAddr          mySlpf;
    CT_SLPF_ProtLvl             myProtLvl;
    CT_SLPF_PRIORITY            myPriority;
    CT_Call_Location            myCallLoc;
    CT_SM_PST                   myPST;
    CT_SM_PSTQ                  myPSTQ;
    CT_SM_SST                   mySST;
    CT_TL1_ExppathAddr          myWkgPrp1;
    CT_TL1_ExppathAddr          myWkgPrp2;
    CT_TL1_ExppathAddr          myProtPrp1;
    CT_TL1_ExppathAddr          myProtPrp2;
    CT_TEL_daHz                 myExpRate;
    uint8                       myGfpTs;
    CT_TL1_ExdpathAddr          myWkgXPath;
    CT_TL1_ExdpathAddr          myProtXPath;
};
typedef TL1_Rtv_Response< TL1_CallRspBlk > TL1_CallResponse;

//---------------------------------------------------------------------------------------

class TL1_CallDetailRspBlk : public TL1_GeneralRspBlk
{
public:
    TL1_CallDetailRspBlk( );
    
    TL1_CallDetailRspBlk( const TL1_CallDetailRspBlk& );
    
    virtual ~TL1_CallDetailRspBlk( );
    
    TL1_CallDetailRspBlk& operator=( const TL1_CallDetailRspBlk& tlBlk );
    
    bool GetCallAddr(CT_TL1_CallAddr& theAddr) const;
    bool GetCallId( CT_ControlPlane_CallId& theCallId ) const;
    bool GetCallNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const;
    bool GetMultiplier( int16& theMultiplier ) const;
    bool GetConnId( CT_ControlPlane_ConnectionId& theConnId ) const;
    bool GetConnNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const;
    bool GetResourceList( list<string>& theResourceList ) const;
    bool GetConnMode( CT_ConnMode& theConnMode) const;
    bool GetConnPath( CT_CallPathType& theConnPath) const;

    void SetCallAddr( const CT_TL1_CallAddr& theAddr);
    void SetCallId( const CT_ControlPlane_CallId& theCallId );
    void SetCallNodeAddr( const CT_TL1_NodeAddr& theNodeAid );
    void SetMultiplier( const int16& theMultiplier );
    void SetConnId( const CT_ControlPlane_ConnectionId& theConnId );
    void SetConnNodeAddr( const CT_TL1_NodeAddr& theNodeAid );
    void SetResource( const string& theResource );
    void SetConnMode( const CT_ConnMode& theConnMode);
    void SetConnPath( const CT_CallPathType& theConnPath);
    
private:
    enum 
    {
        INDEX_Addr = 0,
        INDEX_CallId,
        INDEX_NodeId,
        INDEX_Multiple,	
        INDEX_ConnId,
        INDEX_ConnNodeId,
        INDEX_ConnMode,
        INDEX_ConnPath,
        INDEX_Resource,
        INDEX_END
    };

    vector<bool>                myBitSet;

    CT_TL1_CallAddr             myCallAddr;
    CT_ControlPlane_CallId          myCallId;
    CT_TL1_NodeAddr                 myCallNodeAid;
    int                             myMtNumber;
    CT_ControlPlane_ConnectionId    myConnId;
    CT_TL1_NodeAddr                 myConnNodeAid;
    list<string>                    myResourceList;
    CT_ConnMode                     myConnMode;
    CT_CallPathType                 myConnPath;
};

typedef TL1_Rtv_Response< TL1_CallDetailRspBlk > TL1_CallDetailResponse;

//---------------------------------------------------------------------------------------
class TL1_CallidRspBlk : public TL1_GeneralRspBlk
{
public:

	TL1_CallidRspBlk( );
	
	TL1_CallidRspBlk( const CT_ControlPlane_CallId* theCallid );
	
	TL1_CallidRspBlk(const TL1_CallidRspBlk& );
    
        virtual ~TL1_CallidRspBlk();

        TL1_CallidRspBlk& operator=( const TL1_CallidRspBlk& t1Blk );

        bool operator==( const TL1_CallidRspBlk& t1Blk ) const;

        bool GetCallid( CT_ControlPlane_CallId& theCallid ) const;

        void SetCallid( CT_ControlPlane_CallId& theCallid );

private:
        enum 
        {
            INDEX_Callid = 0,
            INDEX_END
        };

        vector<bool>                 myBitSet;

        CT_ControlPlane_CallId       myCallid;
};

typedef TL1_Rtv_Response< TL1_CallidRspBlk > TL1_CallidResponse;

#endif  // #ifndef __TL1_CALL_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
