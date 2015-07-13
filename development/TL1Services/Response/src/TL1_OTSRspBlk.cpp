/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OTS Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 OTS Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_OTSRspBlk.h>

TL1_OTSRspBlk::TL1_OTSRspBlk():
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS)
{;}

TL1_OTSRspBlk::TL1_OTSRspBlk(const string *theEntityName,
                  const CT_TL1_FacAddr* theAddr,
                  const CT_CardType* theCardType,
                  const CT_SubCardType* theSubCardType,
                  const bool* isAutoAdjustOutPowerEnabled,
                  const bool* isAutoAdjustInPowerEnabled,
                  const bool* isAutoTxPowerShutdownEnabled,
                  const CT_Fac_TraceString* theExpectedTrace,
                  const CT_Fac_TraceString* theSentTrace,
                  const bool* isMonitorTraceEnabled,
                  const CT_ProfileTableId* theAlarmProfile,
                  const CT_FAC_OtsChanMap* theChanMap,
                  const CT_FAC_OtsChanType* theChanType,
                  const CT_SM_PST*  thePST,
                  const CT_SM_PSTQ* thePSTQ,
                  const CT_SM_SST*  theSST)
    : myBitSet( INDEX_END, false ),
      myAlarmProfile(CT_UNKNOWN_PT),
      myAutoAdjustInPowerEnabled(false),
      myAutoAdjustOutPowerEnabled(false),
      myAutoTxPowerShutdownEnabled(false),
      myCardType(0),
      myChanType(CT_ChanType_MIXED),
      myMonitorTraceEnabled(false),
      myPST(CT_SM_PST_NCRT),
      myPSTQ(CT_SM_PSTQ_ANR),
      mySST(CT_SM_SST_LASTRVTFAIL),
      mySubCardType(ALL_SUB_CARD_TYPE)
{
    if (theAddr)
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *theAddr;
    }
    else
    {
        myFacAddr = CT_TL1_FacAddr();
    }

    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }
    
    if( theCardType)
    {
        myBitSet[ INDEX_CardType ] = true;
        myCardType = *theCardType;
    }

    if( theSubCardType)
    {
        myBitSet[ INDEX_SubCardType ] = true;
        mySubCardType = *theSubCardType;
    }

    if( isAutoAdjustOutPowerEnabled )
    {
        myBitSet[ INDEX_AutoAdjustOutPowerEnabled ] = true;
        myAutoAdjustOutPowerEnabled = *isAutoAdjustOutPowerEnabled;
    }

    if( isAutoAdjustInPowerEnabled)
    {
        myBitSet[ INDEX_AutoAdjustInPowerEnabled ] = true;
        myAutoAdjustInPowerEnabled = *isAutoAdjustInPowerEnabled;
    }

    if( isAutoTxPowerShutdownEnabled)
    {
        myBitSet[ INDEX_AutoTxPowerShutdownEnabled ] = true;
        myAutoTxPowerShutdownEnabled = *isAutoTxPowerShutdownEnabled;
    }

    if( theExpectedTrace )
    {
        myBitSet[ INDEX_ExpectedTrace ] = true;
        myExpectedTrace = *theExpectedTrace;
    }

    if( theSentTrace )
    {
        myBitSet[ INDEX_SentTrace ] = true;
        mySentTrace = *theSentTrace;
    }

    if( isMonitorTraceEnabled )
    {
        myBitSet[ INDEX_MonitorTraceEnabled ] = true;
        myMonitorTraceEnabled = *isMonitorTraceEnabled;
    }

    if(theAlarmProfile)
    {
        myBitSet[ INDEX_AlarmProfile ] = true;
        myAlarmProfile = *theAlarmProfile;
    }

    if(theChanMap)
    {
        myBitSet[ INDEX_ChanMap ] = true;
        myChanMap = *theChanMap;
    }

    if(theChanType)
    {
        myBitSet[ INDEX_ChanType ] = true;
        myChanType = *theChanType;
    }

    if(thePST)
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }

    if(thePSTQ)
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }

    if(theSST)
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
}

TL1_OTSRspBlk::TL1_OTSRspBlk(const TL1_OTSRspBlk& otsBlk)
    : myBitSet( INDEX_END, false ), myFacAddr(otsBlk.myFacAddr)
{
    myBitSet                    = otsBlk.myBitSet;
    myEntityName                = otsBlk.myEntityName;
    myCardType                  = otsBlk.myCardType;
    mySubCardType               = otsBlk.mySubCardType;
    myExpectedTrace             = otsBlk.myExpectedTrace;
    mySentTrace                 = otsBlk.mySentTrace;
    myMonitorTraceEnabled       = otsBlk.myMonitorTraceEnabled;
    myAutoAdjustOutPowerEnabled = otsBlk.myAutoAdjustOutPowerEnabled;
    myAutoAdjustInPowerEnabled  = otsBlk.myAutoAdjustInPowerEnabled;
    myAutoTxPowerShutdownEnabled= otsBlk.myAutoTxPowerShutdownEnabled;
    myAlarmProfile              = otsBlk.myAlarmProfile;
    myChanMap                   = otsBlk.myChanMap;
    myChanType                  = otsBlk.myChanType;
    myPST                       = otsBlk.myPST;
    myPSTQ                      = otsBlk.myPSTQ;
    mySST                       = otsBlk.mySST;

}

TL1_OTSRspBlk::~TL1_OTSRspBlk()
{
}

