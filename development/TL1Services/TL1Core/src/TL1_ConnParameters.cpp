/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 30, 2007 - Tong Wu
DESCRIPTION:    Implementation file for Connection TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CONTROLPLANEFAL_H__
#include <TL1Core/TL1_ControlPlaneFal.h>
#endif

#ifndef __TL1_CONNPARAMETERS_H__
#include <TL1Core/TL1_ConnParameters.h>
#endif

TL1_ConnEntParameters::TL1_ConnEntParameters()
{
    myHandle=                           (LT_Handle*)0; 
    myCtag=                             (LT_Ctag)0;
    myCallid=                           (CT_ControlPlane_CallId*)0;
    myNodeAid=                          (CT_TL1_NodeAddr*)0;
    myConnId=                           (CT_ControlPlane_ConnectionId*)0;
    mySignalType=                       (CT_Call_SignalType*)0;
    myMultiplier=                       (uint8*)0;
    myDirection=                        (CT_Call_Directionality*)0;
    myProtection=                       (CT_Conn_ProtectionType*)0;
    myRoute=                            (CT_ControlPlane_Hops*)0;
    myEgress=                           (CT_ControlPlane_LabelSet*)0;

    myEgressTunnelId=                   (uint16*)0;
    myEgressLspId=                      (uint16*)0;
    myEgressExtendedTunnelId=           (uint32*)0;
    myEgressSrcAddr=                    (uint32*)0;
    myIngressTunnelId=                  (uint16*)0;
    myIngressLspId=                     (uint16*)0;
    myIngressExtendedTunnelId=          (uint32*)0;
    myIngressSrcAddr=                   (uint32*)0;

    myE2ESourceAddr=                    (uint32*)0;
    myE2EDestAddr=                      (uint32*)0;
    myE2ETunnelId=                      (uint16*)0;

    myNumOfLabels=                      (uint16*)0;
    myLabelSize=                        (uint8*)0;
    myIfindex=                          (uint32*)0;
    myLabel=                            (uint32*)0;
    myMemberId=                         (uint8*)0;

    myTermCp1P1NodeId=                  (uint32*)0;
    myAssociationId=                    (uint16*)0;

    myReservationStyle=                 (CT_Resv_Style*)0;

    myConnMode=                         (uint8*)0;
    myConnType=                         (uint8*)0;

    myConnRole=                         (CT_CallPathType*)0;
    myConnOperState=                    (CT_Conn_Oper_State*)0;
    myConnStatus=                       (CT_Conn_Status*)0;

    myLastEffort=                       (bool*)0;

    myNumAssocId=                       (uint8*)0;
    myAreaAssocId=                      (uint16*)0;
    myRoutingArea=                      (uint32*)0;
    myAssocType=                        (uint8*)0;

    myExpRate=                          (CT_TEL_daHz*)0;
    myGfpTs=                            (uint8*)0;
}


TL1_ConnEntParameters::TL1_ConnEntParameters(const TL1_ConnEntParameters& theInst )
{
    TL1_ControlPlaneFal::operator=( theInst );
    myHandle=                           theInst.myHandle;    
    myCtag=                             theInst.myCtag;
    myCallid=                           theInst.myCallid;
    myNodeAid=                          theInst.myNodeAid;
    myConnId=                           theInst.myConnId;
    mySignalType=                       theInst.mySignalType;
    myMultiplier=                       theInst.myMultiplier;
    myDirection=                        theInst.myDirection;
    myProtection=                       theInst.myProtection;
    myRoute=                            theInst.myRoute;
    myEgress=                           theInst.myEgress;

    myEgressTunnelId=                   theInst.myEgressTunnelId;
    myEgressLspId=                      theInst.myEgressLspId;
    myEgressExtendedTunnelId=           theInst.myEgressExtendedTunnelId;
    myEgressSrcAddr=                    theInst.myEgressSrcAddr;
    myIngressTunnelId=                  theInst.myIngressTunnelId;
    myIngressLspId=                     theInst.myIngressLspId;
    myIngressExtendedTunnelId=          theInst.myIngressExtendedTunnelId;
    myIngressSrcAddr=                   theInst.myIngressSrcAddr;

    myE2ESourceAddr=                    theInst.myE2ESourceAddr;
    myE2EDestAddr=                      theInst.myE2EDestAddr;
    myE2ETunnelId=                      theInst.myE2ETunnelId;

    myNumOfLabels=                      theInst.myNumOfLabels;
    myLabelSize=                        theInst.myLabelSize;
    myIfindex=                          theInst.myIfindex;
    myLabel=                            theInst.myLabel;
    myMemberId=                         theInst.myMemberId;

    myTermCp1P1NodeId=                  theInst.myTermCp1P1NodeId;
    myAssociationId=                    theInst.myAssociationId;

    myReservationStyle=                 theInst.myReservationStyle;

    myConnMode=                         theInst.myConnMode;
    myConnType=                         theInst.myConnType;

    myReservationStyle=                 theInst.myReservationStyle;

    myConnRole=                         theInst.myConnRole;
    myConnOperState=                    theInst.myConnOperState;
    myConnStatus=                       theInst.myConnStatus;

    myLastEffort=                       theInst.myLastEffort;

    myNumAssocId=                       theInst.myNumAssocId;
    myAreaAssocId=                      theInst.myAreaAssocId;
    myRoutingArea=                      theInst.myRoutingArea;
    myAssocType=                        theInst.myAssocType;

    myExpRate=                          theInst.myExpRate;
    myGfpTs=                            theInst.myGfpTs;
}

