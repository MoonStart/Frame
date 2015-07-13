/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      Software Services
TARGET:          
AUTHOR:         May 07, 2007 - Tong Wu
DESCRIPTION:    Implementation file for CALL TL1 ENT Parameters class
-----------------------------------------------------------------------------*/ 
#ifdef WIN32 // Microsoft bug; identifier that exceeds 255 chars gets truncated
    #pragma warning(disable:4786)
#endif

#ifndef __TL1_CALLPARAMETERS_H__
#include <TL1Core/TL1_CallParameters.h>
#endif



TL1_CallEntParameters::TL1_CallEntParameters()
{
    myHandle=           (LT_Handle*)0;
    myCtag=             (LT_Ctag)0;
    myAEnd=             (CT_ControlPlane_TNA*)0;
    myZEnd=             (CT_ControlPlane_TNA*)0;
    myNodeAddr=         (CT_TL1_NodeAddr*)0;
    myAEnd2=            (CT_ControlPlane_TNA*)0;
    myZEnd2=            (CT_ControlPlane_TNA*)0;
    myNodeId2=          (uint32*)0;
    mySignalType=       (CT_Call_SignalType*)0;
    myMultiplier=       (uint8*)0;
    myIngrss=           (CT_ControlPlane_LabelSet*)0;
    myEgrss=            (CT_ControlPlane_LabelSet*)0;
    myIngrss2=          (CT_ControlPlane_LabelSet*)0;
    myEgrss2=           (CT_ControlPlane_LabelSet*)0;
    myDirection=        (CT_Call_Directionality*)0;
    mySrlg=             (CT_ControlPlane_Srlg*)0;
    myTimeout=          (uint16*)0;
    myCallId=           (CT_ControlPlane_CallId*)0;
    myCallName=         (string*)0;
    myCallOperState=    (CT_Call_Oper_State*)0;
    myCallStatus=       (CT_Call_Status*)0;
    mySlpf=             (CT_TL1_LogicalAddr*)0;
    myProtLvl=          (CT_SLPF_ProtLvl*)0;
    myWorkingPath=      (CT_TL1_ExppathAddr*)0;
    myProtectPath=      (CT_TL1_ExppathAddr*)0;
    myLabelSet=         (CT_TL1_LabelSetAddr*)0;
    myPriority=         (CT_SLPF_PRIORITY*)0;
    myLocation=         (CT_Call_Location*)0;
    myWkgPrp1=          (CT_TL1_ExppathAddr*)0;
    myWkgPrp2=          (CT_TL1_ExppathAddr*)0;
    myProtPrp1=         (CT_TL1_ExppathAddr*)0;
    myProtPrp2=         (CT_TL1_ExppathAddr*)0;
    myCompWkgPrp1=      (bool*)0;
    myCompProtPrp1=     (bool*)0;
    myCallNumber=       (CT_TL1_CallNumber*)0;
    myExpRate=          (CT_TEL_daHz*)0;
    myGfpTs=            (uint8*)0;
    myWkgXPath=         (CT_TL1_ExdpathAddr*)0;
    myProtXPath=        (CT_TL1_ExdpathAddr*)0;
    myCallRetainPath=   (CT_CallRetainPath*)0;
}

TL1_CallEntParameters::TL1_CallEntParameters(const TL1_CallEntParameters& theInst )
{
    TL1_ControlPlaneFal::operator=( theInst );
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myAEnd=                 theInst.myAEnd;
    myZEnd=                 theInst.myZEnd;
    myAEnd2=                theInst.myAEnd2;
    myZEnd2=                theInst.myZEnd2;
    myNodeId2=              theInst.myNodeId2;
    myNodeAddr=             theInst.myNodeAddr;
    mySignalType=           theInst.mySignalType;
    myMultiplier=           theInst.myMultiplier;
    myIngrss=               theInst.myIngrss;
    myEgrss=                theInst.myEgrss;
    myIngrss2=              theInst.myIngrss2;
    myEgrss2=               theInst.myEgrss2;
    myDirection=            theInst.myDirection;
    mySrlg=                 theInst.mySrlg;
    myTimeout=              theInst.myTimeout;
    myCallId=               theInst.myCallId;
    myCallName=             theInst.myCallName;         
    myCallOperState=        theInst.myCallOperState;
    myCallStatus=           theInst.myCallStatus;
    mySlpf=                 theInst.mySlpf;
    myProtLvl=              theInst.myProtLvl;
    myWorkingPath=          theInst.myWorkingPath;
    myProtectPath=          theInst.myProtectPath;
    myLabelSet=             theInst.myLabelSet;
    myPriority=             theInst.myPriority;
    myLocation=             theInst.myLocation;
    myWkgPrp1=              theInst.myWkgPrp1;
    myWkgPrp2=              theInst.myWkgPrp2;
    myProtPrp1=             theInst.myProtPrp1;
    myProtPrp2=             theInst.myProtPrp2;
    myCompWkgPrp1=          theInst.myCompWkgPrp1;
    myCompProtPrp1=         theInst.myCompProtPrp1;
    myCallNumber=           theInst.myCallNumber;
    myExpRate=              theInst.myExpRate;
    myGfpTs=                theInst.myGfpTs;
    myWkgXPath=             theInst.myWkgXPath;
    myProtXPath=            theInst.myProtXPath;
    myCallRetainPath=       theInst.myCallRetainPath;
}

