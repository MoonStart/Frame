/*-----------------------------------------------------------------------------
   Copyright(c) Tellabs Transport Group Inc. All rights reserved.

SUBSYSTEM:      TL1 Response 
TARGET:
AUTHOR:         February 28, 2003- Stephen Wu
DESCRIPTION:    Source file for TL1 Response base class 
-----------------------------------------------------------------------------*/

#include <../TL1_EQRspBlk.h>

TL1_EQRspBlk::TL1_EQRspBlk():
myWave(0),
myPST(CT_SM_PST_OOS),
myPSTQ(CT_SM_PSTQ_MA),
mySST(CT_SM_SST_UAS){;}

TL1_EQRspBlk:: TL1_EQRspBlk(const string* entityName,
                            const CT_TL1_SlotAddr* slotAddr,
                            const CT_CardType* cardType,
                            const CT_SubCardType* subCardType, 
	                        const CT_EqName* cardName,
                            const CT_Band* band,
                            const CT_HalfBand* halfBand,
                            const CT_TL1_PumpPower* pumpPower,
                            const CT_Wavelength* wavelength, 
	                        const CT_ShelfType* shelfType,
                            const CT_EqName* shelfName,
                            const CT_ProfileTableId* ID,
                            const CT_Function* function,
                            const CT_Capacity* capacity,
                            const CT_TEL_TimingMode* theTimingMode,
                            const CT_NumberOfPort* theNumberOfPort,
                            const CT_Rate* theRate,
                            const CT_OeoRegen* theOeoRegen,
                            const CT_InterconMode* theInterconMode,
                            const CT_InterconMode* theInterconModeDflt,
                            const CT_Mount* theMount,
                            const CT_PktEquip* thePktEquip,
                            const CT_SM_PST* PST,
                            const CT_SM_PSTQ* PSTQ,
                            const CT_SM_SST* SST,
                            const CT_Timer* theWaitToRestoreTmr,       
                            const CT_Timer* theVcgTmr,     
                            const CT_Timer* theDiffDelayThreashold,
                            const CT_NumberOfChan* theNumbrChan, 
                            const CT_NumberOfChan* theChanLimit, 
                            const CT_ChanRange* theChanRange,
                            const CT_Length* theLength,
                            const CT_DCM_FiberType* theFiberType,
                            const CT_TEL_mBm* theIL,
                            const CT_Preamp* thePreamp,
                            const CT_Extattn* theExtAttn,
                            const CT_Postamp* thePostamp,
                            const CT_Type* theType,
                            const CT_SwitchDomain* theSwitchDomain,
                            const CT_TEL_SwitchMode* theSwitchMode,
                            const CT_Reach* theReach,
							const CT_Usage* theUsage,
                            const CT_CableLength* theCableLength,
                            const CT_ConnPort* theConnPort,
                            const CT_ConnPortRange* theConnPortRange,
                            const int* theLacpSystemPriority,
                            const CT_LacpSystemId* theLacpSystemId,
                            const CT_Modulation* theModulation,
                            const CT_FanProfile* theFanProfile,
                            const CT_ModVersion* theModVersion,
                            const CT_PktShelfType* thePktShelfType,
							const CT_DiskFormatType* theDiskFormatType)
    : myBitSet( INDEX_END, false), myWave( UNKNOWN_WAVELENGHT )
{
    myEntityName = "";
    if( entityName )  
    {
		myBitSet[ INDEX_EntityName ] = true;
        myEntityName = *entityName;
    }

    mySlotAddr = UNKNOWN_SLOT_ADDR;
    if( slotAddr )  
    {
		myBitSet[ INDEX_SlotAddr ] = true;
        mySlotAddr = *slotAddr;
    }

    myCardType = CARD_TYPE_UNKNOWN;
    if( cardType)
    {
		myBitSet[ INDEX_CardType ] = true;
        myCardType = *cardType;
    }

    mySubCardType = UNKNOWN_SUB_CT;
    if( subCardType)
    {
		myBitSet[ INDEX_SubCardType ] = true;
        mySubCardType = *subCardType;
    }
    
    myCardName =  "";
    if( cardName)
    {
		myBitSet[ INDEX_CardName ] = true;
        myCardName = *cardName;
    }

    myBand = UNKNOWN_BAND;
 	if(band)
    {
		myBitSet[ INDEX_Band ] = true;
        myBand = *band;
    }

    myHalfBand = CT_HALFBAND_UNKNOWN;
    if(halfBand)
    {
		myBitSet[ INDEX_HalfBand ] = true;
        myHalfBand = *halfBand;
    }

 	myPumpPower = CT_TL1_PumpPower_ALL;
 	if(pumpPower)
    {
		myBitSet[ INDEX_PumpPower ] = true;
        myPumpPower = *pumpPower;
    }

  	if(wavelength)
    {
		myBitSet[ INDEX_Wave ] = true;
        myWave = *wavelength;
    }

    myShelfType = UNKNOWN_SHELF;
    if(shelfType)
    {
		myBitSet[ INDEX_ShelfType ] = true;
        myShelfType = *shelfType;
    }

    myShelfName = "";
  	if(shelfName)
    {
		myBitSet[ INDEX_ShelfName ] = true;
        myShelfName = *shelfName;
    }

    myID = CT_UNKNOWN_PT;
  	if(ID)
    {
		myBitSet[ INDEX_profileID ] = true;
        myID = *ID;
    }

    myFunction = CT_FUNCTION_UNKNOWN;
    if(function)
    {
		myBitSet[ INDEX_Function ] = true;
        myFunction = *function;
    }

    myCapacity = CT_CAPACITY_UNKNOWN;
    if(capacity)
    {
		myBitSet[ INDEX_Capacity ] = true;
        myCapacity = *capacity;
    }

    myTimingMode = CT_TEL_UNKNOWN_TIMING;
  	if(theTimingMode)
    {
		myBitSet[ INDEX_TimingMode ] = true;
        myTimingMode = *theTimingMode;
    }

    myNumberOfPort = CT_NUMBER_OF_PORT_UNKNOWN;
   	if(theNumberOfPort)
    {
		myBitSet[ INDEX_NumberOfPort ] = true;
        myNumberOfPort = *theNumberOfPort;
    }

    myRate = CT_RATE_NA;
    if(theRate)
    {
		myBitSet[ INDEX_Rate ] = true;
        myRate = *theRate;
    }

    myOeoRegen = (CT_OeoRegen)CT_TEL_OEO_REGEN_UNKNOWN;
    if(theOeoRegen)
    {
		myBitSet[ INDEX_OeoRegen ] = true;
        myOeoRegen = *theOeoRegen;
    }

    myInterconMode = CT_INTERCON_MODE_UNKNOWN;
    if(theInterconMode)
    {
		myBitSet[ INDEX_InterconMode ] = true;
        myInterconMode = *theInterconMode;
    }

    myInterconModeDflt = CT_INTERCON_MODE_UNKNOWN;
    if(theInterconModeDflt)
    {
		myBitSet[ INDEX_InterconModeDflt ] = true;
        myInterconModeDflt = *theInterconModeDflt;
    }

    myMount = CT_MOUNT_UNKNOWN;
    if(theMount)
    {
		myBitSet[ INDEX_Mount ] = true;
        myMount = *theMount;
    }

    myPktEquip = CT_PKTEQUIP_UNKNOWN;
    if(thePktEquip)
    {
		myBitSet[ INDEX_PktEquip ] = true;
        myPktEquip = *thePktEquip;
    }

    myPST = CT_SM_PST_NCRT;
    if(PST)
    {
		myBitSet[ INDEX_PST ] = true;
        myPST = *PST;
    }

    myPSTQ = CT_SM_PSTQ_DNE;
    if(PSTQ)
    {
		myBitSet[ INDEX_PSTQ ] = true;
        myPSTQ = *PSTQ;
    }

    mySST = CT_SM_SST_BUSY;
    if(SST)
    {
		myBitSet[ INDEX_SST ] = true;
        mySST = *SST;
    }
    
    myWaitToRestoreTmr = CT_UNKNOWN_TIMER_VALUE;
    if (theWaitToRestoreTmr)
    {
        myBitSet[ INDEX_WaitToRestore ] = true;
        myWaitToRestoreTmr = *theWaitToRestoreTmr;
    }
    
    myVcgTmr = CT_UNKNOWN_TIMER_VALUE;
    if (theVcgTmr)
    {
        myBitSet[ INDEX_VcgTmr ] = true;
        myVcgTmr = *theVcgTmr;
    } 

    myDiffDelayThreashold = CT_UNKNOWN_TIMER_VALUE;
    if (theDiffDelayThreashold)
    {
        myBitSet[ INDEX_DiffDelayThreashold ] = true;
        myDiffDelayThreashold = *theDiffDelayThreashold;
    } 

    myNumbrChan = CT_NUMBER_OF_CHAN_UNKNOWN;
    if (theNumbrChan)
    {
        myBitSet[ INDEX_NumbrChan ] = true;
        myNumbrChan = *theNumbrChan;
    } 

    myChanLimit = CT_NUMBER_OF_CHAN_UNKNOWN;
    if (theChanLimit)
    {
        myBitSet[ INDEX_ChanLimit ] = true;
        myChanLimit = *theChanLimit;
    } 

    myChanRange = CT_CHAN_RANGE_UNKNOWN;
    if (theChanRange)
    {
        myBitSet[ INDEX_ChanRange ] = true;
        myChanRange = *theChanRange;
    }

    myLength = CT_LENGTH_UNKNOWN;
    if (theLength)
    {
        myBitSet[ INDEX_Length ] = true;
        myLength = *theLength;
    }

    myFiberType = CT_FIBERTYPE_UNKNOWN;
    if (theFiberType)
    {
        myBitSet[ INDEX_FiberType ] = true;
        myFiberType = *theFiberType;
    }

    myIL = CT_TEL_DEFAULT_AOPE_THRESHOLD;
    if (theIL)
    {
        myBitSet[ INDEX_IL ] = true;
        myIL = *theIL;
    }

    myPreamp = CT_PREAMP_NONE;
    if (thePreamp)
    {
        myBitSet[INDEX_Preamp] = true;
        myPreamp = *thePreamp;
    }

    myExtAttn = CT_ExtAttn_0;
    if (theExtAttn)
    {
        myBitSet[INDEX_ExtAttn] = true;
        myExtAttn = *theExtAttn;
    }

    myPostamp = CT_POSTAMP_NONE;
    if (thePostamp)
    {
        myBitSet[INDEX_Postamp] = true;
        myPostamp = *thePostamp;
    }

    myType = UNKNOWN_CT_TYPE;
    if (theType)
    {
        myBitSet[INDEX_Type] = true;
        myType = *theType;
    }

    mySwitchDomain = CT_SWITCH_DOMAIN_UNKNOWN;
    if (theSwitchDomain)
    {
        myBitSet[INDEX_SwitchDomain] = true;
        mySwitchDomain = *theSwitchDomain;
    }

    mySwitchMode = CT_TEL_SwitchMode_None;
    if (theSwitchMode)
    {
        myBitSet[INDEX_SwitchMode] = true;
        mySwitchMode = *theSwitchMode;
    }

    myReach = CT_REACH_UNKNOWN;
    if (theReach)
    {
        myBitSet[INDEX_Reach] = true;
        myReach = *theReach;
    }

    myUsage = CT_USAGE_UNKNOWN;
	if (theUsage)
    {
        myBitSet[INDEX_Usage] = true;
        myUsage = *theUsage;
    }

    myCableLength = CT_CABLELENGTH_UNKNOWN;
   	if(theCableLength)
    {
		myBitSet[ INDEX_CableLength ] = true;
        myCableLength = *theCableLength;
    }

    myPktShelfType = PKTSHELFTYPE_UNKNOWN;
    if(thePktShelfType)
    {
		myBitSet[ INDEX_PktShelfType ] = true;
        myPktShelfType = *thePktShelfType;
    }

    myDiskFormatType = CT_DISK_FORMAT_UNKNOWN;
    if(theDiskFormatType)
    {
		myBitSet[ INDEX_DiskFormatType ] = true;
        myDiskFormatType = *theDiskFormatType;
    }

    myConnPort = CT_CONNPORT_UNKNOWN;
    if(theConnPort)
    {
        myBitSet[ INDEX_ConnPort ] = true;
        myConnPort = *theConnPort;
    }
    myConnPortRange = CT_CONNPORT_RANGE_UNKNOWN;

    myLacpSystemPriority = 0;
	if (theLacpSystemPriority)
    {
        myBitSet[INDEX_LacpPri] = true;
        myLacpSystemPriority = *theLacpSystemPriority;
    }

	if (theLacpSystemId)
    {
        myBitSet[INDEX_LacpId] = true;
        myLacpSystemId = *theLacpSystemId;
    }

    myModulation = CT_MODULATION_UNKNOWN;
    if (theModulation)
    {
        myBitSet[INDEX_Modulation] = true;
        myModulation = *theModulation;
    }

    myFanProfile = CT_FanProfileUnavailable;
    if(theFanProfile)
    {
        myBitSet[ INDEX_FanProfile ] = true;
        myFanProfile = *theFanProfile;
    }

    myModVersion = CT_MODVERSION_ALL;
    if(theModVersion)
    {
        myBitSet[ INDEX_ModVersion ] = true;
        myModVersion = *theModVersion;
    }
}