TL1_ConnEntParameters::~TL1_ConnEntParameters()
{
}


TL1_ConnEntParameters& 
TL1_ConnEntParameters::operator=( const TL1_ConnEntParameters& theInst )
{
    TL1_ControlPlaneFal::operator=( theInst );
    myHandle=                           theInst.myHandle;    
    myCtag=                             theInst.myCtag;
    myCallid=                           theInst.myCallid;
    myNodeAid=                          theInst.myNodeAid;
    myConnId=                           theInst.myConnId;
    mySignalType=                       theInst.mySignalType;
    myMultiplier=                       theInst.myMultiplier;
    myDirection=                        theInst.myDirection;
    myProtection=                       theInst.myProtection;
    myRoute=                            theInst.myRoute;
    myEgress=                           theInst.myEgress;

    myEgressTunnelId=                   theInst.myEgressTunnelId;
    myEgressLspId=                      theInst.myEgressLspId;
    myEgressExtendedTunnelId=           theInst.myEgressExtendedTunnelId;
    myEgressSrcAddr=                    theInst.myEgressSrcAddr;
    myIngressTunnelId=                  theInst.myIngressTunnelId;
    myIngressLspId=                     theInst.myIngressLspId;
    myIngressExtendedTunnelId=          theInst.myIngressExtendedTunnelId;
    myIngressSrcAddr=                   theInst.myIngressSrcAddr;

    myE2ESourceAddr=                    theInst.myE2ESourceAddr;
    myE2EDestAddr=                      theInst.myE2EDestAddr;
    myE2ETunnelId=                      theInst.myE2ETunnelId;

    myNumOfLabels=                      theInst.myNumOfLabels;
    myLabelSize=                        theInst.myLabelSize;
    myIfindex=                          theInst.myIfindex;
    myLabel=                            theInst.myLabel;
    myMemberId=                         theInst.myMemberId;

    myTermCp1P1NodeId=                  theInst.myTermCp1P1NodeId;
    myAssociationId=                    theInst.myAssociationId;

    myConnMode=                         theInst.myConnMode;
    myConnType=                         theInst.myConnType;

    myReservationStyle=                 theInst.myReservationStyle;

    myConnRole=                         theInst.myConnRole;
    myConnOperState=                    theInst.myConnOperState;
    myConnStatus=                       theInst.myConnStatus;

    myLastEffort=                       theInst.myLastEffort;

    myNumAssocId=                       theInst.myNumAssocId;
    myAreaAssocId=                      theInst.myAreaAssocId;
    myRoutingArea=                      theInst.myRoutingArea;
    myAssocType=                        theInst.myAssocType;

    myExpRate=                          theInst.myExpRate;
    myGfpTs=                            theInst.myGfpTs;

    return *this;
}

