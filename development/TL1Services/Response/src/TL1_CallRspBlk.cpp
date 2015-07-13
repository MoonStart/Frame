/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 CALL Response 
TARGET:
AUTHOR:         May 02, 2007 - Tong Wu
DESCRIPTION:    Source file for TL1 CALL Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_CallRspBlk.h>

TL1_CallRspBlk::TL1_CallRspBlk( )
    :myBitSet( INDEX_END, false ) 
{
}

TL1_CallRspBlk::TL1_CallRspBlk( 
    const CT_TL1_CallAddr               theAddr,
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
    const CT_TL1_ExdpathAddr            theProtXPath )

    :myBitSet( INDEX_END, false )
{
    myBitSet[ INDEX_Addr ] = true;
    myAddr = theAddr;

    myBitSet[ INDEX_CallId ] = true;
    myCallId = theCallId;

    myBitSet[ INDEX_CallName ] = true;
    myCallName = theCallName;

    myBitSet[ INDEX_AEnd ] = true;
    myAEnd = theAEnd;

    myBitSet[ INDEX_ZEnd ] = true;
    myZend = theZend;

    myBitSet[ INDEX_NodeId ] = true;
    myNodeAid = theNodeAid;

    myBitSet[ INDEX_AEnd2 ] = true;
    myAEnd2 = theAEnd2;

    myBitSet[ INDEX_ZEnd2 ] = true;
    myZend2 = theZend2;

    myBitSet[ INDEX_NodeId2 ] = true;
    myNodeId2 = theNodeId2;

    myBitSet[ INDEX_SigType ] = true;
    mySigType = theSigType;

    myBitSet[ INDEX_Multiple ] = true;
    myMultiplier = theMultiplier;

    myBitSet[ INDEX_Direction ] = true;
    myDirectionality = theDirectionality;

    myBitSet[ INDEX_Ingrss ] = true;
    myIngress = theIngress;

    myBitSet[ INDEX_Egrss ] = true;
    myEgress = theEgress;

    myBitSet[ INDEX_CpIngrss ] = true;
    myCpIngress = theCpIngress;

    myBitSet[ INDEX_CpEgrss ] = true;
    myCpEgress = theCpEgress;

    myBitSet[ INDEX_Ingrss2 ] = true;
    myIngress2 = theIngress2;

    myBitSet[ INDEX_Egrss2 ] = true;
    myEgress2 = theEgress2;

    myBitSet[ INDEX_CpIngrss2 ] = true;
    myCpIngress2 = theCpIngress2;

    myBitSet[ INDEX_CpEgrss2 ] = true;
    myCpEgress2 = theCpEgress2;

    myBitSet[ INDEX_LabelSetType ] = true;
    myLabelSetType = theLabelSetType;

    myBitSet[ INDEX_LabelSet ] = true;
    myLabelSet = theLabelSet;

    myBitSet[ INDEX_Srlg ] = true;
    mySrlg = theSrlg;

    myBitSet[ INDEX_Timeout ] = true;
    myTimeout = theTimeout;

    myBitSet[ INDEX_Slpf ] = true;
    mySlpf = theSlpf;

    myBitSet[ INDEX_ProtLvl ] = true;
    myProtLvl = theProtLvl;

    myBitSet[ INDEX_Priority ] = true;
    myPriority = thePriority;

    myBitSet[ INDEX_CallLoc ] = true;
    myCallLoc = theCallLoc;

    if ( thePST )
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }
    else
    {
        myPST = 0;
    }
    
    if ( thePSTQ )
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
    else
    {
        myPSTQ = 0;
    }

    if ( theSST )
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
    else
    {
        mySST = 0;
    }

    myBitSet[ INDEX_WkgPrp1 ] = true;
    myWkgPrp1 = theWkgPrp1;

    myBitSet[ INDEX_WkgPrp2 ] = true;
    myWkgPrp2 = theWkgPrp2;

    myBitSet[ INDEX_ProtPrp1 ] = true;
    myProtPrp1 = theProtPrp1; 

    myBitSet[ INDEX_ProtPrp2 ] = true;
    myProtPrp2 = theProtPrp2; 

    myBitSet[ INDEX_ExpRate ] = true;
    myExpRate = theExpRate; 

    myBitSet[ INDEX_GfpTs ] = true;
    myGfpTs = theGfpTs; 

    myBitSet[ INDEX_WkgXPath ] = true;
    myWkgXPath = theWkgXPath; 

    myBitSet[ INDEX_ProtXPath ] = true;
    myProtXPath = theProtXPath; 
}

