/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Link Response 
TARGET:
AUTHOR:         Keith Halsall - August 8, 2012
DESCRIPTION:    Source file for TL1 DA Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_DaRspBlk.h>
#include <CommonTypes/CT_ControlPlane_Convert.h>

TL1_DaRspBlk::TL1_DaRspBlk( ) :
    myBitSet( INDEX_END, false ),
    myPst(CT_SM_PST_NCRT),
    myPstq(CT_SM_PSTQ_DNE)
{
}

TL1_DaRspBlk::TL1_DaRspBlk( string                  theEntityName,
                            CT_TL1_DiscoveryAgentAddr theAddr,
                            CT_TL1_LinkAddr         theDcnLinkAddr,
                            string                  theMgtDomain,
                            CT_SM_PST               thePST,
                            CT_SM_PSTQ              thePSTQ)

    : myBitSet( INDEX_END, false )
{
    myBitSet[ INDEX_Addr ] = true;
    myDaAddr = theAddr;
    
    myBitSet[ INDEX_EntityName ] = true;
    myEntityName = theEntityName;

    myBitSet[ INDEX_DcnLinkAddr ] = true;
    myDcnLinkAddr = theDcnLinkAddr;

    myBitSet[ INDEX_MgtDomain ] = true;
    myMgtDomain = theMgtDomain;

    myBitSet[ INDEX_PST ] = true;
    myPst = thePST;

    myBitSet[ INDEX_PSTQ ] = true;
    myPstq = thePSTQ;
}

TL1_DaRspBlk::TL1_DaRspBlk( const TL1_DaRspBlk& theRspBlk ) :
    myBitSet( INDEX_END, false )
{
    myBitSet = theRspBlk.myBitSet;
    myDaAddr= theRspBlk.myDaAddr;
    myEntityName= theRspBlk.myEntityName;
    myDcnLinkAddr= theRspBlk.myDcnLinkAddr;
    myMgtDomain= theRspBlk.myMgtDomain;
    myPst= theRspBlk.myPst;
    myPstq= theRspBlk.myPstq;
}

TL1_DaRspBlk::~TL1_DaRspBlk( )
{
}

TL1_DaRspBlk& 
TL1_DaRspBlk::operator=( const TL1_DaRspBlk& theRspBlk )
{
    myBitSet = theRspBlk.myBitSet;
    myDaAddr= theRspBlk.myDaAddr;
    myEntityName= theRspBlk.myEntityName;
    myDcnLinkAddr= theRspBlk.myDcnLinkAddr;
    myMgtDomain= theRspBlk.myMgtDomain;
    myPst= theRspBlk.myPst;
    myPstq = theRspBlk.myPstq;


    return *this;
}

bool 
TL1_DaRspBlk::operator==( const TL1_DaRspBlk& theRspBlk ) const
{
    if ( myBitSet != theRspBlk.myBitSet )           return false;
    if ( myDaAddr != theRspBlk.myDaAddr )           return false;
    if ( myEntityName != theRspBlk.myEntityName )   return false;
    if ( myDcnLinkAddr != theRspBlk.myDcnLinkAddr)          return false;
    if ( myMgtDomain != theRspBlk.myMgtDomain )     return false;
    if ( myPst != theRspBlk.myPst )                 return false;
    if ( myPstq != theRspBlk.myPstq )               return false;


    return true;
}

//--------------------------------------------------------------
void 
TL1_DaRspBlk::SetAddr( const CT_TL1_DiscoveryAgentAddr& theAddr )
{
    myBitSet[ INDEX_Addr ] = true;
    myDaAddr = theAddr;
}

//--------------------------------------------------------------
void 
TL1_DaRspBlk::SetEntityName( const string& theEntityName )
{
    myBitSet[ INDEX_EntityName ] = true;
    myEntityName= theEntityName;
}

//--------------------------------------------------------------
void
TL1_DaRspBlk::SetDcnLinkAddr( const CT_TL1_LinkAddr& theDcnLinkAddr )
{
    myBitSet[ INDEX_DcnLinkAddr ] = true;
    myDcnLinkAddr = theDcnLinkAddr;
}

//--------------------------------------------------------------
void
TL1_DaRspBlk::SetMgtDomain( const string& theMgtDomain )
{
    myBitSet[ INDEX_MgtDomain ] = true;
    myMgtDomain = theMgtDomain;
}

//--------------------------------------------------------------
void 
TL1_DaRspBlk::SetPST( const CT_SM_PST& thePst )
{
    myBitSet[ INDEX_PST ] = true;
    myPst= thePst;
}

//--------------------------------------------------------------
void 
TL1_DaRspBlk::SetPSTQ( const CT_SM_PSTQ& thePstq )
{
    myBitSet[ INDEX_PSTQ ] = true;
    myPstq= thePstq;
}

//--------------------------------------------------------------
bool 
TL1_DaRspBlk::GetAddr( CT_TL1_DiscoveryAgentAddr& theAddr) const
{
    if( true == myBitSet[ INDEX_Addr ] )
    {
        theAddr = myDaAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_DaRspBlk::GetEntityName( string& theEntityName) const
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

//--------------------------------------------------------------
bool 
TL1_DaRspBlk::GetDcnLinkAddr( CT_TL1_LinkAddr& theAddr) const
{
    if( true == myBitSet[ INDEX_DcnLinkAddr ] )
    {
        theAddr = myDcnLinkAddr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_DaRspBlk::GetMgtDomain( string& theMgtDomain) const
{
    if( true == myBitSet[ INDEX_MgtDomain ] )
    {
        theMgtDomain = myMgtDomain;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_DaRspBlk::GetPST(CT_SM_PST& thePst) const
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        thePst = myPst;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
bool 
TL1_DaRspBlk::GetPSTQ(CT_SM_PSTQ& thePstq) const
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        thePstq = myPstq;
        return true;
    }
    else
    {
        return false;
    }
}