TL1_OTSRspBlk& TL1_OTSRspBlk::operator=( const TL1_OTSRspBlk& theBlock )
{
    myBitSet                    = theBlock.myBitSet;
    myEntityName                = theBlock.myEntityName;
    myCardType                  = theBlock.myCardType;
    mySubCardType               = theBlock.mySubCardType;
    myExpectedTrace             = theBlock.myExpectedTrace;
    mySentTrace                 = theBlock.mySentTrace;
    myMonitorTraceEnabled       = theBlock.myMonitorTraceEnabled;
    myAutoAdjustOutPowerEnabled = theBlock.myAutoAdjustOutPowerEnabled;
    myAutoAdjustInPowerEnabled  = theBlock.myAutoAdjustInPowerEnabled;
    myAutoTxPowerShutdownEnabled= theBlock.myAutoTxPowerShutdownEnabled;
    myAlarmProfile              = theBlock.myAlarmProfile;
    myChanMap                   = theBlock.myChanMap;
    myChanType                  = theBlock.myChanType;
    myPST                       = theBlock.myPST;
    myPSTQ                      = theBlock.myPSTQ;
    mySST                       = theBlock.mySST;

    return *this;
}

bool TL1_OTSRspBlk::operator==( const TL1_OTSRspBlk& theBlock ) const
{
    return ( myBitSet                    == theBlock.myBitSet &&
             myEntityName                == theBlock.myEntityName &&
             myCardType                  == theBlock.myCardType &&
             mySubCardType               == theBlock.mySubCardType &&
             myExpectedTrace             == theBlock.myExpectedTrace &&
             mySentTrace                 == theBlock.mySentTrace &&
             myMonitorTraceEnabled       == theBlock.myMonitorTraceEnabled &&
             myAutoAdjustOutPowerEnabled == theBlock.myAutoAdjustOutPowerEnabled &&
             myAutoAdjustInPowerEnabled  == theBlock.myAutoAdjustInPowerEnabled &&
             myAutoTxPowerShutdownEnabled== theBlock.myAutoTxPowerShutdownEnabled &&
             myAlarmProfile              == theBlock.myAlarmProfile &&
             myChanMap                   == theBlock.myChanMap &&
             myChanType                  == theBlock.myChanType &&
             myPST                       == theBlock.myPST &&
             myPSTQ                      == theBlock.myPSTQ &&
             mySST                       == theBlock.mySST );
}

bool TL1_OTSRspBlk::GetEntityName(string& theEntityName ) const
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

bool TL1_OTSRspBlk::GetFacAddr(CT_TL1_FacAddr& theFacAddr ) const
{
    if( true == myBitSet[ INDEX_FacAddr ] )
    {
        theFacAddr = myFacAddr;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetCardType(CT_CardType& theCardType ) const
{
    if( true == myBitSet[ INDEX_CardType ] )
    {
        theCardType = myCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetSubCardType(CT_SubCardType& theSubCardType ) const
{
    if( true == myBitSet[ INDEX_SubCardType ] )
    {
        theSubCardType = mySubCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetAutoAdjustOutPowerEnabled(bool& theAutoAdjustOutPowerEnabled ) const
{
    if( true == myBitSet[ INDEX_AutoAdjustOutPowerEnabled ] )
    {
        theAutoAdjustOutPowerEnabled = myAutoAdjustOutPowerEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetAutoAdjustInPowerEnabled(bool& theAutoAdjustInPowerEnabled ) const
{
    if( true == myBitSet[ INDEX_AutoAdjustInPowerEnabled ] )
    {
        theAutoAdjustInPowerEnabled = myAutoAdjustInPowerEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetAutoTxPowerShutdownEnabled(bool& theAutoTxPowerShutdownEnabled ) const
{
    if( true == myBitSet[ INDEX_AutoTxPowerShutdownEnabled ] )
    {
        theAutoTxPowerShutdownEnabled = myAutoTxPowerShutdownEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetExpectedTrace( CT_Fac_TraceString& theExpectedTrace) const
{
    if( true == myBitSet[ INDEX_ExpectedTrace ] )
    {
        theExpectedTrace = myExpectedTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetSentTrace( CT_Fac_TraceString& theSentTrace) const
{
    if( true == myBitSet[ INDEX_SentTrace ] )
    {
        theSentTrace = mySentTrace;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetMonitorTraceEnabled( bool& theMonitorTraceEnabled) const
{
    if( true == myBitSet[ INDEX_MonitorTraceEnabled ] )
    {
        theMonitorTraceEnabled = myMonitorTraceEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile) const
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

bool TL1_OTSRspBlk::GetChanMap(CT_FAC_OtsChanMap& theChanMap) const
{
    if( true == myBitSet[ INDEX_ChanMap ] )
    {
        theChanMap = myChanMap;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetChanType(CT_FAC_OtsChanType& theChanType) const
{
    if( true == myBitSet[ INDEX_ChanType ] )
    {
        theChanType = myChanType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OTSRspBlk::GetPST( CT_SM_PST& thePST) const
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

bool TL1_OTSRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ) const
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

bool TL1_OTSRspBlk::GetSST( CT_SM_SST& theSST) const
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

CT_SM_PST TL1_OTSRspBlk::GetPST() const
{
    return myPST;
}
CT_SM_PSTQ TL1_OTSRspBlk::GetPSTQ() const
{
    return myPSTQ;
}
CT_SM_SST TL1_OTSRspBlk::GetSST() const
{
    return mySST;
}