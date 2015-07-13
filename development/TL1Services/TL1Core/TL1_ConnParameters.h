/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 29, 2007 - Tong Wu
DESCRIPTION:    Header file for Connection TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONNPARAMETERS_H__
#define __TL1_CONNPARAMETERS_H__

#ifndef __TL1_ENTITY_H__
#include <TL1Core/TL1_Entity.h>
#endif

#ifndef __TL1_ALARMDOMAIN_H__
#include <TL1Core/TL1_AlarmDomain.h>
#endif

#ifndef __TL1_CONNRSPBLK_H__
#include <Response/TL1_ConnRspBlk.h>
#endif

#include <LumosTypes/LT_System.h>
#include <CommonTypes/CT_ControlPlane_Definitions.h>

#ifndef __TL1_CONTROLPLANEFAL_H__
#include <TL1Core/TL1_ControlPlaneFal.h>
#endif

class CT_ControlPlane_CallId;
class CT_ControlPlane_ConnectionId;
class CT_TL1_NodeAddr;
class CT_ControlPlane_Hops;

class TL1_ConnEntParameters : public TL1_ControlPlaneFal 
{
public:
    
    TL1_ConnEntParameters();

    virtual ~TL1_ConnEntParameters();

    TL1_ConnEntParameters(const TL1_ConnEntParameters& theInst );

    TL1_ConnEntParameters& operator=( const TL1_ConnEntParameters& theInst );

    bool operator==( const TL1_ConnEntParameters& theInst ) const;

    inline LT_Handle*                       GetHandle( ) const;
    inline void                             SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                          GetCtag( ) const;
    inline void                             SetCtag( LT_Ctag theCtag );

    inline CT_ControlPlane_CallId*          GetCallid( ) const;
    inline void                             SetCallid( CT_ControlPlane_CallId* theCallid  );

    inline CT_TL1_NodeAddr*                 GetNodeAid( ) const;
    inline void                             SetNodeAid( CT_TL1_NodeAddr* theNodeAid );

    inline CT_ControlPlane_ConnectionId*    GetConnId( ) const;
    inline void                             SetConnId( CT_ControlPlane_ConnectionId* theConnId );

    inline CT_Call_SignalType*              GetSignalType( ) const;
    inline void                             SetSignalType( CT_Call_SignalType* theSignalType );

    inline uint8*                           GetMultiplierValue( ) const;
    inline void                             SetMultiplierValue( uint8* theMultiplierValue );

    inline CT_Call_Directionality*          GetDirection( ) const;
    inline void                             SetDirection( CT_Call_Directionality* theDirection );

    inline CT_Conn_ProtectionType*          GetProtectionType( ) const;
    inline void                             SetProtectionType( CT_Conn_ProtectionType* theProtection );

    inline CT_ControlPlane_Hops*            GetRoute( ) const;
    inline void                             SetRoute( CT_ControlPlane_Hops* theRoute );

    inline uint16*                          GetEgressTunnelId( ) const;
    inline void                             SetEgressTunnelId( uint16* theEgressTunnelId );

    inline uint16*                          GetEgressLspId( ) const;
    inline void                             SetEgressLspId( uint16* theEgressLspId );

    inline uint32*                          GetEgressExtendedTunnelId( ) const;
    inline void                             SetEgressExtendedTunnelId( uint32* theEgressExtendedTunnelId );

    inline uint32*                          GetEgressSrcAddr( ) const;
    inline void                             SetEgressSrcAddr( uint32* theEgressSrcAddr );
    inline uint16*                          GetIngressTunnelId( ) const;
    inline void                             SetIngressTunnelId( uint16* theIngressTunnelId );

    inline uint16*                          GetIngressLspId( ) const;
    inline void                             SetIngressLspId( uint16* theIngressLspId );

    inline uint32*                          GetIngressExtendedTunnelId( ) const;
    inline void                             SetIngressExtendedTunnelId( uint32* theIngressExtendedTunnelId );
    inline uint32*                          GetIngressSrcAddr( ) const;
    inline void                             SetIngressSrcAddr( uint32* theIngressSrcAddr );

    inline uint32*                          GetE2ESourceAddr( ) const;
    inline void                             SetE2ESourceAddr( uint32* theE2ESourceAddr );

    inline uint32*                          GetE2EDestAddr( ) const;
    inline void                             SetE2EDestAddr( uint32* theE2EDestAddr );

