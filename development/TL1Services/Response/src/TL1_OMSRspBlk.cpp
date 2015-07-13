/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OMS Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 OMS Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_OMSRspBlk.h>

TL1_OMSRspBlk::TL1_OMSRspBlk():
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS)
{;}

TL1_OMSRspBlk::TL1_OMSRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_CardType *CardType,
                  const CT_SubCardType *SubCardType,
                  const CT_ProfileTableId *ID,
                  const bool* isAutoAdjustAttenuationEnabled,
                  const CT_SM_PST *PST,
                  const CT_SM_PSTQ *PSTQ,
                  const CT_SM_SST *SST)
    : myBitSet( INDEX_END, false )
{
    if( EntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *EntityName;
    }

    if( FacAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *FacAddr;
    }

    if( CardType)
    {
        myBitSet[ INDEX_CardType ] = true;
        myCardType = *CardType;
    }

    if( SubCardType)
    {
        myBitSet[ INDEX_SubCardType ] = true;
        mySubCardType = *SubCardType;
    }

    if(ID)
    {
        myBitSet[ INDEX_ID ] = true;
        myID = *ID;
    }

    if(isAutoAdjustAttenuationEnabled)
    {
        myBitSet[ INDEX_AutoAdjustAttenuationEnabled ] = true;
        myAutoAdjustAttenuationEnabled = *isAutoAdjustAttenuationEnabled;
    }

    if(PST)
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *PST;
    }

    if(PSTQ)
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *PSTQ;
    }

    if(SST)
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *SST;
    }

}

TL1_OMSRspBlk::TL1_OMSRspBlk(const TL1_OMSRspBlk& omsBlk)
    : myBitSet( INDEX_END, false ), myFacAddr(omsBlk.myFacAddr)
{
    myBitSet        = omsBlk.myBitSet;
    myEntityName    = omsBlk.myEntityName;
    myCardType      = omsBlk.myCardType;
    mySubCardType   = omsBlk.mySubCardType;
    myID            = omsBlk.myID;
    myAutoAdjustAttenuationEnabled = omsBlk.myAutoAdjustAttenuationEnabled;
    myPST           = omsBlk.myPST;
    myPSTQ          = omsBlk.myPSTQ;
    mySST           = omsBlk.mySST;
}

TL1_OMSRspBlk::~TL1_OMSRspBlk()
{
}

TL1_OMSRspBlk& TL1_OMSRspBlk::operator=( const TL1_OMSRspBlk& theBlock )
{
    myBitSet        = theBlock.myBitSet;
    myFacAddr       = theBlock.myFacAddr;
    myEntityName    = theBlock.myEntityName;
    myCardType      = theBlock.myCardType;
    mySubCardType   = theBlock.mySubCardType;
    myID            = theBlock.myID;
    myAutoAdjustAttenuationEnabled = theBlock.myAutoAdjustAttenuationEnabled;
    myPST           = theBlock.myPST;
    myPSTQ          = theBlock.myPSTQ;
    mySST           = theBlock.mySST;

    return *this;
}

bool TL1_OMSRspBlk::operator==( const TL1_OMSRspBlk& theBlock ) const
{
    return ( myBitSet        == theBlock.myBitSet &&
             myFacAddr       == theBlock.myFacAddr &&
             myEntityName    == theBlock.myEntityName &&
             myCardType      == theBlock.myCardType &&
             mySubCardType   == theBlock.mySubCardType &&
             myID            == theBlock.myID &&
             myAutoAdjustAttenuationEnabled == theBlock.myAutoAdjustAttenuationEnabled &&
             myPST           == theBlock.myPST &&
             myPSTQ          == theBlock.myPSTQ &&
             mySST           == theBlock.mySST );
}

bool TL1_OMSRspBlk::GetEntityName(string &EntityName ) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
    {
        EntityName = myEntityName;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        FacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetCardType(CT_CardType &CardType ) const
{
    if( true == myBitSet[ INDEX_CardType ] )
    {
        CardType = myCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetSubCardType(CT_SubCardType &SubCardType ) const
{
    if( true == myBitSet[ INDEX_SubCardType ] )
    {
        SubCardType = mySubCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetALMPF( CT_ProfileTableId &ID) const
{
    if( true == myBitSet[ INDEX_ID ] )
    {
        ID = myID;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetAutoAdjustAttenuationEnabled(bool& theAutoAdjustAttenuationEnabled) const
{
    if( true == myBitSet[ INDEX_AutoAdjustAttenuationEnabled ] )
    {
        theAutoAdjustAttenuationEnabled = myAutoAdjustAttenuationEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetPST( CT_SM_PST &PST) const
{
    if( true == myBitSet[ INDEX_PST ] )
    {
        PST = myPST;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetPSTQ( CT_SM_PSTQ &PSTQ) const
{
    if( true == myBitSet[ INDEX_PSTQ ] )
    {
        PSTQ = myPSTQ;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OMSRspBlk::GetSST( CT_SM_SST &SST) const
{
    if( true == myBitSet[ INDEX_SST ] )
    {
        SST = mySST;
        return true;
    }
    else
    {
        return false;
    }
}

CT_SM_PST TL1_OMSRspBlk::GetPST() const
{
    return myPST;
}
CT_SM_PSTQ TL1_OMSRspBlk::GetPSTQ() const
{
    return myPSTQ;
}
CT_SM_SST TL1_OMSRspBlk::GetSST() const
{
    return mySST;
}