//--------------------------------------------------------------------------------------------------    
TL1_EQRspBlk::TL1_EQRspBlk(const TL1_EQRspBlk& eqBlk)
    : myWave( UNKNOWN_WAVELENGHT ), mySlotAddr(0,0), myPSTQ( eqBlk.myPSTQ), mySST( eqBlk.mySST )
{
    myBitSet            = eqBlk.myBitSet;
    myEntityName        = eqBlk.myEntityName; 
    mySlotAddr          = eqBlk.mySlotAddr; 
	myCardType          = eqBlk.myCardType; 
	mySubCardType       = eqBlk.mySubCardType; 
    myCardName          = eqBlk.myCardName; 
    myBand              = eqBlk.myBand; 
    myHalfBand          = eqBlk.myHalfBand; 
    myPumpPower         = eqBlk.myPumpPower; 
    myWave              = eqBlk.myWave; 
    myShelfType         = eqBlk.myShelfType; 
    myShelfName         = eqBlk.myShelfName; 
    myID                = eqBlk.myID;
    myFunction          = eqBlk.myFunction;
    myCapacity          = eqBlk.myCapacity;
    myTimingMode        = eqBlk.myTimingMode;
    myNumberOfPort      = eqBlk.myNumberOfPort;
    myRate              = eqBlk.myRate;
    myOeoRegen          = eqBlk.myOeoRegen;
    myInterconMode      = eqBlk.myInterconMode;
    myInterconModeDflt  = eqBlk.myInterconModeDflt;
    myMount             = eqBlk.myMount;
    myPktEquip          = eqBlk.myPktEquip;
    myPST               = eqBlk.myPST;
    myWaitToRestoreTmr      = eqBlk.myWaitToRestoreTmr;
    myVcgTmr                = eqBlk.myVcgTmr;
    myDiffDelayThreashold   = eqBlk.myDiffDelayThreashold;   
    myNumbrChan         = eqBlk.myNumbrChan;
    myChanLimit         = eqBlk.myChanLimit;                       
    myChanRange         = eqBlk.myChanRange;
    myLength            = eqBlk.myLength;
    myFiberType         = eqBlk.myFiberType;
    myIL                = eqBlk.myIL;
    myPreamp            = eqBlk.myPreamp;
    myExtAttn           = eqBlk.myExtAttn;
    myPostamp           = eqBlk.myPostamp;
    myType              = eqBlk.myType;
    mySwitchDomain      = eqBlk.mySwitchDomain;
    mySwitchMode        = eqBlk.mySwitchMode;
    myReach             = eqBlk.myReach;
	myUsage             = eqBlk.myUsage;
    myCableLength       = eqBlk.myCableLength;
    myPktShelfType      = eqBlk.myPktShelfType;
    myDiskFormatType    = eqBlk.myDiskFormatType;
    myConnPort          = eqBlk.myConnPort;
    myConnPortRange     = eqBlk.myConnPortRange;
	myLacpSystemPriority = eqBlk.myLacpSystemPriority;
	myLacpSystemId      = eqBlk.myLacpSystemId;
    myModulation        = eqBlk.myModulation;
    myFanProfile        = eqBlk.myFanProfile;
    myModVersion        = eqBlk.myModVersion;
}

