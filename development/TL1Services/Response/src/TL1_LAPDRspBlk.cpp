/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 LAPD Response 
TARGET:
AUTHOR:         July 25, 2006 - Thomas Novak
DESCRIPTION:    Source file for TL1 LPAD Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_LAPDRspBlk.h>

TL1_LAPDRspBlk::TL1_LAPDRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_LAPDRspBlk::TL1_LAPDRspBlk( const TL1_LAPDRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myLapdAddr=         t1Blk.myLapdAddr;

    myProfileAddr=      t1Blk.myProfileAddr;
    myRouterAddr=       t1Blk.myRouterAddr;
    myFlwProtection=    t1Blk.myFlwProtection;
    myChkSumEnable=     t1Blk.myChkSumEnable;
    myHldTmrMult=       t1Blk.myHldTmrMult;
    myConfigTmr=        t1Blk.myConfigTmr;
    myHelloTmr=         t1Blk.myHelloTmr;
    myLMetric=          t1Blk.myLMetric;
    myReDirectHldTmr=   t1Blk.myReDirectHldTmr;
    myRoutingLevel=     t1Blk.myRoutingLevel;
    myEsConfigTmr=      t1Blk.myEsConfigTmr;

    myAlarmProfile=     t1Blk.myAlarmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
}

TL1_LAPDRspBlk::~TL1_LAPDRspBlk( )
{
}

TL1_LAPDRspBlk& 
TL1_LAPDRspBlk::operator=( const TL1_LAPDRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myEntityName=       t1Blk.myEntityName;
    myLapdAddr=         t1Blk.myLapdAddr;

    myProfileAddr=      t1Blk.myProfileAddr;
    myRouterAddr=       t1Blk.myRouterAddr;
    myFlwProtection=    t1Blk.myFlwProtection;
    myChkSumEnable=     t1Blk.myChkSumEnable;
    myHldTmrMult=       t1Blk.myHldTmrMult;
    myConfigTmr=        t1Blk.myConfigTmr;
    myHelloTmr=         t1Blk.myHelloTmr;
    myLMetric=          t1Blk.myLMetric;
    myReDirectHldTmr=   t1Blk.myReDirectHldTmr;
    myRoutingLevel=     t1Blk.myRoutingLevel;
    myEsConfigTmr=      t1Blk.myEsConfigTmr;

    myAlarmProfile=     t1Blk.myAlarmProfile;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;

    return *this;
}

