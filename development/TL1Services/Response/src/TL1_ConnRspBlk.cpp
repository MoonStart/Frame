/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Conn Response 
TARGET:
AUTHOR:         May 30, 2007 - Tong Wu
DESCRIPTION:    Source file for TL1 Connection Response class 
-----------------------------------------------------------------------------*/

#include <CommonTypes/CT_ControlPlane_Convert.h>
#include <Response/TL1_ConnRspBlk.h>

TL1_ConnRspBlk::TL1_ConnRspBlk( ) :
    myBitSet( INDEX_END, false ) 
{
    //Initialize variables to clear coverity errors.
    myConnMode =        (CT_ConnMode)0;
    myConnRole =        (CT_CallPathType)0;
    myDirectionality =  (CT_Call_Directionality)0;
    myMultiplierValue = 0;
    myPST =             (CT_SM_PST)0;
    myPSTQ =            (CT_SM_PSTQ)0;
    mySST =             (CT_SM_SST)0;
    myProtectionType =  (CT_Conn_ProtectionType)0;
    myReservationStyle =(CT_Resv_Style)0;
    mySignalType =      (CT_Call_SignalType)0;
}

TL1_ConnRspBlk::TL1_ConnRspBlk( 
    const CT_ControlPlane_CallId        theCallId,
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
    const CT_SM_SST*                    theSST )

    :myBitSet( INDEX_END, false )
{

    myBitSet[ INDEX_CallId ] = true;
    myCallId = theCallId;

    myBitSet[ INDEX_NodeAid ] = true;
    myNodeAid = theNodeAid;

    myBitSet[ INDEX_ConnId ] = true;
    myConnId = theConnId;

    if( &theSignalType )
    {
        myBitSet[ INDEX_SigType ] = true;
        mySignalType = theSignalType;
    }
    
    if( &theMultiplierValue )
    {
        myBitSet[ INDEX_Multiple ] = true;
        myMultiplierValue = theMultiplierValue;
    }

    if( &theDirectionality )
    {
        myBitSet[ INDEX_Direction ] = true;
        myDirectionality = theDirectionality;
    }

    if( &theProtectionType )
    {
        myBitSet[ INDEX_ProtType ] = true;
        myProtectionType = theProtectionType;
    }

    myBitSet[ INDEX_ConnMode ] = true;
    myConnMode = theConnMode;

    if(theConnRole)
    {
        myBitSet[ INDEX_ConnRole ] = true;
        myConnRole = *theConnRole;
    }
    else
    {
        myConnRole = (CT_CallPathType)0;
    }

    if( theEtoESessionId )
    {
        myBitSet[ INDEX_EtoESessionId ] = true;
        myEtoESessionId = *theEtoESessionId;
    }

    myBitSet[ INDEX_ReservationStyle ] = true;
    myReservationStyle = theReservationStyle;

    if ( thePST )
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }
    else
    {
        myPST = (CT_SM_PST)0;
    }

    if ( thePSTQ )
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
    else
    {
        myPSTQ = (CT_SM_PSTQ)0;
    }

    if ( theSST )
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
    else
    {
        mySST = (CT_SM_SST)0;
    }
}