TL1_CallEntParameters::~TL1_CallEntParameters()
{
}

TL1_CallEntParameters& 
TL1_CallEntParameters::operator=( const TL1_CallEntParameters& theInst )
{
    TL1_ControlPlaneFal::operator=( theInst );
    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myAEnd=                 theInst.myAEnd;
    myZEnd=                 theInst.myZEnd;
    myNodeAddr=             theInst.myNodeAddr;
    myAEnd2=                theInst.myAEnd2;
    myZEnd2=                theInst.myZEnd2;
    myNodeId2=              theInst.myNodeId2;
    mySignalType=           theInst.mySignalType;
    myMultiplier=           theInst.myMultiplier;
    myIngrss=               theInst.myIngrss;
    myEgrss=                theInst.myEgrss;
    myDirection=            theInst.myDirection;
    mySrlg=                 theInst.mySrlg;
    myTimeout=              theInst.myTimeout;
    myCallId=               theInst.myCallId;
    myCallName=             theInst.myCallName;         
    myCallOperState=        theInst.myCallOperState;
    myCallStatus=           theInst.myCallStatus;
    mySlpf=                 theInst.mySlpf;
    myProtLvl=              theInst.myProtLvl;
    myWorkingPath=          theInst.myWorkingPath;
    myProtectPath=          theInst.myProtectPath;
    myLabelSet=             theInst.myLabelSet;
    myPriority=             theInst.myPriority;
    myLocation=             theInst.myLocation;
    myWkgPrp1=              theInst.myWkgPrp1;
    myWkgPrp2=              theInst.myWkgPrp2;
    myProtPrp1=             theInst.myProtPrp1;
    myProtPrp2=             theInst.myProtPrp2;
    myCompWkgPrp1=          theInst.myCompWkgPrp1;
    myCompProtPrp1=         theInst.myCompProtPrp1;
    myCallNumber=           theInst.myCallNumber;
    myExpRate=              theInst.myExpRate;
    myGfpTs=                theInst.myGfpTs;
    myWkgXPath=             theInst.myWkgXPath;
    myProtXPath=            theInst.myProtXPath;
    myCallRetainPath=       theInst.myCallRetainPath;

    return *this;
}