bool 
TL1_ConnEntParameters::operator==( const TL1_ConnEntParameters& theInst ) const
{
    if ( !(TL1_ControlPlaneFal::operator==(theInst) ) )
       return false;

    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( !(myCallid == theInst.myCallid) )
        return false;

    if ( myNodeAid != theInst.myNodeAid)
        return false;

    if ( myConnId != theInst.myConnId )
        return false;

    if ( mySignalType != theInst.mySignalType )
         return false;

    if ( myMultiplier != theInst.myMultiplier )
         return false;

    if ( myDirection != theInst.myDirection )
         return false;

    if ( myProtection != theInst.myProtection )
         return false;

    if ( myRoute != theInst.myRoute )
         return false;

    if( myEgress != theInst.myEgress ) 
        return false;

    if ( myEgressTunnelId != theInst.myEgressTunnelId )
        return false;

    if ( myEgressLspId != theInst.myEgressLspId )
        return false;

    if ( myEgressExtendedTunnelId != theInst.myEgressExtendedTunnelId )
        return false;

    if ( myEgressSrcAddr != theInst.myEgressSrcAddr )
        return false;

    if ( myIngressTunnelId != theInst.myIngressTunnelId )
        return false;

    if ( myIngressLspId != theInst.myIngressLspId )
        return false;

    if ( myIngressExtendedTunnelId != theInst.myIngressExtendedTunnelId )
        return false;
    if ( myIngressSrcAddr != theInst.myIngressSrcAddr )
        return false;

    if ( myE2ESourceAddr != theInst.myE2ESourceAddr )
        return false;

    if ( myE2EDestAddr != theInst.myE2EDestAddr )
        return false;

    if ( myE2ETunnelId != theInst.myE2ETunnelId )
        return false;

    if ( myNumOfLabels != theInst.myNumOfLabels )
        return false;

    if ( myLabelSize != theInst.myLabelSize )
        return false;

    if ( myIfindex != theInst.myIfindex )
        return false;

    if ( myLabel != theInst.myLabel )
        return false;

    if ( myTermCp1P1NodeId != theInst.myTermCp1P1NodeId )
        return false;

    if ( myAssociationId != theInst.myAssociationId )
        return false;

    if ( myConnMode != theInst.myConnMode )
        return false;

    if ( myConnType != theInst.myConnType )
        return false;

    if ( myReservationStyle != theInst.myReservationStyle )
        return false;

    if ( myConnRole != theInst.myConnRole )
        return false;

    if ( myConnOperState != theInst.myConnOperState )
        return false;

    if ( myConnStatus != theInst.myConnStatus )
        return false;

    if ( myLastEffort != theInst.myLastEffort )
        return false;

    if ( myNumAssocId != theInst.myNumAssocId )
        return false;

    if ( myAreaAssocId != theInst.myAreaAssocId )
        return false;

    if ( myRoutingArea != theInst.myRoutingArea )
        return false;

    if ( myAssocType != theInst.myAssocType )
        return false;

    if ( myExpRate != theInst.myExpRate )
        return false;

    if ( myGfpTs != theInst.myGfpTs)
        return false;

    return true;
}



//-----------------------------------------------------------------------------------
TL1_ConnEdParameters::TL1_ConnEdParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myCallid=           (CT_ControlPlane_CallId*)0;
    myNodeAid=          (CT_TL1_NodeAddr*)0;
    myConnId=           (CT_ControlPlane_ConnectionId*)0;
    myIsCommandForced=  (bool*)0;
    myPrimaryState=     (CT_SM_PST*)0;
}

TL1_ConnEdParameters::TL1_ConnEdParameters(const TL1_ConnEdParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myCallid=           theInst.myCallid;
    myNodeAid=          theInst.myNodeAid;
    myConnId=           theInst.myConnId;
    myIsCommandForced=  theInst.myIsCommandForced;
    myPrimaryState=     theInst.myPrimaryState;
}

TL1_ConnEdParameters::~TL1_ConnEdParameters()
{
}

TL1_ConnEdParameters& 
TL1_ConnEdParameters::operator=( const TL1_ConnEdParameters& theInst )
{
    myHandle=           theInst.myHandle;    
    myCtag=             theInst.myCtag;
    myCallid=           theInst.myCallid;
    myNodeAid=          theInst.myNodeAid;
    myConnId=           theInst.myConnId;
    myIsCommandForced=  theInst.myIsCommandForced;
    myPrimaryState=     theInst.myPrimaryState;

    return *this;
}

bool 
TL1_ConnEdParameters::operator==( const TL1_ConnEdParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( !(myCallid == theInst.myCallid) )
        return false;

    if ( myNodeAid != theInst.myNodeAid)
        return false;

    if ( myConnId != theInst.myConnId )
        return false;

    if ( myIsCommandForced != theInst.myIsCommandForced )
        return false;

    if ( myPrimaryState != theInst.myPrimaryState )
        return false;
        
    return true;
}



//-----------------------------------------------------------------------------------
// RTRV-CONN Parameters
TL1_ConnRtrvParameters::TL1_ConnRtrvParameters( )
    :myHandle( (LT_Handle*)0 )
    ,myCtag( (LT_Ctag)0 )
    ,myCallId( (CT_ControlPlane_CallId*)0 )
    ,myNodeAid( (CT_TL1_NodeAddr*)0 )
    ,myConnId( (CT_ControlPlane_ConnectionId*)0 )
    ,myEditablePrimaryState( (CT_SM_PST*)0 )
    ,mySecondaryState( (CT_SM_SST*)0 )
{
}


TL1_ConnRtrvParameters::TL1_ConnRtrvParameters( const TL1_ConnRtrvParameters& theInst )
{
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myCallId=               theInst.myCallId;
    myNodeAid=              theInst.myNodeAid;
    myConnId=               theInst.myConnId;
    myEditablePrimaryState= theInst.myEditablePrimaryState;
    mySecondaryState=       theInst.mySecondaryState;
}

TL1_ConnRtrvParameters::~TL1_ConnRtrvParameters()
{
}


