/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OSC Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 OSC/X Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_OSCRspBlk.h>

TL1_OSCRspBlk::TL1_OSCRspBlk():
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS)
{;}

TL1_OSCRspBlk::TL1_OSCRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_CardType *CardType,
                  const CT_SubCardType *SubCardType,
                  const bool *IsEonMsgEnabled,
                  const CT_FAC_RxSsm* theSsmReceived,
                  const CT_TEL_MsTref* theTimingReference,
                  const CT_TEL_TxTiming* theTxTiming,
                  const CT_ProfileTableId *ID,
                  const CT_SM_PST *PST,
                  const CT_SM_PSTQ *PSTQ,
                  const CT_SM_SST *SST )
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

    if( IsEonMsgEnabled )
    {
        myBitSet[ INDEX_IsEonMsgEnabled ] = true;
        myIsEonMsgEnabled = *IsEonMsgEnabled;
    }

    if(ID)
    {
        myBitSet[ INDEX_ID ] = true;
        myID = *ID;
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

    if(theSsmReceived)
    {
        myBitSet[ INDEX_SsmReceived ] = true;
        mySsmReceived = *theSsmReceived;
    }

    if(theTimingReference)
    {
        myBitSet[ INDEX_TimingRef ] = true;
        myTimingRef = *theTimingReference;
    }

    if(theTxTiming)
    {
        myBitSet[ INDEX_TxTiming ] = true;
        myTxTiming = *theTxTiming;
    }


}

TL1_OSCRspBlk::TL1_OSCRspBlk(const TL1_OSCRspBlk& oscBlk)
    : myBitSet( INDEX_END, false ), myFacAddr( oscBlk.myFacAddr)
{
    myBitSet        = oscBlk.myBitSet;
    myEntityName    = oscBlk.myEntityName;
    myCardType      = oscBlk.myCardType;
    mySubCardType   = oscBlk.mySubCardType;
    myIsEonMsgEnabled = oscBlk.myIsEonMsgEnabled;
    myID            = oscBlk.myID;
    myPST           = oscBlk.myPST;
    myPSTQ          = oscBlk.myPSTQ;
    mySST           = oscBlk.mySST;
    mySsmReceived   = oscBlk.mySsmReceived;
    myTimingRef     = oscBlk.myTimingRef;
    myTxTiming      = oscBlk.myTxTiming;
}

TL1_OSCRspBlk::~TL1_OSCRspBlk()
{
}

TL1_OSCRspBlk& TL1_OSCRspBlk::operator=( const TL1_OSCRspBlk& theBlock )
{
    myFacAddr       = theBlock.myFacAddr;
    myBitSet        = theBlock.myBitSet;
    myEntityName    = theBlock.myEntityName;
    myCardType      = theBlock.myCardType;
    mySubCardType   = theBlock.mySubCardType;
    myIsEonMsgEnabled = theBlock.myIsEonMsgEnabled;
    myID            = theBlock.myID;
    myPST           = theBlock.myPST;
    myPSTQ          = theBlock.myPSTQ;
    mySST           = theBlock.mySST;
    mySsmReceived   = theBlock.mySsmReceived;
    myTimingRef     = theBlock.myTimingRef;
    myTxTiming      = theBlock.myTxTiming;
    return *this;
}

bool TL1_OSCRspBlk::operator==( const TL1_OSCRspBlk& theBlock ) const
{
    return ( myFacAddr       == theBlock.myFacAddr &&
             myBitSet        == theBlock.myBitSet &&
             myEntityName    == theBlock.myEntityName &&
             myCardType      == theBlock.myCardType &&
             mySubCardType   == theBlock.mySubCardType &&
             myIsEonMsgEnabled == theBlock.myIsEonMsgEnabled &&
             myID            == theBlock.myID &&
             myPST           == theBlock.myPST &&
             myPSTQ          == theBlock.myPSTQ &&
             mySST           == theBlock.mySST &&
             mySsmReceived   == theBlock.mySsmReceived &&
             myTimingRef     == theBlock.myTimingRef &&
             myTxTiming      == theBlock.myTxTiming);
}

bool TL1_OSCRspBlk::GetEntityName(string &EntityName ) const
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

bool TL1_OSCRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
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

bool TL1_OSCRspBlk::GetCardType(CT_CardType &CardType ) const
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

bool TL1_OSCRspBlk::GetSubCardType(CT_SubCardType &SubCardType ) const
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