    inline uint16*                          GetE2ETunnelId( ) const;
    inline void                             SetE2ETunnelId( uint16* theE2ETunnelId );

    inline uint16*                          GetNumOfLabels( ) const;
    inline void                             SetNumOfLabels( uint16* theNumOfLabels );

    inline uint8*                           GetLabelSize( ) const;
    inline void                             SetLabelSize( uint8* theLabelSize );

    inline uint32*                          GetIfindex( ) const;
    inline void                             SetIfindex( uint32* theIfindex );

    inline uint32*                          GetLabel( ) const;
    inline void                             SetLabel( uint32* theLabel );

    inline uint8*                           GetMemberId( ) const;
    inline void                             SetMemberId( uint8* theMemberId );

    inline uint32*                          GetTermCp1P1NodeId( ) const;
    inline void                             SetTermCp1P1NodeId( uint32* theTermCp1P1NodeId );

    inline uint16*                          GetAssociationId( ) const;
    inline void                             SetAssociationId( uint16* theAssociationId );

    inline CT_Resv_Style*                   GetReservationStyle( ) const;
    inline void                             SetReservationStyle( CT_Resv_Style* theReservationStyle );

    inline uint8*                           GetConnMode( ) const;
    inline void                             SetConnMode( uint8* theConnMode );

    inline uint8*                           GetConnType( ) const;
    inline void                             SetConnType( uint8* theConnType );

    inline CT_CallPathType*                 GetConnRole( ) const;
    inline void                             SetConnRole( CT_CallPathType* theConnOperState );

    inline CT_Conn_Oper_State*              GetConnOperState( ) const;
    inline void                             SetConnOperState( CT_Conn_Oper_State* theConnOperState );

    inline CT_Conn_Status*                  GetConnStatus( ) const;
    inline void                             SetConnStatus( CT_Conn_Status* theConnStatus );

    inline bool*                            GetLastEffort( ) const;
    inline void                             SetLastEffort( bool* theLastEffort );

    inline uint8*                           GetNumAssocId( ) const;
    inline void                             SetNumAssocId( uint8* theNumAssocId );

    inline uint16*                          GetAreaAssocId( ) const;
    inline void                             SetAreaAssocId( uint16* theAreaAssocId );

    inline uint32*                          GetRoutingArea( ) const;
    inline void                             SetRoutingArea( uint32* theRoutingArea );

    inline uint8*                           GetAssocType( ) const;
    inline void                             SetAssocType( uint8* theAreaAssocType );

    inline CT_ControlPlane_LabelSet*        GetEgress( ) const;
    inline void                             SetEgress( CT_ControlPlane_LabelSet* theEgrss );

    CT_TEL_daHz*                            GetExpRate( ) const;
    void                                    SetExpRate(CT_TEL_daHz* theExpRate);

    uint8*                                  GetGfpTs( ) const;
    void                                    SetGfpTs(uint8* theGfpTs);

private:

    LT_Handle*                      myHandle;
    LT_Ctag                         myCtag;
    CT_ControlPlane_CallId*         myCallid;
    CT_TL1_NodeAddr*                myNodeAid;
    CT_ControlPlane_ConnectionId*   myConnId;
    CT_Call_SignalType*             mySignalType;
    uint8*                          myMultiplier;
    CT_Call_Directionality*         myDirection;
    CT_Conn_ProtectionType*         myProtection;
    CT_ControlPlane_Hops*           myRoute;
    CT_ControlPlane_LabelSet*       myEgress;

    uint16*                         myEgressTunnelId;
    uint16*                         myEgressLspId;
    uint32*                         myEgressExtendedTunnelId;
    uint32*                         myEgressSrcAddr;

    uint16*                         myIngressTunnelId;
    uint16*                         myIngressLspId;
    uint32*                         myIngressExtendedTunnelId;
    uint32*                         myIngressSrcAddr;

    uint32*                         myE2ESourceAddr;
    uint32*                         myE2EDestAddr;
    uint16*                         myE2ETunnelId;

    uint16*                         myNumOfLabels;
    uint8*                          myLabelSize;  
    uint32*                         myIfindex;
    uint32*                         myLabel;
    uint8*                          myMemberId;

    uint32*                         myTermCp1P1NodeId;
    uint16*                         myAssociationId;

    CT_Resv_Style*                  myReservationStyle;

    uint8*                          myConnMode;
    uint8*                          myConnType;