TL1_EQRspBlk::~TL1_EQRspBlk()
{
}

//--------------------------------------------------------------------------------------------------    
TL1_EQRspBlk& TL1_EQRspBlk::operator=( const TL1_EQRspBlk& theBlock )
{
    myBitSet            = theBlock.myBitSet;
    myEntityName        = theBlock.myEntityName; 
    mySlotAddr          = theBlock.mySlotAddr; 
	myCardType          = theBlock.myCardType; 
	mySubCardType       = theBlock.mySubCardType; 
    myCardName          = theBlock.myCardName; 
    myBand              = theBlock.myBand;
    myHalfBand          = theBlock.myHalfBand; 
    myPumpPower         = theBlock.myPumpPower; 
    myWave              = theBlock.myWave; 
    myShelfType         = theBlock.myShelfType; 
    myShelfName         = theBlock.myShelfName; 
    myID                = theBlock.myID; 
    myFunction          = theBlock.myFunction;
    myCapacity          = theBlock.myCapacity;
    myTimingMode        = theBlock.myTimingMode;
    myNumberOfPort      = theBlock.myNumberOfPort;
    myRate              = theBlock.myRate;
    myOeoRegen          = theBlock.myOeoRegen;
    myInterconMode      = theBlock.myInterconMode;
    myInterconModeDflt  = theBlock.myInterconModeDflt;
    myMount             = theBlock.myMount;
    myPktEquip          = theBlock.myPktEquip;
    myPST               = theBlock.myPST;
    myPSTQ              = theBlock.myPSTQ;
    mySST               = theBlock.mySST;
    myWaitToRestoreTmr      = theBlock.myWaitToRestoreTmr;
    myVcgTmr                = theBlock.myVcgTmr;
    myDiffDelayThreashold   = theBlock.myDiffDelayThreashold;
    myNumbrChan         = theBlock.myNumbrChan;
    myChanLimit         = theBlock.myChanLimit;                       
    myChanRange         = theBlock.myChanRange;
    myLength            = theBlock.myLength;
    myFiberType         = theBlock.myFiberType;
    myIL                = theBlock.myIL;
    myPreamp            = theBlock.myPreamp;
    myExtAttn           = theBlock.myExtAttn;
    myPostamp           = theBlock.myPostamp;
    myType              = theBlock.myType;
    mySwitchDomain      = theBlock.mySwitchDomain;
    mySwitchMode        = theBlock.mySwitchMode;
    myReach             = theBlock.myReach;	
	myUsage             = theBlock.myUsage;
    myCableLength       = theBlock.myCableLength;
    myPktShelfType      = theBlock.myPktShelfType;
    myDiskFormatType    = theBlock.myDiskFormatType;
    myConnPort          = theBlock.myConnPort;
    myConnPortRange     = theBlock.myConnPortRange;
    myLacpSystemPriority = theBlock.myLacpSystemPriority;
    myLacpSystemId      = theBlock.myLacpSystemId;
    myModulation        = theBlock.myModulation;
    myFanProfile        = theBlock.myFanProfile;
    myModVersion        = theBlock.myModVersion;
    return *this;
}