bool 
TL1_CallEntParameters::operator==( const TL1_CallEntParameters& theInst ) const
{
    if ( !(TL1_ControlPlaneFal::operator==(theInst) ) )
       return false;

    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myAEnd != theInst.myAEnd )
        return false;

    if ( myZEnd != theInst.myZEnd )
        return false;

    if ( myAEnd2 != theInst.myAEnd2 )
        return false;

    if ( myZEnd2 != theInst.myZEnd2 )
        return false;

    if ( myNodeId2!= theInst.myNodeId2)
        return false;

    if ( myNodeAddr !=theInst.myNodeAddr )
        return false;

    if ( mySignalType != theInst.mySignalType )
         return false;

    if ( myMultiplier != theInst.myMultiplier )
         return false;

    if ( myIngrss != theInst.myIngrss )
         return false;

    if ( myEgrss !=  theInst.myEgrss )
         return false;
         
    if ( myIngrss2 != theInst.myIngrss2 )
         return false;

    if ( myEgrss2 !=  theInst.myEgrss2 )
         return false;

    if ( myDirection != theInst.myDirection )
         return false;

    if ( mySrlg != theInst.mySrlg )
         return false;

    if ( myTimeout != theInst.myTimeout )
         return false;

    if ( myCallId != theInst.myCallId )
         return false;

    if( myCallName != theInst.myCallName ) 
        return false;

    if ( myCallOperState != theInst.myCallOperState )
         return false; 

    if ( myCallStatus != theInst.myCallStatus )
         return false;

    if ( mySlpf != theInst.mySlpf )
        return false;

    if ( myProtLvl != theInst.myProtLvl )
        return false;

    if ( myWorkingPath != theInst.myWorkingPath )
        return false;

    if ( myProtectPath != theInst.myProtectPath )
        return false;

    if ( myLabelSet != theInst.myLabelSet )
        return false;

    if ( myPriority != theInst.myPriority )
        return false;

    if ( myLocation != theInst.myLocation )
        return false;

    if ( myWkgPrp1 != theInst.myWkgPrp1 )
        return false;

    if ( myWkgPrp2 != theInst.myWkgPrp2 )
        return false;

    if ( myProtPrp1 != theInst.myProtPrp1 )
        return false;
    
    if ( myProtPrp2 != theInst.myProtPrp2 )
        return false;
    
    if ( myCompWkgPrp1 != theInst.myCompWkgPrp1 )
        return false;

    if ( myCompProtPrp1 != theInst.myCompProtPrp1 )
        return false;

    if ( myCallNumber != theInst.myCallNumber)
        return false;

    if ( myExpRate != theInst.myExpRate )
        return false;

    if ( myGfpTs != theInst.myGfpTs)
        return false;

    if ( myWkgXPath != theInst.myWkgXPath )
        return false;

    if ( myProtXPath != theInst.myProtXPath )
        return false;

    if ( myCallRetainPath != theInst.myCallRetainPath )
        return false;

    return true;
}

//--------------------------------------------------------------------------------
CT_TL1_ExppathAddr*                      
TL1_CallEntParameters::GetWkgPrp1( ) const
{
    return myWkgPrp1;
}

void                         
TL1_CallEntParameters::SetWkgPrp1( CT_TL1_ExppathAddr* theWkgPrp1 )
{
    myWkgPrp1 = theWkgPrp1;
}

//--------------------------------------------------------------------------------
CT_TL1_ExppathAddr*                      
TL1_CallEntParameters::GetWkgPrp2( ) const
{
    return myWkgPrp2;
}

void                         
TL1_CallEntParameters::SetWkgPrp2( CT_TL1_ExppathAddr* theWkgPrp2 )
{
    myWkgPrp2 = theWkgPrp2;
}

//--------------------------------------------------------------------------------
CT_TL1_ExppathAddr*                      
TL1_CallEntParameters::GetProtPrp1( ) const
{
    return myProtPrp1;
}

void                         
TL1_CallEntParameters::SetProtPrp1( CT_TL1_ExppathAddr* theProtPrp1 )
{
    myProtPrp1 = theProtPrp1;
}

//--------------------------------------------------------------------------------
CT_TL1_ExppathAddr*                      
TL1_CallEntParameters::GetProtPrp2( ) const
{
    return myProtPrp2;
}

void                         
TL1_CallEntParameters::SetProtPrp2( CT_TL1_ExppathAddr* theProtPrp2 )
{
    myProtPrp2 = theProtPrp2;
}

//--------------------------------------------------------------------------------
bool*                      
TL1_CallEntParameters::GetCompWkgPrp1( ) const
{
    return myCompWkgPrp1;
}

void                         
TL1_CallEntParameters::SetCompWkgPrp1( bool* theCompWkgPrp1 )
{
    myCompWkgPrp1 = theCompWkgPrp1;
}

//--------------------------------------------------------------------------------
bool*                      
TL1_CallEntParameters::GetCompProtPrp1( ) const
{
    return myCompProtPrp1;
}

void                         
TL1_CallEntParameters::SetCompProtPrp1( bool* theCompProtPrp1 )
{
    myCompProtPrp1 = theCompProtPrp1;
}

//--------------------------------------------------------------------------------
CT_TL1_CallNumber*   
TL1_CallEntParameters::GetCallNumber() const
{
    return myCallNumber;
}

void
TL1_CallEntParameters::SetCallNumber(CT_TL1_CallNumber * theCallNumber)
{
    myCallNumber = theCallNumber;
}

//-----------------------------------------------------------------------------
// RTRV-CALL Parameters Default Constructor & Destructor
TL1_CallRtrvParameters::TL1_CallRtrvParameters()
    :myHandle( (LT_Handle*)0 )
    ,myCtag( (LT_Ctag)0 )
    ,myCallAddr( (CT_TL1_CallAddr*)0 )
    ,myCallId( (CT_ControlPlane_CallId*)0 )
    ,mySlpf( (CT_TL1_LogicalAddr*)0 )
    ,myAEnd( (CT_ControlPlane_TNA*)0 )
    ,myZEnd( (CT_ControlPlane_TNA*)0 )
    ,myIngrss( (CT_ControlPlane_LabelSet*)0 )
    ,myEgrss( (CT_ControlPlane_LabelSet*)0 )
    ,myAEnd2( (CT_ControlPlane_TNA*)0 )
    ,myZEnd2( (CT_ControlPlane_TNA*)0 )
    ,myIngrss2( (CT_ControlPlane_LabelSet*)0 )
    ,myEgrss2( (CT_ControlPlane_LabelSet*)0 )
    ,myPrpUse( (CT_TL1_ExppathAddr*)0 )
    ,myEditablePrimaryState( (CT_SM_PST*)0 )
    ,mySecondaryState( (CT_SM_SST*)0 )
{
}

TL1_CallRtrvParameters::~TL1_CallRtrvParameters()
{
}


//-----------------------------------------------------------------------------
// RTRV-CALL Parameters Copy Constructor
TL1_CallRtrvParameters::TL1_CallRtrvParameters( const TL1_CallRtrvParameters& theInst )
{

    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myCallAddr=             theInst.myCallAddr;
    myCallId=               theInst.myCallId;
    mySlpf=                 theInst.mySlpf;
    myAEnd=                 theInst.myAEnd;
    myZEnd=                 theInst.myZEnd;
    myIngrss=               theInst.myIngrss;
    myEgrss=                theInst.myEgrss;
    myAEnd2=                theInst.myAEnd2;
    myZEnd2=                theInst.myZEnd2;
    myIngrss2=              theInst.myIngrss2;
    myEgrss2=               theInst.myEgrss2;
    myPrpUse=               theInst.myPrpUse;
    myEditablePrimaryState= theInst.myEditablePrimaryState;
    mySecondaryState=       theInst.mySecondaryState;
}


//-----------------------------------------------------------------------------
// RTRV-CALL Parameters Assignment Operator
TL1_CallRtrvParameters& 
TL1_CallRtrvParameters::operator=( const TL1_CallRtrvParameters& theInst )
{

    myHandle=               theInst.myHandle;    
    myCtag=                 theInst.myCtag;
    myCallAddr=             theInst.myCallAddr;
    myCallId=               theInst.myCallId;
    mySlpf=                 theInst.mySlpf;
    myAEnd=                 theInst.myAEnd;
    myZEnd=                 theInst.myZEnd;
    myIngrss=               theInst.myIngrss;
    myEgrss=                theInst.myEgrss;
    myAEnd2=                theInst.myAEnd2;
    myZEnd2=                theInst.myZEnd2;
    myIngrss2=              theInst.myIngrss2;
    myEgrss2=               theInst.myEgrss2;
    myPrpUse=               theInst.myPrpUse;
    myEditablePrimaryState= theInst.myEditablePrimaryState;
    mySecondaryState=       theInst.mySecondaryState;

    return *this;
}


//-----------------------------------------------------------------------------
// RTRV-CALL Parameters Equality Operator
bool 
TL1_CallRtrvParameters::operator==( const TL1_CallRtrvParameters& theInst ) const
{

    if ( myHandle != theInst.myHandle )
        return false;

    if ( myCtag != theInst.myCtag )
        return false;

    if ( myCallAddr != theInst.myCallAddr )
        return false;

    if ( myCallId != theInst.myCallId )
         return false;

    if ( mySlpf != theInst.mySlpf )
        return false;

    if ( myAEnd != theInst.myAEnd )
        return false;

    if ( myZEnd != theInst.myZEnd )
        return false;

    if ( myIngrss != theInst.myIngrss )
         return false;

    if ( myEgrss !=  theInst.myEgrss )
         return false;

    if ( myAEnd2 != theInst.myAEnd2 )
        return false;

    if ( myZEnd2 != theInst.myZEnd2 )
        return false;

    if ( myIngrss2 != theInst.myIngrss2 )
         return false;

    if ( myEgrss2 !=  theInst.myEgrss2 )
         return false;

    if ( myPrpUse !=  theInst.myPrpUse )
         return false;

    if ( myEditablePrimaryState != theInst.myEditablePrimaryState )
        return false;

    if ( mySecondaryState != theInst.mySecondaryState )
        return false;

    return true;
}