    CT_CallPathType*                myConnRole;
    CT_Conn_Oper_State*             myConnOperState;
    CT_Conn_Status*                 myConnStatus;

    bool*                           myLastEffort;

    uint8*                          myNumAssocId;
    uint16*                         myAreaAssocId;
    uint32*                         myRoutingArea;
    uint8*                          myAssocType;
    CT_TEL_daHz*                    myExpRate;
    uint8*                          myGfpTs;
};


//-----------------------------------------------------------------------------
class TL1_ConnEdParameters  
{
public:
    
    TL1_ConnEdParameters();

    virtual ~TL1_ConnEdParameters();

    TL1_ConnEdParameters(const TL1_ConnEdParameters& theInst );

    TL1_ConnEdParameters& operator=( const TL1_ConnEdParameters& theInst );

    bool operator==( const TL1_ConnEdParameters& theInst ) const;

    inline LT_Handle*                       GetHandle( ) const;
    inline void                             SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                          GetCtag( ) const;
    inline void                             SetCtag( LT_Ctag theCtag );

    inline CT_ControlPlane_CallId*          GetCallid( ) const;
    inline void                             SetCallid( CT_ControlPlane_CallId* theCallid  );

    inline CT_TL1_NodeAddr*                 GetNodeAid( ) const;
    inline void                             SetNodeAid( CT_TL1_NodeAddr* theNodeAid );

    inline CT_ControlPlane_ConnectionId*    GetConnId( ) const;
    inline void                             SetConnId( CT_ControlPlane_ConnectionId* theConnId );

    inline bool*                            GetIsCommandForced( ) const;
    inline void                             SetIsCommandForced( bool* theIsCommandForced );
    
    inline CT_SM_PST*                       GetPrimaryState( ) const;
    inline void                             SetPrimaryState( CT_SM_PST* thePrimaryState );


private:

    LT_Handle*                      myHandle;
    LT_Ctag                         myCtag;
    CT_ControlPlane_CallId*         myCallid;
    CT_TL1_NodeAddr*       myNodeAid;
    CT_ControlPlane_ConnectionId*   myConnId;
    bool*                           myIsCommandForced;
    CT_SM_PST*                      myPrimaryState;
};



//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_ConnEntParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_ConnEntParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_ConnEntParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_ConnEntParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_CallId*    
TL1_ConnEntParameters::GetCallid( ) const
{
    return myCallid;
}


inline void              
TL1_ConnEntParameters::SetCallid( CT_ControlPlane_CallId* theCallid )
{
    myCallid = theCallid;
}

//--------------------------------------------------------------------------------
inline CT_TL1_NodeAddr*                     
TL1_ConnEntParameters::GetNodeAid( ) const
{
    return myNodeAid;
}