TL1_CallRspBlk::TL1_CallRspBlk( const TL1_CallRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=           t1Blk.myBitSet;
    myAddr=             t1Blk.myAddr;
    myCallId=           t1Blk.myCallId;
    myCallName=         t1Blk.myCallName;
    myAEnd=             t1Blk.myAEnd;
    myZend=             t1Blk.myZend;
    myNodeAid=          t1Blk.myNodeAid;
    myAEnd2=            t1Blk.myAEnd2;
    myZend2=            t1Blk.myZend2;
    myNodeId2=          t1Blk.myNodeId2;
    mySigType=          t1Blk.mySigType;
    myMultiplier=       t1Blk.myMultiplier;
    myDirectionality=   t1Blk.myDirectionality;
    myIngress=          t1Blk.myIngress;
    myEgress=           t1Blk.myEgress;
    myCpIngress=        t1Blk.myCpIngress;
    myCpEgress=         t1Blk.myCpEgress;
    myIngress2=         t1Blk.myIngress2;
    myEgress2=          t1Blk.myEgress2;
    myCpIngress2=       t1Blk.myCpIngress2;
    myCpEgress2=        t1Blk.myCpEgress2;
    myLabelSetType=     t1Blk.myLabelSetType;
    myLabelSet=         t1Blk.myLabelSet;
    mySrlg=             t1Blk.mySrlg;
    myTimeout=          t1Blk.myTimeout;
    mySlpf=             t1Blk.mySlpf;
    myProtLvl=          t1Blk.myProtLvl;
    myPriority=         t1Blk.myPriority;
    myCallLoc=          t1Blk.myCallLoc;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
    myWkgPrp1=          t1Blk.myWkgPrp1;
    myWkgPrp2=          t1Blk.myWkgPrp2;
    myProtPrp1=         t1Blk.myProtPrp1;
    myProtPrp2=         t1Blk.myProtPrp2;
    myExpRate=          t1Blk.myExpRate;
    myGfpTs=            t1Blk.myGfpTs;
    myWkgXPath=         t1Blk.myWkgXPath;
    myProtXPath=        t1Blk.myProtXPath;
}

TL1_CallRspBlk::~TL1_CallRspBlk( )
{
}

TL1_CallRspBlk& 
TL1_CallRspBlk::operator=( const TL1_CallRspBlk& t1Blk )
{
    myBitSet=           t1Blk.myBitSet;
    myAddr=             t1Blk.myAddr;
    myCallId=           t1Blk.myCallId;
    myCallName=         t1Blk.myCallName;
    myAEnd=             t1Blk.myAEnd;
    myZend=             t1Blk.myZend;
    myNodeAid=          t1Blk.myNodeAid;
    myAEnd2=            t1Blk.myAEnd2;
    myZend2=            t1Blk.myZend2;
    myNodeId2=          t1Blk.myNodeId2;
    mySigType=          t1Blk.mySigType;
    myMultiplier=       t1Blk.myMultiplier;
    myDirectionality=   t1Blk.myDirectionality;
    myIngress=          t1Blk.myIngress;
    myEgress=           t1Blk.myEgress;
    myCpIngress=        t1Blk.myCpIngress;
    myCpEgress=         t1Blk.myCpEgress;
    myIngress2=         t1Blk.myIngress2;
    myEgress2=          t1Blk.myEgress2;
    myCpIngress2=       t1Blk.myCpIngress2;
    myCpEgress2=        t1Blk.myCpEgress2;
    myLabelSetType=     t1Blk.myLabelSetType;
    myLabelSet=         t1Blk.myLabelSet;
    mySrlg=             t1Blk.mySrlg;
    myTimeout=          t1Blk.myTimeout;
    mySlpf=             t1Blk.mySlpf;
    myProtLvl=          t1Blk.myProtLvl;
    myPriority=         t1Blk.myPriority;
    myCallLoc=          t1Blk.myCallLoc;
    myPST=              t1Blk.myPST;
    myPSTQ=             t1Blk.myPSTQ;
    mySST=              t1Blk.mySST;
    myWkgPrp1=          t1Blk.myWkgPrp1;
    myWkgPrp2=          t1Blk.myWkgPrp2;
    myProtPrp1=         t1Blk.myProtPrp1;
    myProtPrp2=         t1Blk.myProtPrp2;
    myExpRate=          t1Blk.myExpRate;
    myGfpTs=            t1Blk.myGfpTs;
    myWkgXPath=         t1Blk.myWkgXPath;
    myProtXPath=        t1Blk.myProtXPath;

    return *this;
}

