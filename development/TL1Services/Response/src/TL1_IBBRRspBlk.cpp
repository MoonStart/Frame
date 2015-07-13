/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      
TARGET:
AUTHOR:         
DESCRIPTION:    
-----------------------------------------------------------------------------*/

#include <Response/TL1_IBBRRspBlk.h>

TL1_IBBRRspBlk::TL1_IBBRRspBlk(const TL1_SmartParameter<string>& theBridgeAid,
                   const TL1_SmartParameter<int>& theVs,
                   const TL1_SmartParameter<int>& theBridgeVlan,
                   const TL1_SmartParameter<string>& theIp,
                   const TL1_SmartParameter<string>& theIpmask,
                   const TL1_SmartParameter<CT_SM_PST>& thePST,
                   const TL1_SmartParameter<CT_SM_SST>& theSST,
                   const TL1_SmartParameter<CT_SM_PSTQ>& thePSTQ) : 
    myBridgeAid(theBridgeAid),
    myVs(theVs),
    myBridgeVlan(theBridgeVlan),
    myIp(theIp),
    myIpmask(theIpmask),
    myPST(thePST),
    mySST(theSST),
    myPSTQ(thePSTQ)
{
}
  
TL1_IBBRRspBlk::TL1_IBBRRspBlk(const TL1_IBBRRspBlk& theBlock) :
    myBridgeAid(theBlock.myBridgeAid),
    myVs(theBlock.myVs),
    myBridgeVlan(theBlock.myBridgeVlan),
    myIp(theBlock.myIp),
    myIpmask(theBlock.myIpmask),
    myPST(theBlock.myPST),
    mySST(theBlock.mySST),
    myPSTQ(theBlock.myPSTQ)
    
{
}

TL1_IBBRRspBlk::~TL1_IBBRRspBlk()
{
}

TL1_IBBRRspBlk& TL1_IBBRRspBlk::operator=( const TL1_IBBRRspBlk& theBlock )
{
    myBridgeAid = theBlock.myBridgeAid;
    myVs = theBlock.myVs;
    myBridgeVlan = theBlock.myBridgeVlan;
    myIp = theBlock.myIp;
	myIpmask = theBlock.myIpmask;
    myPST = theBlock.myPST;
    mySST = theBlock.mySST;
   	myPSTQ = theBlock.myPSTQ;
	
    return *this;
}


const TL1_SmartParameter<string>& TL1_IBBRRspBlk::GetBridgeAid() const
{
    return myBridgeAid;
}

const TL1_SmartParameter<int>& TL1_IBBRRspBlk::GetVs() const
{
    return myVs;
}

const TL1_SmartParameter<int>& TL1_IBBRRspBlk::GetBridgeVlan() const
{
    return myBridgeVlan;
}

const TL1_SmartParameter<string>& TL1_IBBRRspBlk::GetIp() const
{
    return myIp;
}

const TL1_SmartParameter<string>& TL1_IBBRRspBlk::GetIpmask() const
{
    return myIpmask;
}

const TL1_SmartParameter<CT_SM_PST>& TL1_IBBRRspBlk::GetPST() const
{
    return myPST;
}

const TL1_SmartParameter<CT_SM_SST>& TL1_IBBRRspBlk::GetSST() const
{
    return mySST;
}

const TL1_SmartParameter<CT_SM_PSTQ>& TL1_IBBRRspBlk::GetPSTQ() const
{
    return myPSTQ;
}

