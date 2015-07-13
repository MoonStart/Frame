/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1Services
TARGET:          
AUTHOR:         May 7, 2003- Jean-Francois Emond
DESCRIPTION:    Implementation file for TL1 Rmv Rst response block
-----------------------------------------------------------------------------*/ 

#include <Response/TL1_StateRspBlk.h>

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_SlotAddr >& theSlotAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsSlotAddr( theSlotAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_FacAddr >& theFacAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsFacAddr( theFacAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_CrsAddr >& theCrsAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsCrsAddr( theCrsAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_ProtnAddr >& theProtnAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsProtnAddr( theProtnAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_LogicalAddr >& theNtpAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsNtpAddr( theNtpAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_RpMapAddr >& theRpMapAddr ) :
    itsEntityName( theEntityName ),
    itsRpMapAddr( theRpMapAddr )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_RpAddr >& theRpAddr ) :
    itsEntityName( theEntityName ),
    itsRpAddr( theRpAddr )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_NetworkPartitionAddr >& theNpAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsNpAddr( theNpAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_NodeAddr >& theNodeAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsNodeAddr( theNodeAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_DiscoveryAgentAddr >& theDaAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsDaAddr( theDaAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_LinkAddr >& theLinkAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsLinkAddr( theLinkAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_ControllerAddr >& theControllerAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsControllerAddr( theControllerAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_AdjacencyAddr >& theAdjacencyAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsAdjacencyAddr( theAdjacencyAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_TL1_AreaAddr >& theAreaAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsAreaAddr( theAreaAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theFtpServer ) :
    itsFtpServer( theFtpServer )
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_SwitchDomain >& theSwitchDomainAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsSwitchDomainAddr( theSwitchDomainAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}

TL1_StateRspBlk::~TL1_StateRspBlk()
{
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_StateRspBlk& theBlock ) :
    itsEntityName( theBlock.itsEntityName ),
    itsFtpServer( theBlock.itsFtpServer ),
    itsSlotAddr( theBlock.itsSlotAddr ),
    itsFacAddr( theBlock.itsFacAddr ),
    itsCrsAddr( theBlock.itsCrsAddr ),
    itsEvcAddr( theBlock.itsEvcAddr ),
    itsProtnAddr( theBlock.itsProtnAddr ),
    itsNtpAddr( theBlock.itsNtpAddr ),
    itsRpMapAddr( theBlock.itsRpMapAddr ),
    itsRpAddr( theBlock.itsRpAddr ),
    itsNpAddr( theBlock.itsNpAddr ),
    itsNodeAddr( theBlock.itsNodeAddr ),
    itsDaAddr( theBlock.itsDaAddr ),
    itsLinkAddr( theBlock.itsLinkAddr ),
    itsControllerAddr( theBlock.itsControllerAddr ),
    itsAdjacencyAddr( theBlock.itsAdjacencyAddr ),
    itsAreaAddr( theBlock.itsAreaAddr ),
    itsSwitchDomainAddr( theBlock.itsSwitchDomainAddr ),
    itsPST( theBlock.itsPST ),
    itsPSTQ( theBlock.itsPSTQ ),
    itsSST( theBlock.itsSST )
{
}

TL1_StateRspBlk& TL1_StateRspBlk::operator=( const TL1_StateRspBlk& theBlock )
{
    itsEntityName = theBlock.itsEntityName;
    itsFtpServer = theBlock.itsFtpServer;
    itsSlotAddr = theBlock.itsSlotAddr;
    itsFacAddr = theBlock.itsFacAddr;
    itsCrsAddr = theBlock.itsCrsAddr;
    itsEvcAddr = theBlock.itsEvcAddr;
    itsProtnAddr = theBlock.itsProtnAddr;
    itsNtpAddr = theBlock.itsNtpAddr;
    itsRpMapAddr = theBlock.itsRpMapAddr;
    itsRpAddr = theBlock.itsRpAddr;
    itsNpAddr = theBlock.itsNpAddr;
    itsNodeAddr = theBlock.itsNodeAddr;
    itsDaAddr = theBlock.itsDaAddr;
    itsLinkAddr = theBlock.itsLinkAddr;
    itsControllerAddr = theBlock.itsControllerAddr;
    itsAdjacencyAddr = theBlock.itsAdjacencyAddr;
    itsAreaAddr = theBlock.itsAreaAddr;
    itsSwitchDomainAddr = theBlock.itsSwitchDomainAddr;
    itsPST = theBlock.itsPST;
    itsPSTQ = theBlock.itsPSTQ;
    itsSST = theBlock.itsSST;

    return *this;
}

TL1_StateRspBlk::TL1_StateRspBlk( const TL1_SmartParameter< string >& theEntityName,
                                  const TL1_SmartParameter< CT_EvcData >& theEvcAddr,
                                  const TL1_SmartParameter< CT_SM_PST >& thePST,
                                  const TL1_SmartParameter< CT_SM_PSTQ >& thePSTQ,
                                  const TL1_SmartParameter< CT_SM_SST >& theSST ) :
    itsEntityName( theEntityName ),
    itsEvcAddr( theEvcAddr ),
    itsPST( thePST ),
    itsPSTQ( thePSTQ ),
    itsSST( theSST )
{
}