bool 
TL1_CallRspBlk::operator==( const TL1_CallRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if( myAddr != t1Blk.myAddr )
        return false;

    if ( myCallId != t1Blk.myCallId )
        return false;

    if( myCallName != t1Blk.myCallName )
        return false;

    if ( myAEnd != t1Blk.myAEnd )
        return false;

    if ( myZend != t1Blk.myZend )
        return false;

    if ( myNodeAid != t1Blk.myNodeAid )
        return false;
        
    if ( myAEnd2 != t1Blk.myAEnd2 )
        return false;

    if ( myZend2 != t1Blk.myZend2 )
        return false;

    if ( myNodeId2 != t1Blk.myNodeId2 )
        return false;

    if ( mySigType != t1Blk.mySigType )
        return false;

    if ( myMultiplier != t1Blk.myMultiplier )
        return false;

    if ( myDirectionality != t1Blk.myDirectionality )
        return false;

    if ( myIngress != t1Blk.myIngress )
        return false;

    if ( myEgress != t1Blk.myEgress )
        return false;

    if ( myCpIngress != t1Blk.myCpIngress )
        return false;

    if ( myCpEgress != t1Blk.myCpEgress )
        return false;

    if ( myIngress2 != t1Blk.myIngress2 )
        return false;

    if ( myEgress2 != t1Blk.myEgress2 )
        return false;

    if ( myCpIngress2 != t1Blk.myCpIngress2 )
        return false;

    if ( myCpEgress2 != t1Blk.myCpEgress2 )
        return false;

    if(myLabelSetType != t1Blk.myLabelSetType)
        return false;

    if(myLabelSet != t1Blk.myLabelSet)
        return false;

    if ( mySrlg != t1Blk.mySrlg )
        return false;

    if ( myTimeout != t1Blk.myTimeout )
        return false;

    if ( mySlpf != t1Blk.mySlpf )
        return false;

    if ( myProtLvl != t1Blk.myProtLvl )
        return false;

    if(myPriority != t1Blk.myPriority )
        return false;

    if ( myCallLoc != t1Blk.myCallLoc )
        return false;

    if ( myWkgPrp1 != t1Blk.myWkgPrp1 )
        return false;

    if ( myWkgPrp2 != t1Blk.myWkgPrp2 )
        return false;

    if ( myProtPrp1 != t1Blk.myProtPrp1 )
        return false;

    if ( myProtPrp2 != t1Blk.myProtPrp2 )
        return false;

    if ( myExpRate!= t1Blk.myExpRate)
        return false;

    if ( myGfpTs!= t1Blk.myGfpTs )
        return false;

    if ( myPST != t1Blk.myPST )
        return false;

    if ( myPSTQ != t1Blk.myPSTQ )
        return false;

    if ( mySST != t1Blk.mySST )
        return false;

    if ( myWkgXPath != t1Blk.myWkgXPath )
        return false;

    if ( myProtXPath != t1Blk.myProtXPath )
        return false;

    return true;
}

//--------------------------------------------------------------
bool
TL1_CallRspBlk::GetAddr(CT_TL1_CallAddr& theAddr) const
{
    if ( true == myBitSet[ INDEX_CallName ] )
    {
        theAddr = myAddr;
        return true;
    }
    return false;
}

