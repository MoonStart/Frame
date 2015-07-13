/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 LABELSET Response 
TARGET:
AUTHOR:         November 16, 2010 - Tom Novak
DESCRIPTION:    Source file for TL1 LABELSET Response class 
-----------------------------------------------------------------------------*/

#include <Response/TL1_LabelSetRspBlk.h>

//---------------------------------------------------------------------------------------
TL1_LabelSetRspBlk::TL1_LabelSetRspBlk( ) :
    myBitSet( INDEX_END, false )
{
}

TL1_LabelSetRspBlk::~TL1_LabelSetRspBlk()
{
}

TL1_LabelSetRspBlk& 
TL1_LabelSetRspBlk::operator=( const TL1_LabelSetRspBlk& t1Blk )
{
    myLabelSetAddr =  t1Blk.myLabelSetAddr;
    myIngress=      t1Blk.myIngress;
    myEgress=      t1Blk.myEgress;
    IsIngressSet=   t1Blk.IsIngressSet;
    IsEgressSet=    t1Blk.IsIngressSet;

    return *this;
}

bool 
TL1_LabelSetRspBlk::operator==( const TL1_LabelSetRspBlk& t1Blk ) const
{
    if ( myLabelSetAddr != t1Blk.myLabelSetAddr )
        return false;

    if ( myIngress != t1Blk.myIngress )
        return false;

    if ( myEgress != t1Blk.myEgress )
        return false;

    if ( IsIngressSet != t1Blk.IsIngressSet )
        return false;

    if ( IsEgressSet != t1Blk.IsEgressSet )
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_LabelSetRspBlk::GetLabelSetAddr( CT_TL1_LabelSetAddr & theLabelSetAddr ) const
{
    if( true == myBitSet[ INDEX_LabelSetAddr ] )
    {
        theLabelSetAddr = myLabelSetAddr;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LabelSetRspBlk::SetLabelSetAddr( const CT_TL1_LabelSetAddr& theLabelSetAddr )
{
    myBitSet[ INDEX_LabelSetAddr ] = true;
    myLabelSetAddr = theLabelSetAddr;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_LabelSetRspBlk::GetIngress( CT_ControlPlane_LabelSet& theLabelSet ) const
{
    if( true == myBitSet[ INDEX_Ingress ] )
    {
        theLabelSet = myIngress;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LabelSetRspBlk::SetIngress( const CT_ControlPlane_LabelSet& theLabelSet )
{
    myBitSet[ INDEX_Ingress ] = true;
    myIngress = theLabelSet;
}

//-------------------------------------------------------------------------------------------------------
bool  
TL1_LabelSetRspBlk::GetEgress( CT_ControlPlane_LabelSet& theLabelSet ) const
{
    if( true == myBitSet[ INDEX_Egress ] )
    {
        theLabelSet = myEgress;
        return true;
    }
    else
    {
        return false;
    }
}

void  
TL1_LabelSetRspBlk::SetEgress( const CT_ControlPlane_LabelSet& theLabelSet )
{
    myBitSet[ INDEX_Egress ] = true;
    myEgress = theLabelSet;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_LabelSetRspBlk::GetIngressSet( bool& theIngressSet ) const
{
    if( true == myBitSet[ INDEX_IngSet ] )
    {
        theIngressSet = IsIngressSet;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LabelSetRspBlk::SetIngressSet( const bool& theIngressSet )
{
    myBitSet[ INDEX_IngSet ] = true;
    IsIngressSet = theIngressSet;
}

//-------------------------------------------------------------------------------------------------------
bool 
TL1_LabelSetRspBlk::GetEgressSet( bool& theEgressSet ) const
{
    if( true == myBitSet[ INDEX_EgSet ] )
    {
        theEgressSet = IsEgressSet;
        return true;
    }
    else
    {
        return false;
    }
}

void 
TL1_LabelSetRspBlk::SetEgressSet( const bool& theEgressSet )
{
    myBitSet[ INDEX_EgSet ] = true;
    IsEgressSet = theEgressSet;
}



