/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Retrive Conn Response Class
TARGET:
AUTHOR:         May 30, 2007 - Tong Wu
DESCRIPTION:    Header file for TL1 Retrive Connection Response class declaration
-----------------------------------------------------------------------------*/
#ifdef WIN32 // Microsoft bug, identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifdef __cplusplus

#ifndef __TL1_CONN_RESPONSE_BLOCK_H__
#define __TL1_CONN_RESPONSE_BLOCK_H__

#include <Response/TL1_Response.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>
#include <CommonTypes/CT_SM_Types.h>
#include <CommonTypes/CT_CardTypes.h>
#include <CommonTypes/CT_AM_Definitions.h>
#include <CommonTypes/CT_Telecom.h>
#include <CommonTypes/CT_AgentFacility.h>
#include <CommonTypes/CT_TL1_Base.h>

class TL1_ConnRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_ConnRspBlk( );
	
    TL1_ConnRspBlk( const CT_ControlPlane_CallId        theCallId,
                    const CT_TL1_NodeAddr               theNodeAid,
                    const CT_ControlPlane_ConnectionId  theConnId,  
                    const CT_Call_SignalType            theSignalType,
                    const uint8                         theMultiplierValue,
                    const CT_Call_Directionality        theDirectionality,
                    const CT_Conn_ProtectionType        theProtectionType,
                    const CT_ConnMode                   theConnMode,
                    const CT_CallPathType*              theConnRole,
                    const CT_E2E_SessionId*             theEtoESessionId,
                    const CT_Resv_Style                 theReservationStyle,
                    const CT_SM_PST*                    thePST,
                    const CT_SM_PSTQ*                   thePSTQ,
                    const CT_SM_SST*                    theSST );
 	
    TL1_ConnRspBlk(const TL1_ConnRspBlk& );
    
    virtual ~TL1_ConnRspBlk();

    TL1_ConnRspBlk& operator=( const TL1_ConnRspBlk& t1Blk );

    bool operator==( const TL1_ConnRspBlk& t1Blk ) const;

    bool GetCallId( CT_ControlPlane_CallId& theCallId ) const;
    bool GetNodeAid( CT_TL1_NodeAddr& theNodeAid ) const;
    bool GetConnId( CT_ControlPlane_ConnectionId&  theConnId ) const;
    bool GetSignalType( CT_Call_SignalType& theSignalType ) const;
    bool GetMultiple( uint8& theMultiplierValue ) const;
    bool GetDirection( CT_Call_Directionality& theDirectionality ) const;
    bool GetProtType( CT_Conn_ProtectionType& theProtectionType ) const;
    bool GetConnMode( CT_ConnMode& theConnMode ) const;
    bool GetConnRole( CT_CallPathType& theConnRole ) const;
    bool GetEtoESessionId( CT_E2E_SessionId& theEtoESessionId ) const;
    bool GetReservationStyle( CT_Resv_Style&  theReservationStyle ) const;
    bool GetPST( CT_SM_PST&) const;
    bool GetPSTQ( CT_SM_PSTQ&) const;
    bool GetSST( CT_SM_SST&) const;

    void SetCallId( const CT_ControlPlane_CallId& theCallId );
    void SetNodeAid( const CT_TL1_NodeAddr& theNodeAid );
    void SetConnId( const CT_ControlPlane_ConnectionId&  theConnId );
    void SetSignalType( const CT_Call_SignalType& theSignalType );
    void SetMultiple( const uint8& theMultiplierValue );
    void SetDirection( const CT_Call_Directionality& theDirectionality );
    void SetProtType( const CT_Conn_ProtectionType& theProtectionType );
    void SetConnMode( const CT_ConnMode& theConnMode );
    void SetConnRole( const CT_CallPathType& theConnRole );
    void SetEtoESessionId( const CT_E2E_SessionId& theEtoESessionId );
    void SetReservationStyle( const CT_Resv_Style&  theReservationStyle );
    void SetPST( const CT_SM_PST& thePST);
    void SetPSTQ( const CT_SM_PSTQ& thePSTQ);
    void SetSST( const CT_SM_SST& theSST);


private:

    enum 
    {
        INDEX_CallId = 0,
        INDEX_NodeAid,
        INDEX_ConnId,	
        INDEX_ConnState,
        INDEX_SigType,
        INDEX_Multiple,	
        INDEX_Direction,
        INDEX_ProtType,
        INDEX_ConnMode,
        INDEX_ConnRole,
        INDEX_EtoESessionId,
        INDEX_ReservationStyle,
        INDEX_PST,
        INDEX_PSTQ,
        INDEX_SST,
        INDEX_END
    };

    vector<bool>                    myBitSet;

    CT_ControlPlane_CallId          myCallId;
    CT_TL1_NodeAddr                 myNodeAid;
    CT_ControlPlane_ConnectionId    myConnId;
    CT_Call_SignalType              mySignalType;
    uint8                           myMultiplierValue; 
    CT_Call_Directionality          myDirectionality;
    CT_Conn_ProtectionType          myProtectionType;
    CT_ConnMode                     myConnMode;
    CT_CallPathType                 myConnRole;
    CT_E2E_SessionId                myEtoESessionId;
    CT_Resv_Style                   myReservationStyle;
    CT_SM_PST                       myPST;
    CT_SM_PSTQ                      myPSTQ;
    CT_SM_SST                       mySST;
};
typedef TL1_Rtv_Response< TL1_ConnRspBlk > TL1_ConnResponse;