void
TL1_CallRspBlk::SetAddr(const CT_TL1_CallAddr& theAddr)
{
    myBitSet[ INDEX_Addr ] = true;
    myAddr = theAddr;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetCallId( CT_ControlPlane_CallId& theCallId ) const
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
TL1_CallRspBlk::SetCallId( const CT_ControlPlane_CallId& theCallId ) 
{
   myBitSet[ INDEX_CallId ] = true;
   myCallId = theCallId;
}

//--------------------------------------------------------------
bool
TL1_CallRspBlk::GetCallName(string& theCallName) const
{
    if( true == myBitSet[ INDEX_CallName ] )
    {
        theCallName = myCallName;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetCallName( const string& theCallName ) 
{
   myBitSet[ INDEX_CallName ] = true;
   myCallName = theCallName;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetaEndPoint( CT_ControlPlane_TNA& theAEnd ) const
{
    if( true == myBitSet[ INDEX_AEnd ] )
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
TL1_CallRspBlk::SetaEndPoint( const CT_ControlPlane_TNA& theAEnd )
{
   myBitSet[ INDEX_AEnd ] = true;
   myAEnd = theAEnd;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetzEndPoint( CT_ControlPlane_TNA& theZend ) const
{
    if( true == myBitSet[ INDEX_ZEnd ] )
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
TL1_CallRspBlk::SetzEndPoint( const CT_ControlPlane_TNA& theZend )
{
   myBitSet[ INDEX_ZEnd ] = true;
   myZend = theZend;
}


//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const
{
    if( true == myBitSet[ INDEX_NodeId ] )
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
TL1_CallRspBlk::SetNodeAddr( const CT_TL1_NodeAddr& theNodeAid )
{
    myBitSet[ INDEX_NodeId ] = true;
    myNodeAid= theNodeAid;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetaEndPoint2( CT_ControlPlane_TNA& theAEnd2 ) const
{
    if( true == myBitSet[ INDEX_AEnd2 ] )
    {
        theAEnd2 = myAEnd2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetaEndPoint2( const CT_ControlPlane_TNA& theAEnd2 )
{
   myBitSet[ INDEX_AEnd2 ] = true;
   myAEnd2 = theAEnd2;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetzEndPoint2( CT_ControlPlane_TNA& theZend2 ) const
{
    if( true == myBitSet[ INDEX_ZEnd2 ] )
    {
        theZend2 = myZend2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetzEndPoint2( const CT_ControlPlane_TNA& theZend2 )
{
   myBitSet[ INDEX_ZEnd2 ] = true;
   myZend2 = theZend2;
}


//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetNodeId2( uint32& theNodeId2 ) const
{
    if( true == myBitSet[ INDEX_NodeId2 ] )
    {
        theNodeId2 = myNodeId2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetNodeId2( const uint32& theNodeId2 )
{
    myBitSet[ INDEX_NodeId2 ] = true;
    myNodeId2= theNodeId2;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetSignalType( CT_Call_SignalType& theSigType ) const
{
    if( true == myBitSet[ INDEX_SigType ] )
    {
        theSigType = mySigType;
        return true;
    }
    else
    {
        return false;
    }
}
void 
TL1_CallRspBlk::SetSignalType( const CT_Call_SignalType& theSigType )
{
    myBitSet[ INDEX_SigType ] = true;
    mySigType = theSigType;
}


//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetMultiplier( int16& theMultiplier ) const
{
    if( true == myBitSet[ INDEX_Multiple ] )
    {
        theMultiplier = myMultiplier;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetMultiplier( const int16& theMultiplier )
{
    myBitSet[ INDEX_Multiple ] = true;
    myMultiplier = theMultiplier;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetDirection( CT_Call_Directionality& theDirectionality ) const
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
TL1_CallRspBlk::SetDirection( const CT_Call_Directionality& theDirectionality )
{
    myBitSet[ INDEX_Direction ] = true;
    myDirectionality= theDirectionality;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetIngress( CT_ControlPlane_LabelSet& theIngress ) const
{
    if( true == myBitSet[ INDEX_Ingrss ] )
    {
        theIngress = myIngress;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetIngress( const CT_ControlPlane_LabelSet& theIngress )
{
    myBitSet[ INDEX_Ingrss ] = true;
    myIngress = theIngress;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetEgress( CT_ControlPlane_LabelSet& theEgress ) const
{
    if( true == myBitSet[ INDEX_Egrss ] )
    {
        theEgress = myEgress;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetEgress( const CT_ControlPlane_LabelSet& theEgress )
{
    myBitSet[ INDEX_Egrss ] = true;
    myEgress = theEgress;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetCpIngress( CT_ControlPlane_LabelSet& theCpIngress ) const
{
    if( true == myBitSet[ INDEX_CpIngrss ] )
    {
        theCpIngress = myCpIngress;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetCpIngress( const CT_ControlPlane_LabelSet& theCpIngress )
{
    myBitSet[ INDEX_CpIngrss ] = true;
    myCpIngress = theCpIngress;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetCpEgress( CT_ControlPlane_LabelSet& theCpEgress ) const
{
    if( true == myBitSet[ INDEX_CpEgrss ] )
    {
        theCpEgress = myCpEgress;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetCpEgress( const CT_ControlPlane_LabelSet& theCpEgress )
{
    myBitSet[ INDEX_CpEgrss ] = true;
    myCpEgress = theCpEgress;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetIngress2( CT_ControlPlane_LabelSet& theIngress2 ) const
{
    if( true == myBitSet[ INDEX_Ingrss2 ] )
    {
        theIngress2 = myIngress2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetIngress2( const CT_ControlPlane_LabelSet& theIngress2 )
{
    myBitSet[ INDEX_Ingrss2 ] = true;
    myIngress2 = theIngress2;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetEgress2( CT_ControlPlane_LabelSet& theEgress2 ) const
{
    if( true == myBitSet[ INDEX_Egrss2 ] )
    {
        theEgress2 = myEgress2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetEgress2( const CT_ControlPlane_LabelSet& theEgress2 )
{
    myBitSet[ INDEX_Egrss2 ] = true;
    myEgress2 = theEgress2;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetCpIngress2( CT_ControlPlane_LabelSet& theCpIngress2 ) const
{
    if( true == myBitSet[ INDEX_CpIngrss2 ] )
    {
        theCpIngress2 = myCpIngress2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetCpIngress2( const CT_ControlPlane_LabelSet& theCpIngress2 )
{
    myBitSet[ INDEX_CpIngrss2 ] = true;
    myCpIngress2 = theCpIngress2;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetCpEgress2( CT_ControlPlane_LabelSet& theCpEgress2 ) const
{
    if( true == myBitSet[ INDEX_CpEgrss2 ] )
    {
        theCpEgress2 = myCpEgress2;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetCpEgress2( const CT_ControlPlane_LabelSet& theCpEgress2 )
{
    myBitSet[ INDEX_CpEgrss2 ] = true;
    myCpEgress2 = theCpEgress2;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetLabelSetType(CT_LabelSetType& theLabelSetType) const
{
    if( true == myBitSet[ INDEX_LabelSetType ] )
    {
        theLabelSetType = myLabelSetType;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetLabelSetType(const CT_LabelSetType& theLabelSetType)
{
    myBitSet[ INDEX_LabelSetType ] = true;
    myLabelSetType = theLabelSetType;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetLabelSet(CT_TL1_LabelSetAddr& theLabelSetAddr) const
{
    if( true == myBitSet[ INDEX_LabelSet ] )
    {
        theLabelSetAddr = myLabelSet;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetLabelSet(const CT_TL1_LabelSetAddr& theLabelSetAddr)
{
    myBitSet[ INDEX_LabelSet ] = true;
    myLabelSet = theLabelSetAddr;
}


//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetSrlg( CT_ControlPlane_Srlg& theSrlg ) const
{
    if( true == myBitSet[ INDEX_Srlg ] )
    {
        theSrlg = mySrlg;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetSrlg( const CT_ControlPlane_Srlg& theSrlg )
{
    myBitSet[ INDEX_Srlg ] = true;
    mySrlg = theSrlg;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetTimeout( uint16& theTimeout ) const
{
    if( true == myBitSet[ INDEX_Timeout ] )
    {
        theTimeout = myTimeout;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetTimeout( const uint16& theTimeout )
{
    myBitSet[ INDEX_Timeout ] = true;
    myTimeout= theTimeout;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetSlpf( CT_TL1_LogicalAddr& theSlpf ) const
{
    if( true == myBitSet[ INDEX_Slpf ] )
    {
        theSlpf = mySlpf;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetSlpf( const CT_TL1_LogicalAddr& theSlpf )
{
    myBitSet[ INDEX_Slpf ] = true;
    mySlpf = theSlpf;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_CallRspBlk::GetProtLvl( CT_SLPF_ProtLvl& theProtLvl ) const
{
    if( true == myBitSet[ INDEX_ProtLvl ] )
    {
        theProtLvl = myProtLvl;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_CallRspBlk::SetProtLvl( const CT_SLPF_ProtLvl theProtLvl )
{
    myBitSet[ INDEX_ProtLvl ] = true;
    myProtLvl = theProtLvl;
}


//-----------------------------------------------------------------------------
bool
TL1_CallRspBlk::GetPriority( CT_SLPF_PRIORITY & thePriority ) const
{
    if (true == myBitSet[ INDEX_Priority ] )
    {
        thePriority = myPriority;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetPriority( const CT_SLPF_PRIORITY & thePriority )
{
    myBitSet[ INDEX_Priority ] = true;
    myPriority = thePriority;
}

//--------------------------------------------------------------
bool 
TL1_CallRspBlk::GetCallLoc( CT_Call_Location& theCallLoc ) const
{
    if( true == myBitSet[ INDEX_CallLoc ] )
    {
        theCallLoc = myCallLoc;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallRspBlk::SetCallLoc( const CT_Call_Location& theCallLoc ) 
{
    myBitSet[ INDEX_CallLoc ] = true;
    myCallLoc = theCallLoc;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetWkgPrp1( CT_TL1_ExppathAddr& theExppath ) const
{
    if( true == myBitSet[ INDEX_WkgPrp1 ] )
    {
        theExppath = myWkgPrp1;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetWkgPrp1( const CT_TL1_ExppathAddr& theExppath ) 
{
    myBitSet[ INDEX_WkgPrp1 ] = true;
    myWkgPrp1 = theExppath;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetWkgPrp2( CT_TL1_ExppathAddr& theExppath ) const
{
    if( true == myBitSet[ INDEX_WkgPrp2 ] )
    {
        theExppath = myWkgPrp2;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetWkgPrp2( const CT_TL1_ExppathAddr& theExppath ) 
{
    myBitSet[ INDEX_WkgPrp2 ] = true;
    myWkgPrp2 = theExppath;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetProtPrp1( CT_TL1_ExppathAddr& theExppath ) const
{
    if( true == myBitSet[ INDEX_ProtPrp1 ] )
    {
        theExppath = myProtPrp1;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetProtPrp1( const CT_TL1_ExppathAddr& theExppath ) 
{
    myBitSet[ INDEX_ProtPrp1 ] = true;
    myProtPrp1 = theExppath;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetProtPrp2( CT_TL1_ExppathAddr& theExppath ) const
{
    if( true == myBitSet[ INDEX_ProtPrp2 ] )
    {
        theExppath = myProtPrp2;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetProtPrp2( const CT_TL1_ExppathAddr& theExppath ) 
{
    myBitSet[ INDEX_ProtPrp2 ] = true;
    myProtPrp2 = theExppath;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetExpRate( CT_TEL_daHz& theExpRate ) const
{
    if( true == myBitSet[ INDEX_ExpRate ] )
    {
        theExpRate = myExpRate;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetExpRate( const CT_TEL_daHz& theExpRate ) 
{
    myBitSet[ INDEX_ExpRate ] = true;
    myExpRate = theExpRate;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetGfpTs( uint8& theGfpTs ) const
{
    if( true == myBitSet[ INDEX_GfpTs ] )
    {
        theGfpTs = myGfpTs;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetGfpTs( const uint8& theGfpTs ) 
{
    myBitSet[ INDEX_GfpTs ] = true;
    myGfpTs = theGfpTs;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetWkgXPath( CT_TL1_ExdpathAddr& theWkgXPath ) const
{
    if( true == myBitSet[ INDEX_WkgXPath ] )
    {
        theWkgXPath = myWkgXPath;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetWkgXPath( const CT_TL1_ExdpathAddr& theWkgXPath ) 
{
    myBitSet[ INDEX_WkgXPath ] = true;
    myWkgXPath = theWkgXPath;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_CallRspBlk::GetProtXPath( CT_TL1_ExdpathAddr& theProtXPath ) const
{
    if( true == myBitSet[ INDEX_ProtXPath ] )
    {
        theProtXPath = myProtXPath;
        return true;
    }
    else
    {
        return false;
    }
}

void
TL1_CallRspBlk::SetProtXPath( const CT_TL1_ExdpathAddr& theProtXPath ) 
{
    myBitSet[ INDEX_ProtXPath ] = true;
    myProtXPath = theProtXPath;
}

//-----------------------------------------------------------------------------
bool TL1_CallRspBlk::GetPST( CT_SM_PST& thePST ) const
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

void TL1_CallRspBlk::SetPST( const CT_SM_PST& thePST )  
{
    myBitSet[ INDEX_PST ] = true; 
    myPST = thePST;
}


//-----------------------------------------------------------------------------
bool TL1_CallRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ ) const
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

void TL1_CallRspBlk::SetPSTQ( const CT_SM_PSTQ& thePSTQ )  
{
    myBitSet[ INDEX_PSTQ ] = true; 
    myPSTQ = thePSTQ;
}


//-----------------------------------------------------------------------------
bool TL1_CallRspBlk::GetSST( CT_SM_SST& theSST ) const
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

void TL1_CallRspBlk::SetSST( const CT_SM_SST& theSST )  
{
    myBitSet[ INDEX_SST ] = true; 
    mySST = theSST;
}



//-------------------------------------------------------------------------------------------------------
// Callid response
TL1_CallidRspBlk::TL1_CallidRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_CallidRspBlk::TL1_CallidRspBlk( const CT_ControlPlane_CallId*   theCallid )
      : myBitSet( INDEX_END, false )
{
    if( theCallid )
    {
        myBitSet[ INDEX_Callid ] = true;
        myCallid = *theCallid;
    }
}


TL1_CallidRspBlk::TL1_CallidRspBlk( const TL1_CallidRspBlk& t1Blk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet=                       t1Blk.myBitSet;
    myCallid=                       t1Blk.myCallid;
}

TL1_CallidRspBlk::~TL1_CallidRspBlk( )
{
}

TL1_CallidRspBlk& 
TL1_CallidRspBlk::operator=( const TL1_CallidRspBlk& t1Blk )
{
    myBitSet=                       t1Blk.myBitSet;
    myCallid=                       t1Blk.myCallid;

    return *this;
}

bool 
TL1_CallidRspBlk::operator==( const TL1_CallidRspBlk& t1Blk ) const
{
    if ( myBitSet != t1Blk.myBitSet )
        return false;

    if ( myCallid != t1Blk.myCallid )
        return false;

    return true;
}

//--------------------------------------------------------------
bool 
TL1_CallidRspBlk::GetCallid( CT_ControlPlane_CallId& theCallid ) const
{
    if( true == myBitSet[ INDEX_Callid ] )
    {
        theCallid = myCallid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallidRspBlk::SetCallid( CT_ControlPlane_CallId& theCallid )
{
   myBitSet[ INDEX_Callid ] = true;
   myCallid = theCallid;
}

//--------------------------------------------------------------
TL1_CallDetailRspBlk::TL1_CallDetailRspBlk()
    :myBitSet( INDEX_END, false ) 
{
}

TL1_CallDetailRspBlk::TL1_CallDetailRspBlk( const TL1_CallDetailRspBlk& t1Blk)
    :myBitSet( INDEX_END, false )
{
    myBitSet=        t1Blk.myBitSet;
    myCallAddr=      t1Blk.myCallAddr;
    myCallId =       t1Blk.myCallId;
    myCallNodeAid =  t1Blk.myCallNodeAid;
    myMtNumber =     t1Blk.myMtNumber;
    myConnId =       t1Blk.myConnId;
    myConnNodeAid =  t1Blk.myConnNodeAid;
    myResourceList = t1Blk.myResourceList;
    myConnMode =     t1Blk.myConnMode;
    myConnPath =     t1Blk.myConnPath;
}

TL1_CallDetailRspBlk::~TL1_CallDetailRspBlk( )
{
}


TL1_CallDetailRspBlk& 
TL1_CallDetailRspBlk::operator=( const TL1_CallDetailRspBlk& t1Blk )
{
    myBitSet=        t1Blk.myBitSet;
    myCallAddr=      t1Blk.myCallAddr;
    myCallId =       t1Blk.myCallId;
    myCallNodeAid =  t1Blk.myCallNodeAid;
    myMtNumber =     t1Blk.myMtNumber;
    myConnId =       t1Blk.myConnId;
    myConnNodeAid =  t1Blk.myConnNodeAid;
    myResourceList = t1Blk.myResourceList;
    myConnMode =     t1Blk.myConnMode;
    myConnPath =     t1Blk.myConnPath;

    return *this;
}


//--------------------------------------------------------------
bool
TL1_CallDetailRspBlk::GetCallAddr(CT_TL1_CallAddr & theAddr) const
{
    if( true == myBitSet[ INDEX_Addr ] )
    {
        theAddr = myCallAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallDetailRspBlk::SetCallAddr( const CT_TL1_CallAddr& theAddr)
{
    myBitSet[ INDEX_Addr ] = true;
    myCallAddr = theAddr;
}

//--------------------------------------------------------------
bool
TL1_CallDetailRspBlk::GetCallId( CT_ControlPlane_CallId& theCallId ) const
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
TL1_CallDetailRspBlk::SetCallId( const CT_ControlPlane_CallId& theCallId )
{
    myBitSet[ INDEX_CallId ] = true;
    myCallId = theCallId;
}

//--------------------------------------------------------------
bool
TL1_CallDetailRspBlk::GetCallNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const
{
    if( true == myBitSet[ INDEX_NodeId ] )
    {
        theNodeAid = myCallNodeAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallDetailRspBlk::SetCallNodeAddr( const CT_TL1_NodeAddr& theNodeAid )
{
    myBitSet[ INDEX_NodeId ] = true;
    myCallNodeAid = theNodeAid;
}

//--------------------------------------------------------------
bool
TL1_CallDetailRspBlk::GetMultiplier( int16& theMultiplier ) const
{
    if( true == myBitSet[ INDEX_Multiple ] )
    {
        theMultiplier = myMtNumber;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallDetailRspBlk::SetMultiplier( const int16& theMultiplier )
{
    myBitSet[ INDEX_Multiple ] = true;
    myMtNumber = theMultiplier;
}


//--------------------------------------------------------------
bool
TL1_CallDetailRspBlk::GetConnId( CT_ControlPlane_ConnectionId& theConnId ) const
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
TL1_CallDetailRspBlk::SetConnId( const CT_ControlPlane_ConnectionId& theConnId )
{
    myBitSet[ INDEX_ConnId ] = true;
    myConnId = theConnId;
}

//--------------------------------------------------------------
bool
TL1_CallDetailRspBlk::GetConnNodeAddr( CT_TL1_NodeAddr& theNodeAid ) const
{
    if( true == myBitSet[ INDEX_ConnNodeId ] )
    {
        theNodeAid = myConnNodeAid;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_CallDetailRspBlk::SetConnNodeAddr( const CT_TL1_NodeAddr& theNodeAid )
{
    myBitSet[ INDEX_ConnNodeId ] = true;
    myConnNodeAid = theNodeAid;
}

//-------------------------------------------------------------------------------------------------------
bool
TL1_CallDetailRspBlk::GetResourceList( list<string>& theResourceList ) const
{
    if( true == myBitSet[ INDEX_Resource ] )
    {
        theResourceList = myResourceList;
        return true;
    }
    return false;
}

void
TL1_CallDetailRspBlk::SetResource( const string& theResource )
{
    myBitSet[ INDEX_Resource ] = true;
    myResourceList.push_back( theResource );
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_CallDetailRspBlk::GetConnMode( CT_ConnMode& theConnMode) const
{
    if( true == myBitSet[ INDEX_ConnMode ] )
    {
        theConnMode = myConnMode;
        return true;
    }
    return false;
}

void  
TL1_CallDetailRspBlk::SetConnMode( const CT_ConnMode& theConnMode)
{
    myBitSet[ INDEX_ConnMode ] = true;
    myConnMode = theConnMode;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_CallDetailRspBlk::GetConnPath( CT_CallPathType& theConnPath) const
{
    if( true == myBitSet[ INDEX_ConnPath ] )
    {
        theConnPath = myConnPath;
        return true;
    }
	return false;
}

void  
TL1_CallDetailRspBlk::SetConnPath( const CT_CallPathType& theConnPath)
{
    myBitSet[ INDEX_ConnPath ] = true;
    myConnPath = theConnPath;
}

//--------------------------------------------------------------