TL1_ConnRspBlk::TL1_ConnRspBlk( const TL1_ConnRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myCallId=           t1Blk.myCallId;
    myNodeAid=          t1Blk.myNodeAid;
    myConnId=           t1Blk.myConnId;
    mySignalType=       t1Blk.mySignalType;
    myMultiplierValue=  t1Blk.myMultiplierValue;
    myDirectionality=   t1Blk.myDirectionality;    
    myProtectionType=   t1Blk.myProtectionType;
    myConnMode=         t1Blk.myConnMode;
    myConnRole=         t1Blk.myConnRole;
    myEtoESessionId=    t1Blk.myEtoESessionId;
    myReservationStyle= t1Blk.myReservationStyle;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_ConnRspBlk::~TL1_ConnRspBlk( )
{
}

TL1_ConnRspBlk& 
TL1_ConnRspBlk::operator=( const TL1_ConnRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myCallId=           t1Blk.myCallId;
    myNodeAid=          t1Blk.myNodeAid;
    myConnId=           t1Blk.myConnId;
    mySignalType=       t1Blk.mySignalType;
    myMultiplierValue=  t1Blk.myMultiplierValue;
    myDirectionality=   t1Blk.myDirectionality;    
    myProtectionType=   t1Blk.myProtectionType;
    myConnMode=         t1Blk.myConnMode;
    myConnRole=         t1Blk.myConnRole;
    myEtoESessionId=    t1Blk.myEtoESessionId;
    myReservationStyle= t1Blk.myReservationStyle;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_ConnRspBlk::operator==( const TL1_ConnRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myCallId != t1Blk.myCallId )
        return false;

    if ( myNodeAid != t1Blk.myNodeAid )
        return false;

    if ( myConnId != t1Blk.myConnId )
        return false;

    if ( mySignalType != t1Blk.mySignalType )
        return false;

    if ( myMultiplierValue != t1Blk.myMultiplierValue )
        return false;

    if ( myDirectionality != t1Blk.myDirectionality )
        return false;

    if ( myProtectionType != t1Blk.myProtectionType )
        return false;

    if ( myConnMode != t1Blk.myConnMode )
        return false;

    if ( myConnRole != t1Blk.myConnRole )
        return false;

    if ( myEtoESessionId != t1Blk.myEtoESessionId )
        return false;

    if ( myReservationStyle != t1Blk.myReservationStyle )
        return false;

    if ( myPST != t1Blk.myPST )
        return false;

    if ( myPSTQ != t1Blk.myPSTQ )
        return false;

    if ( mySST != t1Blk.mySST )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetCallId( CT_ControlPlane_CallId& theCallId ) const
{
    if( true == myBitSet[ INDEX_CallId ] )
    {
        theCallId = myCallId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetCallId( const CT_ControlPlane_CallId& theCallId )
{
   myBitSet[ INDEX_CallId ] = true;
   myCallId = theCallId;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetNodeAid( CT_TL1_NodeAddr& theNodeAid ) const
{
    if( true == myBitSet[ INDEX_NodeAid ] )
    {
        theNodeAid = myNodeAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetNodeAid( const CT_TL1_NodeAddr& theNodeAid )
{
    myBitSet[ INDEX_NodeAid ] = true;
    myNodeAid= theNodeAid;
}

//-----------------------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetConnId( CT_ControlPlane_ConnectionId& theConnId ) const
{
    if( true == myBitSet[ INDEX_ConnId ] )
    {
        theConnId = myConnId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetConnId( const CT_ControlPlane_ConnectionId& theConnId )
{
   myBitSet[ INDEX_ConnId ] = true;
   myConnId = theConnId;
}


//-----------------------------------------------------------------------------
// Primary State
bool 
TL1_ConnRspBlk::GetPST( CT_SM_PST& thePST ) const
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        thePST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetPST( const CT_SM_PST& thePST )  
{
    myBitSet[ INDEX_PST ] = true; 
    myPST = thePST;
}


//-----------------------------------------------------------------------------
// Primary State Qualifier
bool 
TL1_ConnRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        thePSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetPSTQ( const CT_SM_PSTQ& thePSTQ )  
{
    myBitSet[ INDEX_PSTQ ] = true; 
    myPSTQ = thePSTQ;
}


//-----------------------------------------------------------------------------
// Secondary State
bool 
TL1_ConnRspBlk::GetSST( CT_SM_SST& theSST ) const
{
    if( true == myBitSet[ INDEX_SST ] )
    {
        theSST = mySST;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetSST( const CT_SM_SST& theSST )  
{
    myBitSet[ INDEX_SST ] = true; 
    mySST = theSST;
}


//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetSignalType( CT_Call_SignalType& theSignalType ) const
{
    if( true == myBitSet[ INDEX_SigType ] )
    {
        theSignalType = mySignalType;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_ConnRspBlk::SetSignalType( const CT_Call_SignalType& theSignalType )
{
    myBitSet[ INDEX_SigType ] = true;
    mySignalType = theSignalType;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetMultiple( uint8& theMultiplierValue ) const
{
    if( true == myBitSet[ INDEX_Multiple ] )
    {
        theMultiplierValue = myMultiplierValue;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetMultiple( const uint8& theMultiplierValue )
{
    myBitSet[ INDEX_Multiple ] = true;
    myMultiplierValue = theMultiplierValue;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetDirection( CT_Call_Directionality& theDirectionality ) const
{
    if( true == myBitSet[ INDEX_Direction ] )
    {
        theDirectionality = myDirectionality;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetDirection( const CT_Call_Directionality& theDirectionality )
{
    myBitSet[ INDEX_Direction ] = true;
    myDirectionality= theDirectionality;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetProtType( CT_Conn_ProtectionType& theProtectionType ) const
{
    if( true == myBitSet[ INDEX_ProtType ] )
    {
        theProtectionType = myProtectionType;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_ConnRspBlk::SetProtType( const CT_Conn_ProtectionType& theProtectionType )
{
    myBitSet[ INDEX_ProtType ] = true;
    myProtectionType = theProtectionType;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetConnMode( CT_ConnMode& theConnMode ) const
{
    if( true == myBitSet[ INDEX_ConnMode ] )
    {
        theConnMode = myConnMode;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetConnMode( const CT_ConnMode& theConnMode )
{
   myBitSet[ INDEX_ConnMode ] = true;
   myConnMode = theConnMode;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetConnRole( CT_CallPathType& theConnRole ) const
{
    if( true == myBitSet[ INDEX_ConnRole ] )
    {
        theConnRole = myConnRole;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetConnRole( const CT_CallPathType& theConnRole )
{
   myBitSet[ INDEX_ConnRole ] = true;
   myConnRole = theConnRole;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetEtoESessionId( CT_E2E_SessionId& theEtoESessionId ) const
{
    if( true == myBitSet[ INDEX_EtoESessionId ] )
    {
        theEtoESessionId = myEtoESessionId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetEtoESessionId( const CT_E2E_SessionId& theEtoESessionId )
{
   myBitSet[ INDEX_EtoESessionId ] = true;
   myEtoESessionId = theEtoESessionId;
}

//--------------------------------------------------------------
bool 
TL1_ConnRspBlk::GetReservationStyle( CT_Resv_Style& theReservationStyle ) const
{
    if( true == myBitSet[ INDEX_ReservationStyle ] )
    {
        theReservationStyle = myReservationStyle;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRspBlk::SetReservationStyle( const CT_Resv_Style& theReservationStyle )
{
   myBitSet[ INDEX_ReservationStyle ] = true;
   myReservationStyle = theReservationStyle;
}



//---------------------------------------------------------------------------------------
TL1_ConnInfoRspBlk::TL1_ConnInfoRspBlk( ) :
    myBitSet( INDEX_END, false ),
    myMtNumber(0),
    myConnMode(CT_ConnMode_Unknown),
    myConnPath(CT_CallPathType_ALL)
{

}

TL1_ConnInfoRspBlk::~TL1_ConnInfoRspBlk()
{
}

TL1_ConnInfoRspBlk& 
TL1_ConnInfoRspBlk::operator=( const TL1_ConnInfoRspBlk& t1Blk )
{

    myCallId        = t1Blk.myCallId;
    myNodeAid       = t1Blk.myNodeAid;
    myConnId        = t1Blk.myConnId;
    myMtNumber      = t1Blk.myMtNumber;
    myResourceList  = t1Blk.myResourceList;
    myConnMode      = t1Blk.myConnMode;
    myConnPath      = t1Blk.myConnPath;

    return *this;
}

bool 
TL1_ConnInfoRspBlk::operator==( const TL1_ConnInfoRspBlk& t1Blk ) const
{
    if ( myCallId != t1Blk.myCallId )
        return false;

    if ( myNodeAid != t1Blk.myNodeAid )
        return false;

    if ( myConnId != t1Blk.myConnId )
        return false;

    if ( myMtNumber != t1Blk.myMtNumber )
        return false;

    if ( myResourceList != t1Blk.myResourceList )
        return false;

    if ( !( myConnMode == t1Blk.myConnMode ) )
        return false;

    if ( !(myConnPath == t1Blk.myConnPath) )
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_ConnInfoRspBlk::GetCallId( CT_ControlPlane_CallId& theCallId ) const
{
    if( true == myBitSet[ INDEX_CallId ] )
    {
        theCallId = myCallId;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_ConnInfoRspBlk::SetCallId( const CT_ControlPlane_CallId& theCallId )
{
    myBitSet[ INDEX_CallId ] = true;
    myCallId = theCallId;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnInfoRspBlk::GetNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const
{
    if( true == myBitSet[ INDEX_Node ] )
    {
        theNodeAid = myNodeAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnInfoRspBlk::SetNodeAddr( const CT_TL1_NodeAddr& theNodeAid )
{
    myBitSet[ INDEX_Node ] = true;
    myNodeAid = theNodeAid;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_ConnInfoRspBlk::GetConnId( CT_ControlPlane_ConnectionId& theConnId ) const
{
    if( true == myBitSet[ INDEX_ConnId ] )
    {
        theConnId = myConnId;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_ConnInfoRspBlk::SetConnId( const CT_ControlPlane_ConnectionId& theConnId )
{
    myBitSet[ INDEX_ConnId ] = true;
    myConnId = theConnId;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnInfoRspBlk::GetMtNumber( int& theMtNumber ) const
{
    if( true == myBitSet[ INDEX_MtNumber ] )
    {
        theMtNumber = myMtNumber;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnInfoRspBlk::SetMtNumber( const int& theMtNumber )
{
    myBitSet[ INDEX_MtNumber ] = true;
    myMtNumber = theMtNumber;
}

//-------------------------------------------------------------------------------------------------------
bool
TL1_ConnInfoRspBlk::GetResourceList( list<string>& theResourceList ) const
{
    if( true == myBitSet[ INDEX_Resource ] )
    {
        theResourceList = myResourceList;
        return true;
    }
    return false;
}

void
TL1_ConnInfoRspBlk::SetResource( const string& theResource )
{
    myBitSet[ INDEX_Resource ] = true;
    myResourceList.push_back( theResource );
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_ConnInfoRspBlk::GetConnMode( CT_ConnMode& theConnMode) const
{
    if( true == myBitSet[ INDEX_ConnMode ] )
    {
        theConnMode = myConnMode;
        return true;
    }
    return false;
}

void  
TL1_ConnInfoRspBlk::SetConnMode( const CT_ConnMode& theConnMode)
{
    myBitSet[ INDEX_ConnMode ] = true;
    myConnMode = theConnMode;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_ConnInfoRspBlk::GetConnPath( CT_CallPathType& theConnPath) const
{
    if( true == myBitSet[ INDEX_ConnPath ] )
    {
        theConnPath = myConnPath;
        return true;
    }
	return false;
}

void  
TL1_ConnInfoRspBlk::SetConnPath( const CT_CallPathType& theConnPath)
{
    myBitSet[ INDEX_ConnPath ] = true;
    myConnPath = theConnPath;
}


//-------------------------------------------------------------------------------------------------------
TL1_ConnRouteRspBlk::TL1_ConnRouteRspBlk( ) :
    myBitSet( INDEX_END, false ),
    myMtNumber( 0 )
{
}

TL1_ConnRouteRspBlk::~TL1_ConnRouteRspBlk( )
{
}

TL1_ConnRouteRspBlk& 
TL1_ConnRouteRspBlk::operator=( const TL1_ConnRouteRspBlk& t1Blk )
{
    myCallId=       t1Blk.myCallId;
    myAEnd=         t1Blk.myAEnd;
    myZend=         t1Blk.myZend;
    myNodeAid=      t1Blk.myNodeAid;
    myConnId=       t1Blk.myConnId;
    myWorkingEro=   t1Blk.myWorkingEro;
    myProtectEro=   t1Blk.myProtectEro;
    myWorkingRro=   t1Blk.myWorkingRro;
    myProtectRro=   t1Blk.myProtectRro;  

    return *this;
}

bool 
TL1_ConnRouteRspBlk::operator==( const TL1_ConnRouteRspBlk& t1Blk ) const
{
    if ( myCallId != t1Blk.myCallId )
        return false;

    if ( myAEnd != t1Blk.myAEnd )
        return false;

    if ( myZend != t1Blk.myZend )
        return false;

    if ( myNodeAid != t1Blk.myNodeAid )
        return false;

    if ( myConnId != t1Blk.myConnId )
        return false;

    if ( myWorkingEro != t1Blk.myWorkingEro )
        return false;

    if ( myProtectEro != t1Blk.myProtectEro )
        return false;

    if ( myWorkingRro != t1Blk.myWorkingRro )
        return false;

    if ( myProtectRro != t1Blk.myProtectRro )
        return false;

    return true;
}
//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetCallId( CT_ControlPlane_CallId& theCallId ) const
{
    if( true == myBitSet[ INDEX_CallId ] )
    {
        theCallId = myCallId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetCallId( const CT_ControlPlane_CallId& theCallId )
{
    myBitSet[ INDEX_CallId ] = true;
    myCallId = theCallId;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetaEndPoint( CT_ControlPlane_TNA& theAEnd ) const
{
    if( true == myBitSet[ INDEX_Aend ] )
    {
        theAEnd = myAEnd;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetaEndPoint( const CT_ControlPlane_TNA& theAEnd )
{
    myBitSet[ INDEX_Aend ] = true;
    myAEnd = theAEnd;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetzEndPoint( CT_ControlPlane_TNA& theZend ) const
{
    if( true == myBitSet[ INDEX_Zend ] )
    {
        theZend = myZend;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetzEndPoint( const CT_ControlPlane_TNA& theZend )
{
    myBitSet[ INDEX_Zend ] = true;
    myZend = theZend;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const
{
    if( true == myBitSet[ INDEX_Node ] )
    {
        theNodeAid = myNodeAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetNodeAddr( const CT_TL1_NodeAddr& theNodeAid )
{
    myBitSet[ INDEX_ConnId ] = true;
    myNodeAid = theNodeAid;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetConnId( CT_ControlPlane_ConnectionId& theConnId ) const
{
    if( true == myBitSet[ INDEX_ConnId ] )
    {
        theConnId = myConnId;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetConnId( CT_ControlPlane_ConnectionId& theConnId )
{
    myBitSet[ INDEX_Node ] = true;
    myConnId = theConnId;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetWorkingEro( CT_ControlPlane_Hops& theWorkingEro ) const
{
    if( true == myBitSet[ INDEX_WorkingEro ] )
    {
        theWorkingEro = myWorkingEro;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetWorkingEro( const CT_ControlPlane_Hops& theWorkingEro )
{
    myBitSet[ INDEX_WorkingEro ] = true;
    myWorkingEro = theWorkingEro;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetProtectEro( CT_ControlPlane_Hops& theProtectEro ) const
{
    if( true == myBitSet[ INDEX_ProtectEro ] )
    {
        theProtectEro = myProtectEro;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetProtectEro( const CT_ControlPlane_Hops& theProtectEro )
{
    myBitSet[ INDEX_ProtectEro ] = true;
    myProtectEro = theProtectEro;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetWorkingRro( CT_ControlPlane_Hops& theWorkingRro ) const
{
    if( true == myBitSet[ INDEX_WorkingRro ] )
    {
        theWorkingRro = myWorkingRro;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetWorkingRro( const CT_ControlPlane_Hops& theWorkingRro )
{
    myBitSet[ INDEX_WorkingRro ] = true;
    myWorkingRro = theWorkingRro;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetProtectRro( CT_ControlPlane_Hops& theProtectRro ) const
{
    if( true == myBitSet[ INDEX_ProtectRro ] )
    {
        theProtectRro = myProtectRro;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetProtectRro( const CT_ControlPlane_Hops& theProtectRro )
{
    myBitSet[ INDEX_ProtectRro ] = true;
    myProtectRro = theProtectRro;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_ConnRouteRspBlk::GetMtNumber( int& theMtNumber ) const
{
    if( true == myBitSet[ INDEX_MtNumber ] )
    {
        theMtNumber = myMtNumber;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_ConnRouteRspBlk::SetMtNumber( const int& theMtNumber )
{
    myBitSet[ INDEX_MtNumber ] = true;
    myMtNumber = theMtNumber;
}