//--------------------------------------------------------------------------------------------------    
bool TL1_EQRspBlk::operator==( const TL1_EQRspBlk& theBlock ) const
{
    return ( myBitSet           == theBlock.myBitSet &&
             myEntityName       == theBlock.myEntityName && 
             mySlotAddr         == theBlock.mySlotAddr && 
	         myCardType         == theBlock.myCardType && 
	         mySubCardType      == theBlock.mySubCardType &&
             myCardName         == theBlock.myCardName &&
             myBand             == theBlock.myBand && 
             myHalfBand         == theBlock.myHalfBand &&
             myPumpPower        == theBlock.myPumpPower && 
             myWave             == theBlock.myWave && 
             myShelfType        == theBlock.myShelfType && 
             myShelfName        == theBlock.myShelfName && 
             myID               == theBlock.myID &&
             myFunction         == theBlock.myFunction &&
             myCapacity         == theBlock.myCapacity &&
             myTimingMode       == theBlock.myTimingMode &&
             myNumberOfPort     == theBlock.myNumberOfPort &&
             myRate             == theBlock.myRate &&
             myOeoRegen         == theBlock.myOeoRegen &&
             myInterconMode     == theBlock.myInterconMode &&
             myInterconModeDflt == theBlock.myInterconModeDflt &&
             myMount            == theBlock.myMount &&
             myPktEquip         == theBlock.myPktEquip &&
             myPST              == theBlock.myPST &&
             myPSTQ             == theBlock.myPSTQ &&
             mySST              == theBlock.mySST  &&
             myWaitToRestoreTmr      == theBlock.myWaitToRestoreTmr &&
             myVcgTmr                == theBlock.myVcgTmr &&
             myDiffDelayThreashold   == theBlock.myDiffDelayThreashold &&
             myNumbrChan         == theBlock.myNumbrChan &&                
             myChanLimit         == theBlock.myChanLimit &&                       
             myChanRange         == theBlock.myChanRange &&
             myLength            == theBlock.myLength &&
             myFiberType         == theBlock.myFiberType &&
             myIL                == theBlock.myIL &&
             myPreamp            == theBlock.myPreamp &&
             myExtAttn           == theBlock.myExtAttn &&
             myPostamp           == theBlock.myPostamp &&
             myType              == theBlock.myType &&
             mySwitchDomain      == theBlock.mySwitchDomain &&
             mySwitchMode        == theBlock.mySwitchMode &&
             myReach             == theBlock.myReach &&
			 myUsage             == theBlock.myUsage &&
             myCableLength       == theBlock.myCableLength &&
             myPktShelfType      == theBlock.myPktShelfType &&
             myDiskFormatType    == theBlock.myDiskFormatType &&
             myConnPort          == theBlock.myConnPort &&
             myConnPortRange     == theBlock.myConnPortRange &&
             myLacpSystemPriority == theBlock.myLacpSystemPriority &&
             myLacpSystemId      == theBlock.myLacpSystemId &&
             myModulation        == theBlock.myModulation &&
             myFanProfile        == theBlock.myFanProfile &&
             myModVersion        == theBlock.myModVersion
            );           
}