bool TL1_OSCRspBlk::GetIsEonMsgEnabled( bool &IsEonMsgEnabled) const
{
    if( true == myBitSet[ INDEX_IsEonMsgEnabled ] )
    {
        IsEonMsgEnabled = myIsEonMsgEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OSCRspBlk::GetALMPF( CT_ProfileTableId &ID) const
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

bool TL1_OSCRspBlk::GetPST( CT_SM_PST &PST) const
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

bool TL1_OSCRspBlk::GetPSTQ( CT_SM_PSTQ &PSTQ) const
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

bool TL1_OSCRspBlk::GetSST( CT_SM_SST &SST) const
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

bool
TL1_OSCRspBlk::GetSsmReceived( CT_FAC_RxSsm& theSsmReceived ) const
{
    if( true == myBitSet[ INDEX_SsmReceived ] )
    {
        theSsmReceived = mySsmReceived;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OSCRspBlk::GetTimingRef( CT_TEL_MsTref& theTimingReference ) const
{
    if( true == myBitSet[ INDEX_TimingRef ] )
    {
        theTimingReference = myTimingRef;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OSCRspBlk::GetTxTiming( CT_TEL_TxTiming& theTxTiming) const
{
    if( true == myBitSet[ INDEX_TxTiming ] )
    {
        theTxTiming= myTxTiming;
        return true;
    }
    else
    {
        return false;
    }
}

CT_SM_PST TL1_OSCRspBlk::GetPST() const
{
    return myPST;
}
CT_SM_PSTQ TL1_OSCRspBlk::GetPSTQ() const
{
    return myPSTQ;
}
CT_SM_SST TL1_OSCRspBlk::GetSST() const
{
    return mySST;
}

// OSCX
TL1_OSCXRspBlk::TL1_OSCXRspBlk():
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS)
{;}

TL1_OSCXRspBlk::TL1_OSCXRspBlk(const string *EntityName,
                  const CT_TL1_FacAddr* FacAddr,
                  const CT_CardType *CardType,
                  const CT_SubCardType *SubCardType,
                  const bool *IsTrafficEnabled,
                  const bool *IsEonMsgEnabled,
                  const uint8 *NpOwner,
                  const CT_SM_PST *PST,
                  const CT_SM_PSTQ *PSTQ,
                  const CT_SM_SST *SST )
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

    if( IsTrafficEnabled )
    {
        myBitSet[ INDEX_IsTrafficEnabled ] = true;
        myIsTrafficEnabled = *IsTrafficEnabled;
    }

    if( IsEonMsgEnabled )
    {
        myBitSet[ INDEX_IsEonMsgEnabled ] = true;
        myIsEonMsgEnabled = *IsEonMsgEnabled;
    }

    if( NpOwner )
    {
        myBitSet[ INDEX_NpOwner ] = true;
        myNpOwner = *NpOwner;
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

TL1_OSCXRspBlk::TL1_OSCXRspBlk(const TL1_OSCXRspBlk& oscxBlk)
    : myBitSet( INDEX_END, false ), myFacAddr( oscxBlk.myFacAddr)
{
    myBitSet        = oscxBlk.myBitSet;
    myEntityName    = oscxBlk.myEntityName;
    myCardType      = oscxBlk.myCardType;
    mySubCardType   = oscxBlk.mySubCardType;
    myIsTrafficEnabled = oscxBlk.myIsTrafficEnabled;
    myIsEonMsgEnabled = oscxBlk.myIsEonMsgEnabled;
    myNpOwner       = oscxBlk.myNpOwner;
    myPST           = oscxBlk.myPST;
    myPSTQ          = oscxBlk.myPSTQ;
    mySST           = oscxBlk.mySST;
}

TL1_OSCXRspBlk::~TL1_OSCXRspBlk()
{
}

TL1_OSCXRspBlk& TL1_OSCXRspBlk::operator=( const TL1_OSCXRspBlk& theBlock )
{
    myFacAddr       = theBlock.myFacAddr;
    myBitSet        = theBlock.myBitSet;
    myEntityName    = theBlock.myEntityName;
    myCardType      = theBlock.myCardType;
    mySubCardType   = theBlock.mySubCardType;
    myIsTrafficEnabled = theBlock.myIsTrafficEnabled;
    myIsEonMsgEnabled = theBlock.myIsEonMsgEnabled;
    myNpOwner       = theBlock.myNpOwner;
    myPST           = theBlock.myPST;
    myPSTQ          = theBlock.myPSTQ;
    mySST           = theBlock.mySST;

    return *this;
}

bool TL1_OSCXRspBlk::operator==( const TL1_OSCXRspBlk& theBlock ) const
{
    return ( myFacAddr       == theBlock.myFacAddr &&
             myBitSet        == theBlock.myBitSet &&
             myEntityName    == theBlock.myEntityName &&
             myCardType      == theBlock.myCardType &&
             mySubCardType   == theBlock.mySubCardType &&
             myIsTrafficEnabled == theBlock.myIsTrafficEnabled &&
             myIsEonMsgEnabled == theBlock.myIsEonMsgEnabled &&
             myNpOwner       == theBlock.myNpOwner &&
             myPST           == theBlock.myPST &&
             myPSTQ          == theBlock.myPSTQ &&
             mySST           == theBlock.mySST );
}

bool TL1_OSCXRspBlk::GetEntityName(string &EntityName ) const
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

bool TL1_OSCXRspBlk::GetFacAddr(CT_TL1_FacAddr& FacAddr ) const
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

bool TL1_OSCXRspBlk::GetCardType(CT_CardType &CardType ) const
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

bool TL1_OSCXRspBlk::GetSubCardType(CT_SubCardType &SubCardType ) const
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

bool TL1_OSCXRspBlk::GetIsTrafficEnabled( bool &IsTrafficEnabled) const
{
    if( true == myBitSet[ INDEX_IsTrafficEnabled ] )
    {
        IsTrafficEnabled = myIsTrafficEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OSCXRspBlk::GetIsEonMsgEnabled( bool &IsEonMsgEnabled) const
{
    if( true == myBitSet[ INDEX_IsEonMsgEnabled ] )
    {
        IsEonMsgEnabled = myIsEonMsgEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OSCXRspBlk::GetNpOwner( uint8 &NpOwner) const
{
    if( true == myBitSet[ INDEX_NpOwner ] )
    {
        NpOwner = myNpOwner;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OSCXRspBlk::GetPST( CT_SM_PST &PST) const
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

bool TL1_OSCXRspBlk::GetPSTQ( CT_SM_PSTQ &PSTQ) const
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

bool TL1_OSCXRspBlk::GetSST( CT_SM_SST &SST) const
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


CT_SM_PST TL1_OSCXRspBlk::GetPST() const
{
    return myPST;
}
CT_SM_PSTQ TL1_OSCXRspBlk::GetPSTQ() const
{
    return myPSTQ;
}
CT_SM_SST TL1_OSCXRspBlk::GetSST() const
{
    return mySST;
}
