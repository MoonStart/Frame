/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 OCH Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 OCH Response class 
-----------------------------------------------------------------------------*/

#include <../TL1_OCHRspBlk.h>

TL1_OCHRspBlk::TL1_OCHRspBlk():
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS){;}

TL1_OCHRspBlk::TL1_OCHRspBlk(const string*                      theEntityName,
                             const CT_TL1_FacAddr*              theAddr,
                             const CT_CardType*                 theCardType,
                             const CT_SubCardType*              theSubCardType,
                             const bool*                        isAutoAdjustAttenuationEnabled,
                             const bool*                        isOtuMapEnabled,
                             const CT_Fac_TraceString*          theExpectedTrace,
                             const CT_Fac_TraceString*          theSentTrace,
                             const bool*                        isMonitorOtiEnabled,
                             const bool*                        isMonitorTraceEnabled,
                             const bool*                        isInsertAisEnabled,
                             const CT_Fac_TraceString*          theProtFunc,
                             const uint8*                       theNpOwner,
                             const CT_TEL_FecType*              theFecType,
                             const CT_TEL_SuperFec*             theSuperFec,
                             const CT_FAC_ExternalConnectivity* theConnectivity,
                             const CT_Fac_ConnectedToString*    theConnectedTo,
                             const CT_TEL_BERLevels*            theSDThreshold,
                             const CT_FAC_RxSsm*                theSsmReceived,
                             const CT_TEL_MsTref*               theTimingReference,
                             const int*                         theProtHoldOffTime,
                             const uint32*                         theExtChannel,
                             //const CT_RelativeWavelength*       theExtChannel,
                             const CT_TEL_OEO_REGEN_MODE*       theOeoRegen,
                             const CT_ProfileTableId*           theAlarmProfile,
                             const CT_TEL_ClkType*              theClkType,
                             const CT_TEL_OTIDStatus*           theOTIDStatus,
                             const CT_TEL_TimCriteriaMode*      theTimDef,
                             const CT_Fac_TraceString*          theExpDapi,
                             const CT_Fac_TraceString*          theExpSapi,
                             const CT_Fac_TraceString*          theTxDapi,
                             const CT_Fac_TraceString*          theTxSapi,
                             const uint16*                      theBurstyBerSdInterval,
                             const uint32*                      theBurstyBerSdThreshold,
                             const CT_Fac_TraceString*          theExpOperator,
                             const CT_Fac_TraceString*          theTxOperator,
                             const CT_SM_PST*                   thePST,
                             const CT_SM_PSTQ*                  thePSTQ,
                             const CT_SM_SST*                   theSST )
    : myBitSet( INDEX_END, false )
{
    if( theEntityName )
    {
        myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *theEntityName;
    }

    if( theAddr )
    {
        myBitSet[ INDEX_FacAddr ] = true;
        myFacAddr = *theAddr;
    }

    if( theCardType)
    {
        myBitSet[ INDEX_CardType ] = true;
        myCardType = *theCardType;
    }
	else
	{
		myCardType = 0;
	}

    if( theSubCardType)
    {
        myBitSet[ INDEX_SubCardType ] = true;
        mySubCardType = *theSubCardType;
    }
	else
	{
		mySubCardType = UNKNOWN_SUB_CT;
	}

    if( isAutoAdjustAttenuationEnabled )
    {
        myBitSet[ INDEX_AutoAdjustAttenuationEnabled ] = true;
        myAutoAdjustAttenuationEnabled = *isAutoAdjustAttenuationEnabled;
    }
	else
	{
		myAutoAdjustAttenuationEnabled = false;
	}

    if( isOtuMapEnabled)
    {
        myBitSet[ INDEX_OtuMapEnabled ] = true;
        myOtuMapEnabled = *isOtuMapEnabled;
    }
	else
	{
		myOtuMapEnabled = false;
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

    if ( theProtFunc )
    {
        myBitSet[ INDEX_ProtFunc ] = true;
        myProtFunc = *theProtFunc;
    }

    if( theNpOwner )
    {
        myBitSet[ INDEX_NpOwner ] = true;
        myNpOwner = *theNpOwner;
    }
	else
	{
		myNpOwner = 0;
	}

    if ( theFecType )
    {   
        myBitSet[ INDEX_FecType ] = true;
        myFecType = *theFecType;
    }
	else 
	{
		myFecType = CT_TEL_FEC_TYPE_UNKNOWN;
	}

    if ( theSuperFec )
    {   
        myBitSet[ INDEX_SuperFec ] = true;
        mySuperFec = *theSuperFec;
    }
    else
    {
        mySuperFec = CT_TEL_FEC_TYPE_SUPERFEC_UNKNOWN;
    }

    if( isMonitorOtiEnabled )
    {
        myBitSet[ INDEX_MonitorOtiEnabled ] = true;
        myMonitorOtiEnabled = *isMonitorOtiEnabled;
    }
	else
	{
		myMonitorOtiEnabled = false;
	}

    if( isMonitorTraceEnabled )
    {
        myBitSet[ INDEX_MonitorTraceEnabled ] = true;
        myMonitorTraceEnabled = *isMonitorTraceEnabled;
    }
	else
	{
		myMonitorTraceEnabled = false;
	}

    if( isInsertAisEnabled )
    {
        myBitSet[ INDEX_InsertAisEnabled ] = true;
        myInsertAisEnabled = *isInsertAisEnabled;
    }
	else
	{
		myInsertAisEnabled=false;
	}

    if( theConnectivity )
    {
        myBitSet[ INDEX_Connectivity ] = true;
        myConnectivity = *theConnectivity;
    }
	else
	{
		myConnectivity = CT_FAC_EXT_NO;  
	}

    if( theConnectedTo )
    {
        myBitSet[ INDEX_ConnectedTo ] = true;
        myConnectedTo = *theConnectedTo;
    }

    if ( theSDThreshold )
    {
        myBitSet[ INDEX_SDThreshold ] = true;
        mySDThreshold = *theSDThreshold;
    }
	else
	{
		mySDThreshold = CT_TEL_INFINITE_BER;
	}


    if ( theSsmReceived )
    {
        myBitSet[ INDEX_SsmReceived ] = true;
        mySsmReceived = *theSsmReceived;
    }
    else
        mySsmReceived = CT_RxSsm_ALL;


    if ( theTimingReference )
    {   
        myBitSet[ INDEX_TimingReference ] = true;
        myTimingReference = *theTimingReference;
    }
    else
        myTimingReference = CT_TEL_MS_TREF_NONE;


    if ( theProtHoldOffTime )
    {   
        myBitSet[ INDEX_ProtHoldOffTime ] = true;
        myProtHoldOffTime = *theProtHoldOffTime;
    }
    else
        myProtHoldOffTime = 0;

    if (theExtChannel)
    {
        myBitSet[INDEX_ExtChannel] = true;
        myExtChannel = *theExtChannel;
    }
    else
       // myExtChannel = UNKNOWN_WAVELENGHT;
        myExtChannel = 0xff;
    if ( theOeoRegen )
    {
    myBitSet[ INDEX_OeoRegen ] = true;
    myOeoRegen = *theOeoRegen;
    }
    else
        myOeoRegen = CT_TEL_OEO_REGEN_OFF;

    if ( theClkType )
    {
        myBitSet[ INDEX_ClkType ] = true;
        myClkType = *theClkType;
    }
	else
	{
		myClkType=CT_TEL_CLK_UNKNOWN;
	}

    if ( theOTIDStatus )
    {
        myBitSet[ INDEX_OTIDStatus ] = true;
        myOTIDStatus = *theOTIDStatus;
    }
	else
	{
		myOTIDStatus = CT_TEL_OTID_DISABLED;
	}

    if ( theTimDef )
    {
        myBitSet[ INDEX_TimDef] = true;
        myTimDef = *theTimDef;
    }
	else
	{
		myTimDef = CT_TEL_TIM_UNKNOWN;
	}

    if ( theExpDapi )
    {
        myBitSet[INDEX_ExpDapi] = true;
        myExpDapi = *theExpDapi;
    }

    if ( theExpSapi )
    {
        myBitSet[INDEX_ExpSapi] = true;
        myExpSapi = *theExpSapi;
    }

    if ( theTxDapi )
    {
        myBitSet[INDEX_TxDapi] = true;
        myTxDapi = *theTxDapi;
    }

    if ( theTxSapi )
    {
        myBitSet[INDEX_TxSapi] = true;
        myTxSapi = *theTxSapi;
    }

    if ( theBurstyBerSdInterval )
    {
        myBitSet[INDEX_BurstyBerSdInterval] = true;
        myBurstyBerSdInterval = *theBurstyBerSdInterval;
    }
    else 
    {
        myBurstyBerSdInterval = 0;
    }

    if ( theBurstyBerSdThreshold )
    {
        myBitSet[INDEX_BurstyBerSdThreshold] = true;
        myBurstyBerSdThreshold = *theBurstyBerSdThreshold;
    }
    else
    {
        myBurstyBerSdThreshold = 0;
    }

    if ( theExpOperator )
    {
        myBitSet[INDEX_ExpOperator] = true;
        myExpOperator = *theExpOperator;
    }

    if ( theTxOperator )
    {
        myBitSet[INDEX_TxOperator] = true;
        myTxOperator = *theTxOperator;
    }
    
    if(theAlarmProfile)
    {
        myBitSet[ INDEX_AlarmProfile ] = true;
        myAlarmProfile = *theAlarmProfile;
    }
	else
	{
		myAlarmProfile = CT_UNKNOWN_PT;
	}

    if(thePST)
    {
        myBitSet[ INDEX_PST ] = true;
        myPST = *thePST;
    }
	else
	{
		myPST = 0;
	}

    if(thePSTQ)
    {
        myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *thePSTQ;
    }
	else
	{
		myPSTQ = 0;
	}

    if(theSST)
    {
        myBitSet[ INDEX_SST ] = true;
        mySST = *theSST;
    }
	else
	{
		mySST = 0;
	}
}

TL1_OCHRspBlk::TL1_OCHRspBlk(const TL1_OCHRspBlk& ochBlk)
    : myBitSet( INDEX_END, false )
{
    myBitSet                        = ochBlk.myBitSet;
    myEntityName                    = ochBlk.myEntityName;
    myFacAddr                       = ochBlk.myFacAddr;
    myCardType                      = ochBlk.myCardType;
    mySubCardType                   = ochBlk.mySubCardType;
    myAutoAdjustAttenuationEnabled  = ochBlk.myAutoAdjustAttenuationEnabled;
    myOtuMapEnabled                 = ochBlk.myOtuMapEnabled;
    myExpectedTrace                 = ochBlk.myExpectedTrace;
    mySentTrace                     = ochBlk.mySentTrace;
    myProtFunc                      = ochBlk.myProtFunc;
    myNpOwner                       = ochBlk.myNpOwner;
    myFecType                       = ochBlk.myFecType;
    mySuperFec                      = ochBlk.mySuperFec;
    myMonitorOtiEnabled             = ochBlk.myMonitorOtiEnabled;
    myMonitorTraceEnabled           = ochBlk.myMonitorTraceEnabled;
    myInsertAisEnabled              = ochBlk.myInsertAisEnabled;
    myConnectivity                  = ochBlk.myConnectivity;
    myConnectedTo                   = ochBlk.myConnectedTo;
    mySDThreshold                   = ochBlk.mySDThreshold;
    mySsmReceived                   = ochBlk.mySsmReceived;
    myTimingReference               = ochBlk.myTimingReference;
    myProtHoldOffTime               = ochBlk.myProtHoldOffTime;
    myExtChannel                    = ochBlk.myExtChannel;
    myOeoRegen                      = ochBlk.myOeoRegen;
    myClkType                       = ochBlk.myClkType;
    myOTIDStatus                    = ochBlk.myOTIDStatus;
    myAlarmProfile                  = ochBlk.myAlarmProfile;
    myTimDef                        = ochBlk.myTimDef;
    myExpDapi                       = ochBlk.myExpDapi;
    myExpSapi                       = ochBlk.myExpSapi;
    myTxDapi                        = ochBlk.myTxDapi;
    myTxSapi                        = ochBlk.myTxSapi;       
    myBurstyBerSdInterval           = ochBlk.myBurstyBerSdInterval;
    myBurstyBerSdThreshold          = ochBlk.myBurstyBerSdThreshold;
    myExpOperator                   = ochBlk.myExpOperator;
    myTxOperator                    = ochBlk.myTxOperator;
    myPST                           = ochBlk.myPST;
    myPSTQ                          = ochBlk.myPSTQ;
    mySST                           = ochBlk.mySST;    
    
}

TL1_OCHRspBlk::~TL1_OCHRspBlk()
{
}

TL1_OCHRspBlk& TL1_OCHRspBlk::operator=( const TL1_OCHRspBlk& theBlock )
{
    myBitSet                        = theBlock.myBitSet;
    myEntityName                    = theBlock.myEntityName;
    myFacAddr                       = theBlock.myFacAddr;
    myCardType                      = theBlock.myCardType;
    mySubCardType                   = theBlock.mySubCardType;
    myAutoAdjustAttenuationEnabled  = theBlock.myAutoAdjustAttenuationEnabled;
    myOtuMapEnabled                 = theBlock.myOtuMapEnabled;
    myExpectedTrace                 = theBlock.myExpectedTrace;
    mySentTrace                     = theBlock.mySentTrace;
    myProtFunc                      = theBlock.myProtFunc;
    myNpOwner                       = theBlock.myNpOwner;
    myFecType                       = theBlock.myFecType;
    mySuperFec                      = theBlock.mySuperFec;
    myMonitorOtiEnabled             = theBlock.myMonitorOtiEnabled;
    myMonitorTraceEnabled           = theBlock.myMonitorTraceEnabled;
    myInsertAisEnabled              = theBlock.myInsertAisEnabled;
    myConnectivity                  = theBlock.myConnectivity;
    myConnectedTo                   = theBlock.myConnectedTo;
    mySDThreshold                   = theBlock.mySDThreshold;
    mySsmReceived                   = theBlock.mySsmReceived;
    myTimingReference               = theBlock.myTimingReference;
    myProtHoldOffTime               = theBlock.myProtHoldOffTime;
    myExtChannel                    = theBlock.myExtChannel;
    myOeoRegen                      = theBlock.myOeoRegen;
    myClkType                       = theBlock.myClkType;
    myOTIDStatus                    = theBlock.myOTIDStatus;
    myAlarmProfile                  = theBlock.myAlarmProfile;
    myTimDef                        = theBlock.myTimDef;
    myExpDapi                       = theBlock.myExpDapi;
    myExpSapi                       = theBlock.myExpSapi;
    myTxDapi                        = theBlock.myTxDapi;
    myTxSapi                        = theBlock.myTxSapi;
    myBurstyBerSdInterval           = theBlock.myBurstyBerSdInterval;
    myBurstyBerSdThreshold          = theBlock.myBurstyBerSdThreshold;
    myExpOperator                   = theBlock.myExpOperator;
    myTxOperator                    = theBlock.myTxOperator;

    myPST                           = theBlock.myPST;
    myPSTQ                          = theBlock.myPSTQ;
    mySST                           = theBlock.mySST;

    return *this;
}

bool TL1_OCHRspBlk::operator==( const TL1_OCHRspBlk& theBlock ) const
{
    return ( myBitSet                       == theBlock.myBitSet                        &&
             myEntityName                   == theBlock.myEntityName                    &&
             myFacAddr                      == theBlock.myFacAddr                       &&
             myCardType                     == theBlock.myCardType                      &&
             mySubCardType                  == theBlock.mySubCardType                   &&
             myAutoAdjustAttenuationEnabled == theBlock.myAutoAdjustAttenuationEnabled  &&
             myOtuMapEnabled                == theBlock.myOtuMapEnabled                 &&
             myExpectedTrace                == theBlock.myExpectedTrace                 &&
             mySentTrace                    == theBlock.mySentTrace                     &&
             myProtFunc                     == theBlock.myProtFunc                      &&
             myNpOwner                      == theBlock.myNpOwner                       &&
             myFecType                      == theBlock.myFecType                       &&
             mySuperFec                     == theBlock.mySuperFec                      &&
             myMonitorOtiEnabled            == theBlock.myMonitorOtiEnabled             &&
             myMonitorTraceEnabled          == theBlock.myMonitorTraceEnabled           &&
             myInsertAisEnabled             == theBlock.myInsertAisEnabled              &&
             myConnectivity                 == theBlock.myConnectivity                  &&
             myConnectedTo                  == theBlock.myConnectedTo                   &&
             mySDThreshold                  == theBlock.mySDThreshold                   &&
             mySsmReceived                  == theBlock.mySsmReceived                   &&
             myTimingReference              == theBlock.myTimingReference               &&
             myProtHoldOffTime              == theBlock.myProtHoldOffTime               &&
             myExtChannel                   == theBlock.myExtChannel                    &&
             myOeoRegen                     == theBlock.myOeoRegen                      &&
             myClkType                      == theBlock.myClkType                       && 
             myOTIDStatus                   == theBlock.myOTIDStatus                    &&
             myAlarmProfile                 == theBlock.myAlarmProfile                  &&
             myTimDef                       == theBlock.myTimDef                        &&
             myExpDapi                      == theBlock.myExpDapi                       &&
             myExpSapi                      == theBlock.myExpSapi                       &&
             myTxDapi                       == theBlock.myTxDapi                        &&
             myTxSapi                       == theBlock.myTxSapi                        &&
             myBurstyBerSdInterval          == theBlock.myBurstyBerSdInterval           &&
             myBurstyBerSdThreshold         == theBlock.myBurstyBerSdThreshold          &&
             myExpOperator                  == theBlock.myExpOperator                   &&
             myTxOperator                   == theBlock.myTxOperator                    &&
             myPST                          == theBlock.myPST                           &&
             myPSTQ                         == theBlock.myPSTQ                          &&
             mySST                          == theBlock.mySST );
}

bool TL1_OCHRspBlk::GetEntityName(string& theEntityName ) const
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

bool TL1_OCHRspBlk::GetFacAddr(CT_TL1_FacAddr& theFacAddr ) const
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

bool TL1_OCHRspBlk::GetCardType(CT_CardType& theCardType ) const
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

bool TL1_OCHRspBlk::GetSubCardType(CT_SubCardType& theSubCardType ) const
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

bool TL1_OCHRspBlk::GetAutoAdjustAttenuationEnabled(bool& theAutoAdjustAttenuationEnabled) const
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

bool TL1_OCHRspBlk::GetOtuMapEnabled(bool& theOtuMapEnabled ) const
{
    if( true == myBitSet[ INDEX_OtuMapEnabled ] )
    {
        theOtuMapEnabled = myOtuMapEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetExpectedTrace( CT_Fac_TraceString& theExpectedTrace) const
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

bool TL1_OCHRspBlk::GetSentTrace( CT_Fac_TraceString& theSentTrace) const
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

bool 
TL1_OCHRspBlk::GetProtFunc( CT_Fac_TraceString& theProtFunc ) const
{
    if( true == myBitSet[ INDEX_ProtFunc ] )
    {
        theProtFunc = myProtFunc;
        return true;
    }
    else
    {
        return false;
    }
}

bool 
TL1_OCHRspBlk::GetNpOwner( uint8 &NpOwner) const
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

bool 
TL1_OCHRspBlk::GetFecType( CT_TEL_FecType& theFecType ) const
{
    if( true == myBitSet[ INDEX_FecType ] )
    {
        theFecType = myFecType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetSuperFec( CT_TEL_SuperFec& theSuperFec) const
{
    if( true == myBitSet[ INDEX_SuperFec ] )
    {
        theSuperFec = mySuperFec;
        return true;
    }
    else
    {
        return false;
    } 
}

bool TL1_OCHRspBlk::GetMonitorOtiEnabled( bool& theMonitorOtiEnabled) const
{
    if( true == myBitSet[ INDEX_MonitorOtiEnabled ] )
    {
        theMonitorOtiEnabled = myMonitorOtiEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetMonitorTraceEnabled( bool& theMonitorTraceEnabled) const
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

bool TL1_OCHRspBlk::GetInsertAisEnabled( bool& theInsertAisEnabled) const
{
    if( true == myBitSet[ INDEX_InsertAisEnabled ] )
    {
        theInsertAisEnabled = myInsertAisEnabled;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetConnectivity( CT_FAC_ExternalConnectivity& theConnectivity) const
{
    if( true == myBitSet[ INDEX_Connectivity ] )
    {
        theConnectivity = myConnectivity;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetConnectedTo ( CT_Fac_ConnectedToString& theConnectedTo ) const
{
    if( true == myBitSet[ INDEX_ConnectedTo ] )
    {
        theConnectedTo = myConnectedTo;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetSDThreshold ( CT_TEL_BERLevels& theSDThreshold ) const
{
    if( true == myBitSet[ INDEX_SDThreshold ] )
    {
        theSDThreshold = mySDThreshold;
        return true;
    }
    else
    {
        return false;
    }
}


bool 
TL1_OCHRspBlk::GetSsmReceived( CT_FAC_RxSsm& theSsmReceived ) const
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

bool 
TL1_OCHRspBlk::GetTimingRef( CT_TEL_MsTref& theTimingReference ) const
{
    if( true == myBitSet[ INDEX_TimingReference ] )
    {
        theTimingReference = myTimingReference;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetProtHoldOffTime( int& theProtHoldOffTime  ) const
{
    if( true == myBitSet[ INDEX_ProtHoldOffTime ] )
    {
        theProtHoldOffTime = myProtHoldOffTime;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetExtChannel(uint32& theExtChannel) const
{
    if (true == myBitSet[INDEX_ExtChannel])
    {
        theExtChannel = myExtChannel;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetOeoRegen( CT_TEL_OEO_REGEN_MODE& theOeoRegen ) const
{
    if ( true == myBitSet[ INDEX_OeoRegen ] )
    {
        theOeoRegen = myOeoRegen;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetClkType( CT_TEL_ClkType& theClkType ) const
{
    if ( true == myBitSet[ INDEX_ClkType ] )
    {
        theClkType = myClkType;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_OCHRspBlk::GetOTIDStatus( CT_TEL_OTIDStatus& theOTIDStatus ) const
{
    if ( true == myBitSet[ INDEX_OTIDStatus ] )
    {
        theOTIDStatus = myOTIDStatus;
        return true;
    }
    else
    {
        return false;
    }
}
bool TL1_OCHRspBlk::GetBurstyBerSdInterval( uint16& theBurstyBerSdInterval ) const
{
    if( true == myBitSet[ INDEX_BurstyBerSdInterval ] )
    {
        theBurstyBerSdInterval = myBurstyBerSdInterval;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetBurstyBerSdThreshold( uint32& theBurstyBerSdThreshold ) const
{
    if( true == myBitSet[ INDEX_BurstyBerSdThreshold ] )
    {
        theBurstyBerSdThreshold = myBurstyBerSdThreshold;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetAlarmProfile( CT_ProfileTableId& theAlarmProfile) const
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

CT_SM_PST TL1_OCHRspBlk::GetPST( ) const
{
    return myPST;
}

CT_SM_PSTQ TL1_OCHRspBlk::GetPSTQ( ) const
{
    return myPSTQ;
}

CT_SM_SST TL1_OCHRspBlk::GetSST( ) const
{
    return mySST;
}

bool TL1_OCHRspBlk::GetPST( CT_SM_PST& thePST) const
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

bool TL1_OCHRspBlk::GetPSTQ( CT_SM_PSTQ& thePSTQ) const
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

bool TL1_OCHRspBlk::GetSST( CT_SM_SST& theSST) const
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

bool TL1_OCHRspBlk::GetTimDef(CT_TEL_TimCriteriaMode & theTimDef) const
{
    if(true == myBitSet[ INDEX_TimDef ])
    {
        theTimDef = myTimDef;
        return true;
     }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetExpDapi(CT_Fac_TraceString & theExpDapi) const
{
    if(true == myBitSet[INDEX_ExpDapi])
    {
        theExpDapi = myExpDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetExpSapi(CT_Fac_TraceString & theExpSapi) const
{
    if(true == myBitSet[INDEX_ExpSapi])
    {
        theExpSapi = myExpSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetTxDapi(CT_Fac_TraceString & theTxDapi) const
{
    if(true == myBitSet[INDEX_TxDapi])
    {
        theTxDapi = myTxDapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetTxSapi(CT_Fac_TraceString & theTxSapi) const
{
    if(true == myBitSet[INDEX_TxSapi])
    {
        theTxSapi = myTxSapi;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetExpOperator(CT_Fac_TraceString& theExpOperator) const
{
    if(true == myBitSet[INDEX_ExpOperator])
    {
        theExpOperator = myExpOperator;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_OCHRspBlk::GetTxOperator(CT_Fac_TraceString& theTxOperator) const
{
    if(true == myBitSet[INDEX_TxOperator])
    {
        theTxOperator = myTxOperator;
        return true;
    }
    else
    {
        return false;
    }
}