bool 
TL1_LAPDRspBlk::operator==( const TL1_LAPDRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myEntityName != t1Blk.myEntityName )
        return false;

    if ( !(myLapdAddr == t1Blk.myLapdAddr ) )
        return false;

    if ( myProfileAddr != t1Blk.myProfileAddr )
        return false;

    if ( myRouterAddr != t1Blk.myRouterAddr )
        return false;

    if ( myFlwProtection != t1Blk.myFlwProtection )
        return false;

    if ( myChkSumEnable != t1Blk.myChkSumEnable )
        return false;

    if ( myHldTmrMult != t1Blk.myHldTmrMult )
        return false;

    if ( myConfigTmr != t1Blk.myConfigTmr )
        return false;

    if ( myHelloTmr != t1Blk.myHelloTmr )
        return false;

    if ( myLMetric != t1Blk.myLMetric )
        return false;

    if ( myReDirectHldTmr != t1Blk.myReDirectHldTmr )
        return false;

    if ( myRoutingLevel != t1Blk.myRoutingLevel )
        return false;

    if ( myEsConfigTmr != t1Blk.myEsConfigTmr )
        return false;

    if ( myAlarmProfile != t1Blk.myAlarmProfile )
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
TL1_LAPDRspBlk::GetEntityName( string& theEntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        theEntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetEntityName( string& theEntityName )
{
   myBitSet[ INDEX_EntityName ] = true;
   myEntityName = theEntityName;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetLapdAddr( CT_TL1_FacAddr& theLapdAddr ) const
{
    if( true == myBitSet[ INDEX_LapdAddr ] )
    {
        theLapdAddr = myLapdAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetLapdAddr( const CT_TL1_FacAddr& theLapdAddr )
{
    myBitSet[ INDEX_LapdAddr ] = true;
    myLapdAddr = theLapdAddr;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetProfileAddr( CT_LapdProfAddr& theProfileAddr ) const
{
    if( true == myBitSet[ INDEX_ProfileAddr ] )
    {
        theProfileAddr = myProfileAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetProfileAddr( const CT_LapdProfAddr& theProfileAddr )
{
    myBitSet[ INDEX_ProfileAddr ] = true;
    myProfileAddr = theProfileAddr;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetRouterAddr( CT_OSIRtrAddr& theRouterAddr ) const
{
    if( true == myBitSet[ INDEX_RouterAddr ] )
    {
        theRouterAddr = myRouterAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetRouterAddr( const CT_OSIRtrAddr& theRouterAddr )
{
    myBitSet[ INDEX_RouterAddr ] = true;
    myRouterAddr = theRouterAddr;
}
 
//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetFlwProtection( CT_LAPD_FlwProt& theFlwProtection ) const
{
    if( true == myBitSet[ INDEX_FlwProtection ] )
    {
        theFlwProtection = myFlwProtection;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_LAPDRspBlk::SetFlwProtection( const CT_LAPD_FlwProt& theFlwProtection )
{
    myBitSet[ INDEX_FlwProtection ] = true;
    myFlwProtection = theFlwProtection;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetChkSumEnable( CT_LAPD_CheckSum& theChkSumEnable ) const
{
    if( true == myBitSet[ INDEX_ChkSumEnable ] )
    {
        theChkSumEnable = myChkSumEnable;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetChkSumEnable( const CT_LAPD_CheckSum& theChkSumEnable )
{
    myBitSet[ INDEX_ChkSumEnable ] = true;
    myChkSumEnable = theChkSumEnable;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetHldTmrMult( uint16& theHldTmrMult ) const
{
    if( true == myBitSet[ INDEX_HldTmrMult ] )
    {
        theHldTmrMult = myHldTmrMult;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetHldTmrMult( const uint16& theHldTmrMult )
{
    myBitSet[ INDEX_HldTmrMult ] = true;
    myHldTmrMult = theHldTmrMult;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetConfigTmr( uint16& theConfigTmr ) const
{
    if( true == myBitSet[ INDEX_ConfigTmr ] )
    {
        theConfigTmr = myConfigTmr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetConfigTmr( const uint16& theConfigTmr )
{
    myBitSet[ INDEX_ConfigTmr ] = true;
    myConfigTmr = theConfigTmr;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetHelloTmr( uint16& theHelloTmr ) const
{
    if( true == myBitSet[ INDEX_HelloTmr ] )
    {
        theHelloTmr = myHelloTmr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetHelloTmr( const uint16& theHelloTmr )
{
    myBitSet[ INDEX_HelloTmr ] = true;
    myHelloTmr = theHelloTmr;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetLMetric( uint16& theLMetric ) const
{
    if( true == myBitSet[ INDEX_LMetric ] )
    {
        theLMetric = myLMetric;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetLMetric( const uint16& theLMetric )
{
    myBitSet[ INDEX_LMetric ] = true;
    myLMetric = theLMetric;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetReDirectHldTmr( uint16& theReDirectHldTmr ) const
{
    if( true == myBitSet[ INDEX_ReDirectHldTmr ] )
    {
        theReDirectHldTmr = myReDirectHldTmr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetReDirectHldTmr( const uint16& theReDirectHldTmr )
{
    myBitSet[ INDEX_ReDirectHldTmr ] = true;
    myReDirectHldTmr = theReDirectHldTmr;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetRoutingLevel( uint16& theRoutingLevel ) const
{
    if( true == myBitSet[ INDEX_RoutingLevel ] )
    {
        theRoutingLevel = myRoutingLevel;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetRoutingLevel( const uint16& theRoutingLevel )
{
    myBitSet[ INDEX_RoutingLevel ] = true;
    myRoutingLevel = theRoutingLevel;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetEsConfigTmr( uint16& theEsConfigTmr ) const
{
    if( true == myBitSet[ INDEX_EsConfigTmr ] )
    {
        theEsConfigTmr = myEsConfigTmr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetEsConfigTmr( const uint16& theEsConfigTmr )
{
    myBitSet[ INDEX_EsConfigTmr ] = true;
    myEsConfigTmr = theEsConfigTmr;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetPST( CT_SM_PST& thePST ) const
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
TL1_LAPDRspBlk::SetPST( CT_SM_PST& thePST )
{
    myBitSet[ INDEX_PST ] = true;
    myPST = thePST;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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
TL1_LAPDRspBlk::SetPSTQ( CT_SM_PSTQ& thePSTQ )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPSTQ = thePSTQ;
}

//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetSST( CT_SM_SST& theSST ) const
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
TL1_LAPDRspBlk::SetSST( CT_SM_SST& theSST )
{
    myBitSet[ INDEX_SST ] = true;
    mySST = theSST;
}



//--------------------------------------------------------------
bool 
TL1_LAPDRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile ) const
{
    if( true == myBitSet[ INDEX_AlarmProfile ] )
    {
        theAlarmProfile = myAlarmProfile;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LAPDRspBlk::SetAlarmProfile( const CT_ProfileTableId& theAlarmProfile )  
{
    myBitSet[ INDEX_AlarmProfile ]  = true;
    myAlarmProfile = theAlarmProfile;
}