TL1_ConnRtrvParameters& 
TL1_ConnRtrvParameters::operator=( const TL1_ConnRtrvParameters& theInst )
{
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myCallId=               theInst.myCallId;
    myNodeAid=              theInst.myNodeAid;
    myConnId=               theInst.myConnId;
    myEditablePrimaryState= theInst.myEditablePrimaryState;
    mySecondaryState=       theInst.mySecondaryState;

    return *this;
}


bool 
TL1_ConnRtrvParameters::operator==( const TL1_ConnRtrvParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( !(myCallId == theInst.myCallId) )
        return false;

    if ( myNodeAid != theInst.myNodeAid)
        return false;

    if ( myConnId != theInst.myConnId )
        return false;

    if ( myEditablePrimaryState != theInst.myEditablePrimaryState )
        return false;

    if ( mySecondaryState != theInst.mySecondaryState )
        return false;
        
    return true;
}



TL1_ConnRouteParameters::TL1_ConnRouteParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myCallId=           (CT_ControlPlane_CallId*)0;
    myNodeAddr=         (CT_TL1_NodeAddr*)0;
    myCallRouteType=    (CT_CallRouteType*)0;
    myCallPathType=     (CT_CallPathType*)0;
    myMultiplier=       (uint8*)0;
}

TL1_ConnRouteParameters::~TL1_ConnRouteParameters()
{
}

TL1_ConnRouteParameters::TL1_ConnRouteParameters(const TL1_ConnRouteParameters& theInst )
{
    myHandle=           theInst.myHandle;
    myCtag=             theInst.myCtag;
    myCallId=           theInst.myCallId;
    myNodeAddr=         theInst.myNodeAddr;
    myCallRouteType=    theInst.myCallRouteType;
    myCallPathType=     theInst.myCallPathType;
    myMultiplier=       theInst.myMultiplier;
}

TL1_ConnRouteParameters& 
TL1_ConnRouteParameters::operator=( const TL1_ConnRouteParameters& theInst )
{
    myHandle=           theInst.myHandle;
    myCtag=             theInst.myCtag;
    myCallId=           theInst.myCallId;
    myNodeAddr=         theInst.myNodeAddr;
    myCallRouteType=    theInst.myCallRouteType;
    myCallPathType=     theInst.myCallPathType;
    myMultiplier=       theInst.myMultiplier;

    return *this;
}

bool TL1_ConnRouteParameters::operator==( const TL1_ConnRouteParameters& theInst ) const
{
    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myCallId != theInst.myCallId )
        return false;

    if ( myNodeAddr != theInst.myNodeAddr )
        return false;

    if ( myCallRouteType != theInst.myCallRouteType )
        return false;

    if ( myCallPathType != theInst.myCallPathType )
        return false;

    if ( myMultiplier != theInst.myMultiplier )
        return false;

    return true;
}

LT_Handle*                   
TL1_ConnRouteParameters::GetHandle( ) const
{
    return myHandle;
}

void                         
TL1_ConnRouteParameters::SetHandle( LT_Handle* theHandle )
{
    myHandle = theHandle;
}

LT_Ctag                     
TL1_ConnRouteParameters::GetCtag( ) const
{
    return myCtag;
}

void                         
TL1_ConnRouteParameters::SetCtag( LT_Ctag theCtag )
{
    myCtag = theCtag;
}

CT_ControlPlane_CallId*    
TL1_ConnRouteParameters::GetCallId( ) const
{
    return myCallId;
}

void              
TL1_ConnRouteParameters::SetCallId( CT_ControlPlane_CallId* theCallId )
{
    myCallId = theCallId;
}

CT_TL1_NodeAddr*    
TL1_ConnRouteParameters::GetNodeAddr( ) const
{
    return myNodeAddr;
}

void                         
TL1_ConnRouteParameters::SetNodeAddr( CT_TL1_NodeAddr* theNodeAddr )
{
    myNodeAddr = theNodeAddr;
}

CT_CallRouteType*        
TL1_ConnRouteParameters::GetCallRouteType( ) const
{
    return myCallRouteType;
}

void                     
TL1_ConnRouteParameters::SetCallRouteType( CT_CallRouteType* theCallRouteType )
{
    myCallRouteType = theCallRouteType;
}

CT_CallPathType*         
TL1_ConnRouteParameters::GetCallPathType( ) const
{
    return myCallPathType;
}

void                     
TL1_ConnRouteParameters::SetCallPathType( CT_CallPathType* theCallPathType )
{
    myCallPathType = theCallPathType;
}

uint8*                  
TL1_ConnRouteParameters::GetMultiplierValue( ) const
{
    return myMultiplier;
}

void                         
TL1_ConnRouteParameters::SetMultiplierValue( uint8* theMultiplierValue )
{
    myMultiplier = theMultiplierValue;
}