//--------------------------------------------------------------------------------------------------    
// Definition for GetEntityName()
bool TL1_EQRspBlk::GetEntityName( string& entityName) const
{
    if( true == myBitSet[ INDEX_EntityName ] )
	{
    	entityName = myEntityName;
		return true;
	}
	else
	{
		return false;
	}
}


// Definition for GetSlotAddr()
bool TL1_EQRspBlk::GetSlotAddr( CT_TL1_SlotAddr& slotAddr) const
{
    if( true == myBitSet[ INDEX_SlotAddr ] )
	{
   	    slotAddr = mySlotAddr;
	    return true;
	}
	else
	{
		return false;
	}
}


bool TL1_EQRspBlk::GetCardType( CT_CardType& type) const 
{
    if( true == myBitSet[ INDEX_CardType ] )
    {
        type = myCardType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetSubCardType( CT_SubCardType& subtype) const 
{
    if( true == myBitSet[ INDEX_SubCardType ] )
    {
        subtype = mySubCardType;  
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_EQRspBlk::GetCardName( CT_EqName& name) const 
{
    if( true == myBitSet[ INDEX_CardName ] )
    {
        name = myCardName;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_EQRspBlk::GetBand( CT_Band& band) const 
{
    if( true == myBitSet[ INDEX_Band ] )
    {
        band = myBand;   
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetHalfBand( CT_HalfBand& halfBand) const 
{
    if( true == myBitSet[ INDEX_HalfBand ] )
    {
        halfBand = myHalfBand;   
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_EQRspBlk::GetPumpPower( CT_TL1_PumpPower& pumpPower) const 
{
    if( true == myBitSet[ INDEX_PumpPower ] )
    {
        pumpPower = myPumpPower;   
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_EQRspBlk::GetChan( CT_Wavelength& wave) const 
{
    if( true == myBitSet[ INDEX_Wave ] )
    {
        wave = myWave;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_EQRspBlk::GetShelfType( CT_ShelfType& type) const 
{
    if( true == myBitSet[ INDEX_ShelfType ] )
    {
        type = myShelfType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetShelfName( CT_EqName& name) const 
{
    if( true == myBitSet[ INDEX_ShelfName ] )
    {
        name = myShelfName;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_EQRspBlk::GetALMPF( CT_ProfileTableId& ID) const
{
    if( true == myBitSet[ INDEX_profileID ] )
    {
    	ID = myID;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetFunction( CT_Function& function) const
{
    if( true == myBitSet[ INDEX_Function ] )
    {
    	function = myFunction;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetCapacity( CT_Capacity& capacity) const
{
    if( true == myBitSet[ INDEX_Capacity ] )
    {
    	capacity = myCapacity;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetTimingMode( CT_TEL_TimingMode& theTimingMode) const
{
    if( true == myBitSet[ INDEX_TimingMode ] )
    {
    	theTimingMode = myTimingMode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetNumberOfPor( CT_NumberOfPort& theNumberOfPort) const
{
    if( true == myBitSet[ INDEX_NumberOfPort ] )
    {
    	theNumberOfPort = myNumberOfPort;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetRate( CT_Rate& theRate) const
{
    if( true == myBitSet[ INDEX_Rate ] )
    {
    	theRate = myRate;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetOeoRegen( CT_OeoRegen& theOeoRegen) const
{
    if( true == myBitSet[ INDEX_OeoRegen ] )
    {
    	theOeoRegen = myOeoRegen;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetInterconMode( CT_InterconMode& theInterconMode) const
{
    if( true == myBitSet[ INDEX_InterconMode ] )
    {
    	theInterconMode = myInterconMode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetInterconModeDflt( CT_InterconMode& theInterconModeDflt) const
{
    if( true == myBitSet[ INDEX_InterconModeDflt ] )
    {
    	theInterconModeDflt = myInterconModeDflt;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetMount( CT_Mount& theMount) const
{
    if( true == myBitSet[ INDEX_Mount ] )
    {
    	theMount = myMount;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetPktEquip( CT_PktEquip& thePktEquip) const
{
    if( true == myBitSet[ INDEX_PktEquip ] )
    {
    	thePktEquip = myPktEquip;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetPST( CT_SM_PST& PST) const 
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


bool TL1_EQRspBlk::GetPSTQ( CT_SM_PSTQ& PSTQ) const 
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

bool TL1_EQRspBlk::GetSST( CT_SM_SST& SST) const 
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

CT_SM_PST TL1_EQRspBlk::GetPST() const 
{
    return myPST;
}

CT_SM_PSTQ TL1_EQRspBlk::GetPSTQ() const 
{
    return myPSTQ;
}

CT_SM_SST TL1_EQRspBlk::GetSST() const 
{
    return mySST;
}

//--------------------------------------------------------------------------------------------------    
bool TL1_EQRspBlk::GetWaitToRestoreTmr(CT_Timer& theWaitToRestoreTmr) const
{
    if( true == myBitSet[ INDEX_WaitToRestore ] )
    {
        theWaitToRestoreTmr = myWaitToRestoreTmr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------------------------------    
bool TL1_EQRspBlk::GetVcgTmr(CT_Timer& theVcgTmr) const
{
    if( true == myBitSet[ INDEX_VcgTmr ] )
    {
        theVcgTmr = myVcgTmr;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------------------------------    
bool TL1_EQRspBlk::GetDiffDelayThreashold(CT_Timer& theDiffDelayThreashold) const
{
    if( true == myBitSet[ INDEX_DiffDelayThreashold ] )
    {
        theDiffDelayThreashold = myDiffDelayThreashold;
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------------------- 
bool TL1_EQRspBlk::GetNumbrChan(CT_NumberOfChan& theNumbrChan) const
{
    if( true == myBitSet[ INDEX_NumbrChan ] )
    {
        theNumbrChan = myNumbrChan;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetChanLimit(CT_NumberOfChan& theChanLimit) const
{
    if( true == myBitSet[ INDEX_ChanLimit ] )
    {
        theChanLimit = myChanLimit;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetChanRange(CT_ChanRange& theChanRange) const
{
    if( true == myBitSet[ INDEX_ChanRange ] )
    {
        theChanRange = myChanRange;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetLength(CT_Length& theLength) const
{
    if( true == myBitSet[ INDEX_Length ] )
    {
        theLength = myLength;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetFiberType(CT_DCM_FiberType& theFiberType) const
{
    if( true == myBitSet[ INDEX_FiberType ] )
    {
        theFiberType = myFiberType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetIL(CT_TEL_mBm& theIL) const
{
    if( true == myBitSet[ INDEX_IL ] )
    {
        theIL = myIL;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetPreamp(CT_Preamp& thePreamp) const
{
    if (true == myBitSet[INDEX_Preamp])
    {
        thePreamp = myPreamp;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetExtAttn(CT_Extattn& theExtAttn) const
{
    if (true == myBitSet[INDEX_ExtAttn])
    {
        theExtAttn = myExtAttn;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetPostamp(CT_Postamp& thePostamp) const
{
    if (true == myBitSet[INDEX_Postamp])
    {
        thePostamp = myPostamp;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetType(CT_Type& theType) const
{
    if (true == myBitSet[INDEX_Type])
    {
        theType = myType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetSwitchDomain(CT_SwitchDomain& theSwitchDomain) const
{
    if (true == myBitSet[INDEX_SwitchDomain])
    {
        theSwitchDomain = mySwitchDomain;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetSwitchMode(CT_TEL_SwitchMode& theSwitchMode) const
{
    if (true == myBitSet[INDEX_SwitchMode])
    {
        theSwitchMode = mySwitchMode;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetReach(CT_Reach& theReach) const
{
    if (true == myBitSet[INDEX_Reach])
    {
        theReach = myReach;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetUsage(CT_Usage& theUsage) const
{
    if (true == myBitSet[INDEX_Usage])
    {
        theUsage = myUsage;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetCableLength( CT_CableLength& theCableLength) const
{
    if( true == myBitSet[ INDEX_CableLength ] )
    {
    	theCableLength = myCableLength;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetPktShelfType( CT_PktShelfType& thePktShelfType) const
{
    if( true == myBitSet[ INDEX_PktShelfType ] )
    {
    	thePktShelfType = myPktShelfType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetDiskFormatType( CT_DiskFormatType& theDiskFormatType) const
{
    if( true == myBitSet[ INDEX_DiskFormatType ] )
    {
    	theDiskFormatType = myDiskFormatType;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetConnPort( CT_ConnPort& theConnPort, CT_ConnPortRange &theConnPortRange) const
{
    if( true == myBitSet[ INDEX_ConnPort ] )
    {
    	theConnPort = myConnPort;
        theConnPortRange = myConnPortRange;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetLacpSystemPriority(int& thePriority) const
{
    if (true == myBitSet[INDEX_LacpPri])
    {
        thePriority = myLacpSystemPriority;
        return true;
    }
    else
    {
        return false;
    }
}


bool TL1_EQRspBlk::GetLacpSystemId(CT_LacpSystemId& theId) const
{
    if (true == myBitSet[INDEX_LacpId])
    {
        theId = myLacpSystemId;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetModulation(CT_Modulation& theModulation) const
{
    if (true == myBitSet[INDEX_Modulation])
    {
        theModulation = myModulation;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetFanProfile(CT_FanProfile& theFanProfile) const
{
    if( true == myBitSet[INDEX_FanProfile])
    {
        theFanProfile = myFanProfile;
        return true;
    }
    else
    {
        return false;
    }
}

bool TL1_EQRspBlk::GetModVersion(CT_ModVersion& theModVersion) const
{
    if( true == myBitSet[INDEX_ModVersion])
    {
        theModVersion = myModVersion;
        return true;
    }
    else
    {
        return false;
    }
}