class TL1_ConnInfoRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_ConnInfoRspBlk( );

    virtual ~TL1_ConnInfoRspBlk();

    TL1_ConnInfoRspBlk& operator=( const TL1_ConnInfoRspBlk& t1Blk );

    bool operator==( const TL1_ConnInfoRspBlk& t1Blk ) const;

    bool GetCallId( CT_ControlPlane_CallId& theCallId ) const;
    bool GetNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const;
    bool GetConnId( CT_ControlPlane_ConnectionId& theConnId ) const;
    bool GetMtNumber( int& theMtNumber ) const;
    bool GetResourceList( list<string>& theResourceType ) const;
    bool GetConnMode( CT_ConnMode& theConnMode) const;
    bool GetConnPath( CT_CallPathType& theConnPath) const;

    void SetCallId( const CT_ControlPlane_CallId& theCallId );
    void SetNodeAddr( const CT_TL1_NodeAddr& theNodeAid );
    void SetConnId( const CT_ControlPlane_ConnectionId& theConnId );
    void SetMtNumber( const int& theMtNumber );
    void SetResource( const string& theResourceType );
    void SetConnMode( const CT_ConnMode& theConnMode);
    void SetConnPath( const CT_CallPathType& theConnPath);

private:
    enum 
    {
        INDEX_CallId = 0,
        INDEX_Node,
        INDEX_ConnId,
        INDEX_MtNumber,
        INDEX_Resource,
        INDEX_ConnMode,
        INDEX_ConnPath,
        INDEX_END
    };

    vector<bool>                    myBitSet;

    CT_ControlPlane_CallId          myCallId;
    CT_TL1_NodeAddr                 myNodeAid;
    CT_ControlPlane_ConnectionId    myConnId;
    int                             myMtNumber;
    list<string>                    myResourceList;
    CT_ConnMode                     myConnMode; 
    CT_CallPathType                 myConnPath;
};
typedef TL1_Rtv_Response< TL1_ConnInfoRspBlk > TL1_ConnInfoResponse;

class TL1_ConnRouteRspBlk : public TL1_GeneralRspBlk
{
public:

    TL1_ConnRouteRspBlk( );

    virtual ~TL1_ConnRouteRspBlk( );

    TL1_ConnRouteRspBlk& operator=( const TL1_ConnRouteRspBlk& t1Blk );

    bool operator==( const TL1_ConnRouteRspBlk& t1Blk ) const;

    bool GetCallId( CT_ControlPlane_CallId& theCallId ) const;
    bool GetaEndPoint( CT_ControlPlane_TNA& theAEnd ) const;
    bool GetzEndPoint( CT_ControlPlane_TNA& theZend ) const;
    bool GetNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const;
    bool GetConnId( CT_ControlPlane_ConnectionId& theConnId ) const;
    bool GetWorkingEro( CT_ControlPlane_Hops& theWorkingEro ) const;
    bool GetProtectEro( CT_ControlPlane_Hops& theProtectEro ) const;
    bool GetWorkingRro( CT_ControlPlane_Hops& theWorkingRro ) const;
    bool GetProtectRro( CT_ControlPlane_Hops& theProtectRro ) const;
    bool GetMtNumber( int& theMtNumber ) const;
    

    void SetCallId( const CT_ControlPlane_CallId& theCallId );
    void SetaEndPoint( const CT_ControlPlane_TNA& theAEnd );
    void SetzEndPoint( const CT_ControlPlane_TNA& theZend );
    void SetNodeAddr( const CT_TL1_NodeAddr& theNodeAid );
    void SetConnId( CT_ControlPlane_ConnectionId& theConnId );
    void SetWorkingEro( const CT_ControlPlane_Hops& theWorkingEro );
    void SetProtectEro( const CT_ControlPlane_Hops& theProtectEro );
    void SetWorkingRro( const CT_ControlPlane_Hops& theWorkingRro );
    void SetProtectRro( const CT_ControlPlane_Hops& theProtectRro );
    void SetMtNumber( const int& theMtNumber );

private:
    enum
    {
        INDEX_CallId = 0,
        INDEX_Aend,
        INDEX_Zend,
        INDEX_Node,
        INDEX_ConnId,
        INDEX_WorkingEro,
        INDEX_ProtectEro,
        INDEX_WorkingRro,
        INDEX_ProtectRro,
        INDEX_MtNumber,
        INDEX_END
    };

    vector<bool>                    myBitSet;

    CT_ControlPlane_CallId          myCallId;
    CT_ControlPlane_TNA             myAEnd;
    CT_ControlPlane_TNA             myZend;
    CT_TL1_NodeAddr                 myNodeAid;
    CT_ControlPlane_ConnectionId    myConnId;
    CT_ControlPlane_Hops            myWorkingEro;
    CT_ControlPlane_Hops            myProtectEro;
    CT_ControlPlane_Hops            myWorkingRro;
    CT_ControlPlane_Hops            myProtectRro;
    int                             myMtNumber;
};
typedef TL1_Rtv_Response< TL1_ConnRouteRspBlk > TL1_ConnRouteResponse;

#endif  // #ifndef __TL1_CONN_RESPONSE_BLOCK_H__

#endif  // #ifdef  __cplusplus