inline void                         
TL1_ConnEntParameters::SetNodeAid( CT_TL1_NodeAddr* theNodeAid )
{
    myNodeAid = theNodeAid;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_ConnectionId*                     
TL1_ConnEntParameters::GetConnId( ) const
{
    return myConnId;
}

inline void                         
TL1_ConnEntParameters::SetConnId( CT_ControlPlane_ConnectionId* theConnId )
{
    myConnId = theConnId;
}

//--------------------------------------------------------------------------------
inline CT_Call_SignalType*    
TL1_ConnEntParameters::GetSignalType( ) const
{
    return mySignalType;
}


inline void              
TL1_ConnEntParameters::SetSignalType( CT_Call_SignalType* theSignalType )
{
    mySignalType = theSignalType;
}

//--------------------------------------------------------------------------------
inline uint8*                   
TL1_ConnEntParameters::GetMultiplierValue( ) const
{
    return myMultiplier;
}

inline void                         
TL1_ConnEntParameters::SetMultiplierValue( uint8* theMultiplierValue )
{
    myMultiplier = theMultiplierValue;
}

//--------------------------------------------------------------------------------
inline CT_Call_Directionality*                     
TL1_ConnEntParameters::GetDirection( ) const
{
    return myDirection;
}

inline void                         
TL1_ConnEntParameters::SetDirection( CT_Call_Directionality* theDirection )
{
    myDirection = theDirection;
}

//--------------------------------------------------------------------------------
inline CT_Conn_ProtectionType*    
TL1_ConnEntParameters::GetProtectionType( ) const
{
    return myProtection;
}


inline void              
TL1_ConnEntParameters::SetProtectionType( CT_Conn_ProtectionType* theProtection )
{
    myProtection = theProtection;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_Hops*                     
TL1_ConnEntParameters::GetRoute( ) const
{
    return myRoute;
}

inline void                         
TL1_ConnEntParameters::SetRoute( CT_ControlPlane_Hops* theRoute )
{
    myRoute = theRoute;
}

//--------------------------------------------------------------------------------
inline uint16* TL1_ConnEntParameters::GetEgressTunnelId( ) const
{
    return myEgressTunnelId;
}

inline void TL1_ConnEntParameters::SetEgressTunnelId( uint16* theEgressTunnelId )
{
    myEgressTunnelId = theEgressTunnelId;
}

//--------------------------------------------------------------------------------
inline uint16* TL1_ConnEntParameters::GetEgressLspId( ) const
{
    return myEgressLspId;
}

inline void TL1_ConnEntParameters::SetEgressLspId( uint16* theEgressLspId )
{
    myEgressLspId = theEgressLspId;
}

//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetEgressExtendedTunnelId( ) const
{
    return myEgressExtendedTunnelId;
}

inline void TL1_ConnEntParameters::SetEgressExtendedTunnelId( uint32* theEgressExtendedTunnelId )
{
    myEgressExtendedTunnelId = theEgressExtendedTunnelId;
}

//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetEgressSrcAddr( ) const
{
    return myEgressSrcAddr;
}
inline void TL1_ConnEntParameters::SetEgressSrcAddr( uint32* theEgressSrcAddr )
{
    myEgressSrcAddr = theEgressSrcAddr;
}
inline uint16* TL1_ConnEntParameters::GetIngressTunnelId( ) const
{
    return myIngressTunnelId;
}

inline void TL1_ConnEntParameters::SetIngressTunnelId( uint16* theIngressTunnelId )
{
    myIngressTunnelId = theIngressTunnelId;
}

//--------------------------------------------------------------------------------
inline uint16* TL1_ConnEntParameters::GetIngressLspId( ) const
{
    return myIngressLspId;
}

inline void TL1_ConnEntParameters::SetIngressLspId( uint16* theIngressLspId )
{
    myIngressLspId = theIngressLspId;
}

//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetIngressExtendedTunnelId( ) const
{
    return myIngressExtendedTunnelId;
}

inline void TL1_ConnEntParameters::SetIngressExtendedTunnelId( uint32* theIngressExtendedTunnelId )
{
    myIngressExtendedTunnelId = theIngressExtendedTunnelId;
}

inline uint32* TL1_ConnEntParameters::GetIngressSrcAddr( ) const
{
    return myIngressSrcAddr;
}
inline void TL1_ConnEntParameters::SetIngressSrcAddr( uint32* theIngressSrcAddr )
{
    myIngressSrcAddr = theIngressSrcAddr;
}

//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetE2ESourceAddr( ) const
{
    return myE2ESourceAddr;
}

inline void TL1_ConnEntParameters::SetE2ESourceAddr( uint32* theE2ESourceAddr )
{
    myE2ESourceAddr = theE2ESourceAddr;
}


//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetE2EDestAddr( ) const
{
    return myE2EDestAddr;
}

inline void TL1_ConnEntParameters::SetE2EDestAddr( uint32* theE2EDestAddr )
{
    myE2EDestAddr = theE2EDestAddr;
}


//--------------------------------------------------------------------------------
inline uint16* TL1_ConnEntParameters::GetE2ETunnelId( ) const
{
    return myE2ETunnelId;
}

inline void TL1_ConnEntParameters::SetE2ETunnelId( uint16* theE2ETunnelId )
{
    myE2ETunnelId = theE2ETunnelId;
}


//--------------------------------------------------------------------------------
inline uint16*                          
TL1_ConnEntParameters::GetNumOfLabels( ) const
{
    return myNumOfLabels;
}

inline void                             
TL1_ConnEntParameters::SetNumOfLabels( uint16* theNumOfLabels )
{
    myNumOfLabels = theNumOfLabels;
}

inline uint8*
TL1_ConnEntParameters::GetLabelSize( ) const
{
    return myLabelSize;
}

inline void
TL1_ConnEntParameters::SetLabelSize( uint8* theLabelSize )
{
    myLabelSize = theLabelSize;
}


//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetIfindex( ) const
{
    return myIfindex;
}

inline void TL1_ConnEntParameters::SetIfindex( uint32* theIfindex )
{
    myIfindex = theIfindex;
}

//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetLabel( ) const
{
    return myLabel;
}

inline void TL1_ConnEntParameters::SetLabel( uint32* theLabel )
{
    myLabel = theLabel;
}

//--------------------------------------------------------------------------------
inline uint8* TL1_ConnEntParameters::GetMemberId( ) const
{
    return myMemberId;
}

inline void TL1_ConnEntParameters::SetMemberId( uint8* theMemberId )
{
    myMemberId = theMemberId;
}

//--------------------------------------------------------------------------------
inline uint32* TL1_ConnEntParameters::GetTermCp1P1NodeId( ) const
{
    return myTermCp1P1NodeId;
}

inline void  TL1_ConnEntParameters::SetTermCp1P1NodeId( uint32* theTermCp1P1NodeId )
{
    myTermCp1P1NodeId = theTermCp1P1NodeId;
}

//--------------------------------------------------------------------------------
inline uint16*  
TL1_ConnEntParameters::GetAssociationId( ) const
{
    return myAssociationId;
}

inline void                             
TL1_ConnEntParameters::SetAssociationId( uint16* theAssociationId )
{
    myAssociationId = theAssociationId;
}

//--------------------------------------------------------------------------------
inline uint8*  
TL1_ConnEntParameters::GetConnMode( ) const
{
    return myConnMode;
}

inline void                             
TL1_ConnEntParameters::SetConnMode( uint8* theConnMode )
{
    myConnMode = theConnMode;
}

//--------------------------------------------------------------------------------
inline uint8*  
TL1_ConnEntParameters::GetConnType( ) const
{
    return myConnType;
}

inline void                             
TL1_ConnEntParameters::SetConnType( uint8* theConnType )
{
    myConnType = theConnType;
}


//--------------------------------------------------------------------------------
inline CT_Resv_Style*  
TL1_ConnEntParameters::GetReservationStyle( ) const
{
    return myReservationStyle;
}

inline void                             
TL1_ConnEntParameters::SetReservationStyle( CT_Resv_Style* theReservationStyle )
{
    myReservationStyle = theReservationStyle;
}


//--------------------------------------------------------------------------------
// Conn Role
inline CT_CallPathType*               
TL1_ConnEntParameters::GetConnRole( ) const
{
    return myConnRole;
}

inline void                         
TL1_ConnEntParameters::SetConnRole( CT_CallPathType* theConnRole )
{
    myConnRole = theConnRole;
}


//--------------------------------------------------------------------------------
// Conn Operational State
inline CT_Conn_Oper_State*               
TL1_ConnEntParameters::GetConnOperState( ) const
{
    return myConnOperState;
}

inline void                         
TL1_ConnEntParameters::SetConnOperState( CT_Conn_Oper_State* theConnOperState )
{
    myConnOperState = theConnOperState;
}


//--------------------------------------------------------------------------------
// Conn Status
inline CT_Conn_Status*               
TL1_ConnEntParameters::GetConnStatus( ) const
{
    return myConnStatus;
}

inline void                         
TL1_ConnEntParameters::SetConnStatus( CT_Conn_Status* theConnStatus )
{
    myConnStatus = theConnStatus;
}

//--------------------------------------------------------------------------------
// Last Effort
inline bool*               
TL1_ConnEntParameters::GetLastEffort( ) const
{
    return myLastEffort;
}

inline void                         
TL1_ConnEntParameters::SetLastEffort( bool* theLastEffort )
{
    myLastEffort = theLastEffort;
}

//--------------------------------------------------------------------------------
inline uint8*  
TL1_ConnEntParameters::GetNumAssocId( ) const
{
    return myNumAssocId;
}

inline void                             
TL1_ConnEntParameters::SetNumAssocId( uint8* theNumAssocId )
{
    myNumAssocId = theNumAssocId;
}

//--------------------------------------------------------------------------------
inline uint16*  
TL1_ConnEntParameters::GetAreaAssocId( ) const
{
    return myAreaAssocId;
}

inline void                             
TL1_ConnEntParameters::SetAreaAssocId( uint16* theAreaAssocId )
{
    myAreaAssocId = theAreaAssocId;
}

//--------------------------------------------------------------------------------
inline uint32*  
TL1_ConnEntParameters::GetRoutingArea( ) const
{
    return myRoutingArea;
}

inline void                             
TL1_ConnEntParameters::SetRoutingArea( uint32* theRoutingArea )
{
    myRoutingArea = theRoutingArea;
}

//--------------------------------------------------------------------------------
inline uint8*  
TL1_ConnEntParameters::GetAssocType( ) const
{
    return myAssocType;
}

inline void                             
TL1_ConnEntParameters::SetAssocType( uint8* theAssocType )
{
    myAssocType = theAssocType;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_LabelSet*    
TL1_ConnEntParameters::GetEgress( ) const
{
    return myEgress;
}


inline void              
TL1_ConnEntParameters::SetEgress( CT_ControlPlane_LabelSet* theEgrss )
{
    myEgress = theEgrss;
}

//--------------------------------------------------------------------------------
inline CT_TEL_daHz*
TL1_ConnEntParameters::GetExpRate( ) const
{
    return myExpRate;
}

inline void
TL1_ConnEntParameters::SetExpRate( CT_TEL_daHz* theExpRate )
{
   myExpRate = theExpRate;
}

//--------------------------------------------------------------------------------
inline uint8*
TL1_ConnEntParameters::GetGfpTs( ) const
{
    return myGfpTs;
}

inline void
TL1_ConnEntParameters::SetGfpTs( uint8* theGfpTs )
{
   myGfpTs = theGfpTs;
}


//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_ConnEdParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_ConnEdParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_ConnEdParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_ConnEdParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_CallId*    
TL1_ConnEdParameters::GetCallid( ) const
{
    return myCallid;
}


inline void              
TL1_ConnEdParameters::SetCallid( CT_ControlPlane_CallId* theCallid )
{
    myCallid = theCallid;
}

//--------------------------------------------------------------------------------
inline CT_TL1_NodeAddr*                     
TL1_ConnEdParameters::GetNodeAid( ) const
{
    return myNodeAid;
}

inline void                         
TL1_ConnEdParameters::SetNodeAid( CT_TL1_NodeAddr* theNodeAid )
{
    myNodeAid = theNodeAid;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_ConnectionId*                     
TL1_ConnEdParameters::GetConnId( ) const
{
    return myConnId;
}

inline void                         
TL1_ConnEdParameters::SetConnId( CT_ControlPlane_ConnectionId* theConnId )
{
    myConnId = theConnId;
}

//--------------------------------------------------------------------------------
inline bool*                        
TL1_ConnEdParameters::GetIsCommandForced( ) const
{
    return myIsCommandForced;
}

inline void                         
TL1_ConnEdParameters::SetIsCommandForced( bool* theIsCommandForced )
{
    myIsCommandForced = theIsCommandForced;
}
//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_ConnEdParameters::GetPrimaryState( ) const
{
    return myPrimaryState;
}

inline void                         
TL1_ConnEdParameters::SetPrimaryState( CT_SM_PST* thePrimaryState )
{
    myPrimaryState = thePrimaryState;
}



//-----------------------------------------------------------------------------
// RTRV-CONN Parameters
class TL1_ConnRtrvParameters  
{
public:
    
    TL1_ConnRtrvParameters();

    virtual ~TL1_ConnRtrvParameters();

    TL1_ConnRtrvParameters( const TL1_ConnRtrvParameters& theInst );

    TL1_ConnRtrvParameters& operator=( const TL1_ConnRtrvParameters& theInst );

    bool operator==( const TL1_ConnRtrvParameters& theInst ) const;

    inline LT_Handle*                    GetHandle( ) const;
    inline void                          SetHandle( LT_Handle* theHandle );

    inline LT_Ctag                       GetCtag( ) const;
    inline void                          SetCtag( LT_Ctag theCtag );

    inline CT_ControlPlane_CallId*       GetCallId( ) const;
    inline void                          SetCallId( CT_ControlPlane_CallId* theCallId  );

    inline CT_TL1_NodeAddr*              GetNodeAid( ) const;
    inline void                          SetNodeAid( CT_TL1_NodeAddr* theNodeAid );

    inline CT_ControlPlane_ConnectionId* GetConnId( ) const;
    inline void                          SetConnId( CT_ControlPlane_ConnectionId* theConnId );

    inline CT_SM_PST*                    GetEditablePrimaryState( ) const;
    inline void                          SetEditablePrimaryState( CT_SM_PST* theEditablePrimaryState );

    inline CT_SM_SST*                    GetSecondaryState( ) const;
    inline void                          SetSecondaryState( CT_SM_PST* theSecondaryState );


private:

    LT_Handle*                     myHandle;
    LT_Ctag                        myCtag;
    CT_ControlPlane_CallId*        myCallId;
    CT_TL1_NodeAddr*               myNodeAid;
    CT_ControlPlane_ConnectionId*  myConnId;
    CT_SM_PST*                     myEditablePrimaryState;
    CT_SM_SST*                     mySecondaryState;
};

//--------------------------------------------------------------------------------
inline LT_Handle*                   
TL1_ConnRtrvParameters::GetHandle( ) const
{
    return myHandle;
}

inline void                         
TL1_ConnRtrvParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

//--------------------------------------------------------------------------------
inline LT_Ctag                     
TL1_ConnRtrvParameters::GetCtag( ) const
{
    return myCtag;
}

inline void                         
TL1_ConnRtrvParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_CallId*    
TL1_ConnRtrvParameters::GetCallId( ) const
{
    return myCallId;
}


inline void              
TL1_ConnRtrvParameters::SetCallId( CT_ControlPlane_CallId* theCallId )
{
    myCallId = theCallId;
}

//--------------------------------------------------------------------------------
inline CT_TL1_NodeAddr*                     
TL1_ConnRtrvParameters::GetNodeAid( ) const
{
    return myNodeAid;
}

inline void                         
TL1_ConnRtrvParameters::SetNodeAid( CT_TL1_NodeAddr* theNodeAid )
{
    myNodeAid = theNodeAid;
}

//--------------------------------------------------------------------------------
inline CT_ControlPlane_ConnectionId*                     
TL1_ConnRtrvParameters::GetConnId( ) const
{
    return myConnId;
}

inline void                         
TL1_ConnRtrvParameters::SetConnId( CT_ControlPlane_ConnectionId* theConnId )
{
    myConnId = theConnId;
}

//--------------------------------------------------------------------------------
inline CT_SM_PST*                   
TL1_ConnRtrvParameters::GetEditablePrimaryState( ) const
{
    return myEditablePrimaryState;
}

inline void                         
TL1_ConnRtrvParameters::SetEditablePrimaryState( CT_SM_PST* theEditablePrimaryState )
{
    myEditablePrimaryState = theEditablePrimaryState;
}

//--------------------------------------------------------------------------------
inline CT_SM_SST*                   
TL1_ConnRtrvParameters::GetSecondaryState( ) const
{
    return mySecondaryState;
}

inline void                         
TL1_ConnRtrvParameters::SetSecondaryState( CT_SM_PST* theSecondaryState )
{
    mySecondaryState = theSecondaryState;
}



//-----------------------------------------------------------------------------
class TL1_ConnRouteParameters  
{
public:
    
    TL1_ConnRouteParameters();

    virtual ~TL1_ConnRouteParameters();

    TL1_ConnRouteParameters(const TL1_ConnRouteParameters& theInst );

    TL1_ConnRouteParameters& operator=( const TL1_ConnRouteParameters& theInst );

    bool operator==( const TL1_ConnRouteParameters& theInst ) const;

    LT_Handle*               GetHandle( ) const;
    void                     SetHandle( LT_Handle* theHandle );

    LT_Ctag                  GetCtag( ) const;
    void                     SetCtag( LT_Ctag theCtag );

    CT_ControlPlane_CallId*  GetCallId( ) const;
    void                     SetCallId( CT_ControlPlane_CallId* theCallId );

    CT_TL1_NodeAddr*         GetNodeAddr( ) const;
    void                     SetNodeAddr( CT_TL1_NodeAddr* theNodeAddr );

    CT_CallRouteType*        GetCallRouteType( ) const;           
    void                     SetCallRouteType( CT_CallRouteType* theCallRouteType );

    CT_CallPathType*         GetCallPathType( ) const;
    void                     SetCallPathType( CT_CallPathType* theCallPathType ); 

    uint8*                   GetMultiplierValue( ) const;
    void                     SetMultiplierValue( uint8* theMultiplierValue );

private:

    LT_Handle*              myHandle;
    LT_Ctag                 myCtag;
    CT_ControlPlane_CallId* myCallId;
    CT_TL1_NodeAddr*        myNodeAddr;
    CT_CallRouteType*       myCallRouteType;
    CT_CallPathType*        myCallPathType;
    uint8*                  myMultiplier;
};

#endif